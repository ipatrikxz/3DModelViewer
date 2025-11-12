#pragma once

#include "util.h"

namespace render 
{
    class VertexBuffer
    {

    public:

        void create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void destroy();
        void bind();
        void unbind();
        void draw(int indexCount);

        // Lazy initialization
        void setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void ensureInitialized();

    private:

        std::vector<Vertex> cachedVertices;
        std::vector<unsigned int> cachedIndices;
        bool isInitialized = false;

    protected:

        unsigned int vbo = 0;
        unsigned int vao = 0;
        unsigned int ibo = 0;
    };

}