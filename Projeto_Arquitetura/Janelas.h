

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

    }while (1);
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
char registrador[32][4];
int valor[32];
int i = 0;

while (fgets(linha, sizeof(linha), arquivo))
{
    instrucao = strtok(linha, " ");

    if (strcmp(instrucao, "li") == 0)
    {
        strcpy(registrador[i], strtok(NULL, ","));
        valor[i] = atoi(strtok(NULL, "\n"));
        i++;
    }

//Instrução add
    if (strcmp(instrucao, "add") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");

        i++;
        strcpy(registrador[i], registradorDestino);

        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        else if (strcmp(registrador[k], registradorOrigem1) == 0)
            {
                indice_origem1 = k;
            }
      
        else if (strcmp(registrador[k], registradorOrigem2) == 0)
            {
                indice_origem2 = k;
            }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        wprintw(win3, "Realizando a adição...\n");
        valor[indice_destino] = valor[indice_origem1] + valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wprintw(win3, "Adição realizada.\n");
        wrefresh(win3); // Atualiza a janela após a operação de adição*/
    }

    }

//Instrução sub
    if (strcmp(instrucao, "sub") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");

        i++;
        strcpy(registrador[i], registradorDestino);

        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        else if (strcmp(registrador[k], registradorOrigem1) == 0)
            {
                indice_origem1 = k;
            }
        else if (strcmp(registrador[k], registradorOrigem2) == 0)
            {
                indice_origem2 = k;
            }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {

        wprintw(win3, "Realizando a subtração...\n");
        valor[indice_destino] = valor[indice_origem1] - valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wprintw(win3, "Subtração realizada.\n");
        wrefresh(win3); // Atualiza a janela após a operação de adição*/
    }

    }

//Instrução addi
    if (strcmp(instrucao, "addi") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem;
        int valorImediato;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem = strtok(NULL, " ,");
        valorImediato = atoi(strtok(NULL, " \n"));

        int indice_destino = -1;
        int indice_origem = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem) == 0)
        {
            indice_origem = k;
        }
    }

    if (indice_destino != -1 && indice_origem != -1)
    {
        valor[indice_destino] = valor[indice_origem] + valorImediato;
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }

    }

//Instrução subi
    if (strcmp(instrucao, "subi") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem;
        int valorImediato;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem = strtok(NULL, " ,");
        valorImediato = atoi(strtok(NULL, " \n"));

        int indice_destino = -1;
        int indice_origem = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem) == 0)
        {
            indice_origem = k;
        }
    }

    if (indice_destino != -1 && indice_origem != -1)
    {
        valor[indice_destino] = valor[indice_origem] - valorImediato;
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }
    
    }

//Instrução mult        
    if (strcmp(instrucao, "mult") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = valor[indice_origem1] * valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }

    }

//Instrução div
    if (strcmp(instrucao, "div") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        if (valor[indice_origem2] != 0)
        {
            valor[indice_destino] = valor[indice_origem1] / valor[indice_origem2];
            wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
            wrefresh(win3);
        }
        else
        {
            wprintw(win3, "Erro: Divisão por zero não é permitida.\n");
            wrefresh(win3);
        }
    }

    }

//Instrução and
    if (strcmp(instrucao, "and") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = valor[indice_origem1] & valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }

    }

//Instrução or
    if (strcmp(instrucao, "or") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = valor[indice_origem1] | valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }

    }

//Instrução xor
    if (strcmp(instrucao, "xor") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = valor[indice_origem1] ^ valor[indice_origem2];
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }

    }
        
//Instrução nor
    if (strcmp(instrucao, "nor") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = ~(valor[indice_origem1] | valor[indice_origem2]);  // Operação NOR
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }
    
    }

//Instrução slt
    if (strcmp(instrucao, "slt") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem1;
        char *registradorOrigem2;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem1 = strtok(NULL, " ,");
        registradorOrigem2 = strtok(NULL, " \n");

        int indice_destino = -1;
        int indice_origem1 = -1;
        int indice_origem2 = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem1) == 0)
        {
            indice_origem1 = k;
        }
        if (strcmp(registrador[k], registradorOrigem2) == 0)
        {
            indice_origem2 = k;
        }
    }

    if (indice_destino != -1 && indice_origem1 != -1 && indice_origem2 != -1)
    {
        valor[indice_destino] = valor[indice_origem1] < valor[indice_origem2] ? 1 : 0;  // Operação SLT
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }
    
    }

//Instrução sll
    if (strcmp(instrucao, "sll") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem;
        int n;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem = strtok(NULL, " ,");
        n = atoi(strtok(NULL, " \n"));  // Converte a string para um inteiro

        int indice_destino = -1;
        int indice_origem = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem) == 0)
        {
            indice_origem = k;
        }
    }

    if (indice_destino != -1 && indice_origem != -1)
    {
        valor[indice_destino] = valor[indice_origem] << n;  // Operação SLL
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }
    
    }

//Instrução sra
    if (strcmp(instrucao, "sra") == 0)
    {
        char *registradorDestino;
        char *registradorOrigem;
        int n;

        registradorDestino = strtok(NULL, " ,");
        i++;
        strcpy(registrador[i], registradorDestino);
        registradorOrigem = strtok(NULL, " ,");
        n = atoi(strtok(NULL, " \n"));  // Converte a string para um inteiro

        int indice_destino = -1;
        int indice_origem = -1;

    for (int k = 0; k < i + 1; k++)
    {
        if (strcmp(registrador[k], registradorDestino) == 0)
        {
            indice_destino = k;
        }
        if (strcmp(registrador[k], registradorOrigem) == 0)
        {
            indice_origem = k;
        }
    }

    if (indice_destino != -1 && indice_origem != -1)
    {
        valor[indice_destino] = valor[indice_origem] >> n;  // Operação SRA
        wprintw(win3, "Registrador: %s, Valor: %d\n", registrador[indice_destino], valor[indice_destino]);
        wrefresh(win3);
    }
    
    }

}

    wgetch(win3); // Aguarda a entrada do usuário
    fclose(arquivo);
    endwin(); // Finaliza o modo curses
}
