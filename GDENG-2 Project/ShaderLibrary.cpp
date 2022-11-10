#include "ShaderLibrary.h"

ShaderLibrary ShaderLibrary::instance = ShaderLibrary();

void ShaderLibrary::init(const size_t expectedShaderCount)
{
	instance.vertexShaderMap.reserve(expectedShaderCount);
	instance.pixelShaderMap.reserve(expectedShaderCount);
}

void ShaderLibrary::release()
{
	instance.vertexShaderMap.clear();
	instance.pixelShaderMap.clear();
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

