#include "ShaderLibrary.h"

ShaderLibrary ShaderLibrary::s_Instance = ShaderLibrary();

void ShaderLibrary::init(const size_t expectedShaderCount)
{
	s_Instance.m_VertexShaderMap.reserve(expectedShaderCount);
	s_Instance.m_PixelShaderMap.reserve(expectedShaderCount);
}

void ShaderLibrary::release()
{
	s_Instance.m_VertexShaderMap.clear();
	s_Instance.m_PixelShaderMap.clear();
}

ShaderLibrary::ShaderLibrary() = default;

ShaderLibrary::~ShaderLibrary() = default;

std::string ShaderLibrary::getShaderNameFromFilename(const std::string_view filename)
{
	std::string result = filename.data();

	size_t finalBackslashPos = result.find_last_of(L'/');

	if (finalBackslashPos == std::string::npos)
		finalBackslashPos = 0ULL;
	else
		finalBackslashPos += 1;

	const size_t startOfExtensionPos = result.find(L'.');

	std::string shaderName = result.substr(finalBackslashPos,
										   startOfExtensionPos - finalBackslashPos);
	return shaderName;
}

