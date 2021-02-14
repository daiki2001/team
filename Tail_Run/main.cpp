#include <DxLib.h>
#include "./Header/Load.h"
#include <ctype.h>
#include "./Header/Input.h"
#include "./Header/Stage.h"
#include "./Header/Scene.h"
#include "./Header/Player.h"
#include "./Header/Change.h"
#include "./Header/Wing.h"
#include "./Header/Claws.h"
#include "./Header/Food.h"
#include "./Header/Goal.h"
#include "./Header/Coin.h"
#include "./Header/Shake.h"
#include "./Header/Select.h"
#include "./Header/Scene.h"
#include "./Header/Initial.h"
#include "./Header/Draw.h"

#define blockSize 32
#define mapWidth 30 + 2
#define mapHeight 20 + 2

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "Tail Run";

// �E�B���h�E����
const int WIN_WIDTH = (mapWidth - 2) * blockSize;

// �E�B���h�E�c��
const int WIN_HEIGHT = (mapHeight - 2) * blockSize;

//�A�C�R���̕ύX
int SetWindowIconID(101);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0xC0, 0xC0, 0xC0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�̓ǂݍ���
	Graphic graph;
	LoadGraphic(graph);

	//�T�E���h�̓ǂݍ���
	Sound sound;
	LoadSound(sound);

	//�e�X�e�[�W�̃}�b�v�`�b�v�A�Ō�̓^�C�g��
	//[�X�e�[�W�ԍ�][mapHeight][mapWidth]
	int mapChip[21][mapHeight][mapWidth] = { 0 };

	int oldMapChip[mapHeight][mapWidth] = { 0 };

	//csv�t�@�C����ǂݍ���ŁA�}�b�v�`�b�v���쐬
	for (int i = 0; i < 21; i++)
	{
		int fileHandle;
		char string[256];
		fileHandle = LoadCSV(i);

		for (int y = 0; y < mapHeight; y++)
		{
			FileRead_gets(string, 256, fileHandle);
			for (int x = 0, j = 0; string[j] != '\0'; j++)
			{
				if (ispunct(string[j]))
				{
					x++;
				}
				else
				{
					mapChip[i][y][x] = string[j] - '0';
				}
			}
		}
		FileRead_close(fileHandle);
	}

	//Xbox�R���g���[���[�̓��͏��
	XINPUT_STATE pad;

	//�L�[���͂�Xbox�R���g���[���[�̓��͂̍������
	//0�`3�F�㉺���E, 4�F�A�N�V�����R�}���h
	bool input[6] = { 0 };

	//1�t���[���O��input�̏��
	bool oldInput[6] = { 0 };

	//
	//���͎��Ԍv���p(���傢�����ɑΉ������邽��)
	int inputCount[6] = { 0 };
	//

	//�Q�[���I���t���O
	bool endFlag = false;

	//�V�[���p�ϐ�
	int scene = Title;

	//�A�j���[�V�������[�v�p�ϐ�
	int animation = 0;
	int playerAnimation = 0, wingAnimation = 0, hungryAnimation = 0,
		coinAnimation = 0, clearAnimation = 0;

	//�����������
	const int length = 8;
	char strNum[length]{};
	int number;

	//�X�e�[�W�ԍ�
	int stageNo = Title;

	int playerX = WIN_WIDTH / 2, playerY = 400; //�v���C���[�̍��W
	const int playerWidth = 16, playerHeight = 14; //�v���C���[�̑傫��(����)

	//���S�t���O
	bool deathFlag = FALSE;

	//���S�G�t�F�N�g�p�t���O
	bool fallDeathFlag = FALSE, hungryDeathFlag = FALSE;

	//��
	int hungryTime = 200;

	int leftMapnumX = (playerX - playerWidth) / blockSize; //�v���C���[�̍��̃}�b�v�`�b�v�̏ꏊ
	int rightMapnumX = (playerX + playerWidth) / blockSize; //�v���C���[�̉E�̃}�b�v�`�b�v�̏ꏊ
	int upMapnumY = (playerY - playerHeight) / blockSize; //�v���C���[�̏�̃}�b�v�`�b�v�̏ꏊ
	int downMapnumY = (playerY + playerHeight) / blockSize; //�v���C���[�̉��̃}�b�v�`�b�v�̏ꏊ

	int memoryX = playerX, memoryY = playerY; //�����O�̃v���C���[�̍��W
	bool playerTurn = FALSE; //false�ŉE�Atrue�ō�����������

	bool itemFlag = FALSE; //false�ł����܁Atrue�ŉH���g����

	bool wingUseFlag = FALSE; //true�ŉH�΂����Ă���

	int clawX = -100, clawY = -100; //�����܂̃w�b�h�̍��W
	const int clawWidth = 8, clawHeight = 8; //�����܂̑傫��(����)
	int chainCount = 0; //�o�Ă鍽�̐�
	int clawFlag = Normal; //1�Ŕ��˒��A2�Ńv���C���[�̈ړ��A3�ł͂˕Ԃ�

	int coinNum = 0; //�R�C��
	int perfectFlag = 0, clearFlag = 0; //�S�[���t���O
	int keyFlag = 1;
	int goalFlag = 0; //�S�[���o���邩�ǂ���

	int stageCoin = 0; //�X�e�[�W���Ƃ̃R�C���̐�������

	int gameoverSelectY = 0;
	int stageSelectX = 0, stageSelectY = 0;

	int star[20] = { 0 };

	int shakeX = 0, shakeY = 0; //�V�F�C�N�l
	double shakePower = 50; //�V�F�C�N�̋���
	int shakeTime = 30; //�V�F�C�N����
	int shakeArea = 10; //�V�F�C�N�͈�
	bool shakeResetFlag = FALSE; //�V�F�C�N�̃��Z�b�g(true�Ń��Z�b�g)

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�Q�[���p�b�h���͏���
		GetJoypadXInputState(DX_INPUT_PAD1, &pad);

		//�ŐV�̓��͏�񂾂������̂�1�t���[���O�̓��͏��Ƃ��ĕۑ�
		for (int i = 0; i < 6; i++)
		{
			oldInput[i] = input[i];
		}

		//���͏��̌���
		Input(keys, pad, input);

		for (int i = 0; i < 4; i++)
		{
			if (input[i] == TRUE)
			{
				//���͎��Ԍv��
				inputCount[i]++;
			}
			else
			{
				//�v�������Z�b�g����
				inputCount[i] = 0;
			}
		}

		//�A�j���[�V����
		animation++;
		if (animation == 5)
		{
			animation = 0;

			coinAnimation++;
			coinAnimation %= 8;

			clearAnimation++;
			clearAnimation %= 6;

			if (hungryDeathFlag == TRUE)
			{
				if (coinAnimation % 4 == 0)
				{
					hungryAnimation++;
				}
			}

			if (input[InputAction] == TRUE)
			{
				if (coinAnimation % 2 == 0)
				{
					playerAnimation++;
				}
				playerAnimation %= 2;
			}
			else
			{
				if (input[InputLeft] == TRUE || input[InputRight] == TRUE)
				{
					playerAnimation++;
					playerAnimation %= 4;
				}
				else
				{
					if (coinAnimation % 2 == 0)
					{
						playerAnimation++;
					}
					playerAnimation %= 2;
				}
			}
		}

		//BGM�Đ�
		if (CheckSoundMem(sound.bgm) == 0)
		{
			PlaySoundMem(sound.bgm, DX_PLAYTYPE_BACK);
		}

		// �X�V����
		switch (scene)
		{
		case Title:
			memoryX = playerX;
			memoryY = playerY;

			if (clawFlag == Normal)
			{
				Player(&playerX, &playerY, &playerTurn, input, mapChip[Title], blockSize);
				Gravity(&playerY);
				if (playerY >= WIN_HEIGHT)
				{
					playerX = WIN_WIDTH / 2;
					playerY = 400;
				}
			}

			//�v���C���[���ړ�������̃}�b�v�`�b�v�̏ꏊ
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//������
			if (clawFlag == Normal)
			{
				if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
				{
					clawFlag = Launching;
					if (playerTurn == 0)
					{
						clawX = playerX;
						clawY = playerY;
					}
					else
					{
						clawX = playerX - playerWidth;
						clawY = playerY;
					}
				}

				//�����܂�SE�̒�~
				StopSoundMem(sound.shot);
			}
			else
			{
				Claws(&clawX, clawWidth, &chainCount, &playerX, playerWidth, playerTurn, clawFlag);
				switch (clawFlag)
				{
				case Launching:
					//���˒�
					if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[Title]) == 1)
					{
						clawFlag = PlayerMove;
					}
					if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[Title]) == 2)
					{
						clawFlag = Cancel;
					}
					if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
					{
						clawFlag = Cancel;
					}
					break;
				case PlayerMove:
					//�v���C���[�̈ړ���
					if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
					{
						clawFlag = Normal;
						clawX = -100;
						clawY = -100;
						chainCount = 0;
					}
					break;
				case Cancel:
					//�����܂̂͂˕Ԃ�
					if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
					{
						clawFlag = Normal;
						clawX = -100;
						clawY = -100;
						chainCount = 0;
					}
					break;
				default:
					break;
				}

				//�����܂̌��ʉ��Đ�
				if (CheckSoundMem(sound.shot) == 0)
				{
					PlaySoundMem(sound.shot, DX_PLAYTYPE_BACKBIT);
				}
			}

			//�v���C���[�̓����蔻��E�߂�����
			PlayerCollision(&playerX, &playerY, playerWidth, playerHeight, &memoryX, &memoryY,
				&leftMapnumX, &rightMapnumX, &upMapnumY, &downMapnumY, input, mapChip[Title], blockSize);

			if (clawFlag == Normal)
			{
				if (playerX <= blockSize * 8)
				{
					endFlag = TRUE;
				}
				if (playerX >= blockSize * 22)
				{
					scene = StageSelection;

					//�����܂�SE�̒�~
					StopSoundMem(sound.shot);
				}
			}
			break;
		case StageSelection:
			Select(&stageSelectX, &stageSelectY, &scene, &stageNo, input, oldInput, inputCount, sound);
			//����
			if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
			{
				//�������t���O
				Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
					&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
					&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
				AnimationInit(&animation, &playerAnimation, &wingAnimation,
					&hungryAnimation, &coinAnimation, &clearAnimation);

				if (scene != Title)
				{
					//�X�e�[�W�̕ۑ�
					for (int y = 0; y < mapHeight; y++)
					{
						for (int x = 0; x < mapWidth; x++)
						{
							oldMapChip[y][x] = mapChip[stageNo][y][x];
						}
					}
				}
			}
			break;
		case Main:
			memoryX = playerX;
			memoryY = playerY;

			Change(&itemFlag, stageNo);

			if (clawFlag == Normal)
			{
				if (input[InputAction] == FALSE)
				{
					Player(&playerX, &playerY, &playerTurn, input, mapChip[stageNo], blockSize);
				}
			}

			if (itemFlag == TRUE)
			{
				//�H
				if (wingUseFlag == TRUE)
				{
					Gravity(&playerY);
					if (wingAnimation <= 0)
					{
						wingUseFlag = FALSE;
					}
					wingAnimation--;
				}
				else
				{
					Gravity(&playerY);
					wingAnimation = 4;
					Wing(&playerY, &wingUseFlag, input, oldInput);
				}
			}
			else
			{
				//������
				if (clawFlag == Normal)
				{
					Gravity(&playerY);
					if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
					{
						clawFlag = Launching;
						if (playerTurn == 0)
						{
							clawX = playerX;
							clawY = playerY;
						}
						else
						{
							clawX = playerX - playerWidth;
							clawY = playerY;
						}
					}

					//�����܂�SE�̒�~
					StopSoundMem(sound.shot);
				}
				else
				{
					Claws(&clawX, clawWidth, &chainCount, &playerX, playerWidth, playerTurn, clawFlag);
					switch (clawFlag)
					{
					case 1:
						//���˒�
						if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[stageNo]) == 1)
						{
							clawFlag = PlayerMove;
						}
						if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[stageNo]) == 2)
						{
							clawFlag = Cancel;
						}
						if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
						{
							clawFlag = Cancel;
						}
						break;
					case 2:
						//�v���C���[�̈ړ���
						if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
						{
							clawFlag = Normal;
							clawX = -100;
							clawY = -100;
							chainCount = 0;
						}
						break;
					case 3:
						//�����܂̂͂˕Ԃ�
						if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
						{
							clawFlag = Normal;
							clawX = -100;
							clawY = -100;
							chainCount = 0;
						}
						break;
					default:
						break;
					}

					//�����܂̌��ʉ��Đ�
					if (CheckSoundMem(sound.shot) == 0)
					{
						PlaySoundMem(sound.shot, DX_PLAYTYPE_BACKBIT);
					}
				}
			}

			//�v���C���[���ړ�������̃}�b�v�`�b�v�̏ꏊ
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//�v���C���[�̓����蔻��E�߂�����
			PlayerCollision(&playerX, &playerY, playerWidth, playerHeight, &memoryX, &memoryY, &leftMapnumX, &rightMapnumX, &upMapnumY, &downMapnumY, input, mapChip[stageNo], blockSize);

			//�v���C���[���ړ�������̃}�b�v�`�b�v�̏ꏊ
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//�R�C��
			Coin(&coinNum, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, sound.coin);

			//��
			Food(&hungryTime, &hungryDeathFlag, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, stageNo, sound.food);

			//�S�[��
			Goal(&coinNum, &clearFlag, &perfectFlag, &keyFlag, &goalFlag, stageCoin, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, sound);

			//�󕠂̃G�t�F�N�g
			if (hungryAnimation >= 3)
			{
				hungryAnimation = 0;
				hungryDeathFlag = FALSE;
				scene = GameOver;

				//�����܂�SE�̒�~
				StopSoundMem(sound.shot);
			}

			//�������̃G�t�F�N�g
			if (playerY >= WIN_HEIGHT && fallDeathFlag == FALSE)
			{
				fallDeathFlag = TRUE;
				shakePower = 20;
				shakeTime = 10;
				shakeArea = 5;
			}

			if (fallDeathFlag == TRUE)
			{
				if (shakeTime >=
					Shake(&shakeX, &shakeY, &shakePower, &shakeTime, shakeArea, shakeResetFlag))
				{
					shakeResetFlag = TRUE;
				}
				else
				{
					shakeResetFlag = FALSE;
					if (shakeTime <= 0)
					{
						fallDeathFlag = FALSE;
						scene = GameOver;

						//�����܂�SE�̒�~
						StopSoundMem(sound.shot);
					}
				}
			}

			//DeathFlag�̌���
			if (fallDeathFlag == TRUE || hungryDeathFlag == TRUE)
			{
				deathFlag = TRUE;
			}

			//�{�[�i�X�X�e�[�W�̏���
			if (stageNo == 20)
			{
				//�R�C���̎c�薇����0�Ȃ�}�b�v���Z�b�g
				if (coinNum % 564 == 0)
				{
					for (int y = 0; y < mapHeight; y++)
					{
						for (int x = 0; x < mapWidth; x++)
						{
							mapChip[stageNo][y][x] = oldMapChip[y][x];
						}
					}
				}

				//�N���A�t���O
				if (hungryTime <= 0)
				{
					perfectFlag = 1;
				}
			}

			//���g���C
			if (input[InputMenu] == 1 && oldInput[InputMenu] == 0)
			{
				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}
				Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
					&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
					&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
				AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);
			}
			
			//�S�[���m�F�p
			if (clearFlag == 1 || perfectFlag == 1)
			{
				//strNum��'\0'�ŏ�����
				for (int i = 0; i < length; i++)
				{
					strNum[i] = '\0';
				}

				//�X�R�A�v�Z
				number = coinNum * 1000;
				sprintf_s(strNum, sizeof(strNum), "%d", number);

				scene = GameClear;

				//�����܂�SE�̒�~
				StopSoundMem(sound.shot);
			}

			break;
		case GameOver:

			//��
			if (inputCount[InputUp] % 20 == 1)
			{
				gameoverSelectY -= 1;
			}
			//��
			if (inputCount[InputDown] % 20 == 1)
			{
				gameoverSelectY += 1;
			}

			//�}�C�i�X�ɂ��Ȃ�
			if (gameoverSelectY < 0) {
				gameoverSelectY = 1;
			}
			if (gameoverSelectY > 1)
			{
				gameoverSelectY = 0;
			}
			//����
			if (input[InputAction] == 1 && oldInput[InputAction] == 0)
			{
				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}

				//�Z���N�g��SE�Đ�
				PlaySoundMem(sound.decision, DX_PLAYTYPE_BACKBIT);

				if (gameoverSelectY == 1)
				{
					scene = Title;
					stageNo = 0;

					//�������t���O
					Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
						&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
						&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
					AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);
				}
				else
				{
					//�������t���O
					Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
						&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
						&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
					AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);

					scene = Main;
				}
			}
			break;

		case GameClear:
			if (input[InputAction] == 1 && oldInput[InputAction] == 0)
			{
				scene = StageSelection;

				if (perfectFlag == TRUE)
				{
					star[stageNo - 1] = TRUE;
				}

				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}
			}

			break;
		default:
			break;
		}

		if (endFlag == TRUE)
		{
			break;
		}

		// �`�揈��
		switch (scene)
		{
		case Title:
			//�w�i�̕`��
			TitleDraw(graph);

			//�n�ʂ̕`��
			StageDraw(blockSize, mapWidth, mapHeight, mapChip[Title], graph, coinAnimation);

			//A�{�^���̕`��
			DrawGraph(blockSize * 14, blockSize * 16, graph.aButton, TRUE);

			//�����܂̕`��
			if (clawFlag != Normal)
			{
				ClawDraw(clawX, clawY, clawWidth, clawHeight, graph, playerTurn, chainCount + 1);
			}

			//�v���C���[�̕`��
			PlayerDraw(playerX, playerY, graph, playerTurn, playerAnimation, input);

			break;
		case Main:
			//�w�i�̕`��
			BGDraw(graph, stageNo);

			//�n�ʂ̕`��
			StageDraw(blockSize, mapWidth, mapHeight, mapChip[stageNo], graph, coinAnimation);

			//�������̃G�t�F�N�g
			if (shakeX != 0 || shakeY != 0)
			{
				BGDraw(graph, stageNo, shakeX, shakeY);
				StageDraw(blockSize, mapWidth, mapHeight, mapChip[stageNo], graph, coinAnimation, shakeX, shakeY);
			}

			//�󕠃Q�[�W
			HungryDraw(hungryTime, graph);

			KeyDraw(goalFlag, graph.key);

			if (itemFlag == TRUE)
			{
				//�H�̕`��
				WingDraw(playerX, playerY, playerWidth, playerHeight, graph, playerTurn, wingUseFlag);
			}
			else
			{
				//�����܂̕`��
				if (clawFlag != Normal)
				{
					ClawDraw(clawX, clawY, clawWidth, clawHeight, graph, playerTurn, chainCount + 1);
				}
			}

			//�v���C���[�̕`��
			if (hungryDeathFlag == TRUE)
			{
				StarvationDrow(playerX, playerY, playerWidth, playerHeight, graph, playerTurn, hungryAnimation);
			}
			else
			{
				PlayerDraw(playerX, playerY, graph, playerTurn, playerAnimation, input);
			}

			break;
		case StageSelection:
			//�Z���N�g���
			SelectDraw(blockSize, stageSelectX, stageSelectY, star, graph);

			break;
		case GameOver:
			//�Q�[���I�[�o�[���
			GameOverDraw(blockSize, gameoverSelectY, graph);

			break;
		case GameClear:
			//�Q�[���N���A���
			GameClearDraw(strNum, clearAnimation, graph);

			break;
		default:
			break;
		}

		//�f�o�b�O�̕`��
		//DebugDraw(blockSize, WIN_WIDTH, WIN_HEIGHT, mapWidth, mapHeight, playerX, playerY, playerWidth, playerHeight);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}