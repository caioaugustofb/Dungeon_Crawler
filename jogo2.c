#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //Para uso do _kbhit e do _getch
#include <windows.h> // Para uso do Sleep
#include <string.h> // Para uso do strlen
#include <math.h> // Para uso do abs
#include <ctype.h> // Para uso do isalpha

#define TAM_VILA 10
#define TAM_F1 10
#define TAM_F2 20
#define TAM_F3 40
#define FASE_ATUAL 0
#define TAM 40

char mapa[4][TAM][TAM] = 
//mapa vila 0 ↓
{{{' ',' ','*','*','*','*','*','*','*','*'},
{' ',' ','*','g','g','g','g','g','g','*'},
{'*','*','*','g','g','g','g','g','g','*'},
{'*','g','g','g','P','g','g','g','g','*'},
{'D','g','g','g','g','g','g','g','g','*'},
{'D','g','g','g','g','g','g','g','g','*'},
{'*','g','g','g','g','g','g','g','g','*'},
{'*','*','*','g','g','g','g','@','g','*'},
{' ',' ','*','g','g','g','g','g','g','*'},
{' ',' ','*','*','*','*','*','*','*','*'}},
//mapa fase 1 ↓
{{'*','*','*','*','*','*','*','*','*','*'},
{'*','&',' ',' ',' ',' ',' ','@',' ','*'},
{'*',' ','*','*',' ','*','*','*',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ','*',' ','*',' ','*'},
{'*','*','*','*',' ','*',' ','*',' ','*'},
{'*','D',' ',' ',' ',' ',' ','*',' ','*'},
{'*',' ',' ',' ',' ','X',' ','V',' ','*'},
{'*','*','*','*','*','*','*','*','*','*'}},
//mapa fase 2 ↓
{{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
{'*','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ','V',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}},
//mapa fase 3 ↓
{{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
{'*','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','V',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}}};

int faseAtual = 1; // Começa na fase 1
int jogadorX = 1, jogadorY = 1;
int posInicialX = 1, posInicialY = 1;
int chaveColetada = 0;
int reinicios = 0;
int interacao = 0;
int i, j, k;
int monstrosPausados = 0; // Variável para controlar quando os monstros param

// Posições iniciais dos monstros para reset
int monstroX_inicial = 5, monstroY_inicial = 8; // Posição inicial do monstro X
int monstroV_inicial = 7, monstroV_inicial_Y = 8; // Posição inicial do monstro V

// armazena o que ta embaixo do jogador (pode ser ' ', '@', etc.)
char embaixoDoJogador = ' ';

int obterTamanhoFase() {
    switch(faseAtual) {
        case 0: return TAM_VILA;
        case 1: return TAM_F1;
        case 2: return TAM_F2;
        case 3: return TAM_F3;
        default: return TAM_F1;
    }
}

void imprimirMapa() {
    system("cls");
    printf("\n=== JOGO DE AVENTURA - FASE %d ===\n", faseAtual);
    printf("Controles: W/A/S/D para mover, I para interagir\n");
    printf("Coletados: Chave [%s] | Reinicios: %d/3\n", chaveColetada ? "SIM" : "NAO", reinicios);
    if (monstrosPausados) {
        printf("*** MONSTROS PAUSADOS ***\n");
    }
    printf("\n");
    
    int tamanho = obterTamanhoFase();
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            printf("%c ", mapa[faseAtual][i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: & = Jogador, @ = Chave, D/= = Porta, X = Monstro Aleatorio, V = Monstro Inteligente\n");
}

void resetarMonstros() {
    int tamanho = obterTamanhoFase();
    
    // Ajusta posições iniciais baseado na fase
    switch(faseAtual) {
        case 1:
            monstroX_inicial = 5; monstroY_inicial = 8;
            monstroV_inicial = 7; monstroV_inicial_Y = 8;
            break;
        case 2:
            monstroX_inicial = 8; monstroY_inicial = 15;
            monstroV_inicial = 17; monstroV_inicial_Y = 15;
            break;
        case 3:
            monstroX_inicial = 15; monstroY_inicial = 29;
            monstroV_inicial = 36; monstroV_inicial_Y = 29;
            break;
    }
    
    // Remove monstros de posições atuais
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (mapa[faseAtual][i][j] == 'X' || mapa[faseAtual][i][j] == 'V') {
                mapa[faseAtual][i][j] = ' ';
            }
        }
    }
    
    // Reposiciona monstros nas posições iniciais
    if (faseAtual >= 1) { // Só tem monstros da fase 1 em diante
        mapa[faseAtual][monstroY_inicial][monstroX_inicial] = 'X';
        mapa[faseAtual][monstroV_inicial_Y][monstroV_inicial] = 'V';
    }
}

void resetarJogador() {
    mapa[faseAtual][jogadorY][jogadorX] = embaixoDoJogador; // restaura o que estava ali
    jogadorX = posInicialX;
    jogadorY = posInicialY;
    embaixoDoJogador = ' '; // posição inicial é chão
    mapa[faseAtual][jogadorY][jogadorX] = '&';
    
    // Reseta os monstros para posições iniciais
    resetarMonstros();
}

void moverJogador(char tecla) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    if (tecla == 'w') novoY--;
    else if (tecla == 's') novoY++;
    else if (tecla == 'a') novoX--;
    else if (tecla == 'd') novoX++;

    char destino = mapa[faseAtual][novoY][novoX];

    if (destino == '*' || destino == 'D' || destino == 'P') {
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
    mapa[faseAtual][jogadorY][jogadorX] = embaixoDoJogador; // restaura o que estava antes
    embaixoDoJogador = destino; // salva o que está na nova posição
    jogadorX = novoX;
    jogadorY = novoY;
    mapa[faseAtual][jogadorY][jogadorX] = '&';
}

void interagir() {
    // Pausa os monstros durante qualquer interação
    monstrosPausados = 1;
    
    if (embaixoDoJogador == '@') {
        chaveColetada = 1;
        embaixoDoJogador = ' '; // A chave some do mapa quando coletada
        printf("Você pegou a chave!\n");
        
        int tamanho = obterTamanhoFase();
        for (i = 0; i < tamanho; i++) {
            for (j = 0; j < tamanho; j++) {
                if(mapa[faseAtual][i][j] == 'D'){
                    mapa[faseAtual][i][j] = '=';
                }
            }
        }
        system("pause");
    } else if (embaixoDoJogador == '=' && chaveColetada) {
        printf("Você abriu a porta!\n");
        printf("Parabéns! Você completou a fase %d!\n", faseAtual);
        system("pause");
    } else if (embaixoDoJogador == 'O') {
        printf("Você apertou o botão!\n");
        system("pause");
    } else {
        printf("Não há nada para interagir aqui.\n");
        system("pause");
    }
    
    // Despausa os monstros após a interação
    monstrosPausados = 0;
}

void moverMonstroAleatorio() {
    // Se os monstros estão pausados ou não é uma fase com monstros, não move
    if (monstrosPausados || faseAtual < 1) {
        return;
    }
    
    int tamanho = obterTamanhoFase();
    int x, y;
    for (y = 0; y < tamanho; y++) {
        for (x = 0; x < tamanho; x++) {
            if (mapa[faseAtual][y][x] == 'X') {
                int dir = rand() % 4;
                int novoX = x;
                int novoY = y;

                if (dir == 0) novoY--;
                else if (dir == 1) novoY++;
                else if (dir == 2) novoX--;
                else if (dir == 3) novoX++;

                if (mapa[faseAtual][novoY][novoX] == ' ' || mapa[faseAtual][novoY][novoX] == '&') {
                    if (mapa[faseAtual][novoY][novoX] == '&') {
                        printf("O monstro aleatório te pegou!\n");
                        reinicios++;
                        if (reinicios >= 3) {
                            printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                            exit(0);
                        }
                        system("pause");
                        resetarJogador();
                        return;
                    }
                    mapa[faseAtual][novoY][novoX] = 'X';
                    mapa[faseAtual][y][x] = ' ';
                    return;
                }
            }
        }
    }
}

// Função para mover o monstro inteligente 'V' em direção ao jogador
void moverMonstroInteligente() {
    // Se os monstros estão pausados ou não é uma fase com monstros, não move
    if (monstrosPausados || faseAtual < 1) {
        return;
    }
    
    int tamanho = obterTamanhoFase();
    int x, y;
    // Procura o monstro 'V' no mapa
    for (y = 0; y < tamanho; y++) {
        for (x = 0; x < tamanho; x++) {
            if (mapa[faseAtual][y][x] == 'V') {
                // Calcula a diferença de posição entre monstro e jogador
                int deltaX = jogadorX - x;
                int deltaY = jogadorY - y;
                
                int novoX = x;
                int novoY = y;
                
                // Determina o movimento baseado na maior distância (Manhattan distance)
                if (abs(deltaX) > abs(deltaY)) {
                    // Move horizontalmente em direção ao jogador
                    if (deltaX > 0) novoX++; // Jogador está à direita
                    else if (deltaX < 0) novoX--; // Jogador está à esquerda
                } else if (abs(deltaY) > 0) {
                    // Move verticalmente em direção ao jogador
                    if (deltaY > 0) novoY++; // Jogador está abaixo
                    else if (deltaY < 0) novoY--; // Jogador está acima
                }
                
                // Verifica se a nova posição é válida
                char destino = mapa[faseAtual][novoY][novoX];
                
                // Pode se mover para espaços vazios ou onde está o jogador
                if (destino == ' ' || destino == '&') {
                    if (destino == '&') {
                        // Monstro pegou o jogador
                        printf("O monstro inteligente te pegou!\n");
                        reinicios++;
                        if (reinicios >= 3) {
                            printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                            exit(0);
                        }
                        system("pause");
                        resetarJogador();
                        return;
                    }
                    // Move o monstro para a nova posição
                    mapa[faseAtual][novoY][novoX] = 'V';
                    mapa[faseAtual][y][x] = ' ';
                    return;
                }
                // Se não pode se mover na direção preferida, tenta movimento alternativo
                else {
                    // Tenta movimento vertical se tentou horizontal primeiro
                    if (abs(deltaX) > abs(deltaY) && abs(deltaY) > 0) {
                        novoX = x; // Reset horizontal movement
                        if (deltaY > 0) novoY = y + 1;
                        else novoY = y - 1;
                        
                        destino = mapa[faseAtual][novoY][novoX];
                        if (destino == ' ' || destino == '&') {
                            if (destino == '&') {
                                printf("O monstro inteligente te pegou!\n");
                                reinicios++;
                                if (reinicios >= 3) {
                                    printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                                    exit(0);
                                }
                                system("pause");
                                resetarJogador();
                                return;
                            }
                            mapa[faseAtual][novoY][novoX] = 'V';
                            mapa[faseAtual][y][x] = ' ';
                            return;
                        }
                    }
                    // Tenta movimento horizontal se tentou vertical primeiro
                    else if (abs(deltaY) >= abs(deltaX) && abs(deltaX) > 0) {
                        novoY = y; // Reset vertical movement
                        if (deltaX > 0) novoX = x + 1;
                        else novoX = x - 1;
                        
                        destino = mapa[faseAtual][novoY][novoX];
                        if (destino == ' ' || destino == '&') {
                            if (destino == '&') {
                                printf("O monstro inteligente te pegou!\n");
                                reinicios++;
                                if (reinicios >= 3) {
                                    printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                                    exit(0);
                                }
                                system("pause");
                                resetarJogador();
                                return;
                            }
                            mapa[faseAtual][novoY][novoX] = 'V';
                            mapa[faseAtual][y][x] = ' ';
                            return;
                        }
                    }
                }
                return; // Sai após processar o primeiro (e único) monstro 'V'
            }
        }
    }
}

int main() {
    srand(time(NULL));

    while (1) {
        imprimirMapa();

        if (_kbhit()) { //_kbhit e _getch reconhecem a tecla pressionada no teclado e puxa do caractere referente
            char tecla = _getch();
            if (tecla == 'i') {
                interagir();
            } else {
                moverJogador(tecla);
            }
        }

        // Move o monstro aleatório 'X'
        moverMonstroAleatorio();
        
        // Move o monstro inteligente 'V'
        moverMonstroInteligente();
        
        Sleep(200);
    }

    return 0;
}