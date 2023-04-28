#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "check.h"
#include "field.h"

using namespace sf;
using namespace std;

#define CELL_SIZE 50
#define LINE_WIDTH 3
#define FIELD_BORDER 20
#define DOWN_SIZE 100

const vector<Keyboard::Key> nums = {
	Keyboard::Num1,
	Keyboard::Num2,
	Keyboard::Num3,
	Keyboard::Num4,
	Keyboard::Num5,
	Keyboard::Num6,
	Keyboard::Num7,
	Keyboard::Num8,
	Keyboard::Num9
};

const vector<Keyboard::Key> keyboardNums = {
	Keyboard::Numpad1,
	Keyboard::Numpad2,
	Keyboard::Numpad3,
	Keyboard::Numpad4,
	Keyboard::Numpad5,
	Keyboard::Numpad6,
	Keyboard::Numpad7,
	Keyboard::Numpad8,
	Keyboard::Numpad9
};

struct tablePos {
	tablePos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
};

vector<tablePos> pos_wrong(int sudoku[9][9], int num)
{
	vector<tablePos> pos;
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == num)
			{
				pos.push_back(tablePos(i, j));
			}
		}
	}
	return pos;
}

void drawTable(RenderWindow* window)
{
	for (int i = 0; i <= 9; i++)
	{
		RectangleShape a(Vector2f(LINE_WIDTH * ((i % 3) == 0 ? 1.7 : 1), 9 * CELL_SIZE + LINE_WIDTH));
		a.setPosition(i * CELL_SIZE + FIELD_BORDER, FIELD_BORDER);
		a.setFillColor(Color::Black);
		(*window).draw(a);

		RectangleShape b(Vector2f(9 * CELL_SIZE + LINE_WIDTH, LINE_WIDTH * ((i % 3) == 0 ? 1.7 : 1)));
		b.setPosition(FIELD_BORDER, i * CELL_SIZE + FIELD_BORDER);
		b.setFillColor(Color::Black);
		(*window).draw(b);
	}
}

void drawNums(RenderWindow* window, Font* regular_font, Font* bold_font, sudoku* var, sudoku table)
{
	Text text;
	text.setFillColor(Color::Black);
	text.setCharacterSize(40);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (table[i][j])
			{
				text.setFont(((*var)[i][j] == 0) ? *regular_font : *bold_font);
				text.setString(to_string(table[i][j]));
				text.setPosition(Vector2f(j * CELL_SIZE + FIELD_BORDER * 1.6, i * CELL_SIZE + FIELD_BORDER));
				(*window).draw(text);
			}
		}
	}
}

void drawWin(RenderWindow* window, Font* font)
{
	Text text;
	text.setCharacterSize(20);
	text.setFillColor(Color::Black);
	text.setFont(*font);
	text.setString("You win!\nPress Any key to go to next level");
	text.setPosition(FIELD_BORDER, CELL_SIZE * 10);
	(*window).draw(text);
}

tablePos processClick(Vector2f pos)
{
	pos.x -= FIELD_BORDER;
	pos.y -= FIELD_BORDER;
	return tablePos(pos.x / CELL_SIZE, pos.y / CELL_SIZE);
}

int getNumByKey(Keyboard::Key key)
{
	for (int i = 0; i < 9; i++)
	{
		if (nums[i] == key || keyboardNums[i] == key)
			return (i + 1);
	}
	return -1;
}

tablePos getPosByKey(Keyboard::Key key)
{
	tablePos pressedPos(0, 0);
	if (key == Keyboard::Left)
		pressedPos.x--;
	if (key == Keyboard::Right)
		pressedPos.x++;
	if (key == Keyboard::Up)
		pressedPos.y--;
	if (key == Keyboard::Down)
		pressedPos.y++;
	return pressedPos;
}

void processNumClick(int num, tablePos pos, int var[9][9], int table[9][9])
{
	if (pos.x == -1)
		return;
	if (var[pos.y][pos.x] != 0)
		return;
	table[pos.y][pos.x] = num;
}
const Color backgroundColor(188, 152, 126);
const Color choosenColor(144, 238, 144);
const Color errorColor(200, 0, 0, 150);

int main()
{
	RenderWindow window(VideoMode(9 * CELL_SIZE + 2.3 * FIELD_BORDER, 9 * CELL_SIZE + 2.3 * FIELD_BORDER + DOWN_SIZE),
		L"Sudoku++", Style::Close);

	window.setVerticalSyncEnabled(true);
	Font regular_font, bold_font;
	if (!regular_font.loadFromFile("Disket-Mono-Regular.ttf") || !bold_font.loadFromFile("Disket-Mono-Bold.ttf"))
		return 0;
	int var_now = 0;
	sudoku* var = getSudoku(var_now);
	sudoku table;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			table[i][j] = (*var)[i][j];
	}

	tablePos choosenPos = tablePos(-1, -1);
	tablePos pressedPos(0, 0);
	bool win = false;
	vector<tablePos> errors;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonReleased)
			{
				pressedPos = processClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
				if ((pressedPos.x == choosenPos.x && pressedPos.y == choosenPos.y)
					|| (pressedPos.x < 0 || pressedPos.x > 8)
					|| (pressedPos.y < 0 || pressedPos.y > 8))
					choosenPos = tablePos(-1, -1);
				else
					choosenPos = pressedPos;
			}
			if (event.type == Event::KeyPressed)
			{
				if (win)
				{
					win = false;
					var_now = (var_now >= 5) ? 0 : (var_now + 1);

					var = getSudoku(var_now);
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
							table[i][j] = (*var)[i][j];
					}
				}
				else
				{
					pressedPos = getPosByKey(event.key.code);
					if (pressedPos.x != 0 || pressedPos.y != 0)
					{
						if (choosenPos.x == -1)
						{
							if (pressedPos.y == 1)
								choosenPos = tablePos(0, 8);
							else if (pressedPos.x == 1)
								choosenPos = tablePos(8, 0);
							else
								choosenPos = tablePos(0, 0);
						}
						else
						{
							choosenPos.x = min(max(choosenPos.x + pressedPos.x, 0), 8);
							choosenPos.y = min(max(choosenPos.y + pressedPos.y, 0), 8);
						}
					}
					else
					{
						int pressedNum = getNumByKey(event.key.code);
						if (pressedNum != -1)
						{
							processNumClick(pressedNum, choosenPos, *var, table);
							if (!now_check(table))
								errors = pos_wrong(table, pressedNum);
							else
								errors.clear();
						}
						else if (event.key.code == Keyboard::BackSpace)
						{
							if (choosenPos.x != -1 && var[choosenPos.y][choosenPos.x] == 0)
							{
								errors.clear();
								table[choosenPos.y][choosenPos.x] = 0;
							}
						}
					}
				}
				win = final_check(table);
			}
		}

		window.clear(backgroundColor);
		if (choosenPos.x != -1)
		{
			RectangleShape rect(Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(Vector2f(choosenPos.x * CELL_SIZE + FIELD_BORDER, choosenPos.y * CELL_SIZE + FIELD_BORDER));
			rect.setFillColor(choosenColor);
			window.draw(rect);
		}
		for (auto error : errors)
		{
			RectangleShape rect(Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(Vector2f(error.y * CELL_SIZE + FIELD_BORDER, error.x * CELL_SIZE + FIELD_BORDER));
			rect.setFillColor(errorColor);
			window.draw(rect);
		}
		drawTable(&window);
		drawNums(&window, &regular_font, &bold_font, var, table);
		if (win)
			drawWin(&window, &bold_font);

		window.display();
	}
	return 0;
}