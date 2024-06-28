#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double calculate_mwr(int morphemes, int words) {
    return (double)morphemes / words;
}

double calculate_fusion_index(int morphemes, int* grammatical_categories) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < morphemes; i++) {
        sum += grammatical_categories[i];
    }
    return (double)sum / morphemes;
}

double calculate_complexity_index(int inflectional_morphemes, int words) {
    return (double)inflectional_morphemes / words;
}

double calculate_si(double mwr, double fusion_index, double complexity_index) {
    return ((mwr + fusion_index + complexity_index) / 3) * 100;
}

double calculate_pof(int function_words, int words) {
    return (double)function_words / words;
}

double calculate_ai(double si, double pof) {
    return ((1 / (si + 1)) + (1 / pof)) * 100;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <words> <morphemes> <inflectional_morphemes> <function_words>\n", argv[0]);
        return 1;
    }

    int words = atoi(argv[1]);
    int morphemes = atoi(argv[2]);
    int inflectional_morphemes = atoi(argv[3]);
    int function_words = atoi(argv[4]);

    int grammatical_categories[] = {0, 1, 1, 1, 0, 0};  // Example categories for each morpheme

    double mwr = calculate_mwr(morphemes, words);
    double fusion_index = calculate_fusion_index(morphemes, grammatical_categories);
    double complexity_index = calculate_complexity_index(inflectional_morphemes, words);
    double si = calculate_si(mwr, fusion_index, complexity_index);
    double pof = calculate_pof(function_words, words);
    double ai = calculate_ai(si, pof);

    printf("Synthetic Index (SI): %.2f\n", si);
    printf("Analytic Index (AI): %.2f\n", ai);

    return 0;
}
