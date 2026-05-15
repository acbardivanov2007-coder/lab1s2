#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#define BOARD_SIZE 8

typedef struct {
  char board[BOARD_SIZE][BOARD_SIZE];
  int turn; // 0 = белые, 1 = чёрные
  bool w_king_moved, w_k_rook_moved, w_q_rook_moved;
  bool b_king_moved, b_k_rook_moved, b_q_rook_moved;
} GameState;

// Инициализация, вывод, парсинг
void init_game(GameState *game);
void print_board(const GameState *game);
bool parse_coord(const char *coord, int *row, int *col);

// Логика ходов и валидации
bool is_path_clear(const char board[BOARD_SIZE][BOARD_SIZE], int r1, int c1,
                   int r2, int c2);
bool is_valid_move(const GameState *game, int fr, int fc, int tr, int tc);
bool make_move(GameState *game, int fr, int fc, int tr, int tc);

#endif // CHESS_H