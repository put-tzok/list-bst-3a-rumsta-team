#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

unsigned int ns[] = { 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

// each tree node contains an integer key and pointers to left and right children nodes
struct node {
    int key;
    struct node *left;
    struct node *right;
};

// tree's beginning is called the root
struct node *root = NULL;

struct node **tree_search(struct node **candidate, int value) {
    if(((**candidate).key < value)&&((**candidate).right != NULL)){            // Sprawdz czy szukany element jest mniejszy czy
            return tree_search(&(**candidate).right, value);                   // większy od węzła i przejdz w dół odpowiednio 
    }                                                                          // w lewą lub prawą strone
    if(((**candidate).key > value)&&((**candidate).left != NULL)){             //
            return tree_search(&(**candidate).left, value);                    //
    }
    if ((**candidate).key == value){                                           
           return candidate;
    }
    
}

struct node* tree_insert(int value) {
    struct node *new_component;                                        // deklaracja 
    new_component = (struct node*) malloc(sizeof(struct node));        // Stwórz wezeł 
        (*new_component).key = value;                                  // Nadaj mu wartość
        (*new_component).left = NULL;                                  // Określ ze nie ma lewego 
        (*new_component).right = NULL;                                 // ani prawego potomka
    
    if (root == NULL){                                                 // Przypadek kiedy drzewo jest puste
        root = new_component;                                          
    }else{
        struct node *struct_operational = root;
        while(1==1){
            if(((*struct_operational).key >= value)&&((*struct_operational).left) != NULL){             // Część w której
                struct_operational = (*struct_operational).left;                                        // szukamy miejsca na
            }                                                                                           // nowy węzeł
            else if(((*struct_operational).key <= value)&&((*struct_operational).right) != NULL){       // 
                struct_operational = (*struct_operational).right;                                       // 
            }                                                                                            
            else if((*struct_operational).key <= value){                                                // Dodanie węzła              
                (*struct_operational).right = new_component;                                            // do drzewa
                return NULL;                                                                            //     
                                                                                                        //
            }else{                                                                                      //
                (*struct_operational).left = new_component;                                             //
                return NULL;                                                                            //
            }
            }

        }
}





struct node **tree_maximum(struct node **candidate) {                     //Szukanie najwiekszej wartosci
    if ((**candidate).right != NULL){                                     //polega na schodzeniu w drzewie
        return tree_maximum(&(**candidate).right);                        //w prawą strone tak długo jak to mozliwe
    }
    
    
    return candidate;
}

void tree_delete(int value) {
    struct node **candidate =  tree_search(&root, value);                                       //Szukam gdzie znajduje się wartość która chce skasowac
    if ((**candidate).left == NULL && (**candidate).right == NULL){               // Przypadek kiedy nie ma potomków-po prostu usuwam węzeł
        *candidate = NULL;
    }else if (((**candidate).left != NULL) && ((**candidate).right == NULL)){     // Istnieje lewy potomek ale nie istnieje prawy - usuwam węzeł a w jego miejsce
        *candidate = (**candidate).left;                                          // wchodzi lewy potomek
    }else if (((**candidate).left == NULL) && ((**candidate).right != NULL)){     // Istnieje prawy potomek ale nie istnieje lewy - 
        *candidate = (**candidate).right;                                         //analogicznie jak w przypadku wyzej
    }else{                                                //sytuacja gdzie usuwany węzeł ma dwóch potomków
        struct node **maxcandidate;
        maxcandidate = tree_maximum(&(**candidate).left); //szukam wartości maksymalnej w lewym poddrzewie
        (**candidate).key = (**maxcandidate).key;         // Zastepuje usuwaną wartość prędzej znalezionym maksem w lewym poddrzewie
        if ((**maxcandidate).left != NULL){               // Jeśli szukana maksymalna wartosc w lewym poddrzewie miała lewogo potomka
        *maxcandidate = (**maxcandidate).left;            // To ten potomek wskakuje na miejsce rodzica
        }
    }
}

unsigned int tree_size(struct node *element) {
    if(element == NULL){                      // Sytuacja gdy drzewo jest puste
        return 0;
    }else{
      return 1 + tree_size((*element).left) + tree_size((*element).right); //Zliczaj elementy schodząc "Piętrami"
    }
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

/*
 * Check if tree is a valid BST.
 *
 * Parameters:
 *      struct node *element:   pointer to node to be checked
 *
 * Returns:
 *      bool:                   true if subtree rooted in "element" is a BST
 */
bool is_bst(struct node *element) {
    // empty tree is a valid BST
    if (element == NULL) {
        return true;
    }
    // leaf node is valid
    if (element->left == NULL && element->right == NULL) {
        return true;
    }
    // only right subnode? check it recursively
    if (element->left == NULL && element->right != NULL) {
        return (element->key < element->right->key) && is_bst(element->right);
    }
    // only left subnode? check it recursively
    if (element->left != NULL && element->right == NULL) {
        return (element->key > element->left->key) && is_bst(element->left);
    }
    // both subnodes present? check both recursively
    return (element->key > element->left->key)
        && (element->key < element->right->key)
        && is_bst(element->left)
        && is_bst(element->right);
}

void insert_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_random(int *t, int n) {
    shuffle(t, n);
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_binary(int *t, int n) {
    // TODO: implement
}

char *insert_names[] = { "Increasing", "Random", "Binary" };
void (*insert_functions[])(int*, int) = { insert_increasing, insert_random, insert_binary };

int main(int argc, char **argv) {
    for (unsigned int i = 0; i < sizeof(insert_functions) / sizeof(*insert_functions); i++) {
        void (*insert)(int*, int) = insert_functions[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // crate an array of increasing integers: 0, 1, 2, ...
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // insert data using one of methods
            clock_t insertion_time = clock();
            insert(t, n);
            insertion_time = clock() - insertion_time;

            assert(tree_size(root) == n);       // after all insertions, tree size must be `n`
            assert(is_bst(root));               // after all insertions, tree must be valid BST

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node **pnode = tree_search(&root, t[k]);
                struct node *iter = *pnode;
                assert(iter != NULL);           // found element cannot be NULL
                assert(iter->key == t[k]);      // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int l = 0, m = n; l < n; l++, m--) {
                assert(tree_size(root) == m);   // tree size must be equal to the expected value
                tree_delete(t[l]);
                assert(is_bst(root));           // after deletion, tree must still be valid BST
            }
            assert(tree_size(root) == 0);       // after all deletions, tree has size zero

            free(root);
            free(t);

            printf("%d\t%s\t%f\t%f\n",
                    n,
                    insert_names[i],
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
