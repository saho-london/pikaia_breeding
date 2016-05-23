#include <Dxlib.h>

#include "graph.h"
#include "MyFunc.h"

Graph::Graph() :
backNumber(0),
statusNumber(0)
{

}

Graph& Graph::get(){
	static Graph inst;
	return inst;
}

void Graph::load_graph()
{
	register_back();
	register_button();
	register_status();

	add_graph("pikaia.png");
	add_graph("pikaia_smile.png");
	add_graph("pikaia_d.png");
	add_graph("pikaia_e.png");

	add_graph("chick.png");
	add_graph("chick_smile.png");
	add_graph("chick_d.png");
	add_graph("chick_f.png");
	add_graph("chick_f_smile.png");
	add_graph("chick_fd.png");
	add_graph("chick_f2.png");
	add_graph("chick_f2_smile.png");
	add_graph("chick_f2d.png");
	add_graph("chick_e.png");

	add_graph("bird.png");
	add_graph("bird_d.png");
	add_graph("bird_f.png");
	add_graph("bird_fd.png");
	add_graph("bird_smile.png");
	add_graph("bird_f_smile.png");
	add_graph("bird_f2.png");
	add_graph("bird_f2d.png");
	add_graph("bird_f2_smile.png");
	add_graph("bird_e.png");

	add_graph("kitten.png");
	add_graph("kitten_d.png");
	add_graph("kitten_f.png");
	add_graph("kitten_fd.png");
	add_graph("kitten_smile.png");
	add_graph("kitten_f_smile.png");
	add_graph("kitten_f2.png");
	add_graph("kitten_f2d.png");
	add_graph("kitten_f2_smile.png");
	add_graph("kitten_e.png");

	add_graph("cat.png");
	add_graph("cat_d.png");
	add_graph("cat_f.png");
	add_graph("cat_fd.png");
	add_graph("cat_smile.png");
	add_graph("cat_f_smile.png");
	add_graph("cat_f2.png");
	add_graph("cat_f2d.png");
	add_graph("cat_f2_smile.png");
	add_graph("cat_e.png");

	add_graph("title.png");
	add_graph("kosi4.png");
	add_graph("kosi5.png");
	add_graph("black.png");
	add_graph("onaka0.png");
	add_graph("onaka1.png");
	add_graph("effect2.png");
	add_graph("effect4.png");
	add_graph("effect6.png");
	add_graph("day0.png");
	add_graph("ba-00.png");
	add_graph("ba-01.png");
	add_graph("keikoku.png");
	add_graph("yes.png");
	add_graph("no.png");
	add_graph("yes1.png");
	add_graph("no1.png");
	add_graph("asobu0.png");
	add_graph("asobu.png");
	add_graph("back_title.png");
	add_graph("option.png");
	add_graph("back.png");
	add_graph("flame.png");
	add_graph("sound.png");
	add_graph("kettei.png");
	add_graph("kettei1.png");
	add_graph("kyannseru.png");
	add_graph("kyannseru1.png");
	add_graph("yazirusi.h.png");
	add_graph("yazirusi.ms.png");
	add_graph("yazirusi.hs.png");
	add_graph("yazirusi.m.png");
	add_graph("title-start.png");
	add_graph("title-tuduki.png");
	add_graph("title-option.png");
	add_graph("title-start.s.png");
	add_graph("title-tuduki.s.png");
	add_graph("title-option.s.png");
	add_graph("skip.png");
	add_graph("skip.s.png");
	add_back();
	add_button();
	add_status();
}

void Graph::load_music()
{
	add_music("pikaiaBGM.wav");
	add_music("pikaiaEvo.wav");
	add_music("pikaiaillness.wav");
	add_music("pikaiaObesity.wav");
	add_music("pikaiaProEpi.wav");
	add_music("pikaiaProEpi(Ã).wav");
	add_music("feed.wav");
	add_music("input.wav");
	add_music("input2.wav");
	add_music("kaifuku.wav");
	add_music("play.wav");
	add_music("dennsionn.wav");
}

void Graph::add_graph(std::string name)
{
	std::string str1 = "Image\\";
	graphMap.emplace(name, LoadGraph((str1 + name).c_str()));
}

void Graph::add_music(std::string name)
{
	std::string str1 = "Sound\\";
	musicMap.emplace(name, LoadSoundMem((str1 + name).c_str()));
}

void Graph::add_back()
{
	for (auto element : backVec)
	{
		add_graph(element);
	}
}

void Graph::register_back()
{
	backVec.emplace_back("haikei.dotto.green.png");
	backVec.emplace_back("haikei.dotto.ore.png");
	backVec.emplace_back("haikei.dotto.pnk.png");
	backVec.emplace_back("haikei.maru1.png");
	backVec.emplace_back("haikei.maru2.png");
	backVec.emplace_back("haikei.sima1.png");
	backVec.emplace_back("haikei.sima2.png");
	backVec.emplace_back("haikei2.png");
	backVec.emplace_back("haikei3.png");
	backVec.emplace_back("haikei4.png");
}

void Graph::add_button()
{
	for (auto element : buttonVec)
	{
		add_graph(element);
	}
}

void Graph::register_button()
{
	buttonVec.emplace_back("botann-07.png");
	buttonVec.emplace_back("botann-08.png");
	buttonVec.emplace_back("botann-09.png");
	buttonVec.emplace_back("botann-10.png");
	buttonVec.emplace_back("botann-11.png");
	buttonVec.emplace_back("botann-12.png");
}

void Graph::add_status()
{
	for (auto element : statusVec)
	{
		add_graph(element);
	}
}

void Graph::register_status()
{
	statusVec.emplace_back("st-19.png");
	statusVec.emplace_back("st-20.png");
	statusVec.emplace_back("st-22.png");
	statusVec.emplace_back("st-26.png");
	statusVec.emplace_back("st-27.png");
}

void Graph::set_volume(int vol)
{
	for (auto element : musicMap)
	{
		ChangeVolumeSoundMem(vol, element.second);
	}
}

void Graph::stop_bgm()
{
	Sound::check_stop_play(Graph::get().musicMap.at("pikaiaProEpi(Ã).wav"));
	Sound::check_stop_play(Graph::get().musicMap.at("pikaiaProEpi.wav"));
	Sound::check_stop_play(Graph::get().musicMap.at("pikaiaBGM.wav"));
}

void Graph::increase_back_number(){ backNumber++; }
void Graph::increase_status_number(){ statusNumber++; }
void Graph::decrease_back_number(){ backNumber--; }
void Graph::decrease_status_number(){ statusNumber--; }
int Graph::get_back_number(){ return backNumber; }
int Graph::get_status_number(){ return statusNumber; }

void Graph::set_back_number(int n)
{
	backNumber = n;
	if (backNumber > backVec.size() - 1){ backNumber = backVec.size() - 1; }
}

void Graph::set_status_number(int n)
{
	statusNumber = n;
	if (statusNumber > statusVec.size() - 1){ statusNumber = statusVec.size() - 1; }
}