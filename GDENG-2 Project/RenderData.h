#pragma once
#include <d3d11.h>

struct RenderData
{
	// Vertices
	void* vertices;

	size_t vertexCount;

	size_t vertexSize;

	// Vertex Layout
	D3D11_INPUT_ELEMENT_DESC* vertexLayout;

	size_t vertexLayoutElementCount;

	// Indices
	unsigned int* indices;

	size_t indexCount;

	// Topology
	D3D11_PRIMITIVE_TOPOLOGY topology;
};
