// Nintendo Sound Emulator.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "NESAPU.h"

NESAPU nesapu;

int main()
{
	BASS_Init(-1, 44100, NULL, NULL, nullptr);
	HSTREAM stream = BASS_StreamCreate(44100, 2, NULL, nesapu.BASSStreamProc, &nesapu);
	BASS_ChannelPlay(stream, false);
	nesapu.SetChannelsEnabled(true, false, false, false, false);
	nesapu.SetPulse1StateConstVol(NESAPU::Duty::_25, false, 15);
	nesapu.SetPulse1Sweep(true, 8, false, 8);
	nesapu.SetPulse1Note(256, 1);
	system("PAUSE");
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
