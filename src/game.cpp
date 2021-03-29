//
// Created by gurkirat on 25/03/21.
//


#include <iostream>
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "maze.h"

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height),
                                                      maze(MAZE_HEIGHT, MAZE_WIDTH) {
}

Game::~Game() {

}

SpriteRenderer *Renderer;

void Game::Init() {
    LoadResources();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float >(this->Height), 0.0f,
                                      -1.0f, 1.0f);
    auto shader = ResourceManager::GetShader("sprite");
    shader.Use();
    shader.SetInteger("u_Image", 0);
    shader.SetMatrix4f("u_Projection", projection);
    Renderer = new SpriteRenderer(shader);
    this->maze.Init();
    this->player = new Player(maze.GetStart(), maze.GetWallSize() * glm::vec2(0.6f, 1.0f) / 1.5f);
    this->imposter = new Imposter(maze.GetImposterPos(), maze.GetWallSize() * glm::vec2(0.6f, 1.0f) / 1.5f);
}

void Game::Update(float dt) {
    this->imposter->Update(this->player->Position, this->maze.directions, this->maze.GetWallSize());
    if (Game::DetectCollision(*this->imposter, *this->player)) {
        State = GAME_LOOSE;
#ifdef DEBUG
        std::cout << "YOU LOST" << "\n";
        exit(0);
    }
#endif
}

void Game::ProcessInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        auto current_pos = this->player->Position;
        if (this->Keys[GLFW_KEY_A])
            this->player->MoveLeft();
        if (this->Keys[GLFW_KEY_D])
            this->player->MoveRight();
        if (this->Keys[GLFW_KEY_W])
            this->player->MoveUp();
        if (this->Keys[GLFW_KEY_S])
            this->player->MoveDown();

        // detect collision with wall
        for (const auto &wall : this->maze.walls) {
            if (Game::DetectCollision(wall, *this->player)) {
                this->player->Position = current_pos;
            }
        }
    }
}

void Game::Render() {
//    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f),
//                         glm::vec2(600.0f, 600.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->maze.Draw(*Renderer);
    this->player->Draw(*Renderer);
    this->imposter->Draw(*Renderer);
}

void Game::LoadResources() {
    ResourceManager::LoadShader("../assets/shaders/vertexShader.glsl",
                                "../assets/shaders/fragmentShader.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("../assets/textures/smile.png", true, "face");
    ResourceManager::LoadTexture("../assets/textures/wall.png", true, "wall");
    ResourceManager::LoadTexture("../assets/textures/player/0.png", true, "player");
}

bool Game::DetectCollision(const GameObject &a, const GameObject &b) {
    bool collisionX = a.Position.x + a.Size.x + COLLISION_BUFFER >= b.Position.x &&
                      b.Position.x + b.Size.x + COLLISION_BUFFER >= a.Position.x;
    bool collisionY = a.Position.y + a.Size.y + COLLISION_BUFFER >= b.Position.y &&
                      b.Position.y + b.Size.y + COLLISION_BUFFER >= a.Position.y;
    return collisionX && collisionY;
}
