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
	std::string toSVG() const override;

	std::string getType() const override;

};