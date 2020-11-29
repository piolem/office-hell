// Fill out your copyright notice in the Description page of Project Settings.


#include "OHDialogComponent.h"
#include "OHCharacter.h"

// Sets default values for this component's properties
UOHDialogComponent::UOHDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOHDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOHDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bShouldDisplayResponses)
	{
		return;
	}

	if(ConversationTimer >= 0)
	{
		ConversationTimer -= DeltaTime;
	}
	else
	{
		ConversationTimer = 0;
		if(!bConversationEnded && !JumpToKey.IsEmpty())
		{
			NextConversationDialog(JumpToKey);
		}
		else
		{
			CurrentConversationDialog = "";
		}
	}
}

void UOHDialogComponent::StartConversation(UDataTable* ConversationData)
{
	CurrentConversationData = ConversationData;
	bConversationEnded = false;

	Play(FName(TEXT("start")));
}

void UOHDialogComponent::NextConversationDialog(FString Key)
{
	bShouldDisplayResponses = false;
	
	Play(FName(Key));
}

void UOHDialogComponent::EndConversation()
{
	bConversationEnded = true;
	bShouldDisplayResponses = false;
	if(AOHCharacter* OwnerCharacter = Cast<AOHCharacter>(GetOwner()))
	{
		OwnerCharacter->EndConversation();
	}

	CurrentConversationDialog = "";
}

void UOHDialogComponent::SkipDialog()
{
	ConversationTimer = 0;
}

void UOHDialogComponent::Play(FName Key)
{
	static const FString ContextString(TEXT("Conversation Row"));

	bShouldDisplayResponses = false;
	CurrentRequiredItemKey.Empty();
	
	FConversationRow* FirstDialog = CurrentConversationData->FindRow<FConversationRow>(Key, ContextString, true);
	
	if(FirstDialog)
	{
		CurrentConversationName = FirstDialog->Name;
		CurrentConversationDialog = FirstDialog->Dialog;

		if(FirstDialog->SoundCue)
		{
			EndDialogTime = FirstDialog->SoundCue->GetDuration();
		}
		else
		{
			const int SymbolsInDialog = FirstDialog->Dialog.Len();
			EndDialogTime = SymbolsInDialog * TextLifetimePerSymbol;
		}

		if(!FirstDialog->RequiredInventoryKey.IsNone())
		{
			bShouldDisplayResponses = true;
			CurrentRequiredItemKey = FirstDialog->RequiredInventoryKey.ToString();
		}
		
		if(FirstDialog->Responses)
		{
			bShouldDisplayResponses = true;

			Responses.Empty();
			for(auto It : FirstDialog->Responses->GetRowMap())
			{
				const auto Row = reinterpret_cast<FResponseSelectorRow*>(It.Value);
				Responses.Add(It.Key.ToString(), Row->Description);
				BranchKeys.Add(It.Key.ToString(), Row->BranchId);
			}
		}
		else if(FirstDialog->bEndsConversation)
		{
			ConversationTimer = EndDialogTime;
			bConversationEnded = true;
			
			if(AOHCharacter* OwnerCharacter = Cast<AOHCharacter>(GetOwner()))
			{
				OwnerCharacter->EndConversation();
			}
		}
		else
		{
			ConversationTimer = EndDialogTime;
			JumpToKey = FirstDialog->NextDialogKey.ToString();
			// todo implement
		}
	}
}


