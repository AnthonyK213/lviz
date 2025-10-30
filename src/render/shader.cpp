#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>

namespace lviz {
namespace render {

static GLint getUniLoc(GLuint prog_id, const std::string &name) {
  return glGetUniformLocation(prog_id, name.c_str());
}

static GLuint getCompiledShader(int shader_type, const char *shader_source) {
  if (!shader_source)
    return 0;

  GLuint shader_id = glCreateShader(shader_type);

  glShaderSource(shader_id, 1, &shader_source, nullptr);
  glCompileShader(shader_id);

  GLint result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

    GLchar *str_info_log = new GLchar[length + 1];
    glGetShaderInfoLog(shader_id, length, &length, str_info_log);

    std::cerr << "Compile error in shader: " << str_info_log << std::endl;
    delete[] str_info_log;
  }

  return shader_id;
}

ShaderSource::ShaderSource()
    : vertex_shader(nullptr), fragment_shader(nullptr),
      geometry_shader(nullptr) {}

Shader::Shader(const ShaderSource &source) : prog_id_(0) {
  prog_id_ = glCreateProgram();

  GLuint vs = getCompiledShader(GL_VERTEX_SHADER, source.vertex_shader);
  GLuint fs = getCompiledShader(GL_FRAGMENT_SHADER, source.fragment_shader);
  GLuint gs = getCompiledShader(GL_GEOMETRY_SHADER, source.geometry_shader);

  glAttachShader(prog_id_, vs);
  glAttachShader(prog_id_, fs);
  glAttachShader(prog_id_, gs);

  glLinkProgram(prog_id_);
  glValidateProgram(prog_id_);

  glDeleteShader(vs);
  glDeleteShader(fs);
  glDeleteShader(gs);
}

Shader::~Shader() {
  if (prog_id_) {
    glDeleteProgram(prog_id_);
    prog_id_ = 0;
  }
}

void Shader::Use() const {
  glUseProgram(prog_id_);
}

void Shader::SetBool(const std::string &name, bool value) {
  glUniform1i(getUniLoc(prog_id_, name), (GLint)value);
}

void Shader::SetNums(const std::string &name, glm::u32 n_nums,
                     const glm::f32 *nums) {
  glUniform1fv(getUniLoc(prog_id_, name), n_nums, nums);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &vec2) {
  glUniform2fv(getUniLoc(prog_id_, name), 1, glm::value_ptr(vec2));
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &vec3) {
  glUniform3fv(getUniLoc(prog_id_, name), 1, glm::value_ptr(vec3));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat4) {
  glUniformMatrix4fv(getUniLoc(prog_id_, name), 1, GL_FALSE,
                     glm::value_ptr(mat4));
}

} // namespace render
} // namespace lviz
