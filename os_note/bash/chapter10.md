# 第十章、認識與學習BASH
## 10.1 認識 BASH 這個 Shell
我們在第一章 Linux 是什麼當中提到了： 管理整個電腦硬體的其實是作業系統的核心 (kernel)，這個核心是需要被保護的！ 所以我們一般使用者就只能透過 shell 來跟核心溝通，以讓核心達到我們所想要達到的工作。 那麼系統有多少 shell 可用呢？為什麼我們要使用 bash 啊？底下分別來談一談喔！

### 10.1.1 硬體、核心與 Shell
這應該是個蠻有趣的話題：『什麼是 Shell 』？相信只要摸過電腦，對於作業系統 (不論是 Linux 、 Unix 或者是 Windows) 有點概念的朋友們大多聽過這個名詞，因為只要有『作業系統』那麼就離不開 Shell 這個東西。不過，在討論 Shell 之前，我們先來瞭解一下電腦的運作狀況吧！ 舉個例子來說：當你要電腦傳輸出來『音樂』的時候，你的電腦需要什麼東西呢？
- 硬體：當然就是需要你的硬體有『音效卡晶片』這個配備，否則怎麼會有聲音；
- 核心管理：作業系統的核心可以支援這個晶片組，當然還需要提供晶片的驅動程式囉；
- 應用程式：需要使用者 (就是你) 輸入發生聲音的指令囉！

這就是基本的一個輸出聲音所需要的步驟！也就是說，你必須要『輸入』一個指令之後， 『硬體』才會透過你下達的指令來工作！那麼硬體如何知道你下達的指令呢？那就是 kernel (核心) 的控制工作了！也就是說，我們必須要透過『 Shell 』將我們輸入的指令與 Kernel 溝通，好讓 Kernel 可以控制硬體來正確無誤的工作！ 基本上，我們可以透過底下這張圖來說明一下：

### 10.1.3 系統的合法 shell 與 /etc/shells 功能
知道什麼是 Shell 之後，那麼我們來瞭解一下 Linux 使用的是哪一個 shell 呢？什麼！哪一個？難道說 shell 不就是『一個 shell 嗎？』哈哈！那可不！由於早年的 Unix 年代，發展者眾，所以由於 shell 依據發展者的不同就有許多的版本，例如常聽到的 Bourne SHell (sh) 、在 Sun 裡頭預設的 C SHell、 商業上常用的 K SHell、, 還有 TCSH 等等，每一種 Shell 都各有其特點。至於 Linux 使用的這一種版本就稱為『 Bourne Again SHell (簡稱 bash) 』，這個 Shell 是 Bourne Shell 的增強版本，也是基準於 GNU 的架構下發展出來的呦！

### 10.1.4 Bash shell 的功能
幹嘛 Linux 要使用他作為預設的 shell 呢？ bash 主要的優點有底下幾個：
- 命令編修能力 (history)
- 命令與檔案補全功能： (\[tab] 按鍵的好處)

    \[Tab] 接在一串指令的第一個字的後面，則為命令補全；
    \[Tab] 接在一串指令的第二個字以後時，則為『檔案補齊』！
    若安裝 bash-completion 軟體，則在某些指令後面使用 \[tab] 按鍵時，可以進行『選項/參數的補齊』功能！
- 命令別名設定功能： (alias)

    假如我需要知道這個目錄底下的所有檔案 (包含隱藏檔) 及所有的檔案屬性，那麼我就必須要下達『 ls -al 』這樣的指令串，唉！真麻煩，有沒有更快的取代方式？呵呵！就使用命令別名呀！例如鳥哥最喜歡直接以 lm 這個自訂的命令來取代上面的命令，也就是說， lm 會等於 ls -al 這樣的一個功能，嘿！那麼要如何作呢？就使用 alias 即可！你可以在指令列輸入 alias 就可以知道目前的命令別名有哪些了！也可以直接下達命令來設定別名呦：

    alias lm='ls -al'

- 工作控制、前景背景控制： (job control, foreground, background)
這部分我們在第十六章 Linux 程序控制中再提及！ 使用前、背景的控制可以讓工作進行的更為順利！至於工作控制(jobs)的用途則更廣， 可以讓我們隨時將工作丟到背景中執行！而不怕不小心使用了 \[Ctrl] + c 來停掉該程序！真是好樣的！此外，也可以在單一登入的環境中，達到多工的目的呢！

- 程式化腳本： (shell scripts)
在 DOS 年代還記得將一堆指令寫在一起的所謂的『批次檔』吧？在 Linux 底下的 shell scripts 則發揮更為強大的功能，可以將你平時管理系統常需要下達的連續指令寫成一個檔案， 該檔案並且可以透過對談互動式的方式來進行主機的偵測工作！也可以藉由 shell 提供的環境變數及相關指令來進行設計，哇！整個設計下來幾乎就是一個小型的程式語言了！該 scripts 的功能真的是超乎鳥哥的想像之外！以前在 DOS 底下需要程式語言才能寫的東西，在 Linux 底下使用簡單的 shell scripts 就可以幫你達成了！真的厲害！這部分我們在第十二章再來談！

- 萬用字元： (Wildcard)
除了完整的字串之外， bash 還支援許多的萬用字元來幫助使用者查詢與指令下達。 舉例來說，想要知道 /usr/bin 底下有多少以 X 為開頭的檔案嗎？使用：『 ls -l /usr/bin/X* 』就能夠知道囉～此外，還有其他可供利用的萬用字元， 這些都能夠加快使用者的操作呢！

### 10.1.5 查詢指令是否為 Bash shell 的內建命令： type
```
[dmtsai@study ~]$ type [-tpa] name
選項與參數：
    ：不加任何選項與參數時，type 會顯示出 name 是外部指令還是 bash 內建指令
-t  ：當加入 -t 參數時，type 會將 name 以底下這些字眼顯示出他的意義：
      file    ：表示為外部指令；
      alias   ：表示該指令為命令別名所設定的名稱；
      builtin ：表示該指令為 bash 內建的指令功能；
-p  ：如果後面接的 name 為外部指令時，才會顯示完整檔名；
-a  ：會由 PATH 變數定義的路徑中，將所有含 name 的指令都列出來，包含 alias

kevin@ubuntu:~/os$ type cd
cd is a shell builtin
kevin@ubuntu:~/os$ type ls
ls is aliased to `ls --color=auto'
kevin@ubuntu:~/os$ type tree
tree is /snap/bin/tree
```

### 10.1.6 指令的下達與快速編輯按鈕
我們在第四章的開始下達指令小節已經提到過在 shell 環境下的指令下達方法，如果你忘記了請回到第四章再去回憶一下！這裡不重複說明了。 鳥哥這裡僅就反斜線 (\) 來說明一下指令下達的方式囉！

上面這個指令用途是將三個檔案複製到 /root 這個目錄下而已。不過，因為指令太長， 於是鳥哥就利用『 \[Enter] 』來將 \[Enter] 這個按鍵『跳脫！』開來，讓 \[Enter] 按鍵不再具有『開始執行』的功能！好讓指令可以繼續在下一行輸入。 需要特別留意， \[Enter] 按鍵是緊接著反斜線 (\) 的，兩者中間沒有其他字元。 因為 \ 僅跳脫『緊接著的下一個字符』而已！所以，萬一我寫成： 『 \ \[Enter] 』，亦即 \[Enter] 與反斜線中間有一個空格時，則 \ 跳脫的是『空白鍵』而不是 \[Enter] 按鍵！這個地方請再仔細的看一遍！很重要！

如果順利跳脫 [Enter] 後，下一行最前面就會主動出現 > 的符號， 你可以繼續輸入指令囉！也就是說，那個 > 是系統自動出現的，你不需要輸入。

另外，當你所需要下達的指令特別長，或者是你輸入了一串錯誤的指令時，你想要快速的將這串指令整個刪除掉，一般來說，我們都是按下刪除鍵的。 有沒有其他的快速組合鍵可以協助呢？是有的！常見的有底下這些：

|組合鍵 |	功能與示範 |
| --- | ----------- |
|[ctrl]+u/[ctrl]+k	| 分別是從游標處向前刪除指令串 ([ctrl]+u) 及向後刪除指令串 ([ctrl]+k)。|
|[ctrl]+a/[ctrl]+e	|分別是讓游標移動到整個指令串的最前面 ([ctrl]+a) 或最後面 ([ctrl]+e)。|

## 10.2 Shell 的變數功能

### 10.2.1 什麼是變數？
那麼，什麼是『變數』呢？簡單的說，就是讓某一個特定字串代表不固定的內容就是了。舉個大家在國中都會學到的數學例子， 那就是：『 y = ax + b 』這東西，在等號左邊的(y)就是變數，在等號右邊的(ax+b)就是變數內容。 要注意的是，左邊是未知數，右邊是已知數喔！ 講的更簡單一點，我們可以『用一個簡單的 "字眼" 來取代另一個比較複雜或者是容易變動的資料』。這有什麼好處啊？最大的好處就是『方便！』。

#### 變數的可變性與方便性

舉例來說，我們每個帳號的郵件信箱預設是以 MAIL 這個變數來進行存取的， 當 dmtsai 這個使用者登入時，他便會取得 MAIL 這個變數，而這個變數的內容其實就是 /var/spool/mail/dmtsai， 那如果 vbird 登入呢？他取得的 MAIL 這個變數的內容其實就是 /var/spool/mail/vbird 。 而我們使用信件讀取指令 mail 來讀取自己的郵件信箱時，嘿嘿，這支程式可以直接讀取 MAIL 這個變數的內容， 就能夠自動的分辨出屬於自己的信箱信件囉！這樣一來，設計程式的設計師就真的很方便的啦！

#### 影響 bash 環境操作的變數

某些特定變數會影響到 bash 的環境喔！舉例來說，我們前面已經提到過很多次的那個 PATH 變數！ 你能不能在任何目錄下執行某個指令，與 PATH 這個變數有很大的關係。例如你下達 ls 這個指令時，系統就是透過 PATH 這個變數裡面的內容所記錄的路徑順序來搜尋指令的呢！如果在搜尋完 PATH 變數內的路徑還找不到 ls 這個指令時， 就會在螢幕上顯示『 command not found 』的錯誤訊息了。

如果說的學理一點，那麼由於在 Linux System 下面，所有的執行緒都是需要一個執行碼， 而就如同上面提到的，你『真正以 shell 來跟 Linux 溝通，是在正確的登入 Linux 之後！』這個時候你就有一個 bash 的執行程序，也才可以真正的經由 bash 來跟系統溝通囉！而在進入 shell 之前，也正如同上面提到的，由於系統需要一些變數來提供他資料的存取 (或者是一些環境的設定參數值， 例如是否要顯示彩色等等的) ，所以就有一些所謂的『環境變數』 需要來讀入系統中了！這些環境變數例如 PATH、HOME、MAIL、SHELL 等等，都是很重要的， 為了區別與自訂變數的不同，環境變數通常以大寫字元來表示呢！

#### 腳本程式設計 (shell script) 的好幫手

這些還都只是系統預設的變數的目的，如果是個人的設定方面的應用呢：例如你要寫一個大型的 script 時，有些資料因為可能由於使用者習慣的不同而有差異，比如說路徑好了，由於該路徑在 script 被使用在相當多的地方，如果下次換了一部主機，都要修改 script 裡面的所有路徑，那麼我一定會瘋掉！ 這個時候如果使用變數，而將該變數的定義寫在最前面，後面相關的路徑名稱都以變數來取代， 嘿嘿！那麼你只要修改一行就等於修改整篇 script 了！方便的很！所以，良好的程式設計師都會善用變數的定義！

最後我們就簡單的對『什麼是變數』作個簡單定義好了： 『**變數就是以一組文字或符號等，來取代一些設定或者是一串保留的資料**！』， 例如：我設定了『myname』就是『VBird』，所以當你讀取 myname 這個變數的時候，系統自然就會知道！哈！那就是 VBird 啦！ 那麼如何『顯示變數』呢？這就需要使用到 echo 這個指令啦！

### 10.2.2 變數的取用與設定：echo, 變數設定規則, unset

說的口沫橫飛的，也不知道『變數』與『變數代表的內容』有啥關係？ 那我們就將『變數』的『內容』拿出來給您瞧瞧好了。你可以利用 echo 這個指令來取用變數， 但是，變數在被取用時，前面必須要加上錢字號『 $ 』才行，舉例來說，要知道 PATH 的內容，該如何是好？

#### 變數的取用: echo

```
kevin@ubuntu:~/os$ echo $variable

kevin@ubuntu:~/os$ echo $PATH
/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
kevin@ubuntu:~/os$ echo ${PATH}
/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
kevin@ubuntu:~/os$ echo $MAIL
/var/mail/kevin
kevin@ubuntu:~/os$ echo $HOME
/home/kevin
```
變數的取用就如同上面的範例，利用 echo 就能夠讀出，只是需要在變數名稱前面加上 $ ， 或者是以 ${變數} 的方式來取用都可以！當然啦，那個 echo 的功能可是很多的， 我們這裡單純是拿 echo 來讀出變數的內容而已，更多的 echo 使用，請自行給他 man echo 吧！ ^_^

#### 變數的設定規則

**變數與變數內容以一個等號『=』來連結**，如下所示：
『myname=VBird』

**等號兩邊不能直接接空白字元**，如下所示為錯誤：
『myname = VBird』或『myname=VBird Tsai』

**變數名稱只能是英文字母與數字，但是開頭字元不能是數字**，如下為錯誤：
『2myname=VBird』

**變數內容若有空白字元可使用雙引號『"』或單引號『'』將變數內容結合起來**，但
雙引號內的特殊字元如 \$ 等，可以保有原本的特性，如下所示：
『var="lang is \$LANG"』則『echo \$var』可得『lang is zh_TW.UTF-8』
```
kevin@ubuntu:~/os$ var="lang is $LANG"
kevin@ubuntu:~/os$ echo $var
lang is en_US.UTF-8
```
單引號內的特殊字元則僅為一般字元 (純文字)，如下所示：
『var='lang is \$LANG'』則『echo \$var』可得『lang is \$LANG』
```
kevin@ubuntu:~/os$ var='lang is $LANG'
kevin@ubuntu:~/os$ echo $var
lang is $LANG
```

可用跳脫字元『 \ 』將特殊符號(如 [Enter], $, \, 空白字元, '等)變成一般字元，如：
『myname=VBird\ Tsai』

在一串指令的執行中，還需要藉由其他額外的指令所提供的資訊時，可以使用反單引號『`指令`』或 『$(指令)』。特別注意，那個 ` 是鍵盤上方的數字鍵 1 左邊那個按鍵，而不是單引號！ 例如想要取得核心版本的設定：
『version=$(uname -r)』再『echo $version』可得『3.10.0-229.el7.x86_64』

若該變數為擴增變數內容時，則可用 "$變數名稱" 或 ${變數} 累加內容，如下所示：
『PATH="$PATH":/home/bin』或『PATH=${PATH}:/home/bin』

**若該變數需要在其他子程序執行，則需要以 export 來使變數變成環境變數**：
『export PATH』

**通常大寫字元為系統預設變數，自行設定變數可以使用小寫字元**，方便判斷 (純粹依照使用者興趣與嗜好) ；

**取消變數的方法為使用 unset** ：『unset 變數名稱』例如取消 myname 的設定：
『unset myname』
底下讓鳥哥舉幾個例子來讓你試看看，就知道怎麼設定好你的變數囉！

```
範例二：承上題，若變數內容為 VBird's name 呢，就是變數內容含有特殊符號時：
[dmtsai@study ~]$ name=VBird's name  
# 單引號與雙引號必須要成對，在上面的設定中僅有一個單引號，因此當你按下 enter 後，
# 你還可以繼續輸入變數內容。這與我們所需要的功能不同，失敗啦！
# 記得，失敗後要復原請按下 [ctrl]-c 結束！
[dmtsai@study ~]$ name="VBird's name"    <==OK 的啦！
# 指令是由左邊向右找→，先遇到的引號先有用，因此如上所示， 單引號變成一般字元！
[dmtsai@study ~]$ name='VBird's name'    <==失敗的啦！
# 因為前兩個單引號已成對，後面就多了一個不成對的單引號了！因此也就失敗了！
[dmtsai@study ~]$ name=VBird\'s\ name     <==OK 的啦！
# 利用反斜線 (\) 跳脫特殊字元，例如單引號與空白鍵，這也是 OK 的啦！

範例四：承範例三，我要將 name 的內容多出 "yes" 呢？
[dmtsai@study ~]$ name=$nameyes  
# 知道了吧？如果沒有雙引號，那麼變數成了啥？name 的內容是 $nameyes 這個變數！
# 呵呵！我們可沒有設定過 nameyes 這個變數吶！所以，應該是底下這樣才對！
[dmtsai@study ~]$ name="$name"yes
[dmtsai@study ~]$ name=${name}yes  <==以此例較佳！

範例五：
kevin@ubuntu:~/os$ name=kevin
kevin@ubuntu:~/os$ echo $name
kevin
kevin@ubuntu:~/os$ bash
kevin@ubuntu:~/os$ echo $name

kevin@ubuntu:~/os$ exit
exit
kevin@ubuntu:~/os$ echo $name
kevin

```
什麼是『子程序』呢？就是說，在我目前這個 shell 的情況下，去啟用另一個新的 shell ，新的那個 shell 就是子程序啦！在一般的狀態下，父程序的自訂變數是無法在子程序內使用的。但是透過 export 將變數變成環境變數後，就能夠在子程序底下應用了！很不賴吧！至於程序的相關概念， 我們會在第十六章程序管理當中提到的喔！

### 10.2.3 環境變數的功能

環境變數可以幫我們達到很多功能～包括家目錄的變換啊、提示字元的顯示啊、執行檔搜尋的路徑啊等等的， 還有很多很多啦！那麼，既然環境變數有那麼多的功能，問一下，目前我的 shell 環境中， 有多少預設的環境變數啊？我們可以利用兩個指令來查閱，分別是 env 與 export 呢！

#### 用 env 觀察環境變數與常見環境變數說明

```
kevin@ubuntu:~/os$ env
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
LD_LIBRARY_PATH=/opt/ros/melodic/lib
SSH_CONNECTION=192.168.0.109 3906 192.168.0.111 22
LESSCLOSE=/usr/bin/lesspipe %s %s
LANG=en_US.UTF-8
OLDPWD=/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b
COLORTERM=truecolor
ROS_ETC_DIR=/opt/ros/melodic/etc/ros
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
XDG_SESSION_ID=4
USER=kevin
PWD=/home/kevin/os
HOME=/home/kevin
BROWSER=/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/helpers/browser.sh
VSCODE_GIT_ASKPASS_NODE=/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/node
CMAKE_PREFIX_PATH=/opt/ros/melodic
TERM_PROGRAM=vscode
SSH_CLIENT=192.168.0.109 3906 22
TERM_PROGRAM_VERSION=1.73.1
XDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-60810494-8ef8-40ee-8564-a679ed7b493d.sock
ROS_ROOT=/opt/ros/melodic/share/ros
ROS_MASTER_URI=http://localhost:11311
ROS_VERSION=1
MAIL=/var/mail/kevin
VSCODE_GIT_ASKPASS_MAIN=/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/extensions/git/dist/askpass-main.js
TERM=xterm-256color
SHELL=/bin/bash
ROS_PYTHON_VERSION=2
SHLVL=4
PYTHONPATH=/opt/ros/melodic/lib/python2.7/dist-packages
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-01c9a08504.sock
ROS_PACKAGE_PATH=/opt/ros/melodic/share
ROSLISP_PACKAGE_DIRECTORIES=
LOGNAME=kevin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
GIT_ASKPASS=/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/extensions/git/dist/askpass.sh
XDG_RUNTIME_DIR=/run/user/1000
PATH=/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
PKG_CONFIG_PATH=/opt/ros/melodic/lib/pkgconfig
ROS_DISTRO=melodic
LESSOPEN=| /usr/bin/lesspipe %s
_=/usr/bin/env
```

HOME
代表使用者的家目錄。還記得我們可以使用 cd ~ 去到自己的家目錄嗎？或者利用 cd 就可以直接回到使用者家目錄了。那就是取用這個變數啦～ 有很多程式都可能會取用到這個變數的值！

SHELL
告知我們，目前這個環境使用的 SHELL 是哪支程式？ Linux 預設使用 /bin/bash 的啦！

HISTSIZE
這個與『歷史命令』有關，亦即是， 我們曾經下達過的指令可以被系統記錄下來，而記錄的『筆數』則是由這個值來設定的。

MAIL
當我們使用 mail 這個指令在收信時，系統會去讀取的郵件信箱檔案 (mailbox)。

PATH
就是執行檔搜尋的路徑啦～目錄與目錄中間以冒號(:)分隔， 由於檔案的搜尋是依序由 PATH 的變數內的目錄來查詢，所以，目錄的順序也是重要的喔。

LANG
這個重要！就是語系資料囉～很多訊息都會用到他， 舉例來說，當我們在啟動某些 perl 的程式語言檔案時，他會主動的去分析語系資料檔案， 如果發現有他無法解析的編碼語系，可能會產生錯誤喔！一般來說，我們中文編碼通常是 zh_TW.Big5 或者是 zh_TW.UTF-8，這兩個編碼偏偏不容易被解譯出來，所以，有的時候，可能需要修訂一下語系資料。 這部分我們會在下個小節做介紹的！

RANDOM
這個玩意兒就是『隨機亂數』的變數啦！目前大多數的 distributions 都會有亂數產生器，那就是 /dev/random 這個檔案。 我們可以透過這個亂數檔案相關的變數 (\$RANDOM) 來隨機取得亂數值喔。在 BASH 的環境下，這個 RANDOM 變數的內容，介於 0~32767 之間，所以，你只要 echo \$RANDOM 時，系統就會主動的隨機取出一個介於 0~32767 的數值。萬一我想要使用 0~9 之間的數值呢？呵呵～利用 declare 宣告數值類型， 然後這樣做就可以了：

#### 用 set 觀察所有變數 (含環境變數與自訂變數)

bash 可不只有環境變數喔，還有一些與 bash 操作介面有關的變數，以及使用者自己定義的變數存在的。 那麼這些變數如何觀察呢？這個時候就得要使用 set 這個指令了。 set 除了環境變數之外， 還會將其他在 bash 內的變數通通顯示出來哩！資訊很多，底下鳥哥僅列出幾個重要的內容：

\$：(關於本 shell 的 PID)
錢字號本身也是個變數喔！這個咚咚代表的是『目前這個 Shell 的執行緒代號』，亦即是所謂的 PID (Process ID)。 更多的程序觀念，我們會在第四篇的時候提及。想要知道我們的 shell 的 PID ，就可以用：『 echo $$ 』即可！出現的數字就是你的 PID 號碼。
```
kevin@ubuntu:~/os$ echo $$
2677
```

\?：(關於上個執行指令的回傳值)
蝦密？問號也是一個特殊的變數？沒錯！在 bash 裡面這個變數可重要的很！ 這個變數是：『**上一個執行的指令所回傳的值**』， 上面這句話的重點是『上一個指令』與『回傳值』兩個地方。當我們執行某些指令時， 這些指令都會回傳一個執行後的代碼。一般來說，如果成功的執行該指令， 則會回傳一個 0 值，如果執行過程發生錯誤，就會回傳『錯誤代碼』才對！一般就是以非為 0 的數值來取代。 我們以底下的例子來看看：

#### export： 自訂變數轉成環境變數

談了 env 與 set 現在知道有所謂的環境變數與自訂變數，那麼這兩者之間有啥差異呢？其實這兩者的差異在於『 **該變數是否會被子程序所繼續引用**』啦！唔！那麼啥是父程序？子程序？ 這就得要瞭解一下指令的下達行為了。

當你登入 Linux 並取得一個 bash 之後，你的 bash 就是一個獨立的程序，這個程序的識別使用的是一個稱為程序識別碼，被稱為 PID 的就是。 接下來你在這個 bash 底下所下達的任何指令都是由這個 bash 所衍生出來的，那些被下達的指令就被稱為子程序了。 我們可以用底下的圖示來簡單的說明一下父程序與子程序的概念：

<div align = center><img src="/os_note/bash/picture/ppid.gif"></div>
<div align = center>圖10.2.3、程序相關性示意圖</div>

如上所示，我們在原本的 bash 底下執行另一個 bash ，結果操作的環境介面會跑到第二個 bash 去(就是子程序)， 那原本的 bash 就會在暫停的情況 (睡著了，就是 sleep)。整個指令運作的環境是實線的部分！若要回到原本的 bash 去， 就只有將第二個 bash 結束掉 (下達 exit 或 logout) 才行。更多的程序概念我們會在第四篇談及，這裡只要有這個概念即可。

這個程序概念與變數有啥關係啊？關係可大了！**因為子程序僅會繼承父程序的環境變數， 子程序不會繼承父程序的自訂變數啦**！所以你在原本 bash 的自訂變數在進入了子程序後就會消失不見， 一直到你離開子程序並回到原本的父程序後，這個變數才會又出現！

換個角度來想，也就是說，**如果我能將自訂變數變成環境變數的話，那不就可以讓該變數值繼續存在於子程序了**？ 呵呵！沒錯！此時，那個 export 指令就很有用啦！如你想要讓該變數內容繼續的在子程序中使用，那麼就請執行：

```
[dmtsai@study ~]$ export 變數名稱
```

這東西用在『分享自己的變數設定給後來呼叫的檔案或其他程序』啦！ 像鳥哥常常在自己的主檔案後面呼叫其他附屬檔案(類似函式的功能)，但是主檔案與附屬檔案內都有相同的變數名稱， 若一再重複設定時，要修改也很麻煩，**此時只要在原本的第一個檔案內設定好『 export 變數 』， 後面所呼叫的檔案就能夠使用這個變數設定了！而不需要重複設定**，這非常實用於 shell script 當中喔！ 如果僅下達 export 而沒有接變數時，那麼此時將會把所有的『環境變數』秀出來喔！例如：

```
kevin@ubuntu:~/os$ export
declare -x BROWSER="/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/helpers/browser.sh"
declare -x CMAKE_PREFIX_PATH="/opt/ros/melodic"
declare -x COLORTERM="truecolor"
declare -x DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/1000/bus"
declare -x GIT_ASKPASS="/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/extensions/git/dist/askpass.sh"
declare -x HOME="/home/kevin"
declare -x LANG="en_US.UTF-8"
declare -x LD_LIBRARY_PATH="/opt/ros/melodic/lib"
declare -x LESSCLOSE="/usr/bin/lesspipe %s %s"
declare -x LESSOPEN="| /usr/bin/lesspipe %s"
declare -x LOGNAME="kevin"
declare -x LS_COLORS="rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:"
declare -x MAIL="/var/mail/kevin"
declare -x OLDPWD="/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b"
declare -x PATH="/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
declare -x PKG_CONFIG_PATH="/opt/ros/melodic/lib/pkgconfig"
declare -x PWD="/home/kevin/os"
declare -x PYTHONPATH="/opt/ros/melodic/lib/python2.7/dist-packages"
declare -x ROSLISP_PACKAGE_DIRECTORIES=""
declare -x ROS_DISTRO="melodic"
declare -x ROS_ETC_DIR="/opt/ros/melodic/etc/ros"
declare -x ROS_MASTER_URI="http://localhost:11311"
declare -x ROS_PACKAGE_PATH="/opt/ros/melodic/share"
declare -x ROS_PYTHON_VERSION="2"
declare -x ROS_ROOT="/opt/ros/melodic/share/ros"
declare -x ROS_VERSION="1"
declare -x SHELL="/bin/bash"
declare -x SHLVL="4"
declare -x SSH_CLIENT="192.168.0.109 3906 22"
declare -x SSH_CONNECTION="192.168.0.109 3906 192.168.0.111 22"
declare -x TERM="xterm-256color"
declare -x TERM_PROGRAM="vscode"
declare -x TERM_PROGRAM_VERSION="1.73.1"
declare -x USER="kevin"
declare -x VSCODE_GIT_ASKPASS_EXTRA_ARGS=""
declare -x VSCODE_GIT_ASKPASS_MAIN="/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/extensions/git/dist/askpass-main.js"
declare -x VSCODE_GIT_ASKPASS_NODE="/home/kevin/.vscode-server/bin/6261075646f055b99068d3688932416f2346dd3b/node"
declare -x VSCODE_GIT_IPC_HANDLE="/run/user/1000/vscode-git-01c9a08504.sock"
declare -x VSCODE_IPC_HOOK_CLI="/run/user/1000/vscode-ipc-60810494-8ef8-40ee-8564-a679ed7b493d.sock"
declare -x XDG_DATA_DIRS="/usr/local/share:/usr/share:/var/lib/snapd/desktop"
declare -x XDG_RUNTIME_DIR="/run/user/1000"
declare -x XDG_SESSION_ID="4"
```

那如何將環境變數轉成自訂變數呢？可以使用本章後續介紹的 declare 呢！

### 10.2.4 影響顯示結果的語系變數 (locale)

還記得我們在第四章裡面提到的語系問題嗎？ 就是當我們使用 man command 的方式去查詢某個資料的說明檔時，該說明檔的內容可能會因為我們使用的語系不同而產生亂碼。 另外，利用 ls 查詢檔案的時間時，也可能會有亂碼出現在時間的部分。那個問題其實就是語系的問題啦。

目前大多數的 Linux distributions 已經都是支援日漸流行的萬國碼了，也都支援大部分的國家語系。 那麼我們的 Linux 到底支援了多少的語系呢？這可以由 locale 這個指令來查詢到喔！
```
kevin@ubuntu:~/os$ locale -a
C
C.UTF-8
en_AG
en_AG.utf8
en_AU.utf8
en_BW.utf8
en_CA.utf8
en_DK.utf8
en_GB.utf8
en_HK.utf8
en_IE.utf8
en_IL
en_IL.utf8
en_IN
en_IN.utf8
en_NG
en_NG.utf8
en_NZ.utf8
en_PH.utf8
en_SG.utf8
en_US.utf8
en_ZA.utf8
en_ZM
en_ZM.utf8
en_ZW.utf8
POSIX
```