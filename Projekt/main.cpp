//
// Created by Maciej Ciura on 06.05.2020.
//
#include <iostream>
#include <cstdio>
#include <string>
#include "BigNum.h"

extern "C" {
void multiply_as (unsigned int *a, unsigned int a_size, unsigned int *b, unsigned int b_size, unsigned int *result);
}

BigNum multiply (BigNum& a, BigNum& b);

int main() {

    std::cout<<"Projekt OiAK Szybkie potegowanie wielkich liczb.\nMaciej Ciura 248879"<<std::endl;

    unsigned int b;
    BigNum a, result("1");

    std::cout<<"Podaj liczbę z zakresu: <0, >, w reprezentacji haksadecymalnej:\n";
    std::cin>>a;
    std::cout<<"Podaj potęgę z zakresu: <0, >, w reprezentacji haksadecymalnej:\n";
    std::cin>>std::hex>>b;

    unsigned int count_zero=0;
    for(int j=0;j<a.size;j++)
    if(a[j]==0) count_zero++;
    if(count_zero!=a.size)
    {
    while( true )
    {
        if( b & 1 )   result = multiply ( result, a );
        if( b >>= 1 ) a = multiply ( a, a ); else break;
    }

    std::cout<<result<<std::endl;
    }
    else
      if(b==0) std::cout<<1<<std::endl;
        else std::cout<<0<<std::endl;

    return 0;
}

BigNum multiply (BigNum& a, BigNum& b)
{
    BigNum temp(a.size+b.size);
    multiply_as(a.tab, a.size, b.tab, b.size, temp.tab);
    int i=temp.size-1;
    while(temp[i]==0) i--;
    temp.size = i+1;
    return temp;
}
