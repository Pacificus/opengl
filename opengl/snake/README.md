
			Игровой процесс

	Здесь представлен мой вариант классической игры змейка. Вначале появляеется змейка размером
3-и клетки. Случайным образом на поле появляется еда размером с 1-у клетку. Программа гарантирует,
что еда не появится "внутри змейки". Змейка может выходить границы поля при этом меняется ее положение на противоположное но сохраняется направление движения. Программа не позволит за один ход
поменять направление на противоположное(например слева-направо). При каждом съедании еды змейка увеличивается на одну клетку. При каждом десятом съедании увеличивается скорость игры. Игра продолжается пока змейка не достигнет максимального размера или не столкнется сама с собой.

			Описание кода

	Программа написана с использованием исключительно библиотеки OpenGL и библиотек С++ <cmath> и <ctime> . Изображения отрисовываются как примитивы через vertex, технология шейдеров не используется. Базовые элементы программы представлены в следующими элементами:
	
	* Функция main() - наша точка входа программы, место инициализации OpenGL
			   и callback, а именно glutDisplayFunc, glutTimerFuc, glutKeyboardFunc

	* void display() - рисует сетку, змейку и еду

	* void timer(int = 0) - через заданное в настройках время обновляет изображение

	* void keyboard(unsigned key, int = 0, int = 0) - реагирует на нажатие клавиш.

Основные данные программы:
	
	* int const MAX - глобальная константа отвечающая за максимальный размер змейки;

	* struct Win - отвечает за хранение данных, отвечающих за настройки экрана (ширина,
			 высота и название)

	* enum KEYS - константы клавиш используемых в игре

	* struct Greed - структура хранящая данные необходимые для отрисовки статичного игрового
			 поля(сетки). Ответсвенность за отрисовку возложена на саму структуру
			 (метов draw()). Для чего используются данные из struct Win

	

