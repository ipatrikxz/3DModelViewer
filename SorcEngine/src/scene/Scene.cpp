#pragma once

#include "Scene.h"

#include "scene/Model.h"
#include "core/Camera.h"

namespace scene 
{
    Scene::Scene() 
    {
        camera = std::make_shared<Camera>();
        
        // default transform
        modelTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
        modelTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        modelTransform.rotation = glm::vec3(0.0f);
        
        // load default model
        loadModel("res/models/sphere/Sphere.obj");
        loadTexture("res/textures/wall.jpg");
    }

    void Scene::loadModel(const std::string& filepath) 
    {
        model = std::make_shared<Model>();
        model->load(filepath);
    }

    void Scene::loadTexture(const std::string& filepath)
    {
        if (!model) return;
        model->loadTexture(filepath);
    }
}