#pragma once
#include "BitmapHelper.h"

#define MAX_FILE_NAME_SIZE                      1024                            

bool Encode(string s, string file_name) {
    unsigned char*** imageData;  //Image data pointer
    int imageWidth = 0;   //Image width
    int imageHeight = 0;  //Image height

    bool b1 = ReadBitmapImage(file_name.c_str(), imageData, imageWidth, imageHeight); //Read the image data via the given library

    if (!b1) {   //Checks if the image read operation was a success.
        return false;
    }

    int n = s.size();  //Size of the secret text
    int val = 0;  //Variable to store numerical ASCII value of the characters of the secret string 
    int bit_val = 0; //Variable to store bit values of the selected ASCII character
    int counter = 0; //A counter that keeps track of the count of imageData bytes updated
    int row = 0; //Current row
    int col = 0; //Current column
    int channel = 0; //Current channel

    for (int i = 0; i < n + 1; i++) {  //Loop to go through all the characters of the string
        char c = s[i]; //Set current characeter in the string to char 'c'
        val = (int)c;  //Get ASCII value of 'c'

        for (int j = 0; j < 8; j++) {  //Loop for 8 times to extract the 8 bits representing the character.
            bit_val = val % 2;  //Get LSB of val.       
            val = val / 2;                                                      
            channel = counter % 3; //Get the current channel.
            col = (counter / 3) % imageWidth; //Get the current column.
            row = (counter / (3 * imageWidth)) % imageHeight; //Get the current row.

            imageData[row][col][channel] = ((imageData[row][col][channel] >> 1) << 1) + bit_val;  //Calculate the value that needs to be written.

            counter++;    //Increase counter to move to next byte in the image
        }
    }

    int file_name_size = file_name.size();
    char encoded_file_name[MAX_FILE_NAME_SIZE];   //File name for the encoded image
    memcpy(encoded_file_name, &file_name[0], file_name_size);  //Copy the already given file name

    if (file_name_size > 4) {                          //This is to remove the ".bmp" part of the file name given. 
        encoded_file_name[file_name_size - 1] = '\0';  //  if have the filename string : "Earth.bmp"
        encoded_file_name[file_name_size - 2] = '\0';  // after removing the .bmp part. Now we have : "Earth"
        encoded_file_name[file_name_size - 3] = '\0';  //  so later we can add "_encoding.bmp" part, so the final name would be "Earth_encoding.bmp"
        encoded_file_name[file_name_size - 4] = '\0';
    }

    string end_file_name(encoded_file_name);
    end_file_name += "_encoded.bmp";


    bool b2 = WriteBitmapImage(end_file_name.c_str(), imageData, imageWidth, imageHeight);  //Write the new .bmp file

    ReleaseMemory(imageData, imageHeight, imageWidth);//Release the memory

    if (!b2) {    //If .bmp file write was unsuccessful, return false
        return false;
    }

    cout << "Encoded image file name : " << end_file_name << endl;

    return true;

}
