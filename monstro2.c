#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //Para uso do _kbhit e do _getch
#include <windows.h> // Para uso do Sleep
#include <string.h> // Para uso do strlen

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
    {'*',' ',' ',' ',' ','X',' ','V',' ','*'},
    {'*','*','*','*','*','*','*','*','*','*'}
};

int jogadorX = 1, jogadorY = 1;
int posInicialX = 1, posInicialY = 1;
int chaveColetada = 0;
int reinicios = 0;
int interacao = 0;
int i, j;
int monstrosPausados = 0; // Variável para controlar quando os monstros param

// armazena o que ta embaixo do jogador (pode ser ' ', '@', etc.)
char embaixoDoJogador = ' ';

void imprimirMapa() {
    printf("\n=== JOGO DE AVENTURA ===\n");
    printf("Controles: W/A/S/D para mover, I para interagir\n");
    printf("Coletados: Chave [%s]\n", chaveColetada ? "SIM" : "NAO");
    if (monstrosPausados) {
        printf("*** MONSTROS PAUSADOS ***\n");
    }
    printf("\n");
    
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: & = Jogador, @ = Chave, D/= = Porta, X = Monstro Aleatorio, V = Monstro Inteligente\n");
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
    
    // Pausa os monstros durante qualquer interação
    monstrosPausados = 1;
    
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
        printf("Parabéns! Você venceu o jogo!\n");
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
    // Se os monstros estão pausados, não move
    if (monstrosPausados) {
        return;
    }
    
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
                    mapa[novoY][novoX] = 'X';
                    mapa[y][x] = ' ';
                    return;
                }
            }
        }
    }
}

// Função para mover o monstro inteligente 'V' em direção ao jogador
void moverMonstroInteligente() {
    // Se os monstros estão pausados, não move
    if (monstrosPausados) {
        return;
    }
    
    int x, y;
    // Procura o monstro 'V' no mapa
    for (y = 0; y < TAM; y++) {
        for (x = 0; x < TAM; x++) {
            if (mapa[y][x] == 'V') {
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
                char destino = mapa[novoY][novoX];
                
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
                    mapa[novoY][novoX] = 'V';
                    mapa[y][x] = ' ';
                    return;
                }
                // Se não pode se mover na direção preferida, tenta movimento alternativo
                else {
                    // Tenta movimento vertical se tentou horizontal primeiro
                    if (abs(deltaX) > abs(deltaY) && abs(deltaY) > 0) {
                        novoX = x; // Reset horizontal movement
                        if (deltaY > 0) novoY = y + 1;
                        else novoY = y - 1;
                        
                        destino = mapa[novoY][novoX];
                        if (destino == ' ' || destino == '&') {
                            if (destino == '&') {
                                printf("O monstro inteligente te pegou!\n");
                                reinicios++;
                                if (reinicios >= 3) {
                                    printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                                    exit(0);
                                }
                                printf("Pressione qualquer tecla para continuar...\n");
                                getch();
                                resetarJogador();
                                return;
                            }
                            mapa[novoY][novoX] = 'V';
                            mapa[y][x] = ' ';
                            return;
                        }
                    }
                    // Tenta movimento horizontal se tentou vertical primeiro
                    else if (abs(deltaY) >= abs(deltaX) && abs(deltaX) > 0) {
                        novoY = y; // Reset vertical movement
                        if (deltaX > 0) novoX = x + 1;
                        else novoX = x - 1;
                        
                        destino = mapa[novoY][novoX];
                        if (destino == ' ' || destino == '&') {
                            if (destino == '&') {
                                printf("O monstro inteligente te pegou!\n");
                                reinicios++;
                                if (reinicios >= 3) {
                                    printf("Reiniciou 3 vezes. Voltando ao menu.\n");
                                    exit(0);
                                }
                                printf("Pressione qualquer tecla para continuar...\n");
                                getch();
                                resetarJogador();
                                return;
                            }
                            mapa[novoY][novoX] = 'V';
                            mapa[y][x] = ' ';
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

        // Move o monstro aleatório 'X'
        moverMonstroAleatorio();
        
        // Move o monstro inteligente 'V'
        moverMonstroInteligente();
        
        Sleep(200);
    }

    return 0;
}
