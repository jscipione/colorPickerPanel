/*
 * Copyright 2009-2013 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_CONTAINERS_VIEW_H
#define _COLOR_CONTAINERS_VIEW_H


#include <View.h>


static const int32 kColorContainerCount  = 40;


class BFile;
class BMessage;

class ColorContainer;


class ColorContainersView : public BView {
public:
									ColorContainersView();
		virtual						~ColorContainersView();

		virtual	void				AttachedToWindow();
		virtual	void				Draw(BRect updateRect);
		virtual	bool				QuitRequested();

				BMessage*			Settings() { return &fSettings; }
				void				SaveSettings();

private:
				status_t			_InitSettingsFile(BFile* file, bool write);
				void				_LoadSettings();
				void				_SaveSettings();

private:
				ColorContainer*		fColorContainer[kColorContainerCount];
				BMessage			fSettings;
};


#endif	// _COLOR_CONTAINERS_VIEW_H
