# `🕷`<em>[dnaspider.exe](https://github.com/dnaspider/dna/releases "Download open source dnaspider.exe &#13;Programmable keyboard software for Windows 10")</em><br><br><sup><sup><a href="https://github.com/dnaspider/dna/wiki/Introduction" title="Introduction">Programmable keyboard software</a> </sup></sup><br><em>for Windows 10 (32/64-bit).</em>
Hello friend, and thank you for your interest in dnaspider.exe.

🥁 Introducing dnaspider.exe. Programmable keyboard software for executing simple keyboard and mouse functionality to your liking. Use this functionality to accelerate through daily tasks like a pro. With the help of dnaspider.exe, you will have the ability to strategically execute your custom built functionality seamlessly.
<h3>How it works ⚙</h3>

dnaspider.exe builds a strand from keyboard keys you press... 
<br><sub><sub>==dnaspider.exe====</sub></sub>
<br><span title="The [t] key on the keyboard was pressed">`strand: t`</span>
<br><span title="The [e] key on the keyboard was pressed">`strand: te`</span>
<br><span title="The [s] key on the keyboard was pressed">`strand: tes`</span>
<br><span title="The [t] key on the keyboard was pressed">`strand: test`</span>
<br><span title="The input sequence [test] was found in the &#13;beginning of one of the lines in db.txt.&#13;Running trailing output...">`strand: *found*`</span>
<br><sup><sup>===============</sup></sup>
<br>This [input strand](https://github.com/dnaspider/dna/wiki/Input-map "View input strand map") is the text that dnaspider.exe  looks for in the beginning of each line in <span title="Database">db.txt</span>. If found, the program executes the trailing text. We'll call this trailing text the <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">output</a> which is the code we'll write which simulates keyboard and mouse functionality as instructed. 

In the following example the output code looks like this `<bs4>hi<shift><left2><shift->` which pretty much says "programmatically press backspace four times, press h, press i, press (hold) shift, press left arrow twice (to select hi), release shift".

The whole code looks like this and c:\dna\db.txt is the database where we'll be building and storing our algos:
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`test:<bs4>hi<shift><left2><shift->`
<br><sup><sup>===============</sup></sup>
<br>The `:` ties the input and output together (<span title="strand:api">input:output</span>). We can also use <span title="test-">`-`</span> <span title="test>">`>`</span> <span title="Press: right_ctrl, w, h, a, t, e, v, e, r">`<whatever:>`</span> or <span title="Press: right_ctrl, w, h, a, t, e, v, e, r">`<whatever->`</span> to tie it together.

Input strand and trailing output must be saved in <em title="Change se.txt > Database: c:/dna/db.txt for a different location or file name.&#13;e.g., Database: C:\Users\USER_NAME\OneDrive\dna\database.htm">c:/dna/db.txt</em> for the program to execute/run.

In order to run, have a clear strand first by toggle `right_ctrl` `backspace` or `pause/break` then simply input the strand `t` `e` `s` `t` in a text area for the effect.

After running the code once you can press `scroll lock` or `escape + equal` to repeat the output.

Lets adjust the code a bit and save.
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`t-hi<connect:>`
<br>`<connect:><shift><left2><shift->`
<br>`test:<bs4>hi<connect:>`
<br><sup><sup>===============</sup></sup>
<br>The `-` ties it together now. Press `t` in a text area to run. Notice the `-` sign auto backspaces the `t`.

Say if you want both to work, make the following changes in c:/dna/se.txt using <span title="Notepad.exe">Notepad</span> or <span title="Visual Studio Code &#13;Code.exe">VSCode</span>.
<br><sub><sub><span title="Settings: c:\dna\se.txt">==se.txt=========</span></sub></sub>
<br><span title="CloseCtrlMode: True">`CloseCtrlMode: 1`</span>
<br><sup><sup>===============</sup></sup>
<br>Press `ctrl + s` to save se.txt.

If using an editor other than <span title="Notepad.exe">Notepad</span> or <span title="Visual Studio Code &#13;Code.exe">VSCode</span>, press `right_ctrl` `s` `e` or restart the program to update the settings.

Now to run, press `right_ctrl` or `escape + comma` after the input (`t` `right_ctrl` or `t` `e` `s` `t` `right_ctrl`).
<h3>Syntax</h3>

<strong><span title="Settings&#013;=se.txt==========&#013;StrandLengthMode: 1&#013;StrandLength: 3&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#013;&#013;Database&#013;=db.txt==========&#013;hello&#013;===============&#13;&#013;Run&#013;Press h e l in a text area&#13;&#13;Program&#13;=dnaspider.exe=====&#013;strand: h&#013;strand: he&#013;strand: hel&#013;===============">`hello`</span>
 <span title="=se.txt==========&#013;StrandLengthMode: 0&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#13;&#13;=db.txt==========&#13;h:ello&#13;===============&#13;&#13;Run&#13;Clear strand then press h&#13;&#13;To clear strand, toggle right&#13;ctrl, pause, or backspace&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h:ello`</span>
 <span title="Use minus sign for auto backspace&#13;&#13;=db.txt==========&#13;h-hello&#13;===============&#13;&#13;Run&#13;Clear strand then press h&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h-hello`</span>
 <span title="=db.txt==========&#13;h>ello&#13;===============&#13;&#13;Run&#13;Press h&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h>ello`</span>
 <span title="=db.txt==========&#13;<h:ello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;Or press esc + comma, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h:ello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h-hello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h-hello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h>ello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h>ello`</span>
 <span title="Connect&#13;&#13;=db.txt========&#13;<i-><o->h<h:>!&#13;<o->hello!&#13;<h:>ello&#13;=============&#13;&#13;Run&#13;Press ctrl, release ctrl, i&#13;&#13;=dnaspider.exe=====&#013;strand: <i&#013;===============">`<h:>ello`</span>
 <span title="Infinite loop&#13;&#13;Press esc or pause to stop&#13;&#13;=db.txt==========&#13;<h-><speed:250>hello <h->&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h->hello`</span></strong>

<h3><a href="https://github.com/dnaspider/dna/wiki" title="API, db.txt, Settings, Interface">Wiki</a>&nbsp;</h3>

Browse the Wiki for information pertaining to the programs <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">API</a>, <a href="https://github.com/dnaspider/dna/wiki/settings" title="se.txt">Settings</a>, <a href="https://github.com/dnaspider/dna/wiki/db.txt" title="db.txt">Database</a>, and <a href="https://github.com/dnaspider/dna/wiki/interface" title="UI">Interface</a> commands.

<h3><a href="https://github.com/dnaspider/dna/releases" title="Press [win + pause] for system type">Download</a>&nbsp;</h3>

Get the latest release.

<h3><a href="https://www.youtube.com/watch?v=OAhHa7FXAnQ" title="Video">Demo</a>,&nbsp;<a href="https://youtu.be/eREkcFJht8k" title="Video">1</a>&nbsp;</h3>

View dnaspider in action.

<h3><a href="https://github.com/dnaspider/dna/archive/master.zip" title="Extract dna-master folder from dna-master.zip to desktop&#13;&#13;dnaspider.vcxproj > Open with > Visual Studio&#13;&#13;Solution Explorer > Source Files > dnaspider.cpp&#13;&#13;Build (Release, x64)&#13;Ctrl + Shift + B&#13;&#13;dnaspider.exe build can be found in dna/x64/release or dna/Release (x86)">Source</a></h3>

Open project file <em>dnaspider.vcxproj</em> in Visual Studio to view, edit, and build.
