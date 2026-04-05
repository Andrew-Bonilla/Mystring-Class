#include "mystring.h"

int main() {
    using namespace std;

    cout << "Enter a string: ";

    MyString s;

    cin >> s;

    for (int i = 0; i < s.length(); ++i) {
        if ('a' <= s[i] && s[i] <= 'z') {
            s[i] = s[i] - ('a' - 'A');
        }
    }

    cout << "Here is how to say it louder: " << s << endl;
}
