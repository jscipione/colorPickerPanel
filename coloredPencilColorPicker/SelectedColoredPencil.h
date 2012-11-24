/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef SELECTED_COLORED_PENCIL_H
#define SELECTED_COLORED_PENCIL_H


#include "ColoredPencil.h"


class BBitmap;
class BRect;

class SelectedColoredPencil : public ColoredPencil {
 public:
								SelectedColoredPencil(rgb_color color);
								~SelectedColoredPencil();

	virtual	void				AttachedToWindow();
	virtual	void				Draw(BRect updateRect);

};


#endif	// SELECTED_COLORED_PENCIL_H
