#include <Camera.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//Projection = glm::ortho(0.f,1280.f, 752.f, 0.f,0.01f,10.f);  //glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1.0f);
	Projection = glm::mat4x4(0.1f,0,0,0,0,0.1f,0,0,0,0,1,0,0,0,0,1);//glm::perspective(45.0f,1280.0f/720.0f,0.001f,100.0f);
	// Camera matrix
	View       = glm::lookAt(
	glm::vec3(1,0,0), // Camera is at (4,3,3), in World Space
	glm::vec3(0,0,0), // and looks at the origin
	glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)

);
}
Camera::~Camera()
{

}