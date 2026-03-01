#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Thing"
GLFWwindow *pWindow;

float backgroundVertices[] = {
    /** top left corner circle
        double x = -0.7;
        double y = 0.7;
        double red = 0;
        double green = 0;
        double blue = 0;
        double radiusX = 0.2;
        double radiusY = 0.2;
        int triangleAmount = 20;
     */
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.49999999999999994f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5097886967409705f, 0.7618033988749934f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5097886967409705f, 0.7618033988749934f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011250153f, 0.8175570504585012f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011250153f, 0.8175570504585012f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495415153f, 0.8618033988749968f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495415153f, 0.8618033988749968f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011250262f, 0.8902113032590357f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011250262f, 0.8902113032590357f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7000000000000206f, 0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7000000000000206f, 0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.761803398875013f, 0.890211303259023f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.761803398875013f, 0.890211303259023f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458518f, 0.8618033988749725f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458518f, 0.8618033988749725f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988750089f, 0.8175570504584678f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988750089f, 0.8175570504584678f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590422f, 0.761803398874954f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590422f, 0.761803398874954f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8999999999999999f, 0.6999999999999585f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8999999999999999f, 0.6999999999999585f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590165f, 0.6381966011249671f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590165f, 0.6381966011249671f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988749602f, 0.582442949541465f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988749602f, 0.582442949541465f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458451f, 0.5381966011249788f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458451f, 0.5381966011249788f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7618033988749342f, 0.5097886967409513f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7618033988749342f, 0.5097886967409513f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6999999999999378f, 0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6999999999999378f, 0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011249475f, 0.5097886967409897f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011249475f, 0.5097886967409897f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495414485f, 0.5381966011250517f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495414485f, 0.5381966011250517f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011249667f, 0.5824429495415655f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011249667f, 0.5824429495415655f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.509788696740945f, 0.6381966011250851f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.509788696740945f, 0.6381966011250851f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.49999999999999994f, 0.7000000000000826f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border left outer triangle
    -0.9f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.9f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border left inner triangle
    -0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.9f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,

    /** bottom left corner circle
        double x = -0.7;
        double y = -0.7;
        double red = 0;
        double green = 0;
        double blue = 0;
        double radiusX = 0.2;
        double radiusY = 0.2;
        int triangleAmount = 20;
     */
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.49999999999999994f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5097886967409705f, -0.6381966011250065f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5097886967409705f, -0.6381966011250065f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011250153f, -0.5824429495414987f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011250153f, -0.5824429495414987f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495415153f, -0.5381966011250031f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495415153f, -0.5381966011250031f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011250262f, -0.5097886967409642f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011250262f, -0.5097886967409642f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7000000000000206f, -0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7000000000000206f, -0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.761803398875013f, -0.5097886967409769f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.761803398875013f, -0.5097886967409769f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458518f, -0.5381966011250274f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458518f, -0.5381966011250274f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988750089f, -0.5824429495415321f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988750089f, -0.5824429495415321f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590422f, -0.638196601125046f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590422f, -0.638196601125046f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8999999999999999f, -0.7000000000000414f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8999999999999999f, -0.7000000000000414f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590165f, -0.7618033988750328f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8902113032590165f, -0.7618033988750328f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988749602f, -0.8175570504585349f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.8618033988749602f, -0.8175570504585349f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458451f, -0.8618033988750211f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.817557050458451f, -0.8618033988750211f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7618033988749342f, -0.8902113032590486f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7618033988749342f, -0.8902113032590486f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6999999999999378f, -0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6999999999999378f, -0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011249475f, -0.8902113032590102f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6381966011249475f, -0.8902113032590102f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495414485f, -0.8618033988749482f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5824429495414485f, -0.8618033988749482f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011249667f, -0.8175570504584344f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5381966011249667f, -0.8175570504584344f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.509788696740945f, -0.7618033988749148f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.509788696740945f, -0.7618033988749148f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.49999999999999994f, -0.6999999999999174f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border bottom outer triangle
    -0.7f, -0.9f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.9f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border bottom inner triangle
    0.7f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.9f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

    /** bottom right corner circle
        double x = 0.7;
        double y = -0.7;
        double red = 0;
        double green = 0;
        double blue = 0;
        double radiusX = 0.2;
        double radiusY = 0.2;
        int triangleAmount = 20;
    */
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8999999999999999f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8902113032590294f, -0.6381966011250065f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8902113032590294f, -0.6381966011250065f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988749846f, -0.5824429495414987f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988749846f, -0.5824429495414987f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504584846f, -0.5381966011250031f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504584846f, -0.5381966011250031f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988749737f, -0.5097886967409642f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988749737f, -0.5097886967409642f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6999999999999793f, -0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6999999999999793f, -0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011249869f, -0.5097886967409769f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011249869f, -0.5097886967409769f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5824429495414819f, -0.5381966011250274f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5824429495414819f, -0.5381966011250274f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.538196601124991f, -0.5824429495415321f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.538196601124991f, -0.5824429495415321f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409577f, -0.638196601125046f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409577f, -0.638196601125046f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.49999999999999994f, -0.7000000000000414f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.49999999999999994f, -0.7000000000000414f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409834f, -0.7618033988750328f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409834f, -0.7618033988750328f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5381966011250398f, -0.8175570504585349f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5381966011250398f, -0.8175570504585349f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.582442949541549f, -0.8618033988750211f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.582442949541549f, -0.8618033988750211f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011250657f, -0.8902113032590486f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011250657f, -0.8902113032590486f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7000000000000621f, -0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7000000000000621f, -0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988750524f, -0.8902113032590102f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988750524f, -0.8902113032590102f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504585514f, -0.8618033988749482f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504585514f, -0.8618033988749482f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988750332f, -0.8175570504584344f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988750332f, -0.8175570504584344f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.890211303259055f, -0.7618033988749148f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.890211303259055f, -0.7618033988749148f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8999999999999999f, -0.6999999999999174f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border right outer triangle
    0.9f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.9f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border right inner triangle
    0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.9f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,

    /** top right corner circle
        double x = 0.7;
        double y = 0.7;
        double red = 0;
        double green = 0;
        double blue = 0;
        double radiusX = 0.2;
        double radiusY = 0.2;
        int triangleAmount = 20;
     */
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8999999999999999f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8902113032590294f, 0.7618033988749934f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8902113032590294f, 0.7618033988749934f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988749846f, 0.8175570504585012f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988749846f, 0.8175570504585012f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504584846f, 0.8618033988749968f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504584846f, 0.8618033988749968f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988749737f, 0.8902113032590357f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988749737f, 0.8902113032590357f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6999999999999793f, 0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6999999999999793f, 0.8999999999999999f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011249869f, 0.890211303259023f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011249869f, 0.890211303259023f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5824429495414819f, 0.8618033988749725f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5824429495414819f, 0.8618033988749725f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.538196601124991f, 0.8175570504584678f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.538196601124991f, 0.8175570504584678f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409577f, 0.761803398874954f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409577f, 0.761803398874954f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.49999999999999994f, 0.6999999999999585f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.49999999999999994f, 0.6999999999999585f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409834f, 0.6381966011249671f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5097886967409834f, 0.6381966011249671f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5381966011250398f, 0.582442949541465f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5381966011250398f, 0.582442949541465f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.582442949541549f, 0.5381966011249788f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.582442949541549f, 0.5381966011249788f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011250657f, 0.5097886967409513f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.6381966011250657f, 0.5097886967409513f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7000000000000621f, 0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7000000000000621f, 0.49999999999999994f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988750524f, 0.5097886967409897f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7618033988750524f, 0.5097886967409897f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504585514f, 0.5381966011250517f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8175570504585514f, 0.5381966011250517f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988750332f, 0.5824429495415655f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8618033988750332f, 0.5824429495415655f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.890211303259055f, 0.6381966011250851f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.890211303259055f, 0.6381966011250851f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.8999999999999999f, 0.7000000000000826f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border top outer triangle
    0.7f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

    // border top inner triangle
    -0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.7f, 0.9f, 0.0f, 0.0f, 0.0f, 0.0f,

    // left main square
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

    // right main square
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
};

// ==========================
// PIECE 1 – Ruby
// ==========================
float piece1[] = {
    -0.70f,0.70f,0.0f,  0.75f,0.10f,0.15f,  0.15f,0.85f,
    -1.0f,1.0f,0.0f,    0.75f,0.10f,0.15f,  0.0f,1.0f,
     0.0f,1.0f,0.0f,    0.75f,0.10f,0.15f,  0.5f,1.0f,
    -0.45f,0.65f,0.0f,  0.75f,0.10f,0.15f,  0.275f,0.825f
};

// ==========================
// PIECE 2 – Sapphire
// ==========================
float piece2[] = {
     0.70f,0.60f,0.0f,  0.10f,0.20f,0.75f,  0.85f,0.80f,
     0.45f,0.65f,0.0f,  0.10f,0.20f,0.75f,  0.725f,0.825f,
     1.0f,1.0f,0.0f,    0.10f,0.20f,0.75f,  1.0f,1.0f,
     1.0f,0.05f,0.0f,   0.10f,0.20f,0.75f,  1.0f,0.525f,
     0.75f,0.05f,0.0f,  0.10f,0.20f,0.75f,  0.875f,0.525f
};

// ==========================
// PIECE 3 – Emerald
// ==========================
float piece3[] = {
    -0.25f,0.50f,0.0f,  0.10f,0.60f,0.25f,  0.375f,0.75f,
    -0.45f,0.65f,0.0f,  0.10f,0.60f,0.25f,  0.275f,0.825f,
     0.0f,0.65f,0.0f,   0.10f,0.60f,0.25f,  0.5f,0.825f,
    -0.65f,0.05f,0.0f,  0.10f,0.60f,0.25f,  0.175f,0.525f
};

// ==========================
// PIECE 4 – Amber
// ==========================
float piece4[] = {
    -0.65f,-0.10f,0.0f, 0.80f,0.45f,0.05f, 0.175f,0.45f,
    -0.65f,0.05f,0.0f,  0.80f,0.45f,0.05f, 0.175f,0.525f,
    -0.45f,-0.55f,0.0f, 0.80f,0.45f,0.05f, 0.275f,0.225f,
    -1.0f,-1.0f,0.0f,   0.80f,0.45f,0.05f, 0.0f,0.0f,
    -1.0f,0.2f,0.0f,    0.80f,0.45f,0.05f, 0.0f,0.6f
};

// ==========================
// PIECE 5 – Amethyst
// ==========================
float piece5[] = {
     0.0f,0.45f,0.0f,   0.55f,0.20f,0.70f, 0.5f,0.725f,
     0.0f,0.65f,0.0f,   0.55f,0.20f,0.70f, 0.5f,0.825f,
     0.45f,0.65f,0.0f,  0.55f,0.20f,0.70f, 0.725f,0.825f,
     0.75f,0.05f,0.0f,  0.55f,0.20f,0.70f, 0.875f,0.525f
};

// ==========================
// PIECE 6 – Teal (center)
// ==========================
float piece6[] = {
     0.0f,0.0f,0.0f,    0.05f,0.55f,0.60f, 0.5f,0.5f,
    -0.65f,0.05f,0.0f,  0.05f,0.55f,0.60f, 0.175f,0.525f,
    -0.73f,-0.02f,0.0f, 0.05f,0.55f,0.60f, 0.135f,0.49f,
    -0.80f,-0.15f,0.0f, 0.05f,0.55f,0.60f, 0.10f,0.425f,
    -0.78f,-0.30f,0.0f, 0.05f,0.55f,0.60f, 0.11f,0.35f,
    -0.65f,-0.43f,0.0f, 0.05f,0.55f,0.60f, 0.175f,0.285f,
    -0.45f,-0.55f,0.0f, 0.05f,0.55f,0.60f, 0.275f,0.225f,
    -1.0f,-1.0f,0.0f,   0.05f,0.55f,0.60f, 0.0f,0.0f,
     1.0f,-1.0f,0.0f,   0.05f,0.55f,0.60f, 1.0f,0.0f,
     0.60f,-0.70f,0.0f, 0.05f,0.55f,0.60f, 0.80f,0.15f,
     0.75f,0.05f,0.0f,  0.05f,0.55f,0.60f, 0.875f,0.525f,
     0.0f,0.65f,0.0f,   0.05f,0.55f,0.60f, 0.5f,0.825f
};

// ==========================
// PIECE 7 – Dark Crimson
// ==========================
float piece7[] = {
    -0.75f,-0.75f,0.0f, 0.50f,0.05f,0.10f, 0.125f,0.125f,
    -1.0f,-1.0f,0.0f,   0.50f,0.05f,0.10f, 0.0f,0.0f,
    -0.45f,-0.55f,0.0f, 0.50f,0.05f,0.10f, 0.275f,0.225f,
    -0.65f,-0.43f,0.0f, 0.50f,0.05f,0.10f, 0.175f,0.285f,
    -1.0f,-0.3f,0.0f,   0.50f,0.05f,0.10f, 0.0f,0.35f
};

// ==========================
// PIECE 8 – Gold
// ==========================
float piece8[] = {
     0.90f,0.0f,0.0f,   0.90f,0.75f,0.15f, 0.95f,0.5f,
     1.0f,1.0f,0.0f,    0.90f,0.75f,0.15f, 1.0f,1.0f,
     1.0f,-1.0f,0.0f,   0.90f,0.75f,0.15f, 1.0f,0.0f,
     0.60f,-0.70f,0.0f, 0.90f,0.75f,0.15f, 0.80f,0.15f,
     0.75f,0.05f,0.0f,  0.90f,0.75f,0.15f, 0.875f,0.525f
};

// ==========================
// PIECE 9 – Cyan
// ==========================
float piece9[] = {
    -0.40f,0.10f,0.0f,  0.10f,0.75f,0.80f, 0.30f,0.55f,
    -0.65f,0.05f,0.0f,  0.10f,0.75f,0.80f, 0.175f,0.525f,
     0.0f,0.65f,0.0f,   0.10f,0.75f,0.80f, 0.5f,0.825f,
    -0.45f,0.65f,0.0f,  0.10f,0.75f,0.80f, 0.275f,0.825f
};

// define OpenGL object IDs to represent the vertex array and the shader program in the GPU
GLuint backgroundVao;       // vertex array object (stores the render state for our vertex array)
GLuint backgroundVbo;       // vertex buffer object (reserves GPU memory for our vertex array)
GLuint backgroundShader;    // combined vertex and fragment shader  

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
    // setup background VOs
    if(!setupVO(
        backgroundVao, 
        backgroundVbo, 
        backgroundShader, 
        backgroundVertices, 
        sizeof(backgroundVertices), 
        "backgroundMove.vs", 
        "backgroundMove.fs"
    )) {
        return false;
    }

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

    // BACKGROUND SHADER
    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1f(glGetUniformLocation(backgroundShader, "time"), time);
    glUniform1f(glGetUniformLocation(backgroundShader, "speed"), speed);

    glBindVertexArray(backgroundVao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(backgroundVertices) / (8 * sizeof(float)));

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
