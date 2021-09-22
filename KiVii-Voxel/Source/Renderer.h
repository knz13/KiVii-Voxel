#pragma once
#include "GL_CALL.h"


class Renderer {
public:
	Renderer() {};
	~Renderer() {};

	void DrawCurrentBound(unsigned int count,unsigned int typeOfDrawing);
	void DrawCurrentBoundNoIB(unsigned int count,unsigned int typeOfDrawing);
};