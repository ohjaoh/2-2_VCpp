#pragma once

struct Data {
	int contentID;

	int startCoordX;
	int startCoordY;

	int endCoordX;
	int endCoordY;

	struct Data *prevData; // ���� ������

};

void push(struct Data data);

struct Data pop() {
	struct Data* result = Top;
	Top = result->prevData;
	return reuslt;
}