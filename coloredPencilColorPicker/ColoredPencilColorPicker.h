/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * This file may be used under the terms of the Be Sample Code License.
 */
#ifndef COLORED_PENCIL_COLOR_PICKER_H
#define COLORED_PENCIL_COLOR_PICKER_H


#include "../ColorPicker.h"


const int32 kMaxColoredPencilCount = 48;


class BBitmap;
class ColoredPencil;
class SelectedColoredPencil;

class ColoredPencilColorPicker : public ColorPicker {
public:
								ColoredPencilColorPicker(rgb_color color);
	virtual						~ColoredPencilColorPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

private:
			rgb_color			fColor;
			SelectedColoredPencil*	fSelectedColor;
			ColoredPencil*		fColoredPencilList[kMaxColoredPencilCount];
			int32				fColoredPencilCount;
};


#endif	// COLORED_PENCIL_COLOR_PICKER_H
