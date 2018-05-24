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



void taoGianDoGantt(process test[],time tinh[], int n)
{
    int timeBd = 0, dem = 0, x=n;
    while(n)
    {
        if(x==n)
            cout << "\t" << timeBd;
        if(test[0].timeXh == 0)
        {
            cout <<"\t" << test[0].pro;
            tinh[dem].timeWait = timeBd - test[0].timeXh;
            tinh[dem].timePro = tinh[dem].timeWait + test[0].cpuB;
            dem++;
            timeBd += test[0].cpuB;
            xoa(test,n,0);
        }
        int minn = test[0].cpuB;
        for(int i = 0; i<n;i++)
            if(test[i].timeXh < timeBd && minn > test[i].cpuB)
                minn = test[i].cpuB;
        for(int i = 0; i<n;i++)
            if(test[i].timeXh < timeBd && minn == test[i].cpuB)
            {

                cout << "\t" << timeBd;
                cout <<"\t" << test[i].pro;
                tinh[dem].timeWait =timeBd - test[i].timeXh;
                tinh[dem].timePro = tinh[dem].timeWait + test[i].cpuB;
                dem++;
                timeBd += test[i].cpuB;
                xoa(test,n,i);
            }
        if(n==0)
            cout << "\t" << timeBd;
    }
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
