/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * This file may be used under the terms of the Be Sample Code License.
 */


#include "ColoredPencilColorPicker.h"

#include <Alignment.h>
#include <Bitmap.h>
#include <ControlLook.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <Rect.h>
#include <SpaceLayoutItem.h>

#include "ColoredPencil.h"
#include "SelectedColoredPencil.h"


ColoredPencilColorPicker::ColoredPencilColorPicker(rgb_color color)
	:
	ColorPickerView(),
	fColor(color)
{
	fSelectedColor = new SelectedColoredPencil(color);

	// add a bunch of colored pencils
	for (int32 i = 0; i < kMaxColoredPencilCount; i++)
		fColoredPencilList[i] = new ColoredPencil;

	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.Add(fSelectedColor)
		.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
		.AddGroup(B_VERTICAL, 0)
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fColoredPencilList[0])
				.Add(fColoredPencilList[1])
				.Add(fColoredPencilList[2])
				.Add(fColoredPencilList[3])
				.Add(fColoredPencilList[4])
				.Add(fColoredPencilList[5])
				.Add(fColoredPencilList[6])
				.Add(fColoredPencilList[7])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fColoredPencilList[8])
				.Add(fColoredPencilList[9])
				.Add(fColoredPencilList[10])
				.Add(fColoredPencilList[11])
				.Add(fColoredPencilList[12])
				.Add(fColoredPencilList[13])
				.Add(fColoredPencilList[14])
				.Add(fColoredPencilList[15])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fColoredPencilList[16])
				.Add(fColoredPencilList[17])
				.Add(fColoredPencilList[18])
				.Add(fColoredPencilList[19])
				.Add(fColoredPencilList[20])
				.Add(fColoredPencilList[21])
				.Add(fColoredPencilList[22])
				.Add(fColoredPencilList[23])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fColoredPencilList[24])
				.Add(fColoredPencilList[25])
				.Add(fColoredPencilList[26])
				.Add(fColoredPencilList[27])
				.Add(fColoredPencilList[28])
				.Add(fColoredPencilList[29])
				.Add(fColoredPencilList[30])
				.Add(fColoredPencilList[31])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fColoredPencilList[32])
				.Add(fColoredPencilList[33])
				.Add(fColoredPencilList[34])
				.Add(fColoredPencilList[35])
				.Add(fColoredPencilList[36])
				.Add(fColoredPencilList[37])
				.Add(fColoredPencilList[38])
				.Add(fColoredPencilList[39])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fColoredPencilList[40])
				.Add(fColoredPencilList[41])
				.Add(fColoredPencilList[42])
				.Add(fColoredPencilList[43])
				.Add(fColoredPencilList[44])
				.Add(fColoredPencilList[45])
				.Add(fColoredPencilList[46])
				.Add(fColoredPencilList[47])
			.End()
		.End();
}


ColoredPencilColorPicker::~ColoredPencilColorPicker()
{
}


void
ColoredPencilColorPicker::AttachedToWindow()
{
	fSelectedColor->SetTarget(this);
	for (int32 i = 0; i < kMaxColoredPencilCount; i++)
		fColoredPencilList[i]->SetTarget(this);

	SetColor(fColor);

	fColoredPencilList[0]->SetColor(make_color(128, 0, 0));
	fColoredPencilList[1]->SetColor(make_color(128, 128, 0));
	fColoredPencilList[2]->SetColor(make_color(0, 128, 0));
	fColoredPencilList[3]->SetColor(make_color(0, 128, 128));
	fColoredPencilList[4]->SetColor(make_color(0, 0, 128));
	fColoredPencilList[5]->SetColor(make_color(128, 0, 128));
	fColoredPencilList[6]->SetColor(make_color(119, 119, 119));
	fColoredPencilList[7]->SetColor(make_color(128, 128, 128));

	fColoredPencilList[8]->SetColor(make_color(128, 64, 0));
	fColoredPencilList[9]->SetColor(make_color(64, 128, 0));
	fColoredPencilList[10]->SetColor(make_color(0, 128, 64));
	fColoredPencilList[11]->SetColor(make_color(0, 64, 128));
	fColoredPencilList[12]->SetColor(make_color(64, 0, 128));
	fColoredPencilList[13]->SetColor(make_color(128, 0, 64));
	fColoredPencilList[14]->SetColor(make_color(95, 95, 95));
	fColoredPencilList[15]->SetColor(make_color(150, 150, 150));

	fColoredPencilList[16]->SetColor(make_color(255, 0, 0));
	fColoredPencilList[17]->SetColor(make_color(255, 255, 0));
	fColoredPencilList[18]->SetColor(make_color(0, 255, 0));
	fColoredPencilList[19]->SetColor(make_color(0, 255, 255));
	fColoredPencilList[20]->SetColor(make_color(0, 0, 255));
	fColoredPencilList[21]->SetColor(make_color(255, 0, 255));
	fColoredPencilList[22]->SetColor(make_color(77, 77, 77));
	fColoredPencilList[23]->SetColor(make_color(178, 178, 178));

	fColoredPencilList[24]->SetColor(make_color(255, 128, 0));
	fColoredPencilList[25]->SetColor(make_color(128, 255, 0));
	fColoredPencilList[26]->SetColor(make_color(0, 255, 128));
	fColoredPencilList[27]->SetColor(make_color(0, 128, 255));
	fColoredPencilList[28]->SetColor(make_color(128, 0, 255));
	fColoredPencilList[29]->SetColor(make_color(255, 0, 128));
	fColoredPencilList[30]->SetColor(make_color(41, 41, 41));
	fColoredPencilList[31]->SetColor(make_color(192, 192, 192));

	fColoredPencilList[32]->SetColor(make_color(255, 102, 102));
	fColoredPencilList[33]->SetColor(make_color(255, 255, 102));
	fColoredPencilList[34]->SetColor(make_color(102, 255, 102));
	fColoredPencilList[35]->SetColor(make_color(102, 255, 255));
	fColoredPencilList[36]->SetColor(make_color(102, 102, 255));
	fColoredPencilList[37]->SetColor(make_color(255, 102, 255));
	fColoredPencilList[38]->SetColor(make_color(28, 28, 28));
	fColoredPencilList[39]->SetColor(make_color(221, 221, 221));

	fColoredPencilList[40]->SetColor(make_color(255, 204, 102));
	fColoredPencilList[41]->SetColor(make_color(204, 255, 102));
	fColoredPencilList[42]->SetColor(make_color(102, 255, 204));
	fColoredPencilList[43]->SetColor(make_color(102, 204, 255));
	fColoredPencilList[44]->SetColor(make_color(204, 102, 255));
	fColoredPencilList[45]->SetColor(make_color(255, 102, 204));
	fColoredPencilList[46]->SetColor(make_color(0, 0, 0));
	fColoredPencilList[47]->SetColor(make_color(255, 255, 255));

	for (int32 i = 0; i < kMaxColoredPencilCount; i++)
		fColoredPencilList[i]->Invalidate();
}


void
ColoredPencilColorPicker::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kColorChanged:
		{
			char *nameFound;
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

			// forward message onto window
			BMessage* forward = new BMessage(kColorChanged);
			forward->AddInt64("when", (int64)system_time());
			forward->AddData("be:value", B_RGB_COLOR_TYPE, &fColor,
				sizeof(fColor));
			Window()->PostMessage(forward);
			delete forward;

			break;
		}

		default:
			BView::MessageReceived(message);
	}
}


void
ColoredPencilColorPicker::SetColor(rgb_color color)
{
	fColor = color;
	if (fSelectedColor != NULL) {
		fSelectedColor->SetColor(color);
		fSelectedColor->Invalidate(fSelectedColor->Bounds());
	}
}
