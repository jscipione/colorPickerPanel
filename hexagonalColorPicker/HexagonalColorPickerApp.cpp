/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "HexagonalColorPickerApp.h"

#include <new>

#include <LayoutBuilder.h>
#include <Window.h>

#include "../ColorPickerPanel.h"
#include "../Protocol.h"
#include "HexagonalColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku.HexagonalColorPicker";


HexagonalColorPickerApp::HexagonalColorPickerApp()
	:
	BApplication(kSignature),
	fPanel(),
	fDefaultColor(make_color(255, 0, 0))
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
		fPanel = new(std::nothrow) ColorPickerPanel(
			new(std::nothrow)HexagonalColorPicker(fDefaultColor), message);
	}

	BApplication::MessageReceived(message);
}


void
HexagonalColorPickerApp::ReadyToRun()
{
	if (fPanel != NULL)
		fPanel->Show();
	else {
		// create a window if run directly
		BWindow* window = new BWindow(BRect(100, 100, 100, 100),
			"Hexagonal picker", B_TITLED_WINDOW, B_NOT_ZOOMABLE
				| B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE
				| B_AUTO_UPDATE_SIZE_LIMITS);

		BLayoutBuilder::Group<>(window, B_VERTICAL, 0)
			.Add(new(std::nothrow) HexagonalColorPicker(fDefaultColor))
			.End();
		window->Show();
	}
}


int
main()
{
	new HexagonalColorPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
