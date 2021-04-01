//
// Created by gurkirat on 25/03/21.
//

#ifndef CATCHME_GAME_H
#define CATCHME_GAME_H

#include "globals.h"
#include "maze.h"
#include "player.h"
#include "imposter.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>


class Game {
public:
    GameState State;
    Player *player;
    int score = 0;
    GameObject *powerup = nullptr, *obstacle = nullptr, *exit_gate = nullptr;
    Imposter *imposter;
    std::chrono::high_resolution_clock::time_point start_time;
    Maze maze;
    bool Keys[1024];
    unsigned int Width, Height;

    Game(unsigned int width, unsigned int height);

    ~Game();

    void Init();

    void ProcessInput(float dt);
    void CheckCollisions();

    void Update(float dt);

    void Render();
    void DrawHUD();

    static void LoadResources();
    static bool DetectCollision(const GameObject& a, const GameObject& b);

    unsigned int GetRemainingTime() const;
};


#endif //CATCHME_GAME_H
