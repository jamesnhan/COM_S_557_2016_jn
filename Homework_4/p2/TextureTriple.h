//
//  Texture.hpp
//  HCI557_Simple_Texture
//
//  Created by Rafael Radkowski on 10/10/15.
//
//
#pragma once

// stl include
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// locals
#include "Texture.h"
#include "GLAppearanceBase.h"



using namespace std;


/*!
 This texture class adds two textures to a glsl shader program.
 It is part of the appearance object and need to be used with a shader program that supports textures.
 */
class GLTripleTexture : public GLTextureBase
{
private:
    // Allow the class GLApperance access to protected variables.
    friend class GLAppearance;
    
    
    // These are the variable names which are used in our glsl shader programs.
    // Make sure that you use the correct names in your programs.
#ifdef WIN32
    static string      _glsl_names[];
#else
    const string      _glsl_names[4] = { "tex1", "tex2", "tex3", "texture_blend"};
#endif
    
    
    
public:
    GLTripleTexture();
    ~GLTripleTexture();
    
    /*!
     Load two bitmap images as textures from files.
     @param path_and_file_texture_1 - path and file of the first image.
     @param path_and_file_texture_1 - path and file of the second image.
     @return int - the texture id when the texture was sucessfully loaded.
     */
    int loadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2, string path_and_file_texture_3);
    
    /*!
     This sets the texture blend model
     @param mode - the values 0,1, or 2
     @return true, when a new mode was set, false when current and new mode are equal
     */
    bool setTextureBlendMode(int mode);
    
    
    
protected:
    
    /*!
     Adds the variables of this object to the shader program
     */
    virtual bool addVariablesToProgram(GLuint program, int variable_index);
    
    
    /*!
     The function indicates that the variables of this object require an update
     */
    virtual bool dirty(GLuint program);
    
    
    
private:
    
    // The texture for this program.
    GLuint      _texture_1;
    GLuint      _texture_2;
    GLuint      _texture_3;
    
    // The blending mode for this texture
    int         _texture_blend_mode;
    
    // location of the texture in the glsl program
    int         _textureIdx1;
    int         _textureIdx2;
    int         _textureIdx3;
    int         _textureBlendModelIdx;
    
    

};
