/*
 * Copyright 2009-2019 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *		Werner Freytag <freytag@gmx.de>
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */


#include "ColorContainersView.h"

#include <stdio.h>

#include <iostream>

#include <Application.h>
#include <Bitmap.h>
#include <Directory.h>
#include <FindDirectory.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <Path.h>
#include <Resources.h>
#include <Size.h>
#include <Window.h>

#include "ColorContainer.h"
#include "ColorPickerPanel.h"


#define COLOR_TO_INT(c) (c.red << 16) + (c.green << 8) + (c.blue)


static const char* kSettingsFileName = "Color_container_settings";

static const float kContainerWidth = 19.0f;


ColorContainersView::ColorContainersView(color_control_layout layout)
	:
	BView("containers view", B_WILL_DRAW),
	fMouseDown(false)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	for (int32 i = 0; i < kColorContainerCount; ++i) {
		fColorContainer[i] = new ColorContainer(BRect(0.0, 0.0,
			kContainerWidth, kContainerWidth));
	}

	switch (layout) {
		default:
		case B_CELLS_NONE:
			BLayoutBuilder::Group<>(this).End();
			break;

		case B_CELLS_2x20:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  0, 1)
						.Add(fColorContainer[2],  1, 0)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  2, 0)
						.Add(fColorContainer[5],  2, 1)
						.Add(fColorContainer[6],  3, 0)
						.Add(fColorContainer[7],  3, 1)
						.Add(fColorContainer[8],  4, 0)
						.Add(fColorContainer[9],  4, 1)
						.Add(fColorContainer[10], 5, 0)
						.Add(fColorContainer[11], 5, 1)
						.Add(fColorContainer[12], 6, 0)
						.Add(fColorContainer[13], 6, 1)
						.Add(fColorContainer[14], 7, 0)
						.Add(fColorContainer[15], 7, 1)
						.Add(fColorContainer[16], 8, 0)
						.Add(fColorContainer[17], 8, 1)
						.Add(fColorContainer[18], 9, 0)
						.Add(fColorContainer[19], 9, 1)
						.Add(fColorContainer[20], 10, 0)
						.Add(fColorContainer[21], 10, 1)
						.Add(fColorContainer[22], 11, 0)
						.Add(fColorContainer[23], 11, 1)
						.Add(fColorContainer[24], 12, 0)
						.Add(fColorContainer[25], 12, 1)
						.Add(fColorContainer[26], 13, 0)
						.Add(fColorContainer[27], 13, 1)
						.Add(fColorContainer[28], 14, 0)
						.Add(fColorContainer[29], 14, 1)
						.Add(fColorContainer[30], 15, 0)
						.Add(fColorContainer[31], 15, 1)
						.Add(fColorContainer[32], 16, 0)
						.Add(fColorContainer[33], 16, 1)
						.Add(fColorContainer[34], 17, 0)
						.Add(fColorContainer[35], 17, 1)
						.Add(fColorContainer[36], 18, 0)
						.Add(fColorContainer[37], 18, 1)
						.Add(fColorContainer[38], 19, 0)
						.Add(fColorContainer[39], 19, 1)
					.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;

		case B_CELLS_4x10:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  0, 1)
						.Add(fColorContainer[2],  1, 0)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  2, 0)
						.Add(fColorContainer[5],  2, 1)
						.Add(fColorContainer[6],  3, 0)
						.Add(fColorContainer[7],  3, 1)
						.Add(fColorContainer[8],  4, 0)
						.Add(fColorContainer[9],  4, 1)
						.Add(fColorContainer[10], 5, 0)
						.Add(fColorContainer[11], 5, 1)
						.Add(fColorContainer[12], 6, 0)
						.Add(fColorContainer[13], 6, 1)
						.Add(fColorContainer[14], 7, 0)
						.Add(fColorContainer[15], 7, 1)
						.Add(fColorContainer[16], 8, 0)
						.Add(fColorContainer[17], 8, 1)
						.Add(fColorContainer[18], 9, 0)
						.Add(fColorContainer[19], 9, 1)
						.Add(fColorContainer[20], 0, 2)
						.Add(fColorContainer[21], 0, 3)
						.Add(fColorContainer[22], 1, 2)
						.Add(fColorContainer[23], 1, 3)
						.Add(fColorContainer[24], 2, 2)
						.Add(fColorContainer[25], 2, 3)
						.Add(fColorContainer[26], 3, 2)
						.Add(fColorContainer[27], 3, 3)
						.Add(fColorContainer[28], 4, 2)
						.Add(fColorContainer[29], 4, 3)
						.Add(fColorContainer[30], 5, 2)
						.Add(fColorContainer[31], 5, 3)
						.Add(fColorContainer[32], 6, 2)
						.Add(fColorContainer[33], 6, 3)
						.Add(fColorContainer[34], 7, 2)
						.Add(fColorContainer[35], 7, 3)
						.Add(fColorContainer[36], 8, 2)
						.Add(fColorContainer[37], 8, 3)
						.Add(fColorContainer[38], 9, 2)
						.Add(fColorContainer[39], 9, 3)
						.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;

		case B_CELLS_5x8:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  0, 1)
						.Add(fColorContainer[2],  1, 0)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  2, 0)
						.Add(fColorContainer[5],  2, 1)
						.Add(fColorContainer[6],  3, 0)
						.Add(fColorContainer[7],  3, 1)
						.Add(fColorContainer[8],  4, 0)
						.Add(fColorContainer[9],  4, 1)
						.Add(fColorContainer[10], 5, 0)
						.Add(fColorContainer[11], 5, 1)
						.Add(fColorContainer[12], 6, 0)
						.Add(fColorContainer[13], 6, 1)
						.Add(fColorContainer[14], 7, 0)
						.Add(fColorContainer[15], 7, 1)
						.Add(fColorContainer[16], 0, 2)
						.Add(fColorContainer[17], 0, 3)
						.Add(fColorContainer[18], 1, 2)
						.Add(fColorContainer[19], 1, 3)
						.Add(fColorContainer[20], 2, 2)
						.Add(fColorContainer[21], 2, 3)
						.Add(fColorContainer[22], 3, 2)
						.Add(fColorContainer[23], 3, 3)
						.Add(fColorContainer[24], 4, 2)
						.Add(fColorContainer[25], 4, 3)
						.Add(fColorContainer[26], 5, 2)
						.Add(fColorContainer[27], 5, 3)
						.Add(fColorContainer[28], 6, 2)
						.Add(fColorContainer[29], 6, 3)
						.Add(fColorContainer[30], 7, 2)
						.Add(fColorContainer[31], 7, 3)
						.Add(fColorContainer[32], 0, 4)
						.Add(fColorContainer[33], 1, 4)
						.Add(fColorContainer[34], 2, 4)
						.Add(fColorContainer[35], 3, 4)
						.Add(fColorContainer[36], 4, 4)
						.Add(fColorContainer[37], 5, 4)
						.Add(fColorContainer[38], 6, 4)
						.Add(fColorContainer[39], 7, 4)
						.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;

		case B_CELLS_8x5:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  0, 1)
						.Add(fColorContainer[2],  1, 0)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  2, 0)
						.Add(fColorContainer[5],  2, 1)
						.Add(fColorContainer[6],  3, 0)
						.Add(fColorContainer[7],  3, 1)
						.Add(fColorContainer[8],  4, 0)
						.Add(fColorContainer[9],  4, 1)
						.Add(fColorContainer[10], 0, 2)
						.Add(fColorContainer[11], 0, 3)
						.Add(fColorContainer[12], 1, 2)
						.Add(fColorContainer[13], 1, 3)
						.Add(fColorContainer[14], 2, 2)
						.Add(fColorContainer[15], 2, 3)
						.Add(fColorContainer[16], 3, 2)
						.Add(fColorContainer[17], 3, 3)
						.Add(fColorContainer[18], 4, 2)
						.Add(fColorContainer[19], 4, 3)
						.Add(fColorContainer[20], 0, 4)
						.Add(fColorContainer[21], 0, 5)
						.Add(fColorContainer[22], 1, 4)
						.Add(fColorContainer[23], 1, 5)
						.Add(fColorContainer[24], 2, 4)
						.Add(fColorContainer[25], 2, 5)
						.Add(fColorContainer[26], 3, 4)
						.Add(fColorContainer[27], 3, 5)
						.Add(fColorContainer[28], 4, 4)
						.Add(fColorContainer[29], 4, 5)
						.Add(fColorContainer[30], 0, 6)
						.Add(fColorContainer[31], 0, 7)
						.Add(fColorContainer[32], 1, 6)
						.Add(fColorContainer[33], 1, 7)
						.Add(fColorContainer[34], 2, 6)
						.Add(fColorContainer[35], 2, 7)
						.Add(fColorContainer[36], 3, 6)
						.Add(fColorContainer[37], 3, 7)
						.Add(fColorContainer[38], 4, 6)
						.Add(fColorContainer[39], 4, 7)
						.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;

		case B_CELLS_10x4:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  0, 1)
						.Add(fColorContainer[2],  1, 0)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  2, 0)
						.Add(fColorContainer[5],  2, 1)
						.Add(fColorContainer[6],  3, 0)
						.Add(fColorContainer[7],  3, 1)
						.Add(fColorContainer[8],  0, 2)
						.Add(fColorContainer[9],  0, 3)
						.Add(fColorContainer[10], 1, 2)
						.Add(fColorContainer[11], 1, 3)
						.Add(fColorContainer[12], 2, 2)
						.Add(fColorContainer[13], 2, 3)
						.Add(fColorContainer[14], 3, 2)
						.Add(fColorContainer[15], 3, 3)
						.Add(fColorContainer[16], 0, 4)
						.Add(fColorContainer[17], 0, 5)
						.Add(fColorContainer[18], 1, 4)
						.Add(fColorContainer[19], 1, 5)
						.Add(fColorContainer[20], 2, 4)
						.Add(fColorContainer[21], 2, 5)
						.Add(fColorContainer[22], 3, 4)
						.Add(fColorContainer[23], 3, 5)
						.Add(fColorContainer[24], 0, 6)
						.Add(fColorContainer[25], 0, 7)
						.Add(fColorContainer[26], 1, 6)
						.Add(fColorContainer[27], 1, 7)
						.Add(fColorContainer[28], 2, 6)
						.Add(fColorContainer[29], 2, 7)
						.Add(fColorContainer[30], 3, 6)
						.Add(fColorContainer[31], 3, 7)
						.Add(fColorContainer[32], 0, 8)
						.Add(fColorContainer[33], 0, 9)
						.Add(fColorContainer[34], 1, 8)
						.Add(fColorContainer[35], 1, 9)
						.Add(fColorContainer[36], 2, 8)
						.Add(fColorContainer[37], 2, 9)
						.Add(fColorContainer[38], 3, 8)
						.Add(fColorContainer[39], 3, 9)
						.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;

		case B_CELLS_20x2:
			BLayoutBuilder::Group<>(this)
				.AddGroup(B_HORIZONTAL, 0.0)
					.AddGlue()
					.AddGrid(1, 1)
						.Add(fColorContainer[0],  0, 0)
						.Add(fColorContainer[1],  1, 0)
						.Add(fColorContainer[2],  0, 1)
						.Add(fColorContainer[3],  1, 1)
						.Add(fColorContainer[4],  0, 2)
						.Add(fColorContainer[5],  1, 2)
						.Add(fColorContainer[6],  0, 3)
						.Add(fColorContainer[7],  1, 3)
						.Add(fColorContainer[8],  0, 4)
						.Add(fColorContainer[9],  1, 4)
						.Add(fColorContainer[10], 0, 5)
						.Add(fColorContainer[11], 1, 5)
						.Add(fColorContainer[12], 0, 6)
						.Add(fColorContainer[13], 1, 6)
						.Add(fColorContainer[14], 0, 7)
						.Add(fColorContainer[15], 1, 7)
						.Add(fColorContainer[16], 0, 8)
						.Add(fColorContainer[17], 1, 8)
						.Add(fColorContainer[18], 0, 9)
						.Add(fColorContainer[19], 1, 9)
						.Add(fColorContainer[20], 0, 10)
						.Add(fColorContainer[21], 1, 10)
						.Add(fColorContainer[22], 0, 11)
						.Add(fColorContainer[23], 1, 11)
						.Add(fColorContainer[24], 0, 12)
						.Add(fColorContainer[25], 1, 12)
						.Add(fColorContainer[26], 0, 13)
						.Add(fColorContainer[27], 1, 13)
						.Add(fColorContainer[28], 0, 14)
						.Add(fColorContainer[29], 1, 14)
						.Add(fColorContainer[30], 0, 15)
						.Add(fColorContainer[31], 1, 15)
						.Add(fColorContainer[32], 0, 16)
						.Add(fColorContainer[33], 1, 16)
						.Add(fColorContainer[34], 0, 17)
						.Add(fColorContainer[35], 1, 17)
						.Add(fColorContainer[36], 0, 18)
						.Add(fColorContainer[37], 1, 19)
						.Add(fColorContainer[38], 0, 19)
						.Add(fColorContainer[39], 1, 19)
						.End()
					.SetInsets(0)
					.AddGlue()
				.End()
			.End();
			break;
	}
}


ColorContainersView::~ColorContainersView()
{
	SaveSettings();
}


void
ColorContainersView::AttachedToWindow()
{
	BView::AttachedToWindow();

	_LoadSettings();

	for (int32 i = 0; i < kColorContainerCount; ++i) {
		int32 intColor;
		if (fSettings.FindInt32("color_well", i, &intColor) == B_OK)
			fColorContainer[i]->SetColor(intColor);
		else
			fColorContainer[i]->SetColor(0xffffff);
	}
}


void
ColorContainersView::Draw(BRect updateRect)
{
	BView::Draw(updateRect);
}


void
ColorContainersView::MouseDown(BPoint where)
{
	Window()->Activate();

	fMouseDown = true;
	fMouseOffset = where;

	SetMouseEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY
		| B_SUSPEND_VIEW_FOCUS | B_LOCK_WINDOW_FOCUS);

	BView::MouseDown(where);
}


void
ColorContainersView::MouseMoved(BPoint where, uint32 code,
	const BMessage* message)
{
	if (fMouseDown) {
		BPoint win_pos = Window()->Frame().LeftTop();
		Window()->MoveTo(win_pos.x + where.x - fMouseOffset.x,
			win_pos.y + where.y - fMouseOffset.y);
	} else
		BView::MouseMoved(where, code, message);
}


void
ColorContainersView::MouseUp(BPoint where)
{
	fMouseDown = false;

	BView::MouseUp(where);
}


void
ColorContainersView::SaveSettings()
{
	fSettings.RemoveName("color_well");
	for (int32 i = 0; i < kColorContainerCount; ++i) {
		fSettings.AddInt32("color_well",
			COLOR_TO_INT(fColorContainer[i]->GetColor()));
	}

	_SaveSettings();
}


void
ColorContainersView::_LoadSettings()
{
	// locate preferences file
	BFile prefsFile;
	if (_InitSettingsFile(&prefsFile, false) != B_OK) {
		fprintf(stderr, "ColorPickerPanel::_LoadSettings() - "
			"no preference file found.\n");
		return;
	}

	// unflatten settings data
	if (fSettings.Unflatten(&prefsFile) != B_OK) {
		fprintf(stderr, "ColorPickerPanel::_LoadSettings() - "
			"error unflattening settings.\n");
	}
}


void
ColorContainersView::_SaveSettings()
{
	// flatten entire archive and write to settings file
	BFile prefsFile;
	status_t result = _InitSettingsFile(&prefsFile, true);
	if (result != B_OK) {
		fprintf(stderr, "ColorPickerPanel::_SaveSettings() - "
			"error creating file: %s\n", strerror(result));
		return;
	}

	result = fSettings.Flatten(&prefsFile);
	if (result != B_OK) {
		fprintf(stderr, "ColorPickerPanel::_SaveSettings() - "
			"error flattening to file: %s\n", strerror(result));
		return;
	}
}


status_t
ColorContainersView::_InitSettingsFile(BFile* file, bool write)
{
	// find user settings directory
	BPath prefsPath;
	status_t result = find_directory(B_USER_SETTINGS_DIRECTORY, &prefsPath);
	if (result != B_OK)
		return result;

	result = prefsPath.Append(kSettingsFileName);
	if (result != B_OK)
		return result;

	if (write) {
		result = file->SetTo(prefsPath.Path(),
			B_CREATE_FILE | B_ERASE_FILE | B_WRITE_ONLY);
	} else
		result = file->SetTo(prefsPath.Path(), B_READ_ONLY);

	return result;
}
