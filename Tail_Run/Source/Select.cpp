#include <DxLib.h>
#include "./../Header/Select.h"
#include "../Header/Input.h"
#include "./../Header/scene.h"
#include "./../Header/Load.h"

void Select(int *stageSelectX, int *stageSelectY, int *scene, int *stageNo, bool input[], bool oldInput[], int inputCount[], Sound sound)
{
	if (nullptr == stageSelectY || nullptr == stageSelectX || nullptr == scene || nullptr == stageNo)
	{
		return;
	}

	bool move = FALSE;

	//��
	if (inputCount[InputUp] % 10 == 1)
	{
		move = TRUE;
		*stageSelectY -= 1;
	}
	//��
	if (inputCount[InputDown] % 10 == 1)
	{
		move = TRUE;
		*stageSelectY += 1;
	}
	//��
	if (inputCount[InputLeft] % 10 == 1)
	{
		move = TRUE;
		*stageSelectX -= 1;
	}
	//�E
	if (inputCount[InputRight] % 10 == 1)
	{
		move = TRUE;
		*stageSelectX += 1;
	}

	if (move == TRUE)
	{
		//�Z���N�g��SE�Đ�
		PlaySoundMem(sound.select, DX_PLAYTYPE_BACKBIT);
	}

	//����
	if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
	{
		//�����SE�Đ�
		PlaySoundMem(sound.decision, DX_PLAYTYPE_BACKBIT);

		switch (*stageSelectY * 7 + *stageSelectX)
		{

		case 0://1�X�e�[�W��
			*stageNo = 1;
			*scene = Main;
			break;

		case 1://2�X�e�[�W��
			*stageNo = 2;
			*scene = Main;
			break;

		case 2://3�X�e�[�W��
			*stageNo = 3;
			*scene = Main;
			break;

		case 3://4�X�e�[�W��
			*stageNo = 4;
			*scene = Main;
			break;

		case 4://5�X�e�[�W��
			*stageNo = 5;
			*scene = Main;
			break;

		case 5://6�X�e�[�W��
			*stageNo = 6;
			*scene = Main;
			break;

		case 6://7�X�e�[�W��
			*stageNo = 7;
			*scene = Main;
			break;

		case 7://8�X�e�[�W��
			*stageNo = 8;
			*scene = Main;
			break;

		case 8://9�X�e�[�W��
			*stageNo = 9;
			*scene = Main;
			break;

		case 9://10�X�e�[�W��
			*stageNo = 10;
			*scene = Main;
			break;

		case 10://�^�C�g��
			*stageNo = Title;
			*scene = Title;
			break;

		case 11://11�X�e�[�W��
			*stageNo = 11;
			*scene = Main;
			break;

		case 12://12�X�e�[�W��
			*stageNo = 12;
			*scene = Main;
			break;

		case 13://13�X�e�[�W��
			*stageNo = 13;
			*scene = Main;
			break;

		case 14://14�X�e�[�W��
			*stageNo = 14;
			*scene = Main;
			break;

		case 15://15�X�e�[�W��
			*stageNo = 15;
			*scene = Main;
			break;

		case 16://16�X�e�[�W��
			*stageNo = 16;
			*scene = Main;
			break;

		case 17://17�X�e�[�W��
			*stageNo = 17;
			*scene = Main;
			break;

		case 18://18�X�e�[�W��
			*stageNo = 18;
			*scene = Main;
			break;

		case 19://19�X�e�[�W��
			*stageNo = 19;
			*scene = Main;
			break;

		case 20://20�X�e�[�W��
			*stageNo = 20;
			*scene = Main;
			break;
		}

	}

	if (*stageSelectX > 6)
	{
		*stageSelectX = 0;
	}
	//�}�C�i�X�ɂ��Ȃ�
	if (*stageSelectX < 0) {
		*stageSelectX = 6;
	}
	if (*stageSelectY > 2)
	{
		*stageSelectY = 0;
	}
	//�}�C�i�X�ɂ��Ȃ�
	if (*stageSelectY < 0) {
		*stageSelectY = 2;
	}
}