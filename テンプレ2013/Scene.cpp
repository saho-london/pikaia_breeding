#include <DxLib.h>
#include <chrono>
#include <shlwapi.h>
#include <memory>
#include "Scene.h"
#include "file.h"
#include "string"
#include "time.h"
#include "myglobal.h"
#include "input.h"
#include "Draw.h"
#include "graph.h"
#pragma comment(lib, "ShLwApi.Lib")


Status::Status() :
bFirstUpdate(true),
existFlag(true)
{
}

void Status::entryAction(){}

void Status::inputAction(){}

void Status::exitAction(){}

void Status::update()
{
	if (bFirstUpdate){
		entryAction();
		bFirstUpdate = false;
	}
	inputAction();
	if (SceneManager::get().nextScene != nullptr || existFlag == false)
	{
		exitAction();
	}
}

void Status::draw(){}

std::shared_ptr<Status> SceneManager::create(Scene sce)
{
	if (sce == sprologue){ return std::make_shared<Prologue>(); }
	if (sce == sgame) { return std::make_shared<Game>(); }
	if (sce == sepilogue){ return std::make_shared<Epilogue>(); }
	if (sce == stitle){ return std::make_shared<Title>(); }
	if (sce == soption){ return std::make_shared<Option>(); }
	return std::make_shared<Prologue>();
	return nullptr;
}

SceneManager::SceneManager() :
loadFlag(notLoadData),
nextScene(nullptr)
{
	sceneVec.push_back(std::make_shared<Title>());
}

void SceneManager::update()
{
	Input::get().update();
	(**(sceneVec.end() - 1)).update();
	if (nextScene != nullptr)
	{
		for (auto iter = sceneVec.begin(); iter < sceneVec.end();)
		{
			iter = sceneVec.erase(iter);
		}
		sceneVec.push_back(nextScene);
		nextScene = nullptr;
	}
	for (auto iter = sceneVec.begin(); iter < sceneVec.end();)
	{
		if (!(**iter).existFlag)
		{
			iter = sceneVec.erase(iter);
		}
		else { iter++; }
	}
}

void SceneManager::draw()
{
	for (auto element : sceneVec)
	{
		element->draw();
	}
}

void SceneManager::load()
{
	SEGOE_20 = CreateFontToHandle("Segoe UI", fontSize1, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	SEGOE_12 = CreateFontToHandle("Segoe UI", fontSize2, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	Graph::get().load_graph();
	Graph::get().load_music();
	TimeManager::get().register_map();
	ChangeVolumeSoundMem(140, Graph::get().musicMap.at("dennsionn.wav"));
	ChangeVolumeSoundMem(180, Graph::get().musicMap.at("input2.wav"));
	Sound::loop_play(Graph::get().musicMap.at("pikaiaBGM.wav"));
	OCURSOR = LoadCursor(NULL, IDC_ARROW);
	HANDCURSOR = LoadCursorFromFile(_T("cursor.cur"));
}

void SceneManager::set_next(Scene nScene)
{
	nextScene = create(nScene);
}

Title::Title() :
Status()
{
}

void Title::entryAction()
{
	intervalTime = 10;
	existTime = 0;
	buttonSize.Set(90, 30);
	newGame.set_center(Vector2(SCREEN.x / 2, 300), buttonSize);
	load.set_center(Vector2(SCREEN.x / 2, 300 + buttonSize.y + 20), buttonSize);
	option.set_center(Vector2(SCREEN.x / 2, 300 + 2 * buttonSize.y + 40), buttonSize);
}

void Title::inputAction()
{
	if (existTime > intervalTime)
	{
		newGame.get_status();
		if (PathFileExists(File::get().get_file_name()))
		{
			load.get_status();
		}
		option.get_status();
		if (newGame.get_clicked_down())
		{
			Sound::back_play(Graph::get().musicMap.at("input2.wav"));
			if (PathFileExists(File::get().get_file_name()))
			{
				SceneManager::get().sceneVec.push_back(std::make_shared<NoticeWindow>());
			}
			else{ SceneManager::get().set_next(sprologue); }
		}
		if (PathFileExists(File::get().get_file_name())){
			if (load.get_clicked_down())
			{
				Sound::back_play(Graph::get().musicMap.at("input2.wav"));
				SceneManager::get().loadFlag = loadData;
				SceneManager::get().set_next(sgame);
			}
		}
		if (option.get_clicked_down())
		{
			Sound::back_play(Graph::get().musicMap.at("input2.wav"));
			SceneManager::get().set_next(soption);
		}
		if (newGame.get_on_mouse_down() || load.get_on_mouse_down() || option.get_on_mouse_down())
		{
			Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		}
	}
	existTime++;
}

void Title::draw()
{
	MyDraw::normal(0, 0, Graph::get().graphMap.at("title.png"));
	newGame.draw_ratio_on_mouse(Graph::get().graphMap.at("title-start.s.png"), Graph::get().graphMap.at("title-start.png"), 0.8, 1, 10);
	if (PathFileExists(File::get().get_file_name())){
		load.draw_ratio_on_mouse(Graph::get().graphMap.at("title-tuduki.s.png"), Graph::get().graphMap.at("title-tuduki.png"), 0.8, 1, 10);
	};
	option.draw_ratio_on_mouse(Graph::get().graphMap.at("title-option.s.png"), Graph::get().graphMap.at("title-option.png"), 0.8, 1, 10);
}

NoticeWindow::NoticeWindow() :
Status()
{
}

void NoticeWindow::entryAction()
{
	notice.set_center(SCREEN / 2, Vector2(0, 0));
	notice.set_ratio_time(5);
	yes.set_center(SCREEN / 2 + Vector2(-90, 55), Vector2(60, 40));
	no.set_center(SCREEN / 2 + Vector2(90, 55), Vector2(60, 40));
}

void NoticeWindow::inputAction()
{
	notice.get_status();
	yes.get_status();
	no.get_status();
	if (yes.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("input2.wav"));
		SceneManager::get().set_next(sprologue);
	}
	if (no.get_clicked_down())
	{
		existFlag = false;
	}

}

void NoticeWindow::draw()
{
	notice.draw_ratio(Graph::get().graphMap.at("keikoku.png"));
	if (notice.is_draw_finished())
	{
		yes.draw_on_mouse(Graph::get().graphMap.at("yes.png"), Graph::get().graphMap.at("yes1.png"));
		no.draw_on_mouse(Graph::get().graphMap.at("no.png"), Graph::get().graphMap.at("no1.png"));
		MyDraw::centertext(SCREEN / 2 + Vector2(0, -50), 0x222222, SEGOE_20, "既にセーブデータが存在します");
		MyDraw::centertext(SCREEN / 2 + Vector2(0, -20), 0x222222, SEGOE_20, "上書きされますがよろしいですか？");
	}
}


Option::Option() :
Status()
{
}

void Option::entryAction()
{
	if (PathFileExists(File::get().get_file_name_option()))
	{
		File::get().load_set_data();
	}
	else
	{
		Graph::get().set_back_number(0);
		Graph::get().set_status_number(0);
	}
	t = 0;
	option.Set(SCREEN.x / 2, 30);
	back.Set(SCREEN.x / 2, 215);
	status.Set(SCREEN.x / 2, 280);
	sound.Set(SCREEN.x / 2, 150);
	backIncrease.set_center(back + Vector2(125, 0), Vector2(30, 24));
	backDecrease.set_center(back - Vector2(125, 0), Vector2(30, 24));
	statusIncrease.set_center(status + Vector2(125, 0), Vector2(30, 24));
	statusDecrease.set_center(status - Vector2(125, 0), Vector2(30, 24));
	soundIncrease.set_center(sound + Vector2(125, 0), Vector2(30, 24));
	soundDecrease.set_center(sound - Vector2(125, 0), Vector2(30, 24));
	set.set_center(Vector2(SCREEN.x / 2 - 50, 355), Vector2(60, 30));
	cancel.set_center(Vector2(SCREEN.x / 2 + 50, 355), Vector2(60, 30));
	volume = 255;
}

void Option::inputAction()
{
	t++;
	//backIncrease.move(Vector2(0.5 * cos(t/80.0 * PI), 0));
	//statusIncrease.move(Vector2(0.5 * cos(t / 80.0 * PI), 0));
	//backDecrease.move(Vector2(-0.5 * cos(t / 80.0 * PI), 0));
	//statusDecrease.move(Vector2(-0.5 * cos(t / 80.0 * PI), 0));

	backIncrease.get_status();
	backDecrease.get_status();
	statusIncrease.get_status();
	statusDecrease.get_status();
	soundIncrease.get_status();
	soundDecrease.get_status();

	set.get_status();;
	cancel.get_status();

	if (backIncrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		if (Graph::get().get_back_number() < Graph::get().backVec.size() - 1)Graph::get().increase_back_number();
	}
	if (backDecrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		if (Graph::get().get_back_number() > 0)Graph::get().decrease_back_number();
	}
	if (statusIncrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		if (Graph::get().get_status_number() < Graph::get().statusVec.size() - 1)Graph::get().increase_status_number();
	}
	if (statusDecrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		if (Graph::get().get_status_number() > 0)Graph::get().decrease_status_number();
	}
	if (soundIncrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		volume += 16; if (volume > 255){ volume = 255; }
	}
	if (soundDecrease.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("dennsionn.wav"));
		volume -= 16; if (volume < 0){ volume = 0; }
	}

	Graph::get().set_volume(volume);

	if (set.get_clicked_down())
	{
		Sound::back_play(Graph::get().musicMap.at("input2.wav"));
		File::get().save_set_data();
		SceneManager::get().set_next(stitle);
	}
	if (cancel.get_clicked_down()){ SceneManager::get().set_next(stitle); }
}

void Option::draw()
{
	MyDraw::exrot(PLAYER_RANGE.get_center(), 520.0 / 390.0, 0, Graph::get().graphMap[Graph::get().backVec[Graph::get().get_back_number()]], 255);
	MyDraw::normal(0, SCREEN.y - 210, Graph::get().graphMap[Graph::get().statusVec[Graph::get().get_status_number()]], 255);
	//MyDraw::centertext(option, 0x553015, SEGOE_20, "オプション");
	MyDraw::center(option, Graph::get().graphMap.at("option.png"));

	//std::string str = "背景" + std::to_string(Graph::get().get_back_number());
	//MyDraw::centertext(back, 0x553015, SEGOE_20, fontSize1, str);
	MyDraw::center(back, Graph::get().graphMap.at("back.png"));
	//str = "フレーム" + std::to_string(Graph::get().get_status_number());
	//MyDraw::centertext(status, 0x553015, SEGOE_20, fontSize1, str);
	MyDraw::center(status, Graph::get().graphMap.at("flame.png"));
	//std::string str = "音量" + 
	std::string str = std::to_string(volume * 100 / 255) + "％";
	MyDraw::centertext(sound + Vector2(0, 30), 0x553015, SEGOE_12, fontSize1, str);
	MyDraw::center(sound, Graph::get().graphMap.at("sound.png"));
	backIncrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.ms.png"), Graph::get().graphMap.at("yazirusi.m.png"), 0.8, 1, 3, 100);
	backDecrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.hs.png"), Graph::get().graphMap.at("yazirusi.h.png"), 0.8, 1, 3, 100);
	statusIncrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.ms.png"), Graph::get().graphMap.at("yazirusi.m.png"), 0.8, 1, 3, 100);
	statusDecrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.hs.png"), Graph::get().graphMap.at("yazirusi.h.png"), 0.8, 1, 3, 100);
	soundIncrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.ms.png"), Graph::get().graphMap.at("yazirusi.m.png"), 0.8, 1, 3, 100);
	soundDecrease.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("yazirusi.hs.png"), Graph::get().graphMap.at("yazirusi.h.png"), 0.8, 1, 3, 100);

	cancel.draw_on_mouse(Graph::get().graphMap.at("kyannseru.png"), Graph::get().graphMap.at("kyannseru1.png"));
	set.draw_on_mouse(Graph::get().graphMap.at("kettei.png"), Graph::get().graphMap.at("kettei1.png"));
	MyDraw::centertext(SCREEN.x / 2, (PLAYER_RANGE.get_end().y + SCREEN.y) / 2, 0x553015, SEGOE_20, "音量、背景とフレームを設定できます");
}

Game::Game() :
Status()
{
}


void Game::entryAction()
{
	TimeManager::get().load_time();
	TimeManager::get().set_last_time();
	drawTime1 = 0;
	drawTime2 = 0;
	intervalTime = 10;
	existTime = 0;
	if (PathFileExists(File::get().get_file_name_option()))
	{
		File::get().load_set_data();
	}
	else
	{
		Graph::get().set_back_number(0);
		Graph::get().set_status_number(0);
	}
	if (SceneManager::get().loadFlag == loadData)
	{
		pManager.load();
		SceneManager::get().loadFlag = notLoadData;
	}
	else
	{
		TimeManager::get().reset_time();
	}
	buttonSize.Set(130, 80);
	button1.set_size(Vector2(buttonSize.x * 0, SCREEN.y - buttonSize.y), buttonSize);
	button2.set_size(Vector2(buttonSize.x * 1, SCREEN.y - buttonSize.y), buttonSize);
	button3.set_size(Vector2(buttonSize.x * 2, SCREEN.y - buttonSize.y), buttonSize);
	backToTitle.set_size(Vector2(280, 0), Vector2(80, 60));
	datePos.Set(100, 35);
	emptySatiety.set(Vector2(37, 445), Vector2(34, 0), Graph::get().graphMap.at("onaka0.png"), 5);
	fullSatiety.set(Vector2(37, 445), Vector2(34, 0), Graph::get().graphMap.at("onaka1.png"), 5);
	emptyExercise.set(Vector2(218, 445), Vector2(34, 0), Graph::get().graphMap.at("asobu0.png"), 5);
	fullExercise.set(Vector2(218, 445), Vector2(34, 0), Graph::get().graphMap.at("asobu.png"), 5);
	exitFlag = false;
	time = 0;

	SetClassLongPtr(GetMainWindowHandle(), GCL_HCURSOR, (LONG)HANDCURSOR);
}

void Game::inputAction(/*, std::shared_ptr<Status> ppOutNextState*/)
{
	if (DEBUG)
	{
		if (Input::get().keydown(KEY_INPUT_C))
		{
			File::get().save_data(PlayerData((pManager.playerPtr->get_player_data().trust)*0.4, pManager.playerPtr->get_player_data().generation + 1));
			exitFlag = true;
		}
	}

	button1.get_status();
	button2.get_status();
	button3.get_status();
	backToTitle.get_status();
	if (exitFlag == false)
	{
		if (existTime > intervalTime)
		{
			if (button1.get_clicked_down()){ pManager.feed(); }
			if (button2.get_clicked_down()){ pManager.play(); }
			if (button3.get_clicked_down()){ pManager.cure(); }
		}
		if (pManager.playerPtr->is_on_mouse() && Input::get().mouse_speed() > pManager.playerPtr->get_mouse_speed_threshold())
		{
			pManager.stroke();
		}
		pManager.update();

		pManager.playerPtr->effect.update();
		TimeManager::get().update();
		if ((pManager.playerPtr->get_state() == bird || pManager.playerPtr->get_state() == cat)
			&& pManager.playerPtr->get_grouth() == pManager.playerPtr->get_max_grouth())
		{
			File::get().save_data(PlayerData((pManager.playerPtr->get_player_data().trust)*0.4, pManager.playerPtr->get_player_data().generation + 1));
			exitFlag = true;
		}
		if (backToTitle.get_clicked_down())
		{
			pManager.save();
			Sound::back_play(Graph::get().musicMap.at("input2.wav"));
			SetClassLongPtr(GetMainWindowHandle(), GCL_HCURSOR, (LONG)OCURSOR);
			SceneManager::get().set_next(stitle);
		}
	}
	if (exitFlag == true)
	{
		time++;
		if (time == 60)
		{

			SetClassLongPtr(GetMainWindowHandle(), GCL_HCURSOR, (LONG)OCURSOR);
		}
		if (time > 180)
		{
			SceneManager::get().set_next(sepilogue);
		}
	}
	existTime++;
}

void Game::exitAction()
{
	TimeManager::get().save_time();
}

void Game::draw(){
	MyTime playTime(TimeManager::get().playTime);
	MyTime T(TimeManager::get().sumPlayTime);

	MyDraw::exrot(PLAYER_RANGE.get_center(), 520.0 / 390.0, 0, Graph::get().graphMap[Graph::get().backVec[Graph::get().get_back_number()]], 255);
	MyDraw::normal(0, SCREEN.y - 210, Graph::get().graphMap[Graph::get().statusVec[Graph::get().get_status_number()]], 255);

	//MyDraw::normal(gManager.gameStatus.button1.start, Graph::get().graphMap.at("button.png"), 255);
	//MyDraw::normal(gManager.gameStatus.button2.start, Graph::get().graphMap.at("button.png"), 255);
	//MyDraw::normal(gManager.gameStatus.button3.start, Graph::get().graphMap.at("button.png"), 255);
	button1.draw_clicked(Graph::get().graphMap[Graph::get().buttonVec[0]], Graph::get().graphMap[Graph::get().buttonVec[3]]);
	button2.draw_clicked(Graph::get().graphMap[Graph::get().buttonVec[1]], Graph::get().graphMap[Graph::get().buttonVec[4]]);
	button3.draw_clicked(Graph::get().graphMap[Graph::get().buttonVec[2]], Graph::get().graphMap[Graph::get().buttonVec[5]]);
	backToTitle.draw_alpha_on_mouse(Graph::get().graphMap.at("back_title.png"), 10);

	if (pManager.playerPtr->get_player_data().diseaseFlag)
	{
		drawTime1++;
		drawTime2 = 0;
		if (drawTime1 < 10)
		{
			MyDraw::centertext(SCREEN.x / 2, 65, 0x553015, SEGOE_12, "Tips　:　ピカイアが病気になったら治療してあげましょう", drawTime1 / 10.0 * 255);
		}
		else MyDraw::centertext(SCREEN.x / 2, 65, 0x553015, SEGOE_12, "Tips　:　ピカイアが病気になったら治療してあげましょう");
	}
	else if (pManager.playerPtr->get_player_data().trust < pManager.playerPtr->get_max_trust() * 0.2)
	{
		drawTime2++;
		drawTime1 = 0;
		if (drawTime2 < 10)
		{
			MyDraw::centertext(SCREEN.x / 2, 65, 0x553015, SEGOE_12, "Tips　:　ピカイアの頭をたくさん撫でてあげましょう", drawTime2 / 10.0 * 255);
		}
		else MyDraw::centertext(SCREEN.x / 2, 65, 0x553015, SEGOE_12, "Tips　:　ピカイアの頭をたくさん撫でてあげましょう");
	}
	else
	{
		drawTime1 = 0;
		drawTime2 = 0;
	}

	pManager.draw();

	emptySatiety.draw();
	fullSatiety.draw_ratio(pManager.playerPtr->get_satiety(), 10);
	emptyExercise.draw();
	fullExercise.draw_ratio(pManager.playerPtr->get_exercise(), 10);
	MyDraw::center(SCREEN.x / 2, 497, Graph::get().graphMap.at("ba-00.png"));
	MyDraw::trim(SCREEN.x / 2 - 195, 497 - 105, 0, 0, 10 + pManager.playerPtr->get_grouth() * 380 / pManager.playerPtr->get_max_grouth(), 210, Graph::get().graphMap.at("ba-01.png"));

	MyDraw::center(datePos, Graph::get().graphMap.at("day0.png"));
	std::chrono::seconds sec;
	sec = std::chrono::duration_cast<std::chrono::seconds>(TimeManager::get().sumPlayTime + TimeManager::get().playTime);
	std::string str = std::to_string(sec.count() / 20 + 1) + "日目(" + std::to_string(pManager.playerPtr->get_player_data().generation) + "代目)";

	MyDraw::centertext(datePos, 0x553015, SEGOE_20, fontSize1, str);

	DrawFormatStringToHandle(SCREEN.x / 2 + 110, 497 + 6, 0x553015, SEGOE_12, "%0.2lf/%0.2lf", pManager.playerPtr->get_player_data().grouth, pManager.playerPtr->get_max_grouth());

	pManager.playerPtr->effect.draw();
	if (exitFlag == true)
	{
		if (time <= 90){
			MyDraw::normal(0, 0, Graph::get().graphMap.at("black.png"), 255 * time / 90);
		}
		else
		{
			MyDraw::normal(0, 0, Graph::get().graphMap.at("black.png"));
			MyDraw::normal(0, 0, Graph::get().graphMap.at("kosi5.png"), 255 * (time - 90) / 90);
		}
	}
}

Prologue::Prologue() :
Status()
{
}

void Prologue::entryAction()
{
	Graph::get().stop_bgm();
	Sound::loop_play(Graph::get().musicMap.at("pikaiaProEpi.wav"));
	File::get().load_set_data();
	std::string str = "prologue.dat";
	prologue.set(str);
	prologue.read();
	skip.set_center(Vector2(SCREEN.x - 50, SCREEN.y - 30), Vector2(40, 20));
}

void Prologue::inputAction(/*, std::shared_ptr<Status> ppOutNextState*/)
{
	skip.get_status();
	prologue.update();
	if (prologue.get_end() < -20)
	{
		SceneManager::get().set_next(sgame);
	}
	if (skip.get_clicked_down())
	{
		SceneManager::get().set_next(sgame);
	}
}

void Prologue::exitAction()
{
	Graph::get().stop_bgm();
	Sound::loop_play(Graph::get().musicMap.at("pikaiaBGM.wav"));
}

void Prologue::draw()
{
	MyDraw::normal(0, 0, Graph::get().graphMap.at("kosi4.png"));
	prologue.draw();
	skip.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("skip.s.png"), Graph::get().graphMap.at("skip.png"), 0.8, 1, 5, 100);
}


Epilogue::Epilogue() :
Status()
{
}

void Epilogue::entryAction()
{
	Graph::get().stop_bgm();
	Sound::loop_play(Graph::get().musicMap.at("pikaiaProEpi(静).wav"));
	writeFlag = true;
	std::string str = "epilogue.dat";
	epilogue.set(str);
	epilogue.read();
	skip.set_center(Vector2(SCREEN.x - 50, SCREEN.y - 30), Vector2(40, 20));
}

void Epilogue::inputAction(/*, std::shared_ptr<Status> ppOutNextState*/)
{
	skip.get_status();
	epilogue.update();
	if (epilogue.get_end() < -20)
	{
		writeFlag = false;
		SceneManager::get().sceneVec.push_back(std::make_shared<Tips>());
	}
	if (skip.get_clicked_down())
	{
		writeFlag = false;
		SceneManager::get().sceneVec.push_back(std::make_shared<Tips>());
	}
}

void Epilogue::draw()
{
	MyDraw::normal(0, 0, Graph::get().graphMap.at("kosi5.png"));
	if (writeFlag)
	{
		epilogue.draw();
		skip.draw_ratio_on_mouse_alpha(Graph::get().graphMap.at("skip.s.png"), Graph::get().graphMap.at("skip.png"), 0.8, 1, 5, 100);
	}
}

Tips::Tips() :
Status(),
existTime(0)
{

}

void Tips::entryAction()
{
	maxExistTime = 400;
}

void Tips::inputAction()
{
	existTime++;
	if (existTime >= maxExistTime)
	{
		SceneManager::get().set_next(stitle);
	}
	if (Input::get().mouseDown)
	{
		SceneManager::get().set_next(stitle);
	}
}

void Tips::draw_log(double alpha)
{
	MyDraw::centertext(SCREEN / 2 + Vector2(0, -30), 0x553015, SEGOE_20, "Tips", alpha*255);
	MyDraw::centertext(SCREEN / 2, 0x553015, SEGOE_12, "ピカイアはたくさん頭をなでたり撫でなかったりすることで", alpha*255);
	MyDraw::centertext(SCREEN / 2 + Vector2(0, 15), 0x553015, SEGOE_12, "ふたつの違う姿に進化する可能性を秘めています", alpha*255);
}

void Tips::draw()
{
	if (existTime < maxExistTime/5)
	{
		draw_log((double)existTime / ((double)maxExistTime / 5.0));
	}
	else	if (existTime > maxExistTime * 4 / 5)
	{
		draw_log((double)(maxExistTime - existTime) / ((double)maxExistTime / 5.0));
	}
	else {
		draw_log(1);
	}

}

void Tips::exitAction()
{
	Graph::get().stop_bgm();
	Sound::loop_play(Graph::get().musicMap.at("pikaiaBGM.wav"));
}