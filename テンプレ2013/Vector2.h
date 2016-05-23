#pragma once

#include <string>
#include <vector>
#include <memory>

//2������̓_��\���N���X

class Rectangular;

class Vector2
{
public:
	double x;
	double y;

	//�R���X�g���N�^��`
	Vector2();
	Vector2(double x_, double y_);

	//�I�y���[�^�[�I�[�o�[���[�h
	Vector2& operator +=(const Vector2& t);
	Vector2& operator -=(const Vector2& t);
	Vector2 operator +(const Vector2& t);
	Vector2 operator -(const Vector2& t);
	Vector2 operator *(double t);
	Vector2 operator /(double t);
	Vector2& operator *=(double t);
	Vector2& operator /=(double t);

	//����
	double operator *(const Vector2& t);

	//�O��
	double cross(const Vector2& t);

	//����֐�
	void Set(double x_, double y_);

	//���_�𒆐S�ɉ�]
	void Rotate(double rad);

	//center�𒆐S�ɉ�]
	void RotateOnPoint(double rad, const Vector2 &center);

	//���_�𒆐S�Ƀx�N�g������]�������̂�Ԃ�
	Vector2 GetRotate(double rad);

	//center�𒆐S�ɉ�]�����x�N�g����Ԃ�
	Vector2 GetRotateOnPoint(double rad, const Vector2 &center);

	//dx,dy�������ړ�
	void Translate(double dx, double dy);

	//�x�N�g���̑傫����Ԃ�
	double Magnitude();

	//�x�N�g���𐳋K������
	void Normalize();

	//���K�����ꂽ�x�N�g����Ԃ�
	Vector2 GetNormalized();

	//�x�N�g���̊p�x��Ԃ�
	double GetAngle();

	//�ɍ��W�n���ŕ\���ꂽ�x�N�g����Ԃ� static
	static Vector2 GetPolar(double r, double angle);

	//�w�肵���͈͓��Ƀx�N�g�����C��
	void maximize(double xMin, double xMax, double yMin, double yMax);
	void maximize(Vector2 Min, Vector2 Max);
	void maximize(Rectangular range);

	//y���Ώ�
	Vector2 symmetry_y();

};

class Rectangular{
	Vector2 start;
	Vector2 end;
	int onMouseTime;
	int clickedTime;
	int existTime;
	int alpha;
	int ratioTime;

	bool is_on_mouse();
	bool is_clicked();

public:

	Rectangular();
	Rectangular(Vector2 s, Vector2 e);

	void get_status();

	bool get_clicked_down();
	bool get_clicked();
	bool get_on_mouse_down();
	bool get_on_mouse();

	void set(Vector2 s, Vector2 e);
	void set(double x1, double y1, double x2, double y2);
	void set_size(Vector2 s, Vector2 size);
	void set_center(Vector2 center, Vector2 size);
	void set_ratio_time(int rT);
	void move(Vector2 dis);

	bool is_in(double x, double y);
	bool is_in(Vector2 point);
	
	void draw();
	void draw(int gHandle);
	void draw_ratio(int gHandle);
	void draw_clicked(int gHandle1, int gHandle2);
	void draw_on_mouse(int gHandle1, int gHandle2);
	void draw_ratio_on_mouse(int gHandle, double ratio1, double ratio2, int time);
	void draw_ratio_on_mouse(int gHandle1, int gHandle2, double ratio1, double ratio2, int time);
	void draw_ratio_on_mouse_alpha(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime);
	void draw_alpha_on_mouse(int gHandle);
	void draw_alpha_on_mouse(int gHandle, int alphaTime);
	void draw(std::string str, int color, int fontHandle);
	void draw(std::string str, int color, int fontHandle, int fontSize);
	void draw_debug(std::string str);

	bool is_draw_finished();

	Vector2 get_start();
	Vector2 get_end();
	Vector2 get_center();
	Vector2 get_size();

	Vector2 rand();
};

class Que
{
	class Point
	{
	public:
		Point(int gHandle);

		int graphHandle;
		int t;
		bool swich;

		void draw(Vector2 p);
		void draw_ratio(Vector2 p, int time);
	};

	Vector2 firstCenter;
	Vector2 duration;
	std::vector<std::shared_ptr<Point>> vec;

public:
	Que();
	Que(Vector2 f, Vector2 d, int gH, int num);

	void set(Vector2 f, Vector2 d, int gH, int num);
	void set(double fx, double fy, double dx, double dy, int gH, int num);
	void set(int num);
	void set(int num, bool f);
	void set(int s, int e);
	void draw();
	void draw(int num);
	void draw(int s, int e);
	void draw_ratio(int num, int time);
};

class Circle
{
	Vector2 center;
	double range;

public:
	Circle(Vector2 c, double r);
	Circle(double x, double y, double r);

	void set(Vector2 c, double r);
	void set(double x, double y, double r);
	Vector2 get_center();
	double get_range();
	Circle symmetry_y(Vector2 outerCenter);
	Circle slide(Vector2 outerCenter);

	void draw();
	void draw(double x, double y);
	void draw(Vector2 outerCenter);
	bool is_in(double x, double y);
	bool is_in(Vector2 point);
	bool is_in(Vector2 point, Vector2 camera);
};