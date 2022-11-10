#pragma once
#include <d3d11.h>

struct RenderData
{
	// Vertices
	void* Vertices;

	unsigned int VertexCount;

	size_t VertexSize;

	// Vertex Layout
	D3D11_INPUT_ELEMENT_DESC* VertexLayout;

	unsigned int VertexLayoutElementCount;

	// Indices
	unsigned int* Indices;

	unsigned int IndexCount;

	// Topology
	D3D11_PRIMITIVE_TOPOLOGY Topology;
};
