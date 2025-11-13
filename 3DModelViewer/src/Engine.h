#pragma once

#include <string>

#include "window/Window.h"
#include <iostream>

namespace window { class RenderWindow; }
namespace scene { class Scene; }
namespace render { class Renderer; }
namespace editor { class Editor; }
namespace input { class InputManager; }

namespace app 
{
    class Engine 
    {

    public:

        Engine();
        ~Engine();
        
        int run();

    private:

        bool init(int width, int height, const std::string& title);
		void shutdown();
        void setupInputBinding();
        void showWelcomeMessage();

        std::unique_ptr<window::RenderWindow> _window;
        std::unique_ptr<scene::Scene> _scene;
        std::unique_ptr<render::Renderer> _renderer;
        std::unique_ptr<editor::Editor> _editor;
        std::unique_ptr<input::InputManager> _input;
    };
}
