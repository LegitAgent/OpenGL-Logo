#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Exercise 2"
GLFWwindow *pWindow;

// PIECE 1 
float piece1[] = {

};

// PIECE 2
float piece2[] = {

};

// PIECE 3
float piece3[] = {

};


// PIECE 4
float piece4[] = {

};

// PIECE 5
float piece5[] = {

};

// PIECE 6

float piece6[] = {

};

#define BLUE 0.0f, 0.0f, 1.0f
// piece 7
float piece7[] = {
    1.0f, 0.0f, 0.0f,  BLUE,  1.0f, 0.0f, // bottom right
    1.0f, 0.8f, 0.0f,  BLUE,  1.0f, 0.8f, // top right
    0.6f, 0.8f, 0.0f,  BLUE,  0.6f, 0.8f,  // top left
    0.55f, 0.7f, 0.0f, BLUE,  0.55f, 0.7f  // bottom left
};

#define RED 1.0f, 0.0f, 0.0f
// PIECE 8
float piece8[] = {
    1.0f, 0.8f, 0.0f, RED,  1.0f, 0.8f, // bottom right
    1.0f, 1.0f, 0.0f, RED,  1.0f, 1.0f, // top right
    0.6f, 1.0f, 0.0f, RED,  0.6f, 1.0f, // top left
    0.6f, 0.8f, 0.0f, RED,  0.6f, 0.8f  // bottom left
};

// PIECE 9

float piece9[] = {
    
};

GLuint RubyVao;
GLuint RubyVbo;
GLuint RubyShader;

GLuint SapphireVao;
GLuint SapphireVbo;
GLuint SapphireShader;

GLuint eyeVao;
GLuint eyeVbo;
GLuint eyeShader;

GLuint EmeraldVao;
GLuint EmeraldVbo;
GLuint EmeraldShader;

GLuint AmberVao;
GLuint AmberVbo;
GLuint AmberShader;

GLuint AmethystVao;
GLuint AmethystVbo;
GLuint AmethystShader;

GLuint TealVao;
GLuint TealVbo;
GLuint TealShader;

GLuint DarkCrimsonVao;
GLuint DarkCrimsonVbo;
GLuint DarkCrimsonShader;

GLuint GoldVao;
GLuint GoldVbo;
GLuint GoldShader;

GLuint CyanVao;
GLuint CyanVbo;
GLuint CyanShader;

GLuint texture;

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
    // setup kettle VOs
    if(!setupVO(
        RubyVao,
        RubyVbo,
        RubyShader,
        piece1,
        sizeof(piece1),
        "ruby.vs",
        "ruby.fs"
    )) {
        return false;
    }

    // setup hole VOs
    if(!setupVO(
        SapphireVao, 
        SapphireVbo, 
        SapphireShader, 
        piece2, 
        sizeof(piece2), 
        "sapphire.vs", 
        "sapphire.fs"
    )) {
        return false;
    }

    if(!setupVO(
        EmeraldVao,
        EmeraldVbo,
        EmeraldShader,
        piece3,
        sizeof(piece3),
        "emerald.vs",
        "emerald.fs"
    )) {
        return false;
    }

    if(!setupVO(
        AmberVao,
        AmberVbo,
        AmberShader,
        piece4,
        sizeof(piece4),
        "amber.vs",
        "amber.fs"
    )) {
        return false;
    }

    if(!setupVO(
        AmethystVao,
        AmethystVbo,
        AmethystShader,
        piece5,
        sizeof(piece5),
        "amethyst.vs",
        "amethyst.fs"
    )) {
        return false;
    }

    if(!setupVO(
        TealVao,
        TealVbo,
        TealShader,
        piece6,
        sizeof(piece6),
        "teal.vs",
        "teal.fs"
    )) {
        return false;
    }

    if(!setupVO(
        DarkCrimsonVao,
        DarkCrimsonVbo,
        DarkCrimsonShader,
        piece7,
        sizeof(piece7),
        "darkcrimson.vs",
        "darkcrimson.fs"
    )) {
        return false;
    }

    if(!setupVO(
        GoldVao,
        GoldVbo,
        GoldShader,
        piece8,
        sizeof(piece8),
        "gold.vs",
        "gold.fs"
    )) {
        return false;
    }

    if(!setupVO(
        CyanVao,
        CyanVbo,
        CyanShader,
        piece9,
        sizeof(piece9),
        "cyan.vs",
        "cyan.fs"
    )) {
        return false;
    }

    texture = gdevLoadTexture("OIP.jpg", GL_REPEAT, true, true);
    if (! texture) return false;
    
    return true;
}

// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // compute a value for the glow amount for this frame
    float time = glfwGetTime();
    float speed = 2.0f;

    // SHADOW SHADER
    glUseProgram(RubyShader);

    glUniform1f(glGetUniformLocation(RubyShader, "time"), time);
    glUniform1f(glGetUniformLocation(RubyShader, "speed"), speed);

    glBindVertexArray(RubyVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece1) / (8 * sizeof(float)));

    // KETTLE SHADER
    glUseProgram(SapphireShader);

    glUniform1f(glGetUniformLocation(SapphireShader, "time"), time);
    glUniform1f(glGetUniformLocation(SapphireShader, "speed"), speed);

    glBindVertexArray(SapphireVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece2) / (8 * sizeof(float)));

    // HOLE SHADER
    glUseProgram(EmeraldShader);

    glUniform1f(glGetUniformLocation(EmeraldShader, "time"), time);
    glUniform1f(glGetUniformLocation(EmeraldShader, "speed"), speed);

    glBindVertexArray(EmeraldVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece3) / (8 * sizeof(float)));

    // EYE SHADER
    glUseProgram(AmberShader);

    glUniform1f(glGetUniformLocation(AmberShader, "time"), time);
    glUniform1f(glGetUniformLocation(AmberShader, "speed"), speed);

    glBindVertexArray(AmberVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece4) / (8 * sizeof(float)));

    // LIGHTNING SHADER
    glUseProgram(AmethystShader);

    glUniform1f(glGetUniformLocation(AmethystShader, "time"), time);
    glUniform1f(glGetUniformLocation(AmethystShader, "speed"), speed);

    glBindVertexArray(AmethystVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece5) / (8 * sizeof(float)));

    // LIGHTNING SHADER
    glUseProgram(TealShader);

    glUniform1f(glGetUniformLocation(TealShader, "time"), time);
    glUniform1f(glGetUniformLocation(TealShader, "speed"), speed);

    glBindVertexArray(TealVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece6) / (8 * sizeof(float)));


    glUseProgram(DarkCrimsonShader);

    glUniform1f(glGetUniformLocation(DarkCrimsonShader, "time"), time);
    glUniform1f(glGetUniformLocation(DarkCrimsonShader, "speed"), speed);

    glBindVertexArray(DarkCrimsonVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece7) / (8 * sizeof(float)));

    glUseProgram(GoldShader);

    glUniform1f(glGetUniformLocation(GoldShader, "time"), time);
    glUniform1f(glGetUniformLocation(GoldShader, "speed"), speed);

    glBindVertexArray(GoldVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece8) / (8 * sizeof(float)));

    glUseProgram(CyanShader);

    glUniform1f(glGetUniformLocation(CyanShader, "time"), time);
    glUniform1f(glGetUniformLocation(CyanShader, "speed"), speed);

    glBindVertexArray(CyanVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece9) / (8 * sizeof(float)));    
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
