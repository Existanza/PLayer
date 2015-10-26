// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <cstdio>
//#include <tchar.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <conio.h>
//#include <unistd.h> // brak pliku

struct settings{
	bool on_top;
	bool shuffle;
};

extern settings ustawienia;

extern std::queue<std::string> foldery;

extern std::vector<std::string> valbums;

extern std::vector<std::string> wektor;

//odt1.cpp
void fshuffle(int liczba_utworow);
void printvolume(float volume);
void lista(int i, int liczba_utworow);

//manual.cpp
void modify_settings(); //modify settings
void ftime(); //first-time configuration
void manual(); //wypisyswanie tekstu przy uruchomieniu
void credits(); //wypisywanie tekstu o prorgamie
void rudimentary(float volume);

//szukauke.cpp
void inicjalizuj_szukanie(); //importowanie muzyki
void szukaj(std::string sciezka);
bool czy_muzyczny(std::string nazwa);
int stworz_playliste(std::string sciezka_albumu);

// TODO: reference additional headers your program requires here
