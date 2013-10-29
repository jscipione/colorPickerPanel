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

#include "../ColorPickerPanel.h"


class BMessage;

extern const char* kSignature;


class SimpleColorPickerApp : public BApplication {
public:
								SimpleColorPickerApp(const char* signature);
	virtual						~SimpleColorPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			ColorPickerPanel*	fPanel;
};


#endif	// SIMPLE_COLOR_PICKERAPP_H
