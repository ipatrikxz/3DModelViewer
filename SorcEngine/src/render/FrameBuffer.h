#pragma once

#include <iostream>

namespace render 
{
    class FrameBuffer
    {

    public:

		FrameBuffer();
        void create(int width, int height);
        void bind();
        void unbind();
        void destroy();
        unsigned int getTexture();

        void resize(int width, int height);

    protected:

        unsigned int fbo;
        unsigned int textureId;
        unsigned int depthId;
        int width;
        int height;
    };

}