#pragma once
#include "Object.h"
class PickUp: public Object
{
protected:
	bool toDelete;
public:
	PickUp(ResourceManager* manager, const std::string& texture_name, float left, float top);
	bool isToDelete();
};

