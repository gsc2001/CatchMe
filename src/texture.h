//
// Created by gurkirat on 25/03/21.
//

#ifndef CATCHME_TEXTURE_H
#define CATCHME_TEXTURE_H

#include <glad/glad.h>

class Texture2D {
public:
    unsigned int ID;
    unsigned int Width, Height;
    unsigned int Internal_Format, Image_Format, Wrap_S, Wrap_T, Filter_Max, Filter_Min;

    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char *data);

    void Bind() const;

};


#endif //CATCHME_TEXTURE_H
