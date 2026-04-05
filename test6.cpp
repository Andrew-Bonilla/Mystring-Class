#include <cassert>
#include "mystring.h"

int main() {
	using namespace std;

	MyString x("test");
	MyString y("btest");

	assert(!(x==y));

	assert(x != y);

	assert(!(x < y));

	assert(y > x);

	assert(!(x<=y));
	assert(!(y>=x));

	assert(x=="test");
	assert(!("test" > x));
	
	
	MyString sp{" "};
	MyString period{"."};
	MyString str;

	str += "This" + sp + "should" + sp
	    += "work" + sp + "without"
	    += sp + "any" + sp + "memory"
	    += sp + "leak"
	    += period;

	cout << str << endl;
	
	
	return 0;
}
