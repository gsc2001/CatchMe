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
    glm::vec2 Position, Velocity, Size;
    glm::vec3 Color;
    float Rotation;
    bool IsActive;
    Texture2D Sprite;


    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, Texture2D sprite,
               glm::vec2 velocity = glm::vec2(0.0f, 0.0f), float rotation = 0.0f);

    virtual void Draw(SpriteRenderer &renderer);
    void Destroy();
    ~GameObject();

};


#endif //CATCHME_GAME_OBJECT_H
