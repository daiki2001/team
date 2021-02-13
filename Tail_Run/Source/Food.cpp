#include <DxLib.h>
#include "./../Header/Food.h"
#include "./../Header/Stage.h"

void Food(int *hungryTime, bool *deathFlag, int map[20 + 2][30 + 2], int leftMapnumX, int rightMapnumX, int upMapnumY, int downMapnumY, const int &stageNo, int soundHandle)
{
	bool hit = FALSE;

	if (nullptr != hungryTime && nullptr != deathFlag)
	{
		if (*hungryTime > 0)
		{
			*hungryTime -= 1;
		}

		//�H�ו��������󕠉�
		if (map[upMapnumY][leftMapnumX] == StageFood)
		{
			hit = TRUE;
			map[upMapnumY][leftMapnumX] = StageNone;
		}
		if (map[downMapnumY][leftMapnumX] == StageFood)
		{
			hit = TRUE;
			map[downMapnumY][leftMapnumX] = StageNone;
		}
		if (map[upMapnumY][rightMapnumX] == StageFood)
		{
			hit = TRUE;
			map[upMapnumY][rightMapnumX] = StageNone;
		}
		if (map[downMapnumY][rightMapnumX] == StageFood)
		{
			hit = TRUE;
			map[downMapnumY][rightMapnumX] = StageNone;
		}

		if (hit == TRUE)
		{
			*hungryTime += 500;

			//�H�ו���SE�Đ�
			PlaySoundMem(soundHandle, DX_PLAYTYPE_BACKBIT);
		}

		//�{�[�i�X�X�e�[�W�ɂȂ�����A�������I
		if (stageNo != 20)
		{
			if (*hungryTime > 1630)
			{
				*hungryTime = 1630;
			}
		}

		//���Ԑ؂�
		if (*hungryTime <= 0)
		{
			if (stageNo != 20)
			{
				*deathFlag = 1;
			}
		}
	}
}