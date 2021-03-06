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
    do{
        cout << "Nhap so tien trinh: ";//Ã­t nháº¥t cÃ³ 2 tiáº¿n trÃ¬nh
        cin >> n;
    }while(n<2);
    int heTienTrinhHopLe=1;
    do
    {
        for(int i = 0; i < n; i++)
        {
            int thoiDiemXuatHienHopLe;
            cout << "\tNhap tien trinh p" << i+1 << endl;
            test[i].pro = i+1;
            do
            {
                thoiDiemXuatHienHopLe = 1;
                cout << "\t\tNhap thoi diem xuat hien: ";//thá»i Ä‘iá»ƒm xuáº¥t hiá»‡n >= 0 && thá»i Ä‘iá»ƒm xuáº¥t hiá»‡n cá»§a 2 tiáº¿n trÃ¬nh ko Ä‘Æ°á»£c trÃ¹ng nhau
                cin >> test[i].timeXh;
                for(int j=0 ; j < i ; j++)
                    if(test[i].timeXh == test[j].timeXh)
                    {
                        cout << "\t\tTrung thoi diem xuat hien.\n";
                        thoiDiemXuatHienHopLe = 0;
                    }
            }while(test[i].timeXh < 0 || thoiDiemXuatHienHopLe == 0);
            do
            {
                cout << "\t\tNhap thoi gian cap: ";//thá»i gian cáº¥p  >0
                cin >> test[i].cpuB;
            }while(test[i].cpuB <= 0);
        }
        for(int i = 0 ; i < n ; i++)
            if(test[i].timeXh == 0)
                heTienTrinhHopLe = 0;
        if(heTienTrinhHopLe != 0)
            cout << "\tHe tien trinh vua nhap khong co tien trinh bat dau o thoi diem 0. Moi nhap lai:\n";
    }while(heTienTrinhHopLe != 0);
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
	sapXep(test,n);
	xuat(test, n);
	cout << endl << "=================================" << endl;
	cout << "Gian do Gantt la: "<< endl;
	int truee = taoGianDoGantt(test,tinh,n);
	if(truee == 1)
        tinhThoiGian(tinh,n);
	cout << endl;
	system("pause");
}
