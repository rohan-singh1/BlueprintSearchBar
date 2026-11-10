//
// Blueprint Search Bar
// 
// Slate search bar exposed to Blueprints
//
// The MIT License (MIT)
//
// Copyright (c) 2024 Rohan Singh
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.



#include "SearchBar.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Input/SSearchBox.h"

#define LOCTEXT_NAMESPACE "BlueprintSearchBar"

USearchBar::USearchBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HintText = LOCTEXT("DefaultHint", "Search");
}

TSharedRef<SWidget> USearchBar::RebuildWidget()
{
	SlateSearchWidget = SNew(SSearchBox)
		.InitialText(InitialText)
		.HintText(HintText)
		.SelectAllTextWhenFocused(bSelectAllTextWhenFocused)
		.DelayChangeNotificationsWhileTyping(bDelayChangeNotificationsWhileTyping)
		.DelayChangeNotificationsWhileTypingSeconds(DelayChangeNotificationsSeconds)
		.MinDesiredWidth(MinDesiredWidth)
		// UObject-bound delegates are skipped safely if this widget has been garbage collected.
		.OnTextChanged(FOnTextChanged::CreateUObject(this, &USearchBar::HandleSearchTextChanged))
		.OnTextCommitted(FOnTextCommitted::CreateUObject(this, &USearchBar::HandleSearchTextCommitted));

	return SlateSearchWidget.ToSharedRef();
}

void USearchBar::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (SlateSearchWidget.IsValid())
	{
		SlateSearchWidget->SetHintText(HintText);
	}
}

void USearchBar::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	SlateSearchWidget.Reset();
}

FText USearchBar::GetText() const
{
	return SlateSearchWidget.IsValid() ? SlateSearchWidget->GetText() : InitialText;
}

void USearchBar::SetText(const FText& InText)
{
	InitialText = InText;
	if (SlateSearchWidget.IsValid())
	{
		SlateSearchWidget->SetText(InText);
	}
}

void USearchBar::ClearText()
{
	SetText(FText::GetEmpty());
}

FText USearchBar::GetHintText() const
{
	return HintText;
}

void USearchBar::SetHintText(const FText& InHintText)
{
	HintText = InHintText;
	if (SlateSearchWidget.IsValid())
	{
		SlateSearchWidget->SetHintText(InHintText);
	}
}

void USearchBar::FocusSearchBar()
{
	if (SlateSearchWidget.IsValid() && FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().SetKeyboardFocus(SlateSearchWidget, EFocusCause::SetDirectly);
	}
}

void USearchBar::HandleSearchTextChanged(const FText& InSearchText)
{
	OnSearchTextChanged.Broadcast(InSearchText);
}

void USearchBar::HandleSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType)
{
	OnSearchTextCommitted.Broadcast(InSearchText, CommitType);
}

#if WITH_EDITOR
const FText USearchBar::GetPaletteCategory()
{
	return LOCTEXT("PaletteCategory", "Input");
}
#endif

#undef LOCTEXT_NAMESPACE
