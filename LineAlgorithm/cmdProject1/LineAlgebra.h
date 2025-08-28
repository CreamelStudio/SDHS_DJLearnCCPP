#pragma once 



namespace LineAlgebra {
	void HLine(int x1, int x2, int y);
	void VLine(int x, int y1, int y2);
	void Rect(int x1, int y1, int x2, int y2);
	void TwoPointLine(int x1, int y1, int x2, int y2);
	void GradualLine(int x1, int y1, int x2, int y2);
	void gotoxy(int x, int y);
	void Dot(int x, int y);
}