#pragma once

#include "Vector2.h"
#include <memory>
#include <string>
#include "effect.h"

enum State{ pikaia, chick, bird , kitten, cat };



//進化時に引き継がれるデータ
struct PlayerData
{
public:
	double individualValueFeed;
	double individualValuePlay;
	int satiety;
	int exercise;
	double grouth;
	double trust;
	State state;
	int diseaseCount;
	bool diseaseFlag;
	int fatCount;
	bool fatFlag;
	Vector2 point;
	Vector2 move;
	int generation;

	PlayerData();

	PlayerData(double tr, int gen);

	PlayerData(double iF, double iP, int sa, int e, double g, double t, State st,
		int dc, bool df, int fc, bool ff, int gen, Vector2 p, Vector2 m);
};

//キャラクターの基底クラス
class IPlayer
{
protected:


	class Impl;
	std::shared_ptr<Impl> impl;

public:

	Effect effect;
	Rectangular playerRange;

	IPlayer(Vector2 h, double r_, int mG);

	void set_player(double iF, double iP, int sa, int e, double g, State st, int dc, bool df, int fc, bool ff);
	void set_player(PlayerData data);
	void set_grouth(int g);
	void set_state(State s);
	void set_disease(int c, bool f);
	void set_point(Vector2 p);
	void set_move(Vector2 m);
	void set_player_data(PlayerData pd);
	void set_target();
	void get_ill();


	int     get_satiety()                const;
	int     get_exercise()               const;
	double  get_grouth()                 const;
	double  get_trust()                  const;
	State   get_state()                  const;
	int     get_disease_count()          const;
	bool    get_disease_flag()           const;
	int     get_fat_count()              const;
	bool    get_fat_flag()               const;
	Vector2 get_point()                  const;
	Vector2 get_move()                   const;
	PlayerData  get_player_data()        const;
	double  get_max_grouth()             const;
	double  get_max_trust()              const;
	double  get_mouse_speed_threshold()  const;
	Circle  get_head()                   const;

	virtual void update();
	virtual void draw();

	virtual void move_update();
	virtual void fat_move_update();
	void normal_update();
	void disease_update();
	void fat_update();

	bool is_on_mouse();

	void feed();
	void play();
	void cure();
	void stroke();
};

//ピカイア状態のキャラクター
class Pikaia : public IPlayer
{
public:
	Pikaia();

	virtual void draw();
};

//鳥のヒナ状態のキャラクター
class Chick : public IPlayer
{

public:

	Chick();

	virtual void draw();
};

//成鳥の状態のキャラクター
class Bird : public IPlayer
{

public:

	Bird();

	virtual void draw();
};

//子猫の状態のキャラクター
class Kitten : public IPlayer
{

public:

	Kitten();

	virtual void draw();
};

//成猫の状態のキャラクター
class Cat : public IPlayer
{

public:

	Cat();

	virtual void draw();
};


//プレイヤーを管理するクラス
class PlayerManager{
private:
	PlayerData wPlayerData; //入れ替え用変数
	bool evolutionFlag;
	int time;

public:
	std::shared_ptr<IPlayer> playerPtr;
	PlayerManager();

	void update();

	void evolution_animation(int gHandle1, int gHandle2);

	void draw();

	void save();

	void load();

	std::shared_ptr<IPlayer> create(State sta);

	void evolution(State sta);

	void feed();
	void play();
	void cure();
	void stroke();
};

