// Assignment: Project 2
// Created By: Juan, and Jevan
// Course: CS 415
// Date: March 29, 2019

#include <iostream>
#include "bigInt.hpp"
using namespace std;

int main() {

        bigInt a, b;
        bigInt result;
        int userInput = 0;

        cout << "Please Enter a value for A: ", cin >> userInput, a = userInput;
        cout << "Please Enter a value for B: ", cin >> userInput, b = userInput;
        cin.clear();
        fflush(stdin);

    while(true) {
        int option = 0;

        cout << "===================" << endl;
        cout << "Options: " << endl;
        cout << "===================" << endl;
        cout << "[1] Task 1" << endl;
        cout << "[2] Task 2" << endl;
        cout << "[3] Exit" << endl;
        cout << "Option: ";
        cin >> option;

        if(option == 1) {
            result = a * b;
            cout << "Using Karatsuba Multiplication: " << endl;
            cout << a << " * " << b << " = " << result << endl;
        } else if(option == 2) {
            result = a ^ b;
            cout << "Using Karatsuba Power: " << endl;
            cout << a << " ^ " << b << " = " << result << endl;

        } else {
            break;
        }
        cout << endl;
    }
    return 0;
}