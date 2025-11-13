#pragma once

#include <memory>
#include <GLFW/glfw3.h>

namespace scene { class Scene; }
namespace render { class Renderer; }

namespace editor
{
    class Viewport;
    class PropertyPanel;

	// Editor class manages the GUI editor using ImGui
    class Editor
    {
    public:
        Editor();
        ~Editor();

        bool init(GLFWwindow* window);
        void shutdown();

        void beginFrame();
        void renderUI(scene::Scene& scene, render::Renderer& renderer);
        void endFrame();

        float getDeltaTime() const { return deltaTime; }

    private:
        void setupDockspace();
        void setupStyle();
        void updateDeltaTime();

        std::unique_ptr<Viewport> viewport;
        std::unique_ptr<PropertyPanel> editorPanel;

        float deltaTime;
        float lastFrameTime;
    };
}