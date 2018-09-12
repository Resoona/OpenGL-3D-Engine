#include "Light.h"

Light::Light(const glm::vec3& direction, float intensity, const glm::vec4& color)
	: direction(direction), intensity(intensity), color(color), p0(0.0f), p1(0.0f), position(glm::vec3(0.0f)), lightVector(glm::vec3(0.0f))
{
}