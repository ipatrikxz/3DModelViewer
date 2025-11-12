#pragma once

#include "EditorPanel.h"

#include "Util.h"
#include "Scene.h"
#include "core/Camera.h"

#include <functional>

namespace ui 
{
    void EditorPanel::render(Scene& scene)
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
    void EditorPanel::drawMeshControls(ui::Scene& scene)
    {
        if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // import Mesh dialog
            if (ImGui::Button("Open Mesh..."))
            {
                fileDialog.Open();
            }

            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentFile.c_str());

            // texture file dialog
            if (ImGui::Button("Open Texture..."))
            {
                textureFileDialog.Open();
            }

            ImGui::SameLine(0, 5.0f);
            ImGui::Text(currentTextureFile.c_str());
        }

        // handle mesh file dialog
        fileDialog.Display();
        if (fileDialog.HasSelected())
        {
            auto file_path = fileDialog.GetSelected().string();
            currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);
            meshLoadCallback(file_path);
            fileDialog.ClearSelected();
        }

        // handle texture file dialog
        textureFileDialog.Display();
        if (textureFileDialog.HasSelected())
        {
            auto texture_path = textureFileDialog.GetSelected().string();
            currentTextureFile = texture_path.substr(texture_path.find_last_of("/\\") + 1);
            textureLoadCallback(texture_path);
            textureFileDialog.ClearSelected();
        }
    }

    // ------------------------------------------------------------------
    // scene lighting controls
    void EditorPanel::drawLightControls(ui::Scene& scene)
    {
        
        if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
        {

            // capture reference to directional light
            DirLight& dirLight = scene.getLights().getDirectionalLight();

            // destruct direction vector
            float dir[3] = { dirLight.direction.x, dirLight.direction.y, dirLight.direction.z };

            ImGui::Separator();
            ImGui::Text("Directional Light");

            if (ImGui::DragFloat3("direction", dir, 0.01f, -1.0f, 1.0f, "%.3f"))
            {
                dirLight.direction = glm::vec3(dir[0], dir[1], dir[2]);
            }

            // Directional Light Color Controls
            float ambient[3] = { dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z };
            if (ImGui::ColorEdit3("ambient", ambient))
            {
                dirLight.ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
            }

            float diffuse[3] = { dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z };
            if (ImGui::ColorEdit3("diffuse", diffuse))
            {
                dirLight.diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
            }

            float specular[3] = { dirLight.specular.x, dirLight.specular.y, dirLight.specular.z };
            if (ImGui::ColorEdit3("specular", specular))
            {
                dirLight.specular = glm::vec3(specular[0], specular[1], specular[2]);
            }

            ImGui::Separator();

            // Simple Point Light Position Control
            ImGui::Text("Point Light Position");
            glm::vec3 pointPos = scene.getLights().getPointLightPosition();
            float pos[3] = { pointPos.x, pointPos.y, pointPos.z };
            if (ImGui::DragFloat3("position", pos, 0.1f, -10.0f, 10.0f, "%.2f"))
            {
                scene.getLights().setPointLightPosition(glm::vec3(pos[0], pos[1], pos[2]));
            }

            ImGui::Separator();

        }
    }

    // ------------------------------------------------------------------
    // camera info
    void EditorPanel::drawCameraInfo(ui::Scene& scene)
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
    void EditorPanel::drawPerformanceInfo(ui::Scene& scene)
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