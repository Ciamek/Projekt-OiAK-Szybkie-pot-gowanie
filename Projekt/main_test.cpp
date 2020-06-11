//
// Created by Maciej Ciura on 06.05.2020.
//
#include <iostream>
#include <cstdio>
#include <string>
#include "BigNum.h"
#include <chrono>
#include <fstream>
#include <ctime>

extern "C" {
void multiply_as (unsigned int *a, unsigned int a_size, unsigned int *b, unsigned int b_size, unsigned int *result);
}

BigNum multiply (BigNum& a, BigNum& b);

int main() {

    std::cout<<"\n\nTest rozpoczety"<<std::endl;

    unsigned int b;
    BigNum a;// result("1");
    unsigned int n,k;

    std::chrono::high_resolution_clock::time_point t1, t2;

    std::ifstream data_file;
    std::ofstream result_file, time_file;
    data_file.open ("data_input");
    data_file>>k>>n;
    time_file.open ("Dane pomiarowe/times_" + std::to_string(n) + std::to_string(k));
    result_file.open ("result_cpp");



    for(int i=0;i<k;i++){

    BigNum result("1");
//    std::cout<<"Podaj liczbę w reprezentacji haksadecymalnej:\n";
    data_file>>a;
//    std::cout<<"Podaj potęgę z zakresu: <0, 255>, w reprezentacji haksadecymalnej:\n";
    data_file>>std::hex>>b;

    unsigned int count_zero=0;
    for(int j=0;j<a.size;j++)
    if(a[j]==0) count_zero++;
    if(count_zero!=a.size)
    {
      double time_avg =0;

      for(int m=0;m<10;m++)
      {
    t1 = std::chrono::high_resolution_clock::now();

    while( true )
    {
        if( b & 1 )   result = multiply ( result, a );
        if( b >>= 1 ) a = multiply ( a, a ); else break;
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    time_avg += time_span.count();
    }
    result_file<<result;
    time_file<<time_avg/10<<std::endl;
    }
    else{
      if(b==0)
      {
        result_file<<1<<std::endl;
        time_file<<0<<std::endl;
      }
      else
      {
      result_file<<0<<std::endl;
      time_file<<0<<std::endl;
      }

    }
  }
    data_file.close();
    time_file.close();
    result_file.close();
    std::cout<<"Gotowe!";
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
