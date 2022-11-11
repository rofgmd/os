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

