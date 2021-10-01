#include "Shader.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"


namespace fs = std::filesystem;
Shader::Shader()
	:m_Filepath("Resources/Shaders/Basic Shader")
{
	
}

Shader::~Shader()
{
}



void Shader::GenerateDefaultShader()
{
	
	if (fs::is_directory(m_Filepath)) {
		for (auto& entry : fs::directory_iterator(m_Filepath)) {
			if (entry.path().filename().string() == "shader.vert") {
				m_Source.VertexSource = ParseShader(GL_VERTEX_SHADER, m_Filepath + '/' + entry.path().filename().string());

			}
			if (entry.path().filename().string() == "shader.frag") {
				m_Source.FragmentSource = ParseShader(GL_FRAGMENT_SHADER, m_Filepath + '/' + entry.path().filename().string());
			}
			if (entry.path().filename().string() == "shader.geom") {
				m_Source.GeometrySource = ParseShader(GL_GEOMETRY_SHADER, m_Filepath + '/' + entry.path().filename().string());

			}
			if (entry.path().filename().string() == "shader.comp") {
				m_Source.ComputeSource = ParseShader(GL_COMPUTE_SHADER, m_Filepath + '/' + entry.path().filename().string());
			}
		}


		m_RendererID = CreateShader();
		hasShader = true;
	}
}

void Shader::GenerateShader(std::string VertexAndFragmentFolderName)
{
	if (hasShader) {
		this->Cleanup();
	}
	
	std::string mainPath = "Resources/Shaders/" + VertexAndFragmentFolderName;
	if (fs::is_directory(mainPath)) {
		for (auto& entry : fs::directory_iterator(mainPath)) {
			if (entry.path().filename().string() == "shader.vert") {
				m_Source.VertexSource = ParseShader(GL_VERTEX_SHADER, mainPath + '/' + entry.path().filename().string());

			}
			if (entry.path().filename().string() == "shader.frag") {
				m_Source.FragmentSource = ParseShader(GL_FRAGMENT_SHADER, mainPath + '/' + entry.path().filename().string());
			}
			if (entry.path().filename().string() == "shader.geom") {
				m_Source.GeometrySource = ParseShader(GL_GEOMETRY_SHADER, mainPath + '/' + entry.path().filename().string());
			}
			if (entry.path().filename().string() == "shader.comp") {
				m_Source.ComputeSource = ParseShader(GL_COMPUTE_SHADER, mainPath + '/' + entry.path().filename().string());
			}
		}
		m_Filepath = mainPath;
		m_RendererID = CreateShader();
		hasShader = true;
		
	}
	else {
		cout << "couldn't find shader path at " << mainPath << " .Please try again." <<endl;
		__debugbreak();
	}

}

void Shader::SetUniform1f(const string& name, float value)
{
	GL_CALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const string& name, int value)
{
	GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const string& name, float v0, float v1, float v2)
{
	GL_CALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3f(const string& name, Vector3f vec)
{
	this->SetUniform3f(name, vec.x, vec.y, vec.z);
}

void Shader::Bind()
{
	
	GL_CALL(glUseProgram(m_RendererID));
	
	
}

void Shader::Unbind()
{
	GL_CALL(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	else {
		m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
		if (m_UniformLocationCache[name] == -1) {
			cout << "Warning: uniform '" << name << "' doesn't exist!" << endl;
		}
		return m_UniformLocationCache[name];
	}

}

string Shader::ParseShader(unsigned int type,const std::string& path)
{
	std::stringstream r_final;
	
	std::string s;
	std::fstream stream(path);
	if (stream.is_open()) {
		while (getline(stream, s)) {
			r_final << s << endl;
		}
	}

	else {
		switch (type) {
		case GL_VERTEX_SHADER:
			cout << "couldn't parse Vertex Shader. Try Again." << endl;
			break;
		case GL_FRAGMENT_SHADER:
			cout << "couldn't parse Fragment Shader. Try Again" << endl;
			break;
		case GL_GEOMETRY_SHADER:
			cout << "couldn't parse Geometry Shader. Try Again" << endl;
			break;
		case GL_COMPUTE_SHADER:
			cout << "couldn't parse Compute Shader. Try Again" << endl;
		}
	}
	return r_final.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, NULL));
	GL_CALL(glCompileShader(id));

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char message[512];

		glGetShaderInfoLog(id, length, &length, message);
		switch (type) {
		case GL_VERTEX_SHADER:
			cout << "Failed to compile vertex shader!" << endl;
			break;
		case GL_FRAGMENT_SHADER:
			cout << "Failed to compile fragment shader!" << endl;
			break;
		case GL_GEOMETRY_SHADER:
			cout << "Failed to compile geomtry shader!" << endl;
			break;
		case GL_COMPUTE_SHADER:
			cout << "Failed to compile compute shader!" << endl;
		}
		cout << message << endl;
		
		glDeleteShader(id);
		return 0;
	}


	return id;

}

unsigned int Shader::CreateShader()
{
	unsigned int program = glCreateProgram();
	if (m_Source.VertexSource != "") {
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, m_Source.VertexSource);
		GL_CALL(glAttachShader(program, vs));
	}
	if (m_Source.FragmentSource != "") {
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, m_Source.FragmentSource);
		GL_CALL(glAttachShader(program, fs));
	}
	if (m_Source.GeometrySource != "") {
		unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, m_Source.GeometrySource);
		GL_CALL(glAttachShader(program, gs));
	}
	if (m_Source.ComputeSource != "") {
		unsigned int cs = CompileShader(GL_COMPUTE_SHADER, m_Source.ComputeSource);
		GL_CALL(glAttachShader(program, cs));
	}
	

	

	GLint numberOfShadersAttached;
	GL_CALL(glGetProgramiv(program, GL_ATTACHED_SHADERS, &numberOfShadersAttached));

	cout << "Number of Shaders Attached: " << numberOfShadersAttached << endl;

	GL_CALL(glLinkProgram(program));

	GLint linkStatus;

	GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));

	if (linkStatus != GL_TRUE) {

		GLint maxLength;
		GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));
		char errorMsg[512];

		GL_CALL(glGetProgramInfoLog(program, maxLength, &maxLength, errorMsg));

		cout << errorMsg << endl;

		__debugbreak();
	}

	GL_CALL(glValidateProgram(program));

	GLint success;
	GL_CALL(glGetProgramiv(program, GL_VALIDATE_STATUS, &success));
	if (success != GL_TRUE) {

		GLint maxLength;
		GL_CALL(glGetProgramiv(program,GL_INFO_LOG_LENGTH, &maxLength));
		char errorMsg[512];
		
		GL_CALL(glGetProgramInfoLog(program, maxLength, &maxLength, errorMsg));

		cout << errorMsg << endl;

		__debugbreak();
	}
	
	

	return program;
}

void Shader::Cleanup()
{
	GL_CALL(glDeleteProgram(m_RendererID));
}

void Shader::SetUniform4f(const string& name, float v0, float v1, float v2, float v3)
{
	GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	
}

void Shader::SetUniformMat4f(const string& name, const glm::mat4& mat)
{
	GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}