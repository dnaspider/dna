// @dnaspider
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <windows.h.>
#include <winuser.h>
using namespace std;

#pragma region "global var"
//bool strandLengthMode = false;
//int strandLength = 3;
bool qScanOnly = false;
string database = "C:\\dna\\db.txt";
int frequency = 150; //ms response -> vk_
short reKey = VK_SCROLL; //repeat
short cKey = VK_CONTROL; // < 
string strand = ""; //<<
string tail=""; //strand:tail
string re = "";//repeat clone
bool showKey = false; //cout >>
bool showStrand = true; //cout >>
bool showOuts = true; //cout >> 
string s2; //#
string qq; //<x>
string qp; //<x:#>
string qx,qy; //<xy:#-#>
auto qxc = 0;//<rp>
auto qyc = 0; 
bool shft = false;
int i = 0;
#pragma endregion

//global sub
void hardScan1(string code, short key) {
	keybd_event(key, 0, 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	if (i + code.length()-1 < tail.length()) { i += code.length()-1; }
}

void hardScan2(string code, short key) {
	string s1 = qq.substr(0, qq.find(">"));//<x*
	//cout << "s1: " << s1 << endl;
	s2 = s1.substr(qq.find("*"));//#
	s2 = s2.substr(1, s2.length() );
	//cout << "s2: " << s2 << endl;
	for (int j = 0; j < stoi(s2); j++) {
		keybd_event(key, 0, 0, 0);
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	}
	if (i += s1.length()-1 < tail.length()) { i += s1.length()-1; }
}

void clearAllKeys() {
	for (int i = 65; i < 91; i++) {	GetAsyncKeyState(i); }
	for (int i = 48; i < 58; i++) { GetAsyncKeyState(i); }
	GetAsyncKeyState(cKey);
	GetAsyncKeyState(VK_SPACE);
}

void kb(short b) {
	keybd_event(VkKeyScan(b), 0, 0, 0);//press
	keybd_event(VkKeyScan(b), 0, KEYEVENTF_KEYUP, 0);
}
void shftHold() {
	keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
}
void shftRelease() {
	keybd_event(VK_LSHIFT, 0, 2, 0);
	keybd_event(VK_RSHIFT, 0, 2, 0);
	if (shft) { shft = false; }
}

void rei(int r){ if (i + r < tail.length()) { i += r; } }

void scanDb() {
	ifstream f(database);
	string cell;

	while (getline(f, cell)) {
		//cout << cell << endl;
		if (re > "" || cell.substr(0, strand.length() + 1) == strand + ":" || cell.substr(0, strand.length() + 1) == strand + "-"  ) { //found:tail //||	(cell.substr(0,  strandLength)==strand && strandLengthMode && cell.substr(0,1)!="<")
			if (re > "") { cell = re; }
			
			tail = cell.substr(strand.length() + 1 , cell.length() - strand.length() + 1); //:tail
						
			if (cell.substr(0, strand.length() + 1) == strand + "-") {//<bs> strand.length()
				if (strand.find("<")==0) { strand.replace(0, 1, ""); }//qScanOnly filter
				//cout << "strand-" << strand << " strand.l " << strand.length()  << endl;
				for (int i = 0; i < strand.length(); i++) {
					keybd_event(VK_BACK, 0, 0, 0);//press
					keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
					GetAsyncKeyState(VK_BACK); //clear
				}
			 	if (cell.substr(0,1)=="<") tail = cell.substr(strand.length() + 2 , cell.length() - strand.length() + 2); //:tail
			}
					
			//if (strandLengthMode) tail = cell.substr(strandLength,cell.length());
			//if (strandLengthMode && re > "") tail = re.substr(1,re.length());

			if (showOuts) { cout << "found: " << cell << endl; }
			if (showOuts) { cout << "tail: " << tail << endl; }
						
			for (i = 0; i < tail.length(); i++)	{				
				GetAsyncKeyState(VK_ESCAPE);if (GetAsyncKeyState(VK_ESCAPE)) { continue; }//stop

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
					//<x>
					if (qq.substr(0, 3) == "<,>"){
						Sleep(150);
						if (i + 2 < tail.length()) { i += 2; }
					}
					if (qq.substr(0,4)=="<ms:") {
						Sleep(stoi(qp));							
						if (i + qp.length() + 4 < tail.length()) { i += qp.length() + 4; }
					} 
					
					else if (qq.substr(0, 4) == "<xy:") {
						if (tail.find("<rp>") != std::string::npos) { POINT pt; GetCursorPos(&pt); qxc = pt.x; qyc = pt.y; }
						SetCursorPos(stoi(qx), stoi(qy));
						if (i + qp.length() + 4 < tail.length()) { i += qp.length() + 4; }
					}
					else if (qq.substr(0, 4) == "<rp>") {//return pointer
						SetCursorPos(qxc, qyc);
						if (i + 3 < tail.length()) { i += 3; }
					}
					else if (qq.substr(0, 4) == "<lh>"){//left hold
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						rei(3);
					}
					else if (qq.substr(0, 4) == "<lr>"){//left release
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						rei(3);
					}
					else if (qq.substr(0, 4) == "<rc>"){//right click
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						rei(3);
					}
					else if (qq.substr(0, 4) == "<rh>"){//right hold
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						rei(3);
					}
					else if (qq.substr(0, 4) == "<rr>"){//right release
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						rei(3);
					}
					
					else if (qq.substr(0, 7) == "<shift>"){ keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0); rei(6); }
					else if (qq.substr(0, 8) == "<shift->"){ keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0); keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0); rei(7); }
					else if (qq.substr(0, 6) == "<ctrl>"){ keybd_event(VK_CONTROL, 0, 0, 0); rei(5); }
					else if (qq.substr(0, 7) == "<ctrl->"){ keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); rei(6); }
					else if (qq.substr(0, 5) == "<alt>"){ keybd_event(VK_LMENU, 0, 0, 0); rei(4); }
					else if (qq.substr(0, 6) == "<alt->"){ keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);rei(5); }
					else if (qq.substr(0, 5) == "<win>"){ keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0); rei(4); }
					else if (qq.substr(0, 6) == "<win->"){ keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	rei(5);	}

#pragma region "f1-f12"					
					else if (qq.substr(0, 4) == "<f1>"){ hardScan1("<f1>", VK_F1); }
					else if (qq.substr(0, 4) == "<f2>"){ hardScan1("<f2>", VK_F2); }
					else if (qq.substr(0, 4) == "<f3>"){ hardScan1("<f3>", VK_F3); }
					else if (qq.substr(0, 4) == "<f4>"){ hardScan1("<f4>", VK_F4); }
					else if (qq.substr(0, 4) == "<f5>"){ hardScan1("<f5>", VK_F5); }
					else if (qq.substr(0, 4) == "<f6>"){ hardScan1("<f6>", VK_F6); }
					else if (qq.substr(0, 4) == "<f7>"){ hardScan1("<f7>", VK_F7); }
					else if (qq.substr(0, 4) == "<f8>"){ hardScan1("<f8>", VK_F8); }
					else if (qq.substr(0, 4) == "<f9>"){ hardScan1("<f9>", VK_F9); }
					else if (qq.substr(0, 5) == "<f10>"){ hardScan1("<f10>", VK_F10); }
					else if (qq.substr(0, 5) == "<f11>"){ hardScan1("<f11>", VK_F11); }
					else if (qq.substr(0, 5) == "<f12>"){ hardScan1("<f12>", VK_F12); }
#pragma endregion

					else if (qq.substr(0, 4) == "<up>"){ hardScan1("<up>", VK_UP); }
					else if (qq.substr(0, 4) == "<up*") { hardScan2("<up*", VK_UP); }
					else if (qq.substr(0, 7) == "<right>"){ hardScan1("<right>", VK_RIGHT); }
					else if (qq.substr(0, 7) == "<right*"){ hardScan2("<right*", VK_RIGHT); }
					else if (qq.substr(0, 6) == "<down>"){ hardScan1("<down>", VK_DOWN); }
					else if (qq.substr(0, 6) == "<down*"){ hardScan2("<down*", VK_DOWN); }
					else if (qq.substr(0, 6) == "<left>"){ hardScan1("<left>", VK_LEFT); }
					else if (qq.substr(0, 6) == "<left*"){ hardScan2("<left*", VK_LEFT); }
					else if (qq.substr(0, 4) == "<bs>") { hardScan1("<bs>", VK_BACK); }
					else if (qq.substr(0, 4) == "<bs*") { hardScan2("<bs*", VK_BACK); }
					else if (qq.substr(0, 5) == "<tab>") { hardScan1("<tab>", VK_TAB); }
					else if (qq.substr(0, 5) == "<tab*") { hardScan2("<tab*", VK_TAB); }
					else if (qq.substr(0, 7) == "<enter>"){ hardScan1("<enter>", VK_RETURN); }
					else if (qq.substr(0, 7) == "<enter*"){ hardScan2("<enter*", VK_RETURN); }
					else if (qq.substr(0, 7) == "<space>"){ hardScan1("<space>", VK_SPACE); }
					else if (qq.substr(0, 7) == "<space*"){ hardScan2("<space*", VK_SPACE); }
					else if (qq.substr(0, 8) == "<delete>"){ hardScan1("<delete>", VK_DELETE); }
					else if (qq.substr(0, 8) == "<delete*"){ hardScan2("<delete*", VK_DELETE); }
					else if (qq.substr(0, 6) == "<home>"){ hardScan1("<home>", VK_HOME); }
					else if (qq.substr(0, 6) == "<home*"){ hardScan2("<home*", VK_HOME); }
					else if (qq.substr(0, 5) == "<end>"){ hardScan1("<end>", VK_END); }
					else if (qq.substr(0, 5) == "<end*") { hardScan2("<end*", VK_END); }
					else if (qq.substr(0, 5) == "<esc>"){ hardScan1("<esc>", VK_ESCAPE); }
					else if (qq.substr(0, 5) == "<esc*"){ hardScan2("<esc*", VK_ESCAPE); }
					else if (qq.substr(0, 6) == "<menu>"){ hardScan1("<menu>", VK_MENU); }
					else if (qq.substr(0, 4) == "<ps>"){ hardScan1("<ps>", VK_SNAPSHOT); }
					else{//<
						if (tail.substr(i, 1) == "<") { 
							
							ifstream f(database);string cell;while (getline(f , cell)) { //<connect:>
								//string qqc = qq.substr(0, qq.find(">"));
								//string cellc = cell.substr(0, qq.substr(0, qq.find(">")).length() );
								//string cellt = cell.substr(cell.substr(0, qq.substr(0, qq.find(">")).length()).length(), cell.length());
								if (qq.substr(0, qq.find(">")) == (cell.substr(0, qq.substr(0, qq.find(">")).length()))) {//<h:>
									string re1 = tail;
									tail = qq.replace(qq.find(qq.substr(0, qq.find(">")) + ">"), qq.substr(0, qq.find(">")).length()+1, cell.substr(cell.substr(0, qq.substr(0, qq.find(">")).length()).length(), cell.length()));
									re = ">" + tail; strand.clear(); scanDb(); re.clear();
									clearAllKeys();
									strand.clear();
									tail = re1;
									return;
								}
							}
							f.close();

							keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0); //stock <
							keybd_event(VkKeyScan(ctail[0]), 0, 0, 0);
							keybd_event(VkKeyScan(ctail[0]), 0, KEYEVENTF_KEYUP, 0);
							shftRelease();							
							if (showOuts) { cout << "ctail: " << tail.substr(i, 1) << endl; }
						}
					}
					break;
				default:
					if ((ctail == "<") || (ctail == ">") || (ctail == "?") || (ctail == ":") || (ctail == "\"") || (ctail == "|") || (ctail == "}") || (ctail == "{") || (ctail == "+") || (ctail == "_") || (ctail == ")") || (ctail == "(") || (ctail == "*") || (ctail == "&") || (ctail == "^") || (ctail == "%") || (ctail == "$") || (ctail == "#") || (ctail == "@") || (ctail == "!") || (ctail == "~") ||
						(ctail == "A") || (ctail == "B") || (ctail == "C") || (ctail == "D") || (ctail == "E") || (ctail == "F") || (ctail == "G") || (ctail == "H") || (ctail == "I") || (ctail == "J") || (ctail == "K") || (ctail == "L") || (ctail == "M") || (ctail == "N") || (ctail == "O") || (ctail == "P") || (ctail == "Q") || (ctail == "R") || (ctail == "S") || (ctail == "T") || (ctail == "U") || (ctail == "V") || (ctail == "W") || (ctail == "X") || (ctail == "Y") || (ctail == "Z")) {
						shft = true;
					}
					if (shft) shftHold();
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
	//cout << "database: >>db<< " << database << endl;
	ifstream f(database);
	string cell;
	while (f >> cell) { cout << cell << endl; }
	f.close();
}

void printXy() { 
POINT pt; GetCursorPos(&pt);
	if (strand=="x") {  cout << "xy: " << pt.x << "-" << pt.y << endl; } 
	else { string to_string(long v); out(":" + to_string(pt.x) + "-" + to_string(pt.y) + ">"); }
}

void printSe() {
	//cout << "<s lm:  Strand length mode: " << strandLengthMode << endl;
	//if (strandLengthMode) cout << "<s le:  Strand length: " << strandLength << endl;
	cout << "<s s:  Toggle show strand: " << showStrand<< endl;
	cout << "<s o:  Toggle show outs: " << showOuts<< endl;
	cout << "<q s:  Toggle < scan only: " << qScanOnly << endl;
	cout << "<q k:  Change < key: " << cKey << endl;
	cout << "<r e:  Change repeat key: " << reKey << endl;
	//cout << "<f r:  Change frequency: " << frequency << endl;
	cout << "Database:  " << database << endl;
	cout << "Hold RCtrl LCtrl or Esc on startup:  Change < key" << endl;
	cout << "Hold O on startup:  Show strand, show outs: 0" << endl;
	//cout << "Hold Q on startup:  Ctrl scan only: true" << endl;
}

void printIn() {
	cout << "@dnaspider\n\nse:  Settings" << endl;
	cout << "db:  Database" << endl;
	cout << "xy:  <xy:>" << endl;
	cout << "Esc:  Stop" << endl;
	string c; if (cKey == VK_CONTROL) c = "Ctrl"; else if (cKey == VK_LCONTROL) c = "LCtrl"; else if (cKey == VK_RCONTROL) c = "RCtrl"; else if (cKey == VK_ESCAPE) c = "Esc";
	cout << c << ":  Toggle <" << endl;
	cout << "Scroll Lock:  Repeat" << endl;
	cout << "<db:  Open database: " << database << endl;
	cout << "\n<ms:1500>  Milliseconds sleep\n<,>  150 milliseconds sleep\n<xy:0-0>  Move pointer\n<lc><rc><lh><rh><lr><rr>  left right click hold release\n<rp>  Return pointer\n<ctrl><shift><alt><win>  Hold key\n<ctrl-><shift-><alt-><win->  Release key\n<up><right><down><left><delete><esc><bs><home><end><space><tab>  Press key\n<bs*2>  Press twice\n<menu>  Press Menu key\n<ps>  Press Print Screen\n<f1>  Press F1 (F1-F12)" << endl;
	cout << "\n" << database << " hello example:\nh:ello\n<h-Hello\n<i:<bs><h->!\nCopy example to "<< database <<", save, then press h, ctrl h, or ctrl i\n" << endl;
	//cout << "In the example above, strands are in the beginning of each line  h: <h- <i:  Strands are separated with a : or - from the tail. If you write a strand with the - separator, The - will auto backspace the amount of characters before the -  Strands can start with the lowercase letter, number, space, or <  Strands look like this: <test: test: test- <test-  Strands do not have a closing >  To make a strand, on a new line in "<<database<<" with ANSI Encoding save <test-1  In a text area, press ctrl, release, type test to execute the tail which is after the -  The tail can be a-z A-Z 0-1 etc. Tails look like this: <win>r<win-><,>test<enter>  Tails can have a link to other strands as well. A link looks like this:  <test:> or <test->  Full example looks like this: First line in db.txt: <test-3<sl:><sec:>2<fail:>  Second: <sec:<ms:1000>  Third: <fail:<sl:><sec:>1<sl:><sec:><bs>  Forth: <sl:<shift><left><shift->  db.txt does not auto create and must be created manually.\n\n";
}
void changeKey(string msg, int ke) {
	kb(VK_ESCAPE); int sl; cout << "Enter new "<< msg << ":" << endl;  cin >> sl; if (sl > 0) { ke = sl; }
	else { return; } clearAllKeys(); cout << msg << ": " << ke << endl; strand.clear();
}
void key(string k) {
	strand.append(k);
	//if (strandLengthMode && strand.length()>strandLength && strand.substr(0,1)!="<") { strand = strand.substr(strand.length() - strandLength); }
	if (showKey) cout << "key: " << k.c_str() << endl;
	if (showStrand) cout << "strand: " << strand.c_str() << endl;

	//perform search
	scanDb();
	if (strand == "db") { printDb();  }
	if (strand=="se"){ printSe(); }
	if (strand == "x" ||strand == "xy") { printXy(); }
	if (strand == "<db") { out("<win>r<win-><,>" + database + "<enter>"); } 
	if (strand == "<q s") { qScanOnly = !qScanOnly; cout << "<q s: " << qScanOnly <<endl; strand.clear(); }
	//if (strand == "<s lm") { strandLengthMode = !strandLengthMode; cout << "Strand length mode: " << strandLengthMode << endl; strand.clear(); if (strandLengthMode) { cout << "strand length: " << strandLength << endl; } }
	//if (strand == "<s le") { kb(VK_ESCAPE); int sl; cout << "Enter new strand length:" << endl;  cin >> sl; if (sl > 0) { strandLength = sl; } else { return; } clearAllKeys(); cout << "strand length: " << strandLength << endl; strand.clear(); }
	if (strand == "<r e") { kb(VK_ESCAPE); int sl; cout << "Enter new repeat key:" << endl;  cin >> sl; if (sl > 0) { reKey = sl; } else { return; } clearAllKeys(); cout << "repeat key: " << reKey << endl; strand.clear(); }
	if (strand == "<q k") { kb(VK_ESCAPE); int sl; cout << "Enter new < key:" << endl;  cin >> sl; if (sl > 0) { cKey = sl; } else { return; } clearAllKeys(); cout << "< key: " << cKey << endl; strand.clear(); }
	if (strand == "<f r") { kb(VK_ESCAPE); int sl; cout << "Enter new frequency:" << endl;  cin >> sl; if (sl > 0) { frequency = sl; } else { return; } clearAllKeys(); cout << "frequency: " << frequency << endl; strand.clear(); }
	if (strand == "<s s") { showStrand = !showStrand; cout << "<s s: " << showStrand <<endl; strand.clear(); }
	if (strand == "<s o") { showOuts = !showOuts; cout << "<s o: " << showOuts <<endl; strand.clear(); }
}


int main() {
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
		if (qScanOnly) { if (qScanOnly && strand.substr(0, 1) == "<") {} else { continue; } }
#pragma region "az"
		if (GetAsyncKeyState(0x41)) { key("a"); }
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
		if (GetAsyncKeyState(0x5A)) { key("z"); }
#pragma endregion
#pragma region "09"
		if (GetAsyncKeyState(0x30)) { key("0"); }
		if (GetAsyncKeyState(0x31)) { key("1"); }
		if (GetAsyncKeyState(0x32)) { key("2"); }
		if (GetAsyncKeyState(0x33)) { key("3"); }
		if (GetAsyncKeyState(0x34)) { key("4"); }
		if (GetAsyncKeyState(0x35)) { key("5"); }
		if (GetAsyncKeyState(0x36)) { key("6"); }
		if (GetAsyncKeyState(0x37)) { key("7"); }
		if (GetAsyncKeyState(0x38)) { key("8"); }
		if (GetAsyncKeyState(0x39)) { key("9"); }
#pragma endregion
		if (GetAsyncKeyState(VK_SPACE)) { key(" "); }
	}
}