#include "Renderer.h"

void Renderer::update()
{
    glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& mesh : _meshes)
    {
        for (auto& face : *mesh)
        {
            glBegin(GL_TRIANGLE_STRIP);
            
            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glColor3f(face.a.color.r, face.a.color.g, face.a.color.b);
            glVertex3f(face.a.x, face.a.y, face.a.z);
            
            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glColor3f(face.b.color.r, face.b.color.g, face.b.color.b);
            glVertex3f(face.b.x, face.b.y, face.b.z);

            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glColor3f(face.c.color.r, face.c.color.g, face.c.color.b);
            glVertex3f(face.c.x, face.c.y, face.c.z);

            glEnd();
        }
    }
}

void Renderer::addMesh(const Mesh& mesh)
{
    _meshes.push_back(&mesh);
}
