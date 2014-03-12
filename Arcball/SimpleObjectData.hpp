//
//  ObjectData.hpp
//  Arcball
//
//  Created by Saburo Okita on 12/03/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#ifndef Arcball_ObjectData_hpp
#define Arcball_ObjectData_hpp

#include <vector>
#include <glm/glm.hpp>

/**
 Just some quick and dirty vertices and normals to draw the cube and the floor,
 meant to be as simple (and probably slow) as possible
 */

static const std::vector<glm::vec3> cube_buffer_data = {
    /* Front */
    glm::vec3( -0.5f,  0.5f, 0.5f ),
    glm::vec3( -0.5f, -0.5f, 0.5f ),
    glm::vec3(  0.5f,  0.5f, 0.5f ),
    glm::vec3(  0.5f, -0.5f, 0.5f ),
    
    /* Left */
    glm::vec3( -0.5f,  0.5f, -0.5f ),
    glm::vec3( -0.5f, -0.5f, -0.5f ),
    glm::vec3( -0.5f,  0.5f,  0.5f ),
    glm::vec3( -0.5f, -0.5f,  0.5f ),
    
    /* Right */
    glm::vec3(  0.5f,  0.5f,  0.5f ),
    glm::vec3(  0.5f, -0.5f,  0.5f ),
    glm::vec3(  0.5f,  0.5f, -0.5f ),
    glm::vec3(  0.5f, -0.5f, -0.5f ),
    
    /* Back */
    glm::vec3(  0.5f,  0.5f, -0.5f ),
    glm::vec3(  0.5f, -0.5f, -0.5f ),
    glm::vec3( -0.5f,  0.5f, -0.5f ),
    glm::vec3( -0.5f, -0.5f, -0.5f ),
    
    /* Top */
    glm::vec3( -0.5f,  0.5f, -0.5f ),
    glm::vec3( -0.5f,  0.5f,  0.5f ),
    glm::vec3(  0.5f,  0.5f, -0.5f ),
    glm::vec3(  0.5f,  0.5f,  0.5f ),
    
    /* Bottom */
    glm::vec3( -0.5f, -0.5f,  0.5f ),
    glm::vec3( -0.5f, -0.5f, -0.5f ),
    glm::vec3(  0.5f, -0.5f,  0.5f ),
    glm::vec3(  0.5f, -0.5f, -0.5f ),
};


static const std::vector<glm::vec3> cube_normals_data = {
    glm::vec3( 0.0f,  0.0f,  1.0f ),
    glm::vec3( 0.0f,  0.0f,  1.0f ),
    glm::vec3( 0.0f,  0.0f,  1.0f ),
    glm::vec3( 0.0f,  0.0f,  1.0f ),
    
    glm::vec3( -1.0f,  0.0f,  0.0f ),
    glm::vec3( -1.0f,  0.0f,  0.0f ),
    glm::vec3( -1.0f,  0.0f,  0.0f ),
    glm::vec3( -1.0f,  0.0f,  0.0f ),
    
    glm::vec3(  1.0f,  0.0f,  0.0f ),
    glm::vec3(  1.0f,  0.0f,  0.0f ),
    glm::vec3(  1.0f,  0.0f,  0.0f ),
    glm::vec3(  1.0f,  0.0f,  0.0f ),
    
    glm::vec3( 0.0f,  0.0f, -1.0f ),
    glm::vec3( 0.0f,  0.0f, -1.0f ),
    glm::vec3( 0.0f,  0.0f, -1.0f ),
    glm::vec3( 0.0f,  0.0f, -1.0f ),
    
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    
    glm::vec3( 0.0f, -1.0f,  0.0f ),
    glm::vec3( 0.0f, -1.0f,  0.0f ),
    glm::vec3( 0.0f, -1.0f,  0.0f ),
    glm::vec3( 0.0f, -1.0f,  0.0f ),
};

static const std::vector<glm::vec3> floor_buffer_data = {
    /* Top */
    glm::vec3( -10.0f,  -0.9f, -10.0f ),
    glm::vec3( -10.0f,  -0.9f,  10.0f ),
    glm::vec3(  10.0f,  -0.9f, -10.0f ),
    glm::vec3(  10.0f,  -0.9f,  10.0f ),
};


static const std::vector<glm::vec3> floor_normals_data = {
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
    glm::vec3( 0.0f,  1.0f,  0.0f ),
};


#endif
