#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

#define CELL_SIZE 50
#define LINE_WIDTH 3
#define FIELD_BORDER 20
#define DOWN_SIZE 100

struct tablePos {
    tablePos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x;
    int y;
};

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

void drawNums(RenderWindow* window, Font* regular_font, Font* bold_font, int var[9][9], int table[9][9])
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
                text.setFont((var[i][j] == 0) ? *regular_font : *bold_font);
                text.setString(to_string(table[i][j]));
                text.setPosition(Vector2f(j * CELL_SIZE + FIELD_BORDER * 1.6, i * CELL_SIZE + FIELD_BORDER));
                (*window).draw(text);
            }
        }
    }
}

tablePos processClick(Vector2f pos)
{
    pos.x -= FIELD_BORDER;
    pos.y -= FIELD_BORDER;
    return tablePos(pos.x / CELL_SIZE, pos.y / CELL_SIZE);
}

int main()
{
    RenderWindow window(VideoMode(9 * CELL_SIZE + 2.3 * FIELD_BORDER, 9 * CELL_SIZE + 2.3 * FIELD_BORDER + DOWN_SIZE), 
        L"Sudoku++", Style::Close);

    window.setVerticalSyncEnabled(true);
    Font regular_font, bold_font;
    if (!regular_font.loadFromFile("Disket-Mono-Regular.ttf") || !bold_font.loadFromFile("Disket-Mono-Bold.ttf"))
        return 0;

    int var_1[9][9] = {
      { 0, 0, 0, 0, 0, 8, 0, 0, 1 },
      { 0, 0, 8, 0, 4, 0, 0, 0, 0 },
      { 0, 0, 3, 0, 9, 1, 0, 4, 2 },
      { 0, 3, 1, 0, 0, 0, 0, 0, 0 },
      { 6, 0, 0, 7, 5, 0, 0, 0, 0 },
      { 0, 2, 0, 3, 0, 6, 0, 9, 5 },
      { 0, 6, 2, 8, 0, 0, 0, 0, 4 },
      { 0, 0, 5, 9, 0, 4, 0, 0, 7 },
      { 0, 0, 4, 0, 0, 0, 2, 0, 9 }
    };

    int table[9][9] = {
      { 0, 0, 0, 0, 0, 8, 0, 0, 1 },
      { 0, 0, 8, 0, 4, 0, 0, 0, 0 },
      { 0, 0, 3, 0, 9, 1, 8, 4, 2 },
      { 0, 3, 1, 0, 0, 0, 0, 0, 0 },
      { 6, 0, 0, 7, 5, 0, 0, 0, 0 },
      { 0, 2, 0, 3, 0, 6, 0, 9, 5 },
      { 0, 6, 2, 8, 0, 0, 0, 0, 4 },
      { 0, 0, 5, 9, 0, 4, 0, 0, 7 },
      { 0, 0, 4, 0, 0, 0, 2, 0, 9 }
    };

    tablePos choosenPos = tablePos(-1, -1);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonReleased)
            {
                choosenPos = processClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
        }
        
        window.clear(Color(188, 152, 126, 255));
        if (choosenPos.x != -1)
        {
            RectangleShape rect(Vector2f(CELL_SIZE, CELL_SIZE));
            rect.setPosition(Vector2f(choosenPos.x * CELL_SIZE + FIELD_BORDER, choosenPos.y * CELL_SIZE + FIELD_BORDER));
            rect.setFillColor(Color(144, 238, 144));
            window.draw(rect);
        }
        drawTable(&window);
        drawNums(&window, &regular_font, &bold_font, var_1, table);
        window.display();
    }      
    return 0;
}