#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>

#include "program2.h"

using namespace std;

int main()
{
    char userInput; //variable for user input
    ifstream icin;  //declare input stream

    string startTime;
    icin.open("program2.dat");  //open input file

    GetUserOption(icin);    //get user option


    return 0;
}

