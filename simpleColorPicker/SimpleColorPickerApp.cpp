/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "SimpleColorPickerApp.h"

#include "../Protocol.h"
#include "SimpleColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.SimpleColorPicker";


SimpleColorPickerApp::SimpleColorPickerApp(const char* signature)
	:
	BApplication(signature),
	fPanel()
{
}


SimpleColorPickerApp::~SimpleColorPickerApp()
{
}


void
SimpleColorPickerApp::MessageReceived(BMessage* message)
{
	if (message->what == kInitiateConnection) {
		// This is the initial open message that ModuleProxy::Invoke is sending
		// us. Pass it on to the new color picker dialog which will find all
		// the details in it
		fPanel = new ColorPickerPanel(new SimpleColorPicker(),
			message);
	}

	BApplication::MessageReceived(message);
}


void
SimpleColorPickerApp::ReadyToRun()
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
	new SimpleColorPickerApp(kSignature);
	be_app->Run();
	delete be_app;
	return 0;
}
