/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef COLORED_PENCIL_COLOR_PICKERAPP_H
#define COLORED_PENCIL_COLOR_PICKERAPP_H


#include <Application.h>


extern const char* kSignature;


class ColorPickerPanel;

class ColoredPencilColorPickerApp : public BApplication {
public:
								ColoredPencilColorPickerApp();
								~ColoredPencilColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*	fPanel;
			rgb_color			fDefaultColor;
};


#endif	// COLORED_PENCIL_COLOR_PICKERAPP_H
