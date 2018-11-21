#include <iostream>
using namespace std;


int NodeCnt, riskCnt, turnCost, maxDist; //n, m, w, d
int* riskPoint_X;
int* riskPoint_Y;
int* riskPoint_R;
int* riskPoint_P;
int source[2] = {0};
int dest[2] = {0};

void inputInfo()
{
	cin >> NodeCnt >> riskCnt >> turnCost >> maxDist;
	riskPoint_X = new int[riskCnt];
	riskPoint_Y = new int[riskCnt];
	riskPoint_R = new int[riskCnt];
	riskPoint_P = new int[riskCnt];
	for (int i = 0; i < riskCnt; i++) {
		cin >> riskPoint_X[i];
	}
	for (int i = 0; i < riskCnt; i++) {
		cin >> riskPoint_Y[i];
	}
	for (int i = 0; i < riskCnt; i++) {
		cin >> riskPoint_R[i];
	}
	for (int i = 0; i < riskCnt; i++) {
		cin >> riskPoint_P[i];
	}
	cin >> source[0] >> source[1] >> dest[0] >> dest[1];
}
