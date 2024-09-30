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

USearchBar::USearchBar(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}

TSharedRef<SWidget> USearchBar::RebuildWidget()
{
    // Create the Slate search bar widget
    SlateSearchWidget = SNew(SSearchBox)
        .InitialText(InitialText)
        .OnTextChanged_Lambda([this](const FText& InSearchText)
            {
                HandleSearchTextChanged(InSearchText);  // Call the function safely
            })
        .OnTextCommitted_Lambda([this](const FText& InSearchText, ETextCommit::Type CommitType)
            {
                HandleSearchTextCommitted(InSearchText, CommitType);  // Call the function safely
            });

            return SlateSearchWidget.ToSharedRef();

    return SlateSearchWidget.ToSharedRef();
}

void USearchBar::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    // Reset the Slate search box widget to release it from memory
    SlateSearchWidget.Reset();
}

void USearchBar::HandleSearchTextChanged(const FText& InSearchText)
{
    // Broadcast changed text to be intercepted by Blueprints
    OnSearchTextChanged.Broadcast(InSearchText);
}

void USearchBar::HandleSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType)
{
    // Broadcast committed text and commit type to be intercepted by Blueprints
    OnSearchTextCommitted.Broadcast(InSearchText, CommitType);
}
