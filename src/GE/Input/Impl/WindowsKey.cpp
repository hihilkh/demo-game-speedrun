#include "GE/Utils/PreprocessorDef.h"

#if _INPUT == INPUT_WINDOWS

#include "../Key.h"
#include <windows.h>

namespace GE::Input
{
	// 参考：https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#pragma region 十字キー
	const KeyCode Key::left		= VK_LEFT;
	const KeyCode Key::right	= VK_RIGHT;
	const KeyCode Key::up		= VK_UP;
	const KeyCode Key::down		= VK_DOWN;
#pragma endregion

#pragma region 特殊文字
	const KeyCode Key::spaceKey		= VK_SPACE;
	const KeyCode Key::returnKey	= VK_RETURN;
#pragma endregion

#pragma region 数字
	const KeyCode Key::zero		= 0x30;
	const KeyCode Key::one		= 0x31;
	const KeyCode Key::two		= 0x32;
	const KeyCode Key::three	= 0x33;
	const KeyCode Key::four		= 0x34;
	const KeyCode Key::five		= 0x35;
	const KeyCode Key::six		= 0x36;
	const KeyCode Key::seven	= 0x37;
	const KeyCode Key::eight	= 0x38;
	const KeyCode Key::nine		= 0x39;
#pragma endregion

#pragma region 英文字
	const KeyCode Key::a = 0x41;
	const KeyCode Key::b = 0x42;
	const KeyCode Key::c = 0x43;
	const KeyCode Key::d = 0x44;
	const KeyCode Key::e = 0x45;
	const KeyCode Key::f = 0x46;
	const KeyCode Key::g = 0x47;
	const KeyCode Key::h = 0x48;
	const KeyCode Key::i = 0x49;
	const KeyCode Key::j = 0x4A;
	const KeyCode Key::k = 0x4B;
	const KeyCode Key::l = 0x4C;
	const KeyCode Key::m = 0x4D;
	const KeyCode Key::n = 0x4E;
	const KeyCode Key::o = 0x4F;
	const KeyCode Key::p = 0x50;
	const KeyCode Key::q = 0x51;
	const KeyCode Key::r = 0x52;
	const KeyCode Key::s = 0x53;
	const KeyCode Key::t = 0x54;
	const KeyCode Key::u = 0x55;
	const KeyCode Key::v = 0x56;
	const KeyCode Key::w = 0x57;
	const KeyCode Key::x = 0x58;
	const KeyCode Key::y = 0x59;
	const KeyCode Key::z = 0x5A;
#pragma endregion
}

#endif