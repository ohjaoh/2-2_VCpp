#pragma once

// ��� Ŭ���� ����
class Nod {
public:
    int data;     // �����͸� �����ϴ� ����
    Nod* next;   // ���� ��带 ����Ű�� ������

    Nod(int data) : data(data), next(nullptr) {} // ������
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