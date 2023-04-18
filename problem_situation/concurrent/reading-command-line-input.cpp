// =================================================================
//
// File: reading-command-line-input.cpp
// Author: Pedro Perez
// Description: This file contains an example of how you can input 
//              data (eg filenames) from the command line.
//
//              To compile: g++ reading-command-line-input.cpp -o app
//
//              To run: ./app ../csharp_examples/*.cs
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>

using namespace std;

// @param argc, the number of arguments received from the command 
//              line.
// @param argv, an array of character strings containing the words 
//              taken from the command line.
// Note: argv[0] will always be the name of the executable file.
int main(int argc, char* argv[]) {
    for (int i = 1; i< argc; i++) {
        cout << "argv[" << i << "] = " << argv[i] << "\n";
    }
    return 0;
}