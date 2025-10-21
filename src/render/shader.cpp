#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>

namespace lviz {
namespace render {

static GLuint getCompiledShader(int shader_type, const char *shader_source) {
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

Shader::Shader(const char *vertex_shader, const char *fragment_shader)
    : prog_id_(0) {
  prog_id_ = glCreateProgram();

  GLuint vs = getCompiledShader(GL_VERTEX_SHADER, vertex_shader);
  GLuint fs = getCompiledShader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(prog_id_, vs);
  glAttachShader(prog_id_, fs);

  glLinkProgram(prog_id_);
  glValidateProgram(prog_id_);

  glDeleteShader(vs);
  glDeleteShader(fs);
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

void Shader::Numbers(const std::string &name, glm::u32 n_num,
                     const glm::f32 *num) {
  GLint myLoc = glGetUniformLocation(prog_id_, name.c_str());
  glUniform1fv(myLoc, n_num, num);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &vec3) {
  GLint myLoc = glGetUniformLocation(prog_id_, name.c_str());
  glUniform3fv(myLoc, 1, glm::value_ptr(vec3));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat4) {
  GLint myLoc = glGetUniformLocation(prog_id_, name.c_str());
  glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
}

} // namespace render
} // namespace lviz
