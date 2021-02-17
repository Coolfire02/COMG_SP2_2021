#pragma once

struct UIItem {
	float originX, originY;
	float sizeOfQuad;

	UIItem() {}

	UIItem(UIItem& item) {
		this->originX = item.originX;
		this->originY = item.originY;
		this->sizeOfQuad = item.sizeOfQuad;
	}
};