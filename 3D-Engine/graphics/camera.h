#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>



class Camera{


private:
	int m_projWidth;
	int m_projHeight;
	float m_fov;

	float m_x;
	float m_y;
	float m_z;



	glm::mat4 m_Projection;
	glm::mat4 m_View;

	glm::mat4 m_MV;


public: 

	Camera(int projWidth, int projHeight, float fov, float x, float y, float z);
	~Camera();
	inline glm::mat4 getMV() { return m_MV; };
	void updatePos(float newx,float newy,float newz);
	void update();
	void reset() const;






};