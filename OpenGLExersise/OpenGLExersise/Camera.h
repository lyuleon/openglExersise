#ifndef CAMERA_H
#define CAMERA_H
#include <glm.hpp>
#include <gtc/matrix_transform.inl>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.04f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup);
	Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup);

	~Camera();

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 UP;
	glm::vec3 WorldUP;
	float Pitch, Yaw;

	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch = true);
	void UpdateCameraVectors();
};
#endif
