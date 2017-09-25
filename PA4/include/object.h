#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();

    void loadModel( std::string model );

    void invertOrbitRev();
    void invertOrbitStop();
    void invertRotRev();
    void invertRotStop();

    void rotateLeft();
    void rotateRight();

    glm::vec2 getOrigin();
    
    

    glm::mat4 GetModel();



  private:
    glm::mat4 model;
    
    GLuint VB;
    GLuint IB;

    

    std::vector<unsigned int> test;

    float angle_orbit;
    float angle_rot; 

    bool orbit_rev;
    bool rot_rev;
    bool orbit_stop;
    bool rot_stop;

    glm::vec2 origin;   
};

#endif /* OBJECT_H */
