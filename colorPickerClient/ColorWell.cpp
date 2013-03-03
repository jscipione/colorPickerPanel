/*
 * Copyright 2001-2013 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus, superstippi@gmx.de
 *		John Scipione, jscipione@gmail.com
 */


#include "ColorWell.h"

#include <new>

#include <ControlLook.h>
#include <LayoutUtils.h>
#include <Message.h>
#include <Rect.h>
#include <Roster.h>
#include <Size.h>
#include <Window.h>

#include "../Protocol.h"


const char* kColorPickerType = "application/x-vnd.Haiku.ColorPicker";


// #pragma mark - Constructors and destructor


BColorWell::BColorWell(BRect frame, const char* name, const char* label,
	rgb_color color, BMessage* message, uint32 resizingMode, uint32 flags)
	:
	BControl(frame, name, label, message, resizingMode, flags),
	fColor(color),
	fPreferredApp(kColorPickerType),
	fPreferredSize(),
	fConnectionOpen(false),
	fLastInvokeTime(0)
{
	// Resize to minimum height if needed
	font_height fontHeight;
	GetFontHeight(&fontHeight);
	float minHeight = (float)ceil(6.0f + fontHeight.ascent
		+ fontHeight.descent);
	if (Bounds().Height() < minHeight)
		ResizeTo(Bounds().Width(), minHeight);
}


BColorWell::BColorWell(const char* name, const char* label, rgb_color color,
	BMessage* message, uint32 flags)
	:
	BControl(name, label, message, flags | B_WILL_DRAW | B_NAVIGABLE),
	fColor(color),
	fPreferredApp(kColorPickerType),
	fPreferredSize(),
	fConnectionOpen(false),
	fLastInvokeTime(0)
{
}


BColorWell::BColorWell(const char* label, rgb_color color, BMessage* message)
	:
	BControl(NULL, label, message, B_WILL_DRAW | B_NAVIGABLE),
	fColor(color),
	fPreferredApp(kColorPickerType),
	fPreferredSize(),
	fConnectionOpen(false),
	fLastInvokeTime(0)
{
}


BColorWell::BColorWell(BMessage* archive)
	:
	BControl(archive)
{
}


BColorWell::~BColorWell()
{
	if (fConnectionOpen)
		fMessenger.SendMessage(kCloseConnection);
}


// #pragma mark - BArchivable interface


BArchivable*
BColorWell::Instantiate(BMessage *archive)
{
	if (validate_instantiation(archive, "BColorWell"))
		return new(std::nothrow) BColorWell(archive);

	return NULL;
}


status_t
BColorWell::Archive(BMessage *archive, bool deep) const
{
	return BControl::Archive(archive, deep);
}


// #pragma mark - virtual public methods


void
BColorWell::Draw(BRect updateRect)
{
	rgb_color base = ui_color(B_PANEL_BACKGROUND_COLOR);
	rgb_color border = ui_color(B_CONTROL_BORDER_COLOR);
	rgb_color background = ui_color(B_CONTROL_BACKGROUND_COLOR);
	BRect colorWellRect(_ColorWellFrame());

	SetHighColor(border);
	StrokeRect(colorWellRect);
	colorWellRect.InsetBy(1.0, 1.0);

	SetHighColor(background);
	FillRect(colorWellRect);
	colorWellRect.InsetBy(4.0, 4.0);

	SetHighColor(border);
	StrokeRect(colorWellRect);
	colorWellRect.InsetBy(1.0, 1.0);

	SetHighColor(fColor);
	FillRect(colorWellRect);

	BRect labelRect(Bounds());
	labelRect.left = colorWellRect.right
		+ be_control_look->DefaultLabelSpacing() * 2;

	be_control_look->DrawLabel(this, Label(), labelRect, updateRect,
		base, 0);
}


void
BColorWell::AttachedToWindow()
{
	BControl::AttachedToWindow();
}


void
BColorWell::DetachedFromWindow()
{
	BControl::DetachedFromWindow();
}


void
BColorWell::AllAttached()
{
	BControl::AllAttached();
}


void
BColorWell::AllDetached()
{
	BControl::AllDetached();
}


void
BColorWell::FrameMoved(BPoint newLocation)
{
	BControl::FrameMoved(newLocation);
}


void
BColorWell::FrameResized(float width, float height)
{
	BControl::FrameResized(width, height);
}


status_t
BColorWell::Invoke(BMessage* message)
{
	if (fConnectionOpen) {
		fMessenger.SendMessage(kActivateWindow);
		// we already have a picker serving us, pull it up
		return B_OK;
	}

	bigtime_t now = system_time();
	if (now - fLastInvokeTime < 1000000) {
		// Don't invoke again for a bit after a first invoke to prevent
		// launching two pickers. It would be nicer to wait after
		// kOpenConnection returns.
		return B_OK;
	}

	fLastInvokeTime = now;

	uint32 buttons;
	BPoint point;
	GetMouse(&point, &buttons);

	BMessage launchMessage(kInitiateConnection);

	launchMessage.AddString(kTargetName, Name());
		// add the current name so that the color picker
		// can set the name, say in the title.
	launchMessage.AddPoint(kInvokePoint, ConvertToScreen(point));
		// add the current invocation point so that the color picker
		// can position itself near the click
	rgb_color color = Color();
	launchMessage.AddData(kInitialValue, B_RGB_COLOR_TYPE, &color,
		sizeof(color));
		// add the current color value
	launchMessage.AddInt32(kRequestedValues, B_RGB_COLOR_TYPE);
		// ask for the fMimeType of values we need
	launchMessage.AddMessenger(kClientAddress, BMessenger(this));
		// this is the messenger we want the color picker to
		// interact with

	if (fPreferredApp != NULL) {
		// whe have a specific preferred appliacation for this instance
		// launch the picker - use the application signature for
		// this particular client
		be_roster->Launch(fPreferredApp, &launchMessage);
	} else {
		be_roster->Launch(kColorPickerType, &launchMessage);
			// launch the picker, just use the mime fMimeType
			// to choose the preferred application
	}

	return BControl::Invoke(message);
}


void
BColorWell::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case B_VALUE_CHANGED:
		{
			rgb_color* color;
			ssize_t size;
			if (message->FindData("be:value", B_RGB_COLOR_TYPE,
					(const void **)(&color), &size) == B_OK) {
				SetColor(*color);
			}
			break;
		}

		case B_CANCEL:
		case kServerQuitting:
			fConnectionOpen = false;
			break;

		case kOpenConnection:
		{
			fConnectionOpen = true;
			BMessenger messenger;
			if (message->FindMessenger(kServerAddress, &messenger) == B_OK)
				fMessenger = messenger;

			break;
		}

		return;
	}

	if (message->WasDropped()) {
		// handle drag & drop
		char* nameFound;
		type_code typeFound;
		if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
				== B_OK) {
			rgb_color* color;
			ssize_t numBytes;
			if (message->FindData(nameFound, typeFound, (const void **)&color,
					&numBytes) == B_OK) {
				SetColor(*color);
	
				// notify the color picker of the color change
				if (fConnectionOpen) {
					BMessage updateMessage(B_VALUE_CHANGED);
					updateMessage.AddData("be:value", B_RGB_COLOR_TYPE, color,
						sizeof(color));
					fMessenger.SendMessage(&updateMessage);
				}
				return;
			}
		}
	}

	BControl::MessageReceived(message);
}


void
BColorWell::KeyDown(const char *bytes, int32 numBytes)
{
	BControl::KeyDown(bytes, numBytes);
}


void
BColorWell::MouseDown(BPoint point)
{
	BControl::MouseDown(point);
}


void
BColorWell::MouseUp(BPoint point)
{
	Invoke();

	BControl::MouseUp(point);
}


void
BColorWell::MouseMoved(BPoint point, uint32 transit, const BMessage* message)
{
	BControl::MouseMoved(point, transit, message);
}


void
BColorWell::GetPreferredSize(float* _width, float* _height)
{
	font_height fontHeight;
	GetFontHeight(&fontHeight);

	if (_width) {
		float width = 12.0f + fontHeight.ascent;

		if (Label())
			width += StringWidth(Label());

		*_width = (float)ceil(width);
	}

	if (_height)
		*_height = (float)ceil(6.0f + fontHeight.ascent + fontHeight.descent);
}


void
BColorWell::ResizeToPreferred()
{
	BControl::ResizeToPreferred();
}


BSize
BColorWell::MinSize()
{
	return BLayoutUtils::ComposeSize(ExplicitMinSize(),
		_ValidatePreferredSize());
}


BSize
BColorWell::MaxSize()
{
	return BLayoutUtils::ComposeSize(ExplicitMaxSize(),
		BSize(B_SIZE_UNLIMITED, _ValidatePreferredSize().height));
}


BSize
BColorWell::PreferredSize()
{
	return BLayoutUtils::ComposeSize(ExplicitPreferredSize(),
		_ValidatePreferredSize());
}


void
BColorWell::MakeFocus(bool focused)
{
	BControl::MakeFocus(focused);
}


void
BColorWell::WindowActivated(bool active)
{
	BControl::WindowActivated(active);
}


int32
BColorWell::Value() const
{
	return fColor.red << 16 + fColor.green << 8 + fColor.blue;
}


void
BColorWell::SetValue(int32 value)
{
	rgb_color color;
	color.red   = (value >> 16) & 255;
	color.green = (value >> 8) & 255;
	color.blue  = value & 255;
	SetColor(color);
}


rgb_color
BColorWell::Color() const
{
	return fColor;
}


void
BColorWell::SetColor(rgb_color color)
{
	color.alpha = 255;
	fColor = color;
	if (Window())
		Invalidate();

	// Send the color in a message to the control target
	BMessage* message = this->Message();
	if (message != NULL) {
		message->AddData("be:value", B_RGB_COLOR_TYPE, &fColor,
			sizeof(fColor));
		message->AddInt64("when", system_time());
		BControl::Invoke(message);
	}
}


const char*
BColorWell::PreferredApp() const
{
	return fPreferredApp;
}


void
BColorWell::SetPreferredApp(const char* type)
{
	fPreferredApp = type;
}


BHandler*
BColorWell::ResolveSpecifier(BMessage *message, int32 index,
	BMessage *specifier, int32 what, const char *property)
{
	return BControl::ResolveSpecifier(message, index, specifier, what,
		property);
}


status_t
BColorWell::GetSupportedSuites(BMessage *message)
{
	return BControl::GetSupportedSuites(message);
}


// #pragma mark - Protected Methods


void
BColorWell::LayoutInvalidated(bool descendants)
{
	// invalidate cached preferred size
	fPreferredSize.Set(B_SIZE_UNSET, B_SIZE_UNSET);
}


// #pragma mark - FBC padding


void BColorWell::_ReservedBColorWell1() {}
void BColorWell::_ReservedBColorWell2() {}
void BColorWell::_ReservedBColorWell3() {}
void BColorWell::_ReservedBColorWell4() {}
void BColorWell::_ReservedBColorWell5() {}
void BColorWell::_ReservedBColorWell6() {}
void BColorWell::_ReservedBColorWell7() {}
void BColorWell::_ReservedBColorWell8() {}
void BColorWell::_ReservedBColorWell9() {}
void BColorWell::_ReservedBColorWell10() {}
void BColorWell::_ReservedBColorWell11() {}
void BColorWell::_ReservedBColorWell12() {}
void BColorWell::_ReservedBColorWell13() {}
void BColorWell::_ReservedBColorWell14() {}
void BColorWell::_ReservedBColorWell15() {}
void BColorWell::_ReservedBColorWell16() {}
void BColorWell::_ReservedBColorWell17() {}
void BColorWell::_ReservedBColorWell18() {}
void BColorWell::_ReservedBColorWell19() {}
void BColorWell::_ReservedBColorWell20() {}


// #pragma mark - Private methods


BRect
BColorWell::_ColorWellFrame() const
{
	font_height fontHeight;
	GetFontHeight(&fontHeight);

	return BRect(4.0f, 2.0f, ceilf(28.0f + fontHeight.ascent),
		ceilf(10.0f + fontHeight.ascent));
}


BSize
BColorWell::_ValidatePreferredSize()
{
	if (!fPreferredSize.IsWidthSet()) {
		font_height fontHeight;
		GetFontHeight(&fontHeight);

		float width = 12.0f + fontHeight.ascent;

		if (Label())
			width += StringWidth(Label());

		fPreferredSize.width = (float)ceil(width);

		fPreferredSize.height = (float)ceil(11.0f + fontHeight.ascent
			+ fontHeight.descent);

		ResetLayoutInvalidation();
	}

	return fPreferredSize;
}


// Forbidden


BColorWell&
BColorWell::operator=(const BColorWell&)
{
	return *this;
}
