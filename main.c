#include "chess.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  GameState game;
  init_game(&game);
  char buf[64], from[4], to[4];

  printf("♟  Шахматы (C99)  ♟\n");
  printf("Ввод: e2 e4 | Для выхода: exit\n");

  while (1) {
    print_board(&game);
    printf("\nХод %s: ", game.turn == 0 ? "белых (A-Z)" : "чёрных (a-z)");

    if (!fgets(buf, sizeof(buf), stdin))
      break;
    buf[strcspn(buf, "\n")] = '\0'; // trim newline

    if (strncmp(buf, "exit", 4) == 0) {
      printf("Игра завершена.\n");
      break;
    }
    if (sscanf(buf, "%3s %3s", from, to) != 2) {
      printf("Формат: e2 e4\n");
      continue;
    }

    int fr, fc, tr, tc;
    if (!parse_coord(from, &fr, &fc) || !parse_coord(to, &tr, &tc)) {
      printf("Некорректные координаты (a-h 1-8).\n");
      continue;
    }

    if (make_move(&game, fr, fc, tr, tc)) {
      // Ход успешен, цикл продолжается
    } else {
      printf("Невозможный ход.\n");
    }
  }
  return 0;
}