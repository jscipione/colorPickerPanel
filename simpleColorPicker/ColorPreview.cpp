/*
 * Copyright 2009-2012 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *		Werner Freytag <freytag@gmx.de>
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */


#include "ColorPreview.h"

#include <Application.h>
#include <Bitmap.h>
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

	SetHighColor(fColor);
	FillRect(bounds);
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
