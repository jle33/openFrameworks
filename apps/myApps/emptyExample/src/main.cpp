#define _WIN32_WINNT 0x0501

//Windows Libraries
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <psapi.h>
#include <process.h>
#include <tlhelp32.h>

//Standard Libraries
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

//Gesture Libraries
#include <ViiM\ViiMIncludes.h>
#include "ofAppGlutWindow.h"
#include "TwoHandGestures.h"
#include "MouseActions.h"
#include "KeyBoardActions.h"

//Intializing the Mouse and Keyboad Object
MouseActions MouseActions::mouse = MouseActions();
KeyBoardActions KeyBoardActions::keyboard = KeyBoardActions();
//Boolean to enable debugging mode for keyboard
bool KeyBoardActions::debug = true;



// This gets called by winapi for every window on the desktop
BOOL CALLBACK EnumWindowsProc(HWND windowHandle, LPARAM lParam)  {
	DWORD searchedProcessId = (DWORD)lParam;  // This is the process ID we search for (passed from BringToForeground as lParam)
	DWORD windowProcessId = 0;
	GetWindowThreadProcessId(windowHandle, &windowProcessId); // Get process ID of the window we just found
	if (searchedProcessId == windowProcessId)  {  // Is it the process we care about?
		std::cout << "Found the window, bringing it to the front" << std::endl;
		SetForegroundWindow(windowHandle);  // Set the found window to foreground
		return FALSE;  // Stop enumerating windows
	}
	return TRUE;  // Continue enumerating
}

//--------------------------------------------------------------
int main(){
	//holds the application in focus
	HANDLE         hProcessSnap = NULL; 
	BOOL           bRet      = FALSE; 
	PROCESSENTRY32 pe32      = {0}; 
	//LPTSTR         exeFile	 = "notepad.exe";
	//LPTSTR         exeFile	 = "hl2.exe";
	LPTSTR         exeFile	 = "OPENNI2.0 SkyGesture.exe";
	int			   retries	 = 5;
	int			   counter   = 0;
	bool		   foundProc = false;

	std::cout << "RESEARCH - SPRING 2013\nAdrian Wang, James Le, Juan Pedraza\n-----------------------------------" << std::endl;
	std::cout << "This program will for, by default, search for CryEngine3 Editor process (The window can not be minimized!). Please have the device ready and plugged in." << std::endl;
	std::cout << "Finding " << exeFile << std::endl;
	//Given a certain amount of retries, it will try to look for the process
	while(counter < retries){
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
		if (hProcessSnap == INVALID_HANDLE_VALUE) return 0; 
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hProcessSnap, &pe32)) 
		{ 
			do 
			{ 
				if (_tcsicmp( pe32.szExeFile, exeFile) == 0) {
					foundProc = true;
					std::cout << "Process Found!" << std::endl; 
					EnumWindows(&EnumWindowsProc, (LPARAM)pe32.th32ProcessID);
					break;
				}
			} while (Process32Next(hProcessSnap, &pe32)); 
		}
		if(foundProc)
			break;
		std::cout << "Retrying " << counter+1 << " of "<< retries << std::endl;
		Sleep(2000);
		counter++;
	}
	if(foundProc){
		/*
		//------Test keyboard emulation---------
		Sleep(5000);
		std::cout << "sending keys" << std::endl;
	
		std::cout << "Moving foward" << std::endl;
		KeyBoardActions::keyboard.PressW();
		Sleep(2500);
		KeyBoardActions::keyboard.ReleaseW();
		Sleep(25);

		std::cout << "Moving Back" << std::endl;
		KeyBoardActions::keyboard.PressS();
		Sleep(2500);
		KeyBoardActions::keyboard.ReleaseS();
		Sleep(25);

		std::cout << "Moving left" << std::endl;
		KeyBoardActions::keyboard.PressA();
		Sleep(2500);
		KeyBoardActions::keyboard.ReleaseA();
		Sleep(25);

		std::cout << "Moving Right" << std::endl;
		KeyBoardActions::keyboard.PressD();
		Sleep(2500);
		KeyBoardActions::keyboard.ReleaseD();
		std::cout << "finished sending" << std::endl;
		//	MouseActions::mouse.LeftClick();
		
		//--------------End of Test --------------------
		*/
		ofAppGlutWindow window; // create a window
		//set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
		ofSetupOpenGL(&window, 320, 160, OF_WINDOW);
		window.setWindowTitle("ViiM - Multiple Hands Gestures");
		ofRunApp(new TwoHandGestures()); // start the app
		
	}
	else
		std::cout << "Process " << exeFile << " was not found. Exiting..." << std::endl;


	system("pause");


}
