# `🕷`<em>[dnaspider.exe](https://github.com/dnaspider/dna/releases "Download open source dnaspider.exe &#13;Programmable keyboard software for Windows 10")</em><br><br><sup><sup>Programmable keyboard software </sup></sup><br><em>for Windows 10 (32/64-bit).</em>
Is a program which builds a strand from keyboard keys you press... 
<br><sub><sub>==dnaspider.exe====</sub></sub>
<br><span title="The [t] key on the keyboard was pressed">`strand: t`</span>
<br><span title="The [e] key on the keyboard was pressed">`strand: te`</span>
<br><span title="The [s] key on the keyboard was pressed">`strand: tes`</span>
<br><span title="The [t] key on the keyboard was pressed">`strand: test`</span>
<br><span title="The input sequence [test] was found in the &#13;beginning of one of the lines in db.txt.&#13;Running trailing output...">`strand: *found*`</span>
<br><sup><sup>===============</sup></sup>
<br>This input strand can be tied to an output (<a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">API</a>). Output simulates keyboard and mouse as if was robot you. 
<br>The output code looks like this `<bs3>hi<shift><left2><shift->` which pretty much says "press backspace three times, press h, press i, press (hold) shift, press left arrow twice (to select hi), release shift". 
<br>With both an input and output you can save it in c:/dna/db.txt and test it out in a text area.
<br>The whole code looks like this:
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`test:<bs3>hi<shift><left2><shift->`
<br><sup><sup>===============</sup></sup>
<br>The `:` ties it together. You can also use `-` `>` <span title="Press: right ctrl, w, h, a, t, e, v, e, r">`<whatever:>`</span> or <span title="Press: right ctrl, w, h, a, t, e, v, e, r">`<whatever->`</span> to tie it together.
<br>After running the code once you can press `Scroll Lock` or `Escape + Equal` to repeat the output.
<br>Lets adjust the code a bit.
<br><sub><sub><span title="Database: c:\dna\db.txt">==db.txt=========</span></sub></sub>
<br>`t-hi<connect:>`
<br>`<connect:><shift><left2><shift->`
<br>`test:<bs4>hi<connect:>`
<br><sup><sup>===============</sup></sup>
<br>The `-` ties it together now. Press `t` in a text area to run. Notice the `-` sign auto backspaces the `t`.
<br>Say if you want both to work, make the following changes.
<br><sub><sub><span title="Settings: c:\dna\se.txt">==se.txt=========</span></sub></sub>
<br><span title="CloseCtrlMode: True">`CloseCtrlMode: 1`</span>
<br><sup><sup>===============</sup></sup>
<br>Save se.txt and press `right ctrl` `s` `e` to update the settings.
 <br>Now to run, <strong title="Toggle right ctrl, backspace, or pause">clear strand</strong> then press `right ctrl` or `escape+comma` after the input (`t` `right ctrl` or `t` `e` `s` `t` `right ctrl`).


<span title="Next level sh*t">Syntax</span>
<br><strong><span title="Settings&#013;=se.txt==========&#013;StrandLengthMode: 1&#013;StrandLength: 3&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#013;&#013;Database&#013;=db.txt==========&#013;hello&#013;===============&#13;&#013;Run&#013;Press h e l in a text area&#13;&#13;Program&#13;=dnaspider.exe=====&#013;strand: h&#013;strand: he&#013;strand: hel&#013;===============">`hello`</span>
 <span title="=se.txt==========&#013;StrandLengthMode: 0&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#13;&#13;=db.txt==========&#13;h:ello&#13;===============&#13;&#13;Run&#13;Clear strand then press h&#13;&#13;To clear strand, toggle right&#13;ctrl, pause, or backspace&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h:ello`</span>
 <span title="Use minus sign for auto backspace&#13;&#13;=db.txt==========&#13;h-hello&#13;===============&#13;&#13;Run&#13;Clear strand then press h&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h-hello`</span>
 <span title="=db.txt==========&#13;h>ello&#13;===============&#13;&#13;Run&#13;Press h&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h>ello`</span>
 <span title="=db.txt==========&#13;<h:ello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;Or press esc + comma, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h:ello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h-hello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h-hello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h>ello&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h>ello`</span>
 <span title="Connect&#13;&#13;=db.txt========&#13;<i-><o->h<h:>!&#13;<o->hello!&#13;<h:>ello&#13;=============&#13;&#13;Run&#13;Press ctrl, release ctrl, i&#13;&#13;=dnaspider.exe=====&#013;strand: <i&#013;===============">`<h:>ello`</span>
 <span title="Infinite loop&#13;&#13;Press esc or pause to stop&#13;&#13;=db.txt==========&#13;<h-><speed:250>hello <h->&#13;===============&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h->hello`</span></strong>

<a href="https://github.com/dnaspider/dna/wiki" title="API, db.txt, Settings, Interface">Wiki</a>&nbsp;
<br>Browse the Wiki for information pertaining to the programs <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">API</a>, <a href="https://github.com/dnaspider/dna/wiki/settings" title="se.txt">Settings</a>, <a href="https://github.com/dnaspider/dna/wiki/db.txt" title="db.txt">Database</a>, and <a href="https://github.com/dnaspider/dna/wiki/interface" title="UI">Interface</a> commands.

<a href="https://github.com/dnaspider/dna/releases" title="Press [win + pause] for system type">Download</a>&nbsp;
<br>Get the latest release.

<a href="https://www.youtube.com/watch?v=OAhHa7FXAnQ" title="Video">Demo</a>,&nbsp;<a href="https://youtu.be/eREkcFJht8k" title="Video">1</a>&nbsp;
<br>View dnaspider in action.

<a href="https://github.com/dnaspider/dna/archive/master.zip" title="Extract dna-master folder from dna-master.zip to desktop&#13;&#13;dnaspider.vcxproj -> Open with -> Visual Studio&#13;&#13;Solution Explorer -> Source Files -> dnaspider.cpp&#13;&#13;Build (Release, x64)&#13;Ctrl + Shift + B&#13;&#13;dnaspider.exe build can be found in dna/x64/release or dna/Release (x86)">Source</a>
<br>Open project to view, edit, and build.
