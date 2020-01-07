#pragma once
#include"cObjectFactory.h"

class iPirate {
public:
	virtual ~iPirate() {};

	virtual void setGameObject(iObject* pTheGO) = 0;
	virtual iObject* getGameObject() = 0;

};