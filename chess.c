#include "chess.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_game(GameState *game) {
  const char *init[BOARD_SIZE] = {"rnbqkbnr", "pppppppp", "........",
                                  "........", "........", "........",
                                  "PPPPPPPP", "RNBQKBNR"};
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      game->board[i][j] = init[i][j];

  game->turn = 0;
  game->w_king_moved = game->w_k_rook_moved = game->w_q_rook_moved = false;
  game->b_king_moved = game->b_k_rook_moved = game->b_q_rook_moved = false;
}

void print_board(const GameState *game) {
  printf("\n  a b c d e f g h\n");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", BOARD_SIZE - i);
    for (int j = 0; j < BOARD_SIZE; j++)
      printf("%c ", game->board[i][j]);
    printf("%d\n", BOARD_SIZE - i);
  }
  printf("  a b c d e f g h\n");
}

bool parse_coord(const char *coord, int *row, int *col) {
  if (strlen(coord) != 2)
    return false;
  char file = coord[0], rank = coord[1];
  if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
    return false;
  *col = file - 'a';
  *row = BOARD_SIZE - (rank - '0');
  return true;
}

/* 🌟 Красивый и лаконичный pathClear */
bool is_path_clear(const char board[BOARD_SIZE][BOARD_SIZE], int r1, int c1,
                   int r2, int c2) {
  int dr = (r2 > r1) ? 1 : (r2 < r1) ? -1 : 0;
  int dc = (c2 > c1) ? 1 : (c2 < c1) ? -1 : 0;

  int r = r1 + dr;
  int c = c1 + dc;
  while (r != r2 || c != c2) {
    if (board[r][c] != '.')
      return false;
    r += dr;
    c += dc;
  }
  return true;
}

/* Проверка, атакуется ли клетка фигурами цвета attacker */
static bool is_square_attacked(const GameState *g, int tr, int tc,
                               int attacker) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      char p = g->board[i][j];
      bool is_attacker =
          (attacker == 0 && isupper(p)) || (attacker == 1 && islower(p));
      if (!is_attacker)
        continue;

      int dr = tr - i, dc = tc - j;
      int adr = abs(dr), adc = abs(dc);

      if (p == 'P' || p == 'p') {
        int dir = isupper(p) ? 1 : -1;
        if (dr == dir && adc == 1)
          return true;
      } else if (p == 'N' || p == 'n') {
        if ((adr == 2 && adc == 1) || (adr == 1 && adc == 2))
          return true;
      } else if (p == 'K' || p == 'k') {
        if (adr <= 1 && adc <= 1 && (dr || dc))
          return true;
      } else if (p == 'B' || p == 'b' || p == 'Q' || p == 'q') {
        if (adr == adc && is_path_clear(g->board, i, j, tr, tc))
          return true;
      } else if (p == 'R' || p == 'r' || p == 'Q' || p == 'q') {
        if ((dr == 0 || dc == 0) && (dr || dc) &&
            is_path_clear(g->board, i, j, tr, tc))
          return true;
      }
    }
  }
  return false;
}

/* Валидация для каждой фигуры */
static bool v_pawn(const GameState *g, int fr, int fc, int tr, int tc) {
  int dir = (g->turn == 0) ? -1 : 1;
  int start = (g->turn == 0) ? 6 : 1;
  if (tr == fr + dir && tc == fc && g->board[tr][tc] == '.')
    return true;
  if (fr == start && tr == fr + 2 * dir && tc == fc &&
      g->board[tr][tc] == '.' && g->board[fr + dir][fc] == '.')
    return true;
  if (tr == fr + dir && abs(tc - fc) == 1 && g->board[tr][tc] != '.') {
    int t_white = isupper(g->board[tr][tc]);
    return (g->turn == 0 && !t_white) || (g->turn == 1 && t_white);
  }
  return false;
}
static bool v_knight(const GameState *g, int fr, int fc, int tr, int tc) {
  (void)g;
  int dr = abs(fr - tr), dc = abs(fc - tc);
  return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}
static bool v_bishop(const GameState *g, int fr, int fc, int tr, int tc) {
  return abs(fr - tr) == abs(fc - tc) &&
         is_path_clear(g->board, fr, fc, tr, tc);
}
static bool v_rook(const GameState *g, int fr, int fc, int tr, int tc) {
  return (fr == tr || fc == tc) && is_path_clear(g->board, fr, fc, tr, tc);
}
static bool v_queen(const GameState *g, int fr, int fc, int tr, int tc) {
  return v_bishop(g, fr, fc, tr, tc) || v_rook(g, fr, fc, tr, tc);
}
static bool v_king(const GameState *g, int fr, int fc, int tr, int tc) {
  (void)g;
  return abs(fr - tr) <= 1 && abs(fc - tc) <= 1;
}

bool is_valid_move(const GameState *game, int fr, int fc, int tr, int tc) {
  char p = game->board[fr][fc];
  if (p == '.')
    return false;

  int p_white = isupper(p);
  if ((game->turn == 0 && !p_white) || (game->turn == 1 && p_white))
    return false;

  char target = game->board[tr][tc];
  if (target != '.' &&
      ((p_white && isupper(target)) || (!p_white && islower(target))))
    return false;

  switch (tolower(p)) {
  case 'p':
    return v_pawn(game, fr, fc, tr, tc);
  case 'n':
    return v_knight(game, fr, fc, tr, tc);
  case 'b':
    return v_bishop(game, fr, fc, tr, tc);
  case 'r':
    return v_rook(game, fr, fc, tr, tc);
  case 'q':
    return v_queen(game, fr, fc, tr, tc);
  case 'k':
    return v_king(game, fr, fc, tr, tc);
  default:
    return false;
  }
}

bool make_move(GameState *game, int fr, int fc, int tr, int tc) {
  if (!is_valid_move(game, fr, fc, tr, tc))
    return false;

  char p = game->board[fr][fc];
  char captured = game->board[tr][tc];

  // 🏰 Рокировка
  if (tolower(p) == 'k' && abs(fc - tc) == 2) {
    int row = (game->turn == 0) ? 7 : 0;
    if (fr != row || tr != row)
      return false;
    bool kingside = (tc > fc);
    int r_from = kingside ? 7 : 0;
    int r_to = kingside ? 5 : 3;

    bool *k_m = game->turn ? &game->b_king_moved : &game->w_king_moved;
    bool *r_m =
        game->turn ? (kingside ? &game->b_k_rook_moved : &game->b_q_rook_moved)
                   : (kingside ? &game->w_k_rook_moved : &game->w_q_rook_moved);
    if (*k_m || *r_m)
      return false;
    if (!is_path_clear(game->board, fr, fc, tr, tc))
      return false;
    if (is_square_attacked(game, fr, fc, 1 - game->turn) ||
        is_square_attacked(game, fr, (fc + tc) / 2, 1 - game->turn) ||
        is_square_attacked(game, tr, tc, 1 - game->turn))
      return false;

    game->board[tr][tc] = p;
    game->board[fr][fc] = '.';
    game->board[tr][r_to] = game->board[tr][r_from];
    game->board[tr][r_from] = '.';
  } else {
    game->board[tr][tc] = p;
    game->board[fr][fc] = '.';
  }

  // Проверка, не остался ли свой король под шахом
  char king_char = (game->turn == 0) ? 'K' : 'k';
  int kr = -1, kc = -1;
  for (int r = 0; r < BOARD_SIZE; r++)
    for (int c = 0; c < BOARD_SIZE; c++)
      if (game->board[r][c] == king_char) {
        kr = r;
        kc = c;
      }

  if (is_square_attacked(game, kr, kc, 1 - game->turn)) {
    // Откат хода
    game->board[fr][fc] = p;
    game->board[tr][tc] = captured;
    if (tolower(p) == 'k' && abs(fc - tc) == 2) {
      int r_from = (tc > fc) ? 7 : 0;
      int r_to = (tc > fc) ? 5 : 3;
      game->board[tr][r_from] = game->board[tr][r_to];
      game->board[tr][r_to] = '.';
    }
    return false;
  }

  // Обновление флагов рокировки
  if (tolower(p) == 'k') {
    if (game->turn == 0)
      game->w_king_moved = true;
    else
      game->b_king_moved = true;
  }
  if (tolower(p) == 'r') {
    if (fc == 0) {
      if (game->turn == 0)
        game->w_q_rook_moved = true;
      else
        game->b_q_rook_moved = true;
    }
    if (fc == 7) {
      if (game->turn == 0)
        game->w_k_rook_moved = true;
      else
        game->b_k_rook_moved = true;
    }
  }

  game->turn = 1 - game->turn;
  return true;
}