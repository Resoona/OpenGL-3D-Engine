#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

	class Camera {

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
		Camera();
		Camera(int projWidth, int projHeight, float fov, float x, float y, float z, float pitch, float yaw);
		~Camera();

		inline glm::vec3 GetPos() { return m_pos; }
		inline glm::vec3 GetFront() { return m_front; }
		inline glm::vec3 GetUp() { return m_up; }
		inline glm::mat4 GetVP() { return m_VP; }
		inline glm::mat4& GetProjectionMatrix() { return m_Projection; }
		inline glm::mat4& GetViewMatrix() { return m_View; }
		inline float GetYaw() { return m_yaw; }
		inline float GetPitch() { return m_pitch; }


		void UpdatePos(float newx, float newy, float newz, float newpitch, float newyaw);
		void Update();
		void Reset() const;
	};