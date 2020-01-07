#include"cGameObject.h"

cGameObject::cGameObject()
{
	this->pushTOVecOrNot = true;

	this->scale = 0.0f;

	this->isVisible = true;

	this->isWireframe = false;
	this->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	this->inverseMass = 0.0f;	// Infinite mass
	this->physicsShapeType = UNKNOWN;
	this->pirateType = NONE;

	this->matWorld = glm::mat4(1.0f);

	
	this->m_uniqueID = cGameObject::next_uniqueID;
	cGameObject::next_uniqueID++;

	this->disableDepthBufferTest = false;
	this->disableDepthBufferWrite = false;


	return;
}


unsigned int cGameObject::getUniqueID(void)
{
	return this->m_uniqueID;
}

 


unsigned int cGameObject::next_uniqueID = 1000;	


//std::vector<cGameObject*> g_vec_pGameObjects;

bool applyPirateAttributestoModel(std::vector<cGameObject*>& g_vec_pGameObjects)
{
	for (int index=0;index<g_vec_pGameObjects.size();index++)
	{
		if (g_vec_pGameObjects[index]->pirateType == MELEE)
		{
			g_vec_pGameObjects[index]->scale = 1.0f;
		}
		else if (g_vec_pGameObjects[index]->pirateType == RANGED)
		{
			g_vec_pGameObjects[index]->scale = 0.5f;
		}
		else if (g_vec_pGameObjects[index]->pirateType == LEADER)
		{
			g_vec_pGameObjects[index]->scale = 2.0f;
		}

			
	}
	return true;
}

