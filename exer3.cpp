#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  720
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

GLuint squareVAO;
GLuint squareVBO;
GLuint squareShader;

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
        squareVAO,
        squareVBO,
        squareShader,
        vertices,
        sizeof(vertices),
        "square.vs",
        "square.fs"
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

    // compute a value for the glow amount for this frame
    // float time = glfwGetTime();
    // float speed = 2.0f;

    // PURPLE PIECE
    glUseProgram(squareShader);

    glEnable(GL_DEPTH_TEST); // enable OpenGL's hidden surface removal

    glm::mat4 matrix;

    matrix = glm::perspective(glm::radians(60.0f),
        (float) WINDOW_WIDTH / WINDOW_HEIGHT,
        0.1f,
        100.0f);

    glUniformMatrix4fv(glGetUniformLocation(squareShader, "matrix"),
        1, GL_FALSE, glm::value_ptr(matrix));

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, main_texture);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, purple_texture);

    // glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureA"), 0);
    // glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureB"), 1);

    // glUniform1f(glGetUniformLocation(PurpleShader, "time"), time);
    // glUniform1f(glGetUniformLocation(PurpleShader, "speed"), speed);

    glBindVertexArray(squareVAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(float)));

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
