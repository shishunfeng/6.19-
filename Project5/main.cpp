#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#define WIDTH 50
#define HEIGHT 50
int year, month, day;  //年月日

char weekday[7][3] = { "一","二","三","四","五","六","日" };
int tempMap[6 * 7] = {0};//暂时存储地图
int map[6][7] = {0};  //正式的地图

//文字布局
void TextLayout()
{
	//设置一下文字的字体
	settextstyle(30,0,"楷体");

	//设置一下文字颜色
	settextcolor(RED);

	//显示文字
	outtextxy(100,10,"于秋悦教育--");

	//输出日期
	char data[20] = { "" };
	sprintf_s(data,20,"%d年%d月%d日",year,month,day);
	outtextxy(430,370,data);
}

//区分平年和闰年
//闰年：能被四整除，不被100整除年份
//能被400整除
int IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
		return 1; 
		return 0;
}

//求每个月的天数
//选择结构
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

//计算用户输入的日期，离1900年1月1日有多少天
int GetSumDay(int year, int month)
{
	int sum = 0;
	for (int i = 1900; i < year; i++)
	{
		sum += IsLeapYear(i) ? 366 : 365;
	}

	//算当前年天数
	for (int i = 1; i < month; i++)
	{
		sum += GetDayByMonth(year,i);
	}
	return sum;
}

 //得到地图
void GetMap(int sum, int year, int month)
{
	int result, temp, i;
	int count = 0;
	result = sum % 7;
	for (i = 0; i < result; i++)
	{
		tempMap[count++] = 0;
	}
	//从第几个打印1号
	temp = 7 - result;
	for (i = 1; i <= GetDayByMonth(year, month); i++)
	{
		tempMap[count++] = i;
	}
	//一维数组装换成二维数组存储
	int pos = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = tempMap[pos++];
		}

	}
}

//文字居中封装函数：xx = (widge-ziti)/2+x;
void OutTextMid(int x, int y, const char* str)
{
	settextstyle(35,0,"楷体");
	settextcolor(WHITE);
	int xx = x + (WIDTH - textwidth(str)) / 2;
	int yy = y + (HEIGHT - textheight(str)) / 2;
	outtextxy(xx,yy,str);
}

//得到地图
void DrawCalendar()
{
	int x = 50, y = 50;
	for (int i = 0; i < 7; i++)
	{
		OutTextMid(x+i*WIDTH,y,weekday[i]);
	}
	//日历几号
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
				//图形化只能输出字符串
				//数字转换字符串
				char str[20] = { "" };
				sprintf_s(str, 20, "%d", map[i][j]);
				OutTextMid(x, y, str);
			}
		}
	}
}

//播放音乐
void PlayMusic()
{
	mciSendString("open ./res/1.mp3", 0, 0, 0);
	mciSendString("play ./res/1.mp3 repeat", 0, 0, 0);
}

//文字鸡汤显示
void TextAction()
{
	const char* text[20] = { "积","极","向","上","努","力","悦" };
	settextstyle(35,0,"楷体");
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
	IMAGE background; //定义图片变量名

	loadimage(&background, "./res/background.bmp"); //图片存放地址

	putimage(0, 0, &background);
	//去掉文字背景
	setbkmode(TRANSPARENT);
	TextLayout();

	DrawCalendar();//显示星期
	TextAction();
	while (1);
	closegraph();
	return 0;
}