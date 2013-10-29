/*
 * Copyright 2001-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _COLOR_WELL_H
#define _COLOR_WELL_H


#include <Control.h>


class BColorWell : public BControl {
public:
								BColorWell(BRect frame, const char* name,
									const char* label, rgb_color color,
									BMessage* message = NULL, uint32 resizingMode
										= B_FOLLOW_LEFT | B_FOLLOW_TOP,
									uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
								BColorWell(const char* name, const char* label,
									rgb_color color, BMessage* message = NULL,
									uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
								BColorWell(const char* label, rgb_color color,
									BMessage* message = NULL); 
								BColorWell(BMessage* archive);
	virtual						~BColorWell();

	static	BArchivable*		Instantiate(BMessage* archive);
	virtual	status_t			Archive(BMessage* archive,
									bool deep = true) const;

	virtual	void				Draw(BRect updateRect);

	virtual	void				AttachedToWindow();
	virtual	void				DetachedFromWindow();
	virtual	void				AllAttached();
	virtual	void				AllDetached();

	virtual	void				FrameMoved(BPoint newLocation);
	virtual	void				FrameResized(float width, float height);

	virtual	status_t			Invoke(BMessage* message = NULL);

	virtual	void				MessageReceived(BMessage* message);

	virtual	void				KeyDown(const char* bytes, int32 numBytes);
	virtual	void				MouseDown(BPoint where);
	virtual	void				MouseUp(BPoint where);
	virtual	void				MouseMoved(BPoint where, uint32 transit,
									const BMessage* dragMessage);

	virtual	void				GetPreferredSize(float* _width,
									float* _height);
	virtual	void				ResizeToPreferred();

	virtual	BSize				MinSize();
	virtual	BSize				MaxSize();
	virtual	BSize				PreferredSize();
	virtual	BAlignment			LayoutAlignment();

	virtual	void				MakeFocus(bool focused = true);

	virtual	void				WindowActivated(bool active);

	virtual rgb_color			Color() const;
	virtual	void				SetColor(rgb_color color);

	virtual	int32				Value() const;
	virtual	void				SetValue(int32 value);

	virtual	const char*			PreferredApp() const;
	virtual	void				SetPreferredApp(const char* type);

	virtual	BHandler*			ResolveSpecifier(BMessage* message,
									int32 index, BMessage* specifier,
									int32 what, const char* property);
	virtual	status_t			GetSupportedSuites(BMessage* message);
#if 0
	virtual	status_t			Perform(perform_code code, void* data);
#endif

protected:
	virtual	void				LayoutInvalidated(bool descendants = false);

private:
	// FBC padding
	virtual	void				_ReservedBColorWell1();
	virtual	void				_ReservedBColorWell2();
	virtual	void				_ReservedBColorWell3();
	virtual	void				_ReservedBColorWell4();
	virtual	void				_ReservedBColorWell5();
	virtual	void				_ReservedBColorWell6();
	virtual	void				_ReservedBColorWell7();
	virtual	void				_ReservedBColorWell8();
	virtual	void				_ReservedBColorWell9();
	virtual	void				_ReservedBColorWell10();
	virtual	void				_ReservedBColorWell11();
	virtual	void				_ReservedBColorWell12();
	virtual	void				_ReservedBColorWell13();
	virtual	void				_ReservedBColorWell14();
	virtual	void				_ReservedBColorWell15();
	virtual	void				_ReservedBColorWell16();
	virtual	void				_ReservedBColorWell17();
	virtual	void				_ReservedBColorWell18();
	virtual	void				_ReservedBColorWell19();
	virtual	void				_ReservedBColorWell20();

private:
			BRect				_ColorWellFrame() const;
			BSize				_ValidatePreferredSize();

	// Forbidden
			BColorWell&		operator=(const BColorWell&);

private:
			rgb_color			fColor;
			const char*			fPreferredApp;
			BSize				fPreferredSize;
			bool				fConnectionOpen;
			bigtime_t			fLastInvokeTime;
			BMessenger			fMessenger;
};


#endif	// _COLOR_WELL_H
