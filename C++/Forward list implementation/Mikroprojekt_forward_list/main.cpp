#include "Czlowiek.h"
#include "Samochod.h"
#include "Lista.h"
#include "funkcje.h"



int main(int argc, char* argv[])
{
	{
		string text_input = get_text_input(argc, argv);
		string bin_input = get_bin_input(argc, argv);
		string text_output = get_text_output(argc, argv);
	    string bin_output = get_bin_output(argc, argv);
		int choice = get_choice(argc, argv);

		//Blok DOUBLE
		if (choice == 1)
		{
			cout << "==================================================" << endl;
			cout << "Testowanie listy jednokierunkowej dla typu double" << endl;
			cout << "==================================================" << endl;
			//string double_input_txt = "Doubles_input.txt";
			My_forward_list<double> lista_double;
			lista_double.wczytaj_baze(text_input);
			cout << "Lista wczytana z pliku " << text_input << endl;

			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_back" << endl;

			lista_double.push_back(23.7);
			lista_double.push_back(-27.2);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_front" << endl;

			lista_double.push_front(43.1);
			lista_double.push_front(-8.2);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_back()" << endl;

			lista_double.pop_back();
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_front()" << endl;

			lista_double.pop_front();
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Rozmiar listy: " << lista_double.size() << endl;
			cout << "==========================================================================================" << endl;
			int index = 4;
			cout << "Szukanie obiektu o indeksie " << index << ":" << endl;

			cout << "Znaleziono obiekt o wartosci: " << lista_double.find(index)->get_value() << endl;
			cout << "==========================================================================================" << endl;
			cout << "Usuwanie obiektu o indeksie " << index << ":" << endl;

			lista_double.erase(4);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco:" << endl;
			lista_double.sort(0);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco:" << endl;
			lista_double.sort(1);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string text_output = "Doubles_output.txt";
			cout << "Zapisanie zawartosci kontenera do pliku " << text_output << endl;
			ofstream output(text_output);
			lista_double.show(output);
			output.close();
			cout << "==========================================================================================" << endl;
			//string double_input_bin = "Doubles_input.bin";
			cout << "Wczytywanie binarne do kontenera z pliku " << bin_input << endl;

			lista_double.clear();
			lista_double.wczytaj_binarnie(bin_input);
			lista_double.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string double_output_bin = "Doubles_output.bin";
			cout << "Zapisanie binarne do pliku " << bin_output << endl;

			lista_double.zapisz_binarnie(bin_output);
			cout << endl << endl;
		}
		//Blok STRING
		else if (choice == 2)
		{
			cout << "==================================================" << endl;
			cout << "Testowanie listy jednokierunkowej dla typu string" << endl;
			cout << "==================================================" << endl;
			//string string_input_txt = "Strings_input.txt";
			My_forward_list<string> lista_string;
			lista_string.wczytaj_baze(text_input);
			cout << "Lista wczytana z pliku " << text_input << endl;
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_back" << endl;
			lista_string.push_back("Drzewo");
			lista_string.push_back("Mebel");
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_front" << endl;
			lista_string.push_front("Szafka");
			lista_string.push_front("Monitor");
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_back()" << endl;
			lista_string.pop_back();
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_front()" << endl;
			lista_string.pop_front();
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Rozmiar listy: " << lista_string.size() << endl;
			cout << "==========================================================================================" << endl;
			int index = 4;
			cout << "Szukanie obiektu o indeksie " << index << ":" << endl;
			cout << "Znaleziono obiekt o wartosci: " << lista_string.find(index)->get_value() << endl;
			cout << "==========================================================================================" << endl;
			cout << "Usuwanie obiektu o indeksie " << index << ":" << endl;
			lista_string.erase(4);
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco:" << endl;
			lista_string.sort(0);
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco:" << endl;
			lista_string.sort(1);
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string string_output_txt = "Strings_output.txt";
			cout << "Zapisanie zawartosci kontenera do pliku " << text_output << endl;
			ofstream output(text_output);
			lista_string.show(output);
			output.close();
			cout << "==========================================================================================" << endl;
			//string string_input_bin = "Strings_input.bin";
			cout << "Wczytywanie binarne do kontenera z pliku " << bin_input << endl;
			lista_string.clear();
			lista_string.wczytaj_binarnie(bin_input);
			lista_string.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string string_output_bin = "String_output.bin";
			cout << "Zapisanie binarne do pliku " << bin_output << endl;

			lista_string.zapisz_binarnie(bin_output);
		}
		//Blok CZLOWIEK
		else if (choice == 3)
		{
			cout << "====================================================" << endl;
			cout << "Testowanie listy jednokierunkowej dla klasy Czlowiek" << endl;
			cout << "====================================================" << endl;

			//string human_input_txt = "Humans_input.txt";
			My_forward_list<Czlowiek> lista_czlowiek;
			lista_czlowiek.wczytaj_baze(text_input);
			cout << "Lista wczytana z pliku " << text_input << endl;
			lista_czlowiek.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_back" << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodawane obiekty: " << endl;
			Czlowiek human1("Jan", "Kowalski", "00112234455", 21);
			Czlowiek human2("Jan", "Nowak", "00122334675", 25);
			human1.display();
			cout << endl;
			human2.display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			lista_czlowiek.push_back(human1);
			lista_czlowiek.push_back(human2);
			lista_czlowiek.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_front" << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodawane obiekty:" << endl;
			Czlowiek human3("Andrzej", "Zawada", "10132238459", 90);
			Czlowiek human4("Leszek", "Majzer", "50162399975", 45);
			human3.display();
			cout << endl;
			human4.display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			lista_czlowiek.push_front(human3);
			lista_czlowiek.push_front(human4);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_back()" << endl;
			lista_czlowiek.pop_back();
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_front()" << endl;
			lista_czlowiek.pop_front();
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Rozmiar listy: " << lista_czlowiek.size() << endl;
			cout << "==========================================================================================" << endl;
			int index = 4;
			cout << "Szukanie obiektu o indeksie " << index << ":" << endl;
			cout << "Znaleziono obiekt o wartosci: " << endl;
			lista_czlowiek.find(index)->get_value().display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Usuwanie obiektu o indeksie " << index << ":" << endl;
			lista_czlowiek.erase(4);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg imienia:" << endl;
			lista_czlowiek.sort(0);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg nazwiska:" << endl;
			lista_czlowiek.sort(0, 2);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg PESELu:" << endl;
			lista_czlowiek.sort(0, 3);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg wieku:" << endl;
			lista_czlowiek.sort(0, 4);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg imienia:" << endl;
			lista_czlowiek.sort(1);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg nazwiska:" << endl;
			lista_czlowiek.sort(1, 2);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg PESELu:" << endl;
			lista_czlowiek.sort(1, 3);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg wieku:" << endl;
			lista_czlowiek.sort(1, 4);
			lista_czlowiek.show();

			cout << "==========================================================================================" << endl;
			//string human_output_txt = "Humans_output.txt";
			cout << "Zapisanie zawartosci kontenera do pliku " << text_output << endl;
			ofstream output(text_output);
			lista_czlowiek.show(output);
			output.close();
			cout << "==========================================================================================" << endl;
			//string human_input_bin = "Humans_input.bin";
			cout << "Wczytywanie binarne do kontenera z pliku " << bin_input << endl;

			lista_czlowiek.clear();
			lista_czlowiek.wczytaj_binarnie(bin_input);
			lista_czlowiek.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string human_output_bin = "Humans_output.bin";
			cout << "Zapisanie binarne do pliku " << bin_output << endl;

			lista_czlowiek.zapisz_binarnie(bin_output);

		}
		//Blok SAMOCHOD
		else if (choice == 4)
		{
			cout << "====================================================" << endl;
			cout << "Testowanie listy jednokierunkowej dla klasy Samochod" << endl;
			cout << "====================================================" << endl;
			//string car_input_txt = "Cars_input.txt";
			My_forward_list<Samochod> lista_samochod;
			lista_samochod.wczytaj_baze(text_input);
			cout << "Lista wczytana z pliku " << text_input << endl;
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_back" << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodawane obiekty: " << endl;
			Samochod car1("Subaru", "Impreza", "W0V7D9EB6K4062279", 250000);
			Samochod car2("Renault", "Megane_III", "L1D7C9WB7K5062289", 60000);
			car1.display();
			cout << endl;
			car2.display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			lista_samochod.push_back(car1);
			lista_samochod.push_back(car2);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodanie do listy za pomoca push_front" << endl;
			cout << "==========================================================================================" << endl;
			cout << "Dodawane obiekty:" << endl;
			Samochod car3("Mazda", "RX7", "K2D7C8WH7K5162349", 200000);
			Samochod car4("Volkswagen", "Golf", "U7B7D1WK7K5262369", 120000);
			car3.display();
			cout << endl;
			car4.display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			lista_samochod.push_front(car3);
			lista_samochod.push_front(car4);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_back()" << endl;
			lista_samochod.pop_back();
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Uzycie pop_front()" << endl;
			lista_samochod.pop_front();
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Rozmiar listy: " << lista_samochod.size() << endl;
			cout << "==========================================================================================" << endl;
			int index = 4;
			cout << "Szukanie obiektu o indeksie " << index << ":" << endl;
			cout << "Znaleziono obiekt o wartosci: " << endl;
			lista_samochod.find(index)->get_value().display();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Usuwanie obiektu o indeksie " << index << ":" << endl;
			lista_samochod.erase(4);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg marki:" << endl;
			lista_samochod.sort(0);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg modelu:" << endl;
			lista_samochod.sort(0, 2);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg VINu:" << endl;
			lista_samochod.sort(0, 3);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy rosnaco wg przebiegu:" << endl;
			lista_samochod.sort(0, 4);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg marki:" << endl;
			lista_samochod.sort(1);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg modelu:" << endl;
			lista_samochod.sort(1, 2);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg VINu:" << endl;
			lista_samochod.sort(1, 3);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			cout << "Sortowanie listy malejaco wg przebiegu:" << endl;
			lista_samochod.sort(1, 4);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string car_output_txt = "Cars_output.txt";
			cout << "Zapisanie zawartosci kontenera do pliku " << text_output << endl;
			ofstream output(text_output);
			lista_samochod.show(output);
			output.close();
			cout << "==========================================================================================" << endl;
			//string car_input_bin = "Cars_input.bin";
			cout << "Wczytywanie binarne do kontenera z pliku " << bin_input << endl;

			lista_samochod.clear();
			lista_samochod.wczytaj_binarnie(bin_input);
			lista_samochod.show();
			cout << endl;
			cout << "==========================================================================================" << endl;
			//string car_output_bin = "Cars_output.bin";
			cout << "Zapisanie binarne do pliku " << bin_output << endl;

			lista_samochod.zapisz_binarnie(bin_output);

			cout << endl << endl;
		}
	}

	_CrtDumpMemoryLeaks(); //wykrywanie wycieków pamięci
}


