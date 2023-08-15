#include <ncurses.h>
#include <stdlib.h>
#include "modo_key.h"

//definindo a função principal

void keymode() {

//definindo struct

    typedef struct {
    int x, y;
    } Point;

//configurando janela e cursor

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

//criando e estabelecendo cores

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

//criando os parâmetros de altura e largura (coordenadas) da janela principal e da tartaruga

    int largura_modo_key, altura_modo_key;
    getmaxyx(stdscr, altura_modo_key, largura_modo_key);

    Point limite_janela[2] = {{1, 1}, {altura_modo_key - 2, largura_modo_key - 2}};
    Point tartaruga = {largura_modo_key / 2, altura_modo_key / 2};

//exibindo a tartaruga no centro com a borda

    attron(COLOR_PAIR(1));
    box(stdscr, 0, 0);
    mvaddch(tartaruga.y, tartaruga.x, '@');

//declarando a mira da tartaruga

    Point nova_mira;

//exibindo a tartaruga no centro com a borda

    while (1) {

        int key = getch();

        nova_mira = tartaruga;

        switch (key) {

//comando leste

            case KEY_RIGHT:
                nova_mira.x++;
                break;

//comando oeste

            case KEY_LEFT:
                nova_mira.x--;
                break;

//comando norte

            case KEY_UP:
                nova_mira.y--;
                break;

//comando sul

            case KEY_DOWN:
                nova_mira.y++;
                break;

//comando noroeste

            case KEY_IC:
                nova_mira.y--;
                nova_mira.x--;
                break;

//comando sudoeste

            case KEY_DC:
                nova_mira.y++;
                nova_mira.x--;
                break;

//comando nordeste

            case KEY_PPAGE:
                nova_mira.y--;
                nova_mira.x++;
                break;

//comando sudeste

            case KEY_NPAGE:
                nova_mira.y++;
                nova_mira.x++;
                break;

//comando para apagar todo o rastro

            case KEY_HOME:
                clear();
                box(stdscr, 0, 0);
                break;
            default:
                continue;
        }

//imprimindo tartaruga e rastro

        mvaddch(tartaruga.y, tartaruga.x, '*');
        mvaddch(nova_mira.y, nova_mira.x, '@');
        wrefresh(stdscr);

        tartaruga = nova_mira;

//estabelecendo as bordas do game-over

        bool colidirlimite_janela = false;

        if ((tartaruga.x >= limite_janela[0].x + largura_modo_key - 2)||
            (tartaruga.x <= limite_janela[0].x - 1)||
            (tartaruga.y <= limite_janela[0].y - 1)||
            (tartaruga.y >= limite_janela[0].y + altura_modo_key - 2))
            {
            colidirlimite_janela = true;
            }

        if (colidirlimite_janela) {

            mvprintw(altura_modo_key / 2, (largura_modo_key - 12) / 2, "[ GAME OVER ]");
            getch();
            clear();
            mvprintw(1, 1, "[ PRESSIONE [ENTER] PARA VOLTAR AO MENU ]");
            break;
        }
    }

    endwin();

    //return 0;

}
