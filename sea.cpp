
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

const int NotUsed = system("color 30"); //�����

const int N = 10 + 2; // +2 ��� �������
const int NUM_SHIPS = 10;

int Ships_id = 1;
int Ships[10] = { 0 };

void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

// ������� �������� ���������� ������� � �������� �����.
// ��� ������� ���������� true ���� ������� ���������� �� ����� � false � �������� ������. 
bool shipInMap(int x, int y, int dir, int sizeShip)
{
	bool in_map = 1;
	for (int i = 0; i < sizeShip; i++)
	{

		if (x < 1 || y < 1 || x >= N - 1 || y >= N - 1)
		{
			in_map = 0;
			break;
		}

		switch (dir)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	return in_map;
}

// ������� ��������� �������� �� ���������� ������� �� ����� �� �������� �����������, � �������� �����������, ��������� �������. 
// ���������� ������ ���� ���������� �������� � ����, ���� �� ��������. 
// ������� �� ���������� ������� � ������, ������ ��������� ����������� ���������. 
bool shipSettingIsPossible(int map[N][N], int x, int y, int dir, int sizeShip)
{
	bool setting_is_possible = 1;

	for (int i = 0; i < sizeShip; i++)
	{

		if (x <= 0 || y <= 0 || x >= N - 1 || y >= N - 1)
		{
			setting_is_possible = 0;
			break;
		}

		if (map[x][y] >= 0 ||
			map[x][y + 1] >= 0 ||
			map[x][y - 1] >= 0 ||
			map[x + 1][y] >= 0 ||
			map[x + 1][y + 1] >= 0 ||
			map[x + 1][y - 1] >= 0 ||
			map[x - 1][y] >= 0 ||
			map[x - 1][y + 1] >= 0 ||
			map[x - 1][y - 1] >= 0)
		{
			setting_is_possible = 0;
			break;
		}

		switch (dir)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	return setting_is_possible;
}


//������� setShipInMap ������������� ������� �� �����. 
//����� ���������� ������� � ������� ������� shipSettingIsPossible ����������� �������� �� ��������� ������� �� �������� �����������, 
//� �������� �����������. ������� ��������� � �������� ���������� �����, ����������, �����������, ������ � ����� �������. 
//����� ������� ����������� � ������ ������ �������, ���������� ��������. 
//� ������ ���������� ��������� ������� ������� ���������� ������, � �������� ������ ����.
bool setShipInMap(int map[N][N], int x, int y, int dir, int sizeShip, int id)
{
	if (shipSettingIsPossible(map, x, y, dir, sizeShip))
	{
		for (int i = 0; i < sizeShip; i++)
		{
			map[x][y] = id;

			switch (dir)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		return true;
	}
	return false;
}

//������� setRandShip ���������� ������� setShipInMap � ������������� �� ��������� ����������� 
//� ���������� ����������� ������� �������� ����� � ������� �������. 
void setRandShip(int map[N][N], int sizeShip, int ship_id)
{
	int x, y;
	int dir = 0;

	int count_tact = 0;

	while (true)
	{

		count_tact++;

		if (count_tact > 1000)
		{
			break;
		}

		// ��������� �������
		x = rand() % (N - 2) + 1;
		y = rand() % (N - 2) + 1;

		// ��������� �����������
		dir = rand() % 4;

		if (setShipInMap(map, x, y, dir, sizeShip, ship_id))
		{
			break;
		}
	}
}

//������� setRandShips(map, ships) � ��������� ����� � � ��������� ����������� (�������������� ��� ������������) ������������� ������� 
//��������� ������� � � �������� �������. ����� ������� ������������� � ��������������� ������� ������ �������. 
void setRandShips(int map[N][N], int ships[NUM_SHIPS])
{
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		setRandShip(map, ships[i], i);
	}
}

// ������� mapShow ������ ���� �� �����. 
// ������� ��������� ��������� ������ � ���������� x, y �� ������� ������������� ����� �������. 
// ������� ���� ���������� �������� #, ������ �� ������� ����� ������ ��������. 
void mapShow(int map[N][N], int x, int y, int mask[N][N], bool useMask)
{
	for (int i = 0; i < N; i++)
	{
		gotoxy(x, y);

		for (int j = 0; j < N; j++)
		{
			if (mask[j][i] == 1 || useMask == 0)
			{
				if (map[j][i] == -3)// �������� ������
				{
					cout << 'X';
				}
				else if (map[j][i] == -2)// ������
				{
					cout << '-';
				}
				else if (map[j][i] == -1)// ������ ������
				{
					cout << ' ';
				}
				else if (map[j][i] == -100)// ������� ����
				{
					cout << '#';
				}
				else // �������
				{
					cout << '@';
				}
			}
			else
			{
				if (map[j][i] == -100)// ������� �������� �� �������� �� �����
				{
					cout << '#';
				}
				else
				{
					cout << ' ';
				}
			}
		}
		y++;
	}
}

void mapShowInHandMode(int map[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[j][i] == -3)
			{
				cout << 'X';
			}
			else if (map[j][i] == -2)
			{
				cout << '.';
			}
			else if (map[j][i] == -1)
			{
				cout << ' ';
			}
			else if (map[j][i] == -100)
			{
				cout << '#';
			}
			else
			{
				cout << '@';
			}

		}
		cout << endl;
	}
}

//������� shipShowInHandMode, ������� ���������� ������� �� �������� �����������, ���������� � ����� �� ������. 
//������� ������ �� ������������, ������ ������������ �� ���� �������� ����.
void shipShowInHandMode(int x, int y, int dir, int sizeShip)
{
	for (int i = 0; i < sizeShip; i++)
	{
		gotoxy(x, y);
		cout << '@';

		switch (dir)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
};

//������ ��������� �������. ������� void handSetShips(int map[N][N], int ships[NUM_SHIPS]) ��������� ���������� ��� ������� �� ������� �����, 
//� ����� ����������� ������� �� �������� ������� � ������������ �� ������� ������� ������. 
//����� ���� ��� ������� ������� ����� ���������� ����� ����������� ����������� ���������� �� �� � �������� �����. 
//���� �� ���������� ����������������� ���������� ����������, �� ������� �����������. 
//��� ������� enter ������� ���������������, �.�. ���������� � ������ ��� �������������� ������� ������������ � ����. 
//��� ��������� ������� ������������ ������� setShipInMap.
void handSetShips(int map[N][N], int ships[NUM_SHIPS])
{
	system("cls");

	int ch;

	int x = 1, y = 1;
	int dir = 0;

	//������ ����������� ��������
	int i = 0;
	while (i < NUM_SHIPS)
	{
		mapShowInHandMode(map);
		shipShowInHandMode(x, y, dir, ships[i]);

		int temp_x = x;
		int temp_y = y;
		int temp_dir = dir;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}

		// �������� ���������� ��� �����������
		switch (ch)
		{
		case 77://������
			x++;
			break;
		case 80://����
			y++;
			break;
		case 75://�����
			x--;
			break;
		case 72://�����
			y--;
			break;
		case 114:// r �������
			dir = !dir;
			break;
		case 13:// ��������� �������
			if (setShipInMap(map, x, y, dir, ships[i], i))
			{
				i++;
			}
			break;
		}

		// �������� ��������� ������� � ���� ����� ��������� ���������
		// ���� �� ����� �� �������� ���������� � �����������
		if (!shipInMap(x, y, dir, ships[i]))
		{
			x = temp_x;
			y = temp_y;
			dir = temp_dir;
		}

		system("cls");
	}
}

//��������. 
//������� shot �������� �� �������� ���������� �� ������� ����. 
//� ������ ��������� ������� ��������� ���������� ������ � ������� �� �������� ������. 
//����� ������� ��������� � ships1 � ships2, ������ � ��� � ����������� �����. 
//����� ����� ������ ����� ���� �� ������� ��������. ������� ���������� 1 ���� ������, 2 � �������� ������ ��� ����, 3 �����, 4 ����. 
//����� ��� ������� ������ ����� ������ �� ���� ��������� -2 �� ������� ��� ��������
int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS], int mask[N][N])
{
	int result = 0;

	// ������� �� ������ ������, ������ ������
	if (map[x][y] == -1)
	{
		map[x][y] = -2; //������ ������ �� ������� ��� ��������
		result = 1;
	}
	// ������� �� ������ �� ������� ��� ��������
	// ��� ������� ����� ��� ���������� ������ ���� ����� �� �� ������� �� ������� ��������
	else if (map[x][y] == -2 || map[x][y] == -3)
	{
		result = 2;// �������� ������
	}
	// ��������� �� �������
	else if (map[x][y] >= 0)
	{
		ships[map[x][y]]--;

		if (ships[map[x][y]] > 0)
		{
			result = 3; //����� 
		}
		else
		{
			result = 4; //����
		}

		map[x][y] = -3; //�������� ������
	}

	mask[x][y] = 1;

	return result;
}

void selectTarget(int& x, int& y)
{
	//system("cls");

	int dir = 0;
	int sizeShip = 4;
	int ch;

	gotoxy(x, y);

	//������ ����������� ��������
	int i = 1;
	while (true)
	{
		//mapShow(map);
		//shipShowInHandMode(x, y, dir, ships[i]);

		int tx = x;
		int ty = y;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}

		// �������� ���������� ��� �����������
		switch (ch)
		{
		case 77://������
			x++;
			break;
		case 80://����
			y++;
			break;
		case 75://�����
			x--;
			break;
		case 72://�����
			y--;
			break;
		case 13:// ��������� �������
			return;
			break;
		}

		if (!shipInMap(x, y, 1, 1))
		{
			x = tx;
			y = ty;
		}
		gotoxy(x, y);
	}
}

// ������������� �����
// ������� ��������� ��������� 100, � ��� ��������� ��������, ������������ ������ ������,  ��������� -1.
void mapInit(int map[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
			{
				map[j][i] = -100;
			}
			else
			{
				map[j][i] = -1;
			}
		}
	}
}

//������� playerIsWin(ships) �������� � �������� �������� ������ �������� ���������� � ���������� 
//true ���� ��� ������� ���������, false � �������� ������.
bool playerIsWin(int ships[NUM_SHIPS])
{
	int s = 0;
	bool win = 0;

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		s = s + ships[i];
	}

	if (s <= 0)
	{
		win = 1;
	}

	return win;
}

//������� humanTurn �������������� �������� �������� �� ������� �������. 
//������� ���������� 1 � ������ ����������� ����, 2 � ������ ������ ������ ��������. 
//����� ������� ��������� ������� ��������� ��������� �� ��� �������. 
//��� �������� ������������ ������� playerIsWin(ships) 
int humanTurn(int map[N][N], int ships[NUM_SHIPS], int mask[N][N])
{
	bool win = false;
	int resultShot = 0;

	int x = 1, y = 1;

	gotoxy(0, 12);
	cout << "��� ���. �������� ����. ������� �������. ������� Enter.";

	while (true)
	{
		selectTarget(x, y);

		resultShot = shot(map, x, y, ships, mask);

		gotoxy(0, 12);
		cout << "                                                                 ";
		gotoxy(0, 12);

		if (resultShot == 1 || resultShot == 2)
		{
			cout << "������" << endl;
			break;
		}
		else if (resultShot == 3)
		{
			cout << "�����" << endl;
		}
		else if (resultShot == 4)
		{
			cout << "����";
			if (playerIsWin(ships))
			{
				return 2; // ������
			}
		}

		Sleep(1000);
		mapShow(map, 0, 0, mask, 1);

		// !!! ������� ����� ����������������
		//break;

	};

	return 1; // ������
}

//�������� ��������� ������� ���� � ����������� �� �����������.
//���������� ���� ���� ������ ���������� ������ �� ����
//���������� ������ ���� ������ ���������� ������ ����
bool changeCoord(int map[N][N], int dir, int& x, int& y)
{
	bool changeDir = 0;

	int tx = x;
	int ty = y;

	switch (dir)
	{
	case 0:
		x++;
		break;
	case 1:
		y++;
		break;
	case 2:
		x--;
		break;
	case 3:
		y--;
		break;
	}

	if (map[x][y] == -100)
	{
		x = tx;
		y = ty;
		changeDir = 1;
	}

	return changeDir;
}

// ������������� ������� ����������� �������� ��� ����
void initDirsVec(vector <int>& dirs)
{
	dirs.clear();
	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);
}

// ��������� �� ������� ���������� ����������� �������� ��� ����
int getDirFromVec(vector <int>& dirs)
{
	int dir = 0;
	if (!dirs.empty())
	{
		dir = dirs[dirs.size() - 1];
		dirs.pop_back();
	}
	return dir;
}

//������� botTurn  ��������� ��� �������� ����������. 
//������� ����� ��� ������ ��������: ��������� � ����� ������ ����� ������� ��������� � �������.
//����� ������� ��������� ������� ������ ��������� ��������� �� ��� �������. 
//��� ����� ����������� ������� ������� playerIsWin(ships) ������� �������� � �������� �������� ������ �������� ���������� 
//� ���������� true ���� ��� ������� ���������, false � �������� ������.
int botTurn(int map[N][N], int ships[NUM_SHIPS], int mask[N][N])
{
	// ���������� ������ �� ������� ������ ������
	static int firstHitX = 0;
	static int firstHitY = 0;

	// ����� ������ ����
	static int mode = 0;

	// ������� ���������� ��� ��������
	static int x = 0;
	static int y = 0;

	// ������� ����������� ��������
	static int dir = 0;

	//������ ��������� �����������
	static vector <int> dirs;

	int resultShot = 0;
	bool win = 0;

	do
	{
		//��������� ����� ��������
		if (mode == 0)
		{
			do // �������� �� ��� ��� ���� ��������� �������� ������
			{
				x = rand() % (N - 2) + 1;
				y = rand() % (N - 2) + 1;

				resultShot = shot(map, x, y, ships, mask);

			} while (resultShot == 2);

			if (resultShot == 1)
			{
				cout << "������ ";
			}
			else if (resultShot == 3)// �����
			{
				mode = 1; // ������� � ����� ������ ���������� �����

				initDirsVec(dirs);

				firstHitX = x;
				firstHitY = y;

				dir = getDirFromVec(dirs);

				cout << "����� ";
			}
			else if (resultShot == 4)
			{
				cout << "���� ";
				if (playerIsWin(ships))
				{
					return 2;
				}
			}
		}
		//����� �������� ����� ������� ��������� � �������
		else if (mode == 1)
		{

			bool changeDir = changeCoord(map, dir, x, y);

			//�������� ����������� ������ �����
			if (changeDir)
			{
				dir = getDirFromVec(dirs);

				// ��������������� ���������� ������� ��������� �� ������� � �� ��� ���� � ����� �����������
				x = firstHitX;
				y = firstHitY;

				// ����� ����������� ���������� ��� ������������ � ��������
				continue;

			}

			// ��������
			resultShot = shot(map, x, y, ships, mask);

			if (resultShot == 1) // ������
			{
				dir = getDirFromVec(dirs);

				x = firstHitX;
				y = firstHitY;

				cout << "������ ";

				return 1;
			}
			else if (resultShot == 3) // �����
			{
				cout << "����� ";
			}
			else if (resultShot == 4) // ����
			{
				mode = 0;

				initDirsVec(dirs);

				cout << "���� ";
				if (playerIsWin(ships))
				{
					return 2;
				}
			}
		}
		Sleep(1000);
	} 	while (resultShot != 1);

	return 1;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	while (true)
	{
		//������� ���� �������� 10 �� 10 �������������� ��������� �������� 12 �� 12, 
		//��� ��� ������� ������� � ������ ����� ��������� �������� ������������ �������.
		int map1[N][N] = { 0 }; // ������� ���� ��������
		int map2[N][N] = { 0 }; // ������� ���� ����������

		mapInit(map1);
		mapInit(map2);

		//������� �������� ���������� � ���������� �������� � ���������� ����� ������� �������. 
		//������ �������� ������������ ���������� NUM_SHIPS. 
		//������ ������� ���������� ����� �������, � ��������  �������� ��� ������. 
		//������� ������� � ������� 0 � 4-� ��������, � � ������� 1 � 3-�������� � �.�.
		int ships1[NUM_SHIPS] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		int ships2[NUM_SHIPS] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

		int mask1[N][N] = { 0 };
		int mask2[N][N] = { 0 };


		cout << " �� � ���� ����������� �����������! ������� �������������� �������� ENTER...." << endl;
		cout<<"    ������� �������� ��� ����������� ������� ���������� ��� ������� -r-..." << endl;
		cout << "=======================================================================================" << "\n\n";
		cout << "_________________________________����� !!!!!!!___________________________________" << "\n\n";
		cout << "    ���������� ������� �������������-������� 1 ... �������-������� 0...." << endl;
		


		int randOrHandMode = 2;

		cin >> randOrHandMode;

		system("cls");

		if (randOrHandMode == 1)
		{
			setRandShips(map1, ships1);
		}
		else
		{
			handSetShips(map1, ships1);
		}

		setRandShips(map2, ships2);

		int x = 0, y = 0;

		//********************************

		int winHuman = 1;
		int winBot = 1;

		bool turn = rand() % 2;

		// ���� ������ ����
		while (true)
		{
			mapShow(map1, 13, 0, mask1, 0);
			mapShow(map2, 0, 0, mask2, 1);

			if (turn == 1)
			{
				winHuman = humanTurn(map2, ships2, mask2);
			}
			else
			{
				cout << endl << "��� ���������� ";
				Sleep(1000);

				winBot = botTurn(map1, ships1, mask1);
			}

			if (winHuman == 2)
			{
				cout << "�� ��������!!!" << endl;
				system("pause");
				break;
			}
			else if (winBot == 2)
			{
				cout << "�� ���������." << endl;
				system("pause");
				break;
			}

			Sleep(1000);
			system("cls");

			turn = !turn;
		}

		
		system("cls");
	}

	system("pause");
	return 0;
}