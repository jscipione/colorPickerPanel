/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColorPicker.h"


ColorPicker::ColorPicker(rgb_color color, int32 flags)
	:
	BView("color picker view", flags),
	fColor(color)
{
}


ColorPicker::ColorPicker(int32 flags)
	:
	BView("color picker", flags),
	fColor((rgb_color) { 0, 0, 0 })
{
}


ColorPicker::~ColorPicker()
{
}


rgb_color
ColorPicker::Color()
{
	return fColor;
}


void
ColorPicker::SetColor(rgb_color color)
{
	fColor = color;
}
