//
// Created by gurkirat on 29/03/21.
//

#include "player.h"
#include "globals.h"
#include "resource_manager.h"

void Player::Move(glm::vec2 diff) {
    this->Position += diff;
    this->Position = glm::clamp(this->Position, glm::vec2(0.0f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
    this->UpdateTexture();
}


Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color) :
        direction(1), frame(0), GameObject(pos, size, ResourceManager::GetTexture("player_1_9"), color) {

}

void Player::MoveRight() {
    this->Move(glm::vec2(PLAYER_SPEED, 0));
    this->direction = 1;


}

void Player::MoveLeft() {
    this->Move(glm::vec2(-PLAYER_SPEED, 0));
    this->direction = 0;
}

void Player::MoveDown() {
    this->Move(glm::vec2(0, PLAYER_SPEED));
}

void Player::MoveUp() {
    this->Move(glm::vec2(0, -PLAYER_SPEED));
}

void Player::UpdateTexture() {
    this->frame += 1;
    this->frame %= 24;
    this->Sprite = ResourceManager::GetTexture("player_" + std::to_string(direction) + "_" + std::to_string(frame));
}

void Player::ResetFrames() {
    this->frame = 0;
    this->UpdateTexture();

}
