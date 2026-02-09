/******************************************************************************
 * This demo draws a somewhat familiar geometric object composed of three
 * triangles.
 *
 * The main differences between this demo and the previous demo are:
 * - Each vertex now defines two subcomponents: position and color.
 * - A uniform variable is introduced to the shader program, which is used to
 *   accomplish a glowing effect.
 *
 * Happy hacking! - eric
 *****************************************************************************/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

// change this to your desired window attributes
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 1280
#define WINDOW_TITLE  "Hello Trifxxxe"
GLFWwindow *pWindow;

// define a vertex array to hold our vertices

float vertices[] =
{
    // position (x, y, z)    color (r, g, b)
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4960573506572384f, 0.06266661678215622f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4960573506572384f, 0.06266661678215622f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4842915805643135f, 0.1243449435824354f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4842915805643135f, 0.1243449435824354f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4648882429441211f, 0.18406227634235053f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4648882429441211f, 0.18406227634235053f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4381533400219238f, 0.24087683705087215f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4381533400219238f, 0.24087683705087215f, 0.0f, 1.0f, 1.0f, 1.0f,
0.40450849718746157f, 0.29389262614625333f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.40450849718746157f, 0.29389262614625333f, 0.0f, 1.0f, 1.0f, 1.0f,
0.3644843137106888f, 0.34227355296436246f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.3644843137106888f, 0.34227355296436246f, 0.0f, 1.0f, 1.0f, 1.0f,
0.31871199487432256f, 0.38525662138791306f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.31871199487432256f, 0.38525662138791306f, 0.0f, 1.0f, 1.0f, 1.0f,
0.26791339748947035f, 0.4221639627510253f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.26791339748947035f, 0.4221639627510253f, 0.0f, 1.0f, 1.0f, 1.0f,
0.21288964578250266f, 0.4524135262330256f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.21288964578250266f, 0.4524135262330256f, 0.0f, 1.0f, 1.0f, 1.0f,
0.15450849718743445f, 0.47552825814758953f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.15450849718743445f, 0.47552825814758953f, 0.0f, 1.0f, 1.0f, 1.0f,
0.09369065729281777f, 0.49114362536435285f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.09369065729281777f, 0.49114362536435285f, 0.0f, 1.0f, 1.0f, 1.0f,
0.031395259764607344f, 0.4990133642141389f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.031395259764607344f, 0.4990133642141389f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.03139525976471011f, 0.4990133642141324f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.03139525976471011f, 0.4990133642141324f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.09369065729291891f, 0.49114362536433354f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.09369065729291891f, 0.49114362536433354f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.15450849718753237f, 0.4755282581475577f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.15450849718753237f, 0.4755282581475577f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.21288964578259584f, 0.45241352623298176f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.21288964578259584f, 0.45241352623298176f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.2679133974895573f, 0.4221639627509701f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.2679133974895573f, 0.4221639627509701f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3187119948744018f, 0.3852566213878475f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3187119948744018f, 0.3852566213878475f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3644843137107592f, 0.34227355296428746f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3644843137107592f, 0.34227355296428746f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.40450849718752196f, 0.2938926261461701f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.40450849718752196f, 0.2938926261461701f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.4381533400219733f, 0.2408768370507821f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.4381533400219733f, 0.2408768370507821f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.4648882429441589f, 0.18406227634225505f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.4648882429441589f, 0.18406227634225505f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.484291580564339f, 0.124344943582336f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.484291580564339f, 0.124344943582336f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.49605735065725126f, 0.06266661678205446f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.49605735065725126f, 0.06266661678205446f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, -1.025233751354071E-13f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, -1.025233751354071E-13f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.49605735065722556f, -0.06266661678225789f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.49605735065722556f, -0.06266661678225789f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.48429158056428806f, -0.1243449435825346f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.48429158056428806f, -0.1243449435825346f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.46488824294408343f, -0.18406227634244568f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.46488824294408343f, -0.18406227634244568f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.43815334002187456f, -0.2408768370509618f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.43815334002187456f, -0.2408768370509618f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.40450849718740145f, -0.29389262614633604f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.40450849718740145f, -0.29389262614633604f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3644843137106188f, -0.34227355296443696f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.3644843137106188f, -0.34227355296443696f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.31871199487424384f, -0.38525662138797817f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.31871199487424384f, -0.38525662138797817f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.26791339748938414f, -0.42216396275108f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.26791339748938414f, -0.42216396275108f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.21288964578241032f, -0.4524135262330691f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.21288964578241032f, -0.4524135262330691f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.15450849718733736f, -0.47552825814762106f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.15450849718733736f, -0.47552825814762106f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.09369065729271749f, -0.49114362536437195f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.09369065729271749f, -0.49114362536437195f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.03139525976450547f, -0.49901336421414527f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.03139525976450547f, -0.49901336421414527f, 0.0f, 1.0f, 1.0f, 1.0f,
0.031395259764811986f, -0.499013364214126f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.031395259764811986f, -0.499013364214126f, 0.0f, 1.0f, 1.0f, 1.0f,
0.09369065729301918f, -0.49114362536431444f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.09369065729301918f, -0.49114362536431444f, 0.0f, 1.0f, 1.0f, 1.0f,
0.15450849718762946f, -0.4755282581475262f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.15450849718762946f, -0.4755282581475262f, 0.0f, 1.0f, 1.0f, 1.0f,
0.2128896457826882f, -0.4524135262329383f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.2128896457826882f, -0.4524135262329383f, 0.0f, 1.0f, 1.0f, 1.0f,
0.2679133974896435f, -0.4221639627509154f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.2679133974896435f, -0.4221639627509154f, 0.0f, 1.0f, 1.0f, 1.0f,
0.3187119948744805f, -0.38525662138778244f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.3187119948744805f, -0.38525662138778244f, 0.0f, 1.0f, 1.0f, 1.0f,
0.36448431371082907f, -0.342273552964213f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.36448431371082907f, -0.342273552964213f, 0.0f, 1.0f, 1.0f, 1.0f,
0.404508497187582f, -0.2938926261460876f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.404508497187582f, -0.2938926261460876f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4381533400220225f, -0.24087683705069265f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4381533400220225f, -0.24087683705069265f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4648882429441965f, -0.18406227634216013f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4648882429441965f, -0.18406227634216013f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4842915805643644f, -0.12434494358223713f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.4842915805643644f, -0.12434494358223713f, 0.0f, 1.0f, 1.0f, 1.0f,
0.49605735065726403f, -0.06266661678195319f, 0.0f, 1.0f, 1.0f, 1.0f,
0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.49605735065726403f, -0.06266661678195319f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 2.0460266106096413E-13f, 0.0f, 1.0f, 1.0f, 1.0f,
};

// define OpenGL object IDs to represent the vertex array and the shader program in the GPU
GLuint vao;         // vertex array object (stores the render state for our vertex array)
GLuint vbo;         // vertex buffer object (reserves GPU memory for our vertex array)
GLuint shader;      // combined vertex and fragment shader

// called by the main function to do initial setup, such as uploading vertex
// arrays, shader programs, etc.; returns true if successful, false otherwise
bool setup()
{
    // generate the VAO and VBO objects and store their IDs in vao and vbo, respectively
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the newly-created VAO to make it the current one that OpenGL will apply state changes to
    glBindVertexArray(vao);

    // upload our vertex array data to the newly-created VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
    shader = gdevLoadShader("logo.vs", "logo.fs");
    if (! shader)
        return false;

    return true;
}

// called by the main function to do rendering per frame
void render()
{
    // clear the whole frame
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // compute a value for the glow amount for this frame
    float glow = fabs(sin(glfwGetTime() / 3.0f)) / 2.0f + 0.5f;

    // using our shader program...
    glUseProgram(shader);

    // ... set the uniform variables of the shader...
    // (in this case, simply set the value of the glow)
    glUniform1f(glGetUniformLocation(shader, "glow"), glow);

    // ... then draw our triangles
    glBindVertexArray(vao);
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
