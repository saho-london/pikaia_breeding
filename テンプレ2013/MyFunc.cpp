#include <iostream>

#include "MyFunc.h"
#include "Vector2.h"
#include "Draw.h"
#include "myglobal.h"
#include "input.h"

#pragma once

//2������̓_��\���N���X
//�R���X�g���N�^��`
Vector2::Vector2() :x(0), y(0){}
Vector2::Vector2(double x_, double y_) : x(x_), y(y_){}

//�I�y���[�^�[�I�[�o�[���[�h
Vector2& Vector2::operator +=(const Vector2& t)
{
	x += t.x;
	y += t.y;
	return *this;
}
Vector2& Vector2::operator -=(const Vector2& t)
{
	x -= t.x;
	y -= t.y;
	return *this;
}
Vector2 Vector2::operator +(const Vector2& t){
	Vector2 temp;
	temp.x = x + t.x;
	temp.y = y + t.y;
	return temp;
}
Vector2 Vector2::operator -(const Vector2& t){
	Vector2 temp;
	temp.x = x - t.x;
	temp.y = y - t.y;
	return temp;
}
Vector2 Vector2::operator *(double t){
	Vector2 temp;
	temp.x = x * t;
	temp.y = y * t;
	return temp;
}
Vector2 Vector2::operator /(double t){
	Vector2 temp;
	temp.x = x / t;
	temp.y = y / t;
	return temp;
}
Vector2& Vector2::operator *=(double t)
{
	x *= t;
	y *= t;
	return *this;
}
Vector2& Vector2::operator /=(double t)
{
	x /= t;
	y /= t;
	return *this;
}

//����
double Vector2::operator *(const Vector2& t){
	return x * t.x + y * t.y;
}

//�O��
double Vector2::cross(const Vector2& t){
	return x * t.y - y * t.x;
}

//����֐�
void Vector2::Set(double x_, double y_)
{
	x = x_; y = y_;
}
//���_�𒆐S�ɉ�]
void Vector2::Rotate(double rad)
{
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = x;	//�ꎞ�i�[
	x = cost * tx - sint * y;		// ( cos�� -sin��) ( x )
	y = sint * tx + cost * y;		// ( sin�� xos�� ) ( y )
}
//center�𒆐S�ɉ�]
void Vector2::RotateOnPoint(double rad, const Vector2 &center)
{
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = x - center.x;	//�ꎞ�i�[
	double ty = y - center.y;	//�ꎞ�i�[
	x = cost * tx - sint * ty + center.x;		// ( cos�� -sin��) ( x )
	y = sint * tx + cost * ty + center.y;		// ( sin�� xos�� ) ( y )
}
//���_�𒆐S�Ƀx�N�g������]�������̂�Ԃ�
Vector2 Vector2::GetRotate(double rad){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = temp.x;	//�ꎞ�i�[
	temp.x = cost * tx - sint * temp.y;		// ( cos�� -sin��) ( x )
	temp.y = sint * tx + cost * temp.y;		// ( sin�� xos�� ) ( y )
	return temp;
}

//center�𒆐S�ɉ�]�����x�N�g����Ԃ�
Vector2 Vector2::GetRotateOnPoint(double rad, const Vector2 &center){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = temp.x - center.x;	//�ꎞ�i�[
	double ty = temp.y - center.y;	//�ꎞ�i�[
	temp.x = cost * tx - sint * ty + center.x;		// ( cos�� -sin��) ( x )
	temp.y = sint * tx + cost * ty + center.y;		// ( sin�� xos�� ) ( y )
	return temp;
}

//dx,dy�������ړ�
void Vector2::Translate(double dx, double dy)
{
	x += dx;
	y += dy;
}
//�x�N�g���̑傫����Ԃ�
double Vector2::Magnitude(){
	return sqrt(x*x + y*y);
}
//�x�N�g���𐳋K������
void Vector2::Normalize(){
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	x /= r;
	y /= r;
}

//���K�����ꂽ�x�N�g����Ԃ�
Vector2 Vector2::GetNormalized(){
	Vector2 temp = *this;
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	temp.x /= r;
	temp.y /= r;
	return temp;
}

//�x�N�g���̊p�x��Ԃ�
double Vector2::GetAngle(){
	return atan2(y, x);
}

//�ɍ��W�n���ŕ\���ꂽ�x�N�g����Ԃ� static
Vector2 Vector2::GetPolar(double r, double angle){
	Vector2 temp;
	temp.x = r * cos(angle);
	temp.y = r * sin(angle);
	return temp;
}

//�w�肵���͈͓��Ƀx�N�g�����C��
void Vector2::maximize(double xMin, double xMax, double yMin, double yMax)
{
	if (x < xMin){ x = xMin; }
	if (x > xMax){ x = xMax; }
	if (y < yMin){ y = yMin; }
	if (y > yMax){ y = yMax; }
}

void Vector2::maximize(Vector2 Min, Vector2 Max)
{
	if (x < Min.x){ x = Min.x; }
	if (x > Max.x){ x = Max.x; }
	if (y < Min.y){ y = Min.y; }
	if (y > Max.y){ y = Max.y; }
}

void Vector2::maximize(Rectangular range)
{
	if (x < range.get_start().x){ x = range.get_start().x; }
	if (x > range.get_end().x){ x = range.get_end().x; }
	if (y < range.get_start().y){ y = range.get_start().y; }
	if (y > range.get_end().y){ y = range.get_end().y; }
}

Vector2 Vector2::symmetry_y()
{
	return Vector2(-x, y);
}

void Sound::loop_play(std::string name)
{
	PlaySoundFile(name.c_str(), DX_PLAYTYPE_LOOP);
}

void Sound::loop_play(int sHandle)
{
	PlaySoundMem(sHandle, DX_PLAYTYPE_LOOP);
}

void Sound::back_play(std::string name)
{
	PlaySoundFile(name.c_str(), DX_PLAYTYPE_BACK);
}

void Sound::back_play(int sHandle)
{
	PlaySoundMem(sHandle, DX_PLAYTYPE_BACK);
}

void Sound::stop_play(int sHandle)
{
	StopSoundMem(sHandle);
}

void Sound::check_stop_play(int sHandle)
{
	if (check_play(sHandle))
	{
		stop_play(sHandle);
	}
}

bool Sound::check_play(int sHandle)
{
	return CheckSoundMem(sHandle);
}

Rectangular::Rectangular() :
start(),
end(),
onMouseTime(0),
clickedTime(0),
existTime(0),
alpha(0),
ratioTime(0)
{

}

Rectangular::Rectangular(Vector2 s, Vector2 e) :
start(s),
end(e),
onMouseTime(0),
clickedTime(0),
existTime(0),
alpha(0),
ratioTime(0)
{

}

bool Rectangular::is_on_mouse()
{
	return is_in(Input::get().mouse);
}

bool Rectangular::is_clicked()
{
	return is_in(Input::get().mouse) && Input::get().mouseState != 0;
}

void Rectangular::get_status()
{
	if (is_on_mouse())	{		onMouseTime++;	}
	else { onMouseTime = 0; }
	if (is_clicked()){ clickedTime++; }
	else { clickedTime = 0; }
	existTime++;
}

bool Rectangular::get_clicked_down()
{
	return clickedTime == 1;
}

bool Rectangular::get_clicked()
{
	return clickedTime > 0;
}

bool Rectangular::get_on_mouse_down()
{
	return onMouseTime == 1;
}

bool Rectangular::get_on_mouse()
{
	return onMouseTime > 0;
}

void Rectangular::set(Vector2 s, Vector2 e)
{
	start = s;
	end = e;
}

void Rectangular::set(double x1, double y1, double x2, double y2)
{
	start.Set(x1, y1);
	end.Set(x2, y2);
}

void Rectangular::set_size(Vector2 s, Vector2 size)
{
	start = s;
	end = s + size;
}

void Rectangular::set_center(Vector2 center, Vector2 size)
{
	start = center - size / 2;
	end = center + size / 2;
}

void Rectangular::set_ratio_time(int rT)
{
	ratioTime = rT;
}

void Rectangular::move(Vector2 dis)
{
	start += dis;
	end += dis;
}

bool Rectangular::is_in(double x, double y){
	return  start.x < x  && x < end.x
		&&  start.y < y  && y < end.y;
}

bool Rectangular::is_in(Vector2 point)
{
	return  start.x < point.x  && point.x < end.x
		&&  start.y < point.y  && point.y < end.y;
}

void Rectangular::draw()
{
	MyDraw::box(start, end, 0xFFFFFF, 1);
}

void Rectangular::draw(int gHandle)
{
	MyDraw::center(get_center(), gHandle);
}

void Rectangular::draw_ratio(int gHandle)
{
	if (existTime <= ratioTime)
	{
		MyDraw::exrot(get_center(), (double)existTime / (double)ratioTime, 0, gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle);
	}
}

void Rectangular::draw_clicked(int gHandle1, int gHandle2)
{
	if (get_clicked())
	{
		MyDraw::center(get_center(), gHandle2);
	}
	else { MyDraw::center(get_center(), gHandle1); }
}

void Rectangular::draw_on_mouse(int gHandle1, int gHandle2)
{
	if (get_on_mouse())
	{
		MyDraw::center(get_center(), gHandle2);
	}
	else { MyDraw::center(get_center(), gHandle1); }
}

void Rectangular::draw_ratio_on_mouse(int gHandle, double ratio1, double ratio2, int time)
{
	if (get_on_mouse())
	{
		if (onMouseTime <= time)
		{
			MyDraw::exrot(get_center(), ((time - onMouseTime)*ratio1 + onMouseTime* ratio2) / time, 0, gHandle);
		}
		else
		{
			MyDraw::center(get_center(), gHandle);
		}
	}
	else
	{
		MyDraw::exrot(get_center(), ratio1, 0, gHandle);
	}
}

void Rectangular::draw_ratio_on_mouse(int gHandle1, int gHandle2, double ratio1, double ratio2, int time)
{
	if (get_on_mouse())
	{
		if (onMouseTime <= time)
		{
			MyDraw::exrot(get_center(), ((time - onMouseTime)*ratio1 + onMouseTime* ratio2) / time, 0, gHandle2);
		}
		else
		{
			MyDraw::center(get_center(), gHandle2);
		}
	}
	else
	{
		MyDraw::center(get_center(),gHandle1);
	}
}

void Rectangular::draw_ratio_on_mouse_alpha(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime)
{
	int aT = (alphaTime/2) * 2;
	if ((existTime % aT) < (aT / 2)){ alpha++; }
	else { alpha--; }

	if (get_on_mouse())
	{
		if (onMouseTime <= ratioTime)
		{
			MyDraw::exrot(get_center(), ((ratioTime - onMouseTime)*ratio1 + onMouseTime* ratio2) / ratioTime, 0, gHandle2, 255 - ((double)alpha/(double)(aT/2))*128.0);
		}
		else
		{
			MyDraw::center(get_center(), gHandle2);
		}
	}
	else
	{
		MyDraw::center(get_center(), gHandle1, 255 - ((double)alpha / (double)(aT / 2))*128.0);
	}
}

void Rectangular::draw_alpha_on_mouse(int gHandle)
{
	if (get_on_mouse())
	{
		MyDraw::center(get_center(), gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle, 127);
	}
}

void Rectangular::draw_alpha_on_mouse(int gHandle, int alphaTime)
{
	if (get_on_mouse())
	{
		if (onMouseTime < alphaTime)
		{
			MyDraw::center(get_center(), gHandle, 127 + 128*((double)onMouseTime/(double)alphaTime));
		}
		else MyDraw::center(get_center(), gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle, 127);
	}
}

void Rectangular::draw(std::string str, int color, int fontHandle)
{
	MyDraw::centertext((start + end) / 2, color, fontHandle, str, 255);
}

void Rectangular::draw(std::string str, int color, int fontHandle, int fontSize)
{
	MyDraw::centertext((start + end - Vector2(0, fontSize)) / 2, color, fontHandle, str, 255);
}

bool Rectangular::is_draw_finished()
{
	return existTime >= ratioTime;
}

Vector2 Rectangular::get_start()
{
	return start;
}

Vector2 Rectangular::get_end()
{
	return end;
}

Vector2 Rectangular::get_center()
{
	return (start + end) / 2;
}

Vector2 Rectangular::get_size()
{
	return start - end;
}

Vector2 Rectangular::rand()
{
	return Vector2(GetRand(end.x - start.x) + start.x, GetRand(end.y - start.y) + start.y);
}

Que::Point::Point(int gHandle) :
graphHandle(gHandle),
t(0),
swich(true)
{

}

void Que::Point::draw(Vector2 p)
{
	if (swich == true)
	{
		MyDraw::center(p, graphHandle);
	}
}

void Que::Point::draw_ratio(Vector2 p, int time)
{
	if (swich == true)
	{
		if (t <= time)
		{
			t++;
			MyDraw::exrot(p, (double)t / (double)time, 0, graphHandle);
		}
		else
		{
			MyDraw::center(p, graphHandle);
		}
	}
	else{ t = 0; }
}

Que::Que()
{
}

Que::Que(Vector2 f, Vector2 d, int gH, int num) :
firstCenter(f),
duration(d)
{
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(Vector2 f, Vector2 d, int gH, int num)
{
	firstCenter = f;
	duration = d;
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(double fx, double fy, double dx, double dy, int gH, int num)
{
	firstCenter.Set(fx, fy);
	duration.Set(dx, dy);
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(int num)
{
	if (num > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = true;
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < num)
			{
				(**iter).swich = true;
			}
			else
			{
				(**iter).swich = false;
			}
		}
	}
}

void Que::set(int num, bool f)
{
	if (num > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = f;
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter - vec.begin() < num; iter++){ (**iter).swich = f; }
	}
}

void Que::set(int s, int e)
{
	if (s > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = false;
		}
	}
	else if (e > vec.size())
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < s)
			{
				(**iter).swich = false;
			}
			else
			{
				(**iter).swich = true;
			}
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < s)
			{
				(**iter).swich = false;
			}
			else if (iter - vec.begin() < e)
			{
				(**iter).swich = true;
			}
			else
			{
				(**iter).swich = false;
			}
		}
	}
}

void Que::draw()
{
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw(int num)
{
	set(num);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw(int s, int e)
{
	set(s, e);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw_ratio(int num, int time)
{
	set(num);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw_ratio(firstCenter + duration*(iter - vec.begin()), time);
	}
}

Circle::Circle(Vector2 c, double r) :
center(c),
range(r)
{

}

Circle::Circle(double x, double y, double r) :
center(x, y),
range(r)
{

}

void Circle::set(Vector2 c, double r)
{
	center = c;
	range = r;
}

void Circle::set(double x, double y, double r)
{
	center.Set(x, y);
	range = r;
}

Vector2 Circle::get_center()
{
	return center;
}

double Circle::get_range()
{
	return range;
}

Circle Circle::symmetry_y(Vector2 outerCenter)
{
	return Circle(outerCenter.x - center.x, outerCenter.y + center.y, range);
}

Circle Circle::slide(Vector2 outerCenter)
{
	return Circle(center + outerCenter, range);
}

void Circle::draw()
{
	MyDraw::circle(center, range, 0xFFFFFF);
}

void Circle::draw(double x, double y)
{
	MyDraw::circle(center, x + x, center.y + y, range, 0xFFFFFF);
}

void Circle::draw(Vector2 camera)
{
	MyDraw::circle(center + camera, range, 0xFFFFFF);
}

bool Circle::is_in(double x, double y)
{
	return (x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) < range*range;
}

bool Circle::is_in(Vector2 point)
{
	return (point - center).Magnitude() < range;
}
bool Circle::is_in(Vector2 point, Vector2 camera)
{
	return (point - (center + camera)).Magnitude() < range;
}

//�ʏ�̕`��E���W�͍�����w��
void MyDraw::normal(int x, int y, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(x, y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�摜�̒����̍��W���w�肵�ĕ`��
void MyDraw::center(int x, int y, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x, y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�g��E��]�`��
void MyDraw::exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�g��E��]�E�����w��`��
void MyDraw::exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//���R�ό`�`��
void MyDraw::modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		x1, y1, x2, y2,
		x3, y3, x4, y4,
		GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//����E�E�����w�肵�ĕ`��
void MyDraw::modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(x1, y1, x2, y2, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
void MyDraw::modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = x + r * cos(angle + i * dangle - dr);
		gy[i] = y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0], gy[0],
		gx[1], gy[1],
		gx[2], gy[2],
		gx[3], gy[3], GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
void MyDraw::trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
void MyDraw::circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x, y, 100, GrHandle, 100 - percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
void MyDraw::circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x, y, percent, GrHandle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�}�`�`��֐�

//����`��
void MyDraw::line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx, sy, ex, ey, color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�Ǝ�
//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
void MyDraw::lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx, sy, sx + r * cos(angle), sy + r * sin(angle), color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//����`��
void MyDraw::box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(x1, y1, x2, y2, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�Ǝ�
//���S���w�肵�Ĕ���`��
void MyDraw::centerbox(double centerx, double centery, double width, double height, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		centerx - width / 2, centery - height / 2,
		centerx + width / 2, centery + height / 2,
		color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�~��`��
void MyDraw::circle(int x, int y, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(x, y, r, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�O�p�`��`��
void MyDraw::triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(x1, y1, x2, y2, x3, y3, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


//�����`��֐�

//������`��
void MyDraw::text(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(x, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�w�肵�����W�𒆐S�ɕ�����`��
void MyDraw::centertext(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(x - wd / 2, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�����̉E��̍��W���w�肵�ĕ�����`��
void MyDraw::righttext(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(x - wd, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
void MyDraw::centertext_space(int x, int y, int color, int font_handle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(x + i * space + basex, y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(x + i * space + basex, y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}



//Vector2�g�p

//�ʏ�̕`��E���W�͍�����w��
void MyDraw::normal(const Vector2& pos, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(pos.x, pos.y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�摜�̒����̍��W���w�肵�ĕ`��
void MyDraw::center(const Vector2& pos, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x, pos.y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�g��E��]�`��
void MyDraw::exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x, pos.y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�g��E��]�E�����w��`��
void MyDraw::exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(pos.x, pos.y, center_pos.x, center_pos.y, Exrate_vec.x, Exrate_vec.y, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//���R�ό`�`��
void MyDraw::modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		pos1.x, pos1.y, pos2.x, pos2.y,
		pos3.x, pos3.y, pos4.x, pos4.y,
		GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//����E�E�����w�肵�ĕ`��
void MyDraw::modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
void MyDraw::modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = pos.x + r * cos(angle + i * dangle - dr);
		gy[i] = pos.y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0], gy[0],
		gx[1], gy[1],
		gx[2], gy[2],
		gx[3], gy[3], GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
void MyDraw::trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(pos.x, pos.y, graph_ul_pos.x, graph_ul_pos.y, size.x, size.y, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
void MyDraw::circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x, pos.y, 100, GrHandle, 100 - percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
void MyDraw::circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x, pos.y, percent, GrHandle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�}�`�`��֐�

//����`��
void MyDraw::line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x, start_pos.y, end_pos.x, end_pos.y, color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�Ǝ�
//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
void MyDraw::lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x, start_pos.y, start_pos.x + r * cos(angle), start_pos.y + r * sin(angle), color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//����`��
void MyDraw::box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(pos1.x, pos1.y, pos2.x, pos2.y, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�Ǝ�
//���S���w�肵�Ĕ���`��
void MyDraw::centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		center_pos.x - size.x / 2, center_pos.y - size.y / 2,
		center_pos.x + size.x / 2, center_pos.y + size.y / 2,
		color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�~��`��
void MyDraw::circle(const Vector2& pos, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(pos.x, pos.y, r, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�O�p�`��`��
void MyDraw::triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


//�����`��֐�

//������`��
void MyDraw::text(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(pos.x, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�w�肵�����W�𒆐S�ɕ�����`��
void MyDraw::centertext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd / 2, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MyDraw::centertext(const Vector2& pos, int color, int font_handle, int fontSize, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd / 2, pos.y - fontSize / 2, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�����̉E��̍��W���w�肵�ĕ�����`��
void MyDraw::righttext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
void MyDraw::centertext_space(const Vector2& pos, int color, int font_handle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(pos.x + i * space + basex, pos.y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(pos.x + i * space + basex, pos.y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}



//�����蔻��

//2��
template<typename T> T Func::Sqr(T x)
{
	return x*x;
}
//���όv�Z
template<typename T> T Func::Dot2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*Bx + Ay*By;
}
//�O�όv�Z
template<typename T> T Func::Cross2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*By - Bx*Ay;
}


//�ǉ�
//�_�Ɖ~
bool Func::PointCircle(const Vector2& point_pos, const Vector2& circle_center, double radius)
{
	return Sqr(circle_center.x - point_pos.x) + Sqr(circle_center.y - point_pos.y) < Sqr(radius);
}

//�~�`���m
bool Func::Circles(double x1, double y1, double r1, double x2, double y2, double r2)
{
	return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
}
bool Func::Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
{
	return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
}
//��`���m
bool Func::Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
{
	return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
}
bool Func::Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
{
	return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
}
//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_)
bool Func::BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad){
	double x, y, ang, width;
	x = px - line_sx;
	y = py - line_sy;
	ang = atan2(line_ey - line_sy, line_ex - line_sx);
	width = dist(line_sx, line_sy, line_ex, line_ey);

	rotateonzero(x, y, -ang);

	if (x > 0 && x < width && y > -broad && y < broad){
		return true;
	}
	else{
		return false;
	}
}

//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_�܂ł̋����A�p�x)
bool Func::BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad){
	double x, y;
	x = px - line_sx;
	y = py - line_sy;

	rotateonzero(x, y, -e_ang);

	if (x > 0 && x < e_r && y > -broad && y < broad){
		return true;
	}
	else{
		return false;
	}
}

//�_�Ƌ�`
bool Func::BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
	return abs(px - box_cx) < box_width / 2
		&& abs(py - box_cy) < box_height / 2;
}

//�_�Ƌ�`
bool Func::BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size){
	return abs(p_pos.x - box_pos.x) < box_size.x / 2
		&& abs(p_pos.y - box_pos.y) < box_size.y / 2;
}
//���ʂ̓_�Ƌ�`
bool Func::DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
{
	return  b1x < px  && px < b2x
		&&  b1y < py  && py < b2y;
}

//�~(���acr,(cx,cy))�̋ߎ������`�Ɓ@�����`(����(rx1,ry1), �E��(rx2, ry2))�̓����蔻��
bool Func::CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
	double rectx = (rx1 + rx2) / 2.0;
	double recty = (ry1 + ry2) / 2.0;
	return	cx > rx1 - cr && cy > ry1 - cr &&
		cx < rx2 + cr && cy < ry2 + cr;
}
//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
double Func::Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y)
{
	double c0;
	c0 = Cross2D(b_x - a_x, b_y - a_y, d_x - c_x, d_y - c_y);
	if (c0 == 0.0f)
		return 0.0f;
	double r0, r1;
	r0 = Cross2D(c_x - a_x, c_y - a_y, b_x - a_x, b_y - a_y) / c0;
	r1 = Cross2D(c_x - a_x, c_y - a_y, d_x - c_x, d_y - c_y) / c0;
	if (r0 >= 0.0f && r0 <= 1.0f && r1 >= 0.0f && r1 <= 1.0f)
		return r1;
	else
		return 0.0f;
}
//Lines�œ������Ă��ꍇ�͈ʒu���v�Z�ł���
Vector2 Func::LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
{
	Vector2 AB(b_x - a_x, b_y - a_y);
	AB *= lines_result;
	AB.Translate(a_x, a_y);
	return AB;
}
//�~�Ɛ���
bool Func::CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey)
{
	if (distSqr(sx, sy, cx, cy) < r*r || distSqr(ex, ey, cx, cy) < r*r){
		return true;
	}
	else {
		double k = ey - sy;
		double l = ex - sx;
		if (!((k*cx - l*cy - k*sx + l*sy)*(k*cx - l*cy - k*sx + l*sy) < r * r * (k*k + l*l))){
			return false;
		}
		if (((sx - cx)*(ex - cx) + (sy - cy)*(ey - cy)) < 0){
			return true;
		}
	}
	return false;
}


//�x�N�g��

//���_�𒆐S��ang����]
void Func::rotateonzero(double &x, double &y, double ang){
	double sx = x - 0;
	double sy = y - 0;
	x = sx * cos(ang) - sy * sin(ang) + 0;
	y = sx * sin(ang) + sy * cos(ang) + 0;
}

//����_(centerx,centery)�𒆐S��ang����]
void Func::rotateonpoint(double &x, double &y, double centerx, double centery, double ang){
	double sx = x - centerx;
	double sy = y - centery;
	x = sx * cos(ang) - sy * sin(ang) + centerx;
	y = sx * sin(ang) + sy * cos(ang) + centery;
}

//(���_����(sx,sy)�ւ̒P�ʃx�N�g�������߂�
void Func::normalizedVector(double &vx, double &vy, double sx, double sy){
	double rd = atan2(sy, sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(sx,sy)����(ex,ey)�ւ̒P�ʃx�N�g�������߂�
void Func::normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
	double rd = atan2(ey - sy, ex - sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɑ��
void Func::calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx = dist * cos(rd);
	resulty = dist * sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
void Func::addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx += dist * cos(rd);
	resulty += dist * sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
void Func::addVector(double r, double angle, double &resultx, double &resulty){
	resultx += r * cos(angle);
	resulty += r * sin(angle);
}

//�ɍ��W�\������xy�\���ɒ���
void Func::polartoxy(double &x, double &y, double r, double ang){
	x = r * cos(ang);
	y = r * sin(ang);
}

//�p�x���v�Z
double Func::calAngle(double x, double y){
	return atan2(y, x);
}

//�p�x���v�Z
double Func::calAngle(double sx, double sy, double ex, double ey){
	return atan2(ey - sy, ex - sx);
}

/*
startx : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
enddif : �J�n�ƏI���̒l�̍���
time_now : ���݂̎���
time_end : Tween�̍��v����
*/

//�^�_�@�����������O���t
double Func::linef(double startx, double dif, double time_now, double time_end){
	return startx + (dif - startx) * (abs(time_end / 2 - time_now) / (time_end / 2));
}

//�^�_�@����������2���Ȑ�
double Func::quadraticf(double startx, double dif, double time_now, double time_end){
	double x = time_now / time_end;
	return startx + (dif - startx) * -4 * (x * x - x);
}


//3�_��ʂ钼���O���t
double Func::graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
	if (t_now < t1){
		return (x1 - x0) * t_now / t1 + x0;
	}
	else{
		return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
	}
}

//4�_��ʂ钼���O���t
double Func::graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end){
	if (t_now < t1){
		return (x1 - x0) * t_now / t1 + x0;
	}
	else if (t_now < t2){
		return (x2 - x1) * (t_now - t1) / (t2 - t1) + x1;
	}
	else{
		return (x3 - x2) * (t_now - t2) / (t_end - t2) + x2;
	}
}


//�C�[�W���O�Ȑ�

/*
t : ���݂̎���
b : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
c : �J�n�ƏI���̒l�̍���
d : Tween�̍��v����
*/

//�C�[�W���O�Ȑ� Cubic
double Func::ease_cubic_in(double t, double b, double c, double d){
	t /= d;
	return c*t*t*t + b;
}

double Func::ease_cubic_out(double t, double b, double c, double d){
	t /= d;
	t = t - 1;
	return c*(t*t*t + 1) + b;
}

double Func::ease_cubic_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1){
		return c / 2.0*t*t*t + b;
	}
	else{
		t = t - 2;
		return c / 2.0 * (t*t*t + 2) + b;
	}
}


//�C�[�W���O�Ȑ� Sinusoidal
double Func::ease_sin_in(double t, double b, double c, double d){
	return -c * cos(t / d * (PI / 2.0)) + c + b;
}

double Func::ease_sin_out(double t, double b, double c, double d){
	return c * sin(t / d * (PI / 2.0)) + b;
}

double Func::ease_sin_inout(double t, double b, double c, double d){
	return -c / 2.0 * (cos(PI*t / d) - 1) + b;
}

//�C�[�W���O�Ȑ� Exponential
double Func::ease_exp_in(double t, double b, double c, double d){
	return c * pow(2.0, (10 * (t / d - 1))) + b;
}

double Func::ease_exp_out(double t, double b, double c, double d){
	return c * (-(pow(2.0, (-10.0 * t / d))) + 1) + b;
}

double Func::ease_exp_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1)
		return c / 2.0 * pow(2.0, (10.0 * (t - 1))) + b;
	t = t - 1;
	return c / 2.0 * (-(pow(2.0, (-10 * t))) + 2) + b;
}

//�C�[�W���O�Ȑ� Circular
double Func::ease_sqrt_in(double t, double b, double c, double d){
	t /= d;
	return -c * (sqrt(1 - t*t) - 1) + b;
}

double Func::ease_sqrt_out(double t, double b, double c, double d){
	t /= d;
	t = t - 1;
	return c * sqrt(1 - t*t) + b;
}

double Func::ease_sqrt_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1)
		return -c / 2.0 * (sqrt(1 - t*t) + 1);
	t = t - 2;
	return c / 2.0 * (sqrt(1 - t*t) + 1) + b;
}



//�x�W�F�Ȑ�  p1->p2->p3  0<t<1
double Func::bz_curve(double p1, double p2, double p3, double t){
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//�x�W�F�Ȑ�  p1->p2->p3  nowtime, endtime
double Func::bz_curve(double p1, double p2, double p3, double nowt, double endt){
	double t = nowt / endt;
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//�A�j���[�V�����p�E�_�^�_�^�_�^�ƂȂ�O���t
int Func::Repeat(int frame, int loop_num)
{
	--loop_num;
	frame = frame % (loop_num * 2);
	if (frame > loop_num)
		return loop_num * 2 - frame;
	else
		return frame;
}

//2���x�W�G�Ȑ����v�Z����֐�
Vector2 Func::GetBezier2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 Result;
	// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//2���x�W�G�Ȑ��Ő���_���ʂ�悤�Ɉ��������ꍇ�̐���_��Ԃ��֐�
Vector2 Func::GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
{
	Vector2 C;
	C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
	C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
	return C;
}

//Control��ʂ�2���x�W�G�Ȑ����v�Z����֐�
Vector2 Func::GetBezierCtrl2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 C;//Control��ʂ�2���x�W�G�Ȑ��̐���_
	Vector2 Result;
	C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
	C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//3���x�W�G�Ȑ����v�Z����֐�
Vector2 Func::GetBezier3(const Vector2& Start, const Vector2& ControlPoint1
	, const Vector2& ControlPoint2, const Vector2& End, float t)
{
	Vector2 Result;
	Result.x = (t*t*t)*End.x + 3 * t*t*(1 - t)*ControlPoint2.x
		+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.x + (1 - t)*(1 - t)*(1 - t)*Start.x;
	Result.y = (t*t*t)*End.y + 3 * t*t*(1 - t)*ControlPoint2.y
		+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.y + (1 - t)*(1 - t)*(1 - t)*Start.y;
	return Result;
}
//�֗��֐�

//HSV��RGB�Ɋ��Z ���ڊ֐��̈����ɓn���p
DWORD Func::GetColorHSV(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	return GetColor(rgb[0], rgb[1], rgb[2]);
}

//HSV��RGB�Ɋ��Z int�ɕۑ�����p
int Func::HSVtoRGB(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	return ((rgb[0]) << 16) + ((rgb[1]) << 8) + rgb[2];
}

//HSV��setdrawbright
void Func::SetDrawBrightHSV(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	SetDrawBright(rgb[0], rgb[1], rgb[2]);
}

//0xXXXXXX��SetDrawBright����֐�
void Func::SetDrawBrightInt(int col){
	SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
}

//�����̊p�x,����̊p�x 2�p�̊֌W��Ԃ��@���v��葤�ɓ������ق����߂����1 �����łȂ����-1
int Func::abs_angle(double angle1, double angle2){
	if (sin(angle2 - angle1) > 0){
		return 1;
	}
	else{
		return -1;
	}
}

//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  tarx�Ƃ̍���erange�ȉ���tarx = x�ɂ���
void Func::moverate(double &x, double tarx, double rate, double erange)
{
	x = x * (1 - rate) + tarx * rate;
	if (abs(x - tarx) < erange){
		x = tarx;
	}
}
//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
void Func::moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist)
{
	x = x * (1 - rate) + tarx * rate;
	y = y * (1 - rate) + tary * rate;
	if (dist(x, y, tarx, tary) < erangedist){
		x = tarx;
		y = tary;
	}
}
//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
void Func::moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist)
{
	v2.x = v2.x * (1 - rate) + tarv2.x * rate;
	v2.y = v2.y * (1 - rate) + tarv2.y * rate;
	if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
		v2 = tarv2;
	}
}


//���_�Ƃ̋�����Ԃ�
double Func::dist(double x, double y){
	return sqrt(x*x + y*y);
}

//2�_�̋�����Ԃ�
double Func::dist(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//2�_�̋�����2���Ԃ�
double Func::distSqr(double x1, double y1, double x2, double y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}


//rate��cool�̃Z�b�g��cool���X�V�Ebool��Ԃ�
bool Func::coolcount(int &cool){
	if (cool > 0){
		cool--;
		return false;
	}
	else{
		cool = 0;
		return true;
	}
}



//��E�U���E����(�b)�E�o�߃t���[�����w�肵��sin��Ԃ�
double Func::sinsec(double base, double a, double t, double frame){
	return base + a * sin(2 * PI * frame / 60.0 / t);
}

//	//�X�N���[���̒��S��Ԃ�
//	inline Vector2 GetScreenCenter(){
//		return Vector2(ScreenWidth / 2, ScreenHeight / 2);
//	}
//
//	//�����_����2�����̑啶���A���t�@�x�b�g��Ԃ�
//	std::string randStr(){
//		std::string str;
//		for (int i = 0; i < 2; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//	//�����_����2�����̑啶���A���t�@�x�b�g��Ԃ�
//	std::string randStr(int loop){
//		std::string str;
//		for (int i = 0; i < loop; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//
//	//�X�N���[������o�Ă��邩��Ԃ��֐�
//	bool isScreenOut(const Vector2 &pos){
//		return pos.x < 0 || pos.x > ScreenWidth
//			|| pos.y < 0 || pos.y > ScreenHeight;
//	}
//
//	//�X�N���[������marge�O�ɏo�Ă��邩��Ԃ��֐�
//	bool isScreenOutMarge(const Vector2 &pos, int marge){
//		return pos.x < -marge || pos.x > ScreenWidth + marge
//			|| pos.y < -marge || pos.y > ScreenHeight + marge;
//	}