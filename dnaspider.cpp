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
bool noClearStrand = 0; //<!>
bool multiLine = 1; wstring multiLineDelim = L"\n"; //DbMultiLineDelimiter:
bool multiblock = 0; //<~m>
bool replacer = 1; //{}
bool BackslashLogicals = 0; //<ifcb:a\|b\|c><ifcb:a|b|c>
bool ToggleCloseCtrl = 0, toggledCC = 0, ToggleKeep = 1; //RSHIFT+CtrlKey_ToggleCloseCtrlMode:
bool ToggleCtrlScanOnly = 0, toggledCSO = 0, flipd = 0; //RSHIFT+CtrlKey_ToggleCtrlScanOnlyMode:
bool Unicode = 1;
bool OutTabs = 1; wstring OutTab = L"\t";
wstring reTail = L"";
wstring linkr = L"";
short ClearStrandKey = VK_PAUSE;
bool multiStrand = 1, showMultiStrand = 0;
auto RgbScaleLayout = 1.00; //100%
auto CloseCtrlSpacer = 120;
bool relink = 0;
wstring link = L""; //<app|rgb|ifcb,,,<link:>
wstring editor = L"Notepad", editor1 = L"Visual Studio Code", db = L"db.txt - ", se = L"se.txt - ";
bool fail = 0;
bool sleep = 1;
bool esc_pressed = 0;
bool pause_resume = 0;
int CommaSleep = 150;
//bool ignoreMediaKeys = false;
bool enableEscX = true;
int ic = 0; //<+>
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
//bool ignorePrintScreen = false; string PrintScreen_Key = "?";
bool strandLengthMode = false;
int strandLength = 3;
bool qScanOnly = false;
wstring database, settings, replacerDb;
int frequency = 150; //>> ms response -> vk_
int speed = 0; //<< 
short reKey = VK_SCROLL; //repeat
short cKey = VK_RCONTROL; //< 163 
wstring strand = L""; //>> supply
wstring tail = L""; //strand:tail
wstring re = L"";//repeat clone
bool showStrand = true; //cout <<
bool showOuts = false; //cout << 
bool showIntro = false;
bool showSettings = 1;
wstring star_num; //*#
wstring qq; //<x>
wstring qp; //<x:#>
wstring qx, qy; //<xy:#,#>
auto qxc = 0, qyc = 0;//<rp>
auto qxcc = 0, qycc = 0;//cc
bool shft = false;
size_t i = 0;
bool close_ctrl_mode = true; //x>, x:, x- 
bool SlightPauseInBetweenConnects = false;
wstring OutsTemplate = L"\\Gstrand:\\t\\t\\7";
bool EscCommaAutoBs = true;
bool EscEqualAutoBs = true;
wstring codes = L""; //tail re
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
#pragma endregion

#pragma region classo
struct Mainn
{
	Mainn();
	ctp 
		c1, c2;//elapsed
	wstring 
		getStrand(), getStrand(wstring), getTail(wstring),
 		s, s1, &t = tail;//strand
	void 
		setStrand(wstring), setTail();
	~Mainn();
};

Mainn::Mainn()
{
	if (!multiStrand) return;
	if (showMultiStrand) wcout << "thread: " << OutTab << "0x" << hex << GetCurrentThreadId() << dec << endl; clockr(c1);
}

void Mainn::setStrand(wstring c)
{
	s1 = c.substr(0, strand.length());
	linkr = s1;
}

wstring Mainn::getStrand() { return s1; }

wstring Mainn::getStrand(wstring c)
{
	s = c.substr(0, strand.length() + !strandLengthMode);
	if (showMultiStrand) {
		wstring b = L">"; if (s[s.size() - 1] == '>' || s[s.size()] == '>' || strandLengthMode) b = L"";
		wcout << "input: " << OutTab << OutTab << (linkr > L""? linkr + b : s + b) << endl;
	}
	return s;
}

void Mainn::setTail()
{
	t = tail;
	if (showMultiStrand) { wcout << "output: " << OutTab; showOutsMsg(L"", t, L"", 0); }
}

wstring Mainn::getTail(wstring t) { return t; }

Mainn::~Mainn()
{
	if (!multiStrand) return;
	t.clear();
	if (showMultiStrand) {
		clockr(c2); chrono::duration<double, milli> ts = c1 - c2;
		wcout << "~thread: " << OutTab << "0x" << hex << GetCurrentThreadId() << dec << " (" << abs(static_cast<long>(ts.count())) << "ms elapsed)\n";
	}
}

struct Multi
{
	Multi(); Multi(wstring);
	wstring 
		getApp(), getLink(), getMS(), getQQ(), getRGBr(), getRGBg(), getRGBb(), getTail(), getX(),
		r, g, b, a, x, m, l,
		t = tail, q = qq;
	size_t
		getI(),
		get_i = i;
	bool 
		getBreak(),
		br = 0;//break
	void
		setApp(wstring), setBreak(), setI(), setLink(wstring), setMS(wstring), setRGBr(wstring), setRGBg(wstring), setRGBb(wstring), setX(wstring);
	~Multi();
};

Multi::Multi() {}

Multi::Multi(wstring r) {}

void Multi::setApp(wstring app) { a = app; }

wstring Multi::getApp() { return a; }

void Multi::setBreak() { br = 1; }

bool Multi::getBreak() { return br; }

size_t Multi::getI() { return get_i; }

void Multi::setI() { get_i = i; }

void Multi::setLink(wstring li) { l = li; }

wstring Multi::getLink() { return l; }

void Multi::setMS(wstring mil) { m = mil; }

wstring Multi::getMS() { return m; }

wstring Multi::getQQ() { return q; }

void Multi::setRGBr(wstring red) { r = red; }

void Multi::setRGBg(wstring gre) { g = gre; }

void Multi::setRGBb(wstring blu) { b = blu; }

wstring Multi::getRGBr() { return r; }

wstring Multi::getRGBg() { return g; }

wstring Multi::getRGBb() { return b; }

wstring Multi::getTail() { return t; }

void Multi::setX(wstring it) { x = it; }

wstring Multi::getX() { return x; }

Multi::~Multi() {}
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

void prints() { if (showStrand) showOutsMsg(L"", OutsTemplate, strand + L"\n", 1); }

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
	wifstream f(replacerDb); if (!f) { showOutsMsg(L"\n", replacerDb, L" not found!", 0); return q; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	wstring cell, se; GetAsyncKeyState(VK_ESCAPE); while (getline(f, cell, multiLineDelim[0])) {
		if (GetAsyncKeyState(VK_ESCAPE) || cell.substr(0, 4) == L"<'''") break;
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
			if (GetAsyncKeyState(VK_ESCAPE)) break;
			q = q.substr(q.find(L"{") + 1, q.find(L"}", q.find(L"{")) - q.find(L"{") - 1); tq = q;
			if (q > L"") { 
				if (multiLine) { q = regex_replace(q, wregex(L"\n"), L""); q = regex_replace(q, wregex(L"\t"), L""); }
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

void scanDb(); void conn() {//<connect:>
	bool con = false; wstring qqs = qq.substr(0, qq.find(L">") + 1);
	if (qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		if (qqs.substr(qqs.length() - 2, 2) == L":>" || qqs.substr(qqs.length() - 2, 2) == L"->") {
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
				if (relink) tail = x; else tail = x + xx;
				tail = isVar(tail);
				if (SlightPauseInBetweenConnects) Sleep(150);
				f.close(); i = -1;
				if (speed > 0) sleep = 0;
				re = L" ";//codes
				return;
			}
		} f.close(); if (fail) { if (showStrand) { wcout << "Fail: " << OutTab << OutTab << qqs << endl; } fail = 0; i = tail.length(); return; } printq();
	}
	else printq();
}

void kbPress(wstring s, short key) {
	wstring n = s;
	if (qq.find(L">") == std::string::npos) { printq(); return; }
	if (qq[n.length()] == '>') star_num = L"1";
	else {
		if (qq.substr(qq.find(L">") - 1, 1) == L":" || qq.substr(qq.find(L">") - 1, 1) == L"-") { conn(); return; }
		n = qq.substr(n.length(), qq.find(L">") - n.length());
		if (n > L"") {
			if (n[0] == '*') n = n.substr(1, n.length()); //case: <f1*
			else if (n[0] == '+') { if (n[1] == '+') { ++ic; } n = to_wstring(ic); } //<f1+> | <f1++> | Variable press <key<+>>
			n = check_if_num(n);
			if (n == L"") { printq(); return; }
			star_num = n;
			if (!(stoi(n) > 0)) { printq(); return; };
		}
		else { printq(); return; }
	}
	INPUT ip[2]{}; ip[0].type = INPUT_KEYBOARD; ip[0].ki.wVk = key;
	if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_HOME || key == VK_END) ip[0].ki.dwFlags = 1; else ip[0].ki.dwFlags = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = 2;
	for (int j = 0; j < stoi(star_num); ++j) {
		GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
		if (GetAsyncKeyState(VK_PAUSE) && key != VK_PAUSE) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
		if (pause_resume) { --j; Sleep(frequency); continue; }
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

void out(wstring ai) { re = L">" + ai; strand.clear(); scanDb(); re.clear(); }

void calc() {
	if (assume) { i += qq.find(L">"); return; }
	qq = to_wstring(ic) + qq.substr(qq.find(L">") + 1, qq.length());
	i = -1;
	if (speed > 0) sleep = 0;
	re = L" ";
	tail = qq;
}

void loadSe() {
	wifstream f(settings); if (!f) { showOutsMsg(L"\n", settings, L" not found!", 0); return; }
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));//
	wstring cell; while (getline(f, cell)) {
		if (cell[0] == 0 || cell[0] == ' ') continue;
		wstring se = cell.substr(0, cell.find_first_of(L":\t ")); se += ':';
		wstring v = (cell.substr(cell.find_first_of(L":\t ") + 1)); if (v.find_first_not_of(L"\t ") == string::npos) { if (se == L"OutsTemplate:") { OutsTemplate = L""; } continue; } v = v.substr(v.find_first_not_of(L"\t "));
		int x = 0; for (size_t i = 0; i <= se.length(); ++i) x += se[i];
		auto er = [se, v]() { showOutsMsg(L"Error in ", settings, L" [" + se + L" " + v + L"]", 0); };
		switch (x) {
			case 2066://DbMultiLineDelimiter:
				if (v.length() > 0 && v[0] != '\\') {
					multiLine = 1; multiLineDelim = v[0];
				}
				else { multiLine = 0; multiLineDelim = L'\n'; }
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
			case 769://Unicode:
				{ if (v == L"1" || v == L"0") Unicode = stoi(v); else er(); } break;
			case 764://OutTabs:
				{ if (v == L"1" || v == L"0") { OutTabs = stoi(v); OutTab = OutTabs ? L"\t" : L""; } else er(); } break;
			case 1462://ClearStrandKey:
				{ if (check_if_num(v) > L"") ClearStrandKey = stoi(v); else er(); } break;
			case 1056://CommaSleep:
				{ if (check_if_num(v) != L"") CommaSleep = stoi(v); else er(); } break;
			case 673://Editor:
				{ if (v.length() > 0) editor = v.substr(0); else er(); } break;
			case 722://Editor1:
				{ if (v.length() > 0) editor1 = v.substr(0); else er(); } break;
			case 680://Assume:
				{ if (v == L"1" || v == L"0") assume = stoi(v); else er(); } break;
			case 1095://ShowStrand:
				{ if (v == L"1" || v == L"0") showStrand = stoi(v); else er(); } break;
			case 847://Database:
				{ if (v.length() > 0) { database = v.substr(0); database = regex_replace(database, wregex(L"/"), L"\\"); db = database.substr(database.find_last_of('\\') + 1) + L" - "; } else er(); } break;
			case 1038://ReplacerDb:
				{ if (v.length() > 0) { replacerDb = v.substr(0); } else er(); } break;
			case 1313://OutsTemplate:
				OutsTemplate = v.substr(0); break;
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
			case 915://Ignore_0-9:
				{ if (v == L"1" || v == L"0") ignore09 = stoi(v); else er(); } break;
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
				{ if (check_if_num(v) > L"") CloseCtrlSpacer = stoi(v); else er(); } break;
			case 1467://RgbScaleLayout:
				{ if (check_if_num(v) > L"") RgbScaleLayout = stod(v); else er(); } break;
			case 1201://MultiStrand:
				{ if (v == L"1" || v == L"0") multiStrand = stoi(v); else er(); } break;
			case 1618://ShowMultiStrand:
				{ if (v == L"1" || v == L"0") showMultiStrand = stoi(v); else er(); } break;
			case 1098://AutoBs_EscH: //Ignore_F1-F12:
				{	if (v == L"1" || v == L"0") {
						if (se == L"AutoBs_EscH:") EscHAutoBs = stoi(v);
						else if (se == L"Ignore_F1-F12:") ignoreF1s = stoi(v);
					}
					else er();
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
			case 1044://Ignore_Tab:
				{ if (v == L"1" || v == L"0") ignoreTab = stoi(v); else er(); } break;
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
			//case 1657://Ignore_MediaKeys:
		}
	}
	f.close();
 }

void printSe() {
	loadSe();
	if (showSettings) {
		wcout << settings << '\n';  ifstream f(settings); if (f.fail()) { showOutsMsg(L"Copy to ", settings, L"\n", 1); }
		cout << "ShowSettings: " << showSettings << '\n';
		cout << "ShowIntro: " << showIntro << '\n';
		cout << "ShowStrand: " << showStrand << '\n';
		cout << "ClearStrandKey: " << ClearStrandKey << '\n';
		cout << "MultiStrand: " << multiStrand << '\n';
		cout << "ShowMultiStrand: " << showMultiStrand << '\n';
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
		cout << "RgbScaleLayout: " << RgbScaleLayout << '\n';
		cout << "Frequency: " << frequency << '\n';
		cout << "Ignore_0-9: " << ignore09 << '\n';
		cout << "Ignore_A-Z: " << ignoreAZ << '\n';
		cout << "Ignore_Arrows: " << ignoreArrows << '\n';
		cout << "Ignore_Backslash: " << ignoreBackslash << '\n';
		cout << "Ignore_Caps: " << ignoreCaps << '\n';
		cout << "Ignore_Comma: " << ignoreComma << '\n';
		cout << "Ignore_Enter: " << ignoreEnter << '\n';
		cout << "Ignore_Equal: " << ignoreEqual << '\n';
		cout << "Ignore_Esc: " << ignoreEsc << '\n';
		cout << "Ignore_F1-F12: " << ignoreF1s << '\n';
		cout << "Ignore_Forwardslash: " << ignoreForwardslash << '\n';
		cout << "Ignore_GraveAccent: " << ignoreGraveAccent << '\n';
		cout << "Ignore_LAlt: " << ignoreLAlt << '\n';
		cout << "Ignore_LBracket: " << ignoreLBracket << '\n';
		cout << "Ignore_LCtrl: " << ignoreLCtrl << '\n';
		cout << "Ignore_LShift: " << ignoreLShift << '\n';
		cout << "Ignore_Menu: " << ignoreMenuKey << '\n';
		cout << "Ignore_Minus: " << ignoreMinus << '\n';
		cout << "Ignore_NumPad: " << ignoreNumPad << '\n';
		cout << "Ignore_Period: " << ignorePeriod << '\n';
		cout << "Ignore_Quote: " << ignoreQuote << '\n';
		cout << "Ignore_RAlt: " << ignoreRAlt << '\n';
		cout << "Ignore_RBracket: " << ignoreRBracket << '\n';
		cout << "Ignore_RCtrl: " << ignoreRCtrl << '\n';
		cout << "Ignore_RShift: " << ignoreRShift << '\n';
		cout << "Ignore_Semicolon: " << ignoreSemicolon << '\n';
		cout << "Ignore_Space: " << ignoreSpace << '\n';
		cout << "Ignore_Tab: " << ignoreTab << '\n';
		//cout << "Ignore_MediaKeys: " << ignoreMediaKeys << '\n';
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

wstring getRGB(bool b = 0) {
	POINT pt; GetCursorPos(&pt); COLORREF color; HDC hDC;
	hDC = GetDC(NULL);
	if (hDC != NULL) {
		color = GetPixel(hDC, pt.x * RgbScaleLayout, pt.y * RgbScaleLayout);
		ReleaseDC(NULL, hDC);
		if (color != CLR_INVALID) {
			wstring c = to_wstring(GetRValue(color)) + L" " + to_wstring(GetGValue(color)) + L" " + to_wstring(GetBValue(color));
			if (b) { qx = to_wstring(pt.x); qy = to_wstring(pt.y); return c; }
			tail = L"<shift>,<shift->rgb:" + c + L">";
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

void showOutsMsg(wstring s, wstring w, wstring s1 = L"", bool b = 0) {
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	size_t x = 0; bool t = 0;
	if (multiLine) { w = regex_replace(w, wregex(L"\n"), L""); w = regex_replace(w, wregex(L"\t"), L""); }
	auto write = [&x, &t](auto w) { 
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
				{ write(ic); } break; //<+>
			case'a':
				{ write('\a'); } break; //beep
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
				{ write('\\'); }
				break;
			case '\'':
				x = w.length() - 1;
				t = 1;
				break;
			case 'c':
				{ write(cbGet()); }
				break;
			case 'n':
				{ write('\n'); }
				break;
			case 'T':
				{ wstring w{}; getTime(w); write(w); }
				break;
			case 't':
				{ write('\t'); }
				break;
			case 'g':
				{ write('>'); }
				break;
			}
			if (t) continue;
		}
		if (w[x] > 127) { cout << "[?]"; continue; } //ignore > 127
		wcout << w[x];
	}
	wcout << s1;
	if (!b) cout << '\n';
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
	wifstream f(database); if (!f) { showOutsMsg(L"\n", database, L" not found!", 0); return; }
	wstring sv = strand;
	if (Unicode) f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>)); //properties, general, language standard, >c++14 //_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	Mainn mainn; wstring cell; relink = 0; while (getline(f, cell, multiLineDelim[0])) { //cout << cell << endl;
		if (cell[1] == '\'') { if (cell.substr(0, 4) == L"<'''") break; } //ignore db...
		if (re > L"" && strand == L"" || strand > L"" && cell > L"" && (close_ctrl_mode && cell.substr(0, sv.size()) == strand || (!strandLengthMode || sv[0] == '<') && cell.substr(0, sv.size()) == sv.substr(0, sv.size() - 1) + L":" || cell.substr(0, sv.size()) == sv.substr(0, sv.size() - 1) + L"-" || cell.substr(0, sv.size() + 1) == sv.substr(0, sv.size() - 1) + L":>" || cell.substr(0, sv.size() + 1) == sv.substr(0, sv.size() - 1) + L"->") || cell.substr(0, sv.size() + 1) == strand + L">" || cell.substr(0, sv.size() + 1) == strand + L":" || cell.substr(0, sv.size() + 1) == strand + L"-" || (strandLengthMode && cell.substr(0, strandLength) == strand && cell[0] != '<') || close_ctrl_mode && strandLengthMode && strand[0] != '<' && cell.substr(0, sv.size() - 1) == sv.substr(0, sv.size() - 1)) { //found i>o, i:o, i-o, i:>o, i->o || i>o, i:o, i-o || io || io
			if (toggledCC) { toggledCC = 0; if (!ToggleKeep) close_ctrl_mode = !close_ctrl_mode; } if (toggledCSO) { toggledCSO = 0; if (!ToggleKeep) qScanOnly = !qScanOnly; } if (flipd) { flipd = 0; if (ToggleCloseCtrl) { if (close_ctrl_mode && strand[strand.length() - 1] == '>') { strand = strand.substr(0, strand.length() - 1); } close_ctrl_mode = 0; } if (ToggleCtrlScanOnly) qScanOnly = 0; }
			if (multiStrand) { if (re == L"") mainn.setStrand(cell); }
			if (close_ctrl_mode && strand.length() > 0 && strand[strand.length() - 1] == '>') strand = strand.substr(0, strand.length() - 1);
			if (re > L"" && strand == L"") {
				if (link[0] == '<' && cell.substr(0, link.length()) == link) relink = 1;
				cell = re;
				if (re[0] == '>') {
					if (re.substr(0, 20) == L"><shift>,<shift->xy:") { POINT pt; GetCursorPos(&pt); wstring xy = to_wstring(pt.x) + L"," + to_wstring(pt.y); cell = L"><shift>,<shift->xy:" + xy + L">"; re = cell; linkr = L""; if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << L"<xy:" + xy + L">\n"; } }
					else if (re.substr(0, 21) == L"><shift>,<shift->rgb:") { getRGB(); linkr = L""; if (showStrand) { showOutsMsg(L"", OutsTemplate, L"", 1); wcout << "<" << tail.substr(16, tail.length()) << endl; } mainn.t.clear(); }
					else if (re.substr(0, 21) == L"><shift>,<shift->app:") { wstring x = L"><shift>,<shift->app:"; out(L"<alt><esc><alt-><,1>"); x += getAppT(); out(L"<shift><alt><esc><alt-><shift->"); re = x + L">"; }
				}
			}
			tail = re > L"" && strand == L"" ? re : cell.substr(strand.length(), cell.length() - strand.length());
			if (multiStrand) mainn.getStrand(cell);
			tail = isVar(tail); //<r:>
			switch (tail[0]) {//set_tail
			case ':':
				tail = tail.substr(1, tail.length());
				if (tail[0] == '>') tail = tail.substr(1, tail.length());
				codes = tail;
				break;
			case '>':
				tail = tail.substr(1, tail.length());
				codes = strand[0] == '<' ? strand.substr(1, strand.length()) + tail : strand + tail;
				break;
			case '-':
				tail = tail.substr(1, tail.length());
				if (tail[0] == '>') tail = tail.substr(1, tail.length());
				for (size_t t = 0; t < strand.length(); ++t) { if (strand[t] == 60 || ((!ignoreMenuKey) && strand[t] == 63) || (!ignoreArrows) && (strand[t] == 76 || strand[t] == 85 || strand[t] == 82 || strand[t] == 68) || (!ignoreF1s) && (strand[t] == 33 || (strand[t] >= 35 && strand[t] <= 38) || (strand[t] >= 40 && strand[t] <= 43) || strand[t] == 64 || strand[t] == 94 || strand[t] == 95) || (!ignoreEsc && strand[t] == 126) || (!ignoreLShift && strand[t] == 83) || (!ignoreRShift && strand[t] == 72) || (!ignoreLAlt && strand[t] == 65) || (!ignoreRAlt && strand[t] == 77) || (!ignoreLCtrl && strand[t] == 67) || (!ignoreRCtrl && strand[t] == 79) || (!ignoreCaps && strand[t] == 80)) { continue; } kb(VK_BACK); } GetAsyncKeyState(VK_BACK);//exclude non bs: < LURD !@#$%^&*()_+ ~ S H A M C O P
				codes = tail;
				break;
			default:
				codes = cell;
			}
			if (multiStrand) { reTail = tail; mainn.setTail(); }
			if (showOuts && !showMultiStrand) { showOutsMsg(L"found: " + OutTab + OutTab, cell); showOutsMsg(L"tail: " + OutTab + OutTab, tail); }
			if (tail.find(L"<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
			f.close(); fail = 0; esc_pressed = 0;
			Multi multi;
			for (i = 0; i < tail.length(); ++i) {
				if (speed > 0) { if (sleep) { if (multiStrand) { multi.t = tail; multi.get_i = i; multi.q = qq; } Sleep(speed); if (multiStrand) { tail = multi.t; i = multi.get_i; qq = multi.q; } } sleep = 1; }
				GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; multiblock = 0; break; } if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }// int m = MessageBoxA(0, "Resume?", "dnaspider", MB_YESNO); if (m != IDYES) { break; } }
				if (pause_resume) { --i; Sleep(frequency); continue; }
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
							if (qp.find(L",") != string::npos) {
								qx = qp.substr(0, qp.find(L","));//x <xy:#,#>
								qy = qp.substr(qp.find(L",") + 1, qp.find(L">") - qp.find(L",") - 1);//y
							}
							else if (qp.find(L" ") != string::npos) {
								qx = qp.substr(0, qp.find(L" "));//x <xy:# #>
								qy = qp.substr(qp.find(L" ") + 1, qp.find(L">") - qp.find(L" ") - 1);
							}
							else { qx.clear(), qy.clear(); } //wcout << "qp: " << qp  << "\nqx: " << qx << "\nqy: " << qy << endl;
						}
					}
					switch (qq[1]) {
					case '<'://cout
						if (testqqb(L"<<:")) {//cout
							showOutsMsg(L"", qp, L"", 1); rei();
							break;
						}
						else conn();
						break;
					case'!':
						if (qqb(L"<!>")) { noClearStrand = 1; rei(); }
						else conn();
						break;
					case '^':
						if (qqb(L"<^>")) {//Toggle back after run
							flipd = 1; if (ToggleCloseCtrl) close_ctrl_mode = 1; if (ToggleCtrlScanOnly) qScanOnly = 1; rei();
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
							multiStrand = 0; rei();
							multiblock = 1;	wstring t = codes; out(tail.substr(i + 1)); multiblock = 0; reTail = t; return;
						}
						else if (qqb(L"<~~m>")) {//enable
							multiStrand = 1; multiblock = 0; rei();
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
							ic += stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'-':
						if (testqqb(L"<-:")) {//-
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic -= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'*':
						if (testqqb(L"<*:")) {//*
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic *= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'/':
						if (testqqb(L"</:")) {//divide
							if (check_if_num(qp) == L"" || stoi(qp) <= 0) { printq(); continue; }
							ic /= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case'%':
						if (testqqb(L"<%:")) {//%
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic %= stoi(qp);
							calc();
							break;
						}
						else conn();
						break;
					case',':
						if (qqb(L"<,") && qq.at(2) != ':' && qq.at(2) != '-') { //<,#> || <,*
							wstring s = qq.substr(2, qq.find('>') - 2);
							if (s == L"") s = to_wstring(CommaSleep);
							if (s[0] == '*') s = s.substr(1, s.length()); //case: <,*
							s = check_if_num(s);
							if (s == L"") { printq(); break; }
							if (stoi(s) > 0 && s[0] != '+') {
								multi.t = tail;
								if (qq[2] == '*') {
									GetAsyncKeyState(VK_ESCAPE); GetAsyncKeyState(VK_PAUSE); for (int j = 0; j < stoi(s); ++j) {//sleep150ms*?
										if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
										if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
										if (pause_resume) { --j; Sleep(frequency); continue; }
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

								wstring tar = a;
								for (; size < length; ++size) { //cout << size << " app:" << a << " *" << x << " " << ms << "ms" << endl;
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
									if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
									if (pause_resume) { --size; Sleep(frequency); continue; }
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
												a = t > L"" ? ta.substr(0, ta.length() - 1 - BackslashLogicals) : ta; if (BackslashLogicals && t == L"") { q = ta[0]; a = ta.substr(1); } if (multiStrand) { multi.setApp(a); }
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
										a = L" ";
										if (sor && sand) multi.br = 1; //sifapp
									}
									else {
										if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
										sifapp();
									}
									if (multi.getBreak()) break;
									if (a == L"") { conn(); mF = 1; multi.setBreak(); break; }

									if (!multi.getBreak()) {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}

								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)// ..., true: false:>
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {// ..., true: false:>
									linkC = linkC.substr(0, linkC.find(L" "));
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
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
						case 't':
							if (qqb(L"<ctrl>")) { kbHold(VK_CONTROL); rei(); }
							else if (qqb(L"<ctrl->")) { kbRelease(VK_CONTROL); rei(); }
							else if (qqb(L"<ctrl")) kbPress(L"<ctrl", VK_CONTROL);
							else conn();
							break;
						case 'B':
						case 'b':
							if (testqqb(L"<CB:") || testqqb(L"<cb:")) {
								qp = regex_replace(qp, wregex(L"\\\\g"), L">");
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
								database = qp;
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
							if (testqqb(L"<ifcb")) {//Clipboard ==, !=, <, <=, g, g=, (f)ind, (F)ind, (n)ot
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
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
								if (qp.find(L",") != string::npos) {
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
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); return; }//stop
									if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
									if (pause_resume) { --size; Sleep(frequency); continue; }
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); multi.setBreak(); break; }
									OpenClipboard(0);
									hcb = GetClipboardData(CF_UNICODETEXT);
									if (hcb != nullptr) {
										c = static_cast<wchar_t*>(GlobalLock(hcb));
										if (c != nullptr) {
											w = TEXT(c);

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
															a = t > L"" ? ta.substr(0, ta.length() - 1 - BackslashLogicals) : ta; if (BackslashLogicals && t == L"") { q = ta[0]; a = ta.substr(1); } if (multiStrand) { multi.setApp(a); }
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
													a = L" ";
													if (sor && sand) multi.br = 1;
												}
												else {
													if (!BackslashLogicals) { a = regex_replace(a, wregex(L"\\\\\\|"), L"|"); a = regex_replace(a, wregex(L"\\\\\\&"), L"&"); }
													sifcb();
												}
											}

											if (multi.getBreak()) break;

											if (a == L"") { conn(); mF = 1; multi.setBreak(); break; }
										}
									}
									CloseClipboard();
									if (!multi.getBreak()) {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}
							
								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								CloseClipboard();
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {//F:
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos) 
												linkC = linkC.substr(linkC.find(L" ") + 1);//<t-<ifcb:a,*,ms, T: F:>
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<ifcb:a,x,ms,<link->..., <ifcb:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {//T:
									linkC = linkC.substr(0, linkC.find(L" "));
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
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
										if (ic == q) b = 1;
										break;
									case 'n': //!=
									case '!':
										if (ic != q) b = 1;
										break;
									case 'l': //<=
									case 'L':
									case '<':
										if (qq[5] == '=' || qq[5] == 'e') {
											if (qp <= to_wstring(ic)) b = 1;
										} //if+le <=
										else if (ic < q) b = 1;
										break;
									case 'g': //g=
										if (qq[5] == '=' || qq[5] == 'e') {
											if (ic >= q) b = 1;
										} //if+ge >=/g=
										else if (ic > q) b = 1;
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
							else if (testqqb(L"<if") && qq[3] != ':' && qq[3] != '-') {//<ift:> | (t)ime, (h)our, (m)in, (s)ec  =|e, !|n, <|l, <=|le, g(>), g=|ge) | <ifs:+5,>
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
								wstring a = qp; if (a == L"") { conn(); break; }
								a = a.substr(0, a.find(L","));
								wstring x = L"1", ms = L"0", linkC; link = L"";//<app:a,x,ms,link>
								if (qp.find(L",") != string::npos) {
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
										if (a.at(0) == '+') a = a.substr(1);
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
									if (a == L"" || check_if_num(a) == L"") { conn(); mF = 1; multi.setBreak(); }
									if (multiStrand) multi.setApp(a);
									if (noq == 0) multi.setBreak();
									int ans = 0, aa = stoi(a);
									switch (qqC[4]) {
									case '+': //+= hr, min, sec <ifm+:5>
										multi.setMS(L"0");
										{ int t = aa;
										if (qqC.at(3) == 'm' || qqC.at(3) == 'h') t *= 60;
										if (qqC.at(3) == 'h') t *= t;
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
									if (ans == 1 || noq == 0) multi.setBreak();
								};
							
								for (; size < length; ++size) { //cout << size << " iftime:" << a << " *" << x << " " << ms << "ms" << endl;
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } CloseClipboard(); return; }//stop
									if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); multi.setBreak(); break; }
								

									if (multiStrand) { a = multi.getApp(); } if (a.find(L"|") != string::npos || a.find(L"&") != string::npos) {//<t-<ifh:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {// | &
											ta += a[j];
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - (a.find(L"\\") != string::npos && BackslashLogicals)) : ta;
												if (a[0] == ' ') a = a.substr(1); if (multiStrand) { multi.setApp(a); }
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

												//wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
												multi.br = 0;
												a = t; j = -1;
												ta.clear();
											}
										}
										a = L" ";
										if (sor && sand) multi.br = 1;
									}
									else sif();
									if (multi.getBreak()) break;
									if (a == L"") { conn(); mF = 1; multi.setBreak(); break; }

								
									if (!multi.getBreak()) {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}
								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {//fail
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<iftime:a,x,ms,<link->..., <iftime:a,x,ms,link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {
									linkC = linkC.substr(0, linkC.find(L" "));
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
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
								srand((unsigned)time(NULL));
								int r{}; wstring rs;
								char s = (qq[5] + qq[1]);
								switch (s) {
								case -84://':r': <rand:> #
									if (check_if_num(qx) != L"" && check_if_num(qy) != L"" && stoi(qy) > stoi(qx)) {
										r = qx == L"0" ?
											rand() % (stoi(qy) + 1) :
											(rand() % (stoi(qy) + 1 - stoi(qx))) + stoi(qx);
									}
									else r = rand();
									rs = to_wstring(r);
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
								rs = parse(r, rs);
								qq = rs + qq.substr(qq.find(L">") + 1, qq.length());
								i = -1;
								if (speed > 0) sleep = 0;
								re = L" ";
								tail = qq;
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
							if (testqqb(L"<RGB:") || testqqb(L"<rgb:")) { //<rgb:r,g,b,x,ms,link>
								if (multiLine) { qp = regex_replace(qp, wregex(L"\n"), L""); qp = regex_replace(qp, wregex(L"\t"), L""); }
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
								if (check_if_num(r) == L"" || check_if_num(g) == L"" || b.find(L" ") == string::npos && check_if_num(b) == L"") { printq(); break; }
								linkC = link; wstring qqC = qq; bool mF = 0;
								auto f = [qqC, &mF]() { mF = 1; i = tail.length(); if (showStrand) wcout << "Fail: " << OutTab << OutTab << qqC.substr(0, qqC.find(L">") + 1) << endl; };
								Multi multi(tail); if (multiStrand) { multi.setApp(a); multi.setRGBr(r); multi.setRGBg(g); multi.setRGBb(b); multi.setX(x); multi.setMS(ms); multi.setLink(link); }
								if (multiStrand) { x = multi.getX(); } auto size{ 0 }, length{ stoi(x) };
									
								auto sifrgb = [&multi, &r, &g, &b, &qqC]() {
									POINT pt; COLORREF color; HDC hDC;
									hDC = GetDC(NULL); GetCursorPos(&pt);
									if (multiStrand) { r = multi.getRGBr(); g = multi.getRGBg(); b = multi.getRGBb(); }
									color = qqC[1] == 'R' ? GetPixel(hDC, qxc * RgbScaleLayout, qyc * RgbScaleLayout) : GetPixel(hDC, pt.x * RgbScaleLayout, pt.y * RgbScaleLayout);//<RGB> get xy from <XY:> or current
									ReleaseDC(NULL, hDC);
									if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b.substr(0,b.find(L" ")))) {
										multi.setBreak();
									}
								};
									
								for (; size < length; ++size) {
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
									if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE);  kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
									if (pause_resume) { --size; Sleep(frequency); continue; }
									if (size >= length) { if (multiStrand) { tail = multi.getTail(); } f(); break; }
										

									if (multiStrand) { a = multi.getApp(); } if (a.find(L"|") != string::npos || a.find(L"&") != string::npos) {//<t-<rgb:a|a|a,*,ms, T: F:>
										wstring t = L"", ta = L"", q = L""; bool sor = 1, sand = 1;
										for (size_t j = 0; j < a.length(); ++j) {
											ta += a[j]; //build ta
											if (a[j] == '|' || a[j] == '&' || j == a.length() - 1) {
												t = a.substr(ta.length());
												if (t > L"") q = a.substr(j, 1);
												a = t > L"" ? ta.substr(0, ta.length() - 1 - (a.find(L"\\") != string::npos && BackslashLogicals)) : ta; 
												if (a[0] == ' ') a = a.substr(1); if (multiStrand) { multi.setApp(a); }
												r = a.substr(0, a.find(L" "));
												b = a.substr(a.find(L" ") + 1);
												g = b.substr(0, b.find(L" "));
												b = b.substr(b.find(L" ") + 1);
												if (multiStrand) { multi.setRGBr(r); multi.setRGBg(g); multi.setRGBb(b); }
												if (b.find(L" ") != string::npos) {//X Y
													auto sx = b.substr(b.find(L" ") + 1);
													auto sy = sx.substr(sx.find(L" ") + 1);
													sx = sx.substr(0, sx.find(L" "));
													b = b.substr(0, b.find(L" "));
													if (qqC[1] == 'R') {
														qxc = stoi(sx); qyc = stoi(sy);
													}
													else SetCursorPos(stoi(sx), stoi(sy));
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

												//wcout << a << "\t(" << multi.br << ")\t"; if (j != a.length() - 1) wcout << q << endl;
												multi.br = 0;
												a = t; j = -1;
												ta.clear();
											}
										}
										a = L" ";
										if (sor && sand) multi.br = 1;
									}
									else {
										if (b.find(L" ") != string::npos) {//X Y
											auto sx = b.substr(b.find(L" ") + 1);
											auto sy = sx.substr(sx.find(L" ") + 1);
											sx = sx.substr(0, sx.find(L" "));
											if (qqC[1] == 'R') {
												qxc = stoi(sx); qyc = stoi(sy);
											}
											else SetCursorPos(stoi(sx), stoi(sy));
										}
										sifrgb();
									}
									if (multi.getBreak()) break;
									if (a == L"") { conn(); mF = 1; multi.setBreak(); break; }

									if (!multi.getBreak()) {
										if (multiStrand) { ms = multi.getMS(); linkC = multi.getLink(); }
										if (length >= 1) Sleep(stoi(ms));
										if (linkC == L":" || linkC == L"-" && linkC.length() == 1) --size;
									}
								}

								if (multiStrand) {
									i = multi.getI(); qqC = multi.getQQ(); linkC = multi.getLink(); if (!mF) { tail = multi.getTail(); i += qqC.find(L">"); } //rei
								}
								if (size >= length) {
									if (linkC.length() > 0) {
										if (linkC == L"<" || linkC[linkC.length() - 1] == ':' || linkC[linkC.length() - 1] == '-') {
											if (linkC == L"<") { if (!multiStrand) rei(); break; }
											if (linkC.find(L" ") != string::npos)
												linkC = linkC.substr(linkC.find(L" ") + 1);
											if (linkC[0] == '<') relink = 0;
											tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
											if (mainn.getStrand() == linkC || linkr == linkC) relink = 1;
											if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
										}
									}
									f(); break;
								}
								if (linkC.find(L" ") != string::npos) {
									linkC = linkC.substr(0, linkC.find(L" "));
									tail = linkC[0] == '<' ? linkC + L">" + qqC.substr(qqC.find(L">") + 1) : L"<" + linkC + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
									if (linkC[0] == '<') relink = 0;
									if (speed > 0) sleep = 0; re = L" "; i = -1; fail = 1; break;
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
							else if (testqqb(L"<RGB") || testqqb(L"<rgb")) {// << RGBXY to cb | <RGB> <RGB|> <RGB&> | -xy if lowercase 
								wstring w = qq.substr(5, qq.find(L">") - 5);
								if (check_if_num(w) == L"") w = L"0";
								size_t n = stoi(w);
								wstring rgb = getRGB(1), rgbc = rgb, h = qq.substr(0, 4) + L":" +  rgb + (qq[1] == 'r' ? L"" : L" " + qx + L" " + qy), hq;
								wcout << h;
								for (size_t i = 0; i < (n * 10); ++i) {// <rgb|3>
									Sleep(95);
									rgb = getRGB(1);
									if (rgb == rgbc) continue;
									hq = L" " + qq.substr(4, 1) + L" " + rgb + (qq[1] == 'r' ? L"" : L" " + qx + L" " + qy); h += hq;// & |
									wcout << hq;
									rgbc = rgb;
								}
								cout << '>' << '\n';
								h += L">";
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
									qx = regex_replace(qx, wregex(L"\\\\g"), L">");
									qy = regex_replace(qy, wregex(L"\\\\g"), L">");
									wstring c = regex_replace(cbGet(), wregex(qx), qy);
									cbSet(c);
								}
								rei();
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
								settings = qp; 
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
							if (qqb(L"<space")) kbPress(L"<space", VK_SPACE);
							else if (testqqb(L"<speed:")) if (check_if_num(qp) != L"") { speed = stoi(qp); rei(); sleep = 0; } else printq();
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
						if (qqb(L"<up")) kbPress(L"<up", VK_UP);
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
					GetAsyncKeyState(VkKeyScanW(ctail[0])); //clear
				}
			}
			if (strand > L"" || re > L"") {
				if (re == L"" || re == L" " || strandLengthMode) { re = L""; reTail = tail = codes; }
				clearAllKeys();
				if (!noClearStrand) strand.clear();
			}
			if (noClearStrand && !close_ctrl_mode) noClearStrand = 0;
			if (speed > 0) speed = 0;
			break;
		}
	}
	f.close();
	if (strand > L"" && close_ctrl_mode && strand[0] == '<') { reTail = strand.substr(1, strand.length() - 2); tail = reTail; }//dbless repeat
}

void printCtrls() {
	wcout << L"Interface\n? + ESC\t\t\tdnaspider.exe\nESC\t\t\tStop\nX + ESC\t\t\tExit\nCTRL + C\nCTRL + BREAK\nH + ESC\t\t\tToggle visibility\nRIGHT_CTRL\t\tToggle < (se.txt CtrlKey: 163)\nLSHIFT + RCTRL\t\t<\nCOMMA + ESC\nRSHIFT + RCTRL\t\tSwitch mode (se.txt RSHIFT+CtrlKey_Toggle...)\nPAUSE_BREAK\t\tReset strand | Pause/Resume\nLSHIFT + PAUSE_BREAK\tClear strand\nP + ESC\t\t\t<xy:>\nA + ESC\t\t\t<app:>\nR + ESC\t\t\t<rgb:> (se.txt RgbScaleLayout: 1.25 | Set to match desktop scale and layout/make everything bigger [125%])\nSCROLL_LOCK\t\tRepeat\nEQUAL + ESC\n\nAPI\nA-Z 0-9 etc.\t\tdnaspider will press key/run\n\t\t\t<test->A-Z 0-9 etc.\n<connect_line>\t\tUse <line_name:> or <line_name->\n\t\t\t<test1-><test-> (se.txt CloseCtrlMode: 1)\n<db>\t\t\tPrint database to console\n\t\t\t<test-><db>\n<se>\t\t\tLoad settings\n\t\t\t<test-><se>\n\t\t\tOr press LCTRL + S inside \"se.txt - Notepad\" (se.txt Editor: Notepad)\n<v>\t\t\tToggle visibility\n\t\t\t<test-><v>\n<,>\t\t\t150ms sleep (se.txt CommaSleep: 150)\n\t\t\t<test->1<,>1\n<,1>\t\t\tSleep for\n<ms:1>\t\t\t<test->1<,1000>1\n<sleep:1>\n<xy:0,0>\t\tMove pointer to x y (P + ESC to get)\n<x:>\t\t\t<test-><xy:0,0><rc>\n<y:>\n<xy>\t\t\tPrint x y\n<rp>\t\t\tReturn pointer (xy)\n\t\t\t<test-><xy:0,0><,1000><rp>\n<XY:><XY>\t\tSet, return pointer\n\t\t\t<test-><XY:0,0><,1000><XY>\n<~><~~>\t\t\tLong set, return pointer\n\t\t\t<test-><~><connect:><~~>\n<~m><~~m>\t\tDisable, enable MultiStrand (No repeat)\n<lc>\t\t\tLEFT, RIGHT, MIDDLE -> CLICK, HOLD, RELEASE\n<rc>\n<mc>\n<lh>\n<rh>\n<mh>\n<lr>\n<rr>\n<mr>\n<sl>\t\t\tSCROLL LEFT, UP, RIGHT, DOWN\n<su>\n<sr>\n<sd>\n<ctrl>\t\t\tHold key\n<shift>\n<alt>\n<win>\n<ctrl->\t\t\tRelease key\n<shift->\n<alt->\n<win->\n<up>\t\t\tPress key\n<right>\n<down>\n<left>\n<delete>\n<esc>\n<bs>\n<home>\n<end>\n<space>\n<tab>\n<enter>\n<pause>\n<caps>\n<win1>\t\t\tPress *\n\t\t\t<test><bs*4>1\n<menu>\t\t\tMENU key\n<ins>\t\t\tINSERT\n<ps>\t\t\tPRINT_SCREEN\n<pu><pd>\t\tPAGE_UP, PAGE_DOWN\n<f1>\t\t\tF1 (F1-F12) \n<yesno:>\t\tVerify message\n\t\t\t<test-><yesno:Continue?>1\n<beep>\t\t\tAlert sound\n<a:>\t\t\tALT codes\n\t\t\t<test-><a:9201>\n<speed:>\t\tOutput\n\t\t\t<test->1<speed:1000>11\n<+:>\t\t\tCalc. (No print, se.txt Assume: 1)\n<-:>\t\t\t<test-><+:1><+:-1>\n<*:>\n</:>\n<%:>\n<+>\t\t\tTotal\n\t\t\t<test-><+><*:7>\n<down+>\t\t\tVariable press * <+>\n\t\t\t<test:><speed:1000><+:1><tab+><test:>\n<bs++>\t\t\tVariable press. Auto increment <+>\n\t\t\t<test-><speed:1000><esc++><<:\\+\\n><test->\n<if+:>\t\t\tStop if <+>\n\t\t\t<test-><+:1><<:\\+:) \\n><if+g:3><test->\n<'>\t\t\tPrint to console\n<''>\t\t\tIgnore rest of line\n<'''>\t\t\tIgnore rest of db \n\t\t\t<test->1<'bs>1<''test>0\n\t\t\t<'''block>\n<app:>\t\t\tContinue if set app to foreground\n\t\t\tSignature: <app:TITLE|TITLE,*,ms,true- else->\n\t\t\t<test-><app:Calculator>1+1<enter>\n\t\t\tDefault: <app:Calculator,1,333,else:>1\n\t\t\tUse | for OR: TITLE|TITLE\n\t\t\tUse \" \" to expand connect option: true- false-\n\t\t\tUse < to reconnect: <true- <false-\n\t\t\t<test-><app:Calculator,1,150,true- false->\n\t\t\t<true->1+1<enter>\n\t\t\t<false-><win>r<win-><app:Run,>calculator<enter><app:Calculator,><true->\n\t\t\tSignature for loop: (Use - : or ,)\n\t\t\t<app:T,*,ms,->\n\t\t\t<app:T,*,ms,:>\n\t\t\t<app:T,>\n\t\t\tCheck, continue: <app:T,*,ms,>\n<App:>\t\t\tContinue if App in foreground\n\t\t\t<test-><App:Calculator,>1+1<enter>\n<app>\t\t\tTITLE to cb\n\t\t\t<test-><speed:1><alt><esc><alt-><app><app:*db.txt - Notepad><ctrl>v<ctrl->\n<rgb:>\t\t\tContinue if rgb in xy location (R + ESC to get)\n\t\t\tSignature <rgb:RED GREEN BLUE X Y,*,ms,true: false:>\n\t\t\t<test-><xy:0,0><rgb:255 255 255>1\n<RGB:>\t\t\tContinue if RGB in XY location\n\t\t\t<test-><XY:0,0><RGB:255 255 255>1\n<rgb>\t\t\tPrint rgb\n\t\t\t<test-><shift>,<shift->rgb:<rgb>>\n<RGB&>\t\t\tRGBXY to cb (No XY if lowercase)\n<RGB|>\t\t\t<test-><RGB&3>\n<cb:>\t\t\tSet clipboard (Auto CTRL + V if CAPS)\n\t\t\t<test-><cb:Test>\n<ifcb:>\t\t\tContinue if cb ==\n<ifcb!:>\t\t!=\n<ifcbg:>\t\tg\n<ifcbge:>\t\tg=\n<ifcbl:>\t\t<\n<ifcble:>\t\t<=\n<ifcbf:>\t\tRegex find\n<ifcbF:>\t\tFind\n<ifcbA:1 x>\t\tOffset find x\n<ifcbS:>\t\tStarts with\n<ifcbE:>\t\tEnds with\n<ifcba:0 1 x>\t\tFind substr\n<ifcblen:>\t\tLength\n\t\t\tSignature: <ifcb:#|#,*,ms,t- f->\n\t\t\t<test-><ifcbge:1>1\n<replace:>\t\tRegex replace (cb)\n\t\t\t<test-><replace:T,t><replace:\\r\\n,>\n<time:>\t\t\tPrint timestamp\n<time>\n<ift:>\t\t\tContinue if time\n<ifh:>\t\t\tHour\n<ifm:>\t\t\tMinute\n<ifs:>\t\t\tSecond\n\t\t\tOptions: ==, !=, <, <=, g, g=, +\n\t\t\tSignature: <ifh:#,*,ms,t- f->\n\t\t\t<test-><ifh<=:5>1\n<rand:>\t\t\tPrint random #, A-Z, a-z, or A-Za-z\n<Rand>\t\t\t<test-><rand:0,1>\n<rand>\n<Rand:>\n<dna>\t\t\tInit.\n\t\t\t<dna><<:Welcome\\n>\n<<:>\t\t\tCustom message\n\t\t\tOptions: \n\t\t\t\\1-9\tcolor\n\t\t\t\\n\tnewline\n\t\t\t\\t\ttab\n\t\t\t\\T\ttime\n\t\t\t\\'\tblank\n\t\t\t\\g\t\">\"\n\t\t\t\\c\tcb\n\t\t\t\\a\tbeep\n\t\t\t\\+\t<+>\n\t\t\t\\d\tRun <+>\n\t\t\t<test-><<:<test-\\g>\n<^>\t\t\tToggle settings back after next run (For RSHIFT + RCTRL)\n<db:>\t\t\tSwitch db, se, r\n<se:>\t\t\t<test-><DB:c:\\dna\\d.txt>\n<r:>\t\t\t(se.txt ReplacerDb)\n{}\t\t\tReplacer (se.txt Replacer: 1)\n\t\t\t<test-><r:C:\\dna\\db.txt>{test:}<cb:{test:}>\n\t\t\ttest:1\n<ml>\t\t\tPrint DbMultiLineDelimiter\n<!>\t\t\tNo clear strand after run\n\n";
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
	scanDb();
	if (strand == L"") prints();
}

void repeat() {
	if (multiblock) return;
	kbRelease(reKey);
	if (multiStrand) {
		thread thread(out, reTail); thread.detach();
	}
	else out(tail);
}

#pragma endregion

int main() {//cout << "@dnaspider\n\n";
#pragma region initial_startup
	{
		WCHAR t[MAX_PATH]; GetSystemDirectoryW(t, MAX_PATH); wstring c = L""; for (i = 0; ; ++i) { if (t[i] == ':') { c += L":\\dna"; break; } c += t[i]; };//root
		database = c + L"\\db.txt"; settings = c + L"\\se.txt"; replacerDb = database;
		if (CreateDirectoryW(c.c_str(), NULL)) {//L"c:/dna"
			showIntro=1;showOuts=1;cKey=VK_CONTROL;ignore09=0;SlightPauseInBetweenConnects=1;multiStrand=0;showMultiStrand=0;//minimalist se.txt
			wcout << database << " not found.\nPress [1] to auto create.\n\n";
			for (;; Sleep(150)) { if (GetAsyncKeyState(VK_ESCAPE)) { RemoveDirectoryW(c.c_str()); Sleep(150); break; }if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
			showOuts = false; wofstream fd(database); fd << "h-Hello\n<e->Enjoy\n<x:><bs><e->!\n\n Getting Started:\n Press H (strand: h),\n RIGHT_CTRL E (strand: <e), \n LEFT_SHIFT + RIGHT_CTRL X or\n COMMA + ESC X (strand: <x)\n in a text area to run.\n\n Tip:\n Clear strand first by toggling\n RIGHT_CTRL, BACKSPACE, or \n LEFT_SHIFT + PAUSE_BREAK.\n\n Press keys separately\n (RIGHT_CTRL, release RIGHT_CTRL, X).\n\n Each line in db.txt is a slot for strand:API.\n\n API's are placed in front of the first :, -, >, ->, or :> of each line.\n\n<winr:><win>r<win-><app:run, 1, 6, :>\n<d-><app:*db.txt - Notepad | db.txt - Notepad, 1, 1, odb->\n<odb-><winr:>" << database << "<enter>\n<s-><app:*se.txt - Notepad | se.txt - Notepad, 1, 1, <ose->\n<ose-><winr:>" << settings << "<enter>\n<se-><se><''Update setting  ->  (se.txt CloseCtrlMode: 1)>\n< -<><left>\n<  -><-<left>\n<   -><t-\n<lt:><shift>,<shift->\n<al-<lt:>alt><lt:>alt-><left6>\n<ct-<lt:>ctrl><lt:>ctrl-><left7>\n<sh-<lt:>shift><lt:>shift-><left8>\n<wi-><lt:>win><lt:>win-><left6>\n\n RCTRL D: Open db.txt\n RCTRL S: Open se.txt"; fd.close(); wofstream fs(settings); fs << "ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nClearStrandKey: 19\nMultiStrand: 0\nShowMultiStrand: 0\nShowOuts: 0\nOutsTemplate: " << OutsTemplate << "\nOutTabs: 1\nDatabase: " << database << "\nDbMultiLineDelimiter: \\n\nReplacer: 0\nReplacerDb: " << replacerDb << "\nCtrlKey: 163\nCloseCtrlMode: 0\nRSHIFT+CtrlKey_ToggleCloseCtrlMode: 0\nRSHIFT+CtrlKey_ToggleKeep: 0\nCloseCtrlSpacer: 120\nCtrlScanOnlyMode: 0\nRSHIFT+CtrlKey_ToggleCtrlScanOnlyMode: 0\nStrandLengthMode: 0\nStrandLength: 3\nRepeatKey: 145\nAutoBs_RepeatKey: 0\nRgbScaleLayout: 1.00\nFrequency: 150\nIgnore_0-9: 0\nIgnore_A-Z: 0\nIgnore_Arrows: 1\nIgnore_Backslash: 1\nIgnore_Caps: 1\nIgnore_Comma: 1\nIgnore_Enter: 1\nIgnore_Equal: 1\nIgnore_Esc: 1\nIgnore_F1-F12: 0\nIgnore_Forwardslash: 1\nIgnore_GraveAccent: 1\nIgnore_LAlt: 1\nIgnore_LBracket: 1\nIgnore_LCtrl: 1\nIgnore_LShift: 1\nIgnore_Menu: 1\nIgnore_Minus: 1\nIgnore_NumPad: 1\nIgnore_Period: 1\nIgnore_Quote: 1\nIgnore_RAlt: 1\nIgnore_RBracket: 1\nIgnore_RCtrl: 1\nIgnore_RShift: 1\nIgnore_Semicolon: 1\nIgnore_Space: 0\nIgnore_Tab: 1\nStartHidden: 0\nSlightPauseInBetweenConnects: 1\nAutoBs_EscH: 1\nAutoBs_EscComma: 1\nAutoBs_EscEqual: 1\nCommaSleep: 150\nBackslashLogicals: 0\nSeHotReload_CtrlS: 1\nSeDbClearStrand_CtrlS: 1\nExit_EscX: 1\nAssume: 0\nUnicode: 1\nEditor: " << editor << "\nEditor1: " << editor1; fs.close(); out(L"<win>r<win-><app:run, 3, 60, :>" + settings + L"<enter><ms:1500><win>r<win-><app:run, 3, 60, :>" + database + L"<enter>"); re = L""; tail = L""; strand.clear();
		}
	}
	loadSe();
	if (Unicode) SetConsoleOutputCP(CP_UTF8);
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	printIntro(); strand = L"<dna>"; scanDb(); strand.clear();//run @ startup
#pragma endregion
	for (;; Sleep(frequency)) {
		if (SeHotReload_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (se + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (se + editor1).c_str()) == GetForegroundWindow())) { HWND np = FindWindowW(0, (se + editor).c_str()), vsc = FindWindowW(0, (se + editor1).c_str()); HWND HotReload = GetForegroundWindow(); if (np == HotReload || vsc == HotReload) { bool b = qScanOnly || ignore09; loadSe(); if ((!b && qScanOnly || ignore09) || (b && !qScanOnly || !ignore09)) clearAllKeys(); else GetAsyncKeyState(83); if (SeDbClearStrand_CtrlS) { strand.clear(); if (showStrand) { prints(); } continue; } else if (!ignoreAZ) key(L"s"); continue; } }//lctrl+s hot reload
		if (SeDbClearStrand_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (db + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (db + editor1).c_str()) == GetForegroundWindow())) { GetAsyncKeyState(83); strand.clear(); if (showStrand) { prints(); } continue; }//clear
		if (GetAsyncKeyState(VK_BACK)) {
			strand = strand.substr(0, strand.length() - 1);
			prints(); continue;
		}
		if (GetAsyncKeyState(cKey)) {//toggle <
			GetAsyncKeyState(VK_LSHIFT); if (GetAsyncKeyState(VK_LSHIFT) && cKey != VK_LSHIFT) { clearAllKeys(); strand = L"<"; prints(); continue; }
			GetAsyncKeyState(VK_RSHIFT); if (GetAsyncKeyState(VK_RSHIFT) && cKey != VK_RSHIFT) { if (ToggleCloseCtrl) { toggledCC = 1; close_ctrl_mode = !close_ctrl_mode; clearAllKeys(); strand = close_ctrl_mode ? L"" : L"<"; } if (ToggleCtrlScanOnly) { toggledCSO = 1; qScanOnly = !qScanOnly; if (!ToggleCloseCtrl) { clearAllKeys(); } strand = L""; } prints(); Sleep(150); continue; }
			if (strand[0] == '<') {
				if (close_ctrl_mode) {//<x>	
					if (strand.find(L">") != std::string::npos) strand.clear();
					else {
						if (strand.length() > 1) {
							if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(CloseCtrlSpacer); kbRelease(cKey); GetAsyncKeyState(cKey); }
							if (multiStrand) {
								i = 0; thread thread(key, L">"); Sleep(CloseCtrlSpacer); thread.detach(); strand.clear();
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
				strand.append(L">"); if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(CloseCtrlSpacer); kbRelease(cKey); GetAsyncKeyState(cKey); } scanDb();
				if (strand > L"") { prints(); if (!noClearStrand) { strand.clear(); } noClearStrand = 0; }
			}//reg
			else {
				if (close_ctrl_mode && strand.length() > 0) strand.clear();
				else { clearAllKeys(); strand = L"<"; }
			}
			prints(); continue;
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
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				getRGB(); out(tail); continue;
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
			if (!ignoreEsc) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key(L"~"); }
			continue;
		}
		//if (!ignorePrintScreen)if (GetAsyncKeyState(VK_SNAPSHOT)) { key(PrintScreen_Key); continue; }
		if (qScanOnly && strand[0] != '<') continue;
#pragma region input_strand
		if (!ignoreAZ) {
			if (GetAsyncKeyState(0x41)) { key(L"a"); continue; }
			if (GetAsyncKeyState(0x42)) { key(L"b"); continue; }
			if (GetAsyncKeyState(0x43)) { key(L"c"); continue; }
			if (GetAsyncKeyState(0x44)) { key(L"d"); continue; }
			if (GetAsyncKeyState(0x45)) { key(L"e"); continue; }
			if (GetAsyncKeyState(0x46)) { key(L"f"); continue; }
			if (GetAsyncKeyState(0x47)) { key(L"g"); continue; }
			if (GetAsyncKeyState(0x48)) { key(L"h"); continue; }
			if (GetAsyncKeyState(0x49)) { key(L"i"); continue; }
			if (GetAsyncKeyState(0x4A)) { key(L"j"); continue; }
			if (GetAsyncKeyState(0x4B)) { key(L"k"); continue; }
			if (GetAsyncKeyState(0x4C)) { key(L"l"); continue; }
			if (GetAsyncKeyState(0x4D)) { key(L"m"); continue; }
			if (GetAsyncKeyState(0x4E)) { key(L"n"); continue; }
			if (GetAsyncKeyState(0x4F)) { key(L"o"); continue; }
			if (GetAsyncKeyState(0x50)) { key(L"p"); continue; }
			if (GetAsyncKeyState(0x51)) { key(L"q"); continue; }
			if (GetAsyncKeyState(0x52)) { key(L"r"); continue; }
			if (GetAsyncKeyState(0x53)) { key(L"s"); continue; }
			if (GetAsyncKeyState(0x54)) { key(L"t"); continue; }
			if (GetAsyncKeyState(0x55)) { key(L"u"); continue; }
			if (GetAsyncKeyState(0x56)) { key(L"v"); continue; }
			if (GetAsyncKeyState(0x57)) { key(L"w"); continue; }
			if (GetAsyncKeyState(0x58)) { key(L"x"); continue; }
			if (GetAsyncKeyState(0x59)) { key(L"y"); continue; }
			if (GetAsyncKeyState(0x5A)) { key(L"z"); continue; }
		}
		if (!ignore09) {
			if (GetAsyncKeyState(0x30)) { key(L"0"); continue; }
			if (GetAsyncKeyState(0x31)) { key(L"1"); continue; }
			if (GetAsyncKeyState(0x32)) { key(L"2"); continue; }
			if (GetAsyncKeyState(0x33)) { key(L"3"); continue; }
			if (GetAsyncKeyState(0x34)) { key(L"4"); continue; }
			if (GetAsyncKeyState(0x35)) { key(L"5"); continue; }
			if (GetAsyncKeyState(0x36)) { key(L"6"); continue; }
			if (GetAsyncKeyState(0x37)) { key(L"7"); continue; }
			if (GetAsyncKeyState(0x38)) { key(L"8"); continue; }
			if (GetAsyncKeyState(0x39)) { key(L"9"); continue; }
		}
		if (!ignoreF1s) {
			if (GetAsyncKeyState(0x70)) { key(L"!"); continue; } //VK_F1
			if (GetAsyncKeyState(0x71)) { key(L"@"); continue; }
			if (GetAsyncKeyState(0x72)) { key(L"#"); continue; }
			if (GetAsyncKeyState(0x73)) { key(L"$"); continue; }
			if (GetAsyncKeyState(0x74)) { key(L"%"); continue; }
			if (GetAsyncKeyState(0x75)) { key(L"^"); continue; }
			if (GetAsyncKeyState(0x76)) { key(L"&"); continue; }
			if (GetAsyncKeyState(0x77)) { key(L"*"); continue; }
			if (GetAsyncKeyState(0x78)) { key(L"("); continue; }
			if (GetAsyncKeyState(0x79)) { key(L")"); continue; }
			if (GetAsyncKeyState(0x7A)) { key(L"_"); continue; }
			if (GetAsyncKeyState(0x7B)) { key(L"+"); continue; }
		}
		if (!ignoreArrows) {
			if (GetAsyncKeyState(VK_LEFT)) { key(L"L"); continue; }
			if (GetAsyncKeyState(VK_UP)) { key(L"U"); continue; }
			if (GetAsyncKeyState(VK_RIGHT)) { key(L"R"); continue; }
			if (GetAsyncKeyState(VK_DOWN)) { key(L"D"); continue; }
		}
		if (!ignoreSpace && GetAsyncKeyState(VK_SPACE)) { key(L" "); continue; }
		if (!ignoreTab && GetAsyncKeyState(VK_TAB)) { key(L"T"); continue; }
		if (!ignoreLShift && GetAsyncKeyState(VK_LSHIFT)) { key(L"S"); continue; }
		if (!ignoreRShift && GetAsyncKeyState(VK_RSHIFT)) { key(L"H"); continue; }
		if (!ignoreLAlt && GetAsyncKeyState(VK_LMENU)) { key(L"A"); continue; }
		if (!ignoreRAlt && GetAsyncKeyState(VK_RMENU)) { key(L"M"); continue; }
		if (!ignoreLCtrl && GetAsyncKeyState(VK_LCONTROL)) { key(L"C"); continue; }
		if (!ignoreRCtrl && GetAsyncKeyState(VK_RCONTROL)) { key(L"O"); continue; }
		if (!ignoreEnter && GetAsyncKeyState(VK_RETURN)) { key(L"E"); continue; }
		if (!ignoreCaps && GetAsyncKeyState(VK_CAPITAL)) { key(L"P"); continue; }
		if (!ignoreGraveAccent && GetAsyncKeyState(VK_OEM_3)) { key(L"`"); continue; }
		if (!ignoreMinus && GetAsyncKeyState(VK_OEM_MINUS)) { key(L"-"); continue; }
		if (!ignoreEqual && GetAsyncKeyState(VK_OEM_PLUS)) { key(L"="); continue; }
		if (!ignoreLBracket && GetAsyncKeyState(VK_OEM_4)) { key(L"["); continue; }
		if (!ignoreRBracket && GetAsyncKeyState(VK_OEM_6)) { key(L"]"); continue; }
		if (!ignoreBackslash && GetAsyncKeyState(VK_OEM_5)) { key(L"\\"); continue; }
		if (!ignoreSemicolon && GetAsyncKeyState(VK_OEM_1)) { key(L";"); continue; }
		if (!ignoreQuote && GetAsyncKeyState(VK_OEM_7)) { key(L"'"); continue; }
		if (!ignoreComma && GetAsyncKeyState(VK_OEM_COMMA)) { key(L","); continue; }
		if (!ignorePeriod && GetAsyncKeyState(VK_OEM_PERIOD)) { key(L"."); continue; }
		if (!ignoreForwardslash && GetAsyncKeyState(VK_OEM_2)) { key(L"/"); continue; }
		if (!ignoreMenuKey) if (GetAsyncKeyState(VK_APPS)) { key(L"?"); continue; }
		/*if (!ignoreMediaKeys) {
			if (GetAsyncKeyState(VK_INSERT)) { key(L"?"); continue; }
			if (GetAsyncKeyState(VK_DELETE)) { key(L"?"); continue; }
			if (GetAsyncKeyState(VK_HOME)) { key(L"?"); continue; }
			if (GetAsyncKeyState(VK_END)) { key(L"?"); continue; }
			if (GetAsyncKeyState(VK_PRIOR)) { key(L"?"); continue; }
			if (GetAsyncKeyState(VK_NEXT)) { key(L"?"); continue; }
		}
		if (GetAsyncKeyState(JOY_BUTTON1)) { key(L"?"); continue; }*/
		if (!ignoreNumPad) {
			if (GetAsyncKeyState(VK_NUMPAD0)) { key(L"Z"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD1)) { key(L"Q"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD2)) { key(L"V"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD3)) { key(L"W"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD4)) { key(L"X"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD5)) { key(L"Y"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD6)) { key(L"B"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD7)) { key(L"F"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD8)) { key(L"G"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD9)) { key(L"I"); continue; }
			if (GetAsyncKeyState(VK_NUMLOCK)) { key(L"N"); continue; }
			if (GetAsyncKeyState(VK_DIVIDE)) { key(L"J"); continue; }
			if (GetAsyncKeyState(VK_MULTIPLY)) { key(L"K"); continue; }
			if (GetAsyncKeyState(VK_SUBTRACT)) { key(L"{"); continue; }
			if (GetAsyncKeyState(VK_ADD)) { key(L"}"); continue; }
			if (GetAsyncKeyState(VK_DECIMAL)) { key(L"\""); continue; }
			if (GetAsyncKeyState(VK_RETURN)) { key(L":"); continue; }
		}
#pragma endregion
	}
}