#include "Renderer.h"

#include "core/Camera.h"
#include "light/Lights.h"
#include "scene/Model.h"
#include "scene/Shader.h"


void render::Renderer::render(scene::Scene& scene)
{
    Model* model = scene.getModel();
    if (!model) return;

    // get references for rendering
    Lights& lights = scene.getLights();
    Camera* camera = scene.getCamera();
    Transform& transform = scene.getModelTransform();

    // render the scene
    renderModel(*model, transform, lights, *camera);
    lights.renderLightGizmo(camera);
}

void render::Renderer::renderModel(Model& model, Transform& transform, Lights& lights, Camera& camera)
{
    auto& meshes = model.getMeshes();
    if (meshes.empty()) return;

    // set transform for all meshes
    for (auto& mesh : meshes)
    {
        mesh->setTransform(transform);
    }

	// Get the shader for lights
    Shader* shader = lights.getLightsShader();
    setupLighting(*shader, lights, camera);

	// Set model matrix
    shader->setMat4("model", transform.to_mat4());

    // Draw the model
    model.draw(*shader);
}

void render::Renderer::setupLighting(Shader& shader, Lights& lights, Camera& camera)
{
    lights.setLightUniforms(shader, &camera);
}
