//
// Created by gurkirat on 25/03/21.
//

#ifndef CATCHME_SPRITE_RENDERER_H
#define CATCHME_SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

class SpriteRenderer {
private:
    Shader shader;
    unsigned int VAO{};

    void initRenderData();

public:
    explicit SpriteRenderer(Shader &shader);

    ~SpriteRenderer();

    void DrawSprite(Texture2D &texture, const glm::vec2 &position, const glm::vec2 &size, const float &rotate,
                    const glm::vec3 &color);

};


#endif //CATCHME_SPRITE_RENDERER_H
