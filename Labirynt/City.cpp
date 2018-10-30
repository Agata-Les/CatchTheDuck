#include "City.h"
#include <algorithm>
#include <sstream>

City::City(IDirect3DDevice9 *pD3DDevice_, const std::vector<std::vector<float>> &cityMatrix_)
	: pD3DDevice(pD3DDevice_), cityMatrix(cityMatrix_)
{
	loadCityMatrix();
	construct();
	constructDecisionPoints();
}

void City::render()
{
	ground->render();

	for (auto& building : buildingsContainer)
	{
		building->render();
	}
}

std::shared_ptr<DecisionPoint> City::getAIDecisionPoint_RANDOM()
{
	const float xSize = numberOfBuildingsInRow * (buildingSize + buildingSpace) + buildingSpace;
	const float zSize = numberOfRows * (buildingSize + buildingSpace) + buildingSpace;
	std::shared_ptr<DecisionPoint> dp = nullptr;

	do {
		unsigned int index = std::rand() / (RAND_MAX / decisionPointsContainer.size());
		dp = decisionPointsContainer[index];

#if _DEBUG
		std::stringstream ss;
		ss << "Spawning bird at point x = " << dp->decisionPointX << " y = " << dp->decisionPointZ << std::endl;
		OutputDebugStringA(ss.str().c_str());
#endif

	} while (dp->decisionPointX <= -xSize / 2.0f ||
			 dp->decisionPointX >= xSize / 2.0f ||
		  	 dp->decisionPointZ <= -zSize / 2.0f ||
			 dp->decisionPointZ >= zSize / 2.0f);

	return dp;
}

void City::loadCityMatrix()
{
	numberOfBuildingsInRow = cityMatrix[0].size();
	numberOfRows = cityMatrix.size();
}

void City::construct()
{
	const float xSize = numberOfBuildingsInRow * (buildingSize + buildingSpace) + buildingSpace;
	const float zSize = numberOfRows * (buildingSize + buildingSpace) + buildingSpace;
	float x = 0.0f;
	float z = zSize / 2.0f - buildingSpace - (buildingSize / 2.0f);

	for (unsigned int i = 0; i < numberOfRows; ++i)
	{
		x = -xSize / 2.0f + buildingSpace + (buildingSize / 2.0f);

		for (unsigned int j = 0; j < numberOfBuildingsInRow; ++j)
		{
			const float buildingHeight = cityMatrix[i][j];

			if (buildingHeight != 0.0f)
			{
				buildingsContainer.push_back(std::make_shared<Building>(pD3DDevice, D3DXVECTOR2(x, z), buildingHeight));
			}
			x = x + buildingSize + buildingSpace;
		}
		z = z - ( buildingSize + buildingSpace );
	}

	ground = std::make_shared<Ground>(pD3DDevice, std::fmax(xSize, zSize));
}

void City::constructDecisionPoints()
{
	const float xSize = numberOfBuildingsInRow * (buildingSize + buildingSpace) + buildingSpace;
	const float zSize = numberOfRows * (buildingSize + buildingSpace) + buildingSpace;
	float x;
	float z = zSize / 2.0f - 1.5f;

	for (unsigned int i = 0; i < numberOfRows * 2 + 1; ++i)
	{
		if(i%2 == 0) x = -xSize / 2.0f + 5.0f;
		else x = -xSize / 2.0f + 1.5f;

		for (unsigned int j = 0; j < numberOfBuildingsInRow + 1; ++j)
		{
			decisionPointsContainer.push_back(
				std::make_shared<DecisionPoint>(x, z, getPossibleMoves(i, j), getLookDirection(i, j))
			);
			x = x + buildingSize + buildingSpace;
		}
		z = z - 3.5f;
	}
}

std::vector<MoveDecision> City::getPossibleMoves(unsigned int i, unsigned int j)
{
	const std::vector<MoveDecision> movesForwardLeft{ MoveDecision::FORWARD, MoveDecision::LEFT };
	const std::vector<MoveDecision> movesAnyDirection{ MoveDecision::FORWARD, MoveDecision::LEFT, MoveDecision::RIGHT };
	const std::vector<MoveDecision> movesLeft{ MoveDecision::LEFT };

	bool isFirstRow = (i == 0);
	bool isSecondRow = (i == 1);
	bool isPenultimateRow = (i == numberOfRows * 2 - 1);
	bool isLastRow = (i == numberOfRows * 2);
	bool isEvenRow = (i % 2 == 0);
	bool isOddRow = (i % 2 != 0);

	bool isFirstPointInRow = (j == 0);
	bool isLastInOddRow = (j == numberOfBuildingsInRow);
	bool isLastInEvenRow = (j == numberOfBuildingsInRow - 1);

	if (isFirstRow)
	{
		if (isFirstPointInRow) return movesLeft;
		else return movesForwardLeft;
	}

	if (isSecondRow)
	{
		if (isFirstPointInRow) return movesForwardLeft;
		else return movesLeft;
	}

	if (isPenultimateRow)
	{
		if (isLastInOddRow) return movesForwardLeft;
		else return movesLeft;
	}

	if (isLastRow)
	{
		if (isLastInEvenRow) return movesLeft;
		else return movesForwardLeft;
	}

	if (isEvenRow)
	{
		if (isFirstPointInRow || isLastInEvenRow) return movesLeft;
		else return movesAnyDirection;
	}

	if (isOddRow)
	{
		if (isFirstPointInRow || isLastInOddRow) return movesForwardLeft;
		else return movesAnyDirection;
	}

#if _DEBUG
	OutputDebugStringA("Something went wrong with City::getPossibleMoves\n");
#endif

	return movesLeft;
}

D3DXVECTOR3 City::getLookDirection(unsigned int i, unsigned int j)
{
	D3DXVECTOR3 directionLeft(-1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 directionRight(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 directionUp(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 directionDown(0.0f, 0.0f, -1.0f);

	bool isFirstRow = (i == 0);
	bool isSecondRow = (i == 1);
	bool isPenultimateRow = (i == numberOfRows * 2 - 1);
	bool isLastRow = (i == numberOfRows * 2);
	bool isEvenRow = (i % 2 == 0);
	bool isOddRow = (i % 2 != 0);
	bool isFirstPointInRow = (j == 0);

	if (isFirstRow)
	{
		return directionLeft;
	}

	if (isSecondRow)
	{
		if (isFirstPointInRow) return directionDown;
		else return directionUp;
	}

	if (isPenultimateRow)
	{
		if (isFirstPointInRow) return directionDown;
		else return directionUp;
	}

	if (isLastRow)
	{
		return directionRight;
	}

	if (isEvenRow)
	{
		return directionRight;
	}

	if (isOddRow)
	{
		if (isFirstPointInRow) return directionDown;
		else return directionUp;
	}

#if _DEBUG
	OutputDebugStringA("Something went wrong with City::getLookDirection\n");
#endif

	return directionLeft;
}
