#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class txtData : public singletonBase<txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//세이브
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);
	
	//로드
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);



	txtData();
	~txtData();
};

