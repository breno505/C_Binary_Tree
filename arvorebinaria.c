// Biblioteca para trabalhar com numeros padronizados
#include <stdint.h>
// Biblioteca para o padrão de entrada e saida
#include <stdio.h>
// Biblioteca para trabalhar com string
#include <string.h>
// Biblioteca para alocação de memória
#include <stdlib.h>

// Definindo a estrutura dos nós
typedef struct node {
    char* name;
    char* type;
    int size, order;
    struct node* left;
    struct node* right;
} node;

// função para criar um novo nó
node* new_node(char* nome, char* tipo, int tamanho, int ordem) {
    node* novo_no = (node*)malloc(sizeof(node));
    novo_no->name = strdup(nome);
    novo_no->type = strdup(tipo);
    novo_no->size = tamanho;
    novo_no->order = ordem;
    novo_no->left = NULL;
    novo_no->right = NULL;
    return novo_no;
}

// Função para inserir um novo nó
void insert_node(node** root, node* new_node) {
    if (*root == NULL) {
        *root = new_node;

    } else {
        int compare = strcmp(new_node->name, (*root)->name);

        if (compare == 0) { // Nomes iguais
            if (strcmp((*root)->type, "rw") == 0) { // Substituir o nó existente se o tipo for "rw"
                free((*root)->type);
                (*root)->type = strdup(new_node->type);
                (*root)->size = new_node->size;
                (*root)->order = new_node->order;
                free(new_node->name);
                free(new_node->type);
                free(new_node);
            } else {
                // Liberar o novo nó se não for substituído
                free(new_node->name);
                free(new_node->type);
                free(new_node);
            }
        } else if (compare < 0) {
            insert_node(&(*root)->left, new_node);
        } else {
            insert_node(&(*root)->right, new_node);
        }
    }
}

// Função para imprimir os nós em ordem
void print_inorder(node* root, FILE* output) {
    if (root == NULL) {
        return;
    }
    print_inorder(root->left, output);
    if (root->size == 1) {
        fprintf(output, "%d %s %s %d byte\n", root->order, root->name, root->type, root->size);
        print_inorder(root->right, output);}
    else {
        fprintf(output, "%d %s %s %d bytes\n", root->order, root->name, root->type, root->size);
        print_inorder(root->right, output);
    }
}

// função para imprimir os nós em pré-ordem
void print_preorder(node* root, FILE* output) {
    if (root == NULL) {
        return;
    }
    if (root->size == 1) {
        fprintf(output, "%d %s %s %d byte\n", root->order, root->name, root->type, root->size);
        print_preorder(root->left, output);
        print_preorder(root->right, output);}
    else {
        fprintf(output, "%d %s %s %d bytes\n", root->order, root->name, root->type, root->size);
        print_preorder(root->left, output);
        print_preorder(root->right, output);
    }
}

// função para imprimir os nós em pós-ordem
void print_postorder(node* root, FILE* output) {
    if (root == NULL) {
        return;
    }
    print_postorder(root->left, output);
    print_postorder(root->right, output);
    if (root->size == 1) {
        fprintf(output, "%d %s %s %d byte\n", root->order, root->name, root->type, root->size);
    }
    else {
        fprintf(output, "%d %s %s %d bytes\n", root->order, root->name, root->type, root->size);
    }
}

// função para liberar memoria
void free_tree(node *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root->name);
    free(root->type);
    free(root);
}

// Função principal
int main(int argc, char* argv[]) {

    // Abrindo os arquivos com as permissoes corretas
    FILE* input = fopen("arvorebinaria.input", "r");
    FILE* output = fopen("arvorebinaria.output", "w");

    // Definindo a raiz e as variáveis
    node* root = NULL;
    char nome[51];
    char tipo[3];
    int tamanho, quantidade;

    // Registrando a quantidade
    fscanf(input, "%d", &quantidade);

    // Inserindo na árvore
    for (int i = 0; i < quantidade; i++) {
        fscanf(input, "%s %s %d", nome, tipo, &tamanho);
       // int ordem = findMaxCounter(root, stack);
        node* novo = new_node(nome, tipo, tamanho, i);
        insert_node(&root, novo);
    }

    // Imprimindo as funções
    fprintf(output, "EPD:\n");
    print_inorder(root, output);
    fprintf(output, "PED:\n");
    print_preorder(root, output);
    fprintf(output, "EDP:\n");
    print_postorder(root,output);

    // Fechando os arquivos
    fclose(input);
    fclose(output);

    // Liberando memória alocada
    free_tree(root);

    return 0;
}