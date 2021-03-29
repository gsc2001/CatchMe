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


class Game {
public:
    GameState State;
    Player *player;
    Imposter *imposter;
    Maze maze;
    bool Keys[1024];
    unsigned int Width, Height;

    Game(unsigned int width, unsigned int height);

    ~Game();

    void Init();

    void ProcessInput(float dt);

    void Update(float dt);

    void Render();


    static void LoadResources();
    static bool DetectCollision(const GameObject& a, const GameObject& b);
};


#endif //CATCHME_GAME_H
