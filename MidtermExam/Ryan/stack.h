#pragma once // include �Ҷ� ��ø�Ǵ� ���� �ѹ��� ���Եǵ��� ������Ų��.
#include <Windows.h>


// ��� Ŭ���� ����
class Nod {
public:
    MSG data;     // �����͸� �����ϴ� ����
    Nod* next;   // ���� ��带 ����Ű�� ������

    Nod(MSG data) : data(data), next(nullptr) {} // ������
};

// ���� Ŭ���� ����
class y_Stack {
private:
    Nod* top; // ������ �� ���� ����Ű�� ������

public:
    y_Stack();    // ������
    ~y_Stack();   // �Ҹ���
    void push(MSG data); // ���ÿ� �����͸� �߰��ϴ� �Լ�
    MSG pop();  // ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
    MSG peek(); // ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
    bool isEmpty(); // ������ ��� �ִ��� Ȯ���ϴ� �Լ�
};
