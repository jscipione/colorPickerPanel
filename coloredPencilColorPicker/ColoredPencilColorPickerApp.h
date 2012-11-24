/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef COLORED_PENCIL_COLOR_PICKERAPP_H
#define COLORED_PENCIL_COLOR_PICKERAPP_H


#include <Application.h>


class BMessage;
class BWindow;
class ColorPickerPanel;

extern const char* kSignature;


class ColoredPencilColorPickerApp : public BApplication {
public:
									ColoredPencilColorPickerApp();
									~ColoredPencilColorPickerApp();

	virtual	void					ReadyToRun();

private:
			ColorPickerPanel*		fColorPickerPanel;			
};


#endif	// COLORED_PENCIL_COLOR_PICKERAPP_H
