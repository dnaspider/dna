// @dnaspider

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>
#include <regex>
#include <codecvt>
using namespace std;

#pragma region global_var
wstring in = L""; //strand
wstring link = L""; //<app|rgb,,,<link:>
wstring editor = L"Notepad", editor1 = L"Visual Studio Code", db = L"";//"db.txt - "
bool fail = 0;
bool sleep = 1;
bool esc_pressed = 0;
bool pause_resume = 0;
bool StockInterfaceControls = false;
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
wstring database = L"C:\\dna\\db.txt";
wstring settings = L"C:\\dna\\se.txt";//R"(C:\dna\se.txt)";
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
bool showSettings = false;
wstring star_num; //*#
wstring qq; //<x>
wstring qp; //<x:#>
wstring qx, qy; //<xy:#,#>
auto qxc = 0;//<rp>
auto qyc = 0;
bool shft = false;
size_t i = 0;
bool close_ctrl_mode = true; //x>, x:, x- 
bool clear_after_stock = true; //<se, <db
bool SlightPauseInBetweenConnects = false;
wstring OutsTemplate = L"strand: ";
bool EscCommaAutoBs = true;
bool EscEqualAutoBs = true;
wstring codes = L""; //tail re
bool EscHAutoBs = true;
bool AutoBs_RepeatKey = 0;
bool SeHotReload_CtrlS=1;
bool SeDbClearStrand_CtrlS=1;
bool assume = 0;
#pragma endregion

#pragma region global_sub
wstring check_if_num(wstring &s) {
	if (assume) return s;
	if (s > L"") {
		for (size_t t = 0; t < s.length(); ++t) {//!0-9
			if (s[0] == ' ') {
				if (s.length() == 1) {
					s = L""; return s;
				}
				s = s.substr(1, s.length()); --t;
				continue;
			}//rem ws
			if (t == 0 && (s[0] == 45 || s[0] == 43) && s.length() != 1) continue; //-+
			if (!(s[t] >= 48 && s[t] <= 57)) { if (showStrand) { wcout << "NAN: " << s << endl; } s = L""; return s; }
		}
	}
	else s = L"";
	return s;
}

void rei() { i += qq.find(L">"); }

void kb(wchar_t b) {//out char
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	if (VkKeyScanW(b) == -1) { ip[0].ki.wScan = b; ip[0].ki.wVk = 0; }
	else { ip[0].ki.wVk = VkKeyScanW(b); }
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

void kb1(wstring b) {//alt codes, emoji
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	ip[0].ki.wScan = (unsigned)stoull(b); ip[0].ki.wVk = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

void kbHold(short key) {
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key; ip.ki.time = 0;
	if (key == VK_LMENU || key == VK_CONTROL) ip.ki.dwFlags = 0; else ip.ki.dwFlags = 1;
	SendInput(1, &ip, sizeof(INPUT));
}

void kbRelease(short key) {
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; SendInput(1, &ip, sizeof(INPUT));
}

void mouseEvent(short key) {
	INPUT ip; ip.type = INPUT_MOUSE; ip.mi.time = 0;
	ip.mi.dwFlags = key;
	if (key == MOUSEEVENTF_HWHEEL) ip.mi.mouseData = 150;//hscrollwheel
	if (key == MOUSEEVENTF_HWHEEL && qq.substr(0,3)==L"<ls") ip.mi.mouseData = -150;
	SendInput(1, &ip, sizeof(ip));
}

void shftRelease() {
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.dwFlags = 2;
	ip.ki.wVk = VK_LSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_RSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	if (shft) { shft = false; }
}

void printq() { kbHold(VK_LSHIFT); kb('<'); shftRelease(); }

void prints() { if (showStrand) wcout << OutsTemplate << strand << '\n'; }

bool qqb(wstring s) {
	if (qq.substr(0, s.length()) == s) return true; else return false;
}

void clearAllKeys() {
	for (int i = 65; i < 91; i++) { GetAsyncKeyState(i); }
	for (int i = 48; i < 58; i++) { GetAsyncKeyState(i); }
	GetAsyncKeyState(cKey);
	GetAsyncKeyState(reKey);
	GetAsyncKeyState(VK_BACK);
	GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_PAUSE);
	GetAsyncKeyState(VK_SPACE);
	if (!ignoreF1s) { GetAsyncKeyState(VK_F1); GetAsyncKeyState(VK_F2); GetAsyncKeyState(VK_F3); GetAsyncKeyState(VK_F4); GetAsyncKeyState(VK_F5); GetAsyncKeyState(VK_F6); GetAsyncKeyState(VK_F7); GetAsyncKeyState(VK_F8); GetAsyncKeyState(VK_F9); GetAsyncKeyState(VK_F10); GetAsyncKeyState(VK_F11); GetAsyncKeyState(VK_F12); }
	if (!ignoreArrows) { GetAsyncKeyState(VK_LEFT); GetAsyncKeyState(VK_UP); GetAsyncKeyState(VK_RIGHT); GetAsyncKeyState(VK_DOWN); }
	if (!ignoreTab)GetAsyncKeyState(VK_TAB);
	if (!ignoreLShift)GetAsyncKeyState(VK_LSHIFT);
	if (!ignoreRShift)GetAsyncKeyState(VK_RSHIFT);
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
	SetConsoleOutputCP(CP_UTF8); while (getline(f, cell)) { wcout << cell << endl; }
	f.close(); cout << endl;
}

void scanDb(); void conn() {//<connect:>	
	bool con = false; wstring qqs = qq.substr(0, qq.find(L">") + 1);
	if (qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		if (qqs.substr(qqs.length() - 2, 2) == L":>" || qqs.substr(qqs.length() - 2, 2) == L"->") {
			con = true;
		}
	}
	if (con) {
		wifstream f(database); wstring cell; while (getline(f, cell)) {
			if (cell.substr(0, 4) == L"<'''") break;
			if (qqs == cell.substr(0, qqs.length())) { //<h:> | <h->
				wstring x = cell.substr(qqs.length()), xx = qq.substr(qqs.length()), l = in.substr(0, link.length());
				qq = x + xx;
				if (link != l && l == qq.substr(0, link.length())) qq = x;
				tail = qq;
				if (SlightPauseInBetweenConnects) Sleep(150);
				strand.clear(); f.close();
				i = -1;
				if (speed > 0) sleep = 0;
				re = L" ";//codes
				return;
			}
		}f.close(); if (fail == 1) { if (showStrand) { wcout << "Fail: " << qqs << endl; } fail = 0; i = tail.length(); return; }printq();
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
			n = check_if_num(n);
			if (n == L"") { printq(); return; }
			star_num = n;
			if (!(stoi(n) > 0)) { printq(); return; };
		}
		else { printq(); return; }
	}
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD; ip[0].ki.wVk = key;
	if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_HOME || key == VK_END) ip[0].ki.dwFlags = 1; else ip[0].ki.dwFlags = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = 2;
	for (int j = 0; j < stoi(star_num); ++j) {
		GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
		if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
		if (pause_resume) { --j; Sleep(frequency); continue; }
		if (s.length() == 3) {
			if (s == L"<,*") Sleep(CommaSleep);
			else if (s == L"<lc") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
			else if (s == L"<rc") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
			else if (s == L"<mc") { mouseEvent(MOUSEEVENTF_MIDDLEDOWN); mouseEvent(MOUSEEVENTF_MIDDLEUP); }
			else if (s == L"<ls" || s == L"<rs") mouseEvent(MOUSEEVENTF_HWHEEL);
			else SendInput(2, ip, sizeof(ip[0]));
		}
		else SendInput(2, ip, sizeof(ip[0]));
		if (speed > 0 && stoi(star_num) != j + 1) Sleep(speed);
	}
	rei();
}

void out(wstring ai) { re = L">" + ai; strand.clear(); scanDb(); re.clear(); }

void calc() {
	qq = to_wstring(ic) + qq.substr(qq.find(L">") + 1, qq.length());
	i = -1;
	re = L" ";
	tail = qq;
}

void loadSe() {
	wifstream f(settings); if (!f) { wcout << settings << " not found!\n"; return; }
	wstring cell; while (getline(f, cell)) {
		wstring se = cell.substr(0, cell.find(L":") + 1);
		wstring v = (cell.substr(cell.find(L":") + 1));
		if (v[0] == ' ') v = v.substr(1, v.length());
		int x = 0; for (size_t i = 0; i <= se.length(); ++i) x += se[i];
		auto er = [se, v]() { wcout << "Error in " << settings << " [" << se << " " << v << "]" << endl; };
		switch (x) {
			case 673://Editor:
				{ if (v.length() > 0) editor = v.substr(0); else er(); } break;
			case 772://Editor1:
				{ if (v.length() > 0) editor1 = v.substr(0); else er(); } break;
			case 680://Assume:
				{ if (v == L"1" || v == L"0") assume = stoi(v); else er(); } break;
			case 1095://ShowStrand:
				{ if (v == L"1" || v == L"0") showStrand = stoi(v); else er(); } break;
			case 847://Database:
				{ if (v.length() > 0) { database = v.substr(0); db = database.substr(database.find_last_of('\\') + 1) + L" - "; } else er(); } break;
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
			case 956://Ignore_A-Z:
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
			case 2699://ClearStrandAfterStockCtrls:
				{ if (v == L"1" || v == L"0") clear_after_stock = stoi(v); else er(); } break;
			case 2913://SlightPauseInBetweenConnects:
				{ if (v == L"1" || v == L"0") SlightPauseInBetweenConnects = stoi(v); else er(); } break;
			case 2339://StockInterfaceControls:
				{ if (v == L"1" || v == L"0") StockInterfaceControls = stoi(v); else er(); } break;
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

void printApi() {
	cout << "API\n"; if (!StockInterfaceControls) { wcout << "<db>  Show database. " << database << " | db.txt e.g., <d><db>\n<se>  Show, load settings. " << settings << " | db.txt e.g., <s><se>\n<v>  Visibility | db.txt e.g., <v><v>\n"; }  cout << "<ms:1><,1><sleep:1>  1ms sleep\n<,>  " << CommaSleep << "ms sleep | se.txt e.g., CommaSleep:150 | db.txt e.g., <test><,><,*3>\n<xy:0,0>  Move pointer (P + ESC to get)\n<x:><y:>  Current position +/- value. E.g., <x:-1>\n<rp> or <XY>  Return pointer\n<XY:>  Set. E.g., <XY:0,0><XY>\n<lc><rc><mc><lh><rh><mh><lr><rr><mr>  LEFT, RIGHT, MIDDLE -> CLICK, HOLD, RELEASE\n<ls><rs>  LEFT, RIGHT SCROLL\n<ctrl><shift><alt><win>  Hold key\n<ctrl-><shift-><alt-><win->  Release key\n<up><right><down><left><delete><esc><bs><home><end><space><tab><enter>  Press key\n<bs*2>  Press twice\n<menu>  Press MENU key\n<ins>  Press INSERT\n<ps>  Press PRINT_SCREEN\n<pu><pd>  Press PAGE_UP, PAGE_DOWN\n<f1>  Press F1 (F1-F12)\n<app:TITLE,*,ms,else->  Set app to foreground. E.g., <app:Calculator>\n<App:>  Continue if app in foreground.\n<yesno:>  Verify message. E.g., <yesno:Continue?>\n<beep>  Alert sound\n<a:>  ALT codes. E.g., <a:9201>\n<speed:>  Output. E.g., <speed:150>\n<+:><-:><*:></:><%:>  Calc. E.g., <+:1>, <+:-1>\n<+>  Clone. E.g., <*:7><+>\n<'><''><'''>  Ignore. E.g., <'bs><''rest of line><'''rest of db>\n<rgb:red,green,blue,*,ms,else:> (Use < to reconnect <else:>)  Continue if rgb in xy (R + ESC to get). E.g., <xy:0,0><rgb:255,255,255><+:1>\n<RGB:>  Continue if RGB in XY location. db.txt e.g., test-><XY:0,0><RGB:255,255,255>1\n<rand:><Rand><rand><Rand:>  Print random #, A-Z, a-z, or A-Za-z. E.g. <rand:0,1><rand:>, <Rand>, <rand>, <Rand:>\n<cb:>  Copy to clipboard. E.g. <cb:Test>\n<replace:>  Regex replace cb. E.g. <replace:t,T>";
	if (showIntro) cout << "\n\nAPI's are placed to right of the first :, -, >, ->, or :> of each line in db.txt\ndb.txt e.g., test-<enter>\nSave example to db.txt then clear strand by toggling RIGHT_CTRL, BACKSPACE, or LEFT_SHIFT + PAUSE_BREAK. Inside a text area, press T E S T to run (strand: test).\n";
	cout << endl;
}

void printStockCtrls() {
	if (StockInterfaceControls) {
		cout << "Stock interface controls" << endl;
		if (!ignoreSpace) {
			cout << "<s s:  Toggle ShowStrand: " << showStrand << endl;
			cout << "<s o:  Toggle ShowOuts: " << showOuts << endl;
			cout << "<q s:  Toggle < scan only | CtrlScanOnlyMode: " << qScanOnly << endl;
			cout << "<c q:  Toggle CloseCtrlMode: " << close_ctrl_mode << endl;
			cout << "<q k:  Change < key | CtrlKey: " << cKey << endl;
			if (!qScanOnly) {
				cout << "<s lm:  Toggle StrandLengthMode: " << strandLengthMode << endl;
				if (strandLengthMode) cout << "<s le:  Change StrandLength: " << strandLength << endl;
			}
			cout << "<r e:  Change RepeatKey: " << reKey << endl;
			//cout << "<f r:  Change frequency: " << frequency << endl;
			wcout << "<d b:  Change Database: " << database << endl;
		}
		cout << "Hold RIGHT_CTRL LEFT_CTRL or ESC on startup:  Change < key" << endl;
		cout << "Hold O on startup:  ShowStrand, ShowOuts: 1" << endl;
		//cout << "Hold Q on startup:  CtrlScanOnlyMode: 1" << endl;
		//cout << "Hold S on startup:  ShowStrand: 1" << endl;
		cout << endl;
	}
}

void printSe() {
	loadSe();
	if (showSettings) {
		wcout << settings << endl;  ifstream f(settings); if (f.fail()) { wcout << "Copy to " << settings; cout << endl; }
		cout << "ShowSettings: " << showSettings << endl;
		cout << "ShowIntro: " << showIntro << endl;
		cout << "ShowStrand: " << showStrand << endl;
		cout << "ShowOuts: " << showOuts << endl;
		wcout << "OutsTemplate: " << OutsTemplate << endl;
		wcout << "Database: " << database << endl;
		cout << "CtrlScanOnlyMode: " << qScanOnly << endl;
		cout << "CtrlKey: " << cKey << endl;
		cout << "StrandLengthMode: " << strandLengthMode << endl;
		cout << "StrandLength: " << strandLength << endl;
		cout << "CloseCtrlMode: " << close_ctrl_mode << endl;
		cout << "RepeatKey: " << reKey << endl;
		cout << "Frequency: " << frequency << endl;
		cout << "Ignore_A-Z: " << ignoreAZ << endl;
		cout << "Ignore_0-9: " << ignore09 << endl;
		cout << "Ignore_Space: " << ignoreSpace << endl;
		cout << "Ignore_F1-F12: " << ignoreF1s << endl;
		cout << "Ignore_Arrows: " << ignoreArrows << endl;
		cout << "Ignore_Esc: " << ignoreEsc << endl;
		cout << "Ignore_Tab: " << ignoreTab << endl;
		cout << "Ignore_Enter: " << ignoreEnter << endl;
		cout << "Ignore_Caps: " << ignoreCaps << endl;
		cout << "Ignore_LShift: " << ignoreLShift << endl;
		cout << "Ignore_RShift: " << ignoreRShift << endl;
		cout << "Ignore_LAlt: " << ignoreLAlt << endl;
		cout << "Ignore_RAlt: " << ignoreRAlt << endl;
		cout << "Ignore_LCtrl: " << ignoreLCtrl << endl;
		cout << "Ignore_RCtrl: " << ignoreRCtrl << endl;
		cout << "Ignore_GraveAccent: " << ignoreGraveAccent << endl;
		cout << "Ignore_Minus: " << ignoreMinus << endl;
		cout << "Ignore_Equal: " << ignoreEqual << endl;
		cout << "Ignore_LBracket: " << ignoreLBracket << endl;
		cout << "Ignore_RBracket: " << ignoreRBracket << endl;
		cout << "Ignore_Backslash: " << ignoreBackslash << endl;
		cout << "Ignore_Semicolon: " << ignoreSemicolon << endl;
		cout << "Ignore_Quote: " << ignoreQuote << endl;
		cout << "Ignore_Comma: " << ignoreComma << endl;
		cout << "Ignore_Period: " << ignorePeriod << endl;
		cout << "Ignore_Forwardslash: " << ignoreForwardslash << endl;
		cout << "Ignore_Menu: " << ignoreMenuKey << endl;
		//cout << "Ignore_MediaKeys: " << ignoreMediaKeys << endl;
		cout << "Ignore_NumPad: " << ignoreNumPad << endl;
		cout << "StartHidden: " << startHidden << endl;
		cout << "ClearStrandAfterStockCtrls: " << clear_after_stock << endl;
		cout << "SlightPauseInBetweenConnects: " << SlightPauseInBetweenConnects << endl;
		cout << "CommaSleep: " << CommaSleep << endl;
		cout << "StockInterfaceControls: " << StockInterfaceControls << endl;
		cout << "AutoBs_EscH: " << EscHAutoBs << endl;
		cout << "AutoBs_EscComma: " << EscCommaAutoBs << endl;
		cout << "AutoBs_EscEqual: " << EscEqualAutoBs << endl;
		cout << "AutoBs_RepeatKey: " << AutoBs_RepeatKey << endl;
		cout << "SeHotReload_CtrlS: " << SeHotReload_CtrlS << endl;
		cout << "SeDbClearStrand_CtrlS: " << SeDbClearStrand_CtrlS << endl;
		cout << "Assume: " << assume << endl;
		wcout << "Editor: " << editor << endl;
		wcout << "Editor1: " << editor1 << endl;
		cout << "Exit_EscX: " << enableEscX << endl;
		cout << endl;
	}
}

void toggle_visibility() {
	(bool)IsWindowVisible(GetConsoleWindow()) == 1 ?
		ShowWindow(GetConsoleWindow(), SW_HIDE)
		:
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	Sleep(150);
	strand.clear();
}

void getApp() {
	out(L"<alt><esc><alt->");
	HWND h = GetForegroundWindow();
	int l = GetWindowTextLength(h);
	wstring title(l,0);
	GetWindowTextW(h, &title[0], l + 1);
	out(L"<shift><,><alt><esc><alt-><shift->");
	if (title == L"") return;
	out(L"<shift>,<shift->app:" + title + L">");
}

void getRGB() {
	POINT pt; GetCursorPos(&pt); COLORREF color; HDC hDC;
	hDC = GetDC(NULL);
	if (hDC != NULL) {
		color = GetPixel(hDC, pt.x, pt.y);
		ReleaseDC(NULL, hDC);
		if (color != CLR_INVALID) {
			wstring c = to_wstring(GetRValue(color)) + L"," + to_wstring(GetGValue(color)) + L"," + to_wstring(GetBValue(color));
			tail = L"<shift>,<shift->rgb:" + c + L">";
			re = tail;
		}
	}
}

void cbSet(wstring& s) {
	auto length = 2 * (wcslen(s.c_str()) + 1);
	HGLOBAL h = GlobalAlloc(GMEM_DDESHARE, length);
	memcpy(GlobalLock(h), s.c_str(), length);
	GlobalUnlock(h);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, h);
	CloseClipboard();
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
wifstream f(database); if (!f) { wcout << database << " not found!\n"; return; }
	wstring cell; f.imbue(locale(f.getloc(), new codecvt_utf8_utf16<wchar_t>));
	while (getline(f, cell)) { //cout << cell << endl;
		if (cell.substr(0, 4) == L"<'''") break; //ignore db...
		if (re > L"" || (close_ctrl_mode && cell.substr(0, strand.length()) == strand || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + L":" || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + L"-" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + L":>" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + L"->") || cell.substr(0, strand.length() + 1) == strand + L">" || cell.substr(0, strand.length() + 1) == strand + L":" || cell.substr(0, strand.length() + 1) == strand + L"-" || (strandLengthMode && cell.substr(0, strandLength) == strand && cell.substr(0, 1) != L"<") || close_ctrl_mode && strandLengthMode && strand.substr(0, 1) != L"<" && cell.substr(0, strand.length() - 1) == strand.substr(0, strand.length() - 1)) { //found i>o, i:o, i-o, i:>o, i->o || i>o, i:o, i-o || io || io
			if (close_ctrl_mode && strand.length() > 0 && strand.substr(strand.length() - 1) == L">") strand = strand.substr(0, strand.length() - 1);
			in = re > L"" ? re.substr(1) : cell;
			if (re > L"") {
				cell = re;
				if (re.substr(0, 20) == L"><shift>,<shift->xy:") { POINT pt; GetCursorPos(&pt); wstring xy = to_wstring(pt.x) + L"," + to_wstring(pt.y); cell = L"><shift>,<shift->xy:" + xy + L">"; re = cell; if (showStrand) { wcout << OutsTemplate << L"<xy:" + xy + L">\n"; } }
				else if (re.substr(0, 21) == L"><shift>,<shift->rgb:") { getRGB(); if (showStrand) { wcout << OutsTemplate << "<" << tail.substr(16, tail.length()) << endl; } }
			}
#pragma region set_tail
			tail = re > L"" ? re : cell.substr(strand.length(), cell.length() - strand.length());
			switch (tail[0]) {
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
			if (showOuts) wcout << "found: " << cell << "\ntail: " << tail << endl;
#pragma endregion
			if (tail.find(L"<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
			f.close();
			fail = 0; for (i = 0; i < tail.length(); ++i) {
				if (speed > 0) { if (sleep) { Sleep(speed); } sleep = 1; }
				GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; break; }if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }// int m = MessageBoxA(0, "Resume?", "dnaspider", MB_YESNO); if (m != IDYES) { break; } }
				if (pause_resume) { --i; Sleep(frequency); continue; }

				wstring ctail = tail.substr(i, 1);//extracted char from tail
				if (showOuts) { wcout << "ctail: " << ctail << endl; }
				switch (ctail[0]) {
				case'<':
					if (i > 0) in = tail.substr(i, tail.length() - i);
					if (!fail) qq = tail.substr(i, tail.length() - i); //<test>
					if (showOuts) { wcout << "qq: " << qq << endl; }
					if (qq.find(L":") != std::string::npos) { //<test:#>
						qp = qq.substr(qq.find(L":") + 1, qq.find(L">") - qq.find(L":") - 1);//#
						qx = qp.substr(0, qp.find(L","));//x <xy:#,#>
						qy = qp.substr(qp.find(L",") + 1, qp.find(L">") - qp.find(L",") - 1);//y
						//cout << "qp: " << qp  << endl; cout << "qx: " << qx << endl; cout << "qy: " << qy << endl;
					}
					switch (qq[1]) {
					case'+': //calc
						if (qqb(L"<+>")) {//repeat#
							calc();
							break;
						}
						else if (qqb(L"<+:")) {//calc +
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic += stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'-':
						if (qqb(L"<-:")) {//-
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic -= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'*':
						if (qqb(L"<*:")) {//*
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic *= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'/':
						if (qqb(L"</:")) {//divide
							if (check_if_num(qp) == L"" || stoi(qp) <= 0) { printq(); continue; }
							ic /= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'%':
						if (qqb(L"<%:")) {//%
							if (check_if_num(qp) == L"") { printq(); continue; }
							ic %= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case',':
						if (qqb(L"<,*")) kbPress(L"<,*", VK_F7);//sleep150ms, vk_dud
						else if (qqb(L"<,")) { //<,#>
							wstring s = qq.substr(2, qq.find('>') - 2);
							if (s == L"") s = to_wstring(CommaSleep);
							s = check_if_num(s);
							if (s == L"") { printq(); break; }
							if (stoi(s) >= 0 && s[0] != '+') { Sleep(stoi(s)); } else { printq(); break; };
							rei();
						}
						else printq();
						break;
					case'\'':
						if (qq.find(L">") != string::npos && qqb(L"<''")) i = tail.length();//<''ignore>...
						else if (qq.find(L">") != string::npos && qqb(L"<'")) { auto x = (qq.find('>') - 2); wstring v = qq.substr(2, x); for(size_t x = 0; x < qq.length() - 1; ++x){ if (qq[x] > 127) { v = L""; break; } } if (showStrand) { SetConsoleCP(CP_UTF8); wstring s = cell[strand.length() + 1] == '>' ? L">" : L"", t = qq.substr(2, qq.find(L">") - 2); wcout << OutsTemplate << strand << cell[strand.length()] << s << " " <<  v << endl; } rei(); sleep = 0; } //<'com1ments>
						else printq();
						break;
					case'a':
					case 'A':
						if (qqb(L"<alt>")) { kbHold(VK_LMENU); rei(); }
						else if (qqb(L"<alt->")) { kbRelease(VK_LMENU); rei(); }
						else if (qqb(L"<alt")) kbPress(L"<alt", VK_LMENU);
						else if (qqb(L"<a:")) {if (qp[0] == ' ') qp = qp.substr(1, qp.length()); kb1(qp); rei(); }//alt codes
						else if (qqb(L"<app:") || qqb(L"<App:")) {//app activate, if app in foreground
							wstring a = qp, x = L"1", ms = L"333"; link = L"";//<app:a,x,ms,link>
							a = a.substr(0, a.find(L","));
							if (a[0] == ' ') a = a.substr(1, a.length());
							if (qp.find(L",") != string::npos) {
								x = qp.substr(qp.find(L",") + 1);
								if (x.find(L",") != string::npos) {
									ms = x.substr(x.find(L",") + 1);
									if (ms.find(L",") != string::npos) {
										link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); }
										ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
									}
									x = x.substr(0, x.find(L","));
								}
								if (check_if_num(x) == L"") { printq(); break; }
							}//cout << a << " " << x << " " << ms << " " << link << endl;
							auto size{ 0 }, length{ stoi(x) };
							HWND h, h1; DWORD pid;
							auto f = []() { i = tail.length(); if (showStrand) wcout << "Fail: <" << qq[1] << "pp:" << qp << ">\n"; };
							for (; size < length; ++size) { //cout << size << " app:" << a << " *" << x << " " << ms << "ms" << endl;
								GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
								if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
								if (pause_resume) { --size; Sleep(frequency); continue; }
								if (size >= length) { f(); break; }
								if (qq[1] == 'A') {//App
									h = GetForegroundWindow(); h1 = FindWindowW(0, a.c_str());
									if (h == h1) { break; fail = 0; }
								}
								else if (qq[1] == 'a') {//'app
									h = FindWindowW(0, a.c_str()); GetWindowThreadProcessId(h, &pid);
									if (h) {
										if (IsIconic(h)) ShowWindow(h, SW_RESTORE);
										SetForegroundWindow(h);
										fail = 0; break;
									}
								}
								if (length >= 1) Sleep(stoi(ms));
							}
							if (size >= length) {//fail
								if (link > L"" && (link[link.length() - 1] == ':' || link[link.length() - 1] == '-')) {
									if (L"<" + link == in.substr(0, link.length() + 1) || link == in.substr(0, link.length())) {
										fail = 1;
									}
									else {
										tail = link[0] == '<' ? link + L">" + qq.substr(qq.find(L">") + 1) : L"<" + link + L">";//<app:a,x,ms,<link->..., <app:a,x,ms,link->
									}
									re = L" "; i = -1; break;
								}
								f(); break;
							}
							rei();
						}
						else conn();
						break;
					case'b':
						if (qqb(L"<bs")) kbPress(L"<bs", VK_BACK);
						else if (qqb(L"<beep>")) { cout << "\a" << endl; rei(); }
						else conn();
						break;
					case'c':
						if (qqb(L"<ctrl>")) { kbHold(VK_CONTROL); rei(); }
						else if (qqb(L"<ctrl->")) { kbRelease(VK_CONTROL); rei(); }
						else if (qqb(L"<ctrl")) kbPress(L"<ctrl", VK_CONTROL);
						else if (qqb(L"<cb:")) {
							cbSet(qp);
							rei();
						}
						else conn();
						break;
					case'd':
						if (qqb(L"<db>")) { printDb(); rei(); }
						else if (qqb(L"<down")) kbPress(L"<down", VK_DOWN);
						else if (qqb(L"<delete")) kbPress(L"<delete", VK_DELETE);
						else conn();
						break;
					case'e':
						if (qqb(L"<enter")) kbPress(L"<enter", VK_RETURN);
						else if (qqb(L"<end")) kbPress(L"<end", VK_END);
						else if (qqb(L"<esc")) kbPress(L"<esc", VK_ESCAPE);
						else conn();
						break;
					case'f':
						if (qqb(L"<f10")) kbPress(L"<f10", VK_F10);
						else if (qqb(L"<f11")) kbPress(L"<f11", VK_F11);
						else if (qqb(L"<f12")) kbPress(L"<f12", VK_F12);
						else if (qqb(L"<f1")) kbPress(L"<f1", VK_F1);
						else if (qqb(L"<f2")) kbPress(L"<f2", VK_F2);
						else if (qqb(L"<f3")) kbPress(L"<f3", VK_F3);
						else if (qqb(L"<f4")) kbPress(L"<f4", VK_F4);
						else if (qqb(L"<f5")) kbPress(L"<f5", VK_F5);
						else if (qqb(L"<f6")) kbPress(L"<f6", VK_F6);
						else if (qqb(L"<f7")) kbPress(L"<f7", VK_F7);
						else if (qqb(L"<f8")) kbPress(L"<f8", VK_F8);
						else if (qqb(L"<f9")) kbPress(L"<f9", VK_F9);
						else conn();
						break;
					case'h':
						if (qqb(L"<home")) kbPress(L"<home", VK_HOME);
						else conn();
						break;
					case'i':
						if (qqb(L"<ins")) kbPress(L"<ins", VK_INSERT);
						else conn();
						break;
					case'l':
						if (qqb(L"<lc")) kbPress(L"<lc", VK_F7);//left click
						else if (qqb(L"<lh>")) {//left hold
							mouseEvent(MOUSEEVENTF_LEFTDOWN);
							rei();
						}
						else if (qqb(L"<lr>")) {//left release
							mouseEvent(MOUSEEVENTF_LEFTUP);
							rei();
						}
						else if (qqb(L"<left")) kbPress(L"<left", VK_LEFT);
						else if (qqb(L"<ls")) { kbPress(L"<ls", VK_F7); }//hscroll+
						else conn();
						break;
					case'm':
						if (qqb(L"<ms:")) if (check_if_num(qp) != L"") { Sleep(stoi(qp));	rei(); }
						else printq();
						else if (qqb(L"<mc")) kbPress(L"<mc", VK_F7);//middle click
						else if (qqb(L"<mh>")) {//middle hold
							mouseEvent(MOUSEEVENTF_MIDDLEDOWN);
							rei();
						}
						else if (qqb(L"<mr>")) {//middle release
							mouseEvent(MOUSEEVENTF_MIDDLEUP);
							rei();
						}
						else if (qqb(L"<menu")) kbPress(L"<menu", VK_APPS);
						else conn();
						break;
					case'p':
						if (qqb(L"<ps")) kbPress(L"<ps", VK_SNAPSHOT);
						else if (qqb(L"<pu")) kbPress(L"<pu", VK_PRIOR);//pgup
						else if (qqb(L"<pd")) kbPress(L"<pd", VK_NEXT);//pgdn
						else conn();
						break;
					case'R':
					case'r':
						if (qqb(L"<rp>")) {//return pointer
							SetCursorPos(qxc, qyc);
							rei();
						}
						else if (qqb(L"<rand:") || qqb(L"<rand>") || qqb(L"<Rand>") || qqb(L"<Rand:")) {//<rand:0,1>
							int r = rand();
							char s = (qq[5] + qq[1]);
							wstring t = tail;
							size_t rei = i;
							switch (s) {
							case -84://':r': <rand:> #
								if (check_if_num(qx) != L"" && check_if_num(qy) != L"" && stoi(qy) > stoi(qx)) {
									r = qx == L"0" ?
										rand() % (stoi(qy) + 1) :
										(rand() % (stoi(qy) + 1 - stoi(qx))) + stoi(qx);
								}
								out(to_wstring(r));
								codes = t; tail = t; i = rei + qq.find(L">");
								break;
							case -112://'>R': <Rand> A-Z
								r = (char)((rand() % ('Z' + 1 - 'A')) + 'A');//cout << (char)r;
								goto outr;
							case -80://'>r': <rand> a-z
								r = (char)((rand() % ('z' + 1 - 'a')) + 'a');//cout << (char)r;
								goto outr;
							case -116://':R': <Rand:> A-Za-z
								r = rand() % 2;
								r = r == 1 ?
									(char)((rand() % ('z' + 1 - 'a')) + 'a') :
									(char)((rand() % ('Z' + 1 - 'A')) + 'A');//cout << (char)r;
							outr:
								switch (r) {
								case 65: out(L"A"); break;
								case 66: out(L"B"); break;
								case 67: out(L"C"); break;
								case 68: out(L"D"); break;
								case 69: out(L"E"); break;
								case 70: out(L"F"); break;
								case 71: out(L"G"); break;
								case 72: out(L"H"); break;
								case 73: out(L"I"); break;
								case 74: out(L"J"); break;
								case 75: out(L"K"); break;
								case 76: out(L"L"); break;
								case 77: out(L"M"); break;
								case 78: out(L"N"); break;
								case 79: out(L"O"); break;
								case 80: out(L"P"); break;
								case 81: out(L"Q"); break;
								case 82: out(L"R"); break;
								case 83: out(L"S"); break;
								case 84: out(L"T"); break;
								case 85: out(L"U"); break;
								case 86: out(L"V"); break;
								case 87: out(L"W"); break;
								case 88: out(L"X"); break;
								case 89: out(L"Y"); break;
								case 90: out(L"Z"); break;
								case 97: out(L"a"); break;
								case 98: out(L"b"); break;
								case 99: out(L"c"); break;
								case 100: out(L"d"); break;
								case 101: out(L"e"); break;
								case 102: out(L"f"); break;
								case 103: out(L"g"); break;
								case 104: out(L"h"); break;
								case 105: out(L"i"); break;
								case 106: out(L"j"); break;
								case 107: out(L"k"); break;
								case 108: out(L"l"); break;
								case 109: out(L"m"); break;
								case 110: out(L"n"); break;
								case 111: out(L"o"); break;
								case 112: out(L"p"); break;
								case 113: out(L"q"); break;
								case 114: out(L"r"); break;
								case 115: out(L"s"); break;
								case 116: out(L"t"); break;
								case 117: out(L"u"); break;
								case 118: out(L"v"); break;
								case 119: out(L"w"); break;
								case 120: out(L"x"); break;
								case 121: out(L"y"); break;
								case 122: out(L"z"); break;
								}
								codes = t; tail = t; i = rei + qq.find(L">");
							}
						}
						else if (qqb(L"<rc")) kbPress(L"<rc", VK_F7);
						else if (qqb(L"<rh>")) {//right hold
							mouseEvent(MOUSEEVENTF_RIGHTDOWN);
							rei();
						}
						else if (qqb(L"<rr>")) {//right release
							mouseEvent(MOUSEEVENTF_RIGHTUP);
							rei();
						}
						else if (qqb(L"<right")) kbPress(L"<right", VK_RIGHT);
						else if (qqb(L"<rs")) { kbPress(L"<rs", VK_F7); }//hscroll-
						else if (qqb(L"<rgb:") || qqb(L"<RGB:")) { //<rgb:r,g,b,x,ms,link>
							wstring r, g, b, x = L"1", ms = L"333"; link = L"";
							auto f = []() { i = tail.length(); if (showStrand) wcout << "Fail: <" << qq[1] << qq[2] << qq[3] << ":" << qp << ">\n"; };
							r = qp.substr(0, qp.find(L","));
							b = qp.substr(qp.find(L",") + 1);
							g = b.substr(0, b.find(L","));
							b = b.substr(b.find(L",") + 1);
							if (b.find(L",") != string::npos) {//x,ms
								x = b; b = b.substr(0, b.find(L","));
								x = x.substr(x.find(L",") + 1);
								if (x.find(L",") != string::npos) {
									ms = x.substr(x.find(L",") + 1);
									if (ms.find(L",") != string::npos) {
										link = ms.substr(ms.find(L",") + 1); if (link[0] == ' ') { link = link.substr(1); }
										ms = ms.substr(0, ms.find(L",")); if (check_if_num(ms) == L"") { printq(); break; }
									}
									x = x.substr(0, x.find(L","));
								}
								if (check_if_num(x) == L"") { printq(); break; }
							}//cout << r << " " << g << " " << b << " " << x << " " << ms << " " << link << endl;
							if (check_if_num(r) == L"" || check_if_num(g) == L"" || check_if_num(b) == L"") { printq(); break; }
							POINT pt; GetCursorPos(&pt);
							COLORREF color; HDC hDC;
							hDC = GetDC(NULL);
							color = (qq[1] == 'R') ? GetPixel(hDC, qxc, qyc) : GetPixel(hDC, pt.x, pt.y);//<RGB> get xy from <XY:> or current
							ReleaseDC(NULL, hDC);
							if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b)) {
								rei();//cout << "rgb\n";
								fail = 0;
							}
							else {
								auto size{ 0 }, length{ stoi(x) };
								for (; size < length; ++size) {
									GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { esc_pressed = 1; pause_resume = 0; if (speed > 0) { speed = 0; } return; }//stop
									if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE);  kbRelease(VK_PAUSE); } else { pause_resume = 1; } }
									if (pause_resume) { --size; Sleep(frequency); continue; }
									if (size >= length) { f(); break; }
									GetCursorPos(&pt);
									color = (qq[1] == 'R') ? GetPixel(hDC, qxc, qyc) : GetPixel(hDC, pt.x, pt.y);//<RGB> get xy from <XY:> or current
									ReleaseDC(NULL, hDC);
									if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b)) {
										fail = 0; break;
									}
									if (length >= 1) Sleep(stoi(ms));
								}
								if (size >= length) { 
									if (link > L"" && (link[link.length() - 1] == ':' || link[link.length() - 1] == '-')) {
										if (L"<" + link == in.substr(0, link.length() + 1) || link == in.substr(0, link.length())) {
											fail = 1;
										}
										else {
											tail = link[0] == '<' ? link + L">" + qq.substr(qq.find(L">") + 1) : L"<" + link + L">";//<rgb:r,g,b,*,ms,<link-> = <link->..., <rgb:r,g,b,*,ms,link-> = <link->
										}
										re = L" "; i = -1; break;
									}
									f(); break;
								}
								rei();
							}
						}
						else if (qqb(L"<replace:")) { 
							wstring cb = L""; OpenClipboard(0);
							HANDLE c = GetClipboardData(CF_UNICODETEXT);
							if (c != nullptr) {
								wchar_t* t = static_cast<wchar_t*>(GlobalLock(c));
								if (t != nullptr) cb = t;
								GlobalUnlock(c);
							}
							CloseClipboard();
							if (cb > L"") {
								cb = regex_replace(cb, wregex(qx), qy);
								cbSet(cb);
							}
							rei();
						}
						else conn();
						break;
					case's':
						if (qqb(L"<se>")) { printSe(); rei(); }
						else if (qqb(L"<shift>")) { kbHold(VK_LSHIFT); rei(); }
						else if (qqb(L"<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
						else if (qqb(L"<shift")) kbPress(L"<shift", VK_LSHIFT);
						else if (qqb(L"<sleep:")) if (check_if_num(qp) != L"") { Sleep(stoi(qp)); rei(); } else printq();
						else if (qqb(L"<space")) kbPress(L"<space", VK_SPACE);
						else if (qqb(L"<speed:")) if (check_if_num(qp) != L"") { speed = stoi(qp); rei(); sleep = 0; } else printq();
						else conn();
						break;
					case't':
						if (qqb(L"<tab")) kbPress(L"<tab", VK_TAB);
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
						if (qqb(L"<xy:")) {
							SetCursorPos(stoi(qx), stoi(qy)); rei();
						}
						else if (qqb(L"<XY>")) {//return pointer
							SetCursorPos(qxc, qyc); rei();
						}
						else if (qqb(L"<XY:")) {//set return pointer
							qxc = stoi(qx); qyc = stoi(qy); rei();
						}
						else if (qqb(L"<x:")) {//x + or - 1px
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
					case 'y':
						if (qqb(L"<yesno:")) {
							int m = MessageBoxW(0, qp.c_str(), L"dnaspider", MB_YESNO);
							if (m == IDYES) { rei(); continue; }
							else { i = tail.length(); break; }
						}
						else if (qqb(L"<y:")) {//y + or - 1px
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
					if ((ctail[0] >= 33 && ctail[0] <= 38) || (ctail[0] >= 40 && ctail[0] <= 43) || ctail[0] == 58 || (ctail[0] >= 62 && ctail[0] <= 90) || ctail[0] == 94 || ctail[0] == 95 || (ctail[0] >= 123 && ctail[0] <= 126)) { shft = true; }//if !"#$%& ()*+ : > ?&AZ ^ _ {|}~
					if (shft) kbHold(VK_LSHIFT);
					kb(ctail[0]);
					if (shft) shftRelease();
					break;
				}
				//GetAsyncKeyState(VkKeyScan(ctail[0])); //clear
			}
			if (strand > L"" || re > L"") {
				if (re == L"" || re == L" " || strandLengthMode) { re = L""; tail = codes; }
				clearAllKeys();
				strand.clear();
			}
			if (speed > 0) speed = 0;
			break;
		}
	}
	f.close();
	if (strand > L"" && close_ctrl_mode && strand[0]=='<') { tail = strand.substr(1, strand.length() - 2); }//dbless repeat
}

void printXy() {
	POINT pt; GetCursorPos(&pt);
	if (strand == L"x") { if (showOuts) cout << "xy: " << pt.x << "," << pt.y << endl; }
	else { out(L"<bs*2>"); out(L"><shift>,<shift->xy:" + to_wstring(pt.x) + L"," + to_wstring(pt.y) + L">"); }
}

void printInterfaceCtrls() {
	wstring c; if (cKey == VK_CONTROL) c = L"CTRL"; else if (cKey == VK_LCONTROL) c = L"LEFT_CTRL"; else if (cKey == VK_RCONTROL) c = L"RIGHT_CTRL"; else if (cKey == VK_ESCAPE) c = L"ESC";
	cout << "Interface" << endl;
	if (StockInterfaceControls) {
		wstring se = qScanOnly ? L"<se" : L"S E"; wcout << se << ":  Settings (Press " << (qScanOnly ? c + L" S E" : L"S E") << " to load " << settings << ")\n";
		if (qScanOnly)se = L"<db"; else se = L"D B"; wcout << se << ":  Database" << endl;
	}
	cout << "ESC:  Stop" << endl;
	if (enableEscX) cout << "X + ESC:  Exit" << endl;
	cout << "H + ESC:  Toggle visibility" << endl;
	wcout << c << " or COMMA + ESC:  Toggle <" << endl;
	wcout << "LEFT_SHIFT + " << c << ":  <" << endl;
	cout << "PAUSE_BREAK:  Reset strand | Pause/Resume" << endl;
	cout << "LEFT_SHIFT + PAUSE_BREAK:  Clear strand" << endl;
	if (StockInterfaceControls) { wcout << "<odb:  Open database: " << database << endl; wcout << "<ose:  Open settings: " << settings << endl; }
	(StockInterfaceControls) ? cout << "<xy or P + ESC" : cout << "P + ESC"; cout << ":  <xy:>" << endl;
	cout << "A + ESC:  <app:>" << endl;
	cout << "R + ESC:  <rgb:>" << endl;
	(reKey == 145) ? c = L"SCROLL_LOCK" : c = L"repeatKey: " + reKey; wcout << c << " or EQUAL + ESC:  Repeat" << endl;
	cout << endl;
}

void printIntro() {
	if (showIntro) {
		printInterfaceCtrls();		
		printStockCtrls();
		printApi();
		printSe();
		printDb();
	}
}

void key(wstring k) {
	strand.append(k);
	if (strandLengthMode && (int)strand.length() > strandLength && strand.substr(0, 1) != L"<") { strand = strand.substr(strand.length() - strandLength); }
	prints();
	if (close_ctrl_mode && strand.find(L">") != std::string::npos && strand.substr(strand.length() - 1) != L">") { strand.clear(); prints(); return; }
	scanDb();
	if (strand > L"" && StockInterfaceControls) {
		if (strand == L"db" || strand == L"<db") { printDb(); if (clear_after_stock)strand.clear(); }
		if (strand == L"se" || strand == L"<se") { printSe(); if (clear_after_stock)strand.clear(); }
		if (strand == L"x" || strand == L"<xy") { printXy(); }
		if (strand == L"<odb") { out(L"<win>r<win-><,>" + database + L"<enter>"); }
		if (strand == L"<ose") { out(L"<win>r<win-><,>" + settings + L"<enter>"); }
		if (!ignoreSpace) {
			if (strand == L"<q s") { qScanOnly = !qScanOnly; cout << "<q s: " << qScanOnly << endl; strand.clear(); }
			if (strand == L"<s lm") { strandLengthMode = !strandLengthMode; cout << "Strand length mode: " << strandLengthMode << endl; strand.clear(); if (strandLengthMode) { cout << "Strand length: " << strandLength << endl; } }
			if (strand == L"<s le") { kb(VK_ESCAPE); int sl; cout << "Enter new strand length:" << endl;  cin >> sl; if (sl > 0) { strandLength = sl; } else { return; } clearAllKeys(); cout << "strand length: " << strandLength << endl; strand.clear(); }
			if (strand == L"<r e") { kb(VK_ESCAPE); int sl; cout << "Enter new repeat key:" << endl;  cin >> sl; if (sl > 0) { reKey = sl; } else { return; } clearAllKeys(); cout << "repeat key: " << reKey << endl; strand.clear(); }
			if (strand == L"<q k") { kb(VK_ESCAPE); int sl; cout << "Enter new < key:" << endl;  cin >> sl; if (sl > 0) { cKey = sl; } else { return; } clearAllKeys(); cout << "< key: " << cKey << endl; strand.clear(); }
			if (strand == L"<f r") { kb(VK_ESCAPE); int sl; cout << "Enter new frequency:" << endl;  cin >> sl; if (sl > 0) { frequency = sl; } else { return; } clearAllKeys(); cout << "frequency: " << frequency << endl; strand.clear(); }
			if (strand == L"<d b") { kb(VK_ESCAPE); wstring sl; cout << "Enter new database:" << endl;  wcin >> sl; if (sl > L"") { database = sl; } else { return; } clearAllKeys(); wcout << "database: " << database << endl; strand.clear(); }
			if (strand == L"<s s") { showStrand = !showStrand; cout << "<s s: " << showStrand << endl; strand.clear(); }
			if (strand == L"<c q") { close_ctrl_mode = !close_ctrl_mode; cout << "<c q: " << close_ctrl_mode << endl; strand.clear(); }
			if (strand == L"<s o") { showOuts = !showOuts; cout << "<s o: " << showOuts << endl; strand.clear(); }
		}
	}
	else if (strand == L"") prints();
}

#pragma endregion

int main() {//cout << "@dnaspider\n\n";
#pragma region initial_startup
	if (CreateDirectory("c:/dna", NULL)) {//L"c:/dna"
		showIntro=1;showOuts=1;cKey=VK_CONTROL;ignore09=0;SlightPauseInBetweenConnects=1;StockInterfaceControls=1;//minimalist se.txt
		wcout << database << " not found.\nPress [1] to auto create.\n\n";
		for (;; Sleep(150)) { if (GetAsyncKeyState(VK_ESCAPE)) { RemoveDirectory("c:/dna"); Sleep(150); break; }if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
		showOuts = false; wofstream fd(database); fd << "h-Hello\n<e->Enjoy\n<x:><bs><e->!\n\nGetting Started:\nPress H (strand: h),\nRIGHT_CTRL E (strand: <e), \nLEFT_SHIFT + RIGHT_CTRL X or,\nCOMMA + ESC X (strand: <x)\nin a text area to run.\n\nTip:\nClear strand first by toggling\nRIGHT_CTRL, BACKSPACE, or \nLEFT_SHIFT + PAUSE_BREAK.\n\nPress keys separately\n(RIGHT_CTRL, release RIGHT_CTRL, X)."; fd.close(); wofstream fs(settings); fs << "ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nShowOuts: 0\nOutsTemplate: " << OutsTemplate << "\nDatabase: " << database << "\nCloseCtrlMode: 0\nCtrlScanOnlyMode: 0\nCtrlKey: 163\nStrandLengthMode: 0\nStrandLength: 3\nRepeatKey: 145\nAutoBs_RepeatKey: 0\nFrequency: 150\nIgnore_A-Z: 0\nIgnore_0-9: 0\nIgnore_Space: 0\nIgnore_F1-F12: 1\nIgnore_Arrows: 1\nIgnore_Esc: 1\nIgnore_Tab: 1\nIgnore_Enter: 1\nIgnore_Caps: 1\nIgnore_LShift: 1\nIgnore_RShift: 1\nIgnore_LAlt: 1\nIgnore_RAlt: 1\nIgnore_LCtrl: 1\nIgnore_RCtrl: 1\nIgnore_GraveAccent: 1\nIgnore_Minus: 1\nIgnore_Equal: 1\nIgnore_LBracket: 1\nIgnore_RBracket: 1\nIgnore_Backslash: 1\nIgnore_Semicolon: 1\nIgnore_Quote: 1\nIgnore_Comma: 1\nIgnore_Period: 1\nIgnore_Forwardslash: 1\nIgnore_Menu: 1\nIgnore_NumPad: 1\nStartHidden: 0\nStockInterfaceControls: 1\nClearStrandAfterStockCtrls: 1\nSlightPauseInBetweenConnects: 1\nAutoBs_EscH: 1\nAutoBs_EscComma: 1\nAutoBs_EscEqual: 1\nCommaSleep: 150\nSeHotReload_CtrlS: 1\nSeDbClearStrand_CtrlS: 1\nExit_EscX: 1\nAssume: 0\nEditor: " << editor << "\nEditor1: " << editor1; fs.close(); out(L"<win>r<win-><app:run, 3>" + settings + L"<enter><ms:1500><win>r<win-><app:run, 3>" + database + L"<enter>"); re = L""; tail = L""; strand.clear();
	}
	loadSe();
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (GetAsyncKeyState(81)) qScanOnly = true; //q
	if (GetAsyncKeyState(83)) showStrand = true; //s
	if (GetAsyncKeyState(79)) { showOuts = true; showStrand = true; }//o
	if (GetAsyncKeyState(VK_RCONTROL)) cKey = VK_RCONTROL;
	if (GetAsyncKeyState(VK_LCONTROL)) cKey = VK_LCONTROL;
	if (GetAsyncKeyState(VK_ESCAPE)) cKey = VK_ESCAPE;
	printIntro();
	srand((unsigned)time(NULL));
#pragma endregion
	for (;; Sleep(frequency)) {
		if (SeHotReload_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (L"se.txt - " + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (L"se.txt - " + editor1).c_str()) == GetForegroundWindow())) { HWND np = FindWindowW(0, (L"se.txt - " + editor).c_str()), vsc = FindWindowW(0, (L"se.txt - " + editor1).c_str()); HWND HotReload = GetForegroundWindow(); if (np == HotReload || vsc == HotReload) { loadSe(); if (SeDbClearStrand_CtrlS) { clearAllKeys(); strand.clear(); if (showStrand) { prints(); } continue; } else if (!ignoreAZ) key(L"s"); continue; } }//lctrl+s hot reload
		if (SeDbClearStrand_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowW(0, (db + editor).c_str()) == GetForegroundWindow() || FindWindowW(0, (db + editor1).c_str()) == GetForegroundWindow())) { strand.clear(); if (showStrand) { prints(); } continue; }//clear
		if (GetAsyncKeyState(VK_BACK)) {
			strand = strand.substr(0, strand.length() - 1);
			prints(); continue;
		}
		if (GetAsyncKeyState(cKey)) {//toggle <
			GetAsyncKeyState(VK_LSHIFT); if (GetAsyncKeyState(VK_LSHIFT) && cKey != VK_LSHIFT) { clearAllKeys(); strand = L"<"; prints(); continue; }
			if (strand.substr(0, 1) == L"<") {
				if (close_ctrl_mode) {//<x>	
					if (strand.find(L">") != std::string::npos) strand.clear();
					else {
						if (strand.length() > 1) {
							//if (cKey >= 160 && cKey <= 165 || cKey == 27) { Sleep(115); } key(">");
							if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(115); kbRelease(cKey); GetAsyncKeyState(cKey); } key(L">");
							if (strand > L"") { strand.clear(); prints(); }
							continue;
						}
						else strand.clear();
					}
				}
				else strand.clear();
			}
			else if (close_ctrl_mode && strand.length() > 0 && strand.find(L">") == std::string::npos) {//x>
				//strand.append(">"); if (cKey >= 160 && cKey <= 165 || cKey == 27) { Sleep(115); } scanDb();
				strand.append(L">"); if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(115); kbRelease(cKey); GetAsyncKeyState(cKey); } scanDb();
				if (strand > L"") { prints(); strand.clear(); }
			}//reg
			else {
				if (close_ctrl_mode && strand.length() > 0) strand.clear();
				else { clearAllKeys(); strand = L"<"; }
			}
			prints(); continue;
		}
		if (GetAsyncKeyState(reKey)) { //repeat
			if (AutoBs_RepeatKey) kb(VK_BACK);
			out(tail);
			kbRelease(reKey); GetAsyncKeyState(reKey);
			continue;
		}
		if (GetAsyncKeyState(VK_PAUSE)) { 
			if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) { strand.clear(); if (ignoreEsc) kb(VK_ESCAPE); prints(); continue; }
			if (strand.substr(0, 1) == L"<") strand = L"<"; else strand.clear();
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
				getRGB();
				out(tail); continue;
			}
			GetAsyncKeyState(65); if (GetAsyncKeyState(65)) {//esc + a: <app:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				wstring s = tail; getApp(); tail = s; continue;
			}
			GetAsyncKeyState(VK_OEM_PLUS); if (GetAsyncKeyState(VK_OEM_PLUS)) {//esc + plus: repeat
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				wstring t = tail;
				if (EscEqualAutoBs) { kb(VK_BACK);  GetAsyncKeyState(VK_BACK); }
				out(t); continue;
			}
			GetAsyncKeyState(0xBC); if (GetAsyncKeyState(0xBC)) {//esc + ,
				if (EscCommaAutoBs) { kb(VK_BACK);  GetAsyncKeyState(VK_BACK); }
				if (strand.substr(0, 1) == L"<" && close_ctrl_mode && strand.length() >= 1) {
					if (strand == L"<")continue;
					strand.append(L">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); scanDb();
					if (strand > L"") strand.clear();
					if (strand == L"") prints();
					continue;
				}
				else { 
					if (strand.substr(0, 1) == L"<") { strand.clear(); prints(); continue; }
					if (strand.substr(0, 1) != L"<" && close_ctrl_mode && strand.length() > 0) {
						strand.append(L">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); scanDb();
						if (strand > L"") strand.clear();
						if (strand == L"") prints();
						continue;
					}
					clearAllKeys(); strand = L"<"; prints(); continue;
				}
			}
			GetAsyncKeyState(0x58); if (GetAsyncKeyState(0x58)) { if (enableEscX) return 0; } //esc + x
			GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) {//esc + h
				if (EscHAutoBs) kb(VK_BACK);
				GetAsyncKeyState(VK_ESCAPE); toggle_visibility(); 
				if (showStrand && !qScanOnly) wcout << OutsTemplate << strand << '\n'; 
				continue; 
			}
			if (!ignoreEsc) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key(L"~"); }
			continue;
		}
		//if (!ignorePrintScreen)if (GetAsyncKeyState(VK_SNAPSHOT)) { key(PrintScreen_Key); continue; }
		if (qScanOnly && strand.substr(0, 1) != L"<") continue;
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