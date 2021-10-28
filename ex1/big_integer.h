/**
 * @file big_integer.h
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
#include <string>
using namespace std;

// -------------------------- const definitions -------------------------
#ifndef EX1_BIG_INTEGER_H
#define EX1_BIG_INTEGER_H
#define POS 1
#define NEG (-1)

/**
 * A class defining a big integer
 */
class big_integer
{
public:
    /**
     * Default constructor
     */
    big_integer();

    /**
     * Copy constructor
     * @param other - biginteger
     */
    big_integer(const big_integer& other);

    /**
     * Constructor with an integer
     * @param num - int
     */
    big_integer(int num);

    /**
     * constructor witha string
     * @param str - string
     */
    big_integer(string str);

    /**
     * Getter to the sign
     * @return _sign
     */
    int getSign() const;

    /**
     * Getter to the data
     * @return _data
     */
    string getData() const;

    /**
     * setter data
     * @param newData
     */
    void setData(string& newData);

    /**
     * Setter sign
     * @param newSign
     */
    void setSign(int newSign);

    /**
     * Operator +=
     */
    big_integer& operator+=(const big_integer& other);

    /**
     * Operator +
     */
    friend big_integer operator+(const big_integer& big1, const big_integer& big2);

    /**
     * Operator -=
     */
    big_integer& operator-=(const big_integer& other);

    /**
     * Operator -
     */
    friend big_integer operator-(const big_integer& big1, const big_integer& big2);

    /**
     * Operator *=
     */
    big_integer &operator*=(const big_integer &other);

    /**
     * Operator *
     */
    friend big_integer operator*(const big_integer& big1, const big_integer& big2);

    /**
     * Operator /=
     */
    big_integer& operator/=(const big_integer& other);

    /**
     * Operator /
     */
    friend big_integer operator/(const big_integer& big1, const big_integer& big2);

    /**
     * Operator %
     */
    friend big_integer operator%(const big_integer &big1, const big_integer &big2);

    /**
     * Operator <
     */
    friend bool operator<(const big_integer& big1, const big_integer& big2);

    /**
     * Operator <=
     */
    friend bool operator<=(const big_integer& big1, const big_integer& big2);

    /**
     * Operator >
     */
    friend bool operator>(const big_integer& big1, const big_integer& big2);

    /**
     * Operator >=
     */
    friend bool operator>=(const big_integer& big1, const big_integer& big2);

    /**
     * Operator ==
     */
    friend bool operator==(const big_integer& big1, const big_integer& big2);

    /**
     * Operator !=
     */
    friend bool operator!=(const big_integer& big1, const big_integer& big2);

    /**
     * Operator =
     */
    big_integer& operator=(const big_integer& big);

    /**
     * Operator <<
     */
    friend ostream &operator<<(ostream &os, const big_integer& myBig);

    /* Static functions */

    /**
     * Find the biggest numbr
     * @param dat1 -big_int
     * @param dat2 - big_int
     * @return 1 iff big1 bigger than big2, 2 if the same, 0 otherwise
     */
    static int findBig(string dat1, string dat2);

    /**
     * check the signs of two big_int
     * @param big1
     * @param big2
     * @return 2 iff the same sign, 0 if big1 neg, 1 otherwise
     */
    static int checkSign(const big_integer& big1, const big_integer& big2);

    /* static fnction checking all the zeros */

    /**
     * check if all the data is only zeros and clear them
     * @param data - string
     * @return true iff only zeros
     */
    static bool checkZeros(string data);

    /**
     * Clear the zeros if there are too much
     * @param data -data to clear
     * @return cleared data
     */
    static string clearZ(string data);

    /**
     * regulat division operation
     * @param data1 - big_int
     * @param data2 _big_int
     * @return result
     */
    string div(string data1, string data2);

private:
    /* Members */
    string _data;
    int _sign;

    /**
     * Check if the string is legal
     * @param string1 - string
     * @return true iff the string is legal
     */
    bool _checkstr(string string1);

    /**
     * A regulat sum operation
     * @param dat1 - first number
     * @param dat2 - secnd number
     * @return result
     */
    string _sum(string dat1, string dat2);

    /**
     * A regular sub operation
     * @param dat1 - first number
     * @param dat2 - secnd number
     * @return - result
     */
    string _sub(string dat1, string dat2);

    /**
     * A multiplication operation between big_int and big_int
     * @param data1 - big_int
     * @param data2 - big_int
     * @return result
     */
    string _multiplication(string data1, string data2);

    /**
     * a multiplication operation with a lonely int
     * @param data1 - int
     * @param data2 - big_int
     * @return result
     */
    string _mult(char data1, string data2);


};


#endif //EX1_BIG_INTEGER_H
