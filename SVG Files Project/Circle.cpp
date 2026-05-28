#include "Circle.h"
#include <iostream>

Circle::Circle(double cx, double cy, double r, const std::string& fill) : Shape(fill), cx(cx), cy(cy), r(r) {}

std::string Circle::getType() const
{
	return "Circle";
}

void Circle::print() const
{
	std::cout << "circle " << cx << " " << cy << " " << r << " " << fill << std::endl;
}

void Circle::translate(double dx, double dy)
{
	cx += dx;
	cy += dy;
}

bool Circle::containsPoint(double px, double py) const
{
	double dx = px - cx;
	double dy = py - cy;

	return dx * dx + dy * dy <= r * r;
}

std::string Circle::toSVG() const
{
	return "<circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) + "\" r=\"" + std::to_string(r) + "\" fill=\"" + fill + "\" />";
}