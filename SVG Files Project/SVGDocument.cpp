#include "SVGDocument.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Rectangle.h";
#include "Circle.h";
#include "Line.h";
SVGDocument::~SVGDocument()
{
	for (Shape* s : shapes)
	{
		delete s;
	}
}

void SVGDocument::setFilename(const std::string& file)
{
	filename = file;//zapazva imeto na fajla; pr:doc.setFilename("figures.svg)
}

const std::string& SVGDocument::getFilename() const
{
	return filename;
}

double SVGDocument::extractNumber(const std::string& text)
{
	//vzima tekst mejdu dvete kavichki: x="15" -> 15
	size_t firstQuote = text.find("\"");
	size_t secondQuote = text.rfind("\"");

	std::string number = text.substr(firstQuote + 1, secondQuote - firstQuote - 1);

	return std::stod(number);//konvertira string v double
}

std::string SVGDocument::extractString(const std::string& text)
{
	size_t firstQuote = text.find("\"");
	size_t secondQuote = text.rfind("\"");

	return text.substr(firstQuote + 1, secondQuote - firstQuote - 1);
}

Rectangle* SVGDocument::loadRectangle(const std::string& line)
{
	std::stringstream ss(line);
	std::string temp;

	double x, y, width, height;
	std::string fill;

	ss >> temp; //<rect

	ss >> temp; //x="5"
	x = extractNumber(temp);

	ss >> temp; //y="5"
	y = extractNumber(temp);

	ss >> temp; //width="10"
	width = extractNumber(temp);

	ss >> temp; //height="10"
	height = extractNumber(temp);

	ss >> temp; //fill="green"
	fill = extractString(temp);

	return new Rectangle(x, y, width, height, fill);
}
Circle* SVGDocument::loadCircle(const std::string& line)
{
	std::stringstream ss(line);
	std::string temp;

	double cx, cy, r;
	std::string fill;

	ss >> temp; //<circle

	ss >> temp;
	cx = extractNumber(temp);

	ss >> temp;
	cy = extractNumber(temp);

	ss >> temp;
	r = extractNumber(temp);

	ss >> temp;
	fill = extractString(temp);

	return new Circle(cx, cy, r, fill);
}
Line* SVGDocument::loadLine(const std::string& line)
{
	std::stringstream ss(line);
	std::string temp;

	double x1, y1, x2, y2;
	std::string stroke;

	ss >> temp; //<line

	ss >> temp;
	x1 = extractNumber(temp);

	ss >> temp;
	y1 = extractNumber(temp);

	ss >> temp;
	x2 = extractNumber(temp);

	ss >> temp;
	y2 = extractNumber(temp);

	ss >> temp;
	stroke = extractString(temp);

	return new Line(x1, y1, x2, y2, stroke);
}
void SVGDocument::load(const std::string& file)
{
	filename = file;
	std::ifstream in(file);

	if (!in.is_open())
	{
		throw std::runtime_error("Could not open file!");
	}

	std::string line;
	while (std::getline(in, line))
	{
		if (line.find("<rect") != std::string::npos)
		{
			//tyrsim <rect v line i vryshtame poziciqta na koqto e nameren a ako ne e namerena vryshtame std::string::npos
			create(loadRectangle(line));
		}
		else if (line.find("<circle") != std::string::npos)
		{		
			create(loadCircle(line));
		}
		else if (line.find("<line") != std::string::npos)
		{
			create(loadLine(line));
		}
	}
}

void SVGDocument::close()
{
	size_t shapeSize = shapes.size();
	for (size_t i = 0; i < shapeSize; i++)
	{
		delete shapes[i];
	}
	shapes.clear();
	filename.clear();
}

void SVGDocument::save() const
{
	std::ofstream out(filename);

	if (!out.is_open())
	{
		throw std::runtime_error("Could not save file!");
	}

	out << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	out << "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\"\n";
	out << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	out << "<svg>\n";

	out.close();

	std::cout << "Successfully saved " << filename << std::endl;
}
void SVGDocument::saveAs(const std::string& newFile)
{
	filename = newFile;

	save();
}

void SVGDocument::print() const
{
	size_t shapeSize = shapes.size();
	for (size_t i = 0; i < shapeSize; i++)
	{
		std::cout << i + 1 << ". ";
		shapes[i]->print();
	}
}
void SVGDocument::create(Shape* shape)
{
	shapes.push_back(shape);
}

void SVGDocument::erase(int index)
{
	if (index < 1 || index > shapes.size())
	{
		throw std::out_of_range("Invalid figure number!");
	}

	delete shapes[index - 1];//zashtoto erase maha pointera ot vectora no ne delete-va obekta

	shapes.erase(index - 1);//mesti iteratora v nachaloto, sled tova na index-1 pozicii i trie elementa
}

void SVGDocument::translate(double dx, double dy)
{
	for (Shape* s : shapes)
	{
		s->translate(dx, dy);
	}
	std::cout << "Translated all figures";
}

void SVGDocument::translate(double dx, double dy, int index)
{
	size_t shapeSize = shapes.size();

	if (index < 1 || index > shapeSize)
	{
		throw std::out_of_range("Invalid figure number!");
	}
	else
	{
		shapes[index - 1]->translate(dx, dy);
		std::cout << "Translated figure";
	}
}

void SVGDocument::withinRectangle(double x, double y, double width, double height) const
{
	bool found = false;

	size_t shapesSize = shapes.size();

	for (size_t i = 0; i < shapesSize; i++)
	{
		if (shapes[i]->containsPoint(x, y) && shapes[i]->containsPoint(x + width, y) && shapes[i]->containsPoint(x, y + height) && shapes[i]->containsPoint(x + width, y + height))
		{
			std::cout << i + 1 << ". ";
			shapes[i]->print();

			found = true;
		}
	}

	if (!found)
	{
		std::cout << "No figures are located within rectangle " << x << " " << y << " " << width << " " << height << std::endl;
	}
}

void SVGDocument::withinCircle(double cx, double cy, double r) const
{
	bool found = false;

	size_t shapesSize = shapes.size();

	for (size_t i = 0; i < shapesSize; i++)
	{
		if (shapes[i]->containsPoint(cx, cy))
		{
			std::cout << i + 1 << ". ";
			shapes[i]->print();

			found = true;
		}
	}

	if (!found)
	{
		std::cout << "No figures are located within circle " << cx << " " << cy << " " << r << std::endl;
	}
}

std::string SVGDocument::getShapeType(int index) const
{
	if (index < 1 | index > shapes.size())
	{
		return "unknown";
	}

	return shapes[index - 1]->getType();
}