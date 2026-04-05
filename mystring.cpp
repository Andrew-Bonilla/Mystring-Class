#include <cstring>
#include <cstdio>

#include "mystring.h"

// default constructor

MyString::MyString() {
#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString()\n", this);
#endif

    data = new char[1];
    data[0] = '\0';

    len = 0;
}

// constructor

MyString::MyString(const char *p) {
#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString(const char *)\n", this);
#endif

    if (p) {
        len = strlen(p);
        data = new char[len+1];
        strcpy(data, p);
    } else {
        data = new char[1];
        data[0] = '\0';
        len = 0;
    }
}

// destructor

MyString::~MyString() {
#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->~MyString()\n", this);
#endif

    delete[] data;
}

// copy constructor

MyString::MyString(const MyString& s) {
#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString(const MyString&)\n", this);
#endif

    len = s.len;

    data = new char[len+1];
    strcpy(data, s.data);
}

// copy assignment

MyString& MyString::operator=(const MyString& rhs) {
#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->op=(const MyString&)\n", this);
#endif

    if (this == &rhs) {
        return *this;
    }

    // first, deallocate memory that 'this' used to hold

    delete[] data;

    // now copy from rhs

    len = rhs.len;

    data = new char[len+1];
    strcpy(data, rhs.data);

    return *this;
}

MyString::MyString(MyString&& s1) noexcept {
#ifdef BASIC4TRACE
	fprintf(stderr, "BASIC4TRACE: (%p)->MyString(MyString&&)\n", this);
#endif
	data = s1.data;
	len = s1.len;

	s1.data = nullptr;
	s1.len = 0;
}

MyString& MyString::operator=(MyString&& s1) noexcept {
#ifdef BASIC4TRACE
	fprintf(stderr, "BASIC4TRACE: (%p)->op=(MyString&&)\n",this);
#endif
	if (this != &s1) {
		delete[] data;
		data = s1.data;
		len = s1.len;
		s1.data = nullptr;
		s1.len = 0;
	}
	return *this;
}

// operator+

MyString operator+(const MyString& s1, const MyString& s2) {
#ifdef BASIC4TRACE
    fprintf(stderr,
            "BASIC4TRACE: op+(const MyString&, const MyString&)\n");
#endif
    MyString result(s1);
    result += s2;
    return result;
}

//+= operator

MyString& MyString::operator+=(const MyString& s2) {
#ifdef BASIC4TRACE
    fprintf(stderr,
            "BASIC4TRACE: op+=(const MyString&)\n");
#endif

    MyString temp;

    delete[] temp.data;

    temp.len = len + s2.len;

    temp.data = new char[temp.len+1];
    strcpy(temp.data, data);
    strcat(temp.data, s2.data);
    *this = temp;
    return *this;
}


// put-to operator

std::ostream& operator<<(std::ostream& os, const MyString& s) {
    os << s.data;
    return os;
}

// get-from operator

std::istream& operator>>(std::istream& is, MyString& s) {
    // this is kinda cheating, but this is just to illustrate how this
    // function can work.

    std::string temp;
    is >> temp;

    delete[] s.data;

    s.len = strlen(temp.c_str());
    s.data = new char[s.len+1];
    strcpy(s.data, temp.c_str());

    return is;
}

// operator[] - in real life this function should be declared inline

char& MyString::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::out_of_range{"MyString::op[]"};
    }
    return data[i];
}

// operator[] const - in real life this should be inline

const char& MyString::operator[](int i) const {
    // illustration of casting away constness
    return ((MyString&)*this)[i];

    // The C-style casting above works, but the proper way
    // to cast away constness in C++ is to do the following:
    //
    // return const_cast<MyString&>(*this)[i];
}

bool operator==(const MyString& s1, const MyString& s2) {
	return std::strcmp(s1.data,s2.data) == 0;
}

bool operator!=(const MyString& s1, const MyString& s2) {
	return !(s1 == s2);
}

bool operator<(const MyString& s1, const MyString& s2) {
	return std::strcmp(s1.data, s2.data) < 0;
}

bool operator>(const MyString& s1, const MyString& s2) {
	return s1 < s2;
}

bool operator<=(const MyString& s1, const MyString& s2) {
	return !(s2 < s1);
}

bool operator>=(const MyString& s1, const MyString& s2) {
	return !(s1 < s2);
}



