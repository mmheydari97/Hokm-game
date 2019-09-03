#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<time.h>
#include<string>
#include<Windows.h>

using namespace std;
string s;
int card[4][13];// all cards
int gc[2][4];// cards on the grand ,row1 = kind of card,row 2 = card number
int dast = 0;
int hokm = 0, hakem, mode, boresh = 0, nadashte[4][4] = { { 0 }, { 0 }, { 0 }, { 0 } }, barande, barande0;
// barande = winner player at each round(4tayee)
//mode = winner team at each time

struct player//player!
{
	int card[4][13];//cards!
	string name;
	int p/*small point*/, P/*big point (choob kebrit)*/, group/*team number*/, n/*player number*/;
};
struct cart
{
	int kind;
	int number;
};
cart cardw;//cardw defined
player p[4];// 4 player defined

void hidecursor();


void giving_card(int);// give card
void initializing();// first necessary values
void hand();// giving cards ,hakem determinig and choosing hokm by computer
void printxy(int x, int y, string a);//print a string on x,y
string play(player& p, int turn);// play for computer
void show(int i);//show player name
HANDLE stdHandle;
CONSOLE_SCREEN_BUFFER_INFO buffInfo;
string play0(int turn);// user playing
void play1();//choosing hokm(user)
string convertcard(int card1[4][13]);//make a string contains card characters for a player
int main()
{
	hidecursor();
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdHandle, 0x20);
	system("cls");
	srand(time(0));
	initializing();
	for (int i = 0; i < 4; i++)
		p[i].P = 0;
	printxy(10, 35, "WELCOME");															//introducing
	printxy(13, 10, "In this game you must choose cards with arrow key and press enter");
	printxy(17, 26, "press any key to continue");
	_getch();
	system("cls");
	printxy(12, 25, "Enter your name : ");
	cin >> p[0].name;
	system("cls");
	while (p[0].P != 7 && p[1].P != 7)// play!
	{
		show(0);			// showing player's name and points
		show(1);
		show(2);
		show(3);
		printxy(2, 60, " ");
		cout << "team 1 score " << p[0].P;
		printxy(3, 60, " ");
		cout << "team 2 score " << p[1].P;
		Sleep(1500);//delay 1.5 s
		system("cls");
		hand();
		show(0);
		show(1);
		show(2);
		show(3);
		printxy(2, 60, " ");
		cout << "team 1 score  " << p[0].P;
		printxy(3, 60, " ");
		cout << "team 2 score  " << p[1].P;
		Sleep(2000);
		printxy(12, 35, "               ");
		printxy(13, 35, "               ");
		while (p[0].p != 7 && p[1].p != 7)//a round
		{
			printxy(2, 77, "");
			cout << p[0].p;
			printxy(3, 77, "");
			cout << p[1].p;
			Sleep(1500);
			printxy(0, 70, " ");
			char c = ' ';
			c += -32 + hokm + 3;
			cout << "hokm :";
			if (int(c) == 3 || int(c) == 4)// red color for hearts and diamonds
				SetConsoleTextAttribute(stdHandle, 0x2C);
			else
				SetConsoleTextAttribute(stdHandle, 0x20);
			cout << c;
			printxy(12, 50, "   ");//erasing previous cards
			printxy(9, 40, "   ");
			printxy(12, 30, "   ");
			printxy(15, 40, "   ");
			for (int i = barande; i < barande + 4; i++)
			{

				printxy(19, 0, convertcard(p[0].card));//show player cards
				show(i % 4);
				if (i % 4 != 0)//computer plays
				{
					if (i % 4 == 1)
					{
						printxy(12, 50, "   ");
						printxy(12, 50, play(p[i % 4], i - barande));
					}
					if (i % 4 == 2)
					{
						printxy(9, 40, "   ");
						printxy(9, 40, play(p[i % 4], i - barande));
					}
					if (i % 4 == 3)
					{
						printxy(12, 30, "   ");
						printxy(12, 30, play(p[i % 4], i - barande));
					}
				}
				else// user plays
				{
					printxy(22, 35, "it's your turn");
					printxy(15, 40, "   ");
					printxy(15, 40, play0(i - barande));
					printxy(22, 35, "              ");
				}
				Sleep(1000);
			}
			boresh = 0;
			barande = barande0;// determine winner of round
			p[barande].p++;//
			p[(barande + 2) % 4].p++;
		}
		dast++;
		system("cls");
		if (p[0].p == 7)
			printxy(12, 35, ""), cout << p[0].name << " and " << p[2].name << "won this round";
		else
			printxy(12, 35, ""), cout << p[1].name << " and " << p[3].name << "won this round";
		p[0].p = p[1].p = 0;
		p[mode - 1].P++;
	}
	system("cls");
	if (p[0].P == 7)
		printxy(12, 35, ""), cout << p[0].name << " and " << p[2].name << "won this round";
	else
		printxy(12, 35, ""), cout << p[1].name << " and " << p[3].name << "won this round";
	_getch();
	return 0;
}
void giving_card(int i)
{
	int r, c, n = 0;
	//r = row
	//c = column
	//n = number of given cards
	for (int j = 0; j < 4; j++)
	{
		n = 0;
		while (n != i)
		{
			c = rand() % 13;
			r = rand() % 4;
			if (card[r][c])
			{
				p[j].card[r][c] = 1;
				card[r][c] = 0;
				n++;
			}

		}
	}
}
void initializing()
{
	boresh = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			nadashte[i][j] = 0;
	p[1].name = "p1";
	p[2].name = "p2";
	p[3].name = "p3";
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 13; k++)
				p[i].card[j][k] = p[i].p = 0, card[j][k] = 1, p[i].group = i % 2 + 1, p[i].n = i, p[i].p = 0;
}
void hand()
{
	int sum = 0, counter = 0, maxim = 0, number = 0;
	initializing();
	giving_card(5);
	if (dast == 0)
	{
		hakem = rand() % 4;//hakem determinig
		barande = barande0 = hakem;
	}
	else
	{
		if (p[hakem].group != mode)
			hakem = (2 * (rand() % 2) + 1 + hakem) % 4;// hakem is from winner team
		barande = barande0 = hakem;
	}
	printxy(12, 35, "hakem : ");
	cout << p[hakem].name;
	if (hakem == 0)// choosing hokm user
	{
		printxy(19, 0, convertcard(p[0].card));
		play1();
	}
	if (hakem != 0)// choosing hokm(computer)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (p[hakem].card[i][j] == 1)
				{
					sum = sum + j;
					counter = counter + 1;
				}
			}
			number = counter * 1000 + sum * 10 + i;
			if (number >= maxim) // number generate
				maxim = number;
			number = 0;
			sum = 0;
			counter = 0;
		}
		hokm = maxim % 10;

	}

	printxy(13, 35, "hokm :");
	char c = ' ';
	c += -32 + hokm + 3;
	if (int(c) == 3 || int(c) == 4)// change color
		SetConsoleTextAttribute(stdHandle, 0x2C);
	else
		SetConsoleTextAttribute(stdHandle, 0x20);
	cout << c;

	giving_card(8);
}
void printxy(int x, int y, string a)
{
	buffInfo.dwCursorPosition.X = y;
	buffInfo.dwCursorPosition.Y = x;
	SetConsoleCursorPosition(stdHandle, buffInfo.dwCursorPosition);
	if (a.length())
		for (int i = 0; i < a.length(); i++)
		{
			if (int(a[i]) == 3 || int(a[i]) == 4)
				SetConsoleTextAttribute(stdHandle, 0x2C);
			else
				SetConsoleTextAttribute(stdHandle, 0x20);
			cout << a[i];
		}

}
string play(player& p, int turn)
{
	//this function decides
	//gc[0][0] = kind of first grand card
	if (turn == 0)
	{
		int x = 0;
		for (int i = 0; i < 4; i++)
			if (nadashte[(p.n + 2) % 4][i] == 1 && i != hokm)
				for (int j = 0; j < 13; j++)
					if (p.card[i][j] == 1)
					{

						gc[0][turn] = i;
						gc[1][turn] = j;
						cardw.kind = i;
						cardw.number = j;
						mode = p.group;
						barande0 = p.n;
						x++;
						break;
					}
		int r = rand() % 4, y = r;
		while (x == 0 && r - y != 3)
		{

			if (nadashte[(p.n + 1) % 4][r % 4] == 0 && nadashte[(p.n + 1) % 4][r % 4] == 0)
				for (int i = 12; i >= 0; i--)
					if (p.card[r % 4][i] == 1)
					{

						gc[0][turn] = r % 4;
						gc[1][turn] = i;
						cardw.kind = r % 4;
						cardw.number = i;
						if (cardw.kind == hokm)
							boresh = 1;
						mode = p.group;
						barande0 = p.n;
						x++;
						break;
					}
			r++;
		}
		r = rand() % 4;
		y = r;
		while (x == 0 && r - y != 3)
		{
			for (int i = 0; i < 13; i++)
				if (p.card[r % 4][i])
				{
					gc[0][turn] = r % 4;
					gc[1][turn] = i;
					cardw.kind = r % 4;
					cardw.number = i;
					if (cardw.kind == hokm)
						boresh = 1;
					mode = p.group;
					barande0 = p.n;
					x++;
					break;
				}
			r++;
		}
	}
	else {//agar turn != 0
		int kind = gc[0][0], n = 0;
		for (int i = 0; i < 13; i++) // baresi dashtan ya nadashtan
			if (p.card[kind][i] == 1)
			{
				n++;
			}
		if (n == 0)//nadarim
		{
			nadashte[p.n][kind] = 1; //// arayeye nadashteha
			if (mode == p.group)//barande rad midim
			{//we have several idea
				int x = 0;
				for (int i = 13; i >= 0; i--)
					for (int j = 0; j < 4; j++)
						if (p.card[j][i] == 1 && j != hokm)
						{
							gc[0][turn] = j;
							gc[1][turn] = i;
							x++;
						}
				if (x == 0)// faghat hokm darim
					for (int i = 0; i < 13; i++)
						if (p.card[hokm][i])
						{
							gc[0][turn] = hokm;
							gc[1][turn] = i;
							if (boresh == 1 && i > cardw.number)
							{
								cardw.number = i;
								cardw.kind = hokm;
								barande0 = p.n;
								mode = p.group;
							}
							else if (boresh == 0)
							{
								cardw.number = i;
								cardw.kind = hokm;
								boresh = 1;
								barande0 = p.n;
								mode = p.group;
							}
						}
			}
			else//bazande
			{
				if (boresh)//boride shode
				{//we have several idea

					int x = 0;
					for (int i = cardw.number; i < 13; i++) // baresi dashtan ya nadashtan hokm
						if (p.card[hokm][i] == 1)
						{
							x++;
							gc[0][turn] = hokm;
							gc[1][turn] = i;
							mode = p.group;
							cardw.number = i;
							cardw.kind = hokm;
							barande0 = p.n;
						}
					if (x == 0)//hokm nadarim rad midim
					{
						for (int i = 13; i >= 0; i--)
							for (int j = 0; j < 4; j++)
								if (p.card[j][i] == 1)
								{
									gc[0][turn] = j;
									gc[1][turn] = i;
								}
					}
				}
				else//boride nashode
				{
					int x = 0;
					for (int i = 0; i < 13; i++) // baresi dashtan ya nadashtan hokm
						if (p.card[hokm][i] == 1)
						{
							x++;
							gc[0][turn] = hokm;
							gc[1][turn] = i;
							mode = p.group;
							cardw.number = i;
							cardw.kind = hokm;
							barande0 = p.n;
							boresh = 1;
							break;
						}
					if (x == 0)//hokm nadarim rad midim
					{
						for (int i = 13; i >= 0; i--)
							for (int j = 0; j < 4; j++)
								if (p.card[j][i] == 1)
								{
									gc[0][turn] = j;
									gc[1][turn] = i;
								}
					}
				}
			}
		}
		else//darim
		{
			if (mode == p.group)//barande
			{// we have 2 idea

				for (int i = 0; i<13; i++)
					if (p.card[kind][i] == 1)
					{
						gc[0][turn] = kind;
						gc[1][turn] = i;
						if (gc[1][turn] > cardw.number && boresh == 0)
							barande0 = p.n, cardw.number = gc[1][turn], cardw.kind = kind;
						else if (kind == hokm && gc[1][turn] > cardw.number)
							barande0 = p.n, cardw.number = gc[1][turn], cardw.kind = kind;

						break;
					}


			}
			else//bazande
			{
				if (boresh == 1)//boride shode
				{
					if (kind != hokm)//agar zamine hokm nabood
					{
						for (int i = 0; i < 13; i++)
							if (p.card[kind][i] == 1)
							{
								gc[0][turn] = kind;
								gc[1][turn] = i;
								break;
							}
					}
					else//agar zamine hokm bood
					{
						int x = 0;
						for (int i = cardw.number; i < 13; i++)
							if (p.card[kind][i] == 1)
							{
								gc[0][turn] = kind;
								gc[1][turn] = i;
								mode = p.group;
								cardw.number = i;
								cardw.kind = kind;
								barande0 = p.n;
								x++;
								break;
							}
						if (x == 0)
							for (int i = 0; i < 13; i++)
								if (p.card[kind][i] == 1)
								{
									gc[0][turn] = kind;
									gc[1][turn] = i;
									x++;
									break;
								}
					}
				}
				else//boride nashode
				{

					int x = 0;
					//we have several idea
					for (int i = cardw.number; i < 13; i++)
						if (p.card[kind][i] == 1)
						{
							gc[0][turn] = kind;
							gc[1][turn] = i;
							cardw.number = i;
							cardw.kind = kind;
							barande0 = p.n;
							mode = p.group;
							x++;
							break;
						}
					if (x == 0)// bishtar az cardw nadarim
					{
						for (int i = 0; i < 13; i++)
							if (p.card[kind][i] == 1)
							{
								gc[0][turn] = kind;
								gc[1][turn] = i;
								break;
							}
					}
				}
			}
		}
	}
	p.card[gc[0][turn]][gc[1][turn]] = 0; // hazf card

	if (gc[0][turn] == hokm)
		boresh = 1;
	char b[5] = { ' ', ' ', ' ', ' ', '\0' };// neshandadan kart entekhabi

	b[0] += -32 + gc[0][turn] + 3;// namade kart

	switch (gc[1][turn])//shomare kart
	{
	case 8:
		b[1] = '1';
		b[2] = '0';
		break;
	case 9:
		b[1] = 'J';
		break;
	case 10:
		b[1] = 'Q';
		break;
	case 11:
		b[1] = 'K';
		break;
	case 12:
		b[1] = 'A';
		break;
	default:
		b[1] += -32 + gc[1][turn] + 50;
		break;
	}
	p.card[gc[0][turn]][gc[1][turn]] = 0;
	//cout<<mode;
	return b;
}
string play0(int turn)
{
	int allow = 0, n = 0, m = 0;
	char c = 'z';
	char a[2] = { 'a', '\0' };
	a[0] -= 97;
	a[0] += 30;
	int x = 0;
	const int left = 75, right = 77;
	string card = convertcard(p[0].card);//card(character)
	if (turn != 0)// check have or not
		for (int i = 0; i < 13; i++)
			if (p[0].card[gc[0][0]][i])
				n++;
	printxy(20, x, a);
	while (!allow)// until choose incorrect card
	{
		if (turn == 0)
			allow = 1;
		if (turn != 0 && n == 0)
			allow = 1, nadashte[0][gc[0][0]] = 1;
		while (int(c) != 13)//curser
		{
			c = _getch();
			if (int(c) == -32)
			{
				c = _getch();
				switch (int(c))
				{
				case left:
				{
					printxy(20, x, " ");
					if (x != 0)
						x -= 4;
					printxy(20, x, a);
					break;
				}
				case right:
				{
					printxy(20, x, " ");
					if (x != (card.length() / 4) * 4 - 4)
						x += 4;
					printxy(20, x, a);
					break;
				}
				}
			}
		}
		if (n != 0 && turn != 0)
		{
			if (int(card[x]) - 3 == gc[0][0])
				allow = 1;
			else
			{
				printxy(23, 25, "you can not choose this card");
				Sleep(1500);
				printxy(23, 25, "                            ");
				c = ' ';
			}
		}
	}
	printxy(20, x, " ");
	printxy(19, 0, "                                                             ");

	gc[0][turn] = int(card[x]) - 3;
	switch (card[x + 1])
	{
	case 'A':
		gc[1][turn] = 12;
		break;
	case 'K':
		gc[1][turn] = 11;
		break;
	case 'Q':
		gc[1][turn] = 10;
		break;
	case 'J':
		gc[1][turn] = 9;
		break;
	default:
		if (card[x + 2] == '0')
			gc[1][turn] = 8;
		else
			gc[1][turn] = int(card[x + 1]) - 50;
		break;
	}
	// ghezavatha
	if (turn == 0)
	{
		cardw.number = gc[1][turn], cardw.kind = gc[0][turn], mode = p[0].group;
		barande0 = 0;
		if (gc[0][turn] == hokm)
			boresh = 1;
	}
	else
	{

		//arzeyabi
		if (boresh == 1)
		{
			if ((gc[1][turn] > cardw.number) && (gc[0][turn] == hokm))
				mode = p[0].group, cardw.number = gc[1][turn], cardw.kind = gc[0][turn], barande0 = 0;

		}
		else//boride nashode
		{
			if (gc[0][turn] == hokm)
				boresh = 1, mode = p[0].group, cardw.number = gc[1][turn], cardw.kind = gc[0][turn], barande0 = 0;
			else
			{

				if (gc[0][turn] == gc[0][0] && gc[1][turn] > cardw.number)
					mode = p[0].group, cardw.number = gc[1][turn], cardw.kind = gc[0][turn], barande0 = 0;


			}
		}
	}
	if (gc[0][turn] == hokm)
		boresh = 1;
	char b[4] = { ' ', ' ', ' ', ' ' };//return string
	for (int i = 0; i < 4; i++)
		b[i] = card[x + i];
	b[3] = '\0';
	p[0].card[gc[0][turn]][gc[1][turn]] = 0;
	return b;

}
void show(int i)
{
	if (i == 0)
		printxy(21, 40, p[0].name);
	if (i == 1)
		printxy(12, 70, p[1].name);
	if (i == 2)
		printxy(1, 40, p[2].name);
	if (i == 3)
		printxy(12, 5, p[3].name);
}
string convertcard(int card1[4][13])
{
	char card[53];
	for (int i = 0; i < 53; i++)
		card[i] = ' ', card[i] -= 32;
	int i = 0;

	for (int j = 0; j < 4; j++)
		for (int k = 0; k < 13; k++)
			if (card1[j][k] == 1)
			{
				card[i] += j + 3;
				switch (k)
				{
				case 12:
					card[i + 1] = 'A';
					break;
				case 11:
					card[i + 1] = 'K';
					break;
				case 10:
					card[i + 1] = 'Q';
					break;
				case 9:
					card[i + 1] = 'J';
					break;
				case 8:
					card[i + 1] = '1';
					card[i + 2] = '0';
					break;
				default:
					card[i + 1] += k + 50;
					break;
				}
				if (int(card[i + 2]) == 0)
					card[i + 2] = ' ';
				card[i + 3] = ' ';
				i += 4;
			}
	card[52] = '\0';
	return card;
}
void play1()
{
	int allow = 0;
	char c = 'z';
	char a[2] = { 'a', '\0' };
	a[0] -= 97;
	a[0] += 30;
	int x = 0;
	string card = convertcard(p[0].card);// card = user cards
	const int left = 75, right = 77;
	printxy(20, x, a);
	while (int(c) != 13)//cursor
	{
		c = _getch();					// get arrow key and moving cursor (those are two characters)
		if (int(c) == -32)
		{
			c = _getch();
			switch (int(c))
			{
			case left:
			{
				printxy(20, x, " ");
				if (x != 0)
					x -= 4;
				printxy(20, x, a);
				break;
			}
			case right:
			{
				printxy(20, x, " ");
				if (x != (card.length() / 4) * 4 - 4)
					x += 4;
				printxy(20, x, a);
				break;
			}
			}
		}
	}
	printxy(20, x, " ");
	hokm = int(card[x]) - 3;
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
