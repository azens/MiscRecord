

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int i;
	GLboolean running = GL_TRUE;
	GLFWwindow* windows[4];

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	for (i = 0;  i < 4;  i++) {
		int left, top, right, bottom;

		windows[i] = glfwCreateWindow(200, 200, titles[i], NULL, NULL);
		if (!windows[i]) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(windows[i], key_callback);

		glfwMakeContextCurrent(windows[i]);
		glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);

		glfwGetWindowFrameSize(windows[i], &left, &top, &right, &bottom);
		glfwSetWindowPos(windows[i],
		                 100 + (i & 1) * (200 + left + right),
		                 100 + (i >> 1) * (200 + top + bottom));
	}

	for (i = 0;  i < 4;  i++)
		glfwShowWindow(windows[i]);

	while (running) {
		for (i = 0;  i < 4;  i++) {
			glfwMakeContextCurrent(windows[i]);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(windows[i]);

			if (glfwWindowShouldClose(windows[i]))
				running = GL_FALSE;
		}

		glfwPollEvents();
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

