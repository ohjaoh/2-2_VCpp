#include "yuhan_stack.h"
#include <iostream>
using namespace std;

int main() {
	y_Stack s;          // ���� ��ü ����
	s.push(10);       // ���ÿ� 10 �߰�
	s.push(20);       // ���ÿ� 20 �߰�
	s.push(30);       // ���ÿ� 30 �߰�
	s.push(40);       // ���ÿ� 40 �߰�
	s.push(50);       // ���ÿ� 50 �߰�
	s.push(60);       // ���ÿ� 60 �߰�
	s.push(70);       // ���ÿ� 70 �߰�
	s.push(80);       // ���ÿ� 80 �߰�
	s.push(90);       // ���ÿ� 90 �߰�
	s.push(100);       // ���ÿ� 100 �߰�
	s.push(110);       // ���ÿ� 110 �߰�
	s.push(120);       // ���ÿ� 120 �߰�

	cout << s.pop() << " ���ؿ��� ���ŵ� \n"; // ���ÿ��� ������ �����ϰ� ���
	cout << "���� Top�� " << s.peek() << "�Դϴ�." << endl; // ���� top ��� ��ȸ
	for (int i = 0; i < 12; i++) {
		int result;
		result = s.pop();
		cout<< result <<endl;
	}

	return 0;
}