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
0.0f, 0.0f, -0.08f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
0.9510565162951472f, 0.3090169943749671f, -0.3f, 1.0f, 1.0f, 1.0f, 0.9510565162951472f, 0.3090169943749671f,
0.8090169943749231f, 0.5877852522925067f, -0.3f, 1.0f, 1.0f, 1.0f, 0.8090169943749231f, 0.5877852522925067f,
0.5877852522924228f, 0.809016994374984f, -0.3f, 1.0f, 1.0f, 1.0f, 0.5877852522924228f, 0.809016994374984f,
0.3090169943748687f, 0.9510565162951792f, -0.3f, 1.0f, 1.0f, 1.0f, 0.3090169943748687f, 0.9510565162951792f,
-1.0341155355510722E-13f, 1.0f, -0.3f, 1.0f, 1.0f, 1.0f, -1.0341155355510722E-13f, 1.0f,
-0.3090169943750654f, 0.9510565162951152f, -0.3f, 1.0f, 1.0f, 1.0f, -0.3090169943750654f, 0.9510565162951152f,
-0.5877852522925902f, 0.8090169943748624f, -0.3f, 1.0f, 1.0f, 1.0f, -0.5877852522925902f, 0.8090169943748624f,
-0.8090169943750447f, 0.5877852522923392f, -0.3f, 1.0f, 1.0f, 1.0f, -0.8090169943750447f, 0.5877852522923392f,
-0.9510565162952112f, 0.30901699437477015f, -0.3f, 1.0f, 1.0f, 1.0f, -0.9510565162952112f, 0.30901699437477015f,
-1.0f, -2.072671963200645E-13f, -0.3f, 1.0f, 1.0f, 1.0f, -1.0f, -2.072671963200645E-13f,
-0.951056516295083f, -0.3090169943751644f, -0.3f, 1.0f, 1.0f, 1.0f, -0.951056516295083f, -0.3090169943751644f,
-0.8090169943748011f, -0.5877852522926745f, -0.3f, 1.0f, 1.0f, 1.0f, -0.8090169943748011f, -0.5877852522926745f,
-0.5877852522922549f, -0.809016994375106f, -0.3f, 1.0f, 1.0f, 1.0f, -0.5877852522922549f, -0.809016994375106f,
-0.3090169943746714f, -0.9510565162952432f, -0.3f, 1.0f, 1.0f, 1.0f, -0.3090169943746714f, -0.9510565162952432f,
3.1067874987517174E-13f, -1.0f, -0.3f, 1.0f, 1.0f, 1.0f, 3.1067874987517174E-13f, -1.0f,
0.3090169943752623f, -0.9510565162950513f, -0.3f, 1.0f, 1.0f, 1.0f, 0.3090169943752623f, -0.9510565162950513f,
0.5877852522927575f, -0.8090169943747408f, -0.3f, 1.0f, 1.0f, 1.0f, 0.5877852522927575f, -0.8090169943747408f,
0.809016994375166f, -0.5877852522921723f, -0.3f, 1.0f, 1.0f, 1.0f, 0.809016994375166f, -0.5877852522921723f,
0.9510565162952748f, -0.3090169943745743f, -0.3f, 1.0f, 1.0f, 1.0f, 0.9510565162952748f, -0.3090169943745743f,
1.0f, 4.1275803580072876E-13f, -0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 4.1275803580072876E-13f,
0.9510565162950197f, 0.3090169943753594f, -0.3f, 1.0f, 1.0f, 1.0f, 0.9510565162950197f, 0.3090169943753594f,
0.8090169943746808f, 0.5877852522928401f, -0.3f, 1.0f, 1.0f, 1.0f, 0.8090169943746808f, 0.5877852522928401f,
0.5877852522920897f, 0.809016994375226f, -0.3f, 1.0f, 1.0f, 1.0f, 0.5877852522920897f, 0.809016994375226f,
0.3090169943744772f, 0.9510565162953064f, -0.3f, 1.0f, 1.0f, 1.0f, 0.3090169943744772f, 0.9510565162953064f,
-5.148373217262858E-13f, 1.0f, -0.3f, 1.0f, 1.0f, 1.0f, -5.148373217262858E-13f, 1.0f,
-0.3090169943754573f, 0.9510565162949879f, -0.3f, 1.0f, 1.0f, 1.0f, -0.3090169943754573f, 0.9510565162949879f,
-0.5877852522929241f, 0.8090169943746197f, -0.3f, 1.0f, 1.0f, 1.0f, -0.5877852522929241f, 0.8090169943746197f,
-0.8090169943752876f, 0.587785252292005f, -0.3f, 1.0f, 1.0f, 1.0f, -0.8090169943752876f, 0.587785252292005f,
-0.951056516295339f, 0.30901699437437674f, -0.3f, 1.0f, 1.0f, 1.0f, -0.951056516295339f, 0.30901699437437674f,
-1.0f, -6.213574997503435E-13f, -0.3f, 1.0f, 1.0f, 1.0f, -1.0f, -6.213574997503435E-13f,
-0.951056516294955f, -0.30901699437555863f, -0.3f, 1.0f, 1.0f, 1.0f, -0.951056516294955f, -0.30901699437555863f,
-0.8090169943745572f, -0.5877852522930103f, -0.3f, 1.0f, 1.0f, 1.0f, -0.8090169943745572f, -0.5877852522930103f,
-0.5877852522919187f, -0.8090169943753502f, -0.3f, 1.0f, 1.0f, 1.0f, -0.5877852522919187f, -0.8090169943753502f,
-0.30901699437427543f, -0.9510565162953719f, -0.3f, 1.0f, 1.0f, 1.0f, -0.30901699437427543f, -0.9510565162953719f,
7.278776777744011E-13f, -1.0f, -0.3f, 1.0f, 1.0f, 1.0f, 7.278776777744011E-13f, -1.0f,
0.30901699437565994f, -0.951056516294922f, -0.3f, 1.0f, 1.0f, 1.0f, 0.30901699437565994f, -0.951056516294922f,
0.5877852522930964f, -0.8090169943744946f, -0.3f, 1.0f, 1.0f, 1.0f, 0.5877852522930964f, -0.8090169943744946f,
0.8090169943754129f, -0.5877852522918325f, -0.3f, 1.0f, 1.0f, 1.0f, 0.8090169943754129f, -0.5877852522918325f,
0.9510565162954049f, -0.3090169943741741f, -0.3f, 1.0f, 1.0f, 1.0f, 0.9510565162954049f, -0.3090169943741741f,
1.0f, 8.343978557984588E-13f, -0.08f, 1.0f, 1.0f, 1.0f, 1.0f, 8.343978557984588E-13f,
};

float circleBottom[] = {
0.0f, 0.0f, 0.08f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
0.9510565162951472f, 0.3090169943749671f, 0.3f, 0.5f, 0.5f, 0.5f, 0.9510565162951472f, 0.3090169943749671f,
0.8090169943749231f, 0.5877852522925067f, 0.3f, 0.5f, 0.5f, 0.5f, 0.8090169943749231f, 0.5877852522925067f,
0.5877852522924228f, 0.809016994374984f, 0.3f, 0.5f, 0.5f, 0.5f, 0.5877852522924228f, 0.809016994374984f,
0.3090169943748687f, 0.9510565162951792f, 0.3f, 0.5f, 0.5f, 0.5f, 0.3090169943748687f, 0.9510565162951792f,
-1.0341155355510722E-13f, 1.0f, 0.3f, 0.5f, 0.5f, 0.5f, -1.0341155355510722E-13f, 1.0f,
-0.3090169943750654f, 0.9510565162951152f, 0.3f, 0.5f, 0.5f, 0.5f, -0.3090169943750654f, 0.9510565162951152f,
-0.5877852522925902f, 0.8090169943748624f, 0.3f, 0.5f, 0.5f, 0.5f, -0.5877852522925902f, 0.8090169943748624f,
-0.8090169943750447f, 0.5877852522923392f, 0.3f, 0.5f, 0.5f, 0.5f, -0.8090169943750447f, 0.5877852522923392f,
-0.9510565162952112f, 0.30901699437477015f, 0.3f, 0.5f, 0.5f, 0.5f, -0.9510565162952112f, 0.30901699437477015f,
-1.0f, -2.072671963200645E-13f, 0.3f, 0.5f, 0.5f, 0.5f, -1.0f, -2.072671963200645E-13f,
-0.951056516295083f, -0.3090169943751644f, 0.3f, 0.5f, 0.5f, 0.5f, -0.951056516295083f, -0.3090169943751644f,
-0.8090169943748011f, -0.5877852522926745f, 0.3f, 0.5f, 0.5f, 0.5f, -0.8090169943748011f, -0.5877852522926745f,
-0.5877852522922549f, -0.809016994375106f, 0.3f, 0.5f, 0.5f, 0.5f, -0.5877852522922549f, -0.809016994375106f,
-0.3090169943746714f, -0.9510565162952432f, 0.3f, 0.5f, 0.5f, 0.5f, -0.3090169943746714f, -0.9510565162952432f,
3.1067874987517174E-13f, -1.0f, 0.3f, 0.5f, 0.5f, 0.5f, 3.1067874987517174E-13f, -1.0f,
0.3090169943752623f, -0.9510565162950513f, 0.3f, 0.5f, 0.5f, 0.5f, 0.3090169943752623f, -0.9510565162950513f,
0.5877852522927575f, -0.8090169943747408f, 0.3f, 0.5f, 0.5f, 0.5f, 0.5877852522927575f, -0.8090169943747408f,
0.809016994375166f, -0.5877852522921723f, 0.3f, 0.5f, 0.5f, 0.5f, 0.809016994375166f, -0.5877852522921723f,
0.9510565162952748f, -0.3090169943745743f, 0.3f, 0.5f, 0.5f, 0.5f, 0.9510565162952748f, -0.3090169943745743f,
1.0f, 4.1275803580072876E-13f, 0.3f, 0.5f, 0.5f, 0.5f, 1.0f, 4.1275803580072876E-13f,
0.9510565162950197f, 0.3090169943753594f, 0.3f, 0.5f, 0.5f, 0.5f, 0.9510565162950197f, 0.3090169943753594f,
0.8090169943746808f, 0.5877852522928401f, 0.3f, 0.5f, 0.5f, 0.5f, 0.8090169943746808f, 0.5877852522928401f,
0.5877852522920897f, 0.809016994375226f, 0.3f, 0.5f, 0.5f, 0.5f, 0.5877852522920897f, 0.809016994375226f,
0.3090169943744772f, 0.9510565162953064f, 0.3f, 0.5f, 0.5f, 0.5f, 0.3090169943744772f, 0.9510565162953064f,
-5.148373217262858E-13f, 1.0f, 0.3f, 0.5f, 0.5f, 0.5f, -5.148373217262858E-13f, 1.0f,
-0.3090169943754573f, 0.9510565162949879f, 0.3f, 0.5f, 0.5f, 0.5f, -0.3090169943754573f, 0.9510565162949879f,
-0.5877852522929241f, 0.8090169943746197f, 0.3f, 0.5f, 0.5f, 0.5f, -0.5877852522929241f, 0.8090169943746197f,
-0.8090169943752876f, 0.587785252292005f, 0.3f, 0.5f, 0.5f, 0.5f, -0.8090169943752876f, 0.587785252292005f,
-0.951056516295339f, 0.30901699437437674f, 0.3f, 0.5f, 0.5f, 0.5f, -0.951056516295339f, 0.30901699437437674f,
-1.0f, -6.213574997503435E-13f, 0.3f, 0.5f, 0.5f, 0.5f, -1.0f, -6.213574997503435E-13f,
-0.951056516294955f, -0.30901699437555863f, 0.3f, 0.5f, 0.5f, 0.5f, -0.951056516294955f, -0.30901699437555863f,
-0.8090169943745572f, -0.5877852522930103f, 0.3f, 0.5f, 0.5f, 0.5f, -0.8090169943745572f, -0.5877852522930103f,
-0.5877852522919187f, -0.8090169943753502f, 0.3f, 0.5f, 0.5f, 0.5f, -0.5877852522919187f, -0.8090169943753502f,
-0.30901699437427543f, -0.9510565162953719f, 0.3f, 0.5f, 0.5f, 0.5f, -0.30901699437427543f, -0.9510565162953719f,
7.278776777744011E-13f, -1.0f, 0.3f, 0.5f, 0.5f, 0.5f, 7.278776777744011E-13f, -1.0f,
0.30901699437565994f, -0.951056516294922f, 0.3f, 0.5f, 0.5f, 0.5f, 0.30901699437565994f, -0.951056516294922f,
0.5877852522930964f, -0.8090169943744946f, 0.3f, 0.5f, 0.5f, 0.5f, 0.5877852522930964f, -0.8090169943744946f,
0.8090169943754129f, -0.5877852522918325f, 0.3f, 0.5f, 0.5f, 0.5f, 0.8090169943754129f, -0.5877852522918325f,
0.9510565162954049f, -0.3090169943741741f, 0.3f, 0.5f, 0.5f, 0.5f, 0.9510565162954049f, -0.3090169943741741f,
1.0f, 8.343978557984588E-13f, 0.08f, 0.5f, 0.5f, 0.5f, 1.0f, 8.343978557984588E-13f,
};

float cylinderStrip[((sizeof(circleTop) / sizeof(float)) - 8) * 2];

// Millennium Falcon-style front mandibles.
float frontMandibles[] = {
    // Upper mandible: front face triangle
    2.05f, 0.40f, -0.06f, 0.78f, 0.78f, 0.80f, 0.0f, 0.0f,
    -0.10f, 1.08f, -0.06f, 0.78f, 0.78f, 0.80f, 1.0f, 0.0f,
    -0.10f, 0.28f, -0.06f, 0.78f, 0.78f, 0.80f, 0.5f, 1.0f,

    // Upper mandible: back face triangle
    2.05f, 0.40f, 0.06f, 0.40f, 0.40f, 0.42f, 0.0f, 0.0f,
    -0.10f, 0.28f, 0.06f, 0.40f, 0.40f, 0.42f, 1.0f, 0.0f,
    -0.10f, 1.08f, 0.06f, 0.40f, 0.40f, 0.42f, 0.5f, 1.0f,

    // Upper mandible: side faces
    -0.10f, 1.08f, -0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 0.0f,
    2.05f, 0.40f, -0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 0.0f,
    2.05f, 0.40f, 0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 1.0f,
    -0.10f, 1.08f, -0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 0.0f,
    2.05f, 0.40f, 0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 1.0f,
    -0.10f, 1.08f, 0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 1.0f,

    -0.10f, 0.28f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 0.0f,
    -0.10f, 0.28f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 0.0f,
    2.05f, 0.40f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 1.0f,
    -0.10f, 0.28f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 0.0f,
    2.05f, 0.40f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 1.0f,
    2.05f, 0.40f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 1.0f,

    -0.10f, 1.08f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 0.0f,
    -0.10f, 1.08f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 0.0f,
    -0.10f, 0.28f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 1.0f,
    -0.10f, 1.08f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 0.0f,
    -0.10f, 0.28f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 1.0f,
    -0.10f, 0.28f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 1.0f,

    // Lower mandible: front face triangle
    2.05f, -0.40f, -0.06f, 0.78f, 0.78f, 0.80f, 0.0f, 0.0f,
    -0.10f, -0.28f, -0.06f, 0.78f, 0.78f, 0.80f, 1.0f, 0.0f,
    -0.10f, -1.08f, -0.06f, 0.78f, 0.78f, 0.80f, 0.5f, 1.0f,

    // Lower mandible: back face triangle
    2.05f, -0.40f, 0.06f, 0.40f, 0.40f, 0.42f, 0.0f, 0.0f,
    -0.10f, -1.08f, 0.06f, 0.40f, 0.40f, 0.42f, 1.0f, 0.0f,
    -0.10f, -0.28f, 0.06f, 0.40f, 0.40f, 0.42f, 0.5f, 1.0f,

    // Lower mandible: side faces
    -0.10f, -0.28f, -0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 0.0f,
    2.05f, -0.40f, -0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 0.0f,
    2.05f, -0.40f, 0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 1.0f,
    -0.10f, -0.28f, -0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 0.0f,
    2.05f, -0.40f, 0.06f, 0.58f, 0.58f, 0.60f, 1.0f, 1.0f,
    -0.10f, -0.28f, 0.06f, 0.58f, 0.58f, 0.60f, 0.0f, 1.0f,

    -0.10f, -1.08f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 0.0f,
    -0.10f, -1.08f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 0.0f,
    2.05f, -0.40f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 1.0f,
    -0.10f, -1.08f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 0.0f,
    2.05f, -0.40f, 0.06f, 0.54f, 0.54f, 0.56f, 1.0f, 1.0f,
    2.05f, -0.40f, -0.06f, 0.54f, 0.54f, 0.56f, 0.0f, 1.0f,

    -0.10f, -0.28f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 0.0f,
    -0.10f, -0.28f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 0.0f,
    -0.10f, -1.08f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 1.0f,
    -0.10f, -0.28f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 0.0f,
    -0.10f, -1.08f, 0.06f, 0.52f, 0.52f, 0.54f, 1.0f, 1.0f,
    -0.10f, -1.08f, -0.06f, 0.52f, 0.52f, 0.54f, 0.0f, 1.0f,
};

// Simple box mesh for add-on details like the center bar.
float podAttachment[] = {
    // Front
    0.5f,  0.5f, -0.5f, 0.74f, 0.74f, 0.76f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.74f, 0.74f, 0.76f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.74f, 0.74f, 0.76f, 1.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 0.74f, 0.74f, 0.76f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.74f, 0.74f, 0.76f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 0.74f, 0.74f, 0.76f, 0.0f, 1.0f,

    // Back
    -0.5f,  0.5f, -0.5f, 0.42f, 0.42f, 0.44f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.42f, 0.42f, 0.44f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.42f, 0.42f, 0.44f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.42f, 0.42f, 0.44f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.42f, 0.42f, 0.44f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.42f, 0.42f, 0.44f, 1.0f, 1.0f,

    // Top
    -0.5f,  0.5f, -0.5f, 0.62f, 0.62f, 0.64f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 0.62f, 0.62f, 0.64f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 0.62f, 0.62f, 0.64f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.62f, 0.62f, 0.64f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 0.62f, 0.62f, 0.64f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.62f, 0.62f, 0.64f, 0.0f, 1.0f,

    // Bottom
    -0.5f, -0.5f, -0.5f, 0.50f, 0.50f, 0.52f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.50f, 0.50f, 0.52f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.50f, 0.50f, 0.52f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.50f, 0.50f, 0.52f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.50f, 0.50f, 0.52f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 0.50f, 0.50f, 0.52f, 1.0f, 1.0f,

    // Right
    -0.5f,  0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 1.0f,

    // Left
    -0.5f,  0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.57f, 0.57f, 0.59f, 1.0f, 1.0f,
};
// not used, similar to square.fs and .vs
// GLuint squareVAO;
// GLuint squareVBO;
// GLuint squareShader;

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
    for (int i = 8; i < size; i += 8) {
        std::copy(topCircle + i, topCircle + i + 8, cylinderStrip + idx);
        idx += 8;
        std::copy(bottomCircle + i, bottomCircle + i + 8, cylinderStrip + idx);
        idx += 8;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));

    // enable the layout locations so they can be used by the vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // important: if you have more vertex arrays to draw, make sure you separately define them
    // with unique VAO and VBO IDs, and follow the same process above to upload them to the GPU

    // load our shader program
    shader = gdevLoadShader(vs, fs);
    if (! shader)
        return false;

    return true;
}

void drawCircularSection(GLuint topShader, GLuint bottomShader, GLuint sideShader,
                        const glm::mat4& matrix) {
    // top cap
    glUseProgram(topShader);
    // sends exactly one matrix, without transposing it or anything. using the memory address of the glm matrix data.
    glUniformMatrix4fv(glGetUniformLocation(topShader, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
    glBindVertexArray(circleTopVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleTop) / (8 * sizeof(float)));
    
    // bottom cap
    glUseProgram(bottomShader);
    glUniformMatrix4fv(glGetUniformLocation(bottomShader, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
    glBindVertexArray(circleBottomVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleBottom) / (8 * sizeof(float)));

    // side walls of the the circles
    glUseProgram(sideShader);
    glUniformMatrix4fv(glGetUniformLocation(sideShader, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
    glBindVertexArray(triangleStripVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(cylinderStrip) / (8 * sizeof(float)));
}

void drawPrismSection(GLuint shader, const glm::mat4& matrix) {
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "matrix"),
        1, GL_FALSE, glm::value_ptr(matrix));
    glBindVertexArray(podAttachmentVAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(podAttachment) / (8 * sizeof(float)));
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
    if (!top_texture) return false;

    gun_texture = gdevLoadTexture("falcon_gun.png", GL_REPEAT, true, true);
    if (!top_texture) return false;

    pod_texture = gdevLoadTexture("falcon_pod.png", GL_REPEAT, true, true);
    if (!top_texture) return false;
    return true;
}

void drawMilleniumFalcon(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    // Main saucer: flatter and wider to read more like the Falcon hull.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, base_texture);

    glm::mat4 baseHull = glm::scale(model, glm::vec3(1.55f, 1.25f, 0.26f));
    drawCircularSection(circleTopShader, circleBottomShader, triangleStripShader,
        projection * view * baseHull);

    // Raised center body: pulled slightly rearward to mimic the Falcon's top mass.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, middle_texture);

    // Connector slab so the base hull and middle hull read as one continuous body.
    glm::mat4 centerConnector = glm::translate(model, glm::vec3(-0.18f, 0.0f, -0.07f));
    centerConnector = glm::scale(centerConnector, glm::vec3(1.02f, 0.84f, 0.22f));
    drawPrismSection(podAttachmentShader, projection * view * centerConnector);
    
    glm::mat4 centerBody = glm::translate(model, glm::vec3(-0.18f, 0.0f, -0.10f));
    centerBody = glm::scale(centerBody, glm::vec3(0.95f, 0.78f, 0.16f));
    drawCircularSection(circleTopShader, circleBottomShader, triangleStripShader,
        projection * view * centerBody);

    // Highest central hump: smaller and offset so the middle protrudes.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, top_texture);

    // Secondary connector to remove the gap between middle hull and top hump.
    glm::mat4 humpConnector = glm::translate(model, glm::vec3(-0.08f, 0.0f, -0.18f));
    humpConnector = glm::scale(humpConnector, glm::vec3(0.58f, 0.48f, 0.14f));
    drawPrismSection(podAttachmentShader, projection * view * humpConnector);
    
    glm::mat4 dorsalHump = glm::translate(model, glm::vec3(-0.05f, 0.0f, -0.21f));
    dorsalHump = glm::scale(dorsalHump, glm::vec3(0.50f, 0.44f, 0.11f));
    drawCircularSection(circleTopShader, circleBottomShader, triangleStripShader,
        projection * view * dorsalHump);
    
    // Mandible
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mandible_texture);
    
    glm::mat4 mandibleModel = glm::translate(model, glm::vec3(0.96f, 0.0f, -0.02f));
    mandibleModel = glm::scale(mandibleModel, glm::vec3(0.72f, 0.76f, 0.95f));
    glm::mat4 mandibleMatrix = projection * view * mandibleModel;

    glUseProgram(frontMandiblesShader);
    glUniformMatrix4fv(
        glGetUniformLocation(frontMandiblesShader, "matrix"),
        1,
        GL_FALSE,
        glm::value_ptr(mandibleMatrix)
    );

    glBindVertexArray(frontMandiblesVAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(frontMandibles) / (8 * sizeof(float)));

    // Center fork bar between the mandibles, extending in the same forward direction.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gun_texture);

    glm::mat4 centerBar = glm::translate(model, glm::vec3(1.20f, 0.0f, -0.03f));
    centerBar = glm::scale(centerBar, glm::vec3(0.95f, 0.16f, 0.18f));
    drawPrismSection(podAttachmentShader, projection * view * centerBar);

    // Pods
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pod_texture);
    // Side thruster pods mounted near the rear flanks.
    glm::mat4 upperThruster = glm::translate(model, glm::vec3(-1.05f, 0.92f, 0.02f));
    upperThruster = glm::scale(upperThruster, glm::vec3(0.24f, 0.24f, 0.13f));
    drawCircularSection(circleTopShader, circleBottomShader, triangleStripShader,
        projection * view * upperThruster);

    glm::mat4 lowerThruster = glm::translate(model, glm::vec3(-1.05f, -0.92f, 0.02f));
    lowerThruster = glm::scale(lowerThruster, glm::vec3(0.24f, 0.24f, 0.13f));
    drawCircularSection(circleTopShader, circleBottomShader, triangleStripShader,
        projection * view * lowerThruster);
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
    
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, -5.0f));
    model1 = glm::rotate(model1, glm::radians(time*100), glm::vec3(0.0f, 1.0f, 0.0f));
    model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2, glm::vec3(5.0f, 0.0f, -5.0f));
    model2 = glm::rotate(model2, glm::radians(time*100), glm::vec3(0.0f, 1.0f, 1.0f));
    model2 = glm::rotate(model2, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model2 = glm::scale(model2, glm::vec3(abs(sin(time)), abs(sin(time)), abs(sin(time))));
    

    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::translate(model3, glm::vec3(-5.0f, 0.0f, -5.0f));
    model3 = glm::rotate(model3, glm::radians(time*100), glm::vec3(1.0f, 0.0f, 0.0f));
    model3 = glm::rotate(model3, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model3 = glm::scale(model3, glm::vec3(abs(sin(time)), abs(sin(time)), abs(sin(time))));

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
