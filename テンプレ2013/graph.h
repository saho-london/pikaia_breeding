#pragma once

#include <vector>
#include <map>
#include <string>


//画像と音素材のハンドルを管理するクラス(シングルトン)

class Graph{
private:
	int backNumber;							//背景画像の番号
	int statusNumber;						//ステータス部分の背景画像の番号

	Graph();

	Graph(const Graph& r) = delete;//コピーを禁止
	Graph& operator=(const Graph& r) = delete; //代入を禁止

public:
	std::map<std::string, int> graphMap;	//画像ハンドルのマップ（画像ファイル名→画像ハンドル）
	std::map<std::string, int> musicMap;	//音ハンドルのマップ（音楽ファイル名→ハンドル）


	std::vector<std::string> backVec;		//背景画像のファイル名を格納するベクター
	std::vector<std::string> buttonVec;		//ボタンの画像ファイル名を格納するベクター
	std::vector<std::string> statusVec;		//ステータス部分の背景画像のファイル名を格納するベクター

	static Graph& get();					

	void load_graph();						//画像ファイル読み込み
	void load_music();						//音楽ファイル読み込み
	void add_graph(std::string name);		//与えられた画像ファイルのハンドルを取得しマップに追加
	void add_music(std::string name);		//与えられた音楽ファイルのハンドルを取得しマップに追加
	void add_back();						//背景ベクターの名前が登録されている画像のハンドルを取得しマップに追加
	void register_back();					//背景ベクターに背景画像の名前を追加
	void add_button();						//ボタンベクターの名前が登録されている画像のハンドルを取得しマップに追加
	void register_button();					//ボタンベクターに背景画像の名前を追加
	void add_status();						//ステータスベクターの名前が登録されている画像のハンドルを取得しマップに追加
	void register_status();					//ステータスベクターに背景画像の名前を追加
	void set_volume(int vol);				//すべての音楽ファイルに音量設定を適用
	void stop_bgm();						//BGMファイルをすべて再生終了

	void increase_back_number();			//背景画像の番号を増やす
	void increase_status_number();			//ステータス部分の背景画像の番号を増やす
	void decrease_back_number();			//背景画像の番号を減らす
	void decrease_status_number();			//ステータス部分の背景画像の番号を減らす
	int get_back_number();					//現在の背景画像の番号を返す
	int get_status_number();				//現在のステータス部分の背景画像の番号を返す
	void set_back_number(int n);			//背景画像の番号を設定する
	void set_status_number(int n);			//ステータス部分の背景画像の番号を設定する
};
