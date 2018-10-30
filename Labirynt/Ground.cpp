#include "Ground.h"
#include "Vertex.h"
#include "Macros.h"
#include <d3dx9.h>
#include <cmath>
#include <tchar.h>

Ground::Ground(IDirect3DDevice9 *pD3DDevice_, float groundSize)
	: numVertexGround(static_cast<int>(4.0f * 2.5f * groundSize * 2.5f * groundSize)), pD3DDevice(pD3DDevice_)
{
	pD3DDevice->CreateVertexBuffer(numVertexGround * sizeof(Vertex), 0, FVF_VERTEX, D3DPOOL_DEFAULT, &pVBground, NULL);
	D3DXCreateTextureFromFile(pD3DDevice, _T("Resources/grass.jpg"), &pTextureGrass);
	create(groundSize);
}

Ground::~Ground()
{
	SAFE_RELEASE(pVBground);
	SAFE_RELEASE(pTextureGrass);
}

void Ground::render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	pD3DDevice->SetTexture(0, pTextureGrass);
	pD3DDevice->SetStreamSource(0, pVBground, 0, sizeof(Vertex));

	for (unsigned int i = 0; i < numVertexGround; ++i)
	{
		pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 4*i, 2);
	}
}

void Ground::create(float groundSizeXZ) 
{
	const float from = -groundSizeXZ / 2.0f;
	const float to = groundSizeXZ / 2.0f;
	const float magicProportion = groundSizeXZ * 100.0f / 80.0f;
	const float quadSize = groundSizeXZ / magicProportion;
	float lowerValue = from;
	float greaterValue = to;
	unsigned int index = 0;

	Vertex* pVertices;

	pVBground->Lock(0, 0, (void**)&pVertices, 0);

	for (unsigned int i = 0; i < magicProportion; ++i)
	{
		for (unsigned int j = 0; j < magicProportion; ++j)
		{
			pVertices[index++] = Vertex(lowerValue, 0.0f, greaterValue, 0.0f, 0.0f);
			pVertices[index++] = Vertex(lowerValue, 0.0f, greaterValue - quadSize, 1.0f, 0.0f);
			pVertices[index++] = Vertex(lowerValue + quadSize, 0.0f, greaterValue - quadSize, 0.5f, 1.0f);
			pVertices[index++] = Vertex(lowerValue + quadSize, 0.0f, greaterValue, 1.0f, 0.0f);

			lowerValue += quadSize;
		}
		greaterValue -= quadSize;
		lowerValue = from;
	}

	pVBground->Unlock();
}
