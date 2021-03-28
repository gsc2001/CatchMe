//
// Created by gurkirat on 26/03/21.
//

#include "game_object.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, Texture2D sprite, glm::vec2 velocity,
                       float rotation) : Position(pos), Size(size), Color(color), Sprite(sprite),
                                         Velocity(velocity), Rotation(rotation), IsActive(true) {

}

void GameObject::Draw(SpriteRenderer &renderer) {
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Destroy() {
    this->IsActive = false;
}

GameObject::~GameObject() {
    this->Destroy();
}

