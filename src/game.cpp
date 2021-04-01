//
// Created by gurkirat on 25/03/21.
//


#include <iostream>
#include <random>
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "maze.h"

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height),
                                                      maze() {
}


Game::~Game() {

}

SpriteRenderer *Renderer;
TextRenderer *Text;

void Game::Init() {
    LoadResources();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float >(this->Height), 0.0f,
                                      -1.0f, 1.0f);
    auto shader = ResourceManager::GetShader("sprite");
    shader.Use();
    shader.SetInteger("u_Image", 0);
    shader.SetMatrix4f("u_Projection", projection);
    Renderer = new SpriteRenderer(shader);
    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("../assets/fonts/arial.ttf", 24);
    this->maze.Init();
    this->player = new Player(maze.GetStart(), maze.GetWallSize() * glm::vec2(0.6f, 1.0f) / 1.5f);
    this->imposter = new Imposter(maze.GetImposterPos(), maze.GetWallSize() * glm::vec2(0.6f, 1.0f) / 1.5f);
    this->exit_gate = new GameObject(maze.GetEnd(), maze.GetWallSize() * glm::vec2(0.8f, 0.5f),
                                     ResourceManager::GetTexture("exit"));
    this->start_time = std::chrono::high_resolution_clock::now();
}

unsigned int Game::GetRemainingTime() const {
    auto end = std::chrono::high_resolution_clock::now();
    auto time_diff = std::chrono::duration_cast<std::chrono::seconds>(end - this->start_time);
    return TIME_LIMIT - time_diff.count();
}

void Game::Update(float dt) {
    if (State != GAME_ACTIVE)
        return;
    this->CheckCollisions();

    if (this->imposter->IsActive) {
        this->imposter->Update(this->player->Position, this->maze.directions, this->maze.GetWallSize(), this->maze.N);
    }

    // check game over
    if (this->GetRemainingTime() <= 0) {
        State = GAME_LOOSE;
    }

}

void Game::ProcessInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        auto current_pos = this->player->Position;
        bool any_key_pressed = false;
        if (this->Keys[GLFW_KEY_A]) {
            any_key_pressed = true;
            this->player->MoveLeft();
        }
        if (this->Keys[GLFW_KEY_D]) {

            any_key_pressed = true;
            this->player->MoveRight();
        }
        if (this->Keys[GLFW_KEY_W]) {

            any_key_pressed = true;
            this->player->MoveUp();
        }
        if (this->Keys[GLFW_KEY_S]) {

            any_key_pressed = true;
            this->player->MoveDown();
        }
        if (!any_key_pressed) {
            this->player->ResetFrames();
        }

        // detect collision with wall
        for (const auto &wall : this->maze.walls) {
            if (Game::DetectCollision(wall, *this->player)) {
                this->player->Position = current_pos;
            }
        }

    }
}

void Game::Render() {
    if (State == GAME_ACTIVE) {
        this->maze.Draw(*Renderer);
        this->player->Draw(*Renderer);
        if (this->imposter->IsActive)
            this->imposter->Draw(*Renderer);
        if (this->powerup != nullptr) {
            this->powerup->Draw(*Renderer);
        }
        if (this->obstacle != nullptr) {
            this->obstacle->Draw(*Renderer);
        }
        this->exit_gate->Draw(*Renderer);

        this->DrawHUD();
    } else if (State == GAME_WIN) {
        Text->RenderText("YOU WON !!!", SCREEN_HEIGHT / 4.0f, WINDOW_WIDTH / 4.0f, 2);
    } else if (State == GAME_LOOSE) {
        Text->RenderText("YOU Lose :(", SCREEN_HEIGHT / 4.0f, WINDOW_WIDTH / 4.0f, 2);
    }
}

void Game::LoadResources() {
    ResourceManager::LoadShader("../assets/shaders/sprite_vs.glsl",
                                "../assets/shaders/sprite_fs.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("../assets/textures/smile.png", true, "face");
    ResourceManager::LoadTexture("../assets/textures/wall.png", true, "wall");

    for (int j = 0; j <= 1; j++) {

        for (int i = 0; i <= 23; i++) {
            ResourceManager::LoadTexture(
                    ("../assets/textures/player/" + std::to_string(j) + "/" + std::to_string(i) + ".png").c_str(), true,
                    "player_" + std::to_string(j) + "_" + std::to_string(i));
        }
    }
    ResourceManager::LoadTexture("../assets/textures/check.jpg", false, "vapour_task");
    ResourceManager::LoadTexture("../assets/textures/red_button.png", true, "powerup_task");
    ResourceManager::LoadTexture("../assets/textures/coin.png", true, "coin");
    ResourceManager::LoadTexture("../assets/textures/bomb.png", true, "bomb");
    ResourceManager::LoadTexture("../assets/textures/board.jpg", false, "board");
    ResourceManager::LoadTexture("../assets/textures/exit.png", true, "exit");
    ResourceManager::LoadShader("../assets/shaders/text_vs.glsl",
                                "../assets/shaders/text_fs.glsl", nullptr, "text");
}

bool Game::DetectCollision(const GameObject &a, const GameObject &b) {
    bool collisionX = a.Position.x + a.Size.x + COLLISION_BUFFER >= b.Position.x &&
                      b.Position.x + b.Size.x + COLLISION_BUFFER >= a.Position.x;
    bool collisionY = a.Position.y + a.Size.y + COLLISION_BUFFER >= b.Position.y &&
                      b.Position.y + b.Size.y + COLLISION_BUFFER >= a.Position.y;
    return collisionX && collisionY;
}

void Game::CheckCollisions() {
    // player and vaporize task
    if (State != GAME_ACTIVE) {
        return;
    }
    if (maze.vap_task->IsActive && Game::DetectCollision(*maze.vap_task, *player)) {
        this->imposter->Vaporize();
        this->maze.vap_task->IsActive = false;
    }
    // player and powerup task
    if (maze.pow_task->IsActive && Game::DetectCollision(*maze.pow_task, *player)) {
        // TODO: Spawn powerup / obstacle
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> r2(0, 1);
        std::uniform_int_distribution<int> r_walls(0, this->maze.free_spaces.size());

        bool is_powerup = r2(mt);
        std::cout << is_powerup << "\n";

        auto position = this->maze.free_spaces[r_walls(mt)];
        auto wall_sz = this->maze.GetWallSize();
        if (is_powerup) {
            // powerup
            this->powerup = new GameObject(wall_sz * position + wall_sz / 4.0f, wall_sz / 2.0f,
                                           ResourceManager::GetTexture("coin"));
            std::cout << this->powerup->Position.x << " " << this->powerup->Position.y << "\n";
        } else {
            this->obstacle = new GameObject(wall_sz * position + wall_sz * glm::vec2(1 / 4.0f, 0.1f),
                                            wall_sz * glm::vec2(0.5f, 0.8f), ResourceManager::GetTexture("bomb"));
            std::cout << this->obstacle->Position.x << " " << this->obstacle->Position.y << "\n";
        }
        this->maze.pow_task->IsActive = false;
    }

    // player and powerup
    if (powerup != nullptr and Game::DetectCollision(*powerup, *player)) {
        this->score += SCORE_INC;
        delete this->powerup;
        this->powerup = nullptr;
    }

    if (obstacle != nullptr and Game::DetectCollision(*obstacle, *player)) {
        this->score -= SCORE_DEC;
        delete this->obstacle;
        this->obstacle = nullptr;
    }
    if (this->imposter->IsActive) {
        if (Game::DetectCollision(*this->imposter, *this->player)) {
            State = GAME_LOOSE;
        }
    }

    auto pending_tasks = (int) (maze.vap_task->IsActive) + (int) (maze.pow_task->IsActive);
    if (Game::DetectCollision(*this->exit_gate, *this->player) and pending_tasks == 0) {
        State = GAME_WIN;
    }
}

void Game::DrawHUD() {
    GameObject background(glm::vec2(SCREEN_WIDTH + 5, 0), glm::vec2(WINDOW_WIDTH - SCREEN_WIDTH - 12),
                          ResourceManager::GetTexture("board"));
    background.Draw(*Renderer);
    Text->RenderText("Score: " + std::to_string(this->score), SCREEN_WIDTH + 20, 20, 1);
    auto completed_tasks = (int) (maze.vap_task->IsActive) + (int) (maze.pow_task->IsActive);
    Text->RenderText("Tasks: " + std::to_string(2 - completed_tasks) + "/2", SCREEN_WIDTH + 20, 80, 1);
    Text->RenderText("Time Remaining: " + std::to_string(this->GetRemainingTime()), SCREEN_WIDTH + 20, 140, 1);

}
