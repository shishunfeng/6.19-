#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#define WIDTH 50
#define HEIGHT 50
int year, month, day;  //������

char weekday[7][3] = { "һ","��","��","��","��","��","��" };
int tempMap[6 * 7] = {0};//��ʱ�洢��ͼ
int map[6][7] = {0};  //��ʽ�ĵ�ͼ

//���ֲ���
void TextLayout()
{
	//����һ�����ֵ�����
	settextstyle(30,0,"����");

	//����һ��������ɫ
	settextcolor(RED);

	//��ʾ����
	outtextxy(100,10,"�����ý���--");

	//�������
	char data[20] = { "" };
	sprintf_s(data,20,"%d��%d��%d��",year,month,day);
	outtextxy(430,370,data);
}

//����ƽ�������
//���꣺�ܱ�������������100�������
//�ܱ�400����
int IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
		return 1; 
		return 0;
}

//��ÿ���µ�����
//ѡ��ṹ
int GetDayByMonth(int year, int month)
{
	switch (month)
	{
	case 2:
		return IsLeapYear(year) ? 29 : 28;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	default:
		return 30;
		break;
	}
}

//�����û���������ڣ���1900��1��1���ж�����
int GetSumDay(int year, int month)
{
	int sum = 0;
	for (int i = 1900; i < year; i++)
	{
		sum += IsLeapYear(i) ? 366 : 365;
	}

	//�㵱ǰ������
	for (int i = 1; i < month; i++)
	{
		sum += GetDayByMonth(year,i);
	}
	return sum;
}

 //�õ���ͼ
void GetMap(int sum, int year, int month)
{
	int result, temp, i;
	int count = 0;
	result = sum % 7;
	for (i = 0; i < result; i++)
	{
		tempMap[count++] = 0;
	}
	//�ӵڼ�����ӡ1��
	temp = 7 - result;
	for (i = 1; i <= GetDayByMonth(year, month); i++)
	{
		tempMap[count++] = i;
	}
	//һά����װ���ɶ�ά����洢
	int pos = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = tempMap[pos++];
		}

	}
}

//���־��з�װ������xx = (widge-ziti)/2+x;
void OutTextMid(int x, int y, const char* str)
{
	settextstyle(35,0,"����");
	settextcolor(WHITE);
	int xx = x + (WIDTH - textwidth(str)) / 2;
	int yy = y + (HEIGHT - textheight(str)) / 2;
	outtextxy(xx,yy,str);
}

//�õ���ͼ
void DrawCalendar()
{
	int x = 50, y = 50;
	for (int i = 0; i < 7; i++)
	{
		OutTextMid(x+i*WIDTH,y,weekday[i]);
	}
	//��������
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int x = WIDTH * j + 50;
			int y = HEIGHT * i + 100;
			if (map[i][j] != 0)
			{
				setlinecolor(BLUE);
				setfillcolor(map[i][j] == day ? LIGHTBLUE : RED);
				fillrectangle(x,y,x+WIDTH,y+HEIGHT);
				//ͼ�λ�ֻ������ַ���
				//����ת���ַ���
				char str[20] = { "" };
				sprintf_s(str, 20, "%d", map[i][j]);
				OutTextMid(x, y, str);
			}
		}
	}
}

//��������
void PlayMusic()
{
	mciSendString("open ./res/1.mp3", 0, 0, 0);
	mciSendString("play ./res/1.mp3 repeat", 0, 0, 0);
}

//���ּ�����ʾ
void TextAction()
{
	const char* text[20] = { "��","��","��","��","Ŭ","��","��" };
	settextstyle(35,0,"����");
	settextcolor(YELLOW);
	int x = 500,y = 50;
	for (int i = 0; i < 7; i++)
	{
		if (i < 6)
		{
			outtextxy(x, y + i * 50, text[i]);
		}
		else
		{
			outtextxy(x-50, y + (i-7) * 50+20, text[i]);
		}
		Sleep(500);
	}
}

int main()
{
	printf("intput year month day:");
	scanf_s("%d%d%d", &year,&month,&day);
	GetMap(GetDayByMonth(year, month), year, month);
	//printf("%d\n",GetSumDay(year,month));
	//system("pause");
	PlayMusic();
	initgraph(563, 413);
	int a;
	a = 1;
	IMAGE background; //����ͼƬ������

	loadimage(&background, "./res/background.bmp"); //ͼƬ��ŵ�ַ

	putimage(0, 0, &background);
	//ȥ�����ֱ���
	setbkmode(TRANSPARENT);
	TextLayout();

	DrawCalendar();//��ʾ����
	TextAction();
	while (1);
	closegraph();
	return 0;
}