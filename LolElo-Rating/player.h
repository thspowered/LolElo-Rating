#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"

int load_ids(Player list_players[], char * filePath);

void divison(Player list_players[], int  numbers_of_players);

void output(Player list_players[],char * filePath,int  numbers_of_players);

void ELO(Player list_players[],Match * matches, int number_pf_matches, int numbers_of_players);