#ifndef _cLightManager_HG_
#define _cLightManager_HG_


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<map>

#include<glm/glm.hpp>

//void getStringForPassingUniformName();
//std::map<int, std::string> LightProperties{
//	{0,"position"},
//	{1,"diffuse"},
//	{2,	"specular"},
//	{3,	"atten"},
//	{4,	"direction"},
//	{5,	"param1"},
//	{6,	"param2"}
//};

struct lightControls
{
	int lightID;
	glm::vec3 lightPosition;
	float lightLinearAtten;
	float lightQuadraticAtten;
	float lightConstAtten;
	glm::vec3 lightSpotDirection;

	float lightSpotInnerAngle;
	float lightSpotOuterAngle;

	float lightONOFF;

};



struct UniformLightItems
{
	GLint L_0_position;
	GLint L_0_diffuse;
	GLint L_0_specular;
	GLint L_0_atten;
	GLint L_0_direction;
	GLint L_0_param1;
	GLint L_0_param2;
};



class cLightManager
{
public:
	cLightManager();
	~cLightManager();

	glm::vec4 lightPosition;
	glm::vec4 lightDiffuse;
	glm::vec4 lightSpecular;
	glm::vec4 lightAtten;
	glm::vec4 lightDirection;
	glm::vec4 lightParam1;
	glm::vec4 lightParam2;


	

private:

};



#endif // _cLightManager_HG
