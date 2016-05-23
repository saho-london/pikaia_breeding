#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "graph.h"
#include "file.h"
#include "time.h"
#include "myglobal.h"
#include "Draw.h"
#include "player.h"


File::File(){//コンストラクタをprivateに置き、クラス外で生成するのを禁止
	FILE_NAME = "data.dat";
	FILE_NAME_OPTION = "setting.dat";
}

void File::load_set_data()
{
	std::ifstream fin(FILE_NAME_OPTION, std::ios::in | std::ios::binary);
	
	int b;
	int s;

	fin.read((char *)&b, sizeof(int));
	fin.read((char *)&s, sizeof(int));

	Graph::get().set_back_number(b);
	Graph::get().set_status_number(s);
}

void File::save_set_data()
{
	std::ofstream fout;
	fout.open(FILE_NAME_OPTION, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!fout) {
		exit(EXIT_FAILURE);
	}
	fout.clear();

	int b = Graph::get().get_back_number();
	int s = Graph::get().get_status_number();

	fout.write((char *)&b, sizeof(int));
	fout.write((char *)&s, sizeof(int));
}

void File::save_data(PlayerData data){
	TimeManager& tManager = TimeManager::get();
	std::ofstream fout;
	fout.open(FILE_NAME, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!fout) {
		exit(EXIT_FAILURE);
	}
	fout.clear();

	auto d = tManager.sumPlayTime + std::chrono::system_clock::now() - tManager.startTime;
	MyTime runTime(d);
	int h = runTime.get_hour();
	int m = runTime.get_minute();
	int s = runTime.get_second();
	int f = runTime.get_frame();

	fout.write((char *) &h, sizeof(int));
	fout.write((char *) &m, sizeof(int));
	fout.write((char *) &s, sizeof(int));
	fout.write((char *) &f, sizeof(int));
	PlayerData p = data;

	fout.write((char *)&p.individualValueFeed, sizeof(double));
	fout.write((char *)&p.individualValuePlay, sizeof(double));
	fout.write((char *)&p.satiety, sizeof(int));
	fout.write((char *)&p.exercise, sizeof(int));
	fout.write((char *)&p.grouth, sizeof(double));
	fout.write((char *)&p.trust, sizeof(double));
	fout.write((char *)&p.state, sizeof(int));
	fout.write((char *)&p.diseaseCount, sizeof(int));
	fout.write((char *)&p.diseaseFlag, sizeof(bool));
	fout.write((char *)&p.fatCount, sizeof(int));
	fout.write((char *)&p.fatFlag, sizeof(bool));
	fout.write((char *)&p.generation, sizeof(int));

	fout.close();
}

PlayerData File::read_data(){
	TimeManager& tManager = TimeManager::get();

	std::ifstream fin(FILE_NAME, std::ios::in | std::ios::binary);


	fin.clear();
	fin.seekg(0, std::ios::beg);
	MyTime t;
	int h = 0;
	int m = 0;
	int s = 0;
	int f = 0;

	double iF;
	double iP;
	int sa = 0;
	int e = 0;
	double g = 0;
	double tr = 0;
	int st = 0;
	int dc = 0;
	int fc = 0;
	bool df = false;
	bool ff = false;
	int ge;

	if (fin.fail())
	{
		exit(EXIT_FAILURE);
	}

	fin.read((char *)&h, sizeof(int));
	fin.read((char *)&m, sizeof(int));
	fin.read((char *)&s, sizeof(int));
	fin.read((char *)&f, sizeof(int));

	fin.read((char *)&iF, sizeof(double));
	fin.read((char *)&iP, sizeof(double));
	fin.read((char *)&sa, sizeof(int));
	fin.read((char *)&e, sizeof(int));
	fin.read((char *)&g, sizeof(double));
	fin.read((char *)&tr, sizeof(double));
	fin.read((char *)&st, sizeof(int));
	fin.read((char *)&dc, sizeof(int));
	fin.read((char *)&df, sizeof(bool));
	fin.read((char *)&fc, sizeof(int));
	fin.read((char *)&ff, sizeof(bool));
	fin.read((char *)&ge, sizeof(int));

	t.set_time(h, m, s, f);
	tManager.sumPlayTime = t.MyTime_to_duration();
	tManager.startTime = std::chrono::system_clock::now();
	return PlayerData(iF, iP, sa, e, g, tr, (State) st, dc, df, fc, ff, ge, homePoint, homePoint);
}

char* File::get_file_name()
{
	return FILE_NAME;
}

char* File::get_file_name_option()
{
	return FILE_NAME_OPTION;
}




Log::Log() :
logSpeed(0.5),
startPoint(SCREEN.y)
{

}

Log::String::String(double y_, std::string str_):
original(SCREEN.x/2, y_),
str(str_)
{

}

void Log::String::draw(Vector2 camera)
{
	int wd = GetDrawFormatStringWidthToHandle(SEGOE_12, "%s", str.c_str());
	DrawFormatStringToHandle(original.x + camera.x - wd / 2, original.y + camera.y, 0x444444, SEGOE_12, "%s", str.c_str());
}

void Log::update()
{
	camera.y -= logSpeed;
}

void Log::read()
{

	std::ifstream ifs(FILE_NAME);
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	int i = 0;
	std::string str;
	if (ifs.fail())
	{
		exit( EXIT_FAILURE);
	}
	while (getline(ifs, str))
	{
		vec.emplace_back(String(i*30+startPoint, str));
		i++;
	}
}



void Log::draw()
{
	for (auto element : vec)
	{
		element.draw(camera);
	}
}

double Log::get_start()
{
	if (vec.size() == 0){
		return camera.y;
	}
	else{
		auto iter = vec.begin();
		return iter->original.y + camera.y;
	}

}

double Log::get_end()
{
	if (vec.size() == 0){
		return camera.y;
	}
	else{
		auto iter = vec.end() - 1;
		return iter->original.y + camera.y;
	}
}

void Log::set(std::string str)
{
	FILE_NAME = str;
}

void Log::reset_camera()
{
	camera = Vector2(0, 0);
}

int Log::vec_size()
{
	return vec.size();
}