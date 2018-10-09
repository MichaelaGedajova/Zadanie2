#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iterator>
#include<sstream>
using namespace std;

template <typename T>
size_t spocitaj(string str) {
	T obj(str);
	return obj.spocitaj();
	}

struct _char:public string{
	_char(string str) : string(str) {};
	 size_t spocitaj() {
		return size();
	}
};

struct _word:public string { 
	_word(string str) : string(str) {};
	 size_t spocitaj() {
		int words = 0;			
		for (int i = 0; i < length(); i++)
		{
			if (at(i) == ' ') words++;
		}
		return words+1;		
	}
};

struct _line:public string {
	_line(string str) : string(str) {};
	 size_t spocitaj() {
		int lines = 0;
		
			for (int i = 0; i < length(); i++)
			{
				if (at(i) == '\n') lines++;
			}
			return lines + 1;		
	}
};

/*
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
			if (l[i] == '/n') lines++;
		}
		return lines + 1;
	}	
}*/
