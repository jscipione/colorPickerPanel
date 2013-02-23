/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */

#include "SimpleColorPicker.h"

#include <Alignment.h>
#include <ColorControl.h>
#include <LayoutBuilder.h>
#include <Rect.h>
#include <SpaceLayoutItem.h>

#include "ColorPreview.h"


const int32 kColorDropped = 'cldp';
const int32 kColorChanged = 'clch';


SimpleColorPicker::SimpleColorPicker(rgb_color color)
	:
	BView("SimpleColorPicker", 0),
	fColor(color)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fColorPreview = new ColorPreview(BRect(0, 0, 50, 50));
	fColorPreview->SetExplicitAlignment(BAlignment(B_ALIGN_HORIZONTAL_CENTER,
		B_ALIGN_BOTTOM));

	fColorControl = new BColorControl(B_ORIGIN, B_CELLS_32x8,
		8.0, "ColorPicker", new BMessage(kColorChanged));

	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.Add(fColorPreview)
		.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
		.Add(fColorControl)
		.End();
}


SimpleColorPicker::~SimpleColorPicker()
{
}


void
SimpleColorPicker::AttachedToWindow()
{
	fColorControl->SetTarget(this);
	SetColor(fColor);
}


void
SimpleColorPicker::MessageReceived(BMessage* message)
{
	char* nameFound;
	type_code typeFound;

	if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
			!= B_OK) {
		switch (message->what) {
			case kColorChanged:
			{
				// Received from the color fPicker when its color changes
				rgb_color color = fColorControl->ValueAsColor();
				SetColor(color);
				break;
			}

			default:
				BView::MessageReceived(message);
		}
		return;
	}

	rgb_color* color;
	ssize_t numBytes;
	message->FindData(nameFound, typeFound, (const void **)&color,
		&numBytes);
	SetColor(*color);
}


void
SimpleColorPicker::SetColor(rgb_color color)
{
	fColor = color;
	fColorPreview->SetColor(color);
	fColorControl->SetValue(color);
}
