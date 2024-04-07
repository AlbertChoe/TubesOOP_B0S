#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
using namespace std;

class ExampleException: public exception {
    const char* what() const throw() {
		return "Example Error Message";
	}
};

class HarvestNotReadyException: public exception{
	const char* what() const throw() {
		return "Not ready for harvest!";
	}
};

class HerbivoresEatMeatException: public exception {
    const char* what() const throw() {
		return "Herbivores can only eat plants";
	}
};

class CarnivoresEatPlantsException: public exception {
    const char* what() const throw() {
		return "Carnivores can only eat meat";
	}
};

class EatMaterialException: public exception{
	const char* what() const throw() {
		return "Material cannot be eaten!";
	}
};

#endif