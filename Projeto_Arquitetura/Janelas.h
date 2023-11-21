

#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header of funtions
void abrirArquivo(FILE *arquivo, char *nomeArquivo);
void Inicio()
{
    initscr(); // Inicializa a biblioteca NCurses
    noecho();
    curs_set(0);
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *Inicio = newwin((yMax / 1.2) + 8, (xMax / 1.2) + 28, 0, 0);
    mvwprintw(Inicio, 18, 20, "   ##                                   ###     ###              #####   ##                    ###          ##");
    mvwprintw(Inicio, 19, 20, "  ####                                   ##      ##  ##  ##    ##   ##                          ##          ## ");
    mvwprintw(Inicio, 20, 20, " ##  ##   #####  #####   ####   ##  ##   ##      ##  ##  ##    #        ###   ##  ##   ##  ##   ##   ####  #####  ####   ######");
    mvwprintw(Inicio, 21, 20, " ##  ##  ##      ##     ##  ##  #######  #####   ##  ##  ##     #####    ##   #######  ##  ##   ##      ##  ##   ##  ##  ##  ##");
    mvwprintw(Inicio, 22, 20, " ######   #####  #####  ######  ## # ##  ##  ##  ##   ####          ##   ##   ## # ##  ##  ##   ##   #####  ##   ##  ##  ## ");
    mvwprintw(Inicio, 23, 20, " ##  ##      ##     ##  ##      ##   ##  ##  ##  ##    ##      ##    ##  ##   ##   ##  ##  ##   ##  ##  ##  ##   ##  ##  ## ");
    mvwprintw(Inicio, 24, 20, " ##  ##  ######  ###### #####   ##   ##  ###### ####   ##       #####   ####  ##   ##  ######  ####  #####  ##    ####   ###");
    wgetch(Inicio);
    werase(Inicio);
    mvwprintw(Inicio, 22, 78, "BY");
    mvwprintw(Inicio, 23, 74, "Jean Guilherme");
    wgetch(Inicio);
    werase(Inicio);
    mvwprintw(Inicio, 22, 78, "AND");
    mvwprintw(Inicio, 23, 77, "Rafael");
    wgetch(Inicio);
    delwin(Inicio);
    endwin();
}
int Opcao(WINDOW *win, int yMax, int xMax)
{
    char *choices[] = {" Sim ", " Nao "};
    int choice;
    int highlight = 0;
    keypad(win, true);
    noecho();
    do
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, (yMax / 2) + i, (xMax / 2) - 9, "%s", choices[i]);
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = 0;
            }

            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 2)
            {
                highlight = 1;
            }

            break;
        }
        if (choice == 10)
        {
            break;
        }

    } while (1);
    return highlight;
}

int Menus(WINDOW *win2)
{
    char *choices[] = {"Abrir Arquivo", "Sair"};
    int choice;
    noecho();
    int highlight = 0;
    keypad(win2, true);
    do
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
                wattron(win2, A_REVERSE);
            mvwprintw(win2, i + 1, 1, "%s", choices[i]);
            wattroff(win2, A_REVERSE);
        }
        choice = wgetch(win2);
        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = 0;
            }

            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 2)
            {
                highlight = 1;
            }

            break;
        }
        if (choice == 10)
        {
            break;
        }

    } while (1);
    return highlight;
}
void PrintaJanela1(WINDOW *win)
{

    werase(win);
    wrefresh(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "File");
    mvwprintw(win, 0, 7, "Edit");
    mvwprintw(win, 0, 12, "sair");
}
void PrintaJ2(WINDOW *win)
{
    mvwprintw(win, 0, 2, "File");
    mvwprintw(win, 0, 7, "Edit");
    mvwprintw(win, 0, 12, "sair");
}

void OpenFile(FILE *Arquivo, int yMax, int xMax)
{
    initscr(); // Inicializa a biblioteca NCurses
    cbreak();
    echo();
    curs_set(0);
    char NomeDoArquivo[10];
    WINDOW *InserirFile = newwin((yMax / 2) / 4, xMax / 2, (yMax / 2) - 10, (xMax / 2) - 40);
    box(InserirFile, 0, 0);
    mvwprintw(InserirFile, 1, 1, "Digite o nome do arquivo");
    wmove(InserirFile, 2, 1);

    wgetstr(InserirFile, NomeDoArquivo);
    abrirArquivo(Arquivo, NomeDoArquivo);

    werase(InserirFile);
    wrefresh(InserirFile);
    noecho();
    endwin();
}
void CreateFile(WINDOW *win)
{
    box(win, 0, 0);
    PrintaJ2(win);
}

void abrirArquivo(FILE *arquivo, char *nomeArquivo)
{

    int ch;

  
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    initscr(); // Inicia o modo curses
    cbreak();
    noecho(); // Desliga o eco de entrada
    WINDOW *win3 = newwin((yMax / 1.2) + 8, (xMax / 1.2) + 28, 0, 0);
    arquivo = fopen(nomeArquivo, "r");

    

    while ((ch = fgetc(arquivo)) != EOF)
    {
        wprintw(win3, "%c", ch);
    }

    wgetch(win3);
    werase(win3);
    wrefresh(win3);

    rewind(arquivo);

char linha[256];
    char *instrucao;
    char *registrador;
    int valor;

    while (fgets(linha, sizeof(linha), arquivo)) {
        instrucao = strtok(linha, " ");
        if (strcmp(instrucao, "li") == 0) {
            registrador = strtok(NULL, ",");
            valor = atoi(strtok(NULL, "\n"));
            wprintw(win3,"Registrador: %s, Valor: %d\n", registrador, valor);
        }
    }

 



    wgetch(win3); // Aguarda a entrada do usuário
    fclose(arquivo);
    endwin(); // Finaliza o modo curses
}
