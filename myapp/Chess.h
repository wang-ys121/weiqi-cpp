#pragma once

#include "stdafx.h"
#include <iostream>
using namespace std;

class Chess
{
private:
	int n; //��������
	int N; //ʵ������洢�������㴦���߿��Ӹ��
	int size; // ���̷��񳤶�
	int o_x, o_y; // ԭ��
	int r; // ���Ӱ뾶
	int step;//���岽��
	int re;//��ʶ�Ƿ���Ի���

	int a1, a2, a3;//���Ÿ�����
	int a[21][21][2];//����1
	int b[21][21][2];//����2
	int c[21][21][2];//�洢�����������ڶ�Ӧ������,����һȦ��Ҫ���ó�3�����ڼ����������

public:
	char buf[5];//��װ��������ͨ��socket����step��c_x,c_y
	int xx, yy;//�������µ�����λ�ã������������ġ�

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
		//��ʼ������[0]λ��ֵΪ0��ʾ���ӣ�1��ʾ���ӣ�2��ʾ���ӣ�3��ʾ�߽磻[1]λ��ֵ0��ʾ����1��ʾ��
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
	//��ʼ���������ȫ������
	void Init_Chess()
	{
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{

			c[i][j][1] = 0;

		}
	};

	//�õ���ǰ���岽��
	int getStep()
	{
		return step;
	};

	//�õ�re
	int getRe()
	{
		return re;
	};

	

	//������
	void Paint_Qipan(CDC *pDC)
	{
		//��������
		for (int i = 0; i < n;  i++)
		{
			pDC->MoveTo(o_x, o_y + i * size);
			pDC->LineTo(o_x + (n - 1) * size, o_y + i * size);

			pDC->MoveTo(o_x + i * size, o_y);
			pDC->LineTo(o_x + i * size, o_y + (n - 1) * size);
		}

		//���Ÿ���
		CBrush mBrush(RGB(0, 0, 0));    //����һ����ˢ����
		pDC->SelectObject(&mBrush);   //����ɵĻ���

		for (int i = a1;  i <= a2;  i += a3)
			for (int j = a1; j <= a2; j += a3)
			{				
				pDC->Ellipse(o_x + (i - 1) * size - 5, o_y + (j - 1) * size - 5, 
					o_x + (i - 1) * size + 5, o_y + (j - 1) * size + 5);//��Բ�����ӣ�������������Բ�����Ͻ����꣬���½����꣬��ԭ�����������Ͻǡ�
			}
		mBrush.DeleteObject();  //��ʱ�ͷ�brush����ֹ�ڴ�й©
	};



	//�������������ȷ��������
	int do_Paint_Cell(int c_x, int c_y, CDC *pDC)
	{

		//���ӵ�ȫ�ֵ�ʵ������
		int x = (c_x - 1) * size + o_x;
		int y = (c_y - 1) * size + o_y;


		if (step % 2 != 0)
		{
			Paint_White(x, y, pDC);
			c[c_y][c_x][0] = 2; //��Ӧ�����ڵ�ֵ��Ϊ2			
		}
		else
		{
			Paint_Black(x, y, pDC);
			c[c_y][c_x][0] = 1;  //��Ӧ�����ڵ�ֵ��Ϊ1��  x��y���굹�ã������
		}

		step++;//ÿ������֮������һ
		re = 1;//���Ի���һ��

		//��buf�е����ݱ�����µ�
		xx = c_x;
		yy = c_y;
		int_to_buf();//����buf�е�����

		return 1;//���ӳɹ�

	}


	//������ �� ����ֵ�����ж��������Ƿ�ɹ� 0��ʾʧ�� 1�ɹ�
	int Paint_Cell(CDC *pDC, CPoint point)
	{
		int x1 = point.x;
		int y1 = point.y;

		//����������������Ƿ���������
		if (x1 > (o_x + (n - 1) * size) || x1 < o_x || y1 >(o_y + (n - 1) * size) || y1 < o_y)
		{
			return 0;
		}		

		//�����������ӵ����꣬ʹ�������ڸ���ϣ���0.5Ϊ�������������룬��Ϊǿ��תΪint��Ĭ�϶���С����
		int c_x = int((x1 - o_x) / (float)size + 0.5) + 1; //���Ӻ�����ڼ�������
		int c_y = int((y1 - o_y) / (float)size + 0.5) + 1;  //����������ڼ�������

		//����������������Ƿ�������ӣ�������
		//�˴������ǵߵ�һ��xy����Ϊʵ������洢�������ģ������������̸���ϵ������෴�����������ҵ����˺þ�,����洢ʱҲ�����
		if (c[c_y][c_x][0] != 0) return 0;

		if (re == 1) Backup();//�������������û�л����򱸷ݼ�¼

		return do_Paint_Cell(c_x, c_y, pDC);

	};
	
	//���ӣ��������ӣ�������Ϊʮ��
	void Del_Cell(int x, int y, CDC *pDC)
	{
		/*�����¼һ�¶Ի��ʺͻ�ˢ��ʹ�����飬
		1.���ʲôҲ����ӣ���ˢ�����ʣ������ʹ��Ĭ�ϵĺ�ɫʵ��Ϊ���ʽ��л�����ʹ��Ĭ�ϵİ�ɫ��������ڲ�
		2.���ֻ��ӻ��ʣ��򻭳���ͼ�α߿�һȦ��������ӻ��ʵ����ԣ�
		  ���ڲ����Ĭ���ǰ�ɫ����Ҳ����û����ӻ�ˢ��ʹ�ð�ɫ���
		3.���ֻ��ӻ�ˢ���򻭳���ͼ�α߿���Ĭ�ϵĺ�ɫʵ�ߣ��ڲ��������ӻ�ˢ������
		4.��ˢ�ͻ��ʶ���ӣ���߿���ڲ����ֱ�����ӻ��ʻ�ˢ������*/


		CPen penWhite;//����һ��ľɫ���ʱ�������������
		penWhite.CreatePen(PS_SOLID, 1, RGB(212, 143, 28));//����ľɫ����
		//CBrush mBrushWhite(RGB(255, 255, 255));  //����һ����ɫ��ˢ����
		CBrush mBrushWhite(RGB(212, 143, 28));  //����һ��ľɫ��ˢ����

		//penWhite.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//�����׻���
		
		pDC->SelectObject(&penWhite);//��ľɫ����ѡ�뵱ǰ�豸����
		pDC->SelectObject(&mBrushWhite);//��ľɫ��ˢ�����豸���������
		pDC->Ellipse(x - r, y - r, x + r, y + r);//��ľɫԲ�������������ӣ���������Բ�����Ͻ����꣬���½����꣬��ԭ�����������Ͻǡ�
		
		//��ʮ��
		CPen penBlack;//����һ���ڻ��ʱ�������ʮ��
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//�����ڻ���
		pDC->SelectObject(&penBlack);//���ڻ���ѡ�뵱ǰ�豸����


		//�����ߣ����ǵ��߽ǵ����
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
		
		//�����ߣ����ǵ��߽ǵ����
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
		

		penWhite.DeleteObject(); //��ʱ�ͷ�pen����ֹ�ڴ�й©
		penBlack.DeleteObject(); //��ʱ�ͷ�pen����ֹ�ڴ�й©

		//���Ÿ���
		CBrush mBrush(RGB(0, 0, 0));    //����һ����ˢ����
		pDC->SelectObject(&mBrush);   //����ɵĻ���

		for (int i = a1; i <= a2; i += a3)
		for (int j = a1; j <= a2; j += a3)
			{
				if (x == o_x + (i - 1) * size && y == o_y + (j - 1) * size)
				{
					pDC->Ellipse(o_x + (i - 1) * size - 5, o_y + (j - 1) * size - 5,
						o_x + (i - 1) * size + 5, o_y + (j - 1) * size + 5);//��Բ�����ӣ�������������Բ�����Ͻ����꣬���½����꣬��ԭ�����������Ͻǡ�
				}			
			}
		mBrush.DeleteObject();  //��ʱ�ͷ�brush����ֹ�ڴ�й©

	};

	

	//���������������,��������ǻ�ã��˻���˼�������пգ�����������������ͬɫ���Ӷ���
	//ĳ�����ӵ��������ֻҪ���Ӿ�����   k��ʾ�����Ǻ�1���2��0
	void Check_Qi(int k)
	{
		//��������λ�ã��洢λ����1-19
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j++)
			{
				//�������Ҫ�������ӣ��������ӣ� �������ѻ�򲻽��м�⴦��
				if (c[i][j][0] != k || c[i][j][1] == 1) continue;  

				//�ж������Ƿ�Ϊ��
				if (c[i - 1][j][0] == 0 ||
					c[i + 1][j][0] == 0 ||
					c[i][j - 1][0] == 0 ||
					c[i][j + 1][0] == 0)
				{
					//Deal_Life(i, j, k, 0);  //��û�������д����������ŵ�����ͬɫ�����û�
					Deal_Life(i, j, k);   //��û�������д����������ŵ�����ͬɫ�����û�
				}
				
			}		
	}

	//���������ŵ�ͬһ��ɫ������Ϊ����õݹ�
	void Deal_Life(int c_x, int c_y, int k)
	{
		//�������Ҫ�������ӣ����ߴ������ѻ���ٴ���
		if (c[c_x][c_y][0] != k || c[c_x][c_y][1] == 1) return;

		c[c_x][c_y][1] = 1;//�������û�
		//�����������
		Deal_Life(c_x, c_y - 1, k);
		Deal_Life(c_x, c_y + 1, k);
		Deal_Life(c_x - 1, c_y, k);
		Deal_Life(c_x + 1, c_y, k);
	};


	//���������ŵ�ͬһ��ɫ������Ϊ����õݹ�    l��ʾ����,��������1234
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

	//������̽�ָ����ɫ����������ȥ��
	int Remove_Cell(int k, CDC *pDC)
	{
		int is = 0;//��ʶ�Ƿ�ɾ������
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				//�������Ҫ�����ɫ�����ӣ������Ӳ����������д���
				if (c[i][j][0] != k || c[i][j][1] != 0) continue;
				c[i][j][0] = 0;//������������0
				
				Del_Cell((j - 1) * size + o_y, (i - 1) * size + o_x, pDC);//��������

				is = 1;
			}
		return is;
	}

	//������Ӯ�����ü򵥵���˫��������
	void Result()
	{
		int sum1 = 0, sum2 = 0;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (c[i][j][0] == 1) sum1 ++;  //������Ӹ���
				if (c[i][j][0] == 2) sum2 ++;  //������Ӹ���			
			}

	};

	//������������
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

	//����
	int reChess(CDC *pDC)
	{
		
		step--;//������һ
		Remove_Cell(1, pDC);//�Ƴ�����
		Remove_Cell(2, pDC);//�Ƴ�����
		rePaint_Chess(pDC);//�ػ����ݵ�b���������

		re = 0;//���������0��
		//��b���ݸ��Ƶ�c���ݣ�c������ǰ�������µ�
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			c[i][j][0] = b[i][j][0];
			c[i][j][1] = b[i][j][1];
		}

		return 1;
	};

	//�ػ����ݵ�����
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
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//�����ڻ���
		CBrush mBrush(RGB(0, 0, 0));    //����һ����ˢ����

		pDC->SelectObject(&penBlack);
		pDC->SelectObject(&mBrush);   //����ˢ��ӽ��豸

		//��Բ�����ӣ�������������Բ�����Ͻ����꣬���½����꣬��ԭ�����������Ͻǡ�
		pDC->Ellipse(x - r, y - r, x + r, y + r);
		
		penBlack.DeleteObject(); //��ʱ�ͷ�pen����ֹ�ڴ�й©
		mBrush.DeleteObject();  //��ʱ�ͷ�brush����ֹ�ڴ�й©
	};
	void Paint_White(int x, int y, CDC *pDC)
	{
		CPen penWhite;//����һ���׻��ʱ���������Բ��������
		penWhite.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//�����׻���
		CBrush mBrushWhite(RGB(255, 255, 255));  //����һ����ɫ��ˢ����	

		pDC->SelectObject(&penWhite);
		pDC->SelectObject(&mBrushWhite);


		//��Բ�����ӣ�����������Բ�����Ͻ����꣬���½����꣬��ԭ�����������Ͻǡ�
		pDC->Ellipse(x - r, y - r, x + r, y + r);

		penWhite.DeleteObject(); //��ʱ�ͷ�pen����ֹ�ڴ�й©
		mBrushWhite.DeleteObject();  //��ʱ�ͷ�brush����ֹ�ڴ�й©
	};

	//����ж�
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

		if (e == 1) return 0;//�����

		return 1;//��ٷ���1
		
	};

	//����Ϸ
	void newGame(CDC *pDC)
	{
		Chess();
		Init_Chess();
		Remove_Cell(1, pDC);
		Remove_Cell(2, pDC);
	}


	//int ת char
	char intTOchar(int a)
	{
		return (char)(a + 48);
	};

	//char ת int
	int charTOint(char a)
	{
		return (int)(a - 48);
	};
	//�õ���ʱ��buf����Ҫ����ȥ��ֵ
	char* getBuf()
	{
		return buf;
	};

	//�������̼�����
	void update(CDC *pDC)
	{
		buf_to_int();
		do_Paint_Cell(xx, yy, pDC);
		
		//ֻ���м򵥵ļ��Է����Ӽ��ɣ���Ϊ�ڴ�����֮ǰ�Ѿ�����
		int who;//�洢�˲������ķ��µģ�1��ʾ�ڣ�2��ʾ�ף�
		who = (step % 2) + 1;//�õ��Է���
		Check_Qi(who);//���Է�����
		Remove_Cell(who, pDC); //�����Է���������
		Init_Chess();//�����ӳ�ʼ����ȫ������
	}

	//�����յ����ַ�����תΪ����
	void buf_to_int()
	{
		xx = charTOint(buf[0]) * 10 + charTOint(buf[1]);
		yy = charTOint(buf[2]) * 10 + charTOint(buf[3]);
	}
	//�����������̵�λ�ã���������9��������תΪ�ĸ��ַ����㴫��
	void int_to_buf()
	{
		buf[0] = intTOchar(xx / 10);
		buf[1] = intTOchar(xx % 10);
		buf[2] = intTOchar(yy / 10);
		buf[3] = intTOchar(yy % 10);
		buf[4] = '\0';
	}

	//����ɹ�����Ƿ�������������
	int Chess_Suc_Deal(CDC *pDC)
	{
		int who;//�洢�˲������ķ��µģ�1��ʾ�ڣ�2��ʾ�ף�
		who = (step % 2) + 1;//�õ��Է���

		Check_Qi(who);//���Է�����
		Remove_Cell(who, pDC); //�����Է���������
		Init_Chess();//�����ӳ�ʼ����ȫ������

		who = ((step + 1) % 2) + 1;//�õ��ҷ���
		Check_Qi(who);//����ҷ�����

		if (Remove_Cell(who, pDC) == 1) 
			return reChess(pDC); //����������ҷ��������ӣ���Ϊ���ŵ㣬��һ����
		
		if(dajie() == 1) 
			return reChess(pDC);//��ٴ�����һ����
		
		Init_Chess();//�����ӳ�ʼ����ȫ������

		return 0;
	}

};

