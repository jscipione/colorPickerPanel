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


#include <Messenger.h>
#include <View.h>
#include <Window.h>


class BMessage;
class ColorPickerView;

class ColorPickerPanel : public BWindow {
 public:
								ColorPickerPanel(ColorPickerView* view,
									BMessage* message = NULL);
	virtual						~ColorPickerPanel();

	virtual	void				MessageReceived(BMessage* message);
	virtual	bool				QuitRequested();

			void				Cancel();
			void				Done();

 private:
			ColorPickerView*	fColorPickerView;
			BMessage*			fMessage;
			BMessenger			fTarget;
			rgb_color			fInitialColor;
};


#endif	// COLOR_PICKER_PANEL_H
