/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus <superstippi@gmx.de>
 *		John Scipione <jscipione@gmail.com>
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


enum {
	MSG_CANCEL					= 'cncl',
	MSG_DONE					= 'done',
};


ColorPickerPanel::ColorPickerPanel(BRect frame, BView* colorPickerView,
	BWindow* window, BMessage* message, BHandler* target)
	:
	BWindow(frame, "Pick a color",
		B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
		B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_AUTO_UPDATE_SIZE_LIMITS
			| B_CLOSE_ON_ESCAPE),
	fColorPickerView(colorPickerView),
	fWindow(window),
	fMessage(message),
	fTarget(target)
{
	BBox* divider = new BBox(
		BRect(0, 0, 0, 0), B_EMPTY_STRING, B_FOLLOW_ALL_SIDES,
			B_FRAME_EVENTS, B_FANCY_BORDER);
	divider->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, 1));

	BButton* defaultButton = new BButton("ok button", "OK",
		new BMessage(MSG_DONE));
	SetDefaultButton(defaultButton);
	defaultButton->SetExplicitAlignment(BAlignment(B_ALIGN_RIGHT, B_ALIGN_VERTICAL_CENTER));
	BButton* cancelButton = new BButton("cancel button", "Cancel",
		new BMessage(MSG_CANCEL));

	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_SMALL_SPACING)
		.Add(fColorPickerView)
		.Add(divider)
		.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING)
			.AddGlue()
			.Add(cancelButton)
			.Add(defaultButton)
			.End()
		.SetInsets(B_USE_DEFAULT_SPACING)
		.End();
}


ColorPickerPanel::~ColorPickerPanel()
{
	delete fMessage;
}


void
ColorPickerPanel::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_CANCEL:
		case MSG_DONE:
		{
			BMessage msg('PSTE');
			BLooper* looper = fTarget ? fTarget->Looper() : be_app;
			if (fMessage)
				msg = *fMessage;
//			if (message->what == MSG_DONE)
//				store_color_in_message(&msg, fColorPickerView->Value());
//			msg.AddRect("panel frame", Frame());
//			msg.AddInt32("panel mode", fColorPickerView->Mode());
			msg.AddBool("begin", true);
			looper->PostMessage(&msg, fTarget);
			PostMessage(B_QUIT_REQUESTED);
			break;
		}

		default:
			BWindow::MessageReceived(message);
			break;
	}
}


// #pragma mark -


void
ColorPickerPanel::Cancel()
{
	PostMessage(MSG_CANCEL);
}


void
ColorPickerPanel::Done()
{
	PostMessage(MSG_DONE);
}


void
ColorPickerPanel::SetMessage(BMessage* message)
{
	delete fMessage;
	fMessage = message;
}


void
ColorPickerPanel::SetTarget(BHandler* target)
{
	fTarget = target;
}
