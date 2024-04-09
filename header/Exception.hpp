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
		return "Belum siap untuk dipanen!";
	}
};

class HerbivoresEatMeatException: public exception {
    const char* what() const throw() {
		return "Herbivora hanya bisa memakan tumbuhan";
	}
};

class CarnivoresEatPlantsException: public exception {
    const char* what() const throw() {
		return "Karnivora hanya bisa memakan daging";
	}
};

class EatMaterialException: public exception{
	const char* what() const throw() {
		return "Tumbuhan material tidak bisa dimakan!";
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

class InvalidTypeException: public exception {
    const char* what() const throw() {
        return "Tipe yang dipilih salah!";
    }
};

class FullSlotException: public exception {
    const char* what() const throw() {
        return "Petak penuh!";
    }
};

class WrongInputException: public exception {
    const char* what() const throw() {
        return "Input tidak sesuai!";
    }
};

class NotEnoughInventoryException: public exception {
    const char* what() const throw() {
        return "Tidak cukup slot di penyimpanan!";
    }
};

class NotEnoughToHarvestException: public exception {
    const char* what() const throw() {
        return "Tidak cukup untuk dipanen!";
    }
};

class NothingToFeed: public exception {
    const char* what() const throw() {
        return "Tidak ada yang bisa diberi makan!";
    }
};


#endif