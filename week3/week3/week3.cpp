#include <stdio.h>
#include <windows.h>

int main() {

	while (1) {
		int escPressed = 0;
		int index = 0;

		printf("���Ŀ���");
		while (1) {
			Sleep(300);
			if (GetAsyncKeyState(VK_ESCAPE)) {// escŰ��� �ٷ� �������
				escPressed = 1; // esc��������Ȯ��
				break; //�Է� while�� Ż��
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				printf("����Ű�Է�");
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				printf("�Ʒ�����Ű�Է�");
			}
			if (GetAsyncKeyState('A') ){
				printf("aŰ�Է�");
			}
		}

		if (escPressed) {
			printf("\n���α׷��� ����˴ϴ�.\n");
			break;//1��° while�� ����
		}

		printf("\n");
	}

	return 0;
}
