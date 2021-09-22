#pragma once
#include "GL_CALL.h"


class Color {

private:
	
	Vector3f m_Color;

	friend class KManager;
public:
	Color(float r, float g, float b);
	Color();

	static Color White;
	static Color Black;
	static Color Blue;
	static Color Green;
	static Color Red;


	Vector3f getNormalized() { return m_Color; }

};

