#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

void main() {
	char abc;

	printf("  201907022\n");
	printf("  오자현의\n");
	printf("  Application\n");

	while (1) {
		printf("command>");
		abc = _getch();

		if (abc == 'p') {
			printf("p입력. 나는 과제를 겁나 잘하는학생이다\n");
		}
		else if (abc == 'f') {
			printf("f입력. 나는 과제가 너무 즐겁다\n");
		}
		else if (abc == 'j') {
			printf("j입력. 교수님 과제 더 내주세요\n");
		}
		else {
			printf("p, j, f, esc키를 입력");
		}
		if (abc == 27) {
			printf("ESC입력. 과제는 이클래스가 아닌 GIT에 올리자");
			break;
		}

		printf("\n");
	}


	return 0;

}