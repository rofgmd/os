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

kevin@ubuntu:~/os$ locale
LANG=en_US.UTF-8
LANGUAGE=
LC_CTYPE="en_US.UTF-8"
LC_NUMERIC="en_US.UTF-8"
LC_TIME="en_US.UTF-8"
LC_COLLATE="en_US.UTF-8"
LC_MONETARY="en_US.UTF-8"
LC_MESSAGES="en_US.UTF-8"
LC_PAPER="en_US.UTF-8"
LC_NAME="en_US.UTF-8"
LC_ADDRESS="en_US.UTF-8"
LC_TELEPHONE="en_US.UTF-8"
LC_MEASUREMENT="en_US.UTF-8"
LC_IDENTIFICATION="en_US.UTF-8"
LC_ALL=
```

### 10.2.5 變數的有效範圍

蝦密？變數也有使用的『範圍』？沒錯啊～我們在上頭的 export 指令說明中，就提到了這個概念了。如果在跑程式的時候，有父程序與子程序的不同程序關係時， 則『變數』可否被引用與 export 有關。被 export 後的變數，我們可以稱他為『環境變數』！ 環境變數可以被子程序所引用，但是其他的自訂變數內容就不會存在於子程序中。

在學理方面，為什麼環境變數的資料可以被子程序所引用呢？這是因為記憶體配置的關係！理論上是這樣的：

    當啟動一個 shell，作業系統會分配一記憶區塊給 shell 使用，此記憶體內之變數可讓子程序取用
    若在父程序利用 export 功能，可以讓自訂變數的內容寫到上述的記憶區塊當中(環境變數)；
    當載入另一個 shell 時 (亦即啟動子程序，而離開原本的父程序了)，子 shell 可以將父 shell 的環境變數所在的記憶區塊導入自己的環境變數區塊當中。
透過這樣的關係，我們就可以讓某些變數在相關的程序之間存在，以幫助自己更方便的操作環境喔！ 不過要提醒的是，這個『環境變數』與『bash 的操作環境』意思不太一樣，舉例來說， PS1 並不是環境變數， 但是這個 PS1 會影響到 bash 的介面 (提示字元嘛)！相關性要釐清喔！^_^

### 10.2.6 變數鍵盤讀取、陣列與宣告： read, array, declare

我們上面提到的變數設定功能，都是由指令列直接設定的，那麼，可不可以讓使用者能夠經由鍵盤輸入？ 什麼意思呢？是否記得某些程式執行的過程當中，會等待使用者輸入 "yes/no" 之類的訊息啊？ 在 bash 裡面也有相對應的功能喔！此外，我們還可以宣告這個變數的屬性，例如：陣列或者是數字等等的。底下就來看看吧！

#### read

要讀取來自鍵盤輸入的變數，就是用 read 這個指令了。這個指令最常被用在 shell script 的撰寫當中， 想要跟使用者對談？用這個指令就對了。關於 script 的寫法，我們會在第十三章介紹，底下先來瞧一瞧 read 的相關語法吧！

```
[dmtsai@study ~]$ read [-pt] variable
選項與參數：
-p  ：後面可以接提示字元！
-t  ：後面可以接等待的『秒數！』這個比較有趣～不會一直等待使用者啦！

範例一：讓使用者由鍵盤輸入一內容，將該內容變成名為 atest 的變數
[dmtsai@study ~]$ read atest
This is a test        <==此時游標會等待你輸入！請輸入左側文字看看
[dmtsai@study ~]$ echo ${atest}
This is a test          <==你剛剛輸入的資料已經變成一個變數內容！

範例二：提示使用者 30 秒內輸入自己的大名，將該輸入字串作為名為 named 的變數內容
[dmtsai@study ~]$ read -p "Please keyin your name: " -t 30 named
Please keyin your name: VBird Tsai   <==注意看，會有提示字元喔！
[dmtsai@study ~]$ echo ${named}
VBird Tsai        <==輸入的資料又變成一個變數的內容了！
```

read 之後不加任何參數，直接加上變數名稱，那麼底下就會主動出現一個空白行等待你的輸入(如範例一)。 如果加上 -t 後面接秒數，例如上面的範例二，那麼 30 秒之內沒有任何動作時， 該指令就會自動略過了～如果是加上 -p ，嘿嘿！在輸入的游標前就會有比較多可以用的提示字元給我們參考！ 在指令的下達裡面，比較美觀啦！ ^_^

#### declare / typeset

declare 或 typeset 是一樣的功能，就是在『宣告變數的類型』。如果使用 declare 後面並沒有接任何參數，那麼 bash 就會主動的將所有的變數名稱與內容通通叫出來，就好像使用 set 一樣啦！ 那麼 declare 還有什麼語法呢？看看先：
```
[dmtsai@study ~]$ declare [-aixr] variable
選項與參數：
-a  ：將後面名為 variable 的變數定義成為陣列 (array) 類型
-i  ：將後面名為 variable 的變數定義成為整數數字 (integer) 類型
-x  ：用法與 export 一樣，就是將後面的 variable 變成環境變數；
-r  ：將變數設定成為 readonly 類型，該變數不可被更改內容，也不能 unset

範例一：讓變數 sum 進行 100+300+50 的加總結果
[dmtsai@study ~]$ sum=100+300+50
[dmtsai@study ~]$ echo ${sum}
100+300+50  <==咦！怎麼沒有幫我計算加總？因為這是文字型態的變數屬性啊！
[dmtsai@study ~]$ declare -i sum=100+300+50
[dmtsai@study ~]$ echo ${sum}
450         <==瞭乎？？

kevin@ubuntu:~/os$ sum=100+200+300
kevin@ubuntu:~/os$ echo $sum
100+200+300
kevin@ubuntu:~/os$ declare -i sum
kevin@ubuntu:~/os$ echo $suum

kevin@ubuntu:~/os$ echo $sum
100+200+300
kevin@ubuntu:~/os$ declare -i sum=100+200+300
kevin@ubuntu:~/os$ echo $sum
600
```
由於在預設的情況底下， bash 對於變數有幾個基本的定義：

**變數類型預設為『字串』**，所以若不指定變數類型，則 1+2 為一個『字串』而不是『計算式』。 所以上述第一個執行的結果才會出現那個情況的；
bash 環境中的數值運算，預設最多僅能到達整數形態，所以 1/3 結果是 0；
現在你曉得為啥你需要進行變數宣告了吧？如果需要非字串類型的變數，那就得要進行變數的宣告才行啦！ 底下繼續來玩些其他的 declare 功能。

```
範例二：將 sum 變成環境變數
[dmtsai@study ~]$ declare -x sum
[dmtsai@study ~]$ export | grep sum
declare -ix sum="450"  <==果然出現了！包括有 i 與 x 的宣告！

範例三：讓 sum 變成唯讀屬性，不可更動！
[dmtsai@study ~]$ declare -r sum
[dmtsai@study ~]$ sum=testing
-bash: sum: readonly variable  <==老天爺～不能改這個變數了！

範例四：讓 sum 變成非環境變數的自訂變數吧！
[dmtsai@study ~]$ declare +x sum  <== 將 - 變成 + 可以進行『取消』動作
[dmtsai@study ~]$ declare -p sum  <== -p 可以單獨列出變數的類型
declare -ir sum="450" <== 看吧！只剩下 i, r 的類型，不具有 x 囉！
```
declare 也是個很有用的功能～尤其是當我們需要使用到底下的陣列功能時， 他也可以幫我們宣告陣列的屬性喔！不過，老話一句，陣列也是在 shell script 比較常用的啦！ 比較有趣的是，如果你不小心將變數設定為『唯讀』，通常得要登出再登入才能復原該變數的類型了！ @_@

#### 陣列 (array) 變數類型

某些時候，我們必須使用陣列來宣告一些變數，這有什麼好處啊？在一般人的使用上， 果然是看不出來有什麼好處的！不過，如果您曾經寫過程式的話，那才會比較瞭解陣列的意義～ 陣列對寫數值程式的設計師來說，可是不能錯過學習的重點之一哩！好！不囉唆～ 那麼要如何設定陣列的變數與內容呢？在 bash 裡頭，陣列的設定方式是：

var[index]=content

意思是說，我有一個陣列名稱為 var ，而這個陣列的內容為 var[1]=小明， var[2]=大明， var[3]=好明 .... 等等，那個 index 就是一些數字啦，重點是用中刮號 ([ ]) 來設定的。 目前我們 bash 提供的是一維陣列。老實說，如果您不必寫一些複雜的程式， 那麼這個陣列的地方，可以先略過，等到有需要再來學習即可！因為要製作出陣列， 通常與迴圈或者其他判斷式交互使用才有比較高的存在意義！
```
範例：設定上面提到的 var[1] ～ var[3] 的變數。
[dmtsai@study ~]$ var[1]="small min"
[dmtsai@study ~]$ var[2]="big min"
[dmtsai@study ~]$ var[3]="nice min"
[dmtsai@study ~]$ echo "${var[1]}, ${var[2]}, ${var[3]}"
small min, big min, nice min`
```

### 10.2.7 與檔案系統及程序的限制關係： ulimit

想像一個狀況：我的 Linux 主機裡面同時登入了十個人，這十個人不知怎麼搞的， 同時開啟了 100 個檔案，每個檔案的大小約 10MBytes ，請問一下， 我的 Linux 主機的記憶體要有多大才夠？ 10*100*10 = 10000 MBytes = 10GBytes ... 老天爺，這樣，系統不掛點才有鬼哩！為了要預防這個情況的發生，所以我們的 bash 是可以『限制使用者的某些系統資源』的，包括可以開啟的檔案數量， 可以使用的 CPU 時間，可以使用的記憶體總量等等。如何設定？用 ulimit 吧！

```
[dmtsai@study ~]$ ulimit [-SHacdfltu] [配額]
選項與參數：
-H  ：hard limit ，嚴格的設定，必定不能超過這個設定的數值；
-S  ：soft limit ，警告的設定，可以超過這個設定值，但是若超過則有警告訊息。
      在設定上，通常 soft 會比 hard 小，舉例來說，soft 可設定為 80 而 hard 
      設定為 100，那麼你可以使用到 90 (因為沒有超過 100)，但介於 80~100 之間時，
      系統會有警告訊息通知你！
-a  ：後面不接任何選項與參數，可列出所有的限制額度；
-c  ：當某些程式發生錯誤時，系統可能會將該程式在記憶體中的資訊寫成檔案(除錯用)，
      這種檔案就被稱為核心檔案(core file)。此為限制每個核心檔案的最大容量。
-f  ：此 shell 可以建立的最大檔案容量(一般可能設定為 2GB)單位為 Kbytes
-d  ：程序可使用的最大斷裂記憶體(segment)容量；
-l  ：可用於鎖定 (lock) 的記憶體量
-t  ：可使用的最大 CPU 時間 (單位為秒)
-u  ：單一使用者可以使用的最大程序(process)數量。

範例一：列出你目前身份(假設為一般帳號)的所有限制資料數值
[dmtsai@study ~]$ ulimit -a
core file size          (blocks, -c) 0          <==只要是 0 就代表沒限制
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited  <==可建立的單一檔案的大小
pending signals                 (-i) 4903
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024       <==同時可開啟的檔案數量
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 4096
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited

範例二：限制使用者僅能建立 10MBytes 以下的容量的檔案
[dmtsai@study ~]$ ulimit -f 10240
[dmtsai@study ~]$ ulimit -a | grep 'file size'
core file size          (blocks, -c) 0
file size               (blocks, -f) 10240 <==最大量為10240Kbyes，相當10Mbytes

[dmtsai@study ~]$ dd if=/dev/zero of=123 bs=1M count=20
File size limit exceeded (core dumped) <==嘗試建立 20MB 的檔案，結果失敗了！

[dmtsai@study ~]$ rm 123  <==趕快將這個檔案刪除囉！同時你得要登出再次的登入才能解開 10M 的限制

kevin@ubuntu:~/os$ ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 21431
max locked memory       (kbytes, -l) 65536
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1048576
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 21431
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

### 10.2.8 變數內容的刪除、取代與替換 (Optional)

變數除了可以直接設定來修改原本的內容之外，有沒有辦法透過簡單的動作來將變數的內容進行微調呢？ 舉例來說，進行變數內容的刪除、取代與替換等！是可以的！我們可以透過幾個簡單的小步驟來進行變數內容的微調喔！ 底下就來試試看！

#### 變數內容的刪除與取代

變數的內容可以很簡單的透過幾個咚咚來進行刪除喔！我們使用 PATH 這個變數的內容來做測試好了。 請你依序進行底下的幾個例子來玩玩，比較容易感受的到鳥哥在這裡想要表達的意義：
```
範例一：先讓小寫的 path 自訂變數設定的與 PATH 內容相同
[dmtsai@study ~]$ path=${PATH}
[dmtsai@study ~]$ echo ${path}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin

範例二：假設我不喜歡 local/bin，所以要將前 1 個目錄刪除掉，如何顯示？
[dmtsai@study ~]$ echo ${path#/*local/bin:}
/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin

${variable#/*local/bin:}
   上面的特殊字體部分是關鍵字！用在這種刪除模式所必須存在的

${variable#/*local/bin:}
   這就是原本的變數名稱，以上面範例二來說，這裡就填寫 path 這個『變數名稱』啦！

${variable#/*local/bin:}
   這是重點！代表『從變數內容的最前面開始向右刪除』，且僅刪除最短的那個

${variable#/*local/bin:}
   代表要被刪除的部分，由於 # 代表由前面開始刪除，所以這裡便由開始的 / 寫起。
   需要注意的是，我們還可以透過萬用字元 * 來取代 0 到無窮多個任意字元

   以上面範例二的結果來看， path 這個變數被刪除的內容如下所示：
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
```
很有趣吧！這樣瞭解了 # 的功能了嗎？接下來讓我們來看看底下的範例三！
```
範例三：我想要刪除前面所有的目錄，僅保留最後一個目錄
[dmtsai@study ~]$ echo ${path#/*:}
/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
# 由於一個 # 僅刪除掉最短的那個，因此他刪除的情況可以用底下的刪除線來看：
# /usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin

[dmtsai@study ~]$ echo ${path##/*:}
/home/dmtsai/bin
# 嘿！多加了一個 # 變成 ## 之後，他變成『刪除掉最長的那個資料』！亦即是：
# /home/dmtsai/bin
```

非常有趣！不是嗎？因為在 PATH 這個變數的內容中，每個目錄都是以冒號『:』隔開的， 所以要從頭刪除掉目錄就是介於斜線 (/) 到冒號 (:) 之間的資料！但是 PATH 中不止一個冒號 (:) 啊！ 所以 # 與 ## 就分別代表：

\# ：符合取代文字的『最短的』那一個；
\##：符合取代文字的『最長的』那一個
上面談到的是『從前面開始刪除變數內容』，那麼如果想要『從後面向前刪除變數內容』呢？ 這個時候就得使用百分比 (%) 符號了！來看看範例四怎麼做吧！
```
範例四：我想要刪除最後面那個目錄，亦即從 : 到 bin 為止的字串
[dmtsai@study ~]$ echo ${path%:*bin}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin
# 注意啊！最後面一個目錄不見去！
# 這個 % 符號代表由最後面開始向前刪除！所以上面得到的結果其實是來自如下：
# /usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin

範例五：那如果我只想要保留第一個目錄呢？
[dmtsai@study ~]$ echo ${path%%:*bin}
/usr/local/bin
# 同樣的， %% 代表的則是最長的符合字串，所以結果其實是來自如下：
# /usr/local/bin
```
由於我是想要由變數內容的後面向前面刪除，而我這個變數內容最後面的結尾是『/home/dmtsai/bin』， 所以你可以看到上面我刪除的資料最終一定是『bin』，亦即是『:*bin』那個 * 代表萬用字元！ 至於 % 與 %% 的意義其實與 # 及 ## 類似！這樣理解否？

瞭解了刪除功能後，接下來談談取代吧！繼續玩玩範例六囉！
```
範例六：將 path 的變數內容內的 sbin 取代成大寫 SBIN：
[dmtsai@study ~]$ echo ${path/sbin/SBIN}
/usr/local/bin:/usr/bin:/usr/local/SBIN:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
# 這個部分就容易理解的多了！關鍵字在於那兩個斜線，兩斜線中間的是舊字串
# 後面的是新字串，所以結果就會出現如上述的特殊字體部分囉！

[dmtsai@study ~]$ echo ${path//sbin/SBIN}
/usr/local/bin:/usr/bin:/usr/local/SBIN:/usr/SBIN:/home/dmtsai/.local/bin:/home/dmtsai/bin
# 如果是兩條斜線，那麼就變成所有符合的內容都會被取代喔！
```


|變數設定方式|	說明|
|---|---|
|\${變數#關鍵字} \${變數##關鍵字}	|若變數內容從頭開始的資料符合『關鍵字』，則將符合的最短資料刪除若變數內容從頭開始的資料符合『關鍵字』，則將符合的最長資料刪除|
|\${變數\%關鍵字} \${變數%%關鍵字}	|若變數內容從尾向前的資料符合『關鍵字』，則將符合的最短資料刪除若變數內容從尾向前的資料符合『關鍵字』，則將符合的最長資料刪除|
|\${變數/舊字串/新字串} \${變數//舊字串/新字串}	|若變數內容符合『舊字串』則『第一個舊字串會被新字串取代』 若變數內容符合『舊字串』則『全部的舊字串會被新字串取代』|

#### 變數的測試與內容替換

在某些時刻我們常常需要『判斷』某個變數是否存在，若變數存在則使用既有的設定，若變數不存在則給予一個常用的設定。 我們舉底下的例子來說明好了，看看能不能較容易被你所理解呢！

```
範例一：測試一下是否存在 username 這個變數，若不存在則給予 username 內容為 root
[dmtsai@study ~]$ echo ${username}
           <==由於出現空白，所以 username 可能不存在，也可能是空字串
[dmtsai@study ~]$ username=${username-root}
[dmtsai@study ~]$ echo ${username}
root       <==因為 username 沒有設定，所以主動給予名為 root 的內容。
[dmtsai@study ~]$ username="vbird tsai" <==主動設定 username 的內容
[dmtsai@study ~]$ username=${username-root}
[dmtsai@study ~]$ echo ${username}
vbird tsai <==因為 username 已經設定了，所以使用舊有的設定而不以 root 取代
```
在上面的範例中，重點在於減號『 - 』後面接的關鍵字！基本上你可以這樣理解：
```
new_var=${old_var-content}
   新的變數，主要用來取代舊變數。新舊變數名稱其實常常是一樣的

new_var=${old_var-content}
   這是本範例中的關鍵字部分！必須要存在的哩！

new_var=${old_var-content}
   舊的變數，被測試的項目！

new_var=${old_var-content}
   變數的『內容』，在本範例中，這個部分是在『給予未設定變數的內容』
```

<div align=center><img src="/os_note/bash/picture/屏幕截图%202022-11-11%20123658.png"></div>
<div align=center></div>

根據上面這張表，我們來進行幾個範例的練習吧！ ^_^！首先讓我們來測試一下，如果舊變數 (str) 不存在時， 我們要給予新變數一個內容，若舊變數存在則新變數內容以舊變數來替換，結果如下：

```
測試：先假設 str 不存在 (用 unset) ，然後測試一下減號 (-) 的用法：
[dmtsai@study ~]$ unset str; var=${str-newvar}
[dmtsai@study ~]$ echo "var=${var}, str=${str}"
var=newvar, str=        <==因為 str 不存在，所以 var 為 newvar

測試：若 str 已存在，測試一下 var 會變怎樣？：
[dmtsai@study ~]$ str="oldvar"; var=${str-newvar}
[dmtsai@study ~]$ echo "var=${var}, str=${str}"
var=oldvar, str=oldvar  <==因為 str 存在，所以 var 等於 str 的內容
```
關於減號 (-) 其實上面我們談過了！這裡的測試只是要讓你更加瞭解，這個減號的測試並不會影響到舊變數的內容。 如果你想要將舊變數內容也一起替換掉的話，那麼就使用等號 (=) 吧！
```
測試：先假設 str 不存在 (用 unset) ，然後測試一下等號 (=) 的用法：
[dmtsai@study ~]$ unset str; var=${str=newvar}
[dmtsai@study ~]$ echo "var=${var}, str=${str}"
var=newvar, str=newvar  <==因為 str 不存在，所以 var/str 均為 newvar

測試：如果 str 已存在了，測試一下 var 會變怎樣？
[dmtsai@study ~]$ str="oldvar"; var=${str=newvar}
[dmtsai@study ~]$ echo "var=${var}, str=${str}"
var=oldvar, str=oldvar  <==因為 str 存在，所以 var 等於 str 的內容
```
那如果我只是想知道，如果舊變數不存在時，整個測試就告知我『有錯誤』，此時就能夠使用問號『 ? 』的幫忙啦！ 底下這個測試練習一下先！
```
測試：若 str 不存在時，則 var 的測試結果直接顯示 "無此變數"
[dmtsai@study ~]$ unset str; var=${str?無此變數}
-bash: str: 無此變數    <==因為 str 不存在，所以輸出錯誤訊息 

測試：若 str 存在時，則 var 的內容會與 str 相同！
[dmtsai@study ~]$ str="oldvar"; var=${str?novar}
[dmtsai@study ~]$ echo "var=${var}, str=${str}"
var=oldvar, str=oldvar  <==因為 str 存在，所以 var 等於 str 的內容
```
基本上這種變數的測試也能夠透過 shell script 內的 if...then... 來處理， 不過既然 bash 有提供這麼簡單的方法來測試變數，那我們也可以多學一些嘛！ 不過這種變數測試通常是在程式設計當中比較容易出現，如果這裡看不懂就先略過，未來有用到判斷變數值時，再回來看看吧！ ^_^

## 10.3 命令別名與歷史命令

我們知道在早期的 DOS 年代，清除螢幕上的資訊可以使用 cls 來清除，但是在 Linux 裡面， 我們則是使用 clear 來清除畫面的。那麼可否讓 cls 等於 clear 呢？可以啊！用啥方法？ link file 還是什麼的？別急！底下我們介紹不用 link file 的命令別名來達成。那麼什麼又是歷史命令？ 曾經做過的舉動我們可以將他記錄下來喔！那就是歷史命令囉～底下分別來談一談這兩個玩意兒。

### 10.3.1 命令別名設定： alias, unalias

```
[dmtsai@study ~]$ history [n]
[dmtsai@study ~]$ history [-c]
[dmtsai@study ~]$ history [-raw] histfiles
選項與參數：
n   ：數字，意思是『要列出最近的 n 筆命令列表』的意思！
-c  ：將目前的 shell 中的所有 history 內容全部消除
-a  ：將目前新增的 history 指令新增入 histfiles 中，若沒有加 histfiles ，
      則預設寫入 ~/.bash_history
-r  ：將 histfiles 的內容讀到目前這個 shell 的 history 記憶中；
-w  ：將目前的 history 記憶內容寫入 histfiles 中！

範例一：列出目前記憶體內的所有 history 記憶
[dmtsai@study ~]$ history
# 前面省略
 1017  man bash
 1018  ll
 1019  history 
 1020  history
# 列出的資訊當中，共分兩欄，第一欄為該指令在這個 shell 當中的代碼，
# 另一個則是指令本身的內容喔！至於會秀出幾筆指令記錄，則與 HISTSIZE 有關！

範例二：列出目前最近的 3 筆資料
[dmtsai@study ~]$ history 3
 1019  history 
 1020  history
 1021  history 3

範例三：立刻將目前的資料寫入 histfile 當中
[dmtsai@study ~]$ history -w
# 在預設的情況下，會將歷史紀錄寫入 ~/.bash_history 當中！
[dmtsai@study ~]$ echo ${HISTSIZE}
1000
```

在正常的情況下，歷史命令的讀取與記錄是這樣的：

- 當我們以 bash 登入 Linux 主機之後，系統會主動的由家目錄的 ~/.bash_history 讀取以前曾經下過的指令，那麼 ~/.bash_history 會記錄幾筆資料呢？這就與你 bash 的 HISTFILESIZE 這個變數設定值有關了！

- 假設我這次登入主機後，共下達過 100 次指令，『等我登出時， 系統就會將 101~1100 這總共 1000 筆歷史命令更新到 ~/.bash_history 當中。』 也就是說，歷史命令在我登出時，會將最近的 HISTFILESIZE 筆記錄到我的紀錄檔當中啦！

- 當然，也可以用 history -w 強制立刻寫入的！那為何用『更新』兩個字呢？ 因為 ~/.bash_history 記錄的筆數永遠都是 HISTFILESIZE 那麼多，舊的訊息會被主動的拿掉！ 僅保留最新的！

那麼 history 這個歷史命令只可以讓我查詢命令而已嗎？呵呵！當然不止啊！ 我們可以利用相關的功能來幫我們執行命令呢！舉例來說囉：

```
kevin@ubuntu:~$ !10
ls
Desktop    Downloads  os        Public  Templates
Documents  Music      Pictures  snap    Videos
kevin@ubuntu:~$ !s
sudo apt install python3-pip
[sudo] password for kevin: 
Reading package lists... Done
Building dependency tree       
Reading state information... Done
python3-pip is already the newest version (20.0.2-5ubuntu1.6).
The following package was automatically installed and is no longer required:
  libllvm11
Use 'sudo apt autoremove' to remove it.
0 upgraded, 0 newly installed, 0 to remove and 404 not upgraded.
kevin@ubuntu:~$ !l
ls
Desktop    Downloads  os        Public  Templates
Documents  Music      Pictures  snap    Videos
kevin@ubuntu:~$ !!
ls
Desktop    Downloads  os        Public  Templates
Documents  Music      Pictures  snap    Videos
```

## 10.4 Bash Shell 的操作環境：

### 10.4.1 路徑與指令搜尋順序

我們在第五章與第六章都曾談過『相對路徑與絕對路徑』的關係， 在本章的前幾小節也談到了 alias 與 bash 的內建命令。現在我們知道系統裡面其實有不少的 ls 指令， 或者是包括內建的 echo 指令，那麼來想一想，如果一個指令 (例如 ls) 被下達時， 到底是哪一個 ls 被拿來運作？很有趣吧！基本上，指令運作的順序可以這樣看：

1. 以相對/絕對路徑執行指令，例如『 /bin/ls 』或『 ./ls 』；
2. 由 alias 找到該指令來執行；
3 .由 bash 內建的 (builtin) 指令來執行；
4. 透過 $PATH 這個變數的順序搜尋到的第一個指令來執行。

### 10.4.2 bash 的進站與歡迎訊息： /etc/issue, /etc/motd

```
kevin@ubuntu:~$ cat /etc/issue
Ubuntu 20.04.2 LTS \n \l

```

>issue 内各代码意义：
\d 本地端时间日期； 
\l 显示第几个终端机接口； 
\m 显示硬件等级 (i386/i486/i586/i686...)； 
\n 显示主机网络名称； 
\o 显示 domain name； 
\r 操作系统版本 (相当于 uname -r) 
\t 显示本地端时间； 
\s 操作系统名称； 
\v 操作系统版本。


### 10.4.3 bash 的環境設定檔

你是否會覺得奇怪，怎麼我們什麼動作都沒有進行，但是一進入 bash 就取得一堆有用的變數了？ 這是因為系統有一些環境設定檔案的存在，讓 bash 在啟動時直接讀取這些設定檔，以規劃好 bash 的操作環境啦！ 而這些設定檔又可以分為全體系統的設定檔以及使用者個人偏好設定檔。要注意的是， 我們前幾個小節談到的命令別名啦、自訂的變數啦，在你登出 bash 後就會失效，所以你想要保留你的設定， 就得要將這些設定寫入設定檔才行。底下就讓我們來聊聊吧！

#### login 與 non-login shell

在開始介紹 bash 的設定檔前，我們一定要先知道的就是 login shell 與 non-login shell！ 重點在於有沒有登入 (login) 啦！

- login shell：取得 bash 時需要完整的登入流程的，就稱為 login shell。舉例來說，你要由 tty1 ~ tty6 登入，需要輸入使用者的帳號與密碼，此時取得的 bash 就稱為『 login shell 』囉；

- non-login shell：取得 bash 介面的方法不需要重複登入的舉動，舉例來說，(1)你以 X window 登入 Linux 後， 再以 X 的圖形化介面啟動終端機，**此時那個終端介面並沒有需要再次的輸入帳號與密碼**，那個 bash 的環境就稱為 non-login shell了。(2)**你在原本的 bash 環境下再次下達 bash 這個指令，同樣的也沒有輸入帳號密碼**， 那第二個 bash (子程序) 也是 non-login shell 。

為什麼要介紹 login, non-login shell 呢？這是因為這兩個取得 bash 的情況中，讀取的設定檔資料並不一樣所致。 由於我們需要登入系統，所以先談談 login shell 會讀取哪些設定檔？一般來說，login shell 其實只會讀取這兩個設定檔：

- /etc/profile：這是系統整體的設定，你最好不要修改這個檔案；
- ~/.bash_profile 或 ~/.bash_login 或 ~/.profile：屬於使用者個人設定，你要改自己的資料，就寫入這裡！


那麼，就讓我們來聊一聊這兩個檔案吧！這兩個檔案的內容可是非常繁複的喔！

#### /etc/profile (login shell 才會讀)

你可以使用 vim 去閱讀一下這個檔案的內容。這個設定檔可以利用使用者的識別碼 (UID) 來決定很多重要的變數資料， 這也是每個使用者登入取得 bash 時一定會讀取的設定檔！ 所以如果你想要幫所有使用者設定整體環境，那就是改這裡囉！不過，沒事還是不要隨便改這個檔案喔 這個檔案設定的變數主要有：

- PATH：會依據 UID 決定 PATH 變數要不要含有 sbin 的系統指令目錄；
- MAIL：依據帳號設定好使用者的 mailbox 到 /var/spool/mail/帳號名；
- USER：根據使用者的帳號設定此一變數內容；
- HOSTNAME：依據主機的 hostname 指令決定此一變數內容；
- HISTSIZE：歷史命令記錄筆數。CentOS 7.x 設定為 1000 ；
- umask：包括 root 預設為 022 而一般用戶為 002 等！

/etc/profile 可不止會做這些事而已，他還會去呼叫外部的設定資料喔！在 CentOS 7.x 預設的情況下，底下這些資料會依序的被呼叫進來：

- /etc/profile.d/*.sh

其實這是個目錄內的眾多檔案！只要在 /etc/profile.d/ 這個目錄內且副檔名為 .sh ，另外，使用者能夠具有 r 的權限， 那麼該檔案就會被 /etc/profile 呼叫進來。在 CentOS 7.x 中，這個目錄底下的檔案規範了 bash 操作介面的顏色、 語系、ll 與 ls 指令的命令別名、vi 的命令別名、which 的命令別名等等。如果你需要幫所有使用者設定一些共用的命令別名時， 可以在這個目錄底下自行建立副檔名為 .sh 的檔案，並將所需要的資料寫入即可喔！

- /etc/locale.conf

這個檔案是由 /etc/profile.d/lang.sh 呼叫進來的！這也是我們決定 bash 預設使用何種語系的重要設定檔！ 檔案裡最重要的就是 LANG/LC_ALL 這些個變數的設定啦！我們在前面的 locale 討論過這個檔案囉！ 自行回去瞧瞧先！

- /usr/share/bash-completion/completions/*

記得我們上頭談過 [tab] 的妙用吧？除了命令補齊、檔名補齊之外，還可以進行指令的選項/參數補齊功能！那就是從這個目錄裡面找到相對應的指令來處理的！ 其實這個目錄底下的內容是由 /etc/profile.d/bash_completion.sh 這個檔案載入的啦！

反正你只要記得，bash 的 login shell 情況下所讀取的整體環境設定檔其實只有 /etc/profile，但是 /etc/profile 還會呼叫出其他的設定檔，所以讓我們的 bash 操作介面變的非常的友善啦！ 接下來，讓我們來瞧瞧，那麼個人偏好的設定檔又是怎麼回事？

#### ~/.bash_profile (login shell 才會讀)

bash 在讀完了整體環境設定的 /etc/profile 並藉此呼叫其他設定檔後，接下來則是會讀取使用者的個人設定檔。 在 login shell 的 bash 環境中，所讀取的個人偏好設定檔其實主要有三個，依序分別是：

- ~/.bash_profile
- ~/.bash_login
- ~/.profile

```
[dmtsai@study ~]$ cat ~/.bash_profile
# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then    <==底下這三行在判斷並讀取 ~/.bashrc
        . ~/.bashrc
fi

# User specific environment and startup programs
PATH=$PATH:$HOME/.local/bin:$HOME/bin    <==底下這幾行在處理個人化設定
export PATH
```
其實 bash 的 login shell 設定只會讀取上面三個檔案的其中一個， 而讀取的順序則是依照上面的順序。也就是說，如果 ~/.bash_profile 存在，那麼其他兩個檔案不論有無存在，都不會被讀取。 如果 ~/.bash_profile 不存在才會去讀取 ~/.bash_login，而前兩者都不存在才會讀取 ~/.profile 的意思。 會有這麼多的檔案，其實是因應其他 shell 轉換過來的使用者的習慣而已。 先讓我們來看一下 dmtsai 的 /home/dmtsai/.bash_profile 的內容是怎樣呢？

這個檔案內有設定 PATH 這個變數喔！而且還使用了 export 將 PATH 變成環境變數呢！ 由於 PATH 在 /etc/profile 當中已經設定過，所以在這裡就以累加的方式增加使用者家目錄下的 ~/bin/ 為額外的執行檔放置目錄。這也就是說，你可以將自己建立的執行檔放置到你自己家目錄下的 ~/bin/ 目錄啦！ 那就可以直接執行該執行檔而不需要使用絕對/相對路徑來執行該檔案。

這個檔案的內容比較有趣的地方在於 if ... then ... 那一段！那一段程式碼我們會在第十二章 shell script 談到，假設你現在是看不懂的。 該段的內容指的是『判斷家目錄下的 ~/.bashrc 存在否，若存在則讀入 ~/.bashrc 的設定』。 bash 設定檔的讀入方式比較有趣，主要是透過一個指令『 source 』來讀取的！ 也就是說 ~/.bash_profile 其實會再呼叫 ~/.bashrc 的設定內容喔！最後，我們來看看整個 login shell 的讀取流程：


<div align=center><img src="/os_note/bash/picture/centos7_bashrc_1.gif"></div>
<div align=center>圖10.4.1、login shell 的設定檔讀取流程</div>

實線的的方向是主線流程，虛線的方向則是被呼叫的設定檔！從上面我們也可以清楚的知道，在 CentOS 的 login shell 環境下，最終被讀取的設定檔是『 ~/.bashrc 』這個檔案喔！所以，你當然可以將自己的偏好設定寫入該檔案即可。 底下我們還要討論一下 source 與 ~/.bashrc 喔！

#### source ：讀入環境設定檔的指令

由於 /etc/profile 與 ~/.bash_profile 都是在取得 login shell 的時候才會讀取的設定檔，所以， 如果你將自己的偏好設定寫入上述的檔案後，通常都是得登出再登入後，該設定才會生效。那麼，能不能直接讀取設定檔而不登
出登入呢？ 可以的！那就得要利用 source 這個指令了！

```
[dmtsai@study ~]$ source 設定檔檔名

範例：將家目錄的 ~/.bashrc 的設定讀入目前的 bash 環境中
[dmtsai@study ~]$ source ~/.bashrc  <==底下這兩個指令是一樣的！
[dmtsai@study ~]$  .  ~/.bashrc

```

利用 source 或小數點 (.) 都可以將設定檔的內容讀進來目前的 shell 環境中！ 舉例來說，我修改了 ~/.bashrc ，那麼不需要登出，立即以 source ~/.bashrc 就可以將剛剛最新設定的內容讀進來目前的環境中！很不錯吧！還有，包括 ~/bash_profile 以及 /etc/profile 的設定中， 很多時候也都是利用到這個 source (或小數點) 的功能喔！

有沒有可能會使用到不同環境設定檔的時候？有啊！ 最常發生在一個人的工作環境分為多種情況的時候了！舉個例子來說，在鳥哥的大型主機中， 常常需要負責兩到三個不同的案子，每個案子所需要處理的環境變數訂定並不相同， 那麼鳥哥就將這兩三個案子分別編寫屬於該案子的環境變數設定檔案，當需要該環境時，就直接『 source 變數檔 』，如此一來，環境變數的設定就變的更簡便而靈活了！

~/.bashrc (non-login shell 會讀)
談完了 login shell 後，那麼 non-login shell 這種非登入情況取得 bash 操作介面的環境設定檔又是什麼？ 當你取得 non-login shell 時，該 bash 設定檔僅會讀取 ~/.bashrc 而已啦！那麼預設的 ~/.bashrc 內容是如何？

```
kevin@ubuntu:~/os$ cat ~/.bashrc
# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
        # We have color support; assume it's compliant with Ecma-48
        # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
        # a case would tend to support setf rather than setaf.)
        color_prompt=yes
    else
        color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
source /opt/ros/melodic/setup.bash
export PATH=/usr/lib/ccache:$PATH
export PATH="$HOME/qemu-5.0.0:$PATH"
export PATH="$HOME/qemu-5.0.0/riscv64-softmmu:$PATH"
export PATH="$HOME/qemu-5.0.0/riscv64-linux-user:$PATH"
export PATH="/usr/local/riscv64-unknown-elf-gcc/bin:$PATH"
export PATH="/usr/local/riscv64-linux-musl-cross/bin:$PATH"
```

此外，咱們的 CentOS 7.x 還會主動的呼叫 /etc/bashrc 這個檔案喔！為什麼需要呼叫 /etc/bashrc 呢？ 因為 /etc/bashrc 幫我們的 bash 定義出底下的資料：

依據不同的 UID 規範出 umask 的值；
依據不同的 UID 規範出提示字元 (就是 PS1 變數)；
呼叫 /etc/profile.d/*.sh 的設定
你要注意的是，這個 /etc/bashrc 是 CentOS 特有的 (其實是 Red Hat 系統特有的)，其他不同的 distributions 可能會放置在不同的檔名就是了。由於這個 ~/.bashrc 會呼叫 /etc/bashrc 及 /etc/profile.d/*.sh ， 所以，萬一你沒有 ~/.bashrc (可能自己不小心將他刪除了)，那麼你會發現你的 bash 提示字元可能會變成這個樣子：

#### 其他相關設定檔

事實上還有一些設定檔可能會影響到你的 bash 操作的，底下就來談一談：

/etc/man_db.conf
這個檔案乍看之下好像跟 bash 沒相關性，但是對於系統管理員來說， 卻也是很重要的一個檔案！這的檔案的內容『規範了使用 man 的時候， man page 的路徑到哪裡去尋找！』所以說的簡單一點，這個檔案規定了下達 man 的時候，該去哪裡查看資料的路徑設定！

那麼什麼時候要來修改這個檔案呢？如果你是以 tarball 的方式來安裝你的資料，那麼你的 man page 可能會放置在 /usr/local/softpackage/man 裡頭，那個 softpackage 是你的套件名稱， 這個時候你就得以手動的方式將該路徑加到 /etc/man_db.conf 裡頭，否則使用 man 的時候就會找不到相關的說明檔囉。

~/.bash_history
還記得我們在歷史命令提到過這個檔案吧？預設的情況下， 我們的歷史命令就記錄在這裡啊！而這個檔案能夠記錄幾筆資料，則與 HISTFILESIZE 這個變數有關啊。每次登入 bash 後，bash 會先讀取這個檔案，將所有的歷史指令讀入記憶體， 因此，當我們登入 bash 後就可以查知上次使用過哪些指令囉。至於更多的歷史指令， 請自行回去參考喔！

~/.bash_logout
這個檔案則記錄了『當我登出 bash 後，系統再幫我做完什麼動作後才離開』的意思。 你可以去讀取一下這個檔案的內容，預設的情況下，登出時， bash 只是幫我們清掉螢幕的訊息而已。 不過，你也可以將一些備份或者是其他你認為重要的工作寫在這個檔案中 (例如清空暫存檔)， 那麼當你離開 Linux 的時候，就可以解決一些煩人的事情囉！

### 10.4.4 終端機的環境設定： stty, set

我們在第四章首次登入 Linux 時就提過，可以在 tty1 ~ tty6 這六個文字介面的終端機 (terminal) 環境中登入，登入的時候我們可以取得一些字元設定的功能喔！ 舉例來說，我們可以利用倒退鍵 (backspace，就是那個←符號的按鍵) 來刪除命令列上的字元， 也可以使用 [ctrl]+c 來強制終止一個指令的運行，當輸入錯誤時，就會有聲音跑出來警告。這是怎麼辦到的呢？ 很簡單啊！因為登入終端機的時候，會自動的取得一些終端機的輸入環境的設定啊！

事實上，目前我們使用的 Linux distributions 都幫我們作了最棒的使用者環境了， 所以大家可以不用擔心操作環境的問題。不過，在某些 Unix like 的機器中，還是可能需要動用一些手腳， 才能夠讓我們的輸入比較快樂～舉例來說，利用 [backspace] 刪除，要比利用 [Del] 按鍵來的順手吧！ 但是某些 Unix 偏偏是以 [del] 來進行字元的刪除啊！所以，這個時候就可以動動手腳囉～

那麼如何查閱目前的一些按鍵內容呢？可以利用 stty (setting tty 終端機的意思) 呢！ stty 也可以幫助設定終端機的輸入按鍵代表意義

```
[dmtsai@study ~]$ stty [-a]
選項與參數：
-a  ：將目前所有的 stty 參數列出來；

kevin@ubuntu:~/os$ stty -a
speed 38400 baud; rows 17; columns 219; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = M-^?; eol2 = M-^?; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z; rprnt = ^R; werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
-parenb -parodd -cmspar cs8 hupcl -cstopb cread -clocal -crtscts
-ignbrk brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr icrnl ixon -ixoff -iuclc ixany imaxbel iutf8
opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
isig icanon iexten echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke -flusho -extproc
```

我們可以利用 stty -a 來列出目前環境中所有的按鍵列表，在上頭的列表當中，需要注意的是特殊字體那幾個， 此外，如果出現 ^ 表示 [Ctrl] 那個按鍵的意思。舉例來說， intr = ^C 表示利用 [ctrl] + c 來達成的。幾個重要的代表意義是：

intr  : 送出一個 interrupt (中斷) 的訊號給目前正在 run 的程序 (就是終止囉！)；
quit  : 送出一個 quit 的訊號給目前正在 run 的程序；
erase : 向後刪除字元，
kill  : 刪除在目前指令列上的所有文字；
eof   : End of file 的意思，代表『結束輸入』。
start : 在某個程序停止後，重新啟動他的 output
stop  : 停止目前螢幕的輸出；
susp  : 送出一個 terminal stop 的訊號給正在 run 的程序。
記不記得我們在第四章講過幾個 Linux 熱鍵啊？沒錯！ 就是這個 stty 設定值內的 intr([ctrl]+c) / eof([ctrl]+d) 囉～至於刪除字元，就是 erase 那個設定值啦！ 如果你想要用 [ctrl]+h 來進行字元的刪除，那麼可以下達：

除了 stty 之外，其實我們的 bash 還有自己的一些終端機設定值呢！那就是利用 set 來設定的！ 我們之前提到一些變數時，可以利用 set 來顯示，除此之外，其實 set 還可以幫我們設定整個指令輸出/輸入的環境。 例如記錄歷史命令、顯示錯誤內容等等。

```
[dmtsai@study ~]$ set [-uvCHhmBx]
選項與參數：
-u  ：預設不啟用。若啟用後，當使用未設定變數時，會顯示錯誤訊息；
-v  ：預設不啟用。若啟用後，在訊息被輸出前，會先顯示訊息的原始內容；
-x  ：預設不啟用。若啟用後，在指令被執行前，會顯示指令內容(前面有 ++ 符號)
-h  ：預設啟用。與歷史命令有關；
-H  ：預設啟用。與歷史命令有關；
-m  ：預設啟用。與工作管理有關；
-B  ：預設啟用。與刮號 [] 的作用有關；
-C  ：預設不啟用。若使用 > 等，則若檔案存在時，該檔案不會被覆蓋。

範例一：顯示目前所有的 set 設定值
[dmtsai@study ~]$ echo $-
himBH
# 那個 $- 變數內容就是 set 的所有設定啦！ bash 預設是 himBH 喔！
kevin@ubuntu:~/os$ echo $-
himBHs    

範例二：設定 "若使用未定義變數時，則顯示錯誤訊息" 
[dmtsai@study ~]$ set -u
[dmtsai@study ~]$ echo $vbirding
-bash: vbirding: unbound variable
# 預設情況下，未設定/未宣告 的變數都會是『空的』，不過，若設定 -u 參數，
# 那麼當使用未設定的變數時，就會有問題啦！很多的 shell 都預設啟用 -u 參數。
# 若要取消這個參數，輸入 set +u 即可！

範例三：執行前，顯示該指令內容。
[dmtsai@study ~]$ set -x
++ printf '\033]0;%s@%s:%s\007' dmtsai study '~'    # 這個是在列出提示字元的控制碼！
[dmtsai@study ~]$ echo ${HOME}
+ echo /home/dmtsai
/home/dmtsai
++ printf '\033]0;%s@%s:%s\007' dmtsai study '~'
# 看見否？要輸出的指令都會先被列印到螢幕上喔！前面會多出 + 的符號！

kevin@ubuntu:~/os$ echo ${HOME}
++ __vsc_preexec_only -x
++ '[' 0 = 0 ']'
++ __vsc_in_command_execution=1
++ __vsc_preexec
++ __vsc_initialized=1
++ [[ ! echo ${HOME} =~ ^__vsc_prompt* ]]
++ '[' 0 = 1 ']'
++ __vsc_current_command='echo ${HOME}'
++ __vsc_command_output_start
++ builtin printf '\033]633;C\007'
++ builtin printf '\033]633;E;%s\007' 'echo ${HOME}'
+ echo /home/kevin
/home/kevin
+++ __vsc_preexec_only /home/kevin
+++ '[' 1 = 0 ']'
++ __vsc_prompt_cmd
++ __vsc_status=0
++ __vsc_precmd
++ __vsc_command_complete 0
++ '[' 'echo ${HOME}' = '' ']'
++ builtin printf '\033]633;D;%s\007' 0
++ __vsc_update_cwd
++ builtin printf '\033]633;P;Cwd=%s\007' /home/kevin/os
++ __vsc_current_command=
++ __vsc_update_prompt
++ '[' 1 = 1 ']'
++ [[ \[\]\[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ \[\] == '' ]]
++ [[ \[\]\[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ \[\] != \\\[\]\6\3\3\;\A\\\\]\\\[\\\e\]\0\;\\\u\@\\\h\:\ \\\w\\\a\\\]\$\{\d\e\b\i\a\n\_\c\h\r\o\o\t\:\+\(\$\d\e\b\i\a\n\_\c\h\r\o\o\t\)\}\\\[\\\0\3\3\[\0\1\;\3\2\m\\\]\\\u\@\\\h\\\[\\\0\3\3\[\0\0\m\\\]\:\\\[\\\0\3\3\[\0\1\;\3\4\m\\\]\\\w\\\[\\\0\3\3\[\0\0\m\\\]\\\$\ \\\[\]\6\3\3\;\B\\\\] ]]
++ [[ \[\]> \[\] == '' ]]
++ [[ \[\]> \[\] != \\\[\]\6\3\3\;\F\\\\]\>\ \\\[\]\6\3\3\;\G\\\\] ]]
++ __vsc_in_command_execution=0
```

 **最後，我們將 bash 預設的組合鍵給他彙整如下**：

 <div align=center><img src="/os_note/bash/picture/屏幕截图%202022-11-15%20171236.png"></div>
 <div align=center>bash 預設的組合鍵</div>

 ### 10.4.5 萬用字元與特殊符號

 在 bash 的操作環境中還有一個非常有用的功能，那就是萬用字元 (wildcard) ！ 我們利用 bash 處理資料就更方便了！底下我們列出一些常用的萬用字元喔：
 <div align=center><img src="/os_note/bash/picture/屏幕截图%202022-11-15%20171535.png"></div>

 ```
 [dmtsai@study ~]$ LANG=C              <==由於與編碼有關，先設定語系一下

範例一：找出 /etc/ 底下以 cron 為開頭的檔名
[dmtsai@study ~]$ ll -d /etc/cron*    <==加上 -d 是為了僅顯示目錄而已

kevin@ubuntu:~/os$ ls os*
os_experiment:
boot_experiment  lesson1  ucore_lab

os_note:
bash  compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  vim

範例二：找出 /etc/ 底下檔名『剛好是五個字母』的檔名
[dmtsai@study ~]$ ll -d /etc/?????    <==由於 ? 一定有一個，所以五個 ? 就對了

kevin@ubuntu:~/os$ ls ???????
路线图.jpg

os_note:
bash  compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  vim

範例三：找出 /etc/ 底下檔名含有數字的檔名
[dmtsai@study ~]$ ll -d /etc/*[0-9]*  <==記得中括號左右兩邊均需 *

範例四：找出 /etc/ 底下，檔名開頭非為小寫字母的檔名：
[dmtsai@study ~]$ ll -d /etc/[^a-z]*  <==注意中括號左邊沒有 *

範例五：將範例四找到的檔案複製到 /tmp/upper 中
[dmtsai@study ~]$ mkdir /tmp/upper; cp -a /etc/[^a-z]* /tmp/upper
```

除了萬用字元之外，bash 環境中的特殊符號有哪些呢？底下我們先彙整一下：

<div align=center><img src="/os_note/bash/picture/屏幕截图%202022-11-15%20172124.png"></div>

以上為 bash 環境中常見的特殊符號彙整！**理論上，你的『檔名』盡量不要使用到上述的字元啦**！

## 10.5 資料流重導向

資料流重導向 (redirect) 由字面上的意思來看，好像就是將『資料給他傳導到其他地方去』的樣子？ 沒錯～**資料流重導向就是將某個指令執行後應該要出現在螢幕上的資料**， 給他傳輸到其他的地方，例如檔案或者是裝置 (例如印表機之類的)！這玩意兒在 Linux 的文字模式底下可重要的！ 尤其是如果我們想要將某些資料儲存下來時，就更有用了！

### 10.5.1 什麼是資料流重導向

什麼是資料流重導向啊？這得要由指令的執行結果談起！一般來說，如果你要執行一個指令，通常他會是這樣的：

<div align=center><img src="/os_note/bash/picture/centos7_redirection.jpg"></div>
<div align=center>圖10.5.1、指令執行過程的資料傳輸情況</div>

我們執行一個指令的時候，這個指令可能會由檔案讀入資料，經過處理之後，再將資料輸出到螢幕上。 在上圖當中， standard output 與 standard error output 分別代表『標準輸出 (STDOUT)』與『標準錯誤輸出 (STDERR)』， 這兩個玩意兒預設都是輸出到螢幕上面來的啊！那麼什麼是標準輸出與標準錯誤輸出呢？

#### standard output 與 standard error output

簡單的說，標準輸出指的是『指令執行所回傳的正確的訊息』，而標準錯誤輸出可理解為『 指令執行失敗後，所回傳的錯誤訊息』。舉個簡單例子來說，我們的系統預設有 /etc/crontab 但卻無 /etc/vbirdsay， 此時若下達『 cat /etc/crontab /etc/vbirdsay 』這個指令時，cat 會進行：

**標準輸出：讀取 /etc/crontab 後，將該檔案內容顯示到螢幕上**；
**標準錯誤輸出：因為無法找到 /etc/vbirdsay，因此在螢幕上顯示錯誤訊息**
不管正確或錯誤的資料都是預設輸出到螢幕上，所以螢幕當然是亂亂的！那能不能透過某些機制將這兩股資料分開呢？ 當然可以啊！那就是資料流重導向的功能啊！資料流重導向可以將 standard output (簡稱 stdout) 與 standard error output (簡稱 stderr) 分別傳送到其他的檔案或裝置去，而分別傳送所用的特殊字元則如下所示：

標準輸入　　(stdin) ：代碼為 0 ，使用 < 或 << ；
標準輸出　　(stdout)：代碼為 1 ，使用 > 或 >> ；
標準錯誤輸出(stderr)：代碼為 2 ，使用 2> 或 2>> ；
為了理解 stdout 與 stderr ，我們先來進行一個範例的練習：

```
範例一：觀察你的系統根目錄 (/) 下各目錄的檔名、權限與屬性，並記錄下來
[dmtsai@study ~]$ ll /  <==此時螢幕會顯示出檔名資訊
[dmtsai@study ~]$ ll / > ~/rootfile <==螢幕並無任何資訊
[dmtsai@study ~]$ ll  ~/rootfile <==有個新檔被建立了！
-rw-rw-r--. 1 dmtsai dmtsai 1078 Jul  9 18:51 /home/dmtsai/rootfile
```

怪了！螢幕怎麼會完全沒有資料呢？這是因為原本『 ll / 』所顯示的資料已經被重新導向到 ~/rootfile 檔案中了！ 那個 ~/rootfile 的檔名可以隨便你取。如果你下達『 cat ~/rootfile 』那就可以看到原本應該在螢幕上面的資料囉。 如果我再次下達：『 ll /home > ~/rootfile 』後，那個 ~/rootfile 檔案的內容變成什麼？ 他將變成『僅有 ll /home 的資料』而已！咦！原本的『 ll / 』資料就不見了嗎？是的！因為該檔案的建立方式是：

該檔案 (本例中是 ~/rootfile) 若不存在，系統會自動的將他建立起來，但是
當這個檔案存在的時候，那麼系統就會先將這個檔案內容清空，然後再將資料寫入！
也就是若以 > 輸出到一個已存在的檔案中，那個檔案就會被覆蓋掉囉！
那如果我想要將資料累加而不想要將舊的資料刪除，那該如何是好？利用兩個大於的符號 (>>) 就好啦！以上面的範例來說，你應該要改成『 ll / >> ~/rootfile 』即可。 如此一來，當 (1) ~/rootfile 不存在時系統會主動建立這個檔案；(2)若該檔案已存在， 則資料會在該檔案的最下方累加進去！
 
上面談到的是 standard output 的正確資料，那如果是 standard error output 的錯誤資料呢？那就透過 2> 及 2>> 囉！同樣是覆蓋 (2>) 與累加 (2>>) 的特性！我們在剛剛才談到 stdout 代碼是 1 而 stderr 代碼是 2 ， 所以這個 2> 是很容易理解的，而如果僅存在 > 時，則代表預設的代碼 1 囉！也就是說：

1> ：以覆蓋的方法將『正確的資料』輸出到指定的檔案或裝置上；
1>>：以累加的方法將『正確的資料』輸出到指定的檔案或裝置上；
2> ：以覆蓋的方法將『錯誤的資料』輸出到指定的檔案或裝置上；
2>>：以累加的方法將『錯誤的資料』輸出到指定的檔案或裝置上；

要注意喔，『 1>> 』以及『 2>> 』中間是沒有空格的！OK！有些概念之後讓我們繼續聊一聊這傢伙怎麼應用吧！ 當你以一般身份執行 find 這個指令的時候，由於權限的問題可能會產生一些錯誤資訊。例如執行『 find / -name testing 』時，可能會產生類似『 find: /root: Permission denied 』之類的訊息。 例如底下這個範例：
```
範例二：利用一般身份帳號搜尋 /home 底下是否有名為 .bashrc 的檔案存在
[dmtsai@study ~]$ find /home -name .bashrc <==身份是 dmtsai 喔！
find: '/home/arod': Permission denied    <== Standard error output
find: '/home/alex': Permission denied    <== Standard error output
/home/dmtsai/.bashrc                     <== Standard output

kevin@ubuntu:~/os$ find /home -name .bashrc
/home/kevin/.bashrc
find: ‘/home/kevin/.dbus’: Permission denied
find: ‘/home/kevin/.gvfs’: Permission denied
find: ‘/home/kevin/.cache/dconf’: Permission denied
find: ‘/home/kevin/.cache/doc’: Permission denied
find: ‘/home/kevin/.config/enchant’: Permission denied
```
由於 /home 底下還有我們之前建立的帳號存在，那些帳號的家目錄你當然不能進入啊！所以就會有錯誤及正確資料了。 好了，那麼假如我想要將資料輸出到 list 這個檔案中呢？執行『 find /home -name .bashrc > list 』 會有什麼結果？呵呵，你會發現 list 裡面存了剛剛那個『正確』的輸出資料， 至於螢幕上還是會有錯誤的訊息出現呢！傷腦筋！如果想要將正確的與錯誤的資料分別存入不同的檔案中需要怎麼做？
```
範例三：承範例二，將 stdout 與 stderr 分存到不同的檔案去
[dmtsai@study ~]$ find /home -name .bashrc > list_right 2> list_error

kevin@ubuntu:~/os$ find /home -name .bashrc > list_right 2> list_error
kevin@ubuntu:~/os$ ls
'\'   list_error   list_right   os_experiment   os_note   路线图.jpg
kevin@ubuntu:~/os$ file list_error 
list_error: UTF-8 Unicode text
kevin@ubuntu:~/os$ cat list_error 
find: ‘/home/kevin/.dbus’: Permission denied
find: ‘/home/kevin/.gvfs’: Permission denied
find: ‘/home/kevin/.cache/dconf’: Permission denied
find: ‘/home/kevin/.cache/doc’: Permission denied
find: ‘/home/kevin/.config/enchant’: Permission denied
kevin@ubuntu:~/os$ cat list_right 
/home/kevin/.bashrc
```

注意喔，此時『螢幕上不會出現任何訊息』！因為剛剛執行的結果中，有 Permission 的那幾行錯誤資訊都會跑到 list_error 這個檔案中，至於正確的輸出資料則會存到 list_right 這個檔案中囉！這樣可以瞭解了嗎？ 如果有點混亂的話，去休息一下再回來看看吧！

#### /dev/null 垃圾桶黑洞裝置與特殊寫法
想像一下，如果我知道錯誤訊息會發生，所以要將錯誤訊息忽略掉而不顯示或儲存呢？ 這個時候黑洞裝置 /dev/null 就很重要了！這個 /dev/null 可以吃掉任何導向這個裝置的資訊喔！將上述的範例修訂一下：

```
範例四：承範例三，將錯誤的資料丟棄，螢幕上顯示正確的資料
[dmtsai@study ~]$ find /home -name .bashrc 2> /dev/null
/home/dmtsai/.bashrc  <==只有 stdout 會顯示到螢幕上， stderr 被丟棄了
```

再想像一下，如果我要將正確與錯誤資料通通寫入同一個檔案去呢？這個時候就得要使用特殊的寫法了！ 我們同樣用底下的案例來說明：

```
範例五：將指令的資料全部寫入名為 list 的檔案中
[dmtsai@study ~]$ find /home -name .bashrc > list 2> list  <==錯誤
[dmtsai@study ~]$ find /home -name .bashrc > list 2>&1     <==正確
[dmtsai@study ~]$ find /home -name .bashrc &> list         <==正確
```

上述表格第一行錯誤的原因是，由於兩股資料同時寫入一個檔案，又沒有使用特殊的語法， 此時兩股資料可能會交叉寫入該檔案內，造成次序的錯亂。所以雖然最終 list 檔案還是會產生，但是裡面的資料排列就會怪怪的，而不是原本螢幕上的輸出排序。 至於寫入同一個檔案的特殊語法如上表所示，你可以使用 2>&1 也可以使用 &> ！ 一般來說，鳥哥比較習慣使用 2>&1 的語法啦！

#### standard input ： < 與 <<

瞭解了 stderr 與 stdout 後，那麼那個 < 又是什麼呀？呵呵！以最簡單的說法來說， 那就是『將原本需要由鍵盤輸入的資料，改由檔案內容來取代』的意思。 我們先由底下的 cat 指令操作來瞭解一下什麼叫做『鍵盤輸入』吧！

```
範例六：利用 cat 指令來建立一個檔案的簡單流程
[dmtsai@study ~]$ cat > catfile
testing
cat file test
<==這裡按下 [ctrl]+d 來離開

[dmtsai@study ~]$ cat catfile
testing
cat file test
```

由於加入 > 在 cat 後，所以那個 catfile 會被主動的建立，而內容就是剛剛鍵盤上面輸入的那兩行資料了。 唔！那我能不能用純文字檔取代鍵盤的輸入，也就是說，用某個檔案的內容來取代鍵盤的敲擊呢？ 可以的！如下所示：

```
範例七：用 stdin 取代鍵盤的輸入以建立新檔案的簡單流程
[dmtsai@study ~]$ cat > catfile < ~/.bashrc
[dmtsai@study ~]$ ll catfile ~/.bashrc
-rw-r--r--. 1 dmtsai dmtsai 231 Mar  6 06:06 /home/dmtsai/.bashrc
-rw-rw-r--. 1 dmtsai dmtsai 231 Jul  9 18:58 catfile
# 注意看，這兩個檔案的大小會一模一樣！幾乎像是使用 cp 來複製一般！
```

這東西非常的有幫助！尤其是用在類似 mail 這種指令的使用上。 理解 < 之後，再來則是怪可怕一把的 << 這個連續兩個小於的符號了。 他代表的是『結束的輸入字元』的意思！舉例來講：『我要用 cat 直接將輸入的訊息輸出到 catfile 中， 且當由鍵盤輸入 eof 時，該次輸入就結束』，那我可以這樣做：

```
[dmtsai@study ~]$ cat > catfile << "eof"
> This is a test.
> OK now stop
> eof  <==輸入這關鍵字，立刻就結束而不需要輸入 [ctrl]+d

[dmtsai@study ~]$ cat catfile
This is a test.
OK now stop     <==只有這兩行，不會存在關鍵字那一行！
```

看到了嗎？利用 << 右側的控制字元，我們可以終止一次輸入， 而不必輸入 [ctrl]+d 來結束哩！這對程式寫作很有幫助喔！好了，那麼為何要使用命令輸出重導向呢？我們來說一說吧！

螢幕輸出的資訊很重要，而且我們需要將他存下來的時候；
背景執行中的程式，不希望他干擾螢幕正常的輸出結果時；
一些系統的例行命令 (例如寫在 /etc/crontab 中的檔案) 的執行結果，希望他可以存下來時；
一些執行命令的可能已知錯誤訊息時，想以『 2> /dev/null 』將他丟掉時；
錯誤訊息與正確訊息需要分別輸出時。
當然還有很多的功能的，最簡單的就是網友們常常問到的：『為何我的 root 都會收到系統 crontab 寄來的錯誤訊息呢』這個咚咚是常見的錯誤， 而如果我們已經知道這個錯誤訊息是可以忽略的時候，嗯！『 2> errorfile 』這個功能就很重要了吧！ 瞭解了嗎？

### 10.5.2 命令執行的判斷依據： ; , &&, ||

在某些情況下，很多指令我想要一次輸入去執行，而不想要分次執行時，該如何是好？基本上你有兩個選擇， 一個是透過第十二章要介紹的 shell script 撰寫腳本去執行，一種則是透過底下的介紹來一次輸入多重指令喔！

#### cmd ; cmd (不考慮指令相關性的連續指令下達)

在某些時候，我們希望可以一次執行多個指令，例如在關機的時候我希望可以先執行兩次 sync 同步化寫入磁碟後才 shutdown 電腦，那麼可以怎麼作呢？這樣做呀：
```
kevin@ubuntu:~/os$ ls ;cd os_note/; ls; cd ..
'\'   os_experiment   os_note   路线图.jpg
bash  compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  vim
```
在指令與指令中間利用分號;來隔開，這樣一來，分號前的指令執行完後就會立刻接著執行後面的指令了。 這真是方便啊～再來，換個角度來想，萬一我想要在某個目錄底下建立一個檔案，也就是說，如果該目錄存在的話， 那我才建立這個檔案，如果不存在，那就算了。也就是說這兩個指令彼此之間是有相關性的， 前一個指令是否成功的執行與後一個指令是否要執行有關！那就得動用到 && 或 || 囉

#### $? (指令回傳值) 與 && 或 ||
如同上面談到的，兩個指令之間有相依性，而這個相依性主要判斷的地方就在於前一個指令執行的結果是否正確。 還記得本章之前我們曾介紹過指令回傳值吧！嘿嘿！沒錯，您真聰明！就是透過這個回傳值啦！ 再複習一次『若前一個指令執行的結果為正確，在 Linux 底下會回傳一個 $? = 0 的值』。 那麼我們怎麼透過這個回傳值來判斷後續的指令是否要執行呢？這就得要藉由『 && 』及『 || 』的幫忙了！ 注意喔，兩個 & 之間是沒有空格的！那個 | 則是 [Shift]+[\] 的按鍵結果。

<div align=center><img src="/os_note/bash/picture/屏幕截图%202022-11-15%20191834.png"></div>

上述的 cmd1 及 cmd2 都是指令。好了，回到我們剛剛假想的情況，就是想要： (1)先判斷一個目錄是否存在； (2)若存在才在該目錄底下建立一個檔案。由於我們尚未介紹如何判斷式 (test) 的使用，在這裡我們使用 ls 以及回傳值來判斷目錄是否存在啦！ 讓我們進行底下這個練習看看：
```
kevin@ubuntu:~/os$ ls os_note/test && touch os_note/test/testfile
ls: cannot access 'os_note/test': No such file or directory
kevin@ubuntu:~/os$ ls os_note/test || mkdir -p os_note/test ; ls os_note/
ls: cannot access 'os_note/test': No such file or directory
bash  compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test  vim
```

由於Linux 底下的指令都是由左往右執行的，所以範例三有幾種結果我們來分析一下：

## 10.6 管線命令 (pipe)

就如同前面所說的， bash 命令執行的時候有輸出的資料會出現！ 那麼如果這群資料必需要經過幾道手續之後才能得到我們所想要的格式，應該如何來設定？ 這就牽涉到管線命令的問題了 (pipe) ，管線命令使用的是『 | 』這個界定符號！ 另外，管線命令與『連續下達命令』是不一樣的呦！ 這點底下我們會再說明。底下我們先舉一個例子來說明一下簡單的管線命令。

假設我們想要知道 /etc/ 底下有多少檔案，那麼可以利用 ls /etc 來查閱，不過， 因為 /etc 底下的檔案太多，導致一口氣就將螢幕塞滿了～不知道前面輸出的內容是啥？此時，我們可以透過 less 指令的協助，利用：
```
kevin@ubuntu:~/os$ ls -al /etc | less
```
如此一來，使用 ls 指令輸出後的內容，就能夠被 less 讀取，並且利用 less 的功能，我們就能夠前後翻動相關的資訊了！很方便是吧？我們就來瞭解一下這個管線命令『 | 』的用途吧！ 其實這個管線命令『 | 』僅能處理經由前面一個指令傳來的正確資訊，也就是 standard output 的資訊，對於 stdandard error 並沒有直接處理的能力。那麼整體的管線命令可以使用下圖表示：

<div align=center><img src="/os_note/bash/picture/0320bash_3.png"></div>
<div align=center>圖10.6.1、管線命令的處理示意圖</div>

在每個管線後面接的第一個資料必定是『指令』喔！而且這個指令必須要能夠接受 standard input 的資料才行，這樣的指令才可以是為『管線命令』，例如 less, more, head, tail 等都是可以接受 standard input 的管線命令啦。至於例如 ls, cp, mv 等就不是管線命令了！因為 ls, cp, mv 並不會接受來自 stdin 的資料。 也就是說，管線命令主要有兩個比較需要注意的地方：

管線命令僅會處理 standard output，對於 standard error output 會予以忽略
管線命令必須要能夠接受來自前一個指令的資料成為 standard input 繼續處理才行。

多說無益，讓我們來玩一些管線命令吧！底下的咚咚對系統管理非常有幫助喔！

### 10.6.1 擷取命令： cut, grep

什麼是擷取命令啊？說穿了，就是將一段資料經過分析後，取出我們所想要的。或者是經由分析關鍵字，取得我們所想要的那一行！ 不過，要注意的是，一般來說，擷取訊息通常是針對『一行一行』來分析的， 並不是整篇訊息分析的喔～底下我們介紹兩個很常用的訊息擷取命令：

#### cut

cut 不就是『切』嗎？沒錯啦！這個指令可以將一段訊息的某一段給他『切』出來～ 處理的訊息是以『行』為單位喔！底下我們就來談一談：

```
[dmtsai@study ~]$ cut -d'分隔字元' -f fields <==用於有特定分隔字元
[dmtsai@study ~]$ cut -c 字元區間            <==用於排列整齊的訊息
選項與參數：
-d  ：後面接分隔字元。與 -f 一起使用；
-f  ：依據 -d 的分隔字元將一段訊息分割成為數段，用 -f 取出第幾段的意思；
-c  ：以字元 (characters) 的單位取出固定字元區間；

範例一：將 PATH 變數取出，我要找出第五個路徑。
[dmtsai@study ~]$ echo ${PATH}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
#      1      |    2   |       3       |    4    |           5           |      6         |
kevin@ubuntu:~/os$ echo ${PATH}
/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/8fa188b2b301d36553cbc9ce1b0a146ccb93351f/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

[dmtsai@study ~]$ echo ${PATH} | cut -d ':' -f 5
# 如同上面的數字顯示，我們是以『 : 』作為分隔，因此會出現 /home/dmtsai/.local/bin
kevin@ubuntu:~/os$ echo ${PATH} | cut -d ':' -f 5
/home/kevin/qemu-5.0.0

# 那麼如果想要列出第 3 與第 5 呢？，就是這樣：
[dmtsai@study ~]$ echo ${PATH} | cut -d ':' -f 3,5
kevin@ubuntu:~/os$ echo ${PATH} | cut -d ':' -f 4,5
/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0

範例二：將 export 輸出的訊息，取得第 12 字元以後的所有字串
[dmtsai@study ~]$ export
declare -x HISTCONTROL="ignoredups"
declare -x HISTSIZE="1000"
declare -x HOME="/home/dmtsai"
declare -x HOSTNAME="study.centos.vbird"
.....(其他省略).....
# 注意看，每個資料都是排列整齊的輸出！如果我們不想要『 declare -x 』時，就得這麼做：

[dmtsai@study ~]$ export | cut -c 12-
HISTCONTROL="ignoredups"
HISTSIZE="1000"
HOME="/home/dmtsai"
HOSTNAME="study.centos.vbird"
.....(其他省略).....
# 知道怎麼回事了吧？用 -c 可以處理比較具有格式的輸出資料！
# 我們還可以指定某個範圍的值，例如第 12-20 的字元，就是 cut -c 12-20 等等！

範例三：用 last 將顯示的登入者的資訊中，僅留下使用者大名
[dmtsai@study ~]$ last
root   pts/1    192.168.201.101  Sat Feb  7 12:35   still logged in
root   pts/1    192.168.201.101  Fri Feb  6 12:13 - 18:46  (06:33)
root   pts/1    192.168.201.254  Thu Feb  5 22:37 - 23:53  (01:16)
# last 可以輸出『帳號/終端機/來源/日期時間』的資料，並且是排列整齊的

[dmtsai@study ~]$ last | cut -d ' ' -f 1
# 由輸出的結果我們可以發現第一個空白分隔的欄位代表帳號，所以使用如上指令：
# 但是因為 root   pts/1 之間空格有好幾個，並非僅有一個，所以，如果要找出 
# pts/1 其實不能以 cut -d ' ' -f 1,2 喔！輸出的結果會不是我們想要的。
```