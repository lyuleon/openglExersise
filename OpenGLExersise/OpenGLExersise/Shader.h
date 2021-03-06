#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:
	unsigned int ID; //shader program ID
	std::string vertexString;
	std::string fragmentString;
	std::string geometryString;
	const char* vertexSource;
	const char* fragmentSource;
	const char* geometrySource;
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	~Shader();
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string& name, const float x, const float y, const float z) const;

	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string& name, const float* value) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setUniformBlock(const std::string &name, const int &value) const;

private:
	void checkCompileErrors(GLuint ID, std::string& type);
};

#endif
