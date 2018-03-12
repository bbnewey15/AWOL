#include<Windows.h>

#define LOG_ACTIVE 1
//or 0

#ifdef LOG_ACTIVE
#pragma once
#include <io.h>
#pragma once
#include <fcntl.h>
#pragma once
#include <iostream>
#pragma once
#include <stdio.h>
#pragma once
#include <fstream>
	int hCrt;
	FILE *hf;

	//I like stdout
	void allocateStdIO() {
		//Create a console for this application
		AllocConsole();
		//Redirect unbuffered STDOUT to the console
		HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
		FILE *COutputHandle = _fdopen(SystemOutput, "w" );
		*stdout = *COutputHandle;
		setvbuf(stdout, NULL, _IONBF, 0);

		//Redirect unbuffered STDERR to the console
		HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
		int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
		FILE *CErrorHandle = _fdopen(SystemError, "w" );
		*stderr = *CErrorHandle;
		setvbuf(stderr, NULL, _IONBF, 0);

		//Redirect unbuffered STDIN to the console
		HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
		FILE *CInputHandle = _fdopen(SystemInput, "r" );
		*stdin = *CInputHandle;
		setvbuf(stdin, NULL, _IONBF, 0);
    
		//make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
		std::ios::sync_with_stdio(true);
	}
#endif