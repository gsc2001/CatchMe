//
// Created by gurkirat on 25/03/21.
//

#ifndef CATCHME_GLOBALS_H
#define CATCHME_GLOBALS_H

#include <iostream>

enum GameState {
    GAME_ACTIVE,
    GAME_WIN,
    GAME_LOOSE
};

enum Movement {
    UP,
    DOWN,
    LEFT, RIGHT, STOP
};

const unsigned int SCREEN_WIDTH = 900;
const unsigned int SCREEN_HEIGHT = 900;

const unsigned int MAZE_WIDTH = 4;
const unsigned int MAZE_HEIGHT = 4;
const float PLAYER_SPEED = 3.0f;


#endif //CATCHME_GLOBALS_H
