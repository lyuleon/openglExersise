#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	Position = position;
	WorldUP = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup)
{
	this->Position = _position;
	this->WorldUP = worldup;
	this->Front = glm::normalize(_target - _position);
	this->Right = glm::normalize(glm::cross(this->Front, worldup));
	this->UP = glm::normalize(glm::cross(this->Front, this->Right));
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
	return glm::lookAt(Position, Position + Front, WorldUP);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = SPEED *deltaTime;
	if (direction == FORWARD)
		Position += Front*velocity;
	if (direction == BACKWARD)
		Position -= Front*velocity;
	if (direction == LEFT)
		Position += Right*velocity;
	if (direction == RIGHT)
		Position -= Right*velocity;
	if (direction == Camera_Movement::UP)
		Position += UP*velocity;
	if (direction == Camera_Movement::DOWN)
		Position -= UP*velocity;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch)
{
	Pitch += deltaY*SENSITIVITY;
	Yaw += -deltaX*SENSITIVITY;
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(WorldUP, Front));
	UP = glm::normalize(glm::cross(Front, Right));
}
