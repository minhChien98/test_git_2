#include<iostream>
#include<iomanip>
#include<stdio.h>

using namespace std;

#define MAX 20

struct process{
	char pro[3];
	int cpuB;
	int timeXh;
};

struct time{
    int timeWait;
    int timePro;
};

void nhap(process test[],int &n)
{
	cout << "Nhap so tien trinh: ";
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cout << "\tNhap tien trinh " << i+1 << endl;
		cout << "\t\tNhap ten tien trinh: ";
		fflush(stdin);gets(test[i].pro);
		cout << "\t\tNhap thoi gian xuat hien: ";
		cin >> test[i].timeXh;
		cout << "\t\tNhap thoi gian xu li: ";
		cin >> test[i].cpuB;
	}
}

void xuat(process test[], int n)
{
	cout << "Bang tien trinh la: " << endl;
	cout << setw(10) << "Process" << setw(7) << "Txh" << setw(7) << "CPUb" << endl;
	for(int i=0; i<n;i++)
	{
		cout << setw(10) << test[i].pro << setw(7) << test[i].timeXh << setw(7) << test[i].cpuB << endl;
	}
}

void xoa(process test[], int &n, int x)
{
	for(int i = x ; i < n ; i++)
		test[i] = test[i+1];
	n--;
}

void sapXep(process test[], int n)
{
	for(int i = 0 ; i < n ; i++)
		for(int j = i+1 ; j<n;j++)
			if(test[i].timeXh > test[j].timeXh)
            {
                process tam = test[i];
                test[i] = test[j];
                test[j] = tam;
            }
}

void KeNgang()
{
	cout << "================";
}



int taoGianDoGantt(process test[],time tinh[], int n)
{
    int timeBd[MAX], dem = 0, x=n;
    timeBd[0]=0;
    process danhSach[MAX];
    int chiSo = 1;
    int index = 2;
    while(n)
    {

        if(test[0].timeXh == 0)
        {

            tinh[dem].timeWait = timeBd[0] - test[0].timeXh;
            tinh[dem].timePro = tinh[dem].timeWait + test[0].cpuB;
            dem++;
            timeBd[1] = test[0].cpuB;
            danhSach[0] = test[0];

            xoa(test,n,0);
        }
        int minn = test[0].cpuB;
        for(int i = 0; i<n;i++)
            if(test[i].timeXh < timeBd[index-1] && minn > test[i].cpuB)
                minn = test[i].cpuB;
        for(int i = 0; i<n;i++)
        {
            int demm = 0;

            if(test[i].timeXh < timeBd[index-1] && test[i].cpuB == minn)
            {
                demm++;
                tinh[dem].timeWait =timeBd[index-1] - test[i].timeXh;
                tinh[dem].timePro = tinh[dem].timeWait + test[i].cpuB;
                dem++;
                timeBd[index] = timeBd[index-1] + test[i].cpuB;
                danhSach[chiSo] = test[i];
                chiSo++;
                xoa(test,n,i);
                break;
            }
            if(demm == 0)
            {
                cout << "\tBan da nhap 2 he tien trinh.";
                return 0;
            }
        }
        index +=1 ;
    }
    for(int i=0;i<x;i++)
        KeNgang();
    cout <<endl << "|";
    for(int i=0;i<x;i++)
        cout << "\tp" << danhSach[i].pro << "\t|";
    cout << endl;
    for(int i=0;i<x;i++)
        KeNgang();
    cout << endl;
    for(int i=0;i<x+1;i++)
        cout << timeBd[i] << "\t\t";
    return 1;
}


void tinhThoiGian(time tinh[], int n)
{
    float timeCho, timeXuLi;
    for(int i=0; i<n;i++)
    {
        timeCho += tinh[i].timeWait;
        timeXuLi += tinh[i].timePro;
    }
    timeCho/=n;
    timeXuLi/=n;
    cout << endl << "Thoi gian cho trung binh la: " << timeCho;
    cout << endl << "Thoi gian xu li trung binh la: " << timeXuLi;
}

int main()
{
	process test[MAX];
	time tinh[MAX];
	int n;
	nhap(test,n);
	xuat(test, n);
	sapXep(test,n);
	xuat(test, n);
	cout << endl << "=================================" << endl;
	cout << "Gian do Gantt la: "<< endl;
	taoGianDoGantt(test,tinh,n);
	tinhThoiGian(tinh,n);
}
