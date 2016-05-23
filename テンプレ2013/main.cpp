#include <DxLib.h>

#include "myglobal.h"
#include "scene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetAlwaysRunFlag(true);

	SetWindowIconID(101);
	SetMainWindowText("�s�J�C�A����L�b�g");

	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(SCREEN.x,  SCREEN.y, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	if (DxLib_Init() == 1){ return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��
	

	//
	//�����œG��v���C���[�̃I�u�W�F�N�g�̎��̂����
	//
	SceneManager::get().load();


	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�	

		SceneManager::get().update();
		SceneManager::get().draw();

		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();
	return 0;
}