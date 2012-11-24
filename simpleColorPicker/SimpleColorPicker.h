/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef SIMPLE_COLOR_PICKER_H
#define SIMPLE_COLOR_PICKER_H


#include <View.h>


class BColorControl;
class BMessage;
class BPoint;
class ColorWell;

class SimpleColorPicker : public BView {
 public:
								SimpleColorPicker(rgb_color color);
	virtual						~SimpleColorPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

 private:
			ColorWell*			fColorWell;
			BColorControl*		fColorControl;

			rgb_color			fColor;
};


#endif	// SIMPLE_COLOR_PICKER_H
