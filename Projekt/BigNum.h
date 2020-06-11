//
// Created by Maciej Ciura on 12.05.2020.
//
#ifndef OIAK_BIGNUM_H
#define OIAK_BIGNUM_H
#include <string>
#include <iostream>

class BigNum {

public:
    unsigned int s_size;
    unsigned int size;
    unsigned int *tab;

    BigNum();
    explicit BigNum(unsigned int size);
    explicit BigNum(std::string str);
    ~BigNum();


    BigNum &operator=(BigNum const & num);
    unsigned int operator[](int n);
};

int charToInt(char c);
std::istream & operator>>(std::istream &in, BigNum &num);
std::ostream & operator<<(std::ostream &out, BigNum &num);


#endif //OIAK_BIGNUM_H
