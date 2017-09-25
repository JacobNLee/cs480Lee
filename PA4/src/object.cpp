#include "object.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>  

#define ORBITAL_SPEED_RATIO .5
#define ORBIT_R 5

using namespace std;
Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };
  

  std::cout << Indices[0] << std::endl;
  std::cout << Vertices[0].vertex[1] << std::endl;
  */


  
  // The index works at a 0th index
  //for(unsigned int i = 0; i < Indices.size(); i++)
  {
    //Indices[i] = Indices[i] - 1;
  }
  //Indices[0] = 1;
  angle_orbit = 0.0f;
  angle_rot = 0.0f;

  orbit_rev = false;
  rot_rev = false;
  orbit_stop = false;
  rot_stop = false;

  //this->Indices.resize( 50 );
  
  /*
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
  */
}

void Object::loadModel( std::string model )
{
  std::istringstream stringStream( model );
  std::string tempLine;
  std::string tempLine2;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;


  int index;
  //std::cout << Indices[0] << std::endl << std::endl;
  //std::cin >> x;
  //test[ 0 ] = 1;
  int i;

  while(stringStream.good())
  {
    std::getline( stringStream, tempLine);
    

    if( tempLine[0] == 'v' && tempLine[1] != 'n' )
    {

    }
    else if( tempLine[0] == 'f' )
    {
      std::istringstream tempStream( tempLine );
      std::getline( tempStream, tempLine2, ' ');
      for( index = 0; index < 3; index++ )
      {
        

        std::getline( tempStream, tempLine2, '/');
        std::cout << tempLine2 << ' ';
        std::getline( tempStream, tempLine2, '/');
        if( tempLine2[0] == '\0')
        {
          Indices.push_back( 0 );
        }
        else
        {
          cout << 0 << ' ';
        }
        std::getline( tempStream, tempLine2, ' ');
        std::cout << tempLine2 << std::endl;

        
      }
       
    }
    else if( tempLine[0] == 'v')
    {

    }
  }

  //glGenBuffers(1, &VB);
  //glBindBuffer(GL_ARRAY_BUFFER, VB);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  //glGenBuffers(1, &IB);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
  test = Indices;

  Vertices.clear();
  Indices.clear();

  
}


Object::~Object()
{
  //Vertices.clear();
  //Indices.clear();
}

void Object::Update(unsigned int dt)
{
  
  if( !orbit_stop )
  {
    if( !orbit_rev )
    {
      angle_orbit += dt * M_PI/1000;
    }
    else
    {
      angle_orbit -= dt * M_PI/1000;
    }
  }

  if( !rot_stop )
  {
    if( !rot_rev )
    {
      angle_rot += dt * M_PI/1000;
    }
    else
    {
      angle_rot -= dt * M_PI/1000;
    }
  }

  origin.x = ORBIT_R * cos( angle_orbit * ORBITAL_SPEED_RATIO  );
  origin.y = ORBIT_R * sin( angle_orbit * ORBITAL_SPEED_RATIO  );
  model = glm::translate( glm::mat4(1.0f),  
                          glm::vec3(
                            origin.x,
                            0.0,
                            origin.y));
                            
  model = glm::rotate(model, (angle_rot), glm::vec3(0.0, 1.0, 0.0));
  
  
  
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{ 
  /*
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  */
}

void Object::invertOrbitRev()
{
  if( orbit_rev == 0 )
      {
        orbit_rev = 1;
      }
      else
      {
        orbit_rev = 0;
      }
}

void Object::invertOrbitStop()
{
  if( orbit_stop == 0 )
      {
        orbit_stop = 1;
      }
      else
      {
        orbit_stop = 0;
      }
}

void Object::invertRotRev()
{
  if( rot_rev == 0 )
      {
        rot_rev = 1;
      }
      else
      {
        rot_rev = 0;
      }
}

void Object::invertRotStop()
{
  if( rot_stop == 0 )
      {
        rot_stop = 1;
      }
      else
      {
        rot_stop = 0;
      }
}

glm::vec2 Object::getOrigin()
{
  return origin;
}

void Object::rotateLeft()
{
  rot_rev = false;
}

void Object::rotateRight()
{
  rot_rev = true;
}

