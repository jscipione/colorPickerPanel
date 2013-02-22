/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */


#include "SimpleColorPickerApp.h"

#include <Window.h>

#include "../ColorPickerPanel.h"
#include "SimpleColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.SimpleColorPicker";


SimpleColorPickerApp::SimpleColorPickerApp()
	:
	BApplication(kSignature),
	fColorPickerPanel(NULL)
{
}


SimpleColorPickerApp::~SimpleColorPickerApp()
{
}


void
SimpleColorPickerApp::MessageReceived(BMessage* message)
{
	BApplication::MessageReceived(message);
}


void
SimpleColorPickerApp::ReadyToRun()
{
	if (fColorPickerPanel == NULL) {
		fColorPickerPanel = new ColorPickerPanel(BRect(100, 100, 100, 200),
			new SimpleColorPicker((rgb_color){ 255, 0, 0 }));

		fColorPickerPanel->Show();
	}		
}


int
main()
{
	SimpleColorPickerApp app;
	app.Run();

	return 0;
}
