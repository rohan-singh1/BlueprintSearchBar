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


#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SearchBar.generated.h"

class SSearchBox;

/**
 * The native Slate search box (magnifying glass, clear button, hint text) as a UMG widget.
 * Works in runtime UI and in Editor Utility Widgets.
 */
UCLASS(BlueprintType, meta = (DisplayName = "Search Bar"))
class BLUEPRINTSEARCHBAR_API USearchBar : public UWidget
{
	GENERATED_BODY()

public:
	USearchBar(const FObjectInitializer& ObjectInitializer);

	// Declared inside the class (as in v1.0) so existing Blueprint bindings keep working.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchTextChanged, const FText&, Text);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSearchTextCommitted, const FText&, Text, ETextCommit::Type, CommitType);

	/** Text shown in the search bar when it is first created. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Search Bar")
	FText InitialText;

	/** Grey placeholder text shown while the search bar is empty. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint Search Bar")
	FText HintText;

	/** Select all existing text when the search bar gains focus. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint Search Bar")
	bool bSelectAllTextWhenFocused = true;

	/** Wait until the user pauses typing before firing On Search Text Changed. Turn off to fire on every keystroke. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint Search Bar")
	bool bDelayChangeNotificationsWhileTyping = true;

	/** How long to wait after the last keystroke, when delaying change notifications. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bDelayChangeNotificationsWhileTyping"), Category = "Blueprint Search Bar")
	float DelayChangeNotificationsSeconds = 0.25f;

	/** Minimum width of the search bar. 0 uses the default. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Blueprint Search Bar")
	float MinDesiredWidth = 0.f;

	/** Fires when the search text changes, including when the clear button is pressed. */
	UPROPERTY(BlueprintAssignable, Category = "Blueprint Search Bar")
	FOnSearchTextChanged OnSearchTextChanged;

	/** Fires when the user presses Enter or the search bar loses focus. */
	UPROPERTY(BlueprintAssignable, Category = "Blueprint Search Bar")
	FOnSearchTextCommitted OnSearchTextCommitted;

	/** Current text in the search bar. */
	UFUNCTION(BlueprintPure, Category = "Blueprint Search Bar")
	FText GetText() const;

	/** Replace the text in the search bar. Fires On Search Text Changed. */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Search Bar")
	void SetText(const FText& InText);

	/** Empty the search bar. Fires On Search Text Changed with empty text. */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Search Bar")
	void ClearText();

	UFUNCTION(BlueprintPure, Category = "Blueprint Search Bar")
	FText GetHintText() const;

	UFUNCTION(BlueprintCallable, Category = "Blueprint Search Bar")
	void SetHintText(const FText& InHintText);

	/** Move keyboard focus into the search bar so the user can type straight away. */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Search Bar")
	void FocusSearchBar();

	//~ UWidget interface
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<SSearchBox> SlateSearchWidget;

	void HandleSearchTextChanged(const FText& InSearchText);
	void HandleSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType);
};
