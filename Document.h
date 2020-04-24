#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

class Document
{

private:
    vector<std::string> *_lines;
    string _lastSearch;
    vector<string>::iterator currentIt;

public:
    Document();
    ~Document();
    /*prints the current line*/
    void printCurrentLine();

    /*prints the current line number then TAB then its content e.g.-> 3n *********************/
    void printNumberedCurrentLine();

    /* prints all lines e.g.-> %p */
    void printAll();

    /*changes current line to the line number it gets*/
    void changeCurrentTo(unsigned int newCurrent);

    /*starts writing mode e.g.-> %i */
    void insert(bool backwords);

    //?????????????????????????/
    /*changes the current line for text that follows*/
    void forwardCurrent();

    /*deletes the current line e.g.-> 3d *************************/
    void deleteCurrent();

    /*search after the current line e.g.-> /text */
    void search(string text);

    /*repeat last search*/
    void repeatSearch();

    /*searches for specific text after the current line and makeing his line the current e.g.-> ?text */
    void searchAbove(string text);

    /*replace current line new one e.g.-> c(...).*/
    void replaceCurrentLine();

    /*replace this string int current line with new string e.g.-> s/old/new/*/
    void replaceStringInCurrent(string input);

    /*Join tow strings and put it on the secod row e.g.-> s/old/new/*/
    void joinString(string input);
};
