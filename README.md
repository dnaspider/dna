&nbsp;<h1><span href="https://github.com/dnaspider/dna/releases" title="Get the latest dnaspider.exe release &#13;&#13;Press [WIN+PAUSE_BREAK] for system type">`🕷`</span>[dnaspider.exe](https://github.com/dnaspider/dna/releases "Programmable keyboard software")</h1>
Hello Friend, and thank you for your interest in dnaspider.exe 🙏.

🥁 Introducing dnaspider.exe programmable keyboard software for Windows (32/64-bit) PCs! Tweak and execute simple or complex ⌨ and 🖱 functionality✨. Use it and build apon your functionality. With the help of dnaspider.exe, you will have the ability to strategically execute your custom built functionality seamlessly! 🦾🤖🦾.

### How it works
dnaspider.exe builds an input strand from keyboard keys you press... 
<pre title="dnaspider.exe"><span title="The [T] key on the keyboard was pressed">strand: <kbd>t</kbd></span>
<span title="The [E] key on the keyboard was pressed">strand: <kbd>te</kbd></span>
<span title="The [S] key on the keyboard was pressed">strand: <kbd>tes</kbd></span>
<span title="The [T] key on the keyboard was pressed">strand: <kbd>test</kbd></span>
<span title="The input sequence [test] was found in the &#13;beginning of one of the lines in db.txt and will trigger a run. &#13;&#13;Press or hold ESC to stop.">strand: <kbd>test></kbd></span></pre>

This input [strand](https://github.com/dnaspider/dna/wiki/Input-map "View input strand map") <kbd>test&gt;</kbd> will be our shortcut and is what dnaspider.exe searches for in the beginning of each line in <span title="Database">db.txt</span>. If found, the program executes the trailing text. This trailing text is our <a href="https://github.com/dnaspider/dna/wiki/api" title="Application programming interface">output</a> and is the code we'll write which simulates functionality we instruct. 

### db.txt
<pre title="db.txt"><span title="Input strand &#13;&#13;Clear strand with BACKSPACE then type 'test' to run">test</span><span title="Use :, -, >, or io:* from se.txt to link the input:output">:</span><span title="Presses BACKSPACE four times">&lt;bs4&gt;</span><span title="Types hi">hi</span><span title="Holds SHIFT">&lt;shift&gt;</span><span title="Presses LEFT twice">&lt;left2&gt;</span><span title="Releases SHIFT">&lt;shift-&gt;</span>
</pre>

Input the strand <kbd>test</kbd> in a text area for the effect.

Lets adjust db.txt to use the auto <span title="-">backspace</span> and <span title="<connect:> or <connect->">connect</span> options.
<pre title="db.txt"><span title="Clear strand then press T, RCTRL to run">t-</span>hi&lt;connect:&gt;
<span title="Use RCTRL, RSHIFT+LSHIFT, or COMMA+ESC for &lt; then type 'connect' followed by RCTRL to run">&lt;connect:&gt;</span>&lt;shift&gt;&lt;left2&gt;&lt;shift-&gt;
test:&lt;bs4&gt;hi&lt;connect:&gt;</pre>

Save then press <kbd>T</kbd> to run.

Lets adjust a setting in se.txt to make <kbd title="Line 3">test</kbd> work.

### se.txt
<pre title="se.txt &#13;&#13;CloseCtrlMode: 1 &#13;(Will be set to On after LCTRL+S🔥save) &#13;&#13;Press RCTRL after strand to run. &#13;(strand: test&gt;)">CloseCtrlMode: 1</pre>

<span title="se.txt &#13;&#13;EditorSe: se.txt - Visual Studio Code">Press <kbd>LCTRL+S</kbd> to🔥save.</span>

Now run your code!

### Repeat
Use <span title="Hold RCTRL, press LCTRL, then release RCTRL"><kbd>RCTRL+LCTRL</kbd></span>, <span><kbd>EQUAL+ESC</kbd></span>, or <span title="se.txt &#13;&#13;RepeatKey: 19"><kbd>PAUSE_BREAK</kbd></span>.

### Syntax
<strong><span title="Settings&#013;=se.txt==========&#013;StrandLengthMode: 3&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#013;&#013;Database&#013;=db.txt==========&#013;hello&#013;===============&#13;&#013;Run&#013;Press H E L in a text area&#13;&#13;Program&#13;=dnaspider.exe=====&#013;strand: h&#013;strand: he&#013;strand: hel&#013;===============">`hello`</span>
 <span title="=se.txt==========&#013;StrandLengthMode: 0&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;===============&#13;&#13;=db.txt==========&#13;h:ello&#13;===============&#13;&#13;Run&#13;Clear strand then press H&#13;&#13;To clear strand, toggle RIGHT_CTRL, &#13;BACKSPACE, or PAUSE_BREAK&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h:ello`</span>
 <span title="Use minus sign for auto BACKSPACE&#13;&#13;=db.txt==========&#13;h-hello&#13;===============&#13;&#13;Run&#13;Clear strand then press H&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h-hello`</span>
 <span title="Use > to remember input strand &#13;for SCROLL_LOCK repeat&#13; &#13;=db.txt==========&#13;h>ello&#13;===============&#13;&#13;Run&#13;Press H&#13;&#13;=dnaspider.exe=====&#013;strand: h&#013;===============">`h>ello`</span>
 <span title="=db.txt==========&#13;<h:ello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;Or press COMMA+ESC, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h:ello`</span>
 <span title="&#13;&#13;=db.txt==========&#13;<h-hello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h-hello`</span>
 <span title="Use > to remember input strand &#13;for SCROLL_LOCK repeat&#13;&#13;=db.txt==========&#13;<h>ello&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h>ello`</span>
 <span title="Connect&#13;&#13;=db.txt========&#13;<i-><o->h<h:>!&#13;<o->hello!&#13;<h:>ello&#13;=============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, I&#13;&#13;=dnaspider.exe=====&#013;strand: <i&#013;===============">`<h:>ello`</span>
 <span title="Infinite loop&#13;&#13;Press ESC to stop or PAUSE_BREAK to pause/resume&#13;&#13;=db.txt==========&#13;<h-><speed:250>hello <h->&#13;===============&#13;&#13;Run&#13;Press RIGHT_CTRL, release RIGHT_CTRL, H&#13;&#13;=dnaspider.exe=====&#013;strand: <&#13;strand: <h&#013;===============">`<h->hello`</span></strong>

### <a href="https://github.com/dnaspider/dna/wiki">Wiki</a> • <a href="https://github.com/dnaspider/dna/wiki/api" title="?+ESC">Codes</a> • <a href="https://github.com/dnaspider/dna/wiki/interface" title="UI">Interface</a>


<h3><a href="https://github.com/dnaspider/dna/archive/master.zip" title="Extract dna-master folder from dna-master.zip to desktop&#13;&#13;dnaspider.vcxproj > Open with > Visual Studio&#13;&#13;Solution Explorer > Source Files > dnaspider.cpp&#13;&#13;Build (Release, x64)&#13;CTRL+SHIFT+B&#13;&#13;dnaspider.exe build can be found in dna/x64/release or dna/Release (x86)">📂Source</a></h3>

Open project file <em>dnaspider.vcxproj</em> in Visual Studio.
