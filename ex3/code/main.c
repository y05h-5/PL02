#include <stdlib.h>
#include <stdio.h>

#include "includes/Jagged.h"

int normalize_freq();
int invert_docfreq(int num_doc, int doc_freq);

int main (void) {
	FILE* config = NULL;
	FILE* terms = NULL;
	FILE* output = NULL; // tfidf.txt

	int num_docs  = 0;
	int num_terms = 0;
	int doc_freq = 0;
	int inv_doc_freq = 0;
	config = fopen("config.txt", "rt");
	terms = fopen("terms.txt", "rt");
	
	// read documents, record frequencies?
	JaggedArray** freq = NULL;
	allocateJaggedArray(freq, num_terms, num_docs);

	// normalize the frequencies
	JaggedArray** freq_norm = NULL;
	allocateJaggedArray(freq_norm, num_terms, num_docs);

	return 0;
}