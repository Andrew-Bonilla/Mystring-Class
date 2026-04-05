CC  = g++
CXX = g++

CFLAGS   = -g -Wall

# Comment out one of the following two lines to enable/disable BASIC4TRACE
CXXFLAGS = -g -Wall -std=c++14 -fno-elide-constructors -DBASIC4TRACE
#CXXFLAGS = -g -Wall -std=c++14 -fno-elide-constructors

executables = test1 test2 test3 test4 test5 test6
objects = mystring.o test1.o test2.o test3.o test4.o test5.o test6.o

.PHONY: default
default: $(executables)

$(executables): mystring.o

$(objects): mystring.h

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default
