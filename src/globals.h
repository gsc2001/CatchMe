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
    STOP,
    UP,
    DOWN,
    LEFT, RIGHT
};

const unsigned int SCREEN_WIDTH = 900;
const unsigned int SCREEN_HEIGHT = 900;
const unsigned int WINDOW_WIDTH = 1200;

const float PLAYER_SPEED = 2.5f;
const float COLLISION_BUFFER = 3.0f;
const int SCORE_INC = 20;
const int SCORE_DEC = 20;


#endif //CATCHME_GLOBALS_H
