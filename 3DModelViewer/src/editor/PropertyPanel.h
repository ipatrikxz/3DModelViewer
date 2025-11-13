#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <memory>

#include "imgui.h"
#include <imfilebrowser.h>

namespace scene { class Scene; }

namespace editor
{

	class PropertyPanel
	{

	public:
		PropertyPanel()
		{
			currentModelFile = "< ... >";

			modelFileDialog.SetTitle("File import dialog window");
			modelFileDialog.SetTypeFilters({ ".obj", ".fbx" });
			modelFileDialog.SetDirectory("res/models/");

			currentTextureFile = "< ... >";
			textureFileDialog.SetTitle("Texture import dialog window");
			textureFileDialog.SetTypeFilters({ ".png", ".jpg", ".jpeg" });
			textureFileDialog.SetDirectory("res/textures/");

			shaderColor = glm::vec3(1, 1, 1);
		}

		void render(scene::Scene& scene);

	private:

		void drawMeshControls(scene::Scene& scene);
		void drawLightControls(scene::Scene& scene);
		void drawCameraInfo(scene::Scene& scene);
		void drawPerformanceInfo(scene::Scene& scene);

		// imgui file browser dialogs
		ImGui::FileBrowser modelFileDialog;
		ImGui::FileBrowser textureFileDialog;

		std::string currentModelFile;
		std::string currentTextureFile;

		glm::vec3 shaderColor;

	};
}