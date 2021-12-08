#include	<stdio.h>
#include	<stdlib.h>
#include	<locale.h>

char jogo[3][3];
int lin, col;

typedef struct{
	int vitoria_x;
	int vitoria_o;
	int empate;
}Num_Vitorias;

// Iniciando a matriz do jogo da velha com ' ' nas posições

void inicializar_jogo(){
	for(lin = 0; lin < 3; lin++){
		for(col = 0; col < 3; col++){
			jogo[lin][col] = ' ';
		}
	}
}

// Imprimindo o jogo da velha na tela

void imprimir_jogo(){
	printf("\n\n\t 0   1   2\n\n");	//colocando os índices colunas
	for(lin = 0; lin < 3; lin++){
		printf("    %d", lin);		// colocando os índices linhas
		for(col = 0; col < 3; col++){
			if(col == 0)	//Esta linha da um espaço no começo do jogo para organizar
				printf("\t");
			printf(" %c ", jogo[lin][col]);
			if(col < 2)
				printf("|");	// colocando "|" nas posições 0 e 1
		}
		printf("\n");
		if(lin < 2)
			printf("\t-----------\n");		// colocando uma linha nas posições 0 e 1
	}
}

// Verificar vitória por linha

int ganhar_por_linha(int lin, char c){
	if(jogo[lin][0] == c && jogo[lin][1] == c && jogo[lin][2] == c)
		return 1;
	else
		return 0;
}

int ganhar_por_linhas(char c){
	int ganhar = 0;
	for(lin = 0; lin < 3; lin++){
		ganhar += ganhar_por_linha(lin, c);
	}
	return ganhar;
}
 
 // Verificar vitória por coluna
 
 int ganhar_por_coluna(int col, char c){
	if(jogo[0][col] == c && jogo[1][col] == c && jogo[2][col] == c)
		return 1;
	else
		return 0;
}
 
 int ganhar_por_colunas(char c){
	int ganhar = 0;
	for(col = 0; col < 3; col++){
		ganhar += ganhar_por_coluna(col, c);
	}
	return ganhar;
}

  // Verificar vitória na diagonal principal
  
  int ganhar_na_diagonal_p(char c){
	if(jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c)
		return 1;
	else
		return 0;
}

// Verificar vitória na diagonal secundaria

int ganhar_na_diagonal_s(char c){
	if(jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c)
		return 1;
	else
		return 0;
}

 // Verificar se a coordenada é válida

int verificar_coordenada(int lin, int col){
	if(lin >= 0 && lin < 3 && col >= 0 && col < 3 && jogo[lin][col] == ' ')
		return 1;
	else
		return 0;
}

void ler_coordenadas(char c){
	int linha, coluna;
	
	printf("\n\n");
	
	printf(" Digite a linha: ");
	scanf("%d", &linha);
	
	printf(" Digite a coluna: ");
	scanf("%d", &coluna);
	
	printf("\n");
	
	while(verificar_coordenada(linha, coluna) == 0){
		printf(" Digite uma coordenada válida para a linha: ");
		scanf("%d", &linha);
	
		printf(" Digite uma coordenada válida para a coluna: ");
		scanf("%d", &coluna);
	}
	
	jogo[linha][coluna] = c;
}

 // Verificar empate
 
int verificar_empate(){
	int empate = 0;
	for(lin = 0; lin < 3; lin++){
		for(col = 0; col < 3; col++){
			if(jogo[lin][col] == ' '){
				if(ganhar_por_linhas('X') == 1 || ganhar_por_colunas('X') == 1 || ganhar_na_diagonal_p('X') == 1 || ganhar_na_diagonal_s('X') == 1){
					empate = empate + 0;
				}
				
				else if(ganhar_por_linhas('O') == 1 || ganhar_por_colunas('O') == 1 || ganhar_na_diagonal_p('O') == 1 || ganhar_na_diagonal_s('O') == 1){
					empate = empate + 0;
				}
				else{
					empate++;
				}
			}
		}
	}
	return empate;
}

void jogar(){
	int rodada = 1, vitoria_X = 0, vitoria_O = 0;
	
	do{
		imprimir_jogo();
	
		if (rodada == 1){
			printf("\n\n    Vez do jogador 1\n");
			ler_coordenadas('X');
			rodada++;
			vitoria_X += ganhar_por_linhas('X');
			vitoria_X += ganhar_por_colunas('X');
			vitoria_X += ganhar_na_diagonal_p('X');
			vitoria_X += ganhar_na_diagonal_s('X');
		}
		else{
			printf("\n\n    Vez do jogador 2\n");
			ler_coordenadas('O');
			rodada = 1;
			vitoria_O += ganhar_por_linhas('O');
			vitoria_O += ganhar_por_colunas('O');
			vitoria_O += ganhar_na_diagonal_p('O');
			vitoria_O += ganhar_na_diagonal_s('O');
		}
		
		system("cls");
		
	}while(vitoria_X == 0 && vitoria_O == 0 && verificar_empate() > 0);
	
	imprimir_jogo();
	
	if(verificar_empate() == 0 && vitoria_X == 0 && vitoria_O == 0)
		printf("\n\n O Jogo terminou em empate");
	
	else if(vitoria_O == 1)
		printf("\n\n O Jogador 2 venceu");
	
	else
		printf("\n\n O Jogador 1 venceu");
}


void menu_jogo(){
	inicializar_jogo();
	fflush(stdin);
	int opcao;
    system("cls");
    printf("\t\t\t\t>>>Menu Principal<<<\t\t\t\t\n\n");
    printf("[1] - JOGAR \n[2] - RANKINGS \n[3] - CRÉDITOS \n[4] - SAIR\n\nDigite a opção que deseja efetuar: ");
    opcao = getchar();
    switch(opcao){
	    case '1':
	        system("cls");
	        jogar();
	        break;
	    case '2':
	        system("cls");
	        printf("\t\t\t\t>>>Ranking<<<\n\n\n");
	        
	        FILE *arq;
  			char Linha[100];
  			char *result;
  			int i;
  			
  			arq = fopen("ranking.txt", "rt");
  			
  			for (i = 1; i < 4; i++){
  			result = fgets(Linha, 100, arq);
				if(result){
					if(i < 3)
						printf("O número de vitórias do jogador [%d] é: %s", i, Linha);
				
					if(i == 3){
						printf("\nO Número de empates é: %s", Linha);
						break;
					}
				}
			}
  			
  			fclose(arq);
	        break;
	    case '3':
	        system("cls");
	        printf("\t\t\t\t>>>Créditos<<<\n\n");
	        printf("Arthur Lacerda\n");
	        printf("Lucas Montenegro Nunes\n");
	        printf("Luiz Felipe Vilhena\n");
	        printf("Lailton Abdon\n");
	        break;
	    case '4':
        	system("cls");
        		FILE *limpar;
        		limpar = fopen("ranking.txt", "w");
				fclose(limpar);
       			exit(0);
	    default:
	        printf("\nVocê deve escolher uma opção válida\n");
	        printf("Pressione qualquer tecla para voltar ao menu\n");
	        system("pause");
	        break;
    }
}

int main(){
	setlocale(0, "Portuguese");
	
	char op;
	FILE *pont_arq;
	Num_Vitorias	result;
	
	pont_arq = fopen("ranking.txt", "w+b");
	fprintf(pont_arq, "%d\n%d\n%d", result.vitoria_x = 0, result.vitoria_o = 0, result.empate = 0);
	fclose(pont_arq);
	
	while(1){
		menu_jogo();
		
		if(ganhar_por_linhas('X') == 1 || ganhar_por_colunas('X') == 1 || ganhar_na_diagonal_p('X') == 1 || ganhar_na_diagonal_s('X') == 1){
			result.vitoria_x++;
		}
			
		if(ganhar_por_linhas('O') == 1 || ganhar_por_colunas('O') == 1 || ganhar_na_diagonal_p('O') == 1 || ganhar_na_diagonal_s('O') == 1){
			result.vitoria_o++;
		}
		
		if(verificar_empate() == 0){
			if(ganhar_por_linhas('X') == 1 || ganhar_por_colunas('X') == 1 || ganhar_na_diagonal_p('X') == 1 || ganhar_na_diagonal_s('X') == 1){
				result.empate = result.empate + 0;
			}
			
			else if(ganhar_por_linhas('O') == 1 || ganhar_por_colunas('O') == 1 || ganhar_na_diagonal_p('O') == 1 || ganhar_na_diagonal_s('O') == 1){
				result.empate = result.empate + 0;
			}
			
			else{
				result.empate++;
			}
		}
		
		fflush(stdin);
		
		pont_arq = fopen("ranking.txt", "r+b");
	
		fprintf(pont_arq, "%d\n%d\n%d", result.vitoria_x, result.vitoria_o, result.empate);
	
		fclose(pont_arq);
		
		printf("\n\nDigite [S] para voltar ao menu principal: ");
		op = getchar();
		
		if(op != 'S' && op != 's'){
			exit(0);
		}
	}
	return 0;
}
