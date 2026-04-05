#include "mystring.h"

void f2() {
    MyString s("abc");
    int x = s[-1];
    std::cout << x << std::endl;
}

void f1() {
    MyString s("xyx");
    f2();
    std::cout << s << std::endl;
}

int main() {
    using namespace std;

    try {
        f1();
    }
    catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    cout << "That's all folks!" << endl;
}
