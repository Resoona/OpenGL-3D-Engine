#pragma once

#include "Mesh.h"
#include "Material.h"
#include "buffers/VertexArray.h"

VertexArray* CreateQuad(const glm::vec2& position, const glm::vec2& size);
VertexArray* CreateQuad(float x, float y, float width, float height);
Mesh* CreateCube(float size, MaterialInstance* material);
