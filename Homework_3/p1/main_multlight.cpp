//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "GLAppearance.h"




using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);

    
    // create an apperance object.
	GLAppearance* appearances[4];

	for (int i = 0; i < 4; ++i)
	{
		appearances[i] = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	}

	float pos[12] = { -37.5, 0.0, 0.0,
						-12.5, 0.0, 0.0,
						12.5, 0.0, 0.0,
						37.5, 0.0, 0.0 };

	GLSpotLightSource redSpotLightSource;
	redSpotLightSource._lightPos = glm::vec4(pos[0] + 15.0, pos[1] + 0.0, pos[2] + 20.0, 1.0);
	redSpotLightSource._ambient_intensity = 0.01;
	redSpotLightSource._specular_intensity = 3.0;
	redSpotLightSource._diffuse_intensity = 12.0;
	redSpotLightSource._attenuation_coeff = 0.02;
	redSpotLightSource._cone_angle = 90.0;
	redSpotLightSource._cone_direction = glm::vec3(-1.0, -1.0, 0.0);

	appearances[0]->addLightSource(redSpotLightSource);

	GLSpotLightSource blueSpotLightSource;
	blueSpotLightSource._lightPos = glm::vec4(pos[3] + 13.0, pos[4] + 0.0, pos[5] + 20.0, 1.0);
	blueSpotLightSource._ambient_intensity = 0.1;
	blueSpotLightSource._specular_intensity = 0.0;
	blueSpotLightSource._diffuse_intensity = 15.0;
	blueSpotLightSource._attenuation_coeff = 0.02;
	blueSpotLightSource._cone_angle = 90.0;
	blueSpotLightSource._cone_direction = glm::vec3(-1.0, -1.0, 0.0);

	appearances[1]->addLightSource(blueSpotLightSource);

	GLSpotLightSource greenSpotLightSource1;
	greenSpotLightSource1._lightPos = glm::vec4(pos[6] - 0.0, pos[7] + 20.0, pos[8] + 20.0, 1.0);
	greenSpotLightSource1._ambient_intensity = 0.0;
	greenSpotLightSource1._specular_intensity = 0.0;
	greenSpotLightSource1._diffuse_intensity = 1000.0;
	greenSpotLightSource1._attenuation_coeff = 0.02;
	greenSpotLightSource1._cone_angle = 90.0;
	greenSpotLightSource1._cone_direction = glm::vec3(0.0, -0.7, 0.0);

	GLSpotLightSource greenSpotLightSource2;
	greenSpotLightSource2._lightPos = glm::vec4(pos[6] + 4.0, pos[7] + 0.0, pos[8] + 20.0, 1.0);
	greenSpotLightSource2._ambient_intensity = 0.0;
	greenSpotLightSource2._specular_intensity = 4.0;
	greenSpotLightSource2._diffuse_intensity = 0.0;
	greenSpotLightSource2._attenuation_coeff = 0.02;
	greenSpotLightSource2._cone_angle = 90.0;
	greenSpotLightSource2._cone_direction = glm::vec3(-1.0, -1.0, 0.0);

	appearances[2]->addLightSource(greenSpotLightSource1);
	appearances[2]->addLightSource(greenSpotLightSource2);

	GLSpotLightSource yellowSpotLightSource1;
	yellowSpotLightSource1._lightPos = glm::vec4(pos[9] - 15.0, pos[10] - 5.0, pos[11] + 20.0, 1.0);
	yellowSpotLightSource1._ambient_intensity = 0.05;
	yellowSpotLightSource1._specular_intensity = 1.0;
	yellowSpotLightSource1._diffuse_intensity = 5.0;
	yellowSpotLightSource1._attenuation_coeff = 0.02;
	yellowSpotLightSource1._cone_angle = 90.0;
	yellowSpotLightSource1._cone_direction = glm::vec3(1.0, 1.0, 0.0);

	GLSpotLightSource yellowSpotLightSource2;
	yellowSpotLightSource2._lightPos = glm::vec4(pos[9] - 5.0, pos[10] + 15.0, pos[11] + 20.0, 1.0);
	yellowSpotLightSource2._ambient_intensity = 0.02;
	yellowSpotLightSource2._specular_intensity = 0.5;
	yellowSpotLightSource2._diffuse_intensity = 5.0;
	yellowSpotLightSource2._attenuation_coeff = 0.02;
	yellowSpotLightSource2._cone_angle = 90.0;
	yellowSpotLightSource2._cone_direction = glm::vec3(-1.0, -1.0, 0.0);

	appearances[3]->addLightSource(yellowSpotLightSource1);
	appearances[3]->addLightSource(yellowSpotLightSource2);
    
    // Create a material object
    GLMaterial material[4];
    material[0]._diffuse_material = glm::vec3(0.45, 0.0, 0.0);
    material[0]._ambient_material = glm::vec3(0.45, 0.0, 0.0);
    material[0]._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material[0]._shininess = 50.0;

	material[1]._diffuse_material = glm::vec3(0.0, 0.0, 0.6);
	material[1]._ambient_material = glm::vec3(0.0, 0.0, 0.6);
	material[1]._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material[1]._shininess = 100.0;
    
	material[2]._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
	material[2]._ambient_material = glm::vec3(0.0, 1.0, 0.0);
	material[2]._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material[2]._shininess = 20.0;
    
	material[3]._diffuse_material = glm::vec3(232 / 256.0, 221 / 256.0, 102 / 256.0);
	material[3]._ambient_material = glm::vec3(232 / 256.0, 221 / 256.0, 102 / 256.0);
	material[3]._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material[3]._shininess = 50.0;

    // Add the material to the apperance object
	for (int i = 0; i < 4; ++i)
	{
		appearances[i]->setMaterial(material[i]);
		appearances[i]->finalize();
	}

	GLSphere3D* spheres[4];

	for (int i = 0; i < 4; ++i)
	{
		spheres[i] = new GLSphere3D(pos[3 * i + 0], pos[3 * i + 1], pos[3 * i + 2], 10.0, 90.0, 50.0);
		spheres[i]->setApperance(*appearances[i]);
		spheres[i]->init();
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(0.0, 0.0, 100.0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
   // sphere->enableNormalVectorRenderer();

    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
    
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
        
        // draw the objects
		cs->draw();

		for(int i = 0; i < 4; ++i)
		{
			spheres[i]->draw();
		}
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

