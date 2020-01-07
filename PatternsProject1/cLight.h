#pragma once
#include <string>
#include "iMessageInterface.h"

class cLightImp;

class cLight : public iMessageInterface
{
public:
	cLight();
	cLight(std::string nodeName, float PositionX, float PositionY, float PositionZ, float ConstAtten, float LinearAtten, float QuadraticAtten, float InnerSpot, float OuterSpot);
	~cLight();

	std::string getNodeName();
	void setNodeName(std::string nodeName);
	std::vector<std::string> getAllDataStrings();
	float getPositionX();
	float getPositionY();
	float getPositionZ();
	float getConstAtten();
	float getLinearAtten();
	float getQuadraticAtten();
	glm::vec3 getDirection();
	float getInnerSpot();
	float getOuterSpot();
	float getONOFF();
	glm::vec3 getPositionXYZ();
	void setPositionX(float PositionX);
	void setPositionY(float PositionY);
	void setPositionZ(float PositionZ);
	void setConstAtten(float ConstAtten);
	void setLinearAtten(float LinearAtten);
	void setQuadraticAtten(float QuadraticAtten);
	void setDirection(glm::vec3 Direction);
	void setInnerSpot(float InnerSpot);
	void setOuterSpot(float OuterSpot);
	void setPositionXYZ(glm::vec3 XYZ);
	void setONOFF(float ONOFF);

	virtual sNVPair RecieveMessage(sNVPair message);

private:
	cLightImp* pToImp;

	std::string _nodeName;
	glm::vec3 _positionXYZ;
	float _PositionX;
	float _PositionY;
	float _PositionZ;
	float _ConstAtten;
	float _LinearAtten;
	float _QuadraticAtten;
	glm::vec3 _Direction;
	float _InnerSpot;
	float _OuterSpot;
	float _ONOFF;

};