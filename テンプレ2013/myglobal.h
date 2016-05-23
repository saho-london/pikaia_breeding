#pragma once

#include "Vector2.h"
#include "MyFunc.h"

#define DEBUG 0

extern double PI;					//円周率
extern double DegToRad;				//角度(度)からラジアンに変換する係数

extern int fontSize1;				//フォントサイズ(大)
extern int fontSize2;				//フォントサイズ(小)

extern int SEGOE_20;				//フォントハンドル
extern int SEGOE_12;				//フォントハンドル

extern Vector2 SCREEN;				//画面サイズ
extern Rectangular PLAYER_RANGE;	//キャラクターの可動域
extern Vector2 homePoint;			//キャラクターの初期位置

extern HCURSOR HANDCURSOR;			//手の形のカーソルのハンドル
extern HCURSOR OCURSOR;				//初期のカーソルのハンドル