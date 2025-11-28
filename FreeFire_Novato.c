#include <stdio.h>
#include <stdlib.h>
#include <string.h> //para as funções (strcpy, strcmp)

#define TAM_STRING 30   //tam. máximo de cada string
#define TAM_MAX 10      //tam. máximo de itens na lista

//estrutura que representa a lista
typedef struct {
    char nome[30];
    char tipo [30]; 
    int quantidade;
} item;

// função para limpar o buffer de entrada
void limparBuffer() {      // 'void' - função que não retorna valor
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeritens(item *ptritens, int *cont_atual, const char *texto);

// função principal
int main() {
    item *ptritens; 
    int opcao, cont_atual=0;
    char texto[20];
    
    //alocação de memoria de forma dinâmica.
    ptritens = (item *) malloc(TAM_MAX * sizeof(item));
    //verificação de alocação de memoria.
    if (ptritens == NULL) {
        printf("Erro: Falha ao alocar memoria.");
        return 1;
    } 

    // laço principal do menu
    do {
        printf("=========================================\n");
        printf("MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
        printf("=========================================\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover itens\n");
        printf("3 - Listar itens na Mochila\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------\n");
        printf("\tEscolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();     // Limpa o '/n' deixado pelo scanf.

        // processamento das opções
        switch (opcao) {
            case 1:     // cadastro
                printf("*** CADASTRO DE NOVO ITEM *** \n");

                if (cont_atual < TAM_MAX) {
                    printf("Digite o nome do item: ");
                    fgets(ptritens[cont_atual].nome, TAM_STRING, stdin); //stdin - trata-se do Ponteiro do arquivo de onde a string será lida (nesse caso, leitura do teclado).

                    printf("Digite o tipo: (arma, munição, cura...): ");
                    fgets(ptritens[cont_atual].tipo, TAM_STRING, stdin); //TAM_STRING - número máximo de caracteres a serem lidos.
                  
                    ptritens[cont_atual].nome[strcspn(ptritens[cont_atual].nome, "\n")] = '\0'; // Substitui '\n' pelo terminador nulo '\0'
                    ptritens[cont_atual].tipo[strcspn(ptritens[cont_atual].tipo, "\n")] = '\0'; // strcspn - Recebe duas strings: a primeira é a string onde a pesquisa é realizada, e a segunda é a string que contém os caracteres de "proibição" ou que servem como referência.

                    printf("Digite a quantidade: ");
                    scanf("%d", &ptritens[cont_atual].quantidade);
                    limparBuffer();     // Limpa o '/n' deixado pelo scanf.

                    cont_atual++;

                    printf("\nItem cadastrado com sucesso!\n");

                }else{
                    printf("Mochila cheia! Não é possível cadastrar mais itens.\n");
                }

                printf("Pressione enter para continuar...\n");
                getchar();    
            break;

            case 2: // REMOÇÃO DE ITENS
                printf("*** REMOÇÃO DE ITEM ***\n");
                printf("Digite o item a remover: \n");
                fgets(texto, 20, stdin);
                texto[strcspn(texto, "\n")] = 0;
                removeritens(ptritens, &cont_atual, texto);
                printf("Pressione enter para continuar...\n");
                getchar();

            break;

            case 3: // LISTAGEM DE LIVROS
                printf("*** LISTA DE ITENS NA MOCHILA ***\n");

                if (cont_atual == 0){
                    printf("Nenhum item cadastrado ainda.\n");
                } else {
                    printf("--- Itens na mochila --- : %d de 10\n", cont_atual);
                    printf("NOME, TIPO, QUANTIDADE\n");
                    printf("----------------------------------------\n");
                    for (int i = 0; i < cont_atual; i++) {
                        
                        printf("%s, %s, %d\n", ptritens[i].nome, ptritens[i].tipo, ptritens[i].quantidade);
                    
                    }

                    printf("\n");
                }
                // a pausa é crucial para que o usuário veja a lista antes do proximo loop limpar a tela.
                printf("Pressione enter para continuar...\n");
                getchar(); // Esta função serve para ler um único caractere da entrada padrão (geralmente o teclado) e retorná-lo como um valor inteiro.
                break;
            
            case 0: // SAIR
                printf("\nsaindo do sistema...\n");
            break;
            
            default: // OPÇÃO INVÁLIDA
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione enter para continuar...\n");
                getchar();  //comumente usada em programas C para ler a entrada do usuário, aguardando que o usuário digite algo e pressione Enter
            break;
        }

    } while (opcao !=0);

    return 0;

}

//Para comparar strings, usamos strcmp(string1, string2). Retorna 0 se forem iguais.
//A função percorre os itens em uso na lisa (de 0 até quantidade)
//Essa função retorna 0 se as strings forem idênticas. Se encontrar, guarda a posição (pos) e para o loop.

//definição de função para remover itens.
void removeritens(item *ptritens, int *cont_atual, const char *texto) {
    int i, pos = -1;
    
    if (*cont_atual == 0) {
        printf("Não há itens na mochila!\n");
        return;
    }
    
    for(i = 0; i < *cont_atual; i++) {
    
        if(strcmp(ptritens[i].nome, texto) == 0) {
            pos = i;
            printf("Item removido com sucesso!\n");
            break;
        }        
    }
        if(pos == -1) {
            printf("Erro: O item %s não foi encontrado!\n", texto);
            return;
        }
    // Desloca todos os itens uma posição para trás, cobrindo o item na posição 'pos'
    for(i = pos; i < *cont_atual - 1; i++) {
        // Copia o item da frente (i+1) para a posição atual (i)
        ptritens[i] = ptritens[i + 1];
    }
    
    // Diminui o contador de itens na mochila
    (*cont_atual)--;
}
