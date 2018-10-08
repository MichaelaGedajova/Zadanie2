#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iterator>
#include<sstream>
using namespace std;

int VratDlzkuZnaku(string s) {	
	return s.length();
}

int VratPocetSlov(string w) {
	int words = 0;
	if (w.length() == 0) return 0;
	else
	{
		for (int i = 0; i < w.length(); i++)
		{
			if (w[i] == ' ') words++;
		}
		return words + 1;
	}
}

int VratPocetRiadkov(string l) {
	int lines = 0;	
	if (l.length() == 0) return 0;
	else
	{
		for (int i = 0; i < l.length(); i++)
		{
			if (l[i] == '\n') lines++;
		}
		return lines + 1;
	}
}
