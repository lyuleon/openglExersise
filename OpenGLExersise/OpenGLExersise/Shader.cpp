#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) :Shader(vertexPath, fragmentPath, NULL) {}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::ifstream geometryFile;
	std::stringstream vertexSStream, fragmentSStream, geomeStream;
	std::string vertexSDName = "VERTEXSHADER";
	std::string fragmentSDName = "FRAGMENTSHADER";
	std::string geometrySDName = "GEOMETRYSHADER";
	std::string programSDName = "PROGRAM";

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	if (geometryPath != NULL)
	{
		geometryFile.open(geometryPath);
	}

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw std::exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexFile.close();
		fragmentFile.close();

		if (geometryPath != NULL && geometryFile.is_open())
		{
			geomeStream << geometryFile.rdbuf();
			geometryString = geomeStream.str();
			geometryFile.close();
		}
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

	vertexSource = vertexString.c_str();
	fragmentSource = fragmentString.c_str();
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(vertex);
	glCompileShader(fragment);
	checkCompileErrors(vertex, vertexSDName);
	checkCompileErrors(fragment, fragmentSDName);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, programSDName);
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	if (geometryPath != NULL)
	{
		geometrySource = geometryString.c_str();
		unsigned int geometry;
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &geometrySource, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, geometrySDName);
		glAttachShader(ID, geometry);
		glLinkProgram(ID);
		checkCompileErrors(ID, geometrySDName);
		glDeleteShader(geometry);
	}
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const float* value) const
{
	unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(*value)));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformBlock(const std::string& name, const int& value) const
{
	unsigned int uniformIndex = glGetUniformBlockIndex(ID, name.c_str());
	glUniformBlockBinding(ID, uniformIndex, value);
}

void Shader::setVec3(const std::string& name, const float x, const float y, const float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint ID, std::string& type)
{
	GLint success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, infoLog);
			std::cout << "ERROR:SHADER_COMPILE_ERROR OF type:" << type << "\n" << infoLog << "\n--------------------------------" << std::endl;
		}

	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 1024, NULL, infoLog);
			std::cout << "ERROR:PROGRAM_LINKING_ERROR OF type:" << type << "\n" << infoLog << "\n--------------------------------" << std::endl;
		}
	}
}
