#pragma once

#include "Util.h"
#include <memory>

class Shader;
class Camera;

class Lights {

public:
    Lights();
    ~Lights();

    DirLight& getDirectionalLight() { return dirLight; }
    const DirLight& getDirectionalLight() const { return dirLight; }
    float getPointLightConstant() const { return pointLightConstant; }
    float getPointLightLinear() const { return pointLightLinear; }
    float getPointLightQuadratic() const { return pointLightQuadratic; }
    const glm::vec3& getPointLightPosition() const { return pointLightPosition; }
    const glm::vec3& getPointLightAmbient() const { return pointLightAmbient; }
    const glm::vec3& getPointLightDiffuse() const { return pointLightDiffuse; }
    const glm::vec3& getPointLightSpecular() const { return pointLightSpecular; }
    
    void setDirectionalLight(const DirLight& light);
    void setPointLightPosition(const glm::vec3& position);
    void setPointLightAmbient(const glm::vec3& ambient) { pointLightAmbient = ambient; }
    void setPointLightDiffuse(const glm::vec3& diffuse) { pointLightDiffuse = diffuse; }
    void setPointLightSpecular(const glm::vec3& specular) { pointLightSpecular = specular; }
    void setPointLightConstant(float constant) { pointLightConstant = constant; }
    void setPointLightQuadratic(float quadratic) { pointLightQuadratic = quadratic; }
    void setPointLightLinear(float linear) { pointLightLinear = linear; }

    // Rendering
    void setupShaders();
    void setupLightGizmo();
    void renderLightGizmo(Camera* camera);
    void setLightUniforms(Shader& shader, Camera* camera);

    // Shader access
    Shader* getLightsShader() { return lightsShader.get(); }
    Shader* getGizmoShader() { return gizmoShader.get(); }

private:
    // Light properties
    DirLight dirLight;
    glm::vec3 pointLightPosition;
    glm::vec3 pointLightAmbient;
    glm::vec3 pointLightDiffuse;
    glm::vec3 pointLightSpecular;
    float pointLightConstant;
    float pointLightLinear;
    float pointLightQuadratic;

    // Shaders
    std::shared_ptr<Shader> lightsShader;
    std::shared_ptr<Shader> gizmoShader;

    // Light gizmo
    GLuint lightGizmoVAO;
    Transform lightGizmoTransform;
};
