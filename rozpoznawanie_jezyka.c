#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "rozpoznawanie_jezyka.h"
const LanguageBase LANGUAGES = {
    .German = {
        "GER", {6.51, 1.89, 3.06, 5.08, 17.40, 1.66, 3.01, 4.76, 7.55, 0.27, 1.21, 3.44, 2.53, 9.78, 2.51, 0.79, 0.02, 7.00, 7.27, 6.15, 4.35, 0.67, 1.89, 0.03, 0.04, 1.13}},
    .French = {"FRA", {7.64, 0.90, 3.26, 3.67, 14.72, 1.06, 0.87, 0.74, 7.53, 0.61, 0.05, 5.45, 2.97, 7.10, 5.80, 2.52, 1.36, 6.69, 7.95, 7.24, 6.31, 1.83, 0.04, 0.42, 0.19, 0.21}},
    .Polish = {"POL", {10.99, 1.47, 3.96, 3.25, 8.34, 0.30, 1.42, 1.25, 8.35, 1.84, 3.51, 2.10, 2.80, 5.52, 8.32, 3.13, 0.14, 4.69, 4.32, 3.98, 2.50, 0.04, 5.81, 0.02, 3.76, 6.53}},
    .Finnish = {"FIN", {12.22, 2.21, 0.28, 1.04, 7.97, 0.20, 0.39, 1.85, 10.82, 2.25, 4.97, 5.76, 3.20, 9.81, 5.42, 1.84, 0.01, 2.87, 7.86, 8.75, 5.01, 2.25, 0.09, 0.03, 0.05, 0.48}},
    .Spanish = {"ESP", {12.53, 1.42, 4.68, 5.86, 13.68, 0.69, 1.01, 0.70, 6.25, 0.44, 0.02, 4.97, 3.15, 6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63, 3.93, 0.90, 0.01, 0.22, 0.90, 0.52}},
    .Italian = {"ITA", {11.74, 0.92, 4.50, 3.73, 11.79, 1.15, 1.64, 0.64, 10.14, 0.01, 0.00, 6.51, 2.51, 6.88, 9.83, 3.05, 0.51, 6.37, 4.98, 5.62, 3.01, 2.10, 0.01, 0.49, 0.01, 0.49}},
    .English = {"ENG", {8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07}}};

// Funkcja obliczająca odległość euklidesową między tablicą tekstu a profilem językowym
double calculate_distance(const double *text_frequencies, const double *profile_frequencies)
{
    double distance = 0.0;
    for (int i = 0; i < 26; i++)
    {
        double diff = text_frequencies[i] - profile_frequencies[i];
        distance += diff * diff;
    }
    return sqrt(distance);
}

// Funkcja przekształcająca tablicę wystąpień liter w częstotliwości procentowe
void calculate_frequencies(double *letter_counts, int total_letters)
{
    for (int i = 0; i < 26; i++)
    {
        letter_counts[i] = (double)letter_counts[i] / total_letters * 100.0;
    }
}

// Funkcja określająca język na podstawie częstotliwości liter
const char *detect_language(char *text)
{
    // Alokowanie struktury TextStats na stosie
    TextStats stats;
    statystyki(text, &stats);

    // Przygotowanie tablicy częstotliwości liter
    double text_frequencies[26];
    for (int i = 0; i < 26; i++)
    {
        text_frequencies[i] = stats.tablica_liter[i] + stats.tablica_liter[i + 26];
    }
    calculate_frequencies(text_frequencies, stats.liczba_liter);

    // Definicja dostępnych profili językowych
    const LanguageProfile *profiles[] = {
        &LANGUAGES.German,
        &LANGUAGES.French,
        &LANGUAGES.Polish,
        &LANGUAGES.Finnish,
        &LANGUAGES.Spanish,
        &LANGUAGES.Italian,
        &LANGUAGES.English};

    int num_languages = sizeof(profiles) / sizeof(profiles[0]);

    // Wyszukiwanie najlepszego dopasowania
    const char *best_match = NULL;
    double best_distance = INFINITY;

    for (int i = 0; i < num_languages; i++)
    {
        const LanguageProfile *profile = profiles[i];
        double distance = calculate_distance(text_frequencies, profile->letters);

        if (distance < best_distance)
        {
            best_match = profile->name;
            best_distance = distance;
        }
    }

    return best_match;
}
