/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef CRAYON_COLOR_PICKERAPP_H
#define CRAYON_COLOR_PICKERAPP_H


#include <Application.h>


extern const char* kSignature;


class ColorPickerPanel;

class CrayonColorPickerApp : public BApplication {
public:
								CrayonColorPickerApp();
	virtual						~CrayonColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*	fPanel;
			rgb_color			fDefaultColor;
};


#endif	// CRAYON_COLOR_PICKERAPP_H
