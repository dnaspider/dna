# `👽`[dnaspider.exe](https://github.com/dnaspider/dna/releases "Download open source dnaspider.exe")
Hello Friend, and thank you for your interest in dnaspider.exe 🙏.

🥁 Introducing dnaspider.exe programmable keyboard software for Windows 11, 10 (32/64-bit) PCs! Tweak and execute simple or complex ⌨ and 🖱 functionality+ to your liking. Use this functionality to automate and accelerate through daily tasks like a pro. With the help of dnaspider.exe, you will have the ability to strategically execute your custom built functionality seamlessly. 🦾🤖🦾.
<h3>How it works</h3>

dnaspider.exe builds an input strand from keyboard keys you press... 
<br><sub><sub>==dnaspider.exe====</sub></sub>
<br><span title="The [T] key on the keyboard was pressed">`strand: t`</span>
<br><span title="The [E] key on the keyboard was pressed">`strand: te`</span>
<br><span title="The [S] key on the keyboard was pressed">`strand: tes`</span>
<br><span title="The [T] key on the keyboard was pressed">`strand: test`</span>
<br><span title="The input sequence [test] was found in the &#13;beginning of one of the lines in db.txt.&#13;Running trailing output...">`strand: *found*`</span>
<br><sup><sup>===============</sup></sup>
<br>This [input strand](https://github.com/dnaspider/dna/wiki/Input-map "View input strand map") will be our shortcut and is the text that dnaspider.exe looks for in the beginning of each line in <span title="Database">db.txt</span>. If found, the program executes the trailing text. We'll call this trailing text the <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">output</a> which is the code we'll write which simulates keyboard and mouse functionality as instructed. 

In the following example the output code looks like this `<bs4>hi<shift><left2><shift->` which pretty much says to "programmatically press `BACKSPACE` four times, press `H`, press `I`, press (hold) `SHIFT`, press `LEFT` arrow twice (to select hi), release `SHIFT`".

The whole code looks like this and <em>c:\dna\db.txt</em> is the database where we'll be building and storing our algos:
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`test:<bs4>hi<shift><left2><shift->`
<br><sup><sup>===============</sup></sup>
<br>The `:` links the <span title="strand:api">`input:output`</span> together. We can also use minus sign auto `BACKSPACE` strand option <span title="test-">`-`</span> or remember strand for `SCROLL_LOCK` repeat option <span title="test>">`>`</span>. There are connect options <span title="Press: RIGHT_CTRL, W, H, A, T, E, V, E, R">`<whatever:>`</span> or <span title="Press: RIGHT_CTRL, W, H, A, T, E, V, E, R">`<whatever->`</span> as well.

Input strand and trailing output must be saved in <em title="Change c:\dna\se.txt > Database: c:\dna\db.txt for a different location or file name.&#13;e.g., Database: c:\Users\USER_NAME\OneDrive\dna\database.txt">c:\dna\db.txt</em> for the program to execute/run.

Before you run a code you might have to clear the input strand first by toggle `RIGHT_CTRL` `BACKSPACE` or `LEFT_SHIFT + ClearStrandKey` then simply input the strand `T` `E` `S` `T` in a text area for the effect.

After running the code once you can press `PAUSE_BREAK (se.txt RepeatKey: 19)` or `EQUAL + ESC` or hold `LCTRL` press `RCTRL (se.txt CtrlKey: 163)` then Release `LCTRL` to repeat the output.

Lets adjust the code a bit and use the auto <span title="-">`BACKSPACE`</span> and <span title="<connect:> or <connect->">connect</span> options.
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`t-hi<connect:>`
<br>`<connect:><shift><left2><shift->`
<br>`test:<bs4>hi<connect:>`
<br><sup><sup>===============</sup></sup>
<br>Save then press `T` in a text area to run.

If you want <span title="Line 3">`test:`</span> to work as well, make the following changes in <span title="Settings">c:\dna\se.txt</span> using <span title="se.txt - Visual Studio Code">Code.exe</span>.
<br><sub><sub><span title="Settings: c:\dna\se.txt">==se.txt=========</span></sub></sub>
<br><span title="CloseCtrlMode: True">`CloseCtrlMode: 1`</span>
<br><span title="Or: se - Visual Studio Code">`EditorSe: se.txt - Visual Studio Code`</span>
<br><sup><sup>===============</sup></sup>
<br>In Visual Studio Code, press `CTRL + S` to save <span title="Settings">se.txt</span>.

Now to run, press <span title="se.txt CtrlKey: 163">`RIGHT_CTRL`</span> or `COMMA + ESC` after the input (`T` `RIGHT_CTRL` or `T` `E` `S` `T` `RIGHT_CTRL`  or `LSHIFT + RCTRL` `C` `O` `N` `N` `E` `C` `T` `RCTRL`).
<h3>Syntax</h3>

<strong><span title="Settings&#013;=se.txt==========&#013;StrandLengthMode: 1&#013;StrandLength: 3&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#013;&#013;Database&#013;=db.txt==========&#013;hello&#013;===============&#13;&#013;Run&#013;Press H E L in a text area&#13;&#13;Program&#13;=dnaspider.exe=====&#013;strand: h&#013;strand: he&#013;strand: hel&#013;===============">`hello`</span>
 <span title="=se.txt==========&#013;StrandLengthMode: 0&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#13;&#13;=db.txt==========&#13;h:ello&#13;===============&#13;&#13;Run&#13;Clear strand then press H&#13;&#13;To clear strand, toggle RIGHT_CTRL, &#13;BACKSPACE, or LEFT_SHIFT + PAUSE_BREAK&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h:ello`</span>
 <span title="Use minus sign for auto BACKSPACE&#13;&#13;=db.txt==========&#13;h-hello&#13;===============&#13;&#13;Run&#13;Clear strand then press H&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h-hello`</span>
 <span title="Use > to remember input strand &#13;for SCROLL_LOCK repeat&#13; &#13;=db.txt==========&#13;h>ello&#13;===============&#13;&#13;Run&#13;Press H&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h>ello`</span>
 <span title="=db.txt==========&#13;<h:ello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;Or press COMMA + ESC, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h:ello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h-hello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h-hello`</span>
 <span title="Use > to remember input strand &#13;for SCROLL_LOCK repeat&#13;&#13;=db.txt==========&#13;<h>ello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h>ello`</span>
 <span title="Connect&#13;&#13;=db.txt========&#13;<i-><o->h<h:>!&#13;<o->hello!&#13;<h:>ello&#13;=============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, I&#13;&#13;=dnaspider.exe=====&#013;strand: <i&#013;===============">`<h:>ello`</span>
 <span title="Infinite loop&#13;&#13;Press ESC to stop or PAUSE_BREAK to pause/resume&#13;&#13;=db.txt==========&#13;<h-><speed:250>hello <h->&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h->hello`</span></strong>

<h3><a href="https://github.com/dnaspider/dna/wiki" title="API, db.txt, Settings, Interface">Wiki</a>&nbsp;</h3>

Browse the Wiki for information pertaining to the programs <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">API</a>, <a href="https://github.com/dnaspider/dna/wiki/settings" title="se.txt">Settings</a>, <a href="https://github.com/dnaspider/dna/wiki/db.txt" title="db.txt">Database</a>, and <a href="https://github.com/dnaspider/dna/wiki/interface" title="UI">Interface</a> commands.

<h3><a href="https://github.com/dnaspider/dna/releases" title="Press [WIN + PAUSE_BREAK] for system type">Download</a>&nbsp;</h3>

Get the latest release.

<h3><a href="https://github.com/dnaspider/dna/archive/master.zip" title="Extract dna-master folder from dna-master.zip to desktop&#13;&#13;dnaspider.vcxproj > Open with > Visual Studio&#13;&#13;Solution Explorer > Source Files > dnaspider.cpp&#13;&#13;Build (Release, x64)&#13;CTRL + SHIFT + B&#13;&#13;dnaspider.exe build can be found in dna/x64/release or dna/Release (x86)">📂Source</a></h3>

Open project file <em>dnaspider.vcxproj</em> in Visual Studio.
