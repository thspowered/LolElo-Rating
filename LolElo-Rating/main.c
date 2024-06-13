#include "player.h"
#include "match.h"



int main(int argc, char **argv){
    if (argc != 4){

        printf("Wrong parameters");
        return 1;        
    }

    Player list_players [256];
    Match matches[100];

    int numbers_of_players = load_ids(list_players, argv[2]);

    int indexMatches = load_matches(matches,argv[1]);

    int rb = 1000;
    int number_pf_matches = indexMatches +1;
    
    ELO(list_players,matches,number_pf_matches,numbers_of_players);
    divison(list_players, numbers_of_players);
    
    output(list_players,argv[3],numbers_of_players);
}