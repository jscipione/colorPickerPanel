/*
 * Copyright 2012-2013 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include <Application.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <Message.h>
#include <MimeType.h>
#include <Point.h>
#include <Rect.h>
#include <Size.h>
#include <View.h>
#include <Window.h>

#include "ColorWell.h"


static const uint32 kMsgTriangle = 'tria';
static const uint32 kMsgSquare = 'squa';
static const uint32 kMsgCircle = 'circ';


class TriangleView : public BView {
public:
	TriangleView(BRect frame, const char* name, uint32 resizingMode,
		uint32 flags)
	:
	BView(frame, name, resizingMode, flags)
	{
		SetExplicitMinSize(BSize(frame.Width(), frame.Height()));
		SetExplicitMaxSize(BSize(frame.Width(), frame.Height()));
		SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		fColor = (rgb_color) { 0, 0, 0 };
	}

	virtual void Draw(BRect updateRect)
	{
		SetHighColor(fColor);
		FillTriangle(BPoint(Bounds().Width() / 2, 0),
			BPoint(0, Bounds().Height()),
			BPoint(Bounds().Width(), Bounds().Height()));
	}

	void SetColor(rgb_color color)
	{
		fColor = color;
	}

private:
	rgb_color fColor;
};


class SquareView : public BView {
public:
	SquareView(BRect frame, const char* name, uint32 resizingMode,
		uint32 flags)
	:
	BView(frame, name, resizingMode, flags)
	{
		SetExplicitMinSize(BSize(frame.Width(), frame.Height()));
		SetExplicitMaxSize(BSize(frame.Width(), frame.Height()));
		SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		fColor = (rgb_color) { 0, 0, 0 };
	}

	virtual void Draw(BRect updateRect)
	{
		SetHighColor(fColor);
		FillRect(Bounds());
	}

	void SetColor(rgb_color color)
	{
		fColor = color;
	}

private:
	rgb_color fColor;
};


class CircleView : public BView {
public:
	CircleView(BRect frame, const char* name, uint32 resizingMode,
		uint32 flags)
	:
	BView(frame, name, resizingMode, flags)
	{
		SetExplicitMinSize(BSize(frame.Width(), frame.Height()));
		SetExplicitMaxSize(BSize(frame.Width(), frame.Height()));
		SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		fColor = (rgb_color) { 0, 0, 0 };
	}

	virtual void Draw(BRect updateRect)
	{
		SetHighColor(fColor);
		FillEllipse(Bounds());
	}

	void SetColor(rgb_color color)
	{
		fColor = color;
	}

private:
	rgb_color fColor;
};


class ColorPickerClientView : public BView {
public:
	ColorPickerClientView()
	:
	BView("ColorPickerClientView", B_WILL_DRAW)
	{
		fTriangle = new TriangleView(BRect(0, 0, 40, 40), "triangle",
			B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
		fTriangle->SetColor((rgb_color){ 255, 0, 0 });
		fSquare = new SquareView(BRect(0, 0, 40, 40), "square",
			B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
		fSquare->SetColor((rgb_color){ 0, 255, 0 });
		fCircle = new CircleView(BRect(0, 0, 40, 40), "circle",
			B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
		fCircle->SetColor((rgb_color){ 0, 0, 255 });

		fTriangleColorWell = new BColorWell("Triangle", "triangle color",
			(rgb_color){ 255, 0, 0 });
		fSquareColorWell = new BColorWell("Square", "square color",
			(rgb_color){ 0, 255, 0 });
		fCircleColorWell = new BColorWell("Circle", "circle color",
			(rgb_color){ 0, 0, 255 });

		BLayoutBuilder::Group<>(this)
			.AddGroup(B_VERTICAL, 0)
				.Add(fTriangleColorWell)
				.Add(fSquareColorWell)
				.Add(fCircleColorWell)
				.AddStrut(20)
				.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING)
					.Add(fTriangle)
					.Add(fSquare)
					.Add(fCircle)
				.End()
				.SetInsets(B_USE_DEFAULT_SPACING)
			.End();
	}

	virtual void AttachedToWindow()
	{
		fTriangleColorWell->SetMessage(new BMessage(kMsgTriangle));
		fTriangleColorWell->SetTarget(this);

		fSquareColorWell->SetMessage(new BMessage(kMsgSquare));
		fSquareColorWell->SetTarget(this);

		fCircleColorWell->SetMessage(new BMessage(kMsgCircle));
		fCircleColorWell->SetTarget(this);
	}

	virtual void MessageReceived(BMessage* message)
	{
		switch (message->what) {
			case kMsgTriangle:
			{
				char* nameFound;
				type_code typeFound;
				if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
						!= B_OK) {
					BView::MessageReceived(message);
					return;
				}

				rgb_color* color;
				ssize_t numBytes;
				if (message->FindData(nameFound, typeFound, (const void **)&color,
						&numBytes) == B_OK) {
					fTriangle->SetColor(*color);
					fTriangle->Invalidate();
				}
				break;
			}

			case kMsgSquare:
			{
				char* nameFound;
				type_code typeFound;
				if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
						!= B_OK) {
					BView::MessageReceived(message);
					return;
				}
	
				rgb_color* color;
				ssize_t numBytes;
				if (message->FindData(nameFound, typeFound, (const void **)&color,
						&numBytes) == B_OK) {
					fSquare->SetColor(*color);
					fSquare->Invalidate();
				}
				break;
			}

			case kMsgCircle:
			{
				char* nameFound;
				type_code typeFound;
				if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &nameFound, &typeFound)
						!= B_OK) {
					BView::MessageReceived(message);
					return;
				}
	
				rgb_color* color;
				ssize_t numBytes;
				if (message->FindData(nameFound, typeFound, (const void **)&color,
						&numBytes) == B_OK) {
					fCircle->SetColor(*color);
					fCircle->Invalidate();
				}
				break;
			}

			default:
				BView::MessageReceived(message);
		}
	}

private:
	TriangleView*		fTriangle;
	SquareView*			fSquare;
	CircleView*			fCircle;

	BColorWell*			fTriangleColorWell;
	BColorWell*			fSquareColorWell;
	BColorWell*			fCircleColorWell;
};


class ColorPickerClient : public BApplication {
public:
	ColorPickerClient()
	:
	BApplication("application/x-vnd.Haiku.ColorPickerSample")
	{
		BMimeType type("application/x-vnd.Haiku.ColorPicker");
		type.SetShortDescription("Color picker");
		if (!type.IsInstalled())
			type.Install();

		type.SetPreferredApp("SimpleColorPicker");
	}

protected:
	virtual void ReadyToRun()
	{
		BWindow* window = new BWindow(BRect(200, 200, 300, 300),
			"Example app", B_TITLED_WINDOW, B_NOT_ZOOMABLE
				| B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE
				| B_AUTO_UPDATE_SIZE_LIMITS);
		window->SetLayout(new BGroupLayout(B_HORIZONTAL, 0));
		window->GetLayout()->AddView(new ColorPickerClientView());
		window->Show();
	}
};


int
main()
{
	ColorPickerClient app;
	app.Run();

	return 0;
}
