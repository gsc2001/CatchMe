//
// Created by gurkirat on 29/03/21.
//

#ifndef CATCHME_IMPOSTER_H
#define CATCHME_IMPOSTER_H

#include "player.h"
#include "globals.h"

class Imposter : public Player {
private:
    Movement current_dir = STOP;
    glm::vec2 next_mov;
public:
    Imposter(glm::vec2 pos, glm::vec2 size) : Player(pos, size, glm::vec3(1.0f, 0.0f, 1.0f)) {}

    void Update(glm::vec2 player_pos, Movement **directions, glm::vec2 wall_size);
    void AutoMove();

};


#endif //CATCHME_IMPOSTER_H
