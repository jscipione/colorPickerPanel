/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H


#include <View.h>


class ColorPicker : public BView {
public:
								ColorPicker(rgb_color color);
								ColorPicker();
	virtual						~ColorPicker();

	virtual	rgb_color			Color();
	virtual	void				SetColor(rgb_color color);

protected:
			rgb_color			fColor;
};

#endif	// COLOR_PICKER_H
