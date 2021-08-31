/*
 * Copyright 2001-2008 Werner Freytag.
 * Copyright 2009-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *		Werner Freytag, freytag@gmx.de
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColorPreview.h"

#include <stdio.h>

#include <algorithm>
#include <iostream>

#include <Application.h>
#include <Bitmap.h>
#include <ControlLook.h>
#include <Message.h>
#include <MessageRunner.h>
#include <Resources.h>
#include <String.h>
#include <Window.h>


static const int32 kMsgMessageRunner = 'MsgR';


ColorPreview::ColorPreview(BRect frame, const char* name, const char* label,
	BMessage* message, uint32 resizingMode, uint32 flags)
	:
	BControl(frame, name, label, message, resizingMode, flags),
	fColor(make_color(255, 0, 0)),
	fMessageRunner(NULL)
{
}


ColorPreview::~ColorPreview()
{
}


void
ColorPreview::Draw(BRect updateRect)
{
	rgb_color color = fColor;

	rgb_color background = ui_color(B_PANEL_BACKGROUND_COLOR);
	rgb_color shadow = tint_color(background, B_DARKEN_1_TINT);
	rgb_color darkShadow = tint_color(background, B_DARKEN_3_TINT);
	rgb_color light = tint_color(background, B_LIGHTEN_MAX_TINT);

	BRect bounds(Bounds());

	BeginLineArray(4);
	AddLine(BPoint(bounds.left, bounds.bottom),
	BPoint(bounds.left, bounds.top), shadow);
	AddLine(BPoint(bounds.left + 1.0, bounds.top),
	BPoint(bounds.right, bounds.top), shadow);
	AddLine(BPoint(bounds.right, bounds.top + 1.0),
	BPoint(bounds.right, bounds.bottom), light);
	AddLine(BPoint(bounds.right - 1.0, bounds.bottom),
	BPoint(bounds.left + 1.0, bounds.bottom), light);
	EndLineArray();
	bounds.InsetBy(1.0, 1.0);

	BeginLineArray(4);
	AddLine(BPoint(bounds.left, bounds.bottom),
	BPoint(bounds.left, bounds.top), darkShadow);
	AddLine(BPoint(bounds.left + 1.0, bounds.top),
	BPoint(bounds.right, bounds.top), darkShadow);
	AddLine(BPoint(bounds.right, bounds.top + 1.0),
	BPoint(bounds.right, bounds.bottom), background);
	AddLine(BPoint(bounds.right - 1.0, bounds.bottom),
	BPoint(bounds.left + 1.0, bounds.bottom), background);
	EndLineArray();
	bounds.InsetBy(1.0, 1.0);

	SetHighColor(color);
	FillRect(bounds);
}


void
ColorPreview::MessageReceived(BMessage* message)
{
	if (message->WasDropped()) {
		Invoke(message);
	} else if (message->what == kMsgMessageRunner) {
		BPoint where;
		uint32 buttons;
		GetMouse(&where, &buttons);

		_DragColor(where);
	} else
		BControl::MessageReceived(message);
}


void
ColorPreview::MouseDown(BPoint where)
{
	fMessageRunner = new BMessageRunner(this, new BMessage(kMsgMessageRunner),
		300000, 1);

	BControl::MouseDown(where);
}


void
ColorPreview::MouseMoved(BPoint where, uint32 transit, const BMessage* message)
{
	if (fMessageRunner != NULL)
		_DragColor(where);

	BControl::MouseMoved(where, transit, message);
}


void
ColorPreview::MouseUp(BPoint where)
{
	delete fMessageRunner;
	fMessageRunner = NULL;

	BControl::MouseUp(where);
}



rgb_color
ColorPreview::Color() const
{
	return fColor;
}


void
ColorPreview::SetColor(rgb_color color)
{
	color.alpha = 255;
	fColor = color;
	if (Window())
		Draw(Bounds());
}


void
ColorPreview::_DragColor(BPoint where)
{
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
