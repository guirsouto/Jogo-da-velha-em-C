#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//funções
void limparTela();
void exibirMenu();
void exibirRegras();
int jogarPartida();
int jogarContraMaquina();

int main() {
    int opcao;
    int continuarJogando = 1;

    // Seed para a função de geração de números aleatórios
    srand(time(NULL));

    // Exibir menu inicial
    do {
        exibirMenu();
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Jogar contra a máquina
                jogarContraMaquina();
                break;
            case 2:
                // Jogar multiplayer
                jogarPartida();
                break;
            case 3:
                // Exibir regras
                exibirRegras();
                break;
            case 4:
                // Sair do jogo
                continuarJogando = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        // Limpar o teclado
        while (getchar() != '\n');

        // Pausar a tela para visualização
        limparTela();
    } while (continuarJogando);

    return 0;
}

// Implementações das funções
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibirMenu() {
    printf("\n\t Jogo da Velha - Multiplayer \n");
    printf("\t =========================== \n");
    printf("\t 1. Jogar contra a máquina \n");
    printf("\t 2. Jogar multijogador \n");
    printf("\t 3. Exibir regras \n");
    printf("\t 4. Sair do jogo \n");
}

void exibirRegras() {
    printf("\n\t As regras são simples. \n");
    printf("\t Os jogadores alternam entre as peças 0 e X. \n");
    printf("\t O objetivo é conseguir formar uma linha, coluna ou diagonal com suas peças antes do oponente. \n");
    printf("\t Para desistir de sua vez, digite 0 na posição desejada. \n");

    printf("\nPressione Enter para continuar...");
    getchar();  // Aguarda a entrada do usuário
}

int jogarPartida() {
    // Código para o modo multiplayer
    int l, c, opcao = 1, jogadas = 0, ganhou = 0;
    char jogo[3][3];

    for(l = 0; l < 3; l++){
        for(c = 0; c < 3; c++){
            jogo[l][c] = ' ';
        }
    }

    do{
        // limpar tela
        system("clear");

        // imprimir jogo
        printf("\n\n\t 0   1   2\n\n");
        for(l = 0; l < 3; l++){
            for(c = 0; c < 3; c++){
                if(c == 0)
                    printf("\t");
                printf(" %c ", jogo[l][c]);
                if(c < 2)
                    printf("|");
                if(c == 2)
                    printf(" %d", l);
            }
            if(l < 2)
                printf("\n\t-----------");
            printf("\n");
        }

        // jogador 1
        if(jogadas % 2 == 0){
            do{
                printf("\n\nJogador 1: Escolha a linha (0, 1, 2): ");
                scanf("%d", &l);
                printf("Jogador 1: Escolha a coluna (0, 1, 2): ");
                scanf("%d", &c);
            }while(jogo[l][c] != ' ');

            jogo[l][c] = '0';
        }

        // jogador 2
        else{
            do{
                printf("\n\nJogador 2: Escolha a linha (0, 1, 2): ");
                scanf("%d", &l);
                printf("Jogador 2: Escolha a coluna (0, 1, 2): ");
                scanf("%d", &c);
            }while(jogo[l][c] != ' ');

            jogo[l][c] = 'X';
        }

        jogadas++;

        // verificar se alguém ganhou
        if(jogadas > 4){
            // alguém ganhou por linha
            for(l = 0; l < 3; l++){
                if(jogo[l][0] == '0' && jogo[l][1] == '0' && jogo[l][2] == '0'){
                    printf("\nParabens! O jogador 1 venceu por linha!\n");
                    ganhou = 1;
                    break;
                }
                if(jogo[l][0] == 'X' && jogo[l][1] == 'X' && jogo[l][2] == 'X'){
                    printf("\nParabens! O jogador 2 venceu por linha!\n");
                    ganhou = 1;
                    break;
                }
            }

            // alguém ganhou por coluna
            for(c = 0; c < 3; c++){
                if(jogo[0][c] == '0' && jogo[1][c] == '0' && jogo[2][c] == '0'){
                    printf("\nParabens! O jogador 1 venceu por coluna!\n");
                    ganhou = 1;
                    break;
                }
                if(jogo[0][c] == 'X' && jogo[1][c] == 'X' && jogo[2][c] == 'X'){
                    printf("\nParabens! O jogador 2 venceu por coluna!\n");
                    ganhou = 1;
                    break;
                }
            }

            // alguém ganhou na diagonal principal
            if(jogo[0][0] == '0' && jogo[1][1] == '0' && jogo[2][2] == '0'){
                printf("\nParabens! O jogador 1 venceu na diagonal principal!\n");
                ganhou = 1;
            }

            // alguém ganhou na diagonal secundária
            if(jogo[0][2] == '0' && jogo[1][1] == '0' && jogo[2][0] == '0'){
                printf("\nParabens! O jogador 1 venceu na diagonal secundária!\n");
                ganhou = 1;
            }

            // alguém ganhou na diagonal principal
            if(jogo[0][0] == 'X' && jogo[1][1] == 'X' && jogo[2][2] == 'X'){
                printf("\nParabens! O jogador 2 venceu na diagonal principal!\n");
                ganhou = 1;
            }

            // alguém ganhou na diagonal secundária
            if(jogo[0][2] == 'X' && jogo[1][1] == 'X' && jogo[2][0] == 'X'){
                printf("\nParabens! O jogador 2 venceu na diagonal secundária!\n");
                ganhou = 1;
            }
        }

        if(ganhou)
            break;

        printf("\n\nDeseja continuar jogando? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);
    }while(opcao);

    if(!ganhou)
        printf("\n\nJogo empatado! Ninguém ganhou.\n");

    printf("\n\nObrigado por jogar! ");
    return 0;
}

int jogarContraMaquina() {
    // Estrutura de dados da maquina 
    int l, c, opcao = 1, jogadas = 0, ganhou = 0;
    char jogo[3][3];

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            jogo[l][c] = ' ';
        }
    }

    do {
        // Limpar tela
        limparTela();

        // Imprimir jogo
        printf("\n\n\t 0   1   2\n\n");
        for (l = 0; l < 3; l++) {
            for (c = 0; c < 3; c++) {
                if (c == 0)
                    printf("\t");
                printf(" %c ", jogo[l][c]);
                if (c < 2)
                    printf("|");
                if (c == 2)
                    printf(" %d", l);
            }
            if (l < 2)
                printf("\n\t-----------");
            printf("\n");
        }

        // Jogador
        if (jogadas % 2 == 0) {
            do {
                printf("\n\nJogador 1: Escolha a linha (0, 1, 2): ");
                scanf("%d", &l);
                printf("Jogador 1: Escolha a coluna (0, 1, 2): ");
                scanf("%d", &c);
            } while (jogo[l][c] != ' ');
            jogo[l][c] = '0';
        }

        // Máquina
        else {
            do {
                l = rand() % 3;
                c = rand() % 3;
            } while (jogo[l][c] != ' ');

            printf("\n\nA máquina escolheu a linha %d e coluna %d.\n", l, c);
            jogo[l][c] = 'X';
        }

        jogadas++;

        // Verificar se alguém ganhou
        if (jogadas > 4) {
            // Alguém ganhou por linha
            for (l = 0; l < 3; l++) {
                if (jogo[l][0] == '0' && jogo[l][1] == '0' && jogo[l][2] == '0') {
                    printf("\nParabéns! O jogador 1 venceu por linha!\n");
                    ganhou = 1;
                    break;
                }
                if (jogo[l][0] == 'X' && jogo[l][1] == 'X' && jogo[l][2] == 'X') {
                    printf("\nA máquina venceu por linha!\n");
                    ganhou = 1;
                    break;
                }
            }

            // Alguém ganhou por coluna
            for (c = 0; c < 3; c++) {
                if (jogo[0][c] == '0' && jogo[1][c] == '0' && jogo[2][c] == '0') {
                    printf("\nParabéns! O jogador 1 venceu por coluna!\n");
                    ganhou = 1;
                    break;
                }
                if (jogo[0][c] == 'X' && jogo[1][c] == 'X' && jogo[2][c] == 'X') {
                    printf("\nA máquina venceu por coluna!\n");
                    ganhou = 1;
                    break;
                }
            }

            // Alguém ganhou na diagonal principal
            if (jogo[0][0] == '0' && jogo[1][1] == '0' && jogo[2][2] == '0') {
                printf("\nParabéns! O jogador 1 venceu na diagonal principal!\n");
                ganhou = 1;
            }

            // Alguém ganhou na diagonal secundária
            if (jogo[0][2] == '0' && jogo[1][1] == '0' && jogo[2][0] == '0') {
                printf("\nParabéns! O jogador 1 venceu na diagonal secundária!\n");
                ganhou = 1;
            }

            // Alguém ganhou na diagonal principal
            if (jogo[0][0] == 'X' && jogo[1][1] == 'X' && jogo[2][2] == 'X') {
                printf("\nA máquina venceu na diagonal principal!\n");
                ganhou = 1;
            }

            // Alguém ganhou na diagonal secundária
            if (jogo[0][2] == 'X' && jogo[1][1] == 'X' && jogo[2][0] == 'X') {
                printf("\nA máquina venceu na diagonal secundária!\n");
                ganhou = 1;
            }
        }

        if (ganhou)
            break;

        printf("\n\nDeseja continuar jogando? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);
    } while (opcao);

    if (!ganhou)
        printf("\n\nJogo empatado! Ninguém ganhou.\n");

    printf("\n\nObrigado por jogar! ");
    return 0;
}