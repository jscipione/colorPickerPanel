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
#include <MenuField.h>
#include <MenuItem.h>
#include <Message.h>
#include <MimeType.h>
#include <Point.h>
#include <PopUpMenu.h>
#include <Rect.h>
#include <Resources.h>
#include <Roster.h>
#include <Size.h>
#include <View.h>
#include <Window.h>

#include <string.h>

#include "ColorWell.h"


static const uint32 kMsgTriangle = 'tria';
static const uint32 kMsgSquare = 'squa';
static const uint32 kMsgCircle = 'circ';

static const uint32 kMsgSetPreferredColorPicker = 'spcp';

static const char* kHaikuColorPickerSignature
	= "application/x-vnd.Haiku-ColorPicker";
static const char* kSimpleColorPickerSignature
	= "application/x-vnd.Haiku-SimpleColorPicker";


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
	BView("ColorPickerClientView", B_WILL_DRAW),
	fPickerMenu(new BPopUpMenu("pickerMenu"))
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
		fTriangleColorWell->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED,
			B_SIZE_UNSET));
		fSquareColorWell = new BColorWell("Square", "square color",
			(rgb_color){ 0, 255, 0 });
		fSquareColorWell->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED,
			B_SIZE_UNSET));
		fCircleColorWell = new BColorWell("Circle", "circle color",
			(rgb_color){ 0, 0, 255 });
		fCircleColorWell->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED,
			B_SIZE_UNSET));

		// add the default color picker item
		BMessage message(kMsgSetPreferredColorPicker);
		message.AddString("signature", kSimpleColorPickerSignature);
		BMenuItem* defaultItem = new BMenuItem("Default", new BMessage(message));
		fPickerMenu->AddItem(defaultItem);
		defaultItem->SetMarked(true);

		// add additional color picker items (if available)
		BMimeType haikuColorPicker(kHaikuColorPickerSignature);
		BMessage supportingApps;
		if (haikuColorPicker.GetSupportingApps(&supportingApps) == B_OK) {
			int32 subs = 0;
			supportingApps.FindInt32("be:sub", &subs);
			if (subs > 0)
				fPickerMenu->AddSeparatorItem();

			for (int32 i = 0; i < subs; i++) {
				const char* signature;
				if (supportingApps.FindString("applications", i, &signature) != B_OK)
					break;

				message.RemoveName("signature");
				message.AddString("signature", signature);
				entry_ref entry;
				const char* itemName = be_roster->FindApp(signature, &entry) == B_OK
					? entry.name : signature;
				BMenuItem* item = new BMenuItem(itemName, new BMessage(message));
				fPickerMenu->AddItem(item);
				char preferredSignature[B_MIME_TYPE_LENGTH];
				if (haikuColorPicker.GetPreferredApp(preferredSignature) == B_OK
					&& preferredSignature != NULL
					&& strcasecmp(preferredSignature, signature) == 0) {
					item->SetMarked(true);
				}
			}
		}

		BMenuField* pickerField = new BMenuField("pickerField", "Color picker: ",
			fPickerMenu);

		BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
			.Add(pickerField)
			.AddStrut(B_USE_DEFAULT_SPACING)
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

		fPickerMenu->SetTargetForItems(this);
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
					fTriangleColorWell->SetMessage(new BMessage(kMsgTriangle));
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
					fSquareColorWell->SetMessage(new BMessage(kMsgSquare));
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
					fCircleColorWell->SetMessage(new BMessage(kMsgCircle));
				}
				break;
			}

			case kMsgSetPreferredColorPicker:
			{
				const char* signature;
				if (message->FindString("signature", &signature) != B_OK)
					break;

				BMimeType haikuColorPicker(kHaikuColorPickerSignature);
				BMessage supportingApps;
				if (haikuColorPicker.GetSupportingApps(&supportingApps) != B_OK)
					break;

				const char* application = NULL;
				for (int32 i = 0;
						supportingApps.FindString("applications", i, &application) == B_OK;
						i++) {
					if (strcasecmp(application, signature) == 0) {
						haikuColorPicker.SetPreferredApp(signature);
						break;
					}
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

	BPopUpMenu*			fPickerMenu;
};


status_t
get_app_resources(BResources& resources)
{
	app_info info;
	status_t status = be_app->GetAppInfo(&info);
	if (status != B_OK)
		return status;

	return resources.SetTo(&info.ref);
}


class ColorPickerClient : public BApplication {
public:
	ColorPickerClient()
	:
	BApplication("application/x-vnd.Haiku-ColorPickerClient")
	{
		BMimeType haikuColorPicker(kHaikuColorPickerSignature);
		haikuColorPicker.SetShortDescription("Haiku color picker");

		BResources resources;
		if (get_app_resources(resources) == B_OK) {
			size_t size;
			const void* data = resources.LoadResource(B_VECTOR_ICON_TYPE,
				(int32)0, &size);
			haikuColorPicker.SetIcon((uint8*)data, size);
		}

		if (!haikuColorPicker.IsInstalled())
			haikuColorPicker.Install();

		haikuColorPicker.SetPreferredApp(kSimpleColorPickerSignature);
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
