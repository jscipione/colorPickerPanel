/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2013 Haiku, Inc. All rights reserved. 
 * This file may be used under the terms of the Be Sample Code License.
 */


#include "CrayonColorPicker.h"

#include <Alignment.h>
#include <Bitmap.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <Rect.h>
#include <SpaceLayoutItem.h>

#include "Crayon.h"
#include "SelectedCrayon.h"


CrayonColorPicker::CrayonColorPicker(rgb_color color)
	:
	ColorPicker(),
	fColor(color)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fSelectedColor = new SelectedCrayon(color);

	// add a bunch of crayons
	for (int32 i = 0; i < kMaxCrayonCount; i++)
		fCrayonList[i] = new Crayon();

	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.AddGlue()
		.Add(fSelectedColor)
		.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
		.AddGroup(B_VERTICAL, 1)
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fCrayonList[0])
				.Add(fCrayonList[1])
				.Add(fCrayonList[2])
				.Add(fCrayonList[3])
				.Add(fCrayonList[4])
				.Add(fCrayonList[5])
				.Add(fCrayonList[6])
				.Add(fCrayonList[7])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
				.Add(fCrayonList[8])
				.Add(fCrayonList[9])
				.Add(fCrayonList[10])
				.Add(fCrayonList[11])
				.Add(fCrayonList[12])
				.Add(fCrayonList[13])
				.Add(fCrayonList[14])
				.Add(fCrayonList[15])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fCrayonList[16])
				.Add(fCrayonList[17])
				.Add(fCrayonList[18])
				.Add(fCrayonList[19])
				.Add(fCrayonList[20])
				.Add(fCrayonList[21])
				.Add(fCrayonList[22])
				.Add(fCrayonList[23])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
				.Add(fCrayonList[24])
				.Add(fCrayonList[25])
				.Add(fCrayonList[26])
				.Add(fCrayonList[27])
				.Add(fCrayonList[28])
				.Add(fCrayonList[29])
				.Add(fCrayonList[30])
				.Add(fCrayonList[31])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fCrayonList[32])
				.Add(fCrayonList[33])
				.Add(fCrayonList[34])
				.Add(fCrayonList[35])
				.Add(fCrayonList[36])
				.Add(fCrayonList[37])
				.Add(fCrayonList[38])
				.Add(fCrayonList[39])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(
					B_USE_SMALL_SPACING))
				.Add(fCrayonList[40])
				.Add(fCrayonList[41])
				.Add(fCrayonList[42])
				.Add(fCrayonList[43])
				.Add(fCrayonList[44])
				.Add(fCrayonList[45])
				.Add(fCrayonList[46])
				.Add(fCrayonList[47])
			.End()
		.End()
		.AddGlue()
	.End();
}


CrayonColorPicker::~CrayonColorPicker()
{
}


void
CrayonColorPicker::AttachedToWindow()
{
	fSelectedColor->SetTarget(this);
	for (int32 i = 0; i < kMaxCrayonCount; i++)
		fCrayonList[i]->SetTarget(this);

	SetColor(fColor);

	fCrayonList[0]->SetColor(make_color(128, 0, 0));
	fCrayonList[1]->SetColor(make_color(128, 128, 0));
	fCrayonList[2]->SetColor(make_color(0, 128, 0));
	fCrayonList[3]->SetColor(make_color(0, 128, 128));
	fCrayonList[4]->SetColor(make_color(0, 0, 128));
	fCrayonList[5]->SetColor(make_color(128, 0, 128));
	fCrayonList[6]->SetColor(make_color(119, 119, 119));
	fCrayonList[7]->SetColor(make_color(128, 128, 128));

	fCrayonList[8]->SetColor(make_color(128, 64, 0));
	fCrayonList[9]->SetColor(make_color(64, 128, 0));
	fCrayonList[10]->SetColor(make_color(0, 128, 64));
	fCrayonList[11]->SetColor(make_color(0, 64, 128));
	fCrayonList[12]->SetColor(make_color(64, 0, 128));
	fCrayonList[13]->SetColor(make_color(128, 0, 64));
	fCrayonList[14]->SetColor(make_color(95, 95, 95));
	fCrayonList[15]->SetColor(make_color(150, 150, 150));

	fCrayonList[16]->SetColor(make_color(255, 0, 0));
	fCrayonList[17]->SetColor(make_color(255, 255, 0));
	fCrayonList[18]->SetColor(make_color(0, 255, 0));
	fCrayonList[19]->SetColor(make_color(0, 255, 255));
	fCrayonList[20]->SetColor(make_color(0, 0, 255));
	fCrayonList[21]->SetColor(make_color(255, 0, 255));
	fCrayonList[22]->SetColor(make_color(77, 77, 77));
	fCrayonList[23]->SetColor(make_color(178, 178, 178));

	fCrayonList[24]->SetColor(make_color(255, 128, 0));
	fCrayonList[25]->SetColor(make_color(128, 255, 0));
	fCrayonList[26]->SetColor(make_color(0, 255, 128));
	fCrayonList[27]->SetColor(make_color(0, 128, 255));
	fCrayonList[28]->SetColor(make_color(128, 0, 255));
	fCrayonList[29]->SetColor(make_color(255, 0, 128));
	fCrayonList[30]->SetColor(make_color(41, 41, 41));
	fCrayonList[31]->SetColor(make_color(192, 192, 192));

	fCrayonList[32]->SetColor(make_color(255, 102, 102));
	fCrayonList[33]->SetColor(make_color(255, 255, 102));
	fCrayonList[34]->SetColor(make_color(102, 255, 102));
	fCrayonList[35]->SetColor(make_color(102, 255, 255));
	fCrayonList[36]->SetColor(make_color(102, 102, 255));
	fCrayonList[37]->SetColor(make_color(255, 102, 255));
	fCrayonList[38]->SetColor(make_color(28, 28, 28));
	fCrayonList[39]->SetColor(make_color(221, 221, 221));

	fCrayonList[40]->SetColor(make_color(255, 204, 102));
	fCrayonList[41]->SetColor(make_color(204, 255, 102));
	fCrayonList[42]->SetColor(make_color(102, 255, 204));
	fCrayonList[43]->SetColor(make_color(102, 204, 255));
	fCrayonList[44]->SetColor(make_color(204, 102, 255));
	fCrayonList[45]->SetColor(make_color(255, 102, 204));
	fCrayonList[46]->SetColor(make_color(0, 0, 0));
	fCrayonList[47]->SetColor(make_color(255, 255, 255));

	for (int32 i = 0; i < kMaxCrayonCount; i++)
		fCrayonList[i]->Invalidate();
}


void
CrayonColorPicker::MessageReceived(BMessage* message)
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
CrayonColorPicker::SetColor(rgb_color color)
{
	fColor = color;
	if (fSelectedColor != NULL) {
		fSelectedColor->SetColor(color);
		fSelectedColor->Invalidate(fSelectedColor->Bounds());
	}
}
