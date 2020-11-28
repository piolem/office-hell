// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class OH_API InventoryBack
{
public:
	InventoryBack();
	~InventoryBack();
	bool check_item(std::string it);
	bool add_item(std::string it);
	bool remove_item(std::string it);

	static constexpr long MaxInventorySlots = 20;
	static std::string EmptyInventorySlot;

	std::string Slot[MaxInventorySlots];
};
