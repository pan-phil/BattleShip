
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

const int NotUsed = system("color 30"); //цвета

const int N = 10 + 2; // +2 под границы
const int NUM_SHIPS = 10;

int Ships_id = 1;
int Ships[10] = { 0 };

void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

// функция проверки нахождения корабля в пределах карты.
// Эта функция возвращает true если корабль помещается на карте и false в обратном случае. 
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

// Функция проверяет возможно ли установить корабль на карту по заданным координатам, в заданном направлении, заданного размера. 
// Возвращает истину если постановка возможно и ложь, если не возможна. 
// Функция не записывает корабль в массив, только проверять возможность установки. 
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


//Функцию setShipInMap устанавливает корабль на карту. 
//Перед установкой корабля с помощью функции shipSettingIsPossible проверяется возможно ли установка корабля по заданным координатам, 
//в заданном направлении. Функция принимает в качестве параметров карту, координаты, направление, размер и номер корабля. 
//Номер корабля записвается в каждую ячейку массива, занимаемую кораблем. 
//В случае успешности установки корабля функция возвращает истину, в обратном случае ложь.
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

//Функция setRandShip использует функцию setShipInMap и устанавливает по случайным координатам 
//и случайному направлению корабль заданной длины с заданым номером. 
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

		// первичная позиция
		x = rand() % (N - 2) + 1;
		y = rand() % (N - 2) + 1;

		// генерация направления
		dir = rand() % 4;

		if (setShipInMap(map, x, y, dir, sizeShip, ship_id))
		{
			break;
		}
	}
}

//Функция setRandShips(map, ships) в случайном месте и в случайном направлении (горизонтальном или вертикальном) устанавливает корабль 
//заданного размера и с заданным номером. Номер корабля проставляется в соответствующие номером ячейки массива. 
void setRandShips(int map[N][N], int ships[NUM_SHIPS])
{
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		setRandShip(map, ships[i], i);
	}
}

// Функцию mapShow игрове поле на экран. 
// Функция принимает двумерный массив и координаты x, y по которым производиться вывод массива. 
// Граница поля обозначена символом #, пустая не занятая ничем клетка пробелом. 
void mapShow(int map[N][N], int x, int y, int mask[N][N], bool useMask)
{
	for (int i = 0; i < N; i++)
	{
		gotoxy(x, y);

		for (int j = 0; j < N; j++)
		{
			if (mask[j][i] == 1 || useMask == 0)
			{
				if (map[j][i] == -3)// подбитая палуба
				{
					cout << 'X';
				}
				else if (map[j][i] == -2)// промах
				{
					cout << '-';
				}
				else if (map[j][i] == -1)// пустая клетка
				{
					cout << ' ';
				}
				else if (map[j][i] == -100)// граница поля
				{
					cout << '#';
				}
				else // корабль
				{
					cout << '@';
				}
			}
			else
			{
				if (map[j][i] == -100)// граница рисуется не зависимо от маски
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

//Функцию shipShowInHandMode, которая отображает корабль по заданным координатам, напралению и длине на экране. 
//Корабль никуда не записывается, только отображается на фоне игрового поля.
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

//Ручная установка корабля. Функцию void handSetShips(int map[N][N], int ships[NUM_SHIPS]) позволяет установить все коробли на игровое полое, 
//а также передвигать корабль по клавишам стрелок и поворачивать по нажатии клавишы Пробел. 
//После того как корабль получил новые координаты перед прорисовкой проверяется помещается ли он в пределах карты. 
//Если не помещается восстанавливаются предыдущие координаты, до момента перемещения. 
//При нажатии enter корабль устанавливается, т.е. записается в массив под соответсвующим номером начинающимся с нуля. 
//При установке корабля используется функцию setShipInMap.
void handSetShips(int map[N][N], int ships[NUM_SHIPS])
{
	system("cls");

	int ch;

	int x = 1, y = 1;
	int dir = 0;

	//ручная расстановка кораблей
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

		// изменить координаты или направление
		switch (ch)
		{
		case 77://вправо
			x++;
			break;
		case 80://вниз
			y++;
			break;
		case 75://влево
			x--;
			break;
		case 72://вверх
			y--;
			break;
		case 114:// r поворот
			dir = !dir;
			break;
		case 13:// установка корабля
			if (setShipInMap(map, x, y, dir, ships[i], i))
			{
				i++;
			}
			break;
		}

		// проверка попадания корабля в поле после изменения координат
		// если не попал то откатить координаты и направление
		if (!shipInMap(x, y, dir, ships[i]))
		{
			x = temp_x;
			y = temp_y;
			dir = temp_dir;
		}

		system("cls");
	}
}

//Стрельба. 
//Функцию shot стреляет по заданным координатм на игровом поле. 
//В случае попадания функция уменьшает количество жизней у корабля по которому попали. 
//Жизни корабля храняться в ships1 и ships2, именно в них и уменьшаются жизни. 
//Когда жизни станут равны нулю то корабль потоплен. Функция возвращает 1 если промах, 2 – условный промах для бота, 3 ранен, 4 убит. 
//Также эта функция должна метит клетки на поле значением -2 по которым уже стреляли
int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS], int mask[N][N])
{
	int result = 0;

	// выстрел по пустой клетке, чистый промах
	if (map[x][y] == -1)
	{
		map[x][y] = -2; //пустая клетка по которой уже стреляли
		result = 1;
	}
	// выстрел по клетке по которой уже стреляли
	// это условие нужно для правильной работы бота чтобы он не стрелял по клеткам повторно
	else if (map[x][y] == -2 || map[x][y] == -3)
	{
		result = 2;// условный промах
	}
	// попадание по кораблю
	else if (map[x][y] >= 0)
	{
		ships[map[x][y]]--;

		if (ships[map[x][y]] > 0)
		{
			result = 3; //ранен 
		}
		else
		{
			result = 4; //убит
		}

		map[x][y] = -3; //подбитая палуба
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

	//ручная расстановка кораблей
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

		// изменить координаты или направление
		switch (ch)
		{
		case 77://вправо
			x++;
			break;
		case 80://вниз
			y++;
			break;
		case 75://влево
			x--;
			break;
		case 72://вверх
			y--;
			break;
		case 13:// установка корабля
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

// Инициализация карты
// Граница заполнена значением 100, а все остальные элементы, обозначающие пустые клетки,  значением -1.
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

//Функция playerIsWin(ships) получает в качетсве праметра массив кораблей противника и возвращает 
//true если все корабли потоплены, false в обратном случае.
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

//Функция humanTurn осуществляющую стрельбу человека до первого промаха. 
//Функция возвращает 1 в случае продолжения игры, 2 в случае полной победы человека. 
//После каждого попадания функция проверяет потоплены ли все корабли. 
//Эту проверку осуществляет функцию playerIsWin(ships) 
int humanTurn(int map[N][N], int ships[NUM_SHIPS], int mask[N][N])
{
	bool win = false;
	int resultShot = 0;

	int x = 1, y = 1;

	gotoxy(0, 12);
	cout << "Ваш ход. Выберите цель. Клавиши стрелок. Выстрел Enter.";

	while (true)
	{
		selectTarget(x, y);

		resultShot = shot(map, x, y, ships, mask);

		gotoxy(0, 12);
		cout << "                                                                 ";
		gotoxy(0, 12);

		if (resultShot == 1 || resultShot == 2)
		{
			cout << "Промах" << endl;
			break;
		}
		else if (resultShot == 3)
		{
			cout << "Ранен" << endl;
		}
		else if (resultShot == 4)
		{
			cout << "Убит";
			if (playerIsWin(ships))
			{
				return 2; // победа
			}
		}

		Sleep(1000);
		mapShow(map, 0, 0, mask, 1);

		// !!! отладка потом закомментировать
		//break;

	};

	return 1; // промах
}

//изменеие координат прицела бота в зависимости от направления.
//возвращает ложь если менять напрвление поиска не надо
//возвращает истину если менять напрвление поиска надо
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

// инициализация вектора направлений стрельбы для бота
void initDirsVec(vector <int>& dirs)
{
	dirs.clear();
	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);
}

// получение из вектора очередного направлений стрельбы для бота
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

//Функция botTurn  реализует ход стрельбу компьютера. 
//Функция имеет два режима стрельбы: случайный и режим поиска после первого попадания в корабль.
//После каждого попадания функция должна проверять потоплены ли все корабли. 
//Для этого используйте готовую функцию playerIsWin(ships) которая получает в качетсве праметра массив кораблей противника 
//и возвращает true если все корабли потоплены, false в обратном случае.
int botTurn(int map[N][N], int ships[NUM_SHIPS], int mask[N][N])
{
	// координаты палубы по которой попали первой
	static int firstHitX = 0;
	static int firstHitY = 0;

	// режим работы бота
	static int mode = 0;

	// текущие координаты для стрельбы
	static int x = 0;
	static int y = 0;

	// текущее направление стрельбы
	static int dir = 0;

	//вектор возможных направлений
	static vector <int> dirs;

	int resultShot = 0;
	bool win = 0;

	do
	{
		//случайный режим стрельбы
		if (mode == 0)
		{
			do // стрелять до тех пор пока результат условный промах
			{
				x = rand() % (N - 2) + 1;
				y = rand() % (N - 2) + 1;

				resultShot = shot(map, x, y, ships, mask);

			} while (resultShot == 2);

			if (resultShot == 1)
			{
				cout << "Промах ";
			}
			else if (resultShot == 3)// ранен
			{
				mode = 1; // переход в режим поиска отстальных палуб

				initDirsVec(dirs);

				firstHitX = x;
				firstHitY = y;

				dir = getDirFromVec(dirs);

				cout << "Ранен ";
			}
			else if (resultShot == 4)
			{
				cout << "Убит ";
				if (playerIsWin(ships))
				{
					return 2;
				}
			}
		}
		//режим стрельбы после первого попадания в корабль
		else if (mode == 1)
		{

			bool changeDir = changeCoord(map, dir, x, y);

			//изменить направление поиска палуб
			if (changeDir)
			{
				dir = getDirFromVec(dirs);

				// восстанавливаем координаты первого попадания по кораблю и от них ищем в новом направлении
				x = firstHitX;
				y = firstHitY;

				// смена направления происходит при столкновении с границей
				continue;

			}

			// стрельба
			resultShot = shot(map, x, y, ships, mask);

			if (resultShot == 1) // промах
			{
				dir = getDirFromVec(dirs);

				x = firstHitX;
				y = firstHitY;

				cout << "Промах ";

				return 1;
			}
			else if (resultShot == 3) // ранен
			{
				cout << "Ранен ";
			}
			else if (resultShot == 4) // убит
			{
				mode = 0;

				initDirsVec(dirs);

				cout << "Убит ";
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
		//Игровое поле размером 10 на 10 представляется двумерным массивом 12 на 12, 
		//так как крайние столбцы и строки будут содержать значения обозначающие границы.
		int map1[N][N] = { 0 }; // игровое поле человека
		int map2[N][N] = { 0 }; // игровое поле компьютера

		mapInit(map1);
		mapInit(map2);

		//Массивы содержат информацию о количестве кораблей и количестве палуб каждого корабля. 
		//Размер массивов определяется константой NUM_SHIPS. 
		//Индекс массива определяет номер корабля, а значение  элемента его размер. 
		//Поэтому корабль с номером 0 – 4-х палубный, а с номером 1 – 3-палубный и т.д.
		int ships1[NUM_SHIPS] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		int ships2[NUM_SHIPS] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

		int mask1[N][N] = { 0 };
		int mask2[N][N] = { 0 };


		cout << " Всё в игре управляется стрелочками! Выстрел осуществляется нажатием ENTER...." << endl;
		cout<<"    Поворот кораблей при расстановке вручную происходит при нажатии -r-..." << endl;
		cout << "=======================================================================================" << "\n\n";
		cout << "_________________________________УДАЧИ !!!!!!!___________________________________" << "\n\n";
		cout << "    Расставите корабли автоматически-введите 1 ... вручную-введите 0...." << endl;
		


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

		// цикл раунда игры
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
				cout << endl << "Ход компьютера ";
				Sleep(1000);

				winBot = botTurn(map1, ships1, mask1);
			}

			if (winHuman == 2)
			{
				cout << "Вы победили!!!" << endl;
				system("pause");
				break;
			}
			else if (winBot == 2)
			{
				cout << "Вы проиграли." << endl;
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