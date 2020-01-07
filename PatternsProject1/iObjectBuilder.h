#pragma once
#include"cLeaderPirate.h"
#include"cMeleePirate.h"
#include"cPirate.h"
#include"cRangedPirate.h"

class iObjectBuilder
{
public:
	virtual ~iObjectBuilder() {};

	virtual void SetLeaderPirate(cLeaderPirate* pPirateLeader) = 0;
	virtual void SetMeleePirate(cMeleePirate* pPirateMelee) = 0;
	virtual void SetPirate(cPirate* pPirate) = 0;
	virtual void SetRangedPirate(cRangedPirate* pPirateRanged) = 0;

};