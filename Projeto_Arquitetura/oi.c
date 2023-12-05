
//para compilar gcc -o oi.c -lncurses
// para executar ./oi   ("Nota: Mudar o nome do arquivo depois!!")


#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Janelas.h"


// Header of funtions
void Inicio();
void Janela1(FILE *arquivo, char registrador[32][4], int valor[32]);
void StatusReg(char regitro[32][4], int valor[32],int numReg);
int Janela2( FILE *arquivo,WINDOW *win, int yMax, int xMax,char registrador[32][4], int valor[32]);

void Janela1(FILE *arquivo, char registrador[32][4], int valor[32])
{

    initscr(); // Inicializa a biblioteca NCurses
    noecho();
    curs_set(0);
    char ch, ch2;
    int yMax, xMax, opcao,numReg;
    int sts=0;
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
            mvwprintw(win, 0, 7, "Status");
            mvwprintw(win, 0, 14, "sair");
            // confirmação da escolha
            mvwprintw(win, (yMax / 2) - 3, (xMax / 2) - 15, "Tem Certeza?");
            // função opção para obter a escolha do usuario
            opcao = Opcao(win, yMax, xMax);

            if (opcao == 0)
            {
               numReg=Janela2(arquivo,win, yMax, xMax, registrador, valor);    
            }
            sts=1;
            PrintaJanela1(win);
            // se a opção for "não" ou o usuário escolhera opção sair da janela2 será impresso novamente a janela1

            break;

        case 'e':
            // opção  é destacada usando a função wattron (a opção fica destacada em branco)
            mvwprintw(win, 0, 2, "File");
            wattron(win, A_STANDOUT);
            mvwprintw(win, 0, 7, "Status");
            wattroff(win, A_STANDOUT);
            mvwprintw(win, 0, 14, "sair");
              opcao = Opcao(win, yMax, xMax);
  if (opcao == 0 && sts==1)
            {
                StatusReg(registrador,valor,numReg);
            }else{
                 mvwprintw(win, (yMax / 2) - 3, (xMax / 2)-23 , "Não foi feita nenhuma Alteração");
                  mvwprintw(win, (yMax / 2) - 2, (xMax / 2) -23, "  Todos Registradore valem 0");
               
                 wgetch(win);
            }
            PrintaJanela1(win);
            break;

        default:

            break;
        }

        if (ch == 's')
        { // opção  é destacada usando a função wattron (a opção fica destacada em branco)
            mvwprintw(win, 0, 2, "File");
            mvwprintw(win, 0, 7, "Status");
            wattron(win, A_STANDOUT);
            mvwprintw(win, 0, 14, "sair");
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
void StatusReg(char regitro[32][4], int valor[32],int numReg){
     int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
 WINDOW *Status =newwin((yMax / 1.2) + 8, (xMax / 1.2) + 28, 0, 0);
box(Status, 0, 0);
for (int i = 0; i < numReg; i++)
{
  mvwprintw(Status, 1+i, 1, "%s...%i",regitro[i],valor[i]);

}
wgetch(Status);

}
int Janela2( FILE *arquivo,WINDOW *win, int yMax, int xMax, char registrador[32][4], int valor[32])
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
    int numReg;
    if (opção == 0)
    {
        werase(win2);
        wrefresh(win2);

        // é realizado a abertura de uma nova janela para que o usuário escolha o arquivo a ser executado pelo simulador
       numReg= OpenFile(arquivo, yMax, xMax,registrador,valor);        
        
    }else if (opção == 2)
    {   
        endwin();//finaliza a janela
    }
 return numReg;
}


int main()
{
    FILE *arquivo;//Arquivo  
    char registrador[32][4];
    int valor[32];



   
    Inicio();
    Janela1(arquivo,registrador, valor);
    
    return 0;
}