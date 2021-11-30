#include "MainController.hpp"

MainController::MainController() {
	_curlHandler = std::make_unique<Curl>();
	_outputHandler = std::make_unique<Output>();
	_interpreter = std::make_unique<Interpreter>();
	std::string _fileName = "start.txt";

	while (!_interpreter->End) {
		std::string text = _curlHandler->GetText(_fileName);
		std::cout << text << std::endl;
		_interpreter->GetCommandos(text);
		_interpreter->RunCommandos();
		_fileName = _interpreter->GetFileName();
	}
	std::cout << _fileName << std::endl;
}
