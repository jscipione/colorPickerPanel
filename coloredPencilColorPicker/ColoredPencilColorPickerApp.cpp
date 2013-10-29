/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColoredPencilColorPickerApp.h"

#include "../Protocol.h"
#include "ColoredPencilColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.ColoredPencilColorPicker";


ColoredPencilColorPickerApp::ColoredPencilColorPickerApp()
	:
	BApplication(kSignature),
	fPanel()
{
}


ColoredPencilColorPickerApp::~ColoredPencilColorPickerApp()
{
}


void
ColoredPencilColorPickerApp::MessageReceived(BMessage* message)
{
	if (message->what == kInitiateConnection) {
		// This is the initial open message that ModuleProxy::Invoke is sending
		// us. Pass it on to the new color picker dialog which will find all
		// the details in it
		fPanel = new ColorPickerPanel(
			new ColoredPencilColorPicker((rgb_color){ 200, 10, 10 }), message);
	}

	BApplication::MessageReceived(message);
}


void
ColoredPencilColorPickerApp::ReadyToRun()
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
	new ColoredPencilColorPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
