//
// Created by gurkirat on 25/03/21.
//

#include <iostream>
#include "shader.h"

Shader &Shader::Use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    unsigned int vertexS, fragmentS, geometryS;

    vertexS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexS, 1, &vertexSource, NULL);
    glCompileShader(vertexS);
    checkCompileErrors(vertexS, "VERTEX");

    fragmentS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentS, 1, &fragmentSource, NULL);
    glCompileShader(fragmentS);
    checkCompileErrors(fragmentS, "FRAGMENT");

    if (geometrySource != nullptr) {
        geometryS = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryS, 1, &geometrySource, NULL);
        glCompileShader(geometryS);
        checkCompileErrors(geometryS, "GEOMETRY");
    }

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexS);
    glAttachShader(this->ID, fragmentS);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, geometryS);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    // we can now delete the shaders as they linked to the program now
    glDeleteShader(vertexS);
    glDeleteShader(fragmentS);
    if (geometrySource != nullptr)
        glDeleteShader(geometryS);

}

void Shader::SetFloat(const char *name, float value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char *name, int value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4f(const char *name, const glm::mat4 &value, bool useShader) {
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(value));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

