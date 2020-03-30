#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	Position = position;
	WorldUP = up;
	Yaw = yaw;
	Pitch = pitch;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
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
	return glm::lookAt(Position, Position + Front, UP);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = SPEED *deltaTime;
	if (direction == FORWARD)
		Position += Front*velocity;
	if (direction == BACKWARD)
		Position -= Front*velocity;
	if (direction == LEFT)
		Position -= Right*velocity;
	if (direction == RIGHT)
		Position += Right*velocity;
	if (direction == Camera_Movement::UP)
		Position += UP*velocity;
	if (direction == Camera_Movement::DOWN)
		Position -= UP*velocity;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch)
{
	Pitch += deltaY*SENSITIVITY;
	Yaw += deltaX*SENSITIVITY;
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
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Right = glm::normalize(glm::cross(Front, WorldUP));  
	UP = glm::normalize(glm::cross(Right, Front));
}
