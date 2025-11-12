#pragma once

#include <string>

#include "window/Window.h"
#include "input/InputManager.h"
#include "ui/UIContext.h"

namespace app 
{
    class Engine 
    {

    public:

        Engine();
        ~Engine();
        
        int run();
		void shutDown();

        void showToastMessage();

    private:

        std::unique_ptr<window::RenderWindow> window;

        // components
        std::unique_ptr<ui::UIContext> uiContext;
        std::unique_ptr<input::InputManager> inputManager;

        bool init(int width, int height, const std::string& title);
    };
}
