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


class BMessage;
class BWindow;
class ColorPickerPanel;

extern const char* kSignature;


class HexagonalColorPickerApp : public BApplication {
public:
									HexagonalColorPickerApp();
									~HexagonalColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*		fColorPickerPanel;			
};


#endif	// HEXAGONAL_COLOR_PICKERAPP_H
