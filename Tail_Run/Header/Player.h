#pragma once

//�v���C���[
void Player(int *x, int *y, bool *turn, bool input[], int map[20][30], int blockSize);

//�v���C���[�̓����蔻��E�߂�����
void  PlayerCollision(int *x, int *y, int width, int heigth, int *memoryX, int *memoryY, int *leftMapnumX, int *rightMapnumX, int *upMapnumY, int *downMapnumY, bool input[], int map[20][30], int blockSize);