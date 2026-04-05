A C++ implementation of a custom string class (MyString) built on manual heap memory management. Covers the Rule of Five — constructor, destructor, copy constructor, copy assignment, move constructor, and move assignment — as well as operator overloading for comparison (<, >, ==, etc.) and concatenation (+, +=). Explores object construction/destruction tracing, compiler copy elision (-fno-elide-constructors), and valgrind memory leak testing.

This project was for my C++ course, where I learned the deep theory and details of the language. Below are my theory responses to several questions.

---

**Annotating the BASIC4TRACE output (line #, basic 4 call, variable name & where created/found from):**

[1] 15,constructor,x
[2] 16,constructor,y
[3] 18,copy constructor,a
[4] 18,copy constructor,b
[5] 7,constructor,t
[6] entering operator+
[7] 8,constructor,temp
[8] 8,copy constructor, u1 from return temp
[9] 8,destructor,temp
[10] entering operator+
[11] 8,constructor,temp
[12] 8,copy constructor, u2 from return temp
[13] 8,destructor,temp
[14] 8,copy constructor, u3 from return a + t + b
[15] 8,destructor,u2
[16] 8,destructor,u1
[17] 18,destructor,t
[18] 18,copy constructor, z from u3
[19] 18,destructor,u3
[20] 18,destructor,b
[21] 18,destructor,a
[22] cout << z << endl;
[23] 20,destructor,z
[24] 20,destructor,y
[25] 20,destructor,x

**Changes to BASIC4TRACE output after changing test5.cpp's add() to pass by const reference ( static MyString add(const MyString& a, const MyString& b) ):**

Passing by reference rather than value makes it so that we don't have to copy the arguments. So, the BASIC4TRACE output has fewer MyString(const MyString&) lines and fewer destructor lines for when these copies must disappear.

**What a -fno-elide-constructors flag does in Makefile:**

The flag disables the optimization of not using copy constructors unnecessarily. This is reflected in the log's absence of creating a local result, copying, and destructing, especially when working within operator+.

**Analyzing which copy calls are replaced by move calls after implementing move operations:**

BASIC4TRACE: (0x7ffd5dcaf2c0)->MyString(const char *)
BASIC4TRACE: (0x7ffd5dcaf2d0)->MyString(const char *)
BASIC4TRACE: (0x7ffd5dcaf300)->MyString(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf2f0)->MyString(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf260)->MyString(const char *)
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7ffd5dcaf200)->MyString(const MyString&)
BASIC4TRACE: op+=(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf1a0)->MyString()
BASIC4TRACE: (0x7ffd5dcaf200)->op=(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf1a0)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf270)->MyString(MyString&&)
BASIC4TRACE: (0x7ffd5dcaf200)->~MyString()
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7ffd5dcaf200)->MyString(const MyString&)
BASIC4TRACE: op+=(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf1a0)->MyString()
BASIC4TRACE: (0x7ffd5dcaf200)->op=(const MyString&)
BASIC4TRACE: (0x7ffd5dcaf1a0)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf280)->MyString(MyString&&)
BASIC4TRACE: (0x7ffd5dcaf200)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf310)->MyString(MyString&&)
BASIC4TRACE: (0x7ffd5dcaf280)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf270)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf260)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf2e0)->MyString(MyString&&)
BASIC4TRACE: (0x7ffd5dcaf310)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf2f0)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf300)->~MyString()
one and two
BASIC4TRACE: (0x7ffd5dcaf2e0)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf2d0)->~MyString()
BASIC4TRACE: (0x7ffd5dcaf2c0)->~MyString()

Many copy constructions are replaced by move constructions, as reflected by MyString(MyString&&). Copy operations were sometimes replaced by move operations when there existed temporary objects. Specifically, when operator+ attempts to return temp (local), since the object is temporary, we use a move operator here instead of a copy operator. This is safe because the data pointer is transferred and the old one is replaced by a nullptr, which can be safely deleted on its own, and separately from when the transferred data object might need to be destructed. The temporary will not be used again, so this also ensures safety. The copy constructor calls not replaced by move constructor calls were when we were constructing named objects, as these cannot bind to MyString&& (for move construction). This ensures we keep original data and follow intended behavior.
