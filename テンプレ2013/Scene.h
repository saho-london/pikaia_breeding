#pragma once

#include <string>
#include <memory>
#include "MyFunc.h"
#include "Vector2.h"
#include "player.h"
#include "File.h"


//�V�[���̎��
enum Scene
{
	stitle,
	soption,
	sgame,
	sprologue,
	sepilogue
};

//title��ʂ���Q�[���J�n���ɃZ�[�u�f�[�^�����[�h���邩
enum LoadFlag
{
	loadData,
	notLoadData
};

//�V�[���̊��N���X
class Status
{
private:
	bool bFirstUpdate;

protected:
	virtual void entryAction();
	virtual void inputAction();
	virtual void exitAction();
public:
	bool existFlag;

	Status();

	void update();
	virtual void draw();
};

//�V�[�����Ǘ�����N���X
class SceneManager
{
	SceneManager();

	SceneManager(const SceneManager& r) = delete;//�R�s�[���֎~
	SceneManager& operator=(const SceneManager& r) = delete; //������֎~
public:
	static SceneManager& get(){
		static SceneManager inst;
		return inst;
	}



	std::shared_ptr<Status> create(Scene sce);

	std::vector<std::shared_ptr<Status>> sceneVec;
	std::shared_ptr<Status> nextScene;
	LoadFlag loadFlag;

	void update();
	void draw();
	void load();
	void set_next(Scene nScene);
};

class Title : public Status
{
public:

	Vector2 buttonSize;
	Rectangular newGame;
	Rectangular load;
	Rectangular option;

	int intervalTime;
	int existTime;

	Title();

	virtual void entryAction() override;
	virtual void inputAction() override;

	virtual void draw() override;
};

//title��ʂ̂͂��߂���I�����̒��ӏ���
class NoticeWindow : public Status
{
public:
	NoticeWindow();

	Rectangular notice;

	Rectangular yes;
	Rectangular no;

	virtual void entryAction() override;
	virtual void inputAction() override;

	virtual void draw() override;
};

class Option : public Status
{
public:
	Vector2 option;
	Vector2 back;
	Vector2 status;
	Vector2 sound;
	Rectangular backIncrease;
	Rectangular backDecrease;
	Rectangular statusIncrease;
	Rectangular statusDecrease;
	Rectangular soundIncrease;
	Rectangular soundDecrease;
	Rectangular set;
	Rectangular cancel;

	int t;
	int volume;

	Option();

	virtual void entryAction() override;
	virtual void inputAction() override;

	virtual void draw() override;
};

class Game : public Status
{
public:
	Vector2 buttonSize;
	Vector2 datePos;

	Rectangular button1;
	Rectangular button2;
	Rectangular button3;

	Rectangular backToTitle;

	Que emptySatiety;
	Que fullSatiety;
	Que emptyExercise;
	Que fullExercise;

	bool exitFlag;
	int time;
	int drawTime1;
	int drawTime2;

	int intervalTime;
	int existTime;

	PlayerManager pManager;

	Game();

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	virtual void draw() override;

};

class Prologue : public Status
{
public:
	Log prologue;
	Rectangular skip;

	Prologue();

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	virtual void draw() override;
};

class Epilogue : public Status
{
public:
	Rectangular skip;
	Log epilogue;
	bool writeFlag;

	Epilogue();

	virtual void entryAction() override;
	virtual void inputAction() override;

	virtual void draw() override;
};

//�Q�[���N���A����Tips
class Tips : public Status
{
public:
	int existTime;
	int maxExistTime;

	Tips();

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	void draw_log(double alpha);
	virtual void draw() override;
};