//
// Created by gurkirat on 29/03/21.
//

#include "imposter.h"
#include "maze.h"


void Imposter::Update(glm::vec2 player_pos, Movement **directions, glm::vec2 wall_size) {
    bool check_dir = false;
    switch (current_dir) {
        case UP:
            check_dir = (next_mov.y >= this->Position.y);
            break;
        case DOWN:
            check_dir = (next_mov.y <=  this->Position.y);
            break;
        case LEFT:
            check_dir = (next_mov.x >=  this->Position.x);
            break;
        case RIGHT:
            check_dir = (next_mov.x <=  this->Position.x);
            break;
        case STOP:
            check_dir = true;
            break;
    }
    if (check_dir) {
        auto cord_p = glm::floor(player_pos / wall_size);
        auto cord_i = glm::floor(this->Position / wall_size);
        int p_i = cord_p.y, p_j = cord_p.x;
        int i_i = cord_i.y, i_j = cord_i.x;
        int p = p_i * MAZE_WIDTH + p_j, imposter = i_i * MAZE_WIDTH + i_j;

        auto direction = directions[imposter][p];
        current_dir = direction;
        std::cout << p << " " << imposter << " " << current_dir << "\n";
         switch (direction) {
            case UP:
                next_mov = Position - glm::vec2(0, wall_size.y);
                break;
            case DOWN:
                next_mov = Position + glm::vec2(0, wall_size.y);
                break;
            case LEFT:
                next_mov = Position - glm::vec2(wall_size.x, 0);
                break;
            case RIGHT:
                next_mov = Position + glm::vec2(wall_size.x, 0);
                break;
            case STOP:
#ifdef DEBUG
                std::cout << "Wrong movement" << "\n";
                exit(1);
#endif
                break;
        }

    }
    // now move
    AutoMove();
}

void Imposter::AutoMove() {
    switch (current_dir) {
        case UP:
            MoveUp();
            break;
        case DOWN:
            MoveDown();
            break;
        case LEFT:
            MoveLeft();
            break;
        case RIGHT:
            MoveRight();
            break;
        case STOP:
            break;
    }

}

void Imposter::Vapourize() {
    this->Destroy();
}
