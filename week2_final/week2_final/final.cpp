#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main() {

	printf("=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|  201907022        |\n");
	printf("|  오자현의         |\n");
	printf("|  Application      |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=\n");

	while (1) {
		char input;
		int escPressed = 0;
		int index = 0;
		char str[5] = { ' ',' ' };

		printf("command>");
		while (1) {
			if (_kbhit()) {// 키입력확인
				input = _getch(); // 키 입력 받기
				if (input == 27) { // esc키라면 바로 즉시종료
					escPressed = 1; // esc눌림여부확인
					break; //입력 while문 탈출
				}
				else if (input == '\r') { // 엔터키를 감지 
					break;
				}
				else {
					putchar(input); // 입력된 값을 바로 출력

					str[index] = input; // 배열에 값 담기 근데 여러글자를 집어넣으면 밀리면서 맨 뒤의 글자 2개만 들어감 근데 상관없음 두개이상 들어가면 잘못이라고 출력할거라서
					index = (index + 1) % 2;// 인덱스는 0과 1만가능하게 하고 +1
				}

			}

		}

		for (int i = 0; i < 2; i++) {
			if (str[1] > ' ') { // 배열의2번째자리str[1]에 값이 있다는 것은 한글자입력이 아니라는 것이므로 잘못된입력이라고 출력
				printf("\n잘못된 입력");
				break; // str[1]에 값이있지만 str[0]의 값도 있으니 아래의 조건문에 들어가는 것을 막기위함
			}
			if (str[0] == 'q') {// 만약 배열의 첫번째 자리str[0]가 qwer이라면 아래 조건문 실행
				printf("\nqwer 화이팅!");
				break; // 2번반복되는 것을 막기위한 브레이크 이하동일
			}
			else if (str[0] == 'w') {
				printf("\n과제 너무 좋다");
				break;
			}
			else if (str[0] == 'e') {
				printf("\n담주부턴 과제량 3배다");
				break;
			}
			else if (str[0] == 'r') {
				printf("\n행복합니다.");
				break;
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
