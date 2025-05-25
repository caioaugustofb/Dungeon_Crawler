#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //Para uso do _kbhit e do _getch

#define TAM 10

char mapa[TAM][TAM] = {
    {'*','*','*','*','*','*','*','*','*','*'},
    {'*','&',' ',' ',' ',' ',' ','@',' ','*'},
    {'*',' ','*','*',' ','*','*','*',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ','*',' ','*',' ','*'},
    {'*','*','*','*',' ','*',' ','*',' ','*'},
    {'*','D',' ',' ',' ',' ',' ','*',' ','*'},
    {'*',' ',' ',' ',' ','X',' ',' ',' ','*'},
    {'*','*','*','*','*','*','*','*','*','*'}
};

int jogadorX = 1, jogadorY = 1;
int posInicialX = 1, posInicialY = 1;
int chaveColetada = 0;
int reinicios = 0;
int interacao = 0;
int i, j;

// armazena o que ta embaixo do jogador (pode ser ' ', '@', etc.)
char embaixoDoJogador = ' ';

void imprimirMapa() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void resetarJogador() {
    mapa[jogadorY][jogadorX] = embaixoDoJogador; // restaura o que estava ali
    jogadorX = posInicialX;
    jogadorY = posInicialY;
    embaixoDoJogador = ' '; // posição inicial é chão
    mapa[jogadorY][jogadorX] = '&';
}

void moverJogador(char tecla) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    if (tecla == 'w') novoY--;
    else if (tecla == 's') novoY++;
    else if (tecla == 'a') novoX--;
    else if (tecla == 'd') novoX++;

    char destino = mapa[novoY][novoX];

    if (destino == '*' || destino == 'D') {
        return;
    }

    if (destino == '#' || destino == 'X' || destino == 'V') {
        printf("Você morreu!\n");
        reinicios++;
        if (reinicios >= 3) {
            printf("Reiniciou 3 vezes. Voltando ao menu.\n");
            exit(0);
        }
        system("pause");
        resetarJogador();
        return;
    }

    // mover o jogador
    mapa[jogadorY][jogadorX] = embaixoDoJogador; // restaura o que estava antes
    embaixoDoJogador = destino; // salva o que está na nova posição
    jogadorX = novoX;
    jogadorY = novoY;
    mapa[jogadorY][jogadorX] = '&';
}

void interagir() {
    int x = jogadorX;
    int y = jogadorY;
    
    if (embaixoDoJogador == '@') {
        chaveColetada = 1;
        printf("Você pegou a chave!\n");
        for(i = 0; i < TAM; i++){
            for(j = 0; j < TAM; j++){
                if(mapa[i][j] == 'D'){
                    mapa[i][j] = '=';
                }
            }
        }
        system("pause");
    } else if (embaixoDoJogador == '=' && chaveColetada) {
        printf("Você abriu a porta!\n");
        system("pause");
    } else if (embaixoDoJogador == 'O') {
        printf("Você apertou o botão!\n");
        system("pause");
    }
}

void moverMonstroAleatorio() {
    int x, y;
    for (y = 0; y < TAM; y++) {
        for (x = 0; x < TAM; x++) {
            if (mapa[y][x] == 'X') {
                int dir = rand() % 4;
                int novoX = x;
                int novoY = y;

                if (dir == 0) novoY--;
                else if (dir == 1) novoY++;
                else if (dir == 2) novoX--;
                else if (dir == 3) novoX++;

                if (mapa[novoY][novoX] == ' ' || mapa[novoY][novoX] == '&') {
                    if (mapa[novoY][novoX] == '&') {
                        printf("O monstro te pegou!\n");
                        reinicios++;
                        if (reinicios >= 3) {
                            printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                            exit(0);
                        }
                        system("pause");
                        resetarJogador();
                        return;
                    }
                    mapa[novoY][novoX] = 'X';
                    mapa[y][x] = ' ';
                    return;
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));

    while (1) {
        system("cls");
        imprimirMapa();

        if (_kbhit()) { //_kbhit e _getch reconhecem a tecla pressionada no teclado e puxa do caractere referente
            char tecla = _getch();
            if (tecla == 'i') {
                interagir();
            } else {
                moverJogador(tecla);
            }
        }

        moverMonstroAleatorio();
        _sleep(200);
    }

    return 0;
}