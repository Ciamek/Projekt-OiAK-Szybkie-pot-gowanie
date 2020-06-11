//
// Created by Maciej Ciura on 12.05.2020.
//
#include "BigNum.h"
#include <cmath>


BigNum::BigNum() {
    tab = new unsigned int [0];
    size = 0;
    s_size = 0;
}

BigNum::BigNum(unsigned int _size) {
    tab = new unsigned int [_size];
    for(int i=0; i<_size; i++)
	tab[i]=0;
    size = _size;
    s_size = size * 8;
}

BigNum::BigNum(std::string str) {
    if (str.length()%8 != 0)
        str.insert(0, (8-(str.length()%8)), '0');
    s_size = str.length();
    size = ceil(double(s_size)/8);
    tab = new unsigned int [size];

    for (int i = 0; i < s_size; i+=8)
        for (int j = 0; j < 8; j++)
        {
            tab[(s_size-1)/8 - i/8] <<= 4;
            tab[(s_size-1)/8 - i/8] += charToInt(str[i+j]);
        }
}

BigNum::~BigNum() {
    delete [] tab;
}

BigNum & BigNum::operator=(BigNum const & a)
{
    if(this != &a)
    {
    delete[] tab;
    size = a.size;
    tab = new unsigned int [size];
    for(unsigned int i=0; i<size; i++)
       tab[i] = a.tab[i];
    s_size = a.s_size;
    }
    return *this;
}

unsigned int BigNum::operator[](int n) {
        return tab[n];
}


std::istream & operator>>(std::istream &in, BigNum &num) {
    delete [] num.tab;
    std::string str;
    in >> str;
    if(str[1] == 'x' || str[1] == 'X')
      str.erase(0,2);
    if (str.length()%8 != 0)
        str.insert(0, (8-(str.length()%8)), '0');
    num.s_size = str.length();
    num.size = ceil(double(num.s_size)/8);
    num.tab = new unsigned int [num.size];

    for (int i = 0; i < num.s_size; i+=8)
        for (int j = 0; j < 8; j++)
        {
            num.tab[(num.s_size-1)/8 - i/8] <<= 4;
            num.tab[(num.s_size-1)/8 - i/8] += charToInt(str[i+j]);
        }
    return in;
}

std::ostream & operator<<(std::ostream &out, BigNum &num) {
int i = num.size -1;
//printf("%X",num[i]);
out.fill();
out.width(0);
out<<std::hex<<num[i];

for (i=num.size-2; i>=0; i--)
{
  out.fill('0');
  out.width(8);
  out<<std::hex<<num[i];
}
  out<<std::endl;
	//printf("%08X",num[i]);
  //printf("\n");
  return out;
}

int charToInt(char c)
{
    int number;
    if (c < 58){
        number = c - 48;
        return number;
    }
    if (c < 71){
        number = c - 55;
        return number;
    }
    number = c - 87;
    return number;
}
