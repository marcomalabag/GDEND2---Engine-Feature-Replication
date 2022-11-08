#pragma once
#include <string_view>
#include <unordered_map>

#include "VertexShader.h"

class ShaderLibrary
{
public:
	static void init(size_t expectedShaderCount);

	static void release();

	template <typename T>
	static void registerShader(std::string_view filename);

	template <typename T>
	static T& getShader(std::string_view shaderName);

	ShaderLibrary(const ShaderLibrary&) = delete;

	ShaderLibrary& operator=(const ShaderLibrary&) = delete;

	ShaderLibrary(const ShaderLibrary&&) = delete;

	ShaderLibrary& operator=(const ShaderLibrary&&) = delete;
	
private:
	ShaderLibrary();

	~ShaderLibrary();

	static std::string getShaderNameFromFilename(std::string_view filename);

	static ShaderLibrary s_Instance;

	std::unordered_map<std::string, VertexShader*> m_VertexShaderMap{};

	std::unordered_map<std::string, PixelShader*> m_PixelShaderMap{};
};

template <typename T>
void ShaderLibrary::registerShader(std::string_view filename)
{
}

template <typename T>
T& ShaderLibrary::getShader(std::string_view shaderName)
{
}
