#pragma once

#include "Vector2.h"
#include <vector>
#include <memory>
#include <string>

//�G�t�F�N�g�̃p�[�e�B�N���̊��N���X
class Particle
{
protected:
	Vector2 point;					//���W
	Vector2 velocity;				//���x
	Vector2 acceleration;			//�����x
	int t;							//��������Ă���̎���
	double angle;					//�p�x
	double angleV;					//�p�x�̕ω���
	double alpha;					//�����x
	double startAngle;				//�����p�x
	double ratio;					//�g�嗦
	double ratioV;					//�g�嗦�̕ω���

	int graphHandle;				//�摜

	const int maxT;					 //�G�t�F�N�g�̕`�悷�鎞��

public:
	bool eraseFlag;               

	Particle(Vector2 p, Vector2 v, Vector2 a, double aV, double sA, int mT, int gHandle, double r, double rV);

	virtual void update();			//�X�V
	void erase_update();
	void alpha_update();
	void draw();
};

//sin�g��`���Ȃ��珸���Ă����G�t�F�N�g
class EffectA : public Particle
{
public:
	EffectA(Vector2 p, int gHandle);
	virtual void update();
};

//���ˏ�ɔ�юU���]���Ȃ��痎���Ă����G�t�F�N�g
class EffectB : public Particle
{
public:
	EffectB(Vector2 p, int gHandle);
};


//�p�[�e�B�N���̃|�C���^�̃x�N�^�[�������Ǘ�����N���X
class Effect
{
	std::vector<std::shared_ptr<Particle>> vec;
public:
	int t;

	Effect();
	
	//�p�[�e�B�N������
	std::shared_ptr<Particle> create(std::string str, Vector2 p, int gHandle);
	//�p�[�e�B�N���𐶐����ăx�N�^�[�ɒǉ�
	void add(std::string str, Vector2 p, int rate, int gHandle);
	void update();
	void draw();
};