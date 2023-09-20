#include <iostream>
#include <Windows.h>
#include <vector>
#include <chrono>

int main() {
    int sequence[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT }; // ���ϴ� Ű ������ ����
    int sequenceLength = sizeof(sequence) / sizeof(sequence[0]); // �迭 ����

    std::vector<int> inputKeys; // �Էµ� Ű�� �����ϴ� ����
    auto startTime = std::chrono::high_resolution_clock::now(); // ���� �ð� �ʱ�ȭ

    while (true) {
        if (GetAsyncKeyState(27)) {
            break; // ESC Ű�� ������ ����
        }

        for (int key = VK_SPACE; key <= VK_OEM_CLEAR; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (inputKeys.empty()) {
                    startTime = std::chrono::high_resolution_clock::now(); // ó�� Ű ���� ������ ���� �ð����� ����
                }
                inputKeys.push_back(key);
            }
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);


        if (elapsedTime.count() >= 1000) {
            inputKeys.clear(); // �ð� �ʰ��� ���� �Է� �ʱ�ȭ
        }

        if (inputKeys.size() == sequenceLength) {
            bool correctSequence = true;

            for (int i = 0; i < sequenceLength; ++i) {
                if (inputKeys[i] != sequence[i]) {
                    correctSequence = false;
                    break;
                }
            }

            if (correctSequence) {
                std::cout << "�ʻ��!" << std::endl;
                inputKeys.clear(); // �ùٸ� ������ �Է��� ��� �Է� �ʱ�ȭ
            }
        }
    }

    return 0;
}
