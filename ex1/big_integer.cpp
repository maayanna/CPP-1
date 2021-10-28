/**
 * @file big_integer.cpp
 * @author  Maayann Affriat <maayann.affriat@mail.huji.ac.il>
 * @version 1.0
 * @date 3 sep 2018
 *
 * @brief
 *
 * @section LICENSE
 * This program is not a free software.
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <algorithm>
#include <iostream>
#include "big_integer.h"

/**
 * Default constructor
 */
big_integer::big_integer()
{
    this->_data = "0";
    this->_sign = POS;
}

/**
 * Copy constuctor
 * @param other - big_integer
 */
big_integer::big_integer(const big_integer& other)
{
    this->_data = other._data;
    this->_sign = other._sign;
}

/**
 * constructor receving an integer
 * @param num - int number
 */
big_integer::big_integer(int num)
{
    string myNum = to_string(num);
    this->_sign = POS;
    if ( num < 0)
    {
        this->_sign = NEG;
        myNum = myNum.substr(1, myNum.size());
    }
    reverse(myNum.begin(), myNum.end());
    this->_data = myNum;
}

/**
 * Constructor receving a string
 * @param str - string
 */
big_integer::big_integer(string str)
{
    this->_sign = POS;
    if ( str[0] == '-') //check if negative number
    {
        this->_sign = NEG;
        str = str.substr(1, str.size());
    }
    str = clearZ(str);
    if (!_checkstr(str) || checkZeros(str)) //Not a legal string
    {
        this->_data = "0";
    }
    else
    {
        reverse(str.begin(), str.end());
        this->_data = str;
    }
    if ( this->_data == "0")
    {
        this->_sign = POS;
    }
}

/**
 * Check if the string is legal
 * @param string1 - string
 * @return true iff the string is legal
 */
bool big_integer::_checkstr(string string1)
{
    for (char i : string1)
    {
        if ( i < '0' || '9' < i )
        {
            return false;
        }
    }
    return true;
}

/**
 * A regulat sum operation
 * @param dat1 - first number
 * @param dat2 - secnd number
 * @return result
 */
string big_integer::_sum(string dat1, string dat2)
{
    string dataToReturn;
    size_t s1 = dat1.size();
    size_t s2 = dat2.size();
    size_t diff =  s1 - s2;
    for (unsigned int i = 0; i < diff; ++i)
    {
        dat2 += '0'; //to be the same size
    }
    int result;
    bool remain = false;
    for (unsigned int j = 0; j < s1; ++j)
    {
        result = dat1[j] + dat2[j] - 2 * '0';
        if (remain)
        {
            result++;
            remain = false;
        }
        if ( result > 9)
        {
            result -= 10;
            remain = true;
        }
        dataToReturn += to_string(result);
    }
    if (remain)
    {
        dataToReturn += '1';
    }
    for (unsigned int i = 0; i < diff; ++i)
    {
        dat2.pop_back();
    }
    if (checkZeros(dataToReturn) || checkZeros(dat2)) //If too many zeros
    {
        reverse(dataToReturn.begin(), dataToReturn.end());
        dataToReturn = clearZ(dataToReturn);
        reverse(dataToReturn.begin(), dataToReturn.end());
    }
    return dataToReturn;
}

/**
 * A regular sub operation
 * @param dat1 - first number
 * @param dat2 - secnd number
 * @return - result
 */
string big_integer::_sub(string dat1, string dat2)
{
    string dataToReturn;
    size_t s1 = dat1.size();
    size_t s2 = dat2.size();
    size_t diff = s1 - s2;

    for (unsigned int i = 0; i < diff; ++i)
    {
        dat2 += '0'; //to be the same size
    }

    int result;
    bool remain = false;

    for (unsigned int j = 0; j < s1; ++j)
    {
        if (remain)
        {
            dat1[j] = (char) (dat1[j] - 1);
        }
        if (dat1[j] < dat2[j])
        {
            result = dat1[j] + 10 - dat2[j];
            remain = true;
        }
        else
        {
            result = dat1[j] - dat2[j];
            remain = false;
        }

        dataToReturn += to_string(result);
    }

    for (unsigned int i = 0; i < diff; ++i)
    {
        dat2.pop_back();
    }
    reverse(dataToReturn.begin(), dataToReturn.end()); //clearing the zeros
    dataToReturn = clearZ(dataToReturn);
    reverse(dataToReturn.begin(), dataToReturn.end());
    return dataToReturn;
}

/**
 * a multiplication operation with a lonely int
 * @param data1 - int
 * @param data2 - big_int
 * @return result
 */
string big_integer::_mult(char data1, string data2)
{
    string toReturn;
    int result = 0, count = 0;
    size_t size = data2.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        result = (data1 - '0') * (data2[i] - '0');
        result += count;
        count = 0;
        while ( result >= 10)
        {
            count++;
            result -= 10;
        }
        toReturn += to_string(result);
    }

    if ( count != 0)
    {
        toReturn += to_string(count);
    }
    return toReturn;
}

/**
 * A multiplication operation between big_int and big_int
 * @param data1 - big_int
 * @param data2 - big_int
 * @return result
 */
string big_integer::_multiplication(string data1, string data2)
{
    string toReturn = "0", temp;
    int counter = 0;
    size_t size = data1.size();
    int big;

    for (unsigned int i = 0; i < size; ++i)
    {
        temp = _mult(data1[i], data2); //every int of one with a big_int
        reverse(temp.begin(), temp.end());
        for (int j = 0; j < counter; ++j)
        {
            temp += '0';
        }
        counter++;
        reverse(temp.begin(), temp.end());
        big = findBig(temp, toReturn);
        if (big == 1)
        {
            toReturn = _sum(temp, toReturn);
        }
        else
        {
            toReturn = _sum(toReturn, temp);
        }
    }
    if (checkZeros(toReturn)) //clear all zeros
    {
        toReturn = "0";
    }
    reverse(toReturn.begin(), toReturn.end());
    return toReturn;
}

/**
 * regulat division operation
 * @param data1 - big_int
 * @param data2 _big_int
 * @return result
 */
string big_integer::div(string data1, string data2)
{
    string quotient;
    int count = (int) (data1.size() - 1);
    int div;
    big_integer a, b, flag, r, d;
    int newDat = data1[count] - '0';
    a = big_integer(newDat);
    reverse(data2.begin(), data2.end());
    b = big_integer(data2);
    r = big_integer();
    string data = a.getData();

    while (count > -1)
    {
        while (a < b && count > -1)
        {
            if (count <= 0)
            {
                break;
            }
            count--;
            quotient += '0';
            newDat = data1[count] - '0';
            reverse(data.begin(), data.end());
            data += to_string(newDat);
            data = clearZ(data);
            a.setData(data);
        }
        div = 0;
        flag = big_integer();
        if (a.getData()[a.getData().size() - 1] == '0')
        {
            data = a.getData();
            data.pop_back();
            a.setData(data);
        }
        while (flag <= a)
        {
            flag += b;
            div++;
        }
        div--;
        flag -= b;
        quotient += to_string(div);
        d = big_integer(div);
        r = a - (d * b); //rest
        if (checkZeros(r.getData()))
        {
            data = "0";
        }
        else
        {
            data = r.getData();
        }
        count--;
        newDat = data1[count] - '0';
        reverse(data.begin(), data.end());
        data += to_string(newDat);
        data = clearZ(data);
        a.setData(data);
    }
    quotient = clearZ(quotient);
    return quotient;
}

/**
 * check if all the data is only zeros and clear them
 * @param data - string
 * @return true iff only zeros
 */
bool big_integer::checkZeros(string data)
{
    size_t size = data.size();
    for (unsigned int i = 0; i < size; ++i)
    {
        if (data[i] != '0')
        {
            return false;
        }
    }
    return true;
}

/**
 * Find the biggest numbr
 * @param dat1 -big_int
 * @param dat2 - big_int
 * @return 1 iff big1 bigger than big2, 2 if the same, 0 otherwise
 */
int big_integer::findBig(string dat1, string dat2)
{
    string dataToReturn;
    auto s1 = (int)dat1.size();
    auto s2 = (int)dat2.size();
    int diff = s1 - s2;

    if( diff < 0)
    {
        return 0;
    }
    else if ( diff > 0)
    {
        return 1;
    }
    for (int i = s1 -1; i >= 0; i--)
    {
        if ( dat1[i] < dat2[i])
        {
            return 0;
        }
        else if( dat1[i] > dat2[i])
        {
            return 1;
        }
    }
    return 2; //Same number
}

/**
 * check the signs of two big_int
 * @param big1
 * @param big2
 * @return 2 iff the same sign, 0 if big1 neg, 1 otherwise
 */
int big_integer::checkSign(const big_integer& big1, const big_integer& big2)
{
    int sign1 = big1.getSign();
    int sign2 = big2.getSign();

    if (sign1 * sign2 == POS)
    {
        return 2; //Same sign
    }
    else if( sign1 == NEG)
    {
        return 0;
    }
    return 1;
}

/**
 * Operator +=
 */
big_integer& big_integer::operator+=(const big_integer &other)
{
    string data;
    int big = findBig(getData(), other.getData());

    if ( getSign() * other.getSign() > 0)
    {
        if( big == 1)
        {
            data = _sum(getData(), other.getData());
        }
        else
        {
            data = _sum(other.getData(), getData());
        }
    }
    else if (big == 1)
    {
        data = _sub(getData(), other.getData());
    }
    else
    {
        data = _sub(other.getData(), getData());
        setSign(other.getSign());
    }
    reverse(data.begin(), data.end());
    setData(data);
    return *this;
}

/**
 * Operator +
 */
big_integer operator+(const big_integer& big1, const big_integer& big2)
{
    big_integer myBig(big1);
    myBig += big2;
    return myBig;
}

/**
 * Operator -=
 */
big_integer& big_integer::operator-=(const big_integer &other)
{
    string data;
    int big = findBig(getData(), other.getData());

    if ( getSign() * other.getSign() > 0)
    {
        if( big == 1)
        {
            data = _sub(getData(), other.getData());
        }
        else
        {
            data = _sub(other.getData(), getData());
            setSign(other.getSign() * -1);
        }
    }
    else if (big == 1)
    {
        data = _sum(getData(), other.getData());
    }
    else
    {
        data = _sum(other.getData(), getData());
    }
    reverse(data.begin(), data.end());
    setData(data);
    return *this;
}

/**
 * Operator -
 */
big_integer operator-(const big_integer& big1, const big_integer& big2)
{
    big_integer myBig(big1);
    myBig -= big2;
    return myBig;
}

/**
 * Operator *=
 */
big_integer& big_integer::operator*=(const big_integer &other)
{
    int newSign = getSign() * other.getSign();
    setSign(newSign);
    string data;
    data = _multiplication(getData(), other.getData());
    if (data == "0")
    {
        setSign(POS);
    }
    setData(data);
    return *this;
}

/**
 * Operator *
 */
big_integer operator*(const big_integer& big1, const big_integer& big2)
{
    big_integer myBig(big1);
    myBig *= big2;
    return myBig;
}

/**
 * Operator /=
 */
big_integer& big_integer::operator/=(const big_integer& other)
{
    if ( "0" == other.getData())  //division by Zero
    {
        string data = "0";
        setData(data);
        setSign(POS);
        return *this;
    }
    int sign = getSign() * other.getSign();
    setSign(sign);
    string otherData = other.getData();
    string data = div(getData(), otherData);
    if ( data == "0")
    {
        setSign(POS);
    }
    setData(data);
    return *this;
}

/**
 * Operator /
 */
big_integer operator/(const big_integer &big1, const big_integer &big2)
{
    big_integer myBig(big1);
    myBig /= big2;
    return myBig;
}

/**
 * Operator %
 */
big_integer operator%(const big_integer& big1, const big_integer& big2)
{
    big_integer toreturn = big_integer();
    if ( "0" == big2.getData())  //division by Zero
    {
        string data = "0";
        toreturn.setData(data);
        toreturn.setSign(POS);
        return toreturn;
    }
    big_integer myBig (big1);
    myBig /= big2;
    toreturn = big1 - ( myBig * big2);
    if (toreturn.getData() == "0")
    {
        toreturn.setSign(POS);
    }
    return toreturn;
}

/**
 * Operator <
 */
bool operator<(const big_integer& big1, const big_integer& big2)
{
    int sign, big;
    sign = big_integer::checkSign(big1, big2);
    big = big_integer::findBig(big1.getData(), big2.getData());
    if ( sign == 0)
    {
        return true;
    }
    else if ( sign == 2 && big1.getSign()  == NEG && big == 1)
    {
        return  true;
    }
    else if(sign == 2 && big1.getSign() == POS && big == 0)
    {
        return true;
    }
    return false;
}

/**
 * Operator >
 */
bool operator>(const big_integer& big1, const big_integer& big2)
{
    int sign, big;
    sign = big_integer::checkSign(big1, big2);
    big = big_integer::findBig(big1.getData(), big2.getData());
    if ( sign == 1)
    {
        return true;
    }
    else if ( sign == 2 && big1.getSign()  == NEG && big == 0)
    {
        return true;
    }
    else if(sign == 2 && big1.getSign() == POS && big == 1)
    {
        return true;
    }
    return false;
}


/**
 * Operator <=
 */
bool operator<=(const big_integer& big1, const big_integer& big2)
{
    return !(big1 > big2);
}

/**
 * Operator >=
 */
bool operator>=(const big_integer& big1, const big_integer& big2)
{
    return !(big1 < big2);
}


/**
 * Operator ==
 */
bool operator==(const big_integer& big1, const big_integer& big2)
{
    if(big1.getSign() * big2.getSign() == NEG)
    {
        return false;
    }
    int big = big_integer::findBig(big1.getData(), big2.getData());
    if( big != 2)
    {
        return false;
    }
    return true;
}


/**
 * Operator !=
 */
bool operator!=(const big_integer& big1, const big_integer& big2)
{
    return !(big1 == big2);
}


/**
 * Operator << (Printing operator)
 */
std::ostream& operator<<(std::ostream& os, const big_integer& myBig)
{
    string dataReturn = myBig.getData();
    reverse(dataReturn.begin(), dataReturn.end());

    if (myBig.getSign() == NEG)
    {
        return os << "-" << dataReturn;
    }
    os << dataReturn;
    return os;
}


/**
 * Operator =
 */
big_integer& big_integer::operator=(const big_integer& big) = default;

/**
 * Getter to the data
 * @return _data
 */
string big_integer::getData() const
{
    return this->_data;
}

/**
 * setter data
 * @param newData
 */
void big_integer::setData(string& newData)
{
    reverse(newData.begin(), newData.end());
    if (checkZeros(newData))
    {
        this->_data = "0";
        this->_sign = POS;
    }
    else
    {
        this->_data = newData;
    }
}

/**
 * Getter to the sign
 * @return _sign
 */
int big_integer::getSign() const
{
    return this->_sign;
}

/**
 * Setter sign
 * @param newSign
 */
void big_integer::setSign(int newSign)
{
    this->_sign = newSign;
}

/**
 * Clear the zeros if there are too much
 * @param data -data to clear
 * @return cleared data
 */
string big_integer::clearZ(string data)
{
    reverse(data.begin(), data.end());
    int count = (int) (data.size() - 1);
    while (data[count] == '0')
    {
        if (count == 0)
        {
            break;
        }
        data.pop_back();
        count--;
    }
    reverse(data.begin(), data.end());
    return data;
}