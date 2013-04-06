CommitReader
============

Read every commit mail, present day, present time.

This plugin supports to read commit mail which contains plain diff
as if it is HTML mail.

As a side-effect, it also supports to render normal HTML mail
for Sylpheed.

Requirement
-----------

* Ubuntu 12.04 or later
* Sylpheed 3.4.0 or later.
* WebKitGTK+

Install
-------

```
% sudo apt-get install libwebkit-gtk
% git clone git://github.com/kenhys/sylpheed-commit-reader.git
% cd sylpheed-commit-reader
% ./autogen.sh
% ./configure --sylpheed-build-dir=/path/to/sylpheed_source_dir
% make
% make install
```

Usage
-----

Configure commitreaderrc placed at $HOME/.sylpheed-2.0/.

```
[commit_reader]
enable-private-browsing=false
auto-load-images=false
enable-scripts=false
switch-tab=true
commit-to=commit@example.com;commit2@example.com
```

if you want to read commit mail in plain diff context as HTML mail,
modify "commit-to" property just above.

For example, this plugin shows commit mail as HTML one which matches
 "To:" address to "commit-to".



