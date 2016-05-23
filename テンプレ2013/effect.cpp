#include "effect.h"
#include "Draw.h"
#include "myglobal.h"
#include <DxLib.h>

Particle::Particle(Vector2 p, Vector2 v, Vector2 a, double aV, double sA, int mT, int gHandle, double r, double rV) :
point(p),
velocity(v),
acceleration(a),
t(0),
eraseFlag(false),
angle(0),
angleV(aV),
alpha(255),
maxT(mT),
startAngle(sA),
graphHandle(gHandle),
ratio(r),
ratioV(rV)
{
}

void Particle::update()
{
	point += velocity;
	velocity += acceleration;
	t++;
	angle += angleV;
	ratio += ratioV;
	erase_update();
	alpha_update();
}

void Particle::erase_update()
{
	if (t > maxT)
	{
		eraseFlag = true;
	}
}

void Particle::alpha_update()
{
	alpha -= 255 / maxT;
}


void Particle::draw()
{
	MyDraw::exrot(point, ratio, angle, graphHandle, alpha);
}

EffectA::EffectA(Vector2 p, int gHandle):
Particle(p, Vector2::GetPolar(2, (GetRand(120) - 60) / 360.0*PI - PI / 2), Vector2(0, 0), 0, GetRand(360) / 360.0*PI, 60, gHandle, 1, 0)
{
}

void EffectA::update()
{
	point += velocity + Vector2(cos(startAngle + t / 8.0), 0) * 3;
	t++;
	erase_update();
	alpha_update();
}

EffectB::EffectB(Vector2 p, int gHandle) :
Particle(p, Vector2::GetPolar(2, GetRand(720) / 360.0*PI)*(GetRand(8) / 4.0 + 1), Vector2(0, 0.3), GetRand(10)/200 + 0.1, 0, 35, gHandle, (GetRand(3)/6 + 0.5), 0.02)
{
}

Effect::Effect():
t(0)
{

}

std::shared_ptr<Particle> Effect::create(std::string str, Vector2 p, int gHandle)
{
	if (str == "a"){ return std::make_shared<EffectA>(p, gHandle); }
	else if (str == "b"){ return std::make_shared<EffectB>(p, gHandle); }
	return nullptr;
}

void Effect::add(std::string str, Vector2 p, int rate, int gHandle)
{
	if (rate > 1)
	{
		if (t % rate == 1)
		{
			vec.emplace_back(create(str, p, gHandle));
		}
	}
	else
	{
		vec.emplace_back(create(str, p, gHandle));
	}
}

void Effect::update()
{
	for (auto element : vec){ element->update(); }
	t++;
	for (auto iter = vec.begin(); iter < vec.end();)
	{
		if ((*iter)->eraseFlag)
		{
			iter = vec.erase(iter);
		}
		else { iter++; }
	}
}

void Effect::draw()
{
	for (auto element : vec) { element->draw(); }
}