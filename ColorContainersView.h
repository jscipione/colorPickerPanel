/*
 * Copyright 2009-2013 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_CONTAINERS_VIEW_H
#define _COLOR_CONTAINERS_VIEW_H


#include <View.h>


static const int32 kColorContainerCount  = 40;


class ColorContainer;

class ColorContainersView : public BView {
public:
									ColorContainersView();
		virtual						~ColorContainersView();

		virtual	void				AttachedToWindow();
		virtual	void				Draw(BRect updateRect);

private:
				ColorContainer*		fColorContainer[kColorContainerCount];
};


#endif	// _COLOR_CONTAINERS_VIEW_H
