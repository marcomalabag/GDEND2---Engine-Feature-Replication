#pragma once
#include <string_view>
#include <unordered_map>

#include "Debug.h"
#include "Utils.h"
#include "VertexShader.h"

class ShaderLibrary
{
public:
	static void init(size_t expectedShaderCount);

	static void release();

	template <typename T>
	static bool isShaderRegistered(std::string_view name);

	template <typename T>
	static void add(std::string_view filename);

	template <typename T>
	static T& getShader(std::string_view shaderName);

	ShaderLibrary(const ShaderLibrary&) = delete;

	ShaderLibrary& operator=(const ShaderLibrary&) = delete;

	ShaderLibrary(const ShaderLibrary&&) = delete;

	ShaderLibrary& operator=(const ShaderLibrary&&) = delete;

private:
	ShaderLibrary();

	~ShaderLibrary();

	constexpr const char* VERTEX_SHADER_ENTRY_POINT_NAME = "VSMain";

	constexpr const char* PIXEL_SHADER_ENTRY_POINT_NAME = "PSMain";

	static std::string getShaderNameFromFilename(std::string_view filename);

	static ShaderLibrary s_Instance;

	std::unordered_map<std::string, VertexShader*> m_VertexShaderMap{};

	std::unordered_map<std::string, PixelShader*> m_PixelShaderMap{};
};

//---------- IS SHADER REGISTERED
template <typename T>
bool ShaderLibrary::isShaderRegistered(std::string_view name)
{
	return false;
}

template <>
inline bool ShaderLibrary::isShaderRegistered<VertexShader>(const std::string_view name)
{
	return s_Instance.m_VertexShaderMap.contains(name.data());
}

template <>
inline bool ShaderLibrary::isShaderRegistered<PixelShader>(const std::string_view name)
{
	return s_Instance.m_PixelShaderMap.contains(name.data());
}

//---------- REGISTER SHADER
template <typename T>
void ShaderLibrary::add(const std::string_view filename)
{
}

template <>
inline void ShaderLibrary::add<VertexShader>(const std::string_view filename)
{
	const std::string& shaderName = getShaderNameFromFilename(filename.data());

	if (isShaderRegistered<VertexShader>(shaderName))
	{
		return;
	}

	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* blob      = nullptr;

	const std::wstring filenameWideStr = Utils::cstringToWString(filename.data());

	const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
	                                          nullptr,
	                                          nullptr,
	                                          VERTEX_SHADER_ENTRY_POINT_NAME,
	                                          "vs_5_0",
	                                          0,
	                                          0,
	                                          &blob,
	                                          &errorBlob);
	if (!SUCCEEDED(result))
	{
		if (errorBlob)
		{
			std::string errorString = "Failed to compile Vertex shader: ";
			errorString += static_cast<char*>(errorBlob->GetBufferPointer());
			errorString += "\n";
			Debug::Assert(errorBlob == nullptr, errorString);
			errorBlob->Release();
		}
	}

	s_Instance.m_VertexShaderMap[shaderName] = new VertexShader(blob);
}

template <>
inline void ShaderLibrary::add<PixelShader>(const std::string_view filename)
{
	const std::string& shaderName = getShaderNameFromFilename(filename.data());

	if (isShaderRegistered<PixelShader>(shaderName))
	{
		return;
	}

	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* blob      = nullptr;

	const std::wstring filenameWideStr = Utils::cstringToWString(filename.data());

	const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
	                                          nullptr,
	                                          nullptr,
	                                          PIXEL_SHADER_ENTRY_POINT_NAME,
	                                          "ps_5_0",
	                                          0,
	                                          0,
	                                          &blob,
	                                          &errorBlob);

	if (!SUCCEEDED(result))
	{
		if (errorBlob)
		{
			std::string errorString = "Failed to compile Pixel shader: ";
			errorString += static_cast<char*>(errorBlob->GetBufferPointer());
			errorString += "\n";
			Debug::Assert(errorBlob == nullptr, errorString);
			errorBlob->Release();
		}
	}

	s_Instance.m_PixelShaderMap[shaderName] = new PixelShader(blob);
}

//---------- GET SHADER
template <typename T>
T& ShaderLibrary::getShader(const std::string_view name)
{
	return T();
}

template <>
inline VertexShader& ShaderLibrary::getShader<VertexShader>(const std::string_view name)
{
	const bool isFound = isShaderRegistered<VertexShader>(name);
	Debug::Assert(isFound, "Vertex Shader is not registered!");
	const char* shaderName = name.data();
	return *s_Instance.m_VertexShaderMap[shaderName];
}

template <>
inline PixelShader& ShaderLibrary::getShader<PixelShader>(const std::string_view name)
{
	const bool isFound = isShaderRegistered<PixelShader>(name);
	Debug::Assert(isFound, "Pixel Shader is not registered!");
	const char* shaderName = name.data();
	return *s_Instance.m_PixelShaderMap[shaderName];
}
