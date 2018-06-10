//
// Created by Lukas Bischof on 07.06.18.
//

#ifndef LAUNCHR_UTILITIES_H
#define LAUNCHR_UTILITIES_H

#include <stdio.h>

#define printlnf(chars, ...) printf((chars "\n"), ##__VA_ARGS__)
#define errprintlnf(chars, ...) fprintf(stderr, (chars "\n"), ##__VA_ARGS__)

#ifdef DEBUG
 #define debugprintlnf printlnf
#else
 #define debugprintlnf
#endif

#ifdef __cplusplus
 #define CGUARD extern "C" {
 #define CGUARD_END };
#else
 #define CGUARD
 #define CGUARD_END
#endif

#endif //LAUNCHR_UTILITIES_H
