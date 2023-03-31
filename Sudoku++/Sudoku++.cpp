#include <SFML/Graphics.hpp>
using namespace sf;

#define CELL_SIZE 50
#define LINE_WIDTH 3
#define FIELD_BORDER 20
#define DOWN_SIZE 100

int drawTable(RenderWindow* window)
{
    for (int i = 0; i <= 9; i++)
    {
        RectangleShape a(Vector2f(LINE_WIDTH, 9 * CELL_SIZE + LINE_WIDTH));
        a.setPosition(i * CELL_SIZE + FIELD_BORDER, FIELD_BORDER);
        a.setFillColor(Color::Black);
        (*window).draw(a);

        RectangleShape b(Vector2f(9 * CELL_SIZE + LINE_WIDTH, LINE_WIDTH));
        b.setPosition(FIELD_BORDER, i * CELL_SIZE + FIELD_BORDER);
        b.setFillColor(Color::Black);
        (*window).draw(b);
    }
    return 0;
}

int main()
{

    RenderWindow window(VideoMode(9 * CELL_SIZE + 2 * FIELD_BORDER, 9 * CELL_SIZE + 2 * FIELD_BORDER + DOWN_SIZE), 
        L"Sudoku++", Style::Close);

    window.setVerticalSyncEnabled(true);

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
        window.display();
    }
    return 0;
}