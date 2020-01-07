#include"ProjectControlsAndCallback.h"

//#include"cGameObject.h"
#include "cObjectFactory.h"
//#include"cLightManager.h"
//#include"globals.h"
#include"cMediator.h"

#define TRUE 1
#define FALSE 0

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

extern std::vector<iObject*> g_vec_pGameObjectsNew;
extern std::vector<cLight*> vecLights;
extern cMediator* pMediator;

extern int changeObj;
extern int changeLightObj;
extern int changeCameraTar;
extern int timeodtheday;
extern int flick;

extern glm::vec3 cameraEye;
extern glm::vec3 cameraTarget;
extern glm::vec3 upVector;

void itsNightTime();


bool isShiftKeyDownByAlone(int mods);
bool isCtrlKeyDownByAlone(int mods);


///############## USER #### INPUT ############################################################

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	const float MOVESPEED = 10.0f;
	const float LIGHTMOVESPEED = 1.0f;
	const float OBJECTMOVESPEED = 2.0f;
	const float LIGHTATTRIBSPEED = 0.99f;
	const float LIGHTQUADSPEED = 1.01f;
	const float VELOCITYSPEED = 0.1f;
	const float ROTATESPEED = 0.1f;

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{

		if (key == GLFW_KEY_Q)
		{
			cameraEye.y -= MOVESPEED;
		}
		if (key == GLFW_KEY_E)
		{
			cameraEye.y += MOVESPEED;
		}

		if (key == GLFW_KEY_W)
		{
			cameraEye.z += MOVESPEED;
		}
		if (key == GLFW_KEY_S)
		{
			cameraEye.z -= MOVESPEED;
		}

		if (key == GLFW_KEY_A)
		{
			cameraEye.x -= MOVESPEED;
		}
		if (key == GLFW_KEY_D)
		{
			cameraEye.x += MOVESPEED;
		}

		//Changing the camera to key locations							
		if (key == GLFW_KEY_1)
		{
			cameraTarget = g_vec_pGameObjectsNew[2]->getPositionXYZ();
			cameraEye = glm::vec3(140, 270, -30);
		}
		if (key == GLFW_KEY_2)
		{
			cameraTarget = g_vec_pGameObjectsNew[14]->getPositionXYZ();
			cameraEye = glm::vec3(264, 22, 70);
		}
		if (key == GLFW_KEY_3)
		{
			cameraTarget = g_vec_pGameObjectsNew[0]->getPositionXYZ() + glm::vec3(0, 120, 0);
			cameraEye = glm::vec3(-190, 550, -360);
		}


		//Changing Camera Target
		/*if (key == GLFW_KEY_C && action == GLFW_PRESS)
		{
			changeCameraTar++;

			if (changeCameraTar > g_vec_pGameObjects.size() - 1)
				changeCameraTar = 0;
			cameraTarget = g_vec_pGameObjects[changeCameraTar]->positionXYZ;
		}*/

		//Moved to GameObject Section

		//Switching to next GameObject Model
		if (key == GLFW_KEY_N)
		{
		}

	}

	if (isShiftKeyDownByAlone(mods))
	{
		//Light Position Movement
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
//			vecLightControls[changeLightObj]->lightPosition.y -= LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position Y Down";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			//vecLightControls[changeLightObj]->lightPosition.y += LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position Y Up";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}

		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			//vecLightControls[changeLightObj]->lightPosition.x -= LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position X Down";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			//vecLightControls[changeLightObj]->lightPosition.x += LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position X Up";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			//vecLightControls[changeLightObj]->lightPosition.z -= LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position Z Down";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			//vecLightControls[changeLightObj]->lightPosition.z += LIGHTMOVESPEED;
			sNVPair message;
			message.name = "Position Z Up";
			message.fValue = LIGHTMOVESPEED;
			pMediator->m_vec_pLights.at(changeLightObj)->RecieveMessage(message);
		}
		//Change light Object
		if (key == GLFW_KEY_N && action == GLFW_PRESS)
		{
			changeLightObj++;
			if (changeLightObj > pMediator->m_vec_pLights.size() - 1)
				changeLightObj = 0;
		}

		//Light on/off
		if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		{
			pMediator->m_vec_pLights[changeLightObj]->setONOFF(((bool)pMediator->m_vec_pLights[changeLightObj]->getONOFF() == TRUE) ? FALSE : TRUE);

		}

		//Change to night/day time
		if (key == GLFW_KEY_T && action == GLFW_PRESS)					
		{
			itsNightTime();
		}

		//Light attributes motion

		if (key == GLFW_KEY_O)//&& action == GLFW_PRESS						//LinearAtten 
		{
			pMediator->m_vec_pLights[changeLightObj]->setLinearAtten(pMediator->m_vec_pLights[changeLightObj]->getLinearAtten() * LIGHTATTRIBSPEED);
		}
		if (key == GLFW_KEY_P)
		{
			pMediator->m_vec_pLights[changeLightObj]->setLinearAtten(pMediator->m_vec_pLights[changeLightObj]->getLinearAtten() * LIGHTQUADSPEED);
		}

		if (key == GLFW_KEY_K)						//QuadraticAtten
		{
			pMediator->m_vec_pLights[changeLightObj]->setQuadraticAtten(pMediator->m_vec_pLights[changeLightObj]->getQuadraticAtten() * LIGHTATTRIBSPEED);
		}
		if (key == GLFW_KEY_L)
		{
			pMediator->m_vec_pLights[changeLightObj]->setQuadraticAtten(pMediator->m_vec_pLights[changeLightObj]->getQuadraticAtten() * LIGHTQUADSPEED);
		}

		if (key == GLFW_KEY_U)						//InnerSpotAngle
		{
			pMediator->m_vec_pLights[changeLightObj]->setInnerSpot(pMediator->m_vec_pLights[changeLightObj]->getInnerSpot() + LIGHTMOVESPEED);
		}
		if (key == GLFW_KEY_I)
		{
			pMediator->m_vec_pLights[changeLightObj]->setInnerSpot(pMediator->m_vec_pLights[changeLightObj]->getInnerSpot() - LIGHTMOVESPEED);
		}
		if (key == GLFW_KEY_H)						//OuterSpotAngle
		{
			pMediator->m_vec_pLights[changeLightObj]->setOuterSpot(pMediator->m_vec_pLights[changeLightObj]->getOuterSpot() + LIGHTMOVESPEED);
		}
		if (key == GLFW_KEY_J)
		{
			pMediator->m_vec_pLights[changeLightObj]->setOuterSpot(pMediator->m_vec_pLights[changeLightObj]->getOuterSpot() - LIGHTMOVESPEED);
		}


	}//if (isShiftKeyDownByAlone(mods))


	//Game Object Controls
	if (isCtrlKeyDownByAlone(mods))
	{
		//Moving Position
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x,g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y + OBJECTMOVESPEED, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			//g_vec_pGameObjects[changeObj]->getPositionXYZ().y -= OBJECTMOVESPEED;
			//cameraTarget = g_vec_pGameObjects[changeObj]->positionXYZ;
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y - OBJECTMOVESPEED, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}

		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x + OBJECTMOVESPEED, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y , g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x - OBJECTMOVESPEED, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z + OBJECTMOVESPEED));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y, g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z - OBJECTMOVESPEED));
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}
		//Rotation of the GameObject						
		if (key == GLFW_KEY_I && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x + ROTATESPEED, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z));
		}
		if (key == GLFW_KEY_K && action == GLFW_PRESS)
		{
			//g_vec_pGameObjects[changeObj]->rotationXYZ.x -= ROTATESPEED;
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x - ROTATESPEED, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z));
		}
		if (key == GLFW_KEY_U && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y + ROTATESPEED, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z));
		}
		if (key == GLFW_KEY_O && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y - ROTATESPEED, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z));
		}
		if (key == GLFW_KEY_J && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z + ROTATESPEED));
		}
		if (key == GLFW_KEY_L && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setRotationXYZ(glm::vec3(g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y, g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z - ROTATESPEED));
		}

		//Scale the object
		if (key == GLFW_KEY_G)
		{
			//g_vec_pGameObjects[changeObj]->scale += 0.1f;
			g_vec_pGameObjectsNew[changeObj]->setScale(g_vec_pGameObjectsNew[changeObj]->getScale() + 0.1f);
		}
		if (key == GLFW_KEY_H)
		{
			g_vec_pGameObjectsNew[changeObj]->setScale(g_vec_pGameObjectsNew[changeObj]->getScale() - 0.1f);
		}

		//Changing to Next GameObject
		if (key == GLFW_KEY_N && action == GLFW_PRESS)
		{
			changeObj++;
			if (changeObj > (g_vec_pGameObjectsNew.size() - 1))
				changeObj = 1;
		}
		//changing to previous GameObject
		if (key == GLFW_KEY_B && action == GLFW_PRESS)
		{
			changeObj--;
			if (changeObj <= 0)
				changeObj = (g_vec_pGameObjectsNew.size() - 1);
		}

		//Refresh camera target to gameOBject
		if (key == GLFW_KEY_C)
		{
			cameraTarget = g_vec_pGameObjectsNew[changeObj]->getPositionXYZ();
		}

		//Change to wireframe/ solid
		if (key == GLFW_KEY_V && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[changeObj]->setIsWireframe((g_vec_pGameObjectsNew[changeObj]->getIsWireframe() == true) ? false : true);
		}
		if (key == GLFW_KEY_T && action == GLFW_PRESS)
		{
			g_vec_pGameObjectsNew[0]->setIsWireframe((g_vec_pGameObjectsNew[0]->getIsWireframe() == true) ? false : true);
		}
	}


	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		updateFile();
		std::cout << "File updated"<<std::endl;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}
bool isShiftKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_SHIFT)
	{

		return true;
	}

	return false;
}
bool isCtrlKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}
///############## USER #### INPUT ############################################################


//############################## Function ### Def ###########################################

// update scene file

void updateFile()
{
	std::ofstream rewrite;
	rewrite.open("config/scene.txt");
	if (!rewrite.is_open()) {
		printf("Unable to open file\n");
		system("pause");
	}
	for (int index = 0; index != g_vec_pGameObjectsNew.size(); index++)
	{

		std::string temp;

		temp = "GameObject ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getMeshName();

		temp = " FriendlyName ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getFriendlyName();

		temp = " Position ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getPositionXYZ().x << " " << g_vec_pGameObjectsNew[index]->getPositionXYZ().y << " " << g_vec_pGameObjectsNew[index]->getPositionXYZ().z;

		temp = " Rotation ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getRotationXYZ().x << " " << g_vec_pGameObjectsNew[index]->getRotationXYZ().y << " " << g_vec_pGameObjectsNew[index]->getRotationXYZ().z;

		temp = " Scale ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getScale();

		temp = " Color ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getObjectColourRGBA().x << " " << g_vec_pGameObjectsNew[index]->getObjectColourRGBA().y << " " << g_vec_pGameObjectsNew[index]->getObjectColourRGBA().z;

		temp = " dColor ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getDebugColour().x << " " << g_vec_pGameObjectsNew[index]->getDebugColour().y << " " << g_vec_pGameObjectsNew[index]->getDebugColour().z;

		temp = " velocity ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getVelocity().x << " " << g_vec_pGameObjectsNew[index]->getVelocity().y << " " << g_vec_pGameObjectsNew[index]->getVelocity().z;

		temp = " acceleration ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getAccel().x << " " << g_vec_pGameObjectsNew[index]->getAccel().y << " " << g_vec_pGameObjectsNew[index]->getAccel().z;

		temp = " Mass ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getInverseMass();

		temp = " SphereRadius ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->get_SPHERE_radius();

		temp = " Wireframe ";
		rewrite << temp;
		rewrite << g_vec_pGameObjectsNew[index]->getIsWireframe();

		rewrite << "\n";

		if (index == (g_vec_pGameObjectsNew.size() - 1))
		{
			rewrite << "end";
		}

	}
}
//update scene file