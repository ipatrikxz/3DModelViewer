#pragma once

#include "PropertyPanel.h"

#include "Util.h"
#include "scene/Scene.h"
#include "core/Camera.h"

#include <functional>

namespace editor
{
    // ------------------------------------------------------------------
	// render the editor panel
    void PropertyPanel::render(scene::Scene& scene)
    {
        ImGui::Begin("Properties");
		drawMeshControls(scene);
        drawLightControls(scene);
        drawCameraInfo(scene);
        ImGui::End();

        ImGui::Begin("Stats");
        drawPerformanceInfo(scene);
        ImGui::End();
    }

    // ------------------------------------------------------------------
    // mesh loading controls
    void PropertyPanel::drawMeshControls(scene::Scene& scene)
    {
        if (ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // import Model dialog
            if (ImGui::Button("Open Model..."))
            {
                modelFileDialog.Open();
            }
            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentModelFile.c_str());

            // texture file dialog
            if (ImGui::Button("Open Texture..."))
            {
                textureFileDialog.Open();
            }
            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentTextureFile.c_str());
        }

        // handle model file dialog
        modelFileDialog.Display();
        if (modelFileDialog.HasSelected())
        {
            auto model_path = modelFileDialog.GetSelected();
			currentModelFile = model_path.parent_path().filename().string();
			scene.loadModel(model_path.string());
            modelFileDialog.ClearSelected();
        }

        // handle texture file dialog
        textureFileDialog.Display();
        if (textureFileDialog.HasSelected())
        {
            auto texture_path = textureFileDialog.GetSelected();
			currentTextureFile = texture_path.parent_path().filename().string();
			scene.loadTexture(texture_path.string());
            textureFileDialog.ClearSelected();
        }
    }

    // ------------------------------------------------------------------
    // scene lighting controls
    void PropertyPanel::drawLightControls(scene::Scene& scene)
    {
        
        if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
        {

            Lights& lights = scene.getLights();
            DirLight& dirLight = lights.getDirectionalLight();

            ImGui::Separator();
            ImGui::Text("Directional Light");

            // light direction
            float dir[3] = { dirLight.direction.x, dirLight.direction.y, dirLight.direction.z };
            if (ImGui::DragFloat3("direction", dir, 0.01f, -1.0f, 1.0f))
            {
                dirLight.direction = glm::vec3(dir[0], dir[1], dir[2]);
            }

			// color ambient
            float ambient[3] = { dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z };
            if (ImGui::ColorEdit3("ambient", ambient))
            {
                dirLight.ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
            }

            // color diffuse
            float diffuse[3] = { dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z };
            if (ImGui::ColorEdit3("diffuse", diffuse))
            {
                dirLight.diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
            }

            // color specular
            float specular[3] = { dirLight.specular.x, dirLight.specular.y, dirLight.specular.z };
            if (ImGui::ColorEdit3("specular", specular))
            {
                dirLight.specular = glm::vec3(specular[0], specular[1], specular[2]);
            }

            ImGui::Separator();

            // point Light
            ImGui::Text("Point Light Position");
            glm::vec3 pointPos = lights.getPointLightPosition();
            float pos[3] = { pointPos.x, pointPos.y, pointPos.z };
            if (ImGui::DragFloat3("position", pos, 0.1f, -10.0f, 10.0f))
            {
                lights.setPointLightPosition(glm::vec3(pos[0], pos[1], pos[2]));
            }

            ImGui::Separator();
        }
    }

    // ------------------------------------------------------------------
    // camera info
    void PropertyPanel::drawCameraInfo(scene::Scene& scene)
    {
        
        if (ImGui::CollapsingHeader("Camera"))
        {
            ImGui::Separator();
            ImGui::Text("Location");
            ImGui::Separator();
            ImGui::Text("X: %.2f", scene.getCamera()->getLocation().x);
            ImGui::Text("Y: %.2f", scene.getCamera()->getLocation().y);
            ImGui::Text("Z: %.2f", scene.getCamera()->getLocation().z);

            ImGui::Separator();
            ImGui::Text("Rotation");
            ImGui::Separator();
            ImGui::Text("Pitch: %.2f", scene.getCamera()->getRotation().x);
            ImGui::Text("Yaw: %.2f", scene.getCamera()->getRotation().y);
            ImGui::Text("Roll: %.2f", scene.getCamera()->getRotation().z);
        }
    }

    // ------------------------------------------------------------------
    // performance info
    void PropertyPanel::drawPerformanceInfo(scene::Scene& scene)
    {    
        const ImGuiIO& io = ImGui::GetIO();
        float fps = io.Framerate;
        float frameTime = 1.0f / std::max(fps, 0.01f);

        static const int HISTORY_SIZE = 100;
        static float fpsHistory[HISTORY_SIZE] = {};
        static float frameTimeHistory[HISTORY_SIZE] = {};
        static int offset = 0;

        fpsHistory[offset] = fps;
        frameTimeHistory[offset] = frameTime;
        offset = (offset + 1) % HISTORY_SIZE;

        // FPS Graph
        char fpsOverlay[32];
        sprintf(fpsOverlay, "FPS: %.1f", fps);
        ImGui::PlotHistogram("##fps",
            fpsHistory,
            HISTORY_SIZE,
            offset,
            fpsOverlay,
			0.0f,   // scale min
			420.0f, // scale max
            ImVec2(200, 80));

        // Frame Time Graph
        char frameTimeOverlay[32];
        sprintf(frameTimeOverlay, "Frame Time: %.1f ms", frameTime * 1000);
        ImGui::PlotHistogram("##frametime",
            frameTimeHistory,
            HISTORY_SIZE,
            offset,
            frameTimeOverlay,
			0.0f,   // scale min
            0.05f,  // scale max
            ImVec2(200, 80));
    }

}