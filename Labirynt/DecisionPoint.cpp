#include "DecisionPoint.h"
#include <utility>
#include <cstdlib>

DecisionPoint::DecisionPoint(float x_, float z_, const std::vector<MoveDecision> moves_, D3DXVECTOR3 lookDirNormalized_) :
	decisionPointX(x_),
	decisionPointZ(z_),
	moves(std::move(moves_)),
	lookDirNormalized(lookDirNormalized_)
{
}

MoveDecision DecisionPoint::getRandomMove()
{
	const int index = std::rand() / (RAND_MAX / static_cast<unsigned short int>(moves.size()));
	return moves[index];
}

bool DecisionPoint::isInDecisionPoint(const D3DXVECTOR3 &point)
{
	if (decisionPointX - radius > point.x) return false;
	if (decisionPointX + radius < point.x) return false;
	if (decisionPointZ + radius < point.z) return false;
	if (decisionPointZ - radius > point.z) return false;

	return true;
}

#if _DEBUG
#include <sstream>

const std::string DecisionPoint::debugSTR()
{
	std::stringstream ss;
	ss << "Decision Point x = " << decisionPointX << " z = " << decisionPointZ << " Moves = ";

	for (auto& item : moves)
	{
		ss << item << " ";
	}
	ss << std::endl;

	return ss.str();
}
#endif
