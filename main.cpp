#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/math_3d.h"

using namespace std;

static const unsigned int scr_width = 1920;
static const unsigned int scr_height = 1080;

GLuint renderingProgram;
GLuint vao, vbo;

GLuint createShaderProgram();
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);

int main(int argc, char** argv)
{
	int glfwState = glfwInit();
	if (GLFW_FALSE == glfwState)
	{
		cout << "GLFW initialize failed. Invoke glfwInit()." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "Draw point", nullptr, nullptr);
	glfwMakeContextCurrent(window);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }
	
	glfwInit();

	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//销毁窗口,以及撤销窗口事件
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

GLuint createShaderProgram()
{
    const char* vShaderSource =
    "#version 400\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";

    const char* fShaderSource =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vShader, 1, &vShaderSource, nullptr);
		glShaderSource(fShader, 1, &fShaderSource, nullptr);
		glCompileShader(vShader);
		glCompileShader(fShader);

		GLuint vfProgram = glCreateProgram();
		glAttachShader(vfProgram, vShader);
		glAttachShader(vfProgram, fShader);
		glLinkProgram(vfProgram);

		return vfProgram;
}

void init(GLFWwindow* window)
{
	
	renderingProgram = createShaderProgram();
	//缓冲区最后都会被存入顶点数组对象VAO(Vertex Array Object)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void display(GLFWwindow* window, double currentTime)
{
  Vector3f Vertices[1];
  Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(50.0f);
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
}
