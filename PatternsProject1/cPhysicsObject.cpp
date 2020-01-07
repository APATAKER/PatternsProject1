#include"cPhysicsObject.h"

cPhysicsObject::cPhysicsObject()
{
	


	this->m_uniqueID = cPhysicsObject::next_uniqueID;
	cPhysicsObject::next_uniqueID++;


}

unsigned int cPhysicsObject::getUniqueID(void)
{
	return this->m_uniqueID;
}




unsigned int cPhysicsObject::next_uniqueID = 1000;
