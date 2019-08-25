//
//  Camera.h
//  CraftyEngineiers
//
//  Created by Samuel Hulme on 25/08/2019.
//  Copyright © 2019 SJH. All rights reserved.
//

#pragma once

//vector
#include <vector>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSEITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 0.1f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH): front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed()
    
};
