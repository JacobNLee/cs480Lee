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
    
    std::vector<Vertex> Vertices;
    
    std::vector<unsigned int> Indices;
    std::vector<unsigned int> UVs;
    std::vector<unsigned int> Normals;

    GLuint VB;
    GLuint IB;


    float angle_orbit;
    float angle_rot; 

    bool orbit_rev;
    bool rot_rev;
    bool orbit_stop;
    bool rot_stop;

    glm::vec2 origin;

    int getNumberOfSlashes( std::string inString );
    int getNumber( std::string &inString );
};

#endif /* OBJECT_H */
