

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// pre setup
#define BOARD_SIZE 9
#define EMPTY  \0

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
bool ttt_is_board_full(TicTacToe *self);

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
  char c1 = self->board[i];
  char c2 = self->board[i + 1];
  char c3 = self->board[i + 2];

  for (i = 0; i < 9; i += 3) {
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
  if (self->board[0] == self->board[4] && self->board[4] == self->board[8] &&
          self->board[8] != 0 ||
      self->board[2] == self->board[4] && self->board[4] == self->board[6] &&
          self->board[6] != 0) {
    return self->board[0];
  }
  return 0;
}

bool ttt_is_board_full(TicTacToe *self) {
  int count = 0;
  for (int i = 0; i < 9; i++) {
    if (self->board[i] == 0) {
      count++;
    }
  }
  if (count != 0) {
    return false;
  }

  return true;
}

bool ttt_is_game_over(TicTacToe *self) {
  if (ttt_check_winner(self) != 0 || ttt_is_board_full(self)) {
    return true;
  }
  return false;
}

int main() {
  TicTacToe game;
  ttt_init(&game);
  ttt_print_board(&game);
  ttt_make_move(&game, 3, 'X');
  ttt_make_move(&game, 2, 'O');
  ttt_print_board(&game);
  return 0;
}
