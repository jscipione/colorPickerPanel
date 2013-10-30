/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef SIMPLE_COLOR_PICKER_H
#define SIMPLE_COLOR_PICKER_H


#include "../ColorPickerView.h"


class BColorControl;
class BMessage;
class ColorPreview;

class SimpleColorPicker : public ColorPickerView {
public:
								SimpleColorPicker(rgb_color color);
	virtual						~SimpleColorPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

	virtual	void				SetColor(rgb_color color);

private:
			void				_Init();

private:
			rgb_color			fColor;
			ColorPreview*		fColorPreview;
			BColorControl*		fColorControl;
};


#endif	// SIMPLE_COLOR_PICKER_H
