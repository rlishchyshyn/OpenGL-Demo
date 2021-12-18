#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"

#include "Mesh.h"

class Renderer
{
    friend class Window;
public:
    void addMesh(const Mesh& mesh);

private:
    void update();

private:
    std::vector<const Mesh*> _meshes;
};