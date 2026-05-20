#pragma once
#include <string>
#include <vector>
#include "Shape.hpp"
class SVGDocument
{
private:
	std::vector<Shape*> shapes;//polzvame din.kontejner kojto syhranqva ukazateli kym razlichni figuri nasledqvashti Shape; Shape* shape e samo edin pointer; ne pishem std::vector<Shape> zashtoto Shape e abstract i polymorpism nqma da raboti
	std::string filename;
public:
	SVGDocument() = default;
	~SVGDocument();

	void setFilename(const std::string& file);

	void print() const;
	void create(Shape* shape);
	void erase(int index);
	void translate(double dx, double dy);//vsichki figuri
	void translate(double dx, double dy, int index);//za edna figura; izpolzvame function overloading
	void withinRectangle(double x, double y, double width, double height) const;
	void withinCircle(double cx, double cy, double r) const;
	void save() const;
};