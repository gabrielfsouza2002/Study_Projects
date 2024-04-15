#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Pp 50
#define Pd 1-Pp
#define Pe 30
#define MAXcombustivel 3
#define MAXtempoVOO 3

#define prioridade_max 3
#define prioridade_med 2
#define prioridade_min 1
#define sem_prioridade 0

typedef struct avioes {

  char codigo [4];
  int status_pous_ou_decol;
  int prioridade;
  int combustivel;
  int tempo_voo;
  int tempo_voo_limite;
  char ID[6];

  
} aviaoo;

typedef aviaoo *item;

// definição da estrutura de nó da lista ligada
struct Node {
    item aviao;
    struct Node* next;
};

// definição da estrutura da fila que contém o primeiro e o último nó da lista ligada
struct Fila {
    struct Node* front;
    struct Node* rear;
};

// função para criar um novo nó com um valor especificado
struct Node* newNode(item aviao) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->aviao = aviao;
    node->next = NULL;
    return node;
}

// função para criar uma nova fila vazia
struct Fila* CriarFila() {
    struct Fila* q = (struct Fila*)malloc(sizeof(struct Fila));
    q->front = q->rear = NULL;
    return q;
}

// função para verificar se a fila está vazia
int isEmpty(struct Fila* q) {
    return (q->front == NULL);
}

// função para adicionar um elemento no final da fila
void InsereNaFila(struct Fila* q, item aviao) {
    struct Node* node = newNode(aviao);

    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }

    q->rear->next = node;
    q->rear = node;
}

// função para remover o elemento no início da fila
item RemoveDaFila(struct Fila* q) {

    struct Node* temp = q->front;
    item aviao = temp->aviao;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);

    return aviao;
}

int size(struct Fila* q) {
    int count = 0;

    struct Node* current = q->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

// função para exibir os elementos da fila
void display(struct Fila* q) {
    if (isEmpty(q)) {
        printf("Fila vazia!\n");
        return;
    }

    struct Node* current = q->front;

    while (current != NULL) {
        printf("\n%s-> Prioridade:%d Combustivel:%d TempoDeVoo:%d StatusPousDcol:%d ",current->aviao->ID ,current->aviao->prioridade,current->aviao->combustivel,current->aviao->tempo_voo,current->aviao->status_pous_ou_decol);
        current = current->next;
    }

    printf("\n");
}
/*insere elemento na fia em uma certa posi;'ao position*/
void insertAtPosition(struct Fila* q, item aviao, int position) {
    if (position == 1) {
        struct Node* node = newNode(aviao);
        node->next = q->front;
        q->front = node;
        if (q->rear == NULL) {
            q->rear = node;
        }
        return;
    }

    struct Node* current = q->front;
    int i = 1;

    while (current != NULL && i < position - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Posição inválida!\n");
        return;
    }

    struct Node* node = newNode(aviao);
    node->next = current->next;
    current->next = node;

    if (node->next == NULL) {
        q->rear = node;
    }
}

void removeFromPosition(struct Fila* q, int position) {
    if (q->front == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    if (position == 1) {
        struct Node* node = q->front;
        q->front = node->next;
        free(node);
        if (q->front == NULL) {
            q->rear = NULL;
        }
        return;
    }

    struct Node* current = q->front;
    int i = 1;

    while (current != NULL && i < position - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Posição inválida!\n");
        return;
    }

    struct Node* node = current->next;
    current->next = node->next;
    free(node);

    if (current->next == NULL) {
        q->rear = current;
    }
}

int rand_uniform(int min, int max) {
    return rand() % (max - min + 1) + min;
}

item NovoAviao() {
    int randowP = rand_uniform(0, 100);
    int randowC = rand_uniform(1, MAXcombustivel);
    int randowV = rand_uniform(1, MAXtempoVOO);
    int randowE = randowP;
    item aviao = malloc(sizeof(struct avioes));

    aviao->combustivel = randowC;
    aviao->tempo_voo_limite = randowV;
    aviao->tempo_voo = 0;
    aviao->prioridade = sem_prioridade;
  

    if (randowP <= Pp) {
        aviao->status_pous_ou_decol = 0; /*0 = pouso*/
    } else if (randowP > Pd) {
        aviao->status_pous_ou_decol = 1; /*1 = decolagem*/
    }

    if (aviao->combustivel == 0) {
        aviao->prioridade = prioridade_max;
    }
    if (randowE <= Pe) {
        aviao->prioridade = prioridade_med;
    }

    /*Inserindo Identificacao do aviao*/
    const char* letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    const char* digits = "0123456789"; 
    
 
    for (int i = 0; i < 2; i++) {
        int num = rand_uniform(0, 25);
        aviao->ID[i] = letters[num]; 
    }
    for (int i = 2; i < 5; i++) {
        int num = rand_uniform(0, 9);
        aviao->ID[i] = digits[num]; 
    }
    aviao->ID[5] = '\0'; 

    /*Inserindo codigo de voo*/
    for (int i = 0; i < 3; i++) {
        int num = rand_uniform(0, 25);
        aviao->codigo[i] = letters[num];
    }
    aviao->codigo[3] = '\0';

    return aviao;
}

void empilha_com_prioridade(struct Fila* q, item aviao){

    struct Node* current = q->front;

    int j, cont;
    cont = 0;

    for (j = 0; current != NULL && j < size(q); j++) {

        if(aviao->prioridade <= current->aviao->prioridade)
            cont++;
        else
            break;

        current = current->next;
    }

    insertAtPosition(q, aviao, cont+1);
}


int main() {

    struct Fila* q = CriarFila();
    item novoAviao, aviaoRemovido;
    int T, K, i, j, cont1, cont2, cont3, cont4, cont5;
    int temp_pou, temp_del;
    int pista_interditada = 0;
    int flag1, flag2, flag3;
    double med_temp_pouso;
    double med_temp_decol;
    double med_combustivel;
    int soma_combustivel;
    int pista1, pista2, pista3;

    med_combustivel = 0;
    soma_combustivel = 0;

    pista1 = 0;
    pista2 = 0;
    pista3 = 0;

    printf("\nDigite a quantidade de unidades de tempo: ");
    scanf("%d", &T);

    printf("\nDigite a quantidade de avioes gerados por unidade de tempo: ");
    scanf("%d", &K);

    while (T != 0){

        printf("\n");
        /*Criando  K novos avioes e colocando na fila*/
        for (i = 0; i < K; i++){

            novoAviao = NovoAviao();
            
            empilha_com_prioridade(q,novoAviao);

        }
            printf("\n\n");

        /*exibir avioes esperando*/
        struct Node* current = q->front;
        printf("\nAvioes esperando para pousar e decolar (ID): ");
        display(q);

        temp_pou = 0;
        temp_del = 0;
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        cont4 = 0;
        cont5 = 0;

        /*atualizando informacoes dos avioes e coletando dados de cada aviao da fila*/
        current = q->front;
        for (j = 0; current != NULL && j < size(q); j++) {

            if(current->aviao->combustivel == -1){ /*se o aviao estiver com -1 de combustivel, significa que ele foi desviado para o areporto mais proximo, ou seja, eliminado da fila.*/
                removeFromPosition(q,cont5+1);
                current = q->front;
            }
            if(current->aviao->combustivel == 0){ /*se um aviao tem 0 de combustivel, ele ganha nivel de prioridade maximo para pousar*/
                current->aviao->prioridade == 3;
            }
            if (current->aviao->status_pous_ou_decol == 0){ /*conta tempo de voo dos avioes que pousaram*/
                temp_pou += current->aviao->tempo_voo;
                cont1++;
            }
            else{
                temp_del += current->aviao->tempo_voo; /*conta tempo de voo dos avioes que decolaram*/
                cont2++;
            }

            /*quantidade de avioes em caso de emergencia*/
            if (current->aviao->prioridade == 2) /*conta quantos avioes da fila estao em caso de mergencia*/
                cont3++;


            if (current->aviao->tempo_voo >= current->aviao->tempo_voo_limite + current->aviao->tempo_voo_limite * 0.1) /*se um aviao ja esta com mais de 10% do tempo de seu voo, ele ganha nivel de prioridade 1*/
                current->aviao->prioridade = prioridade_min;

            current->aviao->tempo_voo++; /*atualiza tempo*/
            current->aviao->combustivel--; /*atualiza combustivel*/
            
            current = current->next;
            cont5++;/*auxiliar que ajuda remover aviao com -1 de combustivel*/
    }

        if (cont1 != 0)
            med_temp_pouso = (double)temp_pou/cont1;
        
        if (cont2 != 0)
            med_temp_decol = (double)temp_del/cont2;

        printf("\nTempo medio de espera para pouso: %f\n", med_temp_pouso);  
        printf("Tempo medio de espera para decol: %f\n", med_temp_decol);

        cont1 = 0;
        cont2 = 0;
        flag1 = 0;
        flag2 = 0;
        flag3 = 0;

        soma_combustivel = 0;
        /*sistema de pistas: desempilha da fila at[e que as pistas estejam ocupadas. Dado que a fila esta ordenada por prioridade, esse la;o funciona]*/
        while (pista1 == 0 || pista2 == 0){

            aviaoRemovido = RemoveDaFila(q);
            if (aviaoRemovido->status_pous_ou_decol == 0){
                cont2++;
                soma_combustivel += aviaoRemovido->combustivel+1;
                
            }
            if ((aviaoRemovido->prioridade == 2 || aviaoRemovido->status_pous_ou_decol == 1) && flag1 == 0){
                pista3 = 1;
                flag1 = 1;
                continue;
            }
            if (aviaoRemovido != NULL && flag2 == 0){
                pista1 = 1;
                flag2 = 1;
                continue;
            }
            
            if(aviaoRemovido != NULL && flag3 == 0){
                pista2 = 1;
                flag3 = 1;
                continue;
            }

        }

        if (cont2 != 0)
            med_combustivel += (double)soma_combustivel/cont2;
        /*deixa a pista unutilizada por 2 unidades de tempo*/
        pista_interditada++;
        if (pista_interditada == 3){
            pista1 = 0;
            pista2 = 0;
            pista3 = 0;
            pista_interditada = 0;
        }

        printf("Media de combustivel dos avioes que pousaram: %f\n", (double) med_combustivel); 
        printf("Quantidade de avioes em caso de emergencia: %d\n", cont3); 

        T--;

    }
    return 0;
}

