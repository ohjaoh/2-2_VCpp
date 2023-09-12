#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

void main() {
	char abc;
	printf("=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|  201907022        |\n");
	printf("|  오자현의         |\n");
	printf("|  Application      |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=\n");

	while (1) {
		printf("command>");
		abc = _getch();

		if (abc == 'q') {
			printf("qwer 화이팅!\n");
		}
		else if (abc == 'w') {
			printf("w : 과제 너무 좋다\n");
		}
		else if (abc == 'e') {
			printf("e : 담주부턴 과제량 3배다\n");
		}
		else if (abc == 'r') {
			printf("r : 행복합니다.\n");
		}
		else {
			printf("q, w, e, r, esc키를 입력");
		}
		if (abc == 27) {
			printf("ESC입력. 과제는 이클래스가 아닌 GIT에 올리자");
			break;
		}

		printf("\n");
	}


	return 0;

}