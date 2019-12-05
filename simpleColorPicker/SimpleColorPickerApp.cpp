/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "SimpleColorPickerApp.h"

#include <new>

#include <LayoutBuilder.h>
#include <Window.h>

#include "../ColorPickerPanel.h"
#include "../Protocol.h"
#include "SimpleColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku-SimpleColorPicker";


SimpleColorPickerApp::SimpleColorPickerApp()
	:
	BApplication(kSignature),
	fPanel(NULL),
	fDefaultColor(make_color(0xAA, 0xAA, 0xAA))
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
		fPanel = new(std::nothrow) ColorPickerPanel(
			new(std::nothrow) SimpleColorPicker(fDefaultColor),
			message);
	}

	BApplication::MessageReceived(message);
}


void
SimpleColorPickerApp::ReadyToRun()
{
	if (fPanel != NULL)
		fPanel->Show();
	else {
		// create a window if run directly
		BWindow* window = new BWindow(BRect(100, 100, 100, 100),
			"Simple color picker", B_TITLED_WINDOW, B_NOT_ZOOMABLE
				| B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE
				| B_AUTO_UPDATE_SIZE_LIMITS);

		BLayoutBuilder::Group<>(window, B_VERTICAL, 0)
			.Add(new(std::nothrow) SimpleColorPicker(fDefaultColor))
			.End();
		window->Show();
	}
}


int
main()
{
	new SimpleColorPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
