#pragma once

//#include"cGameObject.h"
#include"cObjectFactory.h"
#include"cModelLoader.h"
#include"cShaderManager.h"
#include"VAOManager.h"


void DrawObject(glm::mat4 m,
	iObject* pCurrentObject,
	GLint shaderProgID,
	cVAOManager* pVAOManager);


glm::mat4 calculateWorldMatrix(iObject* pCurrentObject);

bool ReadGameObjectsData(std::string filename,
	std::vector<iObject*>& g_vec_pGameObjects,
	cModelLoader* pTheModelLoader);