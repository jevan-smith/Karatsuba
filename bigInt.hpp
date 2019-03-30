#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#ifndef UNTITLED5_BIGINT_HPP
#define UNTITLED5_BIGINT_HPP

class bigInt {
public:
    bigInt();
    void operator = (const int &d);
    bigInt operator * (bigInt &b);
    bigInt operator ^ (bigInt &b);
    friend std::ostream & operator << (std::ostream &out, const bigInt &c);
private:
    vector<int> _value;
    void addLeadingZeros(vector<int> &a, vector<int> &b);
    void addZero(int length, vector<int>& v);
    vector<int> addVectors(vector<int> a, vector<int> b);
    vector<int> subtractVectors(std::vector<int> A, std::vector<int> B);
    void shiftPower10(int n, std::vector<int>& v);
    vector<int> convertToVector(int num);
    vector<int> removingLeadingZeros(std::vector<int> v);
    vector<int> power(int a, int b);
    int vectorToInt(std::vector<int> v);
    vector<int> karatsuba_multi(vector<int> a, vector<int> b);
};


#endif //UNTITLED5_BIGINT_HPP
