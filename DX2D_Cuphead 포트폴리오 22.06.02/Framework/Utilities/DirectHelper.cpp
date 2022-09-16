#include "Framework.h"
#include "DirectHelper.h"

const float Value::PI = 3.14159f;

const Vector3 Value::ZeroVec3 = Vector3(0, 0, 0);
const Vector3 Value::OneVec3 = Vector3(1, 1, 1);
const Vector3 Value::LeftVec = Vector3(-1, 0, 0);
const Vector3 Value::RightVec = Vector3(1, 0, 0);
const Vector3 Value::UpVec = Vector3(0, 1, 0);
const Vector3 Value::DownVec = Vector3(0, -1, 0);
const Vector3 Value::FwdVec = Vector3(0, 0, 1);
const Vector3 Value::ScreenSize = Vector3((float)WinMaxWidth, (float)WinMaxHeight, 1);

const Vector2 Value::ZeroVec2 = Vector2(0, 0);
const Vector2 Value::OneVec2 = Vector2(1, 1);
const Vector2 Value::uvlt = Vector2(0, 0);
const Vector2 Value::uvlb = Vector2(0, 1);
const Vector2 Value::uvrt = Vector2(1, 0);
const Vector2 Value::uvrb = Vector2(1, 1);

const Color Value::Red(1, 0, 0, 1);
const Color Value::Green(0, 1, 0, 1);
const Color Value::Blue(0, 0, 1, 1);
const Color Value::Magenta(1, 0, 1, 1);
const Color Value::Black(0, 0, 0, 1);
const Color Value::White(1, 1, 1, 1);
const Color Value::ClearColor = 0xFF555566;

const Matrix Value::Identity = { 1, 0, 0, 0,
								 0, 1, 0, 0,
								 0, 0, 1, 0,
								 0, 0, 0, 1 };
