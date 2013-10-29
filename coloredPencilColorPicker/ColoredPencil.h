/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef COLORED_PENCIL_H
#define COLORED_PENCIL_H


#include <Control.h>


const int32 kColorChanged = 'clch';


class BBitmap;
class BMessage;
class BPoint;
class BRect;

class ColoredPencil : public BControl {
public:
								ColoredPencil();
								ColoredPencil(rgb_color color);
								~ColoredPencil();

	virtual	void				AttachedToWindow();
	virtual	void				Draw(BRect updateRect);
	virtual status_t			Invoke(BMessage* message = NULL);
	virtual	void				MouseDown(BPoint where);

			rgb_color			Color() const;
			void				SetColor(rgb_color color);

protected:
			rgb_color			fColor;
			BBitmap*			fIcon;
};


#endif	// COLORED_PENCIL_H
