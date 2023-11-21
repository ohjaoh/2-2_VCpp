#pragma once // include �Ҷ� ��ø�Ǵ� ���� �ѹ��� ���Եǵ��� ������Ų��.
#include <Windows.h>

// ��� Ŭ���� ����
class Nod {
public:
    int shape;     // �����͸� �����ϴ� ����
    Nod* next;   // ���� ��带 ����Ű�� ������

    Nod(int shape, POINT startpo, POINT endpo) : shape(shape), next(nullptr) {} // ������
};

// ���� Ŭ���� ����
class y_Stack {
private:
    Nod* top; // ������ �� ���� ����Ű�� ������

public:
    y_Stack();    // ������
    ~y_Stack();   // �Ҹ���
    void push(int data); // ���ÿ� �����͸� �߰��ϴ� �Լ�
    int pop();  // ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
    int peek(); // ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
    bool isEmpty(); // ������ ��� �ִ��� Ȯ���ϴ� �Լ�
};