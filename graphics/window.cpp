
#include "window.h"

    void windowResize(GLFWwindow *window, int width, int height);

    Window::Window(const char *title, int width, int height)
    {
        m_Title = title;
        m_Width = width;
        m_Height = height;
        if (!init())
        {
            glfwTerminate();
        }

    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::init()
    {

        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW\n" << std::endl;
            return false;
        }

        //Creating our main window
        m_Window = glfwCreateWindow(m_Width,m_Height,m_Title, NULL,NULL);

        glfwWindowHint(GLFW_SAMPLES,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        if (!m_Window)
        {
            std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible." << std::endl;
            glfwTerminate();
            return false;
        }
        glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowSizeCallback(m_Window, windowResize);

        glewExperimental=true;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW\n" << std::endl;
            return false;
        }

        std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
        return true;
    }

    void Window::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    bool Window::closed() const
    {
        return glfwWindowShouldClose(m_Window) == 1;
    }

    void windowResize(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

