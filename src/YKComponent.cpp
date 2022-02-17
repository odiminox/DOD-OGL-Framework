#include "YKComponent.h"

YKComponent::YKComponent()
{
	_componentID = 0x80;
}

YKComponent::~YKComponent()
{
}

int YKComponent::YKCGetID()
{
	return _componentID;
}

void YKComponent::YKCSetObjectWorldPos(int worldPos)
{
    _objectWorldPos = worldPos;
}

int YKComponent::YKCGetObjectIWorldPos()
{
    return _objectWorldPos;
}