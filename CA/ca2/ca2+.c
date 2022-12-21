#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGHT 17
#define WIDTH 61
#define WIDTH2 45
#define TAP_SIZE 8
#define MAX_ROUND 6
#define MAX_SET 5

char show_card_symbol(int cards[4][11], int card);
int show_card_number(int cards[4][11], int card);
void shuffle_card(int *card);
void board(int cards[4][11], int pc1, int pc2, int pc3, int pc4, int *round, int *set);
void control(int cards[4][11], int *card_number);
void deal_cards(int *player, int *card, int s_player, int *s_card, int n_cards);
int buffer(void);
int bot(int cards[4][11], int bot, int first_player, char trump, char symbol /*playing symbol card*/, int *player_act, int player[4][11] /*player cards*/);
int winner(int cards[4][11], char trump, char symbol, int *player_act, int player[4][11]);
int rule(int cards[4][11], char symbol, int *plater_act, int player[4][11]);
int check_teammate(int cards[4][11], int bot, char trump, char symbol, int *player_act, int player[4][11]);

int main()
{
    int set[2] = {0, 0}, round[2] = {0, 0}, flag = 1, winner_player = 0, player[4][11] /*players hand */, player_act[4] /*players chose*/, s_card = 0, card[44], cards[4][11] /*ABCD*/;
    char trump /*hokm :)*/;

    /*cards array*/
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cards[i][j] = j + 1;
        }
    }

    /*set start*/
    while (set[0] < MAX_SET && set[1] < MAX_SET)
    {
        winner_player = 0;
        s_card = 0;
        shuffle_card(card);

        /*default player cards = 0 && default player acts*/
        for (int i = 0; i < 4; i++)
        {
            player_act[i] = -1;
            for (int j = 0; j < 11; j++)
            {
                player[i][j] = -1;
            }
        }

        /*deal 5 cards to players*/
        for (int i = 0; i < 4; i++)
        {
            deal_cards(player[i], card, 0, &s_card, 5);
        }

        /*select trump*/
        board(cards, -1, -1, -1, -1, round, set);
        control(cards, player[0]);
        while (1)
        {
            do
            {
                printf("Choose game trump: ");
                scanf("%c", &trump);
            } while (buffer());

            if (trump == 'a' || trump == 'A')
            {
                trump = 'A';
                break;
            }
            else if (trump == 'b' || trump == 'B')
            {
                trump = 'B';
                break;
            }
            else if (trump == 'c' || trump == 'C')
            {
                trump = 'C';
                break;
            }
            else if (trump == 'd' || trump == 'D')
            {
                trump = 'D';
                break;
            }
            else
            {
                printf("Invalid symbol!!\n\nsymbols are A,B,C,D\n");
            }
        }
        printf("You choosed %c\n", trump);
        getchar();

        /*deal 4 cards to players*/
        for (int i = 0; i < 4; i++)
        {
            deal_cards(player[i], card, 5, &s_card, 4);
        }

        /*deal 2 cards to players*/
        for (int i = 0; i < 4; i++)
        {
            deal_cards(player[i], card, 9, &s_card, 2);
        }

        /*round start*/
        while (round[0] < MAX_ROUND && round[1] < MAX_ROUND)
        {
            /*user is first*/
            if (winner_player == 0)
            {
                board(cards, -1, -1, -1, -1, round, set);
                control(cards, player[0]);

                /*user move*/
                do
                {
                    do
                    {
                        printf("Choose your card: ");
                        scanf("%d", &player_act[0]);
                    } while (buffer());

                    if (0 <= player_act[0] && player_act[0] < 11)
                    {
                        /*check user card existant*/
                        if (show_card_symbol(cards, player[0][player_act[0]]) != '-')
                        {
                            flag = 0;
                        }
                        else
                        {
                            printf("You played that card before!!\n");
                        }
                    }
                    else
                    {
                        printf("your input should be between 0 and 10\n");
                    }

                } while (flag);
                flag = 1;

                printf("You choosed %c%d\n", show_card_symbol(cards, player[0][player_act[0]]), show_card_number(cards, player[0][player_act[0]]));
                getchar();

                /*bot moves*/
                for (int i = 1; i < 4; i++)
                {
                    player_act[i] = bot(cards, i, winner_player, trump, show_card_symbol(cards, player[winner_player][player_act[winner_player]]), player_act, player);
                }

                board(cards, player[0][player_act[0]], player[1][player_act[1]], player[2][player_act[2]], player[3][player_act[3]], round, set);
                getchar();

                /*show winner*/
                winner_player = winner(cards, trump, show_card_symbol(cards, player[winner_player][player_act[winner_player]]), player_act, player);
                printf("        ******************** PLAYER %d WINS ********************\n", winner_player + 1);

                /*update teams points*/
                if (winner_player % 2 == 0)
                {
                    round[0]++;
                }
                else
                {
                    round[1]++;
                }

                /*update players hand*/
                for (int i = 0; i < 4; i++)
                {
                    player[i][player_act[i]] = -1;
                }
            }
            else // bot is first
            {
                for (int i = winner_player; i < winner_player + 4; i++)
                {
                    if (i % 4 == 0)
                    {
                        /*player turn*/
                        board(cards, player[0][player_act[0]], player[1][player_act[1]], player[2][player_act[2]], player[3][player_act[3]], round, set);
                        control(cards, player[0]);

                        do
                        {
                            do
                            {
                                printf("Choose your card: ");
                                scanf("%d", &player_act[0]);
                            } while (buffer());

                            if (0 <= player_act[0] && player_act[0] < 11)
                            {
                                /*check user card existant*/
                                if (show_card_symbol(cards, player[0][player_act[0]]) != '-')
                                {
                                    /*check user respect game law*/
                                    if (!rule(cards, show_card_symbol(cards, player[winner_player][player_act[winner_player]]), player_act, player))
                                    {
                                        printf("respect game law!!!!\nYou have to play a card with playing symbol:)\n\n");
                                    }
                                    else
                                    {
                                        flag = 0;
                                    }
                                }
                                else
                                {
                                    printf("You played that card before!!\n");
                                }
                            }
                            else
                            {
                                printf("your input should be between 0 and 10\n");
                            }

                        } while (flag);
                        flag = 1;

                        printf("You choosed %c%d\n", show_card_symbol(cards, player[0][player_act[0]]), show_card_number(cards, player[0][player_act[0]]));
                        getchar();
                    }
                    else
                    {
                        /*bot turn*/
                        player_act[i % 4] = bot(cards, i % 4, winner_player, trump, show_card_symbol(cards, player[winner_player][player_act[winner_player]]), player_act, player);
                    }
                }

                board(cards, player[0][player_act[0]], player[1][player_act[1]], player[2][player_act[2]], player[3][player_act[3]], round, set);
                getchar();

                /*show winner*/
                winner_player = winner(cards, trump, show_card_symbol(cards, player[winner_player][player_act[winner_player]]), player_act, player);
                printf("        ******************** PLAYER %d WINS ********************\n", winner_player + 1);

                /*update teams points*/
                if (winner_player % 2 == 0)
                {
                    round[0]++;
                }
                else
                {
                    round[1]++;
                }

                /*update players hand*/
                for (int i = 0; i < 4; i++)
                {
                    player[i][player_act[i]] = -1;
                }
            }
        }

        /*update sets*/
        if (round[0] == MAX_ROUND && round[1] == 0)
        {
            printf("        ******************** TEAM 1 TAKE 2 SETS ********************\n");
            set[0] += 2;
        }
        else if (round[1] == MAX_ROUND && round[0] == 0)
        {
            printf("        ******************** TEAM 2 TAKE 2 SETS ********************\n");
            set[1] += 2;
        }
        else if (round[0] > round[1])
        {
            printf("        ******************** TEAM 1 TAKE 1 SET ********************\n");
            set[0]++;
        }
        else
        {
            printf("        ******************** TEAM 2 TAKE 1 SET ********************\n");
            set[1]++;
        }
        round[0] = 0;
        round[1] = 0;
    }

    /*final Winner*/
    if (set[0] > set[1])
    {
        printf("        ******************** TEAM 1 WINS ********************\n");
        printf("        Dont proud of yourself, You just win from some Bots :)\n");
    }
    else
    {
        printf("        ******************** TEAM 1 WINS ********************\n");
        printf("        OMG XD, You really lose from bots XDDDDDD LOOOOOOOOOOOOOl\n");
    }
}

/*check that user is respecting to game law or not*/
int rule(int cards[4][11], char symbol, int *plater_act, int player[4][11])
{
    if (symbol != show_card_symbol(cards, player[0][plater_act[0]]))
    {
        /*check if player has a symbol card or not*/
        for (int i = 0; i < 11; i++)
        {
            if (show_card_symbol(cards, player[0][i]) == symbol)
            {
                return 0;
            }
        }
    }
    return 1;
}

/*winner*/
int winner(int cards[4][11], char trump, char symbol, int *player_act, int player[4][11])
{
    int flag = 0, chosen_cards[4], counter = 0, final_card = 0;

    /*check for trump*/
    for (int i = 0; i < 4; i++)
    {
        if (trump == show_card_symbol(cards, player[i][player_act[i]]))
        {
            chosen_cards[counter] = i;
            counter++;
            flag = 1;
        }
    }
    if (flag) // trump exist
    {
        /*find biggest card*/
        for (int i = 0; i < counter; i++)
        {
            if (show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]) > final_card)
            {
                final_card = show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]);
            }
        }
        /*return winner player*/
        for (int i = 0; i < counter; i++)
        {
            if (final_card == show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]))
            {
                return chosen_cards[i]; // player number
            }
        }
    }

    ///////////////////////////////////////////////////////
    /*if trump didnt exist*/
    /*check for playing symbol*/
    for (int i = 0; i < 4; i++)
    {
        if (symbol == show_card_symbol(cards, player[i][player_act[i]]))
        {
            chosen_cards[counter] = i;
            counter++;
        }
    }
    /*find biggest card*/
    for (int i = 0; i < counter; i++)
    {
        if (show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]) > final_card)
        {
            final_card = show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]);
        }
    }
    /*return winner player*/
    for (int i = 0; i < counter; i++)
    {
        if (final_card == show_card_number(cards, player[chosen_cards[i]][player_act[chosen_cards[i]]]))
        {
            return chosen_cards[i]; // player number
        }
    }
}

/*BOT: when it's not*/
int bot(int cards[4][11], int bot, int first_player, char trump, char symbol /*playing symbol card*/, int *player_act /*players choice*/, int player[4][11] /*player cards*/)
{
    int counter = 0, flag = 0, chosen_cards[11], final_card = -1;

    /*BOT: when it is the first player in a round*/
    if (bot == first_player)
    {
        
        /*if he has any 10 or 11 card*/
        for (int i = 0; i < 11; i++)
        {
            if (show_card_number(cards, player[bot][i]) == 11 || show_card_number(cards, player[bot][i]) == 10)
            {
                /*return its place*/
                return i;
            }
        }

        /*if he doesnt have then:*/

        /*if he has a nontrump card*/
        final_card = -2;
        /*find them*/
        for (int i = 0; i < 11; i++)
        {
            if (trump != show_card_symbol(cards, player[bot][i]) && show_card_symbol(cards, player[bot][i]) != '-')
            {
                chosen_cards[counter] = player[bot][i];
                counter++;
                flag = 1;
            }
        }
        if (flag) // it has
        {
            flag = 0;
            /*find lowest card*/
            for (int i = 0; i < counter; i++)
            {
                if (show_card_number(cards, final_card) < show_card_number(cards, chosen_cards[i]))
                {
                    final_card = chosen_cards[i];
                }
            }
            /*return its place*/
            for (int i = 0; i < 11; i++)
            {
                if (final_card == player[bot][i])
                {
                    return i;
                }
            }
        }

        /*else: he just has trump card*/
        final_card = -2;
        /*find the lowest card*/
        for (int i = 0; i < 11; i++)
        {
            if (show_card_number(cards, final_card) > show_card_number(cards, player[bot][i]) && show_card_number(cards, player[bot][i]) > 0)
            {
                final_card = player[bot][i];
            }
        }
        /*return its place*/
        for (int i = 0; i < 11; i++)
        {
            if (final_card == player[bot][i])
            {
                return i;
            }
        }
    }

    /////////////////////////////////////////////////
    /*BOT: when it's not*/
    else
    {
        counter = 0;
        flag = 0;
        final_card = -1;

        /*if teammate played a valuable card*/
        if (check_teammate(cards, bot, trump, symbol, player_act, player))
        {
            final_card = -2;

            /*if bot has a playing symbol card*/
            for (int i = 0; i < 11; i++)
            {
                if (symbol == show_card_symbol(cards, player[bot][i]))
                {
                    chosen_cards[counter] = player[bot][i];
                    counter++;
                    flag = 1;
                }
            }
            if (flag) // it has
            {
                flag = 0;
                /*find lowest card*/
                for (int i = 0; i < counter; i++)
                {
                    if (show_card_number(cards, final_card) > show_card_number(cards, chosen_cards[i]))
                    {
                        final_card = chosen_cards[i];
                    }
                }
                /*return its place*/
                for (int i = 0; i < 11; i++)
                {
                    if (final_card == player[bot][i])
                    {
                        return i;
                    }
                }
            }

            /*if he has a nontrump card*/
            final_card = -2;
            /*find them*/
            for (int i = 0; i < 11; i++)
            {
                if (trump != show_card_symbol(cards, player[bot][i]) && show_card_symbol(cards, player[bot][i]) != '-')
                {
                    chosen_cards[counter] = player[bot][i];
                    counter++;
                    flag = 1;
                }
            }
            if (flag) // it has
            {
                flag = 0;
                /*find lowest card*/
                for (int i = 0; i < counter; i++)
                {
                    if (show_card_number(cards, final_card) > show_card_number(cards, chosen_cards[i]))
                    {
                        final_card = chosen_cards[i];
                    }
                }
                /*return its place*/
                for (int i = 0; i < 11; i++)
                {
                    if (final_card == player[bot][i])
                    {
                        return i;
                    }
                }
            }

            /*else : he just has trump cards*/
            counter = 0;
            final_card = -2;
            /*find them*/
            for (int i = 0; i < 11; i++)
            {
                if (trump == show_card_symbol(cards, player[bot][i]))
                {
                    chosen_cards[counter] = player[bot][i];
                    counter++;
                    flag = 1;
                }
            }
            if (flag) // it has
            {
                flag = 0;
                /*find lowest card*/
                for (int i = 0; i < counter; i++)
                {
                    if (show_card_number(cards, final_card) > show_card_number(cards, chosen_cards[i]))
                    {
                        final_card = chosen_cards[i];
                    }
                }
                /*return its place*/
                for (int i = 0; i < 11; i++)
                {
                    if (final_card == player[bot][i])
                    {
                        return i;
                    }
                }
            }
        }
        /*else : he didnt play a valuable card so we will do our business :)*/
        else
        {
            flag = 0;
            final_card = -1;
            /*if bot has a playing symbol card*/
            for (int i = 0; i < 11; i++)
            {
                if (symbol == show_card_symbol(cards, player[bot][i]))
                {
                    chosen_cards[counter] = player[bot][i];
                    counter++;
                    flag = 1;
                }
            }
            if (flag) // it has
            {
                flag = 0;
                /*find biggest card*/
                for (int i = 0; i < counter; i++)
                {
                    if (show_card_number(cards, final_card) < show_card_number(cards, chosen_cards[i]))
                    {
                        final_card = chosen_cards[i];
                    }
                }
                /*return its place*/
                for (int i = 0; i < 11; i++)
                {
                    if (final_card == player[bot][i])
                    {
                        return i;
                    }
                }
            }

            /*if bot doesnt have any playing symbol card. then: */

            /*if bot has a trump card*/
            counter = 0;
            final_card = -1;

            for (int i = 0; i < 11; i++)
            {
                if (trump == show_card_symbol(cards, player[bot][i]))
                {
                    chosen_cards[counter] = player[bot][i];
                    counter++;
                    flag = 1;
                }
            }
            if (flag) // it has
            {
                flag = 0;
                /*find biggest card*/
                for (int i = 0; i < counter; i++)
                {
                    if (show_card_number(cards, final_card) < show_card_number(cards, chosen_cards[i]))
                    {
                        final_card = chosen_cards[i];
                    }
                }
                /*return its place*/
                for (int i = 0; i < 11; i++)
                {
                    if (final_card == player[bot][i])
                    {
                        return i;
                    }
                }
            }

            /*else: he has nothing in his hand :)*/
            final_card = -2;
            /*find the lowest card*/
            for (int i = 0; i < 11; i++)
            {
                if (show_card_number(cards, final_card) > show_card_number(cards, player[bot][i]) && show_card_number(cards, player[bot][i]) > 0)
                {
                    final_card = player[bot][i];
                }
            }
            /*return its place*/
            for (int i = 0; i < 11; i++)
            {
                if (final_card == player[bot][i])
                {
                    return i;
                }
            }
        }
    }
}

/*check bots teammate: what did he play??*/
int check_teammate(int cards[4][11], int bot, char trump, char symbol, int *player_act, int player[4][11])
{
    int teammate = (bot + 2) % 4;
    /*he didnt play any card*/
    if (show_card_symbol(cards, player[teammate][player_act[teammate]]) == '-')
    {
        return 0;
    }
    /*he played some random card*/
    if (show_card_symbol(cards, player[teammate][player_act[teammate]]) != trump && show_card_symbol(cards, player[teammate][player_act[teammate]]) != symbol && show_card_symbol(cards, player[teammate][player_act[teammate]]) != '-')
    {
        return 0;
    }
    /*he played a symbol card*/
    if (show_card_symbol(cards, player[teammate][player_act[teammate]]) == symbol)
    {
        /*if other players played trump card*/
        if (trump == show_card_symbol(cards, player[(teammate - 1) % 4][player_act[(teammate - 1) % 4]]) && (trump != symbol))
        {
            return 0;
        }
        if (trump == show_card_symbol(cards, player[(teammate + 1) % 4][player_act[(teammate + 1) % 4]]) && (trump != symbol))
        {
            return 0;
        }
        /*check previous player card*/
        if (symbol == show_card_symbol(cards, player[(teammate - 1) % 4][player_act[(teammate - 1) % 4]]))
        {
            /*if he played a card more valuable than teammate*/
            if (show_card_number(cards, player[(teammate - 1) % 4][player_act[(teammate - 1) % 4]]) > show_card_number(cards, player[teammate][player_act[teammate]]))
            {
                return 0;
            }
        }
        /*check next player card*/
        if (symbol == show_card_symbol(cards, player[(teammate + 1) % 4][player_act[(teammate + 1) % 4]]))
        {
            /*if he played a card more valuable than teammate*/
            if (show_card_number(cards, player[(teammate + 1) % 4][player_act[(teammate + 1) % 4]]) > show_card_number(cards, player[teammate][player_act[teammate]]))
            {
                return 0;
            }
        }
    }

    /*he played a trump card*/
    if (show_card_symbol(cards, player[teammate][player_act[teammate]]) == trump)
    {
        /*check previous player card*/
        if (trump == show_card_symbol(cards, player[(teammate - 1) % 4][player_act[(teammate - 1) % 4]]))
        {
            /*if he played a card more valuable than teammate*/
            if (show_card_number(cards, player[(teammate - 1) % 4][player_act[(teammate - 1) % 4]]) > show_card_number(cards, player[teammate][player_act[teammate]]))
            {
                return 0;
            }
        }
        /*check next player card*/
        if (trump == show_card_symbol(cards, player[(teammate + 1) % 4][player_act[(teammate + 1) % 4]]))
        {
            /*if he played a card more valuable than teammate*/
            if (show_card_number(cards, player[(teammate + 1) % 4][player_act[(teammate + 1) % 4]]) > show_card_number(cards, player[teammate][player_act[teammate]]))
            {
                return 0;
            }
        }
    }
    return 1;
}

/*shuffle cards*/
void shuffle_card(int *card)
{
    int i, r, temp;
    for (temp = 0, i = 0; temp < 44; i++, temp++)
        card[temp] = i;
    srand(time(NULL));
    for (i = 43; i > 0; i--)
    {
        r = rand() % i;
        temp = card[i];
        card[i] = card[r];
        card[r] = temp;
    }
}

/*deal the cards*/
void deal_cards(int *player, int *card, int s_player, int *s_card, int n_cards) /*s_ means start point*/
{
    for (int i = 0; i < n_cards; i++)
    {
        player[s_player + i] = card[*s_card + i];
    }
    *s_card += n_cards;
}

/*show card*/
char show_card_symbol(int cards[4][11], int card)
{
    if (card == -1)
    {
        return '-';
    }

    switch (card / 11)
    {
    case 0:
        return 'A';

    case 1:
        return 'B';

    case 2:
        return 'C';

    case 3:
        return 'D';
    }
}
int show_card_number(int cards[4][11], int card)
{
    if (card == -1) // lowest number
    {
        return 0;
    }
    else if (card == -2) // biggest number
    {
        return 12;
    }
    return cards[card / 11][card % 11];
}

/*game board*/
void board(int cards[4][11], int pc1, int pc2, int pc3, int pc4, int *round, int *set) /*pc = player card*/
{
    for (int i = 0, width = WIDTH; i < HIGHT; i++)
    {
        /*print player 3*/
        if (i == 0)
        {
            printf("\t");
            for (int j = 0; j < WIDTH; j++)
            {
                if (j == WIDTH / 2)
                {
                    printf("P3");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }

        /*print player 1*/
        else if (i == HIGHT - 1)
        {
            printf("\t");
            for (int j = 0; j < WIDTH; j++)
            {
                if (j == WIDTH / 2)
                {
                    printf("P1");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }

        /*print first and last lines + teams point*/
        else if (i == 1)
        {
            printf("\t");
            for (int j = 0; j < WIDTH; j++)
            {
                printf("-");
            }
            printf("      Team 1 point: %d | set point: %d", round[0], set[0]);
            printf("\n");
        }
        else if (i == HIGHT - 2)
        {
            printf("\t");
            for (int j = 0; j < WIDTH; j++)
            {
                printf("-");
            }
            printf("      Team 2 point: %d | set point: %d", round[1], set[1]);
            printf("\n");
        }

        else
        {
            /*print player 2*/
            for (int j = 0; j < TAP_SIZE; j++)
            {
                if (i == HIGHT / 2 && j == TAP_SIZE - 3)
                {
                    printf("P");
                }
                else if (i == HIGHT / 2 && j == TAP_SIZE - 2)
                {
                    printf("2");
                }
                /*space*/
                else
                {
                    printf(" ");
                }
            }

            for (int j = 0; j < WIDTH; j++)
            {
                /*print columns*/
                if (j == 0 || j == WIDTH - 1)
                {
                    printf("|");
                }
                else
                {
                    /*player 3 card*/
                    if (j == WIDTH / 2 && i == 2)
                    {
                        if (show_card_number(cards, pc3) >= 10)
                        {
                            printf("%c", show_card_symbol(cards, pc3));
                            printf("%d", show_card_number(cards, pc3));
                            j += 2;
                        }
                        else if (pc3 == -1)
                        {
                            printf("  ");
                            j++;
                        }
                        else
                        {
                            printf("%c", show_card_symbol(cards, pc3));
                            printf("%d", show_card_number(cards, pc3));
                            j++;
                        }
                    }

                    /*player 1 card*/
                    else if (j == WIDTH / 2 && i == HIGHT - 3)
                    {
                        if (show_card_number(cards, pc1) >= 10)
                        {
                            printf("%c", show_card_symbol(cards, pc1));
                            printf("%d", show_card_number(cards, pc1));
                            j += 2;
                        }
                        else if (pc1 == -1)
                        {
                            printf("  ");
                            j++;
                        }
                        else
                        {
                            printf("%c", show_card_symbol(cards, pc1));
                            printf("%d", show_card_number(cards, pc1));
                            j++;
                        }
                    }

                    else
                    {
                        /*player 2 card*/
                        if (i == HIGHT / 2 && j == 2)
                        {
                            if (show_card_number(cards, pc2) >= 10)
                            {
                                printf("%c", show_card_symbol(cards, pc2));
                                printf("%d", show_card_number(cards, pc2));
                                j += 2;
                            }
                            else if (pc2 == -1)
                            {
                                printf("  ");
                                j++;
                            }
                            else
                            {
                                printf("%c", show_card_symbol(cards, pc2));
                                printf("%d", show_card_number(cards, pc2));
                                j++;
                            }
                        }
                        /*palyer 4 card*/
                        else if (i == HIGHT / 2 && j == WIDTH - 4)
                        {
                            if (show_card_number(cards, pc4) >= 10)
                            {
                                printf("%c", show_card_symbol(cards, pc4));
                                printf("%d", show_card_number(cards, pc4));
                                j += 2;
                            }
                            else if (pc4 == -1)
                            {
                                printf("  ");
                                j++;
                            }
                            else
                            {
                                printf("%c", show_card_symbol(cards, pc4));
                                printf("%d", show_card_number(cards, pc4));
                                j++;
                            }
                        }
                        /*space*/
                        else
                        {
                            printf(" ");
                        }
                    }
                }
            }
            /*print player 4*/
            if (i == HIGHT / 2)
            {
                printf(" P4");
            }
            printf("\n");
        }
    }
}

/*user control*/
void control(int cards[4][11], int *card_number)
{

    int keypad = 0, symbol = 0, number = 0;
    printf("            ");
    for (int i = 0; i < WIDTH2; i++)
    {
        printf("-");
    }

    /*symbols*/
    printf("\n");
    printf("  symbol    ");
    for (int i = 0; i < WIDTH2; i++)
    {
        if (i % 4 == 0)
        {
            printf("|");
        }
        else if (i % 4 == 2)
        {
            printf("%c", show_card_symbol(cards, card_number[symbol]));
            symbol++;
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");

    printf("            ");
    for (int i = 0; i < WIDTH2; i++)
    {
        printf("-");
    }
    printf("\n");

    /*number*/
    printf("  number    ");
    for (int i = 0; i < WIDTH2; i++)
    {
        if (i % 4 == 0)
        {
            printf("|");
        }
        else if (i % 4 == 2)
        {
            if (card_number[number] % 11 >= 9)
            {
                printf("%d", show_card_number(cards, card_number[number]));
                i++;
            }
            else
            {
                printf("%d", show_card_number(cards, card_number[number]));
            }
            number++;
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");

    printf("            ");
    for (int i = 0; i < WIDTH2; i++)
    {
        printf("-");
    }
    printf("\n");

    /*keypad*/
    printf("            ");
    for (int i = 0; i < WIDTH2; i++)
    {
        if (i % 4 == 2 && i != 0)
        {
            printf("%d", keypad);
            keypad++;
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

/*make buffer free*/
int buffer(void)
{
    int output = 0;
    while (getchar() != '\n')
    {
        output = 1;
    }
    return output;
}