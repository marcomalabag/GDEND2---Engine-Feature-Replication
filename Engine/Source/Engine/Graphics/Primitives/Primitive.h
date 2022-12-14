#pragma once
#include "../../../../Dependencies/tinyobj/tiny_obj_loader.h"

#include "Engine/Graphics/RenderData.h"
#include <fstream>
#include <sstream>

namespace Engine::Primitive
{
	//TODO: Add normals
	struct Vertex
	{
		Vector3Float Position;
		Vector2Float UV;
	};

	inline RenderData* Mesh(StringView filepath)
	{
		std::ifstream file = std::ifstream(filepath.data());

		std::string fileOutput;
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				fileOutput += line;
			}
			file.close();
		}
		else
		{
			return nullptr;
		}

		tinyobj::attrib_t attributes;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warning;
		std::string error;

		std::string cFilepath = filepath.data();
		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, cFilepath.c_str()))
		{
			Debug::Log("File cannot be loaded! {0}", filepath.data());
			return nullptr;
		}

		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		uint32_t currentIndex = 0;
		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				Vertex vertex;
				vertex.Position.x = attributes.vertices[3 * index.vertex_index + 0];
				vertex.Position.y = attributes.vertices[3 * index.vertex_index + 1];
				vertex.Position.z = attributes.vertices[3 * index.vertex_index + 2];

				vertex.UV.x = attributes.texcoords[2 * index.texcoord_index + 0];
				vertex.UV.y = 1.0f - attributes.texcoords[2 * index.texcoord_index + 1];
				vertices->push_back(vertex);

				indices->push_back(currentIndex);
				currentIndex++;
			}
		}

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* meshRenderData               = new RenderData();
		meshRenderData->Vertices                 = vertices->data();
		meshRenderData->VertexCount              = vertices->size();
		meshRenderData->VertexSize               = sizeof(Vertex);
		meshRenderData->VertexLayout             = layout->data();
		meshRenderData->VertexLayoutElementCount = layout->size();
		meshRenderData->Indices                  = indices->data();
		meshRenderData->IndexCount               = indices->size();
		meshRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return meshRenderData;
	}

	inline RenderData* Cube()
	{
		const Vector3Float positionList[] =
		{
			{Vector3Float(-0.5f, -0.5f, -0.5f)},
			{Vector3Float(-0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, -0.5f, -0.5f)},

			//BACK FACE
			{Vector3Float(0.5f, -0.5f, 0.5f)},
			{Vector3Float(0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, -0.5f, 0.5f)}
		};

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		List<Vertex>* vertices = new List<Vertex>{
			{positionList[0], uvList[1]},
			{positionList[1], uvList[0]},
			{positionList[2], uvList[2]},
			{positionList[3], uvList[3]},

			{positionList[4], uvList[1]},
			{positionList[5], uvList[0]},
			{positionList[6], uvList[2]},
			{positionList[7], uvList[3]},

			{positionList[1], uvList[1]},
			{positionList[6], uvList[0]},
			{positionList[5], uvList[2]},
			{positionList[2], uvList[3]},

			{positionList[7], uvList[1]},
			{positionList[0], uvList[0]},
			{positionList[3], uvList[2]},
			{positionList[4], uvList[3]},

			{positionList[3], uvList[1]},
			{positionList[2], uvList[0]},
			{positionList[5], uvList[2]},
			{positionList[4], uvList[3]},

			{positionList[7], uvList[1]},
			{positionList[6], uvList[0]},
			{positionList[1], uvList[2]},
			{positionList[0], uvList[3]}
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		List<uint32_t>* indices = new List<uint32_t>{
			//FRONT SIDE
			0, 1, 2,
			2, 3, 0,
			//BACK SIDE
			4, 5, 6,
			6, 7, 4,
			//TOP SIDE
			8, 9, 10,
			10, 11, 8,
			//BOTTOM SIDE
			12, 13, 14,
			14, 15, 12,
			//RIGHT SIDE
			16, 17, 18,
			18, 19, 16,
			//LEFT SIDE
			20, 21, 22,
			22, 23, 20
		};

		RenderData* cubeRenderData               = new RenderData();
		cubeRenderData->Vertices                 = vertices->data();
		cubeRenderData->VertexCount              = vertices->size();
		cubeRenderData->VertexSize               = sizeof(Vertex);
		cubeRenderData->VertexLayout             = layout->data();
		cubeRenderData->VertexLayoutElementCount = layout->size();
		cubeRenderData->Indices                  = indices->data();
		cubeRenderData->IndexCount               = indices->size();
		cubeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cubeRenderData;
	}

	inline RenderData* Plane()
	{
		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		List<Vertex>* vertices = new List<Vertex>{
			{Vector3Float{-0.5f, 0, -0.5f}, uvList[0]},
			{Vector3Float{-0.5f, 0, 0.5f}, uvList[1]},
			{Vector3Float{0.5f, 0.0f, 0.5f}, uvList[3]},
			{Vector3Float{0.5f, 0.0f, -0.5f}, uvList[2]},
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		List<uint32_t>* indices = new List<uint32_t>{
			0,
			1,
			2,
			2,
			3,
			0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices->data();
		planeRenderData->VertexCount              = vertices->size();
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout->data();
		planeRenderData->VertexLayoutElementCount = layout->size();
		planeRenderData->Indices                  = indices->data();
		planeRenderData->IndexCount               = indices->size();
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	inline RenderData* Frustum(float FOV, float windowHeight, float windowLength, float nearZ, float farZ)
	{
		float fovRadians = FOV / 180 * 3.14;
		float aspectRatio = ((float)windowLength / 2) / ((float)windowHeight / 2);
		
		float nearHeight = 2 * tan(fovRadians / 2) * nearZ;
		float farHeight = 2 * tan(fovRadians / 2) * farZ;
		float nearWidth = (nearHeight * aspectRatio);
		float farWidth = (farHeight * aspectRatio);

		
		float alpha = 0.5f;

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		List<Vertex>* vertices = new List<Vertex>{
			{Vector3Float((-nearWidth * 0.5), (nearHeight * 0.5), nearZ * 6), uvList[1]},
			{Vector3Float((nearWidth * 0.5), (nearHeight * 0.5), nearZ * 6), uvList[0]},
			{Vector3Float((nearWidth * 0.5), (-nearHeight * 0.5), nearZ * 6), uvList[2]},
			{Vector3Float(-(nearWidth * 0.5), (-nearHeight * 0.5), nearZ * 6), uvList[3]},
			{Vector3Float((-farWidth * 0.5), (farHeight * 0.5), farZ * 6), uvList[1]},
			{Vector3Float((farWidth * 0.5), (farHeight * 0.5), farZ * 6), uvList[0]},
			{Vector3Float((farWidth * 0.5), (-farHeight * 0.5), farZ * 6), uvList[2]},
			{Vector3Float(-(farWidth * 0.5), (-farHeight * 0.5), farZ * 6), uvList[3]}
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};




		List<uint32_t>* indices = new List<uint32_t>{
			//Near Plane
			0, 1, 2,
			0, 2, 3,
			//Far Plane
			4, 5, 6,
			4, 6, 7,
			//Left Plane
			0, 4, 7,
			0, 7, 3,
			//Right Plane
			1, 5, 6,
			1, 6, 2,
			//Top Plane
			0, 1, 4,
			1, 4, 5,
			//Bottom Plane
			2, 3, 6,
			3, 6, 7,
		};

		RenderData* FrustumRenderData = new RenderData();
		FrustumRenderData->Vertices = vertices->data();
		FrustumRenderData->VertexCount = vertices->size();
		FrustumRenderData->VertexSize = sizeof(Vertex);
		FrustumRenderData->VertexLayout = layout->data();
		FrustumRenderData->VertexLayoutElementCount = layout->size();
		FrustumRenderData->Indices = indices->data();
		FrustumRenderData->IndexCount = indices->size();
		FrustumRenderData->Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

		return FrustumRenderData;

	}

	inline RenderData* Sphere(float radius, int stackCount, int sectorCount)
	{
		float x, y, z, xy;
		float pi = 3.1415926;
		float sectorStep = 2 * pi / (float)sectorCount;
		float stackStep = pi / (float)stackCount;
		float sectorAngle, stackAngle;

		List<Vertex>* vertices =  new List<Vertex>{};
		List<uint32_t>* indices = new List<uint32_t>{};

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		for (int i = 0; i <= stackCount; i++)
		{
			stackAngle = pi / 2.0f - i * stackStep;
			xy = radius * cosf(stackAngle);
			y = radius * sinf(stackAngle);

			for (int j = 0; j <= sectorCount; j++)
			{
				sectorAngle = j * sectorStep;
				z = xy * cosf(sectorAngle);
				x = xy * sinf(sectorAngle);

				
				vertices->push_back({ Vector3Float(x, y, z), uvList[0] });
			}
		}

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		int k1, k2;

		for (int i = 0; i < stackCount; i++)
		{
			k1 = i * (sectorCount + 1);
			k2 = k1 + sectorCount + 1;

			for (int j = 0; j < sectorCount; j++)
			{
				if (i != 0)
				{
					indices->push_back(k1);
					indices->push_back(k1 + 1);
					indices->push_back(k2);
				}

				if (i != (stackCount - 1))
				{
					indices->push_back(k1 + 1);
					indices->push_back(k2 + 1);
					indices->push_back(k2);
				}

				k1++;
				k2++;
			}
		}

		RenderData* SphereRenderData = new RenderData();
		SphereRenderData->Vertices = vertices[0].data();
		SphereRenderData->VertexCount = vertices->size();
		SphereRenderData->VertexSize = sizeof(Vertex);
		SphereRenderData->VertexLayout = layout->data();
		SphereRenderData->VertexLayoutElementCount = layout->size();
		SphereRenderData->Indices = indices[0].data();
		SphereRenderData->IndexCount = indices->size();
		SphereRenderData->Topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return SphereRenderData;
	}
	inline RenderData* Cylinder(float radius, int sectorCount, float height)
	{
		float pi = 3.1415926f;
		float sectorStep = 2 * pi / (float)sectorCount;
		float sectorAngle;
		
		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};


		List<Vertex>* vertices = new List<Vertex>{};
		List<uint32_t>* indices = new List<uint32_t>{};
		List<Vector3Float>* CircleVertices = new List<Vector3Float>{};

		for (int i = 0; i <= sectorCount; i++)
		{
			sectorAngle = i * sectorStep;
			CircleVertices->push_back(Vector3Float(sinf(sectorAngle), 0.0f, cosf(sectorAngle)));
		}

		for (int i = 0; i < 2; i++)
		{
			float h = -height / 2.0f + i * height;
			int k = 0;
			for (int j = 0; j <= sectorCount; j++)
			{
				vertices->push_back({ Vector3Float(CircleVertices->at(k).x * radius,
					h, 
					CircleVertices->at(k).z * radius), uvList[0] });
				k++;
			}
		}

		int BaseCenterIndex = vertices->size();
		int TopCenterIndex = BaseCenterIndex + sectorCount + 1;

		for (int i = 0; i < 2; i++)
		{
			float h = -height / 2.0f + i * height;
			vertices->push_back({ Vector3Float(0.0f, h, 0.0f), uvList[0] });
			int k = 0;

			for (int j = 0; j < sectorCount; j++)
			{
				vertices->push_back({ Vector3Float(
					CircleVertices->at(k).x * radius, h, CircleVertices->at(k).z * radius), uvList[0]});
				k++;
			}
		}

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		int k1 = 0;
		int k2 = sectorCount + 1;

		for (int i = 0; i < sectorCount; i++)
		{
			indices->push_back(k1);
			indices->push_back(k1 + 1);
			indices->push_back(k2);

			indices->push_back(k2);
			indices->push_back(k1 + 1);
			indices->push_back(k2 + 1);

			k1++;
			k2++;
		}

		int k = BaseCenterIndex + 1;

		for (int i = 0; i < sectorCount; i++)
		{
			if (i < sectorCount - 1)
			{
				indices->push_back(BaseCenterIndex);
				indices->push_back(k + 1);
				indices->push_back(k);
			}
			else
			{
				indices->push_back(BaseCenterIndex);
				indices->push_back(BaseCenterIndex + 1);
				indices->push_back(k);
			}
			k++;
		}

		k = TopCenterIndex + 1;

		for (int i = 0; i < sectorCount; i++)
		{
			if (i < sectorCount - 1)
			{
				indices->push_back(TopCenterIndex);
				indices->push_back(k);
				indices->push_back(k + 1);
			}
			else
			{
				indices->push_back(TopCenterIndex);
				indices->push_back(k);
				indices->push_back(TopCenterIndex + 1);
			}
			k++;
		}

		RenderData* CylinderRenderData = new RenderData();
		CylinderRenderData->Vertices = vertices[0].data();
		CylinderRenderData->VertexCount = vertices->size();
		CylinderRenderData->VertexSize = sizeof(Vertex);
		CylinderRenderData->VertexLayout = layout->data();
		CylinderRenderData->VertexLayoutElementCount = layout->size();
		CylinderRenderData->Indices = indices[0].data();
		CylinderRenderData->IndexCount = indices->size();
		CylinderRenderData->Topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return CylinderRenderData;

	}

}
