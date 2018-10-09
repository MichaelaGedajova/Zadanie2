// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iterator>
#include<sstream>
#include "counter.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) return 0;
	if (argc == 2) {

		string nazov_suboru, riadky, *text = new string[20];
		cout << "Zadaj nazov suboru (bez .txt): \n";
		getline(cin, nazov_suboru);
		nazov_suboru = nazov_suboru + ".txt";
		fstream subor(nazov_suboru.c_str(), fstream::in);

		if ("-c" == (string)argv[argc - 1])
		{
			if (subor.is_open())
			{
				cout << "Pocitanie znakov zo suboru\n" << endl;
				getline(subor, riadky);					
				cout << "Pocet vasich znakov: " << spocitaj<_char>(riadky) << endl;
			}
			else
			{
				cout << "Pocitanie znakov z klavesnice" << endl;
				string s;
				getline(cin, s);
				cout << "Pocet vasich znakov: " << spocitaj<_char>(s) << endl;
			}
		}
		
		if ("-w" == (string)argv[argc - 1])
		{
			if (subor.is_open())
			{
				cout << "Pocitanie slov zo suboru\n" << endl;
				getline(subor, riadky);
				cout << "Pocet vasich slov: " << spocitaj<_word>(riadky) << endl;
			}
			else
			{
				string w;
				cout << "Pocitanie slov z klavesnice\n" << endl;
				getline(cin, w);
				cout << spocitaj<_word>(w) << endl;
			}
		}

		if ("-l" == (string)argv[argc - 1])
		{
			if (subor.is_open())
			{
				cout << "Pocitanie riadkov zo suboru\n" << endl;
				getline(subor, riadky);
				cout << "Pocet vasich riadkov: " << spocitaj<_line>(riadky) << endl;
			}
			else
			{
				string l;
				cout << "Pocitanie riadkov z klavesnice\n" << endl;
				cout << "Zadajte: stop pre ukoncenie pocitania riadkov\n" << endl;
				getline(cin, l);
				cout << spocitaj<_line>(l) << endl;
			}
		}
		subor.close();
		delete[] text;
	}
	return 0;
}
