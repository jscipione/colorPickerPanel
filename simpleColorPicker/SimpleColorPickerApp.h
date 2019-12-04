/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef SIMPLE_COLOR_PICKERAPP_H
#define SIMPLE_COLOR_PICKERAPP_H


#include <Application.h>


extern const char* kSignature;


class ColorPickerPanel;

class SimpleColorPickerApp : public BApplication {
public:
								SimpleColorPickerApp();
	virtual						~SimpleColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*	fPanel;
			rgb_color			fDefaultColor;
};


#endif	// SIMPLE_COLOR_PICKERAPP_H
