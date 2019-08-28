//
//  main.cpp
//  CraftyEngineiers
//
//  Created by Samuel Hulme on 25/08/2019.
//  Copyright © 2019 SJH. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

//GLUT
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//GLFW
#include <GLFW/glfw3.h>

//Camera
#include "Camera.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera  camera(glm::vec3( 0.0f, 0.0f, 3.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

typedef enum
{
    GrassBlock = 0, DirtBlock
}BlockType;

void placeBlock(float x, float y, float z, BlockType type){
    BlockType myType;
    switch(type){
        case BlockType::GrassBlock: myType = type; break;
        case BlockType::DirtBlock: myType = type; break;
    }
    const float sizex = 0.5f;
    const float sizey = 0.5f;
    const float sizez = 0.5f;
    glTranslatef(-x, -y, -z);
    glBegin(GL_QUADS);
    if (myType == BlockType::GrassBlock) {
        glColor3f(.56, .56, .2);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // FRONT
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(sizex, -sizey, sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(-sizex, sizey, sizez);
    if (myType == BlockType::GrassBlock) {
        glColor3f(.56, .56, .2);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // BACK
    glVertex3f(-sizex, -sizey, -sizez);
    glVertex3f(-sizex, sizey, -sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(sizex, -sizey, -sizez);
    if (myType == BlockType::GrassBlock) {
        glColor3f(.56, .56, .2);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // LEFT
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(-sizex, sizey, sizez);
    glVertex3f(-sizex, sizey, -sizez);
    glVertex3f(-sizex, -sizey, -sizez);
    if (myType == BlockType::GrassBlock) {
        glColor3f(.56, .56, .2);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // RIGHT
    glVertex3f(sizex, -sizey, -sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(sizex, -sizey, sizez);
    if (myType == BlockType::GrassBlock) {
        glColor3f(0.0, 1.0, 0.0);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // TOP
    glVertex3f(-sizex, sizey, sizez);
    glVertex3f(sizex, sizey, sizez);
    glVertex3f(sizex, sizey, -sizez);
    glVertex3f(-sizex, sizey, -sizez);
    if (myType == BlockType::GrassBlock) {
        glColor3f(.56, .56, .2);
    }else if (myType == BlockType::DirtBlock) {
        glColor3f(.56, .56, .2);
    }
    // BOTTOM
    glVertex3f(-sizex, -sizey, sizez);
    glVertex3f(-sizex, -sizey, -sizez);
    glVertex3f(sizex, -sizey, -sizez);
    glVertex3f(sizex, -sizey, sizez);
    glEnd();
    glTranslatef(x, y, z);
}

// Clears the window and draws the tetrahedron.  The tetrahedron is  easily
// specified with a triangle strip, though the specification really isn't very
// easy to read.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw a white grid "floor" for the tetrahedron to sit on.
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
        glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
        glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
    }
    glEnd();
    
    placeBlock(.0f, .0f, 1.0f, BlockType::DirtBlock);
    placeBlock(.0f, .0f, .0f, BlockType::GrassBlock);
    
    glFlush();
}

// Sets up global attributes like clear color and drawing color, enables and
// initializes any needed modes (in this case we want backfaces culled), and
// sets up the desired projection and modelview matrices. It is cleaner to
// define these operations in a function separate from main().
void init() {

    // Set the current clear color to sky blue and the current drawing color to
    // white.
    glClearColor(0.1, 0.39, 0.88, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    
    // Tell the rendering engine not to draw backfaces.  Without this code,
    // all four faces of the tetrahedron would be drawn and it is possible
    // that faces farther away could be drawn after nearer to the viewer.
    // Since there is only one closed polyhedron in the whole scene,
    // eliminating the drawing of backfaces gives us the realism we need.
    // THIS DOES NOT WORK IN GENERAL.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(-90, 0, 0, 0);
}

int main(int argc, char** argv)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, "CraftyEngineiers", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }
    //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));
    

    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    /* Loop until the user closes the window */
    init();
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        /* Poll for and process events */
        glfwPollEvents();
        DoMovement( );
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        display();
    }
    
    glfwTerminate();
    return 0;
}

void DoMovement( )
{
    // Camera controls
    if( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}
