// @dnaspider

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

#pragma region "global var"
bool StockInterfaceControls = true;
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
bool ignore09 = false;
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
int strandLength = 3;
bool qScanOnly = false;
string database = R"(C:\dna\db.txt)";
string settings = R"(C:\dna\se.txt)";
int frequency = 150; //>> ms response -> vk_
int speed = 0; //<< 
short reKey = VK_SCROLL; //repeat
short cKey = VK_CONTROL; // < 
string strand = ""; //>> supply
string tail = ""; //strand:tail
string re = "";//repeat clone
bool showStrand = true; //cout <<
bool showOuts = true; //cout << 
bool showIntro = true;
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
bool SlightPauseInBetweenConnects = true;
string OutsTemplate = "strand: ";
bool EscCommaAutoBs = true;
#pragma endregion

#pragma region "global sub"
string check_if_num(string s) {
	if (s > "") {
		for (size_t t = 0; t < s.length(); t++) {//!0-9
			if (t == 0 && (s[0] == 45 || s[0] == 43) && s.length() != 1)continue; //-+
			if ((s[t] >= 48 && s[t] <= 57) == false) { s = ""; return s; }
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

void kbPress(string code, short key) {
	star_num = "1"; if (qqb(code)) {
		star_num = qq.substr(code.length(), qq.find(">") - code.length());
		if (check_if_num(star_num) == "") star_num = "0";
	}//cout << "star_num: <x* " << star_num << endl;
	INPUT ip[2]; ip[0].type = INPUT_KEYBOARD; ip[0].ki.wVk = key;
	//ip[0].ki.dwFlags = key >= 0x23 && key <= 0x28 ? 1 : 0;
	if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_HOME || key == VK_END) ip[0].ki.dwFlags = 1; else ip[0].ki.dwFlags = 0;
	ip[1] = ip[0]; ip[1].ki.dwFlags = 2;
	for (int j = 0; j < stoi(star_num); j++) {
		if (code == "<,*") {
			Sleep(CommaSleep);
			GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { if (speed > 0) { speed = 0; }return; } if (GetAsyncKeyState(VK_PAUSE)) { int m = MessageBoxA(0, "Resume?", "Pause", MB_YESNO); if (m == IDYES) { GetAsyncKeyState(VK_PAUSE); } else { if (speed > 0) { speed = 0; }i = tail.length(); return; } }//stop
		}
		else if (code == "<lc*") { mouseEvent(MOUSEEVENTF_LEFTDOWN); mouseEvent(MOUSEEVENTF_LEFTUP); }
		else if (code == "<rc*") { mouseEvent(MOUSEEVENTF_RIGHTDOWN); mouseEvent(MOUSEEVENTF_RIGHTUP); }
		else SendInput(2, ip, sizeof(ip[0]));
		GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { if (speed > 0) { speed = 0; }return; } if (GetAsyncKeyState(VK_PAUSE)) { int m = MessageBoxA(0, "Resume?", "Pause", MB_YESNO); if (m == IDYES) { GetAsyncKeyState(VK_PAUSE); } else { if (speed > 0) { speed = 0; }i = tail.length(); return; } }//stop
		if (speed > 0 && stoi(star_num) != j + 1) Sleep(speed);
	}
	if (star_num != "0") rei(); else printq();
}

void clearAllKeys() {
	for (int i = 65; i < 91; i++) { GetAsyncKeyState(i); }
	for (int i = 48; i < 58; i++) { GetAsyncKeyState(i); }
	GetAsyncKeyState(cKey);
	GetAsyncKeyState(reKey);
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

void scanDb(); void conn() {//<connect:>	
	bool con = false; string qqs = qq.substr(0, qq.find(">") + 1);
	if (qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		if (qqs.substr(qqs.length() - 2, 2) == ":>" || qqs.substr(qqs.length() - 2, 2) == "->") {
			con = true;
		}
	}
	if (con) {
		ifstream f(database); string cell; while (getline(f, cell)) {
			if (qqs == cell.substr(0, qqs.length())) { //<h:> | <h->
				string re1 = tail;
				string qqc = qq.substr(0, qq.find(">"));
				tail = qq.replace(qq.find(qqc + ">"), qqc.length() + 1, cell.substr(cell.substr(0, qqc.length()).length(), cell.length()));

				if (SlightPauseInBetweenConnects) {
					if (tail.find("<,*") != std::string::npos ||
						tail.find("<,>") != std::string::npos ||
						tail.find("<ms:") != std::string::npos ||
						tail.find("<sleep:") != std::string::npos ||
						tail.find("<speed:") != std::string::npos)
						;
					else
						Sleep(150);
				}

				re = ">" + tail; strand.clear(); scanDb(); re.clear();
				clearAllKeys();
				strand.clear();
				tail = re1;
				f.close();
				i = tail.length();
				return;
			}
		}f.close(); printq();
	}
	else printq();
}

void out(string ai) { re = ">" + ai; strand.clear(); scanDb(); re.clear(); }

void calc() {
	string to_string(long v), t = tail;
	rei();
	qq = to_string(ic) + qq.substr(qq.find(">") + 1, qq.length());
	out(qq);
	tail = t;
	i = tail.length();
}

void loadSe() {
	ifstream f(settings); string cell;	while (getline(f, cell)) {
		string se = cell.substr(0, cell.find(":") + 1);
		string v = (cell.substr(cell.find(":") + 1));
		if (se == "Database:") { database = (v.length() > 0) ? v.substr(1) : v; continue; }
		if (se == "ShowSettings:") { showSettings = stoi(v); continue; }
		if (se == "StrandLengthMode:") { strandLengthMode = stoi(v); continue; }
		if (se == "StrandLength:") { strandLength = stoi(v); continue; }
		if (se == "CtrlScanOnlyMode:") { qScanOnly = stoi(v); continue; }
		if (se == "CtrlKey:") { cKey = stoi(v); continue; }
		if (se == "Frequency:") { frequency = stoi(v); continue; }
		if (se == "RepeatKey:") { reKey = stoi(v); continue; }
		if (se == "ShowStrand:") { showStrand = stoi(v); continue; }
		if (se == "ShowOuts:") { showOuts = stoi(v); continue; }
		if (se == "OutsTemplate:") { OutsTemplate = (v.length() > 0) ? v.substr(1) : v; continue; }
		if (se == "ShowIntro:") { showIntro = stoi(v); continue; }
		if (se == "Exit_EscX:") { enableEscX = stoi(v); continue; }
		if (se == "Ignore_A-Z:") { ignoreAZ = stoi(v); continue; }
		if (se == "Ignore_0-9:") { ignore09 = stoi(v); continue; }
		if (se == "Ignore_Space:") { ignoreSpace = stoi(v); continue; }
		if (se == "Ignore_F1-F12:") { ignoreF1s = stoi(v); continue; }
		if (se == "Ignore_Arrows:") { ignoreArrows = stoi(v); continue; }
		if (se == "Ignore_Esc:") { ignoreEsc = stoi(v); continue; }
		if (se == "Ignore_Tab:") { ignoreTab = stoi(v); continue; }
		if (se == "Ignore_Enter:") { ignoreEnter = stoi(v); continue; }
		if (se == "Ignore_Caps:") { ignoreCaps = stoi(v); continue; }
		if (se == "Ignore_LShift:") { ignoreLShift = stoi(v); continue; }
		if (se == "Ignore_RShift:") { ignoreRShift = stoi(v); continue; }
		if (se == "Ignore_LAlt:") { ignoreLAlt = stoi(v); continue; }
		if (se == "Ignore_RAlt:") { ignoreRAlt = stoi(v); continue; }
		if (se == "Ignore_LCtrl:") { ignoreLCtrl = stoi(v); continue; }
		if (se == "Ignore_RCtrl:") { ignoreRCtrl = stoi(v); continue; }
		if (se == "Ignore_GraveAccent:") { ignoreGraveAccent = stoi(v); continue; }
		if (se == "Ignore_Minus:") { ignoreMinus = stoi(v); continue; }
		if (se == "Ignore_Equal:") { ignoreEqual = stoi(v); continue; }
		if (se == "Ignore_LBracket:") { ignoreLBracket = stoi(v); continue; }
		if (se == "Ignore_RBracket:") { ignoreRBracket = stoi(v); continue; }
		if (se == "Ignore_Backslash:") { ignoreBackslash = stoi(v); continue; }
		if (se == "Ignore_Semicolon:") { ignoreSemicolon = stoi(v); continue; }
		if (se == "Ignore_Quote:") { ignoreQuote = stoi(v); continue; }
		if (se == "Ignore_Comma:") { ignoreComma = stoi(v); continue; }
		if (se == "Ignore_Period:") { ignorePeriod = stoi(v); continue; }
		if (se == "Ignore_Forwardslash:") { ignoreForwardslash = stoi(v); continue; }
		if (se == "Ignore_Menu:") { ignoreMenuKey = stoi(v); continue; }
		//if (se == "Ignore_MediaKeys:") { ignoreMediaKeys = stoi(v); continue; }
		if (se == "Ignore_NumPad:") { ignoreNumPad = stoi(v); continue; }
		if (se == "StartHidden:") { startHidden = stoi(v); continue; }
		if (se == "ClearStrandAfterStockCtrls:") { clear_after_stock = stoi(v); continue; }
		if (se == "CloseCtrlMode:") { close_ctrl_mode = stoi(v); continue; }
		if (se == "SlightPauseInBetweenConnects:") { SlightPauseInBetweenConnects = stoi(v); continue; }
		if (se == "EscCommaAutoBs:") { EscCommaAutoBs = stoi(v); continue; }
		if (se == "CommaSleep:") { CommaSleep = stoi(v); continue; }
		if (se == "StockInterfaceControls:") { StockInterfaceControls = stoi(v); continue; }
	}f.close();
}

void printApi() {
	cout << "API\n"; if (!StockInterfaceControls) { cout << "<se>  Load " << settings << " | db.txt example: <se:<se>\n"; }  cout << "<ms:>  Milliseconds sleep. Example: <ms:1500> or <sleep:1500>\n<,>  " << CommaSleep << " milliseconds sleep\n<xy:0,0>  Move pointer\n<x:><y:>  Current position +/- value. Example: <x:-1>\n<rp>  Return pointer\n<lc><rc><lh><rh><lr><rr>  Left right click hold release\n<ctrl><shift><alt><win>  Hold key\n<ctrl-><shift-><alt-><win->  Release key\n<up><right><down><left><delete><esc><bs><home><end><space><tab><enter>  Press key\n<bs*2>  Press twice\n<menu>  Press Menu key\n<ins>  Press Insert\n<ps>  Press Print Screen\n<pu><pd>  Press Page Up, Page Down\n<f1>  Press F1 (F1-F12)\n<app:>  Set app to foreground. Example: <app:Calculator>\n<App:>  Continue if app in foreground\n<'>  Comments. Example: <'Like so>\n<yesno:>  Verify message. Example: <yesno:Continue?>\n<beep>  Alert sound\n<a:>  Alt codes. Example: <a:9201>\n<speed:>  Output. Example: <speed:150>\n<+:><-:><*:></:><%:>  Calc. Example: <+:1>, <+:-1>\n<+>  Clone. Example: <*:7><+>\n\n";
	if (showIntro) cout << "API's are placed to right of the first :, -, >, ->, or :> of each line in db.txt\nExample: test-<enter>\nSave example to db.txt then clear strand by toggling Ctrl, Backspace, Pause, or Esc + Comma. Inside a text area, press T E S T to run (strand: test)\n";
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
		cout << "Hold O on startup:  ShowStrand, ShowOuts: 0" << endl;
		//cout << "Hold Q on startup:  Ctrl scan only: true" << endl;
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
		cout << "EscCommaAutoBs: " << EscCommaAutoBs << endl;
		cout << "CommaSleep: " << CommaSleep << endl;
		cout << "StockInterfaceControls: " << StockInterfaceControls << endl;
		cout << "Exit_EscX: " << enableEscX << endl;
		cout << endl;
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

	ifstream f(database); string cell; while (getline(f, cell)) { //cout << cell << endl;
		if (re > "" || (close_ctrl_mode && cell.substr(0, strand.length()) == strand || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + ":" || cell.substr(0, strand.length()) == strand.substr(0, strand.length() - 1) + "-" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + ":>" || cell.substr(0, strand.length() + 1) == strand.substr(0, strand.length() - 1) + "->") || cell.substr(0, strand.length() + 1) == strand + ">" || cell.substr(0, strand.length() + 1) == strand + ":" || cell.substr(0, strand.length() + 1) == strand + "-" || (strandLengthMode && cell.substr(0, strandLength) == strand && cell.substr(0, 1) != "<")) { //found i>o, i:o, i-o, i:>o, i->o || i>o, i:o, i-o || io

			if (close_ctrl_mode && strand.length() > 0 && strand.substr(strand.length() - 1) == ">") strand = strand.substr(0, strand.length() - 1);

			if (re > "") {
				cell = re;
				if (re.substr(0, 20) == "><shift>,<shift->xy:") { POINT pt; GetCursorPos(&pt); string to_string(long v); cell = "><shift>,<shift->xy:" + to_string(pt.x) + "," + to_string(pt.y) + ">"; }
			}

			tail = cell.substr(strand.length() + 1, cell.length() - strand.length() + 1);//return
			if (cell.substr(0, strand.length() + 1) == strand + "-") {//<bs> strand.length()
				//for (size_t t = 0; t < strand.length(); t++) { if (strand.substr(l, 1) == "<" || !ignoreArrows && (strand.substr(l, 1) == "L" || strand.substr(l, 1) == "U" || strand.substr(l, 1) == "R" || strand.substr(l, 1) == "D") || !ignoreF1s && (strand.substr(l, 1) == "!" || strand.substr(l, 1) == "@" || strand.substr(l, 1) == "#" || strand.substr(l, 1) == "$" || strand.substr(l, 1) == "%" || strand.substr(l, 1) == "^" || strand.substr(l, 1) == "&" || strand.substr(l, 1) == "*" || strand.substr(l, 1) == "(" || strand.substr(l, 1) == ")" || strand.substr(l, 1) == "_" || strand.substr(l, 1) == "+") || strand.substr(l, 1) == "." || strand.substr(l, 1) == "S" || strand.substr(l, 1) == "H" || strand.substr(l, 1) == "A" || strand.substr(l, 1) == "M" || strand.substr(l, 1) == "C" || strand.substr(l, 1) == "O" || strand.substr(l, 1) == "P") { continue; } kb(VK_BACK); }GetAsyncKeyState(VK_BACK);//ignore non bs
				for (size_t t = 0; t < strand.length(); t++) { if (strand[t] == 60 || ((!ignoreMenuKey) && strand[t] == 63) || (!ignoreArrows) && (strand[t] == 76 || strand[t] == 85 || strand[t] == 82 || strand[t] == 68) || (!ignoreF1s) && (strand[t] == 33 || (strand[t] >= 35 && strand[t] <= 38) || (strand[t] >= 40 && strand[t] <= 43) || strand[t] == 64 || strand[t] == 94 || strand[t] == 95) || (!ignoreEsc && strand[t] == 126) || (!ignoreLShift && strand[t] == 83) || (!ignoreRShift && strand[t] == 72) || (!ignoreLAlt && strand[t] == 65) || (!ignoreRAlt && strand[t] == 77) || (!ignoreLCtrl && strand[t] == 67) || (!ignoreRCtrl && strand[t] == 79) || (!ignoreCaps && strand[t] == 80)) { continue; } kb(VK_BACK); }GetAsyncKeyState(VK_BACK);//exclude non bs
			}
			if (strandLengthMode && strand.length() == strandLength && cell.substr(0, 1) != "<") {
				if (re == "") tail = cell.substr(strandLength, cell.length());
				if (re > "") tail = re.substr(1, re.length());
			}
			if (tail.substr(0, 1) == ">") tail = tail.substr(1, tail.length());//<found>tail
			if (showOuts) { cout << "found: " << cell << "\ntail: " << tail << endl; }

			if (tail.find("<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }

			for (i = 0; i < tail.length(); i++) {
				if (speed > 0) { Sleep(speed); }
				GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE)) { break; }if (GetAsyncKeyState(VK_PAUSE)) { int m = MessageBoxA(0, "Resume?", "Pause", MB_YESNO); if (m == IDYES) { GetAsyncKeyState(VK_PAUSE); } else { if (speed > 0) { speed = 0; }i = tail.length(); break; } }

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
							if (check_if_num(qp) == "") { printq(); continue; }
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
						if (qqb("<,>") || qqb("<,*")) kbPress("<,*", VK_F7);//sleep150ms, vk_dud
						else printq();
						break;
					case'\'':
						if (qqb("<'")) rei(); //<'comments>
						break;
					case'a':
						if (qqb("<alt>")) { kbHold(VK_LMENU); rei(); }
						else if (qqb("<alt*")) kbPress("<alt*", VK_LMENU);
						else if (qqb("<alt->")) { kbRelease(VK_LMENU); rei(); }
						else if (qqb("<a:")) { kb1(qp); rei(); }//alt codes
						else if (qqb("<app:")) {//app activate
							for (int w = 0; w < 25; w++) {
								if (w >= 24) { if (showOuts) { cout << "app: " << qp << " not found\n"; strand.clear(); } f.close(); return; }
								DWORD pid; HWND h = FindWindowA(0, qp.c_str());	GetWindowThreadProcessId(h, &pid);
								if (h) { if (IsIconic(h)) { ShowWindow(h, SW_RESTORE); } SetForegroundWindow(h); break; }
								if (GetAsyncKeyState(VK_ESCAPE)) { f.close(); return; }
								Sleep(333);
							}//Sleep(150);
							rei();
						}
						else conn();
						break;
					case 'A':
						if (qqb("<App:")) {//if app in foreground
							HWND h = GetForegroundWindow();	HWND h1 = FindWindowA(0, qp.c_str());
							if (h == h1) { rei(); continue; }
							else { if (showOuts) { cout << "fail: <App:" << qp << ">" << endl; } i = tail.length(); break; }
						}
						else conn();
						break;
					case'b':
						if (qqb("<bs>") || qqb("<bs*")) kbPress("<bs*", VK_BACK);
						else if (qqb("<beep>")) { cout << "\a" << endl; rei(); }
						else conn();
						break;
					case'c':
						if (qqb("<ctrl>")) { kbHold(VK_CONTROL); rei(); }
						else if (qqb("<ctrl*")) kbPress("<ctrl*", VK_CONTROL);
						else if (qqb("<ctrl->")) { kbRelease(VK_CONTROL); rei(); }
						else conn();
						break;
					case'd':
						if (qqb("<down>") || qqb("<down*")) kbPress("<down*", VK_DOWN);
						else if (qqb("<delete>") || qqb("<delete*")) kbPress("<delete*", VK_DELETE);
						else conn();
						break;
					case'e':
						if (qqb("<enter>") || qqb("<enter*")) kbPress("<enter*", VK_RETURN);
						else if (qqb("<end>") || qqb("<end*")) kbPress("<end*", VK_END);
						else if (qqb("<esc>") || qqb("<esc*")) kbPress("<esc*", VK_ESCAPE);
						else conn();
						break;
					case'f':
						if (qqb("<f1>") || qqb("<f1*")) kbPress("<f1*", VK_F1);
						else if (qqb("<f2>") || qqb("<f2*")) kbPress("<f2*", VK_F2);
						else if (qqb("<f3>") || qqb("<f3*")) kbPress("<f3*", VK_F3);
						else if (qqb("<f4>") || qqb("<f4*")) kbPress("<f4*", VK_F4);
						else if (qqb("<f5>") || qqb("<f5*")) kbPress("<f5*", VK_F5);
						else if (qqb("<f6>") || qqb("<f6*")) kbPress("<f6*", VK_F6);
						else if (qqb("<f7>") || qqb("<f7*")) kbPress("<f7*", VK_F7);
						else if (qqb("<f8>") || qqb("<f8*")) kbPress("<f8*", VK_F8);
						else if (qqb("<f9>") || qqb("<f9*")) kbPress("<f9*", VK_F9);
						else if (qqb("<f10>") || qqb("<f10*")) kbPress("<f10*", VK_F10);
						else if (qqb("<f11>") || qqb("<f11*")) kbPress("<f11*", VK_F11);
						else if (qqb("<f12>") || qqb("<f12*")) kbPress("<f12*", VK_F12);
						else conn();
						break;
					case'h':
						if (qqb("<home>") || qqb("<home*")) kbPress("<home*", VK_HOME);
						else conn();
						break;
					case'i':
						if (qqb("<ins>") || qqb("<ins*")) kbPress("<ins*", VK_INSERT);
						else conn();
						break;					
					case'l':
						if (qqb("<lc>") || qqb("<lc*")) kbPress("<lc*", VK_F7); //left click
						else if (qqb("<lh>")) {//left hold
							mouseEvent(MOUSEEVENTF_LEFTDOWN);
							rei();
						}
						else if (qqb("<lr>")) {//left release
							mouseEvent(MOUSEEVENTF_LEFTUP);
							rei();
						}
						else if (qqb("<left>") || qqb("<left*")) kbPress("<left*", VK_LEFT);
						else conn();
						break;
					case'm':
						if (qqb("<ms:")) if (check_if_num(qp) != "") { Sleep(stoi(qp));	rei(); }
						else printq();
						else if (qqb("<menu>") || qqb("<menu*")) kbPress("<menu*", VK_APPS);
						else conn();
						break;
					case'p':
						if (qqb("<ps>") || qqb("<ps*")) kbPress("<ps*", VK_SNAPSHOT);
						else if (qqb("<pu>") || qqb("<pu*")) kbPress("<pu*", VK_PRIOR);//pgup
						else if (qqb("<pd>") || qqb("<pd*")) kbPress("<pd*", VK_NEXT);//pgdn
						else conn();
						break;
					case'r':
						if (qqb("<rp>")) {//return pointer
							SetCursorPos(qxc, qyc);
							rei();
						}
						else if (qqb("<rc>") || qqb("<rc*")) kbPress("<rc*", VK_F7);
						else if (qqb("<rh>")) {//right hold
							mouseEvent(MOUSEEVENTF_RIGHTDOWN);
							rei();
						}
						else if (qqb("<rr>")) {//right release
							mouseEvent(MOUSEEVENTF_RIGHTUP);
							rei();
						}
						else if (qqb("<right>") || qqb("<right*")) kbPress("<right*", VK_RIGHT);
						else conn();
						break;
					case's':
						if (!StockInterfaceControls && qqb("<se>")) { printSe(); rei(); }
						else if (qqb("<shift>")) { kbHold(VK_LSHIFT); rei(); }
						else if (qqb("<shift*")) kbPress("<shift*", VK_LSHIFT);
						else if (qqb("<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
						else if (qqb("<sleep:")) if (check_if_num(qp) != "") { Sleep(stoi(qp)); rei(); }
						else printq();
						else if (qqb("<space>") || qqb("<space*")) kbPress("<space*", VK_SPACE);
						else if (qqb("<speed:")) if (check_if_num(qp) != "") { speed = stoi(qp); rei(); }
						else printq();
						else conn();
						break;
					case't':
						if (qqb("<tab>") || qqb("<tab*")) kbPress("<tab*", VK_TAB);
						else conn();
						break;
					case'u':
						if (qqb("<up>") || qqb("<up*")) kbPress("<up*", VK_UP);
						else conn();
						break;
					case'w':
						if (qqb("<win>")) { kbHold(VK_LWIN); rei(); }
						else if (qqb("<win*")) kbPress("<win*", VK_LWIN);
						else if (qqb("<win->")) { kbRelease(VK_LWIN); rei(); }
						else conn();
						break;
					case'x':
						if (qqb("<xy:")) {
							SetCursorPos(stoi(qx), stoi(qy)); rei();
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
							int m = MessageBoxA(0, qp.c_str(), "Verify", MB_YESNO);
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
			clearAllKeys();
			strand.clear();
			if (speed > 0)speed = 0;
			break;
		}
	}
	f.close();
}

void printDb() {
	cout << database << "\n";
	ifstream f(database); string cell;
	SetConsoleOutputCP(CP_UTF8); while (getline(f, cell)) { cout << cell << endl; }
	f.close(); cout << endl;
}

void printXy() {
	POINT pt; GetCursorPos(&pt);
	if (strand == "x") { if (showOuts) cout << "xy: " << pt.x << "," << pt.y << endl; }
	else { string to_string(long v); out("<bs*2>"); out("><shift>,<shift->xy:" + to_string(pt.x) + "," + to_string(pt.y) + ">"); }
}

void printInterfaceCtrls() {
	string c; if (cKey == VK_CONTROL) c = "Ctrl"; else if (cKey == VK_LCONTROL) c = "LCtrl"; else if (cKey == VK_RCONTROL) c = "RCtrl"; else if (cKey == VK_ESCAPE) c = "Esc";
	cout << "Interface" << endl;
	if (StockInterfaceControls) {
		string se = qScanOnly ? "<se" : "se"; cout << se << ":  Settings (Press " << (qScanOnly ? c+" S E" : "S E") << " to load " << settings << ")\n";
		if (qScanOnly)se = "<db"; else se = "db"; cout << se << ":  Database" << endl;
	}
	(StockInterfaceControls) ? cout << "<xy" : cout << "Esc + P"; cout << ":  <xy:>" << endl;
	cout << "Esc:  Stop" << endl;
	cout << "Esc + H:  Toggle visibility" << endl;
	if (enableEscX) cout << "Esc + X:  Exit" << endl;
	cout << "Esc + Comma:  <" << endl;
	cout << c << ":  Toggle <" << endl;
	(reKey == 145) ? c = "Scroll Lock" : c = "repeatKey: " + reKey; cout << c << " or Esc + Equal: Repeat" << endl;
	cout << "Pause Break:  Clear strand | Pause/Resume" << endl;
	if (StockInterfaceControls) { cout << "<odb:  Open database: " << database << endl;	cout << "<ose:  Open settings: " << settings << endl; }
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

int main() {
	cout << "@dnaspider\n\n";
	if (CreateDirectory("c:/dna", NULL)) {
		cout << database << " not found.\nPress [1] to auto create.\n\n";
		for (;; Sleep(150)) { if (GetAsyncKeyState(VK_ESCAPE)) { RemoveDirectory("c:/dna"); Sleep(150); GetAsyncKeyState(VK_ESCAPE); break; }if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1)) { break; } }
		showOuts = false; ofstream fd(database); fd << "h:ello\n<h->Hello\n<i:><bs><h->!\n\n\nGetting Started:\nPress h (strand: h), ctrl h (strand: <h), or ctrl i (strand: <i) in a text area to run\n\nTip:\nClear strand first by toggling ctrl, backspace, esc + comma or pause/break key\nPress keys independently. e.g., right ctrl, release right ctrl, h"; fd.close(); ofstream fs(settings); fs << "ShowSettings: 1\nShowIntro: 1\nShowStrand: 1\nShowOuts: 0\nOutsTemplate: " << OutsTemplate << "\nDatabase: " << database << "\nCtrlScanOnlyMode: 0\nCtrlKey: 163\nStrandLengthMode: 0\nStrandLength: 3\nCloseCtrlMode: 0\nRepeatKey: 145\nFrequency: 150\nIgnore_A-Z: 0\nIgnore_0-9: 0\nIgnore_Space: 0\nIgnore_F1-F12: 1\nIgnore_Arrows: 1\nIgnore_Esc: 1\nIgnore_Tab: 1\nIgnore_Enter: 1\nIgnore_Caps: 1\nIgnore_LShift: 1\nIgnore_RShift: 1\nIgnore_LAlt: 1\nIgnore_RAlt: 1\nIgnore_LCtrl: 1\nIgnore_RCtrl: 1\nIgnore_GraveAccent: 1\nIgnore_Minus: 1\nIgnore_Equal: 1\nIgnore_LBracket: 1\nIgnore_RBracket: 1\nIgnore_Backslash: 1\nIgnore_Semicolon: 1\nIgnore_Quote: 1\nIgnore_Comma: 1\nIgnore_Period: 1\nIgnore_Forwardslash: 1\nIgnore_Menu: 1\nIgnore_NumPad: 1\nStartHidden: 0\nClearStrandAfterStockCtrls: 1\nSlightPauseInBetweenConnects: 1\nEscCommaAutoBs: 1\nCommaSleep: 150\nStockInterfaceControls: 1\nExit_EscX: 1"; fs.close(); out("<win>r<win-><app:run>" + settings + "<enter><ms:1500><win>r<win-><app:run>" + database + "<enter>");  showOuts = true; re = ""; strand.clear();
	}
	else { ; }
	loadSe();
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (StockInterfaceControls) {
		if (GetAsyncKeyState(81)) { qScanOnly = true; }//q
		if (GetAsyncKeyState(79)) { showOuts = false; showStrand = false; }//o
		if (GetAsyncKeyState(VK_RCONTROL))cKey = VK_RCONTROL;
		if (GetAsyncKeyState(VK_LCONTROL))cKey = VK_LCONTROL;
		if (GetAsyncKeyState(VK_ESCAPE))cKey = VK_ESCAPE;
	}
	printIntro();
	for (;; Sleep(frequency)) {
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
		if (GetAsyncKeyState(reKey)) { out(tail); kbRelease(reKey); GetAsyncKeyState(reKey); continue; }//repeat
		if (GetAsyncKeyState(VK_PAUSE)) { if (strand.substr(0, 1) == "<") strand = "<"; else strand.clear(); continue; }
		if (GetAsyncKeyState(VK_ESCAPE)) {
			if (!ignoreEsc) { kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); key("~"); }
			GetAsyncKeyState(80); if (GetAsyncKeyState(80)) {//esc + p: <xy:>
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				POINT pt; GetCursorPos(&pt);
				string to_string(long v); out("<bs>"); out("><shift>,<shift->xy:" + to_string(pt.x) + "," + to_string(pt.y) + ">");

			}
			GetAsyncKeyState(VK_OEM_PLUS); if (GetAsyncKeyState(VK_OEM_PLUS)) {//esc + plus: repeat
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE);
				string t = tail;
				out("<bs>");
				out(t);
			}
			GetAsyncKeyState(0xBC); if (GetAsyncKeyState(0xBC)) {
				kbRelease(VK_ESCAPE); GetAsyncKeyState(VK_ESCAPE); kbRelease(VK_OEM_COMMA); GetAsyncKeyState(VK_OEM_COMMA); if (EscCommaAutoBs) { kb(VK_BACK); GetAsyncKeyState(VK_BACK); } clearAllKeys(); //,
				if (strand.substr(0, 1) == "<" && close_ctrl_mode && strand.length() > 1 || strand.length() > 0 && close_ctrl_mode) {
					if (strand == "<")continue; strand.append(">"); prints(); scanDb(); if (strand > "") { strand.clear(); }
				}
				else { if (strand.substr(0, 1) == "<") { strand.clear(); prints(); continue; }strand.clear(); strand = "<"; prints(); }
			}
			GetAsyncKeyState(0x58); if (GetAsyncKeyState(0x58)) { if (enableEscX) return 0; } GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) { if ((bool)IsWindowVisible(GetConsoleWindow()) == true) { ShowWindow(GetConsoleWindow(), SW_HIDE); Sleep(150); strand.clear(); } else { ShowWindow(GetConsoleWindow(), SW_SHOW); Sleep(150); strand.clear(); } if (showStrand && !qScanOnly) cout << OutsTemplate << strand << '\n'; continue; }
		}
		if (qScanOnly && strand.substr(0, 1) != "<") continue;
#pragma region "a-z"
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
#pragma endregion
#pragma region "0-9"
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
#pragma endregion
#pragma region "F1-F12"
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
#pragma endregion
#pragma region "_"
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
		if (!ignoreQuote && GetAsyncKeyState(VK_OEM_7)) { key(","); continue; }
		if (!ignoreComma && GetAsyncKeyState(VK_OEM_COMMA)) { key(","); continue; }
		if (!ignorePeriod && GetAsyncKeyState(VK_OEM_PERIOD)) { key("."); continue; }
		if (!ignoreForwardslash && GetAsyncKeyState(VK_OEM_2)) { key("/"); continue; }

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
		/*if (!ignoreMediaKeys) {
			if (GetAsyncKeyState(VK_INSERT)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_DELETE)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_HOME)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_END)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_PRIOR)) { key("?"); continue; }
			if (GetAsyncKeyState(VK_NEXT)) { key("?"); continue; }
		}*/
		if (!ignoreMenuKey) if (GetAsyncKeyState(VK_APPS)) { key("?"); continue; }
		//if (GetAsyncKeyState(JOY_BUTTON1)) { key("?"); continue; }
#pragma endregion
	}
}