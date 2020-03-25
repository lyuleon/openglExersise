#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	Position = position;
	WorldUP = up;
	Yaw = yaw;
	Pitch = pitch;
	Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	UpdateCameraVectors();
}

Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup)
{
	this->Position = _position;
	this->WorldUP = worldup;
	this->Forward = glm::normalize(_target - _position);
	this->Right = glm::normalize(glm::cross(this->Forward, worldup));
	this->UP = glm::normalize(glm::cross(this->Forward, this->Right));
	this->Yaw = YAW;
}

Camera::Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup)
{
	this->Position = _position;
	this->WorldUP = worldup;
	this->Pitch = pitch;
	this->Yaw = yaw;
	UpdateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUP);
	/*glm::mat4 mat1 = glm::mat4(glm::vec4(Right, 0), glm::vec4(UP, 0), glm::vec4(Forward, 0), glm::vec4(glm::vec3(0), 1));
	glm::mat4 mat2 = glm::translate(glm::mat4(1), glm::vec3(-Position.x, -Position.y, -Position.z));
	return mat1*mat2;*/
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = SPEED *deltaTime;
	if (direction == FORWARD)
		Position += Forward*velocity;
	if (direction == BACKWARD)
		Position -= Forward*velocity;
	if (direction == LEFT)
		Position -= Right*velocity;
	if (direction == RIGHT)
		Position += Right*velocity;
	if(direction == Camera_Movement::UP)
		Position -= UP*velocity;
	if(direction == Camera_Movement::DOWN)
		Position += UP*velocity;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch += deltaY*SENSITIVITY;
	Yaw += deltaX*SENSITIVITY;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	this->Forward.x = glm::cos(Pitch)*glm::cos(Yaw);
	this->Forward.y = glm::sin(Pitch);
	this->Forward.z = glm::cos(Pitch)*glm::sin(Yaw);
	this->Right = glm::normalize(glm::cross(this->Forward, WorldUP));
	this->UP = glm::normalize(glm::cross(this->Forward, this->Right));
}
