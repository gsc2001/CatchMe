//
// Created by gurkirat on 29/03/21.
//

#include "player.h"
#include "globals.h"
#include "resource_manager.h"

void Player::Move(glm::vec2 diff) {
    this->Position += diff;
    this->Position = glm::clamp(this->Position, glm::vec2(0.0f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

}


Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color) : GameObject(pos, size,
                                                                            ResourceManager::GetTexture("player_0"),
                                                                            color
) {

}

void Player::MoveRight() {
    this->Move(glm::vec2(PLAYER_SPEED, 0));
}

void Player::MoveLeft() {
    this->Move(glm::vec2(-PLAYER_SPEED, 0));
}

void Player::MoveDown() {
    this->Move(glm::vec2(0, PLAYER_SPEED));
}

void Player::MoveUp() {
    this->Move(glm::vec2(0, -PLAYER_SPEED));
}
