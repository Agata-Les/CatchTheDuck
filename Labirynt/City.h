#pragma once

#include "Building.h"
#include "Ground.h"
#include "DecisionPoint.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <vector>
#include <memory>

class City
{
public:
	City(IDirect3DDevice9* pD3DDevice_, const std::vector<std::vector<float>>& cityMatrix_);
	~City() = default;

	void render() const;
	std::shared_ptr<DecisionPoint> getAIDecisionPoint_RANDOM();

	std::vector<std::shared_ptr<Building>> buildingsContainer;
	std::vector<std::shared_ptr<DecisionPoint>> decisionPointsContainer;
	
private:
	void loadCityMatrix();
	void construct();
	void constructDecisionPoints();
	std::vector<MoveDecision> getPossibleMoves(unsigned int i, unsigned int j) const;
	D3DXVECTOR3 getLookDirection(unsigned int i, unsigned int j) const;

	IDirect3DDevice9* pD3DDevice;

	unsigned int numberOfBuildingsInRow = 0;
	unsigned int numberOfRows = 0;
	const float buildingSize = 4.0f;
	const float buildingSpace = 3.0f;
	std::shared_ptr<Ground> ground = nullptr;
	const std::vector<std::vector<float>>& cityMatrix;
};
