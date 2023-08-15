#include <ncurses.h>
#include <string.h>
#include "modo_comando.h"
#include "modo_key.h"

#define MAX_MENU_ITEMS 3
#define SUBMENU_ITEMS 2

//criando função para desenhar menu principal

void desenha_menu(int marcado) {

    int linhas, colunas;

//criando struct de itens do menu principal

    char *menu[MAX_MENU_ITEMS] = {
        "1 - Iniciar",
        "2 - Menu",
        "3 - Sair"
    };

    getmaxyx(stdscr, linhas, colunas);
    clear();

//definindo cor e imprimindo título do jogo

    attron(COLOR_PAIR(1));  // Define a cor de texto como verde e fundo como preto.
    mvprintw(linhas / 2 - MAX_MENU_ITEMS, (colunas - strlen("Logo Turtle")) / 2, "Logo Turtle");

//criando loop for para exibir os itens

    for (int i = 0; i < MAX_MENU_ITEMS; i++) {

        if (i == marcado) {
            attron(A_REVERSE);
            mvprintw(linhas / 2 + i, (colunas - strlen(menu[i])) / 2, "%s", menu[i]);
            attroff(A_REVERSE);
        }

        else {
            mvprintw(linhas / 2 + i, (colunas - strlen(menu[i])) / 2, "%s", menu[i]);
        }
    }

    refresh();
}

//criando função para desenhar submenu

void desenha_submenu(int marcado) {

    int linhas, colunas;

//criando struct de itens do submenu

    char *submenu[SUBMENU_ITEMS] = {
        "1 - Logo Turtle [Facil]",
        "2 - Logo Turtle [Dificil]"
    };

    getmaxyx(stdscr, linhas, colunas);
    clear();

//definindo cor e loop for para exibir os itens do submenu

    attron(COLOR_PAIR(1));

    for (int i = 0; i < SUBMENU_ITEMS; i++) {

        if (i == marcado) {
            attron(A_REVERSE);
            mvprintw(linhas / 2 + i, (colunas - strlen(submenu[i])) / 2, "%s", submenu[i]);
            attroff(A_REVERSE);
        }

        else {
            mvprintw(linhas / 2 + i, (colunas - strlen(submenu[i])) / 2, "%s", submenu[i]);
        }
    }

    refresh();
}

//criando função para modularizar e chamar os modos

void modos(int mode) {
    clear();
    if (mode == 0) {
        comandos();
    } else if (mode == 1) {
        keymode();
    }
    getch();
    clear();
}

//criando função para mostrar as instruções no menu

void desenha_info() {

    int linha_info = 3;

    attron(COLOR_PAIR(2));
    mvprintw(linha_info++, 0, "Logo Turtle [Facil]");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(linha_info++, 0, "Comandos de Sentido: NORTE, NORDESTE, NOROESTE, LESTE, OESTE, SUL, SUDESTE e SUDOESTE;");
    mvprintw(linha_info++, 0, "Comandos de Casas: Quantidade de casas a andar;");
    mvprintw(linha_info++, 0, "Comandos Diversos: APAGAR, VOLTAR e SAIR;");
    mvprintw(linha_info++, 0, "[EXEMPLOS]:");
    mvprintw(linha_info++, 0, "1- OESTE 10;");
    mvprintw(linha_info++, 0, "2- APAGAR;");
    mvprintw(linha_info++, 0, "3- VOLTAR;");
    mvprintw(linha_info++, 0, "4- SAIR;");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    mvprintw(linha_info++, 0, "OBS: Digite o primeiro comando como STRING seguido de um SPACE e um VALOR INTEIRO.");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(3));
    mvprintw(linha_info++, 0, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    attroff(COLOR_PAIR(3));

    linha_info++;

    attron(COLOR_PAIR(2));
    mvprintw(linha_info++, 0, "Logo Turtle [Dificil]");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(linha_info++, 0, "Comandos de Sentido [Pontos cardeais]: NORTE, SUL, OESTE e LESTE || [UP/DOWN/LEFT/RIGHT];");
    mvprintw(linha_info++, 0, "Comandos de Sentido [Pontos colaterais]: NOROESTE, SUDOESTE, NORDESTE e SUDESTE || [INS/DEL/PGUP/PGDN];");
    mvprintw(linha_info++, 0, "Comandos diversos: APAGAR RASTRO || [HM];");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    mvprintw(linha_info++, 0, "OBS: [ GAME OVER ] caso a tartaruga encoste na borda.");
    attroff(COLOR_PAIR(4));

    mvprintw(linha_info+2, 0, "PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU");

    getch();  // Espera o usuário pressionar uma tecla para voltar ao menu.
}

//criando função do menu e chamando todas as outras funções voids definidas

int main() {

//inicializando e configurando a tela inicial

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);

//estabelecendo parâmetros de cores

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);

//criando variáveis para destacar onde o cursor está para interagir

    int marcado = 0;
    int sub_marcado = 0;
    int in_submenu = 0;
    int in_menu = 0;

//criando loop principal while para exibir e interagir com todos os menus

    while (1) {

//exibindo o submenu iniciar

        if (in_submenu) {
            desenha_submenu(sub_marcado);
        }

        else {
            desenha_menu(marcado);
        }

        int c = getch();

//condicionais em switch case para mudar a localização do cursor e interagir

        switch (c) {
            case KEY_UP:

                if (in_submenu) {
                    sub_marcado--;
                    if (sub_marcado < 0) sub_marcado = SUBMENU_ITEMS - 1;
                }

                else {
                    marcado--;
                    if (marcado < 0) marcado = MAX_MENU_ITEMS - 1;
                }
                break;

            case KEY_DOWN:

                if (in_submenu) {
                    sub_marcado++;
                    if (sub_marcado >= SUBMENU_ITEMS) sub_marcado = 0;
                }

                else {
                    marcado++;
                    if (marcado >= MAX_MENU_ITEMS) marcado = 0;
                }
                break;


            case 10:

                if (in_submenu) {
                    modos(sub_marcado);
                    in_submenu = 0;
                }

                else {

//opção do iniciar para ir para os modos de jogo

                    if (marcado == 0) {
                        in_submenu = 1;
                    }

//opção do menu para mostrar as instruções

                    else if (marcado == 1) {
                        clear();
                        desenha_info();
                    }

//opção do sair

                    else if (marcado == 2) {
                        endwin();
                        return 0;
                    }
                }
                break;
        }
    }

    endwin();
    return 0;
}
