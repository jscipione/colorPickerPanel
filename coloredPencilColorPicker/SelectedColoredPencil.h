/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
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
};


#endif	// SELECTED_COLORED_PENCIL_H
