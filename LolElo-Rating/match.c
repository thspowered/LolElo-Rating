#include "match.h"

int load_matches(Match * matches,char * filePath)
{

    FILE* pF = fopen(filePath ,"r");
    if(pF == NULL)
    {
        printf("File was not found\n");
        exit(1);
    }

    char line[255] = {0};

    bool loadingMatch = false;
    int index_Matches = -1;
    while (fgets(line, sizeof(line), pF) != NULL) 
    {
        if (strcmp(line, "match\n") == 0)
        {
            loadingMatch = true;
            index_Matches++;
        }

        bzero(line, sizeof(line));
        if(loadingMatch == true)
        {
            fgets(line,sizeof(line),pF);
            char* token = strtok(line, ",");
            token[strlen(token)] = 0;
            matches[index_Matches].teams[0].players_ids[0] = atoi(token);
            token = strtok(NULL, ",");
            token[strlen(token)] = 0;
            matches[index_Matches].teams[0].players_ids[1] = atoi(token);
            token = strtok(NULL, ",");
            token[strlen(token)] = 0;
            matches[index_Matches].teams[0].players_ids[2] = atoi(token);

            bzero(line, sizeof(line));

            //skipping KAD (KDA)
            fgets(line,sizeof(line),pF);
            bzero(line, sizeof(line));

            fgets(line,sizeof(line),pF);
            char* token2 = strtok(line, ",");
            token2[strlen(token2)] = 0;
            matches[index_Matches].teams[1].players_ids[0] = atoi(token2);
            token2 = strtok(NULL, ",");
            token2[strlen(token2)] = 0;
            matches[index_Matches].teams[1].players_ids[1] = atoi(token2);
            token2 = strtok(NULL, ",");
            token2[strlen(token2)] = 0;
            matches[index_Matches].teams[1].players_ids[2] = atoi(token2);

            bzero(line, sizeof(line));

            //skipping KAD (KDA)
            fgets(line,sizeof(line),pF);
            bzero(line, sizeof(line));


            fgets(line,sizeof(line),pF);
            if (strcmp(line, "red\n") == 0)
            {
                matches[index_Matches].winner = RED_WIN;
            }
            else
            {
                matches[index_Matches].winner = BLUE_WIN;
            }

            bzero(line, sizeof(line));
            loadingMatch = false;

        }
        
    
    } 
    fclose(pF);
    return index_Matches;
}