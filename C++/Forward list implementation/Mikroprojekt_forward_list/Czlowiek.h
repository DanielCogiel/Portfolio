#include <iostream>
#include <fstream>
#include <sstream>
#include <crtdbg.h>

using namespace std;

#ifndef CZLOWIEK_H
#define CZLOWIEK_H
/**Klasa reprezentuj�ca cz�owieka.*/
class Czlowiek
{
public:
	string imie, nazwisko, PESEL;
	int wiek;
public:
	Czlowiek() : imie(""), nazwisko(""), PESEL(""), wiek(0) {}
	Czlowiek(string _imie, string _nazwisko, string _PESEL, int _wiek) : imie(_imie), nazwisko(_nazwisko), PESEL(_PESEL), wiek(_wiek) {}
	~Czlowiek() {}
	/**Metoda wy�wietlaj�ca atrybuty cz�owieka.
	* @param output Strumie� wyj�ciowy
	*/
	void display(ostream& output = cout);
	/**Metoda wczytuj�ca atrybuty cz�owieka z podanego strumienia wej�ciowego.
	* @param Strumie� wej�ciowy
	*/
	void wczytaj_z_pliku(ifstream& input);
};

void Czlowiek::display(ostream& output)
{
	output << imie << " " << nazwisko << " " << PESEL << " " << wiek;
}

void Czlowiek::wczytaj_z_pliku(ifstream& input)
{
	if (input.good())
	{
		string wiersz;
		stringstream s_wiersz;
		getline(input, wiersz);
		s_wiersz << wiersz;
		s_wiersz >> imie >> nazwisko >> PESEL >> wiek;
	}
}

#endif