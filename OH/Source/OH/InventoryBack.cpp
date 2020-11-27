// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBack.h"

InventoryBack::InventoryBack()
{

	for (long i = 0; i < MaxInventorySlots; ++i)
		this->Slot[i] = EmptyInventorySlot;
}

InventoryBack::~InventoryBack()
{
}


bool InventoryBack::check_item(std::string it) {
	for (long i = 0; i < MaxInventorySlots; ++i)
		if(this->Slot[i] == it) return true;
		
	return false;
}
bool InventoryBack::add_item(std::string it) {
	if (check_item(it)) return false;
	for (long i = 0; i < MaxInventorySlots; ++i)
		if (this->Slot[i] == EmptyInventorySlot) {
			this->Slot[i] = it;
			return true;
		}

	return false;
}
bool InventoryBack::remove_item(std::string it) {
	if (!check_item(it)) return false;
	for (long i = 0; i < MaxInventorySlots; ++i)
		if (this->Slot[i] == it) {
			this->Slot[i] = EmptyInventorySlot;
			return true;
		}
	return false;
}