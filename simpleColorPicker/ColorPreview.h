/*
 * Copyright 2001-2008 Werner Freytag.
 * Copyright 2009-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_PREVIEW_H
#define _COLOR_PREVIEW_H


#include <Control.h>


class BMessage;
class BMessageRunner;


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
	virtual	void				MouseDown(BPoint where);
	virtual	void				MouseMoved(BPoint where, uint32 transit,
									const BMessage* message);
	virtual	void				MouseUp(BPoint where);

			rgb_color			Color() const;
			void				SetColor(rgb_color color);

private:
			void				_DragColor(BPoint where);

			rgb_color			fColor;

			BMessageRunner*		fMessageRunner;
};

#endif	// _COLOR_PREVIEW_H
