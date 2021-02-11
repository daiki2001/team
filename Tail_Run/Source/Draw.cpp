#include <DxLib.h>
#include "./../Header/Draw.h"
#include "./../Header/Load.h"
#include "./../Header/Stage.h"

void BGDraw(const Graphic &graphic, const int &stageNo, const int &shakeX, const int &shakeY)
{
	int i = 0;
	if(stageNo == 20)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	DrawGraph(shakeX, shakeY, graphic.background[i], TRUE);
}

void TitleDraw(const Graphic &graphic)
{
	BGDraw(graphic, 0);
	DrawGraph(48, 32, graphic.title, TRUE);
}

void SelectDraw(const int &blockSize, const int &stageSelectX, const int &stageSelectY, const int star[], const Graphic &graphic)
{
	DrawGraph(0, 0, graphic.stage, TRUE);

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (x + y * 7 < 10)
			{
				if (star[x + y * 7] == 1)
				{
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[0], TRUE);
				}
				else
				{
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[1], TRUE);
				}
			}
			else if (x + y * 7 > 10)
			{
				if (star[(x + y * 7) - 1] == 1)
				{
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[0], TRUE);
				}
				else
				{
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[1], TRUE);
				}
			}
		}
	}

	DrawGraph(stageSelectX * 4 * blockSize + 32, stageSelectY * 6 * blockSize + 48, graphic.stageselect, TRUE);
}

void GameOverDraw(const int &blockSize, const int &gameoverSelectY, const Graphic &graphic)
{
	DrawGraph(0, 0, graphic.gameover, TRUE);
	DrawGraph(0, gameoverSelectY * 5 * blockSize, graphic.gameoverselect, TRUE);
}

void GameClearDraw(const char strNum[], const int clearAnimation, const Graphic &graphic)
{
	DrawGraph(0, 0, graphic.clear[clearAnimation], TRUE);

	//数字を表示
	for (int i = 0; i < 10; i++) {
		int num = strNum[i] - 48;
		DrawGraph(96 * i + 290, 340, graphic.number[num], TRUE);
	}
}

void StageDraw(const int &blockSize, const int &mapW, const int &mapH, const int mapChip[20][30], const Graphic &graphic, const int &animationCount, const int &shakeX, const int &shakeY)
{
	for (int y = 0; y < mapH; y++)
	{
		for (int x = 0; x < mapW; x++)
		{
			switch (mapChip[y][x])
			{
			case StageNone:
				break;
			case StageGround:
				//地面の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.block[0], TRUE);
				break;
			case StageGoal:
				//ゴールの描画
				DrawGraph(blockSize * x + shakeX, blockSize * (y - 1) + shakeY, graphic.goal, TRUE);
				break;
			case StageCoin:
				//コインの描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.coin[animationCount], TRUE);
				break;
			case StageFood:
				//食べ物の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.food, TRUE);
				break;
			case StageKey:
				//鍵の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.key, TRUE);
				break;
			case StagePile:
				//杭の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.pile, TRUE);
				break;
			case StageSlime:
				break;
			case StageMagma:
				break;
			case StageIce:
				break;
			default:
				break;
			}
		}
	}
}

void PlayerDraw(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &turn, const int &animationCount, const bool input[])
{
	if (input[4] == FALSE && (input[2] == TRUE || input[3] == TRUE))
	{
		if (turn == TRUE)
		{
			DrawTurnGraph(x - width, y - height, graphic.player.run[animationCount], TRUE);
		}
		else
		{
			DrawGraph(x - width, y - height, graphic.player.run[animationCount], TRUE);
		}
	}
	else
	{
		if (turn == TRUE)
		{
			DrawTurnGraph(x - width, y - height, graphic.player.idle[animationCount], TRUE);
		}
		else
		{
			DrawGraph(x - width, y - height, graphic.player.idle[animationCount], TRUE);
		}
	}
}

void StarvationDrow(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &turn, const int &animationCount)
{
	if (turn == TRUE)
	{
		DrawTurnGraph(x - width, y - height, graphic.player.hungry[animationCount], TRUE);
	}
	else
	{
		DrawGraph(x - width, y - height, graphic.player.hungry[animationCount], TRUE);
	}
}

void ClawDraw(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &playerTurn, const int &count)
{
	if (playerTurn == TRUE)
	{
		DrawGraph(x - width, y - height + 4, graphic.player.claw[0], TRUE);
		for (int i = 0; i < count; i++)
		{
			DrawGraph(x - width + width * 2 * i, y - height + 4, graphic.player.claw[1], TRUE);
		}
	}
	else
	{
		DrawTurnGraph(x - width, y - height + 4, graphic.player.claw[0], TRUE);
		for (int i = 0; i < count; i++)
		{
			DrawGraph(x - width - width * 2 * i, y - height + 4, graphic.player.claw[1], TRUE);
		}
	}
}

void WingDraw(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &turn, const bool &useFlag)
{
	if (turn == TRUE)
	{
		if (useFlag == TRUE)
		{
			DrawRotaGraph(x + width, y + height, 1.0, 0.0, graphic.player.wing, TRUE, FALSE, TRUE);
		}
		else
		{
			DrawRotaGraph(x + width, y - height, 1.0, 0.0, graphic.player.wing, TRUE, FALSE, FALSE);
		}
	}
	else
	{
		if (useFlag == TRUE)
		{
			DrawRotaGraph(x - width, y + height, 1.0, 0.0, graphic.player.wing, TRUE, TRUE, TRUE);
		}
		else
		{
			DrawRotaGraph(x - width, y - height, 1.0, 0.0, graphic.player.wing, TRUE, TRUE, FALSE);
		}
	}
}

void HungryDraw(const int hungryTime, const Graphic &graphic)
{
	DrawBox(30, 13, hungryTime / 4 + 30, 45, GetColor(255, 0, 0), TRUE);
	DrawGraph(0, 0, graphic.hungry, TRUE);
}

void DebugDraw(const int &blockSize, const int &winW, const int &winH, const int &mapW, const int &mapH, const int &playerX, const int &playerY, const int &playerW, const int &playerH)
{
	for (int x = 0; x < mapW; x++)
	{
		DrawLine(blockSize * x, 0, blockSize * x, winH, GetColor(0xFF, 0xFF, 0xFF));
	}
	for (int y = 0; y < mapH; y++)
	{
		DrawLine(0, blockSize * y, winW, blockSize * y, GetColor(0xFF, 0xFF, 0xFF));
	}
	DrawLineBox(playerX - 16, playerY - 16, playerX + 16, playerY + 16, GetColor(0xFF, 0xFF, 0xFF));
}