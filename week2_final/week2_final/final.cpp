#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main() {

	printf("=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|  201907022        |\n");
	printf("|  ��������         |\n");
	printf("|  Application      |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=\n");

	while (1) {
		char input;
		int escPressed = 0;
		int index = 0;
		char str[5] = { ' ',' ' };

		printf("command>");
		while (1) {
			if (_kbhit()) {// Ű�Է�Ȯ��
				input = _getch(); // Ű �Է� �ޱ�
				if (input == 27) { // escŰ��� �ٷ� �������
					escPressed = 1; // esc��������Ȯ��
					break; //�Է� while�� Ż��
				}
				else if (input == '\r') { // ����Ű�� ���� 
					break;
				}
				else {
					putchar(input); // �Էµ� ���� �ٷ� ���

					str[index] = input; // �迭�� �� ��� �ٵ� �������ڸ� ��������� �и��鼭 �� ���� ���� 2���� �� �ٵ� ������� �ΰ��̻� ���� �߸��̶�� ����ҰŶ�
					index = (index + 1) % 2;// �ε����� 0�� 1�������ϰ� �ϰ� +1
				}

			}

		}

		for (int i = 0; i < 2; i++) {
			if (str[1] > ' ') { // �迭��2��°�ڸ�str[1]�� ���� �ִٴ� ���� �ѱ����Է��� �ƴ϶�� ���̹Ƿ� �߸����Է��̶�� ���
				printf("\n�߸��� �Է�");
				break; // str[1]�� ���������� str[0]�� ���� ������ �Ʒ��� ���ǹ��� ���� ���� ��������
			}
			if (str[0] == 'q') {// ���� �迭�� ù��° �ڸ�str[0]�� qwer�̶�� �Ʒ� ���ǹ� ����
				printf("\nqwer ȭ����!");
				break; // 2���ݺ��Ǵ� ���� �������� �극��ũ ���ϵ���
			}
			else if (str[0] == 'w') {
				printf("\n���� �ʹ� ����");
				break;
			}
			else if (str[0] == 'e') {
				printf("\n���ֺ��� ������ 3���");
				break;
			}
			else if (str[0] == 'r') {
				printf("\n�ູ�մϴ�.");
				break;
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
