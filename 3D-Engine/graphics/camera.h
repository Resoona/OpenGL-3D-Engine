#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>



class Camera{


private:
	int m_projWidth;
	int m_projHeight;
	float m_fov;


	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_up;

	glm::vec3 m_right;

	float m_pitch;
	float m_yaw;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	glm::mat4 m_MV;


public: 

	Camera(int projWidth, int projHeight, float fov, float x, float y, float z, float pitch, float yaw);
	~Camera();
	inline glm::mat4 getMV() { return m_MV; };
	void updatePos(float newx,float newy,float newz, float newpitch, float newyaw);
	void update();
	void reset() const;






};