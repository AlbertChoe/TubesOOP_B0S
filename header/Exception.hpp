#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
using namespace std;

class ExampleException: public exception {
    const char* what() const throw() {
		return "Example Error Message";
	}
};

#endif