/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */
#ifndef HEXAGONAL_COLOR_PICKER_H
#define HEXAGONAL_COLOR_PICKER_H


#include "../ColorPickerView.h"


const int32 kMaxHexagonCount = 143;


class BMessage;
class BPoint;
class BTextControl;
class Hexagon;

class HexagonalColorPicker : public ColorPickerView {
public:
								HexagonalColorPicker(rgb_color color);
	virtual						~HexagonalColorPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

private:
			rgb_color			fColor;
			Hexagon*			fHexagonList[kMaxHexagonCount];
			int32				fHexagonCount;
			BTextControl*		fHexTextControl;
};


#endif	// HEXAGONAL_COLOR_PICKER_H
