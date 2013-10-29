/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef SELECTED_CRAYON_H
#define SELECTED_CRAYON_H


#include "Crayon.h"


class BBitmap;
class BRect;

class SelectedCrayon : public Crayon {
public:
								SelectedCrayon(rgb_color color);
								~SelectedCrayon();

	virtual	void				AttachedToWindow();
};


#endif	// SELECTED_CRAYON_H
