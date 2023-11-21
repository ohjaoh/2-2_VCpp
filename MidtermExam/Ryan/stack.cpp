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
void y_Stack::push(int shape) {
    Nod* newNod = new Nod(shape); // �� ��� ����
    newNod->next = top; // �� ����� next�� ���� top���� ����
    top = newNod; // �� ��带 ���ο� top���� ����
}

// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
int y_Stack::pop() {
    if (isEmpty()) {
        cout << "y_Stack Underflow" << endl;
        return -1;
    }
    else {
        Nod* temp = top; // ���� top ��带 �ӽ� ����
        top = top->next; // top�� ���� ���� �̵�
        int poppedData = temp->shape; // ���ŵ� ������ ����
        delete temp; // ��� �޸� ����
        return poppedData; // ���ŵ� ������ ��ȯ
    }
}

// ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
int y_Stack::peek() {
    if (isEmpty()) {
        cout << "y_Stack is Empty" << endl;
        return -1;
    }
    else {
        return top->shape; // top ������ ��ȯ
    }
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
bool y_Stack::isEmpty() {
    return top == nullptr; // top�� null�̸� ������ ��� �ִ� ��
}