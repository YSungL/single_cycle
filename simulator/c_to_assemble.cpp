#include "process.h"
#include <iostream>
#include<fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

void c_code_to_assemble_code()
{
    ifstream fin;
    string tmpstr;
    string dir = string(".");
    vector<string> files = vector<string>();
    int file_num = -1;
    for(int i = 0; i < files.size() ; i++)
    {
        string temp = files[i];
        if(temp[-1] == "c" && temp[-2] == ".")
        {
            file_num = i;
            break;
        }
    }
    if(file_num != -1)
    {
        //fin.open(files[file_num]);
        string cmd ="gcc -S -masm=att ";
        cmd = cmd + files[file_num];
        system(cmd);
    }
    else
    {
        cout << error << endl;
        return 0;
    }

}
