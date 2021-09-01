/*
 * Copyright 2009-2012 Haiku, Inc. All Rights Reserved.
 * Copyright 2001-2008 Werner Freytag.
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *		Werner Freytag <freytag@gmx.de>
 * Authors:
 *		Stephan Aßmus <superstippi@gmx.de>
 *		John Scipione <jscipione@gmail.com>
 */


#include "ColorSlider.h"

#include <iostream>
#include <math.h>

#include <Bitmap.h>
#include <OS.h>
#include <Window.h>

#include "convert_rgb_hsv.h"
#include "color_mode.h"

#define SLIDER_WIDTH 35.0
#define SLIDER_HEIGHT 259.0
#define SLIDER_RECT BRect(0.0, 0.0, SLIDER_WIDTH, SLIDER_HEIGHT)
#define round(x) (int)(x+0.5)


ColorSlider::ColorSlider(color_mode mode, float value1, float value2)
	:
	BControl("color slider", "", new BMessage(MSG_COLOR_SLIDER),
		B_WILL_DRAW | B_FRAME_EVENTS),
	fColorMode(mode),
	fFixedValue1(value1),
	fFixedValue2(value2),
	fMouseDown(false),
	fBgBitmap(new BBitmap(SLIDER_RECT, B_RGB32, true)),
	fBgView(NULL),
	fUpdateThread(0),
	fUpdatePort(0)
{
	SetViewColor(B_TRANSPARENT_32_BIT);
	SetExplicitSize(BSize(SLIDER_WIDTH, SLIDER_HEIGHT));

	if (fBgBitmap->IsValid() && fBgBitmap->Lock()) {
		fBgView = new BView(SLIDER_RECT, "", B_FOLLOW_NONE, B_WILL_DRAW);
		fBgBitmap->AddChild(fBgView);
		fBgView->SetOrigin(8.0, 2.0);
		fBgBitmap->Unlock();
	} else {
		delete fBgBitmap;
		fBgBitmap = NULL;
		fBgView = this;
	}

	fUpdatePort = create_port(100, "color slider update port");

	fUpdateThread = spawn_thread(&ColorSlider::_UpdateThread,
		"color slider update thread", 10, this);
	resume_thread(fUpdateThread);

	Update(2);
}


ColorSlider::~ColorSlider() {
	if (fUpdatePort)
		delete_port(fUpdatePort);

	if (fUpdateThread)
		kill_thread(fUpdateThread);

	delete fBgBitmap;
}


void
ColorSlider::AttachedToWindow()
{
	BControl::AttachedToWindow();

	SetViewColor(B_TRANSPARENT_32_BIT);

	if (Parent())
		SetViewColor(Parent()->ViewColor());
	else
		SetViewColor(216, 216, 216);

	if (fBgBitmap != NULL && fBgBitmap->Lock()) {
		fBgView->SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		fBgView->FillRect(SLIDER_RECT.OffsetToCopy(0.0, -2.0));
		fBgBitmap->Unlock();
	} else
		SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	Update(2);
}


void
ColorSlider::Draw(BRect updateRect)
{
	Update(0);
}


void
ColorSlider::FrameResized(float width, float height)
{
	if (fBgBitmap != NULL) {
		fBgBitmap->Lock();
		delete fBgBitmap;
	}

	fBgBitmap = new BBitmap(SLIDER_RECT, B_RGB32, true);
	if (fBgBitmap->IsValid() && fBgBitmap->Lock()) {
		fBgView = new BView(SLIDER_RECT, "", B_FOLLOW_NONE, B_WILL_DRAW);
		fBgBitmap->AddChild(fBgView);
		fBgView->SetOrigin(8.0, 2.0);
		fBgBitmap->Unlock();
	} else {
		delete fBgBitmap;
		fBgBitmap = NULL;
		fBgView = this;
	}

	Update(2);
}


status_t
ColorSlider::Invoke(BMessage* message)
{
	if (!message)
		message = Message();

	message->RemoveName("value");

	switch (fColorMode) {
		case R_SELECTED:
		case G_SELECTED:
		case B_SELECTED:
			message->AddFloat("value", 1.0 - (float)Value() / 255);
			break;

		case H_SELECTED:
			message->AddFloat("value", (1.0 - (float)Value() / 255) * 6);
			break;

		case S_SELECTED:
		case V_SELECTED:
			message->AddFloat("value", 1.0 - (float)Value() / 255);
			break;
	}

	return BControl::Invoke(message);
}


void
ColorSlider::MouseDown(BPoint where)
{
	Window()->Activate();

	fMouseDown = true;
	SetMouseEventMask(B_POINTER_EVENTS,
		B_SUSPEND_VIEW_FOCUS | B_LOCK_WINDOW_FOCUS);

	_TrackMouse(where);
	fMouseDown = true;
}


void
ColorSlider::MouseMoved(BPoint where, uint32 code, const BMessage* message)
{
	if (message != NULL || !fMouseDown)
		return;

	_TrackMouse(where);
}


void
ColorSlider::MouseUp(BPoint where)
{
	fMouseDown = false;
}


void
ColorSlider::SetValue(int32 value)
{
	value = max_c(min_c(value, 255), 0);
	if (value != Value()) {
		BControl::SetValue(value);

		Update(1);
	}
}


//	#pragma mark -


void
ColorSlider::OtherValues(float* value1, float* value2) const
{
	if (value1 && value2) {
		*value1 = fFixedValue1;
		*value2 = fFixedValue2;
	}
}


void
ColorSlider::SetOtherValues(float value1, float value2)
{
	fFixedValue1 = value1;
	fFixedValue2 = value2;

	if (fColorMode != H_SELECTED)
		Update(2);
}


void
ColorSlider::SetMarkerToColor(rgb_color color)
{
	float h = 0.0f;
	float s = 0.0f;
	float v = 0.0f;

	if ((fColorMode & (H_SELECTED | S_SELECTED | V_SELECTED)) != 0) {
		RGB_to_HSV((float)color.red / 255.0f, (float)color.green / 255.0f,
			(float)color.blue / 255.0f, h, s, v);
	}

	switch (fColorMode) {
		case R_SELECTED:
			SetValue(255 - color.red);
			break;

		case G_SELECTED:
			SetValue(255 - color.green);
			break;

		case B_SELECTED:
			SetValue(255 - color.blue);
			break;

		case H_SELECTED:
			SetValue(255.0 - round(h / 6.0 * 255.0));
			break;

		case S_SELECTED:
			SetValue(255.0 - round(s * 255.0));
			break;

		case V_SELECTED:
			SetValue(255.0 - round(v * 255.0));
			break;
	}
}


void
ColorSlider::SetModeAndValues(color_mode mode, float value1,
	float value2)
{
	float R(0);
	float G(0);
	float B(0);
	float h(0);
	float s(0);
	float v(0);

	fBgBitmap->Lock();

	switch (fColorMode) {
		case R_SELECTED:
			R = 255 - Value();
			G = round(fFixedValue1 * 255.0);
			B = round(fFixedValue2 * 255.0);
			break;

		case G_SELECTED:
			R = round(fFixedValue1 * 255.0);
			G = 255 - Value();
			B = round(fFixedValue2 * 255.0);
			break;

		case B_SELECTED:
			R = round(fFixedValue1 * 255.0);
			G = round(fFixedValue2 * 255.0);
			B = 255 - Value();
			break;

		case H_SELECTED:
			h = (1.0 - (float)Value() / 255.0) * 6.0;
			s = fFixedValue1;
			v = fFixedValue2;
			break;

		case S_SELECTED:
			h = fFixedValue1;
			s = 1.0 - (float)Value() / 255.0;
			v = fFixedValue2;
			break;

		case V_SELECTED:
			h = fFixedValue1;
			s = fFixedValue2;
			v = 1.0 - (float)Value() / 255.0;
			break;
	}

	if ((fColorMode & (H_SELECTED | S_SELECTED | V_SELECTED)) != 0) {
		HSV_to_RGB(h, s, v, R, G, B);
		R *= 255.0;
		G *= 255.0;
		B *= 255.0;
	}

	rgb_color color = { round(R), round(G), round(B), 255 };

	fColorMode = mode;
	SetOtherValues(value1, value2);
	fBgBitmap->Unlock();

	SetMarkerToColor(color);
	Update(2);
}


void
ColorSlider::Update(int depth)
{
	// depth
	// 0 = not onscreen
	// 1 = bitmap 1
	// 2 = bitmap 0

	if (depth == 2) {
		write_port(fUpdatePort, MSG_UPDATE, NULL, 0);
		return;
	}

	if (Parent() == NULL)
		return;

	rgb_color background = ui_color(B_PANEL_BACKGROUND_COLOR);
	rgb_color shadow = tint_color(background, B_DARKEN_1_TINT);
	rgb_color darkShadow = tint_color(background, B_DARKEN_3_TINT);
	rgb_color light = tint_color(background, B_LIGHTEN_MAX_TINT);

	if (depth >= 1) {
		fBgBitmap->Lock();

		BRect bounds(-8.0, -2.0, fBgView->Bounds().right - 8.0,
			fBgView->Bounds().bottom - 2.0);

		bounds.InsetBy(6.0, 0.0);

		// Frame
		fBgView->BeginLineArray(4);
		fBgView->AddLine(BPoint(bounds.left, bounds.bottom),
			BPoint(bounds.left, bounds.top), shadow);
		fBgView->AddLine(BPoint(bounds.left + 1.0, bounds.top),
			BPoint(bounds.right, bounds.top), shadow);
		fBgView->AddLine(BPoint(bounds.right, bounds.top + 1.0),
			BPoint(bounds.right, bounds.bottom), light);
		fBgView->AddLine(BPoint(bounds.right - 1.0, bounds.bottom),
			BPoint(bounds.left + 1.0, bounds.bottom), light);
		fBgView->EndLineArray();
		bounds.InsetBy(1.0, 1.0);

		fBgView->BeginLineArray(4);
		fBgView->AddLine(BPoint(bounds.left, bounds.bottom),
			BPoint(bounds.left, bounds.top), darkShadow);
		fBgView->AddLine(BPoint(bounds.left + 1.0, bounds.top),
			BPoint(bounds.right, bounds.top), darkShadow);
		fBgView->AddLine(BPoint(bounds.right, bounds.top + 1.0),
			BPoint(bounds.right, bounds.bottom), background);
		fBgView->AddLine(BPoint(bounds.right - 1.0, bounds.bottom),
			BPoint(bounds.left + 1.0, bounds.bottom), background);
		fBgView->EndLineArray();
		bounds.InsetBy(-7.0, -1.0);

		// Clear the area to the left and right of the slider
		fBgView->SetHighColor(background);
		fBgView->FillRect(BRect(bounds.left, bounds.top, bounds.left + 5.0,
			bounds.bottom));
		fBgView->FillRect(BRect(bounds.right - 5.0, bounds.top, bounds.right,
			bounds.bottom));

		// Marker
		fBgView->SetHighColor(0, 0, 0);
		float value = Value();

		fBgView->StrokeLine(BPoint(bounds.left, value - 2.0),
			BPoint(bounds.left + 5.0, value));
		fBgView->StrokeLine(BPoint(bounds.left, value + 2.0));
		fBgView->StrokeLine(BPoint(bounds.left, value - 2.0));

		fBgView->StrokeLine(BPoint(bounds.right, value - 2.0),
			BPoint(bounds.right - 5.0, value));
		fBgView->StrokeLine(BPoint(bounds.right, value + 2.0));
		fBgView->StrokeLine(BPoint(bounds.right, value - 2.0));

		fBgView->Sync();

		fBgBitmap->Unlock();
	}

	DrawBitmap(fBgBitmap);
}


//	#pragma mark -


void
ColorSlider::_DrawColorLine(BView *view, float y, int r, int g, int b)
{
	rgb_color color = {r, g, b, 255};
	y = 255.0 - y;

	view->AddLine(BPoint(0.0, y), BPoint(19.0, y), color);
}


void
ColorSlider::_TrackMouse(BPoint where)
{
	SetValue((int)where.y - 2);
	Invoke();
}


int32
ColorSlider::_UpdateThread(void* data)
{
	// initialization

	ColorSlider *colorSlider = (ColorSlider*)data;

	bool looperLocked = colorSlider->LockLooper();

	port_id	port = colorSlider->fUpdatePort;

	if (looperLocked)
		colorSlider->UnlockLooper();

	// draw

	float h, s, v, r, g, b;
	int R, G, B;

	int32 msg_code;
	char msg_buffer;

	while (true) {
		port_info info;

		do {
			read_port(port, &msg_code, &msg_buffer, sizeof(msg_buffer));
			get_port_info(port, &info);
		} while (info.queue_count);

		if (!colorSlider->LockLooper())
			continue;

		uint colormode = colorSlider->fColorMode;
		float fixedvalue1 = colorSlider->fFixedValue1;
		float fixedvalue2 = colorSlider->fFixedValue2;

		BBitmap* bitmap = colorSlider->fBgBitmap;
		BView* view = colorSlider->fBgView;

		bitmap->Lock();

		colorSlider->UnlockLooper();

		view->BeginLineArray(256);

		switch (colormode) {
			case R_SELECTED:
			{
				G = round(fixedvalue1 * 255);
				B = round(fixedvalue2 * 255);
				for (int R = 0; R < 256; ++R)
					_DrawColorLine(view, R, R, G, B);
				break;
			}

			case G_SELECTED:
			{
				R = round(fixedvalue1 * 255);
				B = round(fixedvalue2 * 255);
				for (int G = 0; G < 256; ++G)
					_DrawColorLine(view, G, R, G, B);
				break;
			}

			case B_SELECTED:
			{
				R = round(fixedvalue1 * 255);
				G = round(fixedvalue2 * 255);
				for (int B = 0; B < 256; ++B)
					_DrawColorLine(view, B, R, G, B);
				break;
			}

			case H_SELECTED:
			{
				s = 1.0;
				v = 1.0;
				for (int y = 0; y < 256; ++y) {
					HSV_to_RGB((float)y * 6.0 / 255.0, s, v, r, g, b);
					_DrawColorLine(view, y, r * 255, g * 255, b * 255);
				}
				break;
			}

			case S_SELECTED:
			{
				h = fixedvalue1;
				v = 1.0;
				for (int y = 0; y < 256; ++y)
				{
					HSV_to_RGB(h, (float)y / 255, v, r, g, b);
					_DrawColorLine(view, y, r * 255, g * 255, b * 255 );
				}
				break;
			}

			case V_SELECTED:
			{
				h = fixedvalue1;
				s = 1.0;
				for (int y = 0; y < 256; ++y) {
					HSV_to_RGB(h, s, (float)y / 255, r, g, b);
					_DrawColorLine(view, y, r * 255, g * 255, b * 255);
				}
				break;
			}
		}

		view->EndLineArray();
		view->Sync();
		bitmap->Unlock();

		if (colorSlider->LockLooper()) {
			colorSlider->Update(1);
			colorSlider->UnlockLooper();
		}
	}

	return B_OK;
}
