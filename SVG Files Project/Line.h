#pragma once
#include "Shape.hpp"

class Line : public Shape
{
private:
	double x1, y1, x2, y2;

public:
	Line(double x1, double y1, double x2, double y2, const std::string& fill);

	void print() const override;
	void translate(double dx, double dy) override;
	bool containsPoint(double px, double py) const override;
	std::string toSVG() const override;

	std::string getType() const override;
};