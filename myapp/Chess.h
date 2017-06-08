#pragma once

#include "stdafx.h"
#include <iostream>
using namespace std;

class Chess
{
private:
	int n; //棋盘线数
	int N; //实际数组存储数，方便处理，边框多加格点
	int size; // 棋盘方格长度
	int o_x, o_y; // 原点
	int r; // 棋子半径
	int step;//下棋步数
	int re;//标识是否可以悔棋

	int a1, a2, a3;//画九个点用
	int a[21][21][2];//备份1
	int b[21][21][2];//备份2
	int c[21][21][2];//存储棋子在棋盘内对应的数据,四周一圈都要设置成3，便于检测棋子死活

public:
	char buf[5];//封装棋子数据通过socket传输step，c_x,c_y
	int xx, yy;//保存最新的棋子位置，包括传过来的。

public:
	Chess()
	{
		n = 19;
		N = n + 2;
		o_y = o_x = 50;
		size = 20;
		r = size / 2;
		re = 0;
		step = 0;
		a1 = 4;
		a2 = 16;
		a3 = 6;
		//初始化棋子[0]位的值为0表示无子，1表示黑子，2表示白子，3表示边界；[1]位的值0表示死，1表示活
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				a[i][j][0] = 0;
				a[i][j][1] = 0;
				b[i][j][0] = 0;
				b[i][j][1] = 0;
				c[i][j][0] = 0;
				c[i][j][1] = 0;
				if (i == 0 || j == 0 || i == 20 || j == 20)
				{
					a[i][j][0] = 3;
					b[i][j][0] = 3;
					c[i][j][0] = 3;
				}
			}
	};
	~Chess();

public:
	//初始化棋子死活，全部置死
	void Init_Chess()
	{
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{

			c[i][j][1] = 0;

		}
	};

	//得到当前下棋步数
	int getStep()
	{
		return step;
	};

	//得到re
	int getRe()
	{
		return re;
	};

	

	//画棋盘
	void Paint_Qipan(CDC *pDC)
	{
		//画网格线
		for (int i = 0; i < n;  i++)
		{
			pDC->MoveTo(o_x, o_y + i * size);
			pDC->LineTo(o_x + (n - 1) * size, o_y + i * size);

			pDC->MoveTo(o_x + i * size, o_y);
			pDC->LineTo(o_x + i * size, o_y + (n - 1) * size);
		}

		//画九个点
		CBrush mBrush(RGB(0, 0, 0));    //定义一个画刷变量
		pDC->SelectObject(&mBrush);   //保存旧的画笔

		for (int i = a1;  i <= a2;  i += a3)
			for (int j = a1; j <= a2; j += a3)
			{				
				pDC->Ellipse(o_x + (i - 1) * size - 5, o_y + (j - 1) * size - 5, 
					o_x + (i - 1) * size + 5, o_y + (j - 1) * size + 5);//画圆（黑子），，依次是椭圆的左上角坐标，右下角坐标，，原点坐标是左上角。
			}
		mBrush.DeleteObject();  //及时释放brush，防止内存泄漏
	};



	//如果棋子坐标正确则下棋子
	int do_Paint_Cell(int c_x, int c_y, CDC *pDC)
	{

		//棋子的全局的实际坐标
		int x = (c_x - 1) * size + o_x;
		int y = (c_y - 1) * size + o_y;


		if (step % 2 != 0)
		{
			Paint_White(x, y, pDC);
			c[c_y][c_x][0] = 2; //对应数组内的值置为2			
		}
		else
		{
			Paint_Black(x, y, pDC);
			c[c_y][c_x][0] = 1;  //对应数组内的值置为1，  x，y坐标倒置，详见上
		}

		step++;//每次下棋之后步数加一
		re = 1;//可以悔棋一步

		//将buf中的数据变成最新的
		xx = c_x;
		yy = c_y;
		int_to_buf();//更新buf中的数据

		return 1;//落子成功

	}


	//画棋子 ， 返回值用于判断下棋子是否成功 0表示失败 1成功
	int Paint_Cell(CDC *pDC, CPoint point)
	{
		int x1 = point.x;
		int y1 = point.y;

		//检测所下棋子坐标是否在棋盘内
		if (x1 > (o_x + (n - 1) * size) || x1 < o_x || y1 >(o_y + (n - 1) * size) || y1 < o_y)
		{
			return 0;
		}		

		//修正下棋棋子的坐标，使棋子落在格点上，加0.5为了满足四舍五入，因为强制转为int会默认丢掉小数。
		int c_x = int((x1 - o_x) / (float)size + 0.5) + 1; //棋子横坐标第几个格子
		int c_y = int((y1 - o_y) / (float)size + 0.5) + 1;  //棋子纵坐标第几个格子

		//检测所下棋子坐标是否存在棋子，，，，
		//此处坐标是颠倒一下xy，因为实际数组存储是这样的，与棋子在棋盘格点上的坐标相反，此问题让我调试了好久,下面存储时也是如此
		if (c[c_y][c_x][0] != 0) return 0;

		if (re == 1) Backup();//如果允许下子且没有悔棋则备份记录

		return do_Paint_Cell(c_x, c_y, pDC);

	};
	
	//提子，消掉棋子，画棋子为十字
	void Del_Cell(int x, int y, CDC *pDC)
	{
		/*这里记录一下对画笔和画刷的使用体验，
		1.如果什么也不添加（画刷，画笔），则会使用默认的黑色实线为画笔进行画，会使用默认的白色进行填充内部
		2.如果只添加画笔，则画出的图形边框一圈的线是添加画笔的属性，
		  而内部填充默认是白色，即也就是没有添加画刷，使用白色填充
		3.如果只添加画刷，则画出的图形边框是默认的黑色实线，内部填充是添加画刷的属性
		4.画刷和画笔都添加，则边框和内部填充分别是添加画笔画刷的属性*/


		CPen penWhite;//定义一个木色画笔变量，，消棋子
		penWhite.CreatePen(PS_SOLID, 1, RGB(212, 143, 28));//创建木色画笔
		//CBrush mBrushWhite(RGB(255, 255, 255));  //定义一个白色画刷变量
		CBrush mBrushWhite(RGB(212, 143, 28));  //定义一个木色画刷变量

		//penWhite.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//创建白画笔
		
		pDC->SelectObject(&penWhite);//将木色画笔选入当前设备环境
		pDC->SelectObject(&mBrushWhite);//将木色画刷加入设备，用于填充
		pDC->Ellipse(x - r, y - r, x + r, y + r);//画木色圆，用于消掉棋子，依次是椭圆的左上角坐标，右下角坐标，，原点坐标是左上角。
		
		//画十字
		CPen penBlack;//定义一个黑画笔变量，画十字
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//创建黑画笔
		pDC->SelectObject(&penBlack);//将黑画笔选入当前设备环境


		//画横线，考虑到边角的情况
		if (x == o_x)
		{
			pDC->MoveTo(x, y);
			pDC->LineTo(x + r, y);
		}
		else if (x == (o_x + size * (n - 1)))
		{
			pDC->MoveTo(x - r, y);
			pDC->LineTo(x, y);
		}
		else
		{
			pDC->MoveTo(x - r, y);
			pDC->LineTo(x + r, y);
		}
		
		//画纵线，考虑到边角的情况
		if (y == o_y)
		{
			pDC->MoveTo(x, y);
			pDC->LineTo(x, y + r);
		}
		else if (y == (o_y + size * (n - 1)))
		{
			pDC->MoveTo(x, y - r);
			pDC->LineTo(x, y);
		}
		else
		{
			pDC->MoveTo(x, y - r);
			pDC->LineTo(x, y + r);
		}
		

		penWhite.DeleteObject(); //及时释放pen，防止内存泄漏
		penBlack.DeleteObject(); //及时释放pen，防止内存泄漏

		//画九个点
		CBrush mBrush(RGB(0, 0, 0));    //定义一个画刷变量
		pDC->SelectObject(&mBrush);   //保存旧的画笔

		for (int i = a1; i <= a2; i += a3)
		for (int j = a1; j <= a2; j += a3)
			{
				if (x == o_x + (i - 1) * size && y == o_y + (j - 1) * size)
				{
					pDC->Ellipse(o_x + (i - 1) * size - 5, o_y + (j - 1) * size - 5,
						o_x + (i - 1) * size + 5, o_y + (j - 1) * size + 5);//画圆（黑子），，依次是椭圆的左上角坐标，右下角坐标，，原点坐标是左上角。
				}			
			}
		mBrush.DeleteObject();  //及时释放brush，防止内存泄漏

	};

	

	//检测所有棋子死活,如果棋子是活得（此活意思是四周有空）则将所有与它相连的同色棋子都活
	//某个棋子的死活：四周只要有子就是死   k表示棋子是黑1或白2空0
	void Check_Qi(int k)
	{
		//遍历所有位置，存储位置是1-19
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j++)
			{
				//如果不是要检测的棋子，或无棋子， 或棋子已活，则不进行检测处理
				if (c[i][j][0] != k || c[i][j][1] == 1) continue;  

				//判断棋子是否为活
				if (c[i - 1][j][0] == 0 ||
					c[i + 1][j][0] == 0 ||
					c[i][j - 1][0] == 0 ||
					c[i][j + 1][0] == 0)
				{
					//Deal_Life(i, j, k, 0);  //活得话，则进行处理，将所连着的所有同色棋子置活
					Deal_Life(i, j, k);   //活得话，则进行处理，将所连着的所有同色棋子置活
				}
				
			}		
	}

	//将所有连着的同一颜色棋子置为活，利用递归
	void Deal_Life(int c_x, int c_y, int k)
	{
		//如果不是要检测的棋子，或者此棋子已活，不再处理
		if (c[c_x][c_y][0] != k || c[c_x][c_y][1] == 1) return;

		c[c_x][c_y][1] = 1;//将棋子置活
		//检测四周棋子
		Deal_Life(c_x, c_y - 1, k);
		Deal_Life(c_x, c_y + 1, k);
		Deal_Life(c_x - 1, c_y, k);
		Deal_Life(c_x + 1, c_y, k);
	};


	//将所有连着的同一颜色棋子置为活，利用递归    l表示方向,上下左右1234
	/*void Deal_Life(int c_x, int c_y, int k, int l)
	{
		if (c[c_x][c_y][0] != k || c[c_x][c_y][1] == 1) return;

		c[c_x][c_y][1] = 1;

		if (l == 0)
		{
			Deal_Life(c_x, c_y - 1, k, 2);
			Deal_Life(c_x, c_y + 1, k, 1);
			Deal_Life(c_x - 1, c_y, k, 4);
			Deal_Life(c_x + 1, c_y, k, 3);
		}

		if (l == 1)
		{
			
			Deal_Life(c_x, c_y + 1, k, 1);
			Deal_Life(c_x - 1, c_y, k, 4);
			Deal_Life(c_x + 1, c_y, k, 3);
		}

		if (l == 2)
		{
			Deal_Life(c_x, c_y - 1, k, 2);
			
			Deal_Life(c_x - 1, c_y, k, 4);
			Deal_Life(c_x + 1, c_y, k, 3);
		}

		if (l == 3)
		{
			Deal_Life(c_x, c_y - 1, k, 2);
			Deal_Life(c_x, c_y + 1, k, 1);
			
			Deal_Life(c_x + 1, c_y, k, 3);
		}

		if (l == 4)
		{
			Deal_Life(c_x, c_y - 1, k, 2);
			Deal_Life(c_x, c_y + 1, k, 1);
			Deal_Life(c_x - 1, c_y, k, 4);			
		}		
	};*/

	//检测棋盘将指定颜色的死的棋子去掉
	int Remove_Cell(int k, CDC *pDC)
	{
		int is = 0;//标识是否删掉棋子
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				//如果不是要检测颜色的棋子，或棋子不死，不进行处理
				if (c[i][j][0] != k || c[i][j][1] != 0) continue;
				c[i][j][0] = 0;//将死的棋子置0
				
				Del_Cell((j - 1) * size + o_y, (i - 1) * size + o_x, pDC);//擦掉棋子

				is = 1;
			}
		return is;
	}

	//计算输赢，采用简单的数双方子评判
	void Result()
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (c[i][j][0] == 1) sum1 ++;  //计算黑子个数
				if (c[i][j][0] == 2) sum2 ++;  //计算白子个数			
			}

	};

	//备份棋盘数据
	void Backup()
	{
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a[i][j][0] = b[i][j][0];
			a[i][j][1] = b[i][j][1];

			b[i][j][0] = c[i][j][0];
			b[i][j][1] = c[i][j][1];			
		}
	};

	//悔棋
	int reChess(CDC *pDC)
	{
		
		step--;//步数减一
		Remove_Cell(1, pDC);//移除黑子
		Remove_Cell(2, pDC);//移除白子
		rePaint_Chess(pDC);//重画备份的b数组的棋子

		re = 0;//悔棋次数置0；
		//将b数据复制到c数据，c保留当前棋盘最新的
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			c[i][j][0] = b[i][j][0];
			c[i][j][1] = b[i][j][1];
		}

		return 1;
	};

	//重画备份的棋子
	void rePaint_Chess(CDC *pDC)
	{
	
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (b[i][j][0] == 0 || b[i][j][0] == 3) continue;

			if (b[i][j][0] == 1)
				Paint_Black((j-1) * size + o_x, (i-1) * size + o_y, pDC);
			else 
				Paint_White((j - 1) * size + o_x, (i - 1) * size + o_y, pDC);
		}

	};

	void Paint_Black(int x, int y, CDC *pDC)
	{
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//创建黑画笔
		CBrush mBrush(RGB(0, 0, 0));    //定义一个画刷变量

		pDC->SelectObject(&penBlack);
		pDC->SelectObject(&mBrush);   //将画刷添加进设备

		//画圆（黑子），，依次是椭圆的左上角坐标，右下角坐标，，原点坐标是左上角。
		pDC->Ellipse(x - r, y - r, x + r, y + r);
		
		penBlack.DeleteObject(); //及时释放pen，防止内存泄漏
		mBrush.DeleteObject();  //及时释放brush，防止内存泄漏
	};
	void Paint_White(int x, int y, CDC *pDC)
	{
		CPen penWhite;//定义一个白画笔变量，消白圆，消棋子
		penWhite.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//创建白画笔
		CBrush mBrushWhite(RGB(255, 255, 255));  //定义一个白色画刷变量	

		pDC->SelectObject(&penWhite);
		pDC->SelectObject(&mBrushWhite);


		//画圆（白子），依次是椭圆的左上角坐标，右下角坐标，，原点坐标是左上角。
		pDC->Ellipse(x - r, y - r, x + r, y + r);

		penWhite.DeleteObject(); //及时释放pen，防止内存泄漏
		mBrushWhite.DeleteObject();  //及时释放brush，防止内存泄漏
	};

	//打劫判断
	int dajie()
	{
		int e = 0;

		//
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (c[i][j][0] != a[i][j][0])
			{
				e = 1;
				break;
			}
		}

		if (e == 1) return 0;//不打劫

		return 1;//打劫返回1
		
	};

	//新游戏
	void newGame(CDC *pDC)
	{
		Chess();
		Init_Chess();
		Remove_Cell(1, pDC);
		Remove_Cell(2, pDC);
	}


	//int 转 char
	char intTOchar(int a)
	{
		return (char)(a + 48);
	};

	//char 转 int
	int charTOint(char a)
	{
		return (int)(a - 48);
	};
	//得到此时的buf，需要传过去的值
	char* getBuf()
	{
		return buf;
	};

	//更新棋盘及数据
	void update(CDC *pDC)
	{
		buf_to_int();
		do_Paint_Cell(xx, yy, pDC);
		
		//只进行简单的检测对方棋子即可，因为在传过来之前已经检测过
		int who;//存储此步棋是哪方下的，1表示黑，2表示白；
		who = (step % 2) + 1;//得到对方；
		Check_Qi(who);//检测对方棋子
		Remove_Cell(who, pDC); //消掉对方死的棋子
		Init_Chess();//将棋子初始化，全部置死
	}

	//将接收到的字符数据转为整数
	void buf_to_int()
	{
		xx = charTOint(buf[0]) * 10 + charTOint(buf[1]);
		yy = charTOint(buf[2]) * 10 + charTOint(buf[3]);
	}
	//将棋子在棋盘的位置（包括大于9）的整数转为四个字符方便传输
	void int_to_buf()
	{
		buf[0] = intTOchar(xx / 10);
		buf[1] = intTOchar(xx % 10);
		buf[2] = intTOchar(yy / 10);
		buf[3] = intTOchar(yy % 10);
		buf[4] = '\0';
	}

	//下棋成功后对是否销子做出处理
	int Chess_Suc_Deal(CDC *pDC)
	{
		int who;//存储此步棋是哪方下的，1表示黑，2表示白；
		who = (step % 2) + 1;//得到对方；

		Check_Qi(who);//检测对方棋子
		Remove_Cell(who, pDC); //消掉对方死的棋子
		Init_Chess();//将棋子初始化，全部置死

		who = ((step + 1) % 2) + 1;//得到我方；
		Check_Qi(who);//检测我方棋子

		if (Remove_Cell(who, pDC) == 1) 
			return reChess(pDC); //如果会消掉我方死的棋子，则为禁着点，退一步棋
		
		if(dajie() == 1) 
			return reChess(pDC);//打劫处理，退一步棋
		
		Init_Chess();//将棋子初始化，全部置死

		return 0;
	}

};

