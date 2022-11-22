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
瞭解了吧？其實 [] 裡面不論有幾個字元，他都僅代表某『一個』字元， 所以，上面的例子說明了，我需要的字串是『tast』或『test』兩個字串而已！ 而如果想要搜尋到有 oo 的字元時，則使用
```bash
[dmtsai@study ~]$ grep -n 'oo' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.
18:google is the best tools for search keyword.
19:goooooogle yes!
```
但是，如果我不想要 oo 前面有 g 的話呢？此時，可以利用在集合字元的反向選擇 [^] 來達成：
```bash
[dmtsai@study ~]$ grep -n '[^g]oo' regular_express.txt
2:apple is my favorite food.
3:Football game is not use feet only.
18:google is the best tools for search keyword.
19:goooooogle yes!
```
意思就是說，我需要的是 oo ，但是 oo 前面不能是 g 就是了！仔細比較上面兩個表格，妳會發現，第 1,9 行不見了，因為 oo 前面出現了 g 所致！第 2,3 行沒有疑問，因為 foo 與 Foo 均可被接受！但是第 18 行明明有 google 的 goo 啊～別忘記了，因為該行後面出現了 tool 的 too 啊！所以該行也被列出來～ 也就是說， 18 行裡面雖然出現了我們所不要的項目 (goo) 但是由於有需要的項目 (too) ， 因此，是符合字串搜尋的喔！

至於第 19 行，同樣的，因為 goooooogle 裡面的 oo 前面可能是 o ，例如： go(ooo)oogle ，所以，這一行也是符合需求的！

再來，假設我 oo 前面不想要有小寫字元，所以，我可以這樣寫 [^abcd....z]oo ， 但是這樣似乎不怎麼方便，由於小寫字元的 ASCII 上編碼的順序是連續的， 因此，我們可以將之簡化為底下這樣：
```bash
[dmtsai@study ~]$ grep -n '[^a-z]oo' regular_express.txt
3:Football game is not use feet only.
```
也就是說，當我們在一組集合字元中，如果該字元組是連續的，例如大寫英文/小寫英文/數字等等， 就可以使用[a-z],[A-Z],[0-9]等方式來書寫，那麼如果我們的要求字串是數字與英文呢？ 呵呵！就將他全部寫在一起，變成：[a-zA-Z0-9]。例如，我們要取得有數字的那一行，就這樣：
```bash
[dmtsai@study ~]$ grep -n '[0-9]' regular_express.txt
5:However, this dress is about $ 3183 dollars.
15:You are the best is mean you are the no. 1.
```
但由於考慮到語系對於編碼順序的影響，因此除了連續編碼使用減號『 - 』之外， 你也可以使用如下的方法來取得前面兩個測試的結果：
```bash
[dmtsai@study ~]$ grep -n '[^[:lower:]]oo' regular_express.txt
# 那個 [:lower:] 代表的就是 a-z 的意思！請參考前兩小節的說明表格

[dmtsai@study ~]$ grep -n '[[:digit:]]' regular_express.txt
```
啥？上頭在寫啥東西呢？不要害怕！分開來瞧一瞧。我們知道 [:lower:] 就是 a-z 的意思，那麼 [a-z] 當然就是 [[:lower:]] 囉！鳥哥第一次接觸正規表示法的時候，看到兩層中括號差點昏倒～完全看不懂！現在，請注意那個疊代的意義， 自然就能夠比較清楚了解囉！

這樣對於 [] 以及 [^] 以及 [] 當中的 - ，還有關於前面表格提到的特殊關鍵字有瞭解了嗎？^_^！

#### 例題三、行首與行尾字元 ^ $

我們在例題一當中，可以查詢到一行字串裡面有 the 的，那如果我想要讓 the 只在行首列出呢？ 這個時候就得要使用定位字元了！我們可以這樣做：

```bash
[dmtsai@study ~]$ grep -n '^the' regular_express.txt
12:the symbol '*' is represented as start.
```
此時，就只剩下第 12 行，因為只有第 12 行的行首是 the 開頭啊～此外， 如果我想要開頭是小寫字元的那一行就列出呢？可以這樣：

```bash
[dmtsai@study ~]$ grep -n '^[a-z]' regular_express.txt
2:apple is my favorite food.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
12:the symbol '*' is represented as start.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
```
你可以發現我們可以捉到第一個字元都不是大寫的！上面的指令也可以用如下的方式來取代的：
```bash
kevin@Kevin-Laptop:~/os/os_note/regex$ grep -n '^[[:lower:]]' regular_express.txt
2:apple is my favorite food.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
12:the symbol '*' is represented as start.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
```
好！那如果我不想要開頭是英文字母，則可以是這樣：

```bash
[dmtsai@study ~]$ grep -n '^[^a-zA-Z]' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
21:# I am VBird
# 指令也可以是： grep -n '^[^[:alpha:]]' regular_express.txt
```
注意到了吧？那個 ^ 符號，在字元集合符號(括號[])之內與之外是不同的！ 在 [] 內代表『反向選擇』，在 [] 之外則代表定位在行首的意義！要分清楚喔！ 反過來思考，那如果我想要找出來，行尾結束為小數點 (.) 的那一行，該如何處理：
```bash
[dmtsai@study ~]$ grep -n '\.$' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
11:This window is clear.
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
17:I like dog.
18:google is the best tools for search keyword.
20:go! go! Let's go.
```

特別注意到，因為小數點具有其他意義(底下會介紹)，所以必須要使用跳脫字元(\)來加以解除其特殊意義！ 不過，你或許會覺得奇怪，但是第 5~9 行最後面也是 . 啊～怎麼無法列印出來？ 這裡就牽涉到 Windows 平台的軟體對於斷行字元的判斷問題了！我們使用 cat -A 將第五行拿出來看， 你會發現：
```bash
[dmtsai@study ~]$ cat -An regular_express.txt | head -n 10 | tail -n 6
     5  However, this dress is about $ 3183 dollars.^M$
     6  GNU is free air not free beer.^M$
     7  Her hair is very beauty.^M$
     8  I can't finish the test.^M$
     9  Oh! The soup taste good.^M$
    10  motorcycle is cheap than car.$
```

我們在第九章內談到過斷行字元在 Linux 與 Windows 上的差異， 在上面的表格中我們可以發現 5~9 行為 Windows 的斷行字元 (^M$) ，而正常的 Linux 應該僅有第 10 行顯示的那樣 ($) 。所以囉，那個 . 自然就不是緊接在 $ 之前喔！也就捉不到 5~9 行了！這樣可以瞭解 ^ 與 $ 的意義嗎？ 好了，先不要看底下的解答，自己想一想，那麼如果我想要找出來，哪一行是『空白行』， 也就是說，該行並沒有輸入任何資料，該如何搜尋？
```bash
[dmtsai@study ~]$ grep -n '^$' regular_express.txt
22:
```
因為只有行首跟行尾 (^$)，所以，這樣就可以找出空白行啦！再來，假設你已經知道在一個程式腳本 (shell script) 或者是設定檔當中，空白行與開頭為 # 的那一行是註解，因此如果你要將資料列出給別人參考時， 可以將這些資料省略掉以節省保貴的紙張，那麼你可以怎麼作呢？ 我們以 /etc/rsyslog.conf 這個檔案來作範例，你可以自行參考一下輸出的結果：
```bash
[dmtsai@study ~]$ cat -n /etc/rsyslog.conf
# 在 CentOS 7 中，結果可以發現有 91 行的輸出，很多空白行與 # 開頭的註解行

[dmtsai@study ~]$ grep -v '^$' /etc/rsyslog.conf | grep -v '^#'
# 結果僅有 14 行，其中第一個『 -v '^$' 』代表『不要空白行』，
# 第二個『 -v '^#' 』代表『不要開頭是 # 的那行』喔！
```
是否節省很多版面啊？另外，你可能也會問，那為何不要出現 # 的符號的那行就直接捨棄呢？沒辦法！因為某些註解是與設定寫在同一行的後面， 如果你只是抓 # 就予以去除，那就會將某些設定也同時移除了！那錯誤就大了～

#### 例題四、任意一個字元 . 與重複字元 *

在第十章 bash 當中，我們知道萬用字元 * 可以用來代表任意(0或多個)字元， 但是正規表示法並不是萬用字元，兩者之間是不相同的！ 至於正規表示法當中的『 . 』則代表『絕對有一個任意字元』的意思！這兩個符號在正規表示法的意義如下：

. (小數點)：代表『一定有一個任意字元』的意思；
\* (星星號)：代表『重複前一個字元， 0 到無窮多次』的意思，為組合形態
這樣講不好懂，我們直接做個練習吧！假設我需要找出 g??d 的字串，亦即共有四個字元， 起頭是 g 而結束是 d ，我可以這樣做：

```bash
[dmtsai@study ~]$ grep -n 'g..d' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.
16:The world <Happy> is the same with "glad".

kevin@Kevin-Laptop:~/os$ grep -n 'g..d' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.^M
16:The world <Happy> is the same with "glad".
```

**因為強調 g 與 d 之間一定要存在兩個字元**，因此，第 13 行的 god 與第 14 行的 gd 就不會被列出來啦！再來，如果我想要列出有 oo, ooo, oooo 等等的資料， 也就是說，至少要有兩個(含) o 以上，該如何是好？是 o* 還是 oo* 還是 ooo* 呢？ 雖然你可以試看看結果， 不過結果太佔版面了 @_@ ，所以，我這裡就直接說明。

因為 * 代表的是『重複 0 個或多個前面的 RE 字符』的意義， 因此，『o*』代表的是：『擁有空字元或一個 o 以上的字元』， 特別注意，因為允許空字元(就是有沒有字元都可以的意思)，因此，『 grep -n 'o*' regular_express.txt 』將會把所有的資料都列印出來螢幕上！

那如果是『oo*』呢？則第一個 o 肯定必須要存在，第二個 o 則是可有可無的多個 o ， 所以，凡是含有 o, oo, ooo, oooo 等等，都可以被列出來～

同理，當我們需要『至少兩個 o 以上的字串』時，就需要 ooo* ，亦即是：

```bash
kevin@Kevin-Laptop:~/os$ grep -n 'ooo*' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
```

這樣理解 * 的意義了嗎？好了，現在出個練習，如果我想要字串開頭與結尾都是 g，但是兩個 g 之間僅能存在至少一個 o ，亦即是 gog, goog, gooog.... 等等，那該如何？

```bash
[dmtsai@study ~]$ grep -n 'goo*g' regular_express.txt
18:google is the best tools for search keyword.
19:goooooogle yes!
```

如此瞭解了嗎？再來一題，如果我想要找出 g 開頭與 g 結尾的字串，當中的字元可有可無，那該如何是好？是『g*g』嗎？

```bash
kevin@Kevin-Laptop:~/os$ grep -n 'g*g' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
3:Football game is not use feet only.
9:Oh! The soup taste good.^M
13:Oh!     My god!
14:The gd software is a library for drafting programs.^M
16:The world <Happy> is the same with "glad".
17:I like dog.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
```

但測試的結果竟然出現這麼多行？太詭異了吧？其實一點也不詭異，因為 g*g 裡面的 g* 代表『空字元或一個以上的 g』 在加上後面的 g ，因此，整個 RE 的內容就是 g, gg, ggg, gggg ， 因此，只要該行當中擁有一個以上的 g 就符合所需了！

那該如何得到我們的 g....g 的需求呢？呵呵！就利用任意一個字元『.』啊！ 亦即是：『g.*g』的作法，因為 * 可以是 0 或多個重複前面的字符，而 . 是任意字元，所以： 『.* 就代表零個或多個任意字元』的意思啦！

```bash
kevin@Kevin-Laptop:~/os$ grep -n 'g.*g' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
14:The gd software is a library for drafting programs.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
```

因為是代表 g 開頭與 g 結尾，中間任意字元均可接受，所以，第 1, 14, 20 行是可接受的喔！ 這個 .* 的 RE 表示任意字元是很常見的，希望大家能夠理解並且熟悉！ 再出一題，如果我想要找出『任意數字』的行列呢？因為僅有數字，所以就成為：

```bash
kevin@Kevin-Laptop:~/os$ grep -n '[0-9][0-9]*' ./os_note/regex/regular_express.txt 
5:However, this dress is about $ 3183 dollars.^M
15:You are the best is mean you are the no. 1.
```

雖然使用 grep -n '[0-9]' regular_express.txt 也可以得到相同的結果， 但鳥哥希望大家能夠理解上面指令當中 RE 表示法的意義才好！

#### 例題五、限定連續 RE 字符範圍 {}

在上個例題當中，我們可以利用 . 與 RE 字符及 * 來設定 0 個到無限多個重複字元， **那如果我想要限制一個範圍區間內的重複字元數呢**？舉例來說，我想要找出兩個到五個 o 的連續字串，該如何作？這時候就得要使用到限定範圍的字符 {} 了。 但根據正規表示法的處理原則，要讓 { 生效，得要加上反斜線， 亦即使用 \{ 才能成功的讓限定連續 RE 字符範圍的功能生效喔！ 至於 {} 的語法是這樣的，假設我要找到兩個 o 的字串，可以是：

```bash
kevin@Kevin-Laptop:~/os$ grep -n 'o\{2\}' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
```
這樣看似乎與 ooo* 的字符沒有什麼差異啊？因為第 19 行有多個 o 依舊也出現了！ 好，那麼換個搜尋的字串，假設我們要找出 g 後面接 2 到 5 個 o ，然後再接一個 g 的字串，他會是這樣：
```bash
kevin@Kevin-Laptop:~/os$ grep -n 'go\{2,5\}g' ./os_note/regex/regular_express.txt 
18:google is the best tools for search keyword
```

嗯！很好！第 19 行終於沒有被取用了(因為 19 行有 6 個 o 啊！)。 那麼，如果我想要的是 2 個 o 以上的 goooo....g 呢？除了可以是 gooo*g ，也可以是：

```bash
kevin@Kevin-Laptop:~/os$ grep -n 'go\{2,\}g' ./os_note/regex/regular_express.txt 
18:google is the best tools for search keyword.
19:goooooogle yes!
```

呵呵！就可以找出來啦～

### 11.2.4 基礎正規表示法字符彙整 (characters)

經過了上面的幾個簡單的範例，我們可以將基礎的正規表示法特殊字符彙整如下：

|RE 字符|意義與範例|
|--- |--- |
|^word|意義：待搜尋的字串(word)在行首！範例：搜尋行首為 # 開始的那一行，並列出行號 ``` grep -n '^#' regular_express.txt```|
|word$|意義：待搜尋的字串(word)在行尾！範例：將行尾為 ! 的那一行列印出來，並列出行號 ``` grep -n '!$' regular_express.txt ```
|.|意義：代表『一定有一個任意字元』的字符！範例：搜尋的字串可以是 (eve) (eae) (eee) (e e)， 但不能僅有 (ee) ！亦即 e 與 e 中間『一定』僅有一個字元，而空白字元也是字元！``` grep -n 'e.e' regular_express.txt ```
|\ | 意義：透過 shell 的跳脫字符，將特殊符號的特殊意義去除！意義：透過 shell 的跳脫字符，將特殊符號的特殊意義去除！```grep -n \' regular_express.txt``` 
| * | 	意義：重複零個到無窮多個的前一個 RE 字符 範例：找出含有 (es) (ess) (esss) 等等的字串，注意，因為 * 可以是 0 個，所以 es 也是符合帶搜尋字串。另外，因為 * 為重複『前一個 RE 字符』的符號， 因此，在 * 之前必須要緊接著一個 RE 字符喔！例如任意字元則為 『.*』 ！``` grep -n 'ess*' regular_express.txt ``` 
| [list] | 	意義：字元集合的 RE 字符，裡面列出想要擷取的字元！ 範例：搜尋含有 (gl) 或 (gd) 的那一行，需要特別留意的是，在 [] 當中『謹代表一個待搜尋的字元』， 例如『 a[afl]y 』代表搜尋的字串可以是 aay, afy, aly 即 [afl] 代表 a 或 f 或 l 的意思！``` grep -n 'g[ld]' regular_express.txt ``` 
|[n1-n2] | 意義：字元集合的 RE 字符，裡面列出想要擷取的字元範圍！範例：搜尋含有任意數字的那一行！需特別留意，在字元集合 [] 中的減號 - 是有特殊意義的，他代表兩個字元之間的所有連續字元！但這個連續與否與 ASCII 編碼有關，因此，你的編碼需要設定正確(在 bash 當中，需要確定LANG 與 LANGUAGE 的變數是否正確！) 例如所有大寫字元則為 [A-Z] ``` grep -n '[A-Z]' regular_express.txt ``` 
|[^list] | 意義：字元集合的 RE 字符，裡面列出不要的字串或範圍！範例：搜尋的字串可以是 (oog) (ood) 但不能是 (oot) ，那個 ^ 在 [] 內時，代表的意義是『反向選擇』的意思。 例如，我不要大寫字元，則為 [^A-Z]。但是，需要特別注意的是，如果以 ```grep -n [^A-Z] regular_express.txt ```來搜尋，卻發現該檔案內的所有行都被列出，為什麼？因為這個 [^A-Z] 是『非大寫字元』的意思， 因為每一行均有非大寫字元，例如第一行的 "Open Source" 就有 p,e,n,o.... 等等的小寫字 ```grep -n 'oo[^t]' regular_express.txt ``` 
| \\{n,m\\} | 意義：連續 n 到 m 個的『前一個 RE 字符』意義：若為 \{n\} 則是連續 n 個的前一個 RE 字符，意義：若是 \{n,\} 則是連續 n 個以上的前一個 RE 字符！ 範例：在 g 與 g 之間有 2 個到 3 個的 o 存在的字串，亦即 (goog)(gooog) ``` grep -n 'go\{2,3\}g' regular_express.txt ```|

再次強調：『正規表示法的特殊字元』與一般在指令列輸入指令的『萬用字元』並不相同， 例如，在萬用字元當中的 * 代表的是『 0 ~ 無限多個字元』的意思，但是在正規表示法當中， * 則是『重複 0 到無窮多個的前一個 RE 字符』的意思～使用的意義並不相同，不要搞混了！

舉例來說，不支援正規表示法的 ls 這個工具中，若我們使用 『```ls -l * ```』 代表的是任意檔名的檔案，而 『ls -l a* 』代表的是以 a 為開頭的任何檔名的檔案， 但在正規表示法中，我們要找到含有以 a 為開頭的檔案，則必須要這樣：(需搭配支援正規表示法的工具)

```bash
ls | grep -n '^a.*'
```

>例題：
以 ls -l 配合 grep 找出 /etc/ 底下檔案類型為連結檔屬性的檔名
答：
由於 ls -l 列出連結檔時標頭會是『 lrwxrwxrwx 』，因此使用如下的指令即可找出結果：```ls -l /etc | grep '^l'```
若僅想要列出幾個檔案，再以『 ```|wc -l``` 』 來累加處理即可。

### 11.2.5 sed 工具

在瞭解了一些正規表示法的基礎應用之後，再來呢？呵呵～兩個東西可以玩一玩的，那就是 sed 跟底下會介紹的 awk 了！ 這兩個傢伙可是相當的有用的啊！舉例來說，鳥哥寫的 logfile.sh 分析登錄檔的小程式 (第十八章會談到)，絕大部分分析關鍵字的取用、統計等等，就是用這兩個寶貝蛋來幫我完成的！那麼你說，要不要玩一玩啊？^_^

我們先來談一談 sed 好了， sed 本身也是一個管線命令，可以分析 standard input 的啦！ 而且 sed 還可以將資料進行取代、刪除、新增、擷取特定行等等的功能呢！很不錯吧～ 我們先來瞭解一下 sed 的用法，再來聊他的用途好了！

```bash
[dmtsai@study ~]$ sed [-nefr] [動作]
選項與參數：
-n  ：使用安靜(silent)模式。在一般 sed 的用法中，所有來自 STDIN 的資料一般都會被列出到螢幕上。
      但如果加上 -n 參數後，則只有經過 sed 特殊處理的那一行(或者動作)才會被列出來。
-e  ：直接在指令列模式上進行 sed 的動作編輯；
-f  ：直接將 sed 的動作寫在一個檔案內， -f filename 則可以執行 filename 內的 sed 動作；
-r  ：sed 的動作支援的是延伸型正規表示法的語法。(預設是基礎正規表示法語法)
-i  ：直接修改讀取的檔案內容，而不是由螢幕輸出。

動作說明：  [n1[,n2]]function
n1, n2 ：不見得會存在，一般代表『選擇進行動作的行數』，舉例來說，如果我的動作
         是需要在 10 到 20 行之間進行的，則『 10,20[動作行為] 』

function 有底下這些咚咚：
a   ：新增， a 的後面可以接字串，而這些字串會在新的一行出現(目前的下一行)～
c   ：取代， c 的後面可以接字串，這些字串可以取代 n1,n2 之間的行！
d   ：刪除，因為是刪除啊，所以 d 後面通常不接任何咚咚；
i   ：插入， i 的後面可以接字串，而這些字串會在新的一行出現(目前的上一行)；
p   ：列印，亦即將某個選擇的資料印出。通常 p 會與參數 sed -n 一起運作～
s   ：取代，可以直接進行取代的工作哩！通常這個 s 的動作可以搭配正規表示法！
      例如 1,20s/old/new/g 就是啦！
```

#### 以行為單位的新增/刪除功能

sed 光是用看的是看不懂的啦！所以又要來練習了！先來玩玩刪除與新增的功能吧！

```bash
範例一：將 /etc/passwd 的內容列出並且列印行號，同時，請將第 2~5 行刪除！
[dmtsai@study ~]$ nl /etc/passwd | sed '2,5d'
     1  root:x:0:0:root:/root:/bin/bash
     6  sync:x:5:0:sync:/sbin:/bin/sync
     7  shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
.....(後面省略).....
kevin@Kevin-Laptop:~/os$ nl os_note/regex/regular_express.txt | sed '2,5d'
     1  "Open Source" is a good mechanism to develop programs.
     6  GNU is free air not free beer.^M
     7  Her hair is very beauty.^M
     8  I can't finish the test.^M
     9  Oh! The soup taste good.^M
    10  motorcycle is cheap than car.
    11  This window is clear.
    12  the symbol '*' is represented as start.
    13  Oh!     My god!
    14  The gd software is a library for drafting programs.^M
    15  You are the best is mean you are the no. 1.
    16  The world <Happy> is the same with "glad".
    17  I like dog.
    18  google is the best tools for search keyword.
    19  goooooogle yes!
    20  go! go! Let's go.
    21  # I am VBird
```

看到了吧？sed 的動作為 '2,5d' ，那個 d 就是刪除！因為 2-5 行給他刪除了，所以顯示的資料就沒有 2-5 行囉～ 另外，注意一下，原本應該是要下達 sed -e 才對，沒有 -e 也行啦！同時也要注意的是， sed 後面接的動作，請務必以 '' 兩個單引號括住喔！

如果題型變化一下，舉例來說，如果只要刪除第 2 行，可以使用『 ```nl /etc/passwd | sed '2d'``` 』來達成， 至於若是要刪除第 3 到最後一行，則是『 ```nl /etc/passwd | sed '3,$d'``` 』的啦，那個錢字號『 ```$ ```』代表最後一行！

```bash
範例二：承上題，在第二行後(亦即是加在第三行)加上『drink tea?』字樣！
[dmtsai@study ~]$ nl /etc/passwd | sed '2a drink tea'
     1  root:x:0:0:root:/root:/bin/bash
     2  bin:x:1:1:bin:/bin:/sbin/nologin
drink tea
     3  daemon:x:2:2:daemon:/sbin:/sbin/nologin
.....(後面省略).....
kevin@Kevin-Laptop:~/os$ nl os_note/regex/regular_express.txt | sed '2a test'
     1  "Open Source" is a good mechanism to develop programs.
     2  apple is my favorite food.
test
     3  Football game is not use feet only.
     4  this dress doesn't fit me.
     5  However, this dress is about $ 3183 dollars.^M
     6  GNU is free air not free beer.^M
     7  Her hair is very beauty.^M
     8  I can't finish the test.^M
     9  Oh! The soup taste good.^M
    10  motorcycle is cheap than car.
    11  This window is clear.
    12  the symbol '*' is represented as start.
    13  Oh!     My god!
    14  The gd software is a library for drafting programs.^M
    15  You are the best is mean you are the no. 1.
    16  The world <Happy> is the same with "glad".
    17  I like dog.
    18  google is the best tools for search keyword.
    19  goooooogle yes!
    20  go! go! Let's go.
    21  # I am VBird
```

嘿嘿！在 a 後面加上的字串就已將出現在第二行後面囉！那如果是要在第二行前呢？『 ```nl /etc/passwd | sed '2i drink tea'```』就對啦！就是將『 a 』變成『 i 』即可。 增加一行很簡單，那如果是要增將兩行以上呢？

```bash
[dmtsai@study ~]$ nl /etc/passwd | sed '2a Drink tea or ......\
> drink beer ?'
     1  root:x:0:0:root:/root:/bin/bash
     2  bin:x:1:1:bin:/bin:/sbin/nologin
Drink tea or ......
drink beer ?
     3  daemon:x:2:2:daemon:/sbin:/sbin/nologin
.....(後面省略)....
```

這個範例的重點是『我們可以新增不只一行喔！可以新增好幾行』但是每一行之間都必須要以反斜線『 \ 』來進行新行的增加喔！所以，上面的例子中，我們可以發現在第一行的最後面就有 \ 存在啦！在多行新增的情況下， \ 是一定要的喔！

#### 以行為單位的取代與顯示功能

剛剛是介紹如何新增與刪除，那麼如果要整行取代呢？看看底下的範例吧：

```bash
範例四：我想將第2-5行的內容取代成為『No 2-5 number』呢？
[dmtsai@study ~]$ nl /etc/passwd | sed '2,5c No 2-5 number'
     1  root:x:0:0:root:/root:/bin/bash
No 2-5 number
     6  sync:x:5:0:sync:/sbin:/bin/sync
.....(後面省略).....
```

透過這個方法我們就能夠將資料整行取代了！非常容易吧！sed 還有更好用的東東！我們以前想要列出第 11~20 行， 得要透過『```head -n 20 | tail -n 10```』之類的方法來處理，很麻煩啦～ sed 則可以簡單的直接取出你想要的那幾行！是透過行號來捉的喔！看看底下的範例先：
```bash
範例五：僅列出 /etc/passwd 檔案內的第 5-7 行
[dmtsai@study ~]$ nl /etc/passwd | sed -n '5,7p'
     5  lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
     6  sync:x:5:0:sync:/sbin:/bin/sync
     7  shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
kevin@Kevin-Laptop:~/os$ nl /etc/passwd | sed -n '5,7p'
     5  sync:x:4:65534:sync:/bin:/bin/sync
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
```

上述的指令中有個重要的選項『 -n 』，按照說明文件，這個 -n 代表的是『安靜模式』！ 那麼為什麼要使用安靜模式呢？你可以自行下達 sed '5,7p' 就知道了 (5-7 行會重複輸出)！ 有沒有加上 -n 的參數時，輸出的資料可是差很多的喔！你可以透過這個 sed 的以行為單位的顯示功能， 就能夠將某一個檔案內的某些行號捉出來查閱！很棒的功能！不是嗎？
```bash
kevin@Kevin-Laptop:~/os$ nl /etc/passwd | sed '5,7p'
     1  root:x:0:0:root:/root:/bin/bash
     2  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
     3  bin:x:2:2:bin:/bin:/usr/sbin/nologin
     4  sys:x:3:3:sys:/dev:/usr/sbin/nologin
     5  sync:x:4:65534:sync:/bin:/bin/sync
     5  sync:x:4:65534:sync:/bin:/bin/sync
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
     8  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
     9  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
    10  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    11  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
    12  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
    13  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
    14  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
    15  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
    16  irc:x:39:39:ircd:/run/ircd:/usr/sbin/nologin
    17  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
    18  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
    19  systemd-network:x:100:102:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin
    20  systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd:/usr/sbin/nologin
    21  messagebus:x:102:105::/nonexistent:/usr/sbin/nologin
    22  systemd-timesync:x:103:106:systemd Time Synchronization,,,:/run/systemd:/usr/sbin/nologin
    23  syslog:x:104:111::/home/syslog:/usr/sbin/nologin
    24  _apt:x:105:65534::/nonexistent:/usr/sbin/nologin
    25  uuidd:x:106:112::/run/uuidd:/usr/sbin/nologin
    26  tcpdump:x:107:113::/nonexistent:/usr/sbin/nologin
    27  kevin:x:1000:1000:,,,:/home/kevin:/bin/bash
```

#### 部分資料的搜尋並取代的功能

除了整行的處理模式之外， sed 還可以用行為單位進行部分資料的搜尋並取代的功能喔！ 基本上 sed 的搜尋與取代的與 vi 相當的類似！他有點像這樣：
```bash
sed 's/要被取代的字串/新的字串/g'
```

上表中特殊字體的部分為關鍵字，請記下來！至於三個斜線分成兩欄就是新舊字串的替換啦！ 我們使用底下這個取得 IP 數據的範例，一段一段的來處理給您瞧瞧，讓你瞭解一下什麼是咱們所謂的搜尋並取代吧！

```bash
kevin@Kevin-Laptop:~/os$ ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.24.83.41  netmask 255.255.240.0  broadcast 172.24.95.255
        inet6 fe80::215:5dff:fe7c:a2df  prefixlen 64  scopeid 0x20<link>
        ether 00:15:5d:7c:a2:df  txqueuelen 1000  (Ethernet)
        RX packets 439  bytes 139850 (139.8 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 110  bytes 15791 (15.7 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 1364  bytes 10687921 (10.6 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1364  bytes 10687921 (10.6 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

kevin@Kevin-Laptop:~/os$ ifconfig eth0 | grep 'inet '
        inet 172.24.83.41  netmask 255.255.240.0  broadcast 172.24.95.255
kevin@Kevin-Laptop:~/os$ ifconfig eth0 | grep 'inet ' | sed 's/^.*inet //g'
172.24.83.41  netmask 255.255.240.0  broadcast 172.24.95.255
# sed 's/^.*inet //g' 删除从头到inet的内容
kevin@Kevin-Laptop:~/os$ ifconfig eth0 | grep 'inet ' | sed 's/^.*inet //g' \
> | sed 's/ *netmask.*$//g'
172.24.83.41
# sed 's/ *netmask.*$//g' 删除从netmask到尾的内容
```

透過這個範例的練習也建議您依據此一步驟來研究你的指令！就是先觀察，然後再一層一層的試做， 如果有做不對的地方，就先予以修改，改完之後測試，成功後再往下繼續測試。以鳥哥上面的介紹中， 那一大串指令就做了四個步驟！對吧！ ^_^

#### 直接修改檔案內容(危險動作)

你以為 sed 只有這樣的能耐嗎？那可不！ sed 甚至可以直接修改檔案的內容呢！而不必使用管線命令或資料流重導向！ 不過，由於這個動作會直接修改到原始的檔案，所以請你千萬不要隨便拿系統設定檔來測試喔！ 我們還是使用你下載的 regular_express.txt 檔案來測試看看吧！

```bash
範例六：利用 sed 將 regular_express.txt 內每一行結尾若為 . 則換成 !
[dmtsai@study ~]$ sed -i 's/\.$/\!/g' regular_express.txt
# 上頭的 -i 選項可以讓你的 sed 直接去修改後面接的檔案內容而不是由螢幕輸出喔！
# 這個範例是用在取代！請您自行 cat 該檔案去查閱結果囉！

範例七：利用 sed 直接在 regular_express.txt 最後一行加入『# This is a test』
[dmtsai@study ~]$ sed -i '$a # This is a test' regular_express.txt
# 由於 $ 代表的是最後一行，而 a 的動作是新增，因此該檔案最後新增囉！
```

sed 的『 -i 』選項可以直接修改檔案內容，這功能非常有幫助！舉例來說，如果你有一個 100 萬行的檔案，你要在第 100 行加某些文字，此時使用 vim 可能會瘋掉！因為檔案太大了！那怎辦？就利用 sed 啊！透過 sed 直接修改/取代的功能，你甚至不需要使用 vim 去修訂！很棒吧！

總之，這個 sed 不錯用啦！而且很多的 shell script 都會使用到這個指令的功能～ sed 可以幫助系統管理員管理好日常的工作喔！要仔細的學習呢！

## 11.3 延伸正規表示法

事實上，一般讀者只要瞭解基礎型的正規表示法大概就已經相當足夠了，不過，某些時刻為了要簡化整個指令操作， 瞭解一下使用範圍更廣的延伸型正規表示法的表示式會更方便呢！舉個簡單的例子好了，在上節的例題三的最後一個例子中，我們要去除空白行與行首為 # 的行列，使用的是
```bash
grep -v '^$' regular_express.txt | grep -v '^#'
```
需要使用到管線命令來搜尋兩次！那麼如果使用延伸型的正規表示法，我們可以簡化為：
```bash
egrep -v '^$|^#' regular_express.txt
```

延伸型正規表示法可以透過群組功能『 | 』來進行一次搜尋！那個在單引號內的管線意義為『或 or』啦！ 是否變的更簡單呢？此外，grep 預設僅支援基礎正規表示法，如果要使用延伸型正規表示法，你可以使用 grep -E ， 不過更建議直接使用 egrep ！直接區分指令比較好記憶！其實 egrep 與 grep -E 是類似命令別名的關係啦！

熟悉了正規表示法之後，到這個延伸型的正規表示法，你應該也會想到，不就是多幾個重要的特殊符號嗎？ ^_^y 是的～所以，我們就直接來說明一下，延伸型正規表示法有哪幾個特殊符號？由於底下的範例還是有使用到 regular_express.txt ，不巧的是剛剛我們可能將該檔案修改過了 @_@，所以，請重新下載該檔案來練習喔！

|RE 字符 | 意義與範例 |
|--- | ---|
| + | 意義：重複『一個或一個以上』的前一個 RE 字符 範例：搜尋 (god) (good) (goood)... 等等的字串。 那個 o+ 代表『一個以上的 o 』所以，底下的執行成果會將第1, 9, 13 行列出來。```egrep -n 'go+d' regular_express.txt``` |
| ? | 意義：『零個或一個』的前一個 RE 字符 範例：搜尋 (gd) (god) 這兩個字串。 那個 o? 代表『空的或 1 個 o 』所以，上面的執行成果會將第 13, 14 行列出來。 有沒有發現到，這兩個案例( 'go+d' 與 'go?d' )的結果集合與 'go*d' 相同？ 想想看，這是為什麼喔！ ^_^ ```egrep -n 'go?d' regular_express.txt```|
| \| | 意義：用或( or )的方式找出數個字串 範例：搜尋 gd 或 good 這兩個字串，注意，是『或』！ 所以，第 1,9,14 這三行都可以被列印出來喔！那如果還想要找出 dog 呢？```egrep -n 'gd|good' regular_express.txt egrep -n 'gd|good|dog' regular_express.txt ```|
| () | 意義：找出『群組』字串 範例：搜尋 (glad) 或 (good) 這兩個字串，因為 g 與 d 是重複的，所以， 我就可以將 la 與 oo 列於 ( ) 當中，並以 \| 來分隔開來，就可以啦！ ```egrep -n 'g(la|oo)d' regular_express.txt``` |
|()+| 意義：多個重複群組的判別 範例：將『AxyzxyzxyzxyzC』用 echo 叫出，然後再使用如下的方法搜尋一下！```echo 'AxyzxyzxyzxyzC' | egrep 'A(xyz)+C'``` 上面的例子意思是說，我要找開頭是 A 結尾是 C ，中間有一個以上的 "xyz" 字串的意思～| 

```bash
kevin@Kevin-Laptop:~/os$ egrep -n 'go+d' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.^M
13:Oh!     My god!

kevin@Kevin-Laptop:~/os$ egrep -n 'go?d' ./os_note/regex/regular_express.txt 
13:Oh!     My god!
14:The gd software is a library for drafting programs.^M

kevin@Kevin-Laptop:~/os$ egrep -n 'gd|good|dog' ./os_note/regex/regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.^M
14:The gd software is a library for drafting programs.^M
17:I like dog.
```

以上這些就是延伸型的正規表示法的特殊字元。另外，要特別強調的是，那個 ! 在正規表示法當中並不是特殊字元， 所以，如果你想要查出來檔案中含有 ! 與 > 的字行時，可以這樣：

```bash
grep -n '[!>]' regular_express.txt
```
這樣可以瞭解了嗎？常常看到有陷阱的題目寫：『反向選擇這樣對否？ '[!a-z]'？』， 呵呵！是錯的呦～要 '[^a-z] 才是對的！至於更多關於正規表示法的進階文章，請參考文末的參考資料(註2)

## 11.4 文件的格式化與相關處理

接下來讓我們來將文件進行一些簡單的編排吧！底下這些動作可以將你的訊息進行排版的動作， 不需要重新以 vim 去編輯，透過資料流重導向配合底下介紹的 printf 功能，以及 awk 指令， 就可以讓你的訊息以你想要的模樣來輸出了！試看看吧！

### 11.4.1 格式化列印： printf

在很多時候，我們可能需要將自己的資料給他格式化輸出的！ 舉例來說，考試卷分數的輸出，姓名與科目及分數之間，總是可以稍微作個比較漂亮的版面配置吧？ 例如我想要輸出底下的樣式：

```dotnetcli
Name     Chinese   English   Math    Average
DmTsai        80        60     92      77.33
VBird         75        55     80      70.00
Ken           60        90     70      73.33
```

上表的資料主要分成五個欄位，各個欄位之間可使用 tab 或空白鍵進行分隔。 請將上表的資料轉存成為 printf.txt 檔名，等一下我們會利用這個檔案來進行幾個小練習的。 因為每個欄位的原始資料長度其實並非是如此固定的 (Chinese 長度就是比 Name 要多)， 而我就是想要如此表示出這些資料，此時，就得需要列印格式管理員 printf 的幫忙了！ printf 可以幫我們將資料輸出的結果格式化，而且而支援一些特殊的字符～底下我們就來看看！

```bash
[dmtsai@study ~]$ printf '列印格式' 實際內容
選項與參數：
關於格式方面的幾個特殊樣式：
       \a    警告聲音輸出
       \b    倒退鍵(backspace)
       \f    清除螢幕 (form feed)
       \n    輸出新的一行
       \r    亦即 Enter 按鍵
       \t    水平的 [tab] 按鍵
       \v    垂直的 [tab] 按鍵
       \xNN  NN 為兩位數的數字，可以轉換數字成為字元。
關於 C 程式語言內，常見的變數格式
       %ns   那個 n 是數字， s 代表 string ，亦即多少個字元；
       %ni   那個 n 是數字， i 代表 integer ，亦即多少整數位數；
       %N.nf 那個 n 與 N 都是數字， f 代表 floating (浮點)，如果有小數位數，
             假設我共要十個位數，但小數點有兩位，即為 %10.2f 囉！
```

接下來我們來進行幾個常見的練習。假設所有的資料都是一般文字 (這也是最常見的狀態)，因此最常用來分隔資料的符號就是 [Tab] 啦！因為 [Tab] 按鍵可以將資料作個整齊的排列！那麼如何利用 printf 呢？參考底下這個範例：

```bash
範例一：將剛剛上頭資料的檔案 (printf.txt) 內容僅列出姓名與成績：(用 [tab] 分隔)
[dmtsai@study ~]$ printf '%s\t %s\t %s\t %s\t %s\t \n' $(cat printf.txt)
Name     Chinese         English         Math    Average
DmTsai   80      60      92      77.33
VBird    75      55      80      70.00
Ken      60      90      70      73.33
```

由於 printf 並不是管線命令，因此我們得要透過類似上面的功能，將檔案內容先提出來給 printf 作為後續的資料才行。 如上所示，我們將每個資料都以 [tab] 作為分隔，但是由於 Chinese 長度太長，導致 English 中間多了一個 [tab] 來將資料排列整齊！啊～結果就看到資料對齊結果的差異了！

另外，在 printf 後續的那一段格式中，%s 代表一個不固定長度的字串，而字串與字串中間就以 \t 這個 [tab] 分隔符號來處理！你要記得的是，由於 \t 與 %s 中間還有空格，因此每個字串間會有一個 [tab] 與一個空白鍵的分隔喔！

既然每個欄位的長度不固定會造成上述的困擾，那我將每個欄位固定就好啦！沒錯沒錯！這樣想非常好！ 所以我們就將資料給他進行固定欄位長度的設計吧！

```bash
範例二：將上述資料關於第二行以後，分別以字串、整數、小數點來顯示：
[dmtsai@study ~]$ printf '%10s %5i %5i %5i %8.2f \n' $(cat printf.txt | grep -v Name)
    DmTsai    80    60    92    77.33
     VBird    75    55    80    70.00
       Ken    60    90    70    73.33
```

上面這一串格式想必您看得很辛苦！沒關係！一個一個來解釋！上面的格式共分為五個欄位， %10s 代表的是一個長度為 10 個字元的字串欄位，%5i 代表的是長度為 5 個字元的數字欄位，至於那個 %8.2f 則代表長度為 8 個字元的具有小數點的欄位，其中小數點有兩個字元寬度。我們可以使用底下的說明來介紹 %8.2f 的意義：

字元寬度： 12345678
%8.2f意義：00000.00
如上所述，全部的寬度僅有 8 個字元，整數部分佔有 5 個字元，小數點本身 (.) 佔一位，小數點下的位數則有兩位。 這種格式經常使用於數值程式的設計中！這樣瞭解乎？自己試看看如果要將小數點位數變成 1 位又該如何處理？

printf 除了可以格式化處理之外，他還可以依據 ASCII 的數字與圖形對應來顯示資料喔(註3)！ 舉例來說 16 進位的 45 可以得到什麼 ASCII 的顯示圖 (其實是字元啦)？
```bash
範例三：列出 16 進位數值 45 代表的字元為何？
[dmtsai@study ~]$ printf '\x45\n'
E
# 這東西也很好玩～他可以將數值轉換成為字元，如果你會寫 script 的話，
# 可以自行測試一下，由 20~80 之間的數值代表的字元是啥喔！ ^_^
```

printf 的使用相當的廣泛喔！包括等一下後面會提到的 awk 以及在 C 程式語言當中使用的螢幕輸出， 都是利用 printf 呢！鳥哥這裡也只是列出一些可能會用到的格式而已，有興趣的話，可以自行多作一些測試與練習喔！ ^_^

### 11.4.2 awk：好用的資料處理工具

awk 也是一個非常棒的資料處理工具！相較於 sed 常常作用於一整個行的處理， awk 則比較傾向於一行當中分成數個『欄位』來處理。因此，awk 相當的適合處理小型的數據資料處理呢！awk 通常運作的模式是這樣的：
```bash
[dmtsai@study ~]$ awk '條件類型1{動作1} 條件類型2{動作2} ...' filename
```
awk 後面接兩個單引號並加上大括號 {} 來設定想要對資料進行的處理動作。 awk 可以處理後續接的檔案，也可以讀取來自前個指令的 standard output 。 但如前面說的， awk 主要是處理『每一行的欄位內的資料』，而預設的『欄位的分隔符號為 "空白鍵" 或 "[tab]鍵" 』！舉例來說，我們用 last 可以將登入者的資料取出來，結果如下所示
```bash
kevin@Kevin-Laptop:~/os$ last -n 5

wtmp begins Thu Nov 17 14:49:11 2022

[dmtsai@study ~]$ last -n 5 <==僅取出前五行
dmtsai   pts/0     192.168.1.100   Tue Jul 14 17:32   still logged in
dmtsai   pts/0     192.168.1.100   Thu Jul  9 23:36 - 02:58  (03:22)
dmtsai   pts/0     192.168.1.100   Thu Jul  9 17:23 - 23:36  (06:12)
dmtsai   pts/0     192.168.1.100   Thu Jul  9 08:02 - 08:17  (00:14)
dmtsai   tty1                      Fri May 29 11:55 - 12:11  (00:15)
```

若我想要取出帳號與登入者的 IP ，且帳號與 IP 之間以 [tab] 隔開，則會變成這樣：

```bash
[dmtsai@study ~]$ last -n 5 | awk '{print $1 "\t" $3}'
dmtsai  192.168.1.100
dmtsai  192.168.1.100
dmtsai  192.168.1.100
dmtsai  192.168.1.100
dmtsai  Fri
```

上表是 awk 最常使用的動作！透過 print 的功能將欄位資料列出來！欄位的分隔則以空白鍵或 [tab] 按鍵來隔開。 因為不論哪一行我都要處理，因此，就不需要有 "條件類型" 的限制！我所想要的是第一欄以及第三欄， 但是，第五行的內容怪怪的～這是因為資料格式的問題啊！所以囉～使用 awk 的時候，請先確認一下你的資料當中，如果是連續性的資料，請不要有空格或 [tab] 在內，否則，就會像這個例子這樣，會發生誤判喔！

另外，由上面這個例子你也會知道，在 awk 的括號內，每一行的每個欄位都是有變數名稱的，那就是 $1, $2... 等變數名稱。以上面的例子來說， dmtsai 是 $1 ，因為他是第一欄嘛！至於 192.168.1.100 是第三欄， 所以他就是 $3 啦！後面以此類推～呵呵！還有個變數喔！那就是 $0 ，$0 代表『一整列資料』的意思～以上面的例子來說，第一行的 $0 代表的就是『dmtsai .... 』那一行啊！ 由此可知，剛剛上面五行當中，整個 awk 的處理流程是：

讀入第一行，並將第一行的資料填入 $0, $1, $2.... 等變數當中；
依據 "條件類型" 的限制，判斷是否需要進行後面的 "動作"；
做完所有的動作與條件類型；
若還有後續的『行』的資料，則重複上面 1~3 的步驟，直到所有的資料都讀完為止。
經過這樣的步驟，你會曉得， awk 是『以行為一次處理的單位』， 而『以欄位為最小的處理單位』。好了，那麼 awk 怎麼知道我到底這個資料有幾行？有幾欄呢？這就需要 awk 的內建變數的幫忙啦～


|變數名稱	| 代表意義 |
|--- | ---|
|NF	|每一行 ($0) 擁有的欄位總數
|NR	|目前 awk 所處理的是『第幾行』資料
|FS	|目前的分隔字元，預設是空白鍵

我們繼續以上面 last -n 5 的例子來做說明，如果我想要：

列出每一行的帳號(就是 $1)；
列出目前處理的行數(就是 awk 內的 NR 變數)
並且說明，該行有多少欄位(就是 awk 內的 NF 變數)
則可以這樣：

```bash
[dmtsai@study ~]$ last -n 5| awk '{print $1 "\t lines: " NR "\t columns: " NF}'
dmtsai   lines: 1        columns: 10
dmtsai   lines: 2        columns: 10
dmtsai   lines: 3        columns: 10
dmtsai   lines: 4        columns: 10
dmtsai   lines: 5        columns: 9
# 注意喔，在 awk 內的 NR, NF 等變數要用大寫，且不需要有錢字號 $ 啦！
```

這樣可以瞭解 NR 與 NF 的差別了吧？好了，底下來談一談所謂的 "條件類型" 了吧！

#### awk 的邏輯運算字元

既然有需要用到 "條件" 的類別，自然就需要一些邏輯運算囉～例如底下這些：

|運算單元|	代表意義|
|---| --- |
|\> |	大於|
|<	|小於|
|\>=	|大於或等於|
|<=	|小於或等於|
|==	|等於|
|!=	|不等於|

值得注意的是那個『 == 』的符號，因為：

邏輯運算上面亦即所謂的大於、小於、等於等判斷式上面，習慣上是以『 == 』來表示；
如果是直接給予一個值，例如變數設定時，就直接使用 = 而已。
好了，我們實際來運用一下邏輯判斷吧！舉例來說，在 /etc/passwd 當中是以冒號 ":" 來作為欄位的分隔， 該檔案中第一欄位為帳號，第三欄位則是 UID。那假設我要查閱，第三欄小於 10 以下的數據，並且僅列出帳號與第三欄， 那麼可以這樣做：

```bash
[dmtsai@study ~]$ cat /etc/passwd | awk '{FS=":"} $3 < 10 {print $1 "\t " $3}'
root:x:0:0:root:/root:/bin/bash
bin      1
daemon   2
....(以下省略)....
```

有趣吧！不過，怎麼第一行沒有正確的顯示出來呢？這是因為我們讀入第一行的時候，那些變數 $1, $2... 預設還是以空白鍵為分隔的，所以雖然我們定義了 FS=":" 了， 但是卻僅能在第二行後才開始生效。那麼怎麼辦呢？我們可以預先設定 awk 的變數啊！ 利用 BEGIN 這個關鍵字喔！這樣做：

```bash
[dmtsai@study ~]$ cat /etc/passwd | awk 'BEGIN {FS=":"} $3 < 10 {print $1 "\t " $3}'
root     0
bin      1
daemon   2
......(以下省略)......
```

### 11.4.3 檔案比對工具

什麼時候會用到檔案的比對啊？通常是『同一個套裝軟體的不同版本之間，比較設定檔與原始檔的差異』。 很多時候所謂的檔案比對，通常是用在 ASCII 純文字檔的比對上的！那麼比對檔案的指令有哪些？最常見的就是 diff 囉！ 另外，除了 diff 比對之外，我們還可以藉由 cmp 來比對非純文字檔！同時，也能夠藉由 diff 建立的分析檔， 以處理補丁 (patch) 功能的檔案呢！就來玩玩先！

#### diff

diff 就是用在比對兩個檔案之間的差異的，並且是以行為單位來比對的！一般是用在 ASCII 純文字檔的比對上。 由於是以行為比對的單位，因此 diff 通常是用在同一的檔案(或軟體)的新舊版本差異上！ 舉例來說，假如我們要將 /etc/passwd 處理成為一個新的版本，處理方式為： 將第四行刪除，第六行則取代成為『no six line』，新的檔案放置到 /tmp/test 裡面，那麼應該怎麼做？

```bash
[dmtsai@study ~]$ diff [-bBi] from-file to-file
選項與參數：
from-file ：一個檔名，作為原始比對檔案的檔名；
to-file   ：一個檔名，作為目的比對檔案的檔名；
注意，from-file 或 to-file 可以 - 取代，那個 - 代表『Standard input』之意。

-b  ：忽略一行當中，僅有多個空白的差異(例如 "about me" 與 "about     me" 視為相同
-B  ：忽略空白行的差異。
-i  ：忽略大小寫的不同。

範例一：比對 regular_express.txt 與 diff.txt 的差異：
kevin@Kevin-Laptop:~/os$ cp ./os_note/regex/regular_express.txt ./os_note/regex/diff.txt
kevin@Kevin-Laptop:~/os$ sed -i '$a # This is a test' ./os_note/regex/diff.txt 
kevin@Kevin-Laptop:~/os$ diff ./os_note/regex/regular_express.txt ./os_note/regex/diff.txt 
23a24
> # This is a test
```

用 diff 比對檔案真的是很簡單喔！不過，你不要用 diff 去比對兩個完全不相干的檔案，因為比不出個啥咚咚！ 另外， diff 也可以比對整個目錄下的差異喔！舉例來說，我們想要瞭解一下不同的開機執行等級 (runlevel) 內容有啥不同？假設你已經知道執行等級 0 與 5 的啟動腳本分別放置到 /etc/rc0.d 及 /etc/rc5.d ， 則我們可以將兩個目錄比對一下：

```bash
[dmtsai@study ~]$ diff /etc/rc0.d/ /etc/rc5.d/
Only in /etc/rc0.d/: K90network
Only in /etc/rc5.d/: S10network

kevin@Kevin-Laptop:~/os$ diff /etc/rc0.d/ /etc/rc5.d/
Only in /etc/rc0.d/: K01irqbalance
Only in /etc/rc0.d/: K01plymouth
Only in /etc/rc0.d/: K01udev
Only in /etc/rc0.d/: K01unattended-upgrades
Only in /etc/rc0.d/: K01uuidd
Only in /etc/rc5.d/: S01apport
Only in /etc/rc5.d/: S01binfmt-support
Only in /etc/rc5.d/: S01console-setup.sh
Only in /etc/rc5.d/: S01cron
Only in /etc/rc5.d/: S01dbus
Only in /etc/rc5.d/: S01irqbalance
Only in /etc/rc5.d/: S01plymouth
Only in /etc/rc5.d/: S01rsync
Only in /etc/rc5.d/: S01unattended-upgrades
Only in /etc/rc5.d/: S01uuidd
```

#### cmp

相對於 diff 的廣泛用途， cmp 似乎就用的沒有這麼多了～ cmp 主要也是在比對兩個檔案，他主要利用『位元組』單位去比對， 因此，當然也可以比對 binary file 囉～(還是要再提醒喔， diff 主要是以『行』為單位比對， cmp 則是以『位元組』為單位去比對，這並不相同！)

```bash
[dmtsai@study ~]$ cmp [-l] file1 file2
選項與參數：
-l  ：將所有的不同點的位元組處都列出來。因為 cmp 預設僅會輸出第一個發現的不同點。

範例一：用 cmp 比較一下 passwd.old 及 passwd.new
[dmtsai@study testpw]$ cmp passwd.old passwd.new
passwd.old passwd.new differ: char 106, line 4
# 看到了嗎？第一個發現的不同點在第四行，而且位元組數是在第 106 個位元組處！這個 cmp 也可以用來比對 binary 啦！ ^_^

kevin@Kevin-Laptop:~/os$ cmp ./os_note/regex/regular_express.txt ./os_note/regex/diff.txt 
cmp: EOF on ./os_note/regex/regular_express.txt after byte 661, line 23
```

#### patch

patch 這個指令與 diff 可是有密不可分的關係啊！我們前面提到，diff 可以用來分辨兩個版本之間的差異， 舉例來說，剛剛我們所建立的 passwd.old 及 passwd.new 之間就是兩個不同版本的檔案。 那麼，如果要『升級』呢？就是『將舊的檔案升級成為新的檔案』時，應該要怎麼做呢？ 其實也不難啦！就是『先比較先舊版本的差異，並將差異檔製作成為補丁檔，再由補丁檔更新舊檔案』即可。 舉例來說，我們可以這樣做測試：

### 11.4.4 檔案列印準備： pr

如果你曾經使用過一些圖形介面的文書處理軟體的話，那麼很容易發現，當我們在列印的時候， 可以同時選擇與設定每一頁列印時的標頭吧！也可以設定頁碼呢！那麼，如果我是在 Linux 底下列印純文字檔呢 可不可以具有標題啊？可不可以加入頁碼啊？呵呵！當然可以啊！使用 pr 就能夠達到這個功能了。不過， pr 的參數實在太多了，鳥哥也說不完，一般來說，鳥哥都僅使用最簡單的方式來處理而已。舉例來說，如果想要列印 /etc/man_db.conf 呢？

```bash
kevin@Kevin-Laptop:~/os$ pr ./os_note/regex/regular_express.txt 


2022-11-17 18:02       ./os_note/regex/regular_express.txt        Page 1


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

上面特殊字體那一行呢，其實就是使用 pr 處理後所造成的標題啦！標題中會有『檔案時間』、『檔案檔名』及『頁碼』三大項目。 更多的 pr 使用，請參考 pr 的說明啊！ ^_^

## 11.5 重點回顧

正規表示法就是處理字串的方法，他是以行為單位來進行字串的處理行為；

正規表示法透過一些特殊符號的輔助，可以讓使用者輕易的達到『搜尋/刪除/取代』某特定字串的處理程序；
只要工具程式支援正規表示法，那麼該工具程式就可以用來作為正規表示法的字串處理之用；

正規表示法與萬用字元是完全不一樣的東西！萬用字元 (wildcard) 代表的是 bash 操作介面的一個功能， 但正規表示法則是一種字串處理的表示方式！

使用 grep 或其他工具進行正規表示法的字串比對時，因為編碼的問題會有不同的狀態，因此， 你最好將 LANG 等變數設定為 C 或者是 en 等英文語系！

grep 與 egrep 在正規表示法裡面是很常見的兩支程式，其中， egrep 支援更嚴謹的正規表示法的語法；
由於編碼系統的不同，不同的語系 (LANG) 會造成正規表示法擷取資料的差異。因此可利用特殊符號如 [:upper:] 來替代編碼範圍較佳；

由於嚴謹度的不同，正規表示法之上還有更嚴謹的延伸正規表示法；

基礎正規表示法的特殊字符有： *, ., [], [-], [^], ^, $ 等！

常見的支援正規表示法的工具軟體有： grep , sed, vim 等等
printf 可以透過一些特殊符號來將資料進行格式化輸出；

awk 可以使用『欄位』為依據，進行資料的重新整理與輸出；

文件的比對中，可利用 diff 及 cmp 進行比對，其中 diff 主要用在純文字檔案方面的新舊版本比對
patch 指令可以將舊版資料更新到新版 (主要亦由 diff 建立 patch 的補丁來源檔案)