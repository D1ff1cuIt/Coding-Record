#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>
using namespace std;

#define MAX 20

int map[MAX];
int rear = -1;
int front = -1;
int score = 0 , gtime = 0, num = 0;
char get;
int history;
int letterrnd;
fstream  fm;  

void begin();
void mode1(PVOID m);
void mode2(PVOID m);
void mode3(PVOID m);
void getKey(PVOID g);

class Pos
{
	public:
		int x;
		char ch;
		bool temp;
		
		Pos()
		{
			x = 19;
			temp = false;
		}	
};

Pos enter[MAX]; 

class queue
{
	private:
		bool tag;
		bool check;
	public:
		queue();
		void enqueue(char ch);
		void dequeue();
		void display();
		void move();
		void end();
};

queue::queue()
{
	tag = false;
	check = false;
	map[0] = 1;
}

void queue::move() /* ��r�����e�� */ 
{
	for(int i=0;i<MAX;i++)
	{
		if(enter[i].x != 0 && enter[i].temp)
		{
			map[enter[i].x] = 0; /* =0 �ɷ|���ͪŮ� */ 
			enter[i].x--;
		}
		else if(enter[i].x == 0 && enter[i].temp)
		{
			enter[i].x = -1;  /* �קK�d�bmap[0]�ɥi�H���вֿn���� */ 
			map[0] = 1;  /* =1 �ɷ|���� "_" */ 
			dequeue();
		}
	}
}

void queue::enqueue(char ch) /* ������C�q�᭱���J��� */ 
{
	if(rear == front && tag)
		cout << "�}�C���S" << endl;
	else
	{
		rear = (rear+1) % MAX; /* �w���W�L�}�C�ؤo�A�Nrear�k�s */ 
		enter[rear].ch = ch;
		enter[rear].x = 19;   /* �_�l��m */ 
		enter[rear].temp = true; /* �r���ͦ����T=true */ 
		if(front == rear)
		{
			tag = 1;
		}
		else
		{
			tag = 0;
		}
	} 
}

void queue::dequeue() /* ������C�q�e��������� */ 
{
	if(front == rear && tag == false)
		cout << "�}�C�Ū�" << endl;
	else
	{
		front = (front+1) % MAX; /* �w���W�L�}�C�ؤo�A�Nfront�k�s */ 
		enter[front].temp = false;
		if(front == rear)
		{
			tag = 0;
		}
		else
		{
			tag = 1;
		}
	}
		
}

void queue::display() 
{
	system("cls");
	
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			if(enter[j].x == i && enter[j].temp) /* ��s�r����m */ 
			{
				cout << enter[j].ch;
				check = true;
				break;
			}
		}
		
		if(check) /* ����U�ԭz���а��� */ 
		{
			check = false;
		}
			
		else if(map[i] == 0)
		{
			cout << setw(2) << " ";
		}
		
		else if(map[i] == 1)
		{
			cout << "_";
		}
		
	}
	
	cout << "\n\n\n\n���v�̰��G" << history << "\n����: " << score << endl;
	cout << "�Ѿl�ɶ�: " << 60-gtime << "s" << endl;
	cout << "\n\n---�o����---" << endl;
	cout << "�p�g�r�� +1��" << endl;
	cout << "�j�g�r�� +2~4��"<< endl;
	cout << "�S��Ÿ� +3~6��" << endl; 
	cout << "------------" << endl;
	
	if(gtime == 60)
	{
		end();
	}
		
}

void queue::end() /* �C������ */ 
{
	system("cls");
	if(score >= history)
	{
		if(num == 1)
		{
			ofstream fm("history_easy.txt"); /* Ū�����v�����ɮ�(��X) */ 
			fm << score;
			cout << "���ߧA�}�����o�I\n";
			fm.close();
		}
		else if(num == 2)
		{
			ofstream fm("history_normal.txt"); /* Ū�����v�����ɮ�(��X) */ 
			fm << score;
			cout << "���ߧA�}�����o�I\n";
			fm.close();
		}
		else if(num == 3)
		{
			ofstream fm("history_hard.txt"); /* Ū�����v�����ɮ�(��X) */ 
			fm << score;
			cout << "���ߧA�}�����o�I\n";
			fm.close();
		}
	}
	cout << "�o��: " << score << endl;
	
	exit(1); 
}

int main()
{

	
	char choose;
	int speedchoose = 0;
	int speed;
	cout << "���׿��" << endl;
	cout << "(�u���p�g)����:����������(�п�J1)" << endl;
	cout << "(���j�p�g)����:����������(�п�J2)" << endl;
	cout << "(�j�p�g�H�ίS��Ÿ�)����:����������(�п�J3)" << endl;
	while(num != 1 && num != 2 && num != 3)
	{
		choose = getch();
		switch(choose)
		{
			case '1':
				num = 1;
				break;
			case '2':
				num = 2;
				break;
			case '3':
				num = 3;
				break;
			default:
				cout << "�Э��s���" << endl;
				break; 
		}
	}
	
	if(num == 1)
	{
		ifstream fm("history_easy.txt"); /* Ū�����v�����ɮ�(�g�J) */ 
		fm >> history;
		fm.close();
	}
	else if(num == 2)
	{
		ifstream fm("history_normal.txt"); /* Ū�����v�����ɮ�(�g�J) */ 
		fm >> history;
		fm.close();
	}
	else if(num == 3)
	{
		ifstream fm("history_hard.txt"); /* Ū�����v�����ɮ�(�g�J) */ 
		fm >> history;
		fm.close();
	}
	
	cout << "�t�׿��(100 200 500 1000(ms))" << endl;
	while(speedchoose != 100 && speedchoose != 200 && speedchoose != 500 && speedchoose != 1000)
	{
		cin >> speedchoose;
		switch(speedchoose)
		{
			case 100:
				speed = 100;
				break;
			case 200:
				speed = 200;
				break;
			case 500:
				speed = 500;
				break;
			case 1000:
				speed = 1000;
				break;
			default:
				cout << "�Э��s���" << endl;
				break; 
		}
	}
	
	system("cls");
	
	int timecount = 0;
	queue game;
	begin();
	while(1)
	{
		game.display();
		game.move();
		timecount++;
		if(timecount == 1000/speed) /* �C����ƭp�� */ 
		{
			timecount = 0;
			gtime++;
		}
		Sleep(speed);
	}
	
	system("PAUSE");
	return 0;
}

void begin()  /* �C���}�l */  /* �h������ */ 
{
	if(num == 1)
	{
		_beginthread(mode1,0,0);
	}

	else if(num == 2)
	{
		_beginthread(mode2,0,0);
	}

	else if(num == 3)
	{
		_beginthread(mode3,0,0);
	}

	
	_beginthread(getKey,0,0); /* Ū����J�r�� */ 
}

void mode1(PVOID m) /* ����1 */ 
{
	queue game;
	int Smallwordrnd,speedrnd;
	char spawn;
	srand(time(NULL));
	
	while(1)
	{
		Smallwordrnd = (rand()%26)+97; /* �p�g�r���ü� */ 
		speedrnd = (rand()%1001)+500; /* �t�׶ü� 0.5s~1.5s */ 
		spawn = char(Smallwordrnd);
		game.enqueue(spawn);
		Sleep(speedrnd);
	}
}

void mode2(PVOID m) /* ����2 */ 
{
	queue game;
	int Largewordrnd,Smallewordrnd,speedrnd;
	char spawn;
	srand(time(NULL));
	
	while(1)
	{
		Largewordrnd = (rand()%26) + 65;  /* �j�g�r���ü� */ 
	   	Smallewordrnd = (rand()%26) + 97; /* �p�g�r���ü� */ 
		speedrnd = (rand()%1001) + 500; /* �t�׶ü� 0.5s~1.5s */ 
		letterrnd = (rand()%2); /* �j�p�g�r�鲣�Ͷü� */
	
		if(letterrnd == 0) /* �P�_���ͤj�p�g�r�� */ 
		{
			spawn = char(Largewordrnd);
		}
		else
		{
			spawn = char(Smallewordrnd);
		}
			
		game.enqueue(spawn);
		Sleep(speedrnd);
	}
}

void mode3(PVOID m) /* ����3 */ 
{
	queue game;
	int Largewordrnd,Smallewordrnd,speedrnd,symbolrnd;
	char spawn;
	srand(time(NULL));
	
	while(1)
	{
		Largewordrnd = (rand()%26) + 65;  /* �j�g�r���ü� */ 
	   	Smallewordrnd = (rand()%26) + 97; /* �p�g�r���ü� */ 
	   	symbolrnd = (rand()%6) + 33; /* �Ÿ����Ͷü� */ 
		speedrnd = (rand()%1001) + 500; /* �t�׶ü� 0.5s~1.5s */ 
		letterrnd = (rand()%3); /* �j�p�g�r�鲣�Ͷü� */
	
		if(letterrnd == 2) /* �P�_���ͤj�p�g�r�� */ 
		{
			spawn = char(Largewordrnd);
		}
		else if(letterrnd == 1)
		{
			spawn = char(Smallewordrnd);
		}
		else if(letterrnd == 0)
		{
			spawn = char(symbolrnd);
		}
			
		game.enqueue(spawn);
		Sleep(speedrnd);
	}
}

void getKey(PVOID g) /* ��J�r������ & ���ƭp�� */ 
{
	int scorernd;
	while(1)
	{
		get = getch();
		for(int i=0;i<MAX;i++)
		{
			if(enter[i].x == 0 && enter[i].ch == get)
			{
				if(num == 1)
				{
					score = score + 1; /* �p�g�r�� + 1�� */ 
				}
				else if(num == 2)
				{
					if(letterrnd == 0)
					{
						scorernd = (rand()%2) + 2; /* �j�g�r�� + 2~4�� */ 
						score = score + scorernd;
					}
					else
					{
						score = score + 1; /* �p�g�r�� + 1�� */ 
					}
				}
				else if (num == 3)
				{
					if(letterrnd == 2)
					{
						scorernd = (rand()%3) + 2;  /* �j�g�r�� + 2~4�� */ 
						score = score + scorernd;
					}
					else if (letterrnd == 0)
					{
						scorernd = (rand()%4) + 3;  /* �Ÿ� + 3~6�� */ 
						score = score + scorernd;
					}
					else
					{
						score = score + 1; /* �p�g�r�� + 1�� */ 
					}
				}
			} 
		}	
	}
}



