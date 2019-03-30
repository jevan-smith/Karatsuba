#include "bigInt.hpp"

bigInt::bigInt() {}

//private Functions
void bigInt::addLeadingZeros(vector<int> &a, vector<int> &b) {
    int sizeA = a.size();
    int sizeB = b.size();

    if(sizeA != sizeB) {
        int maxSize = max(sizeA, sizeB);
        if(sizeA > sizeB) {
            int addLength = maxSize - sizeB;
            addZero(addLength, b);
        }
        else {
            int addLength = maxSize - sizeA;
            addZero(addLength, a);
        }
    }
}

void bigInt::addZero(int length, vector<int> &v) {
    for (int i = 0; i < length; i++)
        v.push_back(0);
}

vector<int> bigInt::addVectors(vector<int> A, vector<int> B) {

    std::vector <int> result;
    int carryFlag = 0;
    addLeadingZeros(A, B);

    int i = 0;

    while (i < A.size() + 1) {
        //adding single digits ex 9+9 = 18
        if (i == A.size()) {
            if(carryFlag == 1)
                result.push_back(1); //if 1 carry left over, add it ex 9+9=(1)8
            else
                return result;
        }

        else {
            int num = (A[i] + B[i]); //ex 9 + 9 = 18
            std::vector<int> numVec = convertToVector(num); // as vec = {8,1}

            if (carryFlag == 1) {

                //result.push_back((num + 1) % 10); //FIX THIS CHECK THIS not single digit
                numVec = convertToVector(numVec[0] + 1); //9 + 1 = 10 -> {0,1} so 10 mod 10 to get first digit is numVec[0]
                result.push_back(numVec[0]);

                if(num == 9)
                    carryFlag = 1;
                else
                    carryFlag = 0;
            }

            else {
                //result.push_back(num % 10); //FIX THIS CHECK THIS not single digit, TURN TO STRING AND ADD OTHER HALF
                result.push_back(numVec[0]);
            }
            int carry = num + 1;
            if (carry == 10) {
                //do nothing
            }
            else if ((carry / 10) == 1) {
                carryFlag = 1;
            }
        }
        i++;
    }

    return result;
}

vector<int> bigInt::subtractVectors(vector<int> A, vector<int> B) {
    std::vector<int> result;

    int carryFlag = 0;
    addLeadingZeros(A, B);
    int i = 0;

    while (i < A.size()) {

        int num;
        std::vector <int> number;

        if (A[i] < B[i]) {

            num = 10 - (B[i] - A[i]); //single digit subtraction FIX THIS CHECK THIS not single digit

            if (carryFlag == 1) {
                num -= 1;
            }
            carryFlag = 1;
            result.push_back(num);
        }
        else {

            if (carryFlag == 1) {

                num = A[i] - 1;
                if(num < B[i]) {
                    num = 10 - (B[i] - num); //single digit subtraction FIX THIS CHECK THIS not single digit
                    result.push_back(num);
                    carryFlag = 1;
                }
                else if(num == B[i]) {
                    result.push_back(0);
                    carryFlag = 0;
                }
                else {
                    result.push_back(num - B[i]);
                    carryFlag = 0;
                }
            }
            else {
                num = (A[i] - B[i]);
                result.push_back(num);
            }
        }
        i++;
    }
    return result;
}

void bigInt::shiftPower10(int n, std::vector<int>& v) {
    int i = 0;
    while (i < n) {
        //add zero to front example -> 3 * 10^2 -> 300 -> represented here as 003
        v.insert(v.begin(),0);
        i++;
    }
}

std::vector<int> bigInt::convertToVector(int num) {
    std::vector <int> result;

    std::string number = std::to_string(num);
    for (int i = number.length() - 1; i >= 0; i--) {
        std::string n (1, number[i]);
        result.push_back(std::stoi(n));
    }

    return result;
}

vector<int> bigInt::removingLeadingZeros(std::vector<int> v) {

    std::vector <int> result;
    int zeroFlag = 0;

    for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        if ((*it == 0) && (zeroFlag == 0)) {}
            //do nothing
        else {
            zeroFlag = 1;
            result.push_back(*it);
        }
    }

    std::reverse(result.begin(),result.end());
    return result;
}

std::vector<int> bigInt::power(int a, int b) {

    if (b == 0)
        return convertToVector(1);

    std::vector<int> answer = power(a, b/2);

    if ((b % 2) == 0) { //if b is even
        return karatsuba_multi(answer, answer); //(a^n/2)^2
    }

    else { //if b is odd
        return karatsuba_multi(convertToVector(a), karatsuba_multi(answer, answer)); //(a^(n-1)/2)^2 * a
    }
}

int bigInt::vectorToInt(std::vector<int> v) {

    std::string number = "";
    removingLeadingZeros(v);

    for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        number += std::to_string(*it);
    }

    return std::stoi(number);
}

vector<int> bigInt::karatsuba_multi(std::vector<int> A, std::vector<int> B) {
    int numDigitsA = A.size(), numDigitsB = B.size();

    if ((numDigitsA == 1) && (numDigitsB == 1)) { //if both A and B are single digits
        std::vector<int> ans;
        int m = A[0] * B[0]; //multiplying single digits
        ans = convertToVector(m);
        return ans;
    }
    else {
        //fix length, if 2 digits its fine, if 3 make 4, if 4 its fine
        addLeadingZeros(A, B);


        int size = A.size();
        int half = size / 2;


        std::vector<int> subArray_A0, subArray_B0,
                subArray_A1, subArray_B1;

        int i = 0;
        int j = half;

        while (i < half) {
            subArray_A0.push_back(A[i]);
            subArray_B0.push_back(B[i]);
            i++;
        }

        while (j < size) {
            subArray_A1.push_back(A[j]);
            subArray_B1.push_back(B[j]);
            j++;
        }

        std::vector<int> c2 = karatsuba_multi(subArray_A1, subArray_B1); //1st multiplication
        std::vector<int> c0 = karatsuba_multi(subArray_A0, subArray_B0); //2nd multiplication
        std::vector<int> p1 = karatsuba_multi(addVectors(subArray_A1, subArray_A0),
                                              addVectors(subArray_B1, subArray_B0)); //3rd multiplication
        std::vector<int> c1 = subtractVectors(p1, addVectors(c2, c0));

        if ((size % 2) != 0) {
            shiftPower10(size - 1, c2);
        } else {
            shiftPower10(size, c2);
        }
        shiftPower10(half, c1);

        std::vector <int> c2PlusC1 = removingLeadingZeros(addVectors(c2,c1));
        std::vector <int> result = removingLeadingZeros(addVectors(c2PlusC1, c0));

        return result;
    }
}

// Public Functions
void bigInt::operator = (const int &d) {
    std::vector <int> result;

    std::string number = std::to_string(d);
    for (int i = 0; i < number.length(); i++) {
        std::string n (1, number[i]);
        result.push_back(std::stoi(n));
    }

    _value = result;
}

bigInt bigInt::operator * (bigInt &b) {
    bigInt result;
    vector<int> tempA = _value;
    vector<int> tempB = b._value;
    reverse(tempA.begin(),tempA.end()); //Reverse vector
    reverse(tempB.begin(),tempB.end()); //Reverse vector
    vector<int> resultVector = karatsuba_multi(tempA, tempB);
    reverse(resultVector.begin(),resultVector.end()); //Reverse vector
    result._value = resultVector;
    return result;
}

bigInt bigInt::operator ^ (bigInt &b) {
    bigInt result;
    vector<int> tempA = _value;
    vector<int> tempB = b._value;
    reverse(tempA.begin(),tempA.end()); //Reverse vector
    reverse(tempB.begin(),tempB.end()); //Reverse vector
    int tempIntA = vectorToInt(tempA);
    int tempIntB = vectorToInt(tempB); // this error is in this spot
    vector<int> powerValue = power(tempIntA, tempIntB);
    reverse(powerValue.begin(),powerValue.end()); //Reverse vector
    result._value = powerValue;
    return result;
}

std::ostream & operator << (std::ostream &out, const bigInt &c) {
    for(int i = 0; i < c._value.size(); i++) {
        out << c._value[i];
    }
    return out;
}