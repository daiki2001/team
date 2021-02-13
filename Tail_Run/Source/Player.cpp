#include <DxLib.h>
#include "./../Header/Player.h"
#include "../Header/Input.h"
#include "./../Header/Wing.h"
#include "./../Header/Stage.h"

void Player(int *x,int *y, bool *turn, bool input[],int map[20][30], int blockSize)
{
	if (x != nullptr && y != nullptr && turn != nullptr)
	{
		if (input[InputLeft] == TRUE)
		{
			*x -= 2;
			*turn = 1;
		}
		if (input[InputRight] == TRUE)
		{
			*x += 2;
			*turn = 0;
		}
		/*if (input[0] == TRUE)
		{
			*y -= 2;
		}
		if (input[1] == TRUE)
		{
			*y += 2;
		}*/

		if (*x <= 0)
		{
			*x = 0;
		}
		else if (*x >= blockSize * 30)
		{
			*x = blockSize * 30;
		}
		if (*y <= 0)
		{
			*y = 0;
		}
	}
}

void PlayerCollision(int *x, int *y, int width, int heigth, int *memoryX, int *memoryY, int *leftMapnumX, int *rightMapnumX, int *upMapnumY, int *downMapnumY, bool input[], int map[20][30], int blockSize)
{
	if (nullptr != x && nullptr != y &&
		nullptr != memoryX && nullptr != memoryY &&
		nullptr != leftMapnumX && nullptr != rightMapnumX &&
		nullptr != upMapnumY && nullptr != downMapnumY)
	{
		int hokan = 0;

		//�����̃I�u�W�F�N�g�̓����蔻��
		if (input[2] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Y�̏d�Ȃ��Ă���Ƃ����߂�
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
			//�}�b�v�`�b�v�̉��Ԗڂ�
			//����
			*leftMapnumX = (*x - width) / blockSize;
			*downMapnumY = (*y + heigth - 1) / blockSize;
			//����ł��d�Ȃ��Ă���ꍇ��Y�����Ƃ̈ʒu�ɖ߂�X��߂�
			if (map[*downMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*leftMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += width;
				//����
				*leftMapnumX = (*x - width) / blockSize;
				*downMapnumY = (*y + heigth - 1) / blockSize;
				//����ł��d�Ȃ��Ă���ꍇ��Y��߂��AX��߂����܂܂ɂ���
				if (map[*downMapnumY][*leftMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += blockSize - heigth;
				}
			}
		}

		//����̃I�u�W�F�N�g�̓����蔻��
		if (input[2] == TRUE && input[4] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround))
		{
			//Y�̏d�Ȃ��Ă���Ƃ����߂�
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
			//�}�b�v�`�b�v�̉��Ԗڂ�
				//����
			*leftMapnumX = (*x - width) / blockSize;
			*upMapnumY = (*y - heigth) / blockSize;
			//����ł��d�Ȃ��Ă���ꍇ��Y�����Ƃ̈ʒu�ɖ߂�X��߂�
			if (map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*leftMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += width;
				//�}�b�v�`�b�v�̉��Ԗڂ�
				//����
				*leftMapnumX = (*x - width) / blockSize;
				*upMapnumY = (*y - heigth) / blockSize;
				//����ł��d�Ȃ��Ă���ꍇ��Y��߂��AX��߂����܂܂ɂ���
				if (map[*upMapnumY][*leftMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += heigth;
				}
			}
		}

		//�E���̃I�u�W�F�N�g�̓����蔻��
		if (input[3] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Y�̏d�Ȃ��Ă���Ƃ����߂�
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
			//�}�b�v�`�b�v�̉��Ԗڂ�
			//�E��
			*rightMapnumX = (*x + width - 1) / blockSize;
			*downMapnumY = (*y + heigth - 1) / blockSize;
			//����ł��d�Ȃ��Ă���ꍇ��Y�����Ƃ̈ʒu�ɖ߂�X��߂�
			if (map[*downMapnumY][*rightMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += blockSize - width;
				//�}�b�v�`�b�v�̉��Ԗڂ�
				//�E��
				*rightMapnumX = (*x + width - 1) / blockSize;
				*downMapnumY = (*y + heigth - 1) / blockSize;
				//����ł��d�Ȃ��Ă���ꍇ��Y��߂��AX��߂����܂܂ɂ���
				if (map[*downMapnumY][*rightMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += blockSize - heigth;
				}
			}
		}

		//�E��̃I�u�W�F�N�g�̓����蔻��
		if (input[3] == TRUE && input[4] == TRUE && (map[*upMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Y�̏d�Ȃ��Ă���Ƃ����߂�
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
			//�}�b�v�`�b�v�̉��Ԗڂ�
			//�E��
			*rightMapnumX = (*x + width - 1) / blockSize;
			*upMapnumY = (*y - heigth) / blockSize;
			//����ł��d�Ȃ��Ă���ꍇ��Y�����Ƃ̈ʒu�ɖ߂�X��߂�
			if (map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += blockSize - width;
				//�}�b�v�`�b�v�̉��Ԗڂ�
				//�E��
				*rightMapnumX = (*x + width - 1) / blockSize;
				*upMapnumY = (*y - heigth) / blockSize;
				//����ł��d�Ȃ��Ă���ꍇ��Y��߂��AX��߂����܂܂ɂ���
				if (map[*upMapnumY][*rightMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += heigth;
				}
			}
		}

		//������
		if (*x != *memoryX && (map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*leftMapnumX] == StageGround))
		{
			*x = max(*x, *memoryX);
			*x /= blockSize;
			*x *= blockSize;
			*x += width;
		}

		//�E�����Ǔ����蔻��
		if (*x != *memoryX && (map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			*x = max(*x, *memoryX);
			*x /= blockSize;
			*x *= blockSize;
			*x += blockSize - width;
		}

		//�ړ���
		if (*y != *memoryY && (map[*downMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
		}

		//�ړ���
		if (*y != *memoryY && (map[*upMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround))
		{
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
		}
	}
}