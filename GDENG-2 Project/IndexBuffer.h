#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include <iostream>
#include "DeviceContext.h"

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list);
	~IndexBuffer();

	UINT getSizeIndexList();

private:
	UINT sizeList;
	ID3D11Buffer* buffer = nullptr;

	friend class DeviceContext;


};

