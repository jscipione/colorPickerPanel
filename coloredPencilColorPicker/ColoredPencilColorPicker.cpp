/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.
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
	BView("ColoredPencilColorPicker", 0),
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

	fColoredPencilList[0]->SetColor((rgb_color) { 128, 0, 0 });
	fColoredPencilList[1]->SetColor((rgb_color) { 128, 128, 0 });
	fColoredPencilList[2]->SetColor((rgb_color) { 0, 128, 0 });
	fColoredPencilList[3]->SetColor((rgb_color) { 0, 128, 128 });
	fColoredPencilList[4]->SetColor((rgb_color) { 0, 0, 128 });
	fColoredPencilList[5]->SetColor((rgb_color) { 128, 0, 128 });
	fColoredPencilList[6]->SetColor((rgb_color) { 127, 127, 127 });
	fColoredPencilList[7]->SetColor((rgb_color) { 128, 128, 128 });

	fColoredPencilList[8]->SetColor((rgb_color) { 128, 64, 0 });
	fColoredPencilList[9]->SetColor((rgb_color) { 64, 128, 0 });
	fColoredPencilList[10]->SetColor((rgb_color) { 0, 128, 64 });
	fColoredPencilList[11]->SetColor((rgb_color) { 0, 64, 128 });
	fColoredPencilList[12]->SetColor((rgb_color) { 64, 0, 128 });
	fColoredPencilList[13]->SetColor((rgb_color) { 128, 0, 64 });
	fColoredPencilList[14]->SetColor((rgb_color) { 102, 102, 102 });
	fColoredPencilList[15]->SetColor((rgb_color) { 153, 153, 153 });

	fColoredPencilList[16]->SetColor((rgb_color) { 255, 0, 0 });
	fColoredPencilList[17]->SetColor((rgb_color) { 255, 255, 0 });
	fColoredPencilList[18]->SetColor((rgb_color) { 0, 255, 0 });
	fColoredPencilList[19]->SetColor((rgb_color) { 0, 255, 255 });
	fColoredPencilList[20]->SetColor((rgb_color) { 0, 0, 255 });
	fColoredPencilList[21]->SetColor((rgb_color) { 255, 0, 255 });
	fColoredPencilList[22]->SetColor((rgb_color) { 76, 76, 76 });
	fColoredPencilList[23]->SetColor((rgb_color) { 179, 179, 179 });

	fColoredPencilList[24]->SetColor((rgb_color) { 255, 128, 0 });
	fColoredPencilList[25]->SetColor((rgb_color) { 128, 255, 0 });
	fColoredPencilList[26]->SetColor((rgb_color) { 0, 255, 128 });
	fColoredPencilList[27]->SetColor((rgb_color) { 0, 128, 255 });
	fColoredPencilList[28]->SetColor((rgb_color) { 128, 0, 255 });
	fColoredPencilList[29]->SetColor((rgb_color) { 255, 0, 128 });
	fColoredPencilList[30]->SetColor((rgb_color) { 51, 51, 51 });
	fColoredPencilList[31]->SetColor((rgb_color) { 204, 204, 204 });

	fColoredPencilList[32]->SetColor((rgb_color) { 255, 102, 102 });
	fColoredPencilList[33]->SetColor((rgb_color) { 255, 255, 102 });
	fColoredPencilList[34]->SetColor((rgb_color) { 102, 255, 102 });
	fColoredPencilList[35]->SetColor((rgb_color) { 102, 255, 255 });
	fColoredPencilList[36]->SetColor((rgb_color) { 102, 102, 255 });
	fColoredPencilList[37]->SetColor((rgb_color) { 255, 102, 255 });
	fColoredPencilList[38]->SetColor((rgb_color) { 25, 25, 25 });
	fColoredPencilList[39]->SetColor((rgb_color) { 230, 230, 230 });

	fColoredPencilList[40]->SetColor((rgb_color) { 255, 204, 102 });
	fColoredPencilList[41]->SetColor((rgb_color) { 204, 255, 102 });
	fColoredPencilList[42]->SetColor((rgb_color) { 102, 255, 204 });
	fColoredPencilList[43]->SetColor((rgb_color) { 102, 204, 255 });
	fColoredPencilList[44]->SetColor((rgb_color) { 204, 102, 255 });
	fColoredPencilList[45]->SetColor((rgb_color) { 255, 102, 204 });
	fColoredPencilList[46]->SetColor((rgb_color) { 0, 0, 0 });
	fColoredPencilList[47]->SetColor((rgb_color) { 255, 255, 255 });

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