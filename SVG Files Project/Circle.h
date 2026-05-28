#pragma once
#include "Shape.hpp"

class Circle : public Shape
{
private:
	double cx;
	double cy;
	double r;

public:
	Circle(double cx, double cy, double r, const std::string& fill);

	void print() const override;
	void translate(double dx, double dy) override;
	bool containsPoint(double px, double py) const override;
	std::string toSVG() const override;

	std::string getType() const override;
};