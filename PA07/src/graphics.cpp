#include "graphics.h"


void normVect( std::vector<float> &in);

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  timescale = 2500;

  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new MyCamera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  readConfig();

  //get textures right
  for (int i = 0; i < numbObjects; i++)
  {
	  std::string modelPath = "../planets/";
	  std::string texturePath = "../planets/";

    if (objectVector[i].moonOf == -1)
    {
	     modelPath.append(objectVector[i].objectName);
	     texturePath.append(objectVector[i].objectName);
    }
    else 
    {
       modelPath.append("Moon");
       texturePath.append("Moon");
    }

	  modelPath.append("/");
	  texturePath.append("/");

	  modelPath.append(objectVector[i].objectModel);
	  texturePath.append(objectVector[i].objectTexture);

	  objectVector[i].objectModel = modelPath;
	  objectVector[i].objectTexture = texturePath;
  }

  // Create the objects
  for( index = 0; index < numbObjects; ++index )
  {   
    objects.push_back( new Object( objectVector[ index ] ));
  }

  // Set up planet data
  std::vector<float> fromSun;
  std::vector<float> diameter;
  std::vector<float> rotation;
  std::vector<float> orbit;

  for( index = 0; index < numbObjects; ++index )
  {
    fromSun.push_back( objectVector[index].distanceFromSun * 1000000.);
    diameter.push_back( objectVector[index].diameter );
    rotation.push_back( objectVector[index].rotationPeriodHours );
    orbit.push_back( objectVector[index].orbitPeriodDays );
  }

  normVect( fromSun );
  normVect( diameter );
  normVect(  rotation );
  normVect( orbit );

  for( index = 0; index < numbObjects; ++index )
  {
    objects[ index ]->setPlanetVals( fromSun[ index ], diameter[ index ], rotation[ index ], orbit[ index ] );
  }
  

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader( vShader, GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader( fShader, GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_modelMatrix2 = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix2 == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt, int objSelector, int viewingMode)
{
  // Update the object

  for( index = 0; index < numbObjects; ++index )
  {

    if (objectVector[ index ].moonOf == -1)
    {
      objects[ index ]->Update(dt, objectVector[ index ], objects[ 0 ]->getOrigin(), timescale );
    }
    else 
    {
      objects[ index ]->Update(dt, objectVector[ index ], objects[ objectVector[ index ].moonOf ]->getOrigin(), timescale);
    }


  }

  if( viewingMode == 0 )
  {
    m_camera->updateCameraPosition(objectVector[objSelector], objects[objSelector]->getOrigin());    
  }

  if( viewingMode == 1 )
  {
    m_camera->updateCameraPosition( {0,850, 0});
  }

  if( viewingMode == 2)
  {
    m_camera->updateCameraPosition( {0,200, 0});
  }
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the object
  for( index = 0; index < numbObjects; ++index )
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(objects[ index ]->GetModel()));
    objects[ index ]->Render(objectVector[ index ].objectTexture); 
  }

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}


Object* Graphics::getCube()
{
  return objects[ 0 ];
}

void Graphics::readConfig()
{
  std::string tempString;
  vShader = "../shaders/";
  fShader = "../shaders/";

  objectStruct tempStruct;

  ifstream fin;
  fin.open("../config/configFile");

  if (fin.is_open())
  {
    while (fin >> tempString)
    {
      if (tempString.find("vertexShader:") != std::string::npos)
      {
        fin >> tempString;
        vShader.append(tempString);
      }
      else if (tempString.find("fragmentShader:") != std::string::npos)
      {
        fin >> tempString;
        fShader.append(tempString);
      }
      else if (tempString.find("numbObjects:") != std::string::npos)
      {
        fin >> numbObjects;
        break;
      }
    }

    for (int index = 0; index < numbObjects; index++)
    {
      while (fin >> tempString)
      {
        if (tempString.find("objectName") != std::string::npos)
        {
          fin >> tempStruct.objectName;
          std::cout << tempStruct.objectName << std::endl;
        }
        else if (tempString.find("objectModel") != std::string::npos)
        {
          fin >> tempStruct.objectModel;
        }
        else if (tempString.find("objectTexture") != std::string::npos)
        {
          fin >> tempStruct.objectTexture;
        }
        else if (tempString.find("distanceFromSun") != std::string::npos)
        {
          fin >> tempStruct.distanceFromSun;
        }
        else if (tempString.find("diameter") != std::string::npos)
        {
          fin >> tempStruct.diameter;
        }
        else if (tempString.find("rotationPeriodHours") != std::string::npos)
        {
          fin >> tempStruct.rotationPeriodHours;
        }
        else if (tempString.find("orbitPeriodDays") != std::string::npos)
        {
          fin >> tempStruct.orbitPeriodDays;
        }
        else if (tempString.find("moonOf") != std::string::npos)
        {
          //last thing to be read
          fin >> tempStruct.moonOf;
          break;
        }
        else
        {
          std::cerr << "Error config file invalid format with: " << tempString << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      objectVector.push_back(tempStruct);
    }
  }
  else
  {
    std::cerr << "Error loading config file, make sure there is one to load" << std::endl;
    exit(EXIT_FAILURE);
  }

  fin.close();
}

void normVect( std::vector<float> &in)
{
  int minIndex = 0;
  int index;

  float min;

  for( index = 1; index < in.size(); ++index )
  {
    if( in[ minIndex ] > in[ index ] && in[ index ] != 0.0 && in[ index ] != 0 )
    {
      minIndex = index;
    }

    if( in[ minIndex ] == 0.0 )
    {
      minIndex++;
    }
  }

  min = in[ minIndex ];

  for( index = 0; index < in.size(); ++index )
  {
    cout << in[ index ] << ' ';
    in[ index ] = in[ index ] / min;
    cout << in[ index ] << endl;
  }
  cout << endl;
}

void Graphics::incTime()
{
  timescale += 50;
}
void Graphics::decTime()
{
  if( timescale == 50 )
  {

  }
  else
  {
    timescale -= 50;
  }
}