#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10, 100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

// each list node contains an integer key value and pointer to next list node
struct node {
    int key;
    struct node *next;
};

// list's beginning is called the head of list
struct node *head = NULL;


struct node* list_insert(int value) {
    struct node *createNode;									//utworzenie zmiennej o strukturze "node"
    createNode = (struct node*) malloc(sizeof(struct node)); 	//zaalokowanie pamięci dla nowego elementu
    createNode->key = value;									//nadanie mu wartości
    createNode->next = head;									//następneym elementem będzie aktualna głowa
    head = createNode;											//zmiana głowy na aktualnie pierwszy element listy

    return createNode;
}

struct node* list_search(int value) {
    struct node *iter;
    iter = head;								//zmienna pomocnicza przyjmuje wartość głowy
    while (iter != NULL && iter->key != value)	
    {
        iter = iter->next;						//jeśli zmienna nie jest pusta i nie równa się szukanej wartości, przyjmuje wartość następnego elementu struktury
    }
    return iter;
}

void list_delete(int value) {
    struct node *prev;
    struct node *iter;
    if(head->key == value)
	{
    	head=head->next;							//jeśli pierwszy element listy ma wartość równą szukanej, ustawiamy następny element listy na pierwszy
	}
	else
	{
		prev = head;								//prev - poprzedni element
		iter = head->next;							//iter - następny element
		while(iter != NULL && iter->key != value)	//kiedy iter nie jest pusty i nie jest równy szukanej wartości:
		{
			prev = iter;								//poprzeni i następny element przechodzą o jeden w górę
			iter = iter->next;							
		}
		if(iter != NULL)		//wykluczamy, że iter jest pusty, a to oznacza, że jest szukanum elementem
		{
			prev->next = iter->next;	//podmiana wskazania nexta poprzedniego elementu z itera na następny po iterze (omijamy iter, tym samym usuwamy go z listy)
		}
	}
    
}

unsigned int list_size() {
    int size = 0;			//zmienna zliczająca ilość elementów
    struct node *iter;
    iter = head;			//zmienna pomocnicza działająca jak głowica odczytująca
    while(iter != NULL)		//wykonuj pętlę do końca listy
	{
    	size += 1;			//przy każdym elemencie zwiększ size o 1
    	iter = iter->next;	//głowica zmienia położenie na następny element listy
	}
    return size;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
	int i;
    for (i = 0; i < n; i++) {
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
	int i;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

int main() {
    bool no_yes[] = { false, true };
	unsigned int i;
    for (i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++) {
    	printf("Elements: Shuffle: InsertionTime:     SearchTime:\n");
        bool enable_shuffle = no_yes[i];
		unsigned int j;
        for (j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // always create an array of size `n` and fill it with increasing values
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // if true, reorder array elements randomly
            if (enable_shuffle) {
                shuffle(t, n);
            }

            // insert elements in the order present in array `t`
            clock_t insertion_time = clock();
            unsigned int k;
            for (k = 0; k < n; k++) {
                struct node *iter = list_insert(t[k]);
                assert(iter != NULL);       // inserted element cannot be NULL
                assert(iter->key == t[k]);  // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            
            for (k = 0; k < n; k++) {
                struct node *iter = list_search(t[k]);
                assert(iter != NULL);       // found element cannot be NULL
                assert(iter->key == t[k]);  // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            int l;
            for (k = 0, l = n; k < n; k++, l--) {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);       // after all deletions, the list size is zero
            assert(head == NULL);           // after all deletions, the list's head is NULL

            free(t);

            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "  true  " : "  false  ",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
