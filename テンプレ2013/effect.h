#pragma once

#include "Vector2.h"
#include <vector>
#include <memory>
#include <string>

//エフェクトのパーティクルの基底クラス
class Particle
{
protected:
	Vector2 point;					//座標
	Vector2 velocity;				//速度
	Vector2 acceleration;			//加速度
	int t;							//生成されてからの時間
	double angle;					//角度
	double angleV;					//角度の変化率
	double alpha;					//透明度
	double startAngle;				//初期角度
	double ratio;					//拡大率
	double ratioV;					//拡大率の変化率

	int graphHandle;				//画像

	const int maxT;					 //エフェクトの描画する時間

public:
	bool eraseFlag;               

	Particle(Vector2 p, Vector2 v, Vector2 a, double aV, double sA, int mT, int gHandle, double r, double rV);

	virtual void update();			//更新
	void erase_update();
	void alpha_update();
	void draw();
};

//sin波を描きながら昇っていくエフェクト
class EffectA : public Particle
{
public:
	EffectA(Vector2 p, int gHandle);
	virtual void update();
};

//放射状に飛び散り回転しながら落ちていくエフェクト
class EffectB : public Particle
{
public:
	EffectB(Vector2 p, int gHandle);
};


//パーティクルのポインタのベクターを持ち管理するクラス
class Effect
{
	std::vector<std::shared_ptr<Particle>> vec;
public:
	int t;

	Effect();
	
	//パーティクル生成
	std::shared_ptr<Particle> create(std::string str, Vector2 p, int gHandle);
	//パーティクルを生成してベクターに追加
	void add(std::string str, Vector2 p, int rate, int gHandle);
	void update();
	void draw();
};