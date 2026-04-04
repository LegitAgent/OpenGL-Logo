#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Exercise 2"
GLFWwindow *pWindow;

// camera mechanics
// https://learnopengl.com/Getting-Started/Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float lastFrame = 0.0f;
float deltaTime = 0.0f;

float vertices[] =
{
    // position (x, y, z) color (r, g, b)
    -0.50f, -0.50f, -1.00f, 1.0f, 1.0f, 1.0f,
    0.50f, -0.50f, -1.00f, 1.0f, 1.0f, 1.0f,
    -0.50f, 0.50f, -1.00f, 1.0f, 1.0f, 1.0f,
    0.50f, 0.50f, -1.00f, 1.0f, 1.0f, 1.0f,
    -0.50f, 0.50f, -1.00f, 1.0f, 1.0f, 1.0f,
    0.50f, -0.50f, -1.00f, 1.0f, 1.0f, 1.0f
};

float circleTop[] =  {
0.0f, 0.0f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
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
1.0f, 8.343978557984588E-13f, -0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 8.343978557984588E-13f,
};

float circleBottom[] = {
0.0f, 0.0f, 0.3f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
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
1.0f, 8.343978557984588E-13f, 0.3f, 0.5f, 0.5f, 0.5f, 1.0f, 8.343978557984588E-13f,
};

GLuint squareVAO;
GLuint squareVBO;
GLuint squareShader;

GLuint circleTopVAO;
GLuint circleTopVBO;
GLuint circleTopShader;

GLuint circleBottomVAO;
GLuint circleBottomVBO;
GLuint circleBottomShader;

GLuint triangleStripVAO;
GLuint triangleStripVBO;
GLuint triangleStripShader;

// This function is to generate the triangle strip between two circles
// Useful for generating cylinders
void generateCylinderStrip(const float* topCircle, const float* bottomCircle,
                            int size, float* cylinderStrip) {
    int idx = 0;
    for (int i = 0; i < size; i += 8) {
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

// called by the main function to do initial setup, such as uploading vertex
// arrays, shader programs, etc.; returns true if successful, false otherwise
bool setup()
{  

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

    // if(!setupVO(
    //     triangleStripVAO,
    //     triangleStripVBO,
    //     triangleStripShader,
    //     triangleStrip,
    //     sizeof(triangleStrip),
    //     "circleTop.vs",
    //     "circleTop.fs"
    // )) {
    //     return false;
    // }

    return true;
}

// called by the main function to do rendering per frame
void render()
{
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // clear the whole frame
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // GLOBALS
    float time = glfwGetTime();

    // CIRCLE - TOP
    glUseProgram(circleTopShader);

    glEnable(GL_DEPTH_TEST); // enable OpenGL's hidden surface removal

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(time*100), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 circleTopMatrix = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(circleTopShader, "matrix"),
        1, GL_FALSE, glm::value_ptr(circleTopMatrix));

    glBindVertexArray(circleTopVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleTop) / (6 * sizeof(float)));

    // CIRCLE BOTTOM
    glUseProgram(circleBottomShader);

    glEnable(GL_DEPTH_TEST); // enable OpenGL's hidden surface removal

    // glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    
    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(time*100), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 circleBottomMatrix = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(circleBottomShader, "matrix"), 1, GL_FALSE, glm::value_ptr(circleBottomMatrix));

    glBindVertexArray(circleBottomVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleBottom) / (6 * sizeof(float)));

    // CIRCLE BOTTOM
    glUseProgram(triangleStripShader);

    glEnable(GL_DEPTH_TEST); // enable OpenGL's hidden surface removal

    glm::mat4 triangleStripMatrix;

    triangleStripMatrix = glm::perspective(glm::radians(60.0f),
        (float) WINDOW_WIDTH / WINDOW_HEIGHT,
        0.1f,
        100.0f);
    
    triangleStripMatrix = glm::translate(triangleStripMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
    triangleStripMatrix = glm::rotate(triangleStripMatrix, glm::radians(time*100), glm::vec3(0.0f, 1.0f, 0.0f));
    triangleStripMatrix = glm::rotate(triangleStripMatrix, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(triangleStripShader, "matrix"),
        1, GL_FALSE, glm::value_ptr(triangleStripMatrix));

    // glBindVertexArray(triangleStripVAO);
    // glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(triangleStrip) / (6 * sizeof(float)));

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, main_texture);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, purple_texture);

    // glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureA"), 0);
    // glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureB"), 1);

    // glUniform1f(glGetUniformLocation(PurpleShader, "time"), time);
    // glUniform1f(glGetUniformLocation(PurpleShader, "speed"), speed);

}

/*****************************************************************************/

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

    // set up callback functions to handle window system events
    glfwSetKeyCallback(pWindow, handleKeys);
    glfwSetFramebufferSizeCallback(pWindow, handleResize);

    // don't miss any momentary keypresses
    glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

    // initialize GLAD, which acts as a library loader for the current OS's native OpenGL library
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

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
