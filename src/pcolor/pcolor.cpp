#include "pcolor.hpp"
#include <iostream>

/**
 * @brief Implementation of printing a character in red color.
 * @param c Character to print.
 */
void print_red(char c) {
    std::cout << RED << c << NORMAL;
}

/**
 * @brief Implementation of printing a character in green color.
 * @param c Character to print.
 */
void print_green(char c) {
    std::cout << GREEN << c << NORMAL;
}

/**
 * @brief Implementation of printing a character in blue color.
 * @param c Character to print.
 */
void print_blue(char c) {
    std::cout << BLUE << c << NORMAL;
}
