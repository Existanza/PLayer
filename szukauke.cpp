//importowanie muzyki

#include "stdafx.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::queue;

void inicjalizuj_szukanie(){
	bool wczytuj = true;
	string sciezka;
	/*ofstream albums;
	albums.open("albums.txt", std::ios::trunc);
	albums << "";
	albums.close();
	albums.clear();*/
	ifstream i_paths;
	ofstream o_paths;
	i_paths.open("paths.txt");
	if(!i_paths.good())
	{
		i_paths.close();
		i_paths.clear();
		cout << "Give the access paths of your music folders, for example:" << endl
			<< "C:/alex/music/" << endl
			<< "D:/mum/music/" << endl
			<< "write END when you're done" << endl
			<< "(you can always manually modify paths.txt)" << endl;
		while(wczytuj)
		{
			getline(cin, sciezka);
			if(sciezka == "END" || sciezka == "end")
				wczytuj = false;
			o_paths.open("paths.txt", std::ios::app | std::ios::ate);
			o_paths << sciezka << endl;
			o_paths.close();
			o_paths.clear();
		}
	}
	if(!i_paths.is_open())
		i_paths.open("paths.txt");
	sciezka = "aight";
	while(sciezka != "end" && sciezka != "END" && sciezka != "")
	{
		getline(i_paths, sciezka);
		if(sciezka != "end" && sciezka != "END" && sciezka != "")
		{
			foldery.push(sciezka);			
		}
	}
	i_paths.close();
	i_paths.clear();
	if(foldery.empty())
		cout << "No music files found, modify paths.txt" << endl;
	while(!foldery.empty())
	{
		szukaj(foldery.front());
		//albums << foldery.front() << endl << foldery.front() << endl;
		foldery.pop();
	}
}

void szukaj(string start) {

	DIR *sciezka;
	struct dirent *plik;
	struct stat sinfo;
	string full_name;
	string nazwa_pliku;
	//int rozmiar;
	//fstream albums;
	//albums.open("albums.txt", std::ios::app | std::ios::ate);
	bool dodany = false;
	if ((sciezka = opendir(start.c_str())) != NULL) 
	{
		while ((plik = readdir(sciezka)) != NULL) 
		{
			nazwa_pliku = plik->d_name;
			full_name = start + "/" + nazwa_pliku;
			stat (full_name.c_str(), &sinfo);
			if  (((sinfo.st_mode & S_IFREG) == S_IFREG) && !dodany) 
			{
				//rozmiar = sinfo.st_size/1024/1024;	
				//cout << full_name << "  " << rozmiar << " MB" << endl;
				bool a = czy_muzyczny(nazwa_pliku);  //czy dany plik mozna odtworzyc
				if(a)
				{
					//albums << start << endl;
					valbums.push_back(start);
					dodany = true;
				}
			}
			else if (((sinfo.st_mode & S_IFDIR) == S_IFDIR)) 
			{
				if(nazwa_pliku != "." && nazwa_pliku != "..")
				{
					foldery.push(full_name);
					//albums << plik->d_name << endl << full_name << endl;
					//cout << plik->d_name << endl << full_name << endl;
				}
				
			}
		}
		closedir(sciezka);
	}
	else
	{
		cout << "some error " << start << endl;
	}
	//albums.close();
	//albums.clear();

}

bool czy_muzyczny(string start) {
	ifstream formaty;
	int fssize;
	formaty.open("mahpextensions.dll");
	string format = "alright";
	while(format != "end")
	{
		formaty >> format;
		if(format != "end")
		{
			fssize = format.length();
			if(start.compare(start.size()-fssize, fssize, format) == 0)
			{
				formaty.close();
				formaty.clear();
				return true;
			}
		}
	}
	formaty.close();
	formaty.clear();
	return false;
}

int stworz_playliste(string sciezka_albumu) {
	int wynik = 0;
	DIR *sciezka;
	struct dirent *plik;
	struct stat sinfo;
	string nazwa_pliku;
	string pelna_nazwa;

	if ((sciezka = opendir(sciezka_albumu.c_str())) != NULL) 
	{
		while ((plik = readdir(sciezka)) != NULL) 
		{
			nazwa_pliku = plik->d_name;
			pelna_nazwa = sciezka_albumu + "/" + nazwa_pliku;
			stat (pelna_nazwa.c_str(), &sinfo);
			if ((sinfo.st_mode & S_IFREG) == S_IFREG) 
			{
				bool a = czy_muzyczny(nazwa_pliku);
				if(a)
				{
					wektor.push_back(nazwa_pliku);
					wynik += 1;
				}
			}
		}
	}
	return wynik;
}