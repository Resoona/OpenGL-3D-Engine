
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

    class Shader
    {
    private:
        GLuint m_ShaderID;
        const char* m_VertPath;
        const char* m_FragPath;
    public:
        Shader(const char* vertPath, const char* fragPath);
        ~Shader();
        void enable() const;
        void disable() const;

        void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
        //TODO: This returns a private element for texture mapping, rework this
        inline GLint getShaderID() const { return m_ShaderID; };


    private:
        GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        GLint getUniformLocation(const GLchar* name);


    };


