#include "Controllers/MainController.hpp"
#include <iostream>
#include <exception>

int main(int argc, char* argv[])
{
	try {
		std::unique_ptr<MainController> mainController = std::make_unique<MainController>();
	}
	catch (const std::exception& ex) {
		std::cerr << argv[0] << ": " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << argv[0] << ": unknown error\n";
		return EXIT_FAILURE;
	}
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}