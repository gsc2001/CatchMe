//
// Created by gurkirat on 25/03/21.
//

#ifndef CATCHME_RESOURCE_MANAGER_H
#define CATCHME_RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <glad/glad.h>

#include "shader.h"
#include "texture.h"


class ResourceManager {
private:
    ResourceManager() {};

    static Shader
    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

    static Texture2D loadTextureFromFile(const char *file, bool alpha);

public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    static Shader
    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);

    static Shader& GetShader(const std::string& name);

    static Texture2D LoadTexture(const char *file, bool alpha, const std::string& name);

    static Texture2D& GetTexture(const std::string& name);

    static void Clear();
};


#endif //CATCHME_RESOURCE_MANAGER_H
