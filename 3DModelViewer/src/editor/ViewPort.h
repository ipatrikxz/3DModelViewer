#pragma once

#include <memory>
#include <imgui.h>
#include "render/FrameBuffer.h"

namespace scene { class Scene; }
namespace render { class Renderer; }

namespace editor
{
	// Viewport renders a Scene within an imGui window
    class Viewport
    {
    public:
        Viewport();

        void render(scene::Scene& scene, render::Renderer& renderer);

    private:
        void handleResize(scene::Scene& scene);

        std::unique_ptr<render::FrameBuffer> framebuffer;
        float width;
        float height;
    };
}