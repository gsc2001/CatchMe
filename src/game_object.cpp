//
// Created by gurkirat on 26/03/21.
//

#include "game_object.h"


GameObject::GameObject()
        : Position(0.0f, 0.0f),
        Size(1.0f, 1.0f),
        Color(1.0f),
        Rotation(0.0f)
        {

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, float rotation) : Position(
        pos), Size(size), Color(color), Sprite(sprite), Rotation(rotation), IsActive(true) {

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


