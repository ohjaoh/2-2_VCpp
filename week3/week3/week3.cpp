#include <iostream>
#include <chrono>
#include <windows.h>
using namespace std; // ǥ�� ���ӽ����̽��� ���ǵǾ� �ִ� �͵��� ����ϰڴ�.
using namespace std::chrono; // ǥ�� ���ӽ����̽��� ���ǵ� chrono�� �͵��� ����ϰڴ�.
int main() {

	while (1) {
		int escPressed = 0;
		int index = 0;
		chrono::milliseconds waitTime(300);
		bool check = false; 

		cout << "���Ŀ���" << endl;
		while (1) {

			if (GetAsyncKeyState(VK_ESCAPE)) {// escŰ��� �ٷ� �������
				escPressed = 1; // esc��������Ȯ��
				break; //�Է� while�� Ż��
			}

			if (GetAsyncKeyState(VK_RIGHT)) {
				time_point<system_clock> startTime = system_clock::now();
				if (GetAsyncKeyState(VK_DOWN)) {
					if (GetAsyncKeyState(VK_DOWN)) {
						if (GetAsyncKeyState('A')) {
							cout << "�Ƶ����" << endl;
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
			cout << "\n���α׷��� ����˴ϴ�.\n" << endl;
			break;//1��° while�� ����
		}

		cout << "\n" << endl;
	}

	return 0;
}
