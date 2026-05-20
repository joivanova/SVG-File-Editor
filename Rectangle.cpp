#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(double x, double y, double width, double height, const std::string& fill) : Shape(fill), x(x), y(y), width(width), height(height) {}

void Rectangle::print() const
{
	std::cout << "rectangle " << x << " " << y << " " << width << " " << height << " " << fill << std::endl;
}

void Rectangle::translate(double dx, double dy)
{
	x += dx;
	y += dy;
}

bool Rectangle::containsPoint(double px, double py) const
{
	return px >= x && px <= x + width && py >= y && py <= y + height;
}

//bool Rectangle::isWithinRectangle(double rx, double ry, double rw, double rh) const
//{
//	return x >= rx && y >= ry && x + width <= rx + rw && y + height <= ry + rh;
//}
//
//bool Rectangle::isWithinCircle(double cx, double cy, double r) const
//{
//
//}

std::string Rectangle::toSVG() const
{
	return "<rect x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" fill=\"" + fill + "\" />";
}