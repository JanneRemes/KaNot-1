#pragma once

#include <Win32toAndroid.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
	Camera();
	~Camera();
	void Camera2D();
	glm::mat4 Projection;
	glm::mat4 View;
private:

};