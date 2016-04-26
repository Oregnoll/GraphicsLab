#include "RenderProject.h"
/* Draw your scene here */
void RenderProject::loopFunction(const double &deltaTime, const double &elapsedTime)
{
    /// Draw scene ///
    
    bRenderer().getModelRenderer()->drawQueue(/*GL_LINES*/);
    bRenderer().getModelRenderer()->clearQueue();
    
    //// Camera Movement ////
    updateCamera("camera", deltaTime);
    
    /// Update render queue ///
    updateRenderQueue("camera", deltaTime);
    
    // Quit renderer when escape is pressed
    if (bRenderer().getInput()->getKeyState(bRenderer::KEY_ESCAPE) == bRenderer::INPUT_PRESS)
        bRenderer().terminateRenderer();
}



/* Update render queue */
void RenderProject::updateRenderQueue(const std::string &camera, const double &deltaTime)
{
    /*** solar system ***/
    
    // TODO: implement solar system here
    
    vmml::Matrix4f modelMatrix = vmml::create_scaling(vmml::Vector3f(0.6f));
    vmml::Matrix4f viewMatrix = bRenderer().getObjects()->getCamera("camera")->getViewMatrix();
    
    ShaderPtr shader = bRenderer().getObjects()->getShader("guy");
    
    if (shader.get())
    {
        shader->setUniform("ProjectionMatrix", vmml::Matrix4f::IDENTITY);
        shader->setUniform("ViewMatrix", viewMatrix);
        shader->setUniform("ModelMatrix", modelMatrix);
        
        vmml::Matrix3f normalMatrix;
        vmml::compute_inverse(vmml::transpose(vmml::Matrix3f(modelMatrix)), normalMatrix);
        shader->setUniform("NormalMatrix", normalMatrix);
        
        vmml::Vector4f eyePos = vmml::Vector4f(0.0f, 0.0f, 10.0f, 1.0f);
        shader->setUniform("EyePos", eyePos);
        
        shader->setUniform("LightPos", vmml::Vector4f(0.f, 1.f, .5f, 1.f));
        shader->setUniform("Ia", vmml::Vector3f(1.f));
        shader->setUniform("Id", vmml::Vector3f(1.f));
        shader->setUniform("Is", vmml::Vector3f(1.f));
    }
    else
    {
        bRenderer::log("No shader available.");
    }
    
    //shader->setUniform("NormalMatrix", vmml::Matrix3f(modelMatrix));
    //bRenderer().getModelRenderer()->drawModel("guy", "camera", modelMatrix, std::vector<std::string>({ }));
    
    
    
    
    //Draw Text
    ModelPtr text = bRenderer().getObjects()->getTextSprite("text");
    
    bRenderer().getModelRenderer()->drawText("text", "camera", modelMatrix, std::vector<std::string>({ }));
    
    
}

/* Camera movement */
void RenderProject::updateCamera(const std::string &camera, const double &deltaTime)
{
    //// Adjust aspect ratio ////
    bRenderer().getObjects()->getCamera(camera)->setAspectRatio(bRenderer().getView()->getAspectRatio());
}