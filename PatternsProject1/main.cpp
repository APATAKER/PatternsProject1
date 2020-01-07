#include"globals.h"
#include"openGLStuff.h"

#include"cModelLoader.h"
#include"cShaderManager.h"
#include"VAOManager.h"
#include"ProjectControlsAndCallback.h"
#include"Physics.h"
#include"cObjectFactory.h"
#include"gameObjectLoader.h"
#include"cMediator.h"
#include"cLightHelper.h"


// Func Prototypes "moved to gameObjectLoader" DrawObject, calculateWorldMatrix, ReadGameObjectsData


void itsNightTime();
void skullLightFlicker();

cMediator* pMediator = cMediator::createMediator();

GLFWwindow* window;

int main(int argc, char** argv)
{
	window = creatOpenGL(window);


	///######################## MODEL #### LOADING ##### STARTS ### HERE ##########################################
	cModelLoader* pTheModelLoader = new cModelLoader();



	// Models Loaded here

	std::string MeshFilePath ="config/cMeshFilePaths.txt";					
	pTheModelLoader->MeshLoader(MeshFilePath, pTheModelLoader);

	///######################## MODEL #### LOADING ##### ENDS ### HERE ##########################################


	///######################## SHADER #### LOADING ## STARTS ### HERE #############################################
	cShaderManager* pTheShaderManager = new cShaderManager();

	cShaderManager::cShader vertexShad;
	vertexShad.fileName = "assets/shaders/vertexShader01.glsl";

	cShaderManager::cShader fragShader;
	fragShader.fileName = "assets/shaders/fragmentShader01.glsl";

	if (!pTheShaderManager->createProgramFromFile("SimpleShader", vertexShad, fragShader))  
	{
		std::cout << "Error: didn't compile the shader" << std::endl;
		std::cout << pTheShaderManager->getLastError();
		return -1;
	}
	GLuint shaderProgID = pTheShaderManager->getIDFromFriendlyName("SimpleShader");
	///######################## SHADER #### LOADING ## ENDS ### HERE #############################################


	//##### MODELS ### LOADING ### INTO ### VERTEX ### ARRAY ### OBJECT #### (DATA PUSHED INTO SHADER CODE PART)###########

	//cVAOManager* pTheVAOManager = new cVAOManager();
	cVAOManager* pTheVAOManager = cVAOManager::getInstance();	
	// Singleton done Here


	int iterator=0;
	while (iterator != pTheModelLoader->vecMesh.size())
	{
		sModelDrawInfo meshDrawinfo;
		pTheVAOManager->LoadModelIntoVAO(pTheModelLoader->vecMesh[iterator].meshname, pTheModelLoader->vecMesh[iterator], meshDrawinfo, shaderProgID);
		iterator++;
	}


	//##### MODELS ### LOADING ### INTO ### VERTEX ### ARRAY ### OBJECT #### (DATA PUSHED INTO SHADER CODE PART)###########




	//##### GAME ### OBJECTS ### TO ### CREATED ### HERE ##################################################################

	/*g_vec_pGameObjects= ReadGameObjectsData("config/scene.txt");*/
	ReadGameObjectsData("config/scene.txt",g_vec_pGameObjectsNew,pTheModelLoader);			// Abstract Factory done here
	//applyPirateAttributestoModel(g_vec_pGameObjectsNew);


	//##### GAME ### OBJECTS ### TO ### CREATED ### HERE ##################################################################

	

	cameraTarget = g_vec_pGameObjectsNew[0]->getPositionXYZ();
	cameraEye = glm::vec3(0.0f, 300.0f, -420.0f);



	//##### LIGHT ### OBJECTS ### CREATED ### HERE ########################################################################
	//lightControls* Light0 = new lightControls();		//Night Light


	cLight* LightNew0 = new cLight();

	LightNew0->setPositionXYZ(glm::vec3(80, 820, 12));
	LightNew0->setLinearAtten(0.000000000190631f);
	LightNew0->setQuadraticAtten(0.00000183209f);
	LightNew0->setConstAtten(0.0000001f);
	LightNew0->setONOFF(0);

	//lightControls* Light1 = new lightControls();		//Daylight 1

	cLight* LightNew1 = new cLight();

	LightNew1->setPositionXYZ(glm::vec3(-540, 540, 12));
	LightNew1->setLinearAtten(0.0000006814f);
	LightNew1->setQuadraticAtten(0.00000289207f);
	LightNew1->setConstAtten(0.0000001f);
	LightNew1->setONOFF(1);

	//lightControls* Light2 = new lightControls();		//Daylight 2

	cLight* LightNew2 = new cLight();

	LightNew2->setPositionXYZ(glm::vec3(568, 540, -16));
	LightNew2->setLinearAtten(0.0000006814f);
	LightNew2->setQuadraticAtten(0.00000289207f);
	LightNew2->setConstAtten(0.0000001f);
	LightNew2->setONOFF(1);

	//lightControls* Light3 = new lightControls();		//Skull eye 1

	cLight* LightNew3 = new cLight();

	LightNew3->setPositionXYZ(glm::vec3(72, 206, 175));
	LightNew3->setLinearAtten(0.000000000103631f);
	LightNew3->setQuadraticAtten(0.0462209f);
	LightNew3->setConstAtten(0.0000001f);
	LightNew3->setONOFF(0);


	//lightControls* Light4 = new lightControls();		//Skull eye 2

	cLight* LightNew4 = new cLight();

	LightNew4->setPositionXYZ(glm::vec3(68, 206, 175));
	LightNew4->setLinearAtten(0.000000000103631f);
	LightNew4->setQuadraticAtten(0.0462209f);
	LightNew4->setConstAtten(0.0000001f);
	LightNew4->setONOFF(0);


	//lightControls* Light5 = new lightControls();		//fire inside the cave

	cLight* LightNew5 = new cLight();

	LightNew5->setPositionXYZ(glm::vec3(-102.0f, 1.0, 54.0));
	LightNew5->setLinearAtten(0.00000036534f);
	LightNew5->setQuadraticAtten(0.00366398f);
	LightNew5->setConstAtten(0.0000001f);
	LightNew5->setONOFF(0);


	//lightControls* Light6 = new lightControls();		//Spotlight from small rock 1 to cave(arch1)
	glm::vec3 srock1toarch1 = g_vec_pGameObjectsNew[14]->getPositionXYZ() - g_vec_pGameObjectsNew[17]->getPositionXYZ();

	cLight* LightNew6 = new cLight();

	LightNew6->setPositionXYZ(g_vec_pGameObjectsNew[17]->getPositionXYZ());
	LightNew6->setDirection(glm::normalize(srock1toarch1));
	LightNew6->setInnerSpot(11.0f);
	LightNew6->setOuterSpot(11.5f);
	LightNew6->setLinearAtten(0.0001f);
	LightNew6->setQuadraticAtten(0.000860f);
	LightNew6->setConstAtten(0.0000001f);
	LightNew6->setONOFF(0);


	cLight* LightNew7 = new cLight();

	LightNew7->setPositionXYZ(glm::vec3(g_vec_pGameObjectsNew[6]->getPositionXYZ()) + glm::vec3(0.0f, 1.0f, 0.0f));
	LightNew7->setLinearAtten(0.1f);
	LightNew7->setQuadraticAtten(0.0004601f);
	LightNew7->setConstAtten(0.0000001f);
	LightNew7->setONOFF(0);


	pMediator->m_vec_pLights.push_back(LightNew0);
	pMediator->m_vec_pLights.push_back(LightNew1);
	pMediator->m_vec_pLights.push_back(LightNew2);
	pMediator->m_vec_pLights.push_back(LightNew3);
	pMediator->m_vec_pLights.push_back(LightNew4);
	pMediator->m_vec_pLights.push_back(LightNew5);
	pMediator->m_vec_pLights.push_back(LightNew6);
	pMediator->m_vec_pLights.push_back(LightNew7);


	//std::cout << vecLightControls.size() << std::endl;
	//##### LIGHT ### OBJECTS ### CREATED ### HERE ########################################################################


	cPhysics* pPhysics = new cPhysics();
	glm::vec3 closestPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	cPhysics::sPhysicsTriangle closestTriangle;

	int lightIndex=0;
	

	// While Loop Start

	while (!glfwWindowShouldClose(window))
	{



		glUseProgram(shaderProgID);

		float ratio;
		int width, height;
		glm::mat4 p, v;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;


		p = glm::perspective(0.6f,
			ratio,
			0.1f,
			10000.0f);


		v = glm::mat4(1.0f);
		v = glm::lookAt(cameraEye,
			cameraTarget,
			upVector);


		glViewport(0, 0, width, height);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		
		GLint L_0_position = glGetUniformLocation(shaderProgID, "theLights[0].position");
		GLint L_0_diffuse = glGetUniformLocation(shaderProgID, "theLights[0].diffuse");
		GLint L_0_specular = glGetUniformLocation(shaderProgID, "theLights[0].specular");
		GLint L_0_atten = glGetUniformLocation(shaderProgID, "theLights[0].atten");
		GLint L_0_direction = glGetUniformLocation(shaderProgID, "theLights[0].direction");
		GLint L_0_param1 = glGetUniformLocation(shaderProgID, "theLights[0].param1");
		GLint L_0_param2 = glGetUniformLocation(shaderProgID, "theLights[0].param2");

		GLint L_1_position = glGetUniformLocation(shaderProgID,  "theLights[1].position");
		GLint L_1_diffuse = glGetUniformLocation(shaderProgID,	 "theLights[1].diffuse");
		GLint L_1_specular = glGetUniformLocation(shaderProgID,  "theLights[1].specular");
		GLint L_1_atten = glGetUniformLocation(shaderProgID,	 "theLights[1].atten");
		GLint L_1_direction = glGetUniformLocation(shaderProgID, "theLights[1].direction");
		GLint L_1_param1 = glGetUniformLocation(shaderProgID,	 "theLights[1].param1");
		GLint L_1_param2 = glGetUniformLocation(shaderProgID,	 "theLights[1].param2");

		GLint L_2_position = glGetUniformLocation(shaderProgID, "theLights[2].position");
		GLint L_2_diffuse = glGetUniformLocation(shaderProgID, "theLights[2].diffuse");
		GLint L_2_specular = glGetUniformLocation(shaderProgID, "theLights[2].specular");
		GLint L_2_atten = glGetUniformLocation(shaderProgID, "theLights[2].atten");
		GLint L_2_direction = glGetUniformLocation(shaderProgID, "theLights[2].direction");
		GLint L_2_param1 = glGetUniformLocation(shaderProgID, "theLights[2].param1");
		GLint L_2_param2 = glGetUniformLocation(shaderProgID, "theLights[2].param2");

		GLint L_3_position = glGetUniformLocation(shaderProgID, "theLights[3].position");
		GLint L_3_diffuse = glGetUniformLocation(shaderProgID, "theLights[3].diffuse");
		GLint L_3_specular = glGetUniformLocation(shaderProgID, "theLights[3].specular");
		GLint L_3_atten = glGetUniformLocation(shaderProgID, "theLights[3].atten");
		GLint L_3_direction = glGetUniformLocation(shaderProgID, "theLights[3].direction");
		GLint L_3_param1 = glGetUniformLocation(shaderProgID, "theLights[3].param1");
		GLint L_3_param2 = glGetUniformLocation(shaderProgID, "theLights[3].param2");

		GLint L_4_position = glGetUniformLocation(shaderProgID, "theLights[4].position");
		GLint L_4_diffuse = glGetUniformLocation(shaderProgID, "theLights[4].diffuse");
		GLint L_4_specular = glGetUniformLocation(shaderProgID, "theLights[4].specular");
		GLint L_4_atten = glGetUniformLocation(shaderProgID, "theLights[4].atten");
		GLint L_4_direction = glGetUniformLocation(shaderProgID, "theLights[4].direction");
		GLint L_4_param1 = glGetUniformLocation(shaderProgID, "theLights[4].param1");
		GLint L_4_param2 = glGetUniformLocation(shaderProgID, "theLights[4].param2");

		GLint L_5_position = glGetUniformLocation(shaderProgID, "theLights[5].position");
		GLint L_5_diffuse = glGetUniformLocation(shaderProgID, "theLights[5].diffuse");
		GLint L_5_specular = glGetUniformLocation(shaderProgID, "theLights[5].specular");
		GLint L_5_atten = glGetUniformLocation(shaderProgID, "theLights[5].atten");
		GLint L_5_direction = glGetUniformLocation(shaderProgID, "theLights[5].direction");
		GLint L_5_param1 = glGetUniformLocation(shaderProgID, "theLights[5].param1");
		GLint L_5_param2 = glGetUniformLocation(shaderProgID, "theLights[5].param2");

		GLint L_6_position = glGetUniformLocation(shaderProgID, "theLights[6].position");
		GLint L_6_diffuse = glGetUniformLocation(shaderProgID, "theLights[6].diffuse");
		GLint L_6_specular = glGetUniformLocation(shaderProgID, "theLights[6].specular");
		GLint L_6_atten = glGetUniformLocation(shaderProgID, "theLights[6].atten");
		GLint L_6_direction = glGetUniformLocation(shaderProgID, "theLights[6].direction");
		GLint L_6_param1 = glGetUniformLocation(shaderProgID, "theLights[6].param1");
		GLint L_6_param2 = glGetUniformLocation(shaderProgID, "theLights[6].param2");

		GLint L_7_position = glGetUniformLocation(shaderProgID, "theLights[7].position");
		GLint L_7_diffuse = glGetUniformLocation(shaderProgID, "theLights[7].diffuse");
		GLint L_7_specular = glGetUniformLocation(shaderProgID, "theLights[7].specular");
		GLint L_7_atten = glGetUniformLocation(shaderProgID, "theLights[7].atten");
		GLint L_7_direction = glGetUniformLocation(shaderProgID, "theLights[7].direction");
		GLint L_7_param1 = glGetUniformLocation(shaderProgID, "theLights[7].param1");
		GLint L_7_param2 = glGetUniformLocation(shaderProgID, "theLights[7].param2");



		

		glUniform4f(L_0_position,															//LIght 0  Night Light
			LightNew0->getPositionXYZ().x,
			LightNew0->getPositionXYZ().y,
			LightNew0->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_0_diffuse, 0.0745f, 0.3686f, 0.8392f, 1.0f);	// Dark Blue stuff (night light)
		glUniform4f(L_0_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_0_atten, 0.0f,						 // constant attenuation
			LightNew0->getLinearAtten(),							 // Linear 
			LightNew0->getQuadraticAtten(),						// Quadratic 
			1000000.0f);									// Distance cut off

		// Point light:
		glUniform4f(L_0_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);

		glUniform4f(L_0_param2, LightNew0->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);



						
		glUniform4f(L_1_position,															//Light 1 - Daylight 1 
			LightNew1->getPositionXYZ().x,
			LightNew1->getPositionXYZ().y,
			LightNew1->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_1_diffuse, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_1_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_1_atten, 0.0f,						
			LightNew1->getLinearAtten(),
			LightNew1->getQuadraticAtten(),
			1000000.0f);									

		// Point light:
		glUniform4f(L_1_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);

		glUniform4f(L_1_param2, LightNew1->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);



		glUniform4f(L_2_position,														//Light 2 - dayLight 2
			LightNew2->getPositionXYZ().x,
			LightNew2->getPositionXYZ().y,
			LightNew2->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_2_diffuse, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_2_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_2_atten, 0.0f,						
			LightNew2->getLinearAtten(),
			LightNew2->getQuadraticAtten(),
			1000000.0f);									

		// Point light:
		glUniform4f(L_2_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);
		glUniform4f(L_2_param2, LightNew2->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);


		glUniform4f(L_3_position,														//Light 3 - skull eye 1
			LightNew3->getPositionXYZ().x,
			LightNew3->getPositionXYZ().y,
			LightNew3->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_3_diffuse, 1.0f, 0.5490f, 0.0f, 1.0f);	// Orange
		glUniform4f(L_3_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_3_atten, 0.0f,						
			LightNew3->getLinearAtten(),
			LightNew3->getQuadraticAtten(),
			1000000.0f);									

		// Point light:
		glUniform4f(L_3_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);
		glUniform4f(L_3_param2, LightNew3->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);


		glUniform4f(L_4_position,														//Light 4 - skull eye 2
			LightNew4->getPositionXYZ().x,
			LightNew4->getPositionXYZ().y,
			LightNew4->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_4_diffuse, 1.0f, 0.5490f, 0.0f, 1.0f);	// Orange
		glUniform4f(L_4_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_4_atten, 0.0f,
			LightNew4->getLinearAtten(),
			LightNew4->getQuadraticAtten(),
			1000000.0f);

		// Point light:
		glUniform4f(L_4_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);
		glUniform4f(L_4_param2, LightNew4->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);


		glUniform4f(L_5_position,														//Light 5 - Fire in the cave
			LightNew5->getPositionXYZ().x,
			LightNew5->getPositionXYZ().y,
			LightNew5->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_5_diffuse, 1.0f, 0.0f, 0.0f, 1.0f);	// Red
		glUniform4f(L_5_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_5_atten, 0.0f,
			LightNew5->getLinearAtten(),
			LightNew5->getQuadraticAtten(),
			1000000.0f);

		// Point light:
		glUniform4f(L_5_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);
		glUniform4f(L_5_param2, LightNew5->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);


		glUniform4f(L_6_position,														//Light 6 - Spotlight on the cave
			LightNew6->getPositionXYZ().x,
			LightNew6->getPositionXYZ().y,
			LightNew6->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_6_diffuse, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_6_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_6_atten, 0.0f,
			LightNew6->getLinearAtten(),
			LightNew6->getQuadraticAtten(),
			1000000.0f);
		glUniform4f(L_6_direction,
			LightNew6->getDirection().x,
			LightNew6->getDirection().y,
			LightNew6->getDirection().z,
			1.0f);
		// spot light:
		glUniform4f(L_6_param1, 1.0f /*SPOT light*/, LightNew6->getInnerSpot(), LightNew6->getOuterSpot(), 1.0f);
		glUniform4f(L_6_param2, LightNew6->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);


		glUniform4f(L_7_position,														//Light 7 - NONE
			LightNew7->getPositionXYZ().x,
			LightNew7->getPositionXYZ().y,
			LightNew7->getPositionXYZ().z,
			1.0f);
		glUniform4f(L_7_diffuse, 0.3176f, 1.0f, 0.0509f, 1.0f);	// White
		glUniform4f(L_7_specular, 1.0f, 1.0f, 1.0f, 1.0f);	// White
		glUniform4f(L_7_atten, 0.0f,
			LightNew7->getLinearAtten(),
			LightNew7->getQuadraticAtten(),
			1000000.0f);

		// Point light:
		glUniform4f(L_7_param1, 0.0f /*POINT light*/, 0.0f, 0.0f, 1.0f);
		glUniform4f(L_7_param2, LightNew7->getONOFF() /*Light is on*/, 0.0f, 0.0f, 1.0f);

		// Also set the position of my "eye" (the camera)
		GLint eyeLocation_UL = glGetUniformLocation(shaderProgID, "eyeLocation");

		glUniform4f(eyeLocation_UL,
			cameraEye.x, cameraEye.y, cameraEye.z, 1.0f);
		
		
		std::stringstream ssTitle;
		ssTitle
			<< " Cam Pos: "
			<< cameraEye.x << ", "
			<< cameraEye.y << ", "
			<< cameraEye.z
			<< "CurObj Name: " << g_vec_pGameObjectsNew[changeObj]->getFriendlyName()
			<< " CurrObj Pos: "
			<< g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().x << ", "
			<< g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().y << ", "
			<< g_vec_pGameObjectsNew[changeObj]->getPositionXYZ().z << ", "
			<< " CurrObj Rot: "
			<< g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().x << ", "
			<< g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().y << ", "
			<< g_vec_pGameObjectsNew[changeObj]->getRotationXYZ().z << ", "
			<< "Light ID: "
			//<< vecLights[changeLightObj]->lightID << " = "
			<< pMediator->m_vec_pLights[changeLightObj]->getPositionX() << ", "
			<< pMediator->m_vec_pLights[changeLightObj]->getPositionY() << ", "
			<< pMediator->m_vec_pLights[changeLightObj]->getPositionZ()
			<< " isOn/Off: "
			<< pMediator->m_vec_pLights[changeLightObj]->getONOFF()
			<< " Atten: "
			<< pMediator->m_vec_pLights[changeLightObj]->getConstAtten() << " : "
			<< pMediator->m_vec_pLights[changeLightObj]->getLinearAtten() << " : "
			<< pMediator->m_vec_pLights[changeLightObj]->getQuadraticAtten()
			<<" Inner/Outer spot: "
			<< pMediator->m_vec_pLights[changeLightObj]->getInnerSpot() << " : "
			<< pMediator->m_vec_pLights[changeLightObj]->getOuterSpot();
		
		
		glfwSetWindowTitle(window, ssTitle.str().c_str());


		GLint matView_UL = glGetUniformLocation(shaderProgID, "matView");
		GLint matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));


		for (int index = 0; index != g_vec_pGameObjectsNew.size(); index++)
		{
			/*glm::mat4 matModel = glm::mat4(1.0f);*/

			iObject* pCurrentObject = g_vec_pGameObjectsNew[index];

			DrawObject(pCurrentObject->getMatWorld(), pCurrentObject,
				shaderProgID, pTheVAOManager);

		}

		//Physics implementation
		
		/*pPhysics->IntegrationStep(g_vec_pGameObjects, 0.01f);					
		pPhysics->TestForCollisions(g_vec_pGameObjects);						
		pPhysics->CheckIfCrossedEndBound(g_vec_pGameObjects);					*/

		//flicker implementation		
		skullLightFlicker();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//While Loop Ends







	glfwDestroyWindow(window);
	glfwTerminate();

	delete pTheModelLoader;

	exit(EXIT_SUCCESS);

	return 0;
}


// Draw OBject func starts



// Draw Object func ends



void skullLightFlicker()									
{

	float dimmestAtten = 0.903631f;
	float brightestAtten = 0.000000000103631f;
	if (timeodtheday == 0)
	{

		pMediator->m_vec_pLights[3]->setLinearAtten(randInRange<float>(dimmestAtten, brightestAtten));
		pMediator->m_vec_pLights[4]->setLinearAtten(randInRange<float>(dimmestAtten, brightestAtten));
		

	}
}

void itsNightTime()									
{
	if (timeodtheday == 1)
	{
		pMediator->m_vec_pLights[0]->setONOFF(1);
		pMediator->m_vec_pLights[1]->setONOFF(0);
		pMediator->m_vec_pLights[2]->setONOFF(0);
		pMediator->m_vec_pLights[3]->setONOFF(1);
		pMediator->m_vec_pLights[4]->setONOFF(1);
		pMediator->m_vec_pLights[5]->setONOFF(1);
		pMediator->m_vec_pLights[6]->setONOFF(1);
		timeodtheday = 0;
	}
	else
	{
		pMediator->m_vec_pLights[0]->setONOFF(0);
		pMediator->m_vec_pLights[1]->setONOFF(1);
		pMediator->m_vec_pLights[2]->setONOFF(1);
		pMediator->m_vec_pLights[3]->setONOFF(0);
		pMediator->m_vec_pLights[4]->setONOFF(0);
		pMediator->m_vec_pLights[5]->setONOFF(0);
		pMediator->m_vec_pLights[6]->setONOFF(0);
		timeodtheday = 1;
	}
}


