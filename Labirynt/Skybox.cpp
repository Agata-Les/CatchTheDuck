#include "Skybox.h"
#include "Vertex.h"
#include "Macros.h"
#include <d3dx9.h>
#include <tchar.h>

Skybox::Skybox(IDirect3DDevice9 *pD3DDevice_) : pD3DDevice(pD3DDevice_)
{
	pD3DDevice->CreateVertexBuffer(numOfVertices * sizeof(Vertex), 0, FVF_VERTEX, D3DPOOL_DEFAULT, &pVB, NULL);
	pD3DDevice->CreateIndexBuffer(numOfIndices * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL);
	D3DXCreateTextureFromFile(pD3DDevice, _T("Resources/skybox.jpg"), &pTextureSkybox);
	create();
}

Skybox::~Skybox()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
	SAFE_RELEASE(pTextureSkybox);
}

void Skybox::render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pD3DDevice->SetFVF(FVF_VERTEX);

	pD3DDevice->SetTexture(0, pTextureSkybox);
	pD3DDevice->SetStreamSource(0, pVB, 0, sizeof(Vertex));
	pD3DDevice->SetIndices(pIB);

	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numOfVertices, 0, 12);
}

void Skybox::create()
{
	Vertex* pVertices;

	pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0] = Vertex(-skyBoxWidth, skyBoxWidth, -skyBoxWidth, 0.0f, 0.5f);
	pVertices[1] = Vertex(skyBoxWidth, skyBoxWidth, -skyBoxWidth, 0.75f, 0.5f);
	pVertices[2] = Vertex(-skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 0.0f, 1.0f);
	pVertices[3] = Vertex(skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 0.75f, 1.0f);
	pVertices[4] = Vertex(-skyBoxWidth, skyBoxWidth, skyBoxWidth, 0.25f, 0.5f);
	pVertices[5] = Vertex(skyBoxWidth, skyBoxWidth, skyBoxWidth, 0.50f, 0.5f);
	pVertices[6] = Vertex(-skyBoxWidth, -skyBoxWidth, skyBoxWidth, 0.25f, 1.0f);
	pVertices[7] = Vertex(skyBoxWidth, -skyBoxWidth, skyBoxWidth, 0.50f, 1.0f);
	pVertices[8] = Vertex(-skyBoxWidth, skyBoxWidth, -skyBoxWidth, 1.0f, 0.5f);
	pVertices[9] = Vertex(skyBoxWidth, skyBoxWidth, -skyBoxWidth, 0.75f, 0.5f);
	pVertices[10] = Vertex(-skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 1.00f, 1.0f);
	pVertices[11] = Vertex(skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 0.75f, 1.0f);

	pVertices[12] = Vertex(-skyBoxWidth, skyBoxWidth, skyBoxWidth, 0.25f, 0.5f);
	pVertices[13] = Vertex(skyBoxWidth, skyBoxWidth, skyBoxWidth, 0.5f, 0.5f);
	pVertices[14] = Vertex(-skyBoxWidth, skyBoxWidth, -skyBoxWidth, 0.25f, 0.0f);
	pVertices[15] = Vertex(skyBoxWidth, skyBoxWidth, -skyBoxWidth, 0.5f, 0.0f);

	pVertices[16] = Vertex(-skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 0.0f, 0.5f);
	pVertices[17] = Vertex(skyBoxWidth, -skyBoxWidth, -skyBoxWidth, 0.25f, 0.5f);
	pVertices[18] = Vertex(-skyBoxWidth, -skyBoxWidth, skyBoxWidth, 0.0f, 0.0f);
	pVertices[19] = Vertex(skyBoxWidth, -skyBoxWidth, skyBoxWidth, 0.25f, 0.0f); 

	pVB->Unlock();

	const unsigned short int indices[] =
	{
		8, 9, 10,
		10, 9, 11,
		4, 0, 6,
		6, 0, 2, 
		7, 5, 6,
		6, 5, 4,
		3, 1, 7,
		7, 1, 5,
		13, 12, 15,
		12, 14, 15,
		16, 17, 19,
		16, 19, 18,
	};

	void *pVoid;

	pIB->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	pIB->Unlock();
}
