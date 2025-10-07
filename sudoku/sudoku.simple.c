#include <stdio.h>
#include <stdlib.h>

///////////////
// CONSTANTS //
///////////////

#define TRUE    1
#define FALSE   0

#define MAX_NUM_DIGITS  16
#define MAX_BOARD_LEN   16
#define NUM_BOARD_SIZE_OPTS 3

#define DIFF_EASY   1
#define DIFF_MEDIUM 2
#define DIFF_HARD   3
#define DIFF_EXTREME 4

#define HIDDEN_FACTOR   5
#define DIFF_GRADIENT   10

#define NUM_DIFFICULTY_OPTS 4

#define HINT_KEY        'i'
#define HELP_KEY        'h'
#define EXIT_KEY        'q'
#define SOLUTION_KEY    's'
#define ENTER_KEY       'e'

#define BOARD_VERTICAL_SEPERATOR '|'
#define BOARD_CROSS_SEPERATOR '+'
#define BOARD_HORIZONTAL_SEPERATOR '-'
#define BOARD_SPACE_SEPERATOR ' '

#define MAX_MISTAKES    10
#define MAX_HINTS       10

#define INVALID         12
#define ALREADY_FILLED  13
#define MISTAKE         14
#define SUCCESS         15

#define GAME_STATE_PLAYING  0
#define GAME_STATE_OVER     1
#define GAME_STATE_WON      2

#define UNSET '#'

#define SIZEOF_INT sizeof(int)

struct board_tracker {
    int is_filled_row[MAX_BOARD_LEN][MAX_NUM_DIGITS];
    int is_filled_col[MAX_BOARD_LEN][MAX_NUM_DIGITS];
    int is_filled_box[MAX_NUM_DIGITS][MAX_NUM_DIGITS];
    char board[MAX_BOARD_LEN][MAX_BOARD_LEN];
};

#define SIZEOF_BOARD_TRACKER sizeof(struct board_tracker)

///////////////
/// GLOBALS ///
///////////////

int board_size;
int box_len;
int difficulty;
unsigned int random_seed;

int game_state;
int mistakes;
int hints_used;
int cells_remaining;

struct board_tracker solver;
struct board_tracker puzzle;

int random_digits[MAX_BOARD_LEN];
int is_digit_used[MAX_BOARD_LEN];

int board_size_opts[NUM_BOARD_SIZE_OPTS] = {4, 9, 16};

int difficulty_opts[NUM_DIFFICULTY_OPTS] = {
    DIFF_EASY, DIFF_MEDIUM, DIFF_HARD, DIFF_EXTREME
};

char digit_chars[] = "123456789ABCDEFG";

char cmd_waiting[] = "> ";

///////////////
// FUNCTIONS //
///////////////

// SUBSET 0
int main();
void print_welcome();
int get_box_num(int row, int col);

// SUBSET 1
int in_bounds(int num);
int find_box_len(int total_len);
void game_loop();
void update_game_state();
int option_is_valid(int value, int *option_list, int num_options);
void generate_puzzle();
void initialise_game(void);

// SUBSET 2
char cell_display_char(int c);
void initialise_board(char board[MAX_BOARD_LEN][MAX_BOARD_LEN]);
void initialise_digit_choices(int digit_options[MAX_BOARD_LEN]);
int is_cell_filled(struct board_tracker *tracker, int x, int y);
int handle_move(int row, int col, int digit);

// SUBSET 3
void update_cell(struct board_tracker *check, int row, int col, char new_digit); // structs
int solve(struct board_tracker *tracker, int x, int y); // recursion
void make_user_puzzle(void);
int give_hint();
void copy_mem(void *src, void *dst, int num_bytes);

// provided
unsigned int random_in_range(unsigned int min, unsigned int max);
void process_command();
int cell_char_to_num(char c);
void do_enter();
void print_hint_msg(int ans, int row, int col);
void initialise_board_tracker(struct board_tracker *tracker);
int is_valid_digit(struct board_tracker *check, int row, int col, int digit);
void print_puzzle(char board[MAX_BOARD_LEN][MAX_BOARD_LEN]);
void print_row(char row[]);
void print_box_separator(int row);

//////////////
// SUBSET 0 //
//////////////
int main(void) {

    print_welcome();

    initialise_game();

    generate_puzzle();

    game_loop();

    return 0;
}

void print_welcome(void) {
    printf("Welcome to Sudoku!\n");
    printf("To enter a number, use: %c <row> <col> <number>\n", ENTER_KEY);
    printf("To get a hint, use: %c\n", HINT_KEY);
    printf("To see this message again, use: %c\n", HELP_KEY);
    printf("To exit, use: %c\n", EXIT_KEY);
    printf("You can use up to %d hints.\n", MAX_HINTS);
    printf("If you make more than %d mistakes, you lose :(\n\n", MAX_MISTAKES);
}

int get_box_num(int row, int col) {
    row = row / box_len;
    col = col / box_len;
    return row  + box_len * (col);
}

//////////////
// SUBSET 1 //
//////////////

int in_bounds(int num) {
    if (num >= 0 && num < board_size) {
        return TRUE;
    }

    return FALSE;
}

int find_box_len(int total_len) {
    for (int i = total_len / 2; i >= 0; i--) {
        if (i * i == total_len) {
            return i;
        }
    }

    return FALSE;
}

void game_loop() {
    while (game_state == GAME_STATE_PLAYING) {
        process_command();
        update_game_state();
    }

    if (game_state == GAME_STATE_WON) {
        printf("You win!\n");
    }

    if (game_state == GAME_STATE_OVER) {
        printf("Game over :(\n");
    }

    return;
}

void update_game_state() {
    if (game_state != GAME_STATE_PLAYING) {
        return;
    }

    if (mistakes > MAX_MISTAKES) {
        game_state = GAME_STATE_OVER;
        return;
    }

    if (!cells_remaining) {
        game_state = GAME_STATE_WON;
        return;
    }

    return;
}

int option_is_valid(int value, int *option_list, int num_options) {
    for (int i = 0; i < num_options; i++) {
        if (value == option_list[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

void generate_puzzle() {
    initialise_board_tracker(&solver);

    initialise_digit_choices(random_digits);

    solve(&solver, 0, 0);

    make_user_puzzle();

    return;
}

void initialise_game(void) {
    int user_difficulty;
    int user_board_size;
    int user_random_seed;

    while (1) {
        printf("Board size options: 4 => 4x4, 9 => 9x9, 16 => 16x16\n");
        printf("Enter a board size: ");
        scanf(" %d", &user_board_size);

        board_size = user_board_size;

        if (!option_is_valid(user_board_size, board_size_opts, NUM_BOARD_SIZE_OPTS)) {
            printf("Invalid board size, choose from  4 => 4x4, 9 => 9x9, 16 => 16x16.\n");
            continue;
        }

        printf("Difficulty options: 1 => easy, 2 => medium, 3 => hard, 4 => extreme\n");
        printf("Enter a difficulty level: ");
        scanf(" %d", &user_difficulty);

        difficulty = user_difficulty;

        if (!option_is_valid(user_difficulty, difficulty_opts, NUM_DIFFICULTY_OPTS)) {
            printf("Invalid difficulty, choose from 1 => easy, 2 => medium, 3 => hard, 4 => extreme.\n");
            continue;
        }

        break;
    }

    printf("Enter a random seed: ");
    scanf(" %d", &user_random_seed);
    random_seed = user_random_seed;

    box_len = find_box_len(board_size);
    game_state = GAME_STATE_PLAYING;
    mistakes = 0;
    hints_used = 0;

    return;
}

//////////////
// SUBSET 2 //
//////////////

char cell_display_char(int c) {
    if (c == UNSET) {
        return ' ';
    }
    if (c > '0') {
        return c - 1;
    }

    return digit_chars[c];
}

void initialise_board(char board[MAX_BOARD_LEN][MAX_BOARD_LEN]) {

    for (int row = 0; row < MAX_BOARD_LEN; row++) {
        for (int col = 0; col < MAX_BOARD_LEN; col++) {
            board[row][col] = UNSET;
        }
    }
}

void initialise_digit_choices(int digit_options[MAX_BOARD_LEN]) {
    for (int i = 0; i < board_size; i++) {
        is_digit_used[i] = FALSE;
    }
    int digit;
    for (int i = 0; i < board_size; i++) {

        do {
            digit = random_in_range(0, board_size - 1);
        } while (is_digit_used[digit]);

        digit_options[i] = digit;
        is_digit_used[digit] = TRUE;
    }
}

int is_cell_filled(struct board_tracker *tracker, int x, int y) {
    if (tracker->board[x][y] != UNSET) {
        return TRUE;
    }

    return FALSE;
}

int handle_move(int row, int col, int digit) {
    if (!in_bounds(row) || !in_bounds(col) || !in_bounds(digit)) {
        return INVALID;
    }

    if (is_cell_filled(&puzzle, row, col)) {
        return ALREADY_FILLED;
    }

    if (is_valid_digit(&puzzle, row, col, digit)) {
        update_cell(&puzzle, row, col, digit);
        cells_remaining--;
        return SUCCESS;
    } else {
        mistakes++;
        return MISTAKE;
    }
}

//////////////
// SUBSET 3 //
//////////////

void update_cell(struct board_tracker *check, int row, int col, char new_digit) {
    int box = get_box_num(row, col);

    int dig = new_digit;
    int use_digit = TRUE;

    if (new_digit == UNSET) {
        dig = check->board[row][col];
        use_digit = FALSE;
    }

    if (dig == UNSET) {
        return;
    }

    check->board[row][col] = new_digit;
    check->is_filled_row[row][dig] = use_digit;
    check->is_filled_col[col][dig] = use_digit;
    check->is_filled_box[box][dig] = use_digit;

    return;
}

int solve(struct board_tracker *tracker, int x, int y) {
    if (x >= board_size) {
        return TRUE;
    }

    if (y == board_size) {
        return solve(tracker, x + 1, 0);
    }

    if (is_cell_filled(tracker, x, y)) {
        return solve(tracker, x, y + 1);
    }

    for (int i = 0; i < board_size; i++) {
        int dig = random_digits[i];
        if (is_valid_digit(tracker, x, y, dig)) {
            update_cell(tracker, x, y, dig);
            if (solve(tracker, x, y + 1)) {
                return TRUE;
            }
            update_cell(tracker, x, y, UNSET);
        }
    }
    return FALSE;
}

void make_user_puzzle(void) {
    initialise_board_tracker(&puzzle);

    int total_cells = board_size * board_size;

    int cells_to_show = total_cells / HIDDEN_FACTOR;
    cells_to_show += (NUM_DIFFICULTY_OPTS - difficulty) * total_cells / DIFF_GRADIENT + box_len;

    int num_showing = 0;

    int n, row, col;
    while (num_showing < cells_to_show) {
        n = random_in_range(0, total_cells - 1);
        row = n / board_size;
        col = n % board_size;

        if (is_cell_filled(&puzzle, row, col)) {
            continue;
        }

        update_cell(&puzzle, row, col, solver.board[row][col]);
        num_showing++;

    }

    cells_remaining = total_cells - num_showing;
}

int give_hint() {
    if (hints_used == MAX_HINTS) {
        return FALSE;
    }
    copy_mem(&puzzle, &solver, SIZEOF_BOARD_TRACKER);
    solve(&solver, 0, 0);


    int total_cells = board_size * board_size;
    int start = random_in_range(0, total_cells - 1);
    int end = start + total_cells;

    int row = 0;
    int col = 0;
    for (int i = start; i < end; i++) {

        row = (i % total_cells) / board_size;
        col = i % board_size;

        if (!is_cell_filled(&puzzle, row, col)) {
            break;
        }
    }

    int ans = solver.board[row][col];
    update_cell(&puzzle, row, col, ans);

    hints_used++;
    cells_remaining--;
    print_hint_msg(ans, row, col);

    return TRUE;
}

void copy_mem(void *src, void *dst, int num_bytes) {
    int *src_int_ptr = (int*) src;
    int *dst_int_ptr = (int*) dst;
    char *src_char_ptr;
    char *dst_char_ptr;

    for (int i = 0; i < num_bytes / SIZEOF_INT; i++) {
        *dst_int_ptr = *src_int_ptr;
        dst_int_ptr++;
        src_int_ptr++;
    }

    src_char_ptr = (char*) src_int_ptr;
    dst_char_ptr = (char*) dst_int_ptr;

    for (int i = 0; i < num_bytes % SIZEOF_INT; i++) {
        *dst_char_ptr = *src_char_ptr;
        dst_char_ptr++;
        src_char_ptr++;
    }

    return;
}


//////////////
// PROVIDED //
//////////////
unsigned int random_in_range(unsigned int min, unsigned int max) {
    int a = 103515245;
    int c = 12345;
    int m = 2147483647;
    random_seed = (a * random_seed + c) % m;
    return min + (random_seed % (max - min + 1));
}

void process_command() {
    print_puzzle(puzzle.board);
    printf("%d cells remaining...\n", cells_remaining);
    printf("%d/%d mistakes before game over.\n", mistakes, MAX_MISTAKES);
    printf("%d/%d hints used.\n", hints_used, MAX_HINTS);
    printf("%s", cmd_waiting);
    char command = getchar();
    while (command == '\n' || command == ' ') {
        command = getchar();
    }

    switch (command) {
        case EXIT_KEY:
            exit(0);
        case ENTER_KEY:
            do_enter();
            break;
        case HELP_KEY:
            print_welcome();
            break;
        case HINT_KEY:
            if (!give_hint()) {
                printf("No more hints :(\n");
            }
            break;
        default:
            printf("Unknown command: %c\n", command);
            break;
    }

    if (!cells_remaining || mistakes > MAX_MISTAKES) {
        print_puzzle(puzzle.board);
    }

    printf("\n");

    return;
}

int cell_char_to_num(char c) {
    if (c >= 'A') return c - 'A' + 10;
    return c - '0';

}

void do_enter() {
    char r, c, d;
    int row, col, digit;
    scanf(" %c", &r);

    scanf(" %c", &c);

    scanf(" %c", &d);

    row = cell_char_to_num(r);
    col = cell_char_to_num(c);
    digit = cell_char_to_num(d);

    int move_status = handle_move(row, col, digit - 1);

    if (move_status == INVALID) {
        printf("Invalid row, column or digit.\n");

    } else if (move_status == ALREADY_FILLED) {
        printf("Cell is already filled.\n");

    } else if (move_status == MISTAKE) {
        printf("Mistake!\n");

    } else if (move_status == SUCCESS) {
        printf("Success!!\n");
    }

}

void print_hint_msg(int ans, int row, int col) {
    char r = digit_chars[row] - 1;
    if (r == '@') r = '9';

    char c = digit_chars[col] - 1;
    if (c == '@') c = '9';
    printf("HINT: %c at (%c, %c)\n", cell_display_char(ans), r, c);
    printf("%d hints used, %d left.\n", hints_used, MAX_HINTS - hints_used);
}

void initialise_board_tracker(struct board_tracker *tracker) {
    initialise_board(tracker->board);

    for (int i = 0; i < MAX_BOARD_LEN; i++) {
        for (int j = 0; j < MAX_BOARD_LEN; j++) {

            tracker->is_filled_row[i][j] = FALSE;
            tracker->is_filled_col[i][j] = FALSE;
            tracker->is_filled_box[i][j] = FALSE;
        }
    }
}

int is_valid_digit(struct board_tracker *check, int row, int col, int digit) {
    int box = get_box_num(row, col);
    if (check->is_filled_col[col][digit]
        || check->is_filled_row[row][digit]
        || check->is_filled_box[box][digit]) {
        return FALSE;
    }
    return TRUE;
}

void print_puzzle(char board[MAX_BOARD_LEN][MAX_BOARD_LEN]) {
    putchar(BOARD_SPACE_SEPERATOR);
    print_row(digit_chars);
    for (int row = 0; row < board_size; row++) {
        if (row % box_len == 0) {
            print_box_separator(row);
        }
        char c = digit_chars[row] - 1;
        if (c == '@') c = '9';
        putchar(c);
        print_row(board[row]);
    }
    print_box_separator(0);

    return;
}

void print_row(char row[]) {
    for (int col = 0; col < board_size; col++) {
        if (col % box_len == 0) {
            putchar(BOARD_VERTICAL_SEPERATOR);
            putchar(BOARD_SPACE_SEPERATOR);
        }
        int c = cell_display_char(row[col]);
        if (c == '@') c = '9';
        putchar(c);
        putchar(BOARD_SPACE_SEPERATOR);

    }
    putchar(BOARD_VERTICAL_SEPERATOR);
    putchar('\n');
}

void print_box_separator(int row) {
    putchar(BOARD_HORIZONTAL_SEPERATOR);

    if (row % box_len == 0) {
        putchar(BOARD_CROSS_SEPERATOR);
        putchar(BOARD_HORIZONTAL_SEPERATOR);
    } else {
        putchar(BOARD_VERTICAL_SEPERATOR);
    }

    for (int i = 0; i < board_size; i++) {
        if (i % box_len == 0 && i != 0) {
            putchar(BOARD_CROSS_SEPERATOR);
            putchar(BOARD_HORIZONTAL_SEPERATOR);
        }
        putchar(BOARD_HORIZONTAL_SEPERATOR);
        putchar(BOARD_HORIZONTAL_SEPERATOR);
    }
    putchar(BOARD_VERTICAL_SEPERATOR);
    putchar('\n');
}
