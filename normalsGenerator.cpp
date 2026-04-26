#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// replace this vectorArray with the one you need to generate normals for.
// each vertex uses: position (x, y, z), color (r, g, b), uv (s, t). 
// So each vertex is 8 floats.
float vectorArray[] =  {
0.000000f, 0.000000f, -0.039024f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f,
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f,
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f,
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f,
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f,
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f,
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f,
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f,
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f,
0.487805f, 0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f,
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f,
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f,
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f,
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f,
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f,
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f,
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f,
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f,
0.487805f, 0.000000f, -0.039024f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f,
};

// Generates normals for a vertex array in the format used for GL_TRIANGLES.
void generateTriangleNormals(float* vectorArray, int vectorArraySize) {
  // map of each vector's normals
  map<string, vector<glm::vec3>> vectorNormals;
  // go through each triangle
  for (int i = 0; i < vectorArraySize - 8*3 ; i += 8*3) {
    glm::vec3 trianglePoints[3];
    string pointStrings[3];
    // populate the three points of one triangle
    for (int j = 0; j < 3; j++) {
      float x = vectorArray[i + 8*j + 0];
      float y = vectorArray[i + 8*j + 1];
      float z = vectorArray[i + 8*j + 2];
      trianglePoints[j] = glm::vec3(x, y, z);
      for (int k = 0; k < 8; k++) {
        pointStrings[j] += to_string(vectorArray[i + 8*j + k]) + "f, ";
                                                        // could this be "f, "?
      }
    }
    // get the vectors by subtraction
    glm::vec3 vector1 = trianglePoints[2] - trianglePoints[0];
    glm::vec3 vector2 = trianglePoints[1] - trianglePoints[0];
    // get the cross product of two vectors. this will be the normal vector for all three points.
    glm::vec3 cross_p = glm::cross(vector1, vector2);
    
    // add this cross product to the point's list of normals.
    for (string pointString : pointStrings) {
      vectorNormals[pointString].push_back(cross_p); 
    }
  }
  
  // after going through each triangle,
  // get the average of the calculated normals of each point
  map<string, string> averagedNormals;
  for (const auto& [point, normals] : vectorNormals) {
    float totalX = 0.0f;
    float totalY = 0.0f;
    float totalZ = 0.0f;
    for (glm::vec3 normal : normals) {
      totalX += normal.x;
      totalY += normal.y;
      totalZ += normal.z;
    }
    float averagedX = totalX / normals.size();
    float averagedY = totalY / normals.size();
    float averagedZ = totalZ / normals.size();
    
    averagedNormals[point] = to_string(averagedX) + "f, " + 
                             to_string(averagedY) + "f, " + 
                             to_string(averagedZ) + "f, ";
  }
  
  // modify the vectorArray to now include the normals of each vector
  string resultingArray = "";
  for (int i = 0; i < vectorArraySize - 8; i += 8) {
    string point;
    for (int j = 0; j < 8; j++) {
      point += to_string(vectorArray[i + j]) + "f, ";
    }
    point += averagedNormals[point];
    resultingArray += point + '\n';
  }
  
  cout << resultingArray << endl;
  // 
}

// Generates normals for a vertex array in the format used for GL_TRIANGLE_FAN.
void generateFanNormals(float* vectorArray) {
  
}

// Generates normals for a vertex array in the format used for GL_TRIANGLE_STRIP.
void generateStripNormals(float* vectorArray) {
  
}

int main() {
  generateTriangleNormals(vectorArray, sizeof(vectorArray) / sizeof(float));
}