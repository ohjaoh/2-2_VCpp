#include <iostream>
#include <Windows.h>
#include <vector>
#include <chrono>

int main() {
    int sequence[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT }; // 원하는 키 순서를 정의
    int sequenceLength = sizeof(sequence) / sizeof(sequence[0]); // 배열 길이

    std::vector<int> inputKeys; // 입력된 키를 저장하는 벡터
    auto startTime = std::chrono::high_resolution_clock::now(); // 시작 시간 초기화

    while (true) {
        if (GetAsyncKeyState(27)) {
            break; // ESC 키를 누르면 종료
        }

        for (int key = VK_SPACE; key <= VK_OEM_CLEAR; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (inputKeys.empty()) {
                    startTime = std::chrono::high_resolution_clock::now(); // 처음 키 누른 순간을 시작 시간으로 설정
                }
                inputKeys.push_back(key);
            }
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);


        if (elapsedTime.count() >= 1000) {
            inputKeys.clear(); // 시간 초과로 인한 입력 초기화
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
                std::cout << "필살기!" << std::endl;
                inputKeys.clear(); // 올바른 순서로 입력한 경우 입력 초기화
            }
        }
    }

    return 0;
}
