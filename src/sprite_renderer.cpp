//
// Created by gurkirat on 25/03/21.
//

#include "sprite_renderer.h"

void
SpriteRenderer::DrawSprite(Texture2D &texture, const glm::vec2 &position, const glm::vec2 &size, const float &rotate,
                           const glm::vec3 &color) {

    this->shader.Use();
    // Create start with identity
    glm::mat4 model = glm::mat4(1.0f);
    // translate
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // rotate
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    // scale
    model = glm::scale(model, glm::vec3( size, 1.0f));

    this->shader.SetMatrix4f("u_Model", model);
    this->shader.SetVector3f("u_SpriteCol", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->VAO);
}

SpriteRenderer::SpriteRenderer(Shader &shader) {

    this->shader = shader;
    this->initRenderData();
}

void SpriteRenderer::initRenderData() {
    unsigned int VBO;
    // configure a basic cell a square (2 triangles)
    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    // texture cord
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
