#ifndef _globals_HG_
#define _globals_HG_


#include"commonHeaders.h"
//#include "cSphereObject.h"
#include "cMesh.h"
#include"cObjectFactory.h"
//#include"cLightManager.h"
#include"cLight.h"



#define TRUE 1
#define FALSE 0

template <class T>
T randInRange(T min, T max)
{
	double value =
		min + static_cast <double> (rand())
		/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
	return static_cast<T>(value);
};

//std::vector<cGameObject*> g_vec_pGameObjects;
std::vector<iObject*> g_vec_pGameObjectsNew;
//std::vector<lightControls*> vecLightControls;
std::vector<cLight*> vecLights;

int changeObj = 1;
int changeLightObj = 0;
int changeCameraTar = 0;
int timeodtheday = 1;
int flick = 1;

glm::vec3 cameraEye;
glm::vec3 cameraTarget;
glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

#endif // !_globals_HG_