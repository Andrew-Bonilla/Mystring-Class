#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <iostream>

class MyString {

public:

    // default constructor
    MyString();

    // constructor
    MyString(const char* p);

    // destructor
    ~MyString();

    // copy constructor
    MyString(const MyString& s);

    // copy assignment
    MyString& operator=(const MyString& s);

    // move constructor
    MyString(MyString&& other) noexcept;

    // move assignment
    MyString& operator=(MyString&& other) noexcept;

    // returns the length of the string
    int length() const { return len; }

    // put-to operator
    friend std::ostream& operator<<(std::ostream& os, const MyString& s);

    // get-from operator
    friend std::istream& operator>>(std::istream& is, MyString& s);

    // operator[]
    char& operator[](int i);

    // operator[] const
    const char& operator[](int i) const;

    //operators for homework
    friend bool operator==(const MyString& s1, const MyString& s2);
    friend bool operator!=(const MyString& s1, const MyString& s2);
    friend bool operator<(const MyString& s1, const MyString& s2);
    friend bool operator>(const MyString& s1, const MyString& s2);
    friend bool operator<=(const MyString& s1, const MyString& s2);
    friend bool operator>=(const MyString& s1, const MyString& s2);
    MyString& operator+=(const MyString& s2);
private:

    char* data;

    int len;
};

MyString operator+(const MyString& s1, const MyString& s2);

#endif // __MYSTRING_H__
