#include "SVGDocument.h"
#include <iostream>
SVGDocument::~SVGDocument()
{
	size_t shapeSize = shapes.size();

	for (size_t i = 0; i < shapeSize; i++)
	{
		delete shapes[i];
	}
	/*for (Shape* s : shapes)
	{
		delete s;
	}*/
}

void SVGDocument::setFilename(const std::string& file)
{
	filename = file;//zapazva imeto na fajla; pr:doc.setFilename("figures.svg)
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
		std::cout << "There is no figure number " << index << "!" << std::endl;
		return;
	}

	delete shapes[index - 1];//zashtoto erase maha pointera ot vectora no ne delete-va obekta

	shapes.erase(shapes.begin() + (index - 1));//mesti iteratora v nachaloto, sled tova na index-1 pozicii i trie elementa
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
		std::cout << "There is no figure number " << index << "!" << std::endl;
		return;
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
		if (shapes[i]->containsPoint(x,y) && shapes[i]->containsPoint(x + width, y) && shapes[i]->containsPoint(x, y + height) && shapes[i]->containsPoint(x + width, y + height))
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