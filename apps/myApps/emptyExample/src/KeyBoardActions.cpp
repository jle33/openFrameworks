#include "KeyBoardActions.h"


void KeyBoardActions::PressW()
{
	if(KeyBoardActions::debug)
		std::cout << "Press W" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x11; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags =  0|KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::ReleaseW()
{
	if(KeyBoardActions::debug)
		std::cout << "Released W" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x11; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags =  KEYEVENTF_KEYUP;; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}

void KeyBoardActions::PressS()
{
	if(KeyBoardActions::debug)
		std::cout << "Press S" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x1f; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags =  0|KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::ReleaseS()
{
	if(KeyBoardActions::debug)
		std::cout << "Release S" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x1f; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.dwFlags =  KEYEVENTF_KEYUP;; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::PressA()
{
	if(KeyBoardActions::debug)
		std::cout << "Press A" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x1e; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	//ip.ki.wVk = 0x57; //virtual key is ignored when scan is used
	ip.ki.dwFlags =  0|KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::ReleaseA()
{
	if(KeyBoardActions::debug)
		std::cout << "Release A" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x1e; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	//ip.ki.wVk = 0x57; // virtual-key code for the "w" key
	ip.ki.dwFlags =  KEYEVENTF_KEYUP;; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::PressD()
{
	if(KeyBoardActions::debug)
		std::cout << "Press D" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x20; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	//ip.ki.wVk = 0x57; //virtual key is ignored when scan is used
	ip.ki.dwFlags =  0|KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}
void KeyBoardActions::ReleaseD()
{
	if(KeyBoardActions::debug)
		std::cout << "Release D" << std::endl;
	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x20; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	//ip.ki.wVk = 0x57; // virtual-key code for the "w" key
	ip.ki.dwFlags =  KEYEVENTF_KEYUP;; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}