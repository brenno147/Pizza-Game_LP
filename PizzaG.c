#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

void game_menu();
void ranking_menu(); 
void print_ranking();
void vs_ia_menu();
void vs_ia();
void creditos();
int casa_Repetida();
int entregas_Feitas();

//Estrutura Jogador com nome, Pontuação e a posição atual do jogador no jogo.
typedef struct{
	char nome[20];
	int distancia;
	int posicao;
	int tempo;
}Player;

void main()
{
	setlocale(LC_ALL,"");

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
  		ranking_menu();
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
	printf("1 - Modo VS IA\n2 - Modo Contra o tempo\n3 - Modo IA\n4 - Tutorial\n5 - Voltar\n");
	scanf("%d", &op);
	switch(op) {
		case 1:
			vs_ia_menu();
			goto inicio;
		case 2:

			goto inicio;
		case 3:
			goto inicio;
		case 4:
			goto inicio;
		case 5:
			break;
		default:
			goto inicio;
	}
}

void ranking_menu(){
	int op;

	inicio:
	system("cls");
	printf("1 - Ranking facil\n2 - Ranking medio\n3 - Ranking dificil\n");
	scanf("%d", &op);
	switch(op){
		case 1:
			print_ranking("Rankings/records_facil.txt");
			break;
		case 2:
			print_ranking("Rankings/records_medio.txt");
			break;
		case 3:
			print_ranking("Rankings/record_dificil.txt");
			break;
		default:
			goto inicio;
	}
}

void print_ranking(char filename[50]){

	system("cls");

	FILE *fp;
	fp = fopen(filename, "r");

	char ranking_names[10][20];
	int ranking_times[10];

	for(int i = 0; i < 10; i++){
		fscanf(fp, "%19s", ranking_names[i]);
		fscanf(fp, "%i", &ranking_times[i]);
	}

	for(int i = 0; i < 10; i++){
		printf("%s terminou o desafio em %i segundos\n", ranking_names[i], ranking_times[i]);
	}

	system("pause");

	fclose(fp);
}

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
	new_player.distancia = 0;
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
	int escolha;

	//Laço que expressa a quantidade de jogadas que o usuário irá fazer.
	for(int i = 0; i < nodes; i++){
		
		inicio:
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

		scanf("%i", &escolha);//Escolha da proxima posição

		//Teste da escolha
		if(casa_Repetida(escolha, i, visitados)){
			if(!entregas_Feitas(nodes, visitados)){
				printf("Voce nao pode ir numa casa ja visitada\n\n");
				system("pause");
				goto inicio;
			} else if (escolha != 1){
				printf("Voce deve voltar para onde comecou\n\n");
				system("pause");
				goto inicio;
			}
		}

		new_player.distancia += paths[new_player.posicao - 1][escolha - 1];
		new_player.posicao = escolha;//Atualização da posição

		printf("\n\n");
		system("pause");
	}

	system("cls");
	printf("Parabens voce terminou percorrendo %i km", new_player.distancia);
	system("pause");

	//time_t time_final = time(NULL);

	//printf("%.f", difftime(time_final, time_start));

	fclose(fp);
}

//Função que verifica se o usuário está indo em uma casa já visitada
int casa_Repetida(int escolha, int posicao, int casas_visitadas[]){

	for(int i = 0; i <= posicao; i++){
		if(casas_visitadas[i] == escolha){
			return 1;
		}
	}
	return 0;
}

int entregas_Feitas(int nodes, int casas_visitadas[]){

	for(int i = 1; i <= nodes; i++){

		int entregue = 0;

		for(int j = 0; j < nodes; j++){

			if(casas_visitadas[j] == i){
				entregue = 1;
			}
		}

		if(!entregue){
			return 0;
		}
	}
	return 1;
}