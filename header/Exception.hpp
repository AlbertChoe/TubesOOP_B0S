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

class EmptySlotInputException : public exception{
	const char* what() const throw() {
		return "Kamu mengambil harapan kosong dari penyimpanan.\nSilahkan masukan slot yang berisi makanan.\n";
	}
};

class InvalidSlotInputException : public exception{
	const char* what() const throw() {
		return "Apa yang kamu lakukan??" "!! Kamu mencoba untuk memakan itu?!!\nSilahkan masukan slot yang berisi makanan.\n";
    }
};

class NotEnoughAddPlayerException : public exception{
	const char* what() const throw() {
		return "Uang tidak cukup!\n";
    }
};

class WrongInputAddPlayerException : public exception{
	const char* what() const throw() {
		return "Masukan tidak valid\nHanya menerima input petani atau peternak saja\n";
    }
};

class EmptySlotSellException : public exception{
	const char* what() const throw() {
		return "Kamu mengambil harapan kosong dari penyimpanan.\nSilahkan masukan pilihan yang valid.\n";
	}
};

#endif