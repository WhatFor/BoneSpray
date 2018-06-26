#include "stdafx.h"
#include "bonespraygraphics.h"
#include "bonegl_render_model.h"
#include "sload.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"

namespace bonegl
{
	// The program containing our shader registrations
	rm::RenderModels* models;
	GLuint program;

	void render(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glBindVertexArray(models -> GetModel("triangle"));
		glUseProgram(program);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glutSwapBuffers();
	}

	/*
	 *	Called on finish of loop, return to main prog
	 */
	int close()
	{
		delete models;
		glDeleteProgram(program);
		return 0;
	}

	/*
	 *	Called on loop exit
	 */
	void closeCallback()
	{
		glutLeaveMainLoop();
	}

	/*
	 *	Register event listeners against GLUT
	 */
	int registerListeners()
	{
		glutDisplayFunc(render);
		glutCloseFunc(closeCallback);

		return 0;
	}

	/*
	 *	Reads the input shader files, and registers them with a Program for use by GL.
	 */
	int loadShaders()
	{
		SLoader sLoader;
		program = sLoader.CreateProgram
		(
			"Shaders\\Vertex_Shader.glsl",
			"Shaders\\Fragment_Shader.glsl"
		);

		return 0;
	}

	void loadAndBindModels()
	{
		models = new rm::RenderModels();
		models -> CreateTriangleModel("triangle");
	}

	/*
	 *	Initalise GLUT and GLEW, spawning our window and using our config.
	 */
	void init(int argc, char **argv)
	{
		// Config
		const int GL_WINDOW_W = 500;
		const int GL_WINDOW_H = 500;
		const char* WINDOW_NAME = "Bone Spray";
		const bool DISPLAY_FULL_SCREEN = false;


		// Launch GLUT + window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(GL_WINDOW_W, GL_WINDOW_H);
		glutCreateWindow(WINDOW_NAME);
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glewInit();

		// Load models
		loadAndBindModels();

		if (DISPLAY_FULL_SCREEN) glutFullScreen();
	}

	/*
	 *	Launch OpenGL, register shaders and begin the render loop
	 */
	int launch(int argc, char **argv)
	{
		init(argc, argv);
		loadShaders();
		registerListeners();
		glutMainLoop();

		return close();
	}
}