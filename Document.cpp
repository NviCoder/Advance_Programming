#include "Document.h"

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

Document::Document() : _lines(new vector<string>)
{
}

Document::~Document()
{
	_lines->clear();
	delete _lines;
}

void Document::printNumberedCurrentLine()
{

	if (_lines->size() != 0)
	{
		int lineNum = std::distance(_lines->begin(), currentIt) + 1;
		cout << lineNum << "\t" << *currentIt << endl;
	}
	else
		cout << "?" << endl;
}

void Document::printAll()
{
	if (_lines->size() != 0)
	{
		vector<string>::iterator it;
		for (it = _lines->begin(); it < _lines->end(); it++)
			cout << *it << endl;
	}
	else
		cout << "?" << endl;
}

void Document::changeCurrentTo(unsigned int newCurrent)
{
	if (newCurrent <= _lines->size())
	{
		currentIt = _lines->begin();
		advance(currentIt, newCurrent - 1);
	}
	else
		cout << "?" << endl;
}

void Document::insert(bool backwards)
{
	bool end = false;
	string input;

	while (!end)
	{
		input = "";
		getline(cin, input);
		if (input == ".")
			end = true;
		else if (_lines->size() == 0)
		{
			_lines->push_back(input);
			currentIt = _lines->begin();
		}
		else if (backwards)
		{
			currentIt = _lines->insert(currentIt, input); //inserts before the iterator
		}
		else
		{
			currentIt = _lines->insert(next(currentIt), input); //inserts after the iterator
		}
	}
}

void Document::deleteCurrent()
{
	if (_lines->size() != 0)
	{
		vector<string>::iterator it = currentIt;

		//one line in vector
		if (_lines->size() == 1)
		{
			_lines->erase(currentIt);
		}
		//few lines in vector, current is the head
		else if (currentIt == _lines->begin())
		{
			currentIt++;
			_lines->erase(it);
		}
		// few lines in the vector, current is not the head
		else
		{
			currentIt++;
			_lines->erase(it);
		}
	}
}

void Document::searchAbove(string text)
{
	_lastSearch = text;

	if (_lines->size() > 0)
	{

		vector<string>::iterator it;
		for (it = currentIt; it >= _lines->begin(); it--)
		{
			if ((*it).find(text) != string::npos)
			{
				currentIt = it;
				cout << (*it) << endl;
				return;
			}
		}
	}
	cout << "?" << endl;
}

void Document::repeatSearch()
{
	search(_lastSearch);
}

void Document::search(string text)
{
	_lastSearch = text;

	if (_lines->size() > 0)
	{
		vector<string>::iterator it = currentIt;

		do
		{
			if (++it == _lines->end())
				it = _lines->begin();
			if ((*it).find(text) != string::npos)
			{
				currentIt = it;
				cout << (*it) << endl;
				return;
			}

		} while (it != currentIt);
	}
	cout << "?" << endl;
}

void Document::replaceCurrentLine()
{
	if (_lines->size() > 0)
	{

		bool end = false;
		string newLine;

		while (!end)
		{
			newLine = "";
			getline(cin, newLine);
			if (!newLine.compare("."))
			{
				end = true;
			}
			else
			{
				*currentIt = newLine;
				cout << newLine << endl;
			}
		}
	}
	else
		cout << "?" << endl;
}

void Document::replaceStringInCurrent(string input)
{

	string oldNNew = input.substr(2, input.size() - 3); //cut unnecessary head and tail
	size_t middle = oldNNew.find('/');
	string oldString = oldNNew.substr(0, middle);
	string newString = oldNNew.substr(middle + 1);

	size_t index;
	while ((index = (*currentIt).find(oldString)) != string::npos)
	{
		(*currentIt).replace(index, oldString.size(), newString);
	}
}

void Document::joinString(string input)
{

	string oldNNew = input.substr(0, input.size() - 1);
	size_t middle = oldNNew.find(',');
	int line1 = stoi(oldNNew.substr(0, middle));
	int line2 = stoi(oldNNew.substr(middle + 1));

	string first = _lines -> at(line1 - 1);
	string second = _lines -> at(line2 - 1);

	changeCurrentTo(line2);
	deleteCurrent();
	string sendIt = "s/" + first + "/" + first + second;
	replaceStringInCurrent(sendIt);

}
