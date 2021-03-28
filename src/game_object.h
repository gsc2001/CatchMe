//
// Created by gurkirat on 26/03/21.
//

#ifndef CATCHME_GAME_OBJECT_H
#define CATCHME_GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"


class GameObject {
public:
    glm::vec2 Position, Size;
    glm::vec3 Color;
    float Rotation;
    bool IsActive;
    Texture2D Sprite;

    GameObject();

    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), float rotation = 0);

    virtual void Draw(SpriteRenderer &renderer);

    void Destroy();

    ~GameObject();

};


#endif //CATCHME_GAME_OBJECT_H
