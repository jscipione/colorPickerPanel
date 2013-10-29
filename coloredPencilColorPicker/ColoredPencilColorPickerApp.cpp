/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColoredPencilColorPickerApp.h"

#include <Rect.h>
#include <Window.h>

#include "../ColorPickerPanel.h"
#include "ColoredPencilColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.ColoredPencilColorPicker";
//static int32 kColorControlValueChanged = 'ccvc';


ColoredPencilColorPickerApp::ColoredPencilColorPickerApp()
	:
	BApplication(kSignature),
	fColorPickerPanel(NULL)
{
}


ColoredPencilColorPickerApp::~ColoredPencilColorPickerApp()
{
}


void
ColoredPencilColorPickerApp::MessageReceived(BMessage* message)
{
	BApplication::MessageReceived(message);
}


void
ColoredPencilColorPickerApp::ReadyToRun()
{
	if (fColorPickerPanel == NULL) {
		ColoredPencilColorPicker* colorPicker
			= new ColoredPencilColorPicker((rgb_color) { 200, 10, 10 });

		fColorPickerPanel = new ColorPickerPanel(BRect(100, 100, 200, 200),
			static_cast<BView*>(colorPicker));
		fColorPickerPanel->Show();
	}
}


int
main()
{
	ColoredPencilColorPickerApp app;
	app.Run();

	return 0;
}
