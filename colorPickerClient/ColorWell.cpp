/*
 * Copyright 2001-2013 Haiku, Inc. All rights reserved.
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

#if 0
#include <binary_compatibility/Interface.h>
#endif

// golden ratio
#ifdef M_PHI
#	undef M_PHI
#endif
#define M_PHI 1.61803398874989484820


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
BColorWell::Instantiate(BMessage* archive)
{
	if (validate_instantiation(archive, "BColorWell"))
		return new(std::nothrow) BColorWell(archive);

	return NULL;
}


status_t
BColorWell::Archive(BMessage* archive, bool deep) const
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
	colorWellRect.InsetBy(3.0, 3.0);

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
	// Send the color in a message to the control target
	if (message == NULL)
		message = Message();

	if (message == NULL)
		return B_BAD_VALUE;

	message->AddData("be:value", B_RGB_COLOR_TYPE, &fColor,
		sizeof(fColor));

	return BControl::Invoke(message);
}


void
BColorWell::MessageReceived(BMessage* message)
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
BColorWell::KeyDown(const char* bytes, int32 numBytes)
{
	BControl::KeyDown(bytes, numBytes);
}


void
BColorWell::MouseDown(BPoint where)
{
	if (fConnectionOpen) {
		fMessenger.SendMessage(kActivateWindow);
		// we already have a picker serving us, pull it up
		return;
	}

	bigtime_t now = system_time();
	if (now - fLastInvokeTime < 1000000) {
		// Don't invoke again for a bit after a first invoke to prevent
		// launching two pickers. It would be nicer to wait after
		// kOpenConnection returns.
		return;
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

	BControl::MouseDown(point);
}


void
BColorWell::MouseUp(BPoint where)
{
	BControl::MouseUp(where);
}


void
BColorWell::MouseMoved(BPoint where, uint32 transit, const BMessage* message)
{
	BControl::MouseMoved(where, transit, message);
}


// #pragma mark -


void
BColorWell::GetPreferredSize(float* _width, float* _height)
{
	font_height fontHeight;
	GetFontHeight(&fontHeight);

	// calculate height first because width is based on height
	float itemHeight = ceilf(fontHeight.ascent + 10 + fontHeight.descent);

	if (_height != NULL)
		*_height = itemHeight;

	if (_width != NULL) {
		*_width = roundf(itemHeight * M_PHI) - 1 + 12;

		const char* label = Label();
		if (label != NULL)
			*_width += StringWidth(label);
	}
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
		_ValidatePreferredSize());
}


BSize
BColorWell::PreferredSize()
{
	return BLayoutUtils::ComposeSize(ExplicitPreferredSize(),
		_ValidatePreferredSize());
}


BAlignment
BColorWell::LayoutAlignment()
{
	return BLayoutUtils::ComposeAlignment(ExplicitAlignment(),
		BAlignment(B_ALIGN_LEFT, B_ALIGN_VERTICAL_CENTER));
}


// #pragma mark -


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

	Invoke();
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
BColorWell::ResolveSpecifier(BMessage* message, int32 index,
	BMessage* specifier, int32 what, const char* property)
{
	return BControl::ResolveSpecifier(message, index, specifier, what,
		property);
}


status_t
BColorWell::GetSupportedSuites(BMessage* message)
{
	return BControl::GetSupportedSuites(message);
}


#if 0
status_t
BColorWell::Perform(perform_code code, void* _data)
{
	switch (code) {
		case PERFORM_CODE_MIN_SIZE:
			((perform_data_min_size*)_data)->return_value
				= BColorWell::MinSize();
			return B_OK;
		case PERFORM_CODE_MAX_SIZE:
			((perform_data_max_size*)_data)->return_value
				= BColorWell::MaxSize();
			return B_OK;
		case PERFORM_CODE_PREFERRED_SIZE:
			((perform_data_preferred_size*)_data)->return_value
				= BColorWell::PreferredSize();
			return B_OK;
		case PERFORM_CODE_LAYOUT_ALIGNMENT:
			((perform_data_layout_alignment*)_data)->return_value
				= BColorWell::LayoutAlignment();
			return B_OK;
		case PERFORM_CODE_HAS_HEIGHT_FOR_WIDTH:
			((perform_data_has_height_for_width*)_data)->return_value
				= BColorWell::HasHeightForWidth();
			return B_OK;
		case PERFORM_CODE_GET_HEIGHT_FOR_WIDTH:
		{
			perform_data_get_height_for_width* data
				= (perform_data_get_height_for_width*)_data;
			BColorWell::GetHeightForWidth(data->width, &data->min, &data->max,
				&data->preferred);
			return B_OK;
		}
		case PERFORM_CODE_SET_LAYOUT:
		{
			perform_data_set_layout* data = (perform_data_set_layout*)_data;
			BColorWell::SetLayout(data->layout);
			return B_OK;
		}
		case PERFORM_CODE_LAYOUT_INVALIDATED:
		{
			perform_data_layout_invalidated* data
				= (perform_data_layout_invalidated*)_data;
			BColorWell::LayoutInvalidated(data->descendants);
			return B_OK;
		}
		case PERFORM_CODE_DO_LAYOUT:
		{
			BColorWell::DoLayout();
			return B_OK;
		}
	}

	return BControl::Perform(code, _data);
}
#endif


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
BColorWell::_ColorWellFrame()
{
	float itemWidth, itemHeight;
	GetPreferredSize(NULL, &itemHeight);
	itemWidth = roundf(itemHeight * M_PHI) - 1;

	return BRect(4, 2, itemWidth - 4, itemHeight - 2);
}


BSize
BColorWell::_ValidatePreferredSize()
{
	if (!fPreferredSize.IsWidthSet()) {
		float itemWidth, itemHeight;
		GetPreferredSize(&itemWidth, &itemHeight);

		fPreferredSize.width = itemWidth;
		fPreferredSize.height = itemHeight;

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
