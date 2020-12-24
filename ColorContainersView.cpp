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


ColorContainersView::ColorContainersView()
	:
	BView("containers view", B_WILL_DRAW),
	fMouseDown(false)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	for (int32 i = 0; i < kColorContainerCount; ++i)
		fColorContainer[i] = new ColorContainer(BRect(0.0, 0.0, 19.0, 19.0));

	BLayoutBuilder::Group<>(this)
		.AddGroup(B_HORIZONTAL, 24.0)
			.AddGrid(1, 1)
				.Add(fColorContainer[0], 0, 0)
				.Add(fColorContainer[1], 1, 0)
				.Add(fColorContainer[2], 2, 0)
				.Add(fColorContainer[3], 3, 0)
				.Add(fColorContainer[4], 4, 0)
				.Add(fColorContainer[5], 5, 0)
				.Add(fColorContainer[6], 6, 0)
				.Add(fColorContainer[7], 7, 0)
				.Add(fColorContainer[8], 8, 0)
				.Add(fColorContainer[9], 9, 0)
				.Add(fColorContainer[10], 10, 0)
				.Add(fColorContainer[11], 11, 0)
				.Add(fColorContainer[12], 12, 0)
				.Add(fColorContainer[13], 13, 0)
				.Add(fColorContainer[14], 14, 0)
				.Add(fColorContainer[15], 15, 0)
				.Add(fColorContainer[16], 16, 0)
				.Add(fColorContainer[17], 17, 0)
				.Add(fColorContainer[18], 18, 0)
				.Add(fColorContainer[19], 19, 0)
				.Add(fColorContainer[20], 0, 1)
				.Add(fColorContainer[21], 1, 1)
				.Add(fColorContainer[22], 2, 1)
				.Add(fColorContainer[23], 3, 1)
				.Add(fColorContainer[24], 4, 1)
				.Add(fColorContainer[25], 5, 1)
				.Add(fColorContainer[26], 6, 1)
				.Add(fColorContainer[27], 7, 1)
				.Add(fColorContainer[28], 8, 1)
				.Add(fColorContainer[29], 9, 1)
				.Add(fColorContainer[30], 10, 1)
				.Add(fColorContainer[31], 11, 1)
				.Add(fColorContainer[32], 12, 1)
				.Add(fColorContainer[33], 13, 1)
				.Add(fColorContainer[34], 14, 1)
				.Add(fColorContainer[35], 15, 1)
				.Add(fColorContainer[36], 16, 1)
				.Add(fColorContainer[37], 17, 1)
				.Add(fColorContainer[38], 18, 1)
				.Add(fColorContainer[39], 19, 1)
				.End()
			.SetInsets(0)
			.End();
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
