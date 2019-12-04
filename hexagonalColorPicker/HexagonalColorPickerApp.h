/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef HEXAGONAL_COLOR_PICKERAPP_H
#define HEXAGONAL_COLOR_PICKERAPP_H


#include <Application.h>


extern const char* kSignature;


class ColorPickerPanel;

class HexagonalColorPickerApp : public BApplication {
public:
								HexagonalColorPickerApp();
	virtual						~HexagonalColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*	fPanel;
			rgb_color			fDefaultColor;
};


#endif	// HEXAGONAL_COLOR_PICKERAPP_H
