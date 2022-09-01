#include <iostream>
#include <sstream>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

/**Funkcja zwracaj¹ca nazwê wejœciowego pliku tekstowego.
* @param argc Parametr wejœciowy funkcji main, liczba parametrów wejœciowych
* @param argv[] Parametr wejœciowy funkcji main, tablica wskaŸników na char
* @return Nazwa pliku
*/
string get_text_input(int argc, char* argv[]);
/**Funkcja zwracaj¹ca nazwê wejœciowego pliku binarnego.
* @param argc Parametr wejœciowy funkcji main, liczba parametrów wejœciowych
* @param argv[] Parametr wejœciowy funkcji main, tablica wskaŸników na char
* @return Nazwa pliku
*/
string get_bin_input(int argc, char* argv[]);
/**Funkcja zwracaj¹ca nazwê wyjœciowego pliku tekstowego.
* @param argc Parametr wejœciowy funkcji main, liczba parametrów wejœciowych
* @param argv[] Parametr wejœciowy funkcji main, tablica wskaŸników na char
* @return Nazwa pliku
*/
string get_text_output(int argc, char* argv[]);
/**Funkcja zwracaj¹ca nazwê wyjœciowego pliku binarnego.
* @param argc Parametr wejœciowy funkcji main, liczba parametrów wejœciowych
* @param argv[] Parametr wejœciowy funkcji main, tablica wskaŸników na char
* @return Nazwa pliku
*/
string get_bin_output(int argc, char* argv[]);
/**Funkcja zwracaj¹ca numer reprezentuj¹cy wybór, dla jakiego typu bêdzie wykonywany test listy.
* @param argc Parametr wejœciowy funkcji main, liczba parametrów wejœciowych
* @param argv[] Parametr wejœciowy funkcji main, tablica wskaŸników na char
* @return Numer wyboru
*/
int get_choice(int argc, char* argv[]);

#endif