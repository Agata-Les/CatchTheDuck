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
	DecisionPoint(const float x_,
				  const float z_,
				  std::vector<MoveDecision> moves_,
				  const D3DXVECTOR3 lookDirNormalized_);
	~DecisionPoint() = default;

	MoveDecision getRandomMove() const;
	bool isInDecisionPoint(const D3DXVECTOR3& point) const;

	const float decisionPointX;
	const float decisionPointZ;
	const D3DXVECTOR3 lookDirNormalized;

#if _DEBUG
	std::string debugSTR() const;
#endif
	
private:
	const float radius = 0.05f;
	const std::vector<MoveDecision> moves;
};
