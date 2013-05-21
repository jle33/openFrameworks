#include "MouseActions.h"

long fScreenWidth = (GetSystemMetrics( SM_CXSCREEN ) - 1);
long fScreenHeight = (GetSystemMetrics( SM_CYSCREEN ) - 1);

void MouseActions::LeftHold()
{
	INPUT Input={0};	// Create our input, 0 for mouse, 1 for keyboard, 2 for hardware
	Input.type = INPUT_MOUSE;	// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;	// We are setting left mouse button down.
	SendInput( 1, &Input, sizeof(INPUT) );	// Send the input.
	ZeroMemory(&Input,sizeof(INPUT));	//Clear memory
}

void MouseActions::LeftRelease()
{
	INPUT Input={0};							
	Input.type = INPUT_MOUSE;									
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;	// setting left mouse button up.
	SendInput( 1, &Input, sizeof(INPUT) );								
}
void MouseActions::RightHold()
{
	INPUT Input = {0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput( 1, &Input, sizeof(INPUT));
	ZeroMemory(&Input, sizeof(INPUT));
}

void MouseActions::RightRelease()
{
	INPUT Input = {0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
	SendInput( 1, &Input, sizeof(INPUT) );
}

void MouseActions::LeftClick()
{  
	INPUT Input={0};													
	Input.type = INPUT_MOUSE;									
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;							
	SendInput( 1, &Input, sizeof(INPUT) );								

	ZeroMemory(&Input,sizeof(INPUT));									
	Input.type = INPUT_MOUSE;									
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								
	SendInput( 1, &Input, sizeof(INPUT) );								
}


void MouseActions::RightClick()
{
	INPUT Input = {0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput( 1, &Input, sizeof(INPUT));

	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
	SendInput( 1, &Input, sizeof(INPUT) );
}

// Returns the mouses current position, m holds x and y - May need to calculate where the mouse should  move based on sensor?
POINT MouseActions::GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

// Sets the mouses position.
void MouseActions::SetMousePosition(POINT mp)
{
	long fScreenWidth2 = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight2 = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx = mp.x * ( 65535.0f / fScreenWidth  );
	float fy = mp.y * ( 65535.0f / fScreenHeight );		  

	INPUT Input = { 0 };			
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;

	//Storing x, y coordinates into mouse input
	Input.mi.dx	= (long)fx;
	Input.mi.dy	= (long)fy;
	//Sends it to input to be processed
	SendInput(1,&Input,sizeof(INPUT));
}

void MouseActions::moveMouse(float x, float y){
//	std::cout << "X : " << x << " Y : " << y << std::endl;

	float fx = ( 65535.0f /*/ fScreenWidth*/ );
	float fy = ( 65535.0f /*/ fScreenHeight*/ );		  
	//system("pause");
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = long(fx * (x));
	Input.mi.dy = long(fy * (y));
//	std::cout << "Mouse X: " << Input.mi.dx << " Mouse y: " << Input.mi.dy << std::endl;
	SendInput(1,&Input,sizeof(INPUT));
	
}

void MouseActions::Zoom(double originalx, float x1, float y1){
	float dif = originalx-x1;
	INPUT input = {0};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = x1;
	input.mi.dy = y1-dif;
	SendInput(1,&input,sizeof(INPUT));
}

void MouseActions::Rotate(float x, float y){

}