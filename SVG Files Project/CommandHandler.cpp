#include "CommandHandler.h"
#include "SVGDocument.h"
#include <iostream>

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
	else if (command.substr(0, 6) == "erase ")
	{
		eraseCommand(command, doc);
	}
	else if (command == "help")
	{
		helpCommand();
	}
	else if (command == "exit")
	{
		exitCommand();
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

//NZ dali trqbva da q ima tuk
void CommandHandler::eraseCommand(const std::string& command, SVGDocument& doc)
{
	int index = std::stoi(command.substr(6));//stoi convertira string v integer

	std::string type = doc.getShapeType(index);
	doc.erase(index);

	std::cout << "Erased a " << type << " (" << index << ")\n";
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

bool CommandHandler::exitCommand()
{
	std::cout << "Exiting the program...";
	return true;//spira programata
}