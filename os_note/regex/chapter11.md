# 第十一章、正規表示法與文件格式化處理

## 11.1 開始之前：什麼是正規表示法

約略瞭解了 Linux 的基本指令 (BASH) 並且熟悉了 vim 之後，相信你對於敲擊鍵盤的打字與指令下達比較不陌生了吧？ 接下來，底下要開始介紹一個很重要的觀念，那就是所謂的『正規表示法 (Regular Expression)』囉！

#### 什麼是正規表示法

任何一個有經驗的系統管理員，都會告訴你：『**正規表示法真是挺重要的**！』 為什麼很重要呢？因為日常生活就使用的到啊！舉個例子來說， 在你日常使用 vim 作文書處理或程式撰寫時使用到的『搜尋/取代』等等的功能， 這些舉動要作的漂亮，就得要配合正規表示法來處理囉！

簡單的說，**正規表示法就是處理字串的   方法，他是以行為單位來進行字串的處理行為， 正規表示法透過一些特殊符號的輔助，可以讓使用者輕易的達到『搜尋/刪除/取代』某特定字串的處理程序**！

舉例來說，我只想找到 VBird(前面兩個大寫字元) 或 Vbird(僅有一個大寫字元) 這個字樣，但是不要其他的字串 (例如 VBIRD, vbird 等不需要)，該如何辦理？如果在沒有正規表示法的環境中(例如 MS word)，你或許就得要使用忽略大小寫的辦法， 或者是分別以 VBird 及 Vbird 搜尋兩遍。但是，忽略大小寫可能會搜尋到 VBIRD/vbird/VbIrD 等等的不需要的字串而造成困擾。

再舉個系統常見的例子好了，假設妳發現系統在開機的時候，老是會出現一個關於 mail 程式的錯誤， 而開機過程的相關程序都是在 /lib/systemd/system/ 底下，也就是說，在該目錄底下的某個檔案內具有 mail 這個關鍵字，你想要將該檔案捉出來進行查詢修改的動作。此時你怎麼找出來含有這個關鍵字的檔案？ 你當然可以一個檔案一個檔案的開啟，然後去搜尋 mail 這個關鍵字，只是.....該目錄底下的檔案可能不止 100 個說～ 如果瞭解正規表示法的相關技巧，那麼只要一行指令就找出來啦：『grep 'mail' /lib/systemd/system/*』 那個 grep 就是支援正規表示法的工具程式之一！如何～很簡單吧！

談到這裡就得要進一步說明了，**正規表示法基本上是一種『表示法』， 只要工具程式支援這種表示法，那麼該工具程式就可以用來作為正規表示法的字串處理之用**。 例如 vi, grep, awk ,sed 等等工具，因為她們有支援正規表示法， 所以，這些工具就可以使用正規表示法的特殊字元來進行字串的處理。但例如 cp, ls 等指令並未支援正規表示法， 所以就只能使用 bash 自己本身的萬用字元而已。

#### 正規表示法對於系統管理員的用途

那麼為何我需要學習正規表示法呢？對於一般使用者來說，由於使用到正規表示法的機會可能不怎麼多， 因此感受不到他的魅力，不過，對於身為系統管理員的你來說，正規表示法則是一個『不可不學的好東西！』 怎麼說呢？由於系統如果在繁忙的情況之下，每天產生的訊息資訊會多到你無法想像的地步， 而我們也都知道，系統的『錯誤訊息登錄檔案 (第十八章)』 的內容記載了系統產生的所有訊息，當然，這包含你的系統是否被『入侵』的記錄資料。

但是系統的資料量太大了，要身為系統管理員的你每天去看這麼多的訊息資料， 從千百行的資料裡面找出一行有問題的訊息，呵呵～光是用肉眼去看，想不瘋掉都很難！ 這個時候，我們就可以透過『正規表示法』的功能，將這些登錄的資訊進行處理， 僅取出『有問題』的資訊來進行分析，哈哈！如此一來，你的系統管理工作將會 『快樂得不得了』啊！當然，正規表示法的優點還不止於此，等你有一定程度的瞭解之後，你會愛上他喔！

#### 正規表示法的廣泛用途

正規表示法除了可以讓系統管理員管理主機更為便利之外，事實上，由於正規表示法強大的字串處理能力， 目前一堆軟體都支援正規表示法呢！最常見的就是『郵件伺服器』啦！

如果你留意網際網路上的消息，那麼應該不難發現，目前造成網路大塞車的主因之一就是『垃圾/廣告信件』了， 而如果我們可以在伺服器端，就將這些問題郵件剔除的話，用戶端就會減少很多不必要的頻寬耗損了。 那麼如何剔除廣告信件呢？由於廣告信件幾乎都有一定的標題或者是內容，因此， 只要每次有來信時，都先將來信的標題與內容進行特殊字串的比對，發現有不良信件就予以剔除！ 嘿！這個工作怎麼達到啊？就使用正規表示法啊！目前兩大郵件伺服器軟體 sendmail 與 postfix 以及支援郵件伺服器的相關分析軟體，都支援正規表示法的比對功能！

當然還不止於此啦，很多的伺服器軟體都支援正規表示法呢！當然， 雖然各家軟體都支援他，不過，這些『字串』的比對還是需要系統管理員來加入比對規則的， 所以啦！身為系統管理員的你，為了自身的工作以及用戶端的需求， 正規表示法實在是很需要也很值得學習的一項工具呢！

#### 正規表示法與 Shell 在 Linux 當中的角色定位

說實在的，我們在學數學的時候，一個很重要、但是粉難的東西是一定要『背』的， 那就是九九乘法表，背成功了之後，未來在數學應用的路途上，真是一帆風順啊！ 這個九九乘法表我們在小學的時候幾乎背了一整年才背下來，並不是這麼好背的呢！ 但他卻是基礎當中的基礎！你現在一定受惠相當的多呢 ^_^！

而我們談到的這個正規表示法，與前一章的 BASH 就有點像是數學的九九乘法表一樣，是 Linux 基礎當中的基礎，雖然也是最難的部分， 不過，如果學成了之後，一定是『大大的有幫助』的！這就好像是金庸小說裡面的學武難關：任督二脈！ 打通任督二脈之後，武功立刻成倍成長！所以啦， 不論是對於系統的認識與系統的管理部分，他都有很棒的輔助啊！請好好的學習這個基礎吧！ ^_^

#### 延伸的正規表示法

唔！正規表示法還有分喔？沒錯喔！正規表示法的字串表示方式依照不同的嚴謹度而分為： 基礎正規表示法與延伸正規表示法。延伸型正規表示法除了簡單的一組字串處理之外，還可以作群組的字串處理， 例如進行搜尋 VBird 或 netman 或 lman 的搜尋，注意，是『或(or)』而不是『和(and)』的處理， 此時就需要延伸正規表示法的幫助啦！藉由特殊的『 ( 』與『 | 』等字元的協助， 就能夠達到這樣的目的！不過，我們在這裡主力僅是介紹最基礎的基礎正規表示法而已啦！好啦！清清腦門，咱們用功去囉！

## 11.2 基礎正規表示法

既然正規表示法是處理字串的一種表示方式，那麼對字元排序有影響的語系資料就會對正規表示法的結果有影響！ 此外，正規表示法也需要支援工具程式來輔助才行！所以，我們這裡就先介紹一個最簡單的字串擷取功能的工具程式，那就是 grep 囉！ 前一章已經介紹過 grep 的相關選項與參數，本章著重在較進階的 grep 選項說明囉！ 介紹完 grep 的功能之後，就進入正規表示法的特殊字符的處理能力了。

### 11.2.1 語系對正規表示法的影響

為什麼語系的資料會影響到正規表示法的輸出結果呢？我們在第零章計算機概論的文字編碼系統裡面談到，檔案其實記錄的僅有 0 與 1，我們看到的字元文字與數字都是透過編碼表轉換來的。由於不同語系的編碼資料並不相同，所以就會造成資料擷取結果的差異了。 舉例來說，在英文大小寫的編碼順序中，zh_TW.big5 及 C 這兩種語系的輸出結果分別如下：

LANG=C     時：0 1 2 3 4 ... A B C D ... Z a b c d ...z
LANG=zh_TW 時：0 1 2 3 4 ... a A b B c C d D ... z Z

上面的順序是編碼的順序，我們可以很清楚的發現這兩種語系明顯就是不一樣！如果你想要擷取大寫字元而使用 [A-Z] 時， 會發現 LANG=C 確實可以僅捉到大寫字元 (因為是連續的) ，但是如果 LANG=zh_TW.big5 時，就會發現到， 連同小寫的 b-z 也會被擷取出來！因為就編碼的順序來看， big5 語系可以擷取到『 A b B c C ... z Z 』這一堆字元哩！ 所以，使用正規表示法時，需要特別留意當時環境的語系為何， 否則可能會發現與別人不相同的擷取結果喔！

由於一般我們在練習正規表示法時，使用的是相容於 POSIX 的標準，因此就使用『 C 』這個語系(註1)！ 因此，底下的很多練習都是使用『 LANG=C 』這個語系資料來進行的喔！ 另外，為了要避免這樣編碼所造成的英文與數字的擷取問題，因此有些特殊的符號我們得要瞭解一下的！ 這些符號主要有底下這些意義：(註1)

<div align=center><img src="/os_note/regex/images/2022-11-17%20171912.png"></div>

尤其上表中的[:alnum:], [:alpha:], [:upper:], [:lower:], [:digit:] 這幾個一定要知道代表什麼意思，因為他要比 a-z 或 A-Z 的用途要確定的很！好了，底下就讓我們開始來玩玩進階版的 grep 吧！

### 11.2.2 grep 的一些進階選項

我們在第十章 BASH 裡面的 grep 談論過一些基礎用法， 但其實 grep 還有不少的進階用法喔！底下我們僅列出較進階的 grep 選項與參數給大家參考， 基礎的 grep 用法請參考前一章的說明囉！

```bash 
dmtsai@study ~]$ grep [-A] [-B] [--color=auto] '搜尋字串' filename
選項與參數：
-A ：後面可加數字，為 after 的意思，除了列出該行外，後續的 n 行也列出來；
-B ：後面可加數字，為 befer 的意思，除了列出該行外，前面的 n 行也列出來；
--color=auto 可將正確的那個擷取資料列出顏色

範例一：用 dmesg 列出核心訊息，再以 grep 找出內含 qxl 那行
[dmtsai@study ~]$ dmesg | grep 'qxl'
[    0.522749] [drm] qxl: 16M of VRAM memory size
[    0.522750] [drm] qxl: 63M of IO pages memory ready (VRAM domain)
[    0.522750] [drm] qxl: 32M of Surface memory size
[    0.650714] fbcon: qxldrmfb (fb0) is primary device
[    0.668487] qxl 0000:00:02.0: fb0: qxldrmfb frame buffer device
# dmesg 可列出核心產生的訊息！包括硬體偵測的流程也會顯示出來。
# 鳥哥使用的顯卡是 QXL 這個虛擬卡，透過 grep 來 qxl 的相關資訊，可發現如上資訊。

範例二：承上題，要將捉到的關鍵字顯色，且加上行號來表示：
[dmtsai@study ~]$ dmesg | grep -n --color=auto 'qxl'
515:[    0.522749] [drm] qxl: 16M of VRAM memory size
516:[    0.522750] [drm] qxl: 63M of IO pages memory ready (VRAM domain)
517:[    0.522750] [drm] qxl: 32M of Surface memory size
529:[    0.650714] fbcon: qxldrmfb (fb0) is primary device
539:[    0.668487] qxl 0000:00:02.0: fb0: qxldrmfb frame buffer device
# 除了 qxl 會有特殊顏色來表示之外，最前面還有行號喔！其實顏色顯示已經是預設在 alias 當中了！

範例三：承上題，在關鍵字所在行的前兩行與後三行也一起捉出來顯示
[dmtsai@study ~]$ dmesg | grep -n -A3 -B2 --color=auto 'qxl'
# 你會發現關鍵字之前與之後的數行也被顯示出來！這樣可以讓你將關鍵字前後資料捉出來進行分析啦！
```

grep 是一個很常見也很常用的指令，他最重要的功能就是進行字串資料的比對，然後將符合使用者需求的字串列印出來。 需要說明的是『grep 在資料中查尋一個字串時，是以 "整行" 為單位來進行資料的擷取的！』也就是說，假如一個檔案內有 10 行，其中有兩行具有你所搜尋的字串，則將那兩行顯示在螢幕上，其他的就丟棄了！

在 CentOS 7 當中，預設已經將 --color=auto 加入在 alias 當中了！使用者就可以直接使用有關鍵字顯色的 grep 囉！非常方便！

### 11.2.3 基礎正規表示法練習

要瞭解正規表示法最簡單的方法就是由實際練習去感受啦！所以在彙整正規表示法特殊符號前， 我們先以底下這個檔案的內容來進行正規表示法的理解吧！先說明一下，底下的練習大前提是：

語系已經使用『 export LANG=C; export LC_ALL=C 』的設定值；
grep 已經使用 alias 設定成為『 grep --color=auto 』
至於本章的練習用檔案請由底下的連結來下載。需要特別注意的是，底下這個檔案是鳥哥在 MS Windows 系統下編輯的， 並且已經特殊處理過，因此，他雖然是純文字檔，但是內含一些 Windows 系統下的軟體常常自行加入的一些特殊字元，例如斷行字元 (^M) 就是一例！ 所以，你可以直接將底下的文字以 vi 儲存成 regular_express.txt 這個檔案， 不過，還是比較建議直接點底下的連結：

[http://linux.vbird.org/linux_basic/0330regularex/regular_express.txt]
如果你的 Linux 可以直接連上 Internet 的話，那麼使用如下的指令來捉取即可：

wget [http://linux.vbird.org/linux_basic/0330regularex/regular_express.txt]
至於這個檔案的內容如下：

```bash
[dmtsai@study ~]$ vi regular_express.txt
"Open Source" is a good mechanism to develop programs.
apple is my favorite food.
Football game is not use feet only.
this dress doesn't fit me.
However, this dress is about $ 3183 dollars.^M
GNU is free air not free beer.^M
Her hair is very beauty.^M
I can't finish the test.^M
Oh! The soup taste good.^M
motorcycle is cheap than car.
This window is clear.
the symbol '*' is represented as start.
Oh!     My god!
The gd software is a library for drafting programs.^M
You are the best is mean you are the no. 1.
The world <Happy> is the same with "glad".
I like dog.
google is the best tools for search keyword.
goooooogle yes!
go! go! Let's go.
# I am VBird

```

這檔案共有 22 行，最底下一行為空白行！現在開始我們一個案例一個案例的來介紹吧！

#### 例題一、搜尋特定字串

搜尋特定字串很簡單吧？假設我們要從剛剛的檔案當中取得 the 這個特定字串，最簡單的方式就是這樣：

```bash
[dmtsai@study ~]$ grep -n 'the' regular_express.txt
8:I can't finish the test.
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
18:google is the best tools for search keyword.

kevin@Kevin-Laptop:~/os$ grep -n 'the' ./os_note/regex/regular_express.txt 
8:I can't finish the test.^M
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
18:google is the best tools for search keyword.
```

那如果想要『反向選擇』呢？也就是說，當該行沒有 'the' 這個字串時才顯示在螢幕上，那就直接使用：

```bash
kevin@Kevin-Laptop:~/os$ grep -vn 'the' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
4:this dress doesn't fit me.
5:However, this dress is about $ 3183 dollars.^M
6:GNU is free air not free beer.^M
7:Her hair is very beauty.^M
9:Oh! The soup taste good.^M
10:motorcycle is cheap than car.
11:This window is clear.
13:Oh!     My god!
14:The gd software is a library for drafting programs.^M
17:I like dog.
19:goooooogle yes!
20:go! go! Let's go.
21:# I am VBird
22:
23:
```

你會發現，螢幕上出現的行列為除了 8,12,15,16,18 五行之外的其他行列！ 接下來，如果你想要取得不論大小寫的 the 這個字串，則：

```bash
kevin@Kevin-Laptop:~/os$ grep -in 'the' ./os_note/regex/regular_express.txt 
8:I can't finish the test.^M
9:Oh! The soup taste good.^M
12:the symbol '*' is represented as start.
14:The gd software is a library for drafting programs.^M
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
18:google is the best tools for search keyword.
```

除了多兩行 (9, 14行) 之外，第 16 行也多了一個 The 的關鍵字被擷取到喔！

#### 例題二、利用中括號 [] 來搜尋集合字元

如果我想要搜尋 test 或 taste 這兩個單字時，可以發現到，其實她們有共通的 't?st' 存在～這個時候，我可以這樣來搜尋：

```bash
[dmtsai@study ~]$ grep -n 't[ae]st' regular_express.txt
8:I can't finish the test.
9:Oh! The soup taste good.
```