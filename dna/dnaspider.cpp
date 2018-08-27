// @dnaspider
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <windows.h.>
using namespace std;

#pragma region "global var"
bool startHidden = false;
bool ignoreAZ = false;
bool ignore09 = false;
bool strandLengthMode = false;
int strandLength = 3;
bool qScanOnly = false;
string database = "C:\\dna\\db.txt";
string settings = "C:\\dna\\se.txt";
int frequency = 150; //ms response -> vk_
short reKey = VK_SCROLL; //repeat
short cKey = VK_CONTROL; // < 
string strand = ""; //<<
string tail=""; //strand:tail
string re = "";//repeat clone
bool showStrand = true; //cout >>
bool showOuts = true; //cout >> 
bool showIntro = true;
bool showSettings = true;
string s2; //#
string qq; //<x>
string qp; //<x:#>
string qx,qy; //<xy:#-#>
auto qxc = 0;//<rp>
auto qyc = 0; 
bool shft = false;
size_t i = 0;
#pragma endregion

//global sub
inline void rei() { i+=qq.find(">"); }

inline void kb(short b) {//out char
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = VkKeyScan(b);
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void kbHold(short key){
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key; 
	if (key == VK_LMENU || key == VK_CONTROL) ip.ki.dwFlags = 0; else ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	SendInput(1, &ip, sizeof(INPUT));
}

void kbRelease(short key) {
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; SendInput(1, &ip, sizeof(INPUT));
}

void kbPress(string code, short key) {
	string s1 = qq.substr(0, qq.find(">"));//<x*
	s2 = "1"; if (code.substr(code.length() - 1, code.length()) == "*") {
		s2 = s1.substr(qq.find("*"));//#
		s2 = s2.substr(1, s2.length());
	}//cout << "s1: " << s1 << endl;cout << "s2: " << s2 << endl;
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.wVk = key;
	for (int j = 0; j < stoi(s2); j++) {
		if (code == "<,*") { 
			Sleep(150); GetAsyncKeyState(VK_ESCAPE); if (GetAsyncKeyState(VK_ESCAPE))return;
		}else{
			ip.ki.dwFlags = 0; SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = 2; SendInput(1, &ip, sizeof(INPUT));
		}
	}rei();
}

void clearAllKeys() {
	for (int i = 65; i < 91; i++) {	GetAsyncKeyState(i); }
	for (int i = 48; i < 58; i++) { GetAsyncKeyState(i); }
	GetAsyncKeyState(cKey);
	GetAsyncKeyState(reKey);
	GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_PAUSE);
	GetAsyncKeyState(VK_SPACE);
}

void shftRelease() {
	INPUT ip; ip.type = INPUT_KEYBOARD; ip.ki.dwFlags = 2;
	ip.ki.wVk = VK_LSHIFT;	
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_RSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	if (shft) { shft = false; }
}

void mouseEvent(short key) {
	INPUT ip; ip.type = INPUT_MOUSE; ip.mi.time = 0;
	ip.mi.dwFlags = key;
	SendInput(1, &ip, sizeof(ip));
}

inline bool qqb(string s) { return qq.substr(0, s.length()) == s; }

void scanDb(); void conn() {//<connect:>	
	bool con = false; string qqs = qq.substr(0, qq.find(">")+1);	
	if (qqs.find(':') != std::string::npos || qqs.find('-') != std::string::npos) {// :> | ->
		if (qqs.substr(qqs.length() - 2, 2) == ":>" || qqs.substr(qqs.length() - 2, 2) == "->") {
			con=true;}
	}
	if (con){ ifstream f(database); string cell; while (getline(f, cell)) {
		if (qqs == cell.substr(0, qqs.length())) { //<h:> | <h->
			string re1 = tail;
			string qqc = qq.substr(0, qq.find(">"));
			tail = qq.replace(qq.find(qqc + ">"), qqc.length() + 1, cell.substr(cell.substr(0, qqc.length()).length(), cell.length()));
			re = ">" + tail; strand.clear(); scanDb(); re.clear();
			clearAllKeys();
			strand.clear();
			tail = re1;
			f.close(); 
			i = tail.length();
			return;
		}
		}f.close();kbHold(VK_LSHIFT); kb('<'); shftRelease();
	}else{kbHold(VK_LSHIFT);kb('<');shftRelease();}
}

void scanDb() {
	ifstream f(database);string cell;while (getline(f, cell)) { //cout << cell << endl;
		if (re > "" || cell.substr(0, strand.length() + 1) == strand + ":" || cell.substr(0, strand.length() + 1) == strand + "-" || (strandLengthMode && cell.substr(0, strandLength) == strand && cell.substr(0, 1) != "<") || (cell.substr(0, 1) == "<" && cell.substr(0, strand.length()+1) == strand + ">")    ) { //<found:tail, <found-tail, found:tail, <found>tail
			
			if (re > "") { 
				cell = re; 
				if (re.substr(0, 4) == ">xy:") {POINT pt; GetCursorPos(&pt); string to_string(long v); cell=">xy:"+to_string(pt.x)+"-"+to_string(pt.y)+">";}
			}
			
			tail = cell.substr(strand.length() + 1 , cell.length() - strand.length() + 1); //:tail
			if (cell.substr(0, strand.length() + 1) == strand + "-") {//<bs> strand.length()
				if (strand.find("<")==0) { strand.replace(0, 1, ""); }//qScanOnly filter
				for (size_t ii = 0; ii < strand.length(); ii++) { kb(VK_BACK);GetAsyncKeyState(VK_BACK); }
			 	if (cell.substr(0,1)=="<") tail = cell.substr(strand.length() + 2 , cell.length() - strand.length() + 2); //:tail
			}
			if (strandLengthMode && cell.substr(0, 1) != "<") { 
				if (re == "") tail = cell.substr(strandLength, cell.length());
				if (re > "") tail = re.substr(1,re.length());
			}
			if (tail.substr(0,1) == ">") tail=tail.substr(1, tail.length());//<found>tail

			if (showOuts) { cout << "found: " << cell << endl; }
			if (showOuts) { cout << "tail: " << tail << endl; }

			if (tail.find("<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }

			for (i = 0; i < tail.length(); i++)	{
				GetAsyncKeyState(VK_ESCAPE);if (GetAsyncKeyState(VK_ESCAPE)) { return; }//stop

				if (showOuts) { cout << "ctail: " << tail.substr(i, 1) << endl; }
				string ctail = tail.substr(i, 1);//extracted char from tail
				
				switch (ctail[0]) {
				case'<':
					qq = tail.substr(i, tail.length()-i); //<test>										
					if (showOuts) { cout << "qq: " << qq << endl; }
 					if (qq.find(":")!=std::string::npos) { //<test:#>
						qp = qq.substr(qq.find(":") + 1, qq.find(">") - qq.find(":") - 1);//#
						qx = qp.substr(0, qp.find("-"));//x
						qy = qp.substr(qp.find("-") + 1, qp.find(">") - qp.find("-") - 1);//y
						//cout << "qp: " << qp  << endl; cout << "qx: " << qx << endl; cout << "qy: " << qy << endl;
					}
					switch (qq[1]) {
					case',':
						if (qqb("<,>")) {
							Sleep(150);	rei();
						}else if (qqb("<,*")) {//<,*#>
							kbPress("<,*", VK_F7); }
						else{kbHold(VK_LSHIFT);kb('<');shftRelease();}
						break;
					case'\'':
						if (qqb("<'")) { rei(); }//<'comments>
						break;
					case'a':
						if (qqb("<alt>")) { kbHold(VK_LMENU); rei(); }
						else if (qqb("<alt->")) { kbRelease(VK_LMENU); rei(); }
						else if (qqb("<app:")) {
							for (int w = 0; w < 25; w++) {
								if (w >= 24) { if (showOuts) { cout << "app: " << qp << " not found\n"; strand.clear(); }return; }
								DWORD pid; HWND h = FindWindowA(0, qp.c_str());	GetWindowThreadProcessId(h, &pid);
								if (h) { ShowWindow(h, SW_RESTORE); SetForegroundWindow(h); w = 24; continue; }
								if (GetAsyncKeyState(VK_ESCAPE)) return;
								Sleep(333);
							}Sleep(150);
							rei();
						}else{conn();}
					break;
					case 'A':
						if (qqb("<App:")) {
							DWORD pid; HWND h = FindWindowA(0, qp.c_str());	GetWindowThreadProcessId(h, &pid);
							if (h) { ShowWindow(h, SW_RESTORE); SetForegroundWindow(h); continue; }
							else { if (showOuts) { cout << "fail: <App:" << qp << ">" << endl; }return; }
							rei();
						}else{conn();}
						break;
					case'b':
						if (qqb("<bs>")) { kbPress("<bs>", VK_BACK); }
						else if (qqb("<bs*")) { kbPress("<bs*", VK_BACK); }else{conn();}
						break;
					case'c':
						if (qqb("<ctrl>")) { kbHold(VK_CONTROL); rei(); }
						else if (qqb("<ctrl->")) { kbRelease(VK_CONTROL); rei(); }else{conn();}
						break;
					case'd':
						if (qqb("<down>")) { kbPress("<down>", VK_DOWN); }
						else if (qqb("<down*")) { kbPress("<down*", VK_DOWN); }
						else if (qqb("<delete>")) { kbPress("<delete>", VK_DELETE); }
						else if (qqb("<delete*")) { kbPress("<delete*", VK_DELETE); }else{conn();}
						break;
					case'e':
						if (qqb("<enter>")) { kbPress("<enter>", VK_RETURN); }
						else if (qqb("<enter*")) { kbPress("<enter*", VK_RETURN); }
						else if (qqb("<end>")) { kbPress("<end>", VK_END); }
						else if (qqb("<end*")) { kbPress("<end*", VK_END); }
						else if (qqb("<esc>")) { kbPress("<esc>", VK_ESCAPE); }
						else if (qqb("<esc*")) { kbPress("<esc*", VK_ESCAPE); }else{conn();}
						break;
					case'f':			
						if (qqb("<f1>")) { kbPress("<f1>", VK_F1); }
						else if (qqb("<f2>")) { kbPress("<f2>", VK_F2); }
						else if (qqb("<f3>")) { kbPress("<f3>", VK_F3); }
						else if (qqb("<f4>")) { kbPress("<f4>", VK_F4); }
						else if (qqb("<f5>")) { kbPress("<f5>", VK_F5); }
						else if (qqb("<f6>")) { kbPress("<f6>", VK_F6); }
						else if (qqb("<f7>")) { kbPress("<f7>", VK_F7); }
						else if (qqb("<f8>")) { kbPress("<f8>", VK_F8); }
						else if (qqb("<f9>")) { kbPress("<f9>", VK_F9); }
						else if (qqb("<f10>")) { kbPress("<f10>", VK_F10); }
						else if (qqb("<f11>")) { kbPress("<f11>", VK_F11); }
						else if (qqb("<f12>")) { kbPress("<f12>", VK_F12); }else{conn();}
						break;
					case'h':
						if (qqb("<home>")) { kbPress("<home>", VK_HOME); }
						else if (qqb("<home*")) { kbPress("<home*", VK_HOME); }else{conn();}
						break;
					case'l':
						if (qqb("<lc>")) {//left click
							mouseEvent(MOUSEEVENTF_LEFTDOWN);
							mouseEvent(MOUSEEVENTF_LEFTUP);
							rei();
						}
						else if (qqb("<lh>")) {//left hold
							mouseEvent(MOUSEEVENTF_LEFTDOWN);
							rei();
						}
						else if (qqb("<lr>")) {//left release
							mouseEvent(MOUSEEVENTF_LEFTUP);
							rei();
						}
						else if (qqb("<left>")) { kbPress("<left>", VK_LEFT); }
						else if (qqb("<left*")) { kbPress("<left*", VK_LEFT); }else{conn();}
						break;
					case'm':
						if (qqb("<ms:")) {
							Sleep(stoi(qp));
							rei();
						}
						else if (qqb("<menu>")) { kbPress("<menu>", VK_APPS); }else{conn();}
						break;
					case'p':
						if (qqb("<ps>")) { kbPress("<ps>", VK_SNAPSHOT); }else{conn();}
						break;
					case'r':
						if (qqb("<rp>")) {//return pointer
							SetCursorPos(qxc, qyc);
							rei();
						}
						else if (qqb("<rc>")) {//right click
							mouseEvent(MOUSEEVENTF_RIGHTDOWN);
							mouseEvent(MOUSEEVENTF_RIGHTUP);
							rei();
						}
						else if (qqb("<rh>")) {//right hold
							mouseEvent(MOUSEEVENTF_RIGHTDOWN);
							rei();
						}
						else if (qqb("<rr>")) {//right release
							mouseEvent(MOUSEEVENTF_RIGHTUP);
							rei();
						}
						else if (qqb("<right>")) { kbPress("<right>", VK_RIGHT); }
						else if (qqb("<right*")) { kbPress("<right*", VK_RIGHT); }else{conn();}
						break;
					case's':
						if (qqb("<shift>")) { kbHold(VK_LSHIFT); rei(); }
						else if (qqb("<shift->")) { kbRelease(VK_LSHIFT); kbRelease(VK_RSHIFT); rei(); }
						else if (qqb("<sleep:")) {
							Sleep(stoi(qp));
							rei();
						}
						else if (qqb("<space>")) { kbPress("<space>", VK_SPACE); }
						else if (qqb("<space*")) { kbPress("<space*", VK_SPACE); }else{conn();}
						break;
					case't':
						if (qqb("<tab>")) { kbPress("<tab>", VK_TAB); }
						else if (qqb("<tab*")) { kbPress("<tab*", VK_TAB); }else{conn();}
						break;
					case'u':
						if (qqb("<up>")) { kbPress("<up>", VK_UP); }
						else if (qqb("<up*")) { kbPress("<up*", VK_UP); }else{conn();}
						break;					
					case'w':
						if (qqb("<win>")) { kbHold(VK_LWIN); rei(); }
						else if (qqb("<win->")) { kbRelease(VK_LWIN); rei(); }else{conn();}
						break;
					case'x':
						if (qqb("<xy:")){
						SetCursorPos(stoi(qx), stoi(qy));
						rei();
						}else{conn();}
						break;					
					default:
						conn();
					}//<x>
					break;
				default:
					if ((ctail == "<") || (ctail == ">") || (ctail == "?") || (ctail == ":") || (ctail == "\"") || (ctail == "|") || (ctail == "}") || (ctail == "{") || (ctail == "+") || (ctail == "_") || (ctail == ")") || (ctail == "(") || (ctail == "*") || (ctail == "&") || (ctail == "^") || (ctail == "%") || (ctail == "$") || (ctail == "#") || (ctail == "@") || (ctail == "!") || (ctail == "~") ||
						(ctail == "A") || (ctail == "B") || (ctail == "C") || (ctail == "D") || (ctail == "E") || (ctail == "F") || (ctail == "G") || (ctail == "H") || (ctail == "I") || (ctail == "J") || (ctail == "K") || (ctail == "L") || (ctail == "M") || (ctail == "N") || (ctail == "O") || (ctail == "P") || (ctail == "Q") || (ctail == "R") || (ctail == "S") || (ctail == "T") || (ctail == "U") || (ctail == "V") || (ctail == "W") || (ctail == "X") || (ctail == "Y") || (ctail == "Z")) {
						shft = true;
					}
					if (shft) kbHold(VK_LSHIFT);
					kb(ctail[0]);
					if (shft) shftRelease();
					break;
				}
				GetAsyncKeyState(VkKeyScan(ctail[0])); //clear
			}
			clearAllKeys();
			strand.clear();
			break;
		}
	}
	f.close();
}

void out(string ai){ re = ">" + ai; strand.clear(); scanDb(); re.clear(); }

void printDb() {
	ifstream f(database);
	string cell;
	while (getline(f, cell)) { cout << cell << endl; }
	f.close(); cout << endl;
}

void printXy() { 
	POINT pt; GetCursorPos(&pt);
	if (strand=="x") {  if (showOuts) cout << "xy: " << pt.x << "-" << pt.y << endl; } 
	else { string to_string(long v); out("<bs*2>"); out("xy:" + to_string(pt.x) + "-" + to_string(pt.y) + ">"); }
}

void printSe() {
	cout << "Settings interface" << endl;
	cout << "<s s:  Toggle show strand: " << showStrand<< endl;
	cout << "<s o:  Toggle show outs: " << showOuts<< endl;
	cout << "<q s:  Toggle < scan only mode: " << qScanOnly << endl;
	cout << "<q k:  Change < key: " << cKey << endl;
	if(!qScanOnly){cout << "<s lm:  Strand length mode: " << strandLengthMode << endl;
	if (strandLengthMode) cout << "<s le:  Strand length: " << strandLength << endl;}
	cout << "<r e:  Change repeat key: " << reKey << endl;
	//cout << "<f r:  Change frequency: " << frequency << endl;
	cout << "<d b:  Change database: " << database << endl;
	cout << "Hold RCtrl LCtrl or Esc on startup:  Change < key" << endl;
	cout << "Hold O on startup:  Show strand, show outs: 0" << endl;
	//cout << "Hold Q on startup:  Ctrl scan only: true" << endl;
	cout << "\nLoad settings: Copy to "<<settings << endl; 
	cout << "ShowSettings:" << showSettings << endl;
	cout << "ShowIntro:" << showIntro << endl;
	cout << "ShowStrand:" << showStrand  << endl;
	cout << "ShowOuts:" << showOuts << endl;
	cout << "CtrlScanOnlyMode:" << qScanOnly << endl;
	cout << "CtrlKey:" << cKey << endl;
	cout << "StrandLengthMode:" << strandLengthMode << endl;
	cout << "StrandLength:" << strandLength << endl;
	cout << "RepeatKey:" << reKey << endl;
	cout << "Frequency:" << frequency << endl;
	cout << "Ignore_A-Z:" << ignoreAZ << endl;
	cout << "Ignore_0-9:" << ignore09 << endl;
	cout << "StartHidden:" << startHidden << endl;
	cout << "\n";
}

void printIn() {
	string se; if (showIntro){cout<<"Interface"<<endl;
	if (qScanOnly)se = "<se"; else se = "se"; cout << se << ":  Settings" << endl;
	if (qScanOnly)se = "<db"; else se = "db"; cout << se << ":  Database" << endl;
	cout << "<xy:  <xy:>" << endl;
	cout << "Esc:  Stop" << endl;
	cout << "Esc + H:  Toggle visibility" << endl;
	string c; if (cKey == VK_CONTROL) c = "Ctrl"; else if (cKey == VK_LCONTROL) c = "LCtrl"; else if (cKey == VK_RCONTROL) c = "RCtrl"; else if (cKey == VK_ESCAPE) c = "Esc";
	cout << c << ":  Toggle <" << endl;
	cout << "Scroll Lock:  Repeat" << endl;
	cout << "Pause Break:  Clear" << endl;
	cout << "<odb:  Open database: " << database << endl;
	cout << "<ose:  Open settings: " << settings << endl;
	cout << "\nAPI\n<ms:1500>  Milliseconds sleep\n<,>  150 milliseconds sleep\n<xy:0-0>  Move pointer\n<rp>  Return pointer\n<lc><rc><lh><rh><lr><rr>  left right click hold release\n<ctrl><shift><alt><win>  Hold key\n<ctrl-><shift-><alt-><win->  Release key\n<up><right><down><left><delete><esc><bs><home><end><space><tab>  Press key\n<bs*2>  Press twice\n<menu>  Press Menu key\n<ps>  Press Print Screen\n<f1>  Press F1 (F1-F12)\n<app:title>  Activate app via title" << endl;
	string l = "h:ello\n"; string l1 = "h, "; if (qScanOnly) { l = ""; l1 = ""; } cout << "\n" << database << " hello example\n" << l << "<h->Hello\n<i:><bs><h->!\nCopy examples to " << database << ", save, then press " << l1 << "ctrl h, or ctrl i\n" << endl;
}}

void changeKey(string msg, int ke) {
	kb(VK_ESCAPE); int sl; cout << "Enter new "<< msg << ":" << endl;  cin >> sl; if (sl > 0) { ke = sl; }
	else { return; } clearAllKeys(); cout << msg << ": " << ke << endl; strand.clear();
}

void key(string k) {
	strand.append(k);
	if (strandLengthMode && (int)strand.length()>strandLength && strand.substr(0,1)!="<") { strand = strand.substr(strand.length() - strandLength); }
	if (showStrand) cout << "strand: " << strand.c_str() << endl;

	scanDb();if (strand>""){
	if (strand == "db"|| strand == "<db") { printDb();  }
	if (strand=="se"|| strand == "<se"){ printSe(); }
	if (strand == "x" || strand == "<xy") { printXy(); }
	if (strand == "<odb") { out("<win>r<win-><,>" + database + "<enter>"); } 
	if (strand == "<ose") { out("<win>r<win-><,>" + settings + "<enter>"); } 
	if (strand == "<q s") { qScanOnly = !qScanOnly; cout << "<q s: " << qScanOnly <<endl; strand.clear(); }
	if (strand == "<s lm") { strandLengthMode = !strandLengthMode; cout << "Strand length mode: " << strandLengthMode << endl; strand.clear(); if (strandLengthMode) { cout << "strand length: " << strandLength << endl; } }
	if (strand == "<s le") { kb(VK_ESCAPE); int sl; cout << "Enter new strand length:" << endl;  cin >> sl; if (sl > 0) { strandLength = sl; } else { return; } clearAllKeys(); cout << "strand length: " << strandLength << endl; strand.clear(); }
	if (strand == "<r e") { kb(VK_ESCAPE); int sl; cout << "Enter new repeat key:" << endl;  cin >> sl; if (sl > 0) { reKey = sl; } else { return; } clearAllKeys(); cout << "repeat key: " << reKey << endl; strand.clear(); }
	if (strand == "<q k") { kb(VK_ESCAPE); int sl; cout << "Enter new < key:" << endl;  cin >> sl; if (sl > 0) { cKey = sl; } else { return; } clearAllKeys(); cout << "< key: " << cKey << endl; strand.clear(); }
	if (strand == "<f r") { kb(VK_ESCAPE); int sl; cout << "Enter new frequency:" << endl;  cin >> sl; if (sl > 0) { frequency = sl; } else { return; } clearAllKeys(); cout << "frequency: " << frequency << endl; strand.clear(); }
	if (strand == "<d b") { kb(VK_ESCAPE); string sl; cout << "Enter new database:" << endl;  cin >> sl; if (sl > "") { database = sl; } else { return; } clearAllKeys(); cout << "database: " << database << endl; strand.clear(); }
	if (strand == "<s s") { showStrand = !showStrand; cout << "<s s: " << showStrand <<endl; strand.clear(); }
	if (strand == "<s o") { showOuts = !showOuts; cout << "<s o: " << showOuts <<endl; strand.clear(); }  }
}

void loadSe() {
	if (showSettings) {
		ifstream f(settings); string cell;	while (getline(f, cell)) {
			string se = cell.substr(0, cell.find(":") + 1);
			int v = stoi(cell.substr(cell.find(":") + 1));
			if (se == "ShowSettings:") { showSettings = v; if (!showSettings) continue; }
			if (showSettings) cout << se << v << endl;
			if (se == "StrandLengthMode:") { strandLengthMode = v; continue; }
			if (se == "StrandLength:") { strandLength = v; continue; }
			if (se == "CtrlScanOnlyMode:") { qScanOnly = v; continue; }
			if (se == "CtrlKey:") { cKey = v; continue; }
			if (se == "Frequency:") { frequency = v; continue; }
			if (se == "RepeatKey:") { reKey = v; continue; }
			if (se == "ShowStrand:") { showStrand = v; continue; }
			if (se == "ShowOuts:") { showOuts = v; continue; }
			if (se == "ShowIntro:") { showIntro = v; continue; }
			if (se == "Ignore_A-Z:") { ignoreAZ = v; continue; }
			if (se == "Ignore_0-9:") { ignore09 = v; continue; }
			if (se == "StartHidden:") { startHidden = v; continue; }
		}f.close();if (showSettings)cout<<"Loaded "<<settings <<endl;
	}
}

int main() {
	cout << "@dnaspider\n\n";
	loadSe();
	if (startHidden)ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (showSettings)cout << "\n";
	if (GetAsyncKeyState(81)) { qScanOnly = true; }//q
	if (GetAsyncKeyState(79)) { showOuts = false; showStrand = false; }//o
	if (GetAsyncKeyState(VK_RCONTROL))cKey = VK_RCONTROL;
	if (GetAsyncKeyState(VK_LCONTROL))cKey = VK_LCONTROL;
	if (GetAsyncKeyState(VK_ESCAPE))cKey = VK_ESCAPE;
	printIn();
	for (;; Sleep(frequency)) {
		if (GetAsyncKeyState(VK_BACK)) {
			strand = strand.substr(0, strand.length() - 1);
			if (showStrand) { cout << "strand: " << strand.c_str() << endl; }
		}
		if (GetAsyncKeyState(cKey)) {
			if (strand.find("<") == 0) strand.clear();//<strand
			//if (strand.find("<") == 0) { if (qScanOnly) { strand = "<"; } else { strand.clear(); } }//<
			else if (strand.substr(0) != "<") { clearAllKeys(); strand = "<"; }//not <strand
			if (showStrand) { cout << "strand: " << strand.c_str() << endl; }
		}
		if (GetAsyncKeyState(reKey)) { out(tail); }//repeat
		if (GetAsyncKeyState(VK_PAUSE)) { if (strand.find("<") == 0) strand = "<"; else strand.clear(); }		
		if (GetAsyncKeyState(VK_ESCAPE)) { GetAsyncKeyState(0x48); if (GetAsyncKeyState(0x48)) { if ((bool)IsWindowVisible(GetConsoleWindow()) == true) { ShowWindow(GetConsoleWindow(), SW_HIDE); } else { ShowWindow(GetConsoleWindow(), SW_SHOW); } } }
		if (qScanOnly) { if (qScanOnly && strand.substr(0, 1) == "<") {} else { continue; } }
#pragma region "az"
		if (!ignoreAZ){ if (GetAsyncKeyState(0x41)) { key("a"); }
		if (GetAsyncKeyState(0x42)) { key("b"); }
		if (GetAsyncKeyState(0x43)) { key("c"); }
		if (GetAsyncKeyState(0x44)) { key("d"); }
		if (GetAsyncKeyState(0x45)) { key("e"); }
		if (GetAsyncKeyState(0x46)) { key("f"); }
		if (GetAsyncKeyState(0x47)) { key("g"); }
		if (GetAsyncKeyState(0x48)) { key("h"); }
		if (GetAsyncKeyState(0x49)) { key("i"); }
		if (GetAsyncKeyState(0x4A)) { key("j"); }
		if (GetAsyncKeyState(0x4B)) { key("k"); }
		if (GetAsyncKeyState(0x4C)) { key("l"); }
		if (GetAsyncKeyState(0x4D)) { key("m"); }
		if (GetAsyncKeyState(0x4E)) { key("n"); }
		if (GetAsyncKeyState(0x4F)) { key("o"); }
		if (GetAsyncKeyState(0x50)) { key("p"); }
		if (GetAsyncKeyState(0x51)) { key("q"); }
		if (GetAsyncKeyState(0x52)) { key("r"); }
		if (GetAsyncKeyState(0x53)) { key("s"); }
		if (GetAsyncKeyState(0x54)) { key("t"); }
		if (GetAsyncKeyState(0x55)) { key("u"); }
		if (GetAsyncKeyState(0x56)) { key("v"); }
		if (GetAsyncKeyState(0x57)) { key("w"); }
		if (GetAsyncKeyState(0x58)) { key("x"); }
		if (GetAsyncKeyState(0x59)) { key("y"); }
		if (GetAsyncKeyState(0x5A)) { key("z"); } }
#pragma endregion
#pragma region "09"
		if (!ignore09) { if (GetAsyncKeyState(0x30)) { key("0"); }
		if (GetAsyncKeyState(0x31)) { key("1"); }
		if (GetAsyncKeyState(0x32)) { key("2"); }
		if (GetAsyncKeyState(0x33)) { key("3"); }
		if (GetAsyncKeyState(0x34)) { key("4"); }
		if (GetAsyncKeyState(0x35)) { key("5"); }
		if (GetAsyncKeyState(0x36)) { key("6"); }
		if (GetAsyncKeyState(0x37)) { key("7"); }
		if (GetAsyncKeyState(0x38)) { key("8"); }
		if (GetAsyncKeyState(0x39)) { key("9"); } }
#pragma endregion
		if (GetAsyncKeyState(VK_SPACE)) { key(" "); }
	}
}