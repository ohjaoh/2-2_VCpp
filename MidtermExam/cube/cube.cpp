#include <Windows.h>
struct CubeState
{
	POINT go = {0};
	POINT to = { 0 };
};

HRGN Drawcube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	// �߾Ӽ� ���߿� �����
	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 188, NULL);
	LineTo(hdc, 800, 188);
	
	int width = abs(startPoint.x - endPoint.x);
	int height = abs(startPoint.y - endPoint.y);
	int centerX = width / 2;
	int centerY = height / 2;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(startPoint.x, endPoint.x);
	MINPOINT.y = min(startPoint.y, endPoint.y);
	MAXPOINT.x = max(startPoint.x, endPoint.x);
	MAXPOINT.y = max(startPoint.y, endPoint.y);

	CubeState cubestatus; //�̵��ϴ� �Ŷ� ���� �������� ������ ������� ���Ϻ��� ����

	cubestatus.go = MINPOINT;
	cubestatus.to = MAXPOINT;

	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	if (MINPOINT.x <= 376 && MINPOINT.y < 188) {//�»�
		MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //�ظ� �ݽð��
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
		LineTo(hdc, MAXPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
		LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MAXPOINT.y}, // 1�� ������
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 2�� ������
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 3�� ������
		   {MAXPOINT.x, MINPOINT.y}, // 4�� ������
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 5�� ������
		   {MINPOINT.x, MINPOINT.y + centerY / 2}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6,WINDING);
		return Hexa;
	}
	if (MINPOINT.x <= 376 && MINPOINT.y >= 188) {//����
		MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); //�ظ�
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MINPOINT.y);//����

		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2, NULL); // �ո�
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

		MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); // ����
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2�� ������
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5�� ������
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y < 188) {//���
		MoveToEx(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2, NULL); //�ظ� �ݽð��
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2�� ������
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5�� ������
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y >= 188) {//����
		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
		LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

		MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

		MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MINPOINT.y + centerY / 2}, // 2�� ������
		   {MINPOINT.x, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 5�� ������
		   {MAXPOINT.x, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
}
void Movecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start) {

	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);
	POINT end = { mouseX, mouseY };

	// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;

	CubeState cubestatus;
	POINT MINPOINT = { cubestatus.go };
	POINT MAXPOINT = { cubestatus.to };

	MINPOINT.x += deltaX;
	MINPOINT.y += deltaY;
	MAXPOINT.x += deltaX;
	MAXPOINT.y += deltaY;

	Drawcube(hWnd, hdc, MINPOINT, MAXPOINT);
}
void Scalecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);
	POINT end = { mouseX, mouseY };

	// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);
	MINPOINT.x += deltaX;
	MINPOINT.y += deltaY;
	MAXPOINT.x += deltaX;
	MAXPOINT.y += deltaY;

	Drawcube(hWnd, hdc, MINPOINT, MAXPOINT);

}