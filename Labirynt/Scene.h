#pragma once

#include "City.h"
#include "Bird.h"
#include "Crosshair.h"
#include "Bullet.h"
#include "Skybox.h"
#include "UI.h"
#include <d3d9.h>
#include <string>
#include <memory>

class Scene
{
public:
	Scene(IDirect3DDevice9 * pD3DDevice_);
	~Scene() = default;

	void render();
	void tick(const float deltaTime);
	bool isCollision(const D3DXVECTOR3 &point);
	void spawnBullet();
	void spawnBird();
	bool isBirdHit(const D3DXVECTOR3 &previousPoint, const D3DXVECTOR3 &point);

	std::unique_ptr<City> city;
	std::unique_ptr<Bird> bird;
	std::unique_ptr<Crosshair> crossHair;
	std::unique_ptr<Bullet> bullet;
	std::unique_ptr<UI> ui;
	std::unique_ptr<Skybox> skyBox;

private:
	void setScene();
	void loadCityMatrix(const std::string &fileName);

	IDirect3DDevice9 *pD3DDevice;
	std::vector<std::vector<float>> cityMatrix;
};
