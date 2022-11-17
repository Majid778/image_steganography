#include <iostream>
#include <string>
#include "Decoder.h"
#include "Encoder.h"

using namespace std;

bool exit_program = false;

void Exit();

int main() {

	int input;
	string file_name = "";
	string text_to_encode = "";
	string decoded_text = "";
	bool ret = false;  //Boolen to keep track of the state of the function
	string tmp;

	do {

		cout << endl;  //Main menu
		cout << "Image Steganography" << endl;
		cout << endl;
		cout << "1. Encode" << endl;
		cout << "2. Decode" << endl;
		cout << "3. Exit" << endl;
		cout << endl;
		cout << "Input [1-3] : ";

		cin >> input;  //User input
		cout << endl;
		if (input != 1 && input != 2 && input != 3) {
			cout << "Input is invalid. Please try again."; //If the user inputs an invalid value an error message is printed
		}
		if (input < 1 || input > 3) {
			continue;
		}

		switch (input)
		{
		case 1:
			cout << "Enter the secret message to encode : ";
			getline(cin, tmp); 
			getline(cin, text_to_encode);
			cout << "Enter image file name: ";
			getline(cin, file_name);
			ret = Encode(text_to_encode, file_name); //Call the Encoding funciton in the header file
			if (ret) {
				cout << "Encoding successful" << endl;
			}
			else {
				cout << "Encoding failed" << endl;
			}
			break;
		case 2:
			cout << "Enter image file name to retrieve hidden text: ";
			cin >> file_name;
			ret = Decode(file_name, decoded_text); //Call the Decode function in the header file
			if (ret) {
				cout << "Decoding successful" << endl;
				cout << "Decoded message: \"" << decoded_text << "\"" << endl; //Print the decoded message in quotes
			}
			else {
				cout << "Decoding failed" << endl;
			}
			break;
		case 3:
			Exit(); //Exits the program								
				//the memory was allocated in the header files and deleted after use
		}

		

	} while (!exit_program);//Run the program until "exit_program" boolen is true.		

	return 0;
}

void Exit() { //Function to be used as a condition for looping the main body.
	cout << "Program exited successfully" << endl;
	exit_program = true;
}
