#pragma once
#include "GL_CALL.h"
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource = "";
};

class Shader {

private:
	unsigned int m_RendererID;
	ShaderProgramSource m_Source;
	std::string m_Filepath;
	std::unordered_map<string, int> m_UniformLocationCache;
	bool hasShader = false;
public:
	Shader();
	~Shader();

	void GenerateDefaultShader();
	void GenerateShader(std::string VertexAndFragmentFolderName);
	
	void SetUniform1f(const string& name, float value);
	void SetUniform1i(const string& name, int value);
	void SetUniform3f(const string& name, float v0, float v1, float v2);
	void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const string& name, const glm::mat4& mat);
	
	void Bind();
	void Unbind();
	void Cleanup();
private:
	int GetUniformLocation(const std::string name);
	string ParseShader(unsigned int type,const string& path);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader();
};