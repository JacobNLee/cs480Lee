#include <iostream>
#include <fstream>

#include "engine.h"
#include <string.h>


string file2string( string in );



int main(int argc, char **argv)
{
  int index;


  string shaders[ 2 ];
  string model;
  
  for( index = 1; index < argc; index += 2 )
  {
      if( !strcmp( argv[ index ], "--v") || !strcmp( argv[ index ], "--V"))
      { 

        shaders[ 0 ] = argv[ index + 1 ];

        shaders[ 0 ] = file2string( shaders[ 0 ] );

      }
      else if( !strcmp( argv[ index ], "--f") || !strcmp( argv[ index ], "--F"))
      {

        shaders[ 1 ] = argv[ index + 1 ];

        shaders[ 1 ] = file2string( shaders[ 1 ] );

      }
      else if( !strcmp( argv[ index ], "--help") || !strcmp( argv[ index ], "--Help") || !strcmp( argv[ index ], "--HELP") || !strcmp( argv[ index ], "--?"))
      {

        std::cout << "Two sharder files are requied to run this program." << std::endl <<
        "There needs to be a vertex shader and a fragment shader and a .obj file" << std::endl << std::endl <<
        "Below is the format of how each shader file should look." << std::endl <<"They can be in any order" << std::endl <<  std::endl <<
        "--v <vetex shader file name >" << std::endl <<"--f <fragment shader file name >" << endl << "--m <.obj file name>" << endl;
        return 0;
      }
      else if( !strcmp( argv[ index ], "--m") || !strcmp( argv[ index ], "--M"))
      { 

        model = argv[ index + 1 ];
        

      }
      else
      {
        std::cout << "Unrecognized Command Line Option \n try --Help" << std::endl;

        return 1;
      }

  }


  if( shaders[ 0 ] == "" || shaders[ 1 ] == "")
  {
    std::cout << "Error loading shaders, Ending the program" << std::endl;
    return 1;
  }

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);

  

  if(!engine->Initialize( shaders ))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  
  engine->loadModel( model );
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}


string file2string( string in )
{
  fstream fin;
  string out;
  fin.open( in );
  char c;

  while( fin.good() )
  { 
    fin.get( c );
    out.push_back( c );
  }
  
  return out;
}