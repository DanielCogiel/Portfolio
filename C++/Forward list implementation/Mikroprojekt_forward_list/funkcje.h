#include <iostream>
#include <sstream>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

/**Funkcja zwracaj�ca nazw� wej�ciowego pliku tekstowego.
* @param argc Parametr wej�ciowy funkcji main, liczba parametr�w wej�ciowych
* @param argv[] Parametr wej�ciowy funkcji main, tablica wska�nik�w na char
* @return Nazwa pliku
*/
string get_text_input(int argc, char* argv[]);
/**Funkcja zwracaj�ca nazw� wej�ciowego pliku binarnego.
* @param argc Parametr wej�ciowy funkcji main, liczba parametr�w wej�ciowych
* @param argv[] Parametr wej�ciowy funkcji main, tablica wska�nik�w na char
* @return Nazwa pliku
*/
string get_bin_input(int argc, char* argv[]);
/**Funkcja zwracaj�ca nazw� wyj�ciowego pliku tekstowego.
* @param argc Parametr wej�ciowy funkcji main, liczba parametr�w wej�ciowych
* @param argv[] Parametr wej�ciowy funkcji main, tablica wska�nik�w na char
* @return Nazwa pliku
*/
string get_text_output(int argc, char* argv[]);
/**Funkcja zwracaj�ca nazw� wyj�ciowego pliku binarnego.
* @param argc Parametr wej�ciowy funkcji main, liczba parametr�w wej�ciowych
* @param argv[] Parametr wej�ciowy funkcji main, tablica wska�nik�w na char
* @return Nazwa pliku
*/
string get_bin_output(int argc, char* argv[]);
/**Funkcja zwracaj�ca numer reprezentuj�cy wyb�r, dla jakiego typu b�dzie wykonywany test listy.
* @param argc Parametr wej�ciowy funkcji main, liczba parametr�w wej�ciowych
* @param argv[] Parametr wej�ciowy funkcji main, tablica wska�nik�w na char
* @return Numer wyboru
*/
int get_choice(int argc, char* argv[]);

#endif