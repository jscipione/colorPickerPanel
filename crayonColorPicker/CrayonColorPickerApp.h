/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef CRAYON_COLOR_PICKERAPP_H
#define CRAYON_COLOR_PICKERAPP_H


#include <Application.h>


class BMessage;
class BWindow;
class ColorPickerPanel;

extern const char* kSignature;


class CrayonColorPickerApp : public BApplication {
public:
									CrayonColorPickerApp();
									~CrayonColorPickerApp();

	virtual	void					MessageReceived(BMessage*);
	virtual	void					ReadyToRun();

private:
			ColorPickerPanel*		fColorPickerPanel;			
};


#endif	// CRAYON_COLOR_PICKERAPP_H
