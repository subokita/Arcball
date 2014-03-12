//
//  main.cpp
//  Arcball
//
//  Created by Saburo Okita on 11/03/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include <iostream>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>

#include "Shader.h"
#include "Arcball.h"
#include "SimpleObjectData.hpp"

using namespace std;

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 450

/* Arcball instance, sadly we put it here, so that it can be referenced in the callbacks */
static Arcball arcball( WINDOW_WIDTH, WINDOW_HEIGHT, 1.5f, true, true );


void errorCallback( int error, const char * desc );
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mod);
void frameBufferSizeCallback( GLFWwindow *window, int width, int height );
void scrollCallback( GLFWwindow *window, double x, double y );
void mouseButtonCallback( GLFWwindow * window, int button, int action, int mods );
void cursorCallback( GLFWwindow *window, double x, double y );

int main(int argc, const char * argv[]) {
    if( !glfwInit() ) {
        cerr << "Unable to initialize glfw" << endl;
        return false;
    }
    
    /* Tell GLFW to use OpenGL 4.1 */
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    
    GLFWwindow * window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Arcball", NULL, NULL );
    if ( !window ) {
        cerr << "Unable to create glfw window" << endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent( window );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );
    
    cout << "OpenGL Ver: " << glGetString( GL_VERSION ) << endl;
    
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    
    /* Set the callback functions */
    glfwSetErrorCallback( errorCallback );
    glfwSetScrollCallback( window, scrollCallback );
    glfwSetKeyCallback( window, keyCallback );
    glfwSetFramebufferSizeCallback( window, frameBufferSizeCallback );
    glfwSetCursorPosCallback( window, cursorCallback );
    glfwSetMouseButtonCallback( window, mouseButtonCallback );
    
    GLuint vertex_array_id;
    glGenVertexArrays( 1, &vertex_array_id );
    glBindVertexArray( vertex_array_id );
    
    Shader shader( "simpleLighting.vsh", "simpleLighting.fsh" );
    GLuint cube_buffers[2];
    glGenBuffers( 2, cube_buffers );
    glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * cube_buffer_data.size(), &cube_buffer_data[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * cube_normals_data.size(), &cube_normals_data[0], GL_STATIC_DRAW );

    GLuint floor_buffers[2];
    glGenBuffers( 2, floor_buffers );
    glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * floor_buffer_data.size(), &floor_buffer_data[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * floor_normals_data.size(), &floor_normals_data[0], GL_STATIC_DRAW );

    glm::mat4 model      = glm::mat4(1.0);
    glm::mat4 view       = glm::lookAt( glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0., 0., 0.), glm::vec3(0., 1., 0.) );
    glm::mat4 projection = glm::perspective(70.0f, 4.0f/3.0f, 0.1f, 100.0f );
    
    glm::vec3 light_position = glm::vec3( 4, 4, 4 );
    
    shader.bind();
    shader.setUniform( "light_position_w", light_position );
    
    while( !glfwWindowShouldClose( window )){
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        { /* Draw on 1st viewport, show rotation of the camera */
            glViewport( 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT );
            
            glm::mat4 rotated_view = view * arcball.createViewRotationMatrix();
            glm::mat4 mvp = projection * rotated_view * model;
            
            shader.setUniform( "light_color", glm::vec3(1.0, 1.0, 0.0) );
            shader.setUniform( "v", rotated_view );
            shader.setUniform( "m", model );
            shader.setUniform( "mvp", mvp );
            
            /* Draw cube */
            glEnableVertexAttribArray( 0 );
            glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[0] );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnableVertexAttribArray( 1 );
            glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[1] );
            glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnable( GL_CULL_FACE );
            glDrawArrays( GL_TRIANGLE_STRIP, 0, static_cast<int>(cube_buffer_data.size()) );
            
            
            /* Draw the floor, with different color */
            shader.setUniform( "light_color", glm::vec3(0.0, 1.0, 1.0) );
            glEnableVertexAttribArray( 0 );
            glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[0] );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnableVertexAttribArray( 1 );
            glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[1] );
            glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glDisable( GL_CULL_FACE );
            glDrawArrays( GL_TRIANGLE_STRIP, 0, static_cast<int>(floor_buffer_data.size()) );
        }
        
        { /* Draw on 2nd viewport, show rotation of the model */
            glViewport( WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT );
            
            glm::mat4 rotated_model = model * arcball.createModelRotationMatrix( view );
            glm::mat4 mvp = projection * view * rotated_model;
            
            shader.setUniform( "light_color", glm::vec3(1.0, 1.0, 0.0) );
            shader.setUniform( "v", view );
            shader.setUniform( "m", rotated_model );
            shader.setUniform( "mvp", mvp );
            
            /* Draw cube */
            glEnableVertexAttribArray( 0 );
            glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[0] );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnableVertexAttribArray( 1 );
            glBindBuffer( GL_ARRAY_BUFFER, cube_buffers[1] );
            glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnable( GL_CULL_FACE );
            glDrawArrays( GL_TRIANGLE_STRIP, 0, static_cast<int>(cube_buffer_data.size()) );
            
            /* Draw the floor, with different color */
            shader.setUniform( "light_color", glm::vec3(0.0, 1.0, 1.0) );
            glEnableVertexAttribArray( 0 );
            glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[0] );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glEnableVertexAttribArray( 1 );
            glBindBuffer( GL_ARRAY_BUFFER, floor_buffers[1] );
            glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );
            
            glDisable( GL_CULL_FACE );
            glDrawArrays( GL_TRIANGLE_STRIP, 0, static_cast<int>(floor_buffer_data.size()) );
        }
        
        
        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    
    shader.unbind();
    
    glDeleteBuffers( 2, cube_buffers );
    glDeleteBuffers( 2, floor_buffers );
    glDeleteVertexArrays( 1, &vertex_array_id );
    
    return 0;
}



void errorCallback( int error, const char * desc ) {
    fputs( desc, stderr );
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mod) {
    if( action == GLFW_PRESS ) {
        switch ( key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose( window, GL_TRUE );
                return;
            default:
                break;
        }
    }
}

void frameBufferSizeCallback( GLFWwindow *window, int width, int height ) {
    glViewport( 0, 0, width, height );
}

void scrollCallback( GLFWwindow *window, double x, double y ) {
}

void mouseButtonCallback( GLFWwindow * window, int button, int action, int mods ){
    /* Pass the arguments to our arcball object */
    arcball.mouseButtonCallback( window, button, action, mods );
}

void cursorCallback( GLFWwindow *window, double x, double y ) {
    /* Pass the arguments to our arcball object */
    arcball.cursorCallback( window, x, y );
}
