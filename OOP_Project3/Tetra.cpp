#include "pch.h"
#include "Tetra.h"

extern RECT rtScreen;
static VERTEX SV[4];

void Tetra::Init() {
	// 0번: 뿔의 꼭대기 (위)
	v[0].x = 0;    v[0].y = 100;   v[0].z = 0;    v[0].w = 1;

	// 1, 2, 3번: 바닥을 지탱하는 삼각형 (아래)
	v[1].x = -100; v[1].y = -100;  v[1].z = -50;  v[1].w = 1; // 왼쪽 뒤
	v[2].x = 100;  v[2].y = -100;  v[2].z = -50;  v[2].w = 1; // 오른쪽 뒤
	v[3].x = 0;    v[3].y = -100;  v[3].z = 100;  v[3].w = 1; // 앞쪽

	// 인덱스 (면 구성 정보)
	Idx[0] = 0; Idx[1] = 1; Idx[2] = 2; // 앞면
	Idx[3] = 0; Idx[4] = 2; Idx[5] = 3; // 우측면
	Idx[6] = 0; Idx[7] = 3; Idx[8] = 1; // 좌측면
	Idx[9] = 1; Idx[10] = 3; Idx[11] = 2; // 바닥면
}

void Tetra::Process() {
	static int nCnt = 0;

	Matrix3D CTM, RxTM, RyTM, RzTM, STM, ScreenTM;
	CTM.Identity();
	RxTM.RotateX(nCnt);   // 대충 40도 쯤
	RyTM.RotateY(30);   // 대충 30도 쯤
	RzTM.RotateZ(0);   // 대충 15도 쯤

	STM.Scale(1.0f);
	ScreenTM.Move(rtScreen.right / 2.0f, rtScreen.bottom / 2.0f, 0);

	CTM = RxTM * RyTM * RzTM * STM * ScreenTM;

	for (int i = 0; i < 4; i++) {
		SV[i] = v[i] * CTM;
	}

	nCnt++;
}
void Tetra::Render() {
	gdi->OrangePen();

	for (int i = 0; i < 4; i++) {
		gdi->Line(SV[Idx[i * 3 + 0]].x, SV[Idx[i * 3 + 0]].y, SV[Idx[i * 3 + 1]].x, SV[Idx[i * 3 + 1]].y);
		gdi->Line(SV[Idx[i * 3 + 1]].x, SV[Idx[i * 3 + 1]].y, SV[Idx[i * 3 + 2]].x, SV[Idx[i * 3 + 2]].y);
		gdi->Line(SV[Idx[i * 3 + 2]].x, SV[Idx[i * 3 + 2]].y, SV[Idx[i * 3 + 0]].x, SV[Idx[i * 3 + 0]].y);
	}
	

	for (int i = 0; i < 4; i++)
	{
		DrawBigBigDot(SV[i].x, SV[i].y, RGB(255, 255, 0));
	}
}
void Tetra::Release() {

}