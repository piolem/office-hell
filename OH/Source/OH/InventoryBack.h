// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
constexpr long MaxInventorySlots = 20;
const std::string EmptyInventorySlot = "empty";

/**
 * 
 */
class OH_API InventoryBack
{
	std::string Slot[MaxInventorySlots];
public:
	InventoryBack();
	~InventoryBack();
	bool check_item(std::string it);
	bool add_item(std::string it);
	bool remove_item(std::string it);
};
