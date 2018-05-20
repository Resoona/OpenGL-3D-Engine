#include "Camera.h"


class ModelTransform {

private:
	int m_mx;
	int m_my;
	int m_mz;

	Camera m_Camera;

	glm::mat4 m_Model;
	glm::mat4 m_MVP;
	

	void update();

public:
	ModelTransform(Camera camera, int mx, int my, int mz);
	~ModelTransform();
	void updatePos(int newx, int newy, int newz);
	glm::mat4 getMVP(Camera updatedCamera);

};