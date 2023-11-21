#include "stack.h"
#include <iostream>
using namespace std;

// ���� Ŭ������ ������
y_Stack::y_Stack() {
    top = nullptr; // �ʱ�ȭ �� top�� null
}

// ���� Ŭ������ �Ҹ���
y_Stack::~y_Stack() {
    while (!isEmpty()) {
        pop(); // ������ ������� ������ ��� ��� ����
    }
}

// ���ÿ� �����͸� �߰��ϴ� �Լ�
void y_Stack::push(MSG data) {
    Nod* newNod = new Nod(data); // �� ��� ����
    newNod->next = top; // �� ����� next�� ���� top���� ����
    top = newNod; // �� ��带 ���ο� top���� ����
}

// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
MSG y_Stack::pop() {
    if (isEmpty()) {
        MSG emptyMsg = { 0 };
        return emptyMsg;
    }
    else {
        Nod* temp = top;// ���� top ��带 �ӽ� ����
        MSG data = top->data;// top�� ���� ���� �̵�
        top = top->next;// ���ŵ� ������ ����
        delete temp; // ��� �޸� ����
        return data; // ���ŵ� ������ ��ȯ
    }
}

// ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
MSG y_Stack::peek() {
    if (isEmpty()) {
        MSG emptyMsg = { 0 };
        return emptyMsg;
    }
    else {
        return top->data; // top ������ ��ȯ
    }
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
bool y_Stack::isEmpty() {
    return top == nullptr; // top�� null�̸� ������ ��� �ִ� ��
}