#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

void main() {
	char abc;
	printf("=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|  201907022        |\n");
	printf("|  ��������         |\n");
	printf("|  Application      |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=\n");

	while (1) {
		printf("command>");
		abc = _getch();

		if (abc == 'q') {
			printf("qwer ȭ����!\n");
		}
		else if (abc == 'w') {
			printf("w : ���� �ʹ� ����\n");
		}
		else if (abc == 'e') {
			printf("e : ���ֺ��� ������ 3���\n");
		}
		else if (abc == 'r') {
			printf("r : �ູ�մϴ�.\n");
		}
		else {
			printf("q, w, e, r, escŰ�� �Է�");
		}
		if (abc == 27) {
			printf("ESC�Է�. ������ ��Ŭ������ �ƴ� GIT�� �ø���");
			break;
		}

		printf("\n");
	}


	return 0;

}