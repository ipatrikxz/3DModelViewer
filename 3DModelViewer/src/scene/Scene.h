#pragma once

#include <memory>
#include <string>
#include "core/Camera.h"
#include "scene/Model.h"
#include "light/Lights.h"
#include "Util.h"

namespace scene
{
	// Scene holds data for rendering: Camera, Model, Lights, Transforms
    class Scene
    {
    public:
        Scene();

        void loadModel(const std::string& filepath);
        void loadTexture(const std::string& filepath);

        Camera* getCamera() { return camera.get(); }
        Model* getModel() { return model.get(); }
        Lights& getLights() { return lights; }
        Transform& getModelTransform() { return modelTransform; }

    private:
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Model> model;
        Transform modelTransform;
        Lights lights;
    };
}