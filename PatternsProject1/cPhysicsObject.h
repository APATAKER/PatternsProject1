#ifndef _cPhysicsObject_HG_
#define _cPhysicsObject_HG_

#include <glm/glm.hpp>

#include"cGameObject.h"



class cPhysicsObject
{
	


public:
	cPhysicsObject();

	cGameObject* GameObj;

	

	unsigned int getUniqueID(void);

private:

	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;

};
#endif // !_cPhysicsObject_HG_

