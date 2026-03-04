#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Exercise 2"
GLFWwindow *pWindow;

// PIECE 1 - top left piece
#define BLACK 0.3f, 0.3f, 0.3f
float piece_black[] = {
    0.2f, 1.0f, 0.0f, BLACK, 0.2f, 1.0f, // top right
    0.0f, 1.0f, 0.0f, BLACK, 0.0f, 1.0f, // top left
    0.0f, 0.5f, 0.0f, BLACK, 0.0f, 0.5f, // bottom left
    0.030000000000000006f, 0.5327000000000001f, 0.0f, BLACK, 0.030000000000000006f, 0.5327000000000001f,
    0.060000000000000026f, 0.5696000000000001f, 0.0f, BLACK, 0.060000000000000026f, 0.5696000000000001f,
    0.09f, 0.6089f, 0.0f, BLACK, 0.09f, 0.6089f,
    0.12000000000000001f, 0.6487999999999999f, 0.0f, BLACK, 0.12000000000000001f, 0.6487999999999999f,
    0.15000000000000002f, 0.6875f, 0.0f, BLACK, 0.15000000000000002f, 0.6875f,
    // converge point
    0.18000000000000002f, 0.7232000000000001f, 0.0f, BLACK, 0.18000000000000002f, 0.7232000000000001f,  
    0.20999999999999996f, 0.7541f, 0.0f, BLACK, 0.20999999999999996f, 0.7541f,
    0.24f, 0.7784000000000001f, 0.0f, BLACK, 0.24f, 0.7784000000000001f,
    0.26999999999999996f, 0.7943f, 0.0f, BLACK, 0.26999999999999996f, 0.7943f,
    0.29999999999999993f, 0.8f, 0.0f, BLACK, 0.29999999999999993f, 0.8f,
    0.3f, 0.8f, 0.0f, BLACK, 0.3f, 0.8f, // bottom right
};

// PIECE 2 - middle top
#define CYAN 0.0f, 1.0f, 1.0f
float piece_cyan[] = {
    0.6f, 0.8f, 0.0f,  CYAN,  0.6f, 0.8f,  // mid right 
    0.6f, 1.0f, 0.0f, CYAN,  0.6f, 1.0f, // top right
    0.5f, 1.0f, 0.0f, CYAN, 0.5f, 1.0f, // top left
    0.4957500000000001f, 0.9822500000000001f, 0.0f, CYAN, 0.4957500000000001f, 0.9822500000000001f,
    0.48400000000000015f, 0.9600000000000002f, 0.0f, CYAN, 0.48400000000000015f, 0.9600000000000002f,
    0.46624999999999994f, 0.93475f, 0.0f, CYAN, 0.46624999999999994f, 0.93475f,
    0.44399999999999995f, 0.908f, 0.0f, CYAN, 0.44399999999999995f, 0.908f,
    0.41874999999999996f, 0.88125f, 0.0f, CYAN, 0.41874999999999996f, 0.88125f,
    0.392f, 0.8560000000000001f, 0.0f, CYAN, 0.392f, 0.8560000000000001f,
    0.36524999999999996f, 0.83375f, 0.0f, CYAN, 0.36524999999999996f, 0.83375f,
    0.34f, 0.8160000000000001f, 0.0f, CYAN, 0.34f, 0.8160000000000001f,
    0.31775f, 0.80425f, 0.0f, CYAN, 0.31775f, 0.80425f,

    0.3f, 0.8f, 0.0f, CYAN, 0.3f, 0.8f, // mid left
    0.29999999999999993f, 0.8f, 0.0f, CYAN, 0.29999999999999993f, 0.8f,
    0.26999999999999996f, 0.7943f, 0.0f, CYAN, 0.26999999999999996f, 0.7943f,
    0.24f, 0.7784000000000001f, 0.0f, CYAN, 0.24f, 0.7784000000000001f,
    0.20999999999999996f, 0.7541f, 0.0f, CYAN, 0.20999999999999996f, 0.7541f,
    0.18000000000000002f, 0.7232000000000001f, 0.0f, CYAN, 0.18000000000000002f, 0.7232000000000001f,  // bottom left
    0.4f, 0.5f, 0.0f,  CYAN, 0.40f, 0.5f, // peak bottom
    0.55f, 0.7f, 0.0f, CYAN,  0.55f, 0.7f, // bottom right
};

// PIECE 3 - triangle at top left
#define GREEN 0.0f, 1.0f, 0.0f
float piece_green[] = {
    0.2f, 1.0f, 0.0f, GREEN, 0.2f, 1.0f, // top left
    0.3f, 0.8f, 0.0f, GREEN, 0.3f, 0.8f, // bottom
    0.31775000869035724f, 0.8042500086903572f, 0.0f, GREEN, 0.31775000869035724f, 0.8042500086903572f,
    0.34000000610351566f, 0.8160000061035159f, 0.0f, GREEN, 0.34000000610351566f, 0.8160000061035159f,
    0.36525000408887864f, 0.8337500040888786f, 0.0f, GREEN, 0.36525000408887864f, 0.8337500040888786f,
    0.3920000025749206f, 0.8560000025749206f, 0.0f, GREEN, 0.3920000025749206f, 0.8560000025749206f,
    0.4187500014901161f, 0.8812500014901161f, 0.0f, GREEN, 0.4187500014901161f, 0.8812500014901161f,
    0.44400000076293944f, 0.9080000007629395f, 0.0f, GREEN, 0.44400000076293944f, 0.9080000007629395f,
    0.46625000032186503f, 0.934750000321865f, 0.0f, GREEN, 0.46625000032186503f, 0.934750000321865f,
    0.4840000000953674f, 0.9600000000953675f, 0.0f, GREEN, 0.4840000000953674f, 0.9600000000953675f,
    0.49575000001192093f, 0.9822500000119209f, 0.0f, GREEN, 0.49575000001192093f, 0.9822500000119209f,
    0.5f, 1.0f, 0.0f, GREEN, 0.5f, 1.0f, // top right

};


// PIECE 4
#define ORANGE 1.0f, 0.5f, 0.0f
float piece_orange[] = {
    0.0f, 0.3f, 0.0f, ORANGE, 0.0f, 0.3f, // bottom left
    0.25f, 0.27f, 0.0f, ORANGE, 0.25, 0.27, // bottom right

    0.2973549999999999f, 0.27643999999999996f,0.0f, ORANGE, 0.2973549999999999f, 0.27643999999999996f,
    0.32392f, 0.33975999999999995f,0.0f, ORANGE, 0.32392f, 0.33975999999999995f,
    0.357865f, 0.4147199999999999f,0.0f, ORANGE, 0.357865f, 0.4147199999999999f,
    0.39999999999999997f, 0.4999999999999999f,0.0f, ORANGE, 0.39999999999999997f, 0.4999999999999999f,// curve

    0.4f, 0.5f, 0.0f,  ORANGE, 0.40f, 0.5f, // top right
    0.18000000000000002f, 0.7232000000000001f, 0.0f, ORANGE, 0.18000000000000002f, 0.7232000000000001f,  
    0.15000000000000002f, 0.6875f, 0.0f, ORANGE, 0.15000000000000002f, 0.6875f,
    0.12000000000000001f, 0.6487999999999999f, 0.0f, ORANGE, 0.12000000000000001f, 0.6487999999999999f,
    0.09f, 0.6089f, 0.0f, ORANGE, 0.09f, 0.6089f,
    0.060000000000000026f, 0.5696000000000001f, 0.0f, ORANGE, 0.060000000000000026f, 0.5696000000000001f,
    0.030000000000000006f, 0.5327000000000001f, 0.0f, ORANGE, 0.030000000000000006f, 0.5327000000000001f,
    0.0f, 0.5f, 0.0f, ORANGE, 0.0f, 0.5f // top left
};

// PIECE 5
#define WHITE 0.8f, 1.0f, 1.0f
float piece_white[] = {
    0.4f, 0.5f, 0.0f,  WHITE, 0.40f, 0.5f, // bottom left
    0.63f, 0.6f, 0.0f, WHITE, 0.63f, 0.6f, // bottom right
    0.55f, 0.7f, 0.0f, WHITE,  0.55f, 0.7f  // top part

};

// PIECE 6
#define YELLOW 1.0f, 1.0f, 0.0f
float piece_yellow[] = {
    0.23f, 0.0f, 0.0f, YELLOW, 0.23f, 0.0f, // bottom left
    1.0f, 0.0f, 0.0f,  YELLOW,  1.0f, 0.0f, // bottom right
    0.63f, 0.6f, 0.0f, YELLOW, 0.63f, 0.6f, // top right
    0.4f, 0.5f, 0.0f,  YELLOW, 0.40f, 0.5f, // top left

    0.23692000000000005f, 0.07556000000000002f, 0.0f, YELLOW, 0.23692000000000005f, 0.07556000000000002f, 
    0.24576000000000006f, 0.14128000000000004f, 0.0f, YELLOW, 0.24576000000000006f, 0.14128000000000004f,
    0.25664f, 0.19872f, 0.0f, YELLOW, 0.25664f, 0.19872f,
    0.26968f, 0.24943999999999997f, 0.0f, YELLOW, 0.26968f, 0.24943999999999997f,
    0.285f, 0.295f, 0.0f, YELLOW, 0.285f, 0.295f,
    0.30272000000000004f, 0.33696f, 0.0f, YELLOW, 0.30272000000000004f, 0.33696f,
    0.3229599999999999f, 0.37687999999999994f, 0.0f, YELLOW, 0.3229599999999999f, 0.37687999999999994f,
    0.34584000000000004f, 0.41632f, 0.0f, YELLOW, 0.34584000000000004f, 0.41632f,
    0.37148f, 0.45683999999999997f, 0.0f, YELLOW, 0.37148f, 0.45683999999999997f,
    0.4f, 0.49999999999999994f, 0.0f, YELLOW, 0.4f, 0.49999999999999994f, // curve
};


// PIECE 7 - big piece at the top right
#define BLUE 0.0f, 0.0f, 1.0f
float piece_blue[] = {
    1.0f, 0.0f, 0.0f,  BLUE,  1.0f, 0.0f, // bottom right
    1.0f, 0.6f, 0.0f,  BLUE,  1.0f, 0.6f, // top right
    1.0f, 0.6f, 0.0f, BLUE, 1.0f, 0.6f,
    0.9429000000000002f, 0.6056f, 0.0f, BLUE, 0.9429000000000002f, 0.6056f,
    0.8912000000000003f, 0.6208f, 0.0f, BLUE, 0.8912000000000003f, 0.6208f,
    0.8442999999999999f, 0.6432f, 0.0f, BLUE, 0.8442999999999999f, 0.6432f,
    0.8016f, 0.6704f, 0.0f, BLUE, 0.8016f, 0.6704f,
    0.7625f, 0.7000000000000001f, 0.0f, BLUE, 0.7625f, 0.7000000000000001f,
    0.7263999999999999f, 0.7296f, 0.0f, BLUE, 0.7263999999999999f, 0.7296f,
    0.6926999999999999f, 0.7567999999999999f, 0.0f, BLUE, 0.6926999999999999f, 0.7567999999999999f,
    0.6608f, 0.7792000000000001f, 0.0f, BLUE, 0.6608f, 0.7792000000000001f,
    0.6301f, 0.7944f, 0.0f, BLUE, 0.6301f, 0.7944f,
    0.6f, 0.8f, 0.0f, BLUE, 0.6f, 0.8f,
    0.6f, 0.8f, 0.0f,  BLUE,  0.6f, 0.8f,  // top left
    0.55f, 0.7f, 0.0f, BLUE,  0.55f, 0.7f  // bottom left
};


// PIECE 8 - rectangle at top right
#define RED 1.0f, 0.0f, 0.0f
float piece_red[] = {
    1.0f, 0.6f, 0.0f, RED,  1.0f, 0.6f, // bottom right
    1.0f, 1.0f, 0.0f, RED,  1.0f, 1.0f, // top right
    0.6f, 1.0f, 0.0f, RED,  0.6f, 1.0f, // top left
    0.6f, 0.8f, 0.0f, RED,  0.6f, 0.8f,  // bottom left
    0.6f, 0.8f, 0.0f, RED, 0.6f, 0.8f,
    0.6301f, 0.7944000000000001f, 0.0f, RED, 0.6301f, 0.7944000000000001f,
    0.6608f, 0.7792000000000003f, 0.0f, RED, 0.6608f, 0.7792000000000003f,
    0.6927f, 0.7568f, 0.0f, RED, 0.6927f, 0.7568f,
    0.7263999999999999f, 0.7295999999999999f, 0.0f, RED, 0.7263999999999999f, 0.7295999999999999f,
    0.7625f, 0.7f, 0.0f, RED, 0.7625f, 0.7f,
    0.8016000000000001f, 0.6704000000000001f, 0.0f, RED, 0.8016000000000001f, 0.6704000000000001f,
    0.8443f, 0.6432f, 0.0f, RED, 0.8443f, 0.6432f,
    0.8912f, 0.6208f, 0.0f, RED, 0.8912f, 0.6208f,
    0.9429f, 0.6055999999999999f, 0.0f, RED, 0.9429f, 0.6055999999999999f,
    0.9999999999999999f, 0.6f, 0.0f, RED, 0.9999999999999999f, 0.6f,

};

// PIECE 9
#define PURPLE 1.0f, 0.0f, 1.0f
float piece_purple[] = {
    0.0f, 0.0f, 0.0f, PURPLE, 0.0f, 0.0f, // bottom left
    0.23f, 0.0f, 0.0f, PURPLE, 0.23f, 0.0f, // bottom right

    0.23288200000000006f, 0.017820000000000003f,0.0f, PURPLE, 0.23288200000000006f, 0.017820000000000003f,
    0.23565600000000006f, 0.04056000000000002f,0.0f, PURPLE, 0.23565600000000006f, 0.04056000000000002f,
    0.23851400000000003f, 0.06714f,0.0f, PURPLE, 0.23851400000000003f, 0.06714f,
    0.241648f, 0.09648f,0.0f, PURPLE, 0.241648f, 0.09648f,
    0.24525000000000002f, 0.1275f,0.0f, PURPLE, 0.24525000000000002f, 0.1275f,
    0.249512f, 0.15912000000000004f,0.0f, PURPLE, 0.249512f, 0.15912000000000004f,
    0.254626f, 0.19025999999999998f,0.0f, PURPLE, 0.254626f, 0.19025999999999998f,
    0.260784f, 0.21983999999999998f,0.0f, PURPLE, 0.260784f, 0.21983999999999998f,
    0.268178f, 0.24678f,0.0f, PURPLE, 0.268178f, 0.24678f,
    0.27699999999999997f, 0.26999999999999996f,0.0f, PURPLE, 0.27699999999999997f, 0.26999999999999996f, // curve

    0.25f, 0.27f, 0.0f, PURPLE, 0.25, 0.27, // top right
    0.0f, 0.3f, 0.0f, PURPLE, 0.0f, 0.3f, // top left

};

GLuint BlackVao;
GLuint BlackVbo;
GLuint BlackShader;

GLuint CyanVao;
GLuint CyanVbo;
GLuint CyanShader;

GLuint GreenVao;
GLuint GreenVbo;
GLuint GreenShader;

GLuint OrangeVao;
GLuint OrangeVbo;
GLuint OrangeShader;

GLuint WhiteVao;
GLuint WhiteVbo;
GLuint WhiteShader;

GLuint YellowVao;
GLuint YellowVbo;
GLuint YellowShader;

GLuint BlueVao;
GLuint BlueVbo;
GLuint BlueShader;

GLuint RedVao;
GLuint RedVbo;
GLuint RedShader;

GLuint PurpleVao;
GLuint PurpleVbo;
GLuint PurpleShader;

GLuint main_texture;
GLuint texture2;

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
        BlackVao,
        BlackVbo,
        BlackShader,
        piece_black,
        sizeof(piece_black),
        "black.vs",
        "black.fs"
    )) {
        return false;
    }

    if(!setupVO(
        CyanVao,
        CyanVbo,
        CyanShader,
        piece_cyan,
        sizeof(piece_cyan),
        "cyan.vs",
        "cyan.fs"
    )) {
        return false;
    }

    if(!setupVO(
        GreenVao, 
        GreenVbo, 
        GreenShader, 
        piece_green, 
        sizeof(piece_green), 
        "green.vs", 
        "green.fs"
    )) {
        return false;
    }

    if(!setupVO(
        OrangeVao,
        OrangeVbo,
        OrangeShader,
        piece_orange,
        sizeof(piece_orange),
        "orange.vs",
        "orange.fs"
    )) {
        return false;
    }

    if(!setupVO(
        WhiteVao,
        WhiteVbo,
        WhiteShader,
        piece_white,
        sizeof(piece_white),
        "white.vs",
        "white.fs"
    )) {
        return false;
    }

    if(!setupVO(
        YellowVao,
        YellowVbo,
        YellowShader,
        piece_yellow,
        sizeof(piece_yellow),
        "yellow.vs",
        "yellow.fs"
    )) {
        return false;
    }

    if(!setupVO(
        BlueVao,
        BlueVbo,
        BlueShader,
        piece_blue,
        sizeof(piece_blue),
        "blue.vs",
        "blue.fs"
    )) {
        return false;
    }

    if(!setupVO(
        RedVao,
        RedVbo,
        RedShader,
        piece_red,
        sizeof(piece_red),
        "red.vs",
        "red.fs"
    )) {
        return false;
    }

    if(!setupVO(
        PurpleVao,
        PurpleVbo,
        PurpleShader,
        piece_purple,
        sizeof(piece_purple),
        "purple.vs",
        "purple.fs"
    )) {
        return false;
    }

    main_texture = gdevLoadTexture("base.png", GL_REPEAT, true, true);
    if (! main_texture) return false;

    texture2 = gdevLoadTexture("sigma.jpg", GL_REPEAT, true, true);
    if (! texture2) return false;
    
    return true;
}

// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // compute a value for the glow amount for this frame
    float time = glfwGetTime()/2;
    float speed = 2.0f;

    // BLACK PIECE
    glUseProgram(BlackShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(BlackShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(BlackShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(BlackShader, "time"), time);
    glUniform1f(glGetUniformLocation(BlackShader, "speed"), speed);

    glBindVertexArray(BlackVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_black) / (8 * sizeof(float)));

    //CYAN PIECE
    glUseProgram(CyanShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(CyanShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(CyanShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(CyanShader, "time"), time);
    glUniform1f(glGetUniformLocation(CyanShader, "speed"), speed);

    glBindVertexArray(CyanVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_cyan) / (8 * sizeof(float)));    

    // GREEN PIECE
    glUseProgram(GreenShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(GreenShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(GreenShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(GreenShader, "time"), time);
    glUniform1f(glGetUniformLocation(GreenShader, "speed"), speed);

    glBindVertexArray(GreenVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_green) / (8 * sizeof(float)));

    // ORANGE PIECE
    glUseProgram(OrangeShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(OrangeShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(OrangeShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(OrangeShader, "time"), time);
    glUniform1f(glGetUniformLocation(OrangeShader, "speed"), speed);

    glBindVertexArray(OrangeVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_orange) / (8 * sizeof(float)));

    // WHITE PIECE
    glUseProgram(WhiteShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(WhiteShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(WhiteShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(WhiteShader, "time"), time);
    glUniform1f(glGetUniformLocation(WhiteShader, "speed"), speed);

    glBindVertexArray(WhiteVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_white) / (8 * sizeof(float)));

    // YELLOW PIECE
    glUseProgram(YellowShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(YellowShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(YellowShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(YellowShader, "time"), time);
    glUniform1f(glGetUniformLocation(YellowShader, "speed"), speed);

    glBindVertexArray(YellowVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_yellow) / (8 * sizeof(float)));

    // BLUE PIECE
    glUseProgram(BlueShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(BlueShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(BlueShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(BlueShader, "time"), time);
    glUniform1f(glGetUniformLocation(BlueShader, "speed"), speed);

    glBindVertexArray(BlueVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_blue) / (8 * sizeof(float)));

    // RED PIECE
    glUseProgram(RedShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(RedShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(RedShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(RedShader, "time"), time);
    glUniform1f(glGetUniformLocation(RedShader, "speed"), speed);

    glBindVertexArray(RedVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_red) / (8 * sizeof(float)));

    // PURPLE PIECE
    glUseProgram(PurpleShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, main_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureA"), 0);
    glUniform1i(glGetUniformLocation(PurpleShader, "shaderTextureB"), 1);

    glUniform1f(glGetUniformLocation(PurpleShader, "time"), time);
    glUniform1f(glGetUniformLocation(PurpleShader, "speed"), speed);

    glBindVertexArray(PurpleVao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(piece_purple) / (8 * sizeof(float)));

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
