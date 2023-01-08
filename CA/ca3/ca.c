#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define false 0
#define true 1
#define With_name 1
#define With_place 2
#define true 1
#define SIZE 100

typedef struct POST Post;
struct POST
{
    char *content;
    int post_ID;
    int like;
    Post *next;
};

typedef struct LIKE Like;
struct LIKE
{
    Post *post;
    Like *next;
};

typedef struct ACCOUNT account;
struct ACCOUNT
{
    Like *like;
    char *username;
    char *password;
    Post *post;
    account *next;
};

char *get_input(void);
int command(char *input, account *head, int *state);
void free_word(char **input, int counter);
int convert(char *word, int counter, int state);
int signup(account *head, char **word);
int login(account *head, char **word, int *state);
void free_link(account *head);
void free_post(Post *head);
void free_like(Like *head);
int post(account *input, char *word, int state);
account *find_user(account *input, int state, char *name, int mode);
void info(account *head, int state);
int delete(account *head, char *post_id, int state);
int Fprint_user(account *head, int state, char *name);
void help(int state);
int like(account *head, int state, char *name, char *post_id);

int main()
{
    account *head = (account *)malloc(sizeof(account));
    head->next = NULL;
    head->post = NULL;
    head->like = NULL;

    int state = false;

    char *input;
    do
    {
        input = get_input();
    } while (command(input, head, &state) != 2);

    free_link(head);
}

// get string with unknown length
char *get_input(void)
{
    printf("Enter your command: \n");

    int size = SIZE;
    int counter = 0;
    char *input = (char *)calloc(sizeof(char), size);

    while (true)
    {
        if ((input[counter] = (char)getchar()) == '\n')
        {
            break;
        }
        counter++;
        if (counter == 10)
        {
            input = (char *)realloc(input, sizeof(char) * (size += (SIZE / 2)));
        }
    }
    input[counter] = '\0';
    input = (char *)realloc(input, sizeof(char) * (counter + 1));
    return input;
}

// check input and send it to functions(return :1 if input is invalid & 0 if input is valid & 2 if user want to exit)
int command(char *input, account *head, int *state)
{
    if (*input == 0)
    {
        // user just pressed enter
        free(input);
        return 1;
    }

    int counter = 0, flag = false, j = 0, post_flag = false, temp;
    int input_length = strlen(input);
    char **word = (char **)calloc(sizeof(char *), 3);

    word[0] = (char *)calloc(sizeof(char), input_length);
    // seprate string
    for (int i = 0; i < input_length; i++)
    {

        if (post_flag == false)
        {
            if (input[i] == ' ' && i == 0)
            {
                printf("\033[0;31mInvalid command\n\033[0;37mYou can use command \"help\" to see all the commands\n\n");
                free_word(word, counter);
                free(input);
                return 1;
            }
            else if (input[i] == ' ' && i != 0)
            {
                // check for '  '
                if (flag == false)
                {
                    printf("\033[0;31mInvalid command\033[0;37m(you used '  ')\n\033[0;37mYou can use command \"help\" to see all the commands\n\n");
                    free_word(word, counter);
                    free(input);
                    return 1;
                }
                // resize word
                else if (counter <= 2)
                {
                    word[counter] = (char *)realloc(word[counter], sizeof(char) * (j + 1));
                    word[counter][j] = '\0';
                    j = 0;
                    flag = false;
                }
                if (strcmp(word[0], "post") == 0)
                {
                    post_flag = true;
                }
                counter++;
                // go to next word
                if (counter <= 2)
                {
                    word[counter] = (char *)calloc(sizeof(char), (input_length - strlen(word[counter - 1])));
                }
            }
            else
            {
                // write in word
                flag = true;
                word[counter][j] = input[i];
                j++;
            }
        }
        // post content
        else
        {
            // write in word
            word[counter][j] = input[i];
            j++;
        }

        // check number of spaces''
        if (counter >= 3 && post_flag == false)
        {
            printf("\033[0;31mInvalid command\033[0;37m(too many ' ')\n\033[0;37mYou can use command \"help\" to see all the commands\n\n");
            free_word(word, counter);
            free(input);
            return 1;
        }
    }
    // resize last word
    if (j == 0)
    {
        word[counter] = (char *)realloc(word[counter], sizeof(char) * j);
    }
    else
    {
        word[counter] = (char *)realloc(word[counter], sizeof(char) * (j + 1));
        word[counter][j] = '\0';
    }

    free(input);
    // run commands
    switch (convert(word[0], counter, *state))
    {
    case 0:
        printf("\n\033[0;31mInvalid command\033[0;37m\n\033[0;37mYou can use command \"help\" to see all the commands\n\n");
        free_word(word, counter);
        return 1;
        break;
    case 1:
        temp = signup(head, word);
        if (temp == 2)
        {
            // user didnt enter password
            printf("\nHellooo! your account need a password too.\n(Just use 123 \2 i will delete everything anyway after u close this program)\n\n");
            free_word(word, counter);
            return 1;
        }
        else if (temp == 0)
        {
            // account didnt generated
            printf("\n\033[0;31mSorry! This username has been sold.\033[0;37m\n\n");
            free_word(word, counter);
            return 1;
        }
        printf("------------------------------\n");
        printf("\033[0;32mAccount generated successfully\033[0;37m\n");
        printf("------------------------------\n\n");
        free(word[0]); // free unusable command part
        free(word); // free main address

        return 0;

        break;
    case 2:
        temp = login(head, word, state);
        if (temp == 0)
        {
            printf("----------------------------------\n");
            printf("\033[0;33musername or password isn't correct\033[0;37m\n");
            printf("----------------------------------\n\n");
            free_word(word, counter);
            return 1;
        }
        else if (temp == 2)
        {
            printf("\nDidn't you miss something?? OH YEAH \"\033[0;31m\x1B[1mPASSWORD\x1B[0m\033[0;37m\"\n\n");
            free_word(word, counter);
            return 1;
        }
        printf("------------------------\n");
        printf("\033[0;32mYou are in now!!\033[0;36m Enjoy:)\033[0;37m\n");
        printf("------------------------\n\n");
        free_word(word, counter);
        return 0;

        break;
    case 3:
        temp = post(head, word[1], *state);
        if (temp == 0)
        {
            printf("\nYou really think i will let You do that??\n\033[0;31mGo and be a nice \x1B[1mBoy!\x1B[0m \033[0;32mthen \033[0;37m");
            free_word(word, counter);
            return 1;
        }
        printf("--------------\n");
        printf("\033[0;32mNew post added\033[0;37m\n");
        printf("--------------\n");
        free(word[0]); // free unusable command part
        free(word); // free main address
        return 0;
        break;
    case 4:
        switch (like(head, *state, word[1], word[2]))
        {
        case 0:
            printf("\n----------\n");
            printf("\033[0;32mPost Liked\033[0;37m\n");
            printf("----------\n\n");
            free_word(word, counter);
            return 0;
            break;
        case 1:
            printf("\nPost_id is incorrect\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 2:
            printf("\nYou missed Post_id!!\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 3:
            printf("\nNo post found.\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 4:
            printf("\nYou Liked that post before.\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 5:
            printf("\nNo user found.\n\n");
            free_word(word, counter);
            return 1;
            break;
        }
        break;
    case 5:
        *state = false;
        printf("-----------------------------------\n");
        printf("\033[0;33mLogout? \033[0;37mOK shut the door behind you\n");
        printf("-----------------------------------\n");
        free_word(word, counter);
        return 0;
        break;
    case 6:
        switch (delete (head, word[1], *state))
        {
        case 3:
            printf("\nYou dont have any post. Make one then come back to me!\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 2:
            printf("\nCan I read your mind?? \033[0;31m\x1B[1mNO\x1B[0m!!\033[0;37m you have to tell me which post you want to delete.\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 1:
            printf("\nYou dont have a post with that id\n\n");
            free_word(word, counter);
            return 1;
            break;
        }
        printf("--------------------------\n");
        printf("\033[0;32mPost deleted succesfully!!\033[0;37m\n");
        printf("--------------------------\n");
        free_word(word, counter);
        return 0;
        break;
    case 7:
        info(head, *state);
        free_word(word, counter);
        return 0;
        break;
    case 8:
        switch (Fprint_user(head, *state, word[1]))
        {
        case 0:
            free_word(word, counter);
            return 0;
            break;
        case 1:
            printf("\nCouldnt find user.\n\n");
            free_word(word, counter);
            return 1;
            break;
        case 2:
            printf("\nFind who?? Adolf Hitler?\n\n");
            free_word(word, counter);
            return 1;
            break;
        }
        break;
    case 9:
        help(*state);
        free_word(word, counter);
        return 0;
        break;
    case 10:
        // exit
        printf("\033[0;36mYou really wana leave me?\n\033[0;35mOK I will delete everything you just did HAH HAH HAH\n");
        free_word(word, counter);
        return 2;
        break;
    }
}

// convert word to number
int convert(char *word, int counter, int state)
{
    if (strcmp(word, "help") == 0 && counter == 0)
    {
        return 9;
    }
    else if (strcmp(word, "leave") == 0 && counter == 0)
    {
        return 10;
    }
    else if (state == false)
    {
        if (strcmp(word, "signup") == 0 && counter == 2)
        {
            return 1;
        }
        else if (strcmp(word, "login") == 0 && counter == 2)
        {
            return 2;
        }
    }
    else
    {
        if (strcmp(word, "post") == 0 && counter == 1)
        {
            return 3;
        }
        else if (strcmp(word, "like") == 0 && counter == 2)
        {
            return 4;
        }
        else if (strcmp(word, "logout") == 0 && counter == 0)
        {
            return 5;
        }
        else if (strcmp(word, "delete") == 0 && counter == 1)
        {
            return 6;
        }
        else if (strcmp(word, "info") == 0 && counter == 0)
        {
            return 7;
        }
        else if (strcmp(word, "find_user") == 0 && counter == 1)
        {
            return 8;
        }
    }

    return 0;
}

// return : 1 if account generated & 0 if its username has been used & 2 if user didnt enter any password
int signup(account *head, char **word)
{
    if ((int)word[2] == 0)
    {
        return 2;
    }

    // word[1] = username && word[2] = password
    account *cur = head->next;
    account *before = head;

    while (cur != NULL)
    {
        if (strcmp(cur->username, word[1]) == 0)
        {
            // account with this username exist
            return 0;
        }
        cur = cur->next;
        before = before->next;
    }

    // new account
    cur = (account *)malloc(sizeof(account));
    cur->post = (Post *)malloc(sizeof(Post));
    cur->like = (Like *)malloc(sizeof(Like));
    before->next = cur;
    cur->next = NULL;
    cur->post->next = NULL;
    cur->post->post_ID = 0;
    cur->like->next = NULL;
    cur->like->post = NULL; ////////////////

    cur->username = word[1];
    cur->password = word[2];
    return 1; // account generated
}

// return : 1 if login successfully & 2 if if user didnt enter any password
int login(account *head, char **word, int *state)
{
    if ((int)word[2] == 0)
    {
        return 2;
    }

    // word[1] = username && word[2] = password
    account *cur = head->next;
    int counter = 1;

    while (cur != NULL)
    {
        if (strcmp(cur->username, word[1]) == 0 && strcmp(cur->password, word[2]) == 0)
        {
            *state = counter;
            return 1;
        }
        counter++;
        cur = cur->next;
    }
    return 0;
}

// free **pointers
void free_word(char **input, int counter)
{
    for (int i = 0; i <= counter; i++)
    {
        free(input[i]);
    }
    free(input);
}

// free accounts
void free_link(account *head)
{
    account *cur = head->next;

    while (cur != NULL)
    {
        if (cur->next != NULL)
        {
            head->next = cur->next;
            cur->next = NULL;
            if (cur->post != NULL)
            {
                free_post(cur->post);
            }
            free(cur->username);
            free(cur->password);
            if (cur->like != NULL)
            {
                free_like(cur->like);
            }
            free(cur);
            cur = head->next;
        }
        else
        {
            if (cur->post != NULL)
            {
                free_post(cur->post);
            }
            free(cur->username);
            free(cur->password);
            if (cur->like != NULL)
            {
                free_like(cur->like);
            }
            free(cur);
            cur = NULL;
        }
    }
    head->next = NULL;
    free(head);
}

// free posts
void free_post(Post *head)
{
    Post *cur = head->next;

    while (cur != NULL)
    {
        if (cur->next != NULL)
        {
            head->next = cur->next;
            cur->next = NULL;
            free(cur->content);
            free(cur);
            cur = head->next;
        }
        else
        {
            free(cur->content);
            free(cur);
            cur = NULL;
        }
    }
    free(head);
}

// free likes
void free_like(Like *head)
{
    Like *cur = head->next;

    while (cur != NULL)
    {
        if (cur->next != NULL)
        {
            head->next = cur->next;
            cur->next = NULL;
            free(cur);
            cur = head->next;
        }
        else
        {
            free(cur);
            cur = NULL;
        }
    }
    free(head);
}

// return : 1 if post succesfully added & 0 if its not
int post(account *input, char *word, int state)
{
    if ((int)word == 0)
    {
        // user didnt enter anything
        return 0;
    }

    Post *head = (find_user(input, state, "NULL", With_place)->post);

    // find latest post
    /*if (head == NULL)
    {
        head = (Post *)malloc(sizeof(Post));
        head->next = NULL;
        head->post_ID = 0;
    }*/


    Post *cur = head->next;
    Post *before = head;

    while (cur != NULL)
    {
        cur = cur->next;
        before = before->next;
    }

    cur = (Post *)malloc(sizeof(Post));
    cur->content = word;
    cur->like = 0;
    cur->post_ID = before->post_ID + 1;
    cur->next = NULL;
    before->next = cur;
}

// find user . mode : 1 with username & 2 with its place
account *find_user(account *input, int state, char *name, int mode)
{
    account *input_cur = input->next;

    switch (mode)
    {
    case With_name:
        while (strcmp(input_cur->username, name) != 0 && input_cur != NULL)
        {
            input_cur = input_cur->next;
        }
        if (strcmp(input_cur->username, name) == 0)
        {
            // found user
            return input_cur;
        }
        // user didnt exist
        return NULL;
        break;

    case With_place:
        for (int i = 1; i < state; i++)
        {
            input_cur = input_cur->next;
        }
        return input_cur;
        break;
    }
}

void info(account *head, int state)
{
    account *cur = find_user(head, state, "NULL", With_place);
    Post *post_cur = cur->post->next;
    printf("Username: %s\n", cur->username);
    printf("Password: %s\n", cur->password);

    if (post_cur != NULL)
    {
        printf("---------------------------------------------------------\n");
    }
    while (post_cur != NULL)
    {
        printf("\033[0;36mContent: \033[0;37m%s | \033[0;35mLike: \033[0;37m%d | \033[0;32mPost_Id: \033[0;37m%d\n", post_cur->content, post_cur->like, post_cur->post_ID);
        printf("---------------------------------------------------------\n");
        post_cur = post_cur->next;
    }
}

// return : 3 if user doest have any post & 2 if user didnt enter post_id & 1 if user doesnt have a post with that id & 0 if delete post succesfully
int delete(account *head, char *post_id, int state)
{
    // if user didnt enter post_id
    if ((int)post_id == 0)
    {
        return 2;
    }

    // check that input post_id be digits
    for (int i = 0; i < strlen(post_id); i++)
    {
        if (isdigit(post_id[i]) == 0)
        {
            return 1;
        }
    }
    // post_id should be more than 0
    if (atoi(post_id) == 0)
    {
        return 1;
    }

    account *cur = find_user(head, state, NULL, With_place);
    Post *cur_post = cur->post;

    // check if there there is any post
    if (cur_post == NULL)
    {
        return 3;
    }
    if (cur_post->next == NULL)
    {
        return 3;
    }

    Post *before = cur->post;
    cur_post = cur_post->next;

    // find the chosen post
    while (cur_post != NULL)
    {
        if (cur_post->post_ID == atoi(post_id))
        {
            // found
            break;
        }
        before = before->next;
        cur_post = cur_post->next;
    }
    if (cur_post == NULL)
    {
        // if user doesnt have that post
        return 1;
    }

    // delete and free post
    before->next = cur_post->next;
    cur_post->next = NULL;
    free(cur_post->content);
    free(cur_post);

    return 0;
}

// find user and print its info .return: 1 if couldnt find that user & 2 if user didnt enter a name & 0 if found the user
int Fprint_user(account *head, int state, char *name)
{
    // if user didnt enter name
    if ((int)name == 0)
    {
        return 2;
    }

    account *user = find_user(head, state, name, With_name);
    if (user == NULL)
    {
        // that user doesnt exist
        return 1;
    }

    Post *post_cur = user->post->next;
    printf("Username: %s\n", user->username);

    // print its user.
    if (post_cur != NULL)
    {
        printf("---------------------------------------------------------\n");
    }
    while (post_cur != NULL)
    {
        printf("\033[0;36mContent: \033[0;37m%s | \033[0;35mLike: \033[0;37m%d | \033[0;32mPost_Id: \033[0;37m%d\n", post_cur->content, post_cur->like, post_cur->post_ID);
        printf("---------------------------------------------------------\n");
        post_cur = post_cur->next;
    }
    return 0;
}

// print valid commands for user
void help(int state)
{
    printf("\nYou can use these commands in your current state:\n\n");
    printf("leave\n");
    if (state == false)
    {
        printf("signup <user name> <password>\n");
        printf("login <user name> <password>\n");
    }
    else
    {
        printf("post <text>\n");
        printf("like <user name> <post ID>\n");
        printf("logout\n");
        printf("delete <post_id>\n");
        printf("info\n");
        printf("find_user <username>\n");
    }
    printf("\nNow pick one\n\n");
}

// return:0 liked succesfully & 5 if user not found & 2 if user didnt enter post_id & 1 if post_id isn't correct & 3 if No post found & 4 liked that post before
int like(account *head, int state, char *name, char *post_id)
{
    account *chosen = find_user(head, state, name, With_name);
    if (chosen == NULL)
    {
        // check chosen user existant
        return 5;
    }
    // if user didnt enter post_id
    if ((int)post_id == 0)
    {
        return 2;
    }

    // check that input post_id be digits
    for (int i = 0; i < strlen(post_id); i++)
    {
        if (isdigit(post_id[i]) == 0)
        {
            return 1;
        }
    }
    // post_id should be more than 0
    if (atoi(post_id) == 0)
    {
        return 1;
    }

    account *user = find_user(head, state, NULL, With_place);
    Post *post = chosen->post;
    // check if there there is any post
    if (post == NULL)
    {
        return 3;
    }
    if (post->next == NULL)
    {
        return 3;
    }

    post = post->next;

    // find the chosen post
    while (post != NULL)
    {
        if (post->post_ID == atoi(post_id))
        {
            // found
            break;
        }
        post = post->next;
    }
    if (post == NULL)
    {
        // if user doesnt have that post
        return 3;
    }

    // like that post
    Like *cur = user->like;

    while (cur != NULL)
    {
        if (cur->post == post)
        {
            // user liked that post before
            return 4;
        }
        if (cur->next == NULL)
        {
            break;
        }
        cur = cur->next;
    }
    cur->next = (Like *)malloc(sizeof(Like));
    cur = cur->next;
    cur->post = post;
    cur->next = NULL;
    post->like += 1;
    return 0;
}
