/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef SIMPLE_COLOR_PICKERAPP_H
#define SIMPLE_COLOR_PICKERAPP_H


#include <Application.h>


class BMessage;
class BWindow;
class ColorPickerPanel;

extern const char* kSignature;


class SimpleColorPickerApp : public BApplication {
public:
									SimpleColorPickerApp();
									~SimpleColorPickerApp();

	virtual	void					MessageReceived(BMessage*);
	virtual	void					ReadyToRun();

private:
			ColorPickerPanel*		fColorPickerPanel;			
};


#endif	// SIMPLE_COLOR_PICKERAPP_H
