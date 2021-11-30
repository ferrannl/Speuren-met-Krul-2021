#pragma once
#include "../Handlers/Curl.hpp"
#include "../Handlers/Output.hpp"
#include "../Interpreters/Interpreter.hpp"

class MainController
{

private:
	std::unique_ptr<Curl> _curlHandler;
	std::unique_ptr<Interpreter> _interpreter;
	std::unique_ptr<Output> _outputHandler;
	std::string _fileName;


public:
	MainController();
};

