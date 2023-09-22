#include <iostream>
#include <Windows.h>
#include <vector>
#include <chrono>

int sequences[][3] = {
    {VK_DOWN, VK_RIGHT, 'A'}, // 첫 번째 기술 시퀀스
    {VK_LEFT, VK_UP, VK_DOWN} // 두 번째 기술 시퀀스
};

const char* skillNames[] = {
    "1번기술발동", // 첫 번째 기술 이름
    "2번기술발동"  // 두 번째 기술 이름
};

int main() {
    int sequenceIndex = 0; // 현재 검사 중인 키 순서의 인덱스
    int sequenceCount = sizeof(sequences) / sizeof(sequences[0]); // 키 순서의 개수

    std::vector<int> inputKeys; // 입력된 키를 저장하는 벡터
    auto startTime = std::chrono::high_resolution_clock::now(); // 시작 시간 초기화

    std::string wrongInput = ""; // 엉뚱한 값을 저장할 문자열

    while (true) {
        if (GetAsyncKeyState(27)) {
            break; // ESC 키가 눌리면 종료
        }

        bool keyPressed = false; // 키가 눌렸는지 여부 확인

        for (int key = VK_SPACE; key <= VK_OEM_CLEAR; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (inputKeys.empty() || key == sequences[sequenceIndex][inputKeys.size()]) {
                    inputKeys.push_back(key);

                    if (inputKeys.size() == 3) { // 키 순서의 길이에 따라 조정
                        // 입력된 키 순서와 비교하여 필살기를 출력하거나 다음 순서로 이동
                        bool correctSequence = true;
                        for (int i = 0; i < 3; ++i) { // 키 순서의 길이에 따라 조정
                            if (inputKeys[i] != sequences[sequenceIndex][i]) {
                                correctSequence = false;
                                break;
                            }
                        }

                        if (correctSequence) {
                            std::cout << skillNames[sequenceIndex] << std::endl;
                        }
                        else {
                            // 엉뚱한 값을 문자열로 저장
                            wrongInput = "";
                            for (int i = 0; i < 3; ++i) {
                                wrongInput += static_cast<char>(inputKeys[i]);
                            }
                        }

                        inputKeys.clear(); // 입력된 키 초기화
                        sequenceIndex = (sequenceIndex + 1) % sequenceCount; // 다음 키 순서로 이동
                    }

                    keyPressed = true;
                }
            }
        }

        if (!keyPressed) {
            inputKeys.clear(); // 300ms 동안 키가 눌리지 않으면 입력 초기화
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

        if (elapsedTime.count() >= 300) {
            inputKeys.clear();
            startTime = std::chrono::high_resolution_clock::now();
        }

        // 엉뚱한 값을 출력
        if (!wrongInput.empty()) {
            std::cout << "엉뚱한 값: " << wrongInput << std::endl;
            wrongInput = ""; // 출력 후 초기화
        }
    }

    return 0;
}
