
//para compilar gcc -o oi.c -lncurses
// para executar ./oi   ("Nota: Mudar o nome do arquivo depois!!")


#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Janelas.h"


// Header of funtions
void Inicio();
void Janela1(FILE *arquivo);
void Janela2( FILE *arquivo,WINDOW *win, int yMax, int xMax);


void Janela1(FILE *arquivo)
{

    initscr(); // Inicializa a biblioteca NCurses
    noecho();
    curs_set(0);
    char ch, ch2;
    int yMax, xMax, opcao;
    getmaxyx(stdscr, yMax, xMax); // obtenção do tamanho maximo do terminal
    WINDOW *win = newwin((yMax / 1.2) + 8, (xMax / 1.2) + 28, 0, 0);
    PrintaJanela1(win); // função para imprimir as opções da janela

    // while com uma condição que nunca será verdadeira (loop infinito)
    while (ch = wgetch(win))
    { // switch para cada opção escolhida
        switch (ch)
        {
        case 'f':
            // opção  é destacada usando a função wattron (a opção fica destacada em branco)
            wattron(win, A_STANDOUT);
            mvwprintw(win, 0, 2, "File");
            wattroff(win, A_STANDOUT);
            // demais opções continuam no estado inicial
            mvwprintw(win, 0, 7, "Edit");
            mvwprintw(win, 0, 12, "sair");
            // confirmação da escolha
            mvwprintw(win, (yMax / 2) - 3, (xMax / 2) - 15, "Tem Certeza?");
            // função opção para obter a escolha do usuario
            opcao = Opcao(win, yMax, xMax);

            if (opcao == 0)
            {
                Janela2(arquivo,win, yMax, xMax);
              
                
            }
            PrintaJanela1(win);
            // se a opção for "não" ou o usuário escolhera opção sair da janela2 será impresso novamente a janela1

            break;

        case 'e':
            // opção  é destacada usando a função wattron (a opção fica destacada em branco)
            mvwprintw(win, 0, 2, "File");
            wattron(win, A_STANDOUT);
            mvwprintw(win, 0, 7, "Edit");
            wattroff(win, A_STANDOUT);
            mvwprintw(win, 0, 12, "sair");

            break;

        default:

            break;
        }

        if (ch == 's')
        { // opção  é destacada usando a função wattron (a opção fica destacada em branco)
            mvwprintw(win, 0, 2, "File");
            mvwprintw(win, 0, 7, "Edit");
            wattron(win, A_STANDOUT);
            mvwprintw(win, 0, 12, "sair");
            wattroff(win, A_STANDOUT);
            
            opcao = Opcao(win, yMax, xMax);
            if (opcao == 0)
            {  
                break;
            }
            // se a opção for não o loop continua
            PrintaJanela1(win);
        }
    }

   
    wgetch(win);
    endwin();
}
void Janela2( FILE *arquivo,WINDOW *win, int yMax, int xMax)
{
    initscr(); // Inicializa a biblioteca NCurses
    noecho();
    curs_set(0);
    werase(win);
    wrefresh(win);
    WINDOW *win2 = newwin((yMax / 2), xMax / 2, (yMax / 2) - 10, (xMax / 2) - 40);
    box(win2, 0, 0);
    PrintaJ2(win2);
    int opção = Menus(win2);

    if (opção == 0)
    {
        werase(win2);
        wrefresh(win2);

        // é realizado a abertura de uma nova janela para que o usuário escolha o arquivo a ser executado pelo simulador
        OpenFile(arquivo, yMax, xMax);        
        
    }else if (opção == 2)
    {   
        endwin();//finaliza a janela
    }
 
}


int main()
{
    FILE *arquivo;//Arquivo  
 
    Inicio();
    Janela1(arquivo);
   
    return 0;
}