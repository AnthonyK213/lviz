#include "viewport.h"
#include "frame.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

namespace lviz::ui {

struct Cube {
  static constexpr auto xyzArray = std::array{
      // front
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // 1
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,   // 2
      -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // 3

      // top
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // 5
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // 6
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // 7

      // left
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 8
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 9
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // 10
      -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // 11

      // right
      0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, // 12
      0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,  // 13
      0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,   // 14
      0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,  // 15

      // back
      -0.5f, -0.5f, 0.5f, 0.7f, 0.7f, 0.7f, // 16
      0.5f, -0.5f, 0.5f, 0.7f, 0.7f, 0.7f,  // 17
      0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f,   // 18
      -0.5f, 0.5f, 0.5f, 0.7f, 0.7f, 0.7f,  // 19

      // bottom
      -0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f, // 20
      0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,  // 21
      0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, // 22
      -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f // 23
  };

  static constexpr auto triangleVertexIndices = std::array{
      // front
      0, 1, 2, // first triangle
      2, 3, 0, // second triangle

      // top
      4, 5, 6, // first triangle
      6, 7, 4, // second triangle

      // left
      8, 9, 10,  // first triangle
      10, 11, 8, // second triangle

      // right
      14, 13, 12, // 12, 13, 14, // first triangle
      12, 15, 14, // 14, 15, 12, // second triangle

      // back
      18, 17, 16, // 16, 17, 18, // first triangle
      16, 19, 18, // 18, 19, 16, // second triangle

      // bottom
      20, 21, 22, // first triangle
      22, 23, 20  // second triangle
  };
};

Viewport::Viewport(wxWindow *parent, const wxGLAttributes &attribs)
    : wxGLCanvas(parent, attribs), myGLCtxt(nullptr), myGLIsInit(false),
      anglex(0.f), angley(0.f) {
  wxGLContextAttrs ctxtAttribs{};
  ctxtAttribs.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();
  myGLCtxt = new wxGLContext(this, nullptr, &ctxtAttribs);

  if (!myGLCtxt->IsOK()) {
    wxMessageBox("This sample needs an OpenGL 3.3 capable driver.",
                 "OpenGL version error", wxOK | wxICON_INFORMATION, this);
    delete myGLCtxt;
    myGLCtxt = nullptr;
  }

  Bind(wxEVT_PAINT, &Viewport::OnPaint, this);
  Bind(wxEVT_SIZE, &Viewport::OnSize, this);

  Bind(wxEVT_KEY_DOWN, &Viewport::OnKeyDown, this);
}

Viewport::~Viewport() { delete myGLCtxt; }

bool Viewport::InitGLFuncs() {
  if (gladLoadGL())
    return true;

  wxLogError("OpenGL GLAD initialization failed");
  return false;
}

bool Viewport::InitGL() {
  if (!myGLCtxt)
    return false;

  SetCurrent(*myGLCtxt);

  if (!InitGLFuncs()) {
    wxMessageBox("Error: Could not initialize OpenGL function pointers.",
                 "OpenGL initialization error", wxOK | wxICON_INFORMATION,
                 this);
    return false;
  }

  wxLogDebug("OpenGL version: %s",
             reinterpret_cast<const char *>(glGetString(GL_VERSION)));
  wxLogDebug("OpenGL vendor: %s",
             reinterpret_cast<const char *>(glGetString(GL_VENDOR)));

  constexpr auto vertexShaderSource = R"(
              #version 330 core
              layout (location = 0) in vec3 aPos;
              layout (location = 1) in vec3 aColor;
      
              uniform mat4 modelMatrix;
      
              out vec3 vertexColor;
      
              void main()
              {
                  gl_Position = modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
                  vertexColor = aColor;
              }
          )";

  constexpr auto fragmentShaderSource = R"(
              #version 330 core
              out vec4 FragColor;
      
              in vec3 vertexColor;
      
              void main()
              {
                  FragColor = vec4(vertexColor, 1.0);
              }
          )";

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    wxLogDebug("Vertex Shader Compilation Failed: %s", infoLog);
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    wxLogDebug("Fragment Shader Compilation Failed: %s", infoLog);
  }

  myShader = glCreateProgram();
  glAttachShader(myShader, vertexShader);
  glAttachShader(myShader, fragmentShader);
  glLinkProgram(myShader);

  glGetProgramiv(myShader, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(myShader, 512, nullptr, infoLog);
    wxLogDebug("Shader Program Linking Failed: %s", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glGenVertexArrays(1, &myVAO);
  glGenBuffers(1, &myVBO);
  glGenBuffers(1, &myEBO);

  glBindVertexArray(myVAO);
  glBindBuffer(GL_ARRAY_BUFFER, myVBO);
  glBufferData(GL_ARRAY_BUFFER, Cube::xyzArray.size() * sizeof(float),
               Cube::xyzArray.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               Cube::triangleVertexIndices.size() * sizeof(unsigned int),
               Cube::triangleVertexIndices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  myGLIsInit = true;

  return true;
}

void Viewport::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);

  if (!myGLIsInit) {
    return;
  }

  SetCurrent(*myGLCtxt);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  GLint depthFuncValue;
  glGetIntegerv(GL_DEPTH_FUNC, &depthFuncValue);
  glClearDepth(depthFuncValue == GL_LESS ? 1.0f : 0.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(myShader);

  auto modelMatrix = glm::mat4(1.0f);

  modelMatrix = glm::rotate(modelMatrix, glm::radians(anglex),
                            glm::vec3(1.0f, 0.0f, 0.0f));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(angley),
                            glm::vec3(0.0f, 1.0f, 0.0f));

  auto modelMatrixLocation = glGetUniformLocation(myShader, "modelMatrix");
  glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE,
                     glm::value_ptr(modelMatrix));

  glBindVertexArray(myVAO);
  glDrawElements(GL_TRIANGLES, Cube::triangleVertexIndices.size(),
                 GL_UNSIGNED_INT, 0);

  SwapBuffers();
}

void Viewport::OnSize(wxSizeEvent &event) {
  bool firstApperance = IsShownOnScreen() && !myGLIsInit;

  if (firstApperance) {
    InitGL();
  }

  if (myGLIsInit) {
    wxSize viewPortSize = event.GetSize() * GetContentScaleFactor();
    glViewport(0, 0, viewPortSize.x, viewPortSize.y);
  }

  event.Skip();
}

void Viewport::OnKeyDown(wxKeyEvent &event) {
  constexpr float AngleIncrement = 5.0f;

  if (event.GetKeyCode() == WXK_LEFT) {
    angley -= AngleIncrement;
  } else if (event.GetKeyCode() == WXK_RIGHT) {
    angley += AngleIncrement;
  } else if (event.GetKeyCode() == WXK_UP) {
    anglex += AngleIncrement;
  } else if (event.GetKeyCode() == WXK_DOWN) {
    anglex -= AngleIncrement;
  } else {
    event.Skip();
  }

  Refresh();
}

} // namespace lviz::ui
