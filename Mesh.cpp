#include "Mesh.h"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtx/Normal.hpp"
glm::vec3 Normalize(glm::vec3 vec)
{
    glm::vec3 temp;
    float vLen = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    if (vLen == 0)
        return vec;
    temp.x = vec.x / vLen;
    temp.y = vec.y / vLen;
    temp.z = vec.z / vLen;
    return temp;
}
Mesh::Mesh()
{
    MMatrix =  glm::mat4(1.0f);
}


Mesh::Mesh(std::vector<Vertex> vertices,
    std::vector<unsigned int> indices, bool stable,
    Material material)
{
    MMatrix = glm::mat4(1.0f);
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;
    if (stable == 1)
    {
        normals();
        setupMesh();
    }

}
//rysowanie
void Mesh::Draw(Shader *shader)
{
    //je¿eli jest wiêcej ni¿ jedna tekstura na³o¿ona
   // shader->run();
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // je¿eli tekstury s¹
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    //GLint tmp = glGetUniformLocation(shader->Program, "objectColor");
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(MMatrix));
    //glUniform3f(tmp, material.Color.x, material.Color.y, material.Color.z);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
//wrzucenie danych o punktach, normalnych, kordach tekstury, kolorach
void Mesh::setupMesh()
{
    // generates table of verex and assings in VAO
    glGenVertexArrays(1, &VAO);
    // generate buffer object
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //binds an array of vertex
    glBindVertexArray(VAO);
    //to samo co wy¿ej tyle ¿e bufer 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //rysowanie statyczne
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    //thanks to that we are sending an array of verticies to graphic card
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions to buffer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    // vertex normals to buffer 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords to buffer
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    glBindVertexArray(0);
}
//obliczanie normalnych dla punktów
void Mesh::normals()
{
    glm::vec3 temp, tmp = {0,0,0};
    int div = 0;
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        div = 0;
        temp = { 0,0,0 };
        for (unsigned int j = 0; j < indices.size(); j++)
        {
            if (i == indices[j])
            {
                if (j % 3 == 0)
                    tmp = glm::triangleNormal(vertices[indices[j]].Position, vertices[indices[j +2]].Position, vertices[indices[j + 1]].Position);
                   // tmp = CalcNormal(vertices[indices[j]].Position, vertices[indices[j + 1]].Position, vertices[indices[j + 2]].Position);
                if (j % 3 == 1)
                    tmp = glm::triangleNormal(vertices[indices[j]].Position, vertices[indices[j - 1]].Position, vertices[indices[j + 1]].Position);
                    //tmp = CalcNormal(vertices[indices[j]].Position, vertices[indices[j - 1]].Position, vertices[indices[j + 1]].Position);
                if (j % 3 == 2)
                    //tmp = CalcNormal(vertices[indices[j]].Position, vertices[indices[j - 1]].Position, vertices[indices[j -2 ]].Position);
                    tmp = glm::triangleNormal(vertices[indices[j]].Position, vertices[indices[j - 1]].Position, vertices[indices[j -2]].Position);
                temp += tmp;
                div += 1;
            }
        }
        vertices[i].Normal = { temp.x ,temp.y , temp.z  };
    }
    
}

void Mesh::applyTransform()
{    
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        vertices[i].Position = MMatrix * glm::vec4(vertices[i].Position, 1.0f);

    }
    MMatrix = {
        1.0f,0.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f
    };
}
//pamiêtaj skala rotacja przemieszczenie

void rotate_mesh(Mesh* mesh, glm::vec3 rot, glm::vec3 center)
{
    float a = sinf(degtorad * rot.x),
        b = sinf(degtorad * rot.y),
        c = sinf(degtorad * rot.z),
        d = cosf(degtorad * rot.x),
        e = cosf(degtorad * rot.y),
        h = cosf(degtorad * rot.z);
    //to jest rotacja ry, rz, rx co oznacza ¿e przy rotacji z sie knoci
    float temp[9] =
    {
        h * e,
        -a * b - e * c * d,
        b * d - e * c * d,
        c ,
       h * d,
       a * h,
        -b * h,
        b * c * d - e * a,
        e * d + b * c * a
    };
    glm::vec3 tem = { 0.0f, 0.0f, 0.0f };
    //rotowanie ka¿dego wierzcho³ka

    for (unsigned int i = 0; i < mesh->vertices.size(); i++)
    {
        tem.x = (mesh->vertices[i].Position.x - center.x) * temp[0] + (mesh->vertices[i].Position.y - center.y) * temp[1] + (mesh->vertices[i].Position.z - center.z) * temp[2];
        tem.y = (mesh->vertices[i].Position.x - center.x) * temp[3] + (mesh->vertices[i].Position.y - center.y) * temp[4] + (mesh->vertices[i].Position.z - center.z) * temp[5];
        tem.z = (mesh->vertices[i].Position.x - center.x) * temp[6] + (mesh->vertices[i].Position.y - center.y) * temp[7] + (mesh->vertices[i].Position.z - center.z) * temp[8];

        tem.x = tem.x + center.x;
        tem.y = tem.y + center.y;
        tem.z = tem.z + center.z,

        mesh->vertices[i].Position = tem;
    }
    //funkcja dzia³a w miarê dobrz ale nie rotuj o z


}
void move_mesh(Mesh* mesh, glm::vec3 pos)
{
   mesh->MMatrix[3] += glm::vec4(pos, 0.0f);
}
void scale_mesh(Mesh* mesh, glm::vec3 scale, glm::vec3 pos)
{
    mesh->MMatrix = glm::scale(mesh->MMatrix, scale);
}
void rotate_mesh(Mesh* mesh, float angle, glm::vec3 rot, glm::vec3 center)
{
    mesh->MMatrix = glm::rotate(mesh->MMatrix, angle * degtorad, rot);

}
void m_rotate_mesh(Mesh* mesh, glm::vec3 rot, glm::vec3 center)
{
    mesh->MMatrix = glm::rotate(mesh->MMatrix, rot.x * degtorad, {1,0,0});
    mesh->MMatrix = glm::rotate(mesh->MMatrix, rot.y * degtorad, { 0,1,0 });

}
void Mesh::setMaterial(Material mat)
{
    material = mat;
}