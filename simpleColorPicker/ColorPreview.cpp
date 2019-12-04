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

#include <Application.h>
#include <Bitmap.h>
#include <ControlLook.h>
#include <iostream>
#include <MessageRunner.h>
#include <Resources.h>
#include <stdio.h>
#include <String.h>
#include <stdio.h>
#include <Window.h>


ColorPreview::ColorPreview(BRect frame, const char* name, const char* label,
	BMessage* message, uint32 resizingMode, uint32 flags)
	:
	BControl(frame, name, label, message, resizingMode, flags)
{
}


ColorPreview::~ColorPreview()
{
}


void
ColorPreview::Draw(BRect updateRect)
{
	BRect rect(Bounds());

	be_control_look->DrawTextControlBorder(this, rect, updateRect,
		ui_color(B_PANEL_BACKGROUND_COLOR));

	SetHighColor(fColor);
	FillRect(rect);
}


void
ColorPreview::MessageReceived(BMessage* message)
{
	if (message->WasDropped()) {
		Invoke(message);
	} else
		BControl::MessageReceived(message);
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
