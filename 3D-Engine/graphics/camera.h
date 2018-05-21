#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class Camera{


private:
	int m_projWidth;
	int m_projHeight;
	float m_fov;
	float m_pitch;
	float m_yaw;

	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	glm::mat4 m_VP;

public: 

	Camera(int projWidth, int projHeight, float fov, float x, float y, float z, float pitch, float yaw);
	~Camera();
	
	inline glm::vec3 getPos() { return m_pos; };
	inline glm::vec3 getFront() { return m_front; };
	inline glm::vec3 getUp() { return m_up; };
	inline glm::mat4 getVP() { return m_VP; };

	void updatePos(float newx,float newy,float newz, float newpitch, float newyaw);
	void update();
	void reset() const;
};