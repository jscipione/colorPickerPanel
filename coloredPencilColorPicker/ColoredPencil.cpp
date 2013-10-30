/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColoredPencil.h"

#include <Bitmap.h>
#include <InterfaceDefs.h>
#include <Message.h>
#include <Rect.h>


const color_space kColoredPencilColorSpace = B_CMAP8;
const int32 kColoredPencilWidth = 20;
const int32 kColoredPencilHeight = 45;


const unsigned char kColoredPencilBits[] = {
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x07,0x5b,0xff,0xff,0xff,0xff,0xff,0xff,0x5b,0x07,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,
	0x1b,0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,0x1b,
	0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,
	0x1b,0x07,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x07,0x1b,
	0x1b,0x07,0x5b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5b,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b
};


ColoredPencil::ColoredPencil()
	:
	BControl(BRect(0, 0, kColoredPencilWidth - 1, kColoredPencilHeight - 1),
		"ColoredPencil", "", new BMessage(kColorChanged), B_FOLLOW_NONE,
		B_WILL_DRAW),
	fColor((rgb_color) { 0, 0, 0 }),
	fIcon(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}


ColoredPencil::ColoredPencil(rgb_color color)
	:
	BControl(BRect(0, 0, kColoredPencilWidth - 1, kColoredPencilHeight - 1),
		"ColoredPencil", "", new BMessage(kColorChanged), B_FOLLOW_NONE,
		B_WILL_DRAW),
	fColor(color),
	fIcon(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}


ColoredPencil::~ColoredPencil()
{
	delete fIcon;
}


void
ColoredPencil::AttachedToWindow()
{
	fIcon = new BBitmap(Bounds(), kColoredPencilColorSpace, false, false);
	fIcon->SetBits(kColoredPencilBits,
		kColoredPencilWidth * kColoredPencilHeight, 0,
		kColoredPencilColorSpace);
}


void
ColoredPencil::Draw(BRect updateRect)
{
	BRect frame(Bounds());

	PushState();
	SetHighColor(fColor);
	SetLowColor(ViewColor());
	FillRect(frame);
	if (fIcon != NULL) {
		SetDrawingMode(B_OP_OVER);
		DrawBitmapAsync(fIcon, frame);
	}
	PopState();
}


status_t
ColoredPencil::Invoke(BMessage* message)
{
	if (message == NULL)
		message = Message();

	message->RemoveName("selected_color");
	message->AddData("selected_color", B_RGB_COLOR_TYPE, &fColor,
		sizeof(fColor));

	return BControl::Invoke(message);
}


void
ColoredPencil::MouseDown(BPoint where)
{
	Invoke();
	BControl::MouseDown(where);
}


rgb_color
ColoredPencil::Color() const
{
	return fColor;
}


void
ColoredPencil::SetColor(rgb_color color)
{
	color.alpha = 255;
	fColor = color;
	if (Window())
		Invalidate(Bounds());
}
