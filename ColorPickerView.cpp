/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "ColorPickerView.h"


ColorPickerView::ColorPickerView(rgb_color color)
	:
	BView("color picker view", B_WILL_DRAW),
	fColor(color)
{
}


ColorPickerView::ColorPickerView()
	:
	BView("color picker view", B_WILL_DRAW),
	fColor((rgb_color) { 0, 0, 0 })
{
}


ColorPickerView::~ColorPickerView()
{
}


rgb_color
ColorPickerView::Color()
{
	return fColor;
}


void
ColorPickerView::SetColor(rgb_color color)
{
	fColor = color;
}
