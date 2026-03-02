#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Thing"
GLFWwindow *pWindow;

// =================== PIECE 1 – Ruby (top-left, 4-sided) ===========
// Corners: top-left, top-right, bottom-right, bottom-left  (quad)
float piece1[] = {
    //  X       Y      Z     R     G     B      U      V
    -1.0f,  1.0f,  0.0f,  0.75f,0.10f,0.15f,  0.0f,  1.0f,   // TL
    -0.45f, 1.0f,  0.0f,  0.75f,0.10f,0.15f,  0.275f,1.0f,   // TR
    -0.30f, 0.40f, 0.0f,  0.75f,0.10f,0.15f,  0.35f, 0.70f,  // BR
    -1.0f,  0.40f, 0.0f,  0.75f,0.10f,0.15f,  0.0f,  0.70f,  // BL
};

// =================== PIECE 2 – Sapphire (6-sided) =================   
// Upper-left column, hexagonal shape
float piece2[] = {
    //  X       Y      Z     R     G     B      U      V
    -1.0f,  0.40f, 0.0f,  0.10f,0.20f,0.75f,  0.0f,  0.70f,
    -0.30f, 0.40f, 0.0f,  0.10f,0.20f,0.75f,  0.35f, 0.70f,
    -0.10f, 0.10f, 0.0f,  0.10f,0.20f,0.75f,  0.45f, 0.55f,
    -0.10f,-0.30f, 0.0f,  0.10f,0.20f,0.75f,  0.45f, 0.35f,
    -0.70f,-0.30f, 0.0f,  0.10f,0.20f,0.75f,  0.15f, 0.35f,
    -1.0f,  0.0f,  0.0f,  0.10f,0.20f,0.75f,  0.0f,  0.50f,
};

// =================== PIECE 3 – Emerald (triangle, top-centre) =====
float piece3[] = {
    //  X       Y      Z     R     G     B      U      V
    -0.45f, 1.0f,  0.0f,  0.10f,0.60f,0.25f,  0.275f,1.0f,
     0.50f, 1.0f,  0.0f,  0.10f,0.60f,0.25f,  0.75f, 1.0f,
    -0.10f, 0.10f, 0.0f,  0.10f,0.60f,0.25f,  0.45f, 0.55f,
};

// =================== PIECE 4 – Amber (pentagon, curved bottom) ====
// The bottom edge (from BL to BR) is a downward Bézier arc.
// Arc: from (-1,-0.30) curving down to (-0.10,-0.30) via (-0.55,-0.90)
// Pre-tessellated with 10 segments → 11 points on the arc.
// TRIANGLE_FAN centre = centroid of the piece ~ (-0.55, -0.30)
// We build the fan: centre, then outline CCW.
//
// Straight outline vertices (top part):
//   TL (-1.0, 0.0)  →  (-1.0,-0.30)  →  [curve]  →  (-0.10,-0.30)  →  (-0.10, 0.10)
//
// For a TRIANGLE_FAN the first vertex is the hub.
#define AMBER_R 0.80f
#define AMBER_G 0.45f
#define AMBER_B 0.05f

// Arc from P0=(-1.0,-0.30) to P2=(-0.10,-0.30), control P1=(-0.55,-0.90)
// Quadratic Bézier, 10 steps:
// B(t) = (1-t)^2*P0 + 2(1-t)t*P1 + t^2*P2
// t=0.0: (-1.000, -0.300)
// t=0.1: (-0.921, -0.408)
// t=0.2: (-0.844, -0.492)
// t=0.3: (-0.769, -0.552)
// t=0.4: (-0.696, -0.588)
// t=0.5: (-0.625, -0.600)
// t=0.6: (-0.556, -0.588)
// t=0.7: (-0.489, -0.552)
// t=0.8: (-0.424, -0.492)
// t=0.9: (-0.361, -0.408)
// t=1.0: (-0.100, -0.300)
float piece4[] = {
    // Hub (centroid)
    -0.55f,-0.20f, 0.0f,  AMBER_R,AMBER_G,AMBER_B,  0.225f,0.40f,
    // Outline – top-left corner going clockwise
    -1.0f,  0.0f,  0.0f,  AMBER_R,AMBER_G,AMBER_B,  0.0f,  0.50f,
    -1.0f, -0.30f, 0.0f,  AMBER_R,AMBER_G,AMBER_B,  0.0f,  0.35f,
    // Bézier arc (bottom)
    -0.921f,-0.408f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.040f,0.296f,
    -0.844f,-0.492f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.078f,0.254f,
    -0.769f,-0.552f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.116f,0.224f,
    -0.696f,-0.588f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.152f,0.206f,
    -0.625f,-0.600f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.188f,0.200f,
    -0.556f,-0.588f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.222f,0.206f,
    -0.489f,-0.552f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.256f,0.224f,
    -0.424f,-0.492f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.288f,0.254f,
    -0.361f,-0.408f,0.0f, AMBER_R,AMBER_G,AMBER_B,  0.320f,0.296f,
    -0.10f, -0.30f, 0.0f, AMBER_R,AMBER_G,AMBER_B,  0.45f, 0.35f,
    // back up the right side
    -0.10f,  0.10f, 0.0f, AMBER_R,AMBER_G,AMBER_B,  0.45f, 0.55f,
    // close to hub (TRIANGLE_FAN closes automatically to first outline vertex)
    -1.0f,  0.0f,  0.0f,  AMBER_R,AMBER_G,AMBER_B,  0.0f,  0.50f,
};

// =================== PIECE 5 – Amethyst (triangle, centre-right) ==
float piece5[] = {
    //  X       Y      Z     R     G     B      U      V
    -0.10f, 0.10f, 0.0f,  0.55f,0.20f,0.70f,  0.45f, 0.55f,
     0.50f, 1.0f,  0.0f,  0.55f,0.20f,0.70f,  0.75f, 1.0f,
     1.0f,  0.10f, 0.0f,  0.55f,0.20f,0.70f,  1.0f,  0.55f,
};

// =================== PIECE 6 – Teal (large centre, LEFT side curved)
// Left boundary is a cubic Bézier from top-left to bottom-left.
// Straight edges: top (-1,1)→(0.5,1), right (0.5,1)→(1.0,-1),
//                 bottom (1.0,-1)→(-1,-1)
// Left (curved): (-1,-1) → (-1,1) via control pts (-0.30,-0.5),(-0.30,0.5)
// Cubic Bézier, 12 steps:
// P0=(-1,-1), P1=(-0.30,-0.5), P2=(-0.30,0.5), P3=(-1,1)
// Pre-computed (t from 0→1 gives bottom→top, we list top→bottom for CCW):
#define TEAL_R 0.05f
#define TEAL_G 0.55f
#define TEAL_B 0.60f
float piece6[] = {
    // Hub
     0.10f, 0.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  0.55f,0.50f,
    // Top-left (start of straight top edge)
    -1.0f,  1.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  0.0f, 1.0f,
     0.50f, 1.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  0.75f,1.0f,
     1.0f,  0.10f, 0.0f,  TEAL_R,TEAL_G,TEAL_B,  1.0f, 0.55f,
     1.0f, -1.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  1.0f, 0.0f,
    // Bottom edge
    -1.0f, -1.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  0.0f, 0.0f,
    // Curved left side (cubic Bézier bottom→top, 10 steps)
    // B(t)=(1-t)^3*P0+3(1-t)^2*t*P1+3(1-t)*t^2*P2+t^3*P3
    // t=0.1: (-0.938,-0.897)
    -0.938f,-0.897f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.031f,0.052f,
    // t=0.2: (-0.856,-0.776)
    -0.856f,-0.776f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.072f,0.112f,
    // t=0.3: (-0.757,-0.637)
    -0.757f,-0.637f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.122f,0.182f,
    // t=0.4: (-0.645,-0.488)
    -0.645f,-0.488f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.178f,0.256f,
    // t=0.5: (-0.525,-0.250)  [midpoint, slight inward bulge]
    -0.525f,-0.250f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.238f,0.375f,
    // t=0.6: (-0.432, 0.008)
    -0.432f, 0.008f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.284f,0.504f,
    // t=0.7: (-0.370, 0.237)
    -0.370f, 0.237f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.315f,0.619f,
    // t=0.8: (-0.352, 0.424)
    -0.352f, 0.424f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.324f,0.712f,
    // t=0.9: (-0.389, 0.657)
    -0.389f, 0.657f,0.0f, TEAL_R,TEAL_G,TEAL_B,  0.306f,0.829f,
    // t=1.0: top-left = close
    -1.0f,  1.0f,  0.0f,  TEAL_R,TEAL_G,TEAL_B,  0.0f, 1.0f,
};

// =================== PIECE 7 – Dark Crimson (rectangle, bottom-right lower)
float piece7[] = {
    //  X       Y      Z     R     G     B      U      V
    -0.10f,-0.30f, 0.0f,  0.50f,0.05f,0.10f,  0.45f,0.35f,
     1.0f, -0.30f, 0.0f,  0.50f,0.05f,0.10f,  1.0f, 0.35f,
     1.0f, -1.0f,  0.0f,  0.50f,0.05f,0.10f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f,  0.50f,0.05f,0.10f,  0.0f, 0.0f,
    -1.0f, -0.30f, 0.0f,  0.50f,0.05f,0.10f,  0.0f, 0.35f,
    -0.10f,-0.30f, 0.0f,  0.50f,0.05f,0.10f,  0.45f,0.35f, // close fan
};

// =================== PIECE 8 – Gold (right rectangle) =============
float piece8[] = {
    //  X       Y      Z     R     G     B      U      V
     0.50f, 1.0f,  0.0f,  0.90f,0.75f,0.15f,  0.75f,1.0f,
     1.0f,  1.0f,  0.0f,  0.90f,0.75f,0.15f,  1.0f, 1.0f,
     1.0f, -0.30f, 0.0f,  0.90f,0.75f,0.15f,  1.0f, 0.35f,
    -0.10f,-0.30f, 0.0f,  0.90f,0.75f,0.15f,  0.45f,0.35f,
     1.0f,  0.10f, 0.0f,  0.90f,0.75f,0.15f,  1.0f, 0.55f, // interior notch vertex
};

// =================== PIECE 9 – Cyan (tilted quad, curved right side)
// A tilted quadrilateral where the RIGHT edge bulges outward (convex Bézier).
// Straight: TL(-0.10,0.10) → TR(-0.10,1.0... wait, piece 9 is small centre-left piece.
// From image: piece 9 looks like a small square/quad in the centre-left area,
// slightly rotated, with the right side curving outward.
// Approximate corners: TL(-0.55,0.40) TR(-0.10,0.65) BR(-0.10,0.10) BL(-0.55,0.10)
// Right curved edge from TR(-0.10,0.65) → BR(-0.10,0.10) bulging right to (0.15,0.38)
// Quadratic Bézier, 8 steps:
#define CYAN_R 0.10f
#define CYAN_G 0.75f
#define CYAN_B 0.80f
float piece9[] = {
    // Hub (centre)
    -0.325f,0.375f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.338f,0.688f,
    // TL
    -0.55f, 0.65f, 0.0f, CYAN_R,CYAN_G,CYAN_B,  0.225f,0.825f,
    // TR
    -0.10f, 0.65f, 0.0f, CYAN_R,CYAN_G,CYAN_B,  0.45f, 0.825f,
    // Curved right edge TR→BR (bulge to x=+0.15)
    // t=0.125: (-0.076, 0.593)
    -0.076f,0.593f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.462f,0.797f,
    // t=0.25: (-0.009, 0.531)
    -0.009f,0.531f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.496f,0.766f,
    // t=0.375: (0.046, 0.475)
     0.046f,0.475f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.523f,0.738f,
    // t=0.5: (0.075, 0.375)   peak bulge
     0.075f,0.375f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.538f,0.688f,
    // t=0.625: (0.046, 0.275)
     0.046f,0.275f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.523f,0.638f,
    // t=0.75: (-0.009, 0.219)
    -0.009f,0.219f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.496f,0.610f,
    // t=0.875: (-0.076, 0.157)
    -0.076f,0.157f,0.0f, CYAN_R,CYAN_G,CYAN_B,  0.462f,0.579f,
    // BR
    -0.10f, 0.10f, 0.0f, CYAN_R,CYAN_G,CYAN_B,  0.45f, 0.55f,
    // BL
    -0.55f, 0.10f, 0.0f, CYAN_R,CYAN_G,CYAN_B,  0.225f,0.55f,
    // close fan back to TL
    -0.55f, 0.65f, 0.0f, CYAN_R,CYAN_G,CYAN_B,  0.225f,0.825f,
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
