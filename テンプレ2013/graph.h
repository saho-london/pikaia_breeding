#pragma once

#include <vector>
#include <map>
#include <string>


//�摜�Ɖ��f�ނ̃n���h�����Ǘ�����N���X(�V���O���g��)

class Graph{
private:
	int backNumber;							//�w�i�摜�̔ԍ�
	int statusNumber;						//�X�e�[�^�X�����̔w�i�摜�̔ԍ�

	Graph();

	Graph(const Graph& r) = delete;//�R�s�[���֎~
	Graph& operator=(const Graph& r) = delete; //������֎~

public:
	std::map<std::string, int> graphMap;	//�摜�n���h���̃}�b�v�i�摜�t�@�C�������摜�n���h���j
	std::map<std::string, int> musicMap;	//���n���h���̃}�b�v�i���y�t�@�C�������n���h���j


	std::vector<std::string> backVec;		//�w�i�摜�̃t�@�C�������i�[����x�N�^�[
	std::vector<std::string> buttonVec;		//�{�^���̉摜�t�@�C�������i�[����x�N�^�[
	std::vector<std::string> statusVec;		//�X�e�[�^�X�����̔w�i�摜�̃t�@�C�������i�[����x�N�^�[

	static Graph& get();					

	void load_graph();						//�摜�t�@�C���ǂݍ���
	void load_music();						//���y�t�@�C���ǂݍ���
	void add_graph(std::string name);		//�^����ꂽ�摜�t�@�C���̃n���h�����擾���}�b�v�ɒǉ�
	void add_music(std::string name);		//�^����ꂽ���y�t�@�C���̃n���h�����擾���}�b�v�ɒǉ�
	void add_back();						//�w�i�x�N�^�[�̖��O���o�^����Ă���摜�̃n���h�����擾���}�b�v�ɒǉ�
	void register_back();					//�w�i�x�N�^�[�ɔw�i�摜�̖��O��ǉ�
	void add_button();						//�{�^���x�N�^�[�̖��O���o�^����Ă���摜�̃n���h�����擾���}�b�v�ɒǉ�
	void register_button();					//�{�^���x�N�^�[�ɔw�i�摜�̖��O��ǉ�
	void add_status();						//�X�e�[�^�X�x�N�^�[�̖��O���o�^����Ă���摜�̃n���h�����擾���}�b�v�ɒǉ�
	void register_status();					//�X�e�[�^�X�x�N�^�[�ɔw�i�摜�̖��O��ǉ�
	void set_volume(int vol);				//���ׂẲ��y�t�@�C���ɉ��ʐݒ��K�p
	void stop_bgm();						//BGM�t�@�C�������ׂčĐ��I��

	void increase_back_number();			//�w�i�摜�̔ԍ��𑝂₷
	void increase_status_number();			//�X�e�[�^�X�����̔w�i�摜�̔ԍ��𑝂₷
	void decrease_back_number();			//�w�i�摜�̔ԍ������炷
	void decrease_status_number();			//�X�e�[�^�X�����̔w�i�摜�̔ԍ������炷
	int get_back_number();					//���݂̔w�i�摜�̔ԍ���Ԃ�
	int get_status_number();				//���݂̃X�e�[�^�X�����̔w�i�摜�̔ԍ���Ԃ�
	void set_back_number(int n);			//�w�i�摜�̔ԍ���ݒ肷��
	void set_status_number(int n);			//�X�e�[�^�X�����̔w�i�摜�̔ԍ���ݒ肷��
};
