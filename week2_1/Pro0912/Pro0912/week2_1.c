#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

void main() {
	char abc;

	printf("  201907022\n");
	printf("  ��������\n");
	printf("  Application\n");

	while (1) {
		printf("command>");
		abc = _getch();

		if (abc == 'p') {
			printf("p�Է�. ���� ������ �̳� ���ϴ��л��̴�\n");
		}
		else if (abc == 'f') {
			printf("f�Է�. ���� ������ �ʹ� ��̴�\n");
		}
		else if (abc == 'j') {
			printf("j�Է�. ������ ���� �� ���ּ���\n");
		}
		else {
			printf("p, j, f, escŰ�� �Է�");
		}
		if (abc == 27) {
			printf("ESC�Է�. ������ ��Ŭ������ �ƴ� GIT�� �ø���");
			break;
		}

		printf("\n");
	}


	return 0;

}