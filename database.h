#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class elements
{
public:
	const char* name;
	int currentHP;
	int maxHP;
	float angle;
	float acceleration;
	float maxSpeed;

	elements(){};
	~elements(){};

};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;


private:
	arrElement _mTotalElement;

public:
	HRESULT init(void);
	void release(void);

	void loadDatabase(string name);

	//접근자
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAcceleration(string str, float ac);
	void setElementDataMaxSpeed(string str, float ms);

	database();
	~database();
};

