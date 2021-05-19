#pragma once
#include "Object.h"
class Wall : public Object
{
public:
	
	Wall(class ResourceManager* manager,const std::string& texture_name, float left, float top, int width, int height);
virtual	void collision(class Character* player);
	~Wall();
	

};