#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <memory>

class Loader
{
public:
	~Loader();
	static std::shared_ptr<Loader> getInstance();
	void load(IDirect3DDevice9* pD3DDevice);

	ID3DXMesh* bulletMesh = nullptr;
	IDirect3DTexture9* pTextureBullet = nullptr;
	DWORD bulletNumMaterials = 0;

private:
	Loader() = default;
	static std::shared_ptr<Loader> instance;
};
