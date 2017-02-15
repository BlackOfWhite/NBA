#include <stdio.h>
#include <stdlib.h>
#define CHAR_MAX_LENGTH 51
#define MAX_NUMBER_OF_PLAYERS 1000
#define NBA_DATABASE_PATH "NBA_DATABASE.bin"
#define NBA_DATABASE_PATH_PLAYERS "NBA_DATABASE_PLAYERS.bin"

typedef struct Team
{
    int id;
    int number_of_players;
    char team_name[CHAR_MAX_LENGTH];
    int table_score; //punkty w tabeli, 2 win, 0 lose
    int balance; // bilans wygranych.przegranych
    int total_number_of_games_played;
    int throws_success;
    int throws_fail;
    struct Player *head;
    struct Team* next;
} Team;

//Liczba zdobytych punktów w tabeli (2 zwyciestwo, 0 porazka), bilans meczy wygranych-przegranych, ilość rozegranych meczy, kosze zdobyte-kosze stracone

typedef struct Player
{
    int id;
    char first_name[CHAR_MAX_LENGTH];
    char last_name[CHAR_MAX_LENGTH];
    char team[CHAR_MAX_LENGTH];
    int points;
    int blocks;
    int assists;
    float efficiency;
    int rebounds;
    struct Player* next;
} Player;



Team* findLastElementInTeamsList(Team* list)
{
    if (list == NULL)
    {
        printf("Pointer to beginning of the list is not correct!\n");
        return NULL;
    }

    while (list->next != NULL)
        list = list->next;

    return list;
}

Player* findLastElementInPlayersList(Player* list)
{
    if (list == NULL)
    {
        printf("Pointer to beginning of the list is not correct!\n");
        return NULL;
    }

    if (list->next == NULL)
    {
        return list;
    }

    while (list->next != NULL)
        list = list->next;

    return list;
}

int getNextIdPlayer(Player* listElement)
{

    if (listElement->next == NULL)
    {
        return 0;
    }

    int maxId=(listElement->id)+1;
    listElement=listElement->next;
    while (listElement->next != NULL)
    {

        if (listElement->id >=maxId )
        {
            maxId = ((listElement->id) +1);
        }

        listElement = listElement->next;
    }
    return maxId;
}

int getNextIdTeam(Team* listElement)
{
    //empty
    if (listElement->next == NULL)
    {
        return 0;
    }

    int maxId=(listElement->id)+1;
    listElement=listElement->next;
    while (listElement->next != NULL)
    {

        if (listElement->id >=maxId )
        {
            maxId = ((listElement->id) +1);
        }

        listElement = listElement->next;
    }
    return maxId;
}

void enterTeamData(Team* newTeam)
{
    printf("Each of the team parameters has defined maximum length equal to %d characters.\n\n", CHAR_MAX_LENGTH - 1); //-1 poniewaz musi zostac miejsce na znak '\0' konczacy ciag znakow.
    fflush(stdin);
    printf("Enter team name: ");
    fgets(&newTeam->team_name, CHAR_MAX_LENGTH, stdin);
    (newTeam->team_name)[strcspn(newTeam->team_name, "\r\n")] = 0;
    do
    {
        fflush(stdin);
        printf("Enter total table score: ");
        scanf("%d", &newTeam->table_score);
    }
    while (newTeam->table_score < 0);

    fflush(stdin);
    printf("Enter total balance (W-L):");
    scanf("%d", &newTeam->balance);

    do
    {
        fflush(stdin);
        printf("Enter number of games played: ");
        scanf("%d", &newTeam->total_number_of_games_played);
    }
    while (newTeam->total_number_of_games_played < 0);

    do
    {
        fflush(stdin);
        printf("Enter number of successful throws: ");
        scanf("%d", &newTeam->throws_success);
    }
    while (newTeam->throws_success < 0);

    do
    {
        fflush(stdin);
        printf("Enter number of failed throws: ");
        scanf("%d", &newTeam->throws_fail);
    }
    while (newTeam->throws_fail < 0);


    printf("\n\n");
}


void enterPlayerData(Player* newPlayer)
{
    printf("Each of the team parameters has defined maximum length equal to %d characters.\n\n", CHAR_MAX_LENGTH - 1); //-1 poniewaz musi zostac miejsce na znak '\0' konczacy ciag znakow.
    fflush(stdin);
    printf("Enter player first name: ");
    fgets(&newPlayer->first_name, CHAR_MAX_LENGTH, stdin);
    fflush(stdin);
    printf("Enter player last name: ");
    fgets(&newPlayer->last_name, CHAR_MAX_LENGTH, stdin);

    (newPlayer->first_name)[strcspn(newPlayer->first_name, "\r\n")] = 0;
    (newPlayer->last_name)[strcspn(newPlayer->last_name, "\r\n")] = 0;

    do
    {
        fflush(stdin);
        printf("Enter total number of points scored: ");
        scanf("%d", &newPlayer->points);
    }
    while (newPlayer->points < 0);

    do
    {
        fflush(stdin);
        printf("Enter total number of blocks scored: ");
        scanf("%d", &newPlayer->blocks);
    }
    while (newPlayer->blocks < 0);

    do
    {
        fflush(stdin);
        printf("Enter total number of assists scored: ");
        scanf("%d", &newPlayer->assists);
    }
    while (newPlayer->assists < 0);

    do
    {
        fflush(stdin);
        printf("Enter player's efficiency: ");
        scanf("%.2f", &newPlayer->efficiency);
    }
    while (newPlayer->efficiency < 0);

    do
    {
        fflush(stdin);
        printf("Enter number of rebounds scored: ");
        scanf("%d", &newPlayer->rebounds);
    }
    while (newPlayer->rebounds < 0);


    fflush(stdin);
    printf("\n\n");
}

Team* addNewTeamToList(Team** list)
{
    if (*list == NULL) //jezeli lista nie zostala jeszcze utworzona, tworze jej pierwszy element
    {
        *list = (Team*)malloc(sizeof(Team));
        (*list)->next = NULL;
        return *list;
    }

    Team* lastElement = findLastElementInTeamsList(*list);
    if (lastElement == NULL)
    {
        printf("There was an error while searching for last element in the teams list!\n");
        return NULL;
    }

    lastElement->next = (Team*)malloc(sizeof(Team));

    if (lastElement->next == NULL)
    {
        printf("Error while trying to allocate memory for new Team structure!\n");
        return NULL;
    }

    return lastElement->next;
}

Player* addNewPlayerToList(Player* list)
{

    if (list == NULL) //jezeli lista nie zostala jeszcze utworzona, tworze jej pierwszy element
    {
        list = (Player*)malloc(sizeof(Player));
        list->next = NULL;
        return list;
    }

    Player* lastElement = findLastElementInPlayersList(list);
    if (lastElement == NULL)
    {
        printf("There was an error while searching for last element in the players list!\n");
        return NULL;
    }

    lastElement->next = (Player*)malloc(sizeof(Player));
    lastElement->next->next = NULL;

    if (lastElement->next == NULL)
    {
        printf("Error while trying to allocate memory for new Player structure!\n");
        return NULL;
    }

    return lastElement->next;

}

int addNewTeam(Team** list) //0 - blad 1 - OK
{
    Team* newTeam = addNewTeamToList(list);
    if (newTeam == NULL)
        return 0;

    newTeam->next = NULL;
    newTeam->head = NULL;
    newTeam->number_of_players = 0;

    enterTeamData(newTeam);

    newTeam->id = getNextIdTeam(*list);

    return 1;
}

int addNewPlayer(Team** list, char team_name[CHAR_MAX_LENGTH]) //0 - blad 1 - OK
{
    int maxId = -1;
    int added = 0; // 0 false, 1 true
    Player* newPlayer;

    Team* listElement = *list;
    while (listElement != NULL)
    {
        maxId = -1;
        if (strcmp(listElement->team_name,team_name)==0)
        {
            newPlayer = addNewPlayerToList(listElement->head);

            if (newPlayer == NULL)
            {
                return 0;
            }

            if (listElement->head == NULL)
            {
                listElement->head = newPlayer;
            }

            enterPlayerData(newPlayer);

            newPlayer->id = getNextIdPlayer(listElement->head);

            listElement->number_of_players = listElement->number_of_players+1;
            printf("-----------------------------------\n");
            break;
        }
        listElement = listElement->next;
    }

    return 1;
}

// EDIT TEAM
Team* enterEditTeamData(Team* oldTeam)
{
    Team* newTeam = oldTeam;

    // printf("Please enter '-0' to skip editing field.", CHAR_MAX_LENGTH - 1); //-1 poniewaz musi zostac miejsce na znak '\0' konczacy ciag znakow.
    fflush(stdin);
    printf("Enter team name (current: %s):",oldTeam->team_name);
    fgets(&newTeam->team_name, CHAR_MAX_LENGTH, stdin);
    (newTeam->team_name)[strcspn(newTeam->team_name, "\r\n")] = 0;
    do
    {
        fflush(stdin);
        printf("Enter total table score(current: %d):", oldTeam->table_score);
        scanf("%d", &newTeam->table_score);
    }
    while (newTeam->table_score < 0);

    fflush(stdin);
    printf("Enter total balance (W-L) (current: %d):", oldTeam->balance);
    scanf("%d", &newTeam->balance);

    do
    {
        fflush(stdin);
        printf("Enter number of games played (current: %d):", oldTeam->total_number_of_games_played);
        scanf("%d", &newTeam->total_number_of_games_played);
    }
    while (newTeam->total_number_of_games_played < 0);

    do
    {
        fflush(stdin);
        printf("Enter number of successful throws (current %d):", oldTeam->throws_success);
        scanf("%d", &newTeam->throws_success);
    }
    while (newTeam->throws_success < 0);

    do
    {
        fflush(stdin);
        printf("Enter number of failed throws (current %d):", oldTeam->throws_fail);
        scanf("%d", &newTeam->throws_fail);
    }
    while (newTeam->throws_fail < 0);

    strcpy(oldTeam->team_name,newTeam->team_name);
    oldTeam->table_score = newTeam->table_score;
    oldTeam->balance = newTeam->balance;
    oldTeam->total_number_of_games_played = newTeam->total_number_of_games_played;
    oldTeam->throws_success = newTeam->throws_success;
    oldTeam->throws_fail = newTeam->throws_fail;
    return oldTeam;
}
int editTeam(Team* list, char team_name[CHAR_MAX_LENGTH]) //0 - blad 1 - OK
{
    if (list == NULL)
    {
        printf("There are no teams in database!");
        return 0;
    }


    Team* listElement = list;
    while (listElement != NULL)
    {
        if (strcmp(listElement->team_name,team_name)==0)
        {
            Team* newElement = NULL;
            newElement = enterEditTeamData(listElement);
            if (newElement !=NULL)
            {
                printf("Team %s successfully edited.", team_name);
                return 1;
            }
        }
        listElement = listElement->next;
    }

    printf("Failed to edit team %s", team_name);
    return 0;
}
// END OF EDIT TEAM

// EDIT PLEJA'
Player* enterEditPlayerData(Player* oldPlayer)
{
    Player* newPlayer = oldPlayer;

    fflush(stdin);
    printf("Enter player first name (current: %s):",oldPlayer->first_name);
    fgets(&newPlayer->first_name, CHAR_MAX_LENGTH, stdin);
    (newPlayer->first_name)[strcspn(newPlayer->first_name, "\r\n")] = 0;

    fflush(stdin);
    printf("Enter player last name (current: %s):",oldPlayer->last_name);
    fgets(&newPlayer->last_name, CHAR_MAX_LENGTH, stdin);
    (newPlayer->last_name)[strcspn(newPlayer->last_name, "\r\n")] = 0;
    do
    {
        fflush(stdin);
        printf("Enter total number of points scored (current: %d):", oldPlayer->points);
        scanf("%d", &newPlayer->points);
    }
    while (newPlayer->points < 0);

    do
    {
        fflush(stdin);
        printf("Enter total number of blocks scored (current: %d):", oldPlayer->blocks);
        scanf("%d", &newPlayer->blocks);
    }
    while (newPlayer->blocks < 0);

    do
    {
        fflush(stdin);
        printf("Enter total number of assists scored (current: %d):", oldPlayer->assists);
        scanf("%d", &newPlayer->assists);
    }
    while (newPlayer->assists < 0);

    do
    {
        fflush(stdin);
        printf("Enter player's efficiency (current: %.2f):", oldPlayer->efficiency);
        scanf("%.2f", &newPlayer->efficiency);
    }
    while (newPlayer->efficiency < 0);

    do
    {
        fflush(stdin);
        printf("Enter total number of rebounds scored (current: %d):", oldPlayer->rebounds);
        scanf("%d", &newPlayer->rebounds);
    }
    while (newPlayer->rebounds < 0);


    strcpy(oldPlayer->first_name,newPlayer->first_name);
    strcpy(oldPlayer->last_name,newPlayer->last_name);
    oldPlayer->points = newPlayer->points;
    oldPlayer->blocks = newPlayer->blocks;
    oldPlayer->assists = newPlayer->assists;
    oldPlayer->efficiency = newPlayer->efficiency;
    oldPlayer->rebounds = newPlayer->rebounds;
    return oldPlayer;
}
int editPlayer(Team* list, char player_name[CHAR_MAX_LENGTH]) //0 - blad 1 - OK
{
    if (list == NULL)
    {
        printf("There are no team in database!");
        return 0;
    }

    Team* listElement = list;
    while (listElement != NULL)
    {
        Player* displayer = listElement->head;
        while (displayer != NULL)
        {
            char temp[CHAR_MAX_LENGTH];
            strcpy(temp,displayer->first_name);
            strcat(temp," ");
            strcat(temp,displayer->last_name);

            if(strcmp(temp, player_name)==0)
            {
                Player* newElement = NULL;
                newElement = enterEditPlayerData(displayer);
                if (newElement !=NULL)
                {
                    printf("Player %s successfully edited.", player_name);
                    return 1;
                }
                printf("Failed to edit player");
                return 0;
            }
            displayer=displayer->next;
        }


        listElement = listElement->next;
    }

    printf("Failed to find a player");
    return 0;
}
// END OF EDIT PLEJA'R

// DELETE STUFF
int deleteTeam(Team** list, char team_name[CHAR_MAX_LENGTH]) //0 - nie znaleziono karty/blad 1- OK
{
    Team* pointer = NULL;
    if (list == NULL)
    {
        printf("Incorrect team id!\n");
        return 0;
    }

    if (strcmp((*list)->team_name,team_name)==0)
    {
        pointer = (*list)->next;
        free(*list);
        *list = pointer;
        return 1;
    }

    Team* listElement = *list;
    while (listElement->next != NULL)
    {
        if (strcmp(listElement->next->team_name,team_name)==0)
        {
            pointer = listElement->next->next;
            free(listElement->next);
            listElement->next = pointer;
            return 1;
        }
        listElement = listElement->next;
    }

    return 0; //nie odnaleziono karty graficznej o podanym ID
}

int deletePlayer(Team** list, char player_name[CHAR_MAX_LENGTH]) //0 - blad 1- OK
{
    Team* pointer = NULL;
    if (list == NULL)
    {
        printf("There are no teams!\n");
        return 0;
    }
    Team* listElement = *list;
    while (listElement != NULL)
    {
        Player* displayer = listElement->head;
        if (displayer == NULL)
        {
            listElement = listElement->next;
            continue;
        }

        // first
        if (strcmp(displayer->first_name || " " || displayer->last_name, player_name)==0)
        {
            Player* pointer = displayer->next;
            free(displayer);
            listElement->head = pointer;
            return 1;
        }
        // not first
        while (displayer->next != NULL)
        {
            if (strcmp(displayer->next->first_name || " " || displayer->next->last_name, player_name)==0)
            {
                Player* pointer = displayer->next->next;
                free(displayer->next);
                displayer->next=pointer;
                return 1;
            }
            displayer = displayer->next;
        }

        listElement = listElement->next;
    }

    printf("Team with given id does not exist!");
    return 0;

}
// END OF DELETE STUFF

// FILE IO
int emptyListMemory(Team* list) //0 - blad 1 - OK
{
    if (list == NULL)
    {
        printf("Pointer to the list beginning is incorrect!\n");
        return 0;
    }

    Team* nextElement = NULL;
    Team* listElement = list;
    while (listElement != NULL)
    {
        nextElement = listElement->next;
        free(listElement);
        listElement = nextElement;
    }

    return 1;
}

int readDataFromNBADatabase(Team** list, int* numberOfTeams)
{
    // Teams
    FILE* NBADatabase = fopen(NBA_DATABASE_PATH, "rb"); // read binary
    if (NBADatabase == NULL)
    {
        printf("Database file read error!\n");
        return 0;
    }

    // Players
    FILE* NBADatabasePlayers = fopen(NBA_DATABASE_PATH_PLAYERS, "rb"); // read binary
    if (NBADatabasePlayers == NULL)
    {
        printf("Players database file read error!\n");
        return 0;
    }


    fseek(NBADatabase, 0, SEEK_END);
    int TeamsInFile = ftell(NBADatabase) / sizeof(Team);
    fseek(NBADatabase, 0, SEEK_SET);	//ilosc bajtow w pliku/rozmiar w
    //bajtach struktury = ile struktur zostalo zapisanych do pliku
    fseek(NBADatabasePlayers, 0, SEEK_END);
    int PlayersInFile = ftell(NBADatabasePlayers) / sizeof(Player);
    fseek(NBADatabasePlayers, 0, SEEK_SET);

    Team* newTeam = NULL;
    Player* currentPlayer = NULL;
    Player* nextPlayer = NULL;
    while (TeamsInFile>0)
    {
        // Load team
        newTeam = addNewTeamToList(list);
        if (newTeam == NULL)
            break;
        TeamsInFile -= fread(newTeam, sizeof(Team), 1, NBADatabase);
        //newTeam->id = (*numberOfTeams)++;
        newTeam->next = NULL;
        newTeam->head = NULL;

        // Load player
        // add new player to list
        // players to load
        int playersToLoadPerTeam = 0;
        if (newTeam->number_of_players > 0)
        {
            playersToLoadPerTeam = newTeam->number_of_players;
        }
        currentPlayer = NULL;

        int x;
        for (x=1; x<=playersToLoadPerTeam; x++)
        {
            if (x==1)
            {
                newTeam->head = (Player*)malloc(sizeof(Player));
                fread(newTeam->head, sizeof(Player), 1, NBADatabasePlayers);
                newTeam->head->next = NULL;
            }
            else
            {
                Player* listElement = newTeam->head;
                while (listElement->next != NULL)
                {
                    listElement = listElement->next;
                }
                listElement->next = (Player*)malloc(sizeof(Player));
                fread(listElement->next, sizeof(Player), 1, NBADatabasePlayers);
                listElement->next->next=NULL;

            }
        }
    }

    fclose(NBADatabase);
    fclose(NBADatabasePlayers);
    return 1;
}



int saveDataToFile(Team* list)
{

    FILE* NBADatabase = fopen(NBA_DATABASE_PATH, "wb");
    if (NBADatabase == NULL)
    {
        printf("Database file read error\n");
        return 0;
    }

    FILE* NBADatabasePlayers = fopen(NBA_DATABASE_PATH_PLAYERS, "wb");
    if (NBADatabasePlayers == NULL)
    {
        printf("Players database file read error\n");
        return 0;
    }


    while (list != NULL)
    {
        fwrite(list, sizeof(Team), 1, NBADatabase);
        if (list->head != NULL)
        {
            Player* player = list->head;
            while (player != NULL)
            {
                fwrite(player, sizeof(Player), 1, NBADatabasePlayers);
                player = player->next;
            }
        }
        list = list->next;
    }

    fclose(NBADatabase);
    return 1;
}
// END OF FILE IO

// DISPLAY DATA
void displayPlayerDetails(Team** list, char player_name[CHAR_MAX_LENGTH])
{
    int id = 0;
    Team* pointer = *list;
    while (pointer != NULL)
    {
        Player* element = pointer->head;
        while (element!=NULL)
        {

            char text[CHAR_MAX_LENGTH];
            strcpy(text, element->first_name);
            strcat(text," ");
            strcat(text, element->last_name);


            if (strcmp(text, player_name)==0)
            {
                printf("%d Player: %s %s . Total score: %d\n", ++id, element->first_name, element->last_name, element->points);
                return;
            }
            element=element->next;
        }
        pointer = pointer->next;
    }
    printf("Player %s not found", player_name);
}


void displayAllTeams(Team* list)//, float PrzedzialA, float PrzedzialB)
{
    if (list == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    while (list != NULL)
    {
        {
            printf("%d %s [ %d ]", list->id, list->team_name, list->number_of_players);
            printf("\n-----------------------------------\n");
        }
        list = list->next;
    }
}

int displayTeamPlayersDetails(Player* list) // 0 - brak id,  1-OK
{
    if (list == NULL)
    {
        printf("List is empty!\n");
        return 0;
    }

    while (list != NULL)
    {
        printf("\n\t  * %d %s %s",list->id, list->first_name, list->last_name);
        list = list->next;
    }
    return 1;
}

int displayTeamDetails(Team* list, char team_name[CHAR_MAX_LENGTH]) // 0 - brak id,  1-OK
{
    if (list == NULL)
    {
        printf("List is empty!\n");
        return 0;
    }

    while (list != NULL)
    {
        if (strcmp(list->team_name,team_name)==0)
        {
            printf("%d %s", list->id, list->team_name);

            printf("\n  Total score: %d", list->table_score);
            printf("\n  Total balance: %d", list->balance);
            printf("\n  Games played: %d", list->total_number_of_games_played);
            printf("\n  Successful throws: %d", list->throws_success);
            printf("\n  Failed throws: %d", list->throws_fail);
            printf("\n  Players: ");
            if (list->head != NULL)
            {
                displayTeamPlayersDetails(list->head);
            }

            printf("\n-----------------------------------\n");
        }
        list = list->next;
    }
    return 1;
}
// END OF DISPLAY

// RANKING
void showRanking(Team* list)
{
    if (list == NULL || list->next == NULL)
    {
        printf("There must be at least 2 team in database!");
        return;
    }

    Team* element = list;
    int first = 0;
    int x=getListSize(list);
    while (x>=0)
    {
        element = list;
        while (element->next!=NULL)
        {
            if (compareTeam(element, element->next)==2)
            {
                swapTeam(element, element->next);
            }
            element=element->next;
        }
        x--;
    }

    element = list;
    int rank = 0;
    while (element!=NULL)
    {
        printf("%d %s %d %d \n", ++rank, element->team_name, element->table_score, element->balance);
        element = element->next;
    }
}

int compareTeam(Team* t1, Team* t2)   //1 - left, 2 - right, 0 equal
{

    if (t1->table_score > t2->table_score)
    {
        return 1;
    }
    else if (t1->table_score < t2->table_score)
    {
        return 2;
    }
    else
    {
        if (t1->balance > t2->balance)
        {
            return 1;
        }
        else if (t1->balance < t2->balance)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
}

void swapTeam(Team* t1, Team* t2)
{

    if (t1!=NULL && t2!=NULL)
    {
        Team* temp = (Team*)malloc(sizeof(Team));
        temp->id = t1->id;
        temp->balance = t1->balance;
        temp->head = t1->head;
        temp->number_of_players = t1->number_of_players;
        temp->table_score = t1->table_score;
        strcpy(temp->team_name, t1->team_name);
        temp->throws_fail = t1->throws_fail;
        temp->throws_success = t1->throws_success;
        temp->total_number_of_games_played = t1->total_number_of_games_played;


        t1->id = t2->id;
        t1->balance = t2->balance;
        t1->head = t2->head;
        t1->number_of_players = t2->number_of_players;
        t1->table_score = t2->table_score;
        strcpy(t1->team_name, t2->team_name);
        t1->throws_fail = t2->throws_fail;
        t1->throws_success = t2->throws_success;
        t1->total_number_of_games_played = t2->total_number_of_games_played;


        t2->id = temp->id;
        t2->balance = temp->balance;
        t2->head = temp->head;
        t2->number_of_players = temp->number_of_players;
        t2->table_score = temp->table_score;
        strcpy(t2->team_name, temp->team_name);
        t2->throws_fail = temp->throws_fail;
        t2->throws_success = temp->throws_success;
        t2->total_number_of_games_played = temp->total_number_of_games_played;



    }
}

int getListSize(Team* team)
{

    int size = 0;
    if (team == NULL)
    {
        return size;
    }
    while (team != NULL)
    {
        size++;
        team=team->next;
    }

    return size;
}
// END OF RANKING

// CLEAR
void clearScoreboard(Team* team) {
    Team* pointer = team;
    while (pointer != NULL) {
        pointer->balance=0;
        pointer->table_score=0;
        pointer->throws_fail=0;
        pointer->throws_success=0;
        pointer->total_number_of_games_played=0;
        Player* player = pointer->head;
        while (player!=NULL) {
            player->assists=0;
            player->blocks=0;
            player->efficiency=0.0;
            player->points=0;
            player->rebounds=0;
            player=player->next;
        }
        pointer=pointer->next;
    }



}

int main()
{
    int teamsInDatabase = 0;
    int teamsDeleted = 0;
    Team* list = NULL;

    if (readDataFromNBADatabase(&list, &teamsInDatabase))
        printf("Loaded NBA database from file.\nNumber of teams in database: %d\n", teamsInDatabase);

    int choice = 1;
    while (choice != 0)
    {
        printf("\n\n\n\n\n");
        printf("1. Display all teams\n");
        printf("2. Display team details\n");
        printf("3. Find player by name\n");
        printf("4. Add new team\n");
        printf("5. Add new player\n");
        printf("6. Edit team\n");
        printf("7. Edit player\n");
        printf("8. Delete team\n");
        printf("9. Delete player\n");
        printf("10. Ranking\n");
        printf("11. Clear Scoreboard\n");
        printf("0. Save database and exit\n\n");
        printf("Selected option: ");
        scanf("%d", &choice);
        printf("\n-----------------------------------\n");
        fflush(stdin);
        switch (choice)
        {
        case 0:
            //if (list != NULL) // je¿eli lista nie jest utworzona, bez sensu próbowaæ j¹ zapisaæ do pliku czy te¿ zwolniæ pamiêæ.
        {
            if (!saveDataToFile(list))
                printf("Saving players to file failed.");

            if (!emptyListMemory(list))
                printf("Error while trying to empty list");
        }
        break;

        case 1:
            displayAllTeams(list);
            break;
        case 2:
        {
            char team_name[CHAR_MAX_LENGTH];
            fflush(stdin);

            printf("Enter team's name: ");
            fgets(&team_name, CHAR_MAX_LENGTH, stdin);
            (team_name)[strcspn(team_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            displayTeamDetails(list, team_name);
        };
        break;
        case 3:
        {
            char player_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter player's full name: ");
            fgets(&player_name, CHAR_MAX_LENGTH, stdin);
            (player_name)[strcspn(player_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            displayPlayerDetails(&list,player_name);
        };
        break;
        case 4:
        {
            if (addNewTeam(&list))
                teamsInDatabase++;
        };
        break;
        case 5:
        {
            char team_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter team's name: ");
            fgets(&team_name, CHAR_MAX_LENGTH, stdin);
            (team_name)[strcspn(team_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            addNewPlayer(&list, team_name);
        };
        break;
        case 6: // edit team
        {
            char team_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter team's name: ");
            fgets(&team_name, CHAR_MAX_LENGTH, stdin);
            (team_name)[strcspn(team_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            editTeam(list, team_name);
        };
        break;
        case 7: // edit pleja'r
        {
            char player_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter player's full name: ");
            fgets(&player_name, CHAR_MAX_LENGTH, stdin);
            (player_name)[strcspn(player_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            editPlayer(list,player_name);

        };
        break;
        case 8:
        {
            char team_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter team's name: ");
            fgets(&team_name, CHAR_MAX_LENGTH, stdin);
            (team_name)[strcspn(team_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            if (!deleteTeam(&list, team_name))
                printf("Team with this name does not exist");
            else
                teamsDeleted++;
        };
        break;
        case 9:
        {
            char player_name[CHAR_MAX_LENGTH];
            fflush(stdin);
            printf("Enter player's full name: ");
            fgets(&player_name, CHAR_MAX_LENGTH, stdin);
            (player_name)[strcspn(player_name, "\r\n")] = 0;
            printf("-----------------------------------\n");
            deletePlayer(&list,player_name);

        };
        break;
        case 10:
        {
            showRanking(list);
            break;
        }
         case 11:
        {
            clearScoreboard(list);
            break;
        }
        default:
            printf("Incorrect!");
            break;
        }

    }
    return 0;
}
