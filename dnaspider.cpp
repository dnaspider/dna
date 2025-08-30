// @dnaspider

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <regex>
#include <codecvt>
#include <thread>

using namespace std;
using ctp = chrono::steady_clock::time_point;

#pragma region global_var
wstring&&
	Kb_Key_A = L"a", Kb_Key_B = L"b", Kb_Key_C = L"c", Kb_Key_D = L"d", Kb_Key_E = L"e", Kb_Key_F = L"f", Kb_Key_G = L"g", Kb_Key_H = L"h", Kb_Key_I = L"i", Kb_Key_J = L"j", Kb_Key_K = L"k", Kb_Key_L = L"l", Kb_Key_M = L"m", Kb_Key_N = L"n", Kb_Key_O = L"o", Kb_Key_P = L"p", Kb_Key_Q = L"q", Kb_Key_R = L"r", Kb_Key_S = L"s", Kb_Key_T = L"t", Kb_Key_U = L"u", Kb_Key_V = L"v", Kb_Key_W = L"w", Kb_Key_X = L"x", Kb_Key_Y = L"y", Kb_Key_Z = L"z",
	Kb_Key_0 = L"0", Kb_Key_1 = L"1", Kb_Key_2 = L"2", Kb_Key_3 = L"3", Kb_Key_4 = L"4", Kb_Key_5 = L"5", Kb_Key_6 = L"6", Kb_Key_7 = L"7", Kb_Key_8 = L"8", Kb_Key_9 = L"9",
	Kb_Key_F1 = L"", Kb_Key_F2 = L"", Kb_Key_F3 = L"", Kb_Key_F4 = L"", Kb_Key_F5 = L"", Kb_Key_F6 = L"", Kb_Key_F7 = L"", Kb_Key_F8 = L"", Kb_Key_F9 = L"", Kb_Key_F10 = L"", Kb_Key_F11 = L"", Kb_Key_F12 = L"",
	Kb_Key_Left = L"", Kb_Key_Up = L"", Kb_Key_Right = L"", Kb_Key_Down = L"",
	Kb_Key_Esc = L"", Kb_Key_Space = L"", Kb_Key_Tab = L"", Kb_Key_Left_Shift = L"", Kb_Key_Right_Shift = L"", Kb_Key_Left_Alt = L"", Kb_Key_Right_Alt = L"", Kb_Key_Left_Ctrl = L"", Kb_Key_Right_Ctrl = L"", Kb_Key_Enter = L"", Kb_Key_Caps = L"", Kb_Key_Grave_Accent = L"", Kb_Key_Minus = L"", Kb_Key_Equal = L"", Kb_Key_Left_Bracket = L"", Kb_Key_Right_Bracket = L"", Kb_Key_Backslash = L"", Kb_Key_Semicolon = L"", Kb_Key_Quote = L"", Kb_Key_Comma = L"", Kb_Key_Period = L"", Kb_Key_Forwardslash = L"", Kb_Key_Menu = L"",
	Kb_Key_Print_Screen = L"", Kb_Key_Insert = L"", Kb_Key_Delete = L"", Kb_Key_Home = L"", Kb_Key_End = L"", Kb_Key_PgUp = L"", Kb_Key_PgDn = L"",
	Kb_Key_Numpad_0 = L"", Kb_Key_Numpad_1 = L"", Kb_Key_Numpad_2 = L"", Kb_Key_Numpad_3 = L"", Kb_Key_Numpad_4 = L"", Kb_Key_Numpad_5 = L"", Kb_Key_Numpad_6 = L"", Kb_Key_Numpad_7 = L"", Kb_Key_Numpad_8 = L"", Kb_Key_Numpad_9 = L"", Kb_Key_Numlock = L"", Kb_Key_Numpad_Divide = L"", Kb_Key_Numpad_Multiply = L"", Kb_Key_Numpad_Minus = L"", Kb_Key_Numpad_Add = L"", Kb_Key_Numpad_Period = L"", Kb_Key_Numpad_Enter = L""
;
wstring&& pre = L""; //previous reTail
wstring&& io = L" ";//i*o
wstring&& linkr = L"";
wstring&& link = L""; //<app|rgb|ifcb,,,<link:>
wstring&& editor1 = L"Notepad", editor = L"Visual Studio Code", db = L"db.txt - ", se = L"se.txt - ", editorSe = se + editor, editorDb = db + editor;
wstring database, settings, replacerDb;
wstring&& strand = L""; //>> supply
wstring&& tail = L""; //strand:tail
wstring&& re = L"";//repeat clone
wstring&& reTail = L"";
wstring&& codes = L""; //tail re
wstring star_num; //<x*#>
wstring qq; //<x>
wstring qp; //<x:#>
wstring qx, qy; //<xy:#,#>
wstring&& OutsTemplate = L"";
wstring&& Loop_Insert_Text = L"";
wstring&& multiLineDelim = L"\n"; //DbMultiLineDelimiter:
wstring&& OutTab = L"\t"; //OutTabs
double RgbScaleLayout = 1.00; //100%
double ic = 0; //<+> icp
size_t i = 0;
size_t qqLen = 2;
int rri = 0; //++RSHIFTLSHIFT_Only
int CommaSleep = 128;
int frequency = 160; //>> ms response -> vk_
int speed = 0; //<< 
int qxc = 0, qyc = 0;//<rp>
int qxcc = 0, qycc = 0;//cc
int CloseCtrlSpacer = 96;
short Kb_QQ_i = 0, Kb_QQ_k = 0; //qq < [Kb_Key_Q: >q '<bs>]
short strandLengthMode = 0;
short PauseKey = 123; //VK_F12
short ClearStrandKey = 123;
short reKey = VK_PAUSE; //repeat
short cKey = VK_SPACE, cKeyMax = 3; //<
short RSHIFTLSHIFT_Only = 1;
short LSHIFTCtrlKey = 0; //<
short RSHIFTCtrlKeyToggle = 0;
bool toggle_ccm = 0; //RSHIFTCtrlKeyToggle close_ctrl_mode=0
bool ManualRepeat = 0;//<repeat>
bool io_Auto_BS = 1;//i*o
bool NoEscapeOrPause = 0; //<~esc>, <~~esc>
bool noClearStrand = 0; //<!>
bool OutTabs = 1;
bool multiblock = 0; //<~m>
bool Unicode = 1;
bool multiStrand = 1, showMultiStrandElapsedOnly = 0;
bool relink = 0;
bool fail = 0;
bool sleep = 1;
bool esc_pressed = 0;
bool pause_resume = 0;
bool enableEscX = true;
bool startHidden = true;
bool ignoreAZ = false;
bool ignore09 = false;
bool ignoreArrows = true;
bool ignoreF1s = true;//f1-f12
bool ignoreNumPad = true;
bool ignoreOtherKeys = false;
bool qScanOnly = true;
bool showStrand = false; //cout <<
bool showIntro = false;
bool showSettings = true;
bool shft = false;
bool close_ctrl_mode = true; //x>, x:, x- 
bool SlightPauseInBetweenConnects = false;
bool EscCommaAutoBs = true;
bool EscEqualAutoBs = true;
bool EscHAutoBs = true;
bool AutoBs_RepeatKey = false;
bool SeHotReload_CtrlS = true;
bool SeDbClearStrand_CtrlS = true;
bool assume = true;
#pragma endregion

#pragma region protos
void showOutsMsg(wstring, wstring, wstring, bool);
ctp clockr(ctp&);
void cbSet(wstring&);
wstring randn(bool);
void repeat();
#pragma endregion

#pragma region classo
struct Store {
	wstring v, v1;
};
struct Mainn {
	wstring s = L"", s1 = L"", t = tail;//strand
	ctp c1{}, c2{};//elapsed
	Mainn() {
		if (!multiStrand) return;
		if (showMultiStrandElapsedOnly) { clockr(c1); return; }
	}
	~Mainn() {
		if (!multiStrand) return;
		if (showMultiStrandElapsedOnly) { clockr(c2); chrono::duration<double, milli> ts = c1 - c2; wstring q = L""; if (!showStrand) { q = strand[strand.size() - 1] == '>' ? L"" : strand.size() > 0 ? L">" : L""; wstring p = q; q = strand + p; } bool x = showStrand; showStrand = 1; showOutsMsg(L"", OutsTemplate, q, 1); showStrand = x; cout << dec << "(" << abs(static_cast<long>(ts.count())) << "ms elapsed)\n"; return; }
	}
};

struct Multi {
	wstring qp, r, g, b, a, x, m, l, t = tail, q = qq, s = strand;
	double icp = 0; size_t i_ = i;
	int cx = 0, cy = 0, speed_ = 0;
	bool esc = 0, br = 0;//break
	//~Multi() {}
};
#pragma endregion

#pragma region global_sub
static wstring getTime(wstring& w) {
	auto np = chrono::system_clock::now();
	auto n = chrono::system_clock::to_time_t(np);
	char b[26];
	ctime_s(b, sizeof(b), &n);
	for (auto i = 0; i < 26; ++i) {
		if (b[i] == '\n') break;
		w += b[i];
	}
	return w;
}

ctp clockr(ctp& t) {
	return t = chrono::high_resolution_clock::now();
}

static wstring check_if_num(wstring &s) {
	if (assume) return s;
	
	char d = 0;
	for (size_t x = 0; x < s.length(); ++x) {
		if (x == 0 && s[0] == '-') { if (s.length() == 1) { s.clear(); break; } continue; }
		if (s[x] == '.') { ++d; if (d > 1 || s.length() == 1) { s.clear(); break; } continue; }
		if (s[x] < '0' || s[x] > '9') { s.clear(); break; }
	}
	return s;
}

static void kb(wchar_t b) {//out char
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	if (VkKeyScanW(b) == -1) { ip[0].ki.wScan = b; ip[0].ki.wVk = 0; }
	else { ip[0].ki.wVk = VkKeyScanW(b); }
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

static void kb(wstring &b) {
	if (b.find('\\') != string::npos) b = regex_replace(b, wregex(L"\\\\g"), L">");
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	for (auto &i : b) {
		ip[0].ki.wScan = i; ip[0].ki.wVk = 0;
		ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(2, ip, sizeof(ip[0]));
	}
}

static void kbHold(short key) {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key; ip.ki.time = 0;
	if (key == VK_LMENU || key == VK_CONTROL) ip.ki.dwFlags = 0; else ip.ki.dwFlags = 1;
	SendInput(1, &ip, sizeof(INPUT));
}

static void kbRelease(short key) {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; SendInput(1, &ip, sizeof(INPUT));
	GetAsyncKeyState(key);
}

static void mouseEvent(short key) {
	INPUT ip{}; ip.type = INPUT_MOUSE; ip.mi.time = 0;
	ip.mi.dwFlags = key;
	if (key == MOUSEEVENTF_HWHEEL) {
		if (qq.substr(0, 3) == L"<sr") ip.mi.mouseData = WHEEL_DELTA;//scroll right
		else if (qq.substr(0, 3) == L"<sd") { ip.mi.dwFlags = MOUSEEVENTF_WHEEL; ip.mi.mouseData = -WHEEL_DELTA; }//scroll down
		else if (qq.substr(0, 3) == L"<sl") ip.mi.mouseData = -WHEEL_DELTA;//scroll left
		else if (qq.substr(0, 3) == L"<su") { ip.mi.dwFlags = MOUSEEVENTF_WHEEL; ip.mi.mouseData = WHEEL_DELTA; }//scroll up
	}
	SendInput(1, &ip, sizeof(ip));
}

static void shftRelease() {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.dwFlags = 2;
	ip.ki.wVk = VK_LSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_RSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	if (shft) shft = false;
	GetAsyncKeyState(VK_LSHIFT);
	GetAsyncKeyState(VK_RSHIFT);
}

static void printq() { kbHold(VK_LSHIFT); kb('<'); shftRelease(); }

static void prints() { if (showStrand) { auto s = L""+strand; OutsTemplate[0] == '\\' && OutsTemplate[OutsTemplate.length() - 2] == '\\' ? s = s.replace(0, s.length(), OutsTemplate.substr(0, 2) + s + OutsTemplate.substr(OutsTemplate.length() - 2)) : s = s.replace(0, s.length(), L"\\G" + s + L"\\7"); showOutsMsg(L"", OutsTemplate + s, L"\n", 1); } }

static bool qqb(const wstring s) {
	return qq.substr(0, s.length()) == s && qq.find('>') != string::npos;
}

static bool testqqb(const wstring s) {
	return qqb(s) && qq[s.length()] != '>';
}

static void clearAllKeys() {
	if (!ignoreAZ) for (int i = 65; i <= 90; ++i) { GetAsyncKeyState(i); }
	if (!ignore09) for (int i = 48; i <= 57; ++i) { GetAsyncKeyState(i); }
	if (Kb_Key_Right_Shift[0]) GetAsyncKeyState(VK_RSHIFT);
	if (Kb_Key_Left_Shift[0]) GetAsyncKeyState(VK_LSHIFT);
	GetAsyncKeyState(VK_BACK);
	if (Kb_Key_Esc[0]) GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_PAUSE);
	if (Kb_Key_Space[0]) GetAsyncKeyState(VK_SPACE);
	if (!ignoreF1s) { GetAsyncKeyState(VK_F1); GetAsyncKeyState(VK_F2); GetAsyncKeyState(VK_F3); GetAsyncKeyState(VK_F4); GetAsyncKeyState(VK_F5); GetAsyncKeyState(VK_F6); GetAsyncKeyState(VK_F7); GetAsyncKeyState(VK_F8); GetAsyncKeyState(VK_F9); GetAsyncKeyState(VK_F10); GetAsyncKeyState(VK_F11); GetAsyncKeyState(VK_F12); }
	if (!ignoreArrows) { GetAsyncKeyState(VK_LEFT); GetAsyncKeyState(VK_UP); GetAsyncKeyState(VK_RIGHT); GetAsyncKeyState(VK_DOWN); }
	if (Kb_Key_Tab[0])GetAsyncKeyState(VK_TAB);
	if (Kb_Key_Left_Alt[0])GetAsyncKeyState(VK_LMENU);
	if (Kb_Key_Right_Alt[0])GetAsyncKeyState(VK_RMENU);
	if (Kb_Key_Left_Ctrl[0])GetAsyncKeyState(VK_LCONTROL);
	if (Kb_Key_Right_Ctrl[0])GetAsyncKeyState(VK_RCONTROL);
	if (Kb_Key_Enter[0])GetAsyncKeyState(VK_RETURN);
	if (Kb_Key_Caps[0])GetAsyncKeyState(VK_CAPITAL);
	if (Kb_Key_Grave_Accent[0])GetAsyncKeyState(VK_OEM_3);
	if (Kb_Key_Minus[0])GetAsyncKeyState(VK_OEM_MINUS);
	if (Kb_Key_Equal[0])GetAsyncKeyState(VK_OEM_PLUS);
	if (Kb_Key_Left_Bracket[0])GetAsyncKeyState(VK_OEM_4);
	if (Kb_Key_Right_Bracket[0])GetAsyncKeyState(VK_OEM_6);
	if (Kb_Key_Backslash[0])GetAsyncKeyState(VK_OEM_5);
	if (Kb_Key_Semicolon[0])GetAsyncKeyState(VK_OEM_1);
	if (Kb_Key_Quote[0])GetAsyncKeyState(VK_OEM_7);
	if (Kb_Key_Comma[0])GetAsyncKeyState(VK_OEM_COMMA);
	if (Kb_Key_Period[0])GetAsyncKeyState(VK_OEM_PERIOD);
	if (Kb_Key_Forwardslash[0])GetAsyncKeyState(VK_OEM_2);
	if (!ignoreNumPad) { GetAsyncKeyState(VK_NUMLOCK); GetAsyncKeyState(VK_DIVIDE); GetAsyncKeyState(VK_MULTIPLY); GetAsyncKeyState(VK_SUBTRACT); GetAsyncKeyState(VK_ADD); GetAsyncKeyState(VK_RETURN); GetAsyncKeyState(VK_DECIMAL); GetAsyncKeyState(VK_NUMPAD0); GetAsyncKeyState(VK_NUMPAD1); GetAsyncKeyState(VK_NUMPAD2); GetAsyncKeyState(VK_NUMPAD3); GetAsyncKeyState(VK_NUMPAD4); GetAsyncKeyState(VK_NUMPAD5); GetAsyncKeyState(VK_NUMPAD6); GetAsyncKeyState(VK_NUMPAD7); GetAsyncKeyState(VK_NUMPAD8); GetAsyncKeyState(VK_NUMPAD9); }
//	if (!ignoreNumPad) { if (Kb_Key_Numlock[0]) GetAsyncKeyState(VK_NUMLOCK); if (Kb_Key_Numpad_Divide[0]) GetAsyncKeyState(VK_DIVIDE); if (Kb_Key_Numpad_Multiply[0]) GetAsyncKeyState(VK_MULTIPLY); if (Kb_Key_Numpad_Minus[0]) GetAsyncKeyState(VK_SUBTRACT); if (Kb_Key_Numpad_Add[0]) GetAsyncKeyState(VK_ADD); if (Kb_Key_Numpad_Enter[0]) GetAsyncKeyState(VK_RETURN); if (Kb_Key_Numpad_Period[0]) GetAsyncKeyState(VK_DECIMAL); if (Kb_Key_Numpad_0[0]) GetAsyncKeyState(VK_NUMPAD0); if (Kb_Key_Numpad_1[0]) GetAsyncKeyState(VK_NUMPAD1); if (Kb_Key_Numpad_2[0]) GetAsyncKeyState(VK_NUMPAD2); if (Kb_Key_Numpad_3[0]) GetAsyncKeyState(VK_NUMPAD3); if (Kb_Key_Numpad_4[0]) GetAsyncKeyState(VK_NUMPAD4); if (Kb_Key_Numpad_5[0]) GetAsyncKeyState(VK_NUMPAD5); if (Kb_Key_Numpad_6[0]) GetAsyncKeyState(VK_NUMPAD6); if (Kb_Key_Numpad_7[0]) GetAsyncKeyState(VK_NUMPAD7); if (Kb_Key_Numpad_8[0]) GetAsyncKeyState(VK_NUMPAD8); if (Kb_Key_Numpad_9[0]) GetAsyncKeyState(VK_NUMPAD9); }
	if (Kb_Key_Insert[0]) GetAsyncKeyState(VK_INSERT); if (Kb_Key_Delete[0]) GetAsyncKeyState(VK_DELETE); if (Kb_Key_Home[0]) GetAsyncKeyState(VK_HOME); if (Kb_Key_End[0]) GetAsyncKeyState(VK_END); if (Kb_Key_PgUp[0]) GetAsyncKeyState(VK_PRIOR); if (Kb_Key_PgDn[0]) GetAsyncKeyState(VK_NEXT);
	if (Kb_Key_Menu[0]) GetAsyncKeyState(VK_APPS); //menu
}

static void printDb() {
	wcout << database << "\n";
	wifstream f(database); wstring cell;
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	while (getline(f, cell)) { wcout << cell << endl; }
	f.close(); cout << endl;
}

static wstring loadVar(wstring q = L"") {
	wifstream f(replacerDb); if (!f) { showOutsMsg(L"\nReplacerDb \"", replacerDb, L"\" not found!", 0); return q; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	wstring cell, se; GetAsyncKeyState(VK_ESCAPE); while (getline(f, cell, multiLineDelim[0])) {
		if (!NoEscapeOrPause && GetAsyncKeyState(VK_ESCAPE) || cell.substr(0, 4) == L"<'''") break;
		if (!cell[0] || cell[0] == '\n' || cell[0] == ' ') continue;
		se = cell.substr(0, q.length());
		if (se == q) {
			wstring v = cell.substr(q.length());
			q = v;
			f.close();
			return q;
		}
	}
	q.clear();
	f.close();
	return q;
}

static wstring isVar(wstring &q) { // Replacer | {var} {var:} {var-} {var>} | <r:>
	if (!replacerDb[0]) return q;
	if (q.find('{') != string::npos) {
		wstring tqg = q, tq{};
		GetAsyncKeyState(VK_ESCAPE);
		while (tqg.find('{') != string::npos) {
			if (!NoEscapeOrPause && GetAsyncKeyState(VK_ESCAPE)) break;
			q = q.substr(q.find('{') + 1, q.find(L'}', q.find('{')) - q.find('{') - 1); tq = q;
			if (q > L"") {
				if (multiLineDelim[0] != '\\') { q = regex_replace(q, wregex(L"\n"), L""); q = regex_replace(q, wregex(L"\t"), L""); }
				if (q[0] == '\'' && q != L"'") { tqg.replace(tqg.find('{'), 2 + q.length(), L""); q = tqg; continue; } //{'ignore}
				q = loadVar(q);
			}
			if (q == L"") {
				tqg.replace(tqg.find('{'), 1, L"::_::"); q = tqg;
				continue;
			}
			q = regex_replace(q, wregex(L"\\$"), L":s:_:s:");
			tq = regex_replace(tq, wregex(L"\\\\"), L":b:_:b:");
			tq = regex_replace(tq, wregex(L"\\$"), L"\\$");
			tq = regex_replace(tq, wregex(L"\\["), L"\\[");
			tq = regex_replace(tq, wregex(L"\\]"), L"\\]");
			tq = regex_replace(tq, wregex(L"\\("), L"\\(");
			tq = regex_replace(tq, wregex(L"\\)"), L"\\)");
			tq = regex_replace(tq, wregex(L"\\{"), L"\\{");
			tq = regex_replace(tq, wregex(L"\\}"), L"\\}");
			tq = regex_replace(tq, wregex(L"\\|"), L"\\|");
			tq = regex_replace(tq, wregex(L"\\?"), L"\\?");
			tq = regex_replace(tq, wregex(L"\\+"), L"\\+");
			tq = regex_replace(tq, wregex(L"\\*"), L"\\*");
			tq = regex_replace(tq, wregex(L"\\^"), L"\\^");
			tq = regex_replace(tq, wregex(L"\\."), L"\\.");
			tq = regex_replace(tq, wregex(L":b:_:b:"), L"\\\\");
			tqg = regex_replace(tqg, wregex(L"\\{" + tq + L"\\}"), q);
			q = tqg;
		}
		tqg = regex_replace(tqg, wregex(L"::_::"), L"{"); tqg = regex_replace(tqg, wregex(L":s:_:s:"), L"$"); q = tqg;
	}
	return q;
}

static wstring makeXY() {
	wstring re = L"><shift>,<shift->xy:";
	POINT pt; GetCursorPos(&pt);
	wstring xy = to_wstring(pt.x) + L" " + to_wstring(pt.y);
	re += xy;
	re += L">";
	if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << L"<xy:" + xy + L">\n"; }
	return re;
}

static void scanDb(); static wstring conn(bool bg = 0) {//<connect:>
	bool con = false; wstring qqs = qq.substr(0, qq.find('>') + 1);
	if (qqs.find(io[0]) != std::string::npos || qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		wstring x = L""; x += io[0]; x += L">";
		if (qqs.substr(qqs.length() - 2, 2) == x || qqs.substr(qqs.length() - 2, 2) == L":>" || qqs.substr(qqs.length() - 2, 2) == L"->") {
			con = true;
		}
	}
	if (con) {
		wifstream f(database); wstring cell;
		if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));//properties, general, language standard, >c++14 //_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
		while (getline(f, cell, multiLineDelim[0])) {
			if (cell.substr(0, 4) == L"<'''") break;
			if (qqs == cell.substr(0, qqs.length())) { //<h:> | <h->
				wstring x = cell.substr(qqs.length()), xx = qq.substr(qqs.length());
				if (bg)	return x;
				if (relink) tail = x; else tail = x + xx;
				tail = isVar(tail);
				if (SlightPauseInBetweenConnects) Sleep(150);
				f.close(); i = -1;
				if (speed > 0) sleep = 0;
				re = L" ";//codes
				return L"";
			}
		} f.close(); if (fail) { if (showStrand && !assume) { wcout << "Fail: " << OutTab << OutTab << qqs << endl; } fail = 0; i = tail.length(); return L""; } printq();
	}
	else printq();
	return L"";
}

static void setQxQy(wstring x, size_t z = 0) {
	if (x.find(',') != string::npos) {
		qx = x.substr(z, x.find(','));//x <xy:#,#>
		qy = x.substr(x.find(',') + 1, x.find('>') - x.find(',') - 1);//y
	}
	else if (x.find(' ') != string::npos) {
		qx = x.substr(z, x.find(' '));//x <xy:# #>
		qy = x.substr(x.find(' ') + 1, x.find('>') - x.find(' ') - 1);
	}
	else { qx.clear(), qy.clear(); } //wcout << "x: " << x  << "\nqx: " << qx << "\nqy: " << qy << endl;
}

static void kbPress(Multi multi, wstring s, short key) {
	if (multiStrand) qq = multi.q;
	if (qq.find('>') == std::string::npos) { printq(); return; }
	wstring n = s;
	if (qq[n.length()] == '>') star_num = L"1";
	else {
		n = qq.substr(n.length(), qq.find('>') - n.length());
		if (n[0] == ':') n = n.substr(1);
		if (n[0] == ' ') n = n.substr(1);
		if ((qq[qq.find('>') - 1] == io[0] || qq.substr(qq.find('>') - 1, 1) == L":" || qq.substr(qq.find('>') - 1, 1) == L"-") && n[0] != '<') { conn(); return; }
		if (n > L"") {
			if (n[0] == '*') n = n.substr(1, n.length()); //case: <f1*
			else if (n[0] == '+') { if (n[1] == '+') { ++ic; } n = to_wstring(ic); } //<f1+> | <f1++> | Variable press <key<+>>
			n = check_if_num(n);
			if (n == L"") { printq(); return; }
			if (n[0] == '<') {//Assume
				if (n[n.length() - 1] == io[0] || n[n.length() - 1] == ':' || n[n.length() - 1] == '-') {//<x:>
					wstring t = qq;
					qq = n + L">";
					n = conn(1);
					qq = t;
				}
				if (n.substr(1, 5) == L"rand:") {//x:<rand:0,5> | <up{x:}>
					setQxQy(n, 6);
					n = randn(1);
				}
				if (multiStrand) i = multi.i_;
				if (n != L"0") i += 1;
				if (n == L"0") { i += qq.find('>'); if (multiStrand) { multi.i_ = i; } return; }
			}
			star_num = n;
			if (n[0] == '{' || !(stoi(n) > 0)) { printq(); return; };
		}
		else { printq(); return; }
	}
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD; ip[0].ki.wVk = key;
	if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_HOME || key == VK_END) ip[0].ki.dwFlags = 1; else ip[0].ki.dwFlags = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = 2;
	auto sn = stoi(star_num);
	for (int j = 0; j < sn; ++j) {
		GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
		if (s.length() == 3) {
			if (s == L"<lc") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
			else if (s == L"<rc") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
			else if (s == L"<mc") { mouseEvent(MOUSEEVENTF_MIDDLEDOWN); mouseEvent(MOUSEEVENTF_MIDDLEUP); }
			else if (s == L"<sd" || s == L"<sr" || s == L"<su" || s == L"<sl") mouseEvent(MOUSEEVENTF_HWHEEL);
			else SendInput(2, ip, sizeof(ip[0]));
		}
		else SendInput(2, ip, sizeof(ip[0]));
		GetAsyncKeyState(key);
		if (speed > 0 && sn != j + 1) Sleep(speed);
	}
	if (multiStrand) { i = multi.i_; qq = multi.q; }
	i += qq.find('>');
	if (multiStrand) multi.i_ = i;
}

static void out(wstring ai) { re = L">" + ai; strand.clear(); scanDb(); re.clear(); }

static void loadSe() {
	wifstream f(settings); if (!f) { showOutsMsg(L"\nSettings \"", settings, L"\" not found!", 0); if (!settings[0]) { cout << "Create c:\\dna\\se.txt manually\n"; } return; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	wstring cell; while (getline(f, cell)) {
		if (!cell[0] || cell[0] == ' ') continue;
		wstring se = cell.substr(0, cell.find_first_of(L":\t ")); se += ':';
		wstring v = (cell.substr(cell.find_first_of(L":\t ") + 1)); if (v.find_first_not_of(L"\t ") == string::npos) {//""
			if (v != L" ") v.clear();
		} if (se == cell + L":") v.clear();
		if (v[0] && v != L" ") v = v.substr(v.find_first_not_of(L"\t "));
		int x = 0; for (size_t i = 0; i <= se.length(); ++i) x += se[i];
		if (v[0] == '>' && se.substr(0, 7) == L"Kb_Key_") {//set Kb_QQ_k
			wstring s = se.substr(7);
			if (s.length() > 2 || v[0] == '>') {
				{ auto x = v.substr(1, v.find(' ') - 1); auto l = x.length(); bool b = x[0] < 127; qqLen = l > 0 && b ? l + 1 : b ? 1 : l / 2 + 1; } //Kb_Key_Comma >,, '<bs>
				int x = 0; for (size_t i = 0; i <= s.length() - 2; ++i) x += s[i];
				switch (x) {
				case 391://Caps
					Kb_QQ_k = VK_CAPITAL;
					break;
				case 283://Esc
					Kb_QQ_k = VK_ESCAPE;
					break;
				case 779://Left_Alt
					Kb_QQ_k = VK_LMENU;
					break;
				case 894://Right_Alt
					Kb_QQ_k = VK_RMENU;
					break;
				case 493://Comma
					Kb_QQ_k = VK_OEM_COMMA;
					break;
				default: qqLen = v.find_first_of(' ');
				}
			}
			else
				Kb_QQ_k = (short)se[se.length() - 2];
		}
		auto er = [se, v]() { showOutsMsg(L"Error in ", settings, L" [" + se + L" " + v + L"]", 0); };
		switch (x) {
			case 1536://RSHIFT+LSHIFT_Only:
				{ if (check_if_num(v) > L"") { RSHIFTLSHIFT_Only = stoi(v); rri = 0; } else er(); } break;
			case 1261://LSHIFT+CtrlKey:
				{ if (check_if_num(v) > L"") LSHIFTCtrlKey = stoi(v); else er(); } break;
			case 1972://RSHIFT+CtrlKey_Toggle:
				{ if (check_if_num(v) > L"") RSHIFTCtrlKeyToggle = stoi(v); else er(); } break;
			case 1273://ManualRepeat:
				{ if (v == L"0" || v == L"1") ManualRepeat = stoi(v); else er(); } break;
			case 959://AutoBs_io:
				{ if (v == L"0" || v == L"1") io_Auto_BS = stoi(v); else er(); } break;
			case 274://io:
				{ if (!v[0]) { v[0] = ' '; } io = v; } break;
			case 2738://ShowMultiStrandElapsedOnly:
				{ if (v == L"0" || v == L"1") showMultiStrandElapsedOnly = stoi(v); else er(); } break;
			case 865://PauseKey:
				{ if (check_if_num(v) > L"") PauseKey = stoi(v); else er(); } break;
			case 1543://NoEscapeOrPause:
				{ if (v == L"0" || v == L"1") { NoEscapeOrPause = stoi(v); GetAsyncKeyState(VK_ESCAPE); } else er(); } break;
			case 1708://Loop_Insert_Text:
				{ if (!v[0]) { v[0] = '>'; } if (v[v.length() - 1] != '>') v += '>'; Loop_Insert_Text = v; } break;
			case 1946://Kb_Key_Print_Screen:
				Kb_Key_Print_Screen = v; break;
			case 783://Kb_Key_A:
				Kb_Key_A = v; break;
			case 784://Kb_Key_B:
				Kb_Key_B = v; break;
			case 785://Kb_Key_C:
				Kb_Key_C = v; break;
			case 786://Kb_Key_D:
				Kb_Key_D = v; break;
			case 787://Kb_Key_E:
				Kb_Key_E = v; break;
			case 788://Kb_Key_F:
				Kb_Key_F = v; break;
			case 789://Kb_Key_G:
				Kb_Key_G = v; break;
			case 790://Kb_Key_H:
				Kb_Key_H = v; break;
			case 791://Kb_Key_I:
				Kb_Key_I = v; break;
			case 792://Kb_Key_J:
				Kb_Key_J = v; break;
			case 793://Kb_Key_K:
				Kb_Key_K = v; break;
			case 794://Kb_Key_L:
				Kb_Key_L = v; break;
			case 795://Kb_Key_M:
				Kb_Key_M = v; break;
			case 796://Kb_Key_N:
				Kb_Key_N = v; break;
			case 797://Kb_Key_O:
				Kb_Key_O = v; break;
			case 798://Kb_Key_P:
				Kb_Key_P = v; break;
			case 799://Kb_Key_Q:
				Kb_Key_Q = v; break;
			case 800://Kb_Key_R:
				Kb_Key_R = v; break;
			case 801://Kb_Key_S:
				Kb_Key_S = v; break;
			case 802://Kb_Key_T:
				Kb_Key_T = v; break;
			case 803://Kb_Key_U:
				Kb_Key_U = v; break;
			case 804://Kb_Key_V:
				Kb_Key_V = v; break;
			case 805://Kb_Key_W:
				Kb_Key_W = v; break;
			case 806://Kb_Key_X:
				Kb_Key_X = v; break;
			case 807://Kb_Key_Y:
				Kb_Key_Y = v; break;
			case 808://Kb_Key_Z:
				Kb_Key_Z = v; break;
			case 766://Kb_Key_0:
				Kb_Key_0 = v; break;
			case 767://Kb_Key_1:
				Kb_Key_1 = v; break;
			case 768://Kb_Key_2:
				Kb_Key_2 = v; break;
			case 769://Unicode: | //Kb_Key_3:
				{ if (se == L"Unicode:") { if (v == L"0" || v == L"1") Unicode = stoi(v); else er(); }
				else if (se == L"Kb_Key_3:") Kb_Key_3 = v;
				} break;
			case 770://Kb_Key_4:
				Kb_Key_4 = v; break;
			case 771://Kb_Key_5:
				Kb_Key_5 = v; break;
			case 772://Kb_Key_6:
				Kb_Key_6 = v; break;
			case 773://Kb_Key_7:
				Kb_Key_7 = v; break;
			case 774://Kb_Key_8:
				Kb_Key_8 = v; break;
			case 775://Kb_Key_9:
				Kb_Key_9 = v; break;
			case 837://Kb_Key_F1:
				Kb_Key_F1 = v; break;
			case 838://Kb_Key_F2:
				Kb_Key_F2 = v; break;
			case 839://Kb_Key_F3:, EditorDb:
				{ if (se == L"EditorDb:") editorDb = v;
				else if (se == L"Kb_Key_F3:") Kb_Key_F3 = v;
				} break;
			case 840://Kb_Key_F4:
				Kb_Key_F4 = v; break;
			case 841://Kb_Key_F5:
				Kb_Key_F5 = v; break;
			case 842://Kb_Key_F6:
				Kb_Key_F6 = v; break;
			case 843://Kb_Key_F7:
				Kb_Key_F7 = v; break;
			case 844://Kb_Key_F8:
				Kb_Key_F8 = v; break;
			case 845://Kb_Key_F9:
				Kb_Key_F9 = v; break;
			case 885://Kb_Key_F10:
				Kb_Key_F10 = v; break;
			case 886://Kb_Key_F11:
				Kb_Key_F11 = v; break;
			case 887://Kb_Key_F12:
				Kb_Key_F12 = v; break;
			case 1113://Kb_Key_Left:
				Kb_Key_Left = v; break;
			case 1126://Kb_Key_Down:
				Kb_Key_Down = v; break;
			case 1210://Kb_Key_Space:
				Kb_Key_Space = v; break;
			case 1718://Kb_Key_Left_Shift:
				Kb_Key_Left_Shift = v; break;
			case 1833://Kb_Key_Right_Shift:
				Kb_Key_Right_Shift = v; break;
			case 1497://Kb_Key_Left_Alt:
				Kb_Key_Left_Alt = v; break;
			case 1612://Kb_Key_Right_Alt:
				Kb_Key_Right_Alt = v; break;
			case 1613://Kb_Key_Left_Ctrl:
				Kb_Key_Left_Ctrl = v; break;
			case 1728://Kb_Key_Right_Ctrl:
				Kb_Key_Right_Ctrl = v; break;
			case 1228://Kb_Key_Enter: | Kb_Key_Right:
				{ if (se == L"Kb_Key_Enter:") Kb_Key_Enter = v;
				else if (se == L"Kb_Key_Right:") Kb_Key_Right = v;
				} break;
			case 1109://Kb_Key_Caps:
				Kb_Key_Caps = v; break;
			case 1904://Kb_Key_Grave_Accent:
				Kb_Key_Grave_Accent = v; break;
			case 1242://Kb_Key_Minus:
				Kb_Key_Minus = v; break;
			case 1222://Kb_Key_Equal:
				Kb_Key_Equal = v; break;
			case 1908://Kb_Key_Left_Bracket:
				Kb_Key_Left_Bracket = v; break;
			case 1626://Kb_Key_Backslash:
				Kb_Key_Backslash = v; break;
			case 1655://Kb_Key_Semicolon:
				Kb_Key_Semicolon = v; break;
			case 1244://Kb_Key_Quote:
				Kb_Key_Quote = v; break;
			case 1211://Kb_Key_Comma:
				Kb_Key_Comma = v; break;
			case 1329://Kb_Key_Period:
				Kb_Key_Period = v; break;
			case 1982://Kb_Key_Forwardslash:
				Kb_Key_Forwardslash = v; break;
			case 1123://Kb_Key_Menu:
				Kb_Key_Menu = v; break;
			case 1347://Kb_Key_Insert:
				Kb_Key_Insert = v; break;
			case 1111://Kb_Key_Home:
				Kb_Key_Home = v; break;
			case 997://Kb_Key_End: | Kb_Key_Tab:
				{ if (se == L"Kb_Key_End:") Kb_Key_End = v;
				else if (se == L"Kb_Key_Tab:") Kb_Key_Tab = v;
				} break;
			case 1079://Kb_Key_PgDn:
				Kb_Key_PgDn = v; break;
			case 1474://Kb_Key_Numpad_0:
				Kb_Key_Numpad_0 = v; break;
			case 1475://Kb_Key_Numpad_1:
				Kb_Key_Numpad_1 = v; break;
			case 1476://Kb_Key_Numpad_2:
				Kb_Key_Numpad_2 = v; break;
			case 1477://Kb_Key_Numpad_3:
				Kb_Key_Numpad_3 = v; break;
			case 1478://Kb_Key_Numpad_4:
				Kb_Key_Numpad_4 = v; break;
			case 1479://Kb_Key_Numpad_5:
				Kb_Key_Numpad_5 = v; break;
			case 1480://Kb_Key_Numpad_6:
				Kb_Key_Numpad_6 = v; break;
			case 1481://Kb_Key_Numpad_7:
				Kb_Key_Numpad_7 = v; break;
			case 1482://Kb_Key_Numpad_8:
				Kb_Key_Numpad_8 = v; break;
			case 1483://Kb_Key_Numpad_9:
				Kb_Key_Numpad_9 = v; break;
			case 1447://Kb_Key_Numlock:
				Kb_Key_Numlock = v; break;
			case 2023://Kb_Key_Numpad_Divide: | Kb_Key_Right_Bracket:
				{if (se == L"Kb_Key_Numpad_Divide:") Kb_Key_Numpad_Divide = v;
				else if (se == L"Kb_Key_Right_Bracket:") Kb_Key_Right_Bracket = v;
				} break;
			case 2290://Kb_Key_Numpad_Multiply:
				Kb_Key_Numpad_Multiply = v; break;
			case 1950://Kb_Key_Numpad_Minus:
				Kb_Key_Numpad_Minus = v; break;
			case 1691://Kb_Key_Numpad_Add:
				Kb_Key_Numpad_Add = v; break;
			case 2037://Kb_Key_Numpad_Period:
				Kb_Key_Numpad_Period = v; break;
			case 1936://Kb_Key_Numpad_Enter:
				Kb_Key_Numpad_Enter = v; break;
			case 2066://DbMultiLineDelimiter:
				multiLineDelim = v[0] != '\\' ? v[0] : L'\n'; break;
			case 764://OutTabs:
				{ if (v == L"0" || v == L"1") { OutTabs = stoi(v); OutTab = OutTabs ? L"\t" : L""; } else er(); } break;
			case 1462://ClearStrandKey:
				{ if (check_if_num(v) > L"") ClearStrandKey = stoi(v); else er(); } break;
			case 1056://CommaSleep:
				{ if (check_if_num(v) > L"") { if (stoi(v) <= 0) { v = L"1"; } CommaSleep = stoi(v); } else er(); } break;
			case 673://Editor:
				editor = v; break;
			case 722://Editor1:
				editor1 = v; break;
			case 857://EditorSe:
				editorSe = v; break;
			case 680://Assume:
				{ if (v == L"0" || v == L"1") assume = stoi(v); else er(); } break;
			case 1095://ShowStrand:
				{ if (v == L"0" || v == L"1") showStrand = stoi(v); else er(); } break;
			case 847://Database:
				{ if (v.length() > 0) { database = v; database = regex_replace(database, wregex(L"/"), L"\\"); db = database.substr(database.find_last_of('\\') + 1) + L" - "; } else er(); } break;
			case 1038://ReplacerDb:
				replacerDb = v; break;
			case 1313://OutsTemplate: | Kb_Key_Delete:
				{ if (se == L"OutsTemplate:") OutsTemplate = v;
				else if (se == L"Kb_Key_Delete:") Kb_Key_Delete = v;
				} break;
			case 1354://CloseCtrlMode:
				{ if (v == L"0" || v == L"1") close_ctrl_mode = stoi(v); else er(); } break;
			case 1659://CtrlScanOnlyMode:
				{ if (v == L"0" || v == L"1") qScanOnly = stoi(v); else er(); } break;
			case 1677://StrandLengthMode:
				{ if (check_if_num(v) > L"") strandLengthMode = stoi(v); else er(); } break;
			case 965://Ignore_A-Z:
				{ if (v == L"0" || v == L"1") ignoreAZ = stoi(v); else er(); } break;
			case 915://Ignore_0-9: | Kb_Key_Up:
				{ if (se == L"Ignore_0-9:") { if (v == L"0" || v == L"1") ignore09 = stoi(v); else er(); }
				else if (se == L"Kb_Key_Up:")Kb_Key_Up = v;
				} break;
			case 1172://StartHidden:
				{ if (v == L"0" || v == L"1") startHidden = stoi(v); else er(); } break;
			case 760://CtrlKey: (vk_enum max)
				{ if (v.find(' ') != string::npos) {
					wstring max = v.substr(v.find(' ') + 1); if (max.find(' ') != string::npos || max[0] == 0) { er(); break; }
					v = v.substr(0, v.find(' ')); 
					cKeyMax = max == L"1" ? 3 : stoi(max);
				} else cKeyMax = 1;
				cKey = stoi(v); } break;
			case 999://ShowIntro:
				{ if (v == L"0" || v == L"1") showIntro = stoi(v); else er(); } break;
			case 1324://ShowSettings:
				{ if (v == L"0" || v == L"1") showSettings = stoi(v); else er(); } break;
			case 1004://Frequency:
				{ if (check_if_num(v) > L"") frequency = stoi(v); else er(); } break;
			case 964://RepeatKey:
				{ if (check_if_num(v) > L"") reKey = stoi(v); else er(); } break;
			case 1649://AutoBs_RepeatKey:
				{ if (v == L"0" || v == L"1") AutoBs_RepeatKey = stoi(v); else er(); } break;
			case 2913://SlightPauseInBetweenConnects:
				{ if (v == L"0" || v == L"1") SlightPauseInBetweenConnects = stoi(v); else er(); } break;
			case 1571://CloseCtrlSpacer:
				{ if (check_if_num(v) > L"") { if (stoi(v) <= 0) { v = L"1"; } CloseCtrlSpacer = stoi(v); } else er(); } break;
			case 1467://RgbScaleLayout:
				{ if (check_if_num(v) > L"") RgbScaleLayout = stod(v); else er(); } break;
			case 1201://MultiStrand:
				{ if (v == L"0" || v == L"1") multiStrand = stoi(v); else er(); } break;
			case 1098://AutoBs_EscH: | Ignore_F1-F12: | Kb_Key_PgUp:
				{ if (se == L"AutoBs_EscH:") { if (v == L"0" || v == L"1") EscHAutoBs = stoi(v); else er(); }
				else if (se == L"Ignore_F1-F12:") { if (v == L"0" || v == L"1") ignoreF1s = stoi(v); else er(); }
				else if (se == L"Kb_Key_PgUp:") Kb_Key_PgUp = v;
				} break;
			case 1519://AutoBs_EscComma:
				{ if (v == L"0" || v == L"1") EscCommaAutoBs = stoi(v); else er(); } break;
			case 1530://AutoBs_EscEqual:
				{ if (v == L"0" || v == L"1") EscEqualAutoBs = stoi(v); else er(); } break;
			case 1723://SeHotReload_CtrlS:
				{ if (v == L"0" || v == L"1") SeHotReload_CtrlS = stoi(v); else er(); } break;
			case 2098://SeDbClearStrand_CtrlS:
				{ if (v == L"0" || v == L"1") SeDbClearStrand_CtrlS = stoi(v); else er(); } break;
			case 1403://Ignore_Arrows:
				{ if (v == L"0" || v == L"1") ignoreArrows = stoi(v); else er(); } break;
			case 1001://Kb_Key_Esc:
				Kb_Key_Esc = v; break;
			case 1346://Ignore_NumPad:
				{ if (v == L"0" || v == L"1") ignoreNumPad = stoi(v); else er(); } break;
			case 934://Exit_EscX:
				{ if (v == L"0" || v == L"1") enableEscX = stoi(v); else er(); } break;
		}
		if (Kb_Key_Print_Screen[0] || Kb_Key_Space[0] || Kb_Key_Tab[0] || Kb_Key_Left_Shift[0] || Kb_Key_Right_Shift[0] || Kb_Key_Left_Ctrl[0] || Kb_Key_Right_Ctrl[0] || Kb_Key_Enter[0] || Kb_Key_Caps[0] || Kb_Key_Grave_Accent[0] || Kb_Key_Minus[0] || Kb_Key_Equal[0] || Kb_Key_Left_Bracket[0] || Kb_Key_Right_Bracket[0] || Kb_Key_Backslash[0] || Kb_Key_Semicolon[0] || Kb_Key_Quote[0] || Kb_Key_Comma[0] || Kb_Key_Period[0] || Kb_Key_Forwardslash[0] || Kb_Key_Menu[0] || Kb_Key_Insert[0] || Kb_Key_Delete[0] || Kb_Key_Home[0] || Kb_Key_End[0] || Kb_Key_PgUp[0] || Kb_Key_PgDn[0])
			ignoreOtherKeys = 0;
		else
			ignoreOtherKeys = 1;
	}
	f.close();
 }

static void printSe() {
	loadSe();
	if (showSettings) {
		if (qq[1] == 'S') return;
		wcout << settings << '\n'; ifstream f(settings); if (f.fail()) { showOutsMsg(L"Copy to ", settings, L"\n", 1); }
		cout << "ShowSettings: " << showSettings << '\n';
		cout << "ShowIntro: " << showIntro << '\n';
		cout << "ShowStrand: " << showStrand << '\n';
		cout << "ClearStrandKey: " << ClearStrandKey << '\n';
		cout << "MultiStrand: " << multiStrand << '\n';
		cout << "ShowMultiStrandElapsedOnly: " << showMultiStrandElapsedOnly << '\n';
		wcout << "OutsTemplate: " << OutsTemplate << '\n';
		wcout << "OutTabs: " << OutTabs << '\n';
		wcout << "Settings: " << settings << '\n';
		wcout << "Database: " << database << '\n';
		cout << "DbMultiLineDelimiter: "; if (multiLineDelim[0] == '\n') cout << "\\n\n"; else showOutsMsg(L"", multiLineDelim, L"\n", 1);
		wcout << "ReplacerDb: " << replacerDb << '\n';
		cout << "CtrlKey: " << cKey << ' ' << cKeyMax << '\n';
		cout << "LSHIFT+CtrlKey: " << LSHIFTCtrlKey << '\n';
		cout << "CloseCtrlMode: " << close_ctrl_mode << '\n';
		cout << "CloseCtrlSpacer: " << CloseCtrlSpacer << '\n';
		cout << "RSHIFT+CtrlKey_Toggle: " << RSHIFTCtrlKeyToggle << '\n';
		cout << "CtrlScanOnlyMode: " << qScanOnly << '\n';
		cout << "RSHIFT+LSHIFT_Only: " << RSHIFTLSHIFT_Only << '\n';
		cout << "StrandLengthMode: " << strandLengthMode << '\n';
		cout << "RepeatKey: " << reKey << '\n';
		cout << "PauseKey: " << PauseKey << '\n';
		cout << "RgbScaleLayout: " << RgbScaleLayout << '\n';
		cout << "Frequency: " << frequency << '\n';
		cout << "Ignore_0-9: " << ignore09 << '\n';
		wcout << "Kb_Key_0: " << Kb_Key_0 << '\n';
		wcout << "Kb_Key_1: " << Kb_Key_1 << '\n';
		wcout << "Kb_Key_2: " << Kb_Key_2 << '\n';
		wcout << "Kb_Key_3: " << Kb_Key_3 << '\n';
		wcout << "Kb_Key_4: " << Kb_Key_4 << '\n';
		wcout << "Kb_Key_5: " << Kb_Key_5 << '\n';
		wcout << "Kb_Key_6: " << Kb_Key_6 << '\n';
		wcout << "Kb_Key_7: " << Kb_Key_7 << '\n';
		wcout << "Kb_Key_8: " << Kb_Key_8 << '\n';
		wcout << "Kb_Key_9: " << Kb_Key_9 << '\n';
		cout << "Ignore_A-Z: " << ignoreAZ << '\n';
		wcout << "Kb_Key_A: " << Kb_Key_A << '\n';
		wcout << "Kb_Key_B: " << Kb_Key_B << '\n';
		wcout << "Kb_Key_C: " << Kb_Key_C << '\n';
		wcout << "Kb_Key_D: " << Kb_Key_D << '\n';
		wcout << "Kb_Key_E: " << Kb_Key_E << '\n';
		wcout << "Kb_Key_F: " << Kb_Key_F << '\n';
		wcout << "Kb_Key_G: " << Kb_Key_G << '\n';
		wcout << "Kb_Key_H: " << Kb_Key_H << '\n';
		wcout << "Kb_Key_I: " << Kb_Key_I << '\n';
		wcout << "Kb_Key_J: " << Kb_Key_J << '\n';
		wcout << "Kb_Key_K: " << Kb_Key_K << '\n';
		wcout << "Kb_Key_L: " << Kb_Key_L << '\n';
		wcout << "Kb_Key_M: " << Kb_Key_M << '\n';
		wcout << "Kb_Key_N: " << Kb_Key_N << '\n';
		wcout << "Kb_Key_O: " << Kb_Key_O << '\n';
		wcout << "Kb_Key_P: " << Kb_Key_P << '\n';
		wcout << "Kb_Key_Q: " << Kb_Key_Q << '\n';
		wcout << "Kb_Key_R: " << Kb_Key_R << '\n';
		wcout << "Kb_Key_S: " << Kb_Key_S << '\n';
		wcout << "Kb_Key_T: " << Kb_Key_T << '\n';
		wcout << "Kb_Key_U: " << Kb_Key_U << '\n';
		wcout << "Kb_Key_V: " << Kb_Key_V << '\n';
		wcout << "Kb_Key_W: " << Kb_Key_W << '\n';
		wcout << "Kb_Key_X: " << Kb_Key_X << '\n';
		wcout << "Kb_Key_Y: " << Kb_Key_Y << '\n';
		wcout << "Kb_Key_Z: " << Kb_Key_Z << '\n';
		cout << "Ignore_Arrows: " << ignoreArrows << '\n';
		wcout << "Kb_Key_Left: " << Kb_Key_Left << '\n';
		wcout << "Kb_Key_Up: " << Kb_Key_Up << '\n';
		wcout << "Kb_Key_Right: " << Kb_Key_Right << '\n';
		wcout << "Kb_Key_Down: " << Kb_Key_Down << '\n';
		wcout << "Kb_Key_Backslash: " << Kb_Key_Backslash << '\n';
		wcout << "Kb_Key_Caps: " << Kb_Key_Caps << '\n';
		wcout << "Kb_Key_Comma: " << Kb_Key_Comma << '\n';
		wcout << "Kb_Key_Delete: " << Kb_Key_Delete << '\n';
		wcout << "Kb_Key_End: " << Kb_Key_End << '\n';
		wcout << "Kb_Key_Enter: " << Kb_Key_Enter << '\n';
		wcout << "Kb_Key_Equal: " << Kb_Key_Equal << '\n';
		wcout << "Kb_Key_Esc: " << Kb_Key_Esc << '\n';
		cout << "Ignore_F1-F12: " << ignoreF1s << '\n';
		wcout << "Kb_Key_F1: " << Kb_Key_F1 << '\n';
		wcout << "Kb_Key_F2: " << Kb_Key_F2 << '\n';
		wcout << "Kb_Key_F3: " << Kb_Key_F3 << '\n';
		wcout << "Kb_Key_F4: " << Kb_Key_F4 << '\n';
		wcout << "Kb_Key_F5: " << Kb_Key_F5 << '\n';
		wcout << "Kb_Key_F6: " << Kb_Key_F6 << '\n';
		wcout << "Kb_Key_F7: " << Kb_Key_F7 << '\n';
		wcout << "Kb_Key_F8: " << Kb_Key_F8 << '\n';
		wcout << "Kb_Key_F9: " << Kb_Key_F9 << '\n';
		wcout << "Kb_Key_F10: " << Kb_Key_F10 << '\n';
		wcout << "Kb_Key_F11: " << Kb_Key_F11 << '\n';
		wcout << "Kb_Key_F12: " << Kb_Key_F12 << '\n';
		wcout << "Kb_Key_Print_Screen: " << Kb_Key_Print_Screen << '\n';
		wcout << "Kb_Key_Forwardslash: " << Kb_Key_Forwardslash << '\n';
		wcout << "Kb_Key_Grave_Accent: " << Kb_Key_Grave_Accent << '\n';
		wcout << "Kb_Key_Home: " << Kb_Key_Home << '\n';
		wcout << "Kb_Key_Insert: " << Kb_Key_Insert << '\n';
		wcout << "Kb_Key_Left_Alt: " << Kb_Key_Left_Alt << '\n';
		wcout << "Kb_Key_Left_Bracket: " << Kb_Key_Left_Bracket << '\n';
		wcout << "Kb_Key_Left_Ctrl: " << Kb_Key_Left_Ctrl << '\n';
		wcout << "Kb_Key_Left_Shift: " << Kb_Key_Left_Shift << '\n';
		wcout << "Kb_Key_Menu: " << Kb_Key_Menu << '\n';
		wcout << "Kb_Key_Minus: " << Kb_Key_Minus << '\n';
		cout << "Ignore_NumPad: " << ignoreNumPad << '\n';
		wcout << "Kb_Key_Numpad_0: " << Kb_Key_Numpad_0 << '\n';
		wcout << "Kb_Key_Numpad_1: " << Kb_Key_Numpad_1 << '\n';
		wcout << "Kb_Key_Numpad_2: " << Kb_Key_Numpad_2 << '\n';
		wcout << "Kb_Key_Numpad_3: " << Kb_Key_Numpad_3 << '\n';
		wcout << "Kb_Key_Numpad_4: " << Kb_Key_Numpad_4 << '\n';
		wcout << "Kb_Key_Numpad_5: " << Kb_Key_Numpad_5 << '\n';
		wcout << "Kb_Key_Numpad_6: " << Kb_Key_Numpad_6 << '\n';
		wcout << "Kb_Key_Numpad_7: " << Kb_Key_Numpad_7 << '\n';
		wcout << "Kb_Key_Numpad_8: " << Kb_Key_Numpad_8 << '\n';
		wcout << "Kb_Key_Numpad_9: " << Kb_Key_Numpad_9 << '\n';
		wcout << "Kb_Key_Numlock: " << Kb_Key_Numlock << '\n';
		wcout << "Kb_Key_Numpad_Divide: " << Kb_Key_Numpad_Divide << '\n';
		wcout << "Kb_Key_Numpad_Multiply: " << Kb_Key_Numpad_Multiply << '\n';
		wcout << "Kb_Key_Numpad_Minus: " << Kb_Key_Numpad_Minus << '\n';
		wcout << "Kb_Key_Numpad_Add: " << Kb_Key_Numpad_Add << '\n';
		wcout << "Kb_Key_Numpad_Period: " << Kb_Key_Numpad_Period << '\n';
		wcout << "Kb_Key_Numpad_Enter: " << Kb_Key_Numpad_Enter << '\n';
		wcout << "Kb_Key_Period: " << Kb_Key_Period << '\n';
		wcout << "Kb_Key_PgDn: " << Kb_Key_PgDn << '\n';
		wcout << "Kb_Key_PgUp: " << Kb_Key_PgUp << '\n';
		wcout << "Kb_Key_Quote: " << Kb_Key_Quote << '\n';
		wcout << "Kb_Key_Right_Alt: " << Kb_Key_Right_Alt << '\n';
		wcout << "Kb_Key_Right_Bracket: " << Kb_Key_Right_Bracket << '\n';
		wcout << "Kb_Key_Right_Ctrl: " << Kb_Key_Right_Ctrl << '\n';
		wcout << "Kb_Key_Right_Shift: " << Kb_Key_Right_Shift << '\n';
		wcout << "Kb_Key_Semicolon: " << Kb_Key_Semicolon << '\n';
		wcout << "Kb_Key_Space: " << Kb_Key_Space << '\n';
		wcout << "Kb_Key_Tab: " << Kb_Key_Tab << '\n';
		cout << "StartHidden: " << startHidden << '\n';
		cout << "SlightPauseInBetweenConnects: " << SlightPauseInBetweenConnects << '\n';
		cout << "CommaSleep: " << CommaSleep << '\n';
		cout << "AutoBs_EscH: " << EscHAutoBs << '\n';
		cout << "AutoBs_EscComma: " << EscCommaAutoBs << '\n';
		cout << "AutoBs_EscEqual: " << EscEqualAutoBs << '\n';
		cout << "AutoBs_RepeatKey: " << AutoBs_RepeatKey << '\n';
		cout << "SeHotReload_CtrlS: " << SeHotReload_CtrlS << '\n';
		cout << "SeDbClearStrand_CtrlS: " << SeDbClearStrand_CtrlS << '\n';
		cout << "Assume: " << assume << '\n';
		cout << "Unicode: " << Unicode << '\n';
		wcout << "Editor: " << editor << '\n';
		wcout << "Editor1: " << editor1 << '\n';
		wcout << "EditorDb: "; showOutsMsg(editorDb, L"", L"", 0);
		wcout << "EditorSe: "; showOutsMsg(editorSe, L"", L"", 0);
		wcout << "Loop_Insert_Text: " << Loop_Insert_Text << '\n';
		cout << "NoEscapeOrPause: " << NoEscapeOrPause << '\n';
		wcout << "io: " << io << '\n';
		wcout << "AutoBs_io: " << io_Auto_BS << '\n';
		wcout << "ManualRepeat: " << ManualRepeat << '\n';
		cout << "Exit_EscX: " << enableEscX << '\n';
		cout << endl;
	}
}

static void toggle_visibility() {
	if (IsWindowVisible(GetConsoleWindow())) {
		SetForegroundWindow(GetConsoleWindow());
		kb(VK_F12);//if title "Select dnaspider"
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		Sleep(150); out(L"<alt><esc><alt-><,1>");
	}
	else {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		SetForegroundWindow(GetConsoleWindow());
	}
	Sleep(150);
	strand = L"";
}

static wstring getAppT() {
	HWND h = GetForegroundWindow();
	int l = GetWindowTextLength(h);
	wstring title(l, 0);
	GetWindowTextW(h, &title[0], l + 1);
	title = regex_replace(title, wregex(L","), L"\\,"); title = regex_replace(title, wregex(L">"), L"\\g");	title = regex_replace(title, wregex(L"\\|"), L"\\|"); title = regex_replace(title, wregex(L"&"), L"\\&");
	return title;
}

static wstring makeApp() {
	wstring re = L"", x = L"><shift>,<shift->app:";
	out(L"<alt><esc><alt-><,1>");
	x += getAppT();
	out(L"<shift><alt><esc><alt-><shift->");
	re = x + (Loop_Insert_Text > L"" ? Loop_Insert_Text : L">");
	return re;
}

static wstring getRGB(bool b = 0, bool bg = 0) {
	POINT pt; GetCursorPos(&pt); COLORREF color; HDC hDC;
	hDC = GetDC(NULL);
	if (hDC != NULL) {
		auto x = pt.x, y = pt.y; bool rs = 0;
		if (bg) {
			rs = 1;
			if (qq[6] == '>' || qq[6] == ':') Sleep(3000); else { Sleep(1000 * stoi(qq.substr(6, qq.length() - 1))); }
		}
		color = GetPixel(hDC, int(x * RgbScaleLayout), int(y * RgbScaleLayout));
		ReleaseDC(NULL, hDC);
		if (color != CLR_INVALID) {
			wstring c = to_wstring(GetRValue(color)) + L" " + to_wstring(GetGValue(color)) + L" " + to_wstring(GetBValue(color));//cb
			if (b) {
				if (rs) {//rshift+r+esc
					wstring r = L""; 
					if (GetAsyncKeyState(VK_RSHIFT) || qq[6] == ':') r += L"<RGB~:";
					r += (c + L" " + to_wstring(x) + L" " + to_wstring(y));
					if (GetAsyncKeyState(VK_RSHIFT) || qq[6] == ':') r += Loop_Insert_Text > L"" ? Loop_Insert_Text : L">";
					cbSet(r);
					return L"";
				}
				qx = to_wstring(x); qy = to_wstring(y);
				return c;
			}
			if (GetAsyncKeyState(VK_LSHIFT))
				tail = L"><shift>,<shift->rgb:" + c + L" " + to_wstring(x) + L" " + to_wstring(y) + (Loop_Insert_Text > L"" ? Loop_Insert_Text : L">");
			else
				tail = L"><shift>,<shift->rgb:" + c + (Loop_Insert_Text > L"" ? Loop_Insert_Text : L">");
			re = tail;
		}
	}
	return L"";
}

static wstring makeRGB() {
	getRGB();
	if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << "<" << tail.substr(17, tail.length()) << endl; }
	return tail;
}

void cbSet(wstring& s) {
	auto length = 2 * (wcslen(s.c_str()) + 1);
	HGLOBAL h = GlobalAlloc(GMEM_DDESHARE, length);
	if (h != NULL) {
		auto x = GlobalLock(h);
		if (x != NULL) memcpy(x, s.c_str(), length);
		GlobalUnlock(h);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_UNICODETEXT, h);
		CloseClipboard();
	}
}

static auto cbGet(wstring cb = L"") {
	OpenClipboard(0);
	HANDLE c = GetClipboardData(CF_UNICODETEXT);
	if (c != nullptr) {
		wchar_t* t = static_cast<wchar_t*>(GlobalLock(c));
		if (t != nullptr) cb = t;
		GlobalUnlock(c);
	}
	CloseClipboard();
	return cb;
}

static void showOutsMsg(Multi multi, wstring s, wstring w, wstring s1 = L"", bool b = 0) {
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t x = 0; bool t = 0;
	if (multiLineDelim[0] != '\\') { w = regex_replace(w, wregex(L"\n"), L""); w = regex_replace(w, wregex(L"\t"), L""); }
	auto write = [&x, &t](wstring w) {
		wcout << w; ++x; t = 1;
	};
	auto color = [&x, &t, w, hC](WORD n) {
		SetConsoleTextAttribute(hC, n); ++x; t = 1;
		if (w[x] == '\\') --x;
	};
	wcout << s;
	for (; x < w.length(); ++x) {
		if (b && w[x] == '\\') {
			t = 0;
			switch (w[x + 1]) {
			case'd': //out <+>
			{ size_t x = i; wstring t = tail, c = codes;
			out(to_wstring(multi.icp));
			tail = t; i = x; re = L" "; codes = c; }
			write(L""); break;
			case'+':
			{ wstring a = to_wstring(multi.icp); write(a); } break; //<+>
			case'a':
			{ write(L"\a"); } break; //beep
			case'1':
			case'B':
				color(1); break; //blu
			case'2':
			case'G':
				color(2); break; //gr
			case'3':
				color(3); break;
			case'4':
			case'R':
				color(4); break; //r
			case'5':
				color(5); break;
			case'6':
				color(6); break;
			case'7':
				color(7); break;
			case'8':
				color(8); break;
			case'9':
				color(9); break;
			case '\\':
			{ write(L"\\"); }
			break;
			case '\'':
				x = w.length() - 1;
				t = 1;
				break;
			case 'c':
			{ write(cbGet()); }
			break;
			case 'm':
			{ write(multiLineDelim); }
			break;
			case 'n':
			{ write(L"\n"); }
			break;
			case 'T':
			{ wstring w{}; getTime(w); write(w); }
			break;
			case 't':
			{ write(L"\t"); }
			break;
			case 'g':
			{ write(L">"); }
			break;
			}
			if (t) continue;
		}
		wcout << w[x];
	}
	wcout << s1;
	if (!b) cout << '\n';
}

void showOutsMsg(wstring s, wstring w, wstring s1 = L"", bool b = 0) {
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t x = 0; bool t = 0;
	if (multiLineDelim[0] != '\\') { w = regex_replace(w, wregex(L"\n"), L""); w = regex_replace(w, wregex(L"\t"), L""); }
	auto write = [&x, &t](wstring w) {
		wcout << w; ++x; t = 1;
	};
	auto color = [&x, &t, w, hC](WORD n) {
		SetConsoleTextAttribute(hC, n); ++x; t = 1;
		if (w[x] == '\\') --x;
	};
	wcout << s;
	for (; x < w.length(); ++x) {
		if (b && w[x] == '\\') {
			t = 0;
			switch (w[x + 1]) {
			case'd': //out <+>
			{ size_t x = i; wstring t = tail, c = codes;
			out(to_wstring(ic));
			tail = t; i = x; re = L" "; codes = c; }
			write(L""); break;
			case'+':
			{ wstring a = to_wstring(ic); write(a); } break; //<+>
			case'a':
			{ write(L"\a"); } break; //beep
			case'1':
			case'B':
				color(1); break; //blu
			case'2':
			case'G':
				color(2); break; //gr
			case'3':
				color(3); break;
			case'4':
			case'R':
				color(4); break; //r
			case'5':
				color(5); break;
			case'6':
				color(6); break;
			case'7':
				color(7); break;
			case'8':
				color(8); break;
			case'9':
				color(9); break;
			case '\\':
			{ write(L"\\"); }
			break;
			case '\'':
				x = w.length() - 1;
				t = 1;
				break;
			case 'c':
			{ write(cbGet()); }
			break;
			case 'm':
			{ write(multiLineDelim); }
			break;
			case 'n':
			{ write(L"\n"); }
			break;
			case 'T':
			{ wstring w{}; getTime(w); write(w); }
			break;
			case 't':
			{ write(L"\t"); }
			break;
			case 'g':
			{ write(L">"); }
			break;
			}
			if (t) continue;
		}
		wcout << w[x];
	}
	wcout << s1;
	if (!b) cout << '\n';
}

static void rei() { i += qq.find('>'); }

static void rei(Multi multi) {
	tail = multi.t; qp = multi.qp;  qq = multi.q;; i = multi.i_; i += qq.find('>'); multi.i_ = i;
}

static wstring parse(int r, wstring &rs) {
	switch (r) {
	case 65: rs = 'A'; break;
	case 66: rs = 'B'; break;
	case 67: rs = 'C'; break;
	case 68: rs = 'D'; break;
	case 69: rs = 'E'; break;
	case 70: rs = 'F'; break;
	case 71: rs = 'G'; break;
	case 72: rs = 'H'; break;
	case 73: rs = 'I'; break;
	case 74: rs = 'J'; break;
	case 75: rs = 'K'; break;
	case 76: rs = 'L'; break;
	case 77: rs = 'M'; break;
	case 78: rs = 'N'; break;
	case 79: rs = 'O'; break;
	case 80: rs = 'P'; break;
	case 81: rs = 'Q'; break;
	case 82: rs = 'R'; break;
	case 83: rs = 'S'; break;
	case 84: rs = 'T'; break;
	case 85: rs = 'U'; break;
	case 86: rs = 'V'; break;
	case 87: rs = 'W'; break;
	case 88: rs = 'X'; break;
	case 89: rs = 'Y'; break;
	case 90: rs = 'Z'; break;
	case 97: rs = 'a'; break;
	case 98: rs = 'b'; break;
	case 99: rs = 'c'; break;
	case 100: rs = 'd'; break;
	case 101: rs = 'e'; break;
	case 102: rs = 'f'; break;
	case 103: rs = 'g'; break;
	case 104: rs = 'h'; break;
	case 105: rs = 'i'; break;
	case 106: rs = 'j'; break;
	case 107: rs = 'k'; break;
	case 108: rs = 'l'; break;
	case 109: rs = 'm'; break;
	case 110: rs = 'n'; break;
	case 111: rs = 'o'; break;
	case 112: rs = 'p'; break;
	case 113: rs = 'q'; break;
	case 114: rs = 'r'; break;
	case 115: rs = 's'; break;
	case 116: rs = 't'; break;
	case 117: rs = 'u'; break;
	case 118: rs = 'v'; break;
	case 119: rs = 'w'; break;
	case 120: rs = 'x'; break;
	case 121: rs = 'y'; break;
	case 122: rs = 'z'; break;
	}
	return rs;
}

wstring randn(bool bg = 0) {
	srand((unsigned)GetTickCount64());
	int r{}; wstring rs;
	char s = (qq[5] + qq[1]);
	bool parse_ = 1;
	switch (s) {
	default:
	case -84://':r': <rand:> #
		if (check_if_num(qx) != L"" && check_if_num(qy) != L"" && stoi(qy) > stoi(qx)) {
			r = qx == L"0" ?
				rand() % (stoi(qy) + 1) :
				(rand() % (stoi(qy) + 1 - stoi(qx))) + stoi(qx);
		}
		else r = rand();
		rs = to_wstring(r);
		parse_ = 0;
		break;
	case -112://'>R': <Rand> A-Z
		r = (char)((rand() % ('Z' + 1 - 'A')) + 'A');//cout << (char)r;
		break;
	case -80://'>r': <rand> a-z
		r = (char)((rand() % ('z' + 1 - 'a')) + 'a');//cout << (char)r;
		break;
	case -116://':R': <Rand:> A-Za-z
		r = rand() % 2;
		r = r == 1 ?
			(char)((rand() % ('z' + 1 - 'a')) + 'a') :
			(char)((rand() % ('Z' + 1 - 'A')) + 'A');//cout << (char)r;
	}
	if (parse_) rs = parse(r, rs);
	if (bg) return rs;
	qq = rs + qq.substr(qq.find('>') + 1, qq.length());
	i = -1;
	if (speed > 0) sleep = 0;
	re = L" ";
	tail = qq;
	return rs;
}

static void bs_input() {
	for (size_t t = strand[0] == '<'; t < strand.length() - (strand[strand.length()] == '>'); ++t) { if (strand[t] > 127) { ++t; continue; } if (((Kb_Key_Menu[0]) && strand[t] == Kb_Key_Menu[0]) || (!ignoreF1s) && (strand[t] == Kb_Key_F1[0] || strand[t] == Kb_Key_F2[0] || strand[t] == Kb_Key_F3[0] || strand[t] == Kb_Key_F4[0] || strand[t] == Kb_Key_F5[0] || strand[t] == Kb_Key_F6[0] || strand[t] == Kb_Key_F7[0] || strand[t] == Kb_Key_F8[0] || strand[t] == Kb_Key_F9[0] || strand[t] == Kb_Key_F10[0] || strand[t] == Kb_Key_F11[0] || strand[t] == Kb_Key_F12[0]) || (Kb_Key_Esc[0] && strand[t] == Kb_Key_Esc[0]) || (Kb_Key_Left_Shift[0] && strand[t] == Kb_Key_Left_Shift[0]) || (Kb_Key_Right_Shift[0] && strand[t] == Kb_Key_Right_Shift[0]) || (Kb_Key_Left_Alt[0] && strand[t] == Kb_Key_Left_Alt[0]) || (Kb_Key_Right_Alt[0] && strand[t] == Kb_Key_Right_Alt[0]) || (Kb_Key_Left_Ctrl[0] && strand[t] == Kb_Key_Left_Ctrl[0]) || (Kb_Key_Right_Ctrl[0] && strand[t] == Kb_Key_Right_Ctrl[0]) || (Kb_Key_Caps[0] && strand[t] == Kb_Key_Caps[0])) { continue; } kb(VK_BACK); } GetAsyncKeyState(VK_BACK);//exclude non bs: < LURD !@#$%^&*()_+ ~ S H A M C O P
}

static void replace_q(wstring &a, wstring b, wstring c) {
	if (a.find(L"\\" + c) == string::npos) return;
	const wstring y = (L":" + c + L":_:" + c + L":"); //:g:_:g: placeholder
	a = regex_replace(a, wregex(L"\\\\\\\\" + c), y);
	a = regex_replace(a, wregex(L"\\\\" + c), b);
	a = regex_replace(a, wregex(y), L"\\" + c);
}

void scanDb() {
	if (close_ctrl_mode) {
		if (strand.length() == 0) {
			if (!re[0])
				return;
		}
		else {
			if (strand[strand.length() - 1] != '>')
				return;
		}
	}
	Mainn mainn;
	wstring sv = strand;
	wifstream f(database); if (!f) { showOutsMsg(L"\nDatabase \"", database, L"\" not found!", 0); if (!database[0]) { cout << "Create c:\\dna\\db.txt manually\n\n?+ESC\n\n"; } return; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>)); //properties, general, language standard, >c++14 //_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	short svi = 0; if (sv[0] != '<' && strandLengthMode && sv.size() - close_ctrl_mode > 1) { for (auto c : sv) if (c > 127) ++svi; } //counter for non asciis
	wstring cell; relink = 0; bool fallthrough = 0; while (getline(f, cell, multiLineDelim[0])) { //cout << cell << endl;
		
		if (fallthrough && strandLengthMode) {
			if (cell.length() <= strandLengthMode) {
				fallthrough = 0;
				if (cell == L"") { f.close(); return; }
				while (getline(f, cell, multiLineDelim[0])) {
					if (cell == L"") { f.close(); return; }
					if (cell.length() <= strandLengthMode) { continue; }
					else break;
				}
			}
			auto xl = io + L">:-";
			sv = cell.substr(cell[0] == '<', cell.find_first_of(xl));
			fallthrough = 1;
		}
		
		if (cell[1] == '\'') { if (cell.substr(0, 4) == L"<'''") break; } //ignore db...
		if (auto a = strandLengthMode == 1 && sv[0] != '<' ? cell.substr(0, 2) : cell.substr(0, sv.size() > cell.size() ? cell.size() : sv.size() + !close_ctrl_mode), b = strandLengthMode == 1 && sv[0] != '<' ? sv.substr(0, 1) : sv.substr(0, sv.size() - close_ctrl_mode + fallthrough);
			re[0] && !sv[0] || sv[0] && a[0] && a[0] != ' '
			&& a == b + io[0] //<x >
			|| b == cell || fallthrough
			|| strandLengthMode && sv[0] != '<' && (!svi && cell.substr(0, (size_t)strandLengthMode + 1) == sv || svi > strandLengthMode && cell.substr(0, svi) == b) //xxx
			|| a == b + L':' //<x:>
			|| a == b + L'-' //<x->
			|| a == b + L'>' //<x>
		) {
						
			if (sv[0] && sv == cell || (close_ctrl_mode || toggle_ccm) && cell[0] && cell == sv.substr(0, sv.length() - close_ctrl_mode)) {
				if (sv == cell) strand.clear();
				fallthrough = 1;
				continue;
			}
			
			Multi multi;
			if (multiStrand) { strand = multi.s; if (!re[0]) mainn.s1 = linkr = cell.substr(0, strand.size()); }
			if (close_ctrl_mode && strand.length() > 0 && strand[strand.length() - 1] == '>') strand = strand.substr(0, strand.length() - 1); if (multiStrand) multi.s = strand;
			if (re[0] && !strand[0]) {
				if (link[0] == '<' && cell.substr(0, link.length()) == link) relink = 1;
				cell = re;
				if (re[0] == '>' && (re[17] == 'x' || re[17] == 'r' || re[17] == 'a')) {
					switch (re[17]) {
					case 'x':
						if (re.substr(0, 20) == L"><shift>,<shift->xy:") cell = codes = makeXY(); break;
					case 'r':
						if (re.substr(0, 21) == L"><shift>,<shift->rgb:") cell = codes = makeRGB(); break;
					case 'a':
						if (re.substr(0, 21) == L"><shift>,<shift->app:") cell = codes = makeApp(); break;
					}
				}
			}

			tail = cell.find_first_of(io + L">:-") == string::npos ?  L"" : cell.substr(cell.find_first_of(io + L">:-"));
			if (!tail[0]) { fallthrough; continue; }
			
			tail = isVar(tail); //<r:>
			if (multiStrand) multi.t = tail;
			if (tail.substr(0, io.size()) == io) {//io:
				tail = tail.substr(io[0] > 127 ? 2 : 1, tail.length());
				if (tail[0] == '>') tail = tail.substr(1);
				if (io_Auto_BS) bs_input();
				codes = tail;
				multi.t = tail;
			}
			else {
				switch (tail[0]) {//set_tail
				case ':':
					tail = tail.substr(1);
					if (tail[0] == '>') tail = tail.substr(1);
					codes = tail;
					break;
				case '>':
				{
					wstring s = sv[0] ? sv : strand;
					for (size_t t = s[0] == '<'; t < s.size() - (s[s.size() - 1] == '>'); ++t) {
						if (s[t] > 127) { ++t; continue; }
						if (((Kb_Key_Menu[0]) && s[t] == Kb_Key_Menu[0]) || (!ignoreF1s) && (s[t] == Kb_Key_F1[0] || s[t] == Kb_Key_F2[0] || s[t] == Kb_Key_F3[0] || s[t] == Kb_Key_F4[0] || s[t] == Kb_Key_F5[0] || s[t] == Kb_Key_F6[0] || s[t] == Kb_Key_F7[0] || s[t] == Kb_Key_F8[0] || s[t] == Kb_Key_F9[0] || s[t] == Kb_Key_F10[0] || s[t] == Kb_Key_F11[0] || s[t] == Kb_Key_F12[0]) || (Kb_Key_Esc[0] && s[t] == Kb_Key_Esc[0]) || (Kb_Key_Left_Shift[0] && s[t] == Kb_Key_Left_Shift[0]) || (Kb_Key_Right_Shift[0] && s[t] == Kb_Key_Right_Shift[0]) || (Kb_Key_Left_Alt[0] && s[t] == Kb_Key_Left_Alt[0]) || (Kb_Key_Right_Alt[0] && s[t] == Kb_Key_Right_Alt[0]) || (Kb_Key_Left_Ctrl[0] && s[t] == Kb_Key_Left_Ctrl[0]) || (Kb_Key_Right_Ctrl[0] && s[t] == Kb_Key_Right_Ctrl[0]) || (Kb_Key_Caps[0] && s[t] == Kb_Key_Caps[0])) {
							s[t] = '>';
							continue;
						}
					}
					s = regex_replace(s, wregex(L">"), L"");
					if (s[0] == '<') s = s.substr(1);
					strand[0] ? strand = s : sv = s;
					tail = tail.substr(1);
					codes = s + tail;
				}
 					break;
				case '-':
					tail = tail.substr(1);
					if (tail[0] == '>') tail = tail.substr(1);
					if (multiStrand) multi.t = tail;
					bs_input();
					if (multiStrand) tail = multi.t;
					codes = tail;
					break;
				default:
					codes = cell;
				}
				if (multiStrand) multi.t = tail;
			}
			if (noClearStrand) noClearStrand = 0;
			if (multiStrand) { reTail = codes; tail = multi.t; }
			if (tail.find(L"<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
			f.close(); fail = 0; esc_pressed = 0; if (rri && RSHIFTLSHIFT_Only) rri = 0;
			for (i = 0; i < tail.length(); ++i) {
				if (multiStrand) { multi.t = tail; multi.i_ = i; }
				if (speed > 0) { if (sleep) { if (multiStrand) { re = multi.t = tail; multi.i_ = i; multi.q = qq; multi.speed_ = speed; } Sleep(speed); if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; } } sleep = 1; }
				if (!NoEscapeOrPause) {
					GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { if (multi.esc == 1) {} else { esc_pressed = 0; pause_resume = 0; multiblock = 0; break; } }
					GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {//int m = MessageBoxA(0, "Resume?", "dnaspider", MB_YESNO); if (m != IDYES) { break; } }
						while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); }
						if (multiStrand) multi.i_ = i;
						if (showStrand) showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
						pause_resume = 1;
						wstring q = L"~PAUSE\n"; speed = 0;
						while (pause_resume) {
							GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); } break; }
							GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
							if (!esc_pressed) Sleep(150);
						}
						if (showStrand) showOutsMsg(L"", OutsTemplate, q, 1);
						if (q[1] == 'E') break;
						if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
					}
				}
				if (multiStrand) { tail = multi.t; i = multi.i_; multi.q = qq; }
				wstring ctail = tail.substr(i, 1);//extracted char from tail
				switch (ctail[0]) {
				case'<':
					if (multiStrand) { i = multi.i_; qq = multi.q; }
					qq = tail.substr(i, tail.length() - i); //<test>
					if (multiStrand) { multi.q = qq; multi.i_ = i; }
					if (qq.substr(0, qq.find('>')).find(':') != std::string::npos) { //<test:#>
						qp = qq.substr(qq.find(':') + 1, qq.find('>') - qq.find(':') - 1);//#
						if (qp[0]) {
							if (qp[0] == ' ') qp = qp.substr(1);
							setQxQy(qp);
						}
						if (multiStrand) multi.qp = qp;
					}
					switch (qq[1]) {
					case '<':
						if (testqqb(L"<<:")) {//cout
							if (replacerDb[0]) { wstring t = qq; t = isVar(t); } //<<:{<x:>}>
							if (multiStrand) 
								showOutsMsg(multi, L"", qp, L"", 1); 
							else
								showOutsMsg(L"", qp, L"", 1);
							rei();
							break;
						}
						else conn();
						break;
					case '#':
						if (testqqb(L"<#:")) {//ascii_calc
							if (qp.find('\\') != string::npos) qp = regex_replace(a, wregex(L"\\\\g"), L">");
							int s{}; for (auto &x : qp) s += x;
							auto q = to_wstring(s);	cbSet(q);
							rei();
						}
						else conn();
						break;
					case '!':
						if (testqqb(L"<!!!:")) {
							reTail = codes = (qp + L">"); strand.clear(); i = tail.length(); }//set repeat
						else if (testqqb(L"<!!:")) {//multi run
							wstring t = qq.substr(qq.find('>') + 1);//tail
							wstring m = qq.substr(0, qq.find('>')) + L">";//q ms
							wstring x = L"", o = L""; x += io[0]; x += '>';
							if (m.substr(m.length() - 2) == x || m.substr(m.length() - 2) == L":>" || m.substr(m.length() - 2) == L"->") { m = to_wstring(CloseCtrlSpacer); qp = qp.substr(0, qp.length() - (qp[0] != '<')); }
							else {
								m = m.substr(4);
								if (m.find(io[0]) != string::npos) o[0] = io[0];
								else if (m.find(':') != string::npos) o[0] = ':';
								else if (m.find('-') != string::npos) o[0] = '-';
								if (o[0] && m.find(o[0]) != string::npos) qp = m.substr(0, m.find(o[0]) + (qp[0] == '<'));
								else m.clear();
								if (qp[0] == ' ') qp = qp.substr(1);
								if (o[0]) { m = m.substr(m.find(o[0]) + 1); m = m.substr(0, m.length() - 1); }
							}
							if (!m[0] || m[0] == '0') m[0] = '1';
							unsigned int m1 = stoi(m);
							{ Store store; store.v = t; store.v1 = cell[strand.length()] == '>' ? strand + tail : tail;
							strand = qp + (close_ctrl_mode ? L">" : L""); thread thread(scanDb); Sleep(m1); thread.detach(); if (!noClearStrand) { strand.clear(); } noClearStrand = 0;
							tail = store.v; reTail = store.v1; i = -1; }
						}
						else if (qqb(L"<!>") || qqb(L"<!:>") || testqqb(L"<!:")) { if (qq[2] == ':') { if (qq[3] == '>') { strand.clear(); clearAllKeys(); rei(); break; } strand = qp; if (showStrand) { showOutsMsg(L"", OutsTemplate, strand + L"\n", 1); } } noClearStrand = 1; rei(); }
						else conn();
						break;
					case '~':
						if (qqb(L"<~>")) {//manual set xy
							POINT pt; GetCursorPos(&pt); qxcc = pt.x; qycc = pt.y; rei();
						}
						else if (qqb(L"<~~>")) {//manual return xy
							SetCursorPos(qxcc, qycc); rei();
						}
						else if (qqb(L"<~m>")) {//disable
							bool m = multiStrand; multiStrand = 0; rei();
							multiblock = 1;	wstring t = codes; out(tail.substr(i + 1));
							multiblock = 0; multiStrand = m; if (GetAsyncKeyState(VK_ESCAPE)) { i = tail.length(); } reTail = t; return;
						}
						else if (qqb(L"<~~m>")) {//enable
							multiStrand = 1; multiblock = 0; rei();
						}
						else if (qqb(L"<~esc>")) {
							if (multiStrand) multi.esc = 0; else { NoEscapeOrPause = 0; } rei();
						}
						else if (qqb(L"<~~esc>")) {
							if (multiStrand) multi.esc = 1; else { NoEscapeOrPause = 1; } rei();
						}
						else conn();
						break;
					case'+': //calc
					case'-':
					case'*':
					case'/':
					case'%': {
						if (qq[3] == ' ') { //<+: #>
							wstring cb = cbGet();
							if (auto e = cb; !e[0] || check_if_num(e) == L"") { conn(); showOutsMsg(L"NAN: cb{", L"\\4" + cb + L"\\7", L"}", 1); continue; }
							multi.icp = stod(cb);
						}
						
						bool b = 0;
						if (qq[2] == '>' && qq[1] == '+') b = 1; //<+>
						else if (auto e = qp; !e[0] || check_if_num(e) == L"") {
							if (!qp[0]) conn();
							else { showOutsMsg(L"NAN: " + qq.substr(0, 3), L"\\4" + qq.substr(3, qp.length() + (qq[3] == ' ')) + L"\\7", L">", 1); printq(); }
							continue;
						}

						if (b) {}
						else {
							if (qq[2] != ':') { conn(); continue; }
							switch (qq[1]) {
							case'+': multi.icp += stod(qp); break; // <+:>
							case'-': multi.icp -= stod(qp); break;
							case'*': multi.icp *= stod(qp); break;
							case'/':
							case'%': if (stoi(qp) <= 0) { printq(); continue; }
								if (int x = (int)multi.icp; qq[1] == '/') multi.icp /= stod(qp);
								else multi.icp = x % stoi(qp);
							}
						}

						static bool dp;
						if (qp.find('.') != string::npos || qq[3] == ' ' && cbGet().find('.') != string::npos) dp = 1; else { if (!b) dp = 0; }

						wstring x = to_wstring(multi.icp);
						if (!dp || qq[1] == '%') x = x.substr(0, x.find(L"."));
						
						if (qq[3] == ' ') cbSet(x);

						if (b) {
							tail = x + qq.substr(qq.find('>') + 1);
							i = -1;
							ic = multi.icp;
						}
						else rei();
					}
						break;
					case',':
						if (qqb(L"<,") && qq[2] != ':' && qq[2] != '-') { //<,#> || <,*
							if (multiStrand) { i = multi.i_; }
							wstring s = qq.substr(2, qq.find('>') - 2);
							if (s == L"") s = to_wstring(CommaSleep);
							if (s[0] == '*') s = s.substr(1, s.length()); //case: <,*
							s = check_if_num(s);
							if (s == L"") { printq(); break; }
							if (s[0] == ' ') s = s.substr(1); if (s[0] == '<') {//Assume
								if (s[s.length() - 1] == ':' || s[s.length() - 1] == '-') {//<x:>
									wstring t = qq;
									qq = s + L">";
									s = conn(1);
									qq = t;
								}
								if (s.substr(1, 5) == L"rand:") {//x:<rand:0,5> | <,{x:}>
									setQxQy(s, 6);
									s = randn(1);
								}
								i += 1; if (multiStrand) { multi.i_ = i; }
								if (s == L"0") return;
							}
							if (s[0] == '{' || stoi(s) > 0 && s[0] != '+') {
								if (multiStrand) { i = multi.i_; }
								if (qq[2] == '*') {
									GetAsyncKeyState(VK_ESCAPE); GetAsyncKeyState(VK_PAUSE); for (int j = 0; j < stoi(s); ++j) {//sleep150ms*?
										if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); if (showStrand) { cout << '\n'; } return; }//stop
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); }
											if (multiStrand) multi.i_ = i;
											showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); } break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; qp = multi.qp; speed = multi.speed_; }
										}
										Sleep(CommaSleep);
									}
								}
								else { Sleep(stoi(s)); 
									if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; qp = multi.qp; speed = multi.speed_; }
								}
							}
							else { printq(); break; };
							if (multiStrand) rei(multi); else rei();
						}
						else conn();
						break;
					case'\'':
						if (qq.find('>') != string::npos && qqb(L"<''")) i = tail.length();//<''ignore>...
						else if (qq.find('>') != string::npos && qqb(L"<'")) { //<'comments>
							if (showStrand) {
 								if(qq[2] != ' '){
									showOutsMsg(L"", OutsTemplate, L"", 1);
									const wstring& v = qq.substr(2, qq.find('>') - 2);
									if (multiStrand)
										showOutsMsg(multi, L"", v, L"\n", 1);
									else
										showOutsMsg(L"", v, L"\n", 1);
								}
							}
							rei(); sleep = 0;
						}
						else conn();
						break;
					case'a':
					case 'A':
						switch (qq[2]) {
						case 'l':
							if (qqb(L"<alt>")) { kbHold(VK_LMENU); rei(); }
							else if (qqb(L"<alt->")) { kbRelease(VK_LMENU); rei(); }
							else if (qqb(L"<alt")) kbPress(multi, L"<alt", VK_LMENU);
							else conn();
							break;
						case ':':
							if (testqqb(L"<a:")) {//<a:\g>
								kb(qp); rei();
							}
							else conn();
							break;
						case 'p':
							if (testqqb(L"<app:") || testqqb(L"<App:")) {//app activate, if app in foreground
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring gq = L""; if (qp[0] == '\'') { auto x = qp.find(qp[0], 1); if (x == string::npos) { gq = qp[0]; qp = qp.substr(1); } else { gq = qp.substr(1, x - 1); qp = qp.substr(gq.length() + 2 + (qp[gq.length() + 2] == ' ')); } }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link.clear();//<app:a,x,ms,link>
								if (a.find(L"\\,") != wstring::npos) {// \,
									wstring t = a.substr(a.find_last_of(L"\\") + 2);
									if (t.find(',') != string::npos) {
										a = a.substr(0, a.find_last_of(L"\\") + t.find(',') + 2);
										qp = qp.substr(a.length());
									}
									else qp.clear();
								}
								else a = a.substr(0, a.find(','));
								if (qp.find(',') != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(',') + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(',') != string::npos) {
										ms = x.substr(x.find(',') + 1); if (ms == L"") { printq(); break; }
										if (ms.find(',') != string::npos) {
											link = ms.substr(ms.find(',') + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(',')); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(','));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								if (a.find('\\') != string::npos) {
									a = regex_replace(a, wregex(L"\\\\,"), L",");// \,
									a = regex_replace(a, wregex(L"\\\\g"), L">");
								}
								HWND h{}, h1{}; DWORD pid{};
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand && !assume) { wcout << "Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find('>') + 1), L"", 0); } };
								if (multiStrand) { multi.a = a; multi.x = x; multi.m = ms; multi.l = link; }
								if (multiStrand) { x = multi.x; } auto size{ 0 }, length{ stoi(x) };

								auto sifapp = [&multi, &qqC, &pid, &h1, &h, &a]() {
									multi.br = 0; if (multiStrand) a = multi.a;
									if (qqC[1] == 'A') {//App
										h = GetForegroundWindow(); h1 = FindWindowW(0, a.c_str());
										if (h == h1) multi.br = 1;
									}
									else if (qqC[1] == 'a') {//'app
										h = FindWindowW(0, a.c_str()); GetWindowThreadProcessId(h, &pid);
										if (h) {
											if (IsIconic(h)) { ShowWindow(h, SW_RESTORE); ShowWindow(h, SWP_SHOWWINDOW); } SetForegroundWindow(h);
											multi.br = 1;
										}
									}
								};

								wstring tar = a, app = a;
								for (; size < length; ++size) { //cout << size << " app:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); strand.clear(); return; }//stop
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											Sleep(450); while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { kbRelease(PauseKey); break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { ms = multi.m; } f(); break; }
									if (multiStrand) { a = multi.a; qqC = multi.q; }

									tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  ");
									if (tar.find('|') != string::npos || tar.find('&') != string::npos) {// | &
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (tar[j] == '|' || tar[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1) : ta;
												a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&");
												if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1);//!\0
												if (multiStrand) multi.a = a; 
												sifapp(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
												if (!multi.br && q == L"&" && t.find('|') != string::npos) {
													t = t.substr(t.find('|') + 1);
													a = t; j = -1; ta.clear(); continue;
												}
												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find('|') != string::npos) sand = 1; else { if (!sor || t.find('&') == string::npos) break; }
													}
													if (q == L"|") {
														sor = 0;
														if (t.find('&') != string::npos) sor = 1;
														if (t.find('&') != string::npos && t.find('|') == string::npos) sor = 1;
													}
												}
												if (q == L"&" && multi.br) sand = 1;
												if (q == L"|" && multi.br) { sor = 1; break; } //wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
												multi.br = 0; a = t; j = -1; ta.clear();
												tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  ");
											}
										}
										if (!multiStrand) a = app;
										if (sor && sand) multi.br = 1; //sifapp
									}
									else {
										if (a.find('\\') != string::npos) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); if (multiStrand) multi.a = a; }
										sifapp();
									}
									if (multi.br == 1) break;
									else {
										if (multiStrand) { ms = multi.m; linkC = multi.l; }
										if (length >= 1) { if (gq[0] && ms[0] != '0') { if (gq.length() == 1) wcout << gq; else showOutsMsg(L"", gq, L"", 1); } Sleep(stoi(ms)); }
										if (linkC[0] == io[0] && linkC.length() == 1 || linkC == L":" || linkC == L"-") --size;
									}
								}

								if (multiStrand) {
									i = multi.i_; qqC = multi.q; linkC = multi.l; if (!mF) { tail = multi.t; i += qqC.find('>'); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(' ') != string::npos)// ..., true: false:>
												linkC = linkC.substr(linkC.find(' ') + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
											if (mainn.s1 == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(' ') != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(' ') != string::npos) {// ..., true: false:>
									linkC = linkC.substr(0, linkC.find(' '));
									if (linkC == L"<") { if (multiStrand) { i = multi.i_; qqC = multi.q; linkC = multi.l; tail = multi.t; i += qqC.find('>'); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (qqb(L"<app>")) {//app title to cb
								wstring a(getAppT());
								cbSet(a);
								rei();
							}
							else conn();
							break;
						case 'u':
							if (testqqb(L"<Audio:") || testqqb(L"<audio:")) {
								if (qq[1] == 'A') sndPlaySoundW((qp).c_str(), SND_FILENAME | SND_ASYNC); else mciSendStringW((qp).c_str(), 0, 0, 0); //<audio:play test.mp3>
								rei();
							}
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'b':
						if (qqb(L"<bs")) kbPress(multi, L"<bs", VK_BACK);
						else if (qqb(L"<beep>")) { cout << "\a" << endl; rei(); }
						else conn();
						break;
					case'c':
					case'C':
						switch (qq[2]) {
						case 'l':
							if (qqb(L"<cl>")) { wstring l = cbGet(); l = to_wstring(l.length()); cbSet(l); rei(); }
							else conn();
							break;
						case 't':
							if (qqb(L"<ctrl>")) { kbHold(VK_CONTROL); rei(); }
							else if (qqb(L"<ctrl->")) { kbRelease(VK_CONTROL); rei(); }
							else if (qqb(L"<ctrl")) kbPress(multi, L"<ctrl", VK_CONTROL);
							else conn();
							break;
						case 'B':
						case 'b':
							if (testqqb(L"<CB:") || testqqb(L"<cb:")) {
								replace_q(qp, L">", L"g"); replace_q(qp, multiLineDelim, L"m");
								cbSet(qp);
								if (qq[1] == 'C') { kbHold(VK_CONTROL); kb('v'); kbRelease(VK_CONTROL); }
								rei();
							}
							else conn();
							break;
						case 'a':
							if (qqb(L"<caps")) kbPress(multi, L"<caps", VK_CAPITAL);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'd':
					case'D':
						switch (qq[2]) {
						case 'B':
						case 'b':
							if (testqqb(L"<DB:") || testqqb(L"<db:")) {//.h Database:
								if (qq[1] == 'D') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(qp, L"", L"", 0); }
								qp = regex_replace(qp, wregex(L"/"), L"\\");
								wifstream f(qp); if (!f) { showOutsMsg(L"\nDatabase \"", qp, L"\" not found!", 0); return; }
								database = qp;
								db = database.substr(database.find_last_of('\\') + 1) + L" - ";
								rei();
								break;
							}
							else if (qqb(L"<db>")) { printDb(); rei(); }
							else conn();
							break;
						case 'o':
							if (qqb(L"<down")) kbPress(multi, L"<down", VK_DOWN);
							else conn();
							break;
						case 'n':
							if (qqb(L"<dna:")) { replace_q(qp, L">", L"g"); HWND h = GetConsoleWindow(); SetConsoleTitleW(qp.c_str()); rei(); }
							else conn();
							break;
						case 'e':
							if (qqb(L"<delete")) kbPress(multi, L"<delete", VK_DELETE);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'e':
						switch (qq[3]) {
						case 't':
							if (qqb(L"<enter")) kbPress(multi, L"<enter", VK_RETURN);
							else conn();
							break;
						case 'd':
							if (qqb(L"<end")) kbPress(multi, L"<end", VK_END);
							else conn();
							break;
						case 'c':
							if (qqb(L"<esc")) kbPress(multi, L"<esc", VK_ESCAPE);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'f':
						switch (qq[2]) {
						case '1':
							if (qqb(L"<f10")) kbPress(multi, L"<f10", VK_F10);
							else if (qqb(L"<f11")) kbPress(multi, L"<f11", VK_F11);
							else if (qqb(L"<f12")) kbPress(multi, L"<f12", VK_F12);
							else if (qqb(L"<f1")) kbPress(multi, L"<f1", VK_F1);
							else conn();
							break;
						case '2':
							if (qqb(L"<f2")) kbPress(multi, L"<f2", VK_F2);
							else conn();
							break;
						case '3':
							if (qqb(L"<f3")) kbPress(multi, L"<f3", VK_F3);
							else conn();
							break;
						case '4':
							if (qqb(L"<f4")) kbPress(multi, L"<f4", VK_F4);
							else conn();
							break;
						case '5':
							if (qqb(L"<f5")) kbPress(multi, L"<f5", VK_F5);
							else conn();
							break;
						case '6':
							if (qqb(L"<f6")) kbPress(multi, L"<f6", VK_F6);
							else conn();
							break;
						case '7':
							if (qqb(L"<f7")) kbPress(multi, L"<f7", VK_F7);
							else conn();
							break;
						case '8':
							if (qqb(L"<f8")) kbPress(multi, L"<f8", VK_F8);
							else conn();
							break;
						case '9':
							if (qqb(L"<f9")) kbPress(multi, L"<f9", VK_F9);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'h':
						if (qqb(L"<home")) kbPress(multi, L"<home", VK_HOME);
						else conn();
						break;
					case'i':
						switch (qq[2]) {
						case 'f':
							if (testqqb(L"<ifxy")) {//==, !=, <, <=, g, g=
								if (multiStrand) qp = multi.qp;
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring gq = L""; if (qp[0] == '\'') { auto x = qp.find(qp[0], 1); if (x == string::npos) { gq = qp[0]; qp = qp.substr(1); } else { gq = qp.substr(1, x - 1); qp = qp.substr(gq.length() + 2 + (qp[gq.length() + 2] == ' ')); } }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link.clear();//<ifxy:a a,x,ms,link link>
								a = a.substr(0, a.find(','));
								if (qp.find(',') != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(',') + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(',') != string::npos) {
										ms = x.substr(x.find(',') + 1); if (ms == L"") { printq(); break; }
										if (ms.find(',') != string::npos) {
											link = ms.substr(ms.find(',') + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(',')); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(','));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand && !assume) { wcout << "Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find('>') + 1), L"", 0); } };
								if (multiStrand) { multi.a = a; multi.x = x; multi.m = ms; multi.l = link; }
								if (multiStrand) { x = multi.x; } auto size{ 0 }, length{ stoi(x) };

								auto sifxy = [&qqC, &multi, &a]() {
									multi.br = 0; if (multiStrand) a = multi.a;
									auto q = a.find(' ');
									auto x = a.substr(0, q), y = a.substr(q + 1);
									POINT pt; GetCursorPos(&pt);
									if (x == L".") x = to_wstring(pt.x);
									if (y == L".") y = to_wstring(pt.y);
									auto tx = stoi(x), ty = stoi(y);

									switch (qqC[5]) {
									case ':': //== <ifxy:> <ifxy=:> <ifxye:>
									case '=':
									case 'e':
										if (pt.x == tx && pt.y == ty) multi.br = 1;
										break;
									case 'n': //!= <ifxyn:> <ifxy!:>
									case '!':
										if (pt.x != tx && pt.y != ty) multi.br = 1;
										break;
									case 'l'://<= <ifxyl:> <ifxyle:> <ifxy<:> <ifxy<=:>
									case 'L':
									case '<':
										if (qqC[6] == 'e' || qqC[6] == '=') { if (pt.x <= tx && pt.y <= ty) { multi.br = 1; break; } } //ifxyle <=
										if (pt.x < tx && pt.y < ty) multi.br = 1;
										break;
									case 'g'://>= <ifxyg:> <ifxyge:> <ifxyg=:>
										if (qqC[6] == 'e' || qqC[6] == '=') { if (pt.x >= tx && pt.y >= ty) { multi.br = 1; break; } } //ifxyge >=/g=
										if (pt.x > tx && pt.y > ty) multi.br = 1;
										break;
									}
								};

								if (multiStrand) a = multi.a;
								wstring tar = a, app = a;
								if (multiStrand) { x = multi.x; } length = stoi(x);
								for (; size < length; ++size) { //cout << size << "ifxy:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { if (multi.esc == 1) {} else { esc_pressed = 0; pause_resume = 0; multiblock = 0; break; } }
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); }
											if (multiStrand) multi.i_ = i;
											if (showStrand) showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); } break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											if (showStrand) showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { ms = multi.m; } f(); break; }
									if (multiStrand) { a = multi.a; qqC = multi.q; }

									if (tar.find('\\') != string::npos) { tar = regex_replace(tar, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
									if (tar == L"") tar = a;
									if (tar.find('|') != string::npos || tar.find('&') != string::npos) {// | &
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (tar[j] == '|' || tar[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1) : ta;
												a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&");
												if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1); //!\0
												sifxy(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
												if (!multi.br && q == L"&" && t.find('|') != string::npos) {
													t = t.substr(t.find('|') + 1);
													a = t; j = -1; ta.clear(); continue;
												}
												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find('|') != string::npos) sand = 1; else { if (!sor || t.find('&') == string::npos) break; }
													}
													if (q == L"|") {
														sor = 0;
														if (t.find('&') != string::npos) sor = 1;
														if (t.find('&') != string::npos && t.find('|') == string::npos) sor = 1;
													}
												}
												if (q == L"&" && multi.br) sand = 1;
												if (q == L"|" && multi.br) { sor = 1; break; }
												multi.br = 0; a = t; j = -1; ta.clear();
												tar = regex_replace(a, wregex(L"\\\\\\|"), L"  ");
											}
										}
										if (!multiStrand) a = app;
										if (sor) multi.br = 1; //sifxy
									}
									else {
										if (a.find('\\') != string::npos) a = regex_replace(a, wregex(L"\\\\\\|"), L"|");
										if (multiStrand) multi.a = a;
										sifxy();
									}
									if (multi.br == 1) break;
									else {
										if (multiStrand) { ms = multi.m; linkC = multi.l; }
										if (length >= 1) { if (gq[0] && ms[0] != '0') { if (gq.length() == 1) wcout << gq; else showOutsMsg(L"", gq, L"", 1); } Sleep(stoi(ms)); }
										if (linkC[0] == io[0] && linkC.length() == 1 || linkC == L":" || linkC == L"-") --size;
									}
								}
								
								if (multiStrand) {
									i = multi.i_; qqC = multi.q; linkC = multi.l; if (!mF) { tail = multi.t; i += qqC.find('>'); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(' ') != string::npos)// ..., true: false:>
												linkC = linkC.substr(linkC.find(' ') + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<xy:a a,x,ms,<link->..., <xy:a a,x,ms,link->
											if (mainn.s1 == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(' ') != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(' ') != string::npos) {// ..., true: false:>
									linkC = linkC.substr(0, linkC.find(' '));
									if (linkC == L"<") { if (multiStrand) { i = multi.i_; qqC = multi.q; linkC = multi.l; tail = multi.t; i += qqC.find('>'); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<xy:a a,x,ms,<link->..., <xy:a a,x,ms,link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (testqqb(L"<ifcb")) {//Clipboard ==, !=, <, <=, g, g=, (f)ind, (F)ind, (n)ot
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring gq = L""; if (qp[0] == '\'') { auto x = qp.find(qp[0], 1); if (x == string::npos) { gq = qp[0]; qp = qp.substr(1); } else { gq = qp.substr(1, x - 1); qp = qp.substr(gq.length() + 2 + (qp[gq.length() + 2] == ' ')); } }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link.clear();//<ifcb:a,x,ms,link>
								if (a.find(L"\\,") != wstring::npos) {// \,
									wstring t = a.substr(a.find_last_of(L"\\") + 2);
									if (t.find(',') != string::npos) {
										a = a.substr(0, a.find_last_of(L"\\") + t.find(',') + 2);
										qp = qp.substr(a.length());
									}
									else qp.clear();
								}
								else a = a.substr(0, a.find(','));
								if (a.find(L"\\,") != wstring::npos) a = regex_replace(a, wregex(L"\\\\,"), L",");// \,
								wstring app = a;
								if (qp.find(',') != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(',') + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(',') != string::npos) {
										ms = x.substr(x.find(',') + 1); if (ms == L"") { printq(); break; }
										if (ms.find(',') != string::npos) {
											link = ms.substr(ms.find(',') + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(',')); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(','));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) { wcout << L"Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find('>') + 1), L"", 0); } };
								if (multiStrand) { multi.a = a; multi.x = x; multi.m = ms; multi.l = link; }
								HANDLE hcb; wchar_t* c; wstring w;
								if (multiStrand) { x = multi.x; } auto size{ 0 }, length{ stoi(x) };
							
								auto sifcb = [&qqC, &multi, &x, &w, &a]() {
									multi.br = 0;
									switch (qqC[5]) {
									case ':': //== <ifcb:> <ifcb=:> <ifcbe:>
									case '=':
									case 'e':
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w == a) multi.br = 1;
										break;
									case 'A': //<if cb find y starting @ offset x: x y> | <ifcba:1 test>
									case 'a': //<if cb substring from index x matches y: x y> | <ifcbA:0 test>
										{
											auto x = a.substr(0, a.find(' ')), y = a.substr(a.find(' ') + 1);
											y = regex_replace(y, wregex(L"\\\\g"), L">");
											if (qqC[5] == 'A') {
												auto s = stoi(x) - 1; if (w.find(y, s) != wstring::npos) multi.br = 1;
											}
											else { //'a'
												if (w.substr(stoi(x), y.length()) == y) multi.br = 1;
											}
										}
										break;
									case '+': //<ifcb+:>
									{
										wstring xcb = cbGet();
										if (auto x = xcb.find(qp);x) {
											ic = (int)x; multi.br = 1;
										}
									}
										break;
									case 'S': //if cb starts with | <ifcbS:test>
									case 'E': //ends with | <ifcbE:>
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (qqC[5] == 'E') {
											if (w.ends_with(a)) multi.br = 1;
										}
										else { //'S'
											if (w.starts_with(a)) multi.br = 1;
										}
										break;
									case 'n': //!= <ifcbn:> <ifcb!:>
									case '!':
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w != a) multi.br = 1;
										break;
									case 'f': //<ifcbf:>
										if (regex_search(w, wregex(a))) multi.br = 1;
										break;
									case 'F': //<ifcbF:>
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w.find(a) != string::npos) multi.br = 1;
										break;
									case 'l'://<= <ifcbl:> <ifcble:> <ifcb<:> <ifcb<=:> || <ifcblen:>
									case 'L':
									case '<':
										if (check_if_num(a) != L"" && check_if_num(w) != L"") {
											if (qqC.substr(5, 3) == L"len") { //length <ifcblen:> <ifcbleng:>
												unsigned int len = stoi(a);
												if (qqC[8] == '!' || qqC[8] == 'n') { if (w.length() != len) { multi.br = 1; break; } }
												else if (qqC.substr(8, 2) == L"ge" || qqC.substr(8, 2) == L"g=") { if (w.length() >= len) { multi.br = 1; break; } }
												else if (qqC.substr(8) == L"g") { if (w.length() > len) { multi.br = 1; break; } }
												else if (qqC.substr(8, 2) == L"le" || qqC.substr(8, 2) == L"<e" || qqC.substr(8, 2) == L"<=") { if (w.length() <= len) { multi.br = 1; break; } }
												else if (qqC[8] == 'l' || qqC[8] == '<') { if (w.length() < len) { multi.br = 1; break; } }
												else if (qqC[8] == ':' || qqC[8] == 'e' || qqC[8] == '=') { if (w.length() == len) multi.br = 1; break; }//==
												else { a.clear(); break; }
											}
											if (qqC[6] == 'e' || qqC[6] == '=') { if (a == L"0" && w == L"0" || stod(w) <= stod(a)) { multi.br = 1; break; } } //ifcble <=
											if (stod(w) < stod(a)) multi.br = 1;
										}
										break;
									case 'g'://>= <ifcbg:> <ifcbge:> <ifcbg=:>
										if (check_if_num(a) != L"" && check_if_num(w) != L"") {
											if (qqC[6] == 'e' || qqC[6] == '=') { if (a == L"0" && w == L"0" || stod(w) >= stod(a)) { multi.br = 1; break; } } //ifcbge >=/g=
											if (stod(w) > stod(a)) multi.br = 1;
										}
										break;
									default: a.clear(); //f();
									}
								};
							
								wstring tar = a;
								for (; size < length; ++size) { //cout << size << " ifcb:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); clearAllKeys(); strand.clear(); return; }//stop
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											Sleep(450); while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { kbRelease(PauseKey); break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.t; } f(); multi.br = 1; break; }
									OpenClipboard(0);
									hcb = GetClipboardData(CF_UNICODETEXT);
									if (hcb != nullptr) {
										c = static_cast<wchar_t*>(GlobalLock(hcb));
										if (c != nullptr) {
											w = c;
											if (qqC[5] == 'f') sifcb();
											else {
												tar = regex_replace(tar, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  ");
												if (tar.find('|') != string::npos || tar.find('&') != string::npos) {// | &
													wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
													for (size_t j = 0; j < a.length(); ++j) {
														ta += a[j]; //build ta
														if (tar[j] == '|' || tar[j] == '&' || j == a.length() - 1) {
															t = a.substr(ta.length());
															if (t > L"") q = a.substr(j, 1);
															a = t > L"" ? ta.substr(0, ta.length() - 1) : ta;
															a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&");
															if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1); //!\0
															sifcb(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
															if (!multi.br && q == L"&" && t.find('|') != string::npos) {
																t = t.substr(t.find('|') + 1);
																a = t; j = -1; ta.clear(); continue;
															}
															if (!multi.br) {
																if (q == L"&") {
																	sand = 0;
																	if (t.find('|') != string::npos) sand = 1; else { if (!sor || t.find('&') == string::npos) break; }
																}
																if (q == L"|") {
																	sor = 0;
																	if (t.find('&') != string::npos) sor = 1;
																	if (t.find('&') != string::npos && t.find('|') == string::npos) sor = 1;
																}
															}
															if (q == L"&" && multi.br) sand = 1;
															if (q == L"|" && multi.br) { sor = 1; break; } //wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
															multi.br = 0; a = t; j = -1; ta.clear();
															tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  ");
														}
													}
													if (sor && sand) multi.br = 1;
												}
												else {
													if (a.find('\\') != string::npos) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
													sifcb();
												}
											}
											tar = a = app;
											if (multi.br == 1) break;
										}
									}
									CloseClipboard();
									if (!multi.br == 1) {
										if (multiStrand) { ms = multi.m; linkC = multi.l; }
										if (length >= 1) { if (gq[0] && ms[0] != '0') { if (gq.length() == 1) wcout << gq; else showOutsMsg(L"", gq, L"", 1); } Sleep(stoi(ms)); }
										if (linkC[0] == io[0] && linkC.length() == 1 || linkC == L":" || linkC == L"-") --size;
									}
								}
							
								if (multiStrand) {
									i = multi.i_; qqC = multi.q; linkC = multi.l; if (!mF) { tail = multi.t; i += qqC.find('>'); } //rei
								}
								CloseClipboard();
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {//F:
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(' ') != string::npos) 
												linkC = linkC.substr(linkC.find(' ') + 1);//<t-<ifcb:a,*,ms, T: F:>
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<ifcb:a,x,ms,<link->..., <ifcb:a,x,ms,link->
											if (mainn.s1 == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(' ') != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue | Use < in the false slot for continue | <ifcb:a,x,ms,link: <>
									}
									f(); break;
								}
								if (linkC.find(' ') != string::npos) {//T:
									linkC = linkC.substr(0, linkC.find(' '));
									if (linkC == L"<") { if (multiStrand) { i = multi.i_; qqC = multi.q; linkC = multi.l; tail = multi.t; i += qqC.find('>'); } else { rei(); } break; } //true, continue | Use < in the true slot for continue |  <ifcb:a,x,ms,< link:>
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (testqqb(L"<if+")) {//<if+:> | stop if <+>
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); } if (wstring x = qp.substr(0, qp.find(' ')); check_if_num(x) == L"" || !qp[0]) { conn(); break; }
								bool b = 0; int q = stoi(qp.substr(0, qp.find(' ')));
								wstring l = L""; if (qp.find(' ') != string::npos) l = qp.substr(qp.find(' ') + 1);//<if+:# true:>
								switch (qq[4]) {
									default:
									case ':': //==
									case 'e':
									case '=':
										if (multiStrand) { if (multi.icp == q) b = 1; } else { if (ic == q) b = 1; }
										break;
									case 'n': //!=
									case '!':
										if (multiStrand) { if (multi.icp != q) b = 1; } else { if (ic != q) b = 1; }
										break;
									case 'l': //<=
									case 'L':
									case '<':
										if (qq[5] == '=' || qq[5] == 'e') {
											if (multiStrand) { if (qp <= to_wstring(multi.icp)) b = 1; } else { if (qp <= to_wstring(ic)) b = 1; }
										} //if+le <=
										else { if (multiStrand) { if (multi.icp < q) b = 1; } else { if (ic < q) b = 1; } }
										break;
									case 'g': //g=
										if (qq[5] == '=' || qq[5] == 'e') {
											if (multiStrand) { if (multi.icp >= q) b = 1; } else { if (ic >= q) b = 1; }
										} //if+ge >=/g=
										else { if (multiStrand) { if (multi.icp > q) b = 1; } else { if (ic > q) b = 1; } }
									}
								if (b) {
									if (l > L"") {
										tail = l[0] == '<' ? l + L">" + qq.substr(qq.find('>') + 1) : L"<" + l + L">";//<if+:# true->
										if (speed > 0) sleep = 0; re = L" "; i = -1; break;
									}
									i = tail.size(); break;
								}
								else rei();
							}
							else if (testqqb(L"<if") && qq[3] != ':' && qq[3] != '-' && qq[3] != io[0]) {//<ift:> | (t)ime, (h)our, (m)in, (s)ec  =|e, !|n, <|l, <=|le, g(>), g=|ge, <ift+:5> | <ifs:+5,> (MultiStrand:1)
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring gq = L""; if (qp[0] == '\'') { auto x = qp.find(qp[0], 1); if (x == string::npos) { gq = qp[0]; qp = qp.substr(1); } else { gq = qp.substr(1, x - 1); qp = qp.substr(gq.length() + 2 + (qp[gq.length() + 2] == ' ')); } }
								if (qp == L"") { conn(); break; }
								wstring a = qp; a = a.substr(0, a.find(','));
								wstring app = a, x = L"1", ms = L"0", linkC; link.clear();//<ift:a,x,ms,link>
								if (qp.find(',') != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(',') + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(',') != string::npos) {
										ms = x.substr(x.find(',') + 1); if (ms == L"") { printq(); break; }
										if (ms.find(',') != string::npos) {
											link = ms.substr(ms.find(',') + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(',')); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(','));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand && !assume) wcout << "Fail: " << OutTab << OutTab << qqC.substr(0, qqC.find('>') + 1) << endl; };
								if (multiStrand) { multi.a = a; multi.x = x; multi.m = ms; multi.l = link; }
								chrono::system_clock::time_point np;
								time_t n{};
								char b[26]{};
								wstring w{}, h{}, m{}, s{};
								if (multiStrand) { x = multi.x; } auto size{ 0 }, length{ stoi(x) };
								int noq = 0; auto pe = [&a, &noq, qqC](int q) {//+= min, sec. <ifm:+5>
									if (a > L"" && a[0] == '+') {
										if (a[0] == '+') a = a.substr(1);
										int x = stoi(a);
										x += noq;
										if (x >= q) {//24|60
											x -= q;
											if (x >= q) noq = 0;
										}
										a = to_wstring(x);
									}
								};
							
								auto sif = [&]() {
									multi.br = 0;
									np = chrono::system_clock::now();
									n = chrono::system_clock::to_time_t(np);
									ctime_s(b, sizeof(b), &n);
									w.clear(); for (auto i = 0; i < 26; ++i) {
										if (b[i] == '\n') break;
										if (b[i] == ':') continue;
										w += b[i];
									}
									w = w.substr(w.rfind(L" ") - 6, 6);
									if (multiStrand) { a = multi.a; qqC = multi.q; }
									noq = 0;
									switch (qqC[3]) {
									case 't': //time <ift:>
										noq = stoi(w);
										a = regex_replace(a, wregex(L":"), L"");
										break;
									case 'h': //hour <ifh:>
										noq = stoi(w.substr(0, 2));
										pe(24);//+=
										break;
									case 'm': //min <ifm:>
										noq = stoi(w.substr(2, 2));
										pe(60);
										break;
									case 's': //sec <ifs:>
										noq = stoi(w.substr(4, 2));
										pe(60);
									}
									if (multiStrand) multi.a = a;
									int ans = 0, aa = stoi(a);
									switch (qqC[4]) {
									case '+': //+= hr, min, sec <ifm+:5>
										multi.m = L"0";
										{ int t = aa;
										if (qqC[3] == 'm' || qqC[3] == 'h') t *= 60;
										if (qqC[3] == 'h') t *= t;
										Sleep(t * 1000);
										ans = 1; }
										break;
									default:
									case ':': //==
									case 'e':
									case '=':
										if (noq == aa) ans = 1;
										break;
									case 'n': //!=
									case '!':
										if (noq != aa) ans = 1;
										break;
									case 'l': //<=
									case 'L':
									case '<':
										if (qqC[5] == '=' || qqC[5] == 'e') { if (noq <= aa) ans = 1; } //ifcble <=
										else if (noq < aa) ans = 1;
										break;
									case 'g': //g=
										if (qqC[5] == '=' || qqC[5] == 'e') { if (noq >= aa) ans = 1; } //ifcbge >=/g=
										else if (noq > aa) ans = 1;
										break;
									}
									if (ans == 1) multi.br = 1;
								};
							
								for (; size < length; ++size) { //cout << size << " iftime:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); clearAllKeys(); strand.clear(); return; }//stop
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											Sleep(450); while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { kbRelease(PauseKey); break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.t; } f(); multi.br = 1; break; }

									if (multiStrand) { a = multi.a; qqC = multi.q; }
									if (a.find('|') != string::npos || a.find('&') != string::npos) {//<t-<ifh:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {// | &
											ta += a[j];
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1) : ta;
												if (a[0] == ' ') a = a.substr(1);
												sif();
												if (!multi.br && q == L"&" && t.find('|') != string::npos) {
													t = t.substr(t.find('|') + 1);
													a = t; j = -1; ta.clear(); continue;
												}
												if (!multi.br) {
													if (q == L"&") { sand = 0; 
														if (t.find('|') != string::npos) sand = 1; else { if (!sor || t.find('&') == string::npos) break; }
													}
													if (q == L"|") { sor = 0;
													if (t.find('&') != string::npos) { sor = 1; }
													if (t.find('&') != string::npos && t.find('|') == string::npos) { sor = 1; }
													}
												}
											
												if (q == L"&" && multi.br) { sand = 1; }
												if (q == L"|" && multi.br) { 
													sor = 1; break;
												}

												multi.br = 0;
												a = t; j = -1;
												ta.clear();
											}
										}
										if (sor && sand) multi.br = 1;
									}
									else sif();
									if (!multiStrand) a = app;
									if (multi.br == 1) break;
									else {
										if (multiStrand) { ms = multi.m; linkC = multi.l; }
										if (length >= 1) { if (gq[0] && ms[0] != '0') { if (gq.length() == 1) wcout << gq; else showOutsMsg(L"", gq, L"", 1); } Sleep(stoi(ms)); }
										if (linkC[0] == io[0] && linkC.length() == 1 || linkC == L":" || linkC == L"-") --size;
									}
								}
								if (multiStrand) {
									i = multi.i_; qqC = multi.q; linkC = multi.l; if (!mF) { tail = multi.t; i += qqC.find('>'); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(' ') != string::npos)
												linkC = linkC.substr(linkC.find(' ') + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<iftime:a,x,ms,<link->..., <iftime:a,x,ms,link->
											if (mainn.s1 == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(' ') != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(' ') != string::npos) {
									linkC = linkC.substr(0, linkC.find(' '));
									if (linkC == L"<") { if (multiStrand) { i = multi.i_; qqC = multi.q; linkC = multi.l; tail = multi.t; i += qqC.find('>'); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else conn();
							break;
						case 'n':
							if (qqb(L"<ins")) kbPress(multi, L"<ins", VK_INSERT);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'l':
						switch (qq[2]) {
						case 'o'://lowercase cb
							if (qqb(L"<lower>")) {
								wstring s = L"", c = L""; c = cbGet(); for (size_t x = 0; x < c.length(); x++) { s += tolower(c[x]); } cbSet(s); rei(); }
							else conn();
							break;
						case 'c':
							if (qqb(L"<lc")) kbPress(multi, L"<lc", VK_F7);//left click
							else conn();
							break;
						case 'h':
							if (qqb(L"<lh>")) {//left hold
								mouseEvent(MOUSEEVENTF_LEFTDOWN);
								rei();
							}
							else conn();
							break;
						case 'r':
							if (qqb(L"<lr>")) {//left release
								mouseEvent(MOUSEEVENTF_LEFTUP);
								rei();
							}
							else conn();
							break;
						case 'e':
							if (qqb(L"<left")) kbPress(multi, L"<left", VK_LEFT);
							else conn();
							break;
						case 's':
							if (qqb(L"<ls")) { kbPress(multi, L"<ls", VK_F7); }//hscroll+
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'm':
						switch (qq[2]) {
						case 'l':
							if (qqb(L"<ml>")) {//print multiLineDelim
								tail = multiLineDelim[0] + qq.substr(qq.find('>') + 1, qq.length());
								i = -1;
								if (speed > 0) sleep = 0;
								re = L" ";
							}
							else conn();
							break;
						case 's':
							if (qqb(L"<ms:")) if (check_if_num(qp) != L"") { multi.t = tail; Sleep(stoi(qp)); if (multiStrand) rei(multi); else rei(); }
							else printq();
							else conn();
							break;
						case 'c':
							if (qqb(L"<mc")) kbPress(multi, L"<mc", VK_F7);//middle click
							else conn();
							break;
						case 'h':
							if (qqb(L"<mh>")) {//middle hold
								mouseEvent(MOUSEEVENTF_MIDDLEDOWN);
								rei();
							}
							else conn();
							break;
						case 'r':
							if (qqb(L"<mr>")) {//middle release
								mouseEvent(MOUSEEVENTF_MIDDLEUP);
								rei();
							}
							else conn();
							break;
						case 'e':
							if (qqb(L"<menu")) kbPress(multi, L"<menu", VK_APPS);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'p':
						switch (qq[2]) {
						case 'a':
							if (qqb(L"<pause")) { kbPress(multi, L"<pause", VK_PAUSE); GetAsyncKeyState(VK_PAUSE); }
							else conn();
							break;
						case 's':
							if (qqb(L"<ps")) kbPress(multi, L"<ps", VK_SNAPSHOT);
							else conn();
							break;
						case 'u':
							if (qqb(L"<pu")) kbPress(multi, L"<pu", VK_PRIOR);//pgup
							else conn();
							break;
						case 'd':
							if (qqb(L"<pd")) kbPress(multi, L"<pd", VK_NEXT);//pgdn
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'R':
					case'r':
						switch (qq[2]) {
						case ':':
							if (testqqb(L"<R:") || testqqb(L"<r:")) {//.h ReplacerDb:
								if (qq[1] == 'R') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(qp, L"", L"", 0); }
								qp = regex_replace(qp, wregex(L"/"), L"\\");
								replacerDb = qp;
								rei();
							}
							else conn();
							break;
						case 'p':
							if (qqb(L"<rp>")) {//return pointer
								SetCursorPos(qxc, qyc);
								rei();
							}
							else conn();
							break;
						case 'a':
							if (qqb(L"<rand:") || qqb(L"<rand>") || qqb(L"<Rand>") || qqb(L"<Rand:")) {//<rand:0,1>
								randn();
							}
							else conn();
							break;
						case 'c':
							if (qqb(L"<rc")) kbPress(multi, L"<rc", VK_F7); else conn();
							break;
						case 'h':
							if (qqb(L"<rh>")) {//right hold
								mouseEvent(MOUSEEVENTF_RIGHTDOWN);
								rei();
							}
							else conn();
							break;
						case 'r':
							if (qqb(L"<rr>")) {//right release
								mouseEvent(MOUSEEVENTF_RIGHTUP);
								rei();
							}
							else conn();
							break;
						case 'i':
							if (qqb(L"<right")) kbPress(multi, L"<right", VK_RIGHT); else conn();
							break;
						case 's':
							if (qqb(L"<rs")) { kbPress(multi, L"<rs", VK_F7); } else conn();//hscroll-
							break;
						case 'G':
						case 'g':
							if (testqqb(L"<RGB~:") || testqqb(L"<RGB:") || testqqb(L"<rgb:")) { //<rgb:r g b,x,ms,link>
								if (multiStrand) qp = multi.qp;
								if (multiLineDelim[0] != '\\') { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring gq = L""; if (qp[0] == '\'') { auto x = qp.find(qp[0], 1); if (x == string::npos) { gq = qp[0]; qp = qp.substr(1); } else { gq = qp.substr(1, x - 1); qp = qp.substr(gq.length() + 2 + (qp[gq.length() + 2] == ' ')); } }//<rgb:'loop msg'
								if (qp == L"") { conn(); break; }
								wstring r, g, b, a = qp, x = L"1", ms = L"0", linkC; link.clear();
								r = qp.substr(0, qp.find(' '));
								b = qp.substr(qp.find(' ') + 1);
								g = b.substr(0, b.find(' '));
								b = b.substr(b.find(' ') + 1);
								if (b.find(',') != string::npos) {//x,ms
									ms = L"333";
									x = b; b = b.substr(0, b.find(','));
									x = x.substr(x.find(',') + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(',') != string::npos) {
										ms = x.substr(x.find(',') + 1); if (ms == L"") { printq(); break; }
										if (ms.find(',') != string::npos) {
											link = ms.substr(ms.find(',') + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(',')); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(','));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << r << " " << g << " " << b << " " << x << " " << ms << " " << link << endl;
								a = r + L" " + g + L" " + b;
								wstring app = a;
								if (check_if_num(r) == L"" || check_if_num(g) == L"" || b.find(' ') == string::npos && check_if_num(b) == L"") { printq(); break; }
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand && !assume) wcout << "Fail: " << OutTab << OutTab << qqC.substr(0, qqC.find('>') + 1) << endl; };
								if (multiStrand) { multi.a = a; multi.r = r; multi.g = g; multi.b = b; multi.x = x; multi.m = ms; multi.l = link; }
								if (multiStrand) { x = multi.x; } auto size{ 0 }, length{ stoi(x) };

								auto sifrgb = [&multi, &r, &g, &b, &qqC]() {
									multi.br = 0;
									POINT pt; COLORREF color; HDC hDC;
									hDC = GetDC(NULL); GetCursorPos(&pt);
									if (multiStrand) { r = multi.r; g = multi.g; b = multi.b; }
									if (qqC[1] == 'R') { if (multiStrand) { qxc = multi.cx; qyc = multi.cy; } color = GetPixel(hDC, int(qxc * RgbScaleLayout), int(qyc * RgbScaleLayout)); } else { color = GetPixel(hDC, int(pt.x * RgbScaleLayout), int(pt.y * RgbScaleLayout)); }
									ReleaseDC(NULL, hDC);
									if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b.substr(0, b.find(' ')))) {
										multi.br = 1;
										if (multiStrand) qq = multi.q;
										if (qq[4] == '~') {
											POINT pt; GetCursorPos(&pt); qxcc = pt.x; qycc = pt.y;//<RGB~:>
											if (multiStrand) { qxc = multi.cx; qyc = multi.cy; } SetCursorPos(qxc, qyc);
										}
									}
								};

								for (; size < length; ++size) {
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); strand.clear(); return; }//stop
										GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {
											showOutsMsg(L"", OutsTemplate, L"PAUSE\n", 1);
											pause_resume = 1;
											wstring q = L"~PAUSE\n"; speed = 0;
											Sleep(450); while (pause_resume) {
												GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) { kbRelease(PauseKey); break; }
												GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; q = L"~ESC\n"; kbRelease(VK_ESCAPE); break; }
												if (!esc_pressed) Sleep(150);
											}
											showOutsMsg(L"", OutsTemplate, q, 1);
											if (q[1] == 'E') break;
											if (multiStrand) { tail = multi.t; i = multi.i_; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.t; } f(); break; }
									
									
									if (multiStrand) a = multi.a;
									if (a.find('|') != string::npos || a.find('&') != string::npos) {//<t-<rgb:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1) : ta; 
												if (a[0] == ' ') a = a.substr(a.find_first_not_of(' '));
												r = a.substr(0, a.find(' '));
												b = a.substr(a.find(' ') + 1);
												g = b.substr(0, b.find(' '));
												b = b.substr(b.find(' ') + 1);
												if (multiStrand) { multi.r = r; multi.g = g; multi.b = b; }
												if (b.find(' ') != string::npos) {//X Y
													wstring sx = b.substr(b.find(' ') + 1);
													wstring sy = sx.substr(sx.find(' ') + 1);
													if (sx != L"" && sy != L"") {
														sx = sx.substr(0, sx.find(' '));
														b = b.substr(0, b.find(' ')); if (multiStrand) { multi.b = b; }
														if (qqC[1] == 'R') {
															qxc = stoi(sx); qyc = stoi(sy);	if (multiStrand) { multi.cx = qxc; multi.cy = qyc; }
														}
														else SetCursorPos(stoi(sx), stoi(sy));
													}
												}
												sifrgb();

												if (!multi.br && q == L"&" && t.find('|') != string::npos) {
													t = t.substr(t.find('|') + 1);
													a = t; j = -1; ta.clear(); continue;
												}

												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find('|') != string::npos) sand = 1; else { if (!sor || t.find('&') == string::npos) break; }
													}
													if (q == L"|") {
														sor = 0;
														if (t.find('&') != string::npos) { sor = 1; }
														if (t.find('&') != string::npos && t.find('|') == string::npos) { sor = 1; }
													}

												}

												if (q == L"&" && multi.br) { sand = 1; }
												if (q == L"|" && multi.br) {
													sor = 1; break;
												}

												multi.br = 0;
												a = t; j = -1;
												ta.clear();
											}
										}
										if (!multiStrand) a = app;
										if (sor && sand) multi.br = 1;
									}
									else {
										if (b.find(' ') != string::npos) {//X Y
											auto sx = b.substr(b.find(' ') + 1);
											auto sy = sx.substr(sx.find(' ') + 1);
											sx = sx.substr(0, sx.find(' '));
											if (qqC[1] == 'R') {
												qxc = stoi(sx); qyc = stoi(sy);	if (multiStrand) { multi.cx = qxc; multi.cy = qyc; }
											}
											else SetCursorPos(stoi(sx), stoi(sy));
										}
										sifrgb();
									}
									if (multi.br == 1) break;
									else {
										if (multiStrand) { ms = multi.m; linkC = multi.l; }
										if (length >= 1) { if (gq[0] && ms[0] != '0') { if (gq.length() == 1) wcout << gq; else showOutsMsg(L"", gq, L"", 1); } Sleep(stoi(ms)); }
										if (linkC[0] == io[0] && linkC.length() == 1 || linkC == L":" || linkC == L"-") --size;
									}
								}

								if (multiStrand) {
									i = multi.i_; qqC = multi.q; linkC = multi.l; if (!mF) { tail = multi.t; i += qqC.find('>'); } //rei
								}
								if (size >= length) {
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(' ') != string::npos)
												linkC = linkC.substr(linkC.find(' ') + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
											if (mainn.s1 == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(' ') != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(' ') != string::npos) {
									linkC = linkC.substr(0, linkC.find(' '));
									if (linkC == L"<") { if (multiStrand) { i = multi.i_; qqC = multi.q; linkC = multi.l; tail = multi.t; i += qqC.find('>'); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find('>') + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (qqb(L"<rgb>")) {//print r g b
								tail = getRGB(1) + qq.substr(qq.find('>') + 1, qq.length());
								i = -1;
								if (speed > 0) sleep = 0;
								re = L" ";
							}
							else if (testqqb(L"<RGB") || testqqb(L"<rgb") && qq[4] != '~') {// << RGBXY to cb | <RGB> <RGB|> <RGB&> | <RGB|3,> <RGB|3~> | -xy if lowercase, 3sec
								if (qq[5] == ':' && qq[6] == '>') { rei(); conn(); }
								if (testqqb(L"<rgbxy>") || qqb(L"<rgbxy:>")) { getRGB(1, 1); rei(); break; }//rshift + esc + r
								wstring w; switch (qq[4]) {
								case 'x':
								case 'X':
									w += qq.substr(7);
									break;
								case '|':
								case '&':
									w += qq.substr(5);
									break;
								}

								wstring b = L""; if (w[w.size() - 2] == ',' || w[w.size() - 2] == '~') { 
									b = w[w.size() - 2];
								}

								w = w.substr(0, w.find_first_of(L"~,>"));
								
								if (check_if_num(w) == L"") w = L"0";
								size_t n = stoi(w);

								auto t = qq.substr(0, 4); if (b[0] == ',' && Loop_Insert_Text == L"") t = L"";
								
								wstring rgb = getRGB(1), rgbc = rgb, 
									h = t +
									(b[0] == '~' && qq[1] == 'R' ? L"~" : L"") +
									(t > L"" ? L": " : L"") + (qq[4] == 'X' ? qx + L" " + qy : qq[4] == 'x' ? rgb + L" " + qx + L" " + qy : rgb), hq;

								if (showStrand) wcout << h;
								wstring hh = h.substr(0, h.find_first_of(L":") + 1);
								for (size_t i = 0; i < (n * 10); ++i) {// <rgb|3>
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { GetAsyncKeyState(VK_ESCAPE); break; }
									
									Sleep(96);
									if (qq[4] == 'X') {
										POINT pt; GetCursorPos(&pt);
										auto x = to_wstring(pt.x);
										auto y = to_wstring(pt.y);
										if (qx == x && qy == y) continue;
										hq = L" " + qq.substr(6, 1) + L" " + to_wstring(pt.x) + L" " + to_wstring(pt.y);
										qx = x;
										qy = y;
										if (showStrand) wcout << hq;

									}
									else {
										rgb = getRGB(1);
										if (rgb == rgbc) continue;
									}

									switch (qq[4]){
									case 'x':
										hq = L" " + qq.substr(6, 1) + L" " + rgb + L" " + qx + L" " + qy;
										break;
									case 'X':
										hq = L" " + qq.substr(6, 1) + L" " + qx + L" " + qy;
										break;
									case '&':
									case '|':
										hq = L" " + qq.substr(4, 1) + L" " + rgb;
										break;
									}
									h += hq;

									if (showStrand) wcout << hq;
									
									if (qq[4] != 'X') 
										rgbc = rgb;
								}
								
								//<RGBXY&2> hoverless
								if (qq[4] == 'X') {
									if (showStrand) cout << ">";
									Sleep(DWORD((n * 1024 > 2048) ? DWORD(n * 1024) : 2048));

									if (h.find(L":") != string::npos) h = h.substr(h.find_first_of(L":") + 2);

									wstring hc = h;
									wstring hcc = L"";
									wstring xxc = L"";
									wstring yyc = L"";
									COLORREF color; HDC hDC;
									for (size_t i = 0; i < hc.size(); ++i) {
										hDC = GetDC(NULL);
										if (hDC != NULL) {
											xxc = hc.substr(0, hc.find(L" "));
											yyc = hc.substr(hc.find(L" "));
											if (yyc.find(L"|") != string::npos || yyc.find(L"&") != string::npos) {
												yyc = yyc.substr(1, yyc.find(L" ", 1));
											}
											color = GetPixel(hDC, int(stoi(xxc) * RgbScaleLayout), int(stoi(yyc) * RgbScaleLayout));
											ReleaseDC(NULL, hDC);
											if (color != CLR_INVALID) {
												wstring c = to_wstring(GetRValue(color)) + L" " + to_wstring(GetGValue(color)) + L" " + to_wstring(GetBValue(color));
												if (bool a{ hc.find('|') != string::npos }, b{ hc.find('&') != string::npos }; a || b) {
													hcc += c + L" " + xxc + L" " + yyc; if (a) { hcc += L"| "; } if (b) { hcc += L"& "; }
													hc = hc.substr(hc.find_first_of(L"&|") + 2);
												}
												else {
													hcc += c + L" " + xxc + yyc;
													hc = L"";
													h = hh + L" " + hcc;
												}
												i = 0;
											}
										}
									}
								}
								if (showStrand) { if (qq[4] != 'X') cout << '>'; cout << '\n'; }
								
								//filter
								wstring q = L"", c = L"";
								size_t i = 0, x = b[0] == '~';
								wstring r = L"\\" + qq.substr(4, 1) + L"  \\" + qq.substr(4, 1), s = L" \\" + qq.substr(4, 1) + L" $";
								while (h.find(qq[4]) != string::npos) {
									if (!i) { q = h.substr(x + 6);
											  q = q.substr(0, q.find(qq[4]) + 2);
									} else q = h.substr(0, h.find(qq[4]) - 1);
									if (!i) h = h.substr(x + 6 + q.length()); else h = h.substr(h.find(qq[4]) + 2);
									if (h.find(q) != string::npos || ((h + L" " + qq[4] + L" ").find(q)) != string::npos) {
										if (((h + L" " + qq[4] + L" ").find(q)) != string::npos) h = regex_replace(h, wregex(q.substr(0, q.length() - 3)), L""); else
										h = regex_replace(h, wregex(q), L"");
										h = regex_replace(h, wregex(r), qq.substr(4, 1));
										h = regex_replace(h, wregex(s), L"");
									}
									if (!i) c += q; else c += q + L" " + qq.substr(4, 1) + L" ";
									++i;
								}
								if (c[0]) {
									c += h;
									h = c.substr(0, c.length());
									h = regex_replace(h, wregex(s), L"");
								}
								else {
									h += (Loop_Insert_Text == L"" && b[0] == ',' ? L"" : Loop_Insert_Text > L"" ? Loop_Insert_Text : L">");
									cbSet(h);
									rei();
									break;
								}
								if (b[0] == ',' || b[0] == '~') {
									h = t + h + (Loop_Insert_Text == L"" && b[0] == ',' ? L"" : Loop_Insert_Text > L"" ? Loop_Insert_Text : L">");
								}

								rei();
							}
							else conn();
							break;
						case 'e':
							if (testqqb(L"<replace:")) {
								if (cbGet() > L"") {
									if (qp.find(L"\\,") != wstring::npos) {// \,
										wstring t = qp.substr(qp.find_last_of(L"\\") + 2);
										if (t.find(',') != string::npos) {
											qx = qp.substr(0, qp.find_last_of(L"\\") + t.find(',') + 2);
											qy = qp.substr(qx.length() + 1);
											qx = regex_replace(qx, wregex(L"\\\\,"), L",");// \,
										}
									}
									qx = regex_replace(qx, wregex(L"\\\\g"), L">"); qx = regex_replace(qx, wregex(L"\\\\m"), multiLineDelim);
									qy = regex_replace(qy, wregex(L"\\\\g"), L">"); qy = regex_replace(qy, wregex(L"\\\\m"), multiLineDelim);
									wstring c = regex_replace(cbGet(), wregex(qx), qy);
									cbSet(c);
								}
								rei();
							}
							else if (ManualRepeat && qqb(L"<repeat>")) {
								reTail = tail = pre;
								repeat();
								i = tail.length() + 1;
							}
							else conn();
							break;
						default:
							conn();
						}
						break;
					case's':
					case'S':
						switch (qq[2]) {
						case 'E':
						case 'e':
							if (testqqb(L"<SE:") || testqqb(L"<se:")) {//.h Switch Settings: file
								if (qq[1] == 'S') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(qp, L"", L"", 0); }
								qp = regex_replace(qp, wregex(L"/"), L"\\");
								wifstream f(qp); if (!f) { showOutsMsg(L"\nSettings \"", qp, L"\" not found!", 0); return; }
								settings = qp;
								se = settings.substr(settings.find_last_of('\\') + 1) + L" - ";
								loadSe();
								rei();
								break;
							}
							else if (qqb(L"<se>") || qqb(L"<SE>")) { printSe(); rei(); }
							else conn();
							break;
						case 'h':
							if (qqb(L"<shift>")) { kbHold(VK_LSHIFT); rei(); }
							else if (qqb(L"<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
							else if (qqb(L"<shift")) kbPress(multi, L"<shift", VK_LSHIFT);
							else conn();
							break;
						case 'l':
							if (testqqb(L"<sleep:")) if (check_if_num(qp) != L"") { multi.t = tail; Sleep(stoi(qp)); if (multiStrand) rei(multi); else rei(); } else printq();
							else if (qqb(L"<sl")) { kbPress(multi, L"<sl", VK_F7); }//scroll left
							else conn();
							break;
						case 'p':
							if (testqqb(L"<speed:")) { 
								if (check_if_num(qp) != L"") { 
									wstring n = qp;
									if (n[0] == ' ') n = n.substr(1); 
									if (n[0] == '<' && n.substr(1, 5) == L"rand:") {//<speed: <rand: 0, 1111>>
										setQxQy(n, 6);
										i += 1;
										n = randn(1);
										if (n == L"0") { i += qq.find('>'); return; }
									}
									speed = stoi(n); rei(); sleep = 0;
								}
								else printq();
							}
							else if (qqb(L"<space")) kbPress(multi, L"<space", VK_SPACE);
							else conn();
							break;
						case 'd':
							if (qqb(L"<sd")) { kbPress(multi, L"<sd", VK_F7); }//scroll down
							else conn();
							break;
						case 'r':
							if (qqb(L"<sr")) { kbPress(multi, L"<sr", VK_F7); }//scroll right
							else conn();
							break;
						case 'u':
							if (qqb(L"<su")) { kbPress(multi, L"<su", VK_F7); }//scroll up
							else conn();
							break;
						default:
							conn();
						}
						break;
					case't':
						if (qqb(L"<tab")) kbPress(multi, L"<tab", VK_TAB);
						else if (qqb(L"<time>") || qqb(L"<time:>")) {
							wstring w{}; getTime(w);
							if (qq[5] == '>') w = w.substr(w.rfind(L" ") - 8, 8);
							tail = w + qq.substr(qq.find('>') + 1, qq.length());
							i = -1;
							if (speed > 0) sleep = 0;
							re = L" ";
						}
						else conn();
						break;
					case'u':
						if (qqb(L"<upper>")) { wstring s = L"", c = L""; c = cbGet(); for (size_t x = 0; x < c.length(); x++) { s += toupper(c[x]); } cbSet(s); rei(); }
						else if (qqb(L"<up")) kbPress(multi, L"<up", VK_UP);
						else conn();
						break;
					case 'v':
						if (qqb(L"<v>")) { toggle_visibility(); rei(); }
						else conn();
						break;
					case'w':
						if (qqb(L"<win>")) { kbHold(VK_LWIN); rei(); }
						else if (qqb(L"<win->")) { kbRelease(VK_LWIN); rei(); }
						else if (qqb(L"<win")) kbPress(multi, L"<win", VK_LWIN);
						else conn();
						break;
					case'X':
					case'x':
						switch (qq[2]) {
						case 'y':
							if (testqqb(L"<xy:")) {
								if (multiLineDelim[0] != '\\' && qx[0] == '\n' || qx[0] == '\t' || qy[0] == '\n' || qy[0] == '\t') {
									qx = regex_replace(qx, wregex(L"\n"), L""); qx = regex_replace(qx, wregex(L"\t"), L"");
									qy = regex_replace(qy, wregex(L"\n"), L""); qy = regex_replace(qy, wregex(L"\t"), L"");
								}
								if (qx[0] == '.' || qy[0] == '.') {//Use . for current pt | <xy:. 0>  <t-<ifxy:0 . | . 0 | . 864 | 1638 .,1,1000,:>1
									POINT pt; GetCursorPos(&pt);
									qx == L"." ? qx = to_wstring(pt.x) : qy = to_wstring(pt.y);
								}
								SetCursorPos(stoi(qx), stoi(qy)); rei();
							}
							else if (qqb(L"<xy>")) {//print pointer
								POINT pt; GetCursorPos(&pt);
								tail = to_wstring(pt.x) + L" " + to_wstring(pt.y) + qq.substr(qq.find('>') + 1, qq.length());
								i = -1;
								if (speed > 0) sleep = 0;
								re = L" ";
							}
							else conn();
							break;
						case 'Y':
							if (qqb(L"<XY>")) {//return pointer
								SetCursorPos(qxc, qyc); rei();
							}
							else if (testqqb(L"<XY:")) {//set return pointer
								qxc = stoi(qx); qyc = stoi(qy); rei();
							}
							else conn();
							break;
						case ':':
							if (testqqb(L"<x:")) {//x + or - 1px
								if (qp == L"") { conn(); break; }
								if (check_if_num(qp) != L"") {
									POINT pt; GetCursorPos(&pt);
									SetCursorPos(stoi(qp) + (int)(pt.x), (int)(pt.y));
									rei();
								}
								else printq();
							}
							else conn();
							break;
						default:
							conn();
						}
						break;
					case 'y':
						if (testqqb(L"<yesno:")) {
							multi.t = tail;
							int m = MessageBoxW(0, qp.c_str(), L"dnaspider", MB_YESNO);
							if (m == IDYES) { if (multiStrand) rei(multi); else rei(); continue; }
							else { i = tail.length(); break; }
						}
						else if (testqqb(L"<y:")) {//y + or - 1px
							if (qp == L"") { conn(); break; }
							if (check_if_num(qp) != L"") {
								POINT pt; GetCursorPos(&pt);
								SetCursorPos((int)(pt.x), stoi(qp) + (int)(pt.y));
								rei();
							}
							else printq();
						}
						else conn();
						break;
					default:
						conn();
					}//<x>
					break;
				default:
					if (multiLineDelim[0] != '\\') { if (ctail[0] == '\t' || ctail[0] == '\n') { sleep = 0; continue; } }
					if ((ctail[0] >= 33 && ctail[0] <= 38) || (ctail[0] >= 40 && ctail[0] <= 43) || ctail[0] == 58 || (ctail[0] >= 62 && ctail[0] <= 90) || ctail[0] == 94 || ctail[0] == 95 || (ctail[0] >= 123 && ctail[0] <= 126)) { shft = true; }//if !"#$%& ()*+ : > ?&AZ ^ _ {|}~
					if (shft) kbHold(VK_LSHIFT);
					if (multiStrand) { tail = multi.t; i = multi.i_; ctail = tail.substr(i, 1); }
					kb(ctail[0]);
					if (shft) shftRelease();
					
					auto x = (int)ctail[0];
					switch (ctail[0]) {
					case ' ': x = VK_SPACE; break;
					case '0':
					case ')': x = 48; break;
					case '1':
					case '!': x = 49; break;
					case '2':
					case '@': x = 50; break;
					case '3':
					case '#': x = 51; break;
					case '4':
					case '$': x = 52; break;
					case '5':
					case '%': x = 53; break;
					case '6':
					case '^': x = 54; break;
					case '7':
					case '&': x = 55; break;
					case '8':
					case '*': x = 56; break;
					case '9':
					case '(': x = 57; break;
					case '_':
					case '-': x = VK_SUBTRACT; break;
					case '+':
					case '=': x = VK_OEM_PLUS; break;
					case '{':
					case '[': x = VK_OEM_4; break;
					case '}':
					case ']': x = VK_OEM_6; break;
					case '|':
					case '\\': x = VK_OEM_5; break;
					case ':':
					case ';': x = VK_OEM_1; break;
					case '"':
					case '\'': x = VK_OEM_7; break;
					case '<':
					case ',': x = VK_OEM_COMMA; break;
					case '>':
					case '.': x = VK_OEM_PERIOD; break;
					case '?':
					case '/': x = VK_OEM_2; break;
					case '~':
					case '`': x = VK_OEM_3; break;
					default:
					{
						if (ctail[0] > 96 && ctail[0] < 123)
							x -= 32; //a-z
					}
					}
					GetAsyncKeyState(x);
				}
			}
			
			if (!close_ctrl_mode && !noClearStrand && strand == sv && tail == L"") break;//x

			if (strand[0] || re[0]) {
				if (re == L"" || re == L" " || strandLengthMode) { re.clear(); reTail = tail = codes; }
				clearAllKeys();
				if (!noClearStrand && strand == sv) strand.clear();
			}
			if (speed > 0) speed = 0;
			break;
		}
	}
	f.close();
	if (!noClearStrand) { if (strand[0] && close_ctrl_mode && strand[0] == '<') { if (strand[strand.length() - 1] != '>') return; codes = tail = reTail = strand.substr(1, strand.length() - 2); } }//dbless repeat
	if (ManualRepeat) { if (reTail.substr(0, 8) != L"<repeat>") pre = reTail; }
	if (toggle_ccm) { toggle_ccm = 0;
		close_ctrl_mode = !close_ctrl_mode;
		if (fallthrough && strand[0]) strand.clear();
	}
}

static void printCtrls() {
	auto enm = [](short s, wstring l = L"") -> wstring {
		switch (s) {
		case 163: return L"RCTRL\t";
		case 145: return L"SCROLL_LOCK";
		case 19: return L"PAUSE_BREAK";
		case 32: return L"SPACEBAR";
		case 123: return L"F12";
		default: return to_wstring(s) + L"\t";
		}
	};
	wcout <<
L"Interface\n"
"?+ESC\t\t\t"			"dnaspider.exe\n"
"ESC\t\t\t"				"Stop\n"
"X+ESC\t\t\t"			"Exit (Or press: CTRL+C or CTRL+BREAK)\n"
"F11\t\t\t"				"Fullscreen\n"
"H+ESC\t\t\t"			"Toggle visibility\n"
"L+ESC\t\t\t"			"Toggle RSHIFT+LSHIFT_Only: 2\n"
<< enm(cKey) <<			L"\t\tToggle < or run (>) (se.txt CtrlKey: " << to_wstring((short)cKey) << " | Or try CtrlKey: 145, RepeatKey: 19, PauseKey: 123, ClearStrandKey: 123 instead/SCRLK, PAUSE, F12)\n"
"COMMA+ESC\t\t"			"< (>)\n"
"RSHIFT+LSHIFT\t\t"		"Toggle < or double press for <\n"
"LSHIFT+CtrlKey\t\t"	"Clear/Reset strand (se.txt LSHIFT+CtrlKey: 9 | Increased for more time. 0 for off)\n"
"RSHIFT+CtrlKey\t\t"	"Toggle se.txt CloseCtrlMode (se.txt RSHIFT+CtrlKey_Toggle: 9 | Increased for more time. 0 for off)\n"
<< enm(ClearStrandKey) << " (LSHIFT)\t\tClear/Reset strand (se.txt ClearStrandKey: " << to_wstring((short)ClearStrandKey) << ")\n"
<< enm(PauseKey) <<		"\t\t\tPause/Resume\n"
"P+ESC\t\t\t"			"<xy:>\n"
"A+ESC\t\t\t"			"<app:>\n"
"R+ESC (SHIFT)\t\t"		"<rgb:> (se.txt RgbScaleLayout: 1.25 | Match with desktop System > Display, Scale & layout, Scale [125%]) | Use LSHIFT for loop, RSHIFT for <rgbxy> copy (3 second delay)\n"
<< enm(reKey) <<		"\t\tRepeat (se.txt RepeatKey: " << to_wstring((short)reKey) << ")\n"
"EQUAL+ESC\n"			"Hold RCTRL, Press LCTRL, Release RCTRL\n"
"\n"
"API\n"
"A-Z 0-9 etc.\t\t"		"dnaspider will press key/run\n"
"\t\t\t"				"<test->A-Z 0-9 etc.\n"
"<connect_line>\t\t"	"Use <line_name:> or <line_name->\n"
"\t\t\t"				"<test1-><test-> (se.txt CloseCtrlMode: 1)\n"
"<db>\t\t\t"			"Print database to console\n"
"\t\t\t"				"<test-><db>\n"
"<se>\t\t\t"			"Load settings\n"
"\t\t\t"				"<test-><SE> \n"
"\t\t\t"				"(se.txt ShowSettings: 1 to print current settings to console if lowercase)\n"
"\t\t\t"				"Or press LCTRL+S inside \"" << editorSe << L"\" (se.txt EditorSe)\n"
"<v>\t\t\t"				"Toggle visibility\n"
"\t\t\t"				"<test-><v>\n"
"<,>\t\t\t"				"150ms sleep (se.txt CommaSleep: 150)\n"
"\t\t\t"				"<test->1<,>1\n"
"<,1>\t\t\t"			"Sleep for\n"
"<ms:1>\t\t\t"			"<test->1<,1000>1\n"
"<sleep:1>\n"
"<xy:0 0>\t\t"			"Move pointer to x y (P+ESC to get)\n"
"\t\t\t"				"Use . for current\n"
"\t\t\t"				"<test-><xy:. 0><rc>\n"
"<x:>\n"
"<y:>\n"
"<xy>\t\t\t"			"Print x y\n"
"<rp>\t\t\t"			"Return pointer/cursor (xy)\n"
"\t\t\t"				"<test-><xy:0 0><,1000><rp>\n"
"<XY:><XY>\t\t"			"Set, return xy\n"
"\t\t\t"				"<test-><xy:0 0><,1000><XY>\n"
"<~><~~>\t\t\t"			"Long set, return cursor (xy)\n"
"\t\t\t"				"<test-><~><connect:><~~>\n"
"<~m>\t\t\t"			"Auto lock/unlock (se.txt MultiStrand: 1)\n"
"<~~m>\t\t\t"			"Enable MultiStrand\n"
"<lc>\t\t\t"			"LEFT, RIGHT, MIDDLE->CLICK, HOLD, RELEASE\n"
"<rc>\n"
"<mc>\n"
"<lh>\n"
"<rh>\n"
"<mh>\n"
"<lr>\n"
"<rr>\n"
"<mr>\n"
"<sl>\t\t\t"			"SCROLL LEFT, UP, RIGHT, DOWN\n"
"<su>\n"
"<sr>\n"
"<sd>\n"
"<ctrl>\t\t\t"			"Hold key\n"
"<shift>\n"
"<alt>\n"
"<win>\n"
"<ctrl->\t\t\t"			"Release key\n"
"<shift->\n"
"<alt->\n"
"<win->\n"
"<up>\t\t\t"			"Press key\n"
"<right>\n"
"<down>\n"
"<left>\n"
"<delete>\n"
"<esc>\n"
"<bs>\n"
"<home>\n"
"<end>\n"
"<space>\n"
"<tab>\n"
"<enter>\n"
"<pause>\n"
"<caps>\n"
"<win1>\t\t\t"			"Press* \n"
"\t\t\t"				"<test><bs4>1\n"
"<menu>\t\t\t"			"MENU key\n"
"<ins>\t\t\t"			"INSERT\n"
"<ps>\t\t\t"			"PRINT_SCREEN\n"
"<pu><pd>\t\t"			"PAGE_UP, PAGE_DOWN\n"
"<f1>\t\t\t"			"F1 (F1-F12) \n"
"<yesno:>\t\t"			"Verify message\n"
"\t\t\t"				"<test-><yesno:Continue?>1\n"
"<beep>\t\t\t"			"Alert sound\n"
"<a:>\t\t\t"			"Codes\n"
"\t\t\t"				"<test-><a:<shift\\g<shift-\\g><left8>\n"
"<speed:>\t\t"			"Output\n"
"\t\t\t"				"<test->1<speed:1000>11\n"
"<+:>\t\t\t"			"Calc. (Set to cb, use ' ')\n"
"<-:>\t\t\t"			"<test-><+: 1>\n"
"<*:>\n"
"</:>\n"
"<%:>\n"
"<+>\t\t\t"				"Print total\n"
"\t\t\t"				"<test-><+><*:7>\n"
"<down+>\t\t\t"			"Variable press* <+>\n"
"\t\t\t"				"<test:><speed:1000><+:1><tab+><test:>\n"
"<bs++>\t\t\t"			"Variable press. Auto increment <+>\n"
"\t\t\t"				"<test-><speed:1000><esc++><<:\\+\\n><test->\n"
"<if+:>\t\t\t"			"Stop if <+> (Use \" \" for true)\n"
"\t\t\t"				"<test-><+:1><<:\\+:)\\n><if+g:3 true:><test->\n"
"\t\t\t"				"<true:>1\n"
"<'>\t\t\t"				"Print to console\n"
"<' >\t\t\t"			"No print\n"
"<''>\t\t\t"			"Ignore rest of line\n"
"<'''>\t\t\t"			"Ignore rest of db \n"
"\t\t\t"				"<test->1<'bs>1<''test>0\n"
"\t\t\t"				"<'''block>\n"
"<app:>\t\t\t"			"Continue if set app to foreground\n"
"\t\t\t"				"Signature: <app:TITLE|TITLE,*,ms,true- else->\n"
"\t\t\t"				"<test-><app:Calculator>1+1<enter>\n"
"\t\t\t"				"Default: <app:'Calculator,1,333,else:>1\n"
"\t\t\t"				"Use | for OR: TITLE|TITLE\n"
"\t\t\t"				"Use \" \" to expand connect option: true- false-\n"
"\t\t\t"				"Use < to reconnect: <true- <false-\n"
"\t\t\t"				"Use < in true or false slot for continue\n"
"\t\t\t"				"Use ' or '?' after : to print to console\n"
"\t\t\t"				"<test-><app:'Calculator,1,150,true- false->\n"
"\t\t\t"				"<true->1+1<enter>\n"
"\t\t\t"				"<false-><win>r<win-><app:Run,9,6>calc<enter><app:Calculator,><,1111><true->\n"
"\t\t\t"				"Signature for loop: (Use - : or ,)\n"
"\t\t\t"				"<app:T,*,ms,->\n"
"\t\t\t"				"<app:T,*,ms,:>\n"
"\t\t\t"				"<app:T,>\n"
"\t\t\t"				"Check, continue: <app:T,*,ms,>\n"
"<App:>\t\t\t"			"Continue if App in foreground\n"
"\t\t\t"				"<test-><App:Calculator,>1+1<enter>\n"
"<app>\t\t\t"			"TITLE to cb\n"
"\t\t\t"				"<test-><speed:1><alt><esc><alt-><app><app:" << L"\u25cf " << db + editor + L" | " + db + editor + L"><ctrl>v<ctrl->\n"
"<rgb:>\t\t\t"			"Continue if rgb in xy location (R+ESC to get)\n"
"\t\t\t"				"Signature <rgb:RED GREEN BLUE X Y,*,ms,true: false:>\n"
"\t\t\t"				"Use & for AND, | for OR\n"
"\t\t\t"				"<test-><rgb:255 255 255 0 0>1\n"
"<RGB:>\t\t\t"			"Continue if RGB in XY location\n"
"\t\t\t"				"<test-><RGB:255 255 255 0 0>1\n"
"<RGB~:>\t\t\t"			"If RGB is true, go to its XY (RSHIFT+R+ESC)\n"
"\t\t\t"				"<test-><RGB~:'loop msg'0 0 0 0 0 | 1 1 1 0 0,><rc>\n"
"<rgb>\t\t\t"			"Print rgb\n"
"\t\t\t"				"<test-><shift>,<shift->rgb:<rgb>>\n"
"<rgbxy&>\t\t"			"rgbxy to cb (Options: & | XY xy , ~)\n"
"\t\t\t"				"<test-><RGBXY&3,>\n"
"\t\t\t"				"Place cursor over target. Run. Then hover over the data you want. When you see > move cursor away\n"
"<cb:>\t\t\t"			"Set clipboard (Auto CTRL+V if CAPS)\n"
"\t\t\t"				"<test-><cb:Test>\n"
"<cl>\t\t\t"			"Cb length\n"
"<ifxy:>\t\t\t"			"Continue if xy\n"
"<ifcb:>\t\t\t"			"Continue if cb ==\n"
"<ifcb!:>\t\t"			"!=\n"
"<ifcbg:>\t\t"			"g\n"
"<ifcbge:>\t\t"			"g=\n"
"<ifcbl:>\t\t"			"<\n"
"<ifcble:>\t\t"			"<=\n"
"<ifcbf:>\t\t"			"Regex find\n"
"<ifcbF:>\t\t"			"Find\n"
"<ifcb+:>\t\t"			"Set <+> to first occurrence (for <up+>)\n"
"<ifcbA:1 x>\t\t"		"Offset find x\n"
"<ifcbS:>\t\t"			"Starts with\n"
"<ifcbE:>\t\t"			"Ends with\n"
"<ifcba:0 1 x>\t\t"		"Find substr\n"
"<ifcblen:>\t\t"		"Length\n"
"\t\t\t"				"Signature: <ifcb:#|#,*,ms,t- f->\n"
"\t\t\t"				"<test-><ifcbge:1>1\n"
"<replace:>\t\t"		"Regex replace (cb)\n"
"\t\t\t"				"<test-><replace:T,t><replace:\\r\\n,>\n"
"<upper>\t\t\t"			"Uppercase (cb)\n"
"<lower>\n"
"<time:>\t\t\t"			"Print timestamp\n"
"<time>\n"
"<ift:>\t\t\t"			"Continue if time\n"
"<ifh:>\t\t\t"			"Hour\n"
"<ifm:>\t\t\t"			"Minute\n"
"<ifs:>\t\t\t"			"Second\n"
"\t\t\t"				"Options: == != < <= g g= +\n"
"\t\t\t"				"Signature: <ifh:#,*,ms,t- f->\n"
"\t\t\t"				"<test-><ifh<=:5>1\n"
"<rand:>\t\t\t"			"Print random #, A-Z, a-z, or A-Za-z\n"
"<Rand>\t\t\t"			"<test-><rand:0,1>\n"
"<rand>\n"
"<Rand:>\n"
"<dna:>\t\t\t"			"Title\n"
"\t\t\t"				"<dna:new>\n"
"<dna>\t\t\t"			"Init.\n"
"\t\t\t"				"<dna><<:Welcome\\n>\n"
"<<:>\t\t\t"			"Custom message\n"
"\t\t\t"				"Options: \n"
"\t\t\t"				"\\1-9\t"	"Color\n"
"\t\t\t"				"\\n\t"		"Newline\n"
"\t\t\t"				"\\t\t"		"Tab\n"
"\t\t\t"				"\\T\t"		"Time\n"
"\t\t\t"				"\\'\t"		"Blank\n"
"\t\t\t"				"\\g\t"		">\n"
"\t\t\t"				"\\c\t"		"Cb\n"
"\t\t\t"				"\\a\t"		"Beep\n"
"\t\t\t"				"\\+\t"		"<+>\n"
"\t\t\t"				"\\d\t"		"Run <+>\n"
"\t\t\t"				"\\m\t"		"<ml>\n"
"\t\t\t"				"<test-><<:<test-\\g>\n"
"<se:>\t\t\t"			"(se.txt Settings)\n"
"\t\t\t"				"<test-><se:c:\\dna\\s.txt>\n"
"<db:>\t\t\t"			"(se.txt Database)\n"
"\t\t\t"				"<test-><DB:c:\\dna\\d.txt> (Print if caps)\n"
"{}\t\t\t"				"Replacer \n"
"{'}\t\t\t"				"{'ignore}\n"
"<r:>\t\t\t"			"(se.txt ReplacerDb)\n"
"\t\t\t"				"<test->{'test}<R:C:\\dna\\db.txt>{test:}<cb:{test:}>\n"
"\t\t\t"				"test:1\n"
"<ml>\t\t\t"			"Print DbMultiLineDelimiter\n"
"<!>\t\t\t"				"No clear strand after run\n"
"<!:>\t\t\t"			"Set strand after run\n"
"<!!:>\t\t\t"			"Multi run\n"
"<!!!:>\t\t\t"			"Set repeat; end\n"
"<~esc>\t\t\t"			"se.txt NoEscapeOrPause: 0\n"
"<~~esc>\t\t\t"			"NoEscapeOrPause: 1\n"
"<#:>\t\t\t"			"ascii_calc to cb\n"
"\t\t\t"				"<test-><#:x>\n"
"<repeat>\t\t"			"(se.txt ManualRepeat: 1)\n"
"\t\t\t"				"<test-><repeat>\n"
"<audio:>\t\t"			"<audio:play c:\\dna\\1.mp3>\n"
"<Audio:>\t\t"			"<Audio:c:\\dna\\1.wav>\n\n"
;}

static void printIntro() {
	if (showIntro) {
		printCtrls();
		printSe();
		printDb();
	}
}

static void key(wstring k) {
	if (multiblock) return;
	bool bk = 0; if (k.size() > 2 && k.find(' ') != string::npos) {
		wstring re = k.substr(k.find(' ') + 1); bool b = re[0] == '\''; if (b) { re = re.substr(1); if (re[0] == '\'') b = 0; }
		k = k.substr(0, k.find(' '));
		if (k[0] == '>' || k[0] == '<') { //qq < (Kb_Key_Q >q '<bs>)
			GetAsyncKeyState(Kb_QQ_k); ++Kb_QQ_i; size_t l = k[1] < 127 ? k.substr(1).length() : k.length() / 2; if (Kb_QQ_i > l) { Kb_QQ_i = 0; if (k[1]) { for (auto i = 0; i < l + 1; ++i) kb(VK_BACK); GetAsyncKeyState(VK_BACK); } if (k[1] && k[1] != ' ') { strand = L"<"; prints(); return; } }
			else {
				if (k[1] && strand[0] != '<') {
					k = k.substr(1); if (k[0] < 127) k = k[0]; else k = k.substr(0, 2); bk = 1;
				}
			} 
		}
		strand.append(strand[0] == '<' && k[0] == '>' ? L">" : k);
		{
			bool y = showMultiStrandElapsedOnly; if (y) showMultiStrandElapsedOnly = 0;
			Store s; if (b && strand[0] == '<' || b && k[0] == '>' && strand.size() > 1) {
				s.v = strand; out(re); strand = s.v;
			}
			else {
				if (!b) {
					s.v = strand; out(re); strand = s.v;
				}
			}
			if (y) showMultiStrandElapsedOnly = y;
		}
	}
	else {
		if (k[0] == '>' && !strand[0]) {}
		else if (k[0] == '>' && strand == L"<") { strand.clear(); prints(); if (RSHIFTLSHIFT_Only) { rri = 1; } return; }
		else strand.append(k);
	}
	if (!bk && Kb_QQ_i > 0) { Kb_QQ_i = 0; } if (strand[0] == '<' && strand[1] == '>' || strand[0] == '>') { prints(); strand = L""; prints(); return; }
	if (k[0] == '<' || k[0] == '>') {
		strand = strand.substr(0, strand.size() - 1);
		if (k[1] == '-') {
			kb(VK_BACK); GetAsyncKeyState(VK_BACK);
			strand = strand.substr(0, strand.size() - 1);
		}
		!strand[0] ? strand.append(L"<") : strand.append(L">");
	}
	else if (strandLengthMode) {
		if (strand[0] != '<' && strand.length() > strandLengthMode) {
			if (strandLengthMode == 1) {
				if (strand != k) strand = strand.substr(size_t((strand[0] > 127) + 1));
			}
			else {
				size_t x = 0;
				for (auto c : strand) { if (c > 127) ++x; }
				if (x > 0) x /= 2;
				x = strand.length() - x;
				if (x > strandLengthMode)
					strand = strand.substr(strand[0] > 127 ? 2 : 1);
			}
		}
	}
	prints();
	if (close_ctrl_mode && strand[strand.length() - 1] != '>') return;
	if (multiStrand) { i = -1; thread thread(scanDb); thread.detach(); Sleep(1); Sleep(CloseCtrlSpacer); rri++; } else scanDb();
	if (!close_ctrl_mode && strand[0] && strand[strand.length() - 1] != '>') return;
	if (!noClearStrand) { strand = L""; } noClearStrand = 0; if (multiStrand) { if (showStrand) wcout.flush().clear(); }
	if (rri) rri = 0;
}

void repeat() {
	if (multiblock) return;
	kbRelease(reKey);
	if (multiStrand) {
		strand = L""; re = L">" + reTail; i = -1; thread thread(out, reTail); thread.detach(); if (showStrand) { wcout.flush().clear(); }
	}  
	else out(tail);
}

#pragma endregion

#pragma comment(lib, "Winmm.lib")//<audio:>
int main() {//cout << "@dnaspider\n\n";
#pragma region initial_startup
	wcout.imbue(locale()); wcout.clear();
	{
		GetAsyncKeyState(VK_ESCAPE); for (i = 0; i <= 1; i++) { if (GetAsyncKeyState(VK_ESCAPE)) break;
			WCHAR t[MAX_PATH]; GetSystemDirectoryW(t, MAX_PATH); wstring c = L""; for (i = 0; ; ++i) { if (t[i] == ':') { c += L":\\dna"; break; } c += t[i]; };//root
			database = c + L"\\db.txt"; settings = c + L"\\se.txt"; replacerDb = database;
			if (CreateDirectoryW(c.c_str(), NULL)) {//L"c:/dna"
				wstring db_ = L"h-Hello\n<e->Enjoy\n<x:><bs><e->!\n\n Getting Started:\n Press H (strand: h),\n RIGHT_CTRL E (strand: <e), \n RIGHT_SHIFT+LEFT_SHIFT X or\n COMMA+ESC X (strand: <x)\n in a text area to run.\n\n Tip:\n Clear strand first by toggling\n RIGHT_CTRL, BACKSPACE, or \n PAUSE_BREAK.\n\n Press keys separately\n (RIGHT_CTRL, release RIGHT_CTRL, X).\n\n Each line in db.txt is a slot for strand:API.\n\n API's are placed in front of the first :, -, >, ->, or :> of each line.\n (?+ESC)\n\n<wr:><win>r<win-><app:run, 1, 6, :>\n<d-><app: \u25cf " + editorDb + L" | " + db + editor + L", 1, 1, odb->\n<odb-><wr:>" + database + L"<enter>\n<s-><app: " + L"\u25cf " + editorSe + L" | " + se + editor + L", 1, 1, <ose->\n<ose-><wr:>" + settings + L"<enter>\n<se-><se><''Update setting  ->  (se.txt CloseCtrlMode: 1)>\n< -<><left>\n<a-<a:<alt\\g<alt-\\g><left6>\n<c-<a:<ctrl\\g<ctrl-\\g><left7>\n<sh-<a:<shift\\g<shift-\\g><left8>\n<w-><a:<win\\g<win-\\g><left6>\n\n RCTRL D: Open " + db.substr(0, db.length() - 2) + L"\n RCTRL S: Open " + se.substr(0, se.length() - 2);
				wstring se_ = L"ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nClearStrandKey: 19\nMultiStrand: 0\nShowMultiStrandElapsedOnly: 0\nOutsTemplate: \\R\\7strand:\\t\\t\\G\nOutTabs: 1\nSettings: " + settings + L"\nDatabase: " + database + L"\nDbMultiLineDelimiter: \\n\nReplacerDb: " + replacerDb + L"\nCtrlKey: 163\nLSHIFT+CtrlKey: 1\nCloseCtrlMode: 0\nCloseCtrlSpacer: 120\nRSHIFT+CtrlKey_Toggle: 0\nCtrlScanOnlyMode: 0\nRSHIFT+LSHIFT_Only: 0\nStrandLengthMode: 0\nRepeatKey: 145\nPauseKey: 123\nAutoBs_RepeatKey: 0\nRgbScaleLayout: 1.00\nFrequency: 150\nIgnore_0-9: 0\nKb_Key_0: 0\nKb_Key_1: 1\nKb_Key_2: 2\nKb_Key_3: 3\nKb_Key_4: 4\nKb_Key_5: 5\nKb_Key_6: 6\nKb_Key_7: 7\nKb_Key_8: 8\nKb_Key_9: 9\nIgnore_A-Z: 0\nKb_Key_A: a\nKb_Key_B: b\nKb_Key_C: c\nKb_Key_D: d\nKb_Key_E: e\nKb_Key_F: f\nKb_Key_G: g\nKb_Key_H: h\nKb_Key_I: i\nKb_Key_J: j\nKb_Key_K: k\nKb_Key_L: l\nKb_Key_M: m\nKb_Key_N: n\nKb_Key_O: o\nKb_Key_P: p\nKb_Key_Q: q\nKb_Key_R: r\nKb_Key_S: s\nKb_Key_T: t\nKb_Key_U: u\nKb_Key_V: v\nKb_Key_W: w\nKb_Key_X: x\nKb_Key_Y: y\nKb_Key_Z: z\nIgnore_Arrows: 1\nKb_Key_Left: L\nKb_Key_Up: U\nKb_Key_Right: R\nKb_Key_Down: D\nKb_Key_Backslash:\nKb_Key_Caps:\nKb_Key_Comma:\nKb_Key_Delete:\nKb_Key_End:\nKb_Key_Enter:\nKb_Key_Esc:\nIgnore_F1-F12: 0\nKb_Key_F1: !\nKb_Key_F2: @\nKb_Key_F3: #\nKb_Key_F4: $\nKb_Key_F5: %\nKb_Key_F6: ^\nKb_Key_F7: &\nKb_Key_F8: *\nKb_Key_F9: (\nKb_Key_F10: )\nKb_Key_F11: _\nKb_Key_F12: +\nKb_Key_Forwardslash:\nKb_Key_Grave_Accent:\nKb_Key_Print_Screen:\nKb_Key_Home:\nKb_Key_Insert:\nKb_Key_Left_Alt:\nKb_Key_Left_Bracket:\nKb_Key_Left_Ctrl:\nKb_Key_Left_Shift:\nKb_Key_Menu:\nKb_Key_Minus:\nKb_Key_Numpad_0:\nKb_Key_Numpad_1:\nKb_Key_Numpad_2:\nKb_Key_Numpad_3:\nKb_Key_Numpad_4:\nKb_Key_Numpad_5:\nKb_Key_Numpad_6:\nKb_Key_Numpad_7:\nKb_Key_Numpad_8:\nKb_Key_Numpad_9:\nKb_Key_Numlock:\nKb_Key_Numpad_Divide:\nKb_Key_Numpad_Multiply:\nKb_Key_Numpad_Minus:\nKb_Key_Numpad_Add:\nKb_Key_Numpad_Period:\nKb_Key_Numpad_Enter:\nKb_Key_PgDn:\nKb_Key_PgUp:\nKb_Key_Period:\nKb_Key_Quote:\nKb_Key_Right_Alt:\nKb_Key_Right_Bracket:\nKb_Key_Right_Ctrl:\nKb_Key_Right_Shift:\nKb_Key_Semicolon:\nKb_Key_Space: \nKb_Key_Tab:\nStartHidden: 0\nSlightPauseInBetweenConnects: 1\nAutoBs_EscH: 1\nAutoBs_EscComma: 1\nAutoBs_EscEqual: 1\nKb_Key_Equal: =\nCommaSleep: 150\nSeHotReload_CtrlS: 1\nSeDbClearStrand_CtrlS: 1\nExit_EscX: 1\nAssume: 0\nUnicode: 1\nEditor: " + editor + L"\nEditor1: " + editor1 + L"\nEditorSe: " + editorSe + L"\nEditorDb: " + editorDb + L"\nLoop_Insert_Text: ,1,1000,->\nNoEscapeOrPause: 0\nio: *\nAutoBs_io: " + (io_Auto_BS ? L"1" : L"0") + L"\nManualRepeat: " + (ManualRepeat ? L"1" : L"0");
				wstring np = L"notepad ";
				wcout << database << " not found.\nPress [1] to auto create, [ESC] pro, [2] hacker.\nTo reset, delete c:\\dna folder then restart program.\n";
				bool num2pressed = 0; for (;; Sleep(150)) { if (GetAsyncKeyState(50) && !num2pressed) { GetAsyncKeyState(50); num2pressed = 1; cout << "Hold [ESC] for hacker mode settings.\n"; } if (GetAsyncKeyState(VK_ESCAPE)) { GetAsyncKeyState(VK_ESCAPE); Sleep(150); if (GetAsyncKeyState(VK_ESCAPE)) {} else { RemoveDirectoryW(c.c_str()); } break; } if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
				if (num2pressed) { cout << "Hacker mode settings enabled.\n";
					db_ = LR"( Internals
 H+ESC  Toggle visibility
 ?+ESC  Help
 X+ESC  Exit

 Use A, C, S, or W RCTRL to run.
al
a <a:<alt\g<alt-\g><left6>
c <a:<ctrl\g<ctrl-\g><left7>
s <a:<shift\g<shift-\g><left8>
w <a:<win\g<win-\g><left6>

 Use RCTRL S E RCTRL to show settings.
 Or use RSHIFT+LSHIFT instead of RCTRL
 (Hold RSHIFT, press LSHIFT, release RSHIFT).
 Can also use S E RCTRL or Q Q S E Q or S E F2
se
<se ><se>

 Use SCLK or RCTRL+LCTRL for repeat.)";
					se_ = LR"(StrandLengthMode		2
StartHidden				1
ShowStrand				0
RSHIFT+LSHIFT_Only		0
Ignore_F1-F12			0
Kb_Key_F2				>
Kb_Key_Q				>q '<bs>
Kb_Key_Period			.
Kb_Key_Comma			,
Kb_Key_Semicolon		;
Kb_Key_Space  
CtrlKey					163 9
CtrlScanOnlyMode		0
RSHIFT+CtrlKey_Toggle	9
RgbScaleLayout			1.0)";
					np = L"";
					Kb_Key_Period = L"."; Kb_Key_Comma = L","; Kb_Key_Semicolon = L";"; Kb_Key_Space = L" "; ignoreF1s = 0; Kb_Key_F2 = L">"; Kb_Key_Q = L">q '<bs>"; RgbScaleLayout = 1.0; strandLengthMode = 2; cKey = VK_RCONTROL; cKeyMax = 9; RSHIFTLSHIFT_Only = 0; qScanOnly = false;
					Sleep(2048); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				}
				wofstream fd(database); fd.imbue(locale(fd.getloc(), new codecvt_utf8_utf16<wchar_t>)); fd << db_; fd.close(); wofstream fs(settings); fs.imbue(locale(fs.getloc(), new codecvt_utf8_utf16<wchar_t>)); fs << se_; fs.close(); out(L"<win>r<win-><app: run, 3, 60, :>" + np + settings + L"<enter><ms: 1500><win>r<win-><app: run, 3, 60, :>" + np + database + L"<enter>"); re.clear(); tail.clear(); strand.clear();
			}
		}
	}
	loadSe();
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	SetConsoleOutputCP(CP_UTF8); wcout.imbue(locale(wcout.getloc(), new codecvt_utf8_utf16<wchar_t>));
	printIntro(); strand = L"<dna>"; if (multiStrand) { thread thread(scanDb); thread.detach(); Sleep(1); } else scanDb(); if (!noClearStrand) { strand.clear(); } noClearStrand = 0; //run @ startup
#pragma endregion
	for (;; this_thread::sleep_for(chrono::milliseconds(frequency))) {
		if (GetAsyncKeyState(VK_BACK)) {
			if (Kb_QQ_i > 0) Kb_QQ_i = 0;
			if (rri && !strand[0]) rri = 0;
			if (strand == L"") continue;
			auto s = sizeof(wchar_t); if (strand[strand.length() - 1] < 127) s /= 2;
			strand = strand.substr(0, strand.length() - s);
			prints(); if (rri && !strand[0]) rri = 0;
			continue;
		}
		if (GetAsyncKeyState(VK_RSHIFT)) {
			unsigned short min = 0; bool ex = 0;
			while (GetAsyncKeyState(VK_RSHIFT) != 0) {
				if (GetAsyncKeyState(VK_LSHIFT)) { //RSHIFT+LSHIFT <
					++rri; unsigned short x = 0;
					while (GetAsyncKeyState(VK_RSHIFT) != 0) {
						if (GetAsyncKeyState(VK_LSHIFT))
							++x;
						while (GetAsyncKeyState(VK_LSHIFT) != 0)
							Sleep(1);
					}
					if (strand[0] && strand != L"<") { key(L">"); prints(); ex = 1; break; }
					else if (x > 1) strand = L"<";
					else if (!strand[0]) { strand = RSHIFTLSHIFT_Only > 1 && rri == 1 ? L"" : L"<"; }
					else if (RSHIFTLSHIFT_Only > 1) strand = L"";
					else strand = strand[0] == '<' ? L"" : L"<";
					prints(); break;
				}
				if (GetAsyncKeyState(VK_ESCAPE)) { //rshift + r + esc
					if (GetAsyncKeyState(82)) {
						kb(VK_BACK);
						qq = L"<rgbxy:>"; getRGB(1, 1);
						ex = 1; break;
					}
				}
				if (GetAsyncKeyState(cKey) && RSHIFTCtrlKeyToggle) {
					if (min >= RSHIFTCtrlKeyToggle) { ex = 1; break; }
					if (cKey == VK_SPACE) kb(VK_BACK);
					close_ctrl_mode = !close_ctrl_mode;
					toggle_ccm = 1;
					ex = 1; break;
				}
				++min;
				Sleep(frequency / 4);
			}
			if (ex) continue;
			clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			continue;
		}
		if (GetAsyncKeyState(VK_LSHIFT)) {
			bool ex = 0; while (GetAsyncKeyState(VK_LSHIFT) != 0) {
				if (LSHIFTCtrlKey) {
					short min = 0; while (GetAsyncKeyState(VK_LSHIFT) != 0) {
						++min;
						if (GetAsyncKeyState(cKey)) { //lshift + ctrlKey
							if (min > LSHIFTCtrlKey) { Sleep(frequency / 4); continue; }
							if (cKey == VK_SPACE) kb(VK_BACK);
							clearAllKeys();
							strand = strand[0] == '<' ? L"<" : L"";
							prints();
							rri = 1;
							while (GetAsyncKeyState(cKey) != 0) Sleep(frequency / 4);
							kbRelease(VK_LSHIFT);
							ex = 1; break;
						}
						if (GetAsyncKeyState(VK_ESCAPE)) break;
						Sleep(frequency / 4);
					}
				}
				if (ex) break;
				if (GetAsyncKeyState(VK_ESCAPE)) { //lshift + r + esc
					if (GetAsyncKeyState(82)) {
						kbRelease(VK_ESCAPE); kb(VK_BACK);
						out(L"<shift>,<shift->rgb: " + getRGB() + L" " + qx + L" " + qy + (Loop_Insert_Text > L"" ? Loop_Insert_Text : L">"));
						ex = 1;	break;
					}
				}
				Sleep(frequency / 4);
			}
			if (ex) continue;
			clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			continue;
		}
		if (GetAsyncKeyState(VK_LCONTROL)) {
			GetAsyncKeyState(VK_RCONTROL); GetAsyncKeyState(83); bool ex = 0; while (GetAsyncKeyState(VK_LCONTROL) != 0) {
				if (GetAsyncKeyState(VK_RCONTROL)) { while (GetAsyncKeyState(VK_RCONTROL) != 0) { Sleep(frequency / 4); } GetAsyncKeyState(VK_LCONTROL); if (GetAsyncKeyState(VK_LCONTROL)) {} else { repeat(); } continue; }//rctrl+lctrl repeat
				while (GetAsyncKeyState(VK_LCONTROL) != 0) {
					if (GetAsyncKeyState(83)) { while (GetAsyncKeyState(83) != 0) { Sleep(frequency / 3); } 
						if (SeHotReload_CtrlS && (FindWindowW(0, (editorSe).c_str()) == GetForegroundWindow() || FindWindowW(0, (se + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (se + editor1).c_str()) == GetForegroundWindow())) {
							loadSe(); clearAllKeys(); strand.clear(); prints();
						}
						else if (SeDbClearStrand_CtrlS && (FindWindowW(0, (editorDb).c_str()) == GetForegroundWindow() || FindWindowW(0, (db + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (db + editor1).c_str()) == GetForegroundWindow())) {
							clearAllKeys(); strand.clear(); prints();
						}
						while (GetAsyncKeyState(VK_CONTROL) != 0) { Sleep(frequency / 3); }
						ex = 1; break;
					}//lctrl+s
					Sleep(frequency / 4); 
				}
				if (ex) break;
				Sleep(frequency / 4);
			}
			if (ex) continue;
			clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			continue;
		}
		if (GetAsyncKeyState(cKey) && cKeyMax) {//toggle <
			unsigned short x = 0, min = 0;
			while (GetAsyncKeyState(cKey) != 0) {
				if (GetAsyncKeyState(VK_LCONTROL)) {
					while (GetAsyncKeyState(VK_LCONTROL) != 0) Sleep(1);
					++x;
				}
				++min;
				if (min > 1) Sleep(frequency / 4);
			}
			if (x) { //ctrlKey + lctrl
				if (GetAsyncKeyState(VK_ESCAPE)) continue;
				wstring r = L""; for (unsigned char i = 0; i < x; ++i) r += reTail;
				reTail = r;
				repeat();
				continue;
			}
			if (RSHIFTLSHIFT_Only && !strand[0] && !rri) continue;
			if (min > cKeyMax) {}
			else {
				if (cKey == VK_SPACE) kb(VK_BACK);
				if (!strand[0]) strand = L"<";
				else {
					if (strand[0] && strand != L"<") { key(L">"); prints(); continue; }
					if (RSHIFTLSHIFT_Only > 1) strand = L"";
					else strand = strand[0] == '<' ? L"" : L"<";
				}
				prints();
			}
			clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			continue;
		}
		if (GetAsyncKeyState(reKey)) { //repeat - scroll_lock
			if (AutoBs_RepeatKey) kb(VK_BACK);
			repeat();
			continue;
		}
		if (GetAsyncKeyState(ClearStrandKey)) {
			if (Kb_QQ_i) Kb_QQ_i = 0;
			if (!strand[0] || strand == L"<") continue;
			clearAllKeys();
			strand = strand[0] == '<' ? L"<" : L"";
			prints();
			continue; 
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			GetAsyncKeyState(80); if (GetAsyncKeyState(80)) {//esc + p: <xy:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				re = L"><shift>,<shift->xy:";
				strand.clear();
				scanDb();
				continue;
			}
			GetAsyncKeyState(82); if (GetAsyncKeyState(82)) {//esc + r: <rgb:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				re = L"><shift>,<shift->rgb:";
				strand.clear();
				scanDb();
				continue;
			}
			GetAsyncKeyState(65); if (GetAsyncKeyState(65)) {//esc + a: <app:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				re = L"><shift>,<shift->app:";
				strand.clear();
				scanDb();
				continue;
			}
			GetAsyncKeyState(VK_OEM_PLUS); if (GetAsyncKeyState(VK_OEM_PLUS)) {//esc + plus: repeat
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				if (EscEqualAutoBs) { kb(VK_BACK); GetAsyncKeyState(VK_BACK); }
				repeat(); continue;
			}
			GetAsyncKeyState(0xBC); if (GetAsyncKeyState(0xBC)) {//esc + ,
				if (EscCommaAutoBs) { kb(VK_BACK); GetAsyncKeyState(VK_BACK); }
				switch (strand[0]) {
				case '<':
					if (strand == L"<") continue;
					break;
				default:
					if (strand[0]) break;
					strand = L"<"; prints(); clearAllKeys(); continue;
				}
				if (strand.length() > 0) {
					kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
					strand.append(L">"); prints();
					if (multiStrand) { thread thread(scanDb); Sleep(CloseCtrlSpacer); thread.detach(); }
					else scanDb();
					if (!noClearStrand) { strand.clear(); } noClearStrand = 0;
				}
				else continue;
				if (!strand[0]) prints();
				clearAllKeys();
				continue;
			}
			GetAsyncKeyState(76); if (GetAsyncKeyState(76)) {
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				static unsigned short escL = RSHIFTLSHIFT_Only;
				if (RSHIFTLSHIFT_Only) RSHIFTLSHIFT_Only = 0;
				else RSHIFTLSHIFT_Only = escL ? escL : !qScanOnly + close_ctrl_mode;
				if (!RSHIFTLSHIFT_Only) Sleep(frequency);
				strand.clear(); clearAllKeys(); prints();
				continue;
			} //esc + L
			GetAsyncKeyState(0x58); if (GetAsyncKeyState(0x58)) { if (enableEscX) { kb(VK_BACK); return 0; } } //esc + x
			GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) {//esc + h
				if (EscHAutoBs) { kb(VK_BACK); Sleep(1); } GetAsyncKeyState(VK_ESCAPE);
				toggle_visibility();
				if (showStrand && !qScanOnly) showOutsMsg(L"", OutsTemplate, strand + L"\n", 1);
				continue;
			}
			GetAsyncKeyState(VK_OEM_2); if (GetAsyncKeyState(VK_OEM_2)) {
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				printCtrls();
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				SetForegroundWindow(GetConsoleWindow());
				continue;
			} //? + esc
			if (Kb_Key_Esc[0]) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key(Kb_Key_Esc); }
			continue;
		}
		if (Kb_QQ_k != 0 && GetAsyncKeyState(Kb_QQ_k) && RSHIFTLSHIFT_Only && !strand[0]) {
			GetAsyncKeyState(Kb_QQ_k); ++Kb_QQ_i;
			if (Kb_QQ_i > qqLen - 1) { Kb_QQ_i = 0; for(auto i = 0; i < qqLen; ++i) kb(VK_BACK); GetAsyncKeyState(VK_BACK); strand = qScanOnly ? L"<" : L""; ++rri; prints(); clearAllKeys(); continue; }
			Sleep(frequency / 3);
			continue;
		}
		if (qScanOnly && strand[0] != '<') continue;
		if (!rri && RSHIFTLSHIFT_Only && !strand[0]) { if (Kb_QQ_i > 0) { Kb_QQ_i = 0; } continue; }
#pragma region input_strand
		if (!ignoreAZ) {
			if (Kb_Key_A[0] && GetAsyncKeyState(0x41)) { key(Kb_Key_A); continue; }
			if (Kb_Key_B[0] && GetAsyncKeyState(0x42)) { key(Kb_Key_B); continue; }
			if (Kb_Key_C[0] && GetAsyncKeyState(0x43)) { key(Kb_Key_C); continue; }
			if (Kb_Key_D[0] && GetAsyncKeyState(0x44)) { key(Kb_Key_D); continue; }
			if (Kb_Key_E[0] && GetAsyncKeyState(0x45)) { key(Kb_Key_E); continue; }
			if (Kb_Key_F[0] && GetAsyncKeyState(0x46)) { key(Kb_Key_F); continue; }
			if (Kb_Key_G[0] && GetAsyncKeyState(0x47)) { key(Kb_Key_G); continue; }
			if (Kb_Key_H[0] && GetAsyncKeyState(0x48)) { key(Kb_Key_H); continue; }
			if (Kb_Key_I[0] && GetAsyncKeyState(0x49)) { key(Kb_Key_I); continue; }
			if (Kb_Key_J[0] && GetAsyncKeyState(0x4A)) { key(Kb_Key_J); continue; }
			if (Kb_Key_K[0] && GetAsyncKeyState(0x4B)) { key(Kb_Key_K); continue; }
			if (Kb_Key_L[0] && GetAsyncKeyState(0x4C)) { key(Kb_Key_L); continue; }
			if (Kb_Key_M[0] && GetAsyncKeyState(0x4D)) { key(Kb_Key_M); continue; }
			if (Kb_Key_N[0] && GetAsyncKeyState(0x4E)) { key(Kb_Key_N); continue; }
			if (Kb_Key_O[0] && GetAsyncKeyState(0x4F)) { key(Kb_Key_O); continue; }
			if (Kb_Key_P[0] && GetAsyncKeyState(0x50)) { key(Kb_Key_P); continue; }
			if (Kb_Key_Q[0] && GetAsyncKeyState(0x51)) { key(Kb_Key_Q); continue; }
			if (Kb_Key_R[0] && GetAsyncKeyState(0x52)) { key(Kb_Key_R); continue; }
			if (Kb_Key_S[0] && GetAsyncKeyState(0x53)) { key(Kb_Key_S); continue; }
			if (Kb_Key_T[0] && GetAsyncKeyState(0x54)) { key(Kb_Key_T); continue; }
			if (Kb_Key_U[0] && GetAsyncKeyState(0x55)) { key(Kb_Key_U); continue; }
			if (Kb_Key_V[0] && GetAsyncKeyState(0x56)) { key(Kb_Key_V); continue; }
			if (Kb_Key_W[0] && GetAsyncKeyState(0x57)) { key(Kb_Key_W); continue; }
			if (Kb_Key_X[0] && GetAsyncKeyState(0x58)) { key(Kb_Key_X); continue; }
			if (Kb_Key_Y[0] && GetAsyncKeyState(0x59)) { key(Kb_Key_Y); continue; }
			if (Kb_Key_Z[0] && GetAsyncKeyState(0x5A)) { key(Kb_Key_Z); continue; }
		}
		if (!ignore09) {
			if (Kb_Key_0[0] && GetAsyncKeyState(0x30)) { key(Kb_Key_0); continue; }
			if (Kb_Key_1[0] && GetAsyncKeyState(0x31)) { key(Kb_Key_1); continue; }
			if (Kb_Key_2[0] && GetAsyncKeyState(0x32)) { key(Kb_Key_2); continue; }
			if (Kb_Key_3[0] && GetAsyncKeyState(0x33)) { key(Kb_Key_3); continue; }
			if (Kb_Key_4[0] && GetAsyncKeyState(0x34)) { key(Kb_Key_4); continue; }
			if (Kb_Key_5[0] && GetAsyncKeyState(0x35)) { key(Kb_Key_5); continue; }
			if (Kb_Key_6[0] && GetAsyncKeyState(0x36)) { key(Kb_Key_6); continue; }
			if (Kb_Key_7[0] && GetAsyncKeyState(0x37)) { key(Kb_Key_7); continue; }
			if (Kb_Key_8[0] && GetAsyncKeyState(0x38)) { key(Kb_Key_8); continue; }
			if (Kb_Key_9[0] && GetAsyncKeyState(0x39)) { key(Kb_Key_9); continue; }
		}
		if (!ignoreF1s) {
			if (Kb_Key_F1[0] && GetAsyncKeyState(0x70)) { key(Kb_Key_F1); continue; }
			if (Kb_Key_F2[0] && GetAsyncKeyState(0x71)) { key(Kb_Key_F2); continue; }
			if (Kb_Key_F3[0] && GetAsyncKeyState(0x72)) { key(Kb_Key_F3); continue; }
			if (Kb_Key_F4[0] && GetAsyncKeyState(0x73)) { key(Kb_Key_F4); continue; }
			if (Kb_Key_F5[0] && GetAsyncKeyState(0x74)) { key(Kb_Key_F5); continue; }
			if (Kb_Key_F6[0] && GetAsyncKeyState(0x75)) { key(Kb_Key_F6); continue; }
			if (Kb_Key_F7[0] && GetAsyncKeyState(0x76)) { key(Kb_Key_F7); continue; }
			if (Kb_Key_F8[0] && GetAsyncKeyState(0x77)) { key(Kb_Key_F8); continue; }
			if (Kb_Key_F9[0] && GetAsyncKeyState(0x78)) { key(Kb_Key_F9); continue; }
			if (Kb_Key_F10[0] && GetAsyncKeyState(0x79)) { key(Kb_Key_F10); continue; }
			if (Kb_Key_F11[0] && GetAsyncKeyState(0x7A)) { key(Kb_Key_F11); continue; }
			if (Kb_Key_F12[0] && GetAsyncKeyState(0x7B)) { key(Kb_Key_F12); continue; }
		}
		if (!ignoreArrows) {
			if (Kb_Key_Left[0] && GetAsyncKeyState(VK_LEFT)) { key(Kb_Key_Left); continue; }
			if (Kb_Key_Up[0] && GetAsyncKeyState(VK_UP)) { key(Kb_Key_Up); continue; }
			if (Kb_Key_Right[0] && GetAsyncKeyState(VK_RIGHT)) { key(Kb_Key_Right); continue; }
			if (Kb_Key_Down[0] && GetAsyncKeyState(VK_DOWN)) { key(Kb_Key_Down); continue; }
		}
		if (!ignoreOtherKeys) {
			if (Kb_Key_Print_Screen[0] && GetAsyncKeyState(VK_SNAPSHOT)) { key(Kb_Key_Print_Screen); continue; }
			if (Kb_Key_Space[0] && GetAsyncKeyState(VK_SPACE)) { key(Kb_Key_Space); continue; }
			if (Kb_Key_Tab[0] && GetAsyncKeyState(VK_TAB)) { key(Kb_Key_Tab); continue; }
			if (Kb_Key_Left_Shift[0] && GetAsyncKeyState(VK_LSHIFT)) { key(Kb_Key_Left_Shift); continue; }
			if (Kb_Key_Right_Shift[0] && GetAsyncKeyState(VK_RSHIFT)) { key(Kb_Key_Right_Shift); continue; }
			if (Kb_Key_Left_Ctrl[0] && GetAsyncKeyState(VK_LCONTROL)) { key(Kb_Key_Left_Ctrl); continue; }
			if (Kb_Key_Right_Ctrl[0] && GetAsyncKeyState(VK_RCONTROL)) { key(Kb_Key_Right_Ctrl); continue; }
			if (Kb_Key_Enter[0] && GetAsyncKeyState(VK_RETURN)) { key(Kb_Key_Enter); continue; }
			if (Kb_Key_Caps[0] && GetAsyncKeyState(VK_CAPITAL)) { key(Kb_Key_Caps); continue; }
			if (Kb_Key_Grave_Accent[0] && GetAsyncKeyState(VK_OEM_3)) { key(Kb_Key_Grave_Accent); continue; }
			if (Kb_Key_Minus[0] && GetAsyncKeyState(VK_OEM_MINUS)) { key(Kb_Key_Minus); continue; }
			if (Kb_Key_Equal[0] && GetAsyncKeyState(VK_OEM_PLUS)) { key(Kb_Key_Equal); continue; }
			if (Kb_Key_Left_Bracket[0] && GetAsyncKeyState(VK_OEM_4)) { key(Kb_Key_Left_Bracket); continue; }
			if (Kb_Key_Right_Bracket[0] && GetAsyncKeyState(VK_OEM_6)) { key(Kb_Key_Right_Bracket); continue; }
			if (Kb_Key_Backslash[0] && GetAsyncKeyState(VK_OEM_5)) { key(Kb_Key_Backslash); continue; }
			if (Kb_Key_Semicolon[0] && GetAsyncKeyState(VK_OEM_1)) { key(Kb_Key_Semicolon); continue; }
			if (Kb_Key_Quote[0] && GetAsyncKeyState(VK_OEM_7)) { key(Kb_Key_Quote); continue; }
			if (Kb_Key_Comma[0] && GetAsyncKeyState(VK_OEM_COMMA)) { key(Kb_Key_Comma); continue; }
			if (Kb_Key_Period[0] && GetAsyncKeyState(VK_OEM_PERIOD)) { key(Kb_Key_Period); continue; }
			if (Kb_Key_Forwardslash[0] && GetAsyncKeyState(VK_OEM_2)) { key(Kb_Key_Forwardslash); continue; }
			if (Kb_Key_Menu[0] && GetAsyncKeyState(VK_APPS)) { key(Kb_Key_Menu); continue; }
			if (Kb_Key_Insert[0] && GetAsyncKeyState(VK_INSERT)) { key(Kb_Key_Insert); continue; }
			if (Kb_Key_Delete[0] && GetAsyncKeyState(VK_DELETE)) { key(Kb_Key_Delete); continue; }
			if (Kb_Key_Home[0] && GetAsyncKeyState(VK_HOME)) { key(Kb_Key_Home); continue; }
			if (Kb_Key_End[0] && GetAsyncKeyState(VK_END)) { key(Kb_Key_End); continue; }
			if (Kb_Key_PgUp[0] && GetAsyncKeyState(VK_PRIOR)) { key(Kb_Key_PgUp); continue; }
			if (Kb_Key_PgDn[0] && GetAsyncKeyState(VK_NEXT)) { key(Kb_Key_PgDn); continue; }
		}
		if (!ignoreNumPad) {
			if (Kb_Key_Numpad_0[0] && GetAsyncKeyState(VK_NUMPAD0)) { key(Kb_Key_Numpad_0); continue; }
			if (Kb_Key_Numpad_1[0] && GetAsyncKeyState(VK_NUMPAD1)) { key(Kb_Key_Numpad_1); continue; }
			if (Kb_Key_Numpad_2[0] && GetAsyncKeyState(VK_NUMPAD2)) { key(Kb_Key_Numpad_2); continue; }
			if (Kb_Key_Numpad_3[0] && GetAsyncKeyState(VK_NUMPAD3)) { key(Kb_Key_Numpad_3); continue; }
			if (Kb_Key_Numpad_4[0] && GetAsyncKeyState(VK_NUMPAD4)) { key(Kb_Key_Numpad_4); continue; }
			if (Kb_Key_Numpad_5[0] && GetAsyncKeyState(VK_NUMPAD5)) { key(Kb_Key_Numpad_5); continue; }
			if (Kb_Key_Numpad_6[0] && GetAsyncKeyState(VK_NUMPAD6)) { key(Kb_Key_Numpad_6); continue; }
			if (Kb_Key_Numpad_7[0] && GetAsyncKeyState(VK_NUMPAD7)) { key(Kb_Key_Numpad_7); continue; }
			if (Kb_Key_Numpad_8[0] && GetAsyncKeyState(VK_NUMPAD8)) { key(Kb_Key_Numpad_8); continue; }
			if (Kb_Key_Numpad_9[0] && GetAsyncKeyState(VK_NUMPAD9)) { key(Kb_Key_Numpad_9); continue; }
			if (Kb_Key_Numlock[0] && GetAsyncKeyState(VK_NUMLOCK)) { key(Kb_Key_Numlock); continue; }
			if (Kb_Key_Numpad_Divide[0] && GetAsyncKeyState(VK_DIVIDE)) { key(Kb_Key_Numpad_Divide); continue; }
			if (Kb_Key_Numpad_Multiply[0] && GetAsyncKeyState(VK_MULTIPLY)) { key(Kb_Key_Numpad_Multiply); continue; }
			if (Kb_Key_Numpad_Minus[0] && GetAsyncKeyState(VK_SUBTRACT)) { key(Kb_Key_Numpad_Minus); continue; }
			if (Kb_Key_Numpad_Add[0] && GetAsyncKeyState(VK_ADD)) { key(Kb_Key_Numpad_Add); continue; }
			if (Kb_Key_Numpad_Period[0] && GetAsyncKeyState(VK_DECIMAL)) { key(Kb_Key_Numpad_Period); continue; }
			if (Kb_Key_Numpad_Enter[0] && GetAsyncKeyState(VK_RETURN)) { key(Kb_Key_Numpad_Enter); continue; }
		}
		if (GetAsyncKeyState(VK_LMENU)) {
			if (Kb_Key_Left_Alt[0]) key(Kb_Key_Left_Alt);
			else {
				while (GetAsyncKeyState(VK_LMENU) != 0)	Sleep(frequency / 4);
				clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			}
			continue;
		}
		if (GetAsyncKeyState(VK_RMENU)) {
			if (Kb_Key_Right_Alt[0]) key(Kb_Key_Right_Alt);
			else {
				while (GetAsyncKeyState(VK_RMENU) != 0)	Sleep(frequency / 4);
				clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			}
			continue;
		}
		if (GetAsyncKeyState(VK_LWIN) || GetAsyncKeyState(VK_RWIN)) {
			while (GetAsyncKeyState(VK_LWIN) != 0 || GetAsyncKeyState(VK_RWIN) != 0) Sleep(frequency / 4);
			clearAllKeys(); if (Kb_QQ_i) Kb_QQ_i = 0;
			continue;
		}
#pragma endregion
	}
	return 0;
}