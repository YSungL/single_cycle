#include <iostream>
#include<fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <sstream>
#include <math.h>
using namespace std;
vector<long long> reg;
vector<string >d_mem;
#define max_sign 2147483647
#define min_sign -2147483648
#define max_unsign 4294967295
#define mult_sign 9223372036854775807
#define mult_unsign 18446744073709551615
int lock_num = 0;
int lock = 0;
int jal_mark = 0;
int safe_H = 0;//use for mult
int safe_L = 0;
long long convert_dex(string str_bin)
{
    int str_size = str_bin.size();
    long long dec = 0;
    int bin_pow = 0;
    for(int i = (str_size-1) ; i>=0 ; i--)
    {
        int num = 0;
        //cost ~0.017sec
        stringstream temp_num;
        temp_num << str_bin[i];
        temp_num >> num;
        long long temp = num * pow(2,bin_pow);
        dec += temp;
        bin_pow++;
        // cost ~0.024sec
        /*
        if(str_bin[i] == '1') num = 1;
        int temp = num * pow(2,bin_pow);
        dec += temp;
        bin_pow++;*/
    }
    return dec;
}
string convert_bin(long long num)
{
    if(num < 0)//avoid data is signed
    {
        num = num & 4294967295;
    }
    string temp = "";
    while(true)
    {
        if(num % 2 == 0)
        {
            temp += "0";
            num = num/2;
        }
        else if(num % 2 == 1)
        {
            temp += "1";
            num = num/2;
        }
        if(num == 0)
            break;
    }
    string output = "";
    int s_num = temp.size();
    for(int i = 31; i >= 0 ; i--)
    {
        if(i >= s_num)
            output += "0";
        else
            output += temp[i];
    }
    return output;
}
string convert_hex(long long num)
{
    if(num < 0)//avoid data is signed
    {
        num = num & 4294967295;
    }
    string temp = "";
    while(true)
    {
        if(num % 16 == 0)
        {
            temp += "0";
            num = num/16;
        }
        else if(num % 16 == 1)
        {
            temp += "1";
            num = num/16;
        }
        else if(num % 16 == 2)
        {
            temp += "2";
            num = num/16;
        }
        else if(num % 16 == 3)
        {
            temp += "3";
            num = num/16;
        }
        else if(num % 16 == 4)
        {
            temp += "4";
            num = num/16;
        }
        else if(num % 16 == 5)
        {
            temp += "5";
            num = num/16;
        }
        else if(num % 16 == 6)
        {
            temp += "6";
            num = num/16;
        }
        else if(num % 16 == 7)
        {
            temp += "7";
            num = num/16;
        }
        else if(num % 16 == 8)
        {
            temp += "8";
            num = num/16;
        }
        else if(num % 16 == 9)
        {
            temp += "9";
            num = num/16;
        }
        else if(num % 16 == 10)
        {
            temp += "A";
            num = num/16;
        }
        else if(num % 16 == 11)
        {
            temp += "B";
            num = num/16;
        }
        else if(num % 16 == 12)
        {
            temp += "C";
            num = num/16;
        }
        else if(num % 16 == 13)
        {
            temp += "D";
            num = num/16;
        }
        else if(num % 16 == 14)
        {
            temp += "E";
            num = num/16;
        }
        else
        {
            temp += "F";
            num = num/16;
        }
        if(num == 0)
            break;
    }
    string output = "0x";
    int s_num = temp.size();
    for(int i = 7; i >= 0 ; i--)
    {
        if(i >= s_num)
            output += "0";
        else
            output += temp[i];
    }
    return output;

}
int ins_add(char *rs , char *rt , char *rd) // sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] + reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }

    if(reg[t3] > max_sign || reg[t3] < min_sign )
    {
        cout << "Number Overflow" << endl;
    }

    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$" << t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_addu(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] + reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] < 0) // convert to positive number
    {
        unsigned long long  j = (unsigned long long ) reg[t3];
        j = j & max_unsign;
        reg[t3] = j;
    }
    if(reg[t3] > max_unsign)
    {
        reg[t3] = reg[t3] & max_unsign;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$" <<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sub(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] - reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] > max_sign || reg[t3] < min_sign )
    {
        cout << "Number Overflow" << endl;
        return 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_and(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] & reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_or(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] | reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_xor(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = reg[t1] ^ reg[t2];
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nor(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~(reg[t1] | reg[t2]);
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nand(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~(reg[t1] & reg[t2]);
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_slt(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];;
    if(reg[t1] < reg[t2])
        reg[t3] = 1;
    else
        reg[t3] = 0;
    if(t3 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] != temp){
        if(t3 < 10)
            cout << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            cout << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sll(char *rt , char *rd , char *shamt)//+ ~ -
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    reg[t2] = reg[t1] << t3;
    if(reg[t2] > max_sign || reg[t2] < min_sign)
    {
        cout << "Number Overflow" << endl;
        return 0;
    }

    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}

int ins_srl(char *rt , char *rd , char *shamt)//+ ~ -
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    if(reg[t1] < 0)
    {
        long long temp_num = reg[t1] >> t3;
        int ppow = pow(2,(32-t3)) - 1;
        reg[t2] = (temp_num & ppow);
    }
    else
        reg[t2] = reg[t1] >> t3;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << reg[t2] << endl;
        else
            cout << "$" << t2 << ": " << reg[t2] << endl;
    }
    reg[34] = reg[34] + 4;
    cout << convert_hex(reg[34]) << endl;
    return 0;
}

int ins_sra(char *rt , char *rd , char *shamt)//+~- sign extend
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    reg[t2] = reg[t1] >> t3;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] > max_sign || reg[t2] < min_sign)
    {
        cout << "Number Overflow" << endl;
        return 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << convert_hex(reg[34]) << endl;
    return 0;
}

int ins_jr(char *rs)
{
    int t1 = convert_dex(rs);
    reg[34] = t1;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}

int ins_mult(char *rs , char *rt)
{
    long long result = 0;
    long long temp = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    result = reg[t1] * reg[t2];
    if(result < 0)
        result = result & mult_unsign;
    reg[32] = result/pow(2,31);
    temp = reg[32] * pow(2,31);
    reg[33] = result - temp;
    if(reg[32] > max_unsign || reg[33] > max_unsign)
        cout << "Number Overflow" << endl;
    if(safe_H == 1 || safe_L == 1)
    {
        cout << "Overwrite HI-LO registers" << endl;
    }
    cout << "$HI: " << convert_hex(reg[32]) << endl;
    cout << "$LO: " << convert_hex(reg[33]) << endl;
    safe_H = 1;
    safe_L = 1;
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_multu(char *rs , char *rt)
{
    long long result = 0;
    long long temp = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    if(reg[t1] < 0)
        result = (reg[t1] &mult_sign) * reg[t2];
    else if(reg[t2] < 0)
        result = reg[t1] * (reg[t2] &mult_sign);
    else
        result = reg[t1] * reg[t2];
    reg[32] = result/pow(2,31);
    temp = reg[32] * pow(2,31);
    reg[33] = result - temp;
    if(reg[32] > max_unsign || reg[33] > max_unsign)
        cout << "Number Overflow" << endl;
    if(safe_H == 1 || safe_L == 1)
    {
        cout << "Overwrite HI-LO registers" << endl;
    }
    cout << "$HI: " << convert_hex(reg[32]) << endl;
    cout << "$LO: " << convert_hex(reg[33]) << endl;
    safe_H = 1;
    safe_L = 1;
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_mfhi(char *rd)
{
    int t1 = convert_dex(rd);
    reg[t1] = reg[32];
    safe_H = 0;
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_mflo(char *rd)
{
    int t1 = convert_dex(rd);
    reg[t1] = reg[33];
    safe_L = 0;
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
//*****************************************I Type
int ins_addi(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    reg[t2] = reg[t1] + t3;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] > max_sign || reg[t2] < min_sign )
    {
        cout << "Number Overflow" << endl;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_addiu(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(t3 < 0)
    {
        t3 = t3 & max_unsign;
    }
    reg[t2] = reg[t1] + t3;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t3] > max_unsign)
    {
        reg[t3] = reg[t3] & max_unsign;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lw(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;//if=4(remember imm is dexc)
    int temp_sign = 0;
    int add_num = 0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm);
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    for(int i = (start_word*8) ; i < ((start_word*8)+32) ; i++)
        str_real += str_temp[i];
    reg[t2] = convert_dex(str_real);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }

    if(imm % 4 != 0)
    {
        cout << "Misalignment Error" << endl;
        close = 1;
    }
    if(close == 1)
        return -1;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lh(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int temp_sign = 0;
    int add_num = 0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = (int32_t)reg[t1];
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm);
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    if(imm % 2 != 0)
    {
        cout << "Misalignment Error" << endl;
        close = 1;
    }
    for(int i = (start_word*8) ; i < ((start_word*8)+16) ; i++)
    {
        if(str_temp[0] == '1')
        {
            if(count < 16)
            {
                str_real += "1";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
        else if(str_temp[0] == '0')
        {
            if(count < 16)
            {
                str_real += "0";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
    }
    reg[t2] = convert_dex(str_real);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(close == 1)
        return -1;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lb(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    //cout << "t3"<< t3 << endl;
    int add_num =0;
    int temp_sign=0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm);
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    for(int i = (start_word*8) ; i < ((start_word*8)+8) ; i++)
    {
        if(str_temp[0] == '1')
        {
            if(count < 24)
            {
                str_real += "1";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
        else if(str_temp[0] == '0')
        {
            if(count < 24)
            {
                str_real += "0";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
    }
    reg[t2] = convert_dex(str_real);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(close == 1)
        return -1;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lhu(char *rs , char *rt , int imm)//+16-1(imm = 16 bits)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    int add_num = reg[t1] + imm;
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    if(imm % 2 != 0)
    {
        cout << "Misalignment Error" << endl;
        close = 1;
    }
    for(int i = (start_word*8) ; i < ((start_word*8)+16) ; i++)
    {
        if(count < 16)
        {
            str_real += "0";
            i = (start_word*8)-1;
            count ++ ;
        }
        else
        {
            str_real += str_temp[i];
        }
    }
    reg[t2] = convert_dex(str_real);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(close == 1)
        return -1;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lbu(char *rs , char *rt , int imm)//+16-1(imm = 16 bits)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    int add_num = reg[t1] + imm;
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    for(int i = (start_word*8) ; i < ((start_word*8)+8) ; i++)
    {
        if(count < 24)
        {
            str_real += "0";
            i = (start_word*8)-1;
            count ++ ;
        }
        else
        {
            str_real += str_temp[i];
        }
    }
    reg[t2] = convert_dex(str_real);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(close == 1)
        return -1;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sw(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int add_num =0;
    int temp_sign = 0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm);
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    if(imm % 4 != 0)
    {
        cout << "Misalignment Error" << endl;
        close = 1;
    }
    int start_area = add_num/4;
    d_mem[start_area+2]=convert_bin(reg[t2]);
    if(close == 1)
        return -1;
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sh(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int add_num = 0;
    int temp_sign = 0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm);
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    if(imm % 2 != 0)
    {
        cout << "Misalignment Error" << endl;
        close = 1;
    }
    if(close == 1)
        return -1;
    int start_area = add_num/4;
    int start_word = add_num%4;
    d_mem[start_area+2];
    unsigned int temp_1 = 0;
    unsigned int temp_2 = 0;
    if(start_word == 0)
    {
        temp_1 = reg[t2]&65535;
        temp_1 = temp_1 << 16;
        temp_2 = convert_dex(d_mem[start_area+2])&65535;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    else
    {
        temp_1 = reg[t2]&65535;//low
        temp_2 = convert_dex(d_mem[start_area+2])&4294901760;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sb(char *rs , char *rt , int imm)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int temp_sign = 0;
    int add_num = 0;
    long long temp = reg[t2];
    if(reg[t1] > max_sign)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+imm;
    }
    else
        add_num = reg[t1]+imm;
    if(add_num > 1024 || add_num < 0)
    {
        cout << "Address Overflow" << endl;
        close = 1;
    }
    if(close == 1)
        return -1;
    int start_area = add_num/4;
    int start_word = add_num%4;
    d_mem[start_area+2];
    unsigned int temp_1 = 0;
    unsigned int temp_2 = 0;
    unsigned int temp_3 = 0;
    if(start_word == 0)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 24;
        temp_2 = convert_dex(d_mem[start_area+2])&16777215;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    else if(start_word == 1)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 16;
        temp_2 = convert_dex(d_mem[start_area+2])&4278190079;
        temp_3 = convert_dex(d_mem[start_area+2])&65535;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2+temp_3);
    }
    else if(start_word == 2)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 8;
        temp_2 = convert_dex(d_mem[start_area+2])&4294901760;//(2^32-1)-(2^16-1) high
        temp_3 = convert_dex(d_mem[start_area+2])&255;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2+temp_3);
    }
    else
    {
        temp_1 = reg[t2]&255;//low
        temp_2 = convert_dex(d_mem[start_area+2])&4294967040;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lui( char *rt , int imm)
{
    int t2 = convert_dex(rt);
    long long temp = reg[t2];
    reg[t2] = imm << 16;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_andi(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & max_unsign;
        imm = j;
    }
    reg[t2] = reg[t1]&imm;
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_ori(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & max_unsign;
        imm = j;
    }
    reg[t2] = reg[t1]|imm;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nori(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & max_unsign;
        imm = j;
    }
    reg[t2] = ~(reg[t1]|imm);
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_slti(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & max_unsign;
        imm = j;
    }
    if(reg[t1] < imm) // <X -> 1
        reg[t2] = 1;
    else
        reg[t2] = 0;
    if(t2 == 0){
        cout << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            cout << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            cout << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_beq(char *rs , char *rt , int imm) // ==
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    if(reg[t1] == reg[t2])
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        cout << "PC: " << convert_hex(reg[34]) << endl;
        return (imm);
    }
    else
    {
        reg[34] = reg[34] + 4;
        cout << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_bne(char *rs , char *rt , int imm) // !=
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    //cout << reg[t1] << endl;
    //cout << reg[t2] << endl;
    if(reg[t1] != reg[t2])
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        cout << "PC: " << convert_hex(reg[34]) << endl;
        return (imm);
    }
    else
    {
        reg[34] = reg[34] + 4;
        cout << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_bgtz(char *rs, int imm) // !=
{
    int t1 = convert_dex(rs);
    int t3 = imm;
    if(reg[t1] > 0)
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        cout << "PC: " << convert_hex(reg[34]) << endl;
        return imm;
    }
    else
    {
        reg[34] = reg[34] + 4;
        cout << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_j(int imm) //come back
{
    reg[34] = reg[34] - (4*imm);
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return imm;

}
int ins_jal(int imm) // come back
{
    reg[31] = reg[34];
    reg[34] = reg[34] + (4*imm);
    cout << "$31: " << convert_hex(reg[31]) << endl;
    cout << "PC: " << convert_hex(reg[34]) << endl;
    return imm;
}
string conver_to_decode(int label , string opcode = "" , string func = "")
{
    string type_r[17] = {"add" , "addu" , "sub" , "and" , "or" ,
                       "xor" , "nor" , "nand" , "slt" , "sll" ,
                       "srl" , "sra" , "jr" , "mult" , "multu" ,
                       "mfhi" , "mflo"};
    string r_fun[17] = {"100000" , "100001" , "100010" , "100100" , "100101" ,
                     "100110" , "100111" , "101000" , "101010" , "000000" ,
                     "000010" , "000011" , "001000" , "011000" , "011001",
                     "010000" , "010010"};

    string type_i[18] = {"addi" , "addiu" , "lw" , "lh" , "lhu" ,
                       "lb" , "lbu" , "sw" , "sh" , "sb" ,
                       "lui" , "andi" , "ori" , "nori" , "slti" ,
                       "beq" , "bne" , "bgtz"};
    string i_opcode[18] = {"001000" , "001001" , "100011" , "100001" , "100101",
                         "100000" , "100100" , "101011" , "101001" , "101000",
                         "001111" , "001100" , "001101" , "001110" , "001010",
                         "000100" , "000101" , "000111"};
    string type_j[2] = {"j", "jal"};
    string j_opcode[2] = {"000010" , "000011"};
    string type_s[1] = {"halt"};
    string s_opcode[1] = {"111111"};
    if(label == 1) // divide and conquer
    {
        for(int i = 0; i < 17 ;i++)
        {
            string op = r_fun[i];
            if(op == func)
                return type_r[i];
            if(i == 16)
                return "no instrument";
        }
    }
    else if(label == 2)
    {
        for(int i = 0; i < 18 ;i++)
        {
            string op = i_opcode[i];
            if(op == opcode)
                return type_i[i];
            if(i == 17)
                return "no instrument";
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
    //int cnt = 0, line = 0;
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
    //dimage open ******************************************************************
    FILE* fp_2;
    fp_2 = fopen("dimage.bin" , "rb");
    if (!fp_2)
        return 1 ;
    unsigned char buff_2;
    vector<unsigned char>d_bin;
    while(fread(&buff_2,sizeof(char),1,fp_2) == 1)
    {
        d_bin.push_back(buff_2);

    }
    string tempbin_2 = "";
    for(int i = 0 ; i < d_bin.size() ; i++)
    {
        bitset<8> bin(d_bin[i]); //nest block bin is new declare
        string str = bin.to_string<char,std::string::traits_type,std::string::allocator_type>();
        tempbin_2 = tempbin_2 + str;
        if((i+1)%4 == 0)
        {
            d_mem.push_back(tempbin_2);
            tempbin_2 = "";
        }
    }
    //vector<string > ins;
    //int* label = (int*) malloc (sizeof(int));
    // initial register
    int cycle = 0;
    cout << "cycle " << cycle << endl;
    for(int i = 0 ; i < 35 ; i++)
    {
        if(i == 29)
            reg.push_back(convert_dex(d_mem[0]));
        else if (i == 34)
            reg.push_back(convert_dex(binary[0]));
        else
            reg.push_back(0x00);
    }
    for(int i = 0 ; i < 35 ; i++)
    {
        if(i < 10)
            cout << "$0" << i << ": " << convert_hex(reg[i]) << endl;
        else if (i == 32)
            cout << "$HI: " << convert_hex(reg[i]) << endl;
        else if (i == 33)
            cout << "$LO: " << convert_hex(reg[i]) << endl;
        else if (i == 34)
            cout << "PC: " << convert_hex(reg[i]) << endl;
        else
            cout << "$" << i << ": " << convert_hex(reg[i]) << endl;
    }
    for(int i = 2 ; i < binary.size(); i++)
    {

        int data_error = 0;
        //cout << "line = " <<(i-1) << endl;
        const string null = "";
        char* temp_bin = strdup(binary[i].c_str());
        char *opcode = new char[6]();
        opcode[6] = '\0';
        memcpy(opcode,temp_bin,6);
        if(strcmp(opcode,"111111") == 0)
        {
            return 0;
        }
        cout << "cycle " << cycle << endl;
        cycle++;
        //cout << opcode << endl;
        //cout << "YES" << endl;
        if(strcmp(opcode,"000000") == 0)
        {
            //label[i] = 1;
            char *func = new char[6]();
            func[6] = '\0';
            memcpy(func,temp_bin+26,6);
            char *rs = new char[5]();
            rs[5] = '\0';
            memcpy(rs,temp_bin+6,5);
            char *rt = new char[5]();
            rt[5] = '\0';
            memcpy(rt,temp_bin+11,5);
            char *rd = new char[5]();
            rd[5] = '\0';
            memcpy(rd,temp_bin+16,5);
            char *shamt = new char[5]();
            shamt[5] = '\0';
            memcpy(shamt,temp_bin+21,5);
            string ins = "";
            //cout << func << endl;
            ins = conver_to_decode(1 , null , func);

            //cout << ins << endl;
            if(ins == "add")
                ins_add(rs,rt,rd);
            if(ins == "addu")
                ins_addu(rs,rt,rd);
            if(ins == "sub")
                ins_sub(rs,rt,rd);
            if(ins == "and")
                ins_and(rs,rt,rd);
            if(ins == "or")
                ins_or(rs,rt,rd);
            if(ins == "xor")
                ins_xor(rs,rt,rd);
            if(ins == "nor")
                ins_nor(rs,rt,rd);
            if(ins == "nand")
                ins_nand(rs,rt,rd);
            if(ins == "slt")
                ins_slt(rs,rt,rd);
            if(ins == "sll")
                 ins_slt(rt,rd,shamt);
            if(ins == "srl")
                 ins_slt(rt,rd,shamt);
            if(ins == "sra")
                 ins_sra(rt,rd,shamt);
            if(ins == "jr")
            {
                ins_jr(rs);
                int return_block = jal_mark;
                jal_mark = 0;
                i = i - jal_mark;
            }
            if(ins == "mult")
                 ins_mult(rs,rt);
            if(ins == "multu")
                 ins_multu(rs,rt);
            if(ins == "mfhi")
                 ins_mfhi(rd);
            if(ins == "mflo")
                 ins_mflo(rd);
            //cout << "r_type" << label[i] << endl;
        }
        else if(strcmp(opcode,"000010") == 0 || strcmp(opcode,"000011") == 0) // jump
        {
            char *addrt = new char[26]();
            memcpy(addrt,temp_bin+6,26);
            int addr = convert_dex(addrt);
            if(strcmp(opcode,"000011"))
            {
                jal_mark = ins_jal(addr);
                i = i + jal_mark;
            }
            else if(strcmp(opcode,"000010"))
            {
                int j_re = ins_j(addr);
                i = i - j_re;
            }

        }
/*
        else if(strcmp(opcode,"111111") == 0)
        {
            return 0 ;
        }
*/
        else //
        {

            int new_block = 0;
            char *rs = new char[5]();
            rs[5] = '\0';
            memcpy(rs,temp_bin+6,5);
            char *rt = new char[5]();
            rt[5] = '\0';
            memcpy(rt,temp_bin+11,5);
            char *a1 = new char[16]();
            a1[16] = '\0';
            memcpy(a1,temp_bin+16,16);
            int imm_unsigned = convert_dex(a1);
            int imm_signed = 0;
            if(imm_unsigned > 32767)
            {
                imm_signed = (int16_t) imm_unsigned;
            }
            else
                imm_signed = imm_unsigned;
            string ins = "";
            ins = conver_to_decode(2 , opcode , null);
            //system("PAUSE");
            if(ins == "addi")
                ins_addi(rs,rt,imm_signed);
            if(ins == "addiu")
                ins_addiu(rs,rt,imm_unsigned);
            if(ins == "lw")
                if(ins_lw(rs,rt,imm_signed) == -1)
                    break;
            if(ins == "lh")
                if(ins_lh(rs,rt,imm_signed) == -1)
                    break;
            if(ins == "lhu")
                if(ins_lhu(rs,rt,imm_unsigned) == -1)
                    break;
            if(ins == "lb")
                if(ins_lb(rs,rt,imm_signed) == -1)
                    break;
            if(ins == "lbu")
                if(ins_lbu(rs,rt,imm_unsigned) == -1)
                    break;
            if(ins == "sw")
                if(ins_sw(rs,rt,imm_signed) == -1)
                    break;
            if(ins == "sh")
                if(ins_sh(rs,rt,imm_signed) == -1)
                    break;
            if(ins == "sb")
                if(ins_sb(rs,rt,imm_signed) == -1)
                   break;
            if(ins == "lui")
                ins_lui(rt,imm_signed);
            if(ins == "andi")
                ins_andi(rs,rt,imm_unsigned);
            if(ins == "ori")
                ins_ori(rs,rt,imm_unsigned);
            if(ins == "nori")
                ins_nori(rs,rt,imm_unsigned);
            if(ins == "slti")
                ins_slti(rs,rt,imm_signed);
            if(ins == "beq")
                new_block = ins_beq(rs,rt,imm_signed);
            if(ins == "bne")
                new_block = ins_bne(rs,rt,imm_signed);
            if(ins == "bgtz")
                new_block = ins_bgtz(rs,imm_signed);
            if(new_block != 0)
                i = i + new_block  ;
        }
    }
}
