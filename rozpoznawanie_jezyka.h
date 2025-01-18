#include "biblioteka.h"

typedef struct language_profile {
    char name[4];         // Skrót nazwy języka, np. "GER", "POL"
    double letters[26];   // Częstotliwości liter a-z
} LanguageProfile;

typedef const struct language_base {
    LanguageProfile German;   
    LanguageProfile French;   
    LanguageProfile Polish;   
    LanguageProfile Finnish;  
    LanguageProfile Spanish;  
    LanguageProfile Italian;  
    LanguageProfile English;  
} LanguageBase;

// Hardkodowane dane o częstotliwościach liter
const LanguageBase LANGUAGES = {
    .German = {
        .name = "GER",
        .letters = {
            6.51,  // a
            1.89,  // b
            2.73,  // c
            5.08,  // d
            16.40, // e
            1.66,  // f
            3.01,  // g
            4.76,  // h
            7.55,  // i
            0.27,  // j
            1.21,  // k
            3.44,  // l
            2.53,  // m
            9.78,  // n
            2.51,  // o
            0.79,  // p
            0.02,  // q
            7.00,  // r
            7.27,  // s
            6.15,  // t
            4.35,  // u
            0.67,  // v
            1.89,  // w
            0.03,  // x
            0.04,  // y
            1.13   // z
        }
    },
    .French = {
        .name = "FRA",
        .letters = {
            7.64,  // a
            0.93,  // b
            3.26,  // c
            3.67,  // d
            14.71, // e
            1.06,  // f
            0.87,  // g
            0.74,  // h
            7.52,  // i
            0.61,  // j
            0.05,  // k
            5.46,  // l
            2.96,  // m
            7.09,  // n
            5.27,  // o
            2.49,  // p
            1.36,  // q
            6.55,  // r
            8.08,  // s
            7.07,  // t
            6.39,  // u
            1.83,  // v
            0.04,  // w
            0.30,  // x
            0.24,  // y
            0.32   // z
        }
    },
    .Polish = {
        .name = "POL",
        .letters = {
            8.97,  // a
            1.48,  // b
            3.99,  // c
            3.29,  // d
            7.92,  // e
            0.31,  // f
            1.38,  // g
            1.07,  // h
            8.28,  // i
            2.34,  // j
            3.41,  // k
            2.14,  // l
            2.91,  // m
            5.60,  // n
            7.59,  // o
            3.10,  // p
            0.00,  // q
            4.57,  // r
            4.26,  // s
            3.97,  // t
            2.35,  // u
            0.03,  // v
            4.55,  // w
            0.02,  // x
            3.86,  // y
            5.62   // z
        }
    },
    .Finnish = {
        .name = "FIN",
        .letters = {
            12.22, // a
            2.24,  // b
            0.28,  // c
            1.04,  // d
            7.96,  // e
            1.73,  // f
            0.39,  // g
            1.85,  // h
            10.82, // i
            2.04,  // j
            4.97,  // k
            5.76,  // l
            3.20,  // m
            8.82,  // n
            5.38,  // o
            1.84,  // p
            0.02,  // q
            2.41,  // r
            7.86,  // s
            9.30,  // t
            5.09,  // u
            2.52,  // v
            0.09,  // w
            0.03,  // x
            0.01,  // y
            1.08   // z
        }
    },
    .Spanish = {
        .name = "SPA",
        .letters = {
            11.53, // a
            2.22,  // b
            4.02,  // c
            5.01,  // d
            12.18, // e
            0.69,  // f
            1.77,  // g
            0.70,  // h
            6.25,  // i
            0.44,  // j
            0.01,  // k
            4.97,  // l
            3.15,  // m
            6.71,  // n
            8.68,  // o
            2.51,  // p
            0.88,  // q
            6.87,  // r
            7.98,  // s
            4.63,  // t
            3.93,  // u
            1.14,  // v
            0.01,  // w
            0.22,  // x
            0.90,  // y
            0.52   // z
        }
    },
    .Italian = {
        .name = "ITA",
        .letters = {
            11.74, // a
            0.92,  // b
            4.50,  // c
            3.73,  // d
            11.79, // e
            0.95,  // f
            1.64,  // g
            1.54,  // h
            10.14, // i
            0.00,  // j
            0.00,  // k
            6.51,  // l
            2.51,  // m
            6.88,  // n
            9.83,  // o
            3.05,  // p
            0.51,  // q
            6.37,  // r
            4.98,  // s
            5.62,  // t
            3.01,  // u
            2.10,  // v
            0.00,  // w
            0.00,  // x
            0.00,  // y
            1.18   // z
        }
    },
    .English = {
        .name = "ENG",
        .letters = {
            8.12,  // a
            1.49,  // b
            2.71,  // c
            4.32,  // d
            12.70, // e
            2.23,  // f
            2.02,  // g
            6.09,  // h
            6.97,  // i
            0.15,  // j
            0.77,  // k
            4.03,  // l
            2.41,  // m
            6.75,  // n
            7.51,  // o
            1.93,  // p
            0.10,  // q
            5.99,  // r
            6.33,  // s
            9.06,  // t
            2.76,  // u
            0.98,  // v
            2.36,  // w
            0.15,  // x
            1.97,  // y
            0.07   // z
        }
    }

};
