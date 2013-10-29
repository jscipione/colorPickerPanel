/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "HexagonalColorPickerApp.h"

#include <Window.h>

#include "../ColorPickerPanel.h"
#include "HexagonalColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.HexagonalColorPicker";


HexagonalColorPickerApp::HexagonalColorPickerApp()
	:
	BApplication(kSignature),
	fColorPickerPanel(NULL)
{
}


HexagonalColorPickerApp::~HexagonalColorPickerApp()
{
}


void
HexagonalColorPickerApp::MessageReceived(BMessage* message)
{
	BApplication::MessageReceived(message);
}


void
HexagonalColorPickerApp::ReadyToRun()
{
	if (fColorPickerPanel == NULL) {
		fColorPickerPanel = new ColorPickerPanel(BRect(100, 100, 100, 200),
			new HexagonalColorPicker((rgb_color){ 255, 0, 0 }));
		fColorPickerPanel->Show();
	}		
}


int
main()
{
	HexagonalColorPickerApp app;
	app.Run();

	return 0;
}
