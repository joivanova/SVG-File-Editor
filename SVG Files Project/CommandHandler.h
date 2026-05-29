#pragma once
#include <string>
#include "SVGDocument.h"

class CommandHandler
{
public:
	bool executeCommand(const std::string& command, SVGDocument& doc);

private:
	void openCommand(const std::string& command, SVGDocument& doc);
	void closeCommand(SVGDocument& doc);

	void saveCommand(SVGDocument& doc);
	void saveAsCommand(const std::string& command, SVGDocument& doc);

	void printCommand(SVGDocument& doc);

	void helpCommand();
	
	void eraseCommand(const std::string& command, SVGDocument& doc);
	void createCommand(const std::string& command, SVGDocument& doc);
	void translateCommand(const std::string& command, SVGDocument& doc);
	void withinCommand(const std::string& command, SVGDocument& doc);
};