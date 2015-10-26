//wypisywanie tekstu

#include "stdafx.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

void modify_settings() {
	ofstream o_settings;
	bool wait = true;
	o_settings.open("settings.txt", std::ios::out | std::ios::trunc);
		cout << "Do you want be able to modify the audio settings when player isn't on top? (Y/N)" << endl;
		if (GetAsyncKeyState('Y'))
			{
				while (GetAsyncKeyState('Y'));
			}
		if (GetAsyncKeyState('N'))
			{
				while (GetAsyncKeyState('N'));
			}
		while(wait)
		{
		if (GetAsyncKeyState('Y'))
			{
				wait = false;
				cout << "Changes saved" << endl;
				o_settings << "true" << endl;
				ustawienia.on_top = true;
				while (GetAsyncKeyState('Y'));
			}
		if (GetAsyncKeyState('N'))
			{
				wait = false;
				cout << "Changes saved" << endl;
				o_settings << "false" << endl;
				ustawienia.on_top = false;
				while (GetAsyncKeyState('N'));
			}
		}
		wait = true;
		cout << "Do you want to shuffle?" << endl;
		while(wait)
		{
		if (GetAsyncKeyState('Y'))
			{
				wait = false;
				cout << "Changes saved" << endl;
				o_settings << "true" << endl;
				ustawienia.shuffle = true;
				while (GetAsyncKeyState('Y'));
			}
		if (GetAsyncKeyState('N'))
			{
				wait = false;
				cout << "Changes saved" << endl;
				o_settings << "false" << endl;
				ustawienia.shuffle = false;
				while (GetAsyncKeyState('N'));
			}
		}
		o_settings.close();
		o_settings.clear();
}

void ftime() {
	string ustawienie;
	ifstream i_settings;
	i_settings.open("settings.txt", std::ios::in);
	if(!i_settings.good())
	{
		i_settings.close();
		modify_settings();
	}
	else
	{
		i_settings >> ustawienie;
		if(ustawienie == "FALSE" || ustawienie == "false")
			ustawienia.on_top = false;
		else if(ustawienie == "TRUE" || ustawienie == "true")
			ustawienia.on_top = true;
		else
		{
			ustawienia.on_top = false;
			cout << "settings.txt is corrupt, default value set: false" << endl
				<< "(you can change the value in settings.txt)" << endl;
		}
		i_settings >> ustawienie;
		if(ustawienie == "FALSE" || ustawienie == "false")
			ustawienia.shuffle = false;
		else if(ustawienie == "TRUE" || ustawienie == "true")
			ustawienia.shuffle = true;
		else
		{
			ustawienia.shuffle = false;
			cout << "settings.txt is corrupt, default value set: false" << endl
				<< "(you can change the value in settings.txt)" << endl;
		}
	}
	i_settings.close();
	i_settings.clear();
}

void manual() {
cout<< "     _     " << endl
    << "|\\/|| || |" << endl
	<< "|  ||-||-|" << endl
	<< "|  || || |" << endl
	<< "      Player - Minimalistic Audio Hardcore Player (Beta Release)" << endl
	<< endl;

cout << "Enable the numlock and use appropriate keys on the numeric keypad:" << endl
	<< "[7]A-B REPEAT    [8]LOUDER    [9]REPEAT" << endl
	<< " [4]PREVIOUS   [5]PAUSE/PLAY   [6]NEXT" << endl
	<< "  [1]ABOUT       [2]SOFTER   [3]SETTINGS" << endl
	<< "  [0]QUIT" << endl
	<< endl;

cout << "Volume (0-100): 50" << endl 
	<< endl;
}

void credits() {
cout << "MAH Player - Minimalistic Audio Hardcore Player (Beta Release)" << endl
	<< "Copyright (C) 2014 Michal \"Deca\" kraft.sc2@gmail.com" << endl
	<< "Useful things used: FMOD Sound System, copyright (C) Firelight Technologies Pty, Ltd., 1994-2013. and the relevant guide on djkaty.com" << endl
	<< endl;
}

void rudimentary(float volume) {
	system("cls");
cout<< "     _     " << endl
    << "|\\/|| || |" << endl
	<< "|  ||-||-|" << endl
	<< "|  || || |" << endl
	<< "      Player - Minimalistic Audio Hardcore Player (Beta Release)" << endl
	<< endl;

cout<< "[7]A-B REPEAT    [8]LOUDER    [9]REPEAT" << endl
	<< " [4]PREVIOUS   [5]PAUSE/PLAY   [6]NEXT" << endl
	<< "  [1]ABOUT       [2]SOFTER   [3]SETTINGS" << endl
	<< "  [0]QUIT" << endl << endl;
	printvolume(volume);
}

