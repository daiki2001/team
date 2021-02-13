#include <DxLib.h>
#include "./../Header/Goal.h"
#include "./../Header/Key.h"
#include "./../Header/Stage.h"
#include "./../Header/Load.h"

void Goal(int *coinNum, int *clearFlag, int *pefectFlag, int *key, int *goalFlag, int stageCoin,
	int map[20 + 2][30 + 2], int leftMapnumX, int rightMapnumX, int upMapnumY, int downMapnumY, Sound sound)
{
	if (nullptr == coinNum || nullptr == clearFlag || nullptr == pefectFlag)
	{
		return;
	}

	bool hit = FALSE;

	//���̊l��
	if (map[upMapnumY][leftMapnumX] == StageKey)
	{
		hit = TRUE;
		map[upMapnumY][leftMapnumX] = StageNone;
	}
	if (map[downMapnumY][leftMapnumX] == StageKey)
	{
		hit = TRUE;
		map[downMapnumY][leftMapnumX] = StageNone;
	}
	if (map[upMapnumY][rightMapnumX] == StageKey)
	{
		hit = TRUE;
		map[upMapnumY][rightMapnumX] = StageNone;
	}
	if (map[downMapnumY][rightMapnumX] == StageKey)
	{
		hit = TRUE;
		map[downMapnumY][rightMapnumX] = StageNone;
	}

	if (hit == TRUE)
	{
		Key(key, goalFlag);

		//����SE�Đ�
		PlaySoundMem(sound.key, DX_PLAYTYPE_BACKBIT);
	}

	//�S�[��
	if (*goalFlag == 1 &&
		(map[upMapnumY][leftMapnumX] == StageGoal || map[downMapnumY][leftMapnumX] == StageGoal ||
			map[upMapnumY][rightMapnumX] == StageGoal || map[downMapnumY][rightMapnumX] == StageGoal))
	{
		//�S�[����SE�Đ�
		PlaySoundMem(sound.goal, DX_PLAYTYPE_BACKBIT);

		//�p�[�t�F�N�g
		if (*coinNum >= stageCoin)
		{
			*pefectFlag = 1;
		}
		else
			//�N���A�[
		{
			*clearFlag = 1;
		}
	}
}