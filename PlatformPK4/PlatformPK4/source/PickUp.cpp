#include "PickUp.h"

PickUp::PickUp(ResourceManager* manager, const std::string& texture_name, float left, float top):Object(manager, texture_name, left, top), toDelete(false)
{
}

bool PickUp::isToDelete()
{
	return toDelete;
}
