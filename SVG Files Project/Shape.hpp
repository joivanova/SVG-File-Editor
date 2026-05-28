#pragma once
#include <string>
class Shape
{
protected:
	std::string fill;
public:
	Shape(const std::string& fill) : fill(fill){}
	virtual ~Shape() = default;

	virtual void print() const = 0;
	virtual void translate(double dx, double dy) = 0;
	virtual bool containsPoint(double x, double y) const = 0;
	virtual std::string toSVG() const = 0;
	
	virtual std::string getType() const = 0;
};