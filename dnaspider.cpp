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
wstring
	Kb_Key_A = L"a", Kb_Key_B = L"b", Kb_Key_C = L"c", Kb_Key_D = L"d", Kb_Key_E = L"e", Kb_Key_F = L"f", Kb_Key_G = L"g", Kb_Key_H = L"h", Kb_Key_I = L"i", Kb_Key_J = L"j", Kb_Key_K = L"k", Kb_Key_L = L"l", Kb_Key_M = L"m", Kb_Key_N = L"n", Kb_Key_O = L"o", Kb_Key_P = L"p", Kb_Key_Q = L"q", Kb_Key_R = L"r", Kb_Key_S = L"s", Kb_Key_T = L"t", Kb_Key_U = L"u", Kb_Key_V = L"v", Kb_Key_W = L"w", Kb_Key_X = L"x", Kb_Key_Y = L"y", Kb_Key_Z = L"z",
	Kb_Key_0 = L"0", Kb_Key_1 = L"1", Kb_Key_2 = L"2", Kb_Key_3 = L"3", Kb_Key_4 = L"4", Kb_Key_5 = L"5", Kb_Key_6 = L"6", Kb_Key_7 = L"7", Kb_Key_8 = L"8", Kb_Key_9 = L"9",
	Kb_Key_F1 = L"!", Kb_Key_F2 = L"@", Kb_Key_F3 = L"#", Kb_Key_F4 = L"$", Kb_Key_F5 = L"%", Kb_Key_F6 = L"^", Kb_Key_F7 = L"&", Kb_Key_F8 = L"*", Kb_Key_F9 = L"(", Kb_Key_F10 = L")", Kb_Key_F11 = L"_", Kb_Key_F12 = L"+",
	Kb_Key_Left = L"L", Kb_Key_Up = L"U", Kb_Key_Right = L"R", Kb_Key_Down = L"D",
	Kb_Key_Esc = L"~", Kb_Key_Space = L" ", Kb_Key_Tab = L"T", Kb_Key_Left_Shift = L"S", Kb_Key_Right_Shift = L"H", Kb_Key_Left_Alt = L"A", Kb_Key_Right_Alt = L"M", Kb_Key_Left_Ctrl = L"C", Kb_Key_Right_Ctrl = L"O", Kb_Key_Enter = L"E", Kb_Key_Caps = L"P", Kb_Key_Grave_Accent = L"`", Kb_Key_Minus = L"-", Kb_Key_Equal = L"=", Kb_Key_Left_Bracket = L"[", Kb_Key_Right_Bracket = L"]", Kb_Key_Backslash = L"\\",  Kb_Key_Semicolon = L";", Kb_Key_Quote = L"'", Kb_Key_Comma = L",", Kb_Key_Period = L".", Kb_Key_Forwardslash = L"/", Kb_Key_Menu = L"?",
	Kb_Key_Print_Screen = L"?", Kb_Key_Insert = L"?", Kb_Key_Delete = L"?", Kb_Key_Home = L"?", Kb_Key_End = L"?", Kb_Key_PgUp = L"?", Kb_Key_PgDn = L"?",
	Kb_Key_Numpad_0 = L"Z", Kb_Key_Numpad_1 = L"Q", Kb_Key_Numpad_2 = L"V", Kb_Key_Numpad_3 = L"W", Kb_Key_Numpad_4 = L"X", Kb_Key_Numpad_5 = L"Y", Kb_Key_Numpad_6 = L"B", Kb_Key_Numpad_7 = L"F", Kb_Key_Numpad_8 = L"G", Kb_Key_Numpad_9 = L"I", Kb_Key_Numlock = L"N", Kb_Key_Numpad_Divide = L"J", Kb_Key_Numpad_Multiply = L"K", Kb_Key_Numpad_Minus = L"{", Kb_Key_Numpad_Add = L"}", Kb_Key_Numpad_Period = L"\\", Kb_Key_Numpad_Enter = L":"
;
wstring pre = L""; //previous reTail
wstring io = L"*";//i*o
wstring linkr = L"";
wstring link = L""; //<app|rgb|ifcb,,,<link:>
wstring editor = L"Notepad", editor1 = L"Visual Studio Code", editorSe = L"  - Notepad", editorDb = L"  - Notepad", db = L"db.txt - ", se = L"se.txt - ";
wstring database, settings, replacerDb;
wstring strand = L""; //>> supply
wstring tail = L""; //strand:tail
wstring re = L"";//repeat clone
wstring reTail = L"";
wstring codes = L""; //tail re
wstring star_num; //<x*#>
wstring qq; //<x>
wstring qp; //<x:#>
wstring qx, qy; //<xy:#,#>
wstring OutsTemplate = L"\\Gstrand:\\t\\t\\7";
wstring Loop_Insert_Text = L",";
double RgbScaleLayout = 1.00; //100%
size_t i = 0;
int CommaSleep = 150;
int ic = 0; //<+> icp
int strandLength = 3;
int frequency = 150; //>> ms response -> vk_
int speed = 0; //<< 
int qxc = 0, qyc = 0;//<rp>
int qxcc = 0, qycc = 0;//cc
int CloseCtrlSpacer = 120;
short PauseKey = 123; // VK_F12
short ClearStrandKey = VK_PAUSE;
short reKey = VK_SCROLL; //repeat
short cKey = VK_RCONTROL; //< 163
bool ManualRepeat = 0;//<repeat>
bool io_Auto_BS = 1;//i*o
bool NoEscapeOrPause = 0; //<~esc>, <~~esc>
bool Loop_Insert = 1;
bool Ignore_Print_Screen = 1, Ignore_Insert = 1, Ignore_Delete = 1, Ignore_Home = 1, Ignore_End = 1, Ignore_PgUp = 1, Ignore_PgDn = 1;
bool noClearStrand = 0; //<!>
bool multiLine = 1; wstring multiLineDelim = L"\n"; //DbMultiLineDelimiter:
bool multiblock = 0; //<~m>
bool replacer = 1; //{}
bool BackslashLogicals = 0; //<ifcb:a\|b\|c><ifcb:a|b|c>
bool ToggleCloseCtrl = 0, toggledCC = 0, ToggleKeep = 1; //RSHIFT+CtrlKey_ToggleCloseCtrlMode:
bool ToggleCtrlScanOnly = 0, toggledCSO = 0, flipd = 0; //RSHIFT+CtrlKey_ToggleCtrlScanOnlyMode:
bool Unicode = 1;
bool OutTabs = 1; wstring OutTab = L"\t";
bool multiStrand = 1, showMultiStrand = 0, showMultiStrandElapsedOnly = 0;
bool relink = 0;
bool fail = 0;
bool sleep = 1;
bool esc_pressed = 0;
bool pause_resume = 0;
bool enableEscX = true;
bool ignoreNumPad = true;
bool ignoreMenuKey = true;
bool ignoreGraveAccent = true; //`
bool ignoreMinus = true;
bool ignoreEqual = true;
bool ignoreLBracket = true;
bool ignoreRBracket = true;
bool ignoreBackslash = true;
bool ignoreSemicolon = true;
bool ignoreQuote = true;
bool ignoreComma = true;
bool ignorePeriod = true;
bool ignoreForwardslash = true;
bool startHidden = false;
bool ignoreAZ = false;
bool ignore09 = true;
bool ignoreSpace = false;
bool ignoreArrows = true;
bool ignoreF1s = true;//f1-f12
bool ignoreEsc = true;
bool ignoreTab = true;
bool ignoreLShift = true;
bool ignoreRShift = true;
bool ignoreLAlt = true;
bool ignoreRAlt = true;
bool ignoreLCtrl = true;
bool ignoreRCtrl = true;
bool ignoreEnter = true;
bool ignoreCaps = true;
bool strandLengthMode = false;
bool qScanOnly = false;
bool showStrand = true; //cout <<
bool showOuts = false; //cout << 
bool showIntro = false;
bool showSettings = 1;
bool shft = false;
bool close_ctrl_mode = true; //x>, x:, x- 
bool SlightPauseInBetweenConnects = false;
bool EscCommaAutoBs = true;
bool EscEqualAutoBs = true;
bool EscHAutoBs = true;
bool AutoBs_RepeatKey = 0;
bool SeHotReload_CtrlS=1;
bool SeDbClearStrand_CtrlS=1;
bool assume = 0;
#pragma endregion

#pragma region protos
void showOutsMsg(wstring, wstring, wstring, bool);
ctp clockr(ctp&);
void cbSet(wstring&);
wstring randn(bool);
void repeat();
#pragma endregion

#pragma region classo
struct Mainn {
	wstring s, s1, &t = tail;//strand
	ctp c1, c2;//elapsed
	Mainn()	{
		if (!multiStrand) return;
		if (showMultiStrandElapsedOnly && !showMultiStrand) { clockr(c1); return; }
		if (showMultiStrand) { wcout << "thread: " << OutTab << "0x" << hex << GetCurrentThreadId() << dec << endl; clockr(c1); }
	}
	void setStrand(wstring c) {
		linkr = s1 = c.substr(0, strand.length());
	}
	wstring getStrand() {
		return s1;
	}
	wstring getStrand(wstring &c) {
		s = c.substr(0, strand.length() + !strandLengthMode);
		if (showMultiStrand) {
			wstring b = L">"; if (s[s.size() - 1] == '>' || s[s.size()] == '>' || strandLengthMode) b = L"";
			wcout << "input: " << OutTab << OutTab << (linkr > L""? linkr + b : s + b) << endl;
		}
		return s;
	}
	void setTail() {
		t = tail;
		if (showMultiStrand) { wcout << "output: " << OutTab; showOutsMsg(L"", t, L"", 0); }
	}
	wstring getTail(wstring &t) {
		return t;
	}
	~Mainn() {
		if (!multiStrand) return;
		t.clear();
		if (showMultiStrandElapsedOnly && !showMultiStrand) { clockr(c2); chrono::duration<double, milli> ts = c1 - c2; wstring q = L""; if (!showStrand) { q = strand[strand.length() - 1] == '>' ? L"" : strand.length() > 0 ? L">" : L""; wstring p = q; q = strand + p; } bool x = showStrand; showStrand = 1; showOutsMsg(L"", OutsTemplate, q, 1); showStrand = x; cout << dec << "(" << abs(static_cast<long>(ts.count())) << "ms elapsed)\n"; return; }
		if (showMultiStrand) {
			clockr(c2); chrono::duration<double, milli> ts = c1 - c2;
			wcout << "~thread: " << OutTab << "0x" << hex << GetCurrentThreadId() << dec << " (" << abs(static_cast<long>(ts.count())) << "ms elapsed)\n";
		}
	}
};

struct Multi {
	wstring r, g, b, a, x, m, l, t = tail, q = qq;
	size_t get_i = i, icp = 0;
	int cx{}, cy{}, speed_ = 0;
	bool esc = 0, br = 0;//break
	Multi() {}
	Multi(wstring& r) {}
	void setSpeed(int& sl) { speed_ = sl; }
	void setApp(wstring& app) {
		a = app;
	}
	size_t get_icp() {
		return icp;
	}
	wstring getApp() {
		return a;
	}
	void setBreak() {
		br = 1;
	}
	bool getBreak() {
		return br;
	}
	size_t getI() {
		return get_i;
	}
	void setI() {
		get_i = i;
	}
	void setLink(wstring& li) {
		l = li;
	}
	wstring getLink() {
		return l;
	}
	void setMS(wstring mil) {
		m = mil;
	}
	wstring getMS() {
		return m;
	}
	wstring getQQ() {
		return q;
	}
	void setRGBr(wstring& red) {
		r = red;
	}
	void setRGBg(wstring& gre) {
		g = gre;
	}
	void setRGBb(wstring& blu) {
		b = blu;
	}
	wstring getRGBr() {
		return r;
	}
	wstring getRGBg() {
		return g;
	}
	wstring getRGBb() {
		return b;
	}
	int getQxc() {
		return cx;//qxc
	}
	void setQxc(int& it) {
		cx = it;
	}
	int getQyc() {
		return cy;//qyc
	}
	void setQyc(int& it) {
		cy = it;
	}
	wstring getTail() {
		return t;
	}
	void setX(wstring& it) {
		x = it;
	}
	wstring getX() {
		return x;
	}
	//~Multi() {}
};
#pragma endregion

#pragma region global_sub
wstring getTime(wstring& w) {
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

wstring check_if_num(wstring &s) {
	if (assume) return s;
	if (s > L"") {
		int c = 0, d = 0;
		auto f = [&s]() { if (showStrand) wcout << "NAN: " << OutTab << OutTab << s << endl; s = L""; return s; };
		for (size_t t = 0; t < s.length(); ++t) {//!0-9
			if (s[0] == ' ') {
				if (s.length() == 1) {
					s = L""; return s;
				}
				s = s.substr(1, s.length()); --t;
				continue;
			}//rem ws
			if (c > 1 || d > 1) f();
			if (s[t] == '.') { if (s.length() == 1) { f(); } ++d; continue; }
			if (t == 0 && (s[0] == 45 || s[0] == 43) && s.length() != 1) { ++c; continue; }//-+
			if (!(s[t] >= 48 && s[t] <= 57)) f();
		}
	}
	else s = L"";
	return s;
}

void kb(wchar_t b) {//out char
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	if (VkKeyScanW(b) == -1) { ip[0].ki.wScan = b; ip[0].ki.wVk = 0; }
	else { ip[0].ki.wVk = VkKeyScanW(b); }
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

void kb(wstring b) {//alt codes, emoji
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	ip[0].ki.wScan = (unsigned)stoull(b); ip[0].ki.wVk = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

void kbHold(short key) {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key; ip.ki.time = 0;
	if (key == VK_LMENU || key == VK_CONTROL) ip.ki.dwFlags = 0; else ip.ki.dwFlags = 1;
	SendInput(1, &ip, sizeof(INPUT));
}

void kbRelease(short key) {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; SendInput(1, &ip, sizeof(INPUT));
}

void mouseEvent(short key) {
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

void shftRelease() {
	INPUT ip{}; ip.type = INPUT_KEYBOARD; ip.ki.dwFlags = 2;
	ip.ki.wVk = VK_LSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_RSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	if (shft) { shft = false; }
}

void printq() { kbHold(VK_LSHIFT); kb('<'); shftRelease(); }

void prints(bool clear = 0) { if (clear) strand.clear(); if (showStrand) showOutsMsg(L"", OutsTemplate, strand + L"\n", 1); }

bool qqb(const wstring s) {
	return qq.substr(0, s.length()) == s && qq.find(L">") != string::npos;
}

bool testqqb(const wstring s) {
	return qqb(s) && qq[s.length()] != '>';
}

void clearAllKeys() {
	if (!ignoreAZ) for (int i = 65; i <= 90; ++i) { GetAsyncKeyState(i); }
	if (!ignore09) for (int i = 48; i <= 57; ++i) { GetAsyncKeyState(i); }
	GetAsyncKeyState(reKey);
	GetAsyncKeyState(cKey);
	GetAsyncKeyState(VK_RSHIFT);
	GetAsyncKeyState(VK_LSHIFT);
	GetAsyncKeyState(VK_BACK);
	GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_PAUSE);
	if (!ignoreSpace) GetAsyncKeyState(VK_SPACE);
	if (!ignoreF1s) { GetAsyncKeyState(VK_F1); GetAsyncKeyState(VK_F2); GetAsyncKeyState(VK_F3); GetAsyncKeyState(VK_F4); GetAsyncKeyState(VK_F5); GetAsyncKeyState(VK_F6); GetAsyncKeyState(VK_F7); GetAsyncKeyState(VK_F8); GetAsyncKeyState(VK_F9); GetAsyncKeyState(VK_F10); GetAsyncKeyState(VK_F11); GetAsyncKeyState(VK_F12); }
	if (!ignoreArrows) { GetAsyncKeyState(VK_LEFT); GetAsyncKeyState(VK_UP); GetAsyncKeyState(VK_RIGHT); GetAsyncKeyState(VK_DOWN); }
	if (!ignoreTab)GetAsyncKeyState(VK_TAB);
	if (!ignoreLAlt)GetAsyncKeyState(VK_LMENU);
	if (!ignoreRAlt)GetAsyncKeyState(VK_RMENU);
	if (!ignoreLCtrl)GetAsyncKeyState(VK_LCONTROL);
	if (!ignoreRCtrl)GetAsyncKeyState(VK_RCONTROL);
	if (!ignoreEnter)GetAsyncKeyState(VK_RETURN);
	if (!ignoreCaps)GetAsyncKeyState(VK_CAPITAL);
	if (!ignoreGraveAccent)GetAsyncKeyState(VK_OEM_3);
	if (!ignoreMinus)GetAsyncKeyState(VK_OEM_MINUS);
	if (!ignoreEqual)GetAsyncKeyState(VK_OEM_PLUS);
	if (!ignoreLBracket)GetAsyncKeyState(VK_OEM_4);
	if (!ignoreRBracket)GetAsyncKeyState(VK_OEM_6);
	if (!ignoreBackslash)GetAsyncKeyState(VK_OEM_5);
	if (!ignoreSemicolon)GetAsyncKeyState(VK_OEM_1);
	if (!ignoreQuote)GetAsyncKeyState(VK_OEM_7);
	if (!ignoreComma)GetAsyncKeyState(VK_OEM_COMMA);
	if (!ignorePeriod)GetAsyncKeyState(VK_OEM_PERIOD);
	if (!ignoreForwardslash)GetAsyncKeyState(VK_OEM_2);
	if (!ignoreNumPad) { GetAsyncKeyState(VK_NUMLOCK); GetAsyncKeyState(VK_DIVIDE); GetAsyncKeyState(VK_MULTIPLY); GetAsyncKeyState(VK_SUBTRACT); GetAsyncKeyState(VK_ADD); GetAsyncKeyState(VK_RETURN); GetAsyncKeyState(VK_DECIMAL); GetAsyncKeyState(VK_NUMPAD0); GetAsyncKeyState(VK_NUMPAD1); GetAsyncKeyState(VK_NUMPAD2); GetAsyncKeyState(VK_NUMPAD3); GetAsyncKeyState(VK_NUMPAD4); GetAsyncKeyState(VK_NUMPAD5); GetAsyncKeyState(VK_NUMPAD6); GetAsyncKeyState(VK_NUMPAD7); GetAsyncKeyState(VK_NUMPAD8); GetAsyncKeyState(VK_NUMPAD9); }
	//if (!ignoreMediaKeys) {GetAsyncKeyState(VK_INSERT);GetAsyncKeyState(VK_DELETE);GetAsyncKeyState(VK_HOME);GetAsyncKeyState(VK_END);GetAsyncKeyState(VK_PRIOR);GetAsyncKeyState(VK_NEXT);}
	if (!ignoreMenuKey) GetAsyncKeyState(VK_APPS); //menu
}

void printDb() {
	wcout << database << "\n";
	wifstream f(database); wstring cell;
	while (getline(f, cell)) { wcout << cell << endl; }
	f.close(); cout << endl;
}

wstring loadVar(wstring q = L"") {
	wifstream f(replacerDb); if (!f) { showOutsMsg(L"\nReplacerDb \"", replacerDb, L"\" not found!", 0); return q; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	wstring cell, se; GetAsyncKeyState(VK_ESCAPE); while (getline(f, cell, multiLineDelim[0])) {
		if (!NoEscapeOrPause && GetAsyncKeyState(VK_ESCAPE) || cell.substr(0, 4) == L"<'''") break;
		if (cell[0] == 0 || cell[0] == '\n' || cell[0] == ' ') continue;
		se = cell.substr(0, q.length());
		if (se == q) {
			wstring v = cell.substr(q.length());
			q = v;
			f.close();
			return q;
		}
	}
	q = L"";
	f.close();
	return q;
}

wstring isVar(wstring &q) { // Replacer | {var} {var:} {var-} {var>} | <r:>
	if (!replacer) return q;
	if (q.find(L"{") != string::npos) {
		wstring tqg = q, tq{};
		GetAsyncKeyState(VK_ESCAPE);
		while (tqg.find(L"{") != string::npos) {
			if (!NoEscapeOrPause && GetAsyncKeyState(VK_ESCAPE)) break;
			q = q.substr(q.find(L"{") + 1, q.find(L"}", q.find(L"{")) - q.find(L"{") - 1); tq = q;
			if (q > L"") {
				if (multiLine) { q = regex_replace(q, wregex(L"\n"), L""); q = regex_replace(q, wregex(L"\t"), L""); }
				if (q[0] == '\'' && q != L"'") { tqg.replace(tqg.find(L"{"), 2 + q.length(), L""); q = tqg; continue; } //{'ignore}
				q = loadVar(q);
			}
			if (q == L"") {
				tqg.replace(tqg.find(L"{"), 1, L"::_::"); q = tqg;
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

void scanDb(); wstring conn(bool bg = 0) {//<connect:>
	bool con = false; wstring qqs = qq.substr(0, qq.find(L">") + 1);
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
		} f.close(); if (fail) { if (showStrand) { wcout << "Fail: " << OutTab << OutTab << qqs << endl; } fail = 0; i = tail.length(); return L""; } printq();
	}
	else printq();
	return L"";
}

void setQxQy(wstring x, size_t z = 0) {
	if (x.find(L",") != string::npos) {
		qx = x.substr(z, x.find(L","));//x <xy:#,#>
		qy = x.substr(x.find(L",") + 1, x.find(L">") - x.find(L",") - 1);//y
	}
	else if (x.find(L" ") != string::npos) {
		qx = x.substr(z, x.find(L" "));//x <xy:# #>
		qy = x.substr(x.find(L" ") + 1, x.find(L">") - x.find(L" ") - 1);
	}
	else { qx.clear(), qy.clear(); } //wcout << "x: " << x  << "\nqx: " << qx << "\nqy: " << qy << endl;
}

void kbPress(wstring s, short key) {
	if (qq.find(L">") == std::string::npos) { printq(); return; }
	wstring n = s;
	if (qq[n.length()] == '>') star_num = L"1";
	else {
		n = qq.substr(n.length(), qq.find(L">") - n.length());
		if (n[0] == ':') n = n.substr(1);
		if (n[0] == ' ') n = n.substr(1);
		if ((qq[qq.find('>') - 1] == io[0] || qq.substr(qq.find(L">") - 1, 1) == L":" || qq.substr(qq.find(L">") - 1, 1) == L"-") && n[0] != '<') { conn(); return; }
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
				i += 1;
				if (n == L"0") { i += qq.find(L">"); return; }
			}
			star_num = n;
			if (n[0] == '{' || !(stoi(n) > 0)) { printq(); return; };
		}
		else { printq(); return; }
	}
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD; ip[0].ki.wVk = key;
	if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_HOME || key == VK_END) ip[0].ki.dwFlags = 1; else ip[0].ki.dwFlags = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = 2;
	for (int j = 0; j < stoi(star_num); ++j) {
		GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
		if (s.length() == 3) {
			if (s == L"<lc") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
			else if (s == L"<rc") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
			else if (s == L"<mc") { mouseEvent(MOUSEEVENTF_MIDDLEDOWN); mouseEvent(MOUSEEVENTF_MIDDLEUP); }
			else if (s == L"<sd" || s == L"<sr" || s == L"<su" || s == L"<sl") mouseEvent(MOUSEEVENTF_HWHEEL);
			else SendInput(2, ip, sizeof(ip[0]));
		}
		else SendInput(2, ip, sizeof(ip[0]));
		if (speed > 0 && stoi(star_num) != j + 1) { if (multiStrand) { Multi multi; Sleep(speed); tail = multi.t; i = multi.get_i; qq = multi.q; } else Sleep(speed); }
	}
	i += qq.find(L">");
}

void out(wstring ai) { re = L">" + ai; strand.clear(); scanDb(); Sleep(1); re.clear(); }

void calc() {
	if (assume) { i += qq.find(L">"); return; }
	qq = to_wstring(ic) + qq.substr(qq.find(L">") + 1, qq.length());
	i = -1;
	if (speed > 0) sleep = 0;
	re = L" ";
	tail = qq;
}

void loadSe() {
	wifstream f(settings); if (!f) { showOutsMsg(L"\nSettings \"", settings, L"\" not found!", 0); if (settings == L"") { cout << "Create c:\\dna\\se.txt manually\n"; } return; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));//
	wstring cell; while (getline(f, cell)) {
		if (cell[0] == 0 || cell[0] == ' ') continue;
		wstring se = cell.substr(0, cell.find_first_of(L":\t ")); se += ':';
		wstring v = (cell.substr(cell.find_first_of(L":\t ") + 1)); if (v.find_first_not_of(L"\t ") == string::npos) { if (se == L"OutsTemplate:") { OutsTemplate = L""; } else if (se == L"Kb_Key_Space:") { Kb_Key_Space = L" "; } continue; } v = v.substr(v.find_first_not_of(L"\t "));
		int x = 0; for (size_t i = 0; i <= se.length(); ++i) x += se[i];
		auto er = [se, v]() { showOutsMsg(L"Error in ", settings, L" [" + se + L" " + v + L"]", 0); };
		switch (x) {
			case 1273://ManualRepeat:
				{ if (v == L"1" || v == L"0") ManualRepeat = stoi(v); else er(); } break;
			case 1022://io_Auto_BS:
				{ if (v == L"1" || v == L"0") io_Auto_BS = stoi(v); else er(); } break;
			case 274://io:
				{ if (v.length() > 0) io = v[0]; else er(); } break;
			case 2738://ShowMultiStrandElapsedOnly:
				{ if (v == L"1" || v == L"0") showMultiStrandElapsedOnly = stoi(v); else er(); } break;
			case 865://PauseKey:
				{ if (check_if_num(v) != L"") PauseKey = stoi(v); else er(); } break;
			case 1543://NoEscapeOrPause:
				{ if (v == L"1" || v == L"0") { NoEscapeOrPause = stoi(v); GetAsyncKeyState(VK_ESCAPE); } else er(); } break;
			case 2053://R+ESC_A+ESC_Loop_Insert: <rgb,> <app,>
				{ if (v == L"1" || v == L"0") Loop_Insert = stoi(v); else er(); } break;
			case 1708://Loop_Insert_Text:
				{ if (v == L"Loop_Insert_Text" || v == L"") v = L">"; if (v.substr(v.length() - 1) != L">") v += L">"; if (v.length() > 0) Loop_Insert_Text = v.substr(0); else er(); } break;
			case 1993://Ignore_Print_Screen:
				{ if (v == L"1" || v == L"0") Ignore_Print_Screen = stoi(v); else er(); } break;
			case 1946://Kb_Key_Print_Screen::
				{ if (v.length() > 0) Kb_Key_Print_Screen = v.substr(0); else er(); } break;
			case 1394://Ignore_Insert:
				{ if (v == L"1" || v == L"0") Ignore_Insert = stoi(v); else er(); } break;
			case 1360://Ignore_Delete:
				{ if (v == L"1" || v == L"0") Ignore_Delete = stoi(v); else er(); } break;
			case 1158://Ignore_Home:
				{ if (v == L"1" || v == L"0") Ignore_Home = stoi(v); else er(); } break;
			case 1044://Ignore_End: | Ignore_Tab:
				{ if (v == L"1" || v == L"0") {
					if (se == L"Ignore_End:") Ignore_End = stoi(v);
					else if (se == L"Ignore_Tab:") ignoreTab = stoi(v);
				} else er(); } break;
			case 1145://Ignore_PgUp:
				{ if (v == L"1" || v == L"0") Ignore_PgUp = stoi(v); else er(); } break;
			case 783://Kb_Key_A:
				{ if (v.length() > 0) Kb_Key_A = v.substr(0); else er(); } break;
			case 784://Kb_Key_B:
				{ if (v.length() > 0)Kb_Key_B = v.substr(0); else er(); } break;
			case 785://Kb_Key_C:
				{ if (v.length() > 0) Kb_Key_C = v.substr(0); else er(); } break;
			case 786://Kb_Key_D:
				{ if (v.length() > 0) Kb_Key_D = v.substr(0); else er(); } break;
			case 787://Kb_Key_E:
				{ if (v.length() > 0) Kb_Key_E = v.substr(0); else er(); } break;
			case 788://Kb_Key_F:
				{ if (v.length() > 0) Kb_Key_F = v.substr(0); else er(); } break;
			case 789://Kb_Key_G:
				{ if (v.length() > 0) Kb_Key_G = v.substr(0); else er(); } break;
			case 790://Kb_Key_H:
				{ if (v.length() > 0) Kb_Key_H = v.substr(0); else er(); } break;
			case 791://Kb_Key_I:
				{ if (v.length() > 0) Kb_Key_I = v.substr(0); else er(); } break;
			case 792://Kb_Key_J:
				{ if (v.length() > 0) Kb_Key_J = v.substr(0); else er(); } break;
			case 793://Kb_Key_K:
				{ if (v.length() > 0) Kb_Key_K = v.substr(0); else er(); } break;
			case 794://Kb_Key_L:
				{ if (v.length() > 0) Kb_Key_L = v.substr(0); else er(); } break;
			case 795://Kb_Key_M:
				{ if (v.length() > 0) Kb_Key_M = v.substr(0); else er(); } break;
			case 796://Kb_Key_N:
				{ if (v.length() > 0) Kb_Key_N = v.substr(0); else er(); } break;
			case 797://Kb_Key_O:
				{ if (v.length() > 0) Kb_Key_O = v.substr(0); else er(); } break;
			case 798://Kb_Key_P:
				{ if (v.length() > 0) Kb_Key_P = v.substr(0); else er(); } break;
			case 799://Kb_Key_Q:
				{ if (v.length() > 0) Kb_Key_Q = v.substr(0); else er(); } break;
			case 800://Kb_Key_R:
				{ if (v.length() > 0) Kb_Key_R = v.substr(0); else er(); } break;
			case 801://Kb_Key_S:
				{ if (v.length() > 0) Kb_Key_S = v.substr(0); else er(); } break;
			case 802://Kb_Key_T:
				{ if (v.length() > 0) Kb_Key_T = v.substr(0); else er(); } break;
			case 803://Kb_Key_U:
				{ if (v.length() > 0) Kb_Key_U = v.substr(0); else er(); } break;
			case 804://Kb_Key_V:
				{ if (v.length() > 0) Kb_Key_V = v.substr(0); else er(); } break;
			case 805://Kb_Key_W:
				{ if (v.length() > 0) Kb_Key_W = v.substr(0); else er(); } break;
			case 806://Kb_Key_X:
				{ if (v.length() > 0) Kb_Key_X = v.substr(0); else er(); } break;
			case 807://Kb_Key_Y:
				{ if (v.length() > 0) Kb_Key_Y = v.substr(0); else er(); } break;
			case 808://Kb_Key_Z:
				{ if (v.length() > 0) Kb_Key_Z = v.substr(0); else er(); } break;
			case 766://Kb_Key_0:
				{ if (v.length() > 0) Kb_Key_0 = v.substr(0); else er(); } break;
			case 767://Kb_Key_1:
				{ if (v.length() > 0) Kb_Key_1 = v.substr(0); else er(); } break;
			case 768://Kb_Key_2:
				{ if (v.length() > 0) Kb_Key_2 = v.substr(0); else er(); } break;
			case 769://Unicode: | //Kb_Key_3:
				{ if (se == L"Unicode:") { if (v == L"1" || v == L"0") Unicode = stoi(v); else er(); }
				else if (se == L"Kb_Key_3:") { if (v.length() > 0) Kb_Key_3 = v.substr(0); else er(); }
				} break;
			case 770://Kb_Key_4:
				{ if (v.length() > 0) Kb_Key_4 = v.substr(0); else er(); } break;
			case 771://Kb_Key_5:
				{ if (v.length() > 0) Kb_Key_5 = v.substr(0); else er(); } break;
			case 772://Kb_Key_6:
				{ if (v.length() > 0) Kb_Key_6 = v.substr(0); else er(); } break;
			case 773://Kb_Key_7:
				{ if (v.length() > 0) Kb_Key_7 = v.substr(0); else er(); } break;
			case 774://Kb_Key_8:
				{ if (v.length() > 0) Kb_Key_8 = v.substr(0); else er(); } break;
			case 775://Kb_Key_9:
				{ if (v.length() > 0) Kb_Key_9 = v.substr(0); else er(); } break;
			case 837://Kb_Key_F1:
				{ if (v.length() > 0) Kb_Key_F1 = v.substr(0); else er(); } break;
			case 838://Kb_Key_F2:
				{ if (v.length() > 0) Kb_Key_F2 = v.substr(0); else er(); } break;
			case 839://Kb_Key_F3:, EditorDb:
				{ if (v.length() > 0) {
					if (se == L"EditorDb:") editorDb = v.substr(0);
					else if (se == L"Kb_Key_F3:") Kb_Key_F3 = v.substr(0);
				}else er(); } break;
			case 840://Kb_Key_F4:
				{ if (v.length() > 0) Kb_Key_F4 = v.substr(0); else er(); } break;
			case 841://Kb_Key_F5:
				{ if (v.length() > 0) Kb_Key_F5 = v.substr(0); else er(); } break;
			case 842://Kb_Key_F6:
				{ if (v.length() > 0) Kb_Key_F6 = v.substr(0); else er(); } break;
			case 843://Kb_Key_F7:
				{ if (v.length() > 0) Kb_Key_F7 = v.substr(0); else er(); } break;
			case 844://Kb_Key_F8:
				{ if (v.length() > 0) Kb_Key_F8 = v.substr(0); else er(); } break;
			case 845://Kb_Key_F9:
				{ if (v.length() > 0) Kb_Key_F9 = v.substr(0); else er(); } break;
			case 885://Kb_Key_F10:
				{ if (v.length() > 0) Kb_Key_F10 = v.substr(0); else er(); } break;
			case 886://Kb_Key_F11:
				{ if (v.length() > 0) Kb_Key_F11 = v.substr(0); else er(); } break;
			case 887://Kb_Key_F12:
				{ if (v.length() > 0) Kb_Key_F12 = v.substr(0); else er(); } break;
			case 1113://Kb_Key_Left:
				{ if (v.length() > 0) Kb_Key_Left = v.substr(0); else er(); } break;
			case 1126://Kb_Key_Down: | Ignore_PgDn:
				{ if (se == L"Kb_Key_Down:") { if (v.length() > 0) Kb_Key_Down = v.substr(0); else er(); }
				else if (se == L"Ignore_PgDn:") { if (v == L"1" || v == L"0") Ignore_PgDn = stoi(v); else er(); }
				} break;
			case 1210://Kb_Key_Space:
				{ if (v.length() > 0) Kb_Key_Space = v.substr(0); } break;
			case 1718://Kb_Key_Left_Shift:
				{ if (v.length() > 0) Kb_Key_Left_Shift = v.substr(0); else er(); } break;
			case 1833://Kb_Key_Right_Shift:
				{ if (v.length() > 0) Kb_Key_Right_Shift = v.substr(0); else er(); } break;
			case 1497://Kb_Key_Left_Alt:
				{ if (v.length() > 0) Kb_Key_Left_Alt = v.substr(0); else er(); } break;
			case 1612://Kb_Key_Right_Alt:
				{ if (v.length() > 0) Kb_Key_Right_Alt = v.substr(0); else er(); } break;
			case 1613://Kb_Key_Left_Ctrl:
				{ if (v.length() > 0) Kb_Key_Left_Ctrl = v.substr(0); else er(); } break;
			case 1728://Kb_Key_Right_Ctrl:
				{ if (v.length() > 0) Kb_Key_Right_Ctrl = v.substr(0); else er(); } break;
			case 1228://Kb_Key_Enter: | Kb_Key_Right:
				{ if (v.length() > 0) {
					if (se == L"Kb_Key_Enter:") Kb_Key_Enter = v.substr(0);
					else if (se == L"Kb_Key_Right:") Kb_Key_Right = v.substr(0);
				} else er(); } break;
			case 1109://Kb_Key_Caps:
				{ if (v.length() > 0) Kb_Key_Caps = v.substr(0); else er(); } break;
			case 1904://Kb_Key_Grave_Accent:
				{ if (v.length() > 0) Kb_Key_Grave_Accent = v.substr(0); else er(); } break;
			case 1242://Kb_Key_Minus:
				{ if (v.length() > 0) Kb_Key_Minus = v.substr(0); else er(); } break;
			case 1222://Kb_Key_Equal:
				{ if (v.length() > 0) Kb_Key_Equal = v.substr(0); else er(); } break;
			case 1908://Kb_Key_Left_Bracket:
				{ if (v.length() > 0) Kb_Key_Left_Bracket = v.substr(0); else er(); } break;
			case 1626://Kb_Key_Backslash:
				{ if (v.length() > 0) Kb_Key_Backslash = v.substr(0); else er(); } break;
			case 1655://Kb_Key_Semicolon:
				{ if (v.length() > 0) Kb_Key_Semicolon = v.substr(0); else er(); } break;
			case 1244://Kb_Key_Quote:
				{ if (v.length() > 0) Kb_Key_Quote = v.substr(0); else er(); } break;
			case 1211://Kb_Key_Comma:
				{ if (v.length() > 0) Kb_Key_Comma = v.substr(0); else er(); } break;
			case 1329://Kb_Key_Period:
				{ if (v.length() > 0) Kb_Key_Period = v.substr(0); else er(); } break;
			case 1982://Kb_Key_Forwardslash:
				{ if (v.length() > 0) Kb_Key_Forwardslash = v.substr(0); else er(); } break;
			case 1123://Kb_Key_Menu:
				{ if (v.length() > 0) Kb_Key_Menu = v.substr(0); else er(); } break;
			case 1347://Kb_Key_Insert:
				{ if (v.length() > 0) Kb_Key_Insert = v.substr(0); else er(); } break;
			case 1111://Kb_Key_Home:
				{ if (v.length() > 0) Kb_Key_Home = v.substr(0); else er(); } break;
			case 997://Kb_Key_End: | Kb_Key_Tab:
				{ if (v.length() > 0) {
					if (se == L"Kb_Key_End:") Kb_Key_End = v.substr(0);
					else if (se == L"Kb_Key_Tab:") Kb_Key_Tab = v.substr(0);
				 } else er(); } break;
			case 1079://Kb_Key_PgDn:
				{ if (v.length() > 0) Kb_Key_PgDn = v.substr(0); else er(); } break;
			case 1474://Kb_Key_Numpad_0:
				{ if (v.length() > 0) Kb_Key_Numpad_0 = v.substr(0); else er(); } break;
			case 1475://Kb_Key_Numpad_1:
				{ if (v.length() > 0) Kb_Key_Numpad_1 = v.substr(0); else er(); } break;
			case 1476://Kb_Key_Numpad_2:
				{ if (v.length() > 0) Kb_Key_Numpad_2 = v.substr(0); else er(); } break;
			case 1477://Kb_Key_Numpad_3:
				{ if (v.length() > 0) Kb_Key_Numpad_3 = v.substr(0); else er(); } break;
			case 1478://Kb_Key_Numpad_4:
				{ if (v.length() > 0) Kb_Key_Numpad_4 = v.substr(0); else er(); } break;
			case 1479://Kb_Key_Numpad_5:
				{ if (v.length() > 0) Kb_Key_Numpad_5 = v.substr(0); else er(); } break;
			case 1480://Kb_Key_Numpad_6:
				{ if (v.length() > 0) Kb_Key_Numpad_6 = v.substr(0); else er(); } break;
			case 1481://Kb_Key_Numpad_7:
				{ if (v.length() > 0) Kb_Key_Numpad_7 = v.substr(0); else er(); } break;
			case 1482://Kb_Key_Numpad_8:
				{ if (v.length() > 0) Kb_Key_Numpad_8 = v.substr(0); else er(); } break;
			case 1483://Kb_Key_Numpad_9:
				{ if (v.length() > 0) Kb_Key_Numpad_9 = v.substr(0); else er(); } break;
			case 1447://Kb_Key_Numlock:
				{ if (v.length() > 0) Kb_Key_Numlock = v.substr(0); else er(); } break;
			case 2023://Kb_Key_Numpad_Divide: | Kb_Key_Right_Bracket:
				{ if (v.length() > 0) {
					if (se == L"Kb_Key_Numpad_Divide:") Kb_Key_Numpad_Divide = v.substr(0);
					else if (se == L"Kb_Key_Right_Bracket:") Kb_Key_Right_Bracket = v.substr(0);
				} else er(); } break;
			case 2290://Kb_Key_Numpad_Multiply:
				{ if (v.length() > 0) Kb_Key_Numpad_Multiply = v.substr(0); else er(); } break;
			case 1950://Kb_Key_Numpad_Minus:
				{ if (v.length() > 0) Kb_Key_Numpad_Minus = v.substr(0); else er(); } break;
			case 1691://Kb_Key_Numpad_Add:
				{ if (v.length() > 0) Kb_Key_Numpad_Add = v.substr(0); else er(); } break;
			case 2037://Kb_Key_Numpad_Period:
				{ if (v.length() > 0) Kb_Key_Numpad_Period = v.substr(0); else er(); } break;
			case 1936://Kb_Key_Numpad_Enter:
				{ if (v.length() > 0) Kb_Key_Numpad_Enter = v.substr(0); else er(); } break;
			case 2066://DbMultiLineDelimiter:
				if (v.length() > 0 && v[0] != '\\') {
					multiLine = 1; multiLineDelim = v[0];
				} else { multiLine = 0; multiLineDelim = L'\n'; }
				break;
			case 872://Replacer:
				{ if (v == L"1" || v == L"0") replacer = stoi(v); else er(); } break;
			case 1780://BackslashLogicals:
				{ if (v == L"1" || v == L"0") BackslashLogicals = stoi(v); else er(); } break;
			case 3573://RSHIFT+CtrlKey_ToggleCtrlScanOnlyMode:
				{ if (v == L"1" || v == L"0") ToggleCtrlScanOnly = stoi(v); else er(); } break;
			case 3268://RSHIFT+RCTRL_ToggleCloseCtrlMode:
				{ if (v == L"1" || v == L"0") ToggleCloseCtrl = stoi(v); else er(); } break;
			case 2361://RSHIFT+CtrlKey_ToggleKeep:
				{ if (v == L"1" || v == L"0") ToggleKeep = stoi(v); else er(); } break;
			case 764://OutTabs:
				{ if (v == L"1" || v == L"0") { OutTabs = stoi(v); OutTab = OutTabs ? L"\t" : L""; } else er(); } break;
			case 1462://ClearStrandKey:
				{ if (check_if_num(v) > L"") ClearStrandKey = stoi(v); else er(); } break;
			case 1056://CommaSleep:
				{ if (check_if_num(v) != L"") { if (stoi(v) <= 0) { v = L"1"; } CommaSleep = stoi(v); } else er(); } break;
			case 673://Editor:
				{ if (v.length() > 0) editor = v.substr(0); else er(); } break;
			case 722://Editor1:
				{ if (v.length() > 0) editor1 = v.substr(0); else er(); } break;
			case 857://EditorSe:
				{ if (v.length() > 0) editorSe = v.substr(0); else er(); } break;
			//case 839://EditorDb:
			case 680://Assume:
				{ if (v == L"1" || v == L"0") assume = stoi(v); else er(); } break;
			case 1095://ShowStrand:
				{ if (v == L"1" || v == L"0") showStrand = stoi(v); else er(); } break;
			case 847://Database:
				{ if (v.length() > 0) { database = v.substr(0); database = regex_replace(database, wregex(L"/"), L"\\"); db = database.substr(database.find_last_of('\\') + 1) + L" - "; } else er(); } break;
			case 1038://ReplacerDb:
				{ if (v.length() > 0) { replacerDb = v.substr(0); } else er(); } break;
			case 1313://OutsTemplate: | Kb_Key_Delete:
				{ if (se == L"OutsTemplate:") OutsTemplate = v.substr(0);
				else if (se == L"Kb_Key_Delete:") { if (v.length() > 0) Kb_Key_Delete = v.substr(0); else er(); }
				} break;
			case 1354://CloseCtrlMode:
				{ if (v == L"1" || v == L"0") close_ctrl_mode = stoi(v); else er(); } break;
			case 1659://CtrlScanOnlyMode:
				{ if (v == L"1" || v == L"0") qScanOnly = stoi(v); else er(); } break;
			case 1677://StrandLengthMode:
				{ if (v == L"1" || v == L"0") strandLengthMode = stoi(v); else er(); } break;
			case 1288://StrandLength:
				{ if (check_if_num(v) != L"") strandLength = stoi(v); else er(); } break;
			case 965://Ignore_A-Z:
				{ if (v == L"1" || v == L"0") ignoreAZ = stoi(v); else er(); } break;
			case 915://Ignore_0-9: | Kb_Key_Up:
				{ if (se == L"Ignore_0-9:") { if (v == L"1" || v == L"0") ignore09 = stoi(v); else er(); }
				else if (se == L"Kb_Key_Up:"){ if (v.length() > 0) Kb_Key_Up = v.substr(0); else er(); }
				} break;
			case 1172://StartHidden:
				{ if (v == L"1" || v == L"0") startHidden = stoi(v); else er(); } break;
			case 760://CtrlKey:
				{ if (check_if_num(v) > L"") cKey = stoi(v); else er(); } break;
			case 999://ShowIntro:
				{ if (v == L"1" || v == L"0") showIntro = stoi(v); else er(); } break;
			case 1324://ShowSettings:
				{ if (v == L"1" || v == L"0") showSettings = stoi(v); else er(); } break;
			case 1004://Frequency:
				{ if (check_if_num(v) != L"") frequency = stoi(v); else er(); } break;
			case 964://RepeatKey:
				{ if (check_if_num(v) != L"") reKey = stoi(v); else er(); } break;
			case 1649://AutoBs_RepeatKey:
				{ if (v == L"1" || v == L"0") AutoBs_RepeatKey = stoi(v); else er(); } break;
			case 902://ShowOuts:
				{ if (v == L"1" || v == L"0") showOuts = stoi(v); else er(); } break;
			case 2913://SlightPauseInBetweenConnects:
				{ if (v == L"1" || v == L"0") SlightPauseInBetweenConnects = stoi(v); else er(); } break;
			case 1571://CloseCtrlSpacer:
				{ if (check_if_num(v) > L"") { if (stoi(v) <= 0) { v = L"1"; } CloseCtrlSpacer = stoi(v); } else er(); } break;
			case 1467://RgbScaleLayout:
				{ if (check_if_num(v) > L"") RgbScaleLayout = stod(v); else er(); } break;
			case 1201://MultiStrand:
				{ if (v == L"1" || v == L"0") multiStrand = stoi(v); else er(); } break;
			case 1618://ShowMultiStrand:
				{ if (v == L"1" || v == L"0") showMultiStrand = stoi(v); else er(); } break;
			case 1098://AutoBs_EscH: | Ignore_F1-F12: | Kb_Key_PgUp:
				{ if (se == L"AutoBs_EscH:") { if (v == L"1" || v == L"0") EscHAutoBs = stoi(v); else er(); }
				else if (se == L"Ignore_F1-F12:") { if (v == L"1" || v == L"0") ignoreF1s = stoi(v); else er(); }
				else if (se == L"Kb_Key_PgUp:") { if (v.length() > 0) Kb_Key_PgUp = v.substr(0); else er(); }
				} break;
			case 1519://AutoBs_EscComma:
				{ if (v == L"1" || v == L"0") EscCommaAutoBs = stoi(v); else er(); } break;
			case 1530://AutoBs_EscEqual:
				{ if (v == L"1" || v == L"0") EscEqualAutoBs = stoi(v); else er(); } break;
			case 1723://SeHotReload_CtrlS:
				{ if (v == L"1" || v == L"0") SeHotReload_CtrlS = stoi(v); else er(); } break;
			case 2098://SeDbClearStrand_CtrlS:
				{ if (v == L"1" || v == L"0") SeDbClearStrand_CtrlS = stoi(v); else er(); } break;
			case 1257://Ignore_Space:
				{ if (v == L"1" || v == L"0") ignoreSpace = stoi(v); else er(); } break;
			case 1403://Ignore_Arrows:
				{ if (v == L"1" || v == L"0") ignoreArrows = stoi(v); else er(); } break;
			case 1048://Ignore_Esc:
				{ if (v == L"1" || v == L"0") ignoreEsc = stoi(v); else er(); } break;
			case 1001://Kb_Key_Esc:
				{ if (v.length() > 0) Kb_Key_Esc = v.substr(0); else er(); } break;
			case 1275://Ignore_Enter:
				{ if (v == L"1" || v == L"0") ignoreEnter = stoi(v); else er(); } break;
			case 1156://Ignore_Caps:
				{ if (v == L"1" || v == L"0") ignoreCaps = stoi(v); else er(); } break;
			case 1351://Ignore_LShift:
				{ if (v == L"1" || v == L"0") ignoreLShift = stoi(v); else er(); } break;
			case 1357://Ignore_RShift:
				{ if (v == L"1" || v == L"0") ignoreRShift = stoi(v); else er(); } break;
			case 1130://Ignore_LAlt:
				{ if (v == L"1" || v == L"0") ignoreLAlt = stoi(v); else er(); } break;
			case 1136://Ignore_RAlt:
				{ if (v == L"1" || v == L"0") ignoreRAlt = stoi(v); else er(); } break;
			case 1246://Ignore_LCtrl:
				{ if (v == L"1" || v == L"0") ignoreLCtrl = stoi(v); else er(); } break;
			case 1252://Ignore_RCtrl:
				{ if (v == L"1" || v == L"0") ignoreRCtrl = stoi(v); else er(); } break;
			case 1856://Ignore_GraveAccent:
				{ if (v == L"1" || v == L"0") ignoreGraveAccent = stoi(v); else er(); } break;
			case 1289://Ignore_Minus:
				{ if (v == L"1" || v == L"0") ignoreMinus = stoi(v); else er(); } break;
			case 1269://Ignore_Equal:
				{ if (v == L"1" || v == L"0") ignoreEqual = stoi(v); else er(); } break;
			case 1541://Ignore_LBracket:
				{ if (v == L"1" || v == L"0") ignoreLBracket = stoi(v); else er(); } break;
			case 1547://Ignore_RBracket:
				{ if (v == L"1" || v == L"0") ignoreRBracket = stoi(v); else er(); } break;
			case 1673://Ignore_Backslash:
				{ if (v == L"1" || v == L"0") ignoreBackslash = stoi(v); else er(); } break;
			case 1702://Ignore_Semicolon:
				{ if (v == L"1" || v == L"0") ignoreSemicolon = stoi(v); else er(); } break;
			case 1291://Ignore_Quote:
				{ if (v == L"1" || v == L"0") ignoreQuote = stoi(v); else er(); } break;
			case 1258://Ignore_Comma:
				{ if (v == L"1" || v == L"0") ignoreComma = stoi(v); else er(); } break;
			case 1376://Ignore_Period:
				{ if (v == L"1" || v == L"0") ignorePeriod = stoi(v); else er(); } break;
			case 2029://Ignore_Forwardslash:
				{ if (v == L"1" || v == L"0") ignoreForwardslash = stoi(v); else er(); } break;
			case 1170://Ignore_Menu:
				{ if (v == L"1" || v == L"0") ignoreMenuKey = stoi(v); else er(); } break;
			case 1346://Ignore_NumPad:
				{ if (v == L"1" || v == L"0") ignoreNumPad = stoi(v); else er(); } break;
			case 934://Exit_EscX:
				{ if (v == L"1" || v == L"0") enableEscX = stoi(v); else er(); } break;
		}
	}
	f.close();
 }

void printSe() {
	loadSe();
	if (showSettings) {
		auto print = [](wstring s) { if (s[0] > 127) { SetConsoleOutputCP(CP_UTF7); } wcout << s << '\n'; SetConsoleOutputCP(CP_UTF8); };
		wcout << settings << '\n'; ifstream f(settings); if (f.fail()) { showOutsMsg(L"Copy to ", settings, L"\n", 1); }
		cout << "ShowSettings: " << showSettings << '\n';
		cout << "ShowIntro: " << showIntro << '\n';
		cout << "ShowStrand: " << showStrand << '\n';
		cout << "ClearStrandKey: " << ClearStrandKey << '\n';
		cout << "MultiStrand: " << multiStrand << '\n';
		cout << "ShowMultiStrand: " << showMultiStrand << '\n';
		cout << "ShowMultiStrandElapsedOnly: " << showMultiStrandElapsedOnly << '\n';
		cout << "ShowOuts: " << showOuts << '\n';
		wcout << "OutsTemplate: " << OutsTemplate << '\n';
		wcout << "OutTabs: " << OutTabs << '\n';
		wcout << "Settings: " << settings << '\n';
		wcout << "Database: " << database << '\n';
		cout << "DbMultiLineDelimiter: "; if (multiLineDelim[0] == '\n') cout << "\\n\n"; else showOutsMsg(L"", multiLineDelim, L"\n", 1);
		cout << "Replacer: " << replacer << '\n';
		wcout << "ReplacerDb: " << replacerDb << '\n';
		cout << "CtrlKey: " << cKey << '\n';
		cout << "CloseCtrlMode: " << close_ctrl_mode << '\n';
		cout << "RSHIFT+CtrlKey_ToggleCloseCtrlMode: " << ToggleCloseCtrl << '\n';
		cout << "RSHIFT+CtrlKey_ToggleKeep: " << ToggleKeep << '\n';
		cout << "CloseCtrlSpacer: " << CloseCtrlSpacer << '\n';
		cout << "CtrlScanOnlyMode: " << qScanOnly << '\n';
		cout << "RSHIFT+CtrlKey_ToggleCtrlScanOnlyMode: " << ToggleCtrlScanOnly << '\n';
		cout << "StrandLengthMode: " << strandLengthMode << '\n';
		cout << "StrandLength: " << strandLength << '\n';
		cout << "RepeatKey: " << reKey << '\n';
		cout << "PauseKey: " << PauseKey << '\n';
		cout << "RgbScaleLayout: " << RgbScaleLayout << '\n';
		cout << "Frequency: " << frequency << '\n';
		cout << "Ignore_0-9: " << ignore09 << '\n';
		wcout << "Kb_Key_0: "; print(Kb_Key_0);
		wcout << "Kb_Key_1: "; print(Kb_Key_1);
		wcout << "Kb_Key_2: "; print(Kb_Key_2);
		wcout << "Kb_Key_3: "; print(Kb_Key_3);
		wcout << "Kb_Key_4: "; print(Kb_Key_4);
		wcout << "Kb_Key_5: "; print(Kb_Key_5);
		wcout << "Kb_Key_6: "; print(Kb_Key_6);
		wcout << "Kb_Key_7: "; print(Kb_Key_7);
		wcout << "Kb_Key_8: "; print(Kb_Key_8);
		wcout << "Kb_Key_9: "; print(Kb_Key_9);
		cout << "Ignore_A-Z: " << ignoreAZ << '\n';
		wcout << "Kb_Key_A: "; print(Kb_Key_A);
		wcout << "Kb_Key_B: "; print(Kb_Key_B);
		wcout << "Kb_Key_C: "; print(Kb_Key_C);
		wcout << "Kb_Key_D: "; print(Kb_Key_D);
		wcout << "Kb_Key_E: "; print(Kb_Key_E);
		wcout << "Kb_Key_F: "; print(Kb_Key_F);
		wcout << "Kb_Key_G: "; print(Kb_Key_G);
		wcout << "Kb_Key_H: "; print(Kb_Key_H);
		wcout << "Kb_Key_I: "; print(Kb_Key_I);
		wcout << "Kb_Key_J: "; print(Kb_Key_J);
		wcout << "Kb_Key_K: "; print(Kb_Key_K);
		wcout << "Kb_Key_L: "; print(Kb_Key_L);
		wcout << "Kb_Key_M: "; print(Kb_Key_M);
		wcout << "Kb_Key_N: "; print(Kb_Key_N);
		wcout << "Kb_Key_O: "; print(Kb_Key_O);
		wcout << "Kb_Key_P: "; print(Kb_Key_P);
		wcout << "Kb_Key_Q: "; print(Kb_Key_Q);
		wcout << "Kb_Key_R: "; print(Kb_Key_R);
		wcout << "Kb_Key_S: "; print(Kb_Key_S);
		wcout << "Kb_Key_T: "; print(Kb_Key_T);
		wcout << "Kb_Key_U: "; print(Kb_Key_U);
		wcout << "Kb_Key_V: "; print(Kb_Key_V);
		wcout << "Kb_Key_W: "; print(Kb_Key_W);
		wcout << "Kb_Key_X: "; print(Kb_Key_X);
		wcout << "Kb_Key_Y: "; print(Kb_Key_Y);
		wcout << "Kb_Key_Z: "; print(Kb_Key_Z);
		cout << "Ignore_Arrows: " << ignoreArrows << '\n';
		wcout << "Kb_Key_Left: "; print(Kb_Key_Left);
		wcout << "Kb_Key_Up: "; print(Kb_Key_Up);
		wcout << "Kb_Key_Right: "; print(Kb_Key_Right);
		wcout << "Kb_Key_Down: "; print(Kb_Key_Down);
		cout << "Ignore_Backslash: " << ignoreBackslash << '\n';
		wcout << "Kb_Key_Backslash: "; print(Kb_Key_Backslash);
		cout << "Ignore_Caps: " << ignoreCaps << '\n';
		wcout << "Kb_Key_Caps: "; print(Kb_Key_Caps);
		cout << "Ignore_Comma: " << ignoreComma << '\n';
		wcout << "Kb_Key_Comma: "; print(Kb_Key_Comma);
		cout << "Ignore_Delete: " << Ignore_Delete << '\n';
		wcout << "Kb_Key_Delete: "; print(Kb_Key_Delete);
		cout << "Ignore_End: " << Ignore_End << '\n';
		wcout << "Kb_Key_End: "; print(Kb_Key_End);
		cout << "Ignore_Enter: " << ignoreEnter << '\n';
		wcout << "Kb_Key_Enter: "; print(Kb_Key_Enter);
		cout << "Ignore_Equal: " << ignoreEqual << '\n';
		wcout << "Kb_Key_Equal: "; print(Kb_Key_Equal);
		cout << "Ignore_Esc: " << ignoreEsc << '\n';
		wcout << "Kb_Key_Esc: "; print(Kb_Key_Esc);
		cout << "Ignore_F1-F12: " << ignoreF1s << '\n';
		wcout << "Kb_Key_F1: "; print(Kb_Key_F1);
		wcout << "Kb_Key_F2: "; print(Kb_Key_F2);
		wcout << "Kb_Key_F3: "; print(Kb_Key_F3);
		wcout << "Kb_Key_F4: "; print(Kb_Key_F4);
		wcout << "Kb_Key_F5: "; print(Kb_Key_F5);
		wcout << "Kb_Key_F6: "; print(Kb_Key_F6);
		wcout << "Kb_Key_F7: "; print(Kb_Key_F7);
		wcout << "Kb_Key_F8: "; print(Kb_Key_F8);
		wcout << "Kb_Key_F9: "; print(Kb_Key_F9);
		wcout << "Kb_Key_F10: "; print(Kb_Key_F10);
		wcout << "Kb_Key_F11: "; print(Kb_Key_F11);
		wcout << "Kb_Key_F12: "; print(Kb_Key_F12);
		cout << "Ignore_Print_Screen: " << Ignore_Print_Screen << '\n';
		wcout << "Kb_Key_Print_Screen: "; print(Kb_Key_Print_Screen);
		cout << "Ignore_Forwardslash: " << ignoreForwardslash << '\n';
		wcout << "Kb_Key_Forwardslash: "; print(Kb_Key_Forwardslash);
		cout << "Ignore_GraveAccent: " << ignoreGraveAccent << '\n';
		wcout << "Kb_Key_Grave_Accent: "; print(Kb_Key_Grave_Accent);
		cout << "Ignore_Home: " << Ignore_Home << '\n';
		wcout << "Kb_Key_Home: "; print(Kb_Key_Home);
		cout << "Ignore_Insert: " << Ignore_Insert << '\n';
		wcout << "Kb_Key_Insert: "; print(Kb_Key_Insert);
		cout << "Ignore_LAlt: " << ignoreLAlt << '\n';
		wcout << "Kb_Key_Left_Alt: "; print(Kb_Key_Left_Alt);
		cout << "Ignore_LBracket: " << ignoreLBracket << '\n';
		wcout << "Kb_Key_Left_Bracket: "; print(Kb_Key_Left_Bracket);
		cout << "Ignore_LCtrl: " << ignoreLCtrl << '\n';
		wcout << "Kb_Key_Left_Ctrl: "; print(Kb_Key_Left_Ctrl);
		cout << "Ignore_LShift: " << ignoreLShift << '\n';
		wcout << "Kb_Key_Left_Shift: "; print(Kb_Key_Left_Shift);
		cout << "Ignore_Menu: " << ignoreMenuKey << '\n';
		wcout << "Kb_Key_Menu: "; print(Kb_Key_Menu);
		cout << "Ignore_Minus: " << ignoreMinus << '\n';
		wcout << "Kb_Key_Minus: "; print(Kb_Key_Minus);
		cout << "Ignore_NumPad: " << ignoreNumPad << '\n';
		wcout << "Kb_Key_Numpad_0: "; print(Kb_Key_Numpad_0);
		wcout << "Kb_Key_Numpad_1: "; print(Kb_Key_Numpad_1);
		wcout << "Kb_Key_Numpad_2: "; print(Kb_Key_Numpad_2);
		wcout << "Kb_Key_Numpad_3: "; print(Kb_Key_Numpad_3);
		wcout << "Kb_Key_Numpad_4: "; print(Kb_Key_Numpad_4);
		wcout << "Kb_Key_Numpad_5: "; print(Kb_Key_Numpad_5);
		wcout << "Kb_Key_Numpad_6: "; print(Kb_Key_Numpad_6);
		wcout << "Kb_Key_Numpad_7: "; print(Kb_Key_Numpad_7);
		wcout << "Kb_Key_Numpad_8: "; print(Kb_Key_Numpad_8);
		wcout << "Kb_Key_Numpad_9: "; print(Kb_Key_Numpad_9);
		wcout << "Kb_Key_Numlock: "; print(Kb_Key_Numlock);
		wcout << "Kb_Key_Numpad_Divide: "; print(Kb_Key_Numpad_Divide);
		wcout << "Kb_Key_Numpad_Multiply: "; print(Kb_Key_Numpad_Multiply);
		wcout << "Kb_Key_Numpad_Minus: "; print(Kb_Key_Numpad_Minus);
		wcout << "Kb_Key_Numpad_Add: "; print(Kb_Key_Numpad_Add);
		wcout << "Kb_Key_Numpad_Period: "; print(Kb_Key_Numpad_Period);
		wcout << "Kb_Key_Numpad_Enter: "; print(Kb_Key_Numpad_Enter);
		cout << "Ignore_Period: " << ignorePeriod << '\n';
		wcout << "Kb_Key_Period: "; print(Kb_Key_Period);
		cout << "Ignore_PgDn: " << Ignore_PgDn << '\n';
		wcout << "Kb_Key_PgDn: "; print(Kb_Key_PgDn);
		cout << "Ignore_PgUp: " << Ignore_PgUp << '\n';
		wcout << "Kb_Key_PgUp: "; print(Kb_Key_PgUp);
		cout << "Ignore_Quote: " << ignoreQuote << '\n';
		wcout << "Kb_Key_Quote: "; print(Kb_Key_Quote);
		cout << "Ignore_RAlt: " << ignoreRAlt << '\n';
		wcout << "Kb_Key_Right_Alt: "; print(Kb_Key_Right_Alt);
		cout << "Ignore_RBracket: " << ignoreRBracket << '\n';
		wcout << "Kb_Key_Right_Bracket: "; print(Kb_Key_Right_Bracket);
		cout << "Ignore_RCtrl: " << ignoreRCtrl << '\n';
		wcout << "Kb_Key_Right_Ctrl: "; print(Kb_Key_Right_Ctrl);
		cout << "Ignore_RShift: " << ignoreRShift << '\n';
		wcout << "Kb_Key_Right_Shift: "; print(Kb_Key_Right_Shift);
		cout << "Ignore_Semicolon: " << ignoreSemicolon << '\n';
		wcout << "Kb_Key_Semicolon: "; print(Kb_Key_Semicolon);
		cout << "Ignore_Space: " << ignoreSpace << '\n';
		wcout << "Kb_Key_Space: "; print(Kb_Key_Space);
		cout << "Ignore_Tab: " << ignoreTab << '\n';
		wcout << "Kb_Key_Tab: "; print(Kb_Key_Tab);
		cout << "StartHidden: " << startHidden << '\n';
		cout << "SlightPauseInBetweenConnects: " << SlightPauseInBetweenConnects << '\n';
		cout << "CommaSleep: " << CommaSleep << '\n';
		cout << "BackslashLogicals: " << BackslashLogicals << '\n';
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
		wcout << "EditorDb: " << editorDb << '\n';
		wcout << "EditorSe: " << editorSe << '\n';
		cout << "R+ESC_A+ESC_Loop_Insert: " << Loop_Insert << '\n';
		wcout << "Loop_Insert_Text: " << Loop_Insert_Text << '\n';
		cout << "NoEscapeOrPause: " << NoEscapeOrPause << '\n';
		wcout << "io: " << io << '\n';
		wcout << "io_Auto_BS: " << io_Auto_BS << '\n';
		wcout << "ManualRepeat: " << ManualRepeat << '\n';
		cout << "Exit_EscX: " << enableEscX << '\n';
		cout << '\n';
	}
}

void toggle_visibility() {
	if (IsWindowVisible(GetConsoleWindow())) {
		SetForegroundWindow(GetConsoleWindow());
		kb(VK_F12);//if title "Select dnaspider"
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	else
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	Sleep(150);
	strand.clear();
}

wstring getAppT() {
	HWND h = GetForegroundWindow();
	int l = GetWindowTextLength(h);
	wstring title(l, 0);
	GetWindowTextW(h, &title[0], l + 1);
	title = regex_replace(title, wregex(L","), L"\\,"); title = regex_replace(title, wregex(L">"), L"\\g");	if (!BackslashLogicals) { title = regex_replace(title, wregex(L"\\|"), L"\\|"); title = regex_replace(title, wregex(L"&"), L"\\&"); }
	return title;
}

void getApp() {
	bool b = showMultiStrand; showMultiStrand = 0;
	out(L"<shift>,<shift->app:");
	showMultiStrand = b;
}

wstring getRGB(bool b = 0, bool bg = 0) {
	POINT pt; GetCursorPos(&pt); COLORREF color; HDC hDC;
	hDC = GetDC(NULL);
	if (hDC != NULL) {
		auto x = pt.x, y = pt.y; bool rs = 0;
		if (bg) {
			rs = 1;
			Sleep(3000);
		}
		color = GetPixel(hDC, x * RgbScaleLayout, y * RgbScaleLayout);
		ReleaseDC(NULL, hDC);
		if (color != CLR_INVALID) {
			wstring c = to_wstring(GetRValue(color)) + L" " + to_wstring(GetGValue(color)) + L" " + to_wstring(GetBValue(color));//cb
			if (b) {
				if (rs) {//rshift+r+esc
					auto r = L"<RGB~:" + c + L" " + to_wstring(x) + L" " + to_wstring(y) + (Loop_Insert ? Loop_Insert_Text : L">");
					cbSet(r);
					return L"";
				}
				qx = to_wstring(x); qy = to_wstring(y);
				return c;
			}
			if (GetAsyncKeyState(VK_LSHIFT))
				tail = L"<shift>,<shift->rgb:" + c + L" " + to_wstring(x) + L" " + to_wstring(y) + (Loop_Insert ? Loop_Insert_Text : L">");
			else
				tail = L"<shift>,<shift->rgb:" + c + (Loop_Insert ? Loop_Insert_Text : L">");
			re = tail;
		}
	}
	return L"";
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

auto cbGet(wstring cb = L"") {
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

void showOutsMsg(Multi multi, wstring s, wstring w, wstring s1 = L"", bool b = 0) {
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t x = 0; bool t = 0;
	if (multiLine) { w = regex_replace(w, wregex(L"\n"), L""); w = regex_replace(w, wregex(L"\t"), L""); }
	auto write = [&x, &t](wstring w) {
		if (w[0] > 127) SetConsoleOutputCP(CP_UTF7);
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
			out(to_wstring(multi.get_icp()));
			tail = t; i = x; re = L" "; codes = c; }
			write(L""); break;
			case'+':
			{ wstring a = to_wstring(multi.get_icp()); write(a); } break; //<+>
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
		if (w[x] > 127) SetConsoleOutputCP(CP_UTF7);
		wcout << w[x]; if (wcout.fail()) { wcout.imbue(locale()); wcout.clear(); wcout << L"[?]"; }
	}
	SetConsoleOutputCP(CP_UTF7); wcout << s1; if (wcout.fail()) { wcout.imbue(locale()); wcout.clear(); wcout << L"[?]\n"; }
	if (!b) cout << '\n';
	SetConsoleOutputCP(CP_UTF8);
}

void showOutsMsg(wstring s, wstring w, wstring s1 = L"", bool b = 0) {
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t x = 0; bool t = 0;
	if (multiLine) { w = regex_replace(w, wregex(L"\n"), L""); w = regex_replace(w, wregex(L"\t"), L""); }
	auto write = [&x, &t](wstring w) {
		if (w[0] > 127) SetConsoleOutputCP(CP_UTF7);
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
		if (w[x] > 127) SetConsoleOutputCP(CP_UTF7);
		wcout << w[x]; if (wcout.fail()) { wcout.imbue(locale()); wcout.clear(); wcout << L"[?]"; }
	}
	SetConsoleOutputCP(CP_UTF7); wcout << s1; if (wcout.fail()) { wcout.imbue(locale()); wcout.clear(); wcout << L"[?]\n"; }
	if (!b) cout << '\n';
	SetConsoleOutputCP(CP_UTF8);
}

void rei() { i += qq.find(L">"); }

void rei(Multi multi) {
	tail = multi.getTail(); qq = multi.getQQ(); i = multi.getI(); i += qq.find(L">");
}

wstring parse(int r, wstring &rs) {
	switch (r) {
	case 65: rs = L"A"; break;
	case 66: rs = L"B"; break;
	case 67: rs = L"C"; break;
	case 68: rs = L"D"; break;
	case 69: rs = L"E"; break;
	case 70: rs = L"F"; break;
	case 71: rs = L"G"; break;
	case 72: rs = L"H"; break;
	case 73: rs = L"I"; break;
	case 74: rs = L"J"; break;
	case 75: rs = L"K"; break;
	case 76: rs = L"L"; break;
	case 77: rs = L"M"; break;
	case 78: rs = L"N"; break;
	case 79: rs = L"O"; break;
	case 80: rs = L"P"; break;
	case 81: rs = L"Q"; break;
	case 82: rs = L"R"; break;
	case 83: rs = L"S"; break;
	case 84: rs = L"T"; break;
	case 85: rs = L"U"; break;
	case 86: rs = L"V"; break;
	case 87: rs = L"W"; break;
	case 88: rs = L"X"; break;
	case 89: rs = L"Y"; break;
	case 90: rs = L"Z"; break;
	case 97: rs = L"a"; break;
	case 98: rs = L"b"; break;
	case 99: rs = L"c"; break;
	case 100: rs = L"d"; break;
	case 101: rs = L"e"; break;
	case 102: rs = L"f"; break;
	case 103: rs = L"g"; break;
	case 104: rs = L"h"; break;
	case 105: rs = L"i"; break;
	case 106: rs = L"j"; break;
	case 107: rs = L"k"; break;
	case 108: rs = L"l"; break;
	case 109: rs = L"m"; break;
	case 110: rs = L"n"; break;
	case 111: rs = L"o"; break;
	case 112: rs = L"p"; break;
	case 113: rs = L"q"; break;
	case 114: rs = L"r"; break;
	case 115: rs = L"s"; break;
	case 116: rs = L"t"; break;
	case 117: rs = L"u"; break;
	case 118: rs = L"v"; break;
	case 119: rs = L"w"; break;
	case 120: rs = L"x"; break;
	case 121: rs = L"y"; break;
	case 122: rs = L"z"; break;
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
		[[fallthrough]];
	case -80://'>r': <rand> a-z
		r = (char)((rand() % ('z' + 1 - 'a')) + 'a');//cout << (char)r;
		[[fallthrough]];
	case -116://':R': <Rand:> A-Za-z
		r = rand() % 2;
		r = r == 1 ?
			(char)((rand() % ('z' + 1 - 'a')) + 'a') :
			(char)((rand() % ('Z' + 1 - 'A')) + 'A');//cout << (char)r;
	}
	if (parse_) rs = parse(r, rs);
	if (bg) return rs;
	qq = rs + qq.substr(qq.find(L">") + 1, qq.length());
	i = -1;
	if (speed > 0) sleep = 0;
	re = L" ";
	tail = qq;
	return rs;
}

void bs_input() {
	for (size_t t = 0; t < strand.length(); ++t) { if (strand[t] == 60 || ((!ignoreMenuKey) && strand[t] == Kb_Key_Menu[0]) || (!ignoreF1s) && (strand[t] == Kb_Key_F1[0] || strand[t] == Kb_Key_F2[0] || strand[t] == Kb_Key_F3[0] || strand[t] == Kb_Key_F4[0] || strand[t] == Kb_Key_F5[0] || strand[t] == Kb_Key_F6[0] || strand[t] == Kb_Key_F7[0] || strand[t] == Kb_Key_F8[0] || strand[t] == Kb_Key_F9[0] || strand[t] == Kb_Key_F10[0] || strand[t] == Kb_Key_F11[0] || strand[t] == Kb_Key_F12[0]) || (!ignoreEsc && strand[t] == Kb_Key_Esc[0]) || (!ignoreLShift && strand[t] == Kb_Key_Left_Shift[0]) || (!ignoreRShift && strand[t] == Kb_Key_Right_Shift[0]) || (!ignoreLAlt && strand[t] == Kb_Key_Left_Alt[0]) || (!ignoreRAlt && strand[t] == Kb_Key_Right_Alt[0]) || (!ignoreLCtrl && strand[t] == Kb_Key_Left_Ctrl[0]) || (!ignoreRCtrl && strand[t] == Kb_Key_Right_Ctrl[0]) || (!ignoreCaps && strand[t] == Kb_Key_Caps[0])) { continue; } kb(VK_BACK); } GetAsyncKeyState(VK_BACK);//exclude non bs: < LURD !@#$%^&*()_+ ~ S H A M C O P
}

void scanDb() {
	if (close_ctrl_mode) {
		if (strand.length() == 0) {
			if (re == L"")
				return;
		}
		else {
			if (strand.substr(strand.length() - 1) != L">")
				return;
		}
	}
	wifstream f(database); if (!f) { showOutsMsg(L"\nDatabase \"", database, L"\" not found!", 0); if (database == L"") { cout << "Create c:\\dna\\db.txt manually\n\n?+ESC\n\n"; } return; }
	wstring sv = strand;
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>)); //properties, general, language standard, >c++14 //_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	Mainn mainn; wstring cell; relink = 0; while (getline(f, cell, multiLineDelim[0])) { //cout << cell << endl;
		if (cell[1] == '\'') { if (cell.substr(0, 4) == L"<'''") break; } //ignore db...
		if (re > L"" && strand == L"" || strand > L"" && cell > L"" && (close_ctrl_mode && cell.substr(0, sv.size()) == strand || (!strandLengthMode || sv[0] == '<') && cell.substr(0, sv.size()) == sv.substr(0, sv.size() - 1) + io[0] || cell.substr(0, sv.size()) == sv.substr(0, sv.size() - 1) + L":" || cell.substr(0, sv.size()) == sv.substr(0, sv.size() - 1) + L"-" || cell.substr(0, sv.size() + 1) == sv.substr(0, sv.size() - 1) + L":>" || cell.substr(0, sv.size() + 1) == sv.substr(0, sv.size() - 1) + L"->") || cell.substr(0, sv.size() + 1) == strand + L">" || cell.substr(0, sv.size() + 1) == strand + L":" || cell.substr(0, sv.size() + 1) == strand + L"-" || cell.substr(0, sv.size() + 1) == strand + L"^" || cell.substr(0, sv.size() + 1) == strand + io[0] || (strandLengthMode && cell.substr(0, strandLength) == strand && cell[0] != '<') || close_ctrl_mode && strandLengthMode && strand[0] != '<' && cell.substr(0, sv.size() - 1) == sv.substr(0, sv.size() - 1)) { //found i>o, i:o, i-o, i:>o, i->o || i>o, i:o, i-o, i^o, i*o || io || io
			if (toggledCC) { toggledCC = 0; if (!ToggleKeep) close_ctrl_mode = !close_ctrl_mode; } if (toggledCSO) { toggledCSO = 0; if (!ToggleKeep) qScanOnly = !qScanOnly; } if (flipd) { flipd = 0; if (ToggleCloseCtrl) { if (close_ctrl_mode && strand[strand.length() - 1] == '>') { strand = strand.substr(0, strand.length() - 1); } close_ctrl_mode = 0; } if (ToggleCtrlScanOnly) qScanOnly = 0; }
			if (multiStrand) { if (re == L"") mainn.setStrand(cell); }
			if (close_ctrl_mode && strand.length() > 0 && strand[strand.length() - 1] == '>') strand = strand.substr(0, strand.length() - 1);
			if (re > L"" && strand == L"") {
				if (link[0] == '<' && cell.substr(0, link.length()) == link) relink = 1;
				cell = re;
				if (re[0] == '>') {
					if (re.substr(0, 20) == L"><shift>,<shift->xy:") { POINT pt; GetCursorPos(&pt); wstring xy = to_wstring(pt.x) + L"," + to_wstring(pt.y); codes = L"<shift>,<shift->xy:"; cell = codes + xy + L">"; re = cell; linkr = L""; if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << L"<xy:" + xy + L">\n"; } }
					else if (re.substr(0, 21) == L"><shift>,<shift->rgb:") { cell = L"<shift>,<shift->rgb:"; getRGB(); linkr = L""; if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << "<" << tail.substr(16, tail.length()) << endl; } mainn.t.clear(); }
					else if (re.substr(0, 21) == L"><shift>,<shift->app:") { wstring x = L"><shift>,<shift->app:"; out(L"<alt><esc><alt-><,1>"); x += getAppT(); out(L"<shift><alt><esc><alt-><shift->"); re = x + (Loop_Insert ? Loop_Insert_Text : L">"); }
				}
			}
			tail = re > L"" && strand == L"" ? re : cell.substr(strand.length(), cell.length() - strand.length());
			if (multiStrand) mainn.getStrand(cell);
			tail = isVar(tail); //<r:>
			if (tail[0] == io[0]) {//io:
				bool b = 0;	if (strand[0] != '<' && tail[1] == '>') { tail = tail.substr(2, tail.length()); codes = strand + tail; b = 1; }
				else tail = tail.substr(1, tail.length());
				if (tail[0] == '>') tail = tail.substr(1, tail.length());
				if (io_Auto_BS) bs_input();
				if (!b) codes = tail;
			}
			else {
				switch (tail[0]) {//set_tail
				case ':':
					tail = tail.substr(1, tail.length());
					if (tail[0] == '>') tail = tail.substr(1, tail.length());
					codes = tail;
					break;
				case '>':
					tail = tail.substr(1, tail.length());
					if (sv > L"") codes = strand[0] == '<' ? strand.substr(1, strand.length()) + tail : strand + tail;
					break;
				case '^'://i^o
					close_ctrl_mode = !close_ctrl_mode; qScanOnly = !qScanOnly;//<^^>
					if (tail[1] == '>') { tail = tail.substr(2, tail.length()); codes = strand + tail; break; }
					[[fallthrough]];
				case '-':
					tail = tail.substr(1, tail.length());
					if (tail[0] == '>') tail = tail.substr(1, tail.length());
					bs_input();
					codes = tail;
					break;
				default:
					codes = cell;
				}
			}
			if (noClearStrand) noClearStrand = 0;
			if (multiStrand) { reTail = codes; mainn.setTail(); }
			if (showOuts && !showMultiStrand) { showOutsMsg(L"found: " + OutTab + OutTab, cell); showOutsMsg(L"tail: " + OutTab + OutTab, tail); }
			if (tail.find(L"<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
			f.close(); fail = 0; esc_pressed = 0;
			Multi multi;
			for (i = 0; i < tail.length(); ++i) {
				if (multiStrand) { if (strand == sv && !noClearStrand) strand.clear(); }//multiStrand variant clear
				if (speed > 0) { if (sleep) { if (multiStrand) { re = multi.t = tail; multi.get_i = i; multi.q = qq; multi.setSpeed(speed); } Sleep(speed); if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; } } sleep = 1; }
				if (!NoEscapeOrPause) {
					GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { if (multi.esc == 1) {} else { esc_pressed = 0; pause_resume = 0; multiblock = 0; break; } }
					GetAsyncKeyState(PauseKey); if (GetAsyncKeyState(PauseKey)) {//int m = MessageBoxA(0, "Resume?", "dnaspider", MB_YESNO); if (m != IDYES) { break; } }
						while (GetAsyncKeyState(PauseKey) != 0) { Sleep(frequency / 3); }
						if (multiStrand) multi.setI();
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
						if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
					}
				}
				wstring ctail = tail.substr(i, 1);//extracted char from tail
				if (showOuts) { wcout << "ctail: " << OutTab << OutTab << (ctail[0] > 127 ? L"[?]" : ctail) << endl; }
				switch (ctail[0]) {
				case'<':
					qq = tail.substr(i, tail.length() - i); //<test>
					if (multiStrand) { multi.q = qq; multi.get_i = i; }
					if (showOuts) showOutsMsg(L"qq: " + OutTab + OutTab, qq);
					if (qq.substr(0, qq.find(L">")).find(L":") != std::string::npos) { //<test:#>
						qp = qq.substr(qq.find(L":") + 1, qq.find(L">") - qq.find(L":") - 1);//#
						if (qp[0] > 0) {
							if (qp[0] == ' ') qp = qp.substr(1);
							setQxQy(qp);
						}
					}
					switch (qq[1]) {
					case '<':
						if (testqqb(L"<<:")) {//cout
							if (replacer) { wstring t = qq; t = isVar(t); } //<<:{<x:>}>
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
							int s{}; for (auto &x : qp) s += x;
							auto q = to_wstring(s);	cbSet(q);
							rei();
						}
						else conn();
						break;
					case '!':
						if (testqqb(L"<!!!:")) {
							reTail = codes = (qp + L">"); strand = L""; i = tail.length(); }//set repeat
						else if (testqqb(L"<!!:")) {//multi run
							wstring t = qq.substr(qq.find(L">") + 1);//tail
							wstring m = qq.substr(0, qq.find(L">")) + L">";//q ms
							wstring x = L""; x += io[0]; x += L">";
							if (m.substr(m.length() - 2) == x || m.substr(m.length() - 2) == L":>" || m.substr(m.length() - 2) == L"->") m = to_wstring(CloseCtrlSpacer);
							else {
								m = m.substr(4); wstring io = L"";
								if (m.find(::io[0]) != string::npos) io = ::io[0];
								else if (m.find(L":") != string::npos) io = L":";
								else io = L"-";
								qp = m.substr(0, m.find(io) + 1);
								if (qp[0] == ' ') qp = qp.substr(1);
								m = m.substr(m.find(io) + 1);
								m = m.substr(0, m.length() - 1);
							}
							if (m == L"" || m == L"0") m = L"1";
							unsigned int m1 = stoi(m);
							strand = qp + L">"; thread thread(scanDb); Sleep(m1); thread.detach();
							tail = t; i = -1;
						}
						else if (qqb(L"<!>") || qqb(L"<!:>") || testqqb(L"<!:")) { if (qq[2] == ':') { if (qq[3] == '>') { strand.clear(); clearAllKeys(); rei(); break; } strand = qp; if (showStrand) { showOutsMsg(L"", OutsTemplate, strand + L"\n", 1); } } noClearStrand = 1; rei(); }
						else conn();
						break;
					case '^':
						if (qqb(L"<^>")) {//Toggle back after run
							flipd = 1; if (ToggleCloseCtrl) close_ctrl_mode = 1; if (ToggleCtrlScanOnly) qScanOnly = 1; rei();
						}
						else if (qqb(L"<^^>")) {
							close_ctrl_mode = !close_ctrl_mode; qScanOnly = !qScanOnly;
							tail.replace(tail.find(L"<^^>"), 4, L"");
							--i;
						}
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
						if (qqb(L"<+>")) {//repeat#
							calc();
							break;
						}
						else if (testqqb(L"<+:")) {//calc +
							if (check_if_num(qp) == L"") { printq(); continue; }
							if (multiStrand) multi.icp += stoi(qp); else ic += stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'-':
						if (testqqb(L"<-:")) {//-
							if (check_if_num(qp) == L"") { printq(); continue; }
							if (multiStrand) multi.icp -= stoi(qp); else ic -= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'*':
						if (testqqb(L"<*:")) {//*
							if (check_if_num(qp) == L"") { printq(); continue; }
							if (multiStrand) multi.icp *= stoi(qp); else ic *= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'/':
						if (testqqb(L"</:")) {//divide
							if (check_if_num(qp) == L"" || stoi(qp) <= 0) { printq(); continue; }
							if (multiStrand) multi.icp /= stoi(qp); else ic /= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'%':
						if (testqqb(L"<%:")) {//%
							if (check_if_num(qp) == L"") { printq(); continue; }
							if (multiStrand) multi.icp %= stoi(qp); else ic %= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case',':
						if (qqb(L"<,") && qq[2] != ':' && qq[2] != '-') { //<,#> || <,*
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
								i += 1; if (multiStrand) { multi.setI(); }
								if (s == L"0") return;
							}
							if (s[0] == '{' || stoi(s) > 0 && s[0] != '+') {
								multi.t = tail;
								if (qq[2] == '*') {
									GetAsyncKeyState(VK_ESCAPE); GetAsyncKeyState(VK_PAUSE); for (int j = 0; j < stoi(s); ++j) {//sleep150ms*?
										if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); if (showStrand) { cout << '\n'; } return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
										Sleep(CommaSleep);
									}
								}
								else Sleep(stoi(s));
							}
							else { printq(); break; };
							if (multiStrand) rei(multi); else rei();
						}
						else conn();
						break;
					case'\'':
						if (qq.find(L">") != string::npos && qqb(L"<''")) i = tail.length();//<''ignore>...
						else if (qq.find(L">") != string::npos && qqb(L"<'")) { //<'comments>
							if (showStrand) {
								showOutsMsg(L"", OutsTemplate, L"", 1);
								const wstring& v = qq.substr(2, qq.find('>') - 2);
								if (multiStrand)
									showOutsMsg(multi, L"", v, L"\n", 1);
								else
									showOutsMsg(L"", v, L"\n", 1);
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
							else if (qqb(L"<alt")) kbPress(L"<alt", VK_LMENU);
							else conn();
							break;
						case ':':
							if (testqqb(L"<a:")) {//alt codes
								kb(qp); rei();
							}
							else conn();
							break;
						case 'p':
							if (testqqb(L"<app:") || testqqb(L"<App:")) {//app activate, if app in foreground
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link = L"";//<app:a,x,ms,link>
								if (a.find(L"\\,") != wstring::npos) {// \,
									wstring t = a.substr(a.find_last_of(L"\\") + 2);
									if (t.find(L",") != string::npos) {
										a = a.substr(0, a.find_last_of(L"\\") + t.find(L",") + 2);
										qp = qp.substr(a.length());
									}
									else qp = L"";
								}
								else a = a.substr(0, a.find(L","));
								if (qp.find(L",") != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(L",") + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(L",") != string::npos) {
										ms = x.substr(x.find(L",") + 1); if (ms == L"") { printq(); break; }
										if (ms.find(L",") != string::npos) {
											link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(L","));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								a = regex_replace(a, wregex(L"\\\\,"), L",");// \,
								a = regex_replace(a, wregex(L"\\\\g"), L">");
								HWND h{}, h1{}; DWORD pid{};
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) { wcout << "Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find(L">") + 1), L"", 0); } };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };
								
								auto sifapp = [&multi, &qqC, &pid, &h1, &h, &a]() {
									if (qqC[1] == 'A') {//App
										h = GetForegroundWindow(); h1 = FindWindowW(0, a.c_str());
										if (h == h1) multi.setBreak();
									}
									else if (qqC[1] == 'a') {//'app
										h = FindWindowW(0, a.c_str()); GetWindowThreadProcessId(h, &pid);
										if (h) {
											if (IsIconic(h)) { ShowWindow(h, SW_RESTORE); ShowWindow(h, SWP_SHOWWINDOW); } SetForegroundWindow(h);
											multi.setBreak();
										}
									}
								};

								wstring tar = a, app = a;
								for (; size < length; ++size) { //cout << size << " app:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); prints(1); return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { ms = multi.getMS(); } f(); break; }
									if (multiStrand) { a = multi.getApp(); qqC = multi.getQQ(); }
									
									if (!BackslashLogicals) { tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
									if (tar.find(L"|") != string::npos || tar.find(L"&") != string::npos) {// | &
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (tar[j] == '|' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || tar[j] == '&' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - BackslashLogicals) : ta; if (BackslashLogicals && t == L"") { q = ta[0]; a = ta.substr(1); }
												if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
												if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1);//!\0
												sifapp(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find(L"|") != string::npos) sand = 1; else break;
													}
													if (q == L"|") {
														sor = 0;
														if (t.find(L"&") != string::npos) sor = 1;
														if (t.find(L"&") != string::npos && t.find(L"|") == string::npos) sor = 1;
													}
												}
												if (q == L"&" && multi.br) sand = 1;
												if (q == L"|" && multi.br) { sor = 1; break; } //wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
												multi.br = 0; a = t; j = -1; ta.clear();
												if (!BackslashLogicals) { tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
											}
										}
										if (!multiStrand) a = app;
										if (sor && sand) multi.br = 1; //sifapp
									}
									else {
										if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
										sifapp();
									}
									if (multi.getBreak()) break;
									else {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC[0] == io[0] || linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}

								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)// ..., true: false:>
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(L" ") != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {// ..., true: false:>
									linkC = linkC.substr(0, linkC.find(L" "));
									if (linkC == L"<") { if (multiStrand) { i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); tail = multi.getTail(); i += qqC.find(L">"); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
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
						default:
							conn();
						}
						break;
					case'b':
						if (qqb(L"<bs")) kbPress(L"<bs", VK_BACK);
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
							else if (qqb(L"<ctrl")) kbPress(L"<ctrl", VK_CONTROL);
							else conn();
							break;
						case 'B':
						case 'b':
							if (testqqb(L"<CB:") || testqqb(L"<cb:")) {
								qp = regex_replace(qp, wregex(L"\\\\g"), L">"); qp = regex_replace(qp, wregex(L"\\\\m"), multiLineDelim);
								cbSet(qp);
								if (qq[1] == 'C') { kbHold(VK_CONTROL); kb('v'); kbRelease(VK_CONTROL); }
								rei();
							}
							else conn();
							break;
						case 'a':
							if (qqb(L"<caps")) kbPress(L"<caps", VK_CAPITAL);
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
								if (qq[1] == 'D') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(L"", qp, L"", 0); }
								qp = regex_replace(qp, wregex(L"/"), L"\\");
								wifstream f(qp); if (!f) { showOutsMsg(L"\nDatabase \"", qp, L"\" not found!", 0); return; }
								database = editorDb = qp;
								db = database.substr(database.find_last_of('\\') + 1) + L" - ";
								rei();
								break;
							}
							else if (qqb(L"<db>")) { printDb(); rei(); }
							else conn();
							break;
						case 'o':
							if (qqb(L"<down")) kbPress(L"<down", VK_DOWN);
							else conn();
							break;
						case 'n':
							if (qqb(L"<dna:")) { HWND h = GetConsoleWindow(); SetConsoleTitleW(qp.c_str()); rei(); }
							else conn();
							break;
						case 'e':
							if (qqb(L"<delete")) kbPress(L"<delete", VK_DELETE);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'e':
						switch (qq[3]) {
						case 't':
							if (qqb(L"<enter")) kbPress(L"<enter", VK_RETURN);
							else conn();
							break;
						case 'd':
							if (qqb(L"<end")) kbPress(L"<end", VK_END);
							else conn();
							break;
						case 'c':
							if (qqb(L"<esc")) kbPress(L"<esc", VK_ESCAPE);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'f':
						switch (qq[2]) {
						case '1':
							if (qqb(L"<f10")) kbPress(L"<f10", VK_F10);
							else if (qqb(L"<f11")) kbPress(L"<f11", VK_F11);
							else if (qqb(L"<f12")) kbPress(L"<f12", VK_F12);
							else if (qqb(L"<f1")) kbPress(L"<f1", VK_F1);
							else conn();
							break;
						case '2':
							if (qqb(L"<f2")) kbPress(L"<f2", VK_F2);
							else conn();
							break;
						case '3':
							if (qqb(L"<f3")) kbPress(L"<f3", VK_F3);
							else conn();
							break;
						case '4':
							if (qqb(L"<f4")) kbPress(L"<f4", VK_F4);
							else conn();
							break;
						case '5':
							if (qqb(L"<f5")) kbPress(L"<f5", VK_F5);
							else conn();
							break;
						case '6':
							if (qqb(L"<f6")) kbPress(L"<f6", VK_F6);
							else conn();
							break;
						case '7':
							if (qqb(L"<f7")) kbPress(L"<f7", VK_F7);
							else conn();
							break;
						case '8':
							if (qqb(L"<f8")) kbPress(L"<f8", VK_F8);
							else conn();
							break;
						case '9':
							if (qqb(L"<f9")) kbPress(L"<f9", VK_F9);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'h':
						if (qqb(L"<home")) kbPress(L"<home", VK_HOME);
						else conn();
						break;
					case'i':
						switch (qq[2]) {
						case 'f':
							if (testqqb(L"<ifxy")) {//==, !=, <, <=, g, g=
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link = L"";//<ifxy:a a,x,ms,link link>
								a = a.substr(0, a.find(L","));
								if (qp.find(L",") != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(L",") + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(L",") != string::npos) {
										ms = x.substr(x.find(L",") + 1); if (ms == L"") { printq(); break; }
										if (ms.find(L",") != string::npos) {
											link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(L","));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) { wcout << "Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find(L">") + 1), L"", 0); } };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };

								auto sifxy = [&qqC, &multi, &a]() {
									auto q = a.find(L" ");
									auto x = a.substr(0, q), y = a.substr(q + 1);
									POINT pt; GetCursorPos(&pt);
									if (x == L".") x = to_wstring(pt.x);
									if (y == L".") y = to_wstring(pt.y);
									auto tx = stoi(x), ty = stoi(y);

									switch (qqC[5]) {
									case ':': //== <ifxy:> <ifxy=:> <ifxye:>  
									case '=':
									case 'e':
										if (pt.x == tx && pt.y == ty) multi.setBreak();
										break;
									case 'n': //!= <ifxyn:> <ifxy!:>
									case '!':
										if (pt.x != tx && pt.y != ty) multi.setBreak();
										break;
									case 'l'://<= <ifxyl:> <ifxyle:> <ifxy<:> <ifxy<=:>
									case 'L':
									case '<':
										if (qqC[6] == 'e' || qqC[6] == '=') { if (pt.x <= tx && pt.y <= ty) { multi.setBreak(); break; } } //ifxyle <=
										if (pt.x < tx && pt.y < ty) multi.setBreak();
										break;
									case 'g'://>= <ifxyg:> <ifxyge:> <ifxyg=:>
										if (qqC[6] == 'e' || qqC[6] == '=') { if (pt.x >= tx && pt.y >= ty) { multi.setBreak(); break; } } //ifxyge >=/g=
										if (pt.x > tx && pt.y > ty) multi.setBreak();
										break;
									}
								};

								wstring tar = a, app = a;
								for (; size < length; ++size) { //cout << size << "ifxy:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); prints(1); return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { ms = multi.getMS(); } f(); break; }
									if (multiStrand) { a = multi.getApp(); qqC = multi.getQQ(); }

									if (!BackslashLogicals) { tar = regex_replace(tar, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
									if (tar == L"") tar = a;
									if (tar.find(L"|") != string::npos || tar.find(L"&") != string::npos) {// | &
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (tar[j] == '|' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || tar[j] == '&' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - BackslashLogicals) : ta; if (BackslashLogicals && t == L"") { q = ta[0]; a = ta.substr(1); }
												if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
												if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1); //!\0
												sifxy(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find(L"|") != string::npos) sand = 1; else break;
													}
													if (q == L"|") {
														sor = 0;
														if (t.find(L"&") != string::npos) sor = 1;
														if (t.find(L"&") != string::npos && t.find(L"|") == string::npos) sor = 1;
													}
												}
												if (q == L"&" && multi.br) sand = 1;
												if (q == L"|" && multi.br) { sor = 1; break; }
												multi.br = 0; a = t; j = -1; ta.clear();
												if (!BackslashLogicals) tar = regex_replace(a, wregex(L"\\\\\\|"), L"  ");
											}
										}
										if (!multiStrand) a = app;
										if (sor) multi.br = 1; //sifxy
									}
									else {
										if (!BackslashLogicals) a = regex_replace(a, wregex(L"\\\\\\|"), L"|");
										sifxy();
									}
									if (multi.getBreak()) break;
									else {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC[0] == io[0] || linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}
								
								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)// ..., true: false:>
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<xy:a a,x,ms,<link->..., <xy:a a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(L" ") != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {// ..., true: false:>
									linkC = linkC.substr(0, linkC.find(L" "));
									if (linkC == L"<") { if (multiStrand) { i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); tail = multi.getTail(); i += qqC.find(L">"); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<xy:a a,x,ms,<link->..., <xy:a a,x,ms,link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (testqqb(L"<ifcb")) {//Clipboard ==, !=, <, <=, g, g=, (f)ind, (F)ind, (n)ot
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								if (qp == L"") { conn(); break; }
								wstring a = qp, x = L"1", ms = L"0", linkC; link = L"";//<ifcb:a,x,ms,link>
								if (a.find(L"\\,") != wstring::npos) {// \,
									wstring t = a.substr(a.find_last_of(L"\\") + 2);
									if (t.find(L",") != string::npos) {
										a = a.substr(0, a.find_last_of(L"\\") + t.find(L",") + 2);
										qp = qp.substr(a.length());
									}
									else qp = L"";
								}
								else a = a.substr(0, a.find(L","));
								if (a.find(L"\\,") != wstring::npos) a = regex_replace(a, wregex(L"\\\\,"), L",");// \,
								wstring app = a;
								if (qp.find(L",") != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(L",") + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(L",") != string::npos) {
										ms = x.substr(x.find(L",") + 1); if (ms == L"") { printq(); break; }
										if (ms.find(L",") != string::npos) {
											link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(L","));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) { wcout << L"Fail: " << OutTab << OutTab; showOutsMsg(L"", qqC.substr(0, qqC.find(L">") + 1), L"", 0); } };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								HANDLE hcb; wchar_t* c; wstring w;
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };
							
								auto sifcb = [&qqC, &multi, &x, &w, &a]() {
									switch (qqC[5]) {
									case ':': //== <ifcb:> <ifcb=:> <ifcbe:>
									case '=':
									case 'e':
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w == a) multi.setBreak();
										break;
									case 'A': //<if cb find y starting @ offset x: x y> | <ifcba:1 test>
									case 'a': //<if cb substring from index x matches y: x y> | <ifcbA:0 test>
										{
											auto x = a.substr(0, a.find(L" ")), y = a.substr(a.find(L" ") + 1);
											y = regex_replace(y, wregex(L"\\\\g"), L">");
											if (qqC[5] == 'A') {
												auto s = stoi(x) - 1; if (w.find(y, s) != wstring::npos) multi.setBreak();
											}
											else { //'a'
												if (w.substr(stoi(x), y.length()) == y) multi.setBreak();
											}
										}
										break;
									case 'S': //if cb starts with | <ifcbS:test>
									case 'E': //ends with | <ifcbE:>
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (qqC[5] == 'E') {
											if (w.ends_with(a)) multi.setBreak();
										}
										else { //'S'
											if (w.starts_with(a)) multi.setBreak();
										}
										break;
									case 'n': //!= <ifcbn:> <ifcb!:>
									case '!':
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w != a) multi.setBreak();
										break;
									case 'f': //<ifcbf:>
										if (regex_search(w, wregex(a))) multi.setBreak();
										break;
									case 'F': //<ifcbF:>
										a = regex_replace(a, wregex(L"\\\\g"), L">");
										if (w.find(a) != string::npos) multi.setBreak();
										break;
									case 'l'://<= <ifcbl:> <ifcble:> <ifcb<:> <ifcb<=:> || <ifcblen:>
									case 'L':
									case '<':
										if (check_if_num(a) != L"" && check_if_num(w) != L"") {
											if (qqC.substr(5, 3) == L"len") { //length <ifcblen:> <ifcbleng:>
												unsigned int len = stoi(a);
												if (qqC[8] == '!' || qqC[8] == 'n') { if (w.length() != len) { multi.setBreak(); break; } }
												else if (qqC.substr(8, 2) == L"ge" || qqC.substr(8, 2) == L"g=") { if (w.length() >= len) { multi.setBreak(); break; } }
												else if (qqC.substr(8) == L"g") { if (w.length() > len) { multi.setBreak(); break; } }
												else if (qqC.substr(8, 2) == L"le" || qqC.substr(8, 2) == L"<e" || qqC.substr(8, 2) == L"<=") { if (w.length() <= len) { multi.setBreak(); break; } }
												else if (qqC[8] == 'l' || qqC[8] == '<') { if (w.length() < len) { multi.setBreak(); break; } }
												else if (qqC[8] == ':' || qqC[8] == 'e' || qqC[8] == '=') { if (w.length() == len) multi.setBreak(); break; }//==
												else { a = L""; break; }
											}
											if (qqC[6] == 'e' || qqC[6] == '=') { if (a == L"0" && w == L"0" || stod(w) <= stod(a)) { multi.setBreak(); break; } } //ifcble <=
											if (stod(w) < stod(a)) multi.setBreak();
										}
										break;
									case 'g'://>= <ifcbg:> <ifcbge:> <ifcbg=:>
										if (check_if_num(a) != L"" && check_if_num(w) != L"") {
											if (qqC[6] == 'e' || qqC[6] == '=') { if (a == L"0" && w == L"0" || stod(w) >= stod(a)) { multi.setBreak(); break; } } //ifcbge >=/g=
											if (stod(w) > stod(a)) multi.setBreak();
										}
										break;
									default: a = L""; //f();
									}
								};
							
								wstring tar = a;
								for (; size < length; ++size) { //cout << size << " ifcb:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); clearAllKeys(); prints(1); return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); multi.setBreak(); break; }
									OpenClipboard(0);
									hcb = GetClipboardData(CF_UNICODETEXT);
									if (hcb != nullptr) {
										c = static_cast<wchar_t*>(GlobalLock(hcb));
										if (c != nullptr) {
											w = c;
											if (qqC[5] == 'f') sifcb();
											else {
												if (!BackslashLogicals) { tar = regex_replace(tar, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
												if (tar.find(L"|") != string::npos || tar.find(L"&") != string::npos) {// | &
													wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
													for (size_t j = 0; j < a.length(); ++j) {
														ta += a[j]; //build ta
														if (tar[j] == '|' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || tar[j] == '&' && (!BackslashLogicals ? 1 : tar[j - 1] == '\\') || j == a.length() - 1) {
															t = a.substr(ta.length());
															if (t > L"") q = a.substr(j, 1);
															a = t > L"" ? ta.substr(0, ta.length() - 1 - BackslashLogicals) : ta; if (BackslashLogicals && t == L"") { q = ta[0]; a = ta.substr(1); }
															if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
															if (a[0] == ' ' && a != L" ") { a = a.substr(1); } if (a.length() > 1 && a[a.length() - 1] == ' ') a = a.substr(0, a.length() - 1); //!\0
															sifcb(); //wcout << a << "\t(" << multi.br << ")\t" << b << endl;
															if (!multi.br) {
																if (q == L"&") {
																	sand = 0;
																	if (t.find(L"|") != string::npos) sand = 1; else break;
																}
																if (q == L"|") {
																	sor = 0;
																	if (t.find(L"&") != string::npos) sor = 1;
																	if (t.find(L"&") != string::npos && t.find(L"|") == string::npos) sor = 1;
																}
															}
															if (q == L"&" && multi.br) sand = 1;
															if (q == L"|" && multi.br) { sor = 1; break; } //wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
															multi.br = 0; a = t; j = -1; ta.clear();
															if (!BackslashLogicals) { tar = regex_replace(a, wregex(L"\\\\\\|"), L"  "); tar = regex_replace(tar, wregex(L"\\\\\\&"), L"  "); }
														}
													}
													if (sor && sand) multi.br = 1;
												}
												else {
													if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
													sifcb();
												}
											}
											tar = a = app;
											if (multi.getBreak()) break;
										}
									}
									CloseClipboard();
									if (!multi.getBreak()) {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC[0] == io[0] || linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}
							
								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								CloseClipboard();
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {//F:
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos) 
												linkC = linkC.substr(linkC.find(L" ") + 1);//<t-<ifcb:a,*,ms, T: F:>
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<ifcb:a,x,ms,<link->..., <ifcb:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(L" ") != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue | Use < in the false slot for continue | <ifcb:a,x,ms,link: <>
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {//T:
									linkC = linkC.substr(0, linkC.find(L" "));
									if (linkC == L"<") { if (multiStrand) { i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); tail = multi.getTail(); i += qqC.find(L">"); } else { rei(); } break; } //true, continue | Use < in the true slot for continue |  <ifcb:a,x,ms,< link:>
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (testqqb(L"<if+")) {//<if+:> | stop if <+>
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); } if (check_if_num(qp) == L"" || qp[0] == 0) { conn(); break; }
								bool b = 0; int q = stoi(qp);
								wstring l = L""; if (qp.find(L" ") != string::npos) l = qp.substr(qp.find(L" ") + 1);//<if+:# true:>
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
										tail = l[0] == '<' ? l + L">" + qq.substr(qq.find(L">") + 1) : L"<" + l + L">";//<if+:# true->
										if (speed > 0) sleep = 0; re = L" "; i = -1; break;
									}
									i = tail.size(); break;
								}
								else rei();
							}
							else if (testqqb(L"<if") && qq[3] != ':' && qq[3] != '-' && qq[3] != io[0]) {//<ift:> | (t)ime, (h)our, (m)in, (s)ec  =|e, !|n, <|l, <=|le, g(>), g=|ge, <ift+:5> | <ifs:+5,> (MultiStrand:1)
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								if (qp == L"") { conn(); break; }
								wstring a = qp; a = a.substr(0, a.find(L","));
								wstring app = a, x = L"1", ms = L"0", linkC; link = L"";//<ift:a,x,ms,link>
								if (qp.find(L",") != string::npos) {
									if (a == L"") { printq(); break; }
									ms = L"333";
									x = qp.substr(qp.find(L",") + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(L",") != string::npos) {
										ms = x.substr(x.find(L",") + 1); if (ms == L"") { printq(); break; }
										if (ms.find(L",") != string::npos) {
											link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(L","));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << a << " " << x << " " << ms << " " << link << endl;
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) wcout << "Fail: " << OutTab << OutTab << qqC.substr(0, qqC.find(L">") + 1) << endl; };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								chrono::system_clock::time_point np;
								time_t n{};
								char b[26]{};
								wstring w{}, h{}, m{}, s{};
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };
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
									np = chrono::system_clock::now();
									n = chrono::system_clock::to_time_t(np);
									ctime_s(b, sizeof(b), &n);
									w = L""; for (auto i = 0; i < 26; ++i) {
										if (b[i] == '\n') break;
										if (b[i] == ':') continue;
										w += b[i];
									}
									w = w.substr(w.rfind(L" ") - 6, 6);
									if (multiStrand) { a = multi.getApp(); qqC = multi.getQQ(); }
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
									if (multiStrand) multi.setApp(a);
									int ans = 0, aa = stoi(a);
									switch (qqC[4]) {
									case '+': //+= hr, min, sec <ifm+:5>
										multi.setMS(L"0");
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
									if (ans == 1) multi.setBreak();
								};
							
								for (; size < length; ++size) { //cout << size << " iftime:" << a << " *" << x << " " << ms << "ms" << endl;
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); clearAllKeys(); prints(1); return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); multi.setBreak(); break; }

									if (multiStrand) { a = multi.getApp(); qqC = multi.getQQ(); }
									if (a.find(L"|") != string::npos || a.find(L"&") != string::npos) {//<t-<ifh:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {// | &
											ta += a[j];
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - (a.find(L"\\") != string::npos && BackslashLogicals)) : ta;
												if (a[0] == ' ') a = a.substr(1);
												sif();
												if (!multi.br) {
													if (q == L"&") { sand = 0; 
														if (t.find(L"|") != string::npos) sand = 1; else break;
													}
													if (q == L"|") { sor = 0;
													if (t.find(L"&") != string::npos) { sor = 1; }
													if (t.find(L"&") != string::npos && t.find(L"|") == string::npos) { sor = 1; }
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
									if (multi.getBreak()) break;
									else {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC[0] == io[0] || linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}
								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<iftime:a,x,ms,<link->..., <iftime:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(L" ") != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {
									linkC = linkC.substr(0, linkC.find(L" "));
									if (linkC == L"<") { if (multiStrand) { i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); tail = multi.getTail(); i += qqC.find(L">"); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else conn();
							break;
						case 'n':
							if (qqb(L"<ins")) kbPress(L"<ins", VK_INSERT);
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
							if (qqb(L"<lc")) kbPress(L"<lc", VK_F7);//left click
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
							if (qqb(L"<left")) kbPress(L"<left", VK_LEFT);
							else conn();
							break;
						case 's':
							if (qqb(L"<ls")) { kbPress(L"<ls", VK_F7); }//hscroll+
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
								tail = multiLineDelim[0] + qq.substr(qq.find(L">") + 1, qq.length());
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
							if (qqb(L"<mc")) kbPress(L"<mc", VK_F7);//middle click
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
							if (qqb(L"<menu")) kbPress(L"<menu", VK_APPS);
							else conn();
							break;
						default:
							conn();
						}
						break;
					case'p':
						switch (qq[2]) {
						case 'a':
							if (qqb(L"<pause")) { kbPress(L"<pause", VK_PAUSE); GetAsyncKeyState(VK_PAUSE); }
							else conn();
							break;
						case 's':
							if (qqb(L"<ps")) kbPress(L"<ps", VK_SNAPSHOT);
							else conn();
							break;
						case 'u':
							if (qqb(L"<pu")) kbPress(L"<pu", VK_PRIOR);//pgup
							else conn();
							break;
						case 'd':
							if (qqb(L"<pd")) kbPress(L"<pd", VK_NEXT);//pgdn
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
								if (qq[1] == 'R') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(L"", qp, L"", 0); }
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
							if (qqb(L"<rc")) kbPress(L"<rc", VK_F7); else conn();
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
							if (qqb(L"<right")) kbPress(L"<right", VK_RIGHT); else conn();
							break;
						case 's':
							if (qqb(L"<rs")) { kbPress(L"<rs", VK_F7); } else conn();//hscroll-
							break;
						case 'G':
						case 'g':
							if (testqqb(L"<RGB~:") || testqqb(L"<RGB:") || testqqb(L"<rgb:")) { //<rgb:r g b,x,ms,link>
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								if (qp == L"") { conn(); break; }
								wstring r, g, b, a = qp, x = L"1", ms = L"0", linkC; link = L"";
								r = qp.substr(0, qp.find(L" "));
								b = qp.substr(qp.find(L" ") + 1);
								g = b.substr(0, b.find(L" "));
								b = b.substr(b.find(L" ") + 1);
								if (b.find(L",") != string::npos) {//x,ms
									ms = L"333";
									x = b; b = b.substr(0, b.find(L","));
									x = x.substr(x.find(L",") + 1); if (x[0] == ' ') x = x.substr(1); if (x == L"") { x = L"1"; link = L":"; }
									if (x.find(L",") != string::npos) {
										ms = x.substr(x.find(L",") + 1); if (ms == L"") { printq(); break; }
										if (ms.find(L",") != string::npos) {
											link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); } if (link == L"") link = L"<";
											ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
										}
										x = x.substr(0, x.find(L","));
									}
									if (check_if_num(x) == L"") { printq(); break; }
								}//cout << r << " " << g << " " << b << " " << x << " " << ms << " " << link << endl;
								a = r + L" " + g + L" " + b;
								wstring app = a;
								if (check_if_num(r) == L"" || check_if_num(g) == L"" || b.find(L" ") == string::npos && check_if_num(b) == L"") { printq(); break; }
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) wcout << "Fail: " << OutTab << OutTab << qqC.substr(0, qqC.find(L">") + 1) << endl; };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setRGBr(r); multi.setRGBg(g); multi.setRGBb(b); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };

								auto sifrgb = [&multi, &r, &g, &b, &qqC]() {
									POINT pt; COLORREF color; HDC hDC;
									hDC = GetDC(NULL); GetCursorPos(&pt);
									if (multiStrand) { r = multi.getRGBr(); g = multi.getRGBg(); b = multi.getRGBb(); }
									if (qqC[1] == 'R') { if (multiStrand) { qxc = multi.getQxc(); qyc = multi.getQyc(); } color = GetPixel(hDC, qxc * RgbScaleLayout, qyc * RgbScaleLayout); } else { color = GetPixel(hDC, pt.x * RgbScaleLayout, pt.y * RgbScaleLayout); }
									//color = qqC[1] == 'R' ? GetPixel(hDC, qxc * RgbScaleLayout, qyc * RgbScaleLayout) : GetPixel(hDC, pt.x * RgbScaleLayout, pt.y * RgbScaleLayout);//<RGB> get xy from <XY:> or current
									ReleaseDC(NULL, hDC);
									if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b.substr(0, b.find(L" ")))) {
										multi.setBreak();
										if (multiStrand) qq = multi.getQQ();
										if (qq[4] == '~') {
											POINT pt; GetCursorPos(&pt); qxcc = pt.x; qycc = pt.y;//<RGB~:>
											if (multiStrand) { qxc = multi.getQxc(); qyc = multi.getQyc(); } SetCursorPos(qxc, qyc);
										}
									}
								};

								for (; size < length; ++size) {
									if (!NoEscapeOrPause) {
										GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } clearAllKeys(); prints(1); return; }//stop
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
											if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; speed = multi.speed_; }
										}
									}
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); break; }
									
									
									if (multiStrand) a = multi.getApp();
									if (a.find(L"|") != string::npos || a.find(L"&") != string::npos) {//<t-<rgb:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - (a.find(L"\\") != string::npos && BackslashLogicals)) : ta; 
												if (a[0] == ' ') a = a.substr(a.find_first_not_of(' '));
												r = a.substr(0, a.find(L" "));
												b = a.substr(a.find(L" ") + 1);
												g = b.substr(0, b.find(L" "));
												b = b.substr(b.find(L" ") + 1);
												if (multiStrand) { multi.setRGBr(r); multi.setRGBg(g); multi.setRGBb(b); }
												if (b.find(L" ") != string::npos) {//X Y
													wstring sx = b.substr(b.find(L" ") + 1);
													wstring sy = sx.substr(sx.find(L" ") + 1);
													if (sx != L"" && sy != L"") {
														sx = sx.substr(0, sx.find(L" "));
														b = b.substr(0, b.find(L" ")); if (multiStrand) { multi.setRGBb(b); }
														if (qqC[1] == 'R') {
															qxc = stoi(sx); qyc = stoi(sy);	if (multiStrand) { multi.setQxc(qxc); multi.setQyc(qyc); }
														}
														else SetCursorPos(stoi(sx), stoi(sy));
													}
												}
												sifrgb();
												if (!multi.br) {
													if (q == L"&") {
														sand = 0;
														if (t.find(L"|") != string::npos) sand = 1; else break;
													}
													if (q == L"|") {
														sor = 0;
														if (t.find(L"&") != string::npos) { sor = 1; }
														if (t.find(L"&") != string::npos && t.find(L"|") == string::npos) { sor = 1; }
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
										if (b.find(L" ") != string::npos) {//X Y
											auto sx = b.substr(b.find(L" ") + 1);
											auto sy = sx.substr(sx.find(L" ") + 1);
											sx = sx.substr(0, sx.find(L" "));
											if (qqC[1] == 'R') {
												qxc = stoi(sx); qyc = stoi(sy);	if (multiStrand) { multi.setQxc(qxc); multi.setQyc(qyc); }
											}
											else SetCursorPos(stoi(sx), stoi(sy));
										}
										sifrgb();
									}
									if (multi.getBreak()) break;
									else {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC[0] == io[0] || linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}

								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == io[0] || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
										else if (linkC.find(L" ") != string::npos && linkC[linkC.length() - 1] == '<') { if (multiStrand) { rei(multi); } else { i = 0; rei(); } break; }//false, continue
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {
									linkC = linkC.substr(0, linkC.find(L" "));
									if (linkC == L"<") { if (multiStrand) { i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); tail = multi.getTail(); i += qqC.find(L">"); } else { rei(); } break; } //true, continue
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; break;
								}
								if (!multiStrand) rei();
								break;
							}
							else if (qqb(L"<rgb>")) {//print r g b
								tail = getRGB(1) + qq.substr(qq.find(L">") + 1, qq.length());
								i = -1;
								if (speed > 0) sleep = 0;
								re = L" ";
							}
							else if (testqqb(L"<RGB") || testqqb(L"<rgb") && qq[4] != '~') {// << RGBXY to cb | <RGB> <RGB|> <RGB&> | -xy if lowercase 
								if (qq[5] == ':' && qq[6] == '>') {rei(); conn(); }
								if (testqqb(L"<rgbxy>") || qqb(L"<rgbxy:>")) { getRGB(1, 1); rei(); if (qq[6] == ':') { wstring x = cbGet(); x = x.substr(x.find(':') + 1); x = x.substr(0, x.length() - Loop_Insert_Text.length()); cbSet(x); } break; }//rshift + esc + r
								wstring w = qq.substr(5, qq.find(L">") - 5);
								if (check_if_num(w) == L"") w = L"0";
								size_t n = stoi(w);
								wstring rgb = getRGB(1), rgbc = rgb, h = qq.substr(0, 4) + L":" +  rgb + (qq[1] == 'r' ? L"" : L" " + qx + L" " + qy), hq;
								if (showStrand) wcout << h;
								for (size_t i = 0; i < (n * 10); ++i) {// <rgb|3>
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { GetAsyncKeyState(VK_ESCAPE); break; }
									Sleep(95);
									rgb = getRGB(1);
									if (rgb == rgbc) continue;
									hq = L" " + qq.substr(4, 1) + L" " + rgb + (qq[1] == 'r' ? L"" : L" " + qx + L" " + qy); h += hq;// & |
									if (showStrand) wcout << hq;
									rgbc = rgb;
								}
								if (showStrand) cout << '>' << '\n';
								h += Loop_Insert ? Loop_Insert_Text : L">";
								cbSet(h);
								rei();
							}
							else conn();
							break;
						case 'e':
							if (testqqb(L"<replace:")) {
								if (cbGet() > L"") {
									if (qp.find(L"\\,") != wstring::npos) {// \,
										wstring t = qp.substr(qp.find_last_of(L"\\") + 2);
										if (t.find(L",") != string::npos) {
											qx = qp.substr(0, qp.find_last_of(L"\\") + t.find(L",") + 2);
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
								if (qq[1] == 'S') { showOutsMsg(L"", OutsTemplate, L"", 1); showOutsMsg(L"", qp, L"", 0); }
								qp = regex_replace(qp, wregex(L"/"), L"\\");
								wifstream f(qp); if (!f) { showOutsMsg(L"\nSettings \"", qp, L"\" not found!", 0); return; }
								settings = editorSe = qp;
								se = settings.substr(settings.find_last_of('\\') + 1) + L" - ";
								loadSe();
								rei();
								break;
							}
							else if (qqb(L"<se>")) { printSe(); rei(); }
							else conn();
							break;
						case 'h':
							if (qqb(L"<shift>")) { kbHold(VK_LSHIFT); rei(); }
							else if (qqb(L"<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
							else if (qqb(L"<shift")) kbPress(L"<shift", VK_LSHIFT);
							else conn();
							break;
						case 'l':
							if (testqqb(L"<sleep:")) if (check_if_num(qp) != L"") { multi.t = tail; Sleep(stoi(qp)); if (multiStrand) rei(multi); else rei(); } else printq();
							else if (qqb(L"<sl")) { kbPress(L"<sl", VK_F7); }//scroll left
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
										if (n == L"0") { i += qq.find(L">"); return; }
									}
									speed = stoi(n); rei(); sleep = 0;
								}
								else printq();
							}
							else if (qqb(L"<space")) kbPress(L"<space", VK_SPACE);
							else conn();
							break;
						case 'd':
							if (qqb(L"<sd")) { kbPress(L"<sd", VK_F7); }//scroll down
							else conn();
							break;
						case 'r':
							if (qqb(L"<sr")) { kbPress(L"<sr", VK_F7); }//scroll right
							else conn();
							break;
						case 'u':
							if (qqb(L"<su")) { kbPress(L"<su", VK_F7); }//scroll up
							else conn();
							break;
						default:
							conn();
						}
						break;
					case't':
						if (qqb(L"<tab")) kbPress(L"<tab", VK_TAB);
						else if (qqb(L"<time>") || qqb(L"<time:>")) {
							wstring w{}; getTime(w);
							if (qq[5] == '>') w = w.substr(w.rfind(L" ") - 8, 8);
							tail = w + qq.substr(qq.find(L">") + 1, qq.length());
							i = -1;
							if (speed > 0) sleep = 0;
							re = L" ";
						}
						else conn();
						break;
					case'u':
						if (qqb(L"<upper>")) { wstring s = L"", c = L""; c = cbGet(); for (size_t x = 0; x < c.length(); x++) { s += toupper(c[x]); } cbSet(s); rei(); }
						else if (qqb(L"<up")) kbPress(L"<up", VK_UP);
						else conn();
						break;
					case 'v':
						if (qqb(L"<v>")) { toggle_visibility(); rei(); }
						else conn();
						break;
					case'w':
						if (qqb(L"<win>")) { kbHold(VK_LWIN); rei(); }
						else if (qqb(L"<win->")) { kbRelease(VK_LWIN); rei(); }
						else if (qqb(L"<win")) kbPress(L"<win", VK_LWIN);
						else conn();
						break;
					case'X':
					case'x':
						switch (qq[2]) {
						case 'y':
							if (testqqb(L"<xy:")) {
								if ((multiLine) && qx[0] == '\n' || qx[0] == '\t' || qy[0] == '\n' || qy[0] == '\t') {
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
								tail = to_wstring(pt.x) + L" " + to_wstring(pt.y) + qq.substr(qq.find(L">") + 1, qq.length());
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
					if (multiLine) { if (ctail[0] == '\t' || ctail[0] == '\n') { sleep = 0; continue; } }
					if ((ctail[0] >= 33 && ctail[0] <= 38) || (ctail[0] >= 40 && ctail[0] <= 43) || ctail[0] == 58 || (ctail[0] >= 62 && ctail[0] <= 90) || ctail[0] == 94 || ctail[0] == 95 || (ctail[0] >= 123 && ctail[0] <= 126)) { shft = true; }//if !"#$%& ()*+ : > ?&AZ ^ _ {|}~
					if (shft) kbHold(VK_LSHIFT);
					kb(ctail[0]);
					if (shft) shftRelease();
					GetAsyncKeyState(VkKeyScanW(ctail[0])); GetAsyncKeyState(ctail[0]);//clear
				}
			}
			if (strand > L"" || re > L"") {
				if (re == L"" || re == L" " || strandLengthMode) { re = L""; reTail = tail = codes; }
				clearAllKeys();
				if (!noClearStrand && strand == sv) strand.clear();
			}
			if (speed > 0) speed = 0;
			break;
		}
	}
	f.close();
	if (!noClearStrand) { if (strand > L"" && close_ctrl_mode && strand[0] == '<') { if (strand.substr(strand.length() - 1) != L">") return; codes = tail = reTail = strand.substr(1, strand.length() - 2); } }//dbless repeat
	if (ManualRepeat) { if (reTail.substr(0, 8) != L"<repeat>") pre = reTail; }
}

void printCtrls() {
	wcout << L"Interface\n? + ESC\t\t\tdnaspider.exe\nESC\t\t\tStop\nX + ESC\t\t\tExit (Or press: CTRL + C or CTRL + BREAK)\nF11\t\t\tFullscreen\nH + ESC\t\t\tToggle visibility\nRIGHT_CTRL\t\tToggle < (se.txt CtrlKey: 163 | Or try CtrlKey: 145, RepeatKey: 19, PauseKey: 123, ClearStrandKey: 123 instead / SCRLK, PAUSE, F12)\nLSHIFT + RCTRL\t\t<\nCOMMA + ESC\nRSHIFT + RCTRL\t\tSwitch mode (se.txt RSHIFT+CtrlKey_Toggle...)\nPAUSE_BREAK\t\tReset strand\nLSHIFT + PAUSE_BREAK\tClear strand\nF12\t\t\tPause/Resume (se.txt PauseKey: 123)\nP + ESC\t\t\t<xy:>\nA + ESC\t\t\t<app:>\nR + ESC (SHIFT)\t\t<rgb:> (se.txt RgbScaleLayout: 1.25 | Match with desktop System > Display, Scale & layout, Scale [125%]) | Use LSHIFT for loop, RSHIFT for <rgbxy> copy (3 second delay)\nSCROLL_LOCK\t\tRepeat (se.txt RepeatKey: 145)\nEQUAL + ESC\nHold LCTRL, Press RCTRL, Release LCTRL\n\nAPI\nA-Z 0-9 etc.\t\tdnaspider will press key/run\n\t\t\t<test->A-Z 0-9 etc.\n<connect_line>\t\tUse <line_name:> or <line_name->\n\t\t\t<test1-><test-> (se.txt CloseCtrlMode: 1)\n<db>\t\t\tPrint database to console\n\t\t\t<test-><db>\n<se>\t\t\tLoad settings\n\t\t\t<test-><se>\n\t\t\tOr press LCTRL + S inside \"se.txt - Notepad\" (se.txt Editor: Notepad)\n<v>\t\t\tToggle visibility\n\t\t\t<test-><v>\n<,>\t\t\t150ms sleep (se.txt CommaSleep: 150)\n\t\t\t<test->1<,>1\n<,1>\t\t\tSleep for\n<ms:1>\t\t\t<test->1<,1000>1\n<sleep:1>\n<xy:0,0>\t\tMove pointer to x y (P + ESC to get)\n\t\t\tUse . for current\n\t\t\t<test-><xy:.,0><rc>\n<x:>\n<y:>\n<xy>\t\t\tPrint x y\n<rp>\t\t\tReturn pointer (xy)\n\t\t\t<test-><xy:0,0><,1000><rp>\n<XY:><XY>\t\tSet, return pointer\n\t\t\t<test-><XY:0,0><,1000><XY>\n<~><~~>\t\t\tLong set, return pointer\n\t\t\t<test-><~><connect:><~~>\n<~m>\t\t\tAuto lock/unlock (se.txt MultiStrand: 1)\n<~~m>\t\t\tEnable MultiStrand\n<lc>\t\t\tLEFT, RIGHT, MIDDLE -> CLICK, HOLD, RELEASE\n<rc>\n<mc>\n<lh>\n<rh>\n<mh>\n<lr>\n<rr>\n<mr>\n<sl>\t\t\tSCROLL LEFT, UP, RIGHT, DOWN\n<su>\n<sr>\n<sd>\n<ctrl>\t\t\tHold key\n<shift>\n<alt>\n<win>\n<ctrl->\t\t\tRelease key\n<shift->\n<alt->\n<win->\n<up>\t\t\tPress key\n<right>\n<down>\n<left>\n<delete>\n<esc>\n<bs>\n<home>\n<end>\n<space>\n<tab>\n<enter>\n<pause>\n<caps>\n<win1>\t\t\tPress *\n\t\t\t<test><bs*4>1\n<menu>\t\t\tMENU key\n<ins>\t\t\tINSERT\n<ps>\t\t\tPRINT_SCREEN\n<pu><pd>\t\tPAGE_UP, PAGE_DOWN\n<f1>\t\t\tF1 (F1-F12) \n<yesno:>\t\tVerify message\n\t\t\t<test-><yesno:Continue?>1\n<beep>\t\t\tAlert sound\n<a:>\t\t\tALT codes\n\t\t\t<test-><a:9201>\n<speed:>\t\tOutput\n\t\t\t<test->1<speed:1000>11\n<+:>\t\t\tCalc. (No print, se.txt Assume: 1)\n<-:>\t\t\t<test-><+:1><+:-1>\n<*:>\n</:>\n<%:>\n<+>\t\t\tTotal\n\t\t\t<test-><+><*:7>\n<down+>\t\t\tVariable press * <+>\n\t\t\t<test:><speed:1000><+:1><tab+><test:>\n<bs++>\t\t\tVariable press. Auto increment <+>\n\t\t\t<test-><speed:1000><esc++><<:\\+\\n><test->\n<if+:>\t\t\tStop if <+> (Use \" \" for true)\n\t\t\t<test-><+:1><<:\\+:) \\n><if+g:3 true:><test->\n\t\t\t<true:>1\n<'>\t\t\tPrint to console\n<''>\t\t\tIgnore rest of line\n<'''>\t\t\tIgnore rest of db \n\t\t\t<test->1<'bs>1<''test>0\n\t\t\t<'''block>\n<app:>\t\t\tContinue if set app to foreground\n\t\t\tSignature: <app:TITLE|TITLE,*,ms,true- else->\n\t\t\t<test-><app:Calculator>1+1<enter>\n\t\t\tDefault: <app:Calculator,1,333,else:>1\n\t\t\tUse | for OR: TITLE|TITLE\n\t\t\tUse \" \" to expand connect option: true- false-\n\t\t\tUse < to reconnect: <true- <false-\n\t\t\tUse < in true or false slot for continue\n\t\t\t<test-><app:Calculator,1,150,true- false->\n\t\t\t<true->1+1<enter>\n\t\t\t<false-><win>r<win-><app:Run,>calculator<enter><app:Calculator,><true->\n\t\t\tSignature for loop: (Use - : or ,)\n\t\t\t<app:T,*,ms,->\n\t\t\t<app:T,*,ms,:>\n\t\t\t<app:T,>\n\t\t\tCheck, continue: <app:T,*,ms,>\n<App:>\t\t\tContinue if App in foreground\n\t\t\t<test-><App:Calculator,>1+1<enter>\n<app>\t\t\tTITLE to cb\n\t\t\t<test-><speed:1><alt><esc><alt-><app><app:*db.txt - Notepad><ctrl>v<ctrl->\n<rgb:>\t\t\tContinue if rgb in xy location (R + ESC to get)\n\t\t\tSignature <rgb:RED GREEN BLUE X Y,*,ms,true: false:>\n\t\t\tUse & for AND, | for OR\n\t\t\t<test-><rgb:255 255 255 0 0>1\n<RGB:>\t\t\tContinue if RGB in XY location\n\t\t\t<test-><RGB:255 255 255 0 0>1\n<RGB~:>\t\t\tIf RGB is true, go to its XY (RSHIFT + R + ESC)\n\t\t\t<test-><RGB~:0 0 0 0 0 | 1 1 1 0 0,><rc>\n<rgb>\t\t\tPrint rgb\n\t\t\t<test-><shift>,<shift->rgb:<rgb>>\n<RGB&>\t\t\tRGBXY to cb (No XY if lowercase)\n<RGB|>\t\t\t<test-><RGB&3> (Generate for 3 sec.)\n<rgbxy>\t\t\tRGBXY to cb (3 second delay. For hoverless rgb)\n<rgbxy:>\n<cb:>\t\t\tSet clipboard (Auto CTRL + V if CAPS)\n\t\t\t<test-><cb:Test>\n<cl>\t\t\tCb length\n<ifxy:>\t\t\tContinue if xy\n<ifcb:>\t\t\tContinue if cb ==\n<ifcb!:>\t\t!=\n<ifcbg:>\t\tg\n<ifcbge:>\t\tg=\n<ifcbl:>\t\t<\n<ifcble:>\t\t<=\n<ifcbf:>\t\tRegex find\n<ifcbF:>\t\tFind\n<ifcbA:1 x>\t\tOffset find x\n<ifcbS:>\t\tStarts with\n<ifcbE:>\t\tEnds with\n<ifcba:0 1 x>\t\tFind substr\n<ifcblen:>\t\tLength\n\t\t\tSignature: <ifcb:#|#,*,ms,t- f->\n\t\t\t<test-><ifcbge:1>1\n<replace:>\t\tRegex replace (cb)\n\t\t\t<test-><replace:T,t><replace:\\r\\n,>\n<upper>\t\t\tUppercase (cb)\n<lower>\n<time:>\t\t\tPrint timestamp\n<time>\n<ift:>\t\t\tContinue if time\n<ifh:>\t\t\tHour\n<ifm:>\t\t\tMinute\n<ifs:>\t\t\tSecond\n\t\t\tOptions: ==, !=, <, <=, g, g=, +\n\t\t\tSignature: <ifh:#,*,ms,t- f->\n\t\t\t<test-><ifh<=:5>1\n<rand:>\t\t\tPrint random #, A-Z, a-z, or A-Za-z\n<Rand>\t\t\t<test-><rand:0,1>\n<rand>\n<Rand:>\n<dna:>\t\t\tTitle\n\t\t\t<dna:new>\n<dna>\t\t\tInit.\n\t\t\t<dna><<:Welcome\\n>\n<<:>\t\t\tCustom message\n\t\t\tOptions: \n\t\t\t\\1-9\tColor\n\t\t\t\\n\tNewline\n\t\t\t\\t\tTab\n\t\t\t\\T\tTime\n\t\t\t\\'\tBlank\n\t\t\t\\g\t\">\"\n\t\t\t\\c\tCb\n\t\t\t\\a\tBeep\n\t\t\t\\+\t<+>\n\t\t\t\\d\tRun <+>\n\t\t\t\\m\t<ml>\n\t\t\t<test-><<:<test-\\g>\n<^>\t\t\tFlip, then toggle settings back after next run (For RSHIFT + RCTRL)\n<^^>\t\t\tFlip (CloseCtrlMode, CtrlScanOnlyMode)\n\t\t\tUse i^o for auto <^^>\n\t\t\tUse > for no bs (i^>o)\n<db:>\t\t\tSwitch (se.txt Database)\n<se:>\t\t\t(se.txt Settings)\n\t\t\t<test-><DB:c:\\dna\\d.txt>\n{}\t\t\tReplacer (se.txt Replacer: 1)\n{'}\t\t\t{'ignore}\n<r:>\t\t\t(se.txt ReplacerDb)\n\t\t\t<test->{'test}<R:C:\\dna\\db.txt>{test:}<cb:{test:}>\n\t\t\ttest:1\n<ml>\t\t\tPrint DbMultiLineDelimiter\n<!>\t\t\tNo clear strand after run\n<!:>\t\t\tSet strand after run\n<!!:>\t\t\tMulti run\n<!!!:>\t\t\tSet repeat; end\n<~esc>\t\t\tse.txt NoEscapeOrPause: 0\n<~~esc>\t\t\tNoEscapeOrPause: 1\n<#:>\t\t\tascii_calc to cb\n\t\t\t<test-><#:x>\n<repeat>\t\t(se.txt ManualRepeat: 1)\n\t\t\t<test-><repeat>\n\n";
}

void printIntro() {
	if (showIntro) {
		printCtrls();
		printSe();
		printDb();
	}
}

void key(wstring k) {
	if (multiblock) return;
	strand.append(k);
	if (strandLengthMode && static_cast<int>(strand.length()) > strandLength && strand[0] != '<') strand = strand.substr(strand.length() - strandLength);
	prints();
	if (close_ctrl_mode && strand.find(L">") != std::string::npos && strand[strand.length() - 1] != '>') { strand.clear(); prints(); return; }
	if (multiStrand) { thread thread(scanDb); thread.detach(); return; } else scanDb();
	if (strand == L"") prints();
}

void repeat() {
	if (multiblock) return;
	kbRelease(reKey);
	if (multiStrand) {
		if (reTail.find(L"<^^>") != string::npos) reTail.replace(reTail.find(L"<^^>"), 4, L"");
		thread thread(out, reTail); thread.detach();
	}
	else out(tail);
}

#pragma endregion

int main() {//cout << "@dnaspider\n\n";
	wcout.imbue(locale()); wcout.clear();
#pragma region initial_startup
	{
		GetAsyncKeyState(VK_ESCAPE); for (i = 0; i <= 1; i++) { if (GetAsyncKeyState(VK_ESCAPE)) break;
			WCHAR t[MAX_PATH]; GetSystemDirectoryW(t, MAX_PATH); wstring c = L""; for (i = 0; ; ++i) { if (t[i] == ':') { c += L":\\dna"; break; } c += t[i]; };//root
			database = c + L"\\db.txt"; settings = c + L"\\se.txt"; replacerDb = database;
			if (CreateDirectoryW(c.c_str(), NULL)) {//L"c:/dna"
				showIntro=1;showOuts=1;cKey=VK_CONTROL;ignore09=0;SlightPauseInBetweenConnects=1;multiStrand=0;showMultiStrand=0;//minimalist se.txt
				wcout << database << " not found.\nPress [1] to auto create.\n\n";
				for (;; Sleep(150)) { if (GetAsyncKeyState(VK_ESCAPE)) { RemoveDirectoryW(c.c_str()); Sleep(150); break; }if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
				showOuts = false; wofstream fd(database); fd << "h-Hello\n<e->Enjoy\n<x:><bs><e->!\n\n Getting Started:\n Press H (strand: h),\n RIGHT_CTRL E (strand: <e), \n LEFT_SHIFT + RIGHT_CTRL X or\n COMMA + ESC X (strand: <x)\n in a text area to run.\n\n Tip:\n Clear strand first by toggling\n RIGHT_CTRL, BACKSPACE, or \n LEFT_SHIFT + PAUSE_BREAK.\n\n Press keys separately\n (RIGHT_CTRL, release RIGHT_CTRL, X).\n\n Each line in db.txt is a slot for strand:API.\n\n API's are placed in front of the first :, -, >, ->, or :> of each line.\n\n<winr:><win>r<win-><app:run, 1, 6, :>\n<d-><app:*db.txt - Notepad | db.txt - Notepad, 1, 1, odb->\n<odb-><winr:>" << database << "<enter>\n<s-><app:*se.txt - Notepad | se.txt - Notepad, 1, 1, <ose->\n<ose-><winr:>" << settings << "<enter>\n<se-><se><''Update setting  ->  (se.txt CloseCtrlMode: 1)>\n< -<><left>\n<  -><-<left>\n<   -><t-\n<lt:><shift>,<shift->\n<al-<lt:>alt><lt:>alt-><left6>\n<ct-<lt:>ctrl><lt:>ctrl-><left7>\n<sh-<lt:>shift><lt:>shift-><left8>\n<wi-><lt:>win><lt:>win-><left6>\n\n RCTRL D: Open db.txt\n RCTRL S: Open se.txt"; fd.close(); wofstream fs(settings); fs << "ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nClearStrandKey: 19\nMultiStrand: 0\nShowMultiStrand: 0\nShowMultiStrandElapsedOnly: 0\nShowOuts: 0\nOutsTemplate: " << OutsTemplate << "\nOutTabs: 1\nSettings: " << settings << "\nDatabase: " << database << "\nDbMultiLineDelimiter: \\n\nReplacer: 0\nReplacerDb: " << replacerDb << "\nCtrlKey: 163\nCloseCtrlMode: 0\nRSHIFT+CtrlKey_ToggleCloseCtrlMode: 0\nRSHIFT+CtrlKey_ToggleKeep: 0\nCloseCtrlSpacer: 120\nCtrlScanOnlyMode: 0\nRSHIFT+CtrlKey_ToggleCtrlScanOnlyMode: 0\nStrandLengthMode: 0\nStrandLength: 3\nRepeatKey: 145\nPauseKey: 123\nAutoBs_RepeatKey: 0\nRgbScaleLayout: 1.00\nFrequency: 150\nIgnore_0-9: 0\nKb_Key_0: 0\nKb_Key_1: 1\nKb_Key_2: 2\nKb_Key_3: 3\nKb_Key_4: 4\nKb_Key_5: 5\nKb_Key_6: 6\nKb_Key_7: 7\nKb_Key_8: 8\nKb_Key_9: 9\nIgnore_A-Z: 0\nKb_Key_A: a\nKb_Key_B: b\nKb_Key_C: c\nKb_Key_D: d\nKb_Key_E: e\nKb_Key_F: f\nKb_Key_G: g\nKb_Key_H: h\nKb_Key_I: i\nKb_Key_J: j\nKb_Key_K: k\nKb_Key_L: l\nKb_Key_M: m\nKb_Key_N: n\nKb_Key_O: o\nKb_Key_P: p\nKb_Key_Q: q\nKb_Key_R: r\nKb_Key_S: s\nKb_Key_T: t\nKb_Key_U: u\nKb_Key_V: v\nKb_Key_W: w\nKb_Key_X: x\nKb_Key_Y: y\nKb_Key_Z: z\nIgnore_Arrows: 1\nKb_Key_Left: L\nKb_Key_Up: U\nKb_Key_Right: R\nKb_Key_Down: D\nIgnore_Backslash: 1\nKb_Key_Backslash: \\\nIgnore_Caps: 1\nKb_Key_Caps: P\nIgnore_Comma: 1\nKb_Key_Comma: ,\nIgnore_Delete: 1\nKb_Key_Delete: ?\nIgnore_End: 1\nKb_Key_End: ?\nIgnore_Enter: 1\nKb_Key_Enter: E\nIgnore_Equal: 1\nIgnore_Esc: 1\nKb_Key_Esc: ~\nIgnore_F1-F12: 0\nKb_Key_F1: !\nKb_Key_F2: @\nKb_Key_F3: #\nKb_Key_F4: $\nKb_Key_F5: %\nKb_Key_F6: ^\nKb_Key_F7: &\nKb_Key_F8: *\nKb_Key_F9: (\nKb_Key_F10: )\nKb_Key_F11: _\nKb_Key_F12: +\nIgnore_Forwardslash: 1\nKb_Key_Forwardslash: /\nIgnore_GraveAccent: 1\nKb_Key_Grave_Accent: `\nIgnore_Print_Screen: 1\nKb_Key_Print_Screen: ?\nIgnore_Home: 1\nKb_Key_Home: ?\nIgnore_Insert: 1\nKb_Key_Insert: ?\nIgnore_LAlt: 1\nKb_Key_Left_Alt: A\nIgnore_LBracket: 1\nKb_Key_Left_Bracket: [\nIgnore_LCtrl: 1\nKb_Key_Left_Ctrl: C\nIgnore_LShift: 1\nKb_Key_Left_Shift: S\nIgnore_Menu: 1\nKb_Key_Menu: ?\nIgnore_Minus: 1\nKb_Key_Minus: -\nIgnore_NumPad: 1\nKb_Key_Numpad_0: Z\nKb_Key_Numpad_1: Q\nKb_Key_Numpad_2: V\nKb_Key_Numpad_3: W\nKb_Key_Numpad_4: X\nKb_Key_Numpad_5: Y\nKb_Key_Numpad_6: B\nKb_Key_Numpad_7: F\nKb_Key_Numpad_8: G\nKb_Key_Numpad_9: I\nKb_Key_Numlock: N\nKb_Key_Numpad_Divide: J\nKb_Key_Numpad_Multiply: K\nKb_Key_Numpad_Minus: {\nKb_Key_Numpad_Add: }\nKb_Key_Numpad_Period: \"\nKb_Key_Numpad_Enter: :\nIgnore_PgDn: 1\nKb_Key_PgDn: ?\nIgnore_PgUp: 1\nKb_Key_PgUp: ?\nIgnore_Period: 1\nKb_Key_Period: .\nIgnore_Quote: 1\nKb_Key_Quote: '\nIgnore_RAlt: 1\nKb_Key_Right_Alt: M\nIgnore_RBracket: 1\nKb_Key_Right_Bracket: ]\nIgnore_RCtrl: 1\nKb_Key_Right_Ctrl: O\nIgnore_RShift: 1\nKb_Key_Right_Shift: H\nIgnore_Semicolon: 1\nKb_Key_Semicolon: ;\nIgnore_Space: 0\nKb_Key_Space:  \nIgnore_Tab: 1\nKb_Key_Tab: T\nStartHidden: 0\nSlightPauseInBetweenConnects: 1\nAutoBs_EscH: 1\nAutoBs_EscComma: 1\nAutoBs_EscEqual: 1\nKb_Key_Equal: =\nCommaSleep: 150\nBackslashLogicals: 0\nSeHotReload_CtrlS: 1\nSeDbClearStrand_CtrlS: 1\nExit_EscX: 1\nAssume: 0\nUnicode: 1\nEditor: " << editor << "\nEditor1: " << editor1 << "\nEditorSe: " << editorSe << "\nEditorDb: " << editorDb << "\nR+ESC_A+ESC_Loop_Insert: 0\nLoop_Insert_Text: " << Loop_Insert_Text << "\nNoEscapeOrPause: 0\nio: " << io << "\nio_Auto_BS: " << io_Auto_BS << "\nManualRepeat: " << ManualRepeat; fs.close(); out(L"<win>r<win-><app:run, 3, 60, :>notepad " + settings + L"<enter><ms:1500><win>r<win-><app:run, 3, 60, :>notepad " + database + L"<enter>"); re = L""; tail = L""; strand.clear();
			}
		}
	}
	loadSe();
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	printIntro(); strand = L"<dna>"; scanDb(); strand.clear();//run @ startup
#pragma endregion
	for (;; Sleep(frequency)) {
		if (SeHotReload_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (se + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (se + editor1).c_str()) == GetForegroundWindow() || FindWindowW(0, (editorSe).c_str()) == GetForegroundWindow())) { HWND np = FindWindowW(0, (se + editor).c_str()), vsc = FindWindowW(0, (se + editor1).c_str()), vscS = FindWindowW(0, (editorSe).c_str()); HWND HotReload = GetForegroundWindow(); if (np == HotReload || vsc == HotReload || vscS == HotReload) { bool b = qScanOnly || ignore09; loadSe(); if ((!b && qScanOnly || ignore09) || (b && !qScanOnly || !ignore09)) clearAllKeys(); else GetAsyncKeyState(83); if (SeDbClearStrand_CtrlS) { strand.clear(); if (showStrand) { prints(); } continue; } else if (!ignoreAZ) key(L"s"); continue; } }//lctrl+s hot reload
		if (SeDbClearStrand_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (db + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (db + editor1).c_str()) == GetForegroundWindow() || FindWindowW(0, (editorDb).c_str()) == GetForegroundWindow())) { GetAsyncKeyState(83); strand.clear(); if (showStrand) { prints(); } continue; }//clear
		if (GetAsyncKeyState(VK_BACK)) {
			strand = strand.substr(0, strand.length() - 1);
			prints(); continue;
		}
		if (GetAsyncKeyState(cKey)) {//toggle <
			GetAsyncKeyState(VK_LCONTROL); if (GetAsyncKeyState(VK_LCONTROL) && cKey == 163) { while (GetAsyncKeyState(VK_LCONTROL) != 0) {
					Sleep(frequency/3);//cout << (GetAsyncKeyState(VK_LCONTROL)) << endl;
				} repeat(); continue; }
			GetAsyncKeyState(VK_LSHIFT); if (GetAsyncKeyState(VK_LSHIFT) && cKey != VK_LSHIFT) { clearAllKeys(); strand = L"<"; prints(); continue; }
			GetAsyncKeyState(VK_RSHIFT); if (GetAsyncKeyState(VK_RSHIFT) && cKey != VK_RSHIFT) { kbRelease(VK_RSHIFT); if (ToggleCloseCtrl) { toggledCC = 1; close_ctrl_mode = !close_ctrl_mode; clearAllKeys(); strand = close_ctrl_mode ? L"" : L"<"; } if (ToggleCtrlScanOnly) { toggledCSO = 1; qScanOnly = !qScanOnly; if (!ToggleCloseCtrl) { clearAllKeys(); } strand = L""; } prints(); continue; }
			while (GetAsyncKeyState(cKey) != 0) { 
				GetAsyncKeyState(VK_RETURN); if (GetAsyncKeyState(VK_RETURN)) break;
				Sleep(frequency / 3);
			}
			if (GetAsyncKeyState(VK_RETURN) && cKey != VK_RETURN) { kbRelease(cKey); GetAsyncKeyState(cKey); strand.clear(); prints(); continue; } //ctrl + ~ clear
			if (strand[0] == '<') {
				if (close_ctrl_mode) {//<x>	
					if (strand.find(L">") != std::string::npos) strand.clear();
					else {
						if (strand.length() > 1) {
							if (multiStrand) {
								i = 0; thread thread(key, L">"); Sleep(CloseCtrlSpacer); thread.detach();
								if (!noClearStrand) { strand.clear(); } noClearStrand = 0;
							} else {
								key(L">");
								if (strand > L"") { strand.clear(); prints(); }
							}
							continue;
						}
						else strand.clear();
					}
				}
				else if (!noClearStrand) { strand.clear(); } noClearStrand = 0;
			}
			else if (close_ctrl_mode && strand.length() > 0 && strand.find(L">") == std::string::npos) {//x>
				strand.append(L">"); scanDb();
				if (strand > L"") { prints(); if (!noClearStrand) { strand.clear(); } noClearStrand = 0; }
			}//reg
			else {
				if (close_ctrl_mode && strand.length() > 0) strand.clear();
				else { clearAllKeys(); strand = L"<"; }
			} 
			prints(); Sleep(1); continue;
		}
		if (GetAsyncKeyState(reKey)) { //repeat - scroll_lock
			if (AutoBs_RepeatKey) kb(VK_BACK);
			repeat();
			continue;
		}
		if (GetAsyncKeyState(ClearStrandKey)) { //pause
			if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); strand.clear(); if (ignoreEsc) kb(VK_ESCAPE); prints(); continue; }
			if (strand[0] == '<') strand = L"<"; else strand.clear();
			continue; 
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			GetAsyncKeyState(80); if (GetAsyncKeyState(80)) {//esc + p: <xy:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				re = L"<shift>,<shift->xy:";
				out(re); continue;
			}
			GetAsyncKeyState(82); if (GetAsyncKeyState(82)) {//esc + r: <rgb:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK); GetAsyncKeyState(VK_RSHIFT);
				if (GetAsyncKeyState(VK_LSHIFT)) {//lshift + esc + r
					out(L"<shift>,<shift->rgb: " + getRGB() + L" " + qx + L" " + qy + (Loop_Insert ? Loop_Insert_Text : L">")); continue;
				}
				else if (GetAsyncKeyState(VK_RSHIFT)) {//rshift + esc + r
					getRGB(1, 1); continue;
				}
				else getRGB(); out(tail); continue;
			}
			GetAsyncKeyState(65); if (GetAsyncKeyState(65)) {//esc + a: <app:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				wstring s = tail; getApp(); tail = s; continue;
			}
			GetAsyncKeyState(VK_OEM_PLUS); if (GetAsyncKeyState(VK_OEM_PLUS)) {//esc + plus: repeat
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				if (EscEqualAutoBs) { kb(VK_BACK); GetAsyncKeyState(VK_BACK); }
				repeat(); continue;
			}
			GetAsyncKeyState(0xBC); if (GetAsyncKeyState(0xBC)) {//esc + ,
				if (EscCommaAutoBs) { kb(VK_BACK);  GetAsyncKeyState(VK_BACK); }
				if (strand[0] == '<' && close_ctrl_mode && strand.length() >= 1) {
					if (strand == L"<") continue;
					strand.append(L">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
					if (multiStrand) { thread thread(scanDb); Sleep(CloseCtrlSpacer); thread.detach(); strand.clear(); continue; } else scanDb();
					if (strand > L"") strand.clear();
					if (strand == L"") prints();
					continue;
				}
				else { 
					if (strand[0] == '<') { strand.clear(); prints(); continue; }
					if (strand[0] != '<' && close_ctrl_mode && strand.length() > 0) {
						strand.append(L">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
						if (multiStrand) { thread thread(scanDb); Sleep(CloseCtrlSpacer); thread.detach(); strand.clear(); continue; } else scanDb();
						if (strand > L"") strand.clear();
						if (strand == L"") prints();
						continue;
					}
					clearAllKeys(); strand = L"<"; prints(); continue;
				}
			}
			GetAsyncKeyState(0x58); if (GetAsyncKeyState(0x58)) { if (enableEscX) return 0; } //esc + x
			GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) {//esc + h
				if (EscHAutoBs) { kb(VK_BACK); } GetAsyncKeyState(VK_ESCAPE);
				toggle_visibility(); 
				if (showStrand && !qScanOnly) showOutsMsg(L"", OutsTemplate, strand + L"\n", 1);
				continue; 
			}
			GetAsyncKeyState(VK_OEM_2); if (GetAsyncKeyState(VK_OEM_2)) { printCtrls(); continue; } //? + esc
			if (!ignoreEsc) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key(Kb_Key_Esc); }
			continue;
		}
		if (qScanOnly && strand[0] != '<') continue;
#pragma region input_strand
		if (!ignoreAZ) {
			if (GetAsyncKeyState(0x41)) { key(Kb_Key_A); continue; }
			if (GetAsyncKeyState(0x42)) { key(Kb_Key_B); continue; }
			if (GetAsyncKeyState(0x43)) { key(Kb_Key_C); continue; }
			if (GetAsyncKeyState(0x44)) { key(Kb_Key_D); continue; }
			if (GetAsyncKeyState(0x45)) { key(Kb_Key_E); continue; }
			if (GetAsyncKeyState(0x46)) { key(Kb_Key_F); continue; }
			if (GetAsyncKeyState(0x47)) { key(Kb_Key_G); continue; }
			if (GetAsyncKeyState(0x48)) { key(Kb_Key_H); continue; }
			if (GetAsyncKeyState(0x49)) { key(Kb_Key_I); continue; }
			if (GetAsyncKeyState(0x4A)) { key(Kb_Key_J); continue; }
			if (GetAsyncKeyState(0x4B)) { key(Kb_Key_K); continue; }
			if (GetAsyncKeyState(0x4C)) { key(Kb_Key_L); continue; }
			if (GetAsyncKeyState(0x4D)) { key(Kb_Key_M); continue; }
			if (GetAsyncKeyState(0x4E)) { key(Kb_Key_N); continue; }
			if (GetAsyncKeyState(0x4F)) { key(Kb_Key_O); continue; }
			if (GetAsyncKeyState(0x50)) { key(Kb_Key_P); continue; }
			if (GetAsyncKeyState(0x51)) { key(Kb_Key_Q); continue; }
			if (GetAsyncKeyState(0x52)) { key(Kb_Key_R); continue; }
			if (GetAsyncKeyState(0x53)) { key(Kb_Key_S); continue; }
			if (GetAsyncKeyState(0x54)) { key(Kb_Key_T); continue; }
			if (GetAsyncKeyState(0x55)) { key(Kb_Key_U); continue; }
			if (GetAsyncKeyState(0x56)) { key(Kb_Key_V); continue; }
			if (GetAsyncKeyState(0x57)) { key(Kb_Key_W); continue; }
			if (GetAsyncKeyState(0x58)) { key(Kb_Key_X); continue; }
			if (GetAsyncKeyState(0x59)) { key(Kb_Key_Y); continue; }
			if (GetAsyncKeyState(0x5A)) { key(Kb_Key_Z); continue; }
		}
		if (!ignore09) {
			if (GetAsyncKeyState(0x30)) { key(Kb_Key_0); continue; }
			if (GetAsyncKeyState(0x31)) { key(Kb_Key_1); continue; }
			if (GetAsyncKeyState(0x32)) { key(Kb_Key_2); continue; }
			if (GetAsyncKeyState(0x33)) { key(Kb_Key_3); continue; }
			if (GetAsyncKeyState(0x34)) { key(Kb_Key_4); continue; }
			if (GetAsyncKeyState(0x35)) { key(Kb_Key_5); continue; }
			if (GetAsyncKeyState(0x36)) { key(Kb_Key_6); continue; }
			if (GetAsyncKeyState(0x37)) { key(Kb_Key_7); continue; }
			if (GetAsyncKeyState(0x38)) { key(Kb_Key_8); continue; }
			if (GetAsyncKeyState(0x39)) { key(Kb_Key_9); continue; }
		}
		if (!ignoreF1s) {
			if (GetAsyncKeyState(0x70)) { key(Kb_Key_F1); continue; }
			if (GetAsyncKeyState(0x71)) { key(Kb_Key_F2); continue; }
			if (GetAsyncKeyState(0x72)) { key(Kb_Key_F3); continue; }
			if (GetAsyncKeyState(0x73)) { key(Kb_Key_F4); continue; }
			if (GetAsyncKeyState(0x74)) { key(Kb_Key_F5); continue; }
			if (GetAsyncKeyState(0x75)) { key(Kb_Key_F6); continue; }
			if (GetAsyncKeyState(0x76)) { key(Kb_Key_F7); continue; }
			if (GetAsyncKeyState(0x77)) { key(Kb_Key_F8); continue; }
			if (GetAsyncKeyState(0x78)) { key(Kb_Key_F9); continue; }
			if (GetAsyncKeyState(0x79)) { key(Kb_Key_F10); continue; }
			if (GetAsyncKeyState(0x7A)) { key(Kb_Key_F11); continue; }
			if (GetAsyncKeyState(0x7B)) { key(Kb_Key_F12); continue; }
		}
		if (!ignoreArrows) {
			if (GetAsyncKeyState(VK_LEFT)) { key(Kb_Key_Left); continue; }
			if (GetAsyncKeyState(VK_UP)) { key(Kb_Key_Up); continue; }
			if (GetAsyncKeyState(VK_RIGHT)) { key(Kb_Key_Right); continue; }
			if (GetAsyncKeyState(VK_DOWN)) { key(Kb_Key_Down); continue; }
		}
		if (!Ignore_Print_Screen && GetAsyncKeyState(VK_SNAPSHOT)) { key(Kb_Key_Print_Screen); continue; }
		if (!ignoreSpace && GetAsyncKeyState(VK_SPACE)) { key(Kb_Key_Space); continue; }
		if (!ignoreTab && GetAsyncKeyState(VK_TAB)) { key(Kb_Key_Tab); continue; }
		if (!ignoreLShift && GetAsyncKeyState(VK_LSHIFT)) { key(Kb_Key_Left_Shift); continue; }
		if (!ignoreRShift && GetAsyncKeyState(VK_RSHIFT)) { key(Kb_Key_Right_Shift); continue; }
		if (!ignoreRAlt && GetAsyncKeyState(VK_LMENU)) { key(Kb_Key_Left_Alt); continue; }
		if (!ignoreRAlt && GetAsyncKeyState(VK_RMENU)) { key(Kb_Key_Right_Alt); continue; }
		if (!ignoreLCtrl && GetAsyncKeyState(VK_LCONTROL)) { key(Kb_Key_Left_Ctrl); continue; }
		if (!ignoreRCtrl && GetAsyncKeyState(VK_RCONTROL)) { key(Kb_Key_Right_Ctrl); continue; }
		if (!ignoreEnter && GetAsyncKeyState(VK_RETURN)) { key(Kb_Key_Enter); continue; }
		if (!ignoreCaps && GetAsyncKeyState(VK_CAPITAL)) { key(Kb_Key_Caps); continue; }
		if (!ignoreGraveAccent && GetAsyncKeyState(VK_OEM_3)) { key(Kb_Key_Grave_Accent); continue; }
		if (!ignoreMinus && GetAsyncKeyState(VK_OEM_MINUS)) { key(Kb_Key_Minus); continue; }
		if (!ignoreEqual && GetAsyncKeyState(VK_OEM_PLUS)) { key(Kb_Key_Equal); continue; }
		if (!ignoreLBracket && GetAsyncKeyState(VK_OEM_4)) { key(Kb_Key_Left_Bracket); continue; }
		if (!ignoreRBracket && GetAsyncKeyState(VK_OEM_6)) { key(Kb_Key_Right_Bracket); continue; }
		if (!ignoreBackslash && GetAsyncKeyState(VK_OEM_5)) { key(Kb_Key_Backslash); continue; }
		if (!ignoreSemicolon && GetAsyncKeyState(VK_OEM_1)) { key(Kb_Key_Semicolon); continue; }
		if (!ignoreQuote && GetAsyncKeyState(VK_OEM_7)) { key(Kb_Key_Quote); continue; }
		if (!ignoreComma && GetAsyncKeyState(VK_OEM_COMMA)) { key(Kb_Key_Comma); continue; }
		if (!ignorePeriod && GetAsyncKeyState(VK_OEM_PERIOD)) { key(Kb_Key_Period); continue; }
		if (!ignoreForwardslash && GetAsyncKeyState(VK_OEM_2)) { key(Kb_Key_Forwardslash); continue; }
		if (!ignoreMenuKey) if (GetAsyncKeyState(VK_APPS)) { key(Kb_Key_Menu); continue; }
		if (!Ignore_Insert && GetAsyncKeyState(VK_INSERT)) { key(Kb_Key_Insert); continue; }
		if (!Ignore_Delete && GetAsyncKeyState(VK_DELETE)) { key(Kb_Key_Delete); continue; }
		if (!Ignore_Home && GetAsyncKeyState(VK_HOME)) { key(Kb_Key_Home); continue; }
		if (!Ignore_End && GetAsyncKeyState(VK_END)) { key(Kb_Key_End); continue; }
		if (!Ignore_PgUp && GetAsyncKeyState(VK_PRIOR)) { key(Kb_Key_PgUp); continue; }
		if (!Ignore_PgDn && GetAsyncKeyState(VK_NEXT)) { key(Kb_Key_PgDn); continue; }
		if (!ignoreNumPad) {
			if (GetAsyncKeyState(VK_NUMPAD0)) { key(Kb_Key_Numpad_0); continue; }
			if (GetAsyncKeyState(VK_NUMPAD1)) { key(Kb_Key_Numpad_1); continue; }
			if (GetAsyncKeyState(VK_NUMPAD2)) { key(Kb_Key_Numpad_2); continue; }
			if (GetAsyncKeyState(VK_NUMPAD3)) { key(Kb_Key_Numpad_3); continue; }
			if (GetAsyncKeyState(VK_NUMPAD4)) { key(Kb_Key_Numpad_4); continue; }
			if (GetAsyncKeyState(VK_NUMPAD5)) { key(Kb_Key_Numpad_5); continue; }
			if (GetAsyncKeyState(VK_NUMPAD6)) { key(Kb_Key_Numpad_6); continue; }
			if (GetAsyncKeyState(VK_NUMPAD7)) { key(Kb_Key_Numpad_7); continue; }
			if (GetAsyncKeyState(VK_NUMPAD8)) { key(Kb_Key_Numpad_8); continue; }
			if (GetAsyncKeyState(VK_NUMPAD9)) { key(Kb_Key_Numpad_9); continue; }
			if (GetAsyncKeyState(VK_NUMLOCK)) { key(Kb_Key_Numlock); continue; }
			if (GetAsyncKeyState(VK_DIVIDE)) { key(Kb_Key_Numpad_Divide); continue; }
			if (GetAsyncKeyState(VK_MULTIPLY)) { key(Kb_Key_Numpad_Multiply); continue; }
			if (GetAsyncKeyState(VK_SUBTRACT)) { key(Kb_Key_Numpad_Minus); continue; }
			if (GetAsyncKeyState(VK_ADD)) { key(Kb_Key_Numpad_Add); continue; }
			if (GetAsyncKeyState(VK_DECIMAL)) { key(Kb_Key_Numpad_Period); continue; }
			if (GetAsyncKeyState(VK_RETURN)) { key(Kb_Key_Numpad_Enter); continue; }
		}
#pragma endregion
	}
}