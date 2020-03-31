// @dnaspider

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>
using namespace std;

#pragma region global_var
bool sleep = 1;
bool esc_pressed;
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
string database = R"(C:\dna\db.txt)";
string settings = R"(C:\dna\se.txt)";
int frequency = 150; //>> ms response -> vk_
int speed = 0; //<< 
short reKey = VK_SCROLL; //repeat
short cKey = VK_RCONTROL; //< 163 
string strand = ""; //>> supply
string tail = ""; //strand:tail
string re = "";//repeat clone
bool showStrand = true; //cout <<
bool showOuts = false; //cout << 
bool showIntro = false;
bool showSettings = false;
string star_num; //*#
string qq; //<x>
string qp; //<x:#>
string qx, qy; //<xy:#,#>
auto qxc = 0;//<rp>
auto qyc = 0;
bool shft = false;
size_t i = 0;
bool close_ctrl_mode = true; //x>, x:, x- 
bool clear_after_stock = true; //<se, <db
bool SlightPauseInBetweenConnects = false;
string OutsTemplate = "strand: ";
bool EscCommaAutoBs = true;
bool EscEqualAutoBs = true;
string codes = ""; //tail re
bool EscHAutoBs = true;
bool AutoBs_RepeatKey = 0;
bool SeHotReload_CtrlS=1;
bool SeDbClearStrand_CtrlS=1;
bool assume = 0;
#pragma endregion

#pragma region global_sub
string check_if_num(string &s) {
	if (assume) return s;
	if (s > "") {
		for (size_t t = 0; t < s.length(); ++t) {//!0-9
			if (s[0] == ' ') {
				if (s.length() == 1) {
					s = ""; return s;
				}
				s = s.substr(1, s.length()); --t;
				continue;
			}//rem ws
			if (t == 0 && (s[0] == 45 || s[0] == 43) && s.length() != 1) continue; //-+
			if (!(s[t] >= 48 && s[t] <= 57)) { s = ""; return s; }
		}
	}
	else s = "";
	return s;
}

void rei() { i += qq.find(">"); }

void kb(CHAR b) {//out char
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE;
	if (VkKeyScan(b) == -1) { ip[0].ki.wScan = b; ip[0].ki.wVk = 0; }
	else { ip[0].ki.wVk = VkKeyScan(b); }
	ip[1] = ip[0]; ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(ip[0]));
}

void kb1(string b) {//alt codes, emoji
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.dwFlags = KEYEVENTF_UNICODE; //cout << "hex: " << (unsigned)strtoull(b.c_str(), nullptr, 16) << endl;
	ip[0].ki.wScan = (unsigned)strtoull(b.c_str(), nullptr, 16); ip[0].ki.wVk = 0;//(unsigned)stoull(b);
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
	if (key == MOUSEEVENTF_HWHEEL && qq.substr(0,3)=="<ls") ip.mi.mouseData = -150;
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

void prints() { if (showStrand) cout << OutsTemplate << strand << '\n'; }

bool qqb(string s) {
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
	cout << database << "\n";
	ifstream f(database); string cell;
	SetConsoleOutputCP(CP_UTF8); while (getline(f, cell)) { cout << cell << endl; }
	f.close(); cout << endl;
}

void scanDb(); void conn() {//<connect:>	
	bool con = false; string qqs = qq.substr(0, qq.find(">") + 1);
	if (qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		if (qqs.substr(qqs.length() - 2, 2) == ":>" || qqs.substr(qqs.length() - 2, 2) == "->") {
			con = true;
		}
	}
	if (con) {
		ifstream f(database); string cell; while (getline(f, cell)) {
			if (cell.substr(0, 4) == "<'''") break;
			if (qqs == cell.substr(0, qqs.length())) { //<h:> | <h->
				string qqc = qq.substr(0, qq.find(">"));
				tail = qq.replace(qq.find(qqc + ">"), qqc.length() + 1, cell.substr(cell.substr(0, qqc.length()).length() + 1, cell.length()));
				if (SlightPauseInBetweenConnects) Sleep(150);
				strand.clear(); f.close(); 
				i = -1;
				if (speed > 0) sleep = 0;
				re = " ";//codes
				return;
			}
		}f.close(); printq();
	}
	else printq();
}

void kbPress(string s, short key) {
	string n = s;
	if (qq.find(">") == std::string::npos) { printq(); return; }
	if (qq[n.length()] == '>') star_num = "1";
	else {
		if (qq.substr(qq.find(">") - 1, 1) == ":" || qq.substr(qq.find(">") - 1, 1) == "-") { conn(); return; }
		n = qq.substr(n.length(), qq.find(">") - n.length());
		if (n > "") {
			if (n[0] == '*') n = n.substr(1, n.length()); //case: <f1*
			n = check_if_num(n);
			if (n == "") { printq(); return; }
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
		if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; GetAsyncKeyState(VK_PAUSE); } else { pause_resume = 1; } }
		if (pause_resume) { --j; Sleep(frequency); continue; }
		if (s == "<,*") Sleep(CommaSleep);
		else if (s == "<lc") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
		else if (s == "<rc") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
		else if (s == "<mc") { mouseEvent(MOUSEEVENTF_MIDDLEDOWN); mouseEvent(MOUSEEVENTF_MIDDLEUP); }
		else if (s == "<ls" || s == "<rs") mouseEvent(MOUSEEVENTF_HWHEEL);
		else SendInput(2, ip, sizeof(ip[0]));
		//switch (s[2]) {
		//case '*': Sleep(CommaSleep); break;
		//case 'c':
		//	if (s == "<lc") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
		//	else if (s == "<rc") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
		//	else if (s == "<mc") { mouseEvent(MOUSEEVENTF_MIDDLEDOWN); mouseEvent(MOUSEEVENTF_MIDDLEUP); }
		//	break;
		//case 's':
		//	if (s == "<bs" || s == "<esc" || s == "<ps") SendInput(2, ip, sizeof(ip[0]));
		//	else if (s == "<ls" || s == "<rs") mouseEvent(MOUSEEVENTF_HWHEEL);
		//	break;
		//default: SendInput(2, ip, sizeof(ip[0]));
		//}
		if (speed > 0 && stoi(star_num) != j + 1) Sleep(speed);
	}
	rei();
}

void out(string ai) { re = ">" + ai; strand.clear(); scanDb(); re.clear(); }

void calc() {
	string t = tail;
	qq = to_string(ic) + qq.substr(qq.find(">") + 1, qq.length());
	out(qq);
	tail = t;
	i = tail.length();
}

void loadSe() {
	ifstream f(settings); if (!f) { cout << settings << " not found!\n"; return; }
	string cell; while (getline(f, cell)) {
		string se = cell.substr(0, cell.find(":") + 1);
		string v = (cell.substr(cell.find(":") + 1));
		if (v[0] == ' ') v = v.substr(1, v.length());
		int x = 0; for (size_t i = 0; i <= se.length(); ++i) x += se[i];
		auto er = [se, v]() { cout << "Error in " << settings << " [" << se << " " << v << "]" << endl; };
		switch (x) {
			case 680://Assume:
				{ if (v == "1" || v == "0") assume = stoi(v); else er(); } break;
			case 1095://ShowStrand:
				{ if (v == "1" || v == "0") showStrand = stoi(v); else er(); } break;
			case 847://Database:
				{ if (v.length() > 0) database = v.substr(0); else er(); } break;
			case 1313://OutsTemplate:
				OutsTemplate = v.substr(0); break;
			case 1354://CloseCtrlMode:
				{ if (v == "1" || v == "0") close_ctrl_mode = stoi(v); else er(); } break;
			case 1659://CtrlScanOnlyMode:
				{ if (v == "1" || v == "0") qScanOnly = stoi(v); else er(); } break;
			case 1677://StrandLengthMode:
				{ if (v=="1" || v == "0") strandLengthMode = stoi(v); else er(); } break;
			case 1288://StrandLength:
				{ if (check_if_num(v) != "") strandLength = stoi(v); else er(); } break;
			case 956://Ignore_A-Z:
				{ if (v == "1" || v == "0") ignoreAZ = stoi(v); else er(); } break;
			case 915://Ignore_0-9:
				{ if (v == "1" || v == "0") ignore09 = stoi(v); else er(); } break;
			case 1172://StartHidden:
				{ if (v == "1" || v == "0") startHidden = stoi(v); else er(); } break;
			case 760://CtrlKey:
				{ if (check_if_num(v) > "") cKey = stoi(v); else er(); } break;
			case 999://ShowIntro:
				{ if (v == "1" || v == "0") showIntro = stoi(v); else er(); } break;
			case 1324://ShowSettings:
				{ if (v == "1" || v == "0") showSettings = stoi(v); else er(); } break;
			case 1004://Frequency:
				{ if (check_if_num(v) != "") frequency = stoi(v); else er(); } break;
			case 964://RepeatKey:
				{ if (check_if_num(v) != "") reKey = stoi(v); else er(); } break;
			case 1649://AutoBs_RepeatKey:
				{ if (v == "1" || v == "0") AutoBs_RepeatKey = stoi(v); else er(); } break;
			case 902://ShowOuts:
				{ if (v == "1" || v == "0") showOuts = stoi(v); else er(); } break;
			case 2699://ClearStrandAfterStockCtrls:
				{ if (v == "1" || v == "0") clear_after_stock = stoi(v); else er(); } break;
			case 2913://SlightPauseInBetweenConnects:
				{ if (v == "1" || v == "0") SlightPauseInBetweenConnects = stoi(v); else er(); } break;
			case 2339://StockInterfaceControls:
				{ if (v == "1" || v == "0") StockInterfaceControls = stoi(v); else er(); } break;
			case 1098://AutoBs_EscH: //Ignore_F1-F12:
				{	if (v == "1" || v == "0") {
						if (se == "AutoBs_EscH:") EscHAutoBs = stoi(v);
						else if (se == "Ignore_F1-F12:") ignoreF1s = stoi(v);
					}
					else er();
				} break;
			case 1519://AutoBs_EscComma:
				{ if (v == "1" || v == "0") EscCommaAutoBs = stoi(v); else er(); } break;
			case 1530://AutoBs_EscEqual:
				{ if (v == "1" || v == "0") EscEqualAutoBs = stoi(v); else er(); } break;
			case 1723://SeHotReload_CtrlS:
				{ if (v == "1" || v == "0") SeHotReload_CtrlS = stoi(v); else er(); } break;
			case 2098://SeDbClearStrand_CtrlS:
				{ if (v == "1" || v == "0") SeDbClearStrand_CtrlS = stoi(v); else er(); } break;
			case 1257://Ignore_Space:
				{ if (v == "1" || v == "0") ignoreSpace = stoi(v); else er(); } break;
			case 1403://Ignore_Arrows:
				{ if (v == "1" || v == "0") ignoreArrows = stoi(v); else er(); } break;
			case 1048://Ignore_Esc:
				{ if (v == "1" || v == "0") ignoreEsc = stoi(v); else er(); } break;
			case 1044://Ignore_Tab:
				{ if (v == "1" || v == "0") ignoreTab = stoi(v); else er(); } break;
			case 1275://Ignore_Enter:
				{ if (v == "1" || v == "0") ignoreEnter = stoi(v); else er(); } break;
			case 1156://Ignore_Caps:
				{ if (v == "1" || v == "0") ignoreCaps = stoi(v); else er(); } break;
			case 1351://Ignore_LShift:
				{ if (v == "1" || v == "0") ignoreLShift = stoi(v); else er(); } break;
			case 1357://Ignore_RShift:
				{ if (v == "1" || v == "0") ignoreRShift = stoi(v); else er(); } break;
			case 1130://Ignore_LAlt:
				{ if (v == "1" || v == "0") ignoreLAlt = stoi(v); else er(); } break;
			case 1136://Ignore_RAlt:
				{ if (v == "1" || v == "0") ignoreRAlt = stoi(v); else er(); } break;
			case 1246://Ignore_LCtrl:
				{ if (v == "1" || v == "0") ignoreLCtrl = stoi(v); else er(); } break;
			case 1252://Ignore_RCtrl:
				{ if (v == "1" || v == "0") ignoreRCtrl = stoi(v); else er(); } break;
			case 1856://Ignore_GraveAccent:
				{ if (v == "1" || v == "0") ignoreGraveAccent = stoi(v); else er(); } break;
			case 1289://Ignore_Minus:
				{ if (v == "1" || v == "0") ignoreMinus = stoi(v); else er(); } break;
			case 1269://Ignore_Equal:
				{ if (v == "1" || v == "0") ignoreEqual = stoi(v); else er(); } break;
			case 1541://Ignore_LBracket:
				{ if (v == "1" || v == "0") ignoreLBracket = stoi(v); else er(); } break;
			case 1547://Ignore_RBracket:
				{ if (v == "1" || v == "0") ignoreRBracket = stoi(v); else er(); } break;
			case 1673://Ignore_Backslash:
				{ if (v == "1" || v == "0") ignoreBackslash = stoi(v); else er(); } break;
			case 1702://Ignore_Semicolon:
				{ if (v == "1" || v == "0") ignoreSemicolon = stoi(v); else er(); } break;
			case 1291://Ignore_Quote:
				{ if (v == "1" || v == "0") ignoreQuote = stoi(v); else er(); } break;
			case 1258://Ignore_Comma:
				{ if (v == "1" || v == "0") ignoreComma = stoi(v); else er(); } break;
			case 1376://Ignore_Period:
				{ if (v == "1" || v == "0") ignorePeriod = stoi(v); else er(); } break;
			case 2029://Ignore_Forwardslash:
				{ if (v == "1" || v == "0") ignoreForwardslash = stoi(v); else er(); } break;
			case 1170://Ignore_Menu:
				{ if (v == "1" || v == "0") ignoreMenuKey = stoi(v); else er(); } break;
			case 1346://Ignore_NumPad:
				{ if (v == "1" || v == "0") ignoreNumPad = stoi(v); else er(); } break;
			case 934://Exit_EscX:
				{ if (v == "1" || v == "0") enableEscX = stoi(v); else er(); } break;
			//case 1657://Ignore_MediaKeys:
		}
	}
	f.close();
 }

void printApi() {
	cout << "API\n"; if (!StockInterfaceControls) { cout << "<db>  Show database. " << database << " | db.txt e.g., <d><db>\n<se>  Show, load settings. " << settings << " | db.txt e.g., <s><se>\n<v>  Visibility | db.txt e.g., <v><v>\n"; }  cout << "<ms:1><,1><sleep:1>  1ms sleep\n<,>  " << CommaSleep << "ms sleep | se.txt e.g., CommaSleep:150 | db.txt e.g., <test><,><,*3>\n<xy:0,0>  Move pointer (Esc + P to get)\n<x:><y:>  Current position +/- value. E.g., <x:-1>\n<rp> or <XY>  Return pointer\n<XY:>  Set. E.g., <XY:0,0><XY>\n<lc><rc><mc><lh><rh><mh><lr><rr><mr>  Left, right, middle -> click, hold, release\n<ls><rs>  Left, right scroll\n<ctrl><shift><alt><win>  Hold key\n<ctrl-><shift-><alt-><win->  Release key\n<up><right><down><left><delete><esc><bs><home><end><space><tab><enter>  Press key\n<bs*2>  Press twice\n<menu>  Press Menu key\n<ins>  Press Insert\n<ps>  Press Print Screen\n<pu><pd>  Press Page Up, Page Down\n<f1>  Press F1 (F1-F12)\n<app:>  Set app to foreground. E.g., <app:Calculator>\n<App:>  Continue if app in foreground.\n<yesno:>  Verify message. E.g., <yesno:Continue?>\n<beep>  Alert sound\n<a:>  Alt codes. E.g., <a:9201>\n<speed:>  Output. E.g., <speed:150>\n<+:><-:><*:></:><%:>  Calc. E.g., <+:1>, <+:-1>\n<+>  Clone. E.g., <*:7><+>\n<'><''><'''>  Ignore. E.g., <'bs><''rest of line><'''rest of db>\n<rgb:red,green,blue,*,ms:333>  Continue if rgb in xy (Esc + R to get). E.g., <xy:0,0><rgb:255,255,255><+:1>\n<RGB:>  Continue if RGB in XY location. db.txt e.g., test-><XY:0,0><RGB:255,255,255>1\n<rand:><Rand><rand><Rand:>  Print random #, A-Z, a-z, or A-Za-z. E.g. <rand:0,1><rand:>, <Rand>, <rand>, <Rand:>";
	if (showIntro) cout << "\nAPI's are placed to right of the first :, -, >, ->, or :> of each line in db.txt\ndb.txt e.g., test-<enter>\nSave example to db.txt then clear strand by toggling Right_Ctrl, Backspace, or Shit + Pause_Break. Inside a text area, press T E S T to run (strand: test).\n";
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
			cout << "<d b:  Change Database: " << database << endl;
		}
		cout << "Hold RCtrl LCtrl or Esc on startup:  Change < key" << endl;
		cout << "Hold O on startup:  ShowStrand, ShowOuts: 1" << endl;
		//cout << "Hold Q on startup:  CtrlScanOnlyMode: 1" << endl;
		//cout << "Hold S on startup:  ShowStrand: 1" << endl;
		cout << endl;
	}
}

void printSe() {
	loadSe();
	if (showSettings) {
		cout << settings << endl;  ifstream f(settings); if (f.fail()) { cout << "Copy to " << settings; cout << endl; }
		cout << "ShowSettings: " << showSettings << endl;
		cout << "ShowIntro: " << showIntro << endl;
		cout << "ShowStrand: " << showStrand << endl;
		cout << "ShowOuts: " << showOuts << endl;
		cout << "OutsTemplate: " << OutsTemplate << endl;
		cout << "Database: " << database << endl;
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

void getRGB() {
	POINT pt; GetCursorPos(&pt); COLORREF color; HDC hDC;
	hDC = GetDC(NULL);
	if (hDC != NULL) {
		color = GetPixel(hDC, pt.x, pt.y);
		if (color != CLR_INVALID) {
			string c = to_string(GetRValue(color)) + "," + to_string(GetGValue(color)) + "," + to_string(GetBValue(color));
			tail = "<shift>,<shift->rgb:" + c + ">";
			re = tail;
		}
	}
}

void scanDb() {
	if (close_ctrl_mode) {
		if (strand.length() == 0) {
			if (re == "")
				return;
		}
		else {
			if (strand.substr(strand.length() - 1) != ">")
				return;
		}

	}
	ifstream f(database); if (!f) { cout << database << " not found!\n"; return; }
	string cell; while (getline(f, cell)) { //cout << cell << endl;
		if (cell.substr(0, 4) == "<'''") break; //ignore db...
		if (re > "" || (close_ctrl_mode && cell.substr(0, strand.length()) == strand || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + ":" || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + "-" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + ":>" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + "->") || cell.substr(0, strand.length() + 1) == strand + ">" || cell.substr(0, strand.length() + 1) == strand + ":" || cell.substr(0, strand.length() + 1) == strand + "-" || (strandLengthMode && cell.substr(0, strandLength) == strand && cell.substr(0, 1) != "<") || close_ctrl_mode && strandLengthMode && strand.substr(0, 1) != "<" && cell.substr(0, strand.length() - 1) == strand.substr(0, strand.length() - 1)) { //found i>o, i:o, i-o, i:>o, i->o || i>o, i:o, i-o || io || io
			if (close_ctrl_mode && strand.length() > 0 && strand.substr(strand.length() - 1) == ">") strand = strand.substr(0, strand.length() - 1);
			if (re > "") {
				cell = re;
				if (re.substr(0, 20) == "><shift>,<shift->xy:") { POINT pt; GetCursorPos(&pt); string xy = to_string(pt.x) + "," + to_string(pt.y); cell = "><shift>,<shift->xy:" + xy + ">"; re = cell; if (showStrand) { cout << OutsTemplate << "<xy:" + xy + ">\n"; } }
				else if (re.substr(0, 21) == "><shift>,<shift->rgb:") { getRGB(); if (showStrand) { cout << OutsTemplate << "<" << tail.substr(16, tail.length()) << endl; } }
			}
#pragma region set_tail
			tail = re > "" ? re : cell.substr(strand.length(), cell.length() - strand.length());
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
				for (size_t t = 0; t < strand.length(); t++) { if (strand[t] == 60 || ((!ignoreMenuKey) && strand[t] == 63) || (!ignoreArrows) && (strand[t] == 76 || strand[t] == 85 || strand[t] == 82 || strand[t] == 68) || (!ignoreF1s) && (strand[t] == 33 || (strand[t] >= 35 && strand[t] <= 38) || (strand[t] >= 40 && strand[t] <= 43) || strand[t] == 64 || strand[t] == 94 || strand[t] == 95) || (!ignoreEsc && strand[t] == 126) || (!ignoreLShift && strand[t] == 83) || (!ignoreRShift && strand[t] == 72) || (!ignoreLAlt && strand[t] == 65) || (!ignoreRAlt && strand[t] == 77) || (!ignoreLCtrl && strand[t] == 67) || (!ignoreRCtrl && strand[t] == 79) || (!ignoreCaps && strand[t] == 80)) { continue; } kb(VK_BACK); } GetAsyncKeyState(VK_BACK);//exclude non bs: < LURD !@#$%^&*()_+ ~ S H A M C O P
				codes = tail;
				break;
			default:
				codes = cell;
			}

			if (showOuts) cout << "found: " << cell << "\ntail: " << tail << endl;
#pragma endregion
			if (tail.find("<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
			f.close();
			for (i = 0; i < tail.length(); ++i) {
				if (speed > 0) { if (sleep) { Sleep(speed); } sleep = 1; }
				GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE) || esc_pressed) { esc_pressed = 0; pause_resume = 0; break; }if (GetAsyncKeyState(VK_PAUSE)) { if (pause_resume) { pause_resume = 0; } else { pause_resume = 1; } }// int m = MessageBoxA(0, "Resume?", "dnaspider", MB_YESNO); if (m != IDYES) { break; } }
				if (pause_resume) { --i; Sleep(frequency); continue; }

				string ctail = tail.substr(i, 1);//extracted char from tail
				if (showOuts) { cout << "ctail: " << ctail << endl; }
				switch (ctail[0]) {
				case'<':
					qq = tail.substr(i, tail.length() - i); //<test>
					if (showOuts) { cout << "qq: " << qq << endl; }
					if (qq.find(":") != std::string::npos) { //<test:#>
						qp = qq.substr(qq.find(":") + 1, qq.find(">") - qq.find(":") - 1);//#
						qx = qp.substr(0, qp.find(","));//x <xy:#,#>
						qy = qp.substr(qp.find(",") + 1, qp.find(">") - qp.find(",") - 1);//y
						//cout << "qp: " << qp  << endl; cout << "qx: " << qx << endl; cout << "qy: " << qy << endl;
					}
					switch (qq[1]) {
					case'+': //calc
						if (qqb("<+>")) {//repeat#
							calc();
							break;
						}
						else if (qqb("<+:")) {//calc +
							if (check_if_num(qp) == "") { printq(); continue; }
							ic += stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'-':
						if (qqb("<-:")) {//-
							if (check_if_num(qp) == "") { printq(); continue; }
							ic -= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'*':
						if (qqb("<*:")) {//*
							if (check_if_num(qp) == "") { printq(); continue; }
							ic *= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'/':
						if (qqb("</:")) {//divide
							if (check_if_num(qp) == "" || stoi(qp) <= 0) { printq(); continue; }
							ic /= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case'%':
						if (qqb("<%:")) {//%
							if (check_if_num(qp) == "") { printq(); continue; }
							ic %= stoi(qp);
							calc();
							break;
						}
						else printq();
						break;
					case',':
						if (qqb("<,*")) kbPress("<,*", VK_F7);//sleep150ms, vk_dud
						else if (qqb("<,")) { //<,#>
							string s = qq.substr(2, qq.find('>') - 2);
							if (s == "") s = to_string(CommaSleep);
							s = check_if_num(s);
							if (s=="") { printq(); break; }
							if (s > "" && stoi(s) >= 0 && s[0] != '+') { Sleep(stoi(s)); } else { printq(); break; };
							rei();
						}
						else printq();
						break;
					case'\'':
						if (qq.find(">") != string::npos && qqb("<''")) { i = tail.length(); break; }//<''ignore>...
						else if (qq.find(">") != string::npos && qqb("<'")) rei(); //<'comments>
						else printq();
						break;
					case'a':
						if (qqb("<alt>")) { kbHold(VK_LMENU); rei(); }
						else if (qqb("<alt->")) { kbRelease(VK_LMENU); rei(); }
						else if (qqb("<alt")) kbPress("<alt", VK_LMENU);
						else if (qqb("<a:")) {if (qp[0] == ' ') qp = qp.substr(1, qp.length()); kb1(qp); rei(); }//alt codes
						else if (qqb("<app:")) {//app activate
							DWORD pid; HWND h; 
							string a = qp, d = "1", x = d, m = "333", ms = m;//<app:a,x,ms>
							a = a.substr(0, a.find(","));
							if (a[0] == ' ') a = a.substr(1, a.length());
							if (qp.find(",") != string::npos) {
								x = qp.substr(qp.find(",") + 1);
								if (x.find(",") != string::npos) {
									ms = x.substr(x.find(",") + 1); if (check_if_num(ms) == "") ms = m;
									x = x.substr(0, x.find(","));
								}
								if (check_if_num(x) == "") x = d;
							}//cout << a << " " << x << " " << ms << endl;
							auto size{ 0 }, length{ stoi(x) };
							for (; size < length; size++) { //cout << size << " app:" << a << " *" << x << " " << ms << "ms" << endl; return;
								if (size >= length || GetAsyncKeyState(VK_ESCAPE)) { if (showOuts && size >= length) { cout << "Fail: <app:" << qp << ">\n"; } i = tail.length(); break; }
								h = FindWindowA(0, a.c_str()); GetWindowThreadProcessId(h, &pid);
								if (h) {
									if (IsIconic(h)) ShowWindow(h, SW_RESTORE);
									SetForegroundWindow(h);
									break; 
								}
								Sleep(stoi(ms));
							}
							if (size >= length || GetAsyncKeyState(VK_ESCAPE)) { i = tail.length(); break; }
							rei();
						}
						else conn();
						break;
					case 'A':
						if (qqb("<App:")) {//if app in foreground
							if (qp[0] == ' ') qp = qp.substr(1, qp.length());
							HWND h = GetForegroundWindow();	HWND h1 = FindWindowA(0, qp.c_str());
							if (h == h1) { rei(); continue; }
							else { if (showOuts) { cout << "fail: <App:" << qp << ">" << endl; } i = tail.length(); break; }
						}
						else conn();
						break;
					case'b':
						if (qqb("<bs")) kbPress("<bs", VK_BACK);
						else if (qqb("<beep>")) { cout << "\a" << endl; rei(); }
						else conn();
						break;
					case'c':
						if (qqb("<ctrl>")) { kbHold(VK_CONTROL); rei(); }
						else if (qqb("<ctrl->")) { kbRelease(VK_CONTROL); rei(); }
						else if (qqb("<ctrl")) kbPress("<ctrl", VK_CONTROL);
						else conn();
						break;
					case'd':
						if (qqb("<db>")) { printDb(); rei(); }
						else if (qqb("<down")) kbPress("<down", VK_DOWN);
						else if (qqb("<delete")) kbPress("<delete", VK_DELETE);
						else conn();
						break;
					case'e':
						if (qqb("<enter")) kbPress("<enter", VK_RETURN);
						else if (qqb("<end")) kbPress("<end", VK_END);
						else if (qqb("<esc")) kbPress("<esc", VK_ESCAPE);
						else conn();
						break;
					case'f':
						if (qqb("<f10")) kbPress("<f10", VK_F10);
						else if (qqb("<f11")) kbPress("<f11", VK_F11);
						else if (qqb("<f12")) kbPress("<f12", VK_F12);
						else if (qqb("<f1")) kbPress("<f1", VK_F1);
						else if (qqb("<f2")) kbPress("<f2", VK_F2);
						else if (qqb("<f3")) kbPress("<f3", VK_F3);
						else if (qqb("<f4")) kbPress("<f4", VK_F4);
						else if (qqb("<f5")) kbPress("<f5", VK_F5);
						else if (qqb("<f6")) kbPress("<f6", VK_F6);
						else if (qqb("<f7")) kbPress("<f7", VK_F7);
						else if (qqb("<f8")) kbPress("<f8", VK_F8);
						else if (qqb("<f9")) kbPress("<f9", VK_F9);
						else conn();
						break;
						//{
						//	int s = 0;
						//	for (size_t i = 2; i <= qq.length(); ++i) {
						//		s += qq[i];
						//		if (qq[i] == '*' || qq[i] == ' ' || qq[i] == '>')
						//			break;
						//	}
						//	switch (s) {
						//	case 111://1 + >
						//	case 91: //1 + *
						//	case 81: //1 + " " = 81
						//		if (qqb("<f11")) kbPress("<f11", VK_F11);
						//		else if (qqb("<f12")) kbPress("<f12", VK_F12);
						//		else kbPress("<f1", VK_F1); 
						//		break;	
						//	case 112: 
						//	case 92:
						//	case 82: kbPress("<f2", VK_F2); break;
						//	case 113:
						//	case 93:
						//	case 83: kbPress("<f3", VK_F3); break;
						//	case 114:
						//	case 94:
						//	case 84: kbPress("<f4", VK_F4); break;
						//	case 115: 
						//	case 95: 
						//	case 85: kbPress("<f5", VK_F5); break;
						//	case 116:
						//	case 96:
						//	case 86: kbPress("<f6", VK_F6); break;
						//	case 117:
						//	case 97:
						//	case 87: kbPress("<f7", VK_F7); break;
						//	case 118:
						//	case 98:
						//	case 88: kbPress("<f8", VK_F8); break;
						//	case 119:
						//	case 99:
						//	case 89: kbPress("<f9", VK_F9); break;
						//	case 110:
						//	case 90:
						//	case 129: kbPress("<f10", VK_F10); break;							
						//	default: conn();
						//	}
						//}
						//break;
					case'h':
						if (qqb("<home")) kbPress("<home", VK_HOME);
						else conn();
						break;
					case'i':
						if (qqb("<ins")) kbPress("<ins", VK_INSERT);
						else conn();
						break;
					case'l':
						if (qqb("<lc")) kbPress("<lc", VK_F7);//left click
						else if (qqb("<lh>")) {//left hold
							mouseEvent(MOUSEEVENTF_LEFTDOWN);
							rei();
						}
						else if (qqb("<lr>")) {//left release
							mouseEvent(MOUSEEVENTF_LEFTUP);
							rei();
						}
						else if (qqb("<left")) kbPress("<left", VK_LEFT);
						else if (qqb("<ls")) { kbPress("<ls", VK_F7); }//hscroll+
						else conn();
						break;
					case'm':
						if (qqb("<ms:")) if (check_if_num(qp) != "") { Sleep(stoi(qp));	rei(); }
						else printq();
						else if (qqb("<mc")) kbPress("<mc", VK_F7);//middle click
						else if (qqb("<mh>")) {//middle hold
							mouseEvent(MOUSEEVENTF_MIDDLEDOWN);
							rei();
						}
						else if (qqb("<mr>")) {//middle release
							mouseEvent(MOUSEEVENTF_MIDDLEUP);
							rei();
						}
						else if (qqb("<menu")) kbPress("<menu", VK_APPS);
						else conn();
						break;
					case'p':
						if (qqb("<ps")) kbPress("<ps", VK_SNAPSHOT);
						else if (qqb("<pu")) kbPress("<pu", VK_PRIOR);//pgup
						else if (qqb("<pd")) kbPress("<pd", VK_NEXT);//pgdn
						else conn();
						break;
					case'R':
					case'r':
						if (qqb("<rp>")) {//return pointer
							SetCursorPos(qxc, qyc);
							rei();
						}
						else if (qqb("<rand:") || qqb("<rand>") || qqb("<Rand>") || qqb("<Rand:")) {//<rand:0,1>
							int r = rand();
							char s = (qq[5] + qq[1]);
							string t = tail;
							switch (s) {
							case -84://':r': <rand:> #
								if (check_if_num(qx) != "" && check_if_num(qy) != "" && stoi(qy) > stoi(qx)) {
									r = qx == "0" ?
										rand() % (stoi(qy) + 1) :
										(rand() % (stoi(qy) + 1 - stoi(qx))) + stoi(qx);
								}
								out(to_string(r));
								tail = t;
								i = qq.find(">");
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
								case 65: out("A"); tail = t; i = qq.find(">"); break;
								case 66: out("B"); tail = t; i = qq.find(">"); break;
								case 67: out("C"); tail = t; i = qq.find(">"); break;
								case 68: out("D"); tail = t; i = qq.find(">"); break;
								case 69: out("E"); tail = t; i = qq.find(">"); break;
								case 70: out("F"); tail = t; i = qq.find(">"); break;
								case 71: out("G"); tail = t; i = qq.find(">"); break;
								case 72: out("H"); tail = t; i = qq.find(">"); break;
								case 73: out("I"); tail = t; i = qq.find(">"); break;
								case 74: out("J"); tail = t; i = qq.find(">"); break;
								case 75: out("K"); tail = t; i = qq.find(">"); break;
								case 76: out("L"); tail = t; i = qq.find(">"); break;
								case 77: out("M"); tail = t; i = qq.find(">"); break;
								case 78: out("N"); tail = t; i = qq.find(">"); break;
								case 79: out("O"); tail = t; i = qq.find(">"); break;
								case 80: out("P"); tail = t; i = qq.find(">"); break;
								case 81: out("Q"); tail = t; i = qq.find(">"); break;
								case 82: out("R"); tail = t; i = qq.find(">"); break;
								case 83: out("S"); tail = t; i = qq.find(">"); break;
								case 84: out("T"); tail = t; i = qq.find(">"); break;
								case 85: out("U"); tail = t; i = qq.find(">"); break;
								case 86: out("V"); tail = t; i = qq.find(">"); break;
								case 87: out("W"); tail = t; i = qq.find(">"); break;
								case 88: out("X"); tail = t; i = qq.find(">"); break;
								case 89: out("Y"); tail = t; i = qq.find(">"); break;
								case 90: out("Z"); tail = t; i = qq.find(">"); break;
								case 97: out("a"); tail = t; i = qq.find(">"); break;
								case 98: out("b"); tail = t; i = qq.find(">"); break;
								case 99: out("c"); tail = t; i = qq.find(">"); break;
								case 100: out("d"); tail = t; i = qq.find(">"); break;
								case 101: out("e"); tail = t; i = qq.find(">"); break;
								case 102: out("f"); tail = t; i = qq.find(">"); break;
								case 103: out("g"); tail = t; i = qq.find(">"); break;
								case 104: out("h"); tail = t; i = qq.find(">"); break;
								case 105: out("i"); tail = t; i = qq.find(">"); break;
								case 106: out("j"); tail = t; i = qq.find(">"); break;
								case 107: out("k"); tail = t; i = qq.find(">"); break;
								case 108: out("l"); tail = t; i = qq.find(">"); break;
								case 109: out("m"); tail = t; i = qq.find(">"); break;
								case 110: out("n"); tail = t; i = qq.find(">"); break;
								case 111: out("o"); tail = t; i = qq.find(">"); break;
								case 112: out("p"); tail = t; i = qq.find(">"); break;
								case 113: out("q"); tail = t; i = qq.find(">"); break;
								case 114: out("r"); tail = t; i = qq.find(">"); break;
								case 115: out("s"); tail = t; i = qq.find(">"); break;
								case 116: out("t"); tail = t; i = qq.find(">"); break;
								case 117: out("u"); tail = t; i = qq.find(">"); break;
								case 118: out("v"); tail = t; i = qq.find(">"); break;
								case 119: out("w"); tail = t; i = qq.find(">"); break;
								case 120: out("x"); tail = t; i = qq.find(">"); break;
								case 121: out("y"); tail = t; i = qq.find(">"); break;
								case 122: out("z"); tail = t; i = qq.find(">"); break;
								}
							}
						}
						else if (qqb("<rc")) kbPress("<rc", VK_F7);
						else if (qqb("<rh>")) {//right hold
							mouseEvent(MOUSEEVENTF_RIGHTDOWN);
							rei();
						}
						else if (qqb("<rr>")) {//right release
							mouseEvent(MOUSEEVENTF_RIGHTUP);
							rei();
						}
						else if (qqb("<right")) kbPress("<right", VK_RIGHT);
						else if (qqb("<rs")) { kbPress("<rs", VK_F7); }//hscroll-
						else if (qqb("<rgb:") || qqb("<RGB:")) { //<rgb:r,g,b,x,ms>
							string r, g, b, d = "1", x = d, m = "333", ms = m;
							r = qp.substr(0, qp.find(","));
							b = qp.substr(qp.find(",")+1);
							g = b.substr(0, b.find(","));
							b = b.substr(b.find(",") + 1);
							if (b.find(",") != string::npos) {//x,ms
								x = b; b = b.substr(0, b.find(","));
								x = x.substr(x.find(",") + 1);
								if (x.find(",") != string::npos) {
									ms = x.substr(x.find(",") + 1); if (check_if_num(ms) == "") ms = m;
									x = x.substr(0, x.find(",")); 
								}
								if (check_if_num(x) == "") x = d;
							}//cout << r << " " << g << " " << b << " " << x << " " << ms << endl;
							POINT pt; GetCursorPos(&pt);
							COLORREF color; HDC hDC;
							hDC = GetDC(NULL);
							color = (qq[1] == 'R') ? GetPixel(hDC, qxc, qyc) : GetPixel(hDC, pt.x, pt.y);//<RGB> get xy from <XY:> or current
							if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b)) {
								rei();//cout << "rgb\n";
							}
							else {
								auto size{ 0 }, length{stoi(x)};
								for (; size < length; size++) {
									if (size >= length || GetAsyncKeyState(VK_ESCAPE)) { if (showOuts && size >= length) { cout << "Fail: <rgb:" << qp << ">\n"; } i = tail.length(); break; }
									GetCursorPos(&pt);
									color = (qq[1] == 'R') ? GetPixel(hDC, qxc, qyc) : GetPixel(hDC, pt.x, pt.y);//<RGB> get xy from <XY:> or current
									if (color != CLR_INVALID && GetRValue(color) == stoi(r) && GetGValue(color) == stoi(g) && GetBValue(color) == stoi(b)) break;
									Sleep(stoi(ms));
								}
								if (size >= length || GetAsyncKeyState(VK_ESCAPE)) { i = tail.length(); break; }
								rei();
							}
						}
						else conn();
						break;
					case's':
						if (qqb("<se>")) { printSe(); rei(); }
						else if (qqb("<shift>")) { kbHold(VK_LSHIFT); rei(); }
						else if (qqb("<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
						else if (qqb("<shift")) kbPress("<shift", VK_LSHIFT);
						else if (qqb("<sleep:")) if (check_if_num(qp) != "") { Sleep(stoi(qp)); rei(); } else printq();
						else if (qqb("<space")) kbPress("<space", VK_SPACE);
						else if (qqb("<speed:")) if (check_if_num(qp) != "") { speed = stoi(qp); rei(); sleep = 0; } else printq();
						else conn();
						break;
					case't':
						if (qqb("<tab")) kbPress("<tab", VK_TAB);
						else conn();
						break;
					case'u':
						if (qqb("<up")) kbPress("<up", VK_UP);
						else conn();
						break;
					case 'v':
						if (qqb("<v>")) { toggle_visibility(); rei(); }
						else conn();
						break;
					case'w':
						if (qqb("<win>")) { kbHold(VK_LWIN); rei(); }
						else if (qqb("<win->")) { kbRelease(VK_LWIN); rei(); }
						else if (qqb("<win")) kbPress("<win", VK_LWIN);
						else conn();
						break;
					case'X':
					case'x':
						if (qqb("<xy:")) {
							SetCursorPos(stoi(qx), stoi(qy)); rei();
						}
						else if (qqb("<XY>")) {//return pointer
							SetCursorPos(qxc, qyc);
							rei();
						}
						else if (qqb("<XY:")) {//set return pointer
							qxc = stoi(qx); qyc = stoi(qy); rei();
						}
						else if (qqb("<x:")) {//x + or - 1px
							if (qp == "") { conn(); break; }
							if (check_if_num(qp) != "") {
								POINT pt; GetCursorPos(&pt);
								SetCursorPos(stoi(qp) + (int)(pt.x), (int)(pt.y));
								rei();
							}
							else printq();
						}
						else conn();
						break;
					case 'y':
						if (qqb("<yesno:")) {
							int m = MessageBoxA(0, qp.c_str(), "dnaspider", MB_YESNO);
							if (m == IDYES) { rei(); continue; }
							else { i = tail.length(); break; }
						}
						else if (qqb("<y:")) {//y + or - 1px
							if (qp == "") { conn(); break; }
							if (check_if_num(qp) != "") {
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
			if (strand > "" || re > "") {
				if (re == "" || re == " " || strandLengthMode) { re = ""; tail = codes; }
				clearAllKeys();
				strand.clear();
			}
			if (speed > 0)speed = 0;
			break;
		}
	}
	f.close();
	if (strand > "" && close_ctrl_mode && strand[0]=='<') { tail = strand.substr(1, strand.length() - 2); }//dbless repeat
}

void printXy() {
	POINT pt; GetCursorPos(&pt);
	if (strand == "x") { if (showOuts) cout << "xy: " << pt.x << "," << pt.y << endl; }
	else { out("<bs*2>"); out("><shift>,<shift->xy:" + to_string(pt.x) + "," + to_string(pt.y) + ">"); }
}

void printInterfaceCtrls() {
	string c; if (cKey == VK_CONTROL) c = "Ctrl"; else if (cKey == VK_LCONTROL) c = "LCtrl"; else if (cKey == VK_RCONTROL) c = "RCtrl"; else if (cKey == VK_ESCAPE) c = "Esc";
	cout << "Interface" << endl;
	if (StockInterfaceControls) {
		string se = qScanOnly ? "<se" : "se"; cout << se << ":  Settings (Press " << (qScanOnly ? c+" S E" : "S E") << " to load " << settings << ")\n";
		if (qScanOnly)se = "<db"; else se = "db"; cout << se << ":  Database" << endl;
	}
	cout << "Esc:  Stop" << endl;
	if (enableEscX) cout << "Esc + X:  Exit" << endl;
	cout << "Esc + H:  Toggle visibility" << endl;
	cout << c << ":  Toggle <" << endl;
	cout << "Esc + Comma:  Toggle <" << endl;
	cout << "Pause Break:  Clear strand | Pause/Resume" << endl;
	cout << "Shift + Pause Break:  Clear strand" << endl;
	if (StockInterfaceControls) { cout << "<odb:  Open database: " << database << endl;	cout << "<ose:  Open settings: " << settings << endl; }
	(StockInterfaceControls) ? cout << "<xy or Esc + P" : cout << "Esc + P"; cout << ":  <xy:>" << endl;
	cout << "Esc + R:  <rgb:>" << endl;
	(reKey == 145) ? c = "Scroll Lock" : c = "repeatKey: " + reKey; cout << c << " or Esc + Equal:  Repeat" << endl;
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

void key(string k) {
	strand.append(k);
	if (strandLengthMode && (int)strand.length() > strandLength && strand.substr(0, 1) != "<") { strand = strand.substr(strand.length() - strandLength); }
	prints();
	if (close_ctrl_mode && strand.find(">") != std::string::npos && strand.substr(strand.length() - 1) != ">") { strand.clear(); prints(); return; }
	scanDb();
	if (strand > "" && StockInterfaceControls) {
		if (strand == "db" || strand == "<db") { printDb(); if (clear_after_stock)strand.clear(); }
		if (strand == "se" || strand == "<se") { printSe(); if (clear_after_stock)strand.clear(); }
		if (strand == "x" || strand == "<xy") { printXy(); }
		if (strand == "<odb") { out("<win>r<win-><,>" + database + "<enter>"); }
		if (strand == "<ose") { out("<win>r<win-><,>" + settings + "<enter>"); }
		if (!ignoreSpace) {
			if (strand == "<q s") { qScanOnly = !qScanOnly; cout << "<q s: " << qScanOnly << endl; strand.clear(); }
			if (strand == "<s lm") { strandLengthMode = !strandLengthMode; cout << "Strand length mode: " << strandLengthMode << endl; strand.clear(); if (strandLengthMode) { cout << "Strand length: " << strandLength << endl; } }
			if (strand == "<s le") { kb(VK_ESCAPE); int sl; cout << "Enter new strand length:" << endl;  cin >> sl; if (sl > 0) { strandLength = sl; } else { return; } clearAllKeys(); cout << "strand length: " << strandLength << endl; strand.clear(); }
			if (strand == "<r e") { kb(VK_ESCAPE); int sl; cout << "Enter new repeat key:" << endl;  cin >> sl; if (sl > 0) { reKey = sl; } else { return; } clearAllKeys(); cout << "repeat key: " << reKey << endl; strand.clear(); }
			if (strand == "<q k") { kb(VK_ESCAPE); int sl; cout << "Enter new < key:" << endl;  cin >> sl; if (sl > 0) { cKey = sl; } else { return; } clearAllKeys(); cout << "< key: " << cKey << endl; strand.clear(); }
			if (strand == "<f r") { kb(VK_ESCAPE); int sl; cout << "Enter new frequency:" << endl;  cin >> sl; if (sl > 0) { frequency = sl; } else { return; } clearAllKeys(); cout << "frequency: " << frequency << endl; strand.clear(); }
			if (strand == "<d b") { kb(VK_ESCAPE); string sl; cout << "Enter new database:" << endl;  cin >> sl; if (sl > "") { database = sl; } else { return; } clearAllKeys(); cout << "database: " << database << endl; strand.clear(); }
			if (strand == "<s s") { showStrand = !showStrand; cout << "<s s: " << showStrand << endl; strand.clear(); }
			if (strand == "<c q") { close_ctrl_mode = !close_ctrl_mode; cout << "<c q: " << close_ctrl_mode << endl; strand.clear(); }
			if (strand == "<s o") { showOuts = !showOuts; cout << "<s o: " << showOuts << endl; strand.clear(); }
		}
	}
	else if (strand == "") prints();
}

#pragma endregion

int main() {//cout << "@dnaspider\n\n";
#pragma region initial_startup
	if (CreateDirectory("c:/dna", NULL)) {//L"c:/dna"
		showIntro=1;showOuts=1;cKey=VK_CONTROL;ignore09=0;SlightPauseInBetweenConnects=1;StockInterfaceControls=1;//minimalist se.txt
		cout << database << " not found.\nPress [1] to auto create.\n\n";
		for (;; Sleep(150)) { if (GetAsyncKeyState(VK_ESCAPE)) { RemoveDirectory("c:/dna"); Sleep(150); break; }if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
		showOuts = false; ofstream fd(database); fd << "h-Hello\n<e->Enjoy\n<x:><bs><e->!\n\nGetting Started:\nPress H (strand: h),\nCTRL E (strand: < e), or\nCTRL X (strand: < x)\nin a text area to run.\n\nTip:\nClear strand first by toggling\nCTRL, BACKSPACE, or \nSHIFT + PAUSE_BREAK.\n\nPress keys independently\n(RIGHT_CTRL, release RIGHT_CTRL, X)."; fd.close(); ofstream fs(settings); fs << "ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nShowOuts: 0\nOutsTemplate: " << OutsTemplate << "\nDatabase: " << database << "\nCloseCtrlMode: 0\nCtrlScanOnlyMode: 0\nCtrlKey: 163\nStrandLengthMode: 0\nStrandLength: 3\nRepeatKey: 145\nAutoBs_RepeatKey: 0\nFrequency: 150\nIgnore_A-Z: 0\nIgnore_0-9: 0\nIgnore_Space: 0\nIgnore_F1-F12: 1\nIgnore_Arrows: 1\nIgnore_Esc: 1\nIgnore_Tab: 1\nIgnore_Enter: 1\nIgnore_Caps: 1\nIgnore_LShift: 1\nIgnore_RShift: 1\nIgnore_LAlt: 1\nIgnore_RAlt: 1\nIgnore_LCtrl: 1\nIgnore_RCtrl: 1\nIgnore_GraveAccent: 1\nIgnore_Minus: 1\nIgnore_Equal: 1\nIgnore_LBracket: 1\nIgnore_RBracket: 1\nIgnore_Backslash: 1\nIgnore_Semicolon: 1\nIgnore_Quote: 1\nIgnore_Comma: 1\nIgnore_Period: 1\nIgnore_Forwardslash: 1\nIgnore_Menu: 1\nIgnore_NumPad: 1\nStartHidden: 0\nStockInterfaceControls: 1\nClearStrandAfterStockCtrls: 1\nSlightPauseInBetweenConnects: 1\nAutoBs_EscH: 1\nAutoBs_EscComma: 1\nAutoBs_EscEqual: 1\nCommaSleep: 150\nSeHotReload_CtrlS: 1\nSeDbClearStrand_CtrlS: 1\nExit_EscX: 1\nAssume: 0"; fs.close(); out("<win>r<win-><app:run>" + settings + "<enter><ms:1500><win>r<win-><app:run>" + database + "<enter>"); re = ""; tail = ""; strand.clear();
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
		if (SeHotReload_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowA(0, "se.txt - Notepad") == GetForegroundWindow() || FindWindowA(0, "se.txt - Visual Studio Code") == GetForegroundWindow())) { HWND np = FindWindowA(0, "se.txt - Notepad"), vsc = FindWindowA(0, "se.txt - Visual Studio Code"); HWND HotReload = GetForegroundWindow(); if (np == HotReload || vsc == HotReload) { loadSe(); if (SeDbClearStrand_CtrlS) { clearAllKeys(); strand.clear(); if (showStrand) { prints(); } continue; } else if (!ignoreAZ) key("s"); continue; } }//lctrl+s hot reload
		if (SeDbClearStrand_CtrlS && GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(83) && (FindWindowA(0, "db.txt - Notepad") == GetForegroundWindow() || FindWindowA(0, "db.txt - Visual Studio Code") == GetForegroundWindow())) { strand.clear(); if (showStrand) { prints(); } continue; }//clear
		if (GetAsyncKeyState(VK_BACK)) {
			strand = strand.substr(0, strand.length() - 1);
			prints(); continue;
		}
		if (GetAsyncKeyState(cKey)) {//toggle <
			if (strand.substr(0, 1) == "<") {
				if (close_ctrl_mode) {//<x>	
					if (strand.find(">") != std::string::npos) strand.clear();
					else {
						if (strand.length() > 1) {
							//if (cKey >= 160 && cKey <= 165 || cKey == 27) { Sleep(115); } key(">");
							if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(115); kbRelease(cKey); GetAsyncKeyState(cKey); } key(">");
							if (strand > "") { strand.clear(); prints(); }
							continue;
						}
						else strand.clear();
					}
				}
				else strand.clear();
			}
			else if (close_ctrl_mode && strand.length() > 0 && strand.find(">") == std::string::npos) {//x>
				//strand.append(">"); if (cKey >= 160 && cKey <= 165 || cKey == 27) { Sleep(115); } scanDb();
				strand.append(">"); if (cKey == VK_RCONTROL || cKey == VK_LCONTROL || cKey == VK_LSHIFT || cKey == VK_RSHIFT || cKey == VK_LMENU || cKey == VK_RMENU || cKey == VK_ESCAPE) { Sleep(115); kbRelease(cKey); GetAsyncKeyState(cKey); } scanDb();
				if (strand > "") { prints(); strand.clear(); }
			}//reg
			else {
				if (close_ctrl_mode && strand.length() > 0) strand.clear();
				else { clearAllKeys(); strand = "<"; }
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
			if (strand.substr(0, 1) == "<") strand = "<"; else strand.clear(); 
			continue; 
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			GetAsyncKeyState(80); if (GetAsyncKeyState(80)) {//esc + p: <xy:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				re = "<shift>,<shift->xy:";
				out(re); continue;
			}
			GetAsyncKeyState(82); if (GetAsyncKeyState(82)) {//esc + r: <rgb:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				kb(VK_BACK); GetAsyncKeyState(VK_BACK);
				getRGB();
				out(tail); continue;
			}
			GetAsyncKeyState(VK_OEM_PLUS); if (GetAsyncKeyState(VK_OEM_PLUS)) {//esc + plus: repeat
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				string t = tail;
				if (EscEqualAutoBs) { kb(VK_BACK);  GetAsyncKeyState(VK_BACK); }
				out(t); continue;
			}
			GetAsyncKeyState(0xBC); if (GetAsyncKeyState(0xBC)) {//esc + ,
				if (EscCommaAutoBs) { kb(VK_BACK);  GetAsyncKeyState(VK_BACK); }
				if (strand.substr(0, 1) == "<" && close_ctrl_mode && strand.length() >= 1) {
					if (strand == "<")continue;
					strand.append(">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); scanDb();
					if (strand > "") strand.clear();
					if (strand == "") prints();
					continue;
				}
				else { 
					if (strand.substr(0, 1) == "<") { strand.clear(); prints(); continue; }
					if (strand.substr(0, 1) != "<" && close_ctrl_mode && strand.length() > 0) {
						strand.append(">"); prints(); kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); scanDb();
						if (strand > "") strand.clear();
						if (strand == "") prints();
						continue;
					}
					clearAllKeys(); strand = "<"; prints(); continue;
				}
			}
			GetAsyncKeyState(0x58); if (GetAsyncKeyState(0x58)) { if (enableEscX) return 0; } //esc + x
			GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) {//esc + h
				if (EscHAutoBs) kb(VK_BACK);
				GetAsyncKeyState(VK_ESCAPE); toggle_visibility(); 
				if (showStrand && !qScanOnly) cout << OutsTemplate << strand << '\n'; 
				continue; 
			}
			if (!ignoreEsc) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key("~"); }
			continue;
		}
		//if (!ignorePrintScreen)if (GetAsyncKeyState(VK_SNAPSHOT)) { key(PrintScreen_Key); continue; }
		if (qScanOnly && strand.substr(0, 1) != "<") continue;
#pragma region input_strand
		if (!ignoreAZ) {
			if (GetAsyncKeyState(0x41)) { key("a"); continue; }
			if (GetAsyncKeyState(0x42)) { key("b"); continue; }
			if (GetAsyncKeyState(0x43)) { key("c"); continue; }
			if (GetAsyncKeyState(0x44)) { key("d"); continue; }
			if (GetAsyncKeyState(0x45)) { key("e"); continue; }
			if (GetAsyncKeyState(0x46)) { key("f"); continue; }
			if (GetAsyncKeyState(0x47)) { key("g"); continue; }
			if (GetAsyncKeyState(0x48)) { key("h"); continue; }
			if (GetAsyncKeyState(0x49)) { key("i"); continue; }
			if (GetAsyncKeyState(0x4A)) { key("j"); continue; }
			if (GetAsyncKeyState(0x4B)) { key("k"); continue; }
			if (GetAsyncKeyState(0x4C)) { key("l"); continue; }
			if (GetAsyncKeyState(0x4D)) { key("m"); continue; }
			if (GetAsyncKeyState(0x4E)) { key("n"); continue; }
			if (GetAsyncKeyState(0x4F)) { key("o"); continue; }
			if (GetAsyncKeyState(0x50)) { key("p"); continue; }
			if (GetAsyncKeyState(0x51)) { key("q"); continue; }
			if (GetAsyncKeyState(0x52)) { key("r"); continue; }
			if (GetAsyncKeyState(0x53)) { key("s"); continue; }
			if (GetAsyncKeyState(0x54)) { key("t"); continue; }
			if (GetAsyncKeyState(0x55)) { key("u"); continue; }
			if (GetAsyncKeyState(0x56)) { key("v"); continue; }
			if (GetAsyncKeyState(0x57)) { key("w"); continue; }
			if (GetAsyncKeyState(0x58)) { key("x"); continue; }
			if (GetAsyncKeyState(0x59)) { key("y"); continue; }
			if (GetAsyncKeyState(0x5A)) { key("z"); continue; }
		}
		if (!ignore09) {
			if (GetAsyncKeyState(0x30)) { key("0"); continue; }
			if (GetAsyncKeyState(0x31)) { key("1"); continue; }
			if (GetAsyncKeyState(0x32)) { key("2"); continue; }
			if (GetAsyncKeyState(0x33)) { key("3"); continue; }
			if (GetAsyncKeyState(0x34)) { key("4"); continue; }
			if (GetAsyncKeyState(0x35)) { key("5"); continue; }
			if (GetAsyncKeyState(0x36)) { key("6"); continue; }
			if (GetAsyncKeyState(0x37)) { key("7"); continue; }
			if (GetAsyncKeyState(0x38)) { key("8"); continue; }
			if (GetAsyncKeyState(0x39)) { key("9"); continue; }
		}
		if (!ignoreF1s) {
			if (GetAsyncKeyState(0x70)) { key("!"); continue; } //VK_F1
			if (GetAsyncKeyState(0x71)) { key("@"); continue; }
			if (GetAsyncKeyState(0x72)) { key("#"); continue; }
			if (GetAsyncKeyState(0x73)) { key("$"); continue; }
			if (GetAsyncKeyState(0x74)) { key("%"); continue; }
			if (GetAsyncKeyState(0x75)) { key("^"); continue; }
			if (GetAsyncKeyState(0x76)) { key("&"); continue; }
			if (GetAsyncKeyState(0x77)) { key("*"); continue; }
			if (GetAsyncKeyState(0x78)) { key("("); continue; }
			if (GetAsyncKeyState(0x79)) { key(")"); continue; }
			if (GetAsyncKeyState(0x7A)) { key("_"); continue; }
			if (GetAsyncKeyState(0x7B)) { key("+"); continue; }
		}
		if (!ignoreArrows) {
			if (GetAsyncKeyState(VK_LEFT)) { key("L"); continue; }
			if (GetAsyncKeyState(VK_UP)) { key("U"); continue; }
			if (GetAsyncKeyState(VK_RIGHT)) { key("R"); continue; }
			if (GetAsyncKeyState(VK_DOWN)) { key("D"); continue; }
		}
		if (!ignoreSpace && GetAsyncKeyState(VK_SPACE)) { key(" "); continue; }
		if (!ignoreTab && GetAsyncKeyState(VK_TAB)) { key("T"); continue; }
		if (!ignoreLShift && GetAsyncKeyState(VK_LSHIFT)) { key("S"); continue; }
		if (!ignoreRShift && GetAsyncKeyState(VK_RSHIFT)) { key("H"); continue; }
		if (!ignoreLAlt && GetAsyncKeyState(VK_LMENU)) { key("A"); continue; }
		if (!ignoreRAlt && GetAsyncKeyState(VK_RMENU)) { key("M"); continue; }
		if (!ignoreLCtrl && GetAsyncKeyState(VK_LCONTROL)) { key("C"); continue; }
		if (!ignoreRCtrl && GetAsyncKeyState(VK_RCONTROL)) { key("O"); continue; }
		if (!ignoreEnter && GetAsyncKeyState(VK_RETURN)) { key("E"); continue; }
		if (!ignoreCaps && GetAsyncKeyState(VK_CAPITAL)) { key("P"); continue; }
		if (!ignoreGraveAccent && GetAsyncKeyState(VK_OEM_3)) { key("`"); continue; }
		if (!ignoreMinus && GetAsyncKeyState(VK_OEM_MINUS)) { key("-"); continue; }
		if (!ignoreEqual && GetAsyncKeyState(VK_OEM_PLUS)) { key("="); continue; }
		if (!ignoreLBracket && GetAsyncKeyState(VK_OEM_4)) { key("["); continue; }
		if (!ignoreRBracket && GetAsyncKeyState(VK_OEM_6)) { key("]"); continue; }
		if (!ignoreBackslash && GetAsyncKeyState(VK_OEM_5)) { key("\\"); continue; }
		if (!ignoreSemicolon && GetAsyncKeyState(VK_OEM_1)) { key(";"); continue; }
		if (!ignoreQuote && GetAsyncKeyState(VK_OEM_7)) { key("'"); continue; }
		if (!ignoreComma && GetAsyncKeyState(VK_OEM_COMMA)) { key(","); continue; }
		if (!ignorePeriod && GetAsyncKeyState(VK_OEM_PERIOD)) { key("."); continue; }
		if (!ignoreForwardslash && GetAsyncKeyState(VK_OEM_2)) { key("/"); continue; }
		if (!ignoreMenuKey) if (GetAsyncKeyState(VK_APPS)) { key("?"); continue; }
		/*if (!ignoreMediaKeys) {
			if (GetAsyncKeyState(VK_INSERT)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_DELETE)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_HOME)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_END)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_PRIOR)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_NEXT)) { key("?"); continue; }
		}
		if (GetAsyncKeyState(JOY_BUTTON1)) { key("?"); continue; }*/
		if (!ignoreNumPad) {
			if (GetAsyncKeyState(VK_NUMPAD0)) { key("Z"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD1)) { key("Q"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD2)) { key("V"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD3)) { key("W"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD4)) { key("X"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD5)) { key("Y"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD6)) { key("B"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD7)) { key("F"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD8)) { key("G"); continue; }
			if (GetAsyncKeyState(VK_NUMPAD9)) { key("I"); continue; }
			if (GetAsyncKeyState(VK_NUMLOCK)) { key("N"); continue; }
			if (GetAsyncKeyState(VK_DIVIDE)) { key("J"); continue; }
			if (GetAsyncKeyState(VK_MULTIPLY)) { key("K"); continue; }
			if (GetAsyncKeyState(VK_SUBTRACT)) { key("{"); continue; }
			if (GetAsyncKeyState(VK_ADD)) { key("}"); continue; }
			if (GetAsyncKeyState(VK_DECIMAL)) { key("\""); continue; }
			if (GetAsyncKeyState(VK_RETURN)) { key(":"); continue; }
		}
#pragma endregion
	}
}