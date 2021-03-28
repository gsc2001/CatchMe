//
// Created by gurkirat on 29/03/21.
//

#ifndef CATCHME_PLAYER_H
#define CATCHME_PLAYER_H

#include "game_object.h"

class Player : public GameObject {
public:
    Player() : GameObject() {}

    Player(glm::vec2 pos, glm::vec2 size);

    void Move(glm::vec2 diff);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();



};


#endif //CATCHME_PLAYER_H
