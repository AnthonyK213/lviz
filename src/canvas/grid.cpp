#include "grid.h"
#include "camera.h"

#include "../render/gl_vertex_buffer_layout.h"
#include "../render/gl_vertex_index_buffer.h"

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

static const char *GRID_VS = R"(
#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 Near;
out vec3 Far;

vec3 UnprojectPoint(float x, float y, float z) {
  mat4 inv = inverse(projection * view);
  vec4 point = inv * vec4(x, y, z, 1.0f);
  return point.xyz / point.w;
}

void main() {
  Near = UnprojectPoint(aPos.x, aPos.y, -1.0f);
  Far = UnprojectPoint(aPos.x, aPos.y, 1.0f);

  gl_Position = vec4(aPos, 0.0f, 1.0f);
}
)";

static const char *GRID_FS = R"(
#version 330 core

uniform mat4 view;
uniform mat4 projection;

in vec3 Near;
in vec3 Far;

out vec4 FragColor;

vec4 FragGrid(vec3 point) {
  vec2 coord = point.xy;
  vec2 deriv = fwidth(coord);
  float minX = min(deriv.x, 1.0f);
  float minY = min(deriv.y, 1.0f);

  if (-minY < point.y && point.y < minY) {
    return vec4(0.985f, 0.382f, 0.486f, 1.0f); // x-axis
  } else if (-minX < point.x && point.x < minX) {
    return vec4(0.382f, 0.985f, 0.486f, 1.0f); // y-axis
  } else {
    vec2 uv = fract(coord - 0.5f) - 0.5f;
    vec2 grid = abs(uv) / deriv;
    float line = min(grid.x, grid.y);
    return vec4(vec3(0.2f), 1.0f - min(line, 1.0f));
  }
}

float ComputeDepth(vec3 point) {
  vec4 clipSpacePos = projection * view * vec4(point, 1.0f);
  float depth = clipSpacePos.z / clipSpacePos.w;
  return (depth + 1.0f) * 0.5f;
}

float ComputeLinearDepth(vec3 point) {
  vec4 viewSpacePos = view * vec4(point, 1.0f);
  return -viewSpacePos.z;
}

void main() {
  float t = -(Near.z + 0.01f) / (Far.z - Near.z);
  vec3 fragPos =  Near + t * (Far - Near);

  FragColor = FragGrid(fragPos);
  FragColor *= smoothstep(0.3f, 0.0f, ComputeLinearDepth(fragPos) / 1000.0f);
  FragColor *= float(t > 0);

  gl_FragDepth = ComputeDepth(fragPos);
}
)";

struct GridVertexBufferLayout {
  static const render::GLVertexBufferLayout &GetLayout() {
    static render::GLVertexBufferLayout layout{
        {GL_FLOAT, 2, 0},
    };
    return layout;
  }
};

Grid::Grid(Camera *camera)
    : buffer_(nullptr), shader_(nullptr), camera_(camera) {
  render::ShaderSource shader_source{};
  shader_source.vertex_shader = GRID_VS;
  shader_source.fragment_shader = GRID_FS;
  shader_ = std::make_unique<render::Shader>(shader_source);
}

Grid::~Grid() {}

Presentable::Type Grid::GetType() const {
  return Type::Grid;
}

bool Grid::CreateBuffers() {
  static const glm::vec2 vertices[4] = {
      glm::vec2{-1.0f, -1.0f},
      glm::vec2{-1.0f, 1.0f},
      glm::vec2{1.0f, 1.0f},
      glm::vec2{1.0f, -1.0f},
  };
  static const glm::u32 indices[6] = {0, 1, 2, 0, 2, 3};
  buffer_ = std::make_unique<
      render::GLVertexIndexBuffer<glm::vec2, GridVertexBufferLayout>>(
      4, vertices, 6, indices);
  return true;
}

void Grid::Draw() {
  shader_->Use();

  glm::f32 near_far[2] = {camera_->GetNear(), camera_->GetFar()};
  shader_->SetMat4("view", camera_->GetViewMatrix());
  shader_->SetMat4("projection", camera_->GetProjMatrix());

  if (buffer_)
    buffer_->Draw(GL_TRIANGLES);
}

} // namespace canvas
} // namespace lviz
