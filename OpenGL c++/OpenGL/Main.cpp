#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"





int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 400, "OpenGL Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 400);

    // Define vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f,
        -0.25f, 0.0f,  0.0f,
         0.25f, 0.0f,  0.0f,
         0.0f, -0.5f,  0.0f
    };

    // Define indices
    GLuint indices[] = {
        0, 3, 5,  // Bottom left
        3, 2, 4,  // Bottom right
        5, 4, 1   // Top one
    };

    Shader ShaderProgram("Default.vert", "Default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.linkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();

    

    glClearColor(0.02f, 0.5f, 0.35f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
