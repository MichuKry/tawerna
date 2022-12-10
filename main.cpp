#include "tawerna.h"
#include <iostream>
#include <fstream>

vector<Danie> wszystkieDania;
Zamowienie zamowienie;

void zamowDanie(Danie danie)
{
	
	Pozycja *znaleziona = NULL;
	for (auto& pozycja : zamowienie.pozycje)
	{
		if (pozycja.danie.nazwa == danie.nazwa)
			znaleziona = &pozycja;
	}
	if (znaleziona == NULL) 
	{
		Pozycja pozycja(danie, 1);
		zamowienie.pozycje.emplace_back(pozycja);
		return;
	}
	znaleziona->ilosc+=1;
}
void usunDanie(Danie danie)
{
	Pozycja* znaleziona = NULL;
	size_t poz = 0;
	for (auto& pozycja : zamowienie.pozycje)
	{
		if (pozycja.danie.nazwa == danie.nazwa)
			{
				znaleziona = &pozycja;
				break;
			}
		poz++;
	}
	if (znaleziona == NULL)
		return;
	if (znaleziona->ilosc == 1)
		{
			zamowienie.pozycje.erase(zamowienie.pozycje.begin() + poz);
			return;
		}
	znaleziona->ilosc -= 1;
}
/*void najdluzszyCzas(Danie danie)
{
	int najCzas = 0;
	for (auto& pozycja : zamowienie.pozycje)
	{
		if (najCzas < pozycja.danie.czasWykonaniaMin)
			najCzas = pozycja.danie.czasWykonaniaMin;
	}
}
*/

vector<Danie> wczytajDaniazPliku(string sciezka)
{
	vector<Danie> dania;
	ifstream file;
	file.open(sciezka, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			int kategoria = 0;
			string nazwa;
			int cena = 0;
			int czasPodania = 0;
			vector <string> skladniki;

			string temp = "";
			int it = 0;

			for (it; it < line.length(); it++)
			{

				if (line[it] == ';')
				{
					kategoria = stoi(temp);
					temp = " ";
					it++;
					break;
				}
				temp += line[it];
			}
			for (it; it < line.length(); it++)
			{

				if (line[it] == ';')
				{
					nazwa = temp;
					temp = " ";
					it++;
					break;
				}
				temp += line[it];
			}

			for (it; it < line.length(); it++)
			{
				if (line[it] == ';')
				{
					cena = stoi(temp);
					temp = " ";
					it++;
					break;
				}
				temp += line[it];
			}

			for (it; it < line.length(); it++)
			{
				if (line[it] == ';')
				{
					czasPodania = stoi(temp);
					temp = " ";
					it++;
					break;
				}
				temp += line[it];
			}

			for (it; it < line.length(); it++)
			{
				if (line[it] == ',')
				{
					skladniki.push_back(temp);
					temp = " ";
					it++;
				}
				temp += line[it];
			}
			skladniki.push_back(temp);

			Danie danie(kategoria, nazwa, cena, czasPodania);
			danie.skladniki = skladniki;
			dania.push_back(danie);
		}
		file.close();
	}
	else
	{
		std::cout << "Blad odczytu pliku\n";
	}


	return dania;
}

int main() {
	/* wszystkieDania = {
			 Danie("Kebs", 25, 15),
			 Danie("Onion Orbits", 12, 10),
			 Danie("Tatar awatar", 17, 10)
	 };*/

	wszystkieDania = wczytajDaniazPliku("karta_dan.csv");
	



	//zamowienie.numer = 2137;
	//zamowienie.pozycje.emplace_back(wszystkieDania[0], 1);
	//zamowienie.pozycje.emplace_back(wszystkieDania[1], 2);
	
	wypisz(wszystkieDania);
	wypisz(zamowienie);
	std::cout << "czas zamowienia: " << zamowienie.czasZamowienia() << "\n";
	std::cout << "koszt zamowiena: " << zamowienie.zliczKoszt() << "\n";
	return 0;
}