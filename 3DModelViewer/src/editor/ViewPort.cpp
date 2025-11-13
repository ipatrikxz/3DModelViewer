#include "Viewport.h"

#include "scene/Scene.h"
#include "render/Renderer.h"
#include "core/Camera.h"
#include <GLFW/glfw3.h>

namespace editor
{
    Viewport::Viewport()
        : width(0), height(0)
    {
        framebuffer = std::make_unique<render::FrameBuffer>();
    }

    void Viewport::render(scene::Scene& scene, render::Renderer& renderer)
    {
        ImGui::Begin("Scene");

        // Handle resize
        ImVec2 currentSize = ImGui::GetContentRegionAvail();
        if ((int)currentSize.x != (int)width || (int)currentSize.y != (int)height)
        {
            width = currentSize.x;
            height = currentSize.y;
            handleResize(scene);
        }

        // Render to framebuffer
        framebuffer->bind();
        renderer.render(scene);
        framebuffer->unbind();

        // Display in ImGui
        ImGui::Image(framebuffer->getTextureID(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }

    void Viewport::handleResize(scene::Scene& scene)
    {
        framebuffer->resize((int)width, (int)height);

        Camera* camera = scene.getCamera();
        if (camera && height > 0)
        {
            camera->setAspectRatio(width / height);
        }
    }
}