#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Exercise 2"
GLFWwindow *pWindow;

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
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.4854101966249539f, 0.352671151375504f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.1854101966249212f, 0.5706339097771075f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.18541019662503938f, 0.5706339097770691f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.4854101966250268f, 0.35267115137540356f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.6f, -1.2409386426612867E-13f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.48541019662488094f, -0.3526711513756043f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.18541019662480332f, -0.5706339097771458f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.18541019662515737f, -0.5706339097770308f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.48541019662509993f, -0.35267115137530286f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.6f, 2.487206355840774E-13f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.4854101966248075f, 0.35267115137570537f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.1854101966246843f, 0.5706339097771844f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.1854101966252764f, 0.570633909776992f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.48541019662517315f, 0.3526711513752021f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.6f, -3.7281449985020607E-13f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.4854101966247349f, -0.3526711513758053f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.18541019662456729f, -0.5706339097772225f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.18541019662539293f, -0.5706339097769542f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.48541019662524515f, -0.35267115137510296f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.6f, 4.953096429608745E-13f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
};

float circleBottom[] = {
    
};

float triangleStrip[] = {

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));

    // enable the layout locations so they can be used by the vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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

    return true;
}

// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // GLOBALS
    float time = glfwGetTime();

    // Specify circleTop matrix operations
    glUseProgram(circleTopShader);

    glEnable(GL_DEPTH_TEST); // enable OpenGL's hidden surface removal

    glm::mat4 circleMatrix;

    circleMatrix = glm::perspective(glm::radians(60.0f),
        (float) WINDOW_WIDTH / WINDOW_HEIGHT,
        0.1f,
        100.0f);

    glUniformMatrix4fv(glGetUniformLocation(circleTopShader, "matrix"),
        1, GL_FALSE, glm::value_ptr(circleMatrix));

    glBindVertexArray(circleTopVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circleTop) / (6 * sizeof(float)));


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
