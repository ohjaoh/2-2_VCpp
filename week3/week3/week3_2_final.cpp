#include <iostream>
#include <windows.h>
#include <vector>

int main() {
	const int bufferSize = 128; // 입력 이벤트 버퍼 크기
	INPUT_RECORD inputRecord[bufferSize]; // 입력 이벤트 레코드 배열
	DWORD numEventsRead; // 읽은 이벤트 수를 저장할 변수
	std::vector<WORD> inputSequence; // 입력된 키 시퀀스를 저장할 벡터

	while (true) {
		// 300ms 동안 입력 대기, 입력 시간 초과 시 입력된 값을 배열로 출력
		if (WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), 300) == WAIT_TIMEOUT) {
			/*
			`WaitForSingleObject` 함수는 Windows API 함수로, 특정 객체(여기서는 표준 입력 핸들 `STD_INPUT_HANDLE`)에 대한 상태를 모니터링하고 기다리는 역할을 합니다. 
			`GetStdHandle(STD_INPUT_HANDLE)`를 통해 표준 입력 핸들을 가져와서 해당 핸들에 대한 상태를 확인하고자 합니다.

			여기서 사용된 코드 조건은 다음과 같습니다:
			- `WaitForSingleObject` 함수는 첫 번째 인수로 대기할 객체의 핸들을 받고, 두 번째 인수로 대기 시간(밀리초 단위)을 받습니다. 
			여기서는 `STD_INPUT_HANDLE` (표준 입력 핸들)을 대상으로 300밀리초(즉, 0.3초) 동안 대기합니다.
			- `WAIT_TIMEOUT`은 `WaitForSingleObject` 함수의 반환 값 중 하나로, 대기 시간 동안 지정된 객체의 상태가 변하지 않을 때 반환됩니다. 
			즉, 표준 입력 핸들에 대한 입력이 300밀리초 동안 없을 경우 `WAIT_TIMEOUT`이 반환됩니다.
			
			이것은 입력 시간 초과를 감지하는 부분입니다. 
			만약 300밀리초 동안 입력이 없다면, `WaitForSingleObject` 함수는 `WAIT_TIMEOUT`을 반환하고, 이것을 조건문에서 확인합니다. 
			
			따라서 이 부분은 "300밀리초 동안 입력이 없으면"을 나타내고, 그 경우에 특정 동작(여기서는 입력된 값을 출력하고 배열 초기화)이 수행되도록 합니다.
			*/
			for (WORD keyCode : inputSequence) { 
				/*
				  `for (WORD keyCode : inputSequence)` 부분은 C++11부터 도입된 범위 기반 루프(Range-based loop)를 사용한 코드입니다. 
				  이 부분은 벡터인 `inputSequence`에 저장된 요소들을 반복적으로 처리하는 역할을 합니다.
				  여기서 `inputSequence`는 사용자가 입력한 키의 시퀀스를 저장하는 벡터입니다. 
				  이 벡터에 저장된 각 요소는 `WORD` 자료형을 가지고 있습니다.
				  
				  `for (WORD keyCode : inputSequence)` 부분을 해석하면 다음과 같습니다:
				  - `inputSequence` 벡터에 있는 각 요소를 하나씩 가져와서 `keyCode` 변수에 할당합니다.
				  - 그리고 이 변수 `keyCode`를 사용하여 반복문 내부의 코드 블록을 실행합니다.

				  즉, `for` 루프를 통해 `inputSequence` 벡터에 저장된 각 키 코드를 순회하면서 해당 키 코드에 대한 작업을 수행할 수 있습니다. 이 경우, 입력된 키 코드를 문자로 변환하여 출력하거나 다른 조작을 할 수 있습니다.
				*/
				/* -WORD에 대한 설명
				`WORD`는 Microsoft Windows에서 사용되는 데이터 타입 중 하나로, 16 비트(2 바이트) 크기의 부호 없는 정수를 나타내는 데 사용됩니다. 
				주로 다음과 같은 경우에 `WORD` 데이터 타입이 사용됩니다:
				1. 메모리 구조체에서 16 비트 데이터 필드를 나타내는 데 사용됩니다.
				2. Windows API 함수와 상호 작용할 때, 예를 들어 윈도우 핸들, 가상 키 코드 등의 값은 주로 `WORD`로 표현됩니다.
				3. 그래픽 프로그래밍에서 픽셀의 색상을 나타내는 데 사용될 수 있습니다.
				`WORD`는 부호 없는 정수로, 음수 값을 나타내지 않습니다. 범위는 0부터 65535까지이며, 2^16(2의 16승)가지 다른 값을 표현할 수 있습니다.
				예를 들어, 키보드 입력에서 가상 키 코드(예: VK_DOWN, VK_UP)는 주로 `WORD` 타입으로 정의되며, 이러한 값을 사용하여 특정 키를 나타냅니다.
				*/


				if (keyCode >= 32 && keyCode <= 126) {// 아스키문자 범위에 속하는지 확인
					std::cout << static_cast<char>(keyCode);//static_cast<char>로 키코드를 아스키문자로 변환 후 화면에 출력
				}
			}
			std::cout << std::endl;
			inputSequence.clear(); // 배열 초기화
		}

		// 입력 이벤트를 읽어옴
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inputRecord, bufferSize, &numEventsRead);
		/*
		`ReadConsoleInput` 함수는 Windows API 함수로, 표준 입력 핸들(`STD_INPUT_HANDLE`)에서 입력 이벤트를 읽어올 때 사용됩니다. 
		
		아래는 해당 함수와 관련된 인자들에 대한 설명입니다:
		- 첫 번째 인자 (`GetStdHandle(STD_INPUT_HANDLE)`): 표준 입력 핸들을 반환하는 함수 `GetStdHandle`을 호출하여 얻은 핸들입니다. 이 핸들은 표준 입력(키보드 입력)에 대한 핸들을 가리킵니다. 
		따라서 이 함수를 통해 표준 입력에서 입력 이벤트를 읽어옵니다.
		- 두 번째 인자 (`inputRecord`): `INPUT_RECORD` 구조체 배열입니다. 
		이 배열은 읽어온 입력 이벤트 정보를 저장할 곳으로, `ReadConsoleInput` 함수가 읽어온 입력 이벤트를 이 배열에 저장합니다.
		- 세 번째 인자 (`bufferSize`): 읽어올 입력 이벤트의 최대 개수를 지정합니다. 
		여기서는 `bufferSize` 변수에 저장된 값을 사용하여 최대 `bufferSize` 개수의 입력 이벤트를 읽어옵니다.
		- 네 번째 인자 (`&numEventsRead`): 읽어온 입력 이벤트의 실제 개수가 저장될 변수입니다. 
		`ReadConsoleInput` 함수가 실행된 후에 이 변수에 읽은 입력 이벤트의 개수가 저장됩니다.
		`ReadConsoleInput` 함수는 주로 콘솔 애플리케이션에서 사용되며, 사용자의 키보드 입력과 마우스 입력 등을 모니터링하고 읽어올 때 사용됩니다. 
		입력 이벤트를 읽어와서 이벤트의 종류와 내용을 `INPUT_RECORD` 구조체에 저장하므로, 이를 통해 애플리케이션은 사용자의 입력에 대한 반응을 조작할 수 있습니다.
		*/

		/* DWORD형에 대한 설명
		`DWORD`는 Microsoft Windows에서 사용되는 데이터 타입 중 하나입니다. "Double Word"의 약자로, 32비트 또는 4바이트를 나타내는 부호 없는 정수 데이터 타입입니다. 
		`DWORD`는 일반적으로 양수를 표현할 때 사용되며, 음수를 표현하는 데 사용되는 부호 비트가 없습니다.
		
		주로 다음과 같은 상황에서 `DWORD`를 사용합니다:
		
		1. 메모리 주소나 데이터 크기를 표현할 때: 주소나 데이터의 크기는 양수이며, 4바이트로 나타내는 경우가 많습니다. `DWORD`를 사용하면 편리하게 메모리 주소나 크기를 표현할 수 있습니다.
		2. 비트 조작 및 비트 필드: `DWORD`는 비트 조작 작업에 유용합니다. 여러 플래그 또는 상태를 나타내는 데 사용할 수 있습니다.
		3. Windows API와 상호 작용: Windows API 함수에서는 주로 `DWORD`를 매개변수로 받거나 반환값으로 사용합니다. 예를 들어 파일 크기, 파일 핸들, 프로세스 ID 등을 나타내기 위해 `DWORD`를 사용합니다.
		4. 네트워크 프로그래밍: 네트워크 통신에서 IP 주소, 포트 번호 등을 나타내는 데 `DWORD`를 사용할 수 있습니다.
		
		`DWORD`는 C/C++와 같은 프로그래밍 언어에서 기본적으로 제공되며, 데이터의 크기와 범위를 고려할 때 적절한 데이터 타입을 선택하는 데 도움이 됩니다.
		*/
		for (DWORD i = 0; i < numEventsRead; i++) {
			/*
			i < numEventsRead: 이 부분은 루프의 조건을 나타냅니다. 
			조건을 평가하여 true일 때 루프가 계속 실행됩니다. 
			여기서는 i가 numEventsRead 보다 작을 때 루프가 계속 실행됩니다. 
			이 조건은 입력 이벤트를 모두 처리할 때까지 루프가 실행되도록 합니다.
			*/
			if (inputRecord[i].EventType == KEY_EVENT) {
				/* KEY_EVENT에 대한 설명
				`KEY_EVENT`는 Windows API에서 사용되는 이벤트 종류 중 하나로, 주로 키보드 입력 이벤트를 나타내는 이벤트입니다. 
				`KEY_EVENT`는 키보드 관련 이벤트 정보를 포함하고 있으며, 사용자가 키를 누르거나 뗄 때 발생합니다. 
				`KEY_EVENT` 구조체는 다양한 정보를 저장할 수 있으며, 주로 입력된 키에 대한 정보와 상태를 포함합니다.
				
				`KEY_EVENT` 구조체의 주요 멤버와 설명은 다음과 같습니다:
				1. `bKeyDown`: 부울 값으로, 키를 누를 때 `TRUE`로 설정되고, 키를 뗄 때 `FALSE`로 설정됩니다. 
				이 멤버는 키가 눌렸는지 아니면 뗼렸는지를 나타냅니다.
				
				2. `wRepeatCount`: 키 반복 횟수를 나타내는 정수 값입니다. 
				예를 들어, 사용자가 키를 길게 누르면 이 값이 증가하며, 키 반복을 나타냅니다.
				
				3. `wVirtualKeyCode`: 눌린 키의 가상 키 코드를 나타내는 정수 값입니다. 
				가상 키 코드는 각 키에 대한 고유한 값으로 키보드 입력을 식별하는 데 사용됩니다. 
				예를 들어, 'A' 키의 가상 키 코드는 0x41입니다.

				4. `uChar`: 입력된 문자를 나타내는 정수 값입니다. 
				이 값은 가상 키 코드를 기반으로 해당 문자를 나타냅니다. 
				예를 들어, 'A' 키의 가상 키 코드에 해당하는 `uChar` 값은 'A' 문자의 ASCII 코드인 65입니다.
				
				5. `dwControlKeyState`: 부울 플래그 및 상태를 나타내는 비트 플래그입니다. 
				예를 들어, SHIFT, CTRL, ALT 등의 조합 키의 상태를 나타내며, 이를 통해 조합된 키 입력을 검사할 수 있습니다.
				
				`KEY_EVENT` 구조체는 주로 콘솔 애플리케이션에서 키보드 입력을 처리하고 사용자의 입력에 반응하는 데 사용됩니다. 이를 통해 키보드 이벤트를 모니터링하고 필요한 작업을 수행할 수 있습니다.
				*/
				KEY_EVENT_RECORD keyEvent = inputRecord[i].Event.KeyEvent;
				/*
				`KEY_EVENT_RECORD`는 Windows API에서 키보드 이벤트 정보를 저장하는 구조체입니다. 
				`KEY_EVENT_RECORD` 구조체는 `INPUT_RECORD` 구조체의 멤버 중 하나로 사용되며, `Event` 멤버를 통해 액세스됩니다. 
				`Event` 멤버는 여러 종류의 입력 이벤트를 나타내는데, 여기서는 키보드 이벤트에 대한 정보를 추출하기 위해 사용됩니다.

				`KEY_EVENT_RECORD keyEvent = inputRecord[i].Event.KeyEvent;` 코드는 `inputRecord` 배열에서 `i`번째 입력 이벤트에 대한 정보를 추출하여 `keyEvent` 변수에 저장하는 역할을 합니다. 이 코드를 설명하면 다음과 같습니다:
				1. `inputRecord[i]`: `inputRecord` 배열은 `i`번째 입력 이벤트에 대한 정보를 포함하고 있습니다. `i`는 현재 반복하는 루프의 반복 변수로 사용됩니다.
				2. `inputRecord[i].Event`: `inputRecord[i]`의 `Event` 멤버는 해당 입력 이벤트의 종류를 나타내는데, 여기서는 키보드 이벤트를 가리킵니다.
				3. `inputRecord[i].Event.KeyEvent`: `Event` 멤버가 `KEY_EVENT_RECORD` 구조체를 가리키므로, 이를 `keyEvent` 변수에 대입하여 해당 키보드 이벤트 정보를 추출합니다.
				결과적으로, `keyEvent` 변수에는 `inputRecord` 배열에서 `i`번째 입력 이벤트에 대한 키보드 이벤트 정보가 저장됩니다. 이 정보를 이용하여 해당 키 이벤트의 종류, 눌린 키, 키 반복 횟수, 조합 키 상태 등을 확인하고 처리할 수 있습니다.
				*/
				if (keyEvent.bKeyDown) {// 키가 눌렸을 때
					WORD keyCode = keyEvent.wVirtualKeyCode;// keyEvent의 눌린 키의 가상 키 코드를 나타내는 정수 값입니다. 

					inputSequence.push_back(keyCode); // 입력된 키를 시퀀스에 추가

					if (inputSequence.size() >= 3) {
						// 시퀀스의 마지막 3개 키에 대한 처리
						if (inputSequence[inputSequence.size() - 3] == VK_DOWN && inputSequence[inputSequence.size() - 2] == VK_RIGHT && inputSequence[inputSequence.size() - 1] == 'A') {
							/*
							inputSequence[inputSequence.size() - 3] == VK_DOWN: inputSequence 벡터의 마지막에서 세 번째 위치에 있는 값이 VK_DOWN와 같아야 합니다. 
							여기서 VK_DOWN는 특정 가상 키 코드를 나타내며, 이 경우 아마도 아래 방향키를 나타냅니다.
							inputSequence[inputSequence.size() - 2] == VK_RIGHT: inputSequence 벡터의 마지막에서 두 번째 위치에 있는 값이 VK_RIGHT와 같아야 합니다. 
							VK_RIGHT는 오른쪽 방향키를 나타냅니다.
							inputSequence[inputSequence.size() - 1] == 'A': inputSequence 벡터의 마지막 위치에 있는 값이 문자 'A'와 같아야 합니다.
							즉, 이 조건은 사용자가 특정 순서로 아래 방향키를 누르고 오른쪽 방향키를 누른 후 'A' 키를 눌렀는지를 검사합니다. 
							이 조건이 참이면, 해당 키 시퀀스가 입력되었음을 나타내며, 조건문 내부의 코드 블록이 실행됩니다.
							*/
							std::cout << "아도겐!=0" << std::endl;
							inputSequence.clear(); // 배열 초기화
						}
						else if (inputSequence[inputSequence.size() - 3] == VK_DOWN && inputSequence[inputSequence.size() - 2] == VK_UP && inputSequence[inputSequence.size() - 1] == 'W') {
							std::cout << "라면칩" << std::endl;
							inputSequence.clear(); // 배열 초기화
						}
						else if (inputSequence[inputSequence.size() - 3] == VK_LEFT && inputSequence[inputSequence.size() - 2] == VK_RIGHT && inputSequence[inputSequence.size() - 1] == 'E') {
							std::cout << "이쿠" << std::endl;
							inputSequence.clear(); // 배열 초기화
						}
						else if (inputSequence[inputSequence.size() - 3] == VK_RIGHT && inputSequence[inputSequence.size() - 2] == VK_LEFT && inputSequence[inputSequence.size() - 1] == 'R') {
							std::cout << "에쿠" << std::endl;
							inputSequence.clear(); // 배열 초기화
						}
					}
				}
			}
		}

		// ESC 키를 확인하여 프로그램 종료
		if (GetAsyncKeyState(VK_ESCAPE)) {
			return 0;
		}
	}

	return 0;
}
