#pragma once

//かぎ爪
void Claws(int *clawX, const int &clawWidth, int *chainCount, int *playerX, const int &playerWidth, const bool &playerTurn, const int &flag);

//当たり判定
char PileHit(const int &x, const int &y, const int &width, const int &height, const int &blockSize, const int map[20][30]);
bool ClawHit(const int &clawX, const int &clawWidth, const int &playerX, const int &playerWidth);