#pragma once

#include "Engine.h"

#include "window/Window.h"
#include "core/Camera.h"
#include "scene/Scene.h"
#include "editor/Editor.h"
#include "render/Renderer.h"
#include "input/InputManager.h"
#include "common.h"

namespace app
{
    Engine::Engine() = default;
    Engine::~Engine() = default;

    bool Engine::init(int width, int height, const std::string& title)
    {
        // Create components
        _window = std::make_unique<window::RenderWindow>();
        _renderer = std::make_unique<render::Renderer>();
        _input = std::make_unique<input::InputManager>();
        
        // Initialize window
        if (!_window->init(width, height, title)) { return false; }
        if (!_window->initRenderer()) { return false; }

		// Create scene
        _scene = std::make_unique<scene::Scene>();
        _editor = std::make_unique<editor::Editor>();

        // Initialize editor UI
        if (!_editor->init(_window->getNativeWindow()))
        {
            std::cerr << "Failed to initialize editor\n";
            return false;
        }

        setupInputBinding();

        return true;
    }

    int Engine::run()
    {
        if (!init(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, APP_NAME))
        {
            return -1;
        }

        // Main loop
        while (_window->getIsRunning())
        {
            float dt = _editor->getDeltaTime();

            // Process input
            _input->setDeltaTime(dt);
            _input->processInput(*_window);

            // Render UI and scene
            _editor->beginFrame();
            _editor->renderUI(*_scene, *_renderer);
            _editor->endFrame();

            // Swap buffers and poll events
            _window->swapBuffers();
            _window->processEvents();
        }

        return 0;
    }

    void Engine::shutdown()
    {
        if (_editor) _editor->shutdown();
        if (_window) _window->cleanup();
    }

    void Engine::setupInputBinding()
    {
        Camera* camera = _scene->getCamera();
        if (!camera)
        {
            std::cerr << "Error: Camera not found during input setup \n";
            return;
        }

        // Bind camera movement
        _input->setMovementDelegate([camera](float dt, const glm::vec3& inputVec) {
            camera->moveCamera(dt, inputVec);
        });

        // Bind camera look
        _input->setMouseLookDelegate([camera](double offsetX, double offsetY) { 
            camera->lookCamera(offsetX, offsetY); 
        });
    }

}

