#pragma once

#ifndef _KEYBOARDACTIONS_H
#define _KEYBOARDACTIONS_H

#include <Windows.h>
#include <iostream>
class KeyBoardActions {
public:
	static bool debug;
	static KeyBoardActions keyboard;
	void PressW();
	void ReleaseW();
	void PressA();
	void ReleaseA();
	void PressS();
	void ReleaseS();
	void PressD();
	void ReleaseD();
};

#endif