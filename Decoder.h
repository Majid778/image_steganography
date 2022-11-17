#pragma once
#include "BitmapHelper.h"

using namespace std;

bool Decode(string file_name, string& ss) {
    unsigned char*** imageData;  //Image data holding pointer
    int imageWidth = 0;
    int imageHeight = 0;

    bool b1 = ReadBitmapImage(file_name.c_str(), imageData, imageWidth, imageHeight); //Read the .bmp file

    if (!b1) {   //If read .bmp fails return false
        return false;
    }

    int row = 0;//current row
    int col = 0;//current col
    int channel = 0;//current channel
    char c;
    int collected_bit_count = 0; //counter to verify that all 8 bits were collected
    int curr_bit = 0;//current bit collected
    int val = 0;//variable to store the number represented by the 8bits collected
    int counter = 0;//counter to navigate the image.
    ss = "";
    int string_index = 0;

    while (true) {
        channel = counter % 3;//calculate the current channel
        col = (counter / 3) % imageWidth;  //calculate the current column
        row = (counter / (3 * imageWidth)) % imageHeight;//calculate the current row

        curr_bit = imageData[row][col][channel] % 2; //get the LSB of current image byte

        val += (curr_bit << collected_bit_count); //get the value of the ASCII by shifting the current bit to the left each iteration of the loop                                                                                                   
        collected_bit_count++; //collected_bit_count will increase by one each loop.    

        if (collected_bit_count == 8) { //Once 8 bit is collected, we found one character.
            string temp(1, (char)val);
            ss += temp;
            if (0 == val) {
                break;  //If the character is a NULL character, end the loop.
            }
            val = 0;
            collected_bit_count = 0;
        }
        counter++;
    }

    ReleaseMemory(imageData, imageHeight, imageWidth);  //Release memory

    return true;
}