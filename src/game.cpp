//
// Created by gurkirat on 25/03/21.
//


#include <iostream>
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "maze.h"

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height),
                                                      maze(MAZE_WIDTH, MAZE_HEIGHT) {
}

Game::~Game() {

}

SpriteRenderer *Renderer;

void Game::Init() {
    ResourceManager::LoadShader("../assets/shaders/vertexShader.glsl", "../assets/shaders/fragmentShader.glsl", nullptr,
                                "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float >(this->Height), 0.0f,
                                      -1.0f, 1.0f);
    auto shader = ResourceManager::GetShader("sprite");
    shader.Use();
    shader.SetInteger("u_Image", 0);
    shader.SetMatrix4f("u_Projection", projection);
    Renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("../assets/textures/smile.png", true, "face");
    ResourceManager::LoadTexture("../assets/textures/wall.png", true, "wall");
    this->maze.Init();
}

void Game::Update(float dt) {

}

void Game::ProcessInput(float dt) {

}

void Game::Render() {
//    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f),
//                         glm::vec2(600.0f, 600.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->maze.Draw(*Renderer);
}