// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"

#include "OHDialogComponent.generated.h"

USTRUCT(BlueprintType)
struct FResponseSelectorRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BranchId;
};

USTRUCT(BlueprintType)
struct FConversationRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Dialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* Responses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndsConversation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextDialogKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RequiredInventoryKey;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OH_API UOHDialogComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOHDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartConversation(class UDataTable* ConversationData);
	UFUNCTION(BlueprintCallable)
	void NextConversationDialog(FString Key);
	UFUNCTION(BlueprintCallable)
	void EndConversation();
	UFUNCTION(BlueprintCallable)
	void SkipDialog();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Data)
	FString CurrentConversationName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Data)
	FString CurrentConversationDialog;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Data)
	FString CurrentRequiredItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextLifetimePerSymbol = 0.09f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseVoiceOverTimingIfAvailable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Data)
	class UDataTable* CurrentConversationData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Data)
	bool bShouldDisplayResponses = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Data)
	TMap<FString, FString> Responses;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Data)
	TMap<FString, FString> BranchKeys;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Data)
	bool bConversationEnded = false;

private:
	void Play(FName Key);

	float ConversationTimer;
	float EndDialogTime;
	FString JumpToKey;
	
};
