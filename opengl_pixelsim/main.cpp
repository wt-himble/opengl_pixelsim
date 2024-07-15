#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderClass.h"


int main() {

	// ******************************* Baseline OPENGL *******************************

	// Needed to use the GLFW functions (required to use OPENGL).

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Defines the window used.

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OPENGL_PIXELSIM", NULL, NULL);

	// Checking for problems with the window initialization. Returns -1 and ends the program if any are found.

	if (window == NULL) {

		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;

	}

	// Makes the previously created window the current context. This is essentially establishing the window as being the 
	// location where any rendering will output to.

	glfwMakeContextCurrent(window);

	// Checks to see if GLAD correctly loaded. If not prints a message to indicate so. 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		std::cout << "Failed to initialize GLAD" << std::endl;

	} 

	// Generates the platform specific code needed for whatever machine is running the program. Allows for OPENGL to work
	// across platforms. 

	gladLoadGL();

	// ******************************* Initializing *******************************

	// Information relating to quad:

	float vertexData[] = {

	// Position Coordinates		Texture Coordinates

		1.0f, 1.0f, 0.0f,	   		1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,			1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,			0.0f, 0.0f, 
		-1.0f, 1.0f, 0.0f,			0.0f, 1.0f

	};

	GLuint indicesData[] = {

		0, 1, 3,
		1, 2, 3

	};

	// Create and setup the information needed for the quad the texture will render to.

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the VAO, VBO and EBO so they don't get overwritten.

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Load the texture in order to render it onto the quad.

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 180, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Setup the shaders to render the texture.

	// Data to be added to the texture:

	uint8_t data[] = {

		1.0f, 0.0f, 0.0f

	};

	glViewport(0, 0, 1280, 720);

	Shader shaderProgram("default.vert", "default.frag");
	
	// ******************************* Main Loop *******************************

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		shaderProgram.Activate();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//this code should be at the end of the while loop

		glfwSwapBuffers(window);
		glfwPollEvents();

		
	}

	// Ends the instance of GLFW.

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}