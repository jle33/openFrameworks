#pragma once

#ifndef _MOUSEACTIONS_H
#define _MOUSEACTIONS_H

#include <Windows.h>
#include <WinUser.h>
#include <iostream>

class MouseActions{
public:
	static MouseActions mouse;
	bool	dragRunning;
	bool	HandDetect;
	bool	RightClicked;
	bool	LeftClicked;
	bool	inZoom;
	bool	RightHoldTrue;
	int		AmtHandDetected;
	int		closed_hands;
	float	prevZoom;
	MouseActions(){
		AmtHandDetected = 0;
		prevZoom = 0;
		inZoom = false;
		HandDetect = false;
		RightClicked = false;
		LeftClicked = false;
		dragRunning = false;
		RightHoldTrue = false;
		closed_hands = 0;
	}
	void LeftHold();
	void LeftRelease();
	void RightHold();
	void RightRelease();
	void RightClick();
	void LeftClick();
	POINT GetMousePosition();
	void SetMousePosition(POINT mp);

	void moveMouse(float x, float y);
	void Rotate(float x, float y);
	void Zoom(double originalx, float x1, float x2 );

	

};

#endif
