#include "glm/glm/glm.hpp"
#ifndef Vertex_H
#define  Vertex_H
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec4 Color;
};


#endif