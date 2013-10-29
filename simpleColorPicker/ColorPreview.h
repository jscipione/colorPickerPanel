/*
 * Copyright 2001-2008 Werner Freytag.
 * Copyright 2009-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_PREVIEW_H
#define _COLOR_PREVIEW_H


#include <Control.h>


class ColorPreview : public BControl {
 public:
								ColorPreview(BRect frame, const char* name,
									const char* label, BMessage *message,
									uint32 resizingMode = B_FOLLOW_LEFT
										| B_FOLLOW_TOP,
									uint32 flags = B_WILL_DRAW);
	virtual						~ColorPreview();

	virtual	void				Draw(BRect updateRect);

	virtual	void				MessageReceived(BMessage *message);

			rgb_color			Color() const;
			void				SetColor(rgb_color color);

 private:

			rgb_color			fColor;
};

#endif	// _COLOR_PREVIEW_H
