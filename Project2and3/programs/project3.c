/*
    Jorge Durán Campos
    Luis Montes de Oca Ruiz
    Diego Quirós Artiñano
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>


static char * filename;
static char * filename_with_ext_data;
static char * filename_with_ext_table;
static char * filename_with_ext_comp;

static char * filename_decomp;
static char * ext_decomp;

static unsigned long filelen;

static int bytes_counter;
static int non_byte_nodes_amount;
static unsigned long **bytes;

static unsigned int path_table[256][2];

struct Node {
    int byte;
    unsigned long frequency;
    struct Node* left;
    struct Node* right;
};

struct Node* create_node(int inserting_byte, unsigned long amount) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->byte = inserting_byte;
    new_node->frequency = amount;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct Node* create_node_not_byte(int amount) {
    return create_node(-1, amount);
}

int is_leaf(struct Node* root) {
    if (root->left == NULL && root->right == NULL) return 1;
    return 0;
}

struct Node* create_tree() {
    if (bytes_counter > 1) {
        struct Node* non_byte_nodes[non_byte_nodes_amount];
        for (int i = 0; i < non_byte_nodes_amount; i++) non_byte_nodes[i] = NULL;
        int nb_total = 0, last_nb_add = 0;

        non_byte_nodes[nb_total] = create_node_not_byte(0);

        non_byte_nodes[nb_total]->left = create_node(bytes[0][0], bytes[0][1]);
        non_byte_nodes[nb_total]->right = create_node(bytes[1][0], bytes[1][1]);
        non_byte_nodes[nb_total]->frequency = bytes[0][1] + bytes[1][1];

        int all_loaded = 0;
        int i = 2;
        while (i < bytes_counter || !all_loaded) {
            if (i < bytes_counter - 1) {
                if (non_byte_nodes[last_nb_add]->frequency < bytes[i][1]) {
                    if (nb_total > 0 && non_byte_nodes[last_nb_add + 1]->frequency < bytes[i][1]) {
                        non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add + 1]->frequency + non_byte_nodes[last_nb_add]->frequency);
                        non_byte_nodes[nb_total]->left = non_byte_nodes[last_nb_add];
                        non_byte_nodes[nb_total]->right = non_byte_nodes[last_nb_add + 1];
                        last_nb_add += 2;
                    } else {
                        non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add]->frequency + bytes[i][1]);
                        non_byte_nodes[nb_total]->left = non_byte_nodes[last_nb_add];
                        non_byte_nodes[nb_total]->right = create_node(bytes[i][0], bytes[i][1]);
                        last_nb_add++;
                        i++;
                    }
                } else {
                    if (non_byte_nodes[last_nb_add]->frequency < bytes[i + 1][1]) {
                        non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add]->frequency + bytes[i][1]);
                        non_byte_nodes[nb_total]->left = create_node(bytes[i][0], bytes[i][1]);
                        non_byte_nodes[nb_total]->right = non_byte_nodes[last_nb_add];
                        last_nb_add++;
                        i++;
                    } else {
                        non_byte_nodes[++nb_total] = create_node_not_byte(bytes[i][1] + bytes[i + 1][1]);
                        non_byte_nodes[nb_total]->left = create_node(bytes[i][0], bytes[i][1]);
                        non_byte_nodes[nb_total]->right = create_node(bytes[i + 1][0], bytes[i + 1][1]);
                        i += 2;
                    }
                }
            }
            else if (i == bytes_counter - 1) {
                if (non_byte_nodes[last_nb_add]->frequency < bytes[i][1]) {
                    non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add]->frequency + bytes[i][1]);
                    non_byte_nodes[nb_total]->left = non_byte_nodes[last_nb_add];
                    non_byte_nodes[nb_total]->right = create_node(bytes[i][0], bytes[i][1]);
                    last_nb_add++;
                    i++;
                } else {
                    non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add]->frequency + bytes[i][1]);
                    non_byte_nodes[nb_total]->left = create_node(bytes[i][0], bytes[i][1]);
                    non_byte_nodes[nb_total]->right = non_byte_nodes[last_nb_add];
                    last_nb_add++;
                    i++;
                }
            }
            else if (nb_total > 0) {
                non_byte_nodes[++nb_total] = create_node_not_byte(non_byte_nodes[last_nb_add + 1]->frequency + non_byte_nodes[last_nb_add]->frequency);
                non_byte_nodes[nb_total]->left = non_byte_nodes[last_nb_add];
                non_byte_nodes[nb_total]->right = non_byte_nodes[last_nb_add + 1];
                last_nb_add += 2;
            }
            if (last_nb_add == nb_total && i == bytes_counter) {
                all_loaded = 1;
                break;
            }
        }
        
        return non_byte_nodes[nb_total];
    } else if (bytes_counter == 1){
        return create_node(bytes[0][0], bytes[0][0]);
    } else {
        return NULL;
    }
}

void *get_tree_data() {
    size_t size = 32;
    char * starting = (char *) malloc (32);
    char * number = (char *) malloc (32);
    char * byte = (char *) malloc (32);

    FILE * data = fopen(filename_with_ext_data, "rb");
    getline(&starting, &size, data);
    getline(&starting, &size, data);
    getdelim(&starting, &size,':', data);
    getline(&number, &size, data);
    bytes_counter = atoi(number);
    bytes = (unsigned long **) malloc(bytes_counter * sizeof(unsigned long *));
    for (int i = 0; i < bytes_counter; i++) {
        bytes[i] = (unsigned long *)malloc(2 * sizeof(unsigned long));
    }
    getdelim(&starting, &size, ':', data);
    getline(&number, &size, data);
    filelen = strtoul(number, NULL, 10);
    for (int i = 0; i < bytes_counter; i++) {
        getdelim(&starting, &size,' ', data);
        getdelim(&starting, &size,' ', data);
        getdelim(&byte, &size,' ', data);
        getdelim(&starting, &size,':', data);
        getline(&number, &size, data);
        bytes[i][0] = atoi(byte);
        bytes[i][1] = strtoul(number, NULL, 10);
    }
    getdelim(&starting, &size,':', data);
    getline(&number, &size, data);
    non_byte_nodes_amount = atoi(number) - bytes_counter;
    fclose(data);
}

void decompression(struct Node* root) {
    char * file_decomp = malloc(strlen(filename_decomp)+1+strlen(ext_decomp));
    strcpy(file_decomp, filename_decomp);
    strcat(file_decomp, ext_decomp);

    unsigned long reading_pos = 0;
    unsigned char read_byte = 0;
    int to_left, wrote_counter = 0, temp_bit = 0;

    struct Node* temp = root;

    FILE * in = fopen(filename_with_ext_comp, "rb");
    FILE * out = fopen(file_decomp, "w");

    while(!feof(in) && wrote_counter < root->frequency) {
        fseek(in, reading_pos, SEEK_SET);
        fread(&read_byte, 1, 1, in);
        for (to_left = 0; to_left < 8; to_left++) {
            if (is_leaf(temp)) { 
                fprintf(out,"%c", temp->byte);
                wrote_counter++;
                temp = root;
            }
            temp_bit = (read_byte << to_left)&255;
            temp_bit = temp_bit >> 7;
            if (temp_bit == 0) temp = temp->left;
            else if (temp_bit == 1) temp = temp->right;
            if (is_leaf(temp)) { 
                fprintf(out,"%c", temp->byte);
                wrote_counter++;
                temp = root;
            }
        }
        reading_pos++;
    }
    fclose(out);
    fclose(in);
}

int main(int argc, char *argv[]) {
    if (argc > 1) filename = (argv[1]);
    else {
        printf("Falta el nombre de los archivos externos y comprimido");
        return -1;
    }

    if (argc > 2) filename_decomp = (argv[2]);
    else {
        printf("Falta el nombre del archivo de decompresión");
        return -1;
    }

    if (argc > 3) ext_decomp = (argv[3]);
    else {
        printf("Falta la extensión del documento final");
        return -1;
    }

    filename_with_ext_data = malloc(strlen(filename)+1+4);
    strcpy(filename_with_ext_data, filename);
    strcat(filename_with_ext_data, ".edy");

    filename_with_ext_comp = malloc(strlen(filename)+1+4);
    strcpy(filename_with_ext_comp, filename);
    strcat(filename_with_ext_comp, ".una");

    filename_with_ext_table = malloc(strlen(filename)+1+6);
    strcpy(filename_with_ext_table, filename);
    strcat(filename_with_ext_table, ".table");

    get_tree_data();
    struct Node* root = create_tree();

    decompression(root);

    return 0;
}