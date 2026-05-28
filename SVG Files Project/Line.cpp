#include "Line.h"
#include <iostream>

Line::Line(double x1, double y1, double x2, double y2, const std::string& fill) : Shape(fill), x1(x1), y1(y1), x2(x2), y2(y2){}

std::string Line::getType() const
{
	return "Line";
}

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
	const double epsilon = 0.0001;

	double cross = (px - x1) * (y2 - y1) - (py - y1) * (x2 - x1);//ako rezultatyt e nula tochkata e na pravata
	if (std::abs(cross) > epsilon)
	{
		return false;
	}

	return px >= std::min(x1, x2) && px <= std::max(x1, x2) && py >= std::min(y1, y2) && py <= std::max(y1, y2);//proverqva dali tochkata e mejdu dvata kraq
}

std::string Line::toSVG() const
{
	return "<line x1=\"" + std::to_string(x1) + "\" y1=\"" + std::to_string(y1) + "\" x2=\"" + std::to_string(x2) + "\" y2=\"" + std::to_string(y2) + "\" fill=\"" + fill + "\" />";
}