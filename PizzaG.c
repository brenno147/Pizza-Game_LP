#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#define Pausar system("pause");

void game_menu();
void ranking_menu(); 
void print_ranking();
void vs_time_menu();
void vs_time();
void creditos();
int casa_Repetida();
int entregas_Feitas();
int menor_Caminho();
void ia();
void ia_menu();
void tutorial();
void att_ranking();

//Estrutura Jogador com nome, pontuação, posição atual do jogador e tempo para concluir o jogo.
typedef struct{
	char nome[20];
	int distancia;
	int posicao;
	float tempo;
}Player;

void main()
{
	setlocale(LC_ALL,"");

	int game = 1;

    int opcao;

    //Menu inicial do jogo 

    while(game){
	    system("cls");
	    system("color 0F");

	    printf("================================ENTREGADOR DE PIZZA=======================================\n");
	    printf("\n\n1 - JOGAR \n2 - RANKINGS \n3 - CREDITOS \n4 - SAIR\n");
	    scanf("%d", &opcao);
	    switch (opcao) {
	    case 1:
	        game_menu();
	        break;
	    case 2:
	  		ranking_menu();
	        break;
	    case 3:
	        system("cls");
	        creditos();
	        break;
	    case 4:
	        system("cls");
	        printf("Voce pediu para sair, precione qualquer tecla para continuar\n");
	        game = 0;
	        break;
	    default:
	        printf("Voce deve escolher uma opcao valida\n");
	        Pausar;
		}    
    }
}

void game_menu(){
	int op;

	int play_menu = 1;

	//Menu em que o usuário escolhe o modo de jogo
	while(play_menu){
		system("cls");
		printf("1 - Modo Contra o tempo\n2 - Modo IA\n3 - Tutorial\n4 - Voltar\n");
		scanf("%d", &op);
		switch(op) {
			case 1:
				vs_time_menu();
				break;
			case 2:
				ia_menu();
				break;
			case 3:
				tutorial();
				break;
			case 4:
				play_menu = 0;
				continue;
			default:
				break;
		}
	}
}

void ranking_menu(){
	int op;

	//Menu de escolha de qual dos rankings vai mostrar que depende da dificuldade jogada

	system("cls");
	printf("1 - Ranking facil\n2 - Ranking medio\n3 - Ranking dificil\n");
	scanf("%i", &op);
	switch(op){
		case 1:
			print_ranking("rankings/records_1.txt");
			break;
		case 2:
			print_ranking("rankings/records_2.txt");
			break;
		case 3:
			print_ranking("rankings/records_3.txt");
			break;
		default:
			break;
	}
}

void print_ranking(char filename[50]){

	//Leitura do arquivo de rankings e printa o nome e tempo de cada um dos 10 Jogadores

	system("cls");

	FILE *fp;
	fp = fopen(filename, "r");

	Player ranking[10];

	for(int i = 0; i < 10; i++){
		fscanf(fp, "%19s %i %f", ranking[i].nome, &ranking[i].distancia, &ranking[i].tempo);
	}

	for(int i = 0; i < 10; i++){
		printf("%s percorreu %i km em %.1f segundos\n", ranking[i].nome, ranking[i].distancia, ranking[i].tempo);
	}

	Pausar;

	fclose(fp);
}

void creditos(){

	//Lê o arquivo Creditos.txt e mostra na tela quando o usuário escolhe a opção 3 do menu inicial

	FILE *fp;
	fp = fopen("Creditos.txt", "r");
	
	char creditos[30];
	
	while(fgets(creditos, 30, fp) != NULL){
		printf("%s", creditos);
	}

	printf("\n\n :) \n\n");

	Pausar;

	fclose(fp);
}

void vs_time_menu(){
	int dif;

	//Menu em que o usuário escolhe a dificuldade do jogo contra o tempo.

	system("cls");
	printf("Escolha a dificuldade: \n1 - Facil (Mapa Pequeno) \n2 - Medio (Mapa Medio) \n3 - Dificil (Mapa Grande)\n");
	scanf("%d", &dif);
	switch(dif){
		case 1:
			vs_time("entregador de pizza/cidade_10.txt", 1);
			break;
		case 2:
			vs_time("entregador de pizza/cidade_25.txt", 2);
			break;
		case 3:
			vs_time("entregador de pizza/cidade_50.txt", 3);
			break;
		default:
			break;
	}
}


//Recebe o caminho do arquivo dependendo da dificuldade escolhida 
void vs_time(char filename[50], int dif){
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
	int escolha;//Variavel da escolha da proxima casa a ser visitada feita pelo jogador

	time_t start = time(NULL);

	//Laço que expressa a quantidade de jogadas que o usuário irá fazer.
	for(int i = 0; i < nodes; i++){
		int next_Casa = 0;

		while(!next_Casa){
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

			//Verificar se a escolha é valida
			if(escolha < 1 || escolha > nodes){
				printf("\n\nValor invalido\n\n");
				Pausar;
				continue;
			}

			//Se eu estiver visitando uma casa que ja esteja no vetor visitados
			if(casa_Repetida(escolha, i, visitados)){
				//Se nem todas as casas tiverem sido percorridas
				if(!entregas_Feitas(nodes, visitados)){
					printf("Voce nao pode ir numa casa ja visitada\n\n");
					Pausar;
					continue;
				}
				//Se todas as casas tiverem sido percorridas mas a casa escolhida não for a inicial 
				else if (escolha != 1){
					printf("Voce deve voltar para onde comecou\n\n");
					Pausar;
					continue;
				}
			}

			new_player.distancia += paths[new_player.posicao - 1][escolha - 1];//Atualização da distancia percorrida pelo Jogador
			new_player.posicao = escolha;//Atualização da posição

			printf("\n\n");
			Pausar;
			next_Casa = 1;
		}
	}

	time_t end = time(NULL);
	new_player.tempo = difftime(end, start);

	system("cls");
	printf("Parabens voce terminou percorrendo %i km em %.1f segundos\n", new_player.distancia, new_player.tempo);// Fim do jogo
	Pausar;

	att_ranking(new_player, dif);

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

//Função que percorre todo o vetor casas_visitadas e verifica se todas as casas foram visitadas
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
void ia_menu(){
	int dif;

	//Menu em que o usuário escolhe o mapa a ser percorrido pela IA.

	system("cls");
	printf("Escolha o mapa: \n1 - Mapa Pequeno \n2 - Mapa Medio \n3 - Mapa Grande\n");
	scanf("%d", &dif);
	switch(dif){
		case 1:
			ia("entregador de pizza/cidade_10.txt");
			break;
		case 2:
			ia("entregador de pizza/cidade_25.txt");
			break;
		case 3:
			ia("entregador de pizza/cidade_50.txt");
			break;
		default:
			break;
	}
}

//Função que retorna o menor elemento de um vetor caso o elemento não leve no vetor já visitado
int menor_Caminho(int v[], int visitados[], int nodes){
	int menor = 999;//Variável que é atualizada para achar o menor valor no vetor
	int menor_index = 0;//Variável para achar o índice do menor valor no vetor
	for(int i = 0; i < nodes; i++){
		if(v[i] <= menor && !casa_Repetida(i, nodes, visitados)){
			menor = v[i];//Atualização do menor valor
			menor_index = i;//Atualização do indice do menor valor
		}
	}
	return menor_index;
}

//A função mostra um vetor das casas percorridas pela IA e depois de acordo com o nivel da IA o vetor será embaralhado.
void ia(char filename[50]){
	//Leitura normal do arquivo especificado anteriormente
	system("cls");

	FILE *fp;
	fp = fopen(filename, "r");

	int nodes;

	fscanf(fp, "%d", &nodes);

	int matriz[nodes][nodes];

	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			fscanf(fp, "%d", &matriz[i][j]);
		}
	}

	int visitados[nodes];//Vetor das casas visitadas pela IA
	visitados[0] = 0;//Posição inicial

	for(int i = 0; i < nodes; i++){
		visitados[i+1] = menor_Caminho(matriz[visitados[i]], visitados, nodes);//O proximo valor a ser visitado será o indice do menor valor encontrado pela função
	}

	//Variáveis de auxilio;
	int dif;
	int aux;
	int k;
	srand(time(NULL));

	printf("Escolha o nivel da IA:\n 1 - Alta possibilidade de erro\n2 - Media possibilidade de erro\n3 - Baixa possibilidade de erro");
	scanf("%i", &dif);

	system("cls");

	//Print do melhor caminho possivel da IA
	printf("Melhor caminho:\n");

	for(int i = 0; i < nodes; i++){
		printf("%d->", visitados[i] + 1);
	}
	printf("1\n");

	//Embaralhamento do vetor visitados dependendo do nivel da IA escolhido pelo usuário
	if(dif == 1){
		for(int i = 1; i < nodes; i++){
			k = 1 + rand() % (nodes - 2);
			if(rand() % 2 == 0){
				aux = visitados [i];
				visitados[i] = visitados[k];
				visitados[k] = aux;
			}
		}
	} else if(dif == 2){
		for(int i = 1; i < nodes; i++){
			k = 1 + rand() % (nodes - 2);
			if(rand() % 4 == 0){
				aux = visitados [i];
				visitados[i] = visitados[k];
				visitados[k] = aux;
			}
		}
	} else if(dif == 3){
		for(int i = 1; i < nodes; i++){
			k = 1 + rand() % (nodes - 2);
			if(rand() % 100 < 5){
				aux = visitados [i];
				visitados[i] = visitados[k];
				visitados[k] = aux;
			}
		}
	}

	printf("\n\n");

	//Caminho relizado pela IA
	printf("Caminho feito pela IA:\n");

	for(int i = 0; i < nodes; i++){
		printf("%d->", visitados[i] + 1);
	}
	printf("1\n");
	Pausar;
	fclose(fp);
}

void tutorial(){
	system("cls");
	printf("Quando iniciar o jogo aparecera uma coluna com diversos valores do tipo:\n1-x\n2-x\n3-x\n4-x\n5-x\n...");
	printf("\nCada valor x representa a distancia da casa que voce se encontra para a casa representada pelo numero ao lado\n");
	printf("\nE embaixo aparecera um valor: x->\n");
	printf("Esse valor representa a casa que voce se encontra e o usuario podera inserir para que casa ir\n\n");
	printf("O objetivo do jogador e percorrer todas as casas na menor distancia e menor tempo possivel\n");
}

void att_ranking(Player p, int dif){
	FILE *fp;

	int pos = -1;

	if(dif == 1)
		fp = fopen("Rankings/records_1.txt", "r");
	else if(dif == 2)
		fp = fopen("Rankings/records_2.txt", "r");
	else if(dif == 3)
		fp = fopen("Rankings/records_2.txt", "r");

	Player ranking[10];

	for(int i = 0; i < 10; i++){
		fscanf(fp, "%19s %i %f", ranking[i].nome, &ranking[i].distancia, &ranking[i]. tempo);
	}

	for(int i = 9; i >= 0; i--){
		if(p.distancia < ranking[i].distancia){
			pos = i;
		}
		else if(p.distancia == ranking[i].distancia){
			if(p.tempo < ranking[i].tempo){
				pos = i;
			}
		}
	}

	if(pos >= 0){
		for(int i = 9; i > pos; i--){
			strcpy(ranking[i].nome, ranking[i-1].nome);
			ranking[i].distancia = ranking[i-1].distancia;
			ranking[i].tempo = ranking[i-1].tempo;
		}
		strcpy(ranking[pos].nome, p.nome);
		ranking[pos].distancia = p.distancia;
		ranking[pos].tempo = p.tempo;
	}

	fclose(fp);

	FILE *new;

	if(dif == 1)
		new = fopen("Rankings/records_1.txt", "w+");
	else if(dif == 2)
		new = fopen("Rankings/records_2.txt", "w+");
	else if(dif == 3)
		new = fopen("Rankings/records_2.txt", "w+");

	for(int i = 0; i < 10; i++){
		fprintf(new, "%s %i %.0f\n", ranking[i].nome, ranking[i].distancia, ranking[i].tempo);
	}

	fclose(new);
}