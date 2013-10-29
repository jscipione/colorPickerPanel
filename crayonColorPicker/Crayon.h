/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef CRAYON_H
#define CRAYON_H


#include <Control.h>


const int32 kColorChanged = 'clch';


class BBitmap;
class BMessage;
class BPoint;
class BRect;

class Crayon : public BControl {
 public:
 								Crayon();
								Crayon(rgb_color color);
								~Crayon();

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


#endif	// CRAYON_H
