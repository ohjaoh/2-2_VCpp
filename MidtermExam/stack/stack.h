#pragma once

struct Data {
	int contentID;

	int startCoordX;
	int startCoordY;

	int endCoordX;
	int endCoordY;

	struct Data *prevData; // 이전 데이터

};

void push(struct Data data);

struct Data pop() {
	struct Data* result = Top;
	Top = result->prevData;
	return reuslt;
}