#pragma once
#include <string>
#include <vector>
#include "Shape.hpp"

#include "Rectangle.h";
#include "Circle.h";
#include "Line.h";
class SVGDocument
{
private:
	std::vector<Shape*> shapes;//polzvame din.kontejner kojto syhranqva ukazateli kym razlichni figuri
	std::string filename;

	Rectangle* loadRectangle(const std::string& line);
	Circle* loadCircle(const std::string& line);
	Line* loadLine(const std::string& line);
	
	double extractNumber(const std::string& text);
	std::string extractString(const std::string& text);

public:
	SVGDocument() = default;
	~SVGDocument();

	void setFilename(const std::string& file);
	const std::string& getFilename() const;

	void print() const;
	void create(Shape* shape);
	void erase(int index);
	void translate(double dx, double dy);//vsichki figuri
	void translate(double dx, double dy, int index);//za edna figura; izpolzvame function overloading
	void withinRectangle(double x, double y, double width, double height) const;
	void withinCircle(double cx, double cy, double r) const;

	std::string getShapeType(int index) const;
	
	void load(const std::string& file);
	void close();
	void save() const;
	void saveAs(const std::string& newFile);
};