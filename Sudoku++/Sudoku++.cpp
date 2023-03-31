#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

#define CELL_SIZE 50
#define LINE_WIDTH 3
#define FIELD_BORDER 20
#define DOWN_SIZE 100

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

void drawNums(RenderWindow* window, Font* font, int table[9][9])
{
    Text text;
    text.setFont(*font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(40);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (table[i][j])
            {
                text.setString(to_string(table[i][j]));
                text.setPosition(Vector2f(j * CELL_SIZE + FIELD_BORDER * 1.6, i * CELL_SIZE + FIELD_BORDER));
                (*window).draw(text);
            }
        }
    }
}

int main()
{

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

    RenderWindow window(VideoMode(9 * CELL_SIZE + 2 * FIELD_BORDER, 9 * CELL_SIZE + 2 * FIELD_BORDER + DOWN_SIZE), 
        L"Sudoku++", Style::Close);

    window.setVerticalSyncEnabled(true);
    Font font;
    if (!font.loadFromFile("Disket-Mono-Bold.ttf"))
        return 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        window.clear(Color(188, 152, 126, 255));
        drawTable(&window);
        drawNums(&window, &font, var_1);
        window.display();
    }
    return 0;
}