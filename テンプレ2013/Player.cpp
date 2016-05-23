#pragma once

#include <DxLib.h>
#include "Vector2.h"
#include "player.h"
#include "graph.h"
#include "time.h"
#include "Impl.h"
#include "myglobal.h"
#include "Draw.h"
#include "MyFunc.h"
#include "input.h"
#include "file.h"


PlayerData::PlayerData() :
individualValueFeed(GetRand(40) / 100.0 + 0.8),
individualValuePlay(GetRand(40) / 100.0 + 0.8),
satiety(0),
exercise(0),
grouth(0),
trust(0),
state(pikaia),
diseaseCount(0),
diseaseFlag(false),
fatCount(0),
fatFlag(false),
generation(1),
point(homePoint),
move(homePoint)
{

}

PlayerData::PlayerData(double tr, int gen) :
individualValueFeed(GetRand(40) / 100.0 + 0.8),
individualValuePlay(GetRand(40) / 100.0 + 0.8),
satiety(0),
exercise(0),
grouth(0),
trust(tr),
state(pikaia),
diseaseCount(0),
diseaseFlag(false),
fatCount(0),
fatFlag(false),
generation(gen),
point(homePoint),
move(homePoint)
{

}

PlayerData::PlayerData(double iF, double iP, int sa, int e, double g, double t, State st,
	int dc, bool df, int fc, bool ff, int gen, Vector2 p, Vector2 m) :
	individualValueFeed(iF),
	individualValuePlay(iP),
	satiety(sa),
	exercise(e),
	grouth(g),
	trust(t),
	state(st),
	diseaseCount(dc),
	diseaseFlag(df),
	fatCount(fc),
	fatFlag(ff),
	generation(gen),
	point(p),
	move(m)
{

}

IPlayer::IPlayer(Vector2 h, double r_, int mG)
{
	impl = std::make_shared<Impl>(h, r_, mG);
}


Pikaia::Pikaia() :
IPlayer(Vector2(-50, 5), 25, 80)
{
	playerRange.set(Vector2(50, 40), Vector2(SCREEN.x - 50, SCREEN.x - 20));
}

Chick::Chick() :
IPlayer(Vector2(-42, -40), 25, 150)
{
	playerRange.set(Vector2(30, 60), Vector2(SCREEN.x - 30, SCREEN.x - 50));
}

Bird::Bird() :
IPlayer(Vector2(-47, -65), 23, 150)
{
	playerRange.set(Vector2(40, 110), Vector2(SCREEN.x - 40, SCREEN.x - 80));
}

Kitten::Kitten() :
IPlayer(Vector2(-20, -40), 35, 150)
{
	playerRange.set(Vector2(30, 60), Vector2(SCREEN.x - 30, SCREEN.x - 50));
}

Cat::Cat() :
IPlayer(Vector2(-17, -70), 23, 150)
{
	playerRange.set(Vector2(40, 110), Vector2(SCREEN.x - 40, SCREEN.x - 80));
}

IPlayer::Impl::Impl(Vector2 h, double r_, int mG) :
smileFlag(0),
maxSatiety(5),
maxExercise(5),
maxGrouth(mG),
maxTrust(100),
maxDiseaseCount(5),
fatCountThresholdS(10),
fatCountThresholdL(25),
maxFatCount(30),
MoveV(2),
moveTimeMax(3),
moveTimeMin(1),
feedGrouth_s(1 * playerData.individualValueFeed),
feedGrouth_m(3 * playerData.individualValueFeed),
feedGrouth_l(5 * playerData.individualValueFeed),
playGrouth_s(2 * playerData.individualValuePlay),
playGrouth_m(5 * playerData.individualValuePlay),
playGrouth_l(10 * playerData.individualValuePlay),
trustRate(0.1),
trustThreshold_s(50),
trustThreshold_l(80),
moveRate(0.008),
fatMoveRate(3),
mouseSpeedThreshold(60),
head(h, r_)
{
}

IPlayer::Impl::Impl(Vector2 h, double r_, int mG, int fTs, int fTl) :
maxSatiety(5),
maxExercise(5),
maxGrouth(mG),
maxTrust(100),
maxDiseaseCount(5),
fatCountThresholdS(fTs),
fatCountThresholdL(fTl),
maxFatCount(30),
MoveV(2),
moveTimeMax(3),
moveTimeMin(1),
feedGrouth_s(1 * playerData.individualValueFeed),
feedGrouth_m(3 * playerData.individualValueFeed),
feedGrouth_l(5 * playerData.individualValueFeed),
playGrouth_s(2 * playerData.individualValuePlay),
playGrouth_m(5 * playerData.individualValuePlay),
playGrouth_l(10 * playerData.individualValuePlay),
trustRate(0.1),
trustThreshold_s(50),
trustThreshold_l(80),
moveRate(0.008),
fatMoveRate(3),
mouseSpeedThreshold(60),
head(h, r_)
{
}

bool IPlayer::Impl::reduce_satiety()
{
	playerData.satiety -= 1;
	if (playerData.satiety < 0)
	{
		playerData.satiety = 0;
		return false;
	}
	else { return true; }
}

bool IPlayer::Impl::reduce_exercise()
{
	playerData.exercise -= 1;
	if (playerData.exercise < 0)
	{
		playerData.exercise = 0;
		return false;
	}
	else { return true; }
}

void IPlayer::Impl::recover_ill(){ playerData.diseaseFlag = false; }
void IPlayer::Impl::reset_disease_count(){ playerData.diseaseCount = 0; }
void IPlayer::Impl::get_thin(){ playerData.fatFlag = false; }

void IPlayer::Impl::reduce_fat_count()
{
	if (playerData.fatCount > 0){ playerData.fatCount--; }
}

void IPlayer::Impl::set_trust(double x)
{
	playerData.trust = x;
	if (playerData.trust < 0){ playerData.trust = 0; }
	if (playerData.trust > maxTrust){ playerData.trust = maxTrust; }
}

bool IPlayer::Impl::increase_satiety(int n)
{
	if (playerData.satiety >= maxSatiety){ return false; }
	playerData.satiety += n;
	if (playerData.satiety > maxSatiety)
	{
		playerData.satiety = maxSatiety;
	}
	return true;
}

bool IPlayer::Impl::increase_exercise(int n)
{
	if (playerData.exercise >= maxExercise){ return false; }
	playerData.exercise += n;
	if (playerData.exercise > maxExercise){ playerData.exercise = maxExercise; }
	return true;
}

void IPlayer::Impl::increase_grouth(double n)
{
	playerData.grouth += n;
	if (playerData.grouth > maxGrouth){ playerData.grouth = maxGrouth; }
}

bool IPlayer::Impl::increase_trust(double x)
{
	playerData.trust += x;
	if (playerData.trust > maxTrust)
	{
		playerData.trust = maxTrust;
		return false;
	}
	return true;
}

void IPlayer::Impl::increase_disease_count()
{
	if (playerData.diseaseCount < maxDiseaseCount){ playerData.diseaseCount++; }
}

void IPlayer::Impl::get_ill()
{
	playerData.diseaseFlag = true;
}


void IPlayer::Impl::increase_fat_count()
{
	if (playerData.fatCount < maxFatCount){ playerData.fatCount++; }
}

void IPlayer::Impl::get_fat()
{
	playerData.fatFlag = true;
}

void IPlayer::set_player(double iF, double iP, int s, int e, double g, State st, int dc, bool df, int fc, bool ff)
{
	impl->playerData.individualValueFeed = iF;
	impl->playerData.individualValuePlay = iP;
	impl->playerData.satiety = s;
	impl->playerData.exercise = e;
	impl->playerData.grouth = g;
	impl->playerData.state = st;
	impl->playerData.diseaseCount = dc;
	impl->playerData.diseaseFlag = df;
	impl->playerData.fatCount = fc;
	impl->playerData.fatFlag = ff;
}

void IPlayer::set_player(PlayerData data)
{
	impl->playerData = data;
}

void IPlayer::set_grouth(int g){ impl->playerData.grouth = g; }
void IPlayer::set_state(State s){ impl->playerData.state = s; }

void IPlayer::set_disease(int c, bool f)
{
	impl->playerData.diseaseCount = c;
	impl->playerData.diseaseFlag = f;
}

void IPlayer::set_point(Vector2 p){ impl->playerData.point = p; }
void IPlayer::set_move(Vector2 m){ impl->playerData.move = m; }
void IPlayer::set_player_data(PlayerData pd){ impl->playerData = pd; }

void IPlayer::set_target()
{
	impl->playerData.move = playerRange.rand();
}

void IPlayer::get_ill()

{
	impl->get_ill();
	Sound::back_play(Graph::get().musicMap.at("pikaiaillness.wav"));
	impl->reset_disease_count();
}

int     IPlayer::get_satiety()        const { return impl->playerData.satiety; }
int     IPlayer::get_exercise()       const { return impl->playerData.exercise; }
double  IPlayer::get_grouth()         const { return impl->playerData.grouth; }
double  IPlayer::get_trust()          const { return impl->playerData.trust; }
State   IPlayer::get_state()          const { return impl->playerData.state; }
int     IPlayer::get_disease_count()  const { return impl->playerData.diseaseCount; }
bool    IPlayer::get_disease_flag()   const { return impl->playerData.diseaseFlag; }
Vector2 IPlayer::get_move()           const { return impl->playerData.move; }
Vector2 IPlayer::get_point()          const { return impl->playerData.point; }
PlayerData IPlayer::get_player_data() const { return impl->playerData; }
int     IPlayer::get_fat_count()      const { return impl->playerData.fatCount; }
bool    IPlayer::get_fat_flag()       const { return impl->playerData.fatFlag; }
double  IPlayer::get_max_grouth()     const { return impl->maxGrouth; }
double  IPlayer::get_max_trust()      const { return impl->maxTrust; }
double  IPlayer::get_mouse_speed_threshold() const { return impl->mouseSpeedThreshold; }

//std::string IPlayer::get_player_data_string()  const
//{
//	std::string str = std::to_string(get_satiety());
//	str.append(" ");
//	str.append(std::to_string(get_exercise()));
//	str.append(" ");
//	str.append(std::to_string(get_grouth()));
//	str.append(" ");
//	str.append(std::to_string(get_state()));
//	str.append(" ");
//	str.append(std::to_string(get_disease_count()));
//	str.append(" ");
//	str.append(std::to_string(get_disease_flag()));
//	str.append(" ");
//	str.append(std::to_string(get_fat_count()));
//	str.append(" ");
//	str.append(std::to_string(get_fat_flag()));
//	return str;
//}


Circle IPlayer::get_head() const
{
	if (impl->playerData.move.x > impl->playerData.point.x)
	{
		return impl->head.symmetry_y(impl->playerData.point);
	}
	else return impl->head.slide(impl->playerData.point);
}

void IPlayer::update()
{
	if (impl->playerData.diseaseFlag){ disease_update(); }
	else if (impl->playerData.fatFlag){ fat_update(); }
	else { normal_update(); }
}

void IPlayer::draw()
{
	DrawFormatStringToHandle(20, 140, 0xFFFFFF, SEGOE_20, "%d", impl->playerData.state);
	if (impl->playerData.state == pikaia)
	{
		MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("pikaia.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
	}
	else
	{
		MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
	}
}

void Pikaia::draw()
{
	if (!impl->playerData.diseaseFlag)
	{
		if (impl->smileFlag > 0)
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("pikaia_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
			impl->smileFlag--;
		}
		else
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("pikaia.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
		}
	}
	else
	{
		MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("pikaia_d.png"));
	}
}

void Chick::draw()
{
	if (!impl->playerData.diseaseFlag)
	{
		if (!impl->playerData.fatFlag)
		{
			if (impl->smileFlag > 0)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				impl->smileFlag--;
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
			}
		}
		else
		{
			if (impl->playerData.fatCount < impl->fatCountThresholdL)
			{
				if (impl->smileFlag >0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_f_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_f.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
			else
			{
				if (impl->smileFlag > 0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_f2_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_f2.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
		}
	}
	else
	{
		if (!impl->playerData.fatFlag)
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_d.png"));
		}
		else
		{
			if (impl->playerData.fatCount < 25)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_fd.png"));
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("chick_f2d.png"));
			}
		}
	}
}

void Bird::draw()
{
	if (!impl->playerData.diseaseFlag)
	{
		if (!impl->playerData.fatFlag)
		{
			if (impl->smileFlag > 0)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				impl->smileFlag--;
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
			}
		}
		else
		{
			if (impl->playerData.fatCount < impl->fatCountThresholdL)
			{
				if (impl->smileFlag >0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_f_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_f.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
			else
			{
				if (impl->smileFlag > 0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_f2_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_f2.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
		}
	}
	else
	{
		if (!impl->playerData.fatFlag)
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_d.png"));
		}
		else
		{
			if (impl->playerData.fatCount < 25)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_fd.png"));
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("bird_f2d.png"));
			}
		}
	}
}


void Kitten::draw()
{
	if (!impl->playerData.diseaseFlag)
	{
		if (!impl->playerData.fatFlag)
		{
			if (impl->smileFlag > 0)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				impl->smileFlag--;
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
			}
		}
		else
		{
			if (impl->playerData.fatCount < impl->fatCountThresholdL)
			{
				if (impl->smileFlag >0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_f_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_f.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
			else
			{
				if (impl->smileFlag > 0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_f2_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_f2.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
		}
	}
	else
	{
		if (!impl->playerData.fatFlag)
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_d.png"));
		}
		else
		{
			if (impl->playerData.fatCount < 25)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_fd.png"));
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("kitten_f2d.png"));
			}
		}
	}
}

void Cat::draw()
{
	if (!impl->playerData.diseaseFlag)
	{
		if (!impl->playerData.fatFlag)
		{
			if (impl->smileFlag > 0)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				impl->smileFlag--;
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
			}
		}
		else
		{
			if (impl->playerData.fatCount < impl->fatCountThresholdL)
			{
				if (impl->smileFlag >0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_f_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_f.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
			else
			{
				if (impl->smileFlag > 0)
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_f2_smile.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
					impl->smileFlag--;
				}
				else
				{
					MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_f2.png"), 255, impl->playerData.move.x > impl->playerData.point.x);
				}
			}
		}
	}
	else
	{
		if (!impl->playerData.fatFlag)
		{
			MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_d.png"));
		}
		else
		{
			if (impl->playerData.fatCount < 25)
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_fd.png"));
			}
			else
			{
				MyDraw::center(impl->playerData.point, Graph::get().graphMap.at("cat_f2d.png"));
			}
		}
	}
}
void IPlayer::move_update()
{
	Func::moverate(impl->playerData.point, impl->playerData.move, impl->moveRate);
	impl->playerData.point.maximize(playerRange);
}

void IPlayer::fat_move_update()
{
	Func::moverate(impl->playerData.point, impl->playerData.move, impl->moveRate / impl->fatMoveRate);
	impl->playerData.point.maximize(playerRange);
}

void IPlayer::normal_update()
{
	if (TimeManager::get().check_down("satietyRate"))
	{
		if (impl->reduce_satiety()){}
		else { impl->increase_disease_count(); }
	}
	if (TimeManager::get().check_down("exerciseRate"))
	{
		if (impl->reduce_exercise()){}
		else { impl->increase_disease_count(); }
	}
	if (TimeManager::get().check_down("movePause"))
	{
		set_target();
		TimeManager::get().map.at("movePause")->set(GetRand(impl->moveTimeMax) + impl->moveTimeMin);
	}
	if (TimeManager::get().check_down("diseaseRate"))
	{
		if (GetRand(100) < get_disease_count() + 16 - 2 * (get_satiety() + get_exercise()))
		{
			impl->playerData.diseaseFlag = true;
		}
	}
	move_update();
	if (impl->playerData.diseaseCount == impl->maxDiseaseCount)
	{
		get_ill();
	}
	if (impl->playerData.state != pikaia)
	{
		if (impl->playerData.fatCount >= impl->fatCountThresholdS){ impl->get_fat(); }
	}
}

void IPlayer::disease_update()
{
	if (TimeManager::get().check_down("satietyRate"))
	{
		impl->reduce_satiety();
	}
	if (TimeManager::get().check_down("exerciseRate"))
	{
		impl->reduce_exercise();
	}
	impl->reset_disease_count();
}

void IPlayer::fat_update()
{
	if (TimeManager::get().check_down("satietyRate"))
	{
		if (impl->reduce_satiety()){}
		else { impl->increase_disease_count(); }
	}
	if (TimeManager::get().check_down("exerciseRate"))
	{
		if (impl->reduce_exercise()){}
		else { impl->increase_disease_count(); }
	}
	if (TimeManager::get().check_down("movePause"))
	{
		set_target();
		TimeManager::get().map.at("movePause")->set(GetRand(impl->moveTimeMax*impl->fatMoveRate) + impl->moveTimeMin*impl->fatMoveRate);
	}
	if (TimeManager::get().check_down("diseaseRate"))
	{
		if (GetRand(100) < get_disease_count() + 20 - 2 * get_satiety() - 2 * get_exercise())
		{
			get_ill();
		}
	}
	fat_move_update();
	if (impl->playerData.diseaseCount == impl->maxDiseaseCount)
	{
		get_ill();
	}
	if (impl->playerData.fatCount < impl->fatCountThresholdS){ impl->get_thin(); }
}

bool IPlayer::is_on_mouse()
{
	return get_head().is_in(Input::get().mouse);
}

void IPlayer::feed()
{
	Sound::back_play(Graph::get().musicMap.at("feed.wav"));
	if (!impl->playerData.diseaseFlag){
		if (impl->increase_satiety(1)){
			if (impl->playerData.fatFlag == false){
				if (impl->playerData.trust < impl->trustThreshold_s)
				{
					impl->increase_grouth(impl->feedGrouth_s);
				}
				else if (impl->playerData.trust < impl->trustThreshold_l)
				{
					impl->increase_grouth(impl->feedGrouth_m);
				}
				else { impl->increase_grouth(impl->feedGrouth_l); }
			}
		}
		else
		{
			impl->increase_fat_count();
			if ((impl->playerData.fatCount == impl->fatCountThresholdS || impl->playerData.fatCount == impl->fatCountThresholdL) && impl->playerData.state != pikaia)
			{
				Sound::back_play(Graph::get().musicMap.at("pikaiaObesity.wav"));
			}
		}
	}
}

void IPlayer::play()
{
	Sound::back_play(Graph::get().musicMap.at("play.wav"));
	if (!impl->playerData.diseaseFlag){
		impl->reduce_fat_count();
		if (impl->increase_exercise(1)){
			if (impl->playerData.fatFlag == false){
				if (impl->playerData.trust < impl->trustThreshold_s)
				{
					impl->increase_grouth(impl->playGrouth_s);
				}
				else if (impl->playerData.trust < impl->trustThreshold_l)
				{
					impl->increase_grouth(impl->playGrouth_m);
				}
				else { impl->increase_grouth(impl->playGrouth_l); }
			}
		}
	}
}

void IPlayer::cure()
{
	Sound::back_play(Graph::get().musicMap.at("kaifuku.wav"));
	impl->recover_ill();
	impl->reset_disease_count();
}

void IPlayer::stroke()
{
	if (!impl->playerData.diseaseFlag)
	{
		impl->smileFlag = 10;
		if (impl->increase_trust(impl->trustRate)){ effect.add("a", get_head().get_center(), 8, Graph::get().graphMap.at("effect2.png")); }
		else{ effect.add("a", get_head().get_center(), 10, Graph::get().graphMap.at("effect4.png")); }
	}
}

PlayerManager::PlayerManager() :
wPlayerData(),
evolutionFlag(false),
time(0)
{
	playerPtr = std::make_shared<Pikaia>();
};

void PlayerManager::update()
{
	if (!evolutionFlag)
	{
		if (TimeManager::get().check_down("autoSave")){ save(); }
		playerPtr->update();
		if (playerPtr->get_grouth() == playerPtr->get_max_grouth() && playerPtr->get_state() == pikaia)
		{
			evolutionFlag = true;
			time = 0;
			if (playerPtr->get_player_data().trust == playerPtr->get_max_trust()){ evolution(kitten); }
			else{ evolution(chick); }
		}
		if (playerPtr->get_grouth() == playerPtr->get_max_grouth() && playerPtr->get_state() == chick)
		{
			evolutionFlag = true;
			time = 0;
			evolution(bird);
		}
		if (playerPtr->get_grouth() == playerPtr->get_max_grouth() && playerPtr->get_state() == kitten)
		{
			evolutionFlag = true;
			time = 0;
			evolution(cat);
		}
	}
	else
	{
		time++;
		if (time == 360)
		{
			Sound::back_play(Graph::get().musicMap.at("pikaiaEvo.wav"));
			for (int i = 0; i < 20; i++)
			{
				playerPtr->effect.add("b", playerPtr->get_point(), 0, Graph::get().graphMap.at("effect6.png"));
			}
			evolutionFlag = false;
		}
	}
}

void PlayerManager::evolution_animation(int gHandle1, int gHandle2)
{
	if (time <= 60)
	{
		if (time % 60 <= 30)
		{
			MyDraw::center(playerPtr->get_point(), gHandle1);
		}
		else
		{
			MyDraw::center(playerPtr->get_point(), gHandle2);
		}
	}
	else if (time <= 120)
	{
		if (time % 30 <= 15)
		{
			MyDraw::center(playerPtr->get_point(), gHandle1);
		}
		else
		{
			MyDraw::center(playerPtr->get_point(), gHandle2);
		}
	}
	else if (time <= 240)
	{
		if (time % 20 <= 10)
		{
			MyDraw::center(playerPtr->get_point(), gHandle1);
		}
		else
		{
			MyDraw::center(playerPtr->get_point(), gHandle2);
		}
	}
	else
	{
		if (time % 10 <= 5)
		{
			MyDraw::center(playerPtr->get_point(), gHandle1);
		}
		else
		{
			MyDraw::center(playerPtr->get_point(), gHandle2);
		}
	}
}

void PlayerManager::draw()
{
	if (!evolutionFlag){ playerPtr->draw(); }
	else
	{
		if (playerPtr->get_player_data().state == chick)
		{
			evolution_animation(Graph::get().graphMap.at("pikaia_e.png"), Graph::get().graphMap.at("chick_e.png"));
		}
		else if (playerPtr->get_player_data().state == bird)
		{
			evolution_animation(Graph::get().graphMap.at("chick_e.png"), Graph::get().graphMap.at("bird_e.png"));
		}
		else if (playerPtr->get_player_data().state == kitten)
		{
			evolution_animation(Graph::get().graphMap.at("pikaia_e.png"), Graph::get().graphMap.at("kitten_e.png"));
		}
		else if (playerPtr->get_player_data().state == cat)
		{
			evolution_animation(Graph::get().graphMap.at("kitten_e.png"), Graph::get().graphMap.at("cat_e.png"));
		}
	}
}

void PlayerManager::save()
{
	File::get().save_data(playerPtr->get_player_data());
}

void PlayerManager::load()
{
	playerPtr->set_player(File::get().read_data());
	wPlayerData = playerPtr->get_player_data();
	playerPtr = create(playerPtr->get_state());
	playerPtr->set_player_data(wPlayerData);
}

std::shared_ptr<IPlayer> PlayerManager::create(State sta)
{
	if (sta == pikaia){ return std::make_shared<Pikaia>(); }
	else if (sta == chick){ return std::make_shared<Chick>(); }
	else if (sta == bird){ return std::make_shared<Bird>(); }
	else if (sta == kitten){ return std::make_shared<Kitten>(); }
	else if (sta == cat){ return std::make_shared<Cat>(); }
}

void PlayerManager::evolution(State sta)
{
	wPlayerData = playerPtr->get_player_data();
	playerPtr = create(sta);
	playerPtr->set_player_data(wPlayerData);
	playerPtr->set_grouth(0);
	playerPtr->set_state(sta);
	save();
}


void PlayerManager::feed()
{
	if (!evolutionFlag)
	{
		playerPtr->feed();
	}
}

void PlayerManager::play()
{
	if (!evolutionFlag)
	{
		playerPtr->play();
	}
}

void PlayerManager::cure()
{
	if (!evolutionFlag)
	{
		playerPtr->cure();
	}
}

void PlayerManager::stroke()
{
	if (!evolutionFlag)
	{
		playerPtr->stroke();
	}
}