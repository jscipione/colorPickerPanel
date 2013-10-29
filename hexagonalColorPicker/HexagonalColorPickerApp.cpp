/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "HexagonalColorPickerApp.h"

#include "../Protocol.h"
#include "HexagonalColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.HexagonalColorPicker";


HexagonalColorPickerApp::HexagonalColorPickerApp()
	:
	BApplication(kSignature),
	fPanel()
{
}


HexagonalColorPickerApp::~HexagonalColorPickerApp()
{
}


void
HexagonalColorPickerApp::MessageReceived(BMessage* message)
{
	if (message->what == kInitiateConnection) {
		// This is the initial open message that ModuleProxy::Invoke is sending
		// us. Pass it on to the new color picker dialog which will find all
		// the details in it
		fPanel = new ColorPickerPanel(
			new HexagonalColorPicker((rgb_color){ 255, 0, 0 }), message);
	}

	BApplication::MessageReceived(message);
}


void
HexagonalColorPickerApp::ReadyToRun()
{
	if (fPanel != NULL)
		fPanel->Show();
	else
		Quit();
		// Quit if run directly
}


int
main()
{
	new HexagonalColorPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
