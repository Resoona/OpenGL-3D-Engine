#pragma once
#include <GL/glew.h>


    class Buffer
    {
    private:
        GLuint m_BufferID;
        GLuint m_ComponentCount;
    public:
        Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

        void bind() const;
        void unBind() const;

        inline GLuint getComponentCount() const { return m_ComponentCount; }


    };
