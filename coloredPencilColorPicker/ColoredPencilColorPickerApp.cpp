/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColoredPencilColorPickerApp.h"

#include <new>

#include <LayoutBuilder.h>
#include <Window.h>

#include "../ColorPickerPanel.h"
#include "../Protocol.h"
#include "ColoredPencilColorPicker.h"


const char* kSignature = "application/x-vnd.Haiku-ColoredPencilColorPicker";


ColoredPencilColorPickerApp::ColoredPencilColorPickerApp()
	:
	BApplication(kSignature),
	fPanel(),
	fDefaultColor(make_color(200, 10, 10))
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
		fPanel = new(std::nothrow) ColorPickerPanel(new(std::nothrow)
			ColoredPencilColorPicker(fDefaultColor), message, B_CELLS_4x10);
	}

	BApplication::MessageReceived(message);
}


void
ColoredPencilColorPickerApp::ReadyToRun()
{
	if (fPanel != NULL)
		fPanel->Show();
	else {
		// create a window if run directly
		BWindow* window = new BWindow(BRect(100, 100, 100, 100),
			"Colored pencil picker", B_TITLED_WINDOW, B_NOT_ZOOMABLE
				| B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE
				| B_AUTO_UPDATE_SIZE_LIMITS);

		BLayoutBuilder::Group<>(window, B_VERTICAL, 0)
			.Add(new(std::nothrow) ColoredPencilColorPicker(fDefaultColor))
			.End();
		window->Show();
	}
}


int
main()
{
	new ColoredPencilColorPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
