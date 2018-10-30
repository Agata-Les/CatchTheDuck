#include "Scene.h"
#include "Vertex.h"
#include "Game.h"
#include <tchar.h>
#include <d3dx9.h>
#include <fstream>
#include <sstream>
#include <cctype>

Scene::Scene(IDirect3DDevice9 * pD3DDevice_) : pD3DDevice(pD3DDevice_)
{
	setScene();
	loadCityMatrix("Resources/city.txt");
	city = std::make_unique<City>(pD3DDevice, cityMatrix);
	bird = std::make_unique<Bird>(pD3DDevice, D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 5.0f, 0.0f), city->decisionPointsContainer);
	crossHair = std::make_unique<Crosshair>(pD3DDevice);
	ui = std::make_unique<UI>(pD3DDevice);
	skyBox = std::make_unique<Skybox>(pD3DDevice);
}

void Scene::render()
{
	D3DXMATRIXA16 matView;
	D3DXVECTOR3 vEyePt = Game::getInstance()->player->position;
	D3DXVECTOR3 vLookatPt = Game::getInstance()->player->lookAt;
	D3DXVECTOR3 vUpVec = Game::getInstance()->player->upAxis;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	city->render();
	if (bird) bird->render();
	if (bullet) bullet->render();
	skyBox->render();
	ui->render();
	crossHair->render();
}

void Scene::tick(const float deltaTime)
{
	if (bird) bird->tick(deltaTime);
	if (bullet) bullet->tick(deltaTime);
}

bool Scene::isCollision(const D3DXVECTOR3 &point)
{
	for (auto& building : city->buildingsContainer)
	{
		if (building->isColliding(point)) return true;
	}
	return false;
}

void Scene::spawnBullet()
{
	bullet = std::make_unique<Bullet>(
		pD3DDevice,
		Game::getInstance()->player->position,
		Game::getInstance()->player->lookDirNormalized,
		Game::getInstance()->player->upAxis);
}

void Scene::spawnBird()
{
	std::shared_ptr<DecisionPoint> dp = city->getAIDecisionPoint_RANDOM();
	D3DXVECTOR3 position(dp->decisionPointX, 5.0f, dp->decisionPointZ);
	D3DXVECTOR3 lookAt = position + dp->lookDirNormalized;

	bird = std::make_unique<Bird>(pD3DDevice, position, lookAt, city->decisionPointsContainer);
}

bool Scene::isBirdHit(const D3DXVECTOR3 &previousPoint, const D3DXVECTOR3 &point)
{
	if (!bird) return false;

	const unsigned int numberOfSections = 50;
	const float h = 1.0f / numberOfSections;
	const float i = point.x - previousPoint.x;
	const float r = point.y - previousPoint.y;
	const float e = point.z - previousPoint.z;

	const float m = 0.0f;
	            e;

	for (unsigned int j = 0; j < numberOfSections; ++j)
	{
		float x = previousPoint.x + i * h * j;
		float y = previousPoint.y + r * h * j;
		float z = previousPoint.z + e * h * j;

		if (bird->isColliding(D3DXVECTOR3(x, y, z))) return true;
	}
	return false;
}

void Scene::setScene()
{
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void Scene::loadCityMatrix(const std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (!file.good())
	{
		MessageBox(Game::getInstance()->window->hWnd, _T("Could not open the file city.txt"), _T("Error"), MB_OK);
		PostQuitMessage(0);
		return;
	}

	std::string line;
	std::string singleNumber;
	
	while (std::getline(file, line))
	{
		std::vector<float> singleRow;

		if (!std::isdigit(line[0])) continue;

		for (unsigned int i = 0; i < line.size(); ++i)
		{
			if (std::isdigit(line[i]) || line[i] == '.')
			{
				singleNumber += line[i];
			}

			else if (!singleNumber.empty())
			{
				singleRow.push_back(std::stof(singleNumber));
				singleNumber.clear();
			}
		}
		singleRow.push_back(std::stof(singleNumber));
		cityMatrix.push_back(singleRow);
		singleNumber.clear();
	}
}
