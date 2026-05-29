#include "CommandHandler.h"
#include "SVGDocument.h"
#include <iostream>
#include <sstream>

bool CommandHandler::executeCommand(const std::string& command, SVGDocument& doc)
{
	if (command.substr(0,5) == "open ")
	{
		openCommand(command, doc);
	}
	else if (command == "close")
	{
		closeCommand(doc);
	}
	else if (command == "save")
	{
		saveCommand(doc);
	}
	else if (command.substr(0, 7) == "saveas ")
	{
		saveAsCommand(command, doc);
	}
	else if (command == "print")
	{
		printCommand(doc);
	}	
	else if (command == "help")
	{
		helpCommand();
	}
	else if (command == "exit")
	{
		return true;
	}
	else if (command.substr(0, 6) == "erase ")
	{
		eraseCommand(command, doc);
	}
	else if (command.substr(0, 7) == "create ")
	{
		createCommand(command, doc);
	}
	else if (command.substr(0, 9) == "translate ")
	{
		translateCommand(command, doc);
	}
	else if (command.substr(0, 6) == "within ")
	{
		withinCommand(command, doc);
	}
	else
	{
		std::cout << "Unknown command!" << std::endl;//TODO da izvajda syobshtenie
	}

	return false;//prodyljava programata
}

void CommandHandler::openCommand(const std::string& command, SVGDocument& doc)
{
	std::string file = command.substr(5);

	doc.load(file);
	std::cout << "Successfully opened " << doc.getFilename() << std::endl;
}
void CommandHandler::closeCommand(SVGDocument& doc)
{
	doc.close();

	std::cout << "Successfully closed" << doc.getFilename() << std::endl;
}

void CommandHandler::saveCommand(SVGDocument& doc)
{
	doc.save();

	std::cout << "Successfully saved" << doc.getFilename() << std::endl;
}
void CommandHandler::saveAsCommand(const std::string& command, SVGDocument& doc)
{
	std::string file = command.substr(7);

	doc.saveAs(file);
	std::cout << "Successfully saved another " << doc.getFilename() << std::endl;
}

void CommandHandler::printCommand(SVGDocument& doc)
{
	doc.print();
}

void CommandHandler::helpCommand()
{
	std::cout << "The following commands are supported:\n";
	std::cout << "open <file> opens <file>\n";
	std::cout << "close closes currently opened file\n";
	std::cout << "save saves the currently open file\n";
	std::cout << "saveas <file> saves the currently open file in <file>\n";
	std::cout << "help prints this information\n";
	std::cout << "exit exists the program\n";
}

void CommandHandler::eraseCommand(const std::string& command, SVGDocument& doc)
{
	int index = std::stoi(command.substr(6));//stoi convertira string v integer

	std::string type = doc.getShapeType(index);
	doc.erase(index);

	std::cout << "Erased a " << type << " (" << index << ")\n";
}

void CommandHandler::createCommand(const std::string& command, SVGDocument& doc)
{
	std::stringstream ss(command);
	std::string type;

	ss >> type;//create
	ss >> type;//rectangle/circle/line

	if (type == "rectangle")
	{
		double x, y, width, height;
		std::string fill;
		ss >> x >> y >> width >> height >> fill;

		doc.create(new Rectangle(x, y, width, height, fill));
	}
	else if (type == "circle")
	{
		double cx, cy, r;
		std::string fill;
		ss >> cx >> cy >> r >> fill;
		doc.create(new Circle(cx, cy, r, fill));
	}
	else if (type == "line")
	{
		double x1, y1, x2, y2;
		std::string stroke;
		ss >> x1 >> y1 >> x2 >> y2 >> stroke;
		doc.create(new Line(x1, y1, x2, y2, stroke));
	}
	else
	{
		throw std::invalid_argument("Invalid figure type!");
	}

	std::cout << "Succesfully created figure!" << std::endl;
}

void CommandHandler::translateCommand(const std::string& command, SVGDocument& doc)
{
	std::stringstream ss(command);
	std::string temp;

	ss >> temp; //translate

	double horizontal, vertical;
	ss >> horizontal >> vertical;

	if (ss.eof())
	{
		doc.translate(horizontal, vertical); //za vsichki figuri
	}
	else
	{
		int index;
		ss >> index;

		doc.translate(horizontal, vertical, index); // za edna figura
	}
	std::cout << "Translated successfully!" << std::endl;
}

void CommandHandler::withinCommand(const std::string& command, SVGDocument& doc)
{
	std::stringstream ss(command);
	std::string temp;

	ss >> temp; //within
	ss >> temp; //rectangle/circle

	if (temp == "rectangle")
	{
		double x, y, width, height;
		ss >> x >> y >> width >> height;
		doc.withinRectangle(x,y,width,height);
	}
	else if (temp == "circle")
	{
		double cx, cy, r;
		ss >> cx >> cy >> r;
		doc.withinCircle(cx, cy, r);
	}
	else
	{
		throw std::invalid_argument("Invalid within command!");
	}
}