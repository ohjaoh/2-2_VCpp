#include <iostream>
#include <chrono>
#include <windows.h>
using namespace std; // 표준 네임스페이스에 정의되어 있는 것들을 사용하겠다.
using namespace std::chrono; // 표준 네임스페이스에 정의된 chrono의 것들을 사용하겠다.
int main() {

	while (1) {
		int escPressed = 0;
		int index = 0;
		chrono::milliseconds waitTime(300);
		bool check = false; 

		cout << "기술커멘드" << endl;
		while (1) {

			if (GetAsyncKeyState(VK_ESCAPE)) {// esc키라면 바로 즉시종료
				escPressed = 1; // esc눌림여부확인
				break; //입력 while문 탈출
			}

			if (GetAsyncKeyState(VK_RIGHT)) {
				time_point<system_clock> startTime = system_clock::now();
				if (GetAsyncKeyState(VK_DOWN)) {
					if (GetAsyncKeyState(VK_DOWN)) {
						if (GetAsyncKeyState('A')) {
							cout << "아따라야" << endl;
						}
					}
				}
			}
			if (GetAsyncKeyState(VK_DOWN)) {
			}
			if (GetAsyncKeyState('A')) {
			}
		}

		if (escPressed) {
			cout << "\n프로그램이 종료됩니다.\n" << endl;
			break;//1번째 while문 종료
		}

		cout << "\n" << endl;
	}

	return 0;
}
