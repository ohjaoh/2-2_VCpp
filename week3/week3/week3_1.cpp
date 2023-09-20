#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

int main() {
    int sequence[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT }; // 원하는 키 순서를 정의
    int currentIndex = 0; // 현재 입력해야 하는 키의 인덱스
    int sequenceLength = sizeof(sequence) / sizeof(sequence[0]); // 배열 길이

    while (true) {
        if (GetAsyncKeyState(sequence[currentIndex]) & 0x8000) {
            // 현재 입력해야 하는 키가 눌린 경우
            currentIndex++;

            if (currentIndex == sequenceLength) {
                // 모든 키를 올바른 순서로 입력한 경우
                std::cout << "필살기!" << std::endl;

                // 다음 동작을 위해 초기화
                currentIndex = 0;

                // 300ms 대기
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }

        // 다른 작업 수행
    }

    return 0;
}
