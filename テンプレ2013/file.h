#pragma once

#include <fstream>
#include "Vector2.h"
#include <vector>

struct PlayerData;

//セーブデータの管理をするクラス(シングルトン)
class File{
private:
	char *FILE_NAME;					//プレイデータのファイル
	char *FILE_NAME_OPTION;				//オプションの設定を保存するファイル

	File();

	File(const File& r) = delete;//コピーを禁止
	File& operator=(const File& r) = delete; //代入を禁止

public:
	static File& get(){
		static File inst;
		return inst;
	}

	void load_set_data();				//ロード
	void save_set_data();				//オプションの設定のセーブ
	void save_data(PlayerData data);	//プレイデータのセーブ
	PlayerData read_data();				//プレイデータのロード

	char * get_file_name();				//プレイヤーデータのファイル名を返す関数
	char * get_file_name_option();		//オプションの設定を保存するファイル名を返す関数
};


//ログテキストを読み込んで管理・描画するクラス
class Log{
private:
	//一行分の文字列を保存するクラス
	class String
	{
	public:
		String(double y, std::string str_);
		Vector2 original;			//相対位置
		std::string str;			//文字列
		void draw(Vector2 camera);	//描画関数
	};

	std::string FILE_NAME;			//ログテキストのファイル名
	std::vector<String> vec;		//文字列のベクター
	FILE *fp;
	Vector2 camera;					//全体の絶対位置
	const double logSpeed;			//ログの流れるスピード
	const double startPoint;		//描画開始位置

public:

	Log();


	void update();					//更新
	void read();					//読み込み
	void draw();					//描画
	double get_start();				//先頭の位置を取得
	double get_end();				//末尾の位置を取得
	void set(std::string str);		//ファイル名を代入
	void reset_camera();			//全体の絶対位置を初期位置にする
	int vec_size();					//ベクターのサイズを取得
};
