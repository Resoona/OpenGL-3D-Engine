#pragma once
#include "../utils/Eng.h"

__declspec(align(16)) struct Light
{
	glm::vec4 color;
	glm::vec3 position;
	float p0;
	glm::vec3 direction;
	float p1;
	glm::vec3 lightVector;
	float intensity;

	Light(const glm::vec3& direction, float intensity = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
};