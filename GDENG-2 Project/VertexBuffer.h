#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>
#include <iostream>

class DeviceContext;

class VertexBuffer final
{
public:
	VertexBuffer(void* list_vertices,
	             UINT size_vertex,
	             UINT size_list,
	             void* shader_byte_code,
	             size_t size_byte_shader);

	~VertexBuffer();

public:
	ID3D11Buffer* getBuffer();

	ID3D11InputLayout* getLayout();

	UINT getSizeVertexBuffer();

	UINT getSizeVertexList();

private:
	UINT sizeVertexBuffer;

	UINT sizeVertexList;

private:
	ID3D11Buffer* buffer = nullptr;

	ID3D11InputLayout* layout = nullptr;

private:
	friend class DeviceContext;
};
