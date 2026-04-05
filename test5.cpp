// test5.cpp

#include "mystring.h"

static MyString add(const MyString a, const MyString b)
{
    MyString t{" and "};
    return a + t + b;
}

int main()
{
    using namespace std;

    MyString x{"one"};
    MyString y{"two"};

    MyString z = add(x, y);
    cout << z << endl;
    return 0;
}
