#include "player.h"


int load_ids(Player *list_players, char * filePath)
{
    FILE* pF2 = fopen(filePath, "r");
    if (pF2 == NULL)
    {
        printf("File was not found\n");
        exit(1);
    }
    
    char line[255] = {0};

    //nahravanie id a usernames
    int index = 0;
    while (fgets(line, sizeof(line), pF2) != NULL) 
    {
        char* token = strtok(line, ",");
        token[strlen(token)] = 0;
        list_players[index].id = atoi(token);
        token = strtok(NULL, ",");
        token[strlen(token)-1] = 0;
        strcpy(list_players[index].username, token);
        list_players[index].ra = 1000;

        bzero(line, sizeof(line));
        index++;
    }

    fclose(pF2);

    return index;

}

void divison(Player *list_players, int  numbers_of_players)
{
    for (int i = 0; i < numbers_of_players; i++)
    {
        if (list_players[i].ra <= 1149)
        {
            strcpy(list_players[i].divison , "Bronze");
        }
        else if (list_players[i].ra <= 1499)
        {
            strcpy(list_players[i].divison , "Silver");
        }
        else if (list_players[i].ra <= 1849)
        {
            strcpy(list_players[i].divison , "Gold");
        }
        else if (list_players[i].ra <= 2199)
        {
            strcpy(list_players[i].divison , "Platinum");
        }
        else if (list_players[i].ra >= 2200)
        {
            strcpy(list_players[i].divison , "Diamond");
        }
        
    }
}

void output(Player list_players[],char * filePath,int  numbers_of_players)
{
    FILE* file_output = fopen(filePath, "w");
    if(file_output == NULL)
    {
       printf("Output file cannot be opened\n");
       exit(1);
    }

    fprintf(file_output, "<table cellspacing=3 bgcolor=#000000>\n");

    for (int i = 0; i < numbers_of_players; i++)
    {
        fprintf(file_output, "<tr bgcolor=#ffffff>\n");
        fprintf(file_output, "<td>%d</td>\n", list_players[i].id);
        fprintf(file_output, "<td>%s</td>\n", list_players[i].username);
        fprintf(file_output, "<td>%d</td>\n", list_players[i].ra);
        fprintf(file_output, "<td>%s</td>\n", list_players[i].divison);
        fprintf(file_output, "</tr bgcolor=#ffffff>\n");
    }
    fprintf(file_output, "</table>\n");



    fclose(file_output);
}

void ELO(Player list_players[],Match * matches, int number_pf_matches, int numbers_of_players)
{
    float k = 30.0;
    
    for (int i = 0; i < number_pf_matches; i++)
    {
        float sa = 0.0;
        int enemyIndex = 0;
        int friendlyIndex = 0;
        if (matches[i].winner == RED_WIN)
        {
            sa = 1.0;
            enemyIndex = 0;
            friendlyIndex = 1;
        }
        else
        {
            sa = 0.0;
            enemyIndex = 1;
            friendlyIndex = 0;
        }

        int enemyRAAvg = 0;

        for (int j = 0; j < 3; j++)
        {
            bool founded = false;
            int id_index_founded = -1;
            for(int x = 0 ; x < numbers_of_players; x++)
            {
                if(matches[i].teams[enemyIndex].players_ids[j] == list_players[x].id)
                {
                    id_index_founded= x;
                    founded = true;
                    break;
                }
            }
            if(founded == false)
            {
                printf("NENALEZEN\n");
                exit(1);
            }

            enemyRAAvg = enemyRAAvg + list_players[id_index_founded].ra;
            
        }

        enemyRAAvg = enemyRAAvg/3;


        int enemyRAAvg2 = 0;

        for (int j = 0; j < 3; j++)
        {
            bool founded = false;
            int id_index_founded = -1;
            for(int x = 0 ; x < numbers_of_players; x++)
            {
                if(matches[i].teams[friendlyIndex].players_ids[j] == list_players[x].id)
                {
                    id_index_founded= x;
                    founded = true;
                    break;
                }
            }
            if(founded == false)
            {
                printf("NENALEZEN\n");
                exit(1);
            }

            enemyRAAvg2 = enemyRAAvg2 + list_players[id_index_founded].ra;
            
        }

        enemyRAAvg2 = enemyRAAvg2/3;

        for (int j = 0; j < 3; j++)     //red
        {
            bool founded = false;
            int id_index_founded = -1;
            for(int x = 0 ; x < numbers_of_players; x++)
            {
                if(matches[i].teams[0].players_ids[j] == list_players[x].id)
                {
                    id_index_founded= x;
                    founded = true;
                }
            }
            if(founded == false)
            {
                printf("NENALEZEN\n");
                exit(1);
            }
      
            float ea = 1.0 / (1 + pow(10,((enemyRAAvg - list_players[id_index_founded].ra ) / 400)));

            list_players[id_index_founded].ra = list_players[id_index_founded].ra + (k * (sa -ea));

            
        }
        
        //BLUE

        sa = 0.0;
        if (matches[i].winner == BLUE_WIN)
        {
            sa = 1.0;
        }
        else
        {
            sa = 0.0;
        }

        for (int j = 0; j < 3; j++)     
        {
            bool founded = false;
            int id_index_founded = -1;
            for(int x = 0 ; x < numbers_of_players; x++)
            {
                if(matches[i].teams[1].players_ids[j] == list_players[x].id)
                {
                    id_index_founded= x;
                    founded = true;
                }
            }
            if(founded == false)
            {
                printf("NENALEZEN\n");
                exit(1);
            }
      
            float ea = 1.0 / (1 + pow(10,((enemyRAAvg2 - list_players[id_index_founded].ra ) / 400)));

            list_players[id_index_founded].ra = list_players[id_index_founded].ra + (k * (sa -ea));

            
        }

    }
}