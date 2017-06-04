#include "TargetVersion.h"
#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {

	System* system;

	// Create the system object.
	system = new System();
	if (!system) {
		MessageBox(NULL, "Failed to create system object", "Error", NULL);
		return 0;
	}
	// Initialize and run the system object.
	if (system->initialize())
		system->run();
	else MessageBox(*system->getHWND(), "Failed to initialize system", "Error", NULL);

	// Shutdown and release the system object.
	system->shutdown();
	delete system;
	system = 0;

	return 0;
}