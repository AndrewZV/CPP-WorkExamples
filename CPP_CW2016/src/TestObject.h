#pragma once
#include "DisplayableObject.h"
class TestObject :
	public DisplayableObject
{
public:
	TestObject(BaseEngine* pEngine);
	~TestObject();
	void Draw();
};

