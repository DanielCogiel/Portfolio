#include <iostream>
#include <fstream>
#include <sstream>
#include <crtdbg.h>

using namespace std;

#ifndef LISTA_H
#define LISTA_H

/**Szablon klasy reprezentuj¹cej element listy.*/
template<class T>
class List_element
{
	T value;
	shared_ptr<List_element<T>> pNext;
public:
	List_element(T x = 0) : value(x), pNext(nullptr) {}
	~List_element() {}

	/**Metoda zwracaj¹ca wartoœæ elementu.
	* @return Wartoœæ elementu
	*/
	T get_value();
	/**Metoda ustawiaj¹ca wartoœæ elementu.
	* @param x Nowa wartoœæ
	*/
	void set_value(T x);
	/**Metoda zwracaj¹ca wskaŸnik na nastêpny element.
	* @return WskaŸnik na nastêpny element
	*/
	shared_ptr<List_element<T>> get_next();
	/**Metoda ustawiaj¹ca wskaŸnik na nastêpny element.
	* @param new_next Nowy wskaŸnik na nastêpny element
	*/
	void set_next(shared_ptr<List_element<T>> new_next);
};
/**Szablon klasy reprezentuj¹cej listê jednokierunkow¹.*/
template<class T>
class My_forward_list
{
	shared_ptr<List_element<T>> head, tail;
public:
	My_forward_list() : head(nullptr), tail(nullptr) {}
	My_forward_list(const My_forward_list& to_copy) : head(to_copy.head), tail(to_copy.tail) {}
	My_forward_list(const My_forward_list&& to_move) : head(to_move.head), tail(to_move.tail) {}
	~My_forward_list() {}

	My_forward_list& operator=(const My_forward_list& lista);
	My_forward_list& operator=(My_forward_list&& lista);

	/**Metoda dodaj¹ca element na pocz¹tek listy.
	* @param x Dodawany element
	*/
	void push_front(T x);
	/**Metoda dodaj¹ca element na koniec listy.
	* @param x Dodawany element
	*/
	void push_back(T x);
	/**Metoda usuwaj¹ca element z pocz¹tku listy.*/
	void pop_front();
	/**Metoda usuwaj¹ca element z koñca listy.*/
	void pop_back();
	/**Metoda wyœwietlaj¹ca zawartoœæ listy.
	* @param output Strumieñ wyjœciowy
	*/
	void show(ostream& output = cout);
	/**Metoda zwracaj¹ca rozmiar listy.
	* @return Rozmiar listy
	*/
	int size();
	/**Metoda usuwaj¹ca element z danej pozycji. Generuje stosowny komunikat, jeœli element jest poza zakresem.
	* @param pos Indeks elementu do usuniêcia
	*/
	void erase(int pos);
	/**Metoda znajduj¹ca element na podanej pozycji.
	* @param pos Indeks elementu do znalezienia
	* @return WskaŸnik na szukany element b¹dŸ nullptr
	*/
	shared_ptr<List_element<T>> find(int pos);
	/**Metoda znajduj¹ca indeks podanego elementu.
	* @param elem WskaŸnik na szukany element
	* @return Indeks szukanego elementu
	*/
	int search_index(shared_ptr<List_element<T>> elem);
	/**Metoda zwracaj¹ca wartoœæ TRUE, jeœli lista jest pusta.
	* @return Czy lista jest pusta?
	*/
	bool is_empty();
	/**Metoda sortuj¹ca listê wed³ug podanego kryterium.
	* @param choice Jeœli 0, sortuje rosn¹co, w przeciwnym wypadku malej¹co
	* @param criteria Kryterium sortowania (dla klasy Czlowiek i Samochod)
	*/
	void sort(bool choice, int criteria = 1);
	/**Metoda wczytuj¹ca zawartoœæ listy z podanego pliku binarnego.
	* @param name Nazwa pliku binarnego
	*/
	void wczytaj_binarnie(string name);
	/**Metoda zapisuj¹ca zawartoœæ listy do pliku binarnego.
	* @param name Nazwa pliku binarnego
	*/
	void zapisz_binarnie(string name);
	/**Metoda wczytuj¹ca zawartoœæ listy z podanego pliku.
	* @param Nazwa pliku
	*/
	void wczytaj_baze(string name);
	/**Metoda czyszcz¹ca listê.*/
	void clear();
};

template<class T>
T List_element<T>::get_value()
{
	return this->value;
}

template<class T>
void List_element<T>::set_value(T x)
{
	this->value = x;
}

template<class T>
shared_ptr<List_element<T>> List_element<T>::get_next()
{
	return this->pNext;
}

template<class T>
void List_element<T>::set_next(shared_ptr<List_element<T>> new_next)
{
	this->pNext = new_next;
}

template<class T>
My_forward_list<T>& My_forward_list<T>::operator=(const My_forward_list& lista)
{
	if (this == &lista)
		return *this;
	head = lista.head;
	tail = lista.tail;
	return *this;
}

template<class T>
My_forward_list<T>& My_forward_list<T>::operator=(My_forward_list&& lista)
{
	head = lista.head;
	tail = lista.tail;
	return *this;
}

template<class T>
void My_forward_list<T>::push_front(T x)
{
	shared_ptr<List_element<T>> new_head = make_shared<List_element<T>>(x);

	if (this->head == nullptr)
	{
		head = new_head;
		tail = new_head;
	}
	else
	{
		new_head->set_next(this->head);
		this->head = new_head;
	}
}

template<class T>
void My_forward_list<T>::push_back(T x)
{
	shared_ptr<List_element<T>> new_tail = make_shared<List_element<T>>(x);

	if (this->tail)
		this->tail->set_next(new_tail);
	if (!this->head)
		this->head = new_tail;
	this->tail = new_tail;
}

template<class T>
void My_forward_list<T>::pop_front()
{
	this->head = this->head->get_next();
}

template<class T>
void My_forward_list<T>::pop_back()
{
	shared_ptr<List_element<T>> tmp = this->head;

	while (tmp->get_next() != tail)
		tmp = tmp->get_next();
	tmp->set_next(nullptr);
	this->tail = tmp;
}

template<class T>
void My_forward_list<T>::show(ostream& output)
{
	shared_ptr<List_element<T>> tmp = this->head;
	while (tmp)
	{
		output << tmp->get_value() << " ";
		tmp = tmp->get_next();
	}
}

void My_forward_list<Czlowiek>::show(ostream& output)
{
	shared_ptr<List_element<Czlowiek>> tmp = this->head;
	while (tmp)
	{
		(tmp->get_value()).display(output);
		output << endl;
		tmp = tmp->get_next();
	}
}

void My_forward_list<Samochod>::show(ostream& output)
{
	shared_ptr<List_element<Samochod>> tmp = this->head;
	while (tmp)
	{
		(tmp->get_value()).display(output);
		output << endl;
		tmp = tmp->get_next();
	}
}

template<class T>
int My_forward_list<T>::size()
{
	shared_ptr<List_element<T>> tmp = this->head;
	int licznik = 0;
	while (tmp)
	{
		licznik++;
		tmp = tmp->get_next();
	}
	return licznik;
}

template<class T>
void My_forward_list<T>::erase(int pos)
{
	if (pos < 0 or pos >= this->size())
	{
		cout << "Lista - element poza zakresem." << endl;
		return;
	}
	if (!pos)
	{
		this->pop_front();
		return;
	}
	shared_ptr<List_element<T>> tmp = this->head;
	if (pos == (this->size()) - 1)
	{
		this->pop_back();
		return;
	}
	while (tmp->get_next())
	{
		--pos;
		if (!pos)
		{
			tmp->set_next(tmp->get_next()->get_next());
		}

		tmp = tmp->get_next();
	}

}

template<class T>
shared_ptr<List_element<T>> My_forward_list<T>::find(int pos)
{
	if (pos < 0 or pos >= this->size())
	{
		cout << "Lista - element poza zakresem." << endl;
		return nullptr;
	}
	if (!pos)
		return this->head;
	if (pos == (this->size()) - 1)
		return this->tail;

	shared_ptr<List_element<T>> tmp = this->head;
	while (tmp and pos)
	{
		pos--;
		tmp = tmp->get_next();
	}
	return tmp;

}

template<class T>
int My_forward_list<T>::search_index(shared_ptr<List_element<T>> elem)
{
	int licznik = 0;
	shared_ptr<List_element<T>> tmp = this->head;
	while (tmp)
	{
		if (tmp == elem)
			return licznik;
		licznik++;
		tmp = tmp->get_next();
	}
	return 0;
}

template<class T>
bool My_forward_list<T>::is_empty()
{
	if (head == nullptr)
		return 1;
	else
		return 0;
}

template<class T>
void My_forward_list<T>::sort(bool choice, int criteria)
{

	T min = head->get_value();
	T max = head->get_value();
	shared_ptr<List_element<T>> el_max = head;
	shared_ptr<List_element<T>> el_min = head;
	shared_ptr<List_element<T>> tmp = this->head;
	int rozmiar = size();

	if (choice)
	{
		int licznik = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			tmp = find(licznik);
			min = tmp->get_value();
			el_min = tmp;
			while (tmp)
			{
				if (tmp->get_value() < min)
				{
					min = tmp->get_value();
					el_min = tmp;
				}
				tmp = tmp->get_next();
			}

			licznik++;
			if (!is_empty())
				erase(search_index(el_min));
			push_front(min);
		}

	}
	else
	{
		int licznik = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			tmp = find(licznik);
			max = tmp->get_value();
			el_max = tmp;
			while (tmp)
			{
				if (tmp->get_value() > max)
				{
					max = tmp->get_value();
					el_max = tmp;
				}
				tmp = tmp->get_next();
			}

			licznik++;
			if (!is_empty())
				erase(search_index(el_max));
			push_front(max);
		}
	}
}

void My_forward_list<Czlowiek>::sort(bool choice, int criteria)
{



	if (criteria == 1)
	{
		string min = (head->get_value()).imie;
		string max = (head->get_value()).imie;
		shared_ptr<List_element<Czlowiek>> el_max = head;
		shared_ptr<List_element<Czlowiek>> el_min = head;
		shared_ptr<List_element<Czlowiek>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().imie);
				el_min = tmp;
				while (tmp)
				{


					if ((tmp->get_value()).imie < min)
					{
						min = (tmp->get_value()).imie;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_min->get_value().imie, el_min->get_value().nazwisko, el_min->get_value().PESEL, el_min->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_human);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().imie);
				el_max = tmp;
				while (tmp)
				{


					if ((tmp->get_value()).imie > max)
					{
						max = (tmp->get_value()).imie;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_max->get_value().imie, el_max->get_value().nazwisko, el_max->get_value().PESEL, el_max->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_human);
			}
		}
	}
	else if (criteria == 2)
	{
		string min = (head->get_value()).nazwisko;
		string max = (head->get_value()).nazwisko;
		shared_ptr<List_element<Czlowiek>> el_max = head;
		shared_ptr<List_element<Czlowiek>> el_min = head;
		shared_ptr<List_element<Czlowiek>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().nazwisko);
				el_min = tmp;
				while (tmp)
				{


					if ((tmp->get_value()).nazwisko < min)
					{
						min = (tmp->get_value()).nazwisko;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_min->get_value().imie, el_min->get_value().nazwisko, el_min->get_value().PESEL, el_min->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_human);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().nazwisko);
				el_max = tmp;
				while (tmp)
				{
					if ((tmp->get_value()).nazwisko > max)
					{
						max = (tmp->get_value()).nazwisko;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_max->get_value().imie, el_max->get_value().nazwisko, el_max->get_value().PESEL, el_max->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_human);
			}
		}
	}
	else if (criteria == 3)
	{
		string min = (head->get_value()).PESEL;
		string max = (head->get_value()).PESEL;
		shared_ptr<List_element<Czlowiek>> el_max = head;
		shared_ptr<List_element<Czlowiek>> el_min = head;
		shared_ptr<List_element<Czlowiek>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().PESEL);
				el_min = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).PESEL < min)
					{
						min = (tmp->get_value()).PESEL;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_min->get_value().imie, el_min->get_value().nazwisko, el_min->get_value().PESEL, el_min->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_human);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().PESEL);
				el_max = tmp;
				while (tmp)
				{
					if ((tmp->get_value()).PESEL > max)
					{
						max = (tmp->get_value()).PESEL;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_max->get_value().imie, el_max->get_value().nazwisko, el_max->get_value().PESEL, el_max->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_human);
			}
		}
	}
	else
	{
		int min = (head->get_value()).wiek;
		int max = (head->get_value()).wiek;
		shared_ptr<List_element<Czlowiek>> el_max = head;
		shared_ptr<List_element<Czlowiek>> el_min = head;
		shared_ptr<List_element<Czlowiek>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().wiek);
				el_min = tmp;
				while (tmp)
				{
					if ((tmp->get_value()).wiek < min)
					{
						min = (tmp->get_value()).wiek;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_min->get_value().imie, el_min->get_value().nazwisko, el_min->get_value().PESEL, el_min->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_human);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().wiek);
				el_max = tmp;
				while (tmp)
				{
					if ((tmp->get_value()).wiek > max)
					{
						max = (tmp->get_value()).wiek;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Czlowiek new_human(el_max->get_value().imie, el_max->get_value().nazwisko, el_max->get_value().PESEL, el_max->get_value().wiek);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_human);
			}
		}
	}
}

void My_forward_list<Samochod>::sort(bool choice, int criteria)
{
	if (criteria == 1)
	{
		string min = (head->get_value()).marka;
		string max = (head->get_value()).marka;
		shared_ptr<List_element<Samochod>> el_max = head;
		shared_ptr<List_element<Samochod>> el_min = head;
		shared_ptr<List_element<Samochod>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().marka);
				el_min = tmp;
				while (tmp)
				{


					if ((tmp->get_value()).marka < min)
					{
						min = (tmp->get_value()).marka;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_min->get_value().marka, el_min->get_value().model, el_min->get_value().VIN, el_min->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_car);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().marka);
				el_max = tmp;
				while (tmp)
				{


					if ((tmp->get_value()).marka > max)
					{
						max = (tmp->get_value()).marka;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_max->get_value().marka, el_max->get_value().model, el_max->get_value().VIN, el_max->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_car);
			}
		}
	}
	else if (criteria == 2)
	{
		string min = (head->get_value()).model;
		string max = (head->get_value()).model;
		shared_ptr<List_element<Samochod>> el_max = head;
		shared_ptr<List_element<Samochod>> el_min = head;
		shared_ptr<List_element<Samochod>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().model);
				el_min = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).model < min)
					{
						min = (tmp->get_value()).model;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_min->get_value().marka, el_min->get_value().model, el_min->get_value().VIN, el_min->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_car);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().model);
				el_max = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).model > max)
					{
						max = (tmp->get_value()).model;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_max->get_value().marka, el_max->get_value().model, el_max->get_value().VIN, el_max->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_car);
			}
		}
	}
	else if (criteria == 3)
	{
		string min = (head->get_value()).VIN;
		string max = (head->get_value()).VIN;
		shared_ptr<List_element<Samochod>> el_max = head;
		shared_ptr<List_element<Samochod>> el_min = head;
		shared_ptr<List_element<Samochod>> tmp = this->head;
		int rozmiar = size();

		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().VIN);
				el_min = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).VIN < min)
					{
						min = (tmp->get_value()).VIN;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_min->get_value().marka, el_min->get_value().model, el_min->get_value().VIN, el_min->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_car);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().VIN);
				el_max = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).VIN > max)
					{
						max = (tmp->get_value()).VIN;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_max->get_value().marka, el_max->get_value().model, el_max->get_value().VIN, el_max->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_car);
			}
		}
	}
	else
	{
		int min = (head->get_value()).przebieg;
		int max = (head->get_value()).przebieg;
		shared_ptr<List_element<Samochod>> el_max = head;
		shared_ptr<List_element<Samochod>> el_min = head;
		shared_ptr<List_element<Samochod>> tmp = this->head;
		int rozmiar = size();
		if (choice)
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				min = (tmp->get_value().przebieg);
				el_min = tmp;
				while (tmp)
				{

					if ((tmp->get_value()).przebieg < min)
					{
						min = (tmp->get_value()).przebieg;
						el_min = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_min->get_value().marka, el_min->get_value().model, el_min->get_value().VIN, el_min->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_min));
				push_front(new_car);
			}

		}
		else
		{
			int licznik = 0;
			for (int i = 0; i < rozmiar; i++)
			{
				tmp = find(licznik);
				max = (tmp->get_value().przebieg);
				el_max = tmp;
				while (tmp)
				{
					if ((tmp->get_value()).przebieg > max)
					{
						max = (tmp->get_value()).przebieg;
						el_max = tmp;
					}
					tmp = tmp->get_next();
				}

				licznik++;
				Samochod new_car(el_max->get_value().marka, el_max->get_value().model, el_max->get_value().VIN, el_max->get_value().przebieg);
				if (!is_empty())
					erase(search_index(el_max));
				push_front(new_car);
			}
		}
	}
}

template<class T>
void My_forward_list<T>::wczytaj_binarnie(string name)
{
	ifstream input(name, ios::binary);
	if (input.good())
	{
		while (!input.eof())
		{
			T x;
			input.read((char*)&x, sizeof(x));
			this->push_back(x);
		}
		input.close();
	}
}

void My_forward_list<string>::wczytaj_binarnie(string name)
{

	ifstream input(name, ios::binary);
	if (input.good())
	{
		while (!input.eof())
		{

			string tekst;
			getline(input, tekst, '\0');
			stringstream ss;
			ss << tekst;
			while (ss >> tekst)
				this->push_back(tekst);

		}
		input.close();

	}
}

void My_forward_list<Czlowiek>::wczytaj_binarnie(string name)
{
	ifstream input(name, ios::binary);
	if (input.good())
	{
		while (!input.eof())
		{

			string tekst;
			string _imie, _nazwisko, _PESEL;
			int _wiek;
			getline(input, tekst, '\0');
			stringstream ss;
			ss << tekst;
			while (ss >> _imie >> _nazwisko >> _PESEL >> _wiek)
			{
				Czlowiek new_human(_imie, _nazwisko, _PESEL, _wiek);
				this->push_back(new_human);
			}
		}
		input.close();

	}
}

void My_forward_list<Samochod>::wczytaj_binarnie(string name)
{
	ifstream input(name, ios::binary);
	if (input.good())
	{
		while (!input.eof())
		{

			string tekst;
			string _marka, _model, _VIN;
			int _przebieg;
			getline(input, tekst, '\0');
			stringstream ss;
			ss << tekst;
			while (ss >> _marka >> _model >> _VIN >> _przebieg)
			{
				Samochod new_car(_marka, _model, _VIN, _przebieg);
				this->push_back(new_car);
			}
		}
		input.close();

	}
}

template<class T>
void My_forward_list<T>::zapisz_binarnie(string name)
{
	ofstream output(name);
	if (output.good())
	{
		shared_ptr<List_element<T>> tmp = this->head;
		while (tmp)
		{
			T x = tmp->get_value();
			output.write((const char*)&x, sizeof(x));

			tmp = tmp->get_next();
		}
		output.close();
	}
}

void My_forward_list<string>::zapisz_binarnie(string name)
{
	ofstream output(name);
	if (output.good())
	{
		shared_ptr<List_element<string>> tmp = this->head;
		while (tmp)
		{
			string tekst = tmp->get_value();
			output.write(tekst.c_str(), tekst.size() + 1);
			output << endl;
			tmp = tmp->get_next();
		}
		output.close();
	}
}

void My_forward_list<Czlowiek>::zapisz_binarnie(string name)
{
	ofstream output(name);
	if (output.good())
	{
		shared_ptr<List_element<Czlowiek>> tmp = this->head;
		while (tmp)
		{
			string _imie = tmp->get_value().imie;
			string _nazwisko = tmp->get_value().nazwisko;
			string _PESEL = tmp->get_value().PESEL;
			int _wiek = tmp->get_value().wiek;
			stringstream ss;
			ss << _wiek;
			string wiek_str = ss.str();
			output.write(_imie.c_str(), _imie.size() + 1);
			output.write(_nazwisko.c_str(), _nazwisko.size() + 1);
			output.write(_PESEL.c_str(), _PESEL.size() + 1);
			output.write(wiek_str.c_str(), wiek_str.size() + 1);
			output << endl;
			tmp = tmp->get_next();
		}
		output.close();
	}
}

void My_forward_list<Samochod>::zapisz_binarnie(string name)
{
	ofstream output(name);
	if (output.good())
	{
		shared_ptr<List_element<Samochod>> tmp = this->head;
		while (tmp)
		{
			string _marka = tmp->get_value().marka;
			string _model = tmp->get_value().model;
			string _VIN = tmp->get_value().VIN;
			int _przebieg = tmp->get_value().przebieg;
			stringstream ss;
			ss << _przebieg;
			string przebieg_str = ss.str();
			output.write(_marka.c_str(), _marka.size() + 1);
			output.write(_model.c_str(), _model.size() + 1);
			output.write(_VIN.c_str(), _VIN.size() + 1);
			output.write(przebieg_str.c_str(), przebieg_str.size() + 1);
			output << endl;
			tmp = tmp->get_next();
		}
		output.close();
	}
}

template<class T>
void My_forward_list<T>::wczytaj_baze(string name)
{
	ifstream input(name);
	if (input.good())
	{
		T value;
		while (input >> value)
			this->push_back(value);
		input.close();
	}
}

void My_forward_list<Czlowiek>::wczytaj_baze(string name)
{
	ifstream input(name);
	if (input.good())
	{
		Czlowiek human;
		while (!input.eof())
		{
			human.wczytaj_z_pliku(input);
			push_back(human);
		}
		input.close();
	}
}

void My_forward_list<Samochod>::wczytaj_baze(string name)
{
	ifstream input(name);
	if (input.good())
	{
		Samochod car;
		while (!input.eof())
		{
			car.wczytaj_z_pliku(input);
			push_back(car);
		}
		input.close();
	}
}

template<class T>
void My_forward_list<T>::clear()
{
	this->head = nullptr;
	this->tail = nullptr;
}

#endif 
