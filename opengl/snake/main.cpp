#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

int const MAX = 1000;

struct {
  double width = 800;
  double height = 600;

  char const* title = "Snake";
} Win;

struct {
    int pause = 250;
    double const KOEF = .7;
} GameSet;

enum KEYS {
    ESC = '\033',
    LEFT = 'a',
    RIGHT = 'd',
    UP = 'w',
    DOWN = 's'
};

struct {
    int rows = 36;
    int columns = round(1.0 * rows * Win.width / Win.height);
    double sx = 1. * Win.width / columns;
    double sy = 1. * Win.height / rows;

    void draw(){
        glBegin(GL_LINES);
            for (int i = 0; i < columns; i++) {
                glVertex2d(sx * i, 0);
                glVertex2d(sx * i, Win.height);
            }

            for (int i = 0; i < columns; i++) {
                glVertex2d(0, i * sy);
                glVertex2d(Win.width, i * sy);
            }
        glEnd();
    }
}Greed;


struct Paar{
    int x;
    int y;

    Paar(){
        this->x = 0;
        this->y = 0;
    }

    Paar(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Paar(Paar const& paar) {
        this->x = paar.x;
        this->y = paar.y;
    }

    Paar& operator = (Paar const& paar) {
        if (this != &paar) {
            this->x = paar.x;
            this->y = paar.y;
        }
        return *this;
    }

    bool operator == (Paar const& another) {
        return this->x == another.x && this->y == another.y;
    }

    void draw() {
        glRectd(x * Greed.sx, y * Greed.sy, (x + 1) * Greed.sx, (y + 1) * Greed.sy);
    }
} paars[MAX], food;

void updateFood() {
    food.x = rand() % Greed.columns;
    food.y = rand() % Greed.rows;
}

struct Snake {
    int length = 3;
    int head_x = 20;
    int head_y = 10;

    int dx = 0;
    int dy = 0;

    KEYS keys = KEYS::RIGHT;

    Snake() {
        updateFood();

        paars[0].x = head_x;
        paars[0].y = head_y;

        paars[1].x = head_x - 1;
        paars[1].y = head_y;

        paars[2].x = head_x - 2;
        paars[2].y = head_y;
    }

    void draw() {

        switch (keys) {

        case KEYS::RIGHT:
            dx = 1;
            dy = 0;
            break;

        case KEYS::LEFT:
            dx = -1;
            dy = 0;
            break;

        case KEYS::UP:
            dx = 0;
            dy = 1;
            break;

        case KEYS::DOWN:
            dx = 0;
            dy = -1;
            break;

        default:
            break;
        }


        if (head_x == -1)  {
            head_x = Greed.columns - 1;
        }

        if (head_x == Greed.columns) {
            head_x = 0;
        }

        if (head_y == -1)  {
            head_y = Greed.rows - 1;
        }

        if (head_y == Greed.rows)  {
            head_y = 0;
        }


        paars[0].x = head_x;
        paars[0].y = head_y;

        for (int i = 0; i < length; i++) {
            paars[i].draw();
        }

        for (int i = length - 1; i > 0; i--) {
            paars[i] = paars[i - 1];
        }

        head_x += dx;
        head_y += dy;
    }

    bool isEqual(Paar cell) {
        for (int i = 0; i < length; i++) {
            if (cell == paars[i]) return true;
        }

        return false;
    }

    bool isLoop(){
        for (int i = 4; i < length; i++) {
            if (paars[0] == paars[i])   return true;
        }

        return false;
    }

    void eat() {
        if (length < MAX) {
           length++;

           if (length % 10 == 0)    GameSet.pause = round(GameSet.KOEF * GameSet.pause);
        }

        else exit(1);
    }
} snake;


void updateSnake() {
    if (snake.isLoop()) {
        exit(1);
    }

    if (snake.isEqual(food))    snake.eat();

    while (snake.isEqual(food)) {
        updateFood();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Greed.draw();
    snake.draw();
    food.draw();

    glFlush();
}

void timer(int = 0)
{
    display();
    updateSnake();
    glutTimerFunc(GameSet.pause,timer, 0);
}

void keyboard(unsigned char key, int = 0, int = 0)
{
    switch (key) {

    case ESC:
        exit(1);
        break;

    case KEYS::LEFT:
        if (snake.keys == KEYS::RIGHT) break;
        snake.keys = KEYS::LEFT;
        break;


    case KEYS::RIGHT:
        if (snake.keys == KEYS::LEFT) break;
        snake.keys = KEYS::RIGHT;


        break;

    case KEYS::UP:
        if (snake.keys == KEYS::DOWN) break;
        snake.keys = KEYS::UP;
        break;


    case KEYS::DOWN:
        if (snake.keys == KEYS::UP) break;
        snake.keys = KEYS::DOWN;
        break;

    default:
        break;
    }
}

int main(int c, char** v)
{
    srand(time(0));
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(Win.width, Win.height);
    glutCreateWindow(Win.title);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Win.width, 0, Win.height, -1, 1);
    glClearColor(0, 0, 0, 0);

    glutDisplayFunc(display);
    glutTimerFunc(GameSet.pause, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

