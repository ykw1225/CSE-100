/*
* Name:  Chao Huang & Yeung Kit Wong
* Date:  AUG 5, 2016
* File:  main.cpp
*/

#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include<fstream>
#include<string>

/**
*  IMPORTANT!! YOU MUST USE THE FOLLOWING LINES OF CODE FOR PROMPTS AND OUTPUTS:
*
*  To output size of tree:
*  cout << "Size of tree: " << size << "\n";
*
*  To output height of tree:
*  cout << "Height of tree: " << height << "\n";
*
*  To prompt the user to enter a name:
*  cout << "Enter actor/actress name: " << "\n";
*
*  To tell the user that actor/actress name was found:
*  cout << name << " found!" << "\n";
*
*  To tell the user that actor/actress name was NOT found:
*  cout << name << " NOT found" << "\n";
*
*  To prompt the user to try again:
*  cout << "Search again? (y/n)" << "\n";
*
*
*
*  Use cin to process user input.
*
*
*
*  You MUST output size, then height, then prompt the user to search, as above.
*
*
*
*  You MUST have the prompt for entering the name appear if and only if
*  the user input for trying again is "y" followed by the return key
*
*  You MUST have the program exit (exiting the prompt loop) if and only if
*  the user input for trying again is "n" followed by the return key
*
*  You should handle other inputs for the retry prompt,
*  but we will not be testing them.
*
*  Note that size, height, and name are local variables in main that you
*  should update accordingly. Also note that actor/actress names will be
*  in all caps, last name followed by first name
*  (except in odd cases, eg. "50 CENT" and "ICE-T")
*/

using namespace std;

int main(int argc, char* argv[])
{
	//Size of tree should be stored in local variable size.
	//Height of tree should be stored in local variable height.
	//Input name will be stored in a string name
	unsigned int size = 0;
	unsigned int height = 0;
	std::string name = "";

	//Check for Arguments
	if (argc != 2) {
		cout << "Invalid number of arguments.\n"
			<< "Usage: ./main <input filename>.\n";
		return -1;
	}

	//Open file
	ifstream in;
	in.open(argv[1], ios::binary);

	//Check if input file was actually opened
	if (!in.is_open())
	{
		cout << "Invalid input file. No file was opened. Please try again.\n";
		return -1;
	}

	//Check for empty file
	in.seekg(0, ios_base::end);
	unsigned int len = in.tellg();
	if (len == 0)
	{
		cout << "The file is empty. \n";
		return -1;
	}

	//Resets the stream to beginning of file
	in.seekg(0, ios_base::beg);



	/*
	********************************************
	* main function implementation goes below  *
	********************************************
	*/

	// make a bst to save data
	BST<string> tree;

	// reading file, store into bst until reach the end of file
	while (!in.eof()) {

		// read a line of file
		getline(in, name);

		// store the data into the bst
		tree.insert(name);

	} // end of reading a file

	if (in.is_open())
	{
		in.close();
	}

	// output size and height, prompt user to search
	size = tree.size();
	height = tree.height();
	cout << "Size of tree: " << size << "\n";
	cout << "Height of tree: " << height << "\n";

	// string variable to store the user choice
	string choice = "y";

	// keep asking user if want to continue on searching until say y
	while (choice == "y") {

		// asking user to enter a name to search
		cout << "Enter actor/actress name: " << "\n";

		// store the input to name
		getline(cin, name);

		// found item if iterator not point to last node
		if (tree.find(name) != tree.end())
			cout << name << " found!" << "\n";

		// the name is not found
		else
			cout << name << " NOT found!" << "\n";

		// ask user if want to do it again
		cout << "Search again? (y/n)" << "\n";
		getline(cin, choice);

		// input handling and retry prompt
		while (choice != "y" && choice != "n") {
			cout << "Please enter y / n only! Search again?" << "\n";
			getline(cin, choice);
		}

		// exit if user enter n
		if (choice == "n") break;

	} // end of outter while

	return 0;
}
