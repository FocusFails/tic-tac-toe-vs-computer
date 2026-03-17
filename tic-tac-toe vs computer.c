#include <stdio.h>
#include <stdlib.h>

// --- Prototypes ---
void drawBoard(char board[3][3]);
void resetBoard(char board[3][3]);
int checkFreeSpace(char board[3][3]);
int play(char board[3][3]);
char checkWinner(char board[3][3]);
void get_player_move(char board[3][3]);
int check_winning_move(char board[3][3], char mark, int rowcol[2]);
void calculate_computer_move(char board[3][3]);
void updatelb(char name[10], int score);
void displaylb();
int menu();

// --- Structure ---
struct player_info {
    char name[10];
    int score;
}info;

// --- Initializing characters ---
char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};
const char player_mark = 'X';
const char computer_mark = 'O';

// --- Main Function ---

int main() {
    info.score = 0;
    int score, choice =0;
    float difficulty;
    printf("Welcome to Tic-Tac-Toe vs Computer\
           \nThe board layout is shown below: \n");
    drawBoard(board);
    choice = menu();

    while (choice !=3 ) {
        if (choice == 1) {
                printf("\nEnter your name: ");
                scanf(" %s", info.name);
                resetBoard(board);
                score = play(board);
                info.score += score;
                printf("\nYour current score is: %d", info.score);
                updatelb(info.name, info.score);
                }
        // Display leaderboard
        if (choice == 2) {
                displaylb(); }

        choice = menu();
    }
        // Quit game
        if (choice == 3) {
            printf("\nQuitterrrr.\
                  \nGood-bye :P\n");
            return 0;
        }
}

// --- User-defined Functions ---

int menu() {
    int choice;
    while(1) {
        printf("\nEnter one of the following options:\
               \n1 - Play\
               \n2 - Show leaderboard\
               \n3 - Quit (loser move)\
               \nYour choice: ");

        // Scan and Validate input data type
        if (scanf("%d", &choice) != 1) {  // scanf() returns 1 if input matches variable
        while (getchar() != '\n');  // Clears buffer caused by wrong input
        printf("\n-___- \
               \nEnter a valid number.\n");
        continue;
        }
        else break;
    }
    return choice;
}

void drawBoard(char board[3][3]) {
    // Draws the board
    printf("\n-------------\n");
    printf("| %c | %c | %c |", board[0][0], board[0][1], board[0][2]);
    printf("\n-------------\n");
    printf("| %c | %c | %c |", board[1][0], board[1][1], board[1][2]);
    printf("\n-------------\n");
    printf("| %c | %c | %c |", board[2][0], board[2][1], board[2][2]);
    printf("\n-------------\n");
}

void resetBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {board[i][j] = ' ';}
    }
}

int checkFreeSpace(char board[3][3]) {
    int free = 0;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') { free++; }
        }
    }
    return free;
}

int play(char board[3][3]) {

    char win = checkWinner(board);
    int move =0;
    while (win == 'N' && checkFreeSpace(board)>0) {
            drawBoard(board);
            get_player_move(board);

            win = checkWinner(board);
            if (win == player_mark) {
                    drawBoard(board);
                    printf("\nYou won?!?!? HOW???!! \n");
                    return 1;
                } //Player wins, score increases by 1

            if(checkFreeSpace(board) >0) {
                calculate_computer_move(board);
                win = checkWinner(board);
                }
            if (win == computer_mark) {
                drawBoard(board);
                printf("\nI won, hehe >:) \n");
                return 0;
                } //Player lost. Score remains same
            if (checkFreeSpace(board) == 0) {
                drawBoard(board);
                printf("\nAw. So it's a draw, huh :/ \n");
                return 0;
                } //Player drew. Score remains same
    }
}

void get_player_move(char board[3][3]) {
    // Initializin stuffffffffffffff
    int move, row, col;

    while(1) {
        // Asks for square (1-9)
        printf("Enter a square: ");

        // Scan and Validate input data type
        if (scanf("%d", &move) != 1) {
        while (getchar() != '\n'); // Clears buffer caused by wrong input
        printf("\n-___- \
               \nEnter a valid number.\n");
        continue;
        }

        // Calculate row & column
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        //Validate square
        if (move<1 || move >9) {
                printf("Invalid: Choose square between 1-9.\n");
                continue;
        }
        else if (board[row][col] != ' ') {
                printf("Invalid: Choose an empty square.\n");
                continue;
        }

        // Place player's mark at chosen square
        else {
            board[row][col] = player_mark;
            break;
        }
    }
}

void calculate_computer_move(char board[3][3]) { int row, col, rowcol[2];

    // Place an 'O' in every empty square and check if it wins or not.
    // If it does, place an 'O' there to win.
    if (check_winning_move(board, computer_mark, rowcol) == 1) {
    row = rowcol[0];
    col = rowcol[1];
    // Play the chosen move
    board[row][col] = 'O';
    return;
    }

    // Place an 'X' in every empty square and check if it wins or not.
    // If it does, place an 'O' there to block the player's win.
    if (check_winning_move(board, player_mark, rowcol) == 1) {
    row = rowcol[0];
    col = rowcol[1];
    // Play the chosen move
    board[row][col] = 'O';
    return;
    }

    // If no winning moves exist, choose random row & column using rand()
    // Check if that column is occupied or not
    // If it is, repeat  again using do while loop.
    else {
        do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    // Play the chosen move
    board[row][col] = 'O';
    return;
    }
}

// This function looks into the future
int check_winning_move(char board[3][3], char mark, int rowcol[2]) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if (board[i][j] == ' ') {
                board[i][j] = mark;
                if (checkWinner(board) != 'N') {
                    rowcol[0] = i;
                    rowcol[1] = j;
                    // Reverting board back to present state
                    board[i][j] = ' ';
                    return 1;
                }
                board[i][j] = ' '; // Reverting board back to present state
            }
        }
    }
    return 0;
}

// Checks if there is a winning condition on the board at the instance its called
char checkWinner(char board[3][3]) {
    int i;
    for(i=0;i<3;i++) {
        //Checking columns for win
        if (board[i][0] != ' ' && board[i][1] == board[i][0] && board[i][1] == board[i][2]) {
                return board[i][0];
        }
        //Checking rows for win
        if(board[0][i] != ' ' && board[1][i] == board[0][i] && board[1][i] == board[2][i]) {
                return board[0][i];
        }
        }
    // Checking diagonals for win
    if (board[1][1]!= ' ' && board[1][1] == board[2][2] && board[1][1] == board[0][0]) {
            return board[1][1];
    }
    if (board[1][1]!= ' ' && board[1][1] == board[2][0] && board[1][1] == board[0][2]) {
            return board[1][1];
    }
    // Nope, continue playing
    return 'N';
}

void displaylb() {
    struct player_info leaderboard;
    FILE *fp = fopen("leaderboard.txt", "r");

    if (fp == NULL) {
        printf("\nNo leaderboard data yet.\n");
        return;
    }

    printf("\n--- LEADERBOARD ---\n");
    printf("Name\t\tScore\n");

    while (fscanf(fp, " %[^,],%d", leaderboard.name, &leaderboard.score) != EOF) {
        printf("%s\t\t%d\n", leaderboard.name, leaderboard.score);
    }
    printf("--------------------\n");
    fclose(fp);
    return;
}

/* mmm I understand the problem with this function but idk how exactly to fix the problem yet.
What I have to do: Make updatelb() read everything into a massive array, search for exact same names,
then add the integers assosicated with those names, then finally rewrite that into the original file.
How do I code allat thooooooooo*/

void updatelb(char name[10], int score) {
    FILE *fp;
    fp = fopen("leaderboard.txt", "a");
    if (fp == NULL) {return;}
    fprintf(fp, "%s,%d\n", info.name, info.score);
    fclose(fp);
}

