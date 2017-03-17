#include <iostream>
#include<fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <bitset>
using namespace std;
vector<long long> reg;
#define max_sign 2147483647
#define min_sign -2147483648
#define max_unsign 4294967295
/*
class mips_reg
{
private:
    vector<unsigned char> reg[32];

public:
    mips_reg::mips_reg(unsigned char* = 0)



};*/
/*
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
int ins_add(char *rs , char *rt , char *rd) // sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] + reg[t2];
    if(reg[t3] > max_sign || reg[t3] < min_sign )
    {
        cout << "overflow_error" << endl;
        return 0;
    }

    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;

}
int ins_addu(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] + reg[t2];
    if(reg[t3] > max_unsign)
    {
        reg[t3] = reg[t3] & max_unsign;
    }
    else if(reg[t3] < 0)
    {
        unsigned long long  j = (unsigned long long ) reg[t3];
        j = j & max_unsign;
        reg[t3] = j;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_sub(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] - reg[t2];
    if(reg[t3] > max_sign || reg[t3] < min_sign )
    {
        cout << "overflow_error" << endl;
        return 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_and(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] & reg[t2];
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_or(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] | reg[t2];
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_xor(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] ^ reg[t2];
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_nor(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~(reg[t1] | reg[t2]);
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_nand(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~(reg[t1] & reg[t2]);
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_slt(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    if(reg[t1] < reg[t2])
        reg[t3] = 1;
    else
        reg[t3] = 0;
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "0" <<t3 << ":" << reg[t3] << endl;
        else
            cout << t3 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_sll(char *rt , char *rd , char *shamt)//+
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    if(reg[t2] < 0)
    {
        unsigned long long  j = (unsigned long long ) reg[t3];
        j = j & max_unsign;
        reg[t3] = j;
    }
    reg[t2] = reg[t1] << t3;
    reg[t2] = reg[t2]& max_unsign;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "0" << t2 << ":" << reg[t3] << endl;
        else
            cout << t2 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_srl(char *rt , char *rd , char *shamt)//+
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    if(reg[t2] < 0)
    {
        unsigned long long  j = (unsigned long long ) reg[t3];
        j = j & max_unsign;
        reg[t3] = j;
    }
    reg[t2] = reg[t1] >> t3;
    reg[t2] = reg[t2]& max_unsign;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "0" << t2 << ":" << reg[t3] << endl;
        else
            cout << t2 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_sra(char *rt , char *rd , char *shamt)//+~-
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    reg[t2] = reg[t1] >> t3;
    reg[t2] = reg[t2]& max_sign;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "0" << t2 << ":" << reg[t3] << endl;
        else
            cout << t2 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;
}
int ins_jr(char *rs)
{
    int t1 = convert_dex(rs);
    reg[35] = t1;
    cout << reg[35] << endl;
    return 0;
}
int mult(char *rs , char *rt);
int multu(char *rs , char *rt);
int mfhi(char *rd);
int mflo(char *rd);
//*****************************************I Type
int addi(char *rs , char *rt , int *imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    reg[t2] = reg[t1] + t3;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "0" << t2 << ":" << reg[t3] << endl;
        else
            cout << t2 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;

}
int addi(char *rs , char *rt , int *imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    reg[t2] = reg[t1] + t3;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "0" << t2 << ":" << reg[t3] << endl;
        else
            cout << t2 << ":" << reg[t3] << endl;
    }
    reg[35] = reg[35] + 4;
    cout << reg[35] << endl;
    return 0;

}
string conver_to_decode(int label , string opcode = "" , string func = "")
{
    ifstream fin;
    string tempstr;
    string type_r[] = {"add" , "addu" , "sub" , "and" , "or" ,
                       "xor" , "nor" , "nand" , "slt" , "sll" ,
                       "srl" , "sra" , "jr" , "mult" , "multu" ,
                       "mfhi" , "mflo"};
    string r_fun[] = {"100000" , "100001" , "100010" , "100100" , "100101" ,
                     "100110" , "100111" , "101000" , "101010" , "000000" ,
                     "000010" , "000011" , "001000" , "011000" , "011001",
                     "010000" , "010010"};

    string type_i[] = {"addi" , "addiu" , "lw" , "lh" , "lhu" ,
                       "lb" , "lbu" , "sw" , "sh" , "sb" ,
                       "lui" , "andi" , "ori" , "nori" , "slti" ,
                       "beq" , "bne" , "bgtz"};
    string i_opcode[] = {"001000" , "001001" , "100011" , "100001" , "100101"
                         "100000" , "100100" , "101011" , "101001" , "101000"
                         "001111" , "001100" , "001101" , "001110" , "001010"
                         "000100" , "000101" , "000111"};
    string type_j[] = {"j", "jal"};
    string j_opcode[] = {"000010" , "000011"};
    string type_s[] = {"halt"};
    string s_opcode[] = {"111111"};
    if(label == 1) // divide and conquer
    {
        int i = 0;
        int j = (sizeof(r_fun)/sizeof(r_fun[0]));
        while(true)
        {
            cout << "yes" << endl;
            {
                if(r_fun[i] == func)
                    return type_r[i];
            }
            {
                if(r_fun[j] == func)
                    return type_r[j];
            }
                if(i == j)
                    return "no instrument";
                i++;
                j--;
        }
    }
    else if(label == 2)
    {
        int i = 0;
        int j = (sizeof(i_opcode)/sizeof(i_opcode[0]));
        while(true)
        {
            {
                if(i_opcode[i] == opcode)
                    return type_i[i];
            }
            {
                if(i_opcode[j] == opcode)
                    return type_i[j];
            }
                if(i == j)
                    cout << "NO" << endl;
                    return "no instrument";
                i++;
                j--;
        }

    }
    else if(label == 3)
    {
        if(j_opcode[0] == opcode)
            return type_j[0];
        else if(j_opcode[1] == opcode)
            return type_j[1];
        else
            return "no instrument";
    }
    else
    {
        if(s_opcode[0] == opcode)
            return type_s[0];
        else
            return "no instrument";

    }

}
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
    //vector<string > ins;
    //int* label = (int*) malloc (sizeof(int));
    // initial register
    for(int i = 0 ; i < 35 ; i++)
    {
        reg.push_back(0x00);//before $32

    }
    vector<string > pc;
    for(int i = 0 ; i < binary.size(); i++)
    {
        string null = "";
        char* temp_bin = strdup(binary[i].c_str());
        char *opcode = new char[6]();
        memcpy(opcode,temp_bin,6);
        //cout << opcode << endl;
        if(strcmp(opcode,"000000") == 0)
        {
            //label[i] = 1;
            char *func = new char[6]();
            memcpy(func,temp_bin+26,6);
            char *rs = new char[5]();
            memcpy(rs,temp_bin+6,5);
            char *rt = new char[5]();
            memcpy(rt,temp_bin+11,5);
            char *rd = new char[5]();
            memcpy(rd,temp_bin+16,5);
            char *shamt = new char[5]();
            memcpy(shamt,temp_bin+21,5);
            string ins = "";
            cout << func << endl;
            ins = conver_to_decode(1 , null , func);
            cout << ins << endl;
            if(ins == "add")
                ins_add();
            system("pause");
            //cout << "r_type" << label[i] << endl;
        }

        else if(strcmp(opcode,"000010") == 0 || strcmp(opcode,"000011") == 0)
        {
            //label[i] = 3;
            //cout << "j_type" << label[i] << endl;
        }

        else if(strcmp(opcode,"111111") == 0)
        {
            //label[i]=4;
            //cout << "s_type" << label[i] << endl;
        }

        else
        {
            //label[i] = 2;
            //cout << "i_type" << label[i] << endl;
        }


    }

}
