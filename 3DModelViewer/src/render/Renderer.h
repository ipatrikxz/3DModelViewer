#pragma once

#include "scene/Scene.h"

namespace render
{
    // Renderer takes scene data and draws it
    // All OpenGL calls happen here
    class Renderer
    {
    public:
        Renderer() = default;

        void render(scene::Scene& scene);

    private:
        void renderModel(Model& model, Transform& transform, Lights& lights, Camera& camera);
        void setupLighting(Shader& shader, Lights& lights, Camera& camera);
    };
}