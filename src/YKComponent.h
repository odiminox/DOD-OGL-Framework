#pragma once

#include "Kernal.h"

class YKComponent

{
public:
	YKComponent();
	~YKComponent();

	int YKCGetID();
    void YKCSetObjectWorldPos(int worldPos);
    int YKCGetObjectIWorldPos();

private:
	int _componentID;
    int _objectWorldPos;
};
