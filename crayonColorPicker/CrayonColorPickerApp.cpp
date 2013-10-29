/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "CrayonColorPickerApp.h"

#include <Rect.h>
#include <Window.h>

#include "../ColorPickerPanel.h"
#include "CrayonColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.CrayonColorPicker";
//static int32 kColorControlValueChanged = 'ccvc';


CrayonColorPickerApp::CrayonColorPickerApp()
	:
	BApplication(kSignature),
	fColorPickerPanel(NULL)
{
}


CrayonColorPickerApp::~CrayonColorPickerApp()
{
}


void
CrayonColorPickerApp::MessageReceived(BMessage* message)
{
	BApplication::MessageReceived(message);
}


void
CrayonColorPickerApp::ReadyToRun()
{
	if (fColorPickerPanel == NULL) {
		CrayonColorPicker* colorPicker
			= new CrayonColorPicker((rgb_color) { 200, 10, 10 });

		fColorPickerPanel = new ColorPickerPanel(BRect(100, 100, 200, 200),
			static_cast<BView*>(colorPicker));
		fColorPickerPanel->Show();
	}
}


int
main()
{
	CrayonColorPickerApp app;
	app.Run();

	return 0;
}
