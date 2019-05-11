<h1><a href="https://github.com/dnaspider/dna/releases" title="Release">dnaspider.exe</a></h1>

Programmable keyboard software for Windows 10 (32/64-bit).

When you type with your keyboard, dnaspider builds a strand (`strand: abcd`) that's used for comparing to the beginning pattern of each line in db.txt. If this strand (<em>`abcd`</em>) matches the beginning pattern of a line in db.txt (<a href="" title="c:/dna/db.txt&#13;abcd>hello&#13;abcd:hello&#13;abcd-hello&#13;abcd->hello&#13;abcd:>hello&#13;<abcd>hello..."><em>`abcd`</em> <strong>+</strong> <em>`>`</em> <em>`:`</em> <em>`-`</em> <em>`:>`</em> or <em>`->`</em></a>), dnaspider will run the rest of the line in the form of a programmed keyboard simulation.

<strong><a href="" title="se.txt&#013;StrandLengthMode: 1&#013;StrandLength: 3&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0&#013;&#013;db.txt&#013;hello&#013;&#013;Run&#013;Clear strand then press h e l in a text area.&#13;To clear strand toggle ctrl, pause, backspace, or esc+comma">`hello`</a>
<a href="" title="se.txt&#013;StrandLengthMode: 0&#013;CtrlScanOnlyMode: 0&#013;CloseCtrlMode: 0&#013;Ignore_A-Z: 0">`h:ello`</a>
`h-ello` `h>ello` `<h:ello` `<h-ello` `<h>ello`
<br><a href="" title="Connect or infinate loop.&#13;&#13;db.txt&#13;<h:>ello<h:>&#13;&#13;Run&#13;Press ctrl, release ctrl, h&#13;Press esc or pause key to stop">`<h:>ello`</a> <a href="" title="Connect or infinate loop.&#13;&#13;db.txt&#13;<h->ello<speed:250><h->">`<h->ello`</a></strong>

<h2><a href="https://github.com/dnaspider/dna/wiki" title="API, db.txt, Settings, Interface">Wiki</a>&nbsp;
<a href="https://github.com/dnaspider/dna/releases" title="Press [win + pause] for system type">Download</a>&nbsp;
<a href="https://youtu.be/eREkcFJht8k" title="Video">Demo</a>&nbsp;
<a href="https://github.com/dnaspider/dna/archive/master.zip" title="dnaspider.vcxproj -> Open with -> Visual Studio">Source</a>
</h2>
