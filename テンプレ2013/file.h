#pragma once

#include <fstream>
#include "Vector2.h"
#include <vector>

struct PlayerData;

//�Z�[�u�f�[�^�̊Ǘ�������N���X(�V���O���g��)
class File{
private:
	char *FILE_NAME;					//�v���C�f�[�^�̃t�@�C��
	char *FILE_NAME_OPTION;				//�I�v�V�����̐ݒ��ۑ�����t�@�C��

	File();

	File(const File& r) = delete;//�R�s�[���֎~
	File& operator=(const File& r) = delete; //������֎~

public:
	static File& get(){
		static File inst;
		return inst;
	}

	void load_set_data();				//���[�h
	void save_set_data();				//�I�v�V�����̐ݒ�̃Z�[�u
	void save_data(PlayerData data);	//�v���C�f�[�^�̃Z�[�u
	PlayerData read_data();				//�v���C�f�[�^�̃��[�h

	char * get_file_name();				//�v���C���[�f�[�^�̃t�@�C������Ԃ��֐�
	char * get_file_name_option();		//�I�v�V�����̐ݒ��ۑ�����t�@�C������Ԃ��֐�
};


//���O�e�L�X�g��ǂݍ���ŊǗ��E�`�悷��N���X
class Log{
private:
	//��s���̕������ۑ�����N���X
	class String
	{
	public:
		String(double y, std::string str_);
		Vector2 original;			//���Έʒu
		std::string str;			//������
		void draw(Vector2 camera);	//�`��֐�
	};

	std::string FILE_NAME;			//���O�e�L�X�g�̃t�@�C����
	std::vector<String> vec;		//������̃x�N�^�[
	FILE *fp;
	Vector2 camera;					//�S�̂̐�Έʒu
	const double logSpeed;			//���O�̗����X�s�[�h
	const double startPoint;		//�`��J�n�ʒu

public:

	Log();


	void update();					//�X�V
	void read();					//�ǂݍ���
	void draw();					//�`��
	double get_start();				//�擪�̈ʒu���擾
	double get_end();				//�����̈ʒu���擾
	void set(std::string str);		//�t�@�C��������
	void reset_camera();			//�S�̂̐�Έʒu�������ʒu�ɂ���
	int vec_size();					//�x�N�^�[�̃T�C�Y���擾
};
