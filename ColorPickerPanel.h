/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus <superstippi@gmx.de>
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef COLOR_PICKER_PANEL_H
#define COLOR_PICKER_PANEL_H


#include "Panel.h"


class BHandler;
class BMessage;
class BView;
class BWindow;


class ColorPickerPanel : public Panel {
 public:
								ColorPickerPanel(BRect frame,
												 BView* colorPickerView,
												 BWindow* window = NULL,
												 BMessage* message = NULL,
												 BHandler* target = NULL);
	virtual						~ColorPickerPanel();

	virtual	void				Cancel();

	virtual	void				MessageReceived(BMessage* message);

			void				SetMessage(BMessage* message);
			void				SetTarget(BHandler* target);

 private:
			BView*				fColorPickerView;
			BWindow*			fWindow;
			BMessage*			fMessage;
			BHandler*			fTarget;
};


#endif	// COLOR_PICKER_PANEL_H
