#include <array>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <stack>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nDjinn.hpp>
#include <thx.hpp>
//#include <thinks/ppm.hpp>

//#include "cpu_brute_force/CpuBruteForce.hpp"
//#include "gpu_brute_force/GpuBruteForce.hpp"
//#include "gpu_prism/GpuPrism.hpp"


typedef thx::vec<2, GLfloat> Vec2f;
typedef thx::vec<3, GLfloat> Vec3f;
typedef thx::vec<2, GLushort> Vec2us;
typedef thx::vec<3, GLushort> Vec3us;


GLFWwindow* win = nullptr;
int win_width = 480;
int win_height = 480;




//! DOCS
void framebufferSizeCallback(GLFWwindow* /*win*/,
                             const int w, const int h)
{
  //cout << "framebufferSizeCallback" << endl;

  win_width = w;
  win_height = h;
  ndj::viewport(0, 0, w, h);
}

//! DOCS
void keyCallback(GLFWwindow* window,
                 int key, int scancode, int action, int mods)
{
  //cout << "keyCallback" << endl;
}

//! DOCS
void cursorPosCallback(GLFWwindow* win,
                       const double mx, const double my)
{
  //cout << "cursorPosCallback" << endl;
}

//! DOCS
void mouseButtonCallback(GLFWwindow* window,
                         int button, int action, int mods)
{
  //cout << "mouseButtonCallback" << endl;
}

//! DOCS
void scrollCallback(GLFWwindow* win, double xoffset, double yoffset)
{
  //cout << "scrollCallback" << endl;
}


//! DOCS
void initGLFW(const int width, const int height)
{
  using namespace std;

  if (!glfwInit())
  {
    throw runtime_error("GLFW init error");
  }

  //glfwWindowHint(GLFW_SAMPLES, 4);

  win = glfwCreateWindow(width, height, "euclidean-distance-transform",
                         nullptr, nullptr);
  if (win == nullptr)
  {
    throw runtime_error("GLFW Open Window error");
  }
  glfwMakeContextCurrent(win);
  glfwSetFramebufferSizeCallback(win, framebufferSizeCallback);
  glfwSetKeyCallback(win, keyCallback);
  glfwSetCursorPosCallback(win, cursorPosCallback);
  glfwSetMouseButtonCallback(win, mouseButtonCallback);
  glfwSetScrollCallback(win, scrollCallback);
}


//! DOCS
void initGL()
{
  using namespace std;
  using namespace ndj;

  //enable(GL_MULTISAMPLE);
  //frontFace(GL_CCW);
  //cullFace(GL_BACK);
  //enable(GL_CULL_FACE);

  // So that we don't get clamped values when reading back floating point
  // textures.
  //glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
  //glClampColor(GL_CLAMP_VERTEX_COLOR, GL_FALSE);
  //glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);

  auto glfwMajor = int{0};
  auto glfwMinor = int{0};
  auto glfwRev = int{0};
  glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);

  cout
    << "GLFW version: "
      << glfwMajor << "." << glfwMinor << "." << glfwRev << "\n"
    << "GLEW_VERSION: " << glewGetString(GLEW_VERSION) << "\n"
    << "GL_VERSION: " << getString(GL_VERSION) << "\n"
    << "GL_VENDOR: " << getString(GL_VENDOR) << "\n"
    << "GL_RENDERER: " << getString(GL_RENDERER) << "\n"
    << "GL_SHADING_LANGUAGE_VERSION: "
      << getString(GL_SHADING_LANGUAGE_VERSION) << "\n";

  auto const gl_max_viewport_dims = getIntegers<2>(GL_MAX_VIEWPORT_DIMS);

  cout << "GL_MAX_VERTEX_ATTRIBS: " << getInteger(GL_MAX_VERTEX_ATTRIBS) << "\n";
  cout << "GL_MAX_RENDERBUFFER_SIZE: " << getInteger(GL_MAX_RENDERBUFFER_SIZE) << "\n";
  cout << "GL_MAX_DRAW_BUFFERS: " << getInteger(GL_MAX_DRAW_BUFFERS) << "\n";
  cout << "GL_MAX_TEXTURE_SIZE: " << getInteger(GL_MAX_TEXTURE_SIZE) << endl;
  cout << "GL_MAX_VIEWPORT_DIMS: "
       << gl_max_viewport_dims[0] << ", " << gl_max_viewport_dims[1] << endl;
}


#if 0
//! DOCS
std::vector<thx::vec<2, float>>
GetCircleContour(
  std::size_t const vertex_count,
  thx::vec<2, float> const& center,
  float const radius,
  float const radial_offset_magnitude,
  float const radial_offset_angular_frequency,
  float const time)
{
  using namespace std;
  using namespace thx;

  auto vertices = vector<vec<2, float>>();
  if (vertex_count == 0) {
    return vertices;
  }

  vertices.reserve(vertex_count);
  for (auto i = size_t{0}; i < vertex_count; ++i) {
    auto const angle_rad = deg_to_rad((360.f * i) / vertex_count);
    vertices.push_back(
      center +
      (radius + radial_offset_magnitude *
       cosf(radial_offset_angular_frequency * angle_rad + time)) *
      vec<2, float>(cosf(angle_rad), sinf(angle_rad)));
  }
  return vertices;
}
#endif

#if 0
void initScene(
  thx::vec<2, float> const& grid_corner,
  thx::vec<2, std::size_t> const& grid_size,
  thx::vec<2, float> const& grid_spacing,
  std::vector<GLfloat> const& grid_data,
  std::vector<thx::vec<2, float>> const& contour_vertices)
#endif
void initScene()
{
#if 0
  using namespace std;
  using namespace ndj;

  // Bind camera transformations to uniform buffer.
  auto camera = array<GLfloat, 2 * 16>{{
    1.f, 0.f, 0.f, 0.f, // view_from_world matrix, column 0.
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 0.f, // clip_from_view, column 0.
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f }};
  makeOrthographicProjectionMatrix(
    grid_corner[0] - .5f, grid_corner[0] + grid_size[0] * grid_spacing[0] + .5f,
    grid_corner[1] - .5f, grid_corner[1] + grid_size[1] * grid_spacing[1] + .5f,
    -1.f, 1.f,
    &camera[16]);
  scene_camera_ubo.reset(
    new UniformBuffer(
      camera.size() * sizeof(GLfloat),
      camera.data()));
  scene_camera_ubo->bindBase(scene_camera_uniform_block_binding);

  // Bind model transformations to uniform buffer.
  auto const model = array<GLfloat, 1 * 16>{{
    1.f, 0.f, 0.f, 0.f, // world_from_obj matrix, column 0.
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f }};
  scene_model_ubo.reset(
    new UniformBuffer(
      model.size() * sizeof(GLfloat),
      model.data()));
  scene_model_ubo->bindBase(scene_model_uniform_block_binding);

  initQuad(grid_corner, grid_size, grid_spacing, grid_data);
  initContour(contour_vertices);
  initPrisms(contour_vertices);
#endif
}


void drawScene()
{
#if 0
  using namespace std;
  using namespace ndj;

  viewport(0, 0, win_width, win_height);
  auto const draw_bufs = array<GLenum, 1>{{ GL_BACK }};
  drawBuffers<1>(draw_bufs);
  auto const clear_color = array<GLfloat, 4>{{ .2f, .2f, .2f, 1.f }};
  clearBufferfv(GL_COLOR, 0, clear_color.data());
  drawQuad();
  drawContour();
  drawPrisms();
#endif
}


int main(int argc, char* argv[])
{
  using namespace std;
  using namespace thx;

  try {
    initGLFW(win_width, win_height);
    initGL();

    initScene(); // TODO

    while (!glfwWindowShouldClose(win))
    {
      drawScene();

      // Swap front and back buffers, poll for and process events.
      glfwSwapBuffers(win);
      glfwPollEvents();
    }

    // Close window and terminate GLFW.
    glfwDestroyWindow(win);
    glfwTerminate();
  }
  catch (const std::exception& ex) {
    cerr << "Exception: " << ex.what() << "\n";
    // Close window and terminate GLFW.
    glfwDestroyWindow(win);
    glfwTerminate();
    abort();
  }
  catch (const ndj::Exception& ex) {
    cerr << "Exception: " << ex.what() << "\n";
    // Close window and terminate GLFW.
    glfwDestroyWindow(win);
    glfwTerminate();
    abort();
  }
  catch (...) {
    cerr << "Unknown exception\n";
    // Close window and terminate GLFW.
    glfwDestroyWindow(win);
    glfwTerminate();
    abort();
  }

  return EXIT_SUCCESS;
}
