#pragma once

struct UIItem {
	float originX, originY;
	float sizeX, sizeY;

	UIItem() {}

	UIItem(UIItem& item) {
		this->originX = item.originX;
		this->originY = item.originY;
		this->sizeX = item.sizeX;
		this->sizeY = item.sizeY;
	}
};