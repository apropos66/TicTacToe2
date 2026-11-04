

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// pre setup
#define BOARD_SIZE 9
#define EMPTY '\0'

typedef struct {
  char board[BOARD_SIZE];
  char human_player;
  char ai_player;
} TicTacToe;

// Function delcarations
void ttt_init(TicTacToe *self);
void ttt_print_board(const TicTacToe *self);
bool ttt_make_move(TicTacToe *self, int position, char player);
char ttt_check_winner(const TicTacToe *self);
bool ttt_is_game_over(TicTacToe *self);
bool ttt_is_board_full(const TicTacToe *self);
static int ttt_minimax(TicTacToe *self, bool is_maximizing);
int ttt_get_best_move(TicTacToe *self);
void ttt_play_game(TicTacToe *self);

// functions
void ttt_init(TicTacToe *self) {
  memset(self->board, 0, sizeof self->board);
  self->human_player = 'X';
  self->ai_player = 'O';
}

bool ttt_make_move(TicTacToe *self, int position, char player) {
  if (position < 0 || position >= BOARD_SIZE) {
    return false;
  }
  if (self->board[position] != 0) {
    return false;
  }
  self->board[position] = player;
  return true;
}

void ttt_print_board(const TicTacToe *self) {
  int i = 0;

  for (i = 0; i < 9; i += 3) {
    char c1 = self->board[i];
    char c2 = self->board[i + 1];
    char c3 = self->board[i + 2];
    printf("\t\t%c | %c | %c\n", c1 ? c1 : ' ', c2 ? c2 : ' ', c3 ? c3 : ' ');
    if (i < 6) {
      printf("\t\t---+---+---\n");
    }
  }
}

char ttt_check_winner(const TicTacToe *self) {
  int i;
  // check rows
  for (i = 0; i < 9; i += 3) {
    if (self->board[i] == self->board[i + 1] &&
        self->board[i + 1] == self->board[i + 2] && self->board[i] != 0) {
      return self->board[i];
    }
  }

  // check columns
  for (i = 0; i < 3; i++) {
    if (self->board[i] == self->board[i + 3] &&
        self->board[i + 3] == self->board[i + 6] && self->board[i + 6] != 0) {
      return self->board[i];
    }
  }

  // check diagonals
  if ((self->board[0] == self->board[4] && self->board[4] == self->board[8] &&
       self->board[8] != 0) ||
      (self->board[2] == self->board[4] && self->board[4] == self->board[6] &&
       self->board[6] != 0)) {
    return self->board[4];
  }
  return EMPTY;
}

bool ttt_is_board_full(const TicTacToe *self) {
  for (int i = 0; i < 9; i++) {
    if (self->board[i] == 0) {
      return false;
    }
  }
  return true;
}

bool ttt_is_game_over(TicTacToe *self) {
  if (ttt_check_winner(self) != 0 || ttt_is_board_full(self)) {
    return true;
  }
  return false;
}

static int ttt_minimax(TicTacToe *self, bool is_maximizing) {
  char winner = ttt_check_winner(self);
  if (winner == self->ai_player)
    return 1;
  if (winner == self->human_player)
    return -1;
  if (ttt_is_board_full(self))
    return 0;

  if (is_maximizing) {
    int best_score = -2;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (self->board[i] != EMPTY)
        continue;
      self->board[i] = self->ai_player;
      int score = ttt_minimax(self, false);
      self->board[i] = EMPTY;
      if (score > best_score) {
        best_score = score;
      }
    }
    return best_score;
  } else {
    int best_score = 2;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (self->board[i] != EMPTY)
        continue;

      self->board[i] = self->human_player;
      int score = ttt_minimax(self, true);
      self->board[i] = EMPTY;
      if (score < best_score) {
        best_score = score;
      }
    }
    return best_score;
  }
}

int ttt_get_best_move(TicTacToe *self) {
  int best_score = -2;
  int best_move = -1;
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (self->board[i] != EMPTY)
      continue;
    self->board[i] = self->ai_player;
    int score = ttt_minimax(self, false);
    self->board[i] = EMPTY;
    if (score > best_score) {
      best_score = score;
      best_move = i;
    }
  }
  return best_move;
}

// this funciton is ai-generated
void ttt_play_game(TicTacToe *self) {
  while (true) {
    ttt_print_board(self);

    // --- HUMAN TURN ---
    int move;
    printf("\nYour turn (0-8): ");
    if (scanf("%d", &move) != 1) {
      while (getchar() != '\n')
        ; // clear buffer
      printf("Invalid input!\n");
      continue;
    }

    // Try to make the move. If it fails (invalid or occupied), skip to next
    // loop iteration
    if (!ttt_make_move(self, move, self->human_player)) {
      printf("Invalid move! Try again.\n");
      continue;
    }

    // Check if the human just won
    if (ttt_check_winner(self) != EMPTY || ttt_is_board_full(self)) {
      break; // Exit the loop, game over
    }

    // --- AI TURN ---
    printf("\nAI is thinking...\n");
    int ai_move = ttt_get_best_move(self);
    ttt_make_move(self, ai_move, self->ai_player);

    // Check if the AI just won
    if (ttt_check_winner(self) != EMPTY || ttt_is_board_full(self)) {
      break; // Exit the loop, game over
    }
  }

  // --- GAME OVER PRINTING ---
  ttt_print_board(self);
  char winner = ttt_check_winner(self);
  if (winner == self->human_player) {
    printf("\nYou won!\n");
  } else if (winner == self->ai_player) {
    printf("\nAI won!\n");
  } else {
    printf("\nIt's a draw!\n");
  }
}

int main() {
  TicTacToe game;
  ttt_init(&game);
  ttt_play_game(&game);
  return 0;
}
