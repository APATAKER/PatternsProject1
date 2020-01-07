#ifndef _cGameObject_HG_
#define _cGameObject_HG_

#include"commonHeaders.h"


#include"cMesh.h"
#include"cModelLoader.h"

//#include"cPirate.h"
//#include"cLeaderPirate.h"
//#include"cMeleePirate.h"
//#include"cRangedPirate.h"




enum eShapeTypes
{
	AABB,
	SPHERE,
	CAPSULE,
	PLANE,
	MESH,
	UNKNOWN
};

enum ePirateTypes
{
	MELEE,
	RANGED,
	MEDIC,
	LEADER,
	NONE

};

class cGameObject
{
public:
	cGameObject();

	bool pushTOVecOrNot;
	
	// mesh details
	std::string meshName;
	cMesh GameObjectMesh; 

	// model identifier
	unsigned int friendlyIDNumber;
	std::string friendlyName;
	
	// model modifiers(basic)
	glm::vec3  positionXYZ;
	glm::vec3 prevPositionXYZ;
	glm::vec3  rotationXYZ;
	float scale;
	glm::vec4  objectColourRGBA;

	// model in groups
	ePirateTypes pirateType;

	
	//model physic variables
	glm::mat4 matWorld;
	glm::vec4 diffuseColour;	
	glm::vec4 specularColour;	
	glm::vec3 velocity;
	glm::vec3 accel;
	float HACK_speed;
	float HACK_AngleAroundYAxis;
	eShapeTypes physicsShapeType;
	float inverseMass;
	glm::vec3 AABB_min, AABB_max;
	float SPHERE_radius;

	
	// model debug settings
	bool isWireframe;
	glm::vec4 debugColour;
	bool isVisible;

	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;

	unsigned int getUniqueID(void);


private:

	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;

};

#endif

bool applyPirateAttributestoModel(std::vector<cGameObject*>& g_vec_pGameObjects);

bool ReadGameObjectsData(std::string filename, std::vector<cGameObject*> &g_vec_pGameObjects,cModelLoader* pTheModelLoader);

