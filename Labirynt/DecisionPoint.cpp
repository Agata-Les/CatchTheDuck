#include "DecisionPoint.h"

#include <utility>
#include <cstdlib>

DecisionPoint::DecisionPoint(const float x_,
							 const float z_,
							 std::vector<MoveDecision> moves_,
							 const D3DXVECTOR3 lookDirNormalized_) :
	decisionPointX(x_),
	decisionPointZ(z_),
	lookDirNormalized(lookDirNormalized_),
	moves(std::move(moves_))
{
}

MoveDecision DecisionPoint::getRandomMove() const
{
	const int index = std::rand() / (RAND_MAX / static_cast<unsigned short int>(moves.size()));
	return moves[index];
}

bool DecisionPoint::isInDecisionPoint(const D3DXVECTOR3& point) const
{
	if (decisionPointX - radius > point.x) return false;
	if (decisionPointX + radius < point.x) return false;
	if (decisionPointZ + radius < point.z) return false;
	if (decisionPointZ - radius > point.z) return false;

	return true;
}

#if _DEBUG
#include <sstream>

std::string DecisionPoint::debugSTR() const
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
