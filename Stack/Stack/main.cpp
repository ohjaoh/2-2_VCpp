#include "yuhan_stack.h"
#include <iostream>
using namespace std;

int main() {
	y_Stack s;          // 스택 객체 생성
	s.push(10);       // 스택에 10 추가
	s.push(20);       // 스택에 20 추가
	s.push(30);       // 스택에 30 추가
	s.push(40);       // 스택에 40 추가
	s.push(50);       // 스택에 50 추가
	s.push(60);       // 스택에 60 추가
	s.push(70);       // 스택에 70 추가
	s.push(80);       // 스택에 80 추가
	s.push(90);       // 스택에 90 추가
	s.push(100);       // 스택에 100 추가
	s.push(110);       // 스택에 110 추가
	s.push(120);       // 스택에 120 추가

	cout << s.pop() << " 스텍에서 제거됨 \n"; // 스택에서 데이터 제거하고 출력
	cout << "현재 Top은 " << s.peek() << "입니다." << endl; // 현재 top 요소 조회
	for (int i = 0; i < 12; i++) {
		int result;
		result = s.pop();
		cout<< result <<endl;
	}

	return 0;
}