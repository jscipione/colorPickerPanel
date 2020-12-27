/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus, superstippi@gmx.de
 *		John Scipione, jscipione@gmail.com
 */


#include "ColorPickerPanel.h"

#include <stdio.h>

#include <Alignment.h>
#include <Application.h>
#include <Box.h>
#include <Button.h>
#include <Catalog.h>
#include <Control.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <Locale.h>
#include <Message.h>
#include <Rect.h>
#include <Size.h>
#include <View.h>

#include "ColorPicker.h"
#include "Protocol.h"


enum {
	MSG_CANCEL					= 'cncl',
	MSG_DONE					= 'done',
};


const int32 kColorChanged = 'clch';
const int32 kColorDropped = 'PSTE';


ColorPickerPanel::ColorPickerPanel(ColorPicker* view, BMessage* message,
	color_control_layout layout)
	:
	BWindow(BRect(100, 100, 100, 100), "Pick a color",
		B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
		B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_AUTO_UPDATE_SIZE_LIMITS
			| B_CLOSE_ON_ESCAPE),
	fColorPicker(view),
	fMessage(message)
{
	BBox* divider = new BBox(
		BRect(0, 0, 0, 0), B_EMPTY_STRING, B_FOLLOW_ALL_SIDES,
			B_FRAME_EVENTS, B_FANCY_BORDER);
	divider->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, 1));

	ColorContainersView* containersView = new ColorContainersView(layout);

	BButton* defaultButton = new BButton("ok button", "OK",
		new BMessage(MSG_DONE));
	SetDefaultButton(defaultButton);
	defaultButton->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT,
		B_ALIGN_VERTICAL_CENTER));
	BButton* cancelButton = new BButton("cancel button", "Cancel",
		new BMessage(MSG_CANCEL));

	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_SMALL_SPACING)
		.Add(fColorPicker)
		.Add(divider)
		.Add(containersView)
		.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING)
			.AddGlue()
			.Add(cancelButton)
			.Add(defaultButton)
			.End()
		.SetInsets(B_USE_DEFAULT_SPACING)
		.End();

	if (message != NULL) {
		// set the window title based on the client
		const char* title;
		if (message->FindString(kTargetName, &title) == B_OK) {
			BString newTitle;
			newTitle << "Select \"" << title << "\" color";
			SetTitle(newTitle.String());
		}

		// Move window under the mouse cursor
		BPoint where;
		if (message->FindPoint(kInvokePoint, &where) == B_OK)
			MoveTo(where + BPoint(30, 0));

		// set the initial color value
		const rgb_color *color;
		ssize_t size;
		if (message && message->FindData(kInitialValue, B_RGB_COLOR_TYPE,
				reinterpret_cast<const void **>(&color), &size) == B_OK) {
			fInitialColor = *color;
			fColorPicker->SetColor(fInitialColor);
		}

		// save the address of of the client
		BMessenger target;
		if (message->FindMessenger(kClientAddress, &target) == B_OK) {
			fTarget = target;

			// let the client know we are ready to serve it
			BMessage reply(kOpenConnection);
			reply.AddMessenger(kServerAddress, BMessenger(this));
			reply.AddInt32(kProvidedValues, B_RGB_COLOR_TYPE);
				// and that we can supply color values
	
			fTarget.SendMessage(&reply);
		}
	}
}


ColorPickerPanel::~ColorPickerPanel()
{
	fTarget.SendMessage(kServerQuitting);
}


void
ColorPickerPanel::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kActivateWindow:
			Activate();
			break;

		case kColorChanged:
		case kColorDropped:
		{
			// inform the target that the color has changed
			message->what = B_VALUE_CHANGED;
			fTarget.SendMessage(message);
			break;
		}

		case B_VALUE_CHANGED:
		{
			// client color changed without our intervention,
			// sync up
			rgb_color* color;
			ssize_t size;
			if (message->FindData("be:value", B_RGB_COLOR_TYPE,
					(const void **)(&color), &size) == B_OK) {
				fColorPicker->SetColor(*color);
			}
			break;
		}

		case MSG_CANCEL:
			Cancel();
			break;

		case MSG_DONE:
			Done();
			break;

		case kCloseConnection:
			be_app->PostMessage(B_QUIT_REQUESTED);
			break;

		default:
			BWindow::MessageReceived(message);
			break;
	}
}


bool 
ColorPickerPanel::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
		// when window closes, quit the app
	return true;
}


// #pragma mark -


void
ColorPickerPanel::Cancel()
{
	// reset color back to initial color and quit
	BMessage* message = new BMessage(B_VALUE_CHANGED);
	message->AddData("be:value", B_RGB_COLOR_TYPE, &fInitialColor,
		sizeof(fInitialColor));
	fTarget.SendMessage(message);
	delete message;
	fTarget.SendMessage(B_CANCEL);
	be_app->PostMessage(B_QUIT_REQUESTED);
}


void
ColorPickerPanel::Done()
{
	fTarget.SendMessage(kApplyValue);
	be_app->PostMessage(B_QUIT_REQUESTED);
}
