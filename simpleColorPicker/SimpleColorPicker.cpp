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
#include <Window.h>

#include "ColorPreview.h"


const int32 kColorChanged = 'clch';
const int32 kColorDropped = 'PSTE';


SimpleColorPicker::SimpleColorPicker(rgb_color color)
	:
	ColorPickerView(color),
	fColor(color)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fColorPreview = new ColorPreview(BRect(0, 0, 50, 50), "ColorPreview", "",
		new BMessage(kColorDropped));
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
	fColorPreview->SetTarget(this);
	SetColor(fColor);
}


void
SimpleColorPicker::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kColorChanged:
		{
			// Received from the BColorControl when its color changes
			fColor = fColorControl->ValueAsColor();
			fColor.alpha = 255;
			fColorPreview->SetColor(fColor);
			BMessage* forward = new BMessage(kColorChanged);
			forward->AddInt64("when", (int64)system_time());
			forward->AddData("be:value", B_RGB_COLOR_TYPE, &fColor,
				sizeof(fColor));
			Window()->PostMessage(forward);
			delete forward;
			break;
		}

		case kColorDropped:
		{
			char* nameFound;
			type_code typeFound;
			if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
					!= B_OK) {
				BView::MessageReceived(message);
				return;
			}

			rgb_color* color;
			ssize_t numBytes;
			if (message->FindData(nameFound, typeFound, (const void **)&color,
					&numBytes) == B_OK) {
				SetColor(*color);
				Window()->PostMessage(message);
			}
		}

		default:
			BView::MessageReceived(message);
	}
}


void
SimpleColorPicker::SetColor(rgb_color color)
{
	fColor = color;
	fColorPreview->SetColor(color);
	fColorControl->SetValue(color);
}
