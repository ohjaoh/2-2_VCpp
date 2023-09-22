#include <iostream>
#include <Windows.h>
#include <vector>
#include <chrono>

int sequences[][3] = {
    {VK_DOWN, VK_RIGHT, 'A'}, // ù ��° ��� ������
    {VK_LEFT, VK_UP, VK_DOWN} // �� ��° ��� ������
};

const char* skillNames[] = {
    "1������ߵ�", // ù ��° ��� �̸�
    "2������ߵ�"  // �� ��° ��� �̸�
};

int main() {
    int sequenceIndex = 0; // ���� �˻� ���� Ű ������ �ε���
    int sequenceCount = sizeof(sequences) / sizeof(sequences[0]); // Ű ������ ����

    std::vector<int> inputKeys; // �Էµ� Ű�� �����ϴ� ����
    auto startTime = std::chrono::high_resolution_clock::now(); // ���� �ð� �ʱ�ȭ

    std::string wrongInput = ""; // ������ ���� ������ ���ڿ�

    while (true) {
        if (GetAsyncKeyState(27)) {
            break; // ESC Ű�� ������ ����
        }

        bool keyPressed = false; // Ű�� ���ȴ��� ���� Ȯ��

        for (int key = VK_SPACE; key <= VK_OEM_CLEAR; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (inputKeys.empty() || key == sequences[sequenceIndex][inputKeys.size()]) {
                    inputKeys.push_back(key);

                    if (inputKeys.size() == 3) { // Ű ������ ���̿� ���� ����
                        // �Էµ� Ű ������ ���Ͽ� �ʻ�⸦ ����ϰų� ���� ������ �̵�
                        bool correctSequence = true;
                        for (int i = 0; i < 3; ++i) { // Ű ������ ���̿� ���� ����
                            if (inputKeys[i] != sequences[sequenceIndex][i]) {
                                correctSequence = false;
                                break;
                            }
                        }

                        if (correctSequence) {
                            std::cout << skillNames[sequenceIndex] << std::endl;
                        }
                        else {
                            // ������ ���� ���ڿ��� ����
                            wrongInput = "";
                            for (int i = 0; i < 3; ++i) {
                                wrongInput += static_cast<char>(inputKeys[i]);
                            }
                        }

                        inputKeys.clear(); // �Էµ� Ű �ʱ�ȭ
                        sequenceIndex = (sequenceIndex + 1) % sequenceCount; // ���� Ű ������ �̵�
                    }

                    keyPressed = true;
                }
            }
        }

        if (!keyPressed) {
            inputKeys.clear(); // 300ms ���� Ű�� ������ ������ �Է� �ʱ�ȭ
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

        if (elapsedTime.count() >= 300) {
            inputKeys.clear();
            startTime = std::chrono::high_resolution_clock::now();
        }

        // ������ ���� ���
        if (!wrongInput.empty()) {
            std::cout << "������ ��: " << wrongInput << std::endl;
            wrongInput = ""; // ��� �� �ʱ�ȭ
        }
    }

    return 0;
}
