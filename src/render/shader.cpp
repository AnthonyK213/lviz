#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>

namespace lviz {
namespace render {

static GLuint getCompiledShader(int shader_type,
                                const std::string &shader_source) {
  GLuint shader_id = glCreateShader(shader_type);

  const char *c_source = shader_source.c_str();
  glShaderSource(shader_id, 1, &c_source, nullptr);
  glCompileShader(shader_id);

  GLint result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

    GLchar *str_info_log = new GLchar[length + 1];
    glGetShaderInfoLog(shader_id, length, &length, str_info_log);

    std::fprintf(stderr, "Compile error in shader: %s\n", str_info_log);
    delete[] str_info_log;
  }

  return shader_id;
}

Shader::Shader() : prog_id_(0) {}

bool Shader::Load() {
  //   const std::string vert = R"(
  // #version 330 core

  // layout(location = 0) in vec3 aPosition;
  // layout(location = 1) in vec3 aNormal;

  // uniform mat4 model;
  // uniform mat4 view;
  // uniform mat4 projection;
  // uniform vec4 color;

  // out vec3 WorldPos;
  // out vec3 Normal;
  // out vec4 Color;

  // void main() {
  //   Color = color;
  //   WorldPos = vec3(model * vec4(aPosition, 1.0));
  //   Normal = aNormal;

  //   gl_Position = projection * view * model * vec4(aPosition, 1.0f);
  // })";

  //   const std::string frag = R"(
  // #version 330

  // struct DirLight {
  //   vec3 position;
  //   vec3 color;
  //   float strength;
  // };

  // uniform mat4 model;
  // uniform DirLight dirLight;

  // in vec4 Color;
  // in vec3 WorldPos;
  // in vec3 Normal;

  // out vec4 fOutput;

  // void main () {
  //   mat3 normalMatrix = transpose(inverse(mat3(model)));
  //   vec3 normal = normalize(normalMatrix * Normal);
  //   vec3 light_diff = dirLight.position - vec3(model * vec4(WorldPos, 1));
  //   float luminance = dot(normal, light_diff) / (length(light_diff) *
  //   length(normal)); fOutput = vec4(luminance * dirLight.color, 1.0f) *
  //   dirLight.strength;
  // })";

  const std::string vert = R"(
#version 330 core

layout(location = 0) in vec3 aPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 WorldPos;

void main() {
  gl_Position = projection * view * model * vec4(aPosition, 1.0f);
})";

  const std::string frag = R"(
#version 330 core

out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";

  prog_id_ = glCreateProgram();

  GLuint vs = getCompiledShader(GL_VERTEX_SHADER, vert);
  GLuint fs = getCompiledShader(GL_FRAGMENT_SHADER, frag);

  glAttachShader(prog_id_, vs);
  glAttachShader(prog_id_, fs);

  glLinkProgram(prog_id_);
  glValidateProgram(prog_id_);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return true;
}

void Shader::Use() const {
  glUseProgram(prog_id_);
}

void Shader::Unload() {
  glDeleteProgram(prog_id_);
}

void Shader::SetMat4(const glm::mat4 &mat4, const std::string &name) {
  GLint myLoc = glGetUniformLocation(GetProgId(), name.c_str());
  glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
}

} // namespace render
} // namespace lviz
