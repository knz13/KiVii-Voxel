#include "Renderer.h"


void Renderer::DrawCurrentBound(unsigned int count,unsigned int typeOfDrawing)
{
	GL_CALL(glDrawElements(typeOfDrawing, count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawCurrentBoundNoIB(unsigned int count,unsigned int typeOfDrawing)
{
	GL_CALL(glDrawArrays(typeOfDrawing, 0, count));
}