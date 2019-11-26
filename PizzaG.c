#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void game_menu(); 
void vs_ia_menu();
void vs_ia();
//void ranking();
void creditos();

//Estrutura Jogador com nome, Pontuação e a posição atual do jogador no jogo.
typedef struct{
	char nome[20];
	int pontuacao;
	int posicao;
}Player;

void main()
{
    int opcao;

    //Menu inicial do jogo 

    inicio:
    system("cls");
    system("color 0F");

    printf("1 - JOGAR \n2 - RANKINGS \n3 - CREDITOS \n4 - SAIR\n");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
        game_menu();
        goto inicio;
    case 2:
        system("cls");
  
        goto inicio;
    case 3:
        system("cls");
        creditos();
        goto inicio;
    case 4:
        system("cls");
        printf("Voce pediu para sair, precione qualquer tecla para continuar\n");
        break;
    default:
        printf("Voce deve escolher uma opcao valida\n");
        printf("Precione qualquer tecla para voltar ao menu\n");
        system("pause");
        goto inicio;
    }
}

void game_menu(){
	int op;

	//Menu em que o usuário escolhe o modo de jogo

	inicio:
	system("cls");
	printf("1 - Modo VS IA \n2 - Modo Contra o tempo\n3- Voltar\n");
	scanf("%d", &op);
	switch(op) {
		case 1:
			vs_ia_menu();
			break;
		case 2:

			break;
		case 3:
			break;
		default:
			goto inicio;
	}
}



/*void ranking(){
	printf("O ranking só vale para o modo contra o tempo\n\n");

	FILE *fp;
	fp = fopen("records.txt", "r");

	fclose(fp);
}*/


void creditos(){

	//Lê o arquivo Creditos.txt e mostra na tela quando o usuário escolhe a opção 3 do menu inicial

	FILE *fp;
	fp = fopen("Creditos.txt", "r");
	
	char creditos[4][30];

	for(int i = 0; i < 4; i++){
		fgets(creditos[i], 30, fp);
	}

	for(int i = 0; i < 4; i++){
		printf("%s", creditos[i]);
	}

	printf("\n\n");

	printf(":)");

	printf("\n\n");

	fclose(fp);
}

void vs_ia_menu(){
	int df;

	//Menu em que o usuário escolhe a dificuldade do jogo contra a IA.

	inicio:
	system("cls");
	printf("Escolha a dificuldade: \n1 - Facil (IA facil, Mapa Pequeno) \n2 - Medio (IA mediana, Mapa Medio) \n3 - Dificil (IA dificil, Mapa Grande)\n");
	scanf("%d", &df);
	switch(df){
		case 1:
			vs_ia("entregador de pizza/cidade_10.txt");
			break;
		case 2:
			vs_ia("entregador de pizza/cidade_25.txt");
			break;
		case 3:
			vs_ia("entregador de pizza/cidade_50.txt");
			break;
		default:
			goto inicio;
	}
}

//Recebe o caminho do arquivo dependendo da dificuldade escolhida 
void vs_ia(char filename[50]){
	system("cls");

	//Declara um novo Jogador e seta a posição inicial, no caso a casa 1, e a pontuação inicial
	Player new_player;
	new_player.pontuacao = 0;
	new_player.posicao = 1;

	printf("Digite seu nome:\n");

	scanf("%19s", new_player.nome);

	//Abre os arquivos de distancia na pasta "entregador de pizza"
	FILE *fp;
	int nodes;
	
	fp = fopen(filename, "r");
	fscanf(fp, "%i", &nodes); //Recebe a quantidade de casas a serem percorridas no trajeto do jogo.

	int paths[nodes][nodes]; //Matriz quadrada ixj em que cada elemento é a distancia da casa i para a casa j(Todas as casas são conectadas) 

	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			fscanf(fp, "%i", &paths[i][j]);
		}
	}

	int visitados[nodes]; //Vetor com todas as casas que já foram visitadas

	//Laço que expressa a quantidade de jogadas que o usuário irá fazer.
	for(int i = 0; i < nodes; i++){
		
		system("cls");

		//Laço que printa a coluna com a distancia de todas as casas para a posiçao em que o Jogador se encontra.
		for(int j = 0; j < nodes; j++){
			printf("%i - %i", j+1, paths[j][new_player.posicao - 1]);
			printf("\n");
		}

		visitados[i] = new_player.posicao;//O vetor visitados recebe a posição em que o Jogador se encontra.

		printf("\n\n");

		//Laço que printa o caminho feito até agora pelo Jogador
		for(int k = 0; k <= i; k++){
			printf("%i -> ", visitados[k]);
		}

		scanf("%i", &new_player.posicao);//Atualização da posição(Escolha da próxima casa a ser visitada) *Alterar futuramente

		printf("\n\n");

		system("pause");
	}

	//time_t time_final = time(NULL);

	//printf("%.f", difftime(time_final, time_start));

	fclose(fp);
}

