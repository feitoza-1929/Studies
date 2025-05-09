#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PARTICLES 1

typedef struct Vec2
{
    float x;
    float y;
} Vec2;

typedef struct Particle
{
    Vec2 velocity;
    Vec2 position;
    float mass;
} Particle;

Particle particles[NUM_PARTICLES];

void init_particles()
{
    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        particles[i].position = (Vec2){0, 0};
        particles[i].velocity = (Vec2){0, -0.1};
        particles[i].mass = 1;
    }
}

Vec2 compute_force(Particle *particle)
{
    return (Vec2){0, particle->mass * -9.81};
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow *window = glfwCreateWindow(600, 600, "Particle Simulation", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("GLEW Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float totalSimulationTime = 10;
    float currentTime = 0;
    float dt = 0.1;

    init_particles();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 1.0f, 1.0f);
        
        sleep(dt);
        for (int i = 0; i < NUM_PARTICLES; ++i)
        {
            Particle *particle = &particles[i];
            Vec2 force = compute_force(particle);
            Vec2 acceleration = (Vec2){force.x / particle->mass, force.y / particle->mass};

            particle->velocity.x += acceleration.x * dt;
            particle->velocity.y += acceleration.x * dt;

            particle->position.x += particle->velocity.x * dt;
            particle->position.y += particle->velocity.y * dt;

            float half_size = 0.1f;
            glBegin(GL_QUADS);
            glVertex2f(particle->position.x - half_size, particle->position.y - half_size);
            glVertex2f(particle->position.x + half_size, particle->position.y - half_size);
            glVertex2f(particle->position.x + half_size, particle->position.y + half_size);
            glVertex2f(particle->position.x - half_size, particle->position.y + half_size);
            glEnd();
        }
        currentTime += dt;

        // glBegin(GL_QUADS);
        // glVertex2f(-0.1f, -0.1f);
        // glVertex2f(0.1f, -0.1f);
        // glVertex2f(0.1f, 0.1f);
        // glVertex2f(-0.1f, 0.1f);
        // glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}