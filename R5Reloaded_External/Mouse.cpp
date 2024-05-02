#include "Mouse.h"


int Mouse::device_initialize(){
	const HMODULE user32 = LoadLibraryA("user32.dll");
	
	if (!user32)
	{
		printf("user32.dll failed to load!\n");
		return -1;
	}

	InjectMouseInput = reinterpret_cast<InjectMouseInput_t>(GetProcAddress(user32, "InjectMouseInput"));
	
	if (!InjectMouseInput)
	{
		printf("InjectMouseInput not found!\n");
		return -1;
	}

	return 0;
}

void Mouse::move(char x, char y){
	InjectedInputMouseInfo info = { 0 };
	info.DeltaX = x;
	info.DeltaY = y;
	InjectMouseInput(&info, 1);
}