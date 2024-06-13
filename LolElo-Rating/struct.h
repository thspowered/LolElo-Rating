#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <strings.h>

#define RED_WIN  0
#define BLUE_WIN  1

typedef struct 
{
    int players_ids[3];
}Team;


typedef struct 
{
    Team teams[2];

    int winner;
}Match;

typedef struct 
{
    char username[32];
    char divison[32];
    int id;
    int ra;
}Player;