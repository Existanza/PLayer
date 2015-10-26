// odt1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _USE_MATH_DEFINES

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

settings ustawienia;
std::queue<string> foldery;
vector<string> valbums;

void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << endl;
        exit(-1);
    }
}

vector<string> wektor;

void fshuffle(int liczba_utworow) {			//everyday we're shuffling
    for(int i=0 ; i<liczba_utworow ; i++)
    {
        int r = rand()%liczba_utworow;
        swap(wektor[i], wektor[r]);
    }
}

void printvolume(float volume) {
	cout.setf(std::ios::fixed);
	std::streamsize p = cout.precision();
	cout.precision(0);
	cout << "Volume: " << volume << endl << endl;
	cout.unsetf(std::ios::fixed);
	cout.precision(p);
}

void lista(int i, int liczba_utworow) {
	for(int j=max(0, i-3) ; j<min(liczba_utworow, i+5) ; j++)
		{
			if(i!=j)
				cout << wektor[j] << endl;
			else
				cout << endl << "    " << wektor[j] << endl << endl;
		}
}

int main() {

srand ( (unsigned int)time(NULL) );

std::ios_base::sync_with_stdio(0);

clock_t start_timer;
start_timer = clock();

// ================================================================================================
// Application-independent initialization
// ================================================================================================


    FMOD::System *system;
    FMOD_RESULT result;
    unsigned int version;
    int numDrivers;
    FMOD_SPEAKERMODE speakerMode;
    FMOD_CAPS caps;
    char name[256];

    // Create FMOD interface object
    result = FMOD::System_Create(&system);
    FMODErrorCheck(result);

    // Check version
    result = system->getVersion(&version);
    FMODErrorCheck(result);

    if (version < FMOD_VERSION)
    {
        cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << endl;
        return 0;
    }

    // Get number of sound cards
    result = system->getNumDrivers(&numDrivers);
    FMODErrorCheck(result);

    // No sound cards (disable sound)
    if (numDrivers == 0)
    {
        result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        FMODErrorCheck(result);
    }

    // At least one sound card
    else
    {
        // Get the capabilities of the default (0) sound card
        result = system->getDriverCaps(0, &caps, 0, &speakerMode);
        FMODErrorCheck(result);

        // Set the speaker mode to match that in Control Panel
        result = system->setSpeakerMode(speakerMode);
        FMODErrorCheck(result);

        // Increase buffer size if user has Acceleration slider set to off
        if (caps & FMOD_CAPS_HARDWARE_EMULATED)
        {
            result = system->setDSPBufferSize(1024, 10);
            FMODErrorCheck(result);
        }

        // Get name of driver
        result = system->getDriverInfo(0, name, 256, 0);
        FMODErrorCheck(result);

        // SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
        // PCM floating point output seems to solve it.
        if (strstr(name, "SigmaTel"))
        {
            result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
            FMODErrorCheck(result);
        }
    }

    // Initialise FMOD
    result = system->init(100, FMOD_INIT_NORMAL, 0);

    // If the selected speaker mode isn't supported by this sound card, switch it back to stereo
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
    {
        result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        FMODErrorCheck(result);

        result = system->init(100, FMOD_INIT_NORMAL, 0);
    }
    FMODErrorCheck(result);

// ================================================================================================
// End of the stupid part
// ================================================================================================

ftime();

manual();

inicjalizuj_szukanie();

double seconds;
clock_t end_timer;

		end_timer = clock();
		seconds = ((double)end_timer - start_timer)/CLOCKS_PER_SEC;
		cout << "Application starting time: ";
		cout.precision(2);
		cout << seconds;
		cout << " seconds." << endl << endl;

while(true)
{
	float i_loudness = 50;
	float f_loudness = i_loudness / 100;
	
	bool isPaused;
	bool ready = true;

	int i, j;
	int key = 0;
	int numer_albumu;
	int liczba_utworow;
	
	cout << "Pick the album:" << endl;
	for(i=1 ; i <= valbums.size() ; i++)
	{
		cout << i << ": " << valbums[i-1] << endl;
	}
	cin >> numer_albumu;
	if(numer_albumu>valbums.size())
	{
		cout << "Error, the number is incorrect" << endl;
		return 0;
	}

	string nazwa;
	string sciezka_albumu = valbums[numer_albumu-1];
	cout << sciezka_albumu << endl;
	string sciezka_piosenki;
	
	liczba_utworow = stworz_playliste(sciezka_albumu);
	
	if(ustawienia.shuffle)
		fshuffle(liczba_utworow);

    for(i=0 ; i<liczba_utworow ; i++)
    {
		rudimentary(i_loudness);
		nazwa = wektor[i];

		/*if(i>0)
		{
			cout << wektor[i-1] << endl << endl;
		}
		else
		{
			cout << "<<First track of album" << ">>" << endl << endl;
		}
        cout << "    " << nazwa << endl << endl;
		if(i+1<liczba_utworow)
		{
			cout << wektor[i+1] << endl << endl;
		}
		else
		{
			cout << "<<Last track of album" << ">>" << endl << endl;
		}*/
		
		lista(i, liczba_utworow);
		
		sciezka_piosenki = sciezka_albumu + "/" + nazwa;
        FMOD::Sound *audioStream;
        system->createStream(sciezka_piosenki.c_str(), FMOD_DEFAULT, 0, &audioStream);
			FMODErrorCheck(result);
		FMOD::Channel *channel;
		system->playSound(FMOD_CHANNEL_FREE, audioStream, false, &channel);
			FMODErrorCheck(result);
		channel->setVolume(f_loudness);
			FMODErrorCheck(result);
		bool isPlayin;
		while (channel->isPlaying(&isPlayin) == FMOD_OK && isPlayin) {			
			FMODErrorCheck(system->update());
		if(ustawienia.on_top)
		{
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				i_loudness = max(i_loudness - 5, 0);
				f_loudness = i_loudness / 100;
				//printvolume(i_loudness);
				rudimentary(i_loudness);
				lista(i, liczba_utworow);
				channel->setVolume(f_loudness);
				while (GetAsyncKeyState(VK_NUMPAD2));
			}
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				i_loudness = min(i_loudness + 5, 100);
				f_loudness = i_loudness / 100;
				//printvolume(i_loudness);
				rudimentary(i_loudness);
				lista(i, liczba_utworow);
				channel->setVolume(f_loudness);
				while (GetAsyncKeyState(VK_NUMPAD8));
			}
			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				channel->stop();
				if(i>=1)
					i -= 2;
				else
					i -= 1;
				while (GetAsyncKeyState(VK_NUMPAD4));
			}
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				channel->stop();
				while (GetAsyncKeyState(VK_NUMPAD6));
			}
			if (GetAsyncKeyState(VK_NUMPAD9))
			{
				channel->stop();
				i -= 1;
				while (GetAsyncKeyState(VK_NUMPAD9));
			}
			if (GetAsyncKeyState(VK_NUMPAD5))
			{
				channel->getPaused(&isPaused);
				if(isPaused)
					cout << "*UNPAUSED*" << endl;
				else
					cout << "*PAUSED*" << endl;
				channel->setPaused(!isPaused);
				while (GetAsyncKeyState(VK_NUMPAD5));
			}
			if (GetAsyncKeyState(VK_NUMPAD0))
			{
				channel->stop();
				system->release();
				return 0;
				while (GetAsyncKeyState(VK_NUMPAD0));
			}
			if (GetAsyncKeyState(VK_NUMPAD3))
			{
				modify_settings();
				while (GetAsyncKeyState(VK_NUMPAD3));
			}
			if (GetAsyncKeyState(VK_NUMPAD1))
			{
				credits();
				while (GetAsyncKeyState(VK_NUMPAD1));
			}
			if (GetAsyncKeyState(VK_NUMPAD7))
			{
				
				while (GetAsyncKeyState(VK_NUMPAD7));
			}
		}

		else
		{
			if (_kbhit())
			{
			key = _getch();
			if (key == '2')
			{
				i_loudness = max(i_loudness - 5, 0);
				f_loudness = i_loudness / 100;
				//printvolume(i_loudness);
				rudimentary(i_loudness);
				lista(i, liczba_utworow);
				channel->setVolume(f_loudness);
			}
			if (key == '8')
			{
				i_loudness = min(i_loudness + 5, 100);
				f_loudness = i_loudness / 100;
				//printvolume(i_loudness);
				rudimentary(i_loudness);
				lista(i, liczba_utworow);
				channel->setVolume(f_loudness);
			}
			if (key == '4')
			{
				channel->stop();
				if(i>=1)
					i -= 2;
				else
					i -= 1;
			}
			if (key == '6')
			{
				channel->stop();
			}
			if (key == '9')
			{
				channel->stop();
				i -= 1;
			}
			if (key == '5')
			{
				channel->getPaused(&isPaused);
				if(isPaused)
					cout << "*UNPAUSED*" << endl;
				else
					cout << "*PAUSED*" << endl;
				channel->setPaused(!isPaused);
			}
			if (key == '0')
			{
				channel->stop();
				system->release();
				return 0;
			}
			if (key == '3')
			{
				modify_settings();
				while(_kbhit()) _getch(); 
			}
			if (key == '1')
			{
				credits();
			}
			if (key == '7')
			{

				while(_kbhit()) _getch();
			}
			}
		}

		}
			FMODErrorCheck(result);
		system->update();
    }

	rudimentary(i_loudness);
	wektor.clear();
}

return 0;
}

/*int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}*/
