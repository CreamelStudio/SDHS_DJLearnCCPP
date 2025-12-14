#pragma once
class Tetra
{
private:
	VERTEX v[4];
	int Idx[12];
public:
	Tetra() {}
	~Tetra() {}

	void Init();
	void Process();
	void Render();
	void Release();

};

