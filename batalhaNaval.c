#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para posicionar um navio horizontal
void posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    }
}

// Função para posicionar um navio vertical
void posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para exibir uma matriz de habilidade
void exibirMatriz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar matriz de habilidade tipo "cone"
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= TAM_HABILIDADE/2 - i && j <= TAM_HABILIDADE/2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade tipo "cruz"
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE/2 || j == TAM_HABILIDADE/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade tipo "octaedro"
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - TAM_HABILIDADE/2) + abs(j - TAM_HABILIDADE/2) <= TAM_HABILIDADE/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTabuleiro = origemLinha - offset + i;
            int colunaTabuleiro = origemColuna - offset + j;

            // Verifica se está dentro dos limites do tabuleiro
            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAM_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTabuleiro][colunaTabuleiro] != 3) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    // 1. Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // 2. Posiciona navios
    posicionarNavioHorizontal(tabuleiro, 2, 2); // linha 2, coluna 2
    posicionarNavioVertical(tabuleiro, 5, 7);   // linha 5, coluna 7

    // 3. Cria e aplica habilidade CONE
    printf("Habilidade: CONE\n");
    criarCone(habilidade);
    exibirMatriz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 4, 4);

    // 4. Cria e aplica habilidade CRUZ
    printf("Habilidade: CRUZ\n");
    criarCruz(habilidade);
    exibirMatriz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 7, 2);

    // 5. Cria e aplica habilidade OCTAEDRO
    printf("Habilidade: OCTAEDRO\n");
    criarOctaedro(habilidade);
    exibirMatriz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 6);

    // 6. Exibe o tabuleiro final
    printf("Tabuleiro final:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

