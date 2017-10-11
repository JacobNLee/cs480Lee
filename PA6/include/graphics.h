#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "mycamera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, string shaders[], std::string texture);
    void Update(unsigned int dt);
    void Render();

    Object* getCube();

    
  private:
    std::string ErrorString(GLenum error);

    MyCamera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_modelMatrix2;

    GLuint aTexture;

    Object *m_cube;
    
    

    
};

#endif /* GRAPHICS_H */
