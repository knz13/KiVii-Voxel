#include "Color.h"

Color Color::White = Color(255, 255, 255);
Color Color::Black = Color(0, 0, 0);
Color Color::Blue = Color(0, 0, 255);
Color Color::Green = Color(0, 255, 0);
Color Color::Red = Color(255, 0, 0);
Color::Color(float r, float g, float b)
	:m_Color(r/255,g/255,b/255)
{

}



Color::Color()
	:m_Color({0,0,0})
{
}
