
/*
FUNCTIONS:
	
	nigga: 
		move dataptr to the right by one

	NIGGA: 
		move dataptr to the left by one

	Nigga: 
		increment the selected cell

	niggA:  
		decrement the selected cell

	NIggA:  
		output selected cell to the console as a character

	nIGGa:
		output selected cell as a literal integer

	niGGa:  
		replace the selected cell with user input (one character)

	NiggA:
		replace the selected cell with user input (literal int)

	nigger:  
		jump forwards to matching "NIGGER" instruction if selected cell is zero

	NIGGER:  
		jump backwards to matching "nigger" instruction if selected cell isn't zero

	nigadd (not case sensitive):
		add the selected cell to the cell before it, and write the result to the cell after it

	nigsub (not case sensitive):
		subtract the selected cell from the cell before it, and write the result to the cell after it

	nigmul (not case sensitive):
		multiply the selected cell with the cell before it, and write the result to the cell after it

	nigdiv (not case sensitive):
		divide the selected cell by the one before it, and write the result to the cell after it

	white person (not case sensitive):  
		kills the program

COMPILER FLAGS:

	!define=*macro name* { *code* } (the spaces are required): 
		everywhere *macro name* appears in your code will run *code* like a function

	!tapelength=*new tapelength*: 
		changes the length of the datatape
*/

#include <iostream>
#include <string>
#include <vector>

#define CHAR_MAX_VALUE 255

std::vector<char>* datatape;
unsigned int dataptr;

std::vector<std::string> split(std::string str, char delimiter) {
	
	std::vector<std::string> result;

	std::string current = "";
	for (int i = 0; i < str.size(); i++) {

		if (str[i] == delimiter) {

			if (current == "")
				continue;

			result.push_back(current);
			current = "";
			continue;
		}

		current += str[i];
	}
	if (current != "")
		result.push_back(current);

	return result;
}

std::string lowercase(std::string str) {

	for (int i = 0; i < str.length(); i++)
		str[i] = std::tolower(str[i]);

	return str;
}

int instructionToInt(std::string instruction) {

	if (instruction == "nigga")
		return 1;

	if (instruction == "NIGGA")
		return 2;

	if (instruction == "Nigga")
		return 3;

	if (instruction == "niggA")
		return 4;

	if (instruction == "NIggA")
		return 5;

	if (instruction == "niGGa")
		return 6;

	if (instruction == "nigger")
		return 7;

	if (instruction == "NIGGER")
		return 8;

	if (lowercase(instruction) == "nigadd")
		return 9;

	if (lowercase(instruction) == "nigsub")
		return 10;

	if (lowercase(instruction) == "nigmul")
		return 11;

	if (lowercase(instruction) == "nigdiv")
		return 12;

	if (instruction == "nIGGa")
		return 13;

	if (lowercase(instruction) == "white")
		return 100;

	if (lowercase(instruction) == "person")
		return 101;

	return 0;
}

void doInitInstruction(std::vector<std::string>* code, unsigned int instructionIndex) {

	std::vector<std::string> instructionarr = split((*code)[instructionIndex], '=');

	if (instructionarr[0] == "!tapelength") {

		int value;

		value = std::stoi(instructionarr[1]);
		
		if (value < 0)
			return;

		datatape->clear();
		for (int i = 0; i < value; i++)
			datatape->push_back(0);

		return;
	}

	if (instructionarr[0] == "!define") {

		if (instructionarr[0] != "{")
			return;

		std::vector<std::string> contents;
		
		for (int i = instructionIndex + 2; i < code->size(); i++) {

			if ((*code)[i] == "}")
				break;

			contents.push_back((*code)[i]);
		}

		for (int i = 0; i < code->size(); i++) {

			if ((*code)[i] == instructionarr[1]) {

				code->erase(code->begin() + (i - 1));
				code->insert(code->begin() + (i - 1), contents.begin(), contents.end());
			}
		}
	}
}

void init() {

	//init the data tape with a starting length of 100
	delete(datatape);
	datatape = new std::vector<char>();

	for (int i = 0; i < 200; i++)
		datatape->push_back(0);

	dataptr = 0;

	system("cls");
}

std::vector<char>* compile(std::string* code) {

	std::vector<char>* result = new std::vector<char>();

	std::vector<std::string>* codearr = new std::vector<std::string>(split(*code, ' '));

	for (int i = 0; i < codearr->size(); i++) {

		if ((*codearr)[i][0] == '!') {

			doInitInstruction(codearr, i);
		}
	}

	for (int i = 0; i < codearr->size(); i++) {

		result->push_back(instructionToInt((*codearr)[i]));
	}

	for (int i = 0; i < result->size(); i++) {

		if ((*result)[i] != 0)
			continue;

		result->erase(result->begin() + (i - (i == 0? 0 : 1)));
	}

	return result;
}

void interpret(std::vector<char>* code) {

	for (int i = 0; i < code->size(); i++) {

		switch ((*code)[i]) {

		case 1:
			if (dataptr == datatape->size() - 1) {

				dataptr = 0;
				break;
			}

			dataptr++;
			break;

		case 2:
			if (dataptr == 0) {

				dataptr = datatape->size() - 1;
				break;
			}

			dataptr--;
			break;

		case 3:
			(*datatape)[dataptr]++;
			break;

		case 4:
			(*datatape)[dataptr]--;
			break;

		case 5:
			std::cout << (*datatape)[dataptr];
			break;

		case 6:
			std::cin >> (*datatape)[dataptr];
			break;

		case 7:
			if ((*datatape)[dataptr] != 0)
				break;
				
			for (int j = 1; j != 0; ) {
				
				i++;
				if ((*code)[i] == 8)
					j--;
				
				if ((*code)[i] == 7)
					j++;
			}
			
			i++;
			break;

		case 8:
			if ((*datatape)[dataptr] == 0)
				break;
				
			for (int j = 1; j != 0; ) {
			
				i--;
				if ((*code)[i] == 7)
					j--;
				
				if ((*code)[i] == 8)
					j++;
			}
				
			i++;
			break;

		case 9:
			(*datatape)[dataptr + (dataptr == CHAR_MAX_VALUE ? -CHAR_MAX_VALUE : 1)] =
				(*datatape)[dataptr] + (*datatape)[dataptr - (dataptr == 0 ? -CHAR_MAX_VALUE : 1)];

			break;

		case 10:
			(*datatape)[dataptr + (dataptr == CHAR_MAX_VALUE ? -CHAR_MAX_VALUE : 1)] =
				(*datatape)[dataptr - (dataptr == 0 ? -CHAR_MAX_VALUE : 1)] - (*datatape)[dataptr];

			break;

		case 11:
			(*datatape)[dataptr + (dataptr == CHAR_MAX_VALUE ? -CHAR_MAX_VALUE : 1)] =
				(*datatape)[dataptr] * (*datatape)[dataptr - (dataptr == 0 ? -CHAR_MAX_VALUE : 1)];

			break;

		case 12:
			(*datatape)[dataptr + (dataptr == CHAR_MAX_VALUE ? -CHAR_MAX_VALUE : 1)] =
				(*datatape)[dataptr] / (*datatape)[dataptr - (dataptr == 0 ? -CHAR_MAX_VALUE : 1)];

			break;

		case 13:
			std::cout << (int)(*datatape)[dataptr];
			break;

		case 14:
			int inpt;
			std::cin >> inpt;
			if (inpt <= CHAR_MAX_VALUE)
				(*datatape)[dataptr] = inpt;

			break;

		case 100:
			if ((*code)[i + 1] == 101)
				return;

			break;
		}
	}
}

int main() {

	std::string* code = new std::string();

	while (true) {

		std::string input;
		std::cin >> input;

		if (input == "run")
			break;

		*code += " ";
		*code += input;
	}

	init();

	std::vector<char>* compiledCode = compile(code);

	for (int i = 0; i < compiledCode->size(); i++)
		std::cout << (int)(*compiledCode)[i] << ' ';
	std::cout << std::endl << std::endl;

	interpret(compiledCode);
}
