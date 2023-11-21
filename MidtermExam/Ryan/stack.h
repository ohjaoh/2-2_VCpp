#pragma once // include 할때 중첩되는 것을 한번만 포함되도로 지정시킨다.
#include <Windows.h>

// 노드 클래스 정의
class Nod {
public:
    int shape;     // 데이터를 저장하는 변수
    Nod* next;   // 다음 노드를 가리키는 포인터

    Nod(int shape, POINT startpo, POINT endpo) : shape(shape), next(nullptr) {} // 생성자
};

// 스택 클래스 정의
class y_Stack {
private:
    Nod* top; // 스택의 맨 위를 가리키는 포인터

public:
    y_Stack();    // 생성자
    ~y_Stack();   // 소멸자
    void push(int data); // 스택에 데이터를 추가하는 함수
    int pop();  // 스택에서 데이터를 제거하고 반환하는 함수
    int peek(); // 스택의 맨 위 데이터를 조회하는 함수
    bool isEmpty(); // 스택이 비어 있는지 확인하는 함수
};