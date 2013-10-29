/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * This file may be used under the terms of the Be Sample Code License.
 */
#ifndef CRAYON_COLOR_PICKER_H
#define CRAYON_COLOR_PICKER_H


#include <View.h>


const int32 kMaxCrayonCount = 48;


class BBitmap;
class Crayon;
class SelectedCrayon;

class CrayonColorPicker : public BView {
 public:
								CrayonColorPicker(rgb_color color);
								~CrayonColorPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

 private:
			rgb_color			fColor;
			SelectedCrayon*		fSelectedColor;
			Crayon*				fCrayonList[kMaxCrayonCount];
			int32				fCrayonCount;
};


#endif	// CRAYON_COLOR_PICKER_H
