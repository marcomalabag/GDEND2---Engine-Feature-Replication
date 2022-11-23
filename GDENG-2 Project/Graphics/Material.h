#pragma once
#include "PixelShader.h"
#include "VertexShader.h"

// Material
//	Shader
//		VertexShader
//		PixelShader
//	ShaderData

// If material contains shader data, what about model view proj
struct Material
{
	VertexShader* VertexShaderRef;
	PixelShader* PixelShaderRef;
};