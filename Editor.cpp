#include "Editor.h"
#include <algorithm>
using std::count;
#include <string>
using std::stoi;
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//Editor::Editor():{}

void Editor::loop()
{
	bool quit = false;
	string input;
	bool backwords;

	while (!quit)
	{
		getline(cin, input);

		if (input == "n")
		{
			doc.printNumberedCurrentLine();
		}
		else if (input.at(input.size() - 1) == 'n')
		{
			int lineNumber = stoi(input.substr(0, input.size() - 1));
			doc.changeCurrentTo(lineNumber);
			doc.printNumberedCurrentLine();
		}
		else if (input == "%p")
		{
			doc.printAll();
		}
		else if (input == "a")
		{
			backwords = false;
			doc.insert(backwords);
		}
		else if (input == "i")
		{
			backwords = true;
			doc.insert(backwords);
		}
		else if (input == "c")
		{
			doc.replaceCurrentLine();
		}
		else if (input == "d")
		{
			doc.deleteCurrent();
		}
		else if (input.at(input.size() - 1) == 'd')
		{
			int lineNumber = stoi(input.substr(0, input.size() - 1));
			doc.changeCurrentTo(lineNumber);
			doc.deleteCurrent();
		}
		else if (input.at(input.size() - 1) == 'j')
		{

			doc.joinString(input);
		}
		else if ((input.substr(0, 2) == "s/") && (input[input.size() - 1] == '/' && count(input.begin() + 2, input.end() - 2, '/') == 1))
		{
			doc.replaceStringInCurrent(input);
		}
		else if (input == "Q")
		{
			quit = true;
		}
		else if (input[0] == '/')
			if (input.length() == 1)
			{
				doc.repeatSearch();
			}
			else
			{
				doc.search(input.substr(1));
			}
		else if (input[0] == '?')
		{
			doc.searchAbove(input.substr(1));
		}
		else if (std::find_if(input.begin(), input.end(), ::isdigit) != input.end())
		{
			doc.changeCurrentTo(stoi(input));
		}
		else
			cout << "?" << endl;
	}

}
