/*
 * Copyright 2012 Haiku, Inc.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione <jscipione@gmail.com>
 */
#ifndef HEXAGONAL_COLOR_PICKER_H
#define HEXAGONAL_COLOR_PICKER_H


#include <View.h>


const int32 kMaxHexagonCount = 127;


class BMessage;
class BPoint;
class Hexagon;

class HexagonalColorPicker : public BView {
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
};


#endif	// HEXAGONAL_COLOR_PICKER_H
