// Controls:
// W to move forward
// S to move backward
// A to move to the left
// D to move to the right
// UP to move up
// DOWN to move down

#include <algorithm>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Exercise 3"
GLFWwindow *pWindow;

// camera mechanics
// https://learnopengl.com/Getting-Started/Camera
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = WINDOW_WIDTH / 2, lastY = WINDOW_HEIGHT / 2;
bool firstMouse = true;
float sensitivity = 0.1f;

// camera positions
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

float lastFrame = 0.0f;
float deltaTime = 0.0f;

// Each vertex uses: position (x, y, z), color (r, g, b), uv (s, t)
float circleTop[] =  {
0.000000f, 0.000000f, -0.039024f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000830f, 0.001342f, -0.073532f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f, -0.015121f, -0.005811f, -0.073532f,
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f, -0.013087f, -0.009509f, -0.073532f,
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f, -0.009509f, -0.013087f, -0.073532f,
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f, -0.004999f, -0.015385f, -0.073532f,
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f, 0.000000f, -0.016177f, -0.073532f,
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f, 0.004999f, -0.015385f, -0.073532f,
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f, 0.009509f, -0.013087f, -0.073532f,
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f, 0.013087f, -0.009509f, -0.073532f,
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f, 0.015385f, -0.004999f, -0.073532f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f, 0.016177f, 0.000000f, -0.073532f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f, 0.015385f, 0.004999f, -0.073532f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f, 0.013087f, 0.009509f, -0.073532f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f, 0.009509f, 0.013087f, -0.073532f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f, 0.004999f, 0.015385f, -0.073532f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f, 0.000000f, 0.016177f, -0.073532f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f, -0.004999f, 0.015385f, -0.073532f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f, -0.009509f, 0.013087f, -0.073532f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f, -0.013087f, 0.009509f, -0.073532f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f, -0.011341f, 0.017446f, -0.073532f,
0.487805f, 0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -0.016177f, 0.000000f, -0.073532f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f, -0.015121f, -0.005811f, -0.073532f,
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f, -0.013087f, -0.009509f, -0.073532f,
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f, -0.009509f, -0.013087f, -0.073532f,
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f, -0.004999f, -0.015385f, -0.073532f,
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f, 0.000000f, -0.016177f, -0.073532f,
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f, 0.004999f, -0.015385f, -0.073532f,
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f, 0.009509f, -0.013087f, -0.073532f,
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f, 0.013087f, -0.009509f, -0.073532f,
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f, 0.015385f, -0.004999f, -0.073532f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f, 0.016177f, 0.000000f, -0.073532f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f, 0.015385f, 0.004999f, -0.073532f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f, 0.013087f, 0.009509f, -0.073532f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f, 0.009509f, 0.013087f, -0.073532f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f, 0.004999f, 0.015385f, -0.073532f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f, 0.000000f, 0.016177f, -0.073532f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f, -0.004999f, 0.015385f, -0.073532f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f, -0.009509f, 0.013087f, -0.073532f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f, -0.013087f, 0.009509f, -0.073532f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f, -0.011341f, 0.017446f, -0.073532f,
0.487805f, 0.000000f, -0.039024f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.052350f, -0.073532f,
};

float circleBottom[] = {
0.000000f, 0.000000f, 0.039024f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, 0.000000f, -0.000830f, -0.001342f, -0.073532f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f, 0.015121f, 0.005811f, -0.073532f,
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f, 0.013087f, 0.009509f, -0.073532f,
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f, 0.009509f, 0.013087f, -0.073532f,
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f, 0.004999f, 0.015385f, -0.073532f,
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f, 0.000000f, 0.016177f, -0.073532f,
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f, -0.004999f, 0.015385f, -0.073532f,
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f, -0.009509f, 0.013087f, -0.073532f,
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f, -0.013087f, 0.009509f, -0.073532f,
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f, -0.015385f, 0.004999f, -0.073532f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f, -0.016177f, 0.000000f, -0.073532f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f, -0.015385f, -0.004999f, -0.073532f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f, -0.013087f, -0.009509f, -0.073532f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f, -0.009509f, -0.013087f, -0.073532f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f, -0.004999f, -0.015385f, -0.073532f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f, 0.000000f, -0.016177f, -0.073532f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f, 0.004999f, -0.015385f, -0.073532f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f, 0.009509f, -0.013087f, -0.073532f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f, 0.013087f, -0.009509f, -0.073532f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f, 0.011341f, -0.017446f, -0.073532f,
0.487805f, 0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f, 0.016177f, 0.000000f, -0.073532f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f, 0.015121f, 0.005811f, -0.073532f,
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f, 0.013087f, 0.009509f, -0.073532f,
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f, 0.009509f, 0.013087f, -0.073532f,
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f, 0.004999f, 0.015385f, -0.073532f,
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f, 0.000000f, 0.016177f, -0.073532f,
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f, -0.004999f, 0.015385f, -0.073532f,
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f, -0.009509f, 0.013087f, -0.073532f,
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f, -0.013087f, 0.009509f, -0.073532f,
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f, -0.015385f, 0.004999f, -0.073532f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f, -0.016177f, 0.000000f, -0.073532f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f, -0.015385f, -0.004999f, -0.073532f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f, -0.013087f, -0.009509f, -0.073532f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f, -0.009509f, -0.013087f, -0.073532f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f, -0.004999f, -0.015385f, -0.073532f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f, 0.000000f, -0.016177f, -0.073532f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f, 0.004999f, -0.015385f, -0.073532f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f, 0.009509f, -0.013087f, -0.073532f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f, 0.013087f, -0.009509f, -0.073532f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f, 0.011341f, -0.017446f, -0.073532f,
0.487805f, 0.000000f, 0.039024f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, -0.052350f, -0.073532f,
};

float cylinderStrip[((sizeof(circleTop) / sizeof(float)) - 11) * 2];

// Millennium Falcon-style front mandibles.
float frontMandibles[] = {
1.000000f, 0.195122f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, -0.409280f, 
-0.048780f, 0.526829f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, -0.409280f, 
-0.048780f, 0.136585f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, -0.409280f, 
1.000000f, 0.195122f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.409280f, 
-0.048780f, 0.136585f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.409280f, 
-0.048780f, 0.526829f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, 0.409280f, 
-0.048780f, 0.526829f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 0.000000f, 0.019417f, 0.061391f, 0.000000f, 
1.000000f, 0.195122f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 0.000000f, 0.019417f, 0.061391f, 0.000000f, 
1.000000f, 0.195122f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 1.000000f, 0.019417f, 0.061391f, 0.000000f, 
-0.048780f, 0.526829f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 0.000000f, 0.019417f, 0.061391f, 0.000000f, 
1.000000f, 0.195122f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 1.000000f, 0.019417f, 0.061391f, 0.000000f, 
-0.048780f, 0.526829f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 1.000000f, 0.019417f, 0.061391f, 0.000000f, 
-0.048780f, 0.136585f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 0.000000f, 0.003427f, -0.061391f, 0.000000f, 
-0.048780f, 0.136585f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 0.000000f, 0.003427f, -0.061391f, 0.000000f, 
1.000000f, 0.195122f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 1.000000f, 0.003427f, -0.061391f, 0.000000f, 
-0.048780f, 0.136585f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 0.000000f, 0.003427f, -0.061391f, 0.000000f, 
1.000000f, 0.195122f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 1.000000f, 0.003427f, -0.061391f, 0.000000f, 
1.000000f, 0.195122f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 1.000000f, 0.003427f, -0.061391f, 0.000000f, 
-0.048780f, 0.526829f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f, 
-0.048780f, 0.526829f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f, 
-0.048780f, 0.136585f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, 0.526829f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, 0.136585f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, 0.136585f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
1.000000f, -0.195122f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, -0.409280f,
-0.048780f, -0.136585f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, -0.409280f,
-0.048780f, -0.526829f, -0.029268f, 0.780000f, 0.780000f, 0.800000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, -0.409280f,
1.000000f, -0.195122f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.409280f,
-0.048780f, -0.526829f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.409280f,
-0.048780f, -0.136585f, 0.029268f, 0.400000f, 0.400000f, 0.420000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, 0.409280f,
-0.048780f, -0.136585f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 0.000000f, 0.003427f, 0.061391f, 0.000000f,
1.000000f, -0.195122f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 0.000000f, 0.003427f, 0.061391f, 0.000000f,
1.000000f, -0.195122f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 1.000000f, 0.003427f, 0.061391f, 0.000000f,
-0.048780f, -0.136585f, -0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 0.000000f, 0.003427f, 0.061391f, 0.000000f,
1.000000f, -0.195122f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 1.000000f, 1.000000f, 0.003427f, 0.061391f, 0.000000f,
-0.048780f, -0.136585f, 0.029268f, 0.580000f, 0.580000f, 0.600000f, 0.000000f, 1.000000f, 0.003427f, 0.061391f, 0.000000f,
-0.048780f, -0.526829f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 0.000000f, 0.019417f, -0.061391f, 0.000000f,
-0.048780f, -0.526829f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 0.000000f, 0.019417f, -0.061391f, 0.000000f,
1.000000f, -0.195122f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 1.000000f, 0.019417f, -0.061391f, 0.000000f,
-0.048780f, -0.526829f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 0.000000f, 0.019417f, -0.061391f, 0.000000f,
1.000000f, -0.195122f, 0.029268f, 0.540000f, 0.540000f, 0.560000f, 1.000000f, 1.000000f, 0.019417f, -0.061391f, 0.000000f,
1.000000f, -0.195122f, -0.029268f, 0.540000f, 0.540000f, 0.560000f, 0.000000f, 1.000000f, 0.019417f, -0.061391f, 0.000000f,
-0.048780f, -0.136585f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, -0.136585f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, -0.526829f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, -0.136585f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 0.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, -0.526829f, 0.029268f, 0.520000f, 0.520000f, 0.540000f, 1.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
-0.048780f, -0.526829f, -0.029268f, 0.520000f, 0.520000f, 0.540000f, 0.000000f, 1.000000f, -0.022843f, 0.000000f, 0.000000f,
};

// Simple box mesh for add-on details like the center bar.
float podAttachment[] = {
0.243902f, 0.243902f, -0.243902f, 0.740000f, 0.740000f, 0.760000f, 0.000000f, 0.000000f, 0.237953f, 0.000000f, 0.000000f, 
0.243902f, -0.243902f, -0.243902f, 0.740000f, 0.740000f, 0.760000f, 1.000000f, 0.000000f, 0.237953f, 0.000000f, 0.000000f, 
0.243902f, -0.243902f, 0.243902f, 0.740000f, 0.740000f, 0.760000f, 1.000000f, 1.000000f, 0.237953f, 0.000000f, 0.000000f, 
0.243902f, 0.243902f, -0.243902f, 0.740000f, 0.740000f, 0.760000f, 0.000000f, 0.000000f, 0.237953f, 0.000000f, 0.000000f, 
0.243902f, -0.243902f, 0.243902f, 0.740000f, 0.740000f, 0.760000f, 1.000000f, 1.000000f, 0.237953f, 0.000000f, 0.000000f, 
0.243902f, 0.243902f, 0.243902f, 0.740000f, 0.740000f, 0.760000f, 0.000000f, 1.000000f, 0.237953f, 0.000000f, 0.000000f, 
-0.243902f, 0.243902f, -0.243902f, 0.420000f, 0.420000f, 0.440000f, 0.000000f, 0.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, -0.243902f, 0.243902f, 0.420000f, 0.420000f, 0.440000f, 1.000000f, 1.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, -0.243902f, -0.243902f, 0.420000f, 0.420000f, 0.440000f, 1.000000f, 0.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, 0.243902f, -0.243902f, 0.420000f, 0.420000f, 0.440000f, 0.000000f, 0.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, 0.243902f, 0.243902f, 0.420000f, 0.420000f, 0.440000f, 0.000000f, 1.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, -0.243902f, 0.243902f, 0.420000f, 0.420000f, 0.440000f, 1.000000f, 1.000000f, -0.237953f, 0.000000f, 0.000000f, 
-0.243902f, 0.243902f, -0.243902f, 0.620000f, 0.620000f, 0.640000f, 0.000000f, 0.000000f, 0.000000f, 0.237953f, 0.000000f, 
0.243902f, 0.243902f, -0.243902f, 0.620000f, 0.620000f, 0.640000f, 1.000000f, 0.000000f, 0.000000f, 0.237953f, 0.000000f, 
0.243902f, 0.243902f, 0.243902f, 0.620000f, 0.620000f, 0.640000f, 1.000000f, 1.000000f, 0.000000f, 0.237953f, 0.000000f, 
-0.243902f, 0.243902f, -0.243902f, 0.620000f, 0.620000f, 0.640000f, 0.000000f, 0.000000f, 0.000000f, 0.237953f, 0.000000f, 
0.243902f, 0.243902f, 0.243902f, 0.620000f, 0.620000f, 0.640000f, 1.000000f, 1.000000f, 0.000000f, 0.237953f, 0.000000f, 
-0.243902f, 0.243902f, 0.243902f, 0.620000f, 0.620000f, 0.640000f, 0.000000f, 1.000000f, 0.000000f, 0.237953f, 0.000000f, 
-0.243902f, -0.243902f, -0.243902f, 0.500000f, 0.500000f, 0.520000f, 0.000000f, 0.000000f, 0.000000f, -0.237953f, 0.000000f, 
0.243902f, -0.243902f, 0.243902f, 0.500000f, 0.500000f, 0.520000f, 1.000000f, 1.000000f, 0.000000f, -0.237953f, 0.000000f, 
0.243902f, -0.243902f, -0.243902f, 0.500000f, 0.500000f, 0.520000f, 1.000000f, 0.000000f, 0.000000f, -0.237953f, 0.000000f, 
-0.243902f, -0.243902f, -0.243902f, 0.500000f, 0.500000f, 0.520000f, 0.000000f, 0.000000f, 0.000000f, -0.237953f, 0.000000f, 
-0.243902f, -0.243902f, 0.243902f, 0.500000f, 0.500000f, 0.520000f, 0.000000f, 1.000000f, 0.000000f, -0.237953f, 0.000000f, 
0.243902f, -0.243902f, 0.243902f, 0.500000f, 0.500000f, 0.520000f, 1.000000f, 1.000000f, 0.000000f, -0.237953f, 0.000000f, 
-0.243902f, 0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.237953f,
0.243902f, 0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.237953f,
0.243902f, -0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.237953f,
-0.243902f, 0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.237953f,
0.243902f, -0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.237953f,
-0.243902f, -0.243902f, 0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.237953f,
-0.243902f, 0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, -0.237953f,
0.243902f, -0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, -0.237953f,
0.243902f, 0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, -0.237953f, 
-0.243902f, 0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, -0.237953f,
-0.243902f, -0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, -0.237953f,
0.243902f, -0.243902f, -0.243902f, 0.570000f, 0.570000f, 0.590000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, -0.237953f,
};

GLuint circleTopVAO;
GLuint circleTopVBO;
GLuint circleTopShader;

GLuint circleBottomVAO;
GLuint circleBottomVBO;
GLuint circleBottomShader;

GLuint triangleStripVAO;
GLuint triangleStripVBO;
GLuint triangleStripShader;

GLuint frontMandiblesVAO;
GLuint frontMandiblesVBO;
GLuint frontMandiblesShader;

GLuint podAttachmentVAO;
GLuint podAttachmentVBO;
GLuint podAttachmentShader;

GLuint base_texture;
GLuint middle_texture;
GLuint top_texture;
GLuint mandible_texture;
GLuint gun_texture;
GLuint pod_texture;

// This function is to generate the triangle strip between two circles
// Useful for generating cylinders
void generateCylinderStrip(const float* topCircle, const float* bottomCircle,
                            int size, float* cylinderStrip) {
    int idx = 0;
    for (int i = 11; i < size; i += 11) {
        std::copy(topCircle + i, topCircle + i + 11, cylinderStrip + idx);
        idx += 11;
        std::copy(bottomCircle + i, bottomCircle + i + 11, cylinderStrip + idx);
        idx += 11;
    }
}

// Helper function to setup multiple vaos and vbos
bool setupVO(GLuint& vao, GLuint& vbo, GLuint& shader, float* vertices, size_t size, const char* vs, const char* fs) {
    // generate the VAO and VBO objects and store their IDs in vao and vbo, respectively
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the newly-created VAO to make it the current one that OpenGL will apply state changes to
    glBindVertexArray(vao);

    // upload our vertex array data to the newly-created VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // on the VAO, register the current VBO with the following vertex attribute layout:
    // - the stride length of the vertex array is 6 floats (6 * sizeof(float))
    // - layout location 0 (position) is 3 floats and starts at the first float of the vertex array (offset 0)
    // - layout location 1 (color) is also 3 floats but starts at the fourth float (offset 3 * sizeof(float))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (6 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // enable the layout locations so they can be used by the vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // important: if you have more vertex arrays to draw, make sure you separately define them
    // with unique VAO and VBO IDs, and follow the same process above to upload them to the GPU

    // load our shader program
    shader = gdevLoadShader(vs, fs);
    if (! shader)
        return false;

    return true;
}

// draws a cylinder given the model-view-projection matrix and the shaders for each of the three sections.
// needs diff shaders since cylinders can have different textures.
void drawCylinder(GLuint topShader, GLuint bottomShader, GLuint sideShader,
                    const glm::mat4& projectionMatrix, const glm::mat4& modelMatrix) {

    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    // top cap
    glUseProgram(topShader);
    // sends exactly one matrix, without transposing it or anything. using the memory address of the glm matrix data.
    glUniformMatrix4fv(glGetUniformLocation(topShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(topShader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(topShader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glBindVertexArray(circleTopVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleTop) / (11 * sizeof(float)));
    
    // bottom cap
    glUseProgram(bottomShader);
    glUniformMatrix4fv(glGetUniformLocation(bottomShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(bottomShader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(bottomShader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glBindVertexArray(circleBottomVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleBottom) / (11 * sizeof(float)));

    // side walls of the the circles
    glUseProgram(sideShader);
    glUniformMatrix4fv(glGetUniformLocation(sideShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(sideShader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(sideShader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glBindVertexArray(triangleStripVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(cylinderStrip) / (11 * sizeof(float)));
}

// draws the box section at the center of the falcon. needs a shader and a matrix
void drawPodSection(GLuint shader, const glm::mat4& projectionMatrix, const glm::mat4& modelMatrix) {
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glBindVertexArray(podAttachmentVAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(podAttachment) / (11 * sizeof(float)));
}

// called by the main function to do initial setup, such as uploading vertex
// arrays, shader programs, etc.; returns true if successful, false otherwise
bool setup() {
    generateCylinderStrip(
        circleTop,
        circleBottom,
        sizeof(circleTop) / sizeof(float),
        cylinderStrip
    );

    if(!setupVO(
        circleTopVAO,
        circleTopVBO,
        circleTopShader,
        circleTop,
        sizeof(circleTop),
        "circleTop.vs",
        "circleTop.fs"
    )) {
        return false;
    }

    if(!setupVO(
        circleBottomVAO,
        circleBottomVBO,
        circleBottomShader,
        circleBottom,
        sizeof(circleBottom),
        "circleTop.vs",
        "circleTop.fs"
    )) {
        return false;
    }

    if(!setupVO(
        triangleStripVAO,
        triangleStripVBO,
        triangleStripShader,
        cylinderStrip,
        sizeof(cylinderStrip),
        "circleTop.vs",
        "circleTop.fs"
    )) {
        return false;
    }

    if(!setupVO(
        frontMandiblesVAO,
        frontMandiblesVBO,
        frontMandiblesShader,
        frontMandibles,
        sizeof(frontMandibles),
        "circleTop.vs",
        "circleTop.fs"
    )) {
        return false;
    }

    if(!setupVO(
        podAttachmentVAO,
        podAttachmentVBO,
        podAttachmentShader,
        podAttachment,
        sizeof(podAttachment),
        "circleTop.vs",
        "circleTop.fs"
    )) {
        return false;
    }

    base_texture = gdevLoadTexture("falcon_base.png", GL_REPEAT, true, true);
    if (!base_texture) return false;

    middle_texture = gdevLoadTexture("falcon_middle.png", GL_REPEAT, true, true);
    if (!middle_texture) return false;

    top_texture = gdevLoadTexture("falcon_top.png", GL_REPEAT, true, true);
    if (!top_texture) return false;

    mandible_texture = gdevLoadTexture("falcon_mandible.png", GL_REPEAT, true, true);
    if (!mandible_texture) return false;

    gun_texture = gdevLoadTexture("falcon_gun.png", GL_REPEAT, true, true);
    if (!gun_texture) return false;

    pod_texture = gdevLoadTexture("falcon_pod.png", GL_REPEAT, true, true);
    if (!pod_texture) return false;
    return true;
}

void drawMilleniumFalcon(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    // The raw vertex arrays are scaled down to fit [-1, 1], so scale the
    // assembled ship back up here for a readable on-screen size.
    glm::mat4 projectionView = projection * view;
    model = glm::translate(model, glm::vec3(-0.09f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.44f, 1.44f, 1.44f));

    // Main saucer: flatter and wider to read more like the Falcon hull.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, base_texture);

    glm::mat4 baseHull = glm::scale(model, glm::vec3(1.16f, 0.94f, 0.26f));
    drawCylinder(circleTopShader, circleBottomShader, triangleStripShader, projectionView, baseHull);

    // Raised center body: pulled slightly rearward to mimic the Falcon's top mass.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, middle_texture);

    // Connector slab so the base hull and middle hull read as one continuous body.
    glm::mat4 centerConnector = glm::translate(model, glm::vec3(-0.09f, 0.0f, -0.03f));
    centerConnector = glm::scale(centerConnector, glm::vec3(1.02f, 0.84f, 0.22f));
    drawPodSection(podAttachmentShader, projectionView, centerConnector);
    
    glm::mat4 centerBody = glm::translate(model, glm::vec3(-0.09f, 0.0f, -0.05f));
    centerBody = glm::scale(centerBody, glm::vec3(0.95f, 0.78f, 0.16f));
    drawCylinder(circleTopShader, circleBottomShader, triangleStripShader, projectionView, centerBody);

    // Highest central hump: smaller and offset so the middle protrudes.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, top_texture);

    // Secondary connector to remove the gap between middle hull and top hump.
    glm::mat4 humpConnector = glm::translate(model, glm::vec3(-0.04f, 0.0f, -0.09f));
    humpConnector = glm::scale(humpConnector, glm::vec3(0.58f, 0.48f, 0.14f));
    drawPodSection(podAttachmentShader, projectionView, humpConnector);
    
    glm::mat4 dorsalHump = glm::translate(model, glm::vec3(-0.02f, 0.0f, -0.10f));
    dorsalHump = glm::scale(dorsalHump, glm::vec3(0.50f, 0.44f, 0.11f));
    drawCylinder(circleTopShader, circleBottomShader, triangleStripShader, projectionView, dorsalHump);
    
    // Mandibles
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mandible_texture);
    
    glm::mat4 mandibleModel = glm::translate(model, glm::vec3(0.34f, 0.0f, -0.01f));
    mandibleModel = glm::scale(mandibleModel, glm::vec3(0.74f, 0.76f, 0.35f));
    glm::mat4 mandibleNormal = glm::transpose(glm::inverse(mandibleModel));

    glUseProgram(frontMandiblesShader);
    glUniformMatrix4fv(glGetUniformLocation(frontMandiblesShader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionView));
    glUniformMatrix4fv(glGetUniformLocation(frontMandiblesShader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(mandibleModel));
    glUniformMatrix4fv(glGetUniformLocation(frontMandiblesShader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(mandibleNormal));
    glBindVertexArray(frontMandiblesVAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(frontMandibles) / (11 * sizeof(float)));

    // Center fork bar between the mandibles, extending in the same forward direction.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gun_texture);

    glm::mat4 centerBar = glm::translate(model, glm::vec3(0.59f, 0.0f, -0.01f));
    centerBar = glm::scale(centerBar, glm::vec3(0.95f, 0.16f, 0.18f));
    drawPodSection(podAttachmentShader, projectionView, centerBar);

    // Pods
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pod_texture);
    // Side thruster pods mounted near the rear flanks.
    glm::mat4 upperThruster = glm::translate(model, glm::vec3(-0.43f, 0.36f, 0.01f));
    upperThruster = glm::scale(upperThruster, glm::vec3(0.24f, 0.24f, 0.13f));
    drawCylinder(circleTopShader, circleBottomShader, triangleStripShader, projectionView, upperThruster);

    glm::mat4 lowerThruster = glm::translate(model, glm::vec3(-0.43f, -0.36f, 0.01f));
    lowerThruster = glm::scale(lowerThruster, glm::vec3(0.24f, 0.24f, 0.13f));
    drawCylinder(circleTopShader, circleBottomShader, triangleStripShader, projectionView, lowerThruster);
}

// called by the main function to do rendering per frame
void render()
{
    // gets the time elapsed between the current frame and the last frame, and updates the last frame time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // view matrix
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // camera movement speed
    float cameraSpeed = 1.5f * deltaTime;

    // key inputs for movement
    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;

    // clear the whole frame
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // GLOBALS
    float time = glfwGetTime();

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    
    // flight animation
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::translate(model1, glm::vec3(0.0f, 0.25f, -5.0f));
    model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model1 = glm::rotate(model1, glm::radians(sin(time * 0.75f) * 45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model1 = glm::scale(model1, glm::vec3(sin(time) * 1.8f, sin(time)* 1.8f, sin(time)* 1.8f));

    // rotation animation
    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2, glm::vec3(5.0f, 0.0f, -5.0f));
    model2 = glm::rotate(model2, glm::radians(time * 75.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model2 = glm::rotate(model2, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model2 = glm::scale(model2, glm::vec3(1.5f, 1.5f, 1.5f));
    
    // barrel role animation
    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::translate(model3, glm::vec3(-5.0f + sin(time * 0.9f) * 0.55f, -0.15f, -5.0f));
    model3 = glm::rotate(model3, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model3 = glm::rotate(model3, glm::radians(sin(time * 1.2f) * 8.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model3 = glm::rotate(model3, glm::radians(time * 220.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model3 = glm::scale(model3, glm::vec3(1.5f, 1.5f, 1.5f));

    drawMilleniumFalcon(model1, view, projection);
    drawMilleniumFalcon(model2, view, projection);
    drawMilleniumFalcon(model3, view, projection);
}

/*****************************************************************************/
// mouse movement function
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    // checks if program just started, gets the last x and y values
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    // x and y offsets
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity;

    // sets the last x and y values to xpos and ypos
    lastX = xpos;
    lastY = ypos;
    
    // adds the x and y offsets to yaw and pitch
    yaw += xoffset;
    pitch += yoffset;

    // limits the pitch
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // calculates the camera front vector based on the yaw and pitch values
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}  

// handler called by GLFW when there is a keyboard event
void handleKeys(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    // pressing Esc closes the window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}

// handler called by GLFW when the window is resized
void handleResize(GLFWwindow* pWindow, int width, int height)
{
    // tell OpenGL to do its drawing within the entire "client area" (area within the borders) of the window
    glViewport(0, 0, width, height);
}

// main function
int main(int argc, char** argv)
{
    // initialize GLFW and ask for OpenGL 3.3 core
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // hides the screen first so that it can be readjusted
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // create a GLFW window with the specified width, height, and title
    pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (! pWindow)
    {
        // gracefully terminate if we cannot create the window
        std::cout << "Cannot create the GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    // make the window the current context of subsequent OpenGL commands,
    // and enable vertical sync and aspect-ratio correction on the GLFW window
    glfwMakeContextCurrent(pWindow);
    glfwSwapInterval(1);
    glfwSetWindowAspectRatio(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

    // gets the primary monitor's video mode to calculate the center position of the window, and moves the window there
    // https://www.glfw.org/docs/latest/monitor_guide.html
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    int xpos = (mode->width - WINDOW_WIDTH) / 2;
    int ypos = (mode->height - WINDOW_HEIGHT) / 2;

    // sets the window's position and displays the window
    glfwSetWindowPos(pWindow, xpos, ypos);
    glfwShowWindow(pWindow);

    // set up callback functions to handle window system events
    glfwSetKeyCallback(pWindow, handleKeys);
    glfwSetFramebufferSizeCallback(pWindow, handleResize);

    // don't miss any momentary keypresses
    glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

    // set up mouse movement callback and enable raw mouse motion if supported
    glfwSetCursorPosCallback(pWindow, mouseCallback);
    
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(pWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    // initialize GLAD, which acts as a library loader for the current OS's native OpenGL library
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // set the mouse cursor to the center of the window at the start of the program
    glfwSetCursorPos(pWindow, WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0);

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // if our initial setup is successful...
    if (setup())
    {
        // do rendering in a loop until the user closes the window
        while (! glfwWindowShouldClose(pWindow))
        {
            // render our next frame
            // (by default, GLFW uses double-buffering with a front and back buffer;
            // all drawing goes to the back buffer, so the frame does not get shown yet)
            render();

            // swap the GLFW front and back buffers to show the next frame
            glfwSwapBuffers(pWindow);

            // process any window events (such as moving, resizing, keyboard presses, etc.)
            glfwPollEvents();
        }
    }

    // gracefully terminate the program
    glfwTerminate();
    return 0;
}
