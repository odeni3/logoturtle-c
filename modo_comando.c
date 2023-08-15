#include <ncurses.h>
#include <string.h>
#include "modo_comando.h"

//definindo a função principal

void comandos() {

//configurando janela e cursor

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(TRUE);
    noecho();

//criando e estabelecendo cores

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

//criando os parâmetros de altura e largura (coordenadas) da janela principal e da tartaruga

    int altura_modo_comando, largura_modo_comando;
    getmaxyx(stdscr, altura_modo_comando, largura_modo_comando);
    int tartarugay = altura_modo_comando / 2;
    int tartarugax = largura_modo_comando / 2;

//criando a janela de início antes do jogo começar

    attron(COLOR_PAIR(1));
    box(stdscr, 0, 0);
    mvprintw(tartarugay, (largura_modo_comando - strlen("PRESSIONE [ENTER] PARA INICIAR")) / 2, "PRESSIONE [ENTER] PARA INICIAR");

//atualizando tela e esperando resposta do usuário

    getch();
    clear();

//iniciando a tela de jogo e definindo variáveis

    mvprintw(tartarugay, tartarugax, "@");

    char input[30];
    char sentido[10];
    int casa_final, casa_atual;

//criando loop principal

    while(1) {

        move(altura_modo_comando - 1, 0);
        clrtoeol();

//iniciando caixinha de digitação

        mvprintw(altura_modo_comando - 1, 0, "DIGITE OS MOVIMENTOS:");
        echo();
        curs_set(TRUE);
        getstr(input);

//recebendo as variáveis de sentido e quantidade

        sscanf(input, "%s %d", sentido, &casa_final);

        box(stdscr, 0, 0);
        curs_set(FALSE);
        noecho();

        casa_atual = 0;

//criando condicionais de movimentação e quantidade

//comando oeste

        if (strcasecmp(sentido, "OESTE") == 0) {

            while (casa_atual < casa_final && tartarugax - casa_atual >= 1) {
                mvaddch(tartarugay, tartarugax - casa_atual, '*');
                casa_atual++;
            }

            tartarugax -= casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando leste

        else if (strcasecmp(sentido, "LESTE") == 0) {

            while (casa_atual < casa_final && tartarugax + casa_atual < largura_modo_comando - 1) {
                mvaddch(tartarugay, tartarugax + casa_atual, '*');
                casa_atual++;
            }

            tartarugax += casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando norte

        else if (strcasecmp(sentido, "NORTE") == 0) {

            while (casa_atual < casa_final && tartarugay - casa_atual >= 1) {
                mvaddch(tartarugay - casa_atual, tartarugax, '*');
                casa_atual++;
            }

            tartarugay -= casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando sul

        else if (strcasecmp(sentido, "SUL") == 0) {

            while (casa_atual < casa_final && tartarugay + casa_atual < altura_modo_comando - 3) {
                mvaddch(tartarugay + casa_atual, tartarugax, '*');
                casa_atual++;
            }

            tartarugay += casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando nordeste

        else if (strcasecmp(sentido, "NORDESTE") == 0) {
            while (casa_atual < casa_final && tartarugay - casa_atual >= 1 && tartarugax + casa_atual < largura_modo_comando - 2) {
                mvaddch(tartarugay - casa_atual, tartarugax + casa_atual, '*');
                casa_atual++;
            }

            tartarugay -= casa_atual;
            tartarugax += casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando noroeste

        else if (strcasecmp(sentido, "NOROESTE") == 0) {

            while (casa_atual < casa_final && tartarugay - casa_atual >= 1 && tartarugax - casa_atual >= 1) {
                mvaddch(tartarugay - casa_atual, tartarugax - casa_atual, '*');
                casa_atual++;
            }

            tartarugay -= casa_atual;
            tartarugax -= casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando sudeste

        else if (strcasecmp(sentido, "SUDESTE") == 0) {

            while (casa_atual < casa_final && tartarugay + casa_atual < altura_modo_comando - 3 && tartarugax + casa_atual < largura_modo_comando - 2) {
                mvaddch(tartarugay + casa_atual, tartarugax + casa_atual, '*');
                casa_atual++;
            }

            tartarugay += casa_atual;
            tartarugax += casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando sudoeste

        else if (strcasecmp(sentido, "SUDOESTE") == 0) {

            while (casa_atual < casa_final && tartarugay + casa_atual < altura_modo_comando - 3 && tartarugax - casa_atual >= 1) {
                mvaddch(tartarugay + casa_atual, tartarugax - casa_atual, '*');
                casa_atual++;
            }

            tartarugay += casa_atual;
            tartarugax -= casa_atual;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando para apagar

        else if (strcasecmp(sentido, "APAGAR") == 0) {

            clear();
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando para voltar

        else if (strcasecmp(sentido, "VOLTAR") == 0) {

            mvprintw(tartarugay, tartarugax, " ");
            tartarugay = altura_modo_comando / 2;
            tartarugax = largura_modo_comando / 2;
            mvprintw(tartarugay, tartarugax, "@");
        }

//comando para sair do jogo

        else if (strcasecmp(sentido, "SAIR") == 0) {

            mvprintw(1, 1, "[ JOGO FINALIZADO | PRESSIONE [ENTER] PARA FECHAR ]");
            getch();
            clear();
            mvprintw(1, 1, "[ PRESSIONE [ENTER] NOVAMENTE PARA VOLTAR AO MENU ]");
            break;
        }

//comando para sentido inexistente

        else {

            mvprintw(1, 1, "[ SENTIDO INEXISTENTE | PRESSIONE [ENTER] PARA RESETAR ]");
            getch();
            clear();
            box(stdscr, 0, 0);
            mvprintw(tartarugay, tartarugax, "@");
        }
    }

    endwin();

    //return 0;

}
