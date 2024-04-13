#ifndef PCOLOR_HPP
#define PCOLOR_HPP

/**
 * @file pcolor.hpp
 * @brief Print characters with colors in terminal.
 * 
 * Provides functions to print characters in different colors.
 * Currently supports red, green, and blue colors.
 */

/// Reset color
#define NORMAL "\x1B[0m"
/// Red color
#define RED "\x1B[31m"
/// Green color
#define GREEN "\x1B[32m"
/// Blue color
#define BLUE "\x1B[34m"

/**
 * @brief Print a character in red color.
 * @param c Character to print.
 */
void print_red(char c);

/**
 * @brief Print a character in green color.
 * @param c Character to print.
 */
void print_green(char c);

/**
 * @brief Print a character in blue color.
 * @param c Character to print.
 */
void print_blue(char c);

#endif // PCOLOR_HPP
