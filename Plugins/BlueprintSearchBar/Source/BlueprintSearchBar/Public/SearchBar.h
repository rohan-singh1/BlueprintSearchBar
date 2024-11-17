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
 *
 */
UCLASS(BlueprintType)
class BLUEPRINTSEARCHBAR_API USearchBar : public UWidget
{
	GENERATED_BODY()

public:
	// Function to construct the Slate widget
	virtual TSharedRef<SWidget> RebuildWidget() override;

	// Function to release Slate resources
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	// Constructor
	USearchBar(const FObjectInitializer& ObjectInitializer);

	// Declare a dynamic multicast delegate for search text changes
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchTextChanged, const FText&, Text);

	// Declare a dynamic multicast delegate for search text commit
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSearchTextCommitted, const FText&, Text, ETextCommit::Type, CommitType);

	// Initial text (if any)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Search Bar")
	FText InitialText;

	// Delegate to signal search text changed
	UPROPERTY(BlueprintAssignable, Category = "Blueprint Search Bar")
	FOnSearchTextChanged OnSearchTextChanged;

	// Delegate to signal search text committed
	UPROPERTY(BlueprintAssignable, Category = "Blueprint Search Bar")
	FOnSearchTextCommitted OnSearchTextCommitted;


private:
	TSharedPtr<SSearchBox> SlateSearchWidget;
	void HandleSearchTextChanged(const FText& InSearchText);
	void HandleSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType);
};
