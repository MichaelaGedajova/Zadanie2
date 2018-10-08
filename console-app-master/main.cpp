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

		if ("-c" == (string)argv[argc - 1])
		{
			cout << "Pocitanie znakov z klavesnice" << endl;
			string s;
			getline(cin, s);
			cout << "Pocet vasich znakov: " << VratDlzkuZnaku(s)<< endl;
		}
		
		if ("-w" == (string)argv[argc - 1])
		{
			string w;
			cout << "Pocitanie slov z klavesnice\n" << endl;
			getline(cin, w);
			cout << VratPocetSlov(w) << endl;
		}

		if ("-l" == (string)argv[argc - 1])
		{
			string l;
			cout << "Pocitanie riadkov z klavesnice\n" << endl;
			cout << "Zadajte: stop pre ukoncenie pocitania riadkov\n" << endl;
			getline(cin, l);
			cout<< VratPocetRiadkov(l)<< endl;
		}
	}
	return 0;
}
