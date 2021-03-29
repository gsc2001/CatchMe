//
// Created by gurkirat on 29/03/21.
//

#ifndef CATCHME_IMPOSTER_H
#define CATCHME_IMPOSTER_H

#include "player.h"

class Imposter: public  Player{
public:
    Imposter(glm::vec2 pos, glm::vec2 size): Player(pos, size, glm::vec3(1.0f, 0.0f, 1.0f)) {}
    void GetShortedPath();

};


#endif //CATCHME_IMPOSTER_H
