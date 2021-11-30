#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>  
#include <sstream>
#include <iostream>
#include "../Handlers/Output.hpp"
#include "../Handlers/Curl.hpp"

class Interpreter
{
private:
	std::string _command;
	std::vector <std::string> _stack;
	std::vector<std::string> _commands;
	std::map<std::string, int> _labels;
	std::vector<int> _callStack;
	std::map<std::string, std::string> _variables;
	void checkLabelDefinitions();
	void addLabelDefinition(const std::string& value);
	bool isNumber(std::string s);
	void runCommando(const std::string& line);
	size_t _programCounter;
	void clearRun();
	void gto();

public:
	Interpreter();
	void GetCommandos(const std::string& text);
	void RunCommandos();
	std::vector<std::string> Commands;
	bool End;
	const std::string GetFileName();
};

