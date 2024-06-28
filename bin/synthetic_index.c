#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LINE_LENGTH 10000
#define MAX_SENTENCE_LENGTH 10000

double calculate_mwr(int morphemes, int words) {
    return (double)morphemes / words;
}

double calculate_fusion_index(int morphemes) {
    return 0.5; // Simplified calculation
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

void process_sentence(FILE *csv_file, wchar_t *sentence, int words, int morphemes, int inflectional_morphemes, int function_words) {
    double mwr = calculate_mwr(morphemes, words);
    double fusion_index = calculate_fusion_index(morphemes);
    double complexity_index = calculate_complexity_index(inflectional_morphemes, words);
    double si = calculate_si(mwr, fusion_index, complexity_index);
    double pof = calculate_pof(function_words, words);
    double ai = calculate_ai(si, pof);

    wprintf(L"Processing: \"%ls\"\n", sentence);
    wprintf(L"Words: %d, Morphemes: %d, Inflectional: %d, Function: %d\n", words, morphemes, inflectional_morphemes, function_words);
    wprintf(L"SI: %.2f, AI: %.2f\n\n", si, ai);

    fwprintf(csv_file, L"\"%ls\",%.2f,%.2f\n", sentence, si, ai);
    fflush(csv_file);
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    FILE *input_file = _wfopen(L"input_data.csv", L"r, ccs=UTF-8");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output_file = _wfopen(L"output_data.csv", L"w, ccs=UTF-8");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    fwprintf(output_file, L"Sentence,Synthetic Score,Analytic Score\n");

    wchar_t line[MAX_LINE_LENGTH];
    wchar_t sentence[MAX_SENTENCE_LENGTH];
    int words, morphemes, inflectional_morphemes, function_words;
    int line_count = 0;

    // Skip header
    fgetws(line, MAX_LINE_LENGTH, input_file);

    while (fgetws(line, MAX_LINE_LENGTH, input_file)) {
        line_count++;
        wprintf(L"Reading line %d: %ls", line_count, line);

        wchar_t *comma = wcschr(line, L',');
        if (comma) {
            *comma = L'\0';
            wcscpy_s(sentence, MAX_SENTENCE_LENGTH, line);
            wprintf(L"Sentence: %ls\n", sentence);
            if (swscanf_s(comma + 1, L"%d,%d,%d,%d", &words, &morphemes, &inflectional_morphemes, &function_words) == 4) {
                wprintf(L"Words: %d, Morphemes: %d, Inflectional: %d, Function: %d\n", words, morphemes, inflectional_morphemes, function_words);
                process_sentence(output_file, sentence, words, morphemes, inflectional_morphemes, function_words);
            } else {
                wprintf(L"Failed to parse data for sentence: %ls\n", sentence);
            }
        } else {
            wprintf(L"Failed to find comma separator in line: %ls\n", line);
        }
    }

    fclose(input_file);
    fclose(output_file);

    wprintf(L"Processing complete. Output written to output_data.csv\n");

    return 0;
}
