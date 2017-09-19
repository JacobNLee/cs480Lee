#ifndef MOON_H
#define MOON_H

#include <vector>
#include "graphics_headers.h"

class Moon
{
  public:
    Moon();
    ~Moon();
    void Update(unsigned int dt);
    void Render();

    void invertOrbitRev();
    void invertOrbitStop();
    void invertRotRev();
    void invertRotStop();
    
    

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle_orbit;
    float angle_rot; 

    bool orbit_rev;
    bool rot_rev;
    bool orbit_stop;
    bool rot_stop;   
};

#endif /* MOON_H */
