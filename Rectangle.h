#pragma once
#include "Shape.hpp"

class Rectangle :public Shape
{
private:
	double x;
	double y;
	double width;
	double height;

public:
	Rectangle(double x, double y, double width, double height, const std::string& fill);

	void print() const override;
	void translate(double dx, double dy) override;
	bool containsPoint(double px, double py) const override;
	//bool isWithinRectangle(double rx, double ry, double rw, double rh) const override;
	//bool isWithinCircle(double cx, double cy, double r) const override;
	std::string toSVG() const override;
};