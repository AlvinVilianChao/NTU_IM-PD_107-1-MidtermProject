#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
// string

int NodeCnt, riskCnt, turnCost, maxDist; //n, m, w, d
int* riskPoint_X;
int* riskPoint_Y;
int* riskPoint_R;
int* riskPoint_P;
int source[2] = {0};
int dest[2] = {0};

void inputInfo();
double routeRisk(vector<double> x, vector<double> y);
double routeDist(vector<double> x, vector<double> y);



int main()
{
    inputInfo();

    vector<double> x, y;
    x.push_back(2);

    y.push_back(3);

    cout << routeRisk(x, y);

    return 0;
}

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

// 計算總風險
double routeRisk(vector<double> x, vector<double> y)
{
    // risk 總風險, restDst 上一段走剩的距離
    double risk = 0, restDst = 0;
    
    // 如果vector沒東西
    if (x.size() == 0)
    {
        double xdiff = 0, ydiff = 0, dst = 0, xStarter = 0, yStarter = 0;
        xdiff = dest[0] - source[0], ydiff = dest[1] - source[1];
        dst = pow((pow(xdiff, 2) + pow(ydiff, 2)), 0.5);
        xStarter = source[0], yStarter = source[1];  

        for (int j = 1; j < dst; j++)
        {
            double xPerUnit =  xdiff / dst, yPerUnit = ydiff / dst;
            xStarter += xPerUnit, yStarter += yPerUnit;

            for (int l = 0; l <= riskCnt; l++)
            {
                double difDistance = riskPoint_R[l] - pow((pow((riskPoint_X[l] - xStarter), 2) + pow((riskPoint_Y[l] - yStarter), 2)), 0.5);
                if (difDistance <= 0)
                    continue;

                double tempRisk = riskPoint_P[l] * (difDistance / riskPoint_R[l]);
                risk += tempRisk;
            }
        } 
    }
    else
    {    
        for (int i = 0; i <= x.size(); i++)
        {
            // xdiff 這個點與前一個點的距離, ydiff 同左, dst 兩點距離, xStarter 從指定點出發, yStarter 同左
            double xdiff = 0, ydiff = 0, dst = 0, xStarter = 0, yStarter = 0;

            // 算起點到第1個
            if (i == 0)
            {
                xdiff = x[i] - source[0], ydiff = y[i] - source[1]; 
                dst = pow((pow(xdiff, 2) + pow(ydiff, 2)), 0.5);
                xStarter = source[0], yStarter = source[1]; 
            }
            // 算最後一個轉折點到終點，要先將上一個路段剩餘的距離走完
            else if (i == x.size())
            {   
                xdiff = dest[0] - x[i - 1], ydiff = dest[1] - y[i - 1];
                dst = pow((pow(xdiff, 2) + pow(ydiff, 2)), 0.5);
                xStarter = x[i - 1] + ((restDst * xdiff) / dst), yStarter = y[i - 1] + ((restDst * ydiff) / dst);
            }

            // 要先將上一個路段剩餘的距離走完
            else
            {
                xdiff = x[i] - x[i - 1], ydiff = y[i] - y[i - 1];
                dst = pow((pow(xdiff, 2) + pow(ydiff, 2)), 0.5);
                xStarter = x[i - 1] + ((restDst * xdiff) / dst), yStarter = y[i - 1] + ((restDst * ydiff) / dst);
            }

            // 剪掉先走的那段
            // dst -= restDst;

            for (int j = 1; j < dst; j++)
            {
                double xPerUnit =  xdiff / dst, yPerUnit = ydiff / dst;

                if(i == 0 || (j != 1 && i !=0))
                    xStarter += xPerUnit, yStarter += yPerUnit;

                cout << xStarter << " "<< " " << yStarter << " " <<endl;

                for (int l = 0; l <= riskCnt; l++)
                {
                    double difDistance = riskPoint_R[l] - pow((pow((riskPoint_X[l] - xStarter), 2) + pow((riskPoint_Y[l] - yStarter), 2)), 0.5);

                    if (difDistance <= 0)
                        continue;

                    double tempRisk = riskPoint_P[l] * (difDistance / riskPoint_R[l]);
                    risk += tempRisk;
                }

                // 如果是該路段最後一個點的話，計算剩餘距離
                if (j == static_cast<int>(dst))
                   restDst = 1 - (dst - j);
            }

        }
 
    }

    // 轉彎幾次就加幾次
    risk += turnCost * x.size();

    return risk;
}

// 計算總長
double routeDist(vector<double> x, vector<double> y)
{
    double distance = 0;

    for (int i = 0; i <= x.size(); i++)
    {
        // 算起點到第1個間的距離
        if (i == 0)
            distance += sqrt(pow((x[i] - source[0]), 2) + pow((y[i] - source[0]), 2));
        // 算最後一個轉折點到終點的距離    
        else if (i == x.size())
            distance += sqrt(pow((dest[0] - x[i - 1]), 2) + pow((dest[1] - y[i - 1]), 2));
        else
            distance += sqrt(pow((x[i] - x[i - 1]), 2) + pow((y[i] - y[i - 1]), 2));
    }

    return distance;
}

