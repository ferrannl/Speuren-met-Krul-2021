#include "Interpreter.hpp"
#define IsBigLetter(a) a >= 'A' && a <= 'Z'
#define IsSmallLetter(a) a >= 'a' && a <= 'z'

Interpreter::Interpreter()
{
	_stack = std::vector<std::string>();
	_commands = std::vector<std::string>();
	_labels = std::map<std::string, int>();
	_variables = std::map<std::string, std::string>();
	_callStack = std::vector<int>();
	_programCounter = 0;
	End = false;
}

void Interpreter::GetCommandos(const std::string& text)
{
	std::stringstream stream(text);
	while (stream.good()) {
		std::string line;
		std::getline(stream, line, '\n');
		_commands.push_back(line);
	}
}

void Interpreter::RunCommandos() {

	checkLabelDefinitions();
	while (_commands.size() > _programCounter) {
		std::string value = _commands[_programCounter];
		runCommando(value);
	}
}

void Interpreter::runCommando(const std::string& line) {
	//std::cout << line << std::endl;
	//if (line.empty()) {
	//	++_programCounter;
	//	return;
	//}
	std::string command = _commands[_programCounter];
	if (line.find("\\") != std::string::npos) {
		_stack.push_back(line.substr(1, line.length() - 1));
		++_programCounter;
		return;
	}
	if (line.find("add") != std::string::npos) {
		std::string firstValue = _stack.back();
		_stack.pop_back();
		std::string secondValue = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(std::stoi(firstValue) + std::stoi(secondValue)));
	}
	if (line.find("sub") != std::string::npos) {
		std::string firstValue = _stack.back();
		_stack.pop_back();
		std::string secondValue = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string((std::stoi(secondValue) - std::stoi(firstValue))));
	}
	if (line.find("=") != std::string::npos) {
		std::string value = line.substr(1, line.length() - 1);
		_variables[value] = _stack.back();
		_stack.pop_back();
	}
	if (line.find("dup") != std::string::npos) {
		_stack.push_back(_stack.back());
	}
	if (line.find("mul") != std::string::npos) {
		std::string firstValue = _stack.back();
		_stack.pop_back();
		std::string secondValue = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(std::stoi(firstValue) * std::stoi(secondValue)));
	}
	if (line.find("neg") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(-1 * (std::stoi(value))));
	}
	if (line.find("mod") != std::string::npos) {
		std::string value1 = _stack.back();
		_stack.pop_back();
		std::string value2 = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string((std::stoi(value2) % std::stoi(value1))));
	}
	if (line.find("div") != std::string::npos) {
		std::string value1 = _stack.back();
		_stack.pop_back();
		std::string value2 = _stack.back();
		_stack.pop_back();
		if (value1 == "0" || value2 == "0") {
			std::cout << "CAN'T DIVIDE ZERO" << std::endl;
			return;
		}
		else {
			_stack.push_back(std::to_string(std::stoi(value2) / std::stoi(value1)));
		}
	}
	if (line.find("abs") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(abs((std::stoi(value)))));
	}
	if (line.find("inc") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(std::stoi(value) + 1));
	}
	if (isNumber(line)) {
		_stack.push_back(line);
	}
	if (line.find("$") != std::string::npos) {
		std::string var1 = line.substr(1, line.length() - 1);
		std::string var2 = _variables[var1];
		_stack.push_back(var2);
	}
	if (line.find("cat") != std::string::npos) {
		std::string var1 = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		_stack.push_back(var2 + var1);
	}
	if (line.find("dec") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(std::stoi(value) - 1));
	}
	if (line.find(">") != std::string::npos) {
		std::string label = line.substr(1, line.length() - 1);
		_stack.push_back(label);
	}
	if (line.find("gne") != std::string::npos) {
		std::string labelValue = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		std::string var1 = _stack.back();
		_stack.pop_back();
		if (var1 != var2) {
			_programCounter = (_labels[labelValue]);
			return;
		}
	}
	if (line.find("glt") == 0) {
		std::string labelValue = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		std::string var1 = _stack.back();
		_stack.pop_back();
		if (std::stoi(var1) < std::stoi(var2)) {
			_programCounter = (_labels[labelValue]);
			return;
		}
	}
	if (line.compare("gle") == 0) {
		std::string labelValue = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		std::string var1 = _stack.back();
		_stack.pop_back();
		if (std::stoi(var1) <= std::stoi(var2)) {
			_programCounter = (_labels[labelValue]);
			return;
		}
	}
	if (line.find("ggt") == 0) {
		std::string labelValue = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		std::string var1 = _stack.back();
		_stack.pop_back();
		if (std::stoi(var1) > std::stoi(var2)) {
			_programCounter = (_labels[labelValue]);
			return;
		}
	}
	if (line.find("gge") == 0) {
		std::string labelValue = _stack.back();
		_stack.pop_back();
		std::string var2 = _stack.back();
		_stack.pop_back();
		std::string var1 = _stack.back();
		_stack.pop_back();
		if (std::stoi(var1) >= std::stoi(var2)) {
			_programCounter = _labels[labelValue];
			return;
		}
	}
	if (line.find("gto") == 0) {
		gto();
		return;
	}
	if (line.find("fun") == 0) {
		_callStack.push_back(_programCounter + 1);
		gto();
		return;
	}
	if (line.find("ret") == 0) {
		_programCounter = _callStack.back();
		_callStack.pop_back();
		return;
	}
	if (line.find("rev") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		reverse(value.begin(), value.end());
		_stack.push_back(value);
	}
	if (line.find("slc") != std::string::npos) {
		int to = std::stoi(_stack.back());
		_stack.pop_back();
		int from = std::stoi(_stack.back());
		_stack.pop_back();
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(value.substr(from, (to - from)));
	}
	if (line.find("idx") != std::string::npos) {
		std::string index = _stack.back();
		_stack.pop_back();
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(value.substr(std::stoi(index), 1));
	}
	if (line.find("len") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(std::to_string(value.size()));
	}
	if (line.find("rot") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		std::string result;
		for (char const& letter : value)
		{
			if (IsBigLetter(letter))
				result += ((int)letter - (int)'A' + 13) % 26 + 'A';
			else if (IsSmallLetter(letter))
				result += ((int)letter - (int)'a' + 13) % 26 + 'a';
			else
				result += letter;
		}
		_stack.push_back(result);
	}
	if (line.find("enl") != std::string::npos) {
		std::string value = _stack.back();
		_stack.pop_back();
		_stack.push_back(value + '\n');
	}
	if (line.find("end") != std::string::npos) {
		End = true;
	}
	_programCounter++;
}

const std::string Interpreter::GetFileName()
{
	const std::string filename = _stack.back();
	clearRun();
	return filename.c_str();
}

void Interpreter::clearRun() {
	_stack.clear();
	_commands.clear();
	_labels.clear();
	_variables.clear();
	_callStack.clear();
	_programCounter = 0;
}

void Interpreter::checkLabelDefinitions()
{
	while (_programCounter < _commands.size()) {
		std::string line = _commands[_programCounter];
		++_programCounter;
		if (!line.empty() && line.find(":") != std::string::npos) {
			addLabelDefinition(line);
		}
	}
	_programCounter = 0;
}

void Interpreter::addLabelDefinition(const std::string& line) {
	const std::string& label = line.substr(1, line.length() - 1);
	if (_labels.count(label) == 0) {
		_labels.insert(std::pair<std::string, int>(label, _programCounter));
	}
}

bool Interpreter::isNumber(std::string s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Interpreter::gto() {
	std::string labelValue = _stack.back();
	_stack.pop_back();
	_programCounter = (_labels[labelValue]);
}