/*
 * Copyright 2009-2013 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *		Werner Freytag <freytag@gmx.de>
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */


#include "ColorContainer.h"

#include <stdio.h>

#include <algorithm>
#include <iostream>

#include <Application.h>
#include <Bitmap.h>
#include <Message.h>
#include <MessageRunner.h>
#include <Resources.h>
#include <Size.h>
#include <String.h>
#include <Window.h>


static const int32 kMsgMessageRunner = 'MsgR';


ColorContainer::ColorContainer(BRect frame)
	:
	BView(frame, "ColorContainer", B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW),
	fMouseOffset(BPoint(0, 0)),
	fMessageRunner(0),
	fGotFirstClick(false)
{
	SetExplicitMinSize(BSize(frame.Width(), frame.Height()));
	SetExplicitMaxSize(BSize(frame.Width(), frame.Height()));
}


ColorContainer::~ColorContainer()
{
}


void
ColorContainer::Draw(BRect updateRect)
{
	rgb_color border = (rgb_color){ 184, 184, 184 };
	rgb_color white = (rgb_color){ 255, 255, 255 };

	SetHighColor(border);
	StrokeRect(Bounds());
	SetHighColor(white);
	StrokeRect(Bounds().InsetByCopy(1.0, 1.0));

	SetHighColor(fColor);
	FillRect(Bounds().InsetByCopy(2.0, 2.0));
}


void
ColorContainer::MessageReceived(BMessage* message)
{
	if (message->WasDropped()) {
		char* nameFound;
		type_code typeFound;
		if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
				!= B_OK) {
			BView::MessageReceived(message);
			return;
		}

		rgb_color* color;
		ssize_t numBytes;
		message->FindData(nameFound, typeFound, (const void **)&color,
			&numBytes);
		SetColor(*color);
	} else if (message->what == kMsgMessageRunner) {
		BPoint where;
		uint32 buttons;
		GetMouse(&where, &buttons);

		_DragColor(where);
	}

	BView::MessageReceived(message);
}


void
ColorContainer::MouseDown(BPoint where)
{
	Window()->Activate();

	long clicks = Window()->CurrentMessage()->FindInt32("clicks");

	if (clicks == 2 && fGotFirstClick) {
		BMessage message;
		message.AddData("RGBColor", B_RGB_COLOR_TYPE, &fColor, sizeof(fColor));

		BHandler* colorpreview;
		if ((colorpreview = (BHandler*)Window()->FindView("color preview")))
			Window()->PostMessage(&message, colorpreview);
	} else {
		fGotFirstClick = (clicks == 1);

		bigtime_t doubleClickSpeed;
		if (get_click_speed(&doubleClickSpeed) != B_OK)
			doubleClickSpeed = 300000;

		fMessageRunner = new BMessageRunner(this,
			new BMessage(kMsgMessageRunner), doubleClickSpeed, 1);

		SetMouseEventMask(B_POINTER_EVENTS,
			B_SUSPEND_VIEW_FOCUS | B_LOCK_WINDOW_FOCUS);
	}

	BView::MouseDown(where);
}


void
ColorContainer::MouseMoved(BPoint where, uint32 transit,
	const BMessage* message)
{
	if (fMessageRunner != NULL)
		_DragColor(where);

	BView::MouseMoved(where, transit, message);
}


void
ColorContainer::MouseUp(BPoint where)
{
	delete fMessageRunner;
	fMessageRunner = NULL;

	BView::MouseUp(where);
}


rgb_color
ColorContainer::GetColor() const
{
	return fColor;
}


void
ColorContainer::SetColor(long int c)
{
	rgb_color color;
	color.red   = (c >> 16) & 255;
	color.green = (c >> 8) & 255;
	color.blue  = c & 255;
	SetColor(color);
}


void
ColorContainer::SetColor(rgb_color color)
{
	color.alpha = 255;
	fColor = color;
	if (Window())
		Draw(Bounds());
}


// #pragma mark -


void
ColorContainer::_DragColor(BPoint where)
{
	fGotFirstClick = false;

	BString hexStr;
	hexStr.SetToFormat("#%.2X%.2X%.2X", fColor.red, fColor.green, fColor.blue);

	BMessage message(B_PASTE);
	message.AddData("text/plain", B_MIME_TYPE, hexStr.String(),
		hexStr.Length());
	message.AddData("RGBColor", B_RGB_COLOR_TYPE, &fColor, sizeof(fColor));

	BRect rect(0.0f, 0.0f, 16.0f, 16.0f);

	BBitmap* bitmap = new BBitmap(rect, B_RGB32, true);
	if (bitmap->Lock()) {
		BView* view = new BView(rect, "", B_FOLLOW_NONE, B_WILL_DRAW);
		bitmap->AddChild(view);

		view->SetHighColor(B_TRANSPARENT_COLOR);
		view->FillRect(view->Bounds());

		++rect.top;
		++rect.left;

		view->SetHighColor(0, 0, 0, 100);
		view->FillRect(rect);
		rect.OffsetBy(-1.0f, -1.0f);

		view->SetHighColor(std::min(255, (int)(1.2 * fColor.red + 40)),
			std::min(255, (int)(1.2 * fColor.green + 40)),
			std::min(255, (int)(1.2 * fColor.blue + 40)));
		view->StrokeRect(rect);

		++rect.left;
		++rect.top;

		view->SetHighColor((int32)(0.8 * fColor.red),
			(int32)(0.8 * fColor.green),
			(int32)(0.8 * fColor.blue));
		view->StrokeRect(rect);

		--rect.right;
		--rect.bottom;

		view->SetHighColor(fColor.red, fColor.green, fColor.blue);
		view->FillRect(rect);
		view->Sync();

		bitmap->Unlock();
	}

	DragMessage(&message, bitmap, B_OP_ALPHA, BPoint(14.0f, 14.0f));

	MouseUp(where);
}
