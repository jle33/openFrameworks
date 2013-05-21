#pragma once

#ifndef _TWOHANDGESTURES_

#define _WIN32_WINNT 0x0502
#define WIN32_LEAN_AND_MEAN

#include <ofMain.h>
#include <ViiM/ViiMIncludes.h>



#define NUM_THREADS 5
#define MAX_FRAMES_SHOW 30

typedef struct TrackedHands
{
	VFloat		x;
	VFloat		y;
	VFloat		z;
	VUInt16		ID;
	VBool		handopen;
} TrackedHands;

class TwoHandGestures : public ofBaseApp
{
public:
	VVoid	setup();	//initialized and sets the variables
	VVoid	update();	//updates sensor images
	VVoid	draw();
	VVoid	displayHandPosition();		//displays the hand position
	VVoid	displayGesturesDetected();	//displays the detected gestures

	/* ----- the events' handlers: */
	/* for the hand; */
	static VVoid handCreateHandler(ViiMHandEvent& e, VVoidP object);				//create hand
	static VVoid handUpdateHandler(ViiMHandEvent& e, VVoidP object);				//update hand
	static VVoid handLostHandler(ViiMHandEvent& e, VVoidP object);					//lost Hand
	/* for swipe gestures; */
	static VVoid swipeRightHandler(ViiMGestureEvent& e, VVoidP object);				//swipe right
	static VVoid swipeLeftHandler(ViiMGestureEvent& e, VVoidP object);				//swipe left
	static VVoid swipeUpHandler(ViiMGestureEvent& e, VVoidP object);				//swipe up
	static VVoid swipeDownHandler(ViiMGestureEvent& e, VVoidP object);				//swipe down
	/* for hand profile gestures; */
	static VVoid handOpenHandler(ViiMGestureEvent& e, VVoidP object);				//hand open
	static VVoid handCloseHandler(ViiMGestureEvent& e, VVoidP object);				//hand close
	/* for action gestures */
	static VVoid moveHandler(ViiMGestureEvent& e, VVoidP object);					//move gesture
	//static VVoid waveHandler(ViiMGestureEvent& e, VVoidP object);					//wave gesture
	//static VVoid steadyHandler(ViiMGestureEvent& e, VVoidP object);				//steady gesture
	static VVoid dragHandler(ViiMGestureEvent& e, VVoidP object);					//drag gesture

	//ViiM engine & ViiM gesture unit
	ViiM engine;
	ViiMUnitGesture gesture;
	//to control the gestures desplay
	VUInt32 gestureCount1;
	VUInt32 gestureCount2;
	//controlling hand status
	VBool handVisible;
	VBool handOpen;
	//hand positions
	VFloat handx;
	VFloat handy;
	VFloat handz;

	string openGesture;
	string moveGeseture;
	string currentGesture1;
	string currentGesture2;
	VCharP cGesture;

	VUInt16 width;
	VUInt16 height;

	//map to hold tracked hands
	map<VUInt16, TrackedHands*> trackedHands;
	VChar handID[10];
	//Drawing variables
	ofImage _smoothImage;
	ofImage _depthImage;
	ofImage _descriptionImage;
};


#endif