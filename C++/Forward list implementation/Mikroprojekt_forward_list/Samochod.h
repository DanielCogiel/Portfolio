#include <iostream>
#include <fstream>
#include <sstream>
#include <crtdbg.h>

using namespace std;

#ifndef SAMOCHOD_H
#define SAMOCHOD_H
/**Klasa reprezentuj¹ca samochód.*/
class Samochod
{
public:
	string marka, model, VIN;
	int przebieg;
public:
	Samochod() : marka(""), model(""), VIN(""), przebieg(0) {}
	Samochod(string _marka, string _model, string _VIN, int _przebieg) : marka(_marka), model(_model), VIN(_VIN), przebieg(_przebieg) {}
	~Samochod() {}
	/**Metoda wyœwietlaj¹ca atrybuty samochodu.
	* @param output Strumieñ wyjœciowy
	*/
	void display(ostream& output = cout);
	/**Metoda wczytuj¹ca atrybuty samochodu z podanego strumienia wejœciowego.
	* @param Strumieñ wejœciowy
	*/
	void wczytaj_z_pliku(ifstream& input);
};

void Samochod::display(ostream& output)
{
	output << marka << " " << model << " " << VIN << " " << przebieg;
}

void Samochod::wczytaj_z_pliku(ifstream& input)
{
	if (input.good())
	{
		string wiersz;
		stringstream s_wiersz;
		getline(input, wiersz);
		s_wiersz << wiersz;
		s_wiersz >> marka >> model >> VIN >> przebieg;
	}
}

#endif