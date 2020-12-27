/*
 * Copyright 2009-2013 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_CONTAINERS_VIEW_H
#define _COLOR_CONTAINERS_VIEW_H


#include <File.h>
#include <View.h>


enum color_control_layout {
	B_CELLS_NONE	= 0,
	B_CELLS_2x20	= 2,
	B_CELLS_4x10	= 4,
	B_CELLS_5x8     = 5,
	B_CELLS_8x5     = 8,
	B_CELLS_10x4	= 10,
	B_CELLS_20x2	= 20,
};

static const int32 kColorContainerCount  = 40;


class ColorContainer;

class ColorContainersView : public BView {
 public:
									ColorContainersView(color_control_layout
										layout = B_CELLS_NONE);
		virtual						~ColorContainersView();

		virtual	void				AttachedToWindow();
		virtual	void				Draw(BRect updateRect);

		virtual	void				MouseDown(BPoint where);
		virtual	void				MouseMoved(BPoint where, uint32 code,
										const BMessage *message);
		virtual	void				MouseUp(BPoint where);

				void				SaveSettings();
				BMessage*			Settings() { return &fSettings; }

 private:
				void				_LoadSettings();
				void				_SaveSettings();
				status_t			_InitSettingsFile(BFile* file, bool write);

				BMessage			fSettings;
				bool				fMouseDown;
				BPoint				fMouseOffset;

				ColorContainer*		fColorContainer[kColorContainerCount];
};


#endif	// _COLOR_CONTAINERS_VIEW_H
