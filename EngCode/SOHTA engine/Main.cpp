#include "App.h"

#include <iostream>
#include <fstream> 

App app;
void OpenConsole();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	OpenConsole();

	/*std::ofstream outfile("test.txt");

	outfile << "my text here!" << std::endl;

	outfile.close();*///

	app.StartApp(hInstance);
	app.RunApp();
	app.EndApp();
	
	cout << " fodase";

	FreeConsole();
	return 10;
}

void OpenConsole()
{
	FILE* stream;

	AllocConsole();
	freopen_s(&stream, "conin$", "r", stdin);
	freopen_s(&stream, "conout$", "w", stdout);
	freopen_s(&stream, "conout$", "w", stderr);
	printf("Debugging Window:\n");
}
