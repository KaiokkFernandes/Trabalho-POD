#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct Curso {
    char nomeCurso[100];
    char IES[100];
    char UF[3]; // Unidade da Federação
    char areaEnquadramento[100];
} Curso;

typedef struct Node {
    Curso curso;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, Curso curso) {
    if (root == NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->curso = curso;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    int cmp = strcmp(curso.nomeCurso, root->curso.nomeCurso);
    if (cmp < 0) {
        root->left = insert(root->left, curso);
    } else if (cmp > 0) {
        root->right = insert(root->right, curso);
    }
    return root;
}

Node *search(Node *root, const char *nomeCurso) {
    if (root == NULL || strcmp(root->curso.nomeCurso, nomeCurso) == 0) {
        return root;
    }
    int cmp = strcmp(nomeCurso, root->curso.nomeCurso);
    if (cmp < 0) {
        return search(root->left, nomeCurso);
    } else {
        return search(root->right, nomeCurso);
    }
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

Node *buildTreeFromFile(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[MAX_LINE_LENGTH];
    Node *root = NULL;
    while (!feof(arquivo)) {
        lerLinha(arquivo, linha);
        Curso curso;
        if (sscanf(linha, "%[^,],%[^,],%[^,],%[^,]", curso.nomeCurso, curso.IES, curso.UF, curso.areaEnquadramento) == 4) {
            root = insert(root, curso);
        }
    }
    fclose(arquivo);
    return root;
}

int main() {
    Node *root = buildTreeFromFile("cursos.txt");
    // Agora você pode usar root para pesquisar por um curso específico
    char cursoProcurado[100];
    printf("Digite o nome do curso que deseja procurar: ");
    fgets(cursoProcurado, 100, stdin);
    cursoProcurado[strcspn(cursoProcurado, "\n")] = 0; // Remove newline

    Node *found = search(root, cursoProcurado);
    if (found) {
        printf("Curso encontrado: %s, IES: %s, UF: %s, Área: %s\n", 
            found->curso.nomeCurso, found->curso.IES, found->curso.UF, found->curso.areaEnquadramento);
    } else {
        printf("Curso não encontrado.\n");
    }

    // Não esqueça de liberar a memória da árvore
    freeTree(root);
    return 0;
}
