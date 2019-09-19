/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Daniel Shapiro
 * Date        : 9/26/18
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." - Daniel Shapiro
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	// Iterates through the input string checking that each character is a lower case English letter
	// based off of the islower function from cctype.
	bool track;
	for(unsigned int i = 0; i<s.length(); i++){
		if(islower(s.at(i))){
			track = true;
		}else{
			track = false;
			break;
		}
	}
	return track;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	// Iterates through the input string getting the character at each index, and checking the storage
	// value to see if the same character was found already by &'ing the storage with a checker variable
	// that is used to find the correct place in the storage's bits that corresponds with the right letter.
	// This was done by subtracting 97 from the value of the character since 97 is the ascii value for a.
	// Reassigning the value for storage was done by |'ing it with the value for checker.
	unsigned int storage = 0;
	unsigned int checker = 1;
	bool track;
	for(unsigned int i = 0; i< s.length(); i++){
		checker = checker<<((int) s.at(i) - 97);
		if((storage & checker) == 0){
			storage = (storage | checker);
			checker = 1;
			track = true;
		}else{
			track = false;
			break;
		}

	}
	return track;

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	// Checks to make sure that the user inputs a single string of only lowercase English letters,
	// and alerts the user if they did not do so, then
	// calls the is_all_lowercase() and all_unique_letters() functions to check if the string consists of
	// unique letters, and displays the result to the user.
	if(argc == 1){
		cerr << "Usage: ./unique <string>"<<endl;
	}else if(argc > 2){
			cerr << "Usage: ./unique <string>"<<endl;
	}else if(is_all_lowercase(argv[1]) == false){
			cerr << "Error: String must contain only lowercase letters."<<endl;
	}else if(is_all_lowercase(argv[1]) && all_unique_letters(argv[1])){
		cout << "All letters are unique." <<endl;
	}else{
		cout << "Duplicate letters found." <<endl;
	}






}
