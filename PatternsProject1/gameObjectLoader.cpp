#include"gameObjectLoader.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void DrawObject(glm::mat4 m,
	iObject* pCurrentObject,
	GLint shaderProgID,
	cVAOManager* pVAOManager)
{
	m = calculateWorldMatrix(pCurrentObject);

	GLint matModel_UL = glGetUniformLocation(shaderProgID, "matModel");
	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(m));

	GLint matModelIT_UL = glGetUniformLocation(shaderProgID, "matModelInverseTranspose");
	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(m));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

	GLint newColour_location = glGetUniformLocation(shaderProgID, "newColour");
	glUniform4f(newColour_location,
		pCurrentObject->getObjectColourRGBA().r,
		pCurrentObject->getObjectColourRGBA().g,
		pCurrentObject->getObjectColourRGBA().b, 1.0f);

	GLint diffuseColour_UL = glGetUniformLocation(shaderProgID, "diffuseColour");
	glUniform4f(diffuseColour_UL,
		pCurrentObject->getObjectColourRGBA().r,
		pCurrentObject->getObjectColourRGBA().g,
		pCurrentObject->getObjectColourRGBA().b,
		pCurrentObject->getObjectColourRGBA().a);

	GLint specularColour_UL = glGetUniformLocation(shaderProgID, "specularColour");
	glUniform4f(specularColour_UL,
		1.0f,	// R
		1.0f,	// G
		1.0f,	// B
		1000.0f);	// Specular "power" (how shinny the object is)
					// 1.0 to really big (10000.0f)


	GLint debugColour_UL = glGetUniformLocation(shaderProgID, "debugColour");
	GLint bDoNotLight_UL = glGetUniformLocation(shaderProgID, "bDoNotLight");

	if (pCurrentObject->getIsWireframe())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f(debugColour_UL,
			pCurrentObject->getDebugColour().r,
			pCurrentObject->getDebugColour().g,
			pCurrentObject->getDebugColour().b,
			pCurrentObject->getDebugColour().a);
		glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
	}
	else
	{	// Regular object (lit and not wireframe)
		glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	if (pCurrentObject->getDisableDepthBufferTest())
	{
		glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
	}
	else
	{
		glEnable(GL_DEPTH_TEST);						// Turn ON depth test
	}

	if (pCurrentObject->getDisableDepthBufferWrite())
	{
		glDisable(GL_DEPTH);						// depth buffer ON
	}
	else
	{
		glEnable(GL_DEPTH);								// depth buffer OFF
	}

	sModelDrawInfo drawInfo;

	if (pVAOManager->FindDrawInfoByModelName(pCurrentObject->getMeshName(), drawInfo))
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
			drawInfo.numberOfIndices,
			GL_UNSIGNED_INT,
			0);
		glBindVertexArray(0);
	}

	return;

}

// Calculate world mat func starts

glm::mat4 calculateWorldMatrix(iObject* pCurrentObject)
{

	glm::mat4 matWorld = glm::mat4(1.0f);
	

	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
			glm::vec3(pCurrentObject->getPositionXYZ().x,
				pCurrentObject->getPositionXYZ().y,
				pCurrentObject->getPositionXYZ().z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********



	// ******* ROTATION TRANSFORM *********
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
		pCurrentObject->getRotationXYZ().z,											// Angle 
		glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
		pCurrentObject->getRotationXYZ().y,											// Angle 
		glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
		pCurrentObject->getRotationXYZ().x,											// Angle 
		glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;
	// ******* ROTATION TRANSFORM *********



	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
		glm::vec3(pCurrentObject->getScale(),
			pCurrentObject->getScale(),
			pCurrentObject->getScale()));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}

// Calculate world mat func ends


// Reading GameObject Data from External File and creating GameObject Starts Here
bool ReadGameObjectsData(std::string filename,
	std::vector<iObject*>& g_vec_pGameObjects,
	cModelLoader* pTheModelLoader)
{
	/*std::vector<cGameObject*> g_vec_pGameObjects;*/
	std::ifstream GameObjectData;

	GameObjectData.open(filename);
	if (!GameObjectData.is_open()) {
		printf("Unable to open file\n");
		system("pause");
		return false;
	}

	cObjectFactory* pFactory = new cObjectFactory();

	while (true)
	{

		//cGameObject* currentGameObject = new cGameObject();
		iObject* currentGameObject = pFactory->CreateObject("sphere");
		std::string temp;


		GameObjectData >> temp;

		if (temp == "GameObject")
		{
			std::string curmeshname;
			GameObjectData >> curmeshname;
			currentGameObject->setMeshName(curmeshname);
		}
		else
		{
			break;						// if temp is not at "GameObject" now , then the loop has reached the "end"
		}

		GameObjectData >> temp;

		if (temp == "FriendlyName")
		{
			std::string curFriendlyName;
			GameObjectData >> curFriendlyName;
			currentGameObject->setFriendlyName(curFriendlyName);
		}


		GameObjectData >> temp;

		if (temp == "Position")
		{
			float curPosX;
			float curPosY;
			float curPosZ;
			GameObjectData >> curPosX >> curPosY >> curPosZ;
			currentGameObject->setPositionXYZ(glm::vec3(curPosX, curPosY, curPosZ));
		}

		GameObjectData >> temp;

		if (temp == "Rotation")
		{
			float curRotX;
			float curRotY;
			float curRotZ;
			GameObjectData >> curRotX >> curRotY >> curRotZ;
			currentGameObject->setRotationXYZ(glm::vec3(curRotX, curRotY, curRotZ));
			//GameObjectData >> currentGameObject->rotationXYZ.x >> currentGameObject->rotationXYZ.y >> currentGameObject->rotationXYZ.z;
		}

		GameObjectData >> temp;

		if (temp == "Scale")
		{
			float curScale;
			GameObjectData >> curScale;
			currentGameObject->setScale(curScale);
		}

		GameObjectData >> temp;

		if (temp == "Color")
		{
			float curObjColorX;
			float curObjColorY;
			float curObjColorZ;
			GameObjectData >> curObjColorX >> curObjColorY >> curObjColorZ;
			currentGameObject->setObjectColourRGBA(glm::vec4(curObjColorX, curObjColorY, curObjColorZ, 1.0f));
			//GameObjectData >> currentGameObject->objectColourRGBA.x >> currentGameObject->objectColourRGBA.y >> currentGameObject->objectColourRGBA.z;
		}

		GameObjectData >> temp;

		if (temp == "dColor")
		{
			float curDbugColorX;
			float curDbugColorY;
			float curDbugColorZ;
			GameObjectData >> curDbugColorX >> curDbugColorY >> curDbugColorZ;
			currentGameObject->setDebugColour(glm::vec4(curDbugColorX, curDbugColorY, curDbugColorZ, 1.0f));
			//GameObjectData >> currentGameObject->debugColour.x >> currentGameObject->debugColour.y >> currentGameObject->debugColour.z;
		}

		GameObjectData >> temp;

		if (temp == "velocity")
		{
			glm::vec3 curVel;
			GameObjectData >> curVel.x >> curVel.y >> curVel.z;
			currentGameObject->setVelocity(curVel);
			//GameObjectData >> currentGameObject->velocity.x >> currentGameObject->velocity.y >> currentGameObject->velocity.z;
		}

		GameObjectData >> temp;

		if (temp == "acceleration")
		{
			glm::vec3 curAcc;
			GameObjectData >> curAcc.x >> curAcc.y >> curAcc.z;
			currentGameObject->setAccel(curAcc);
			//GameObjectData >> currentGameObject->accel.x >> currentGameObject->accel.y >> currentGameObject->accel.z;
		}

		GameObjectData >> temp;

		if (temp == "Mass")
		{
			float currInvMass;
			GameObjectData >> currInvMass;
			currentGameObject->setInverseMass(currInvMass);
		}

		GameObjectData >> temp;

		if (temp == "SphereRadius")
		{
			float currSpRadius;
			GameObjectData >> currSpRadius;
			currentGameObject->set_SPHERE_radius(currSpRadius);
		}

		GameObjectData >> temp;

		if (temp == "Wireframe")
		{
			bool isWF;
			GameObjectData >> isWF;
			currentGameObject->setIsWireframe(isWF);
		}



		/*if (currentGameObject->getMeshName() == "terrain")
		{
			currentGameObject->GameObjectMesh = pTheModelLoader->vecMesh[0];
		}
		else if (currentGameObject->meshName == "ball")
		{
			currentGameObject->GameObjectMesh = pTheModelLoader->vecMesh[0];
		}*/

		g_vec_pGameObjects.push_back(currentGameObject);


	}
	return true;
}
// Reading GameObject Data from External File and creating GameObject Ends here