#include "Line.h"
#include <iostream>

Line::Line(double x1, double y1, double x2, double y2, const std::string& fill) : Shape(fill), x1(x1), y1(y1), x2(x2), y2(y2){}

void Line::print() const
{
	std::cout << "line " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << fill << std::endl;
}

void Line::translate(double dx, double dy)
{
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

bool Line::containsPoint(double px, double py) const
{
	//TODO
}

std::string Line::toSVG() const
{
	return "<line x1=\"" + std::to_string(x1) + "\" y1=\"" + std::to_string(y1) + "\" x2=\"" + std::to_string(x2) + "\" y2=\"" + std::to_string(y2) + "\" fill=\"" + fill + "\" />";
}