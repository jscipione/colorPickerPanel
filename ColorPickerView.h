/*
 * Copyright 2013 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef COLOR_PICKER_VIEW_H
#define COLOR_PICKER_VIEW_H


#include <View.h>


class ColorPickerView : public BView {
 public:
 								ColorPickerView(rgb_color color);
 								ColorPickerView();
	virtual						~ColorPickerView();

	virtual	rgb_color			Color();
	virtual	void				SetColor(rgb_color color);

 protected:
			rgb_color			fColor;
};

#endif	// COLOR_PICKER_VIEW_H
