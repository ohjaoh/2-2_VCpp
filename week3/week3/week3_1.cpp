#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

int main() {
    int sequence[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT }; // ���ϴ� Ű ������ ����
    int currentIndex = 0; // ���� �Է��ؾ� �ϴ� Ű�� �ε���
    int sequenceLength = sizeof(sequence) / sizeof(sequence[0]); // �迭 ����

    while (true) {
        if (GetAsyncKeyState(sequence[currentIndex]) & 0x8000) {
            // ���� �Է��ؾ� �ϴ� Ű�� ���� ���
            currentIndex++;

            if (currentIndex == sequenceLength) {
                // ��� Ű�� �ùٸ� ������ �Է��� ���
                std::cout << "�ʻ��!" << std::endl;

                // ���� ������ ���� �ʱ�ȭ
                currentIndex = 0;

                // 300ms ���
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }

        // �ٸ� �۾� ����
    }

    return 0;
}
