#include <iostream>
#include<fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <bitset>
using namespace std;
/*
class r_type
{
private:
    string opcode;
    string rs;
    string rt;
    string rd;
    string shamt;
    string funct;
public:



};
class i_type
{
private:
    string opcode;
    string rs;
    string rt;
    string immed;
public:
};
class j_type
{
private:
    string opcode;
    string addr;
public:

};
class s_type
{
private:
    string opcode;
public:

};
*/
int main()
{

    FILE* fp;
    fp = fopen("iimage.bin" , "rb");
    if (!fp)
        return 1 ;
    unsigned char buff;
    vector<unsigned char>inst;
    int cnt = 0, line = 0;
    while(fread(&buff,sizeof(char),1,fp) == 1)
    {
        inst.push_back(buff);

    }
    vector<string >binary;
    string tempbin = "";
    for(int i = 0 ; i < inst.size() ; i++)
    {
        bitset<8> bin(inst[i]); //nest block bin is new declare
        string str = bin.to_string<char,std::string::traits_type,std::string::allocator_type>();
        tempbin = tempbin + str;
        if((i+1)%4 == 0)
        {
            binary.push_back(tempbin);
            tempbin = "";
        }
    }
    vector<string > ins;
    int* label = (int*) malloc (sizeof(int));
    vector<string > pc;
    for(int i = 0 ; i < binary.size(); i++)
    {
        char* temp_bin = strdup(binary[i].c_str());
        char *opcode = new char[6]();
        memcpy(opcode,temp_bin,6);
        cout << opcode << endl;
        if(strcmp(opcode,"000000") == 0)
        {
            label[i] = 1;
            //cout << "r_type" << label[i] << endl;
        }

        else if(strcmp(opcode,"000010") == 0 || strcmp(opcode,"000011") == 0)
        {
            label[i] = 3;
            //cout << "j_type" << label[i] << endl;
        }

        else if(strcmp(opcode,"111111") == 0)
        {
            label[i]=4;
            //cout << "s_type" << label[i] << endl;
        }

        else
        {
            label[i] = 2;
            //cout << "i_type" << label[i] << endl;
        }


    }

}
