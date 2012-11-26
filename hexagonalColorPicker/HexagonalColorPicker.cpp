/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */

#include "HexagonalColorPicker.h"

#include <stdio.h>
#include <stdlib.h>

#include <Alignment.h>
#include <ControlLook.h>
#include <LayoutBuilder.h>
#include <Rect.h>
#include <Size.h>
#include <SpaceLayoutItem.h>

#include "Hexagon.h"


HexagonalColorPicker::HexagonalColorPicker(rgb_color color)
	:
	BView("HexagonalColorPicker", 0),
	fColor(color)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	for (int32 i = 0; i < kMaxHexagonCount; i++)
		fHexagonList[i] = new Hexagon();

	fHexTextControl = new BTextControl(NULL, "#", NULL, NULL);
	fHexTextControl->SetExplicitMaxSize(
		BSize(be_control_look->DefaultItemSpacing() * 8, B_SIZE_UNSET));
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_DEFAULT_SPACING)
		.AddGroup(B_VERTICAL, -kHexagonHeight / 3.0f)
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 3))
				.Add(fHexagonList[0])
				.Add(fHexagonList[1])
				.Add(fHexagonList[2])
				.Add(fHexagonList[3])
				.Add(fHexagonList[4])
				.Add(fHexagonList[5])
				.Add(fHexagonList[6])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 3))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 2.5)))
				.Add(fHexagonList[7])
				.Add(fHexagonList[8])
				.Add(fHexagonList[9])
				.Add(fHexagonList[10])
				.Add(fHexagonList[11])
				.Add(fHexagonList[12])
				.Add(fHexagonList[13])
				.Add(fHexagonList[14])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 2.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 2))
				.Add(fHexagonList[15])
				.Add(fHexagonList[16])
				.Add(fHexagonList[17])
				.Add(fHexagonList[18])
				.Add(fHexagonList[19])
				.Add(fHexagonList[20])
				.Add(fHexagonList[21])
				.Add(fHexagonList[22])
				.Add(fHexagonList[23])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 2))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 1.5)))
				.Add(fHexagonList[24])
				.Add(fHexagonList[25])
				.Add(fHexagonList[26])
				.Add(fHexagonList[27])
				.Add(fHexagonList[28])
				.Add(fHexagonList[29])
				.Add(fHexagonList[30])
				.Add(fHexagonList[31])
				.Add(fHexagonList[32])
				.Add(fHexagonList[33])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 1.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth))
				.Add(fHexagonList[34])
				.Add(fHexagonList[35])
				.Add(fHexagonList[36])
				.Add(fHexagonList[37])
				.Add(fHexagonList[38])
				.Add(fHexagonList[39])
				.Add(fHexagonList[40])
				.Add(fHexagonList[41])
				.Add(fHexagonList[42])
				.Add(fHexagonList[43])
				.Add(fHexagonList[44])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 0.5)))
				.Add(fHexagonList[45])
				.Add(fHexagonList[46])
				.Add(fHexagonList[47])
				.Add(fHexagonList[48])
				.Add(fHexagonList[49])
				.Add(fHexagonList[50])
				.Add(fHexagonList[51])
				.Add(fHexagonList[52])
				.Add(fHexagonList[53])
				.Add(fHexagonList[54])
				.Add(fHexagonList[55])
				.Add(fHexagonList[56])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 0.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fHexagonList[57])
				.Add(fHexagonList[58])
				.Add(fHexagonList[59])
				.Add(fHexagonList[60])
				.Add(fHexagonList[61])
				.Add(fHexagonList[62])
				.Add(fHexagonList[63])
				.Add(fHexagonList[64])
				.Add(fHexagonList[65])
				.Add(fHexagonList[66])
				.Add(fHexagonList[67])
				.Add(fHexagonList[68])
				.Add(fHexagonList[69])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 0.5)))
				.Add(fHexagonList[70])
				.Add(fHexagonList[71])
				.Add(fHexagonList[72])
				.Add(fHexagonList[73])
				.Add(fHexagonList[74])
				.Add(fHexagonList[75])
				.Add(fHexagonList[76])
				.Add(fHexagonList[77])
				.Add(fHexagonList[78])
				.Add(fHexagonList[79])
				.Add(fHexagonList[80])
				.Add(fHexagonList[81])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 0.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth))
				.Add(fHexagonList[82])
				.Add(fHexagonList[83])
				.Add(fHexagonList[84])
				.Add(fHexagonList[85])
				.Add(fHexagonList[86])
				.Add(fHexagonList[87])
				.Add(fHexagonList[88])
				.Add(fHexagonList[89])
				.Add(fHexagonList[90])
				.Add(fHexagonList[91])
				.Add(fHexagonList[92])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 1.5)))
				.Add(fHexagonList[93])
				.Add(fHexagonList[94])
				.Add(fHexagonList[95])
				.Add(fHexagonList[96])
				.Add(fHexagonList[97])
				.Add(fHexagonList[98])
				.Add(fHexagonList[99])
				.Add(fHexagonList[100])
				.Add(fHexagonList[101])
				.Add(fHexagonList[102])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 1.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 2))
				.Add(fHexagonList[103])
				.Add(fHexagonList[104])
				.Add(fHexagonList[105])
				.Add(fHexagonList[106])
				.Add(fHexagonList[107])
				.Add(fHexagonList[108])
				.Add(fHexagonList[109])
				.Add(fHexagonList[110])
				.Add(fHexagonList[111])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 2))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(floorf(kHexagonWidth * 2.5)))
				.Add(fHexagonList[112])
				.Add(fHexagonList[113])
				.Add(fHexagonList[114])
				.Add(fHexagonList[115])
				.Add(fHexagonList[116])
				.Add(fHexagonList[117])
				.Add(fHexagonList[118])
				.Add(fHexagonList[119])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(ceilf(kHexagonWidth * 2.5)))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 3))
				.Add(fHexagonList[120])
				.Add(fHexagonList[121])
				.Add(fHexagonList[122])
				.Add(fHexagonList[123])
				.Add(fHexagonList[124])
				.Add(fHexagonList[125])
				.Add(fHexagonList[126])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(kHexagonWidth * 3))
			.End()
		.End()
		.Add(fHexTextControl)
	.End();
}


HexagonalColorPicker::~HexagonalColorPicker()
{
}


void
HexagonalColorPicker::AttachedToWindow()
{
	for (int32 i = 0; i < kMaxHexagonCount; i++)
		fHexagonList[i]->SetTarget(this);

	fHexagonList[0]->SetColor((rgb_color) { 0, 51, 102 });
	fHexagonList[1]->SetColor((rgb_color) { 51, 102, 153 });
	fHexagonList[2]->SetColor((rgb_color) { 51, 102, 204 });
	fHexagonList[3]->SetColor((rgb_color) { 0, 51, 153 });
	fHexagonList[4]->SetColor((rgb_color) { 0, 0, 102 });
	fHexagonList[5]->SetColor((rgb_color) { 0, 0, 204 });
	fHexagonList[6]->SetColor((rgb_color) { 0, 0, 51 });

	fHexagonList[7]->SetColor((rgb_color) { 0, 102, 102 });
	fHexagonList[8]->SetColor((rgb_color) { 0, 102, 153 });
	fHexagonList[9]->SetColor((rgb_color) { 0, 153, 204 });
	fHexagonList[10]->SetColor((rgb_color) { 0, 102, 204 });
	fHexagonList[11]->SetColor((rgb_color) { 0, 51, 204 });
	fHexagonList[12]->SetColor((rgb_color) { 0, 0, 255 });
	fHexagonList[13]->SetColor((rgb_color) { 51, 51, 255 });
	fHexagonList[14]->SetColor((rgb_color) { 51, 51, 153 });

	fHexagonList[15]->SetColor((rgb_color) { 102, 153, 153 });
	fHexagonList[16]->SetColor((rgb_color) { 0, 153, 153 });
	fHexagonList[17]->SetColor((rgb_color) { 51, 204, 204 });
	fHexagonList[18]->SetColor((rgb_color) { 0, 204, 255 });
	fHexagonList[19]->SetColor((rgb_color) { 0, 153, 255 });
	fHexagonList[20]->SetColor((rgb_color) { 0, 102, 255 });
	fHexagonList[21]->SetColor((rgb_color) { 51, 102, 255 });
	fHexagonList[22]->SetColor((rgb_color) { 51, 51, 204 });
	fHexagonList[23]->SetColor((rgb_color) { 102, 102, 153 });

	fHexagonList[24]->SetColor((rgb_color) { 51, 153, 102 });
	fHexagonList[25]->SetColor((rgb_color) { 0, 204, 153 });
	fHexagonList[26]->SetColor((rgb_color) { 0, 255, 204 });
	fHexagonList[27]->SetColor((rgb_color) { 0, 255, 255 });
	fHexagonList[28]->SetColor((rgb_color) { 51, 204, 255 });
	fHexagonList[29]->SetColor((rgb_color) { 51, 153, 255 });
	fHexagonList[30]->SetColor((rgb_color) { 102, 153, 255 });
	fHexagonList[31]->SetColor((rgb_color) { 102, 102, 255 });
	fHexagonList[32]->SetColor((rgb_color) { 102, 0, 255 });
	fHexagonList[33]->SetColor((rgb_color) { 102, 0, 204 });

	fHexagonList[34]->SetColor((rgb_color) { 51, 153, 51 });
	fHexagonList[35]->SetColor((rgb_color) { 0, 204, 102 });
	fHexagonList[36]->SetColor((rgb_color) { 0, 255, 153 });
	fHexagonList[37]->SetColor((rgb_color) { 102, 255, 204 });
	fHexagonList[38]->SetColor((rgb_color) { 102, 255, 255 });
	fHexagonList[39]->SetColor((rgb_color) { 102, 204, 255 });
	fHexagonList[40]->SetColor((rgb_color) { 153, 204, 255 });
	fHexagonList[41]->SetColor((rgb_color) { 153, 153, 255 });
	fHexagonList[42]->SetColor((rgb_color) { 153, 102, 255 });
	fHexagonList[43]->SetColor((rgb_color) { 153, 51, 255 });
	fHexagonList[44]->SetColor((rgb_color) { 153, 0, 255 });

	fHexagonList[45]->SetColor((rgb_color) { 0, 102, 0 });
	fHexagonList[46]->SetColor((rgb_color) { 0, 204, 0 });
	fHexagonList[47]->SetColor((rgb_color) { 0, 255, 0 });
	fHexagonList[48]->SetColor((rgb_color) { 102, 255, 153 });
	fHexagonList[49]->SetColor((rgb_color) { 153, 255, 204 });
	fHexagonList[50]->SetColor((rgb_color) { 204, 255, 255 });
	fHexagonList[51]->SetColor((rgb_color) { 204, 204, 255 });
	fHexagonList[52]->SetColor((rgb_color) { 204, 153, 255 });
	fHexagonList[53]->SetColor((rgb_color) { 204, 102, 255 });
	fHexagonList[54]->SetColor((rgb_color) { 204, 51, 255 });
	fHexagonList[55]->SetColor((rgb_color) { 204, 0, 255 });
	fHexagonList[56]->SetColor((rgb_color) { 153, 0, 204 });

	fHexagonList[57]->SetColor((rgb_color) { 0, 51, 0 });
	fHexagonList[58]->SetColor((rgb_color) { 0, 153, 51 });
	fHexagonList[59]->SetColor((rgb_color) { 51, 204, 51 });
	fHexagonList[60]->SetColor((rgb_color) { 102, 255, 102 });
	fHexagonList[61]->SetColor((rgb_color) { 153, 255, 153 });
	fHexagonList[62]->SetColor((rgb_color) { 204, 255, 204 });
	fHexagonList[63]->SetColor((rgb_color) { 255, 255, 255 });
	fHexagonList[64]->SetColor((rgb_color) { 255, 204, 255 });
	fHexagonList[65]->SetColor((rgb_color) { 255, 153, 255 });
	fHexagonList[66]->SetColor((rgb_color) { 255, 102, 255 });
	fHexagonList[67]->SetColor((rgb_color) { 255, 0, 255 });
	fHexagonList[68]->SetColor((rgb_color) { 204, 0, 204 });
	fHexagonList[69]->SetColor((rgb_color) { 102, 0, 102 });

	fHexagonList[70]->SetColor((rgb_color) { 51, 102, 0 });
	fHexagonList[71]->SetColor((rgb_color) { 0, 153, 0 });
	fHexagonList[72]->SetColor((rgb_color) { 102, 255, 51 });
	fHexagonList[73]->SetColor((rgb_color) { 153, 255, 102 });
	fHexagonList[74]->SetColor((rgb_color) { 204, 255, 153 });
	fHexagonList[75]->SetColor((rgb_color) { 255, 255, 204 });
	fHexagonList[76]->SetColor((rgb_color) { 255, 204, 204 });
	fHexagonList[77]->SetColor((rgb_color) { 255, 153, 204 });
	fHexagonList[78]->SetColor((rgb_color) { 255, 102, 204 });
	fHexagonList[79]->SetColor((rgb_color) { 255, 51, 204 });
	fHexagonList[80]->SetColor((rgb_color) { 204, 0, 153 });
	fHexagonList[81]->SetColor((rgb_color) { 153, 51, 153 });

	fHexagonList[82]->SetColor((rgb_color) { 51, 51, 0 });
	fHexagonList[83]->SetColor((rgb_color) { 102, 153, 0 });
	fHexagonList[84]->SetColor((rgb_color) { 153, 255, 51 });
	fHexagonList[85]->SetColor((rgb_color) { 203, 255, 102 });
	fHexagonList[86]->SetColor((rgb_color) { 255, 255, 153 });
	fHexagonList[87]->SetColor((rgb_color) { 255, 203, 153 });
	fHexagonList[88]->SetColor((rgb_color) { 255, 153, 153 });
	fHexagonList[89]->SetColor((rgb_color) { 255, 102, 153 });
	fHexagonList[90]->SetColor((rgb_color) { 255, 51, 153 });
	fHexagonList[91]->SetColor((rgb_color) { 204, 51, 153 });
	fHexagonList[92]->SetColor((rgb_color) { 153, 0, 153 });

	fHexagonList[93]->SetColor((rgb_color) { 102, 102, 51 });
	fHexagonList[94]->SetColor((rgb_color) { 153, 204, 0 });
	fHexagonList[95]->SetColor((rgb_color) { 204, 255, 51 });
	fHexagonList[96]->SetColor((rgb_color) { 255, 255, 102 });
	fHexagonList[97]->SetColor((rgb_color) { 255, 204, 102 });
	fHexagonList[98]->SetColor((rgb_color) { 255, 153, 102 });
	fHexagonList[99]->SetColor((rgb_color) { 255, 102, 102 });
	fHexagonList[100]->SetColor((rgb_color) { 255, 0, 102 });
	fHexagonList[101]->SetColor((rgb_color) { 204, 102, 153 });
	fHexagonList[102]->SetColor((rgb_color) { 153, 51, 102 });

	fHexagonList[103]->SetColor((rgb_color) { 153, 153, 102 });
	fHexagonList[104]->SetColor((rgb_color) { 204, 204, 0 });
	fHexagonList[105]->SetColor((rgb_color) { 255, 255, 0 });
	fHexagonList[106]->SetColor((rgb_color) { 255, 204, 0 });
	fHexagonList[107]->SetColor((rgb_color) { 255, 153, 51 });
	fHexagonList[108]->SetColor((rgb_color) { 255, 102, 0 });
	fHexagonList[109]->SetColor((rgb_color) { 255, 80, 80 });
	fHexagonList[110]->SetColor((rgb_color) { 204, 0, 102 });
	fHexagonList[111]->SetColor((rgb_color) { 102, 0, 51 });

	fHexagonList[112]->SetColor((rgb_color) { 153, 102, 51 });
	fHexagonList[113]->SetColor((rgb_color) { 204, 153, 0 });
	fHexagonList[114]->SetColor((rgb_color) { 255, 153, 0 });
	fHexagonList[115]->SetColor((rgb_color) { 204, 102, 0 });
	fHexagonList[116]->SetColor((rgb_color) { 255, 51, 0 });
	fHexagonList[117]->SetColor((rgb_color) { 255, 0, 0 });
	fHexagonList[118]->SetColor((rgb_color) { 204, 0, 0 });
	fHexagonList[119]->SetColor((rgb_color) { 153, 0, 51 });

	fHexagonList[120]->SetColor((rgb_color) { 102, 51, 0 });
	fHexagonList[121]->SetColor((rgb_color) { 153, 102, 0 });
	fHexagonList[122]->SetColor((rgb_color) { 204, 51, 0 });
	fHexagonList[123]->SetColor((rgb_color) { 153, 51, 0 });
	fHexagonList[124]->SetColor((rgb_color) { 153, 0, 0 });
	fHexagonList[125]->SetColor((rgb_color) { 128, 0, 0 });
	fHexagonList[126]->SetColor((rgb_color) { 153, 51, 51 });

	fHexTextControl->SetDivider(12.0);
	fHexTextControl->SetTarget(this);

	// Only permit (max 6) hexidecimal inputs
	BTextView *hexTextView = fHexTextControl->TextView();
	hexTextView->SetMaxBytes(6);
	for (int32 j = 32; j < 255; ++j) {
		if (!((j >= '0' && j <= '9') || (j >= 'a' && j <= 'f')
			|| (j >= 'A' && j <= 'F'))) {
			hexTextView->DisallowChar(j);
		}
	}

	SetColor(fColor);
}


void
HexagonalColorPicker::MessageReceived(BMessage* message)
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
HexagonalColorPicker::SetColor(rgb_color color)
{
	fColor = color;
	for (int32 i = 0; i < kMaxHexagonCount; i++) {
		if (fHexagonList[i]->Selected())
			fHexagonList[i]->SetSelected(false);
		if (fHexagonList[i]->Color() == color)
			fHexagonList[i]->SetSelected(true);
	}

	// Update the hex text control
	char string[5];
	sprintf(string, "%.6X", (color.red << 16) | (color.green << 8)
		| color.blue);
	fHexTextControl->TextView()->SetText(string);
}
