
#ifndef TWOHANDGESTURES_H
#define TWOHANDGESTURES_H

#include "MouseActions.h"
#include "KeyBoardActions.h"
#include "TwoHandGestures.h"

//static MouseActions mouse;
bool inZoom = false;
double zoomx;

VVoid showMessage(ViiMLogEvent& e, VVoidP obj){
	cout << e.message << endl;
}
VVoid TwoHandGestures::draw()
{
	_depthImage.draw(0, 0, 320, 240);
	_smoothImage.draw(320, 0, 320 , 240);
}

VVoid TwoHandGestures::update()
{
		_depthImage.setFromPixels(engine.getDepthPixels(1), width, height, OF_IMAGE_GRAYSCALE);
	_smoothImage.setFromPixels(engine.getSmoothDepthPixels(1), width, height, OF_IMAGE_GRAYSCALE);
}
VVoid TwoHandGestures::setup(){
	engine.addEventListener(ViiMLogEvent::MESSAGE, showMessage, this);
	gesture.addEventListener(ViiMLogEvent::MESSAGE, showMessage, this);
	engine.startDevice(1, ViiMStream::BOTH, ViiMResolution::VGA, ViiMResolution::VGA);	//start the ViiM engine
	engine.registerUnitProcess(1, gesture);
	engine.setLogLeveToAll(ViiMLogLevel::ALL);
	width = engine.getColorWidth(1);
	height = engine.getColorHeight(1);

	gesture.setFocusType(ViiMFocusType::WAVE_HAND);
	gesture.setFarThreshold(4000); //Sets a threshold so that the sensor detects up to 4 meters away, helps avoid interference from background
	gesture.setNumberOfHandsToProcess(2); // only want to set up two hands

	/* setting up listeners to the desired events*/
	gesture.addEventListener(ViiMHandEvent::CREATE, handCreateHandler, this);					//create hand
	gesture.addEventListener(ViiMHandEvent::UPDATE, handUpdateHandler, this);					//update hand
	gesture.addEventListener(ViiMHandEvent::LOST, handLostHandler, this);						//lost Hand
	gesture.addEventListener(ViiMGestureEvent::SWIPE_RIGHT, swipeRightHandler, this);			//swipe right
	gesture.addEventListener(ViiMGestureEvent::SWIPE_LEFT, swipeLeftHandler, this);				//swipe left
	gesture.addEventListener(ViiMGestureEvent::SWIPE_UP, swipeUpHandler, this);					//swipe up
	gesture.addEventListener(ViiMGestureEvent::SWIPE_DOWN, swipeDownHandler, this);				//swipe down
	gesture.addEventListener(ViiMGestureEvent::HAND_OPEN, handOpenHandler, this);				//hand open
	gesture.addEventListener(ViiMGestureEvent::HAND_CLOSE, handCloseHandler, this);				//hand close
	gesture.addEventListener(ViiMGestureEvent::MOVE, moveHandler, this);						//move gesture
	gesture.addEventListener(ViiMGestureEvent::DRAG, dragHandler, this);						//drag gesture


	gestureCount1 = 0;
	gestureCount2 = 0;
	currentGesture1 = "";
	currentGesture2 = "";
	cGesture = new VChar[100];
	handVisible = false;

	return;
}

/* ----- THE EVENT HANDLERS --------------- */
VVoid TwoHandGestures::handCreateHandler(ViiMHandEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);

	pThis->trackedHands[event.handID] = new TrackedHands();

	pThis->trackedHands[event.handID]->x = event.position.x;
	pThis->trackedHands[event.handID]->y = event.position.y;
	pThis->trackedHands[event.handID]->z = event.position.z;	 
	
	//pThis->handOpen = true;
	cout << event.handID << endl;
	MouseActions::mouse.AmtHandDetected++;
	cout << "Hand Amount: ----------------------------->>>>> " << MouseActions::mouse.AmtHandDetected << endl;
	//system("pause");
	return;
}

VVoid TwoHandGestures::handUpdateHandler(ViiMHandEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);

	pThis->trackedHands[event.handID]->x = event.position.x;
	pThis->trackedHands[event.handID]->y = event.position.y;
	pThis->trackedHands[event.handID]->z = event.position.z;

	if(MouseActions::mouse.AmtHandDetected == 1){
		MouseActions::mouse.moveMouse((pThis->trackedHands[1]->x /* pThis->width*/), (pThis->trackedHands[1]->y /* pThis->height*/));
		std::cout << "ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE_ONE" << std::endl;
	}
	//cout << "Hand Count: " << mouse.AmtHandDetected << endl;
	if(MouseActions::mouse.AmtHandDetected > 1){
		//std::cout << "!!! TWO HANDS !!!" << std::endl;
		//system("pause");
	}
	cout << "CLOSED HANDS ======== " << MouseActions::mouse.closed_hands << endl;
	if(MouseActions::mouse.closed_hands == 2)
	{
		cout << "TWO HANDS CLOSED ********************************************" << endl;
		if(!inZoom)
		{
			zoomx = pThis->trackedHands[event.handID]->x;
			inZoom = true;
		}
		MouseActions::mouse.RightHold();
		MouseActions::mouse.RightHoldTrue = true;
		MouseActions::mouse.Zoom(zoomx, pThis->trackedHands[event.handID]->x, pThis->trackedHands[event.handID]->y);
		zoomx = pThis->trackedHands[event.handID]->x;
	}else{
		inZoom = false;
		if(MouseActions::mouse.RightHoldTrue == true){
			MouseActions::mouse.RightRelease();
			MouseActions::mouse.RightHoldTrue = false;
		}
	}

	return;
}

VVoid TwoHandGestures::handLostHandler(ViiMHandEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);

	delete pThis->trackedHands[event.handID];
	pThis->trackedHands.erase(event.handID);
	MouseActions::mouse.AmtHandDetected--;
	if(MouseActions::mouse.closed_hands != 0)
		MouseActions::mouse.closed_hands--;
	//cout << "Closed Hands: " << mouse.closed_hands << endl;
	//system("pause");
	return;
}

VVoid TwoHandGestures::swipeRightHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Swipe Right ", event.handID);

	cout << event.handID << "-> Swipe Right" << endl;
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;
}

VVoid TwoHandGestures::swipeLeftHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Swipe Left ", event.handID);
	cout << event.handID << "-> Swipe left" << endl;
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/

	return;
}

VVoid TwoHandGestures::swipeUpHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Swipe Up ", event.handID);
	cout << event.handID << "-> Swipe up" << endl;
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;
}

VVoid TwoHandGestures::swipeDownHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Swipe Down ", event.handID);
	cout << event.handID << "-> Swipe down" << endl;
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;
}

void getGesturePos(){

}

VVoid TwoHandGestures::handOpenHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Hand Open ", event.handID);
	cout << event.handID << "-> Open Hand" << endl;

	pThis->handOpen = true;
	VCharP cPos = new VChar[50];
	MouseActions::mouse.LeftRelease();
	if(MouseActions::mouse.AmtHandDetected == 1){
		MouseActions::mouse.LeftRelease();
	}
	if(MouseActions::mouse.closed_hands != 0)
		MouseActions::mouse.closed_hands--;
	cout << "Closed Hands: " << MouseActions::mouse.closed_hands << endl;
	//system("pause");
	//printf("X: %.0f   Z: %.1f \nY: %.0f", pThis->handx, pThis->handz, pThis->handy);
	//system("pause");
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		cout << "the number is" << pThis->cGesture << endl;
		system("pause");
		//pThis->currentGesture1.append(pThis->cGesture);
		
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;
}

VVoid TwoHandGestures::handCloseHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	sprintf(pThis->cGesture, "#%d -> Hand Close ", event.handID);
	cout << event.handID << "-> Close Hand" << endl;

	pThis->handOpen = false;
	if(MouseActions::mouse.AmtHandDetected == 1){
		MouseActions::mouse.LeftHold();
	}
	MouseActions::mouse.closed_hands++;
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/

	return;
}

VVoid TwoHandGestures::dragHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	if(pThis->handOpen == true){
		return;
	}
	
	sprintf(pThis->cGesture, " ( drag ) ");
	cout << event.handID << "-> (drag)" << endl;

	//pThis->handOpen = false;

	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->moveGeseture = "";
		pThis->moveGeseture.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->moveGeseture = "";
		pThis->moveGeseture.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;
	
}

VVoid TwoHandGestures::moveHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	if(pThis->handOpen == false){
		return;
	}
	sprintf(pThis->cGesture, " move ");
	cout << event.handID << "-> (move)" << endl;

	//mouse.GetMousePosition
	/*
	if (trackedIds[0] == event.handID)
	{
		pThis->moveGeseture = "";
		pThis->moveGeseture.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->moveGeseture = "";
		pThis->moveGeseture.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}
	*/
	return;

}



/*
VVoid TwoHandGestures::steadyHandler(ViiMGestureEvent& event, VVoidP object)
{
	TwoHandGestures* pThis = static_cast<TwoHandGestures*>(object);
	VUInt16P trackedIds = pThis->gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);	
	cout << event.handID << " -> Steady" << endl;

	if (trackedIds[0] == event.handID)
	{
		pThis->currentGesture1 = "";
		pThis->currentGesture1.append(pThis->cGesture);
		pThis->gestureCount1 = 1;
	}
	else
	{
		pThis->currentGesture2 = "";
		pThis->currentGesture2.append(pThis->cGesture);
		pThis->gestureCount2 = 1;
	}

}*/




VVoid TwoHandGestures::displayHandPosition()
{

	VCharP cPos = new VChar[50];
	//get the IDs of the processed hands and the number of hands processed - set to 2 in the setup phase with setNumberOfHandsToProcess()
	VUInt16P trackedIds = gesture.getTrackedHandsIDs(ViiMHandStatusType::PROCESSED);
	VUInt16 numberProcessHands = gesture.getNumberOfHandsTracked(ViiMHandStatusType::PROCESSED);
	
	map<VUInt16, TrackedHands*>::iterator it;
	if( trackedHands.size() )
	{
		for(it = trackedHands.begin(); it != trackedHands.end(); ++it)
		{
			sprintf(handID, "#%d", it->first);
			cout << "#" << it->first << endl;

			for(VUInt16 i = 0; i < numberProcessHands; ++i)
			{
				if (it->first == trackedIds[i])
				{
					sprintf(cPos, "#%d -  X: %.0f  Y: %.0f  Z: %.1f ", it->first, it->second->x * width, it->second->y * height, it->second->z);
					cout << "#" << it->first << " - X: " << it->second->x * width << "		Y: " << it->second->y * height << "		Z: " << it->second->z << endl;
				}
			}
		}
	}
	return;
}

VVoid TwoHandGestures::displayGesturesDetected()
{
	if (gestureCount1 && gestureCount1 < MAX_FRAMES_SHOW)
	{
		//gestures1.drawString(currentGesture1, 720, 420);
		gestureCount1++;
	}
	else
		gestureCount1 = 0;

	if (gestureCount2 && gestureCount2 < MAX_FRAMES_SHOW)
	{
		//gestures2.drawString(currentGesture2, 720, 450);
		gestureCount2++;
	}
	else
		gestureCount2 = 0;

	return;
}

//ViiM GESTURE FUNCTIONS##############################END
#endif