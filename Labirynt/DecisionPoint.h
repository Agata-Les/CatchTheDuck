#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

enum MoveDecision
{
	FORWARD,
	LEFT,
	RIGHT,
};

class DecisionPoint
{
public:
	DecisionPoint(float x_, float z_, const std::vector<MoveDecision> moves_, D3DXVECTOR3 lookDirNormalized_);
	~DecisionPoint() = default;

	MoveDecision getRandomMove();
	bool isInDecisionPoint(const D3DXVECTOR3 &point);

	float decisionPointX = 0.0f;
	float decisionPointZ = 0.0f;
	const D3DXVECTOR3 lookDirNormalized;

#if _DEBUG
	const std::string debugSTR();
#endif
	
private:
	const float radius = 0.05f;
	const std::vector<MoveDecision> moves;
};
