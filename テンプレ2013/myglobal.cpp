#include "myglobal.h"
#include "math.h"
#include "MyFunc.h"
#include "Vector2.h"

double PI = atan(1.0) * 4;
double DegToRad = PI / 180;

int fontSize1 = 20;
int fontSize2 = 12;

int SEGOE_20;
int SEGOE_12;

HCURSOR HANDCURSOR;
HCURSOR OCURSOR;

Vector2 SCREEN(390, 600);
Rectangular PLAYER_RANGE(Vector2(0, 0), Vector2(SCREEN.x, SCREEN.x - 20));
Vector2 homePoint(160, 200);