#include <stdio.h>
#include <windows.h>

int main() {

	while (1) {
		int escPressed = 0;
		int index = 0;

		printf("기술커멘드");
		while (1) {
			Sleep(300);
			if (GetAsyncKeyState(VK_ESCAPE)) {// esc키라면 바로 즉시종료
				escPressed = 1; // esc눌림여부확인
				break; //입력 while문 탈출
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				printf("우측키입력");
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				printf("아래방향키입력");
			}
			if (GetAsyncKeyState('A') ){
				printf("a키입력");
			}
		}

		if (escPressed) {
			printf("\n프로그램이 종료됩니다.\n");
			break;//1번째 while문 종료
		}

		printf("\n");
	}

	return 0;
}
