#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <random>
#include <algorithm>
#include <stdlib.h>

class Droplet
{
    public:
        Droplet()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0,4000);
            this->w = 0.0075f/2;
            this->h = 0.1f;
            GLfloat vel;
            GLfloat offset;
            offset = dis(gen);
            offset = offset/1000.f;
            vel = rand() % 35 + 5;
            vel = vel / 100.f;
            this->speed = vel;
            this->x+=offset;
        }

        void draw(GLfloat x, GLfloat y)
        {
        glBegin(GL_QUADS);
            glColor3f(0.f, 0.4f, 0.9f);
            glVertex3f(-2.f+this->x,            0.f  + this->y, 0.f);
            glVertex3f(-2.f+this->x + this->w,  0.f  + this->y, 0.f);
            glVertex3f(-2.f+this->x + this->w,  0.f  + this->y + this->h, 0.f);
            glVertex3f(-2.f+this->x,            0.f  + this->y + this->h, 0.f);
        glEnd();
        }
        
        void rain()
        {
            if(this->y < -1.f){
                this->y = 1.f;
            }
            else{
                this->y-=this->speed;
            }
        }
    private:
        GLfloat x,y,w,h;
        GLfloat speed;
};

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    Droplet d1[400];
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(1280, 720, "Rain", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        for(int i = 0; i < 400; i++)
        {
            d1[i].draw(-2.f,1.f);
            d1[i].rain();
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}