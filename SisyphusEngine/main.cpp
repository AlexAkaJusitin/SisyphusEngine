#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
int main()
{
	//Stuff for assigning versions of opengl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tell glfw we are using the modern core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLfloat vertices[] =
	{
		//first triangle
		-0.5f, -0.5f * float(sqrt(3)) / 3,	0.0f,		0.8f, 0.3f, 0.02f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		1.0f, 0.6f, 0.32f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.9f, 0.45f, 0.17f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,		0.9f, 0.45f, 0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f

	};

	GLuint indices[] =
	{
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // upper triangle
	};


	//width, height, name, FULLSCREEN, share?
	GLFWwindow* window = glfwCreateWindow(800, 600, "SisyphusEngine", NULL, NULL);
	if (window == NULL)
	{
		//IF somehow the window doesn't create succesfully
		std::cout << "[ERROR]: Failed to create window!";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//While I do not close the window, the program runs
	//There are functions that close it
	gladLoadGL();//load GLAD
	glad_glViewport(0, 0, 800, 600);//for rendering
	//we need to reference the shaders

	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	glfwSwapBuffers(window);//swap the front buffer with the back buffer

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//load the back buffer with color
		glClear(GL_COLOR_BUFFER_BIT);//clear back buffer
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9,GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);//swap the front buffer with the back buffer
		//for handling events(there is a queue of events), kinda like an update function
		glfwPollEvents();

	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}