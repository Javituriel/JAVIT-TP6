// aoc03.c
// Compilation: make
// Usage: ./aoc03  < input.txt
// Produit les totaux pour k=2 et k=12 (somme en grande précision)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Retourne une nouvelle chaîne (heap) correspondant à la sous-séquence
// lexicographiquement maximale (en chiffres) de longueur k, en respectant l'ordre.
char *max_subseq(const char *s, size_t k) {
    size_t n = strlen(s);
    if (k == 0) {
        char *r = malloc(1); r[0] = '\0'; return r;
    }
    if (k >= n) {
        // copie entière
        char *r = malloc(n + 1);
        strcpy(r, s);
        return r;
    }
    char *res = malloc(k + 1);
    size_t start = 0;
    for (size_t i = 0; i < k; ++i) {
        size_t end = n - (k - i) + 1; // exclusive
        char mx = '0';
        size_t mx_idx = start;
        for (size_t j = start; j < end; ++j) {
            char c = s[j];
            if (c > mx) { mx = c; mx_idx = j; }
            if (mx == '9') break; // early exit: can't beat '9'
        }
        res[i] = mx;
        start = mx_idx + 1;
    }
    res[k] = '\0';
    return res;
}

// Addition de deux entiers décimaux donnés sous forme de chaînes (non signées).
// Les entrées peuvent être grandes. Renvoie une nouvelle chaîne (heap) contenant le résultat.
char *string_add(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    size_t maxl = (la > lb ? la : lb);
    // résultat au plus maxl+1 chiffres
    char *res = malloc(maxl + 2);
    size_t ia = la, ib = lb, ir = 0;
    int carry = 0;
    // addition de droite à gauche
    while (ia > 0 || ib > 0 || carry) {
        int da = 0, db = 0;
        if (ia > 0) { da = a[--ia] - '0'; }
        if (ib > 0) { db = b[--ib] - '0'; }
        int s = da + db + carry;
        res[ir++] = (char)('0' + (s % 10));
        carry = s / 10;
    }
    // res contient le nombre à l'envers
    for (size_t i = 0; i < ir / 2; ++i) {
        char t = res[i];
        res[i] = res[ir - 1 - i];
        res[ir - 1 - i] = t;
    }
    res[ir] = '\0';
    return res;
}

// Trim newline and leading/trailing whitespace
void trim_inplace(char *s) {
    // trim right
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || isspace((unsigned char)s[n-1])))
        s[--n] = '\0';
    // trim left
    size_t start = 0;
    while (s[start] && isspace((unsigned char)s[start])) ++start;
    if (start > 0) memmove(s, s + start, strlen(s + start) + 1);
}

int main(void) {
    // accumulateurs sous forme de chaînes décimales (initialisés à "0")
    char *sum_k2 = malloc(2); strcpy(sum_k2, "0");
    char *sum_k12 = malloc(2); strcpy(sum_k12, "0");

    char line[4096];
    while (fgets(line, sizeof(line), stdin)) {
        trim_inplace(line);
        if (line[0] == '\0') continue;
        // valider que la ligne est bien composée de chiffres 1..9 (tolérance)
        size_t L = strlen(line);
        int ok = 1;
        for (size_t i = 0; i < L; ++i) {
            if (line[i] < '0' || line[i] > '9') { ok = 0; break; }
        }
        if (!ok) continue;

        // Q1: k = 2
        char *s2 = max_subseq(line, 2);
        // ajouter s2 à sum_k2
        char *new_sum_k2 = string_add(sum_k2, s2);
        free(sum_k2); sum_k2 = new_sum_k2;
        free(s2);

        // Q2: k = 12
        // If line shorter than 12, max_subseq will give the whole line (but spec expects k exactly 12:
        // in that case we interpret that if line length < k, take whole line — problem data does not have short lines)
        char *s12 = max_subseq(line, 12);
        char *new_sum_k12 = string_add(sum_k12, s12);
        free(sum_k12); sum_k12 = new_sum_k12;
        free(s12);
    }

    // Affichage final
    printf("Question 1 (k=2) total : %s\n", sum_k2);
    printf("Question 2 (k=12) total: %s\n", sum_k12);

    free(sum_k2);
    free(sum_k12);
    return 0;
}
