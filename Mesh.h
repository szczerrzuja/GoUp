#pragma once
#include "Texture.h"
#include "Vertex.h"
#include "Stable.h"
#include "Material.h"
#include "Shaders/Shader.h"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <math.h>
#include <vector>
class Mesh {
private:

    void setupMesh();
    
    void normals();
public:
    //  render data
    GLuint VAO, VBO, EBO;
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    glm::mat4 MMatrix;
    Material material;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool stable,
        Material mat = {  {0.2f,1.0f, 0.5f}, {1.0f,0.5f, 0.2f} , 1.0f });
    void Draw(Shader *shader);
    Mesh();
    void applyTransform();
    void setMaterial(Material mat);

};
void scale_mesh(Mesh* mesh, glm::vec3 scale, glm::vec3 pos = { 0,0,0 });
void rotate_mesh(Mesh* mesh,float angle, glm::vec3 rot, glm::vec3 center = {0,0,0});
void move_mesh(Mesh* mesh, glm::vec3 pos);
void rotate_mesh(Mesh* mesh, glm::vec3 rot, glm::vec3 center = { 0,0,0 });
void m_rotate_mesh(Mesh* mesh, glm::vec3 rot, glm::vec3 center = { 0,0,0 });