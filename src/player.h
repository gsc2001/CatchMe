//
// Created by gurkirat on 29/03/21.
//

#ifndef CATCHME_PLAYER_H
#define CATCHME_PLAYER_H

#include "game_object.h"

class Player : public GameObject {
public:
    // direction 1 = right , 0 = left
    int direction = 1;
    int frame = 0;
    Player() : GameObject() {}

    Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));

    void Move(glm::vec2 diff);

    void MoveLeft();

    void MoveRight();

    void MoveUp();

    void MoveDown();

    void UpdateTexture();


};


#endif //CATCHME_PLAYER_H
