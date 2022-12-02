# 第十三章、Linux 帳號管理與 ACL 權限設定

## 13.1 Linux 的帳號與群組

管理員的工作中，相當重要的一環就是『管理帳號』啦！因為整個系統都是你在管理的， 並且所有一般用戶的帳號申請，都必須要透過你的協助才行！所以你就必須要瞭解一下如何管理好一個伺服器主機的帳號啦！ 在管理 Linux 主機的帳號時，我們必須先來瞭解一下 Linux 到底是如何辨別每一個使用者的！

### 13.1.1 使用者識別碼： UID 與 GID

雖然我們登入 Linux 主機的時候，輸入的是我們的帳號，但是其實 Linux 主機並不會直接認識你的『帳號名稱』的，他僅認識 ID 啊 (ID 就是一組號碼啦)。 由於電腦僅認識 0 與 1，所以主機對於數字比較有概念的；至於帳號只是為了讓人們容易記憶而已。 而你的 ID 與帳號的對應就在 /etc/passwd 當中哩。

那麼到底有幾種 ID 呢？還記得我們在第五章內有提到過， 每一個檔案都具有『擁有人與擁有群組』的屬性嗎？沒錯啦～每個登入的使用者至少都會取得兩個 ID ，一個是使用者 ID (User ID ，簡稱 UID)、一個是群組 ID (Group ID ，簡稱 GID)。

那麼檔案如何判別他的擁有者與群組呢？其實就是利用 UID 與 GID 啦！每一個檔案都會有所謂的擁有者 ID 與擁有群組 ID ，當我們有要顯示檔案屬性的需求時，系統會依據 /etc/passwd 與 /etc/group 的內容， 找到 UID / GID 對應的帳號與群組名稱再顯示出來！我們可以作個小實驗，你可以用 root 的身份 vim /etc/passwd ，然後將你的一般身份的使用者的 ID 隨便改一個號碼，然後再到你的一般身份的目錄下看看原先該帳號擁有的檔案，你會發現該檔案的擁有人變成了 『數字了』呵呵！這樣可以理解了嗎？來看看底下的例子：

```bash
kevin@Kevin-Laptop:~/os$ id kevin
uid=1000(kevin) gid=1000(kevin) groups=1000(kevin),4(adm),20(dialout),24(cdrom),25(floppy),27(sudo),29(audio),30(dip),44(video),46(plugdev),116(netdev)
kevin@Kevin-Laptop:~/os$ ll -d /home/kevin
drwxr-x--- 9 kevin kevin 4096 Nov 25 20:39 /home/kevin/

```

你一定要瞭解的是，**上面的例子僅是在說明 UID 與帳號的對應性，在一部正常運作的 Linux 主機環境下，上面的動作不可隨便進行， 這是因為系統上已經有很多的資料被建立存在了，隨意修改系統上某些帳號的 UID 很可能會導致某些程序無法進行**，這將導致系統無法順利運作的結果， 因為權限的問題啊！所以，瞭解了之後，請趕快回到 /etc/passwd 裡面，將數字改回來喔！

### 13.1.2 使用者帳號

Linux 系統上面的使用者如果需要登入主機以取得 shell 的環境來工作時，他需要如何進行呢？ **首先，他必須要在電腦前面利用 tty1~tty6 的終端機提供的 login 介面，並輸入帳號與密碼後才能夠登入**。 如果是透過網路的話，那至少使用者就得要學習 ssh 這個功能了 (伺服器篇再來談)。 那麼你輸入帳號密碼後，系統幫你處理了什麼呢？

先找尋 /etc/passwd 裡面是否有你輸入的帳號？如果沒有則跳出，如果有的話則將該帳號對應的 UID 與 GID (在 /etc/group 中) 讀出來，另外，該帳號的家目錄與 shell 設定也一併讀出；

再來則是核對密碼表啦！這時 Linux 會進入 /etc/shadow 裡面找出對應的帳號與 UID，然後核對一下你剛剛輸入的密碼與裡頭的密碼是否相符？

如果一切都 OK 的話，就進入 Shell 控管的階段囉！
大致上的情況就像這樣，所以當你要登入你的 Linux 主機的時候，那個 /etc/passwd 與 /etc/shadow 就必須要讓系統讀取啦 (這也是很多攻擊者會將特殊帳號寫到 /etc/passwd 裡頭去的緣故)，所以呢，如果你要備份 Linux 的系統的帳號的話，那麼這兩個檔案就一定需要備份才行呦！

由上面的流程我們也知道，跟使用者帳號有關的有兩個非常重要的檔案，**一個是管理使用者 UID/GID 重要參數的 /etc/passwd ，一個則是專門管理密碼相關資料的 /etc/shadow 囉**！那這兩個檔案的內容就非常值得進行研究啦！ 底下我們會簡單的介紹這兩個檔案，詳細的說明可以參考 man 5 passwd 及 man 5 shadow (註1)。

#### /etc/passwd 檔案結構

這個檔案的構造是這樣的：每一行都代表一個帳號，有幾行就代表有幾個帳號在你的系統中！ 不過需要特別留意的是，裡頭很多帳號本來就是系統正常運作所必須要的，我們可以簡稱他為系統帳號， 例如 bin, daemon, adm, nobody 等等，這些帳號請不要隨意的殺掉他呢！這個檔案的內容有點像這樣：

```bash
kevin@Kevin-Laptop:~/os$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
irc:x:39:39:ircd:/run/ircd:/usr/sbin/nologin
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
systemd-network:x:100:102:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin
systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd:/usr/sbin/nologin
messagebus:x:102:105::/nonexistent:/usr/sbin/nologin
systemd-timesync:x:103:106:systemd Time Synchronization,,,:/run/systemd:/usr/sbin/nologin
syslog:x:104:111::/home/syslog:/usr/sbin/nologin
_apt:x:105:65534::/nonexistent:/usr/sbin/nologin
uuidd:x:106:112::/run/uuidd:/usr/sbin/nologin
tcpdump:x:107:113::/nonexistent:/usr/sbin/nologin
kevin:x:1000:1000:,,,:/home/kevin:/bin/bash
```

我們先來看一下每個 Linux 系統都會有的第一行，就是 root 這個系統管理員那一行好了， 你可以明顯的看出來，每一行使用『:』分隔開，共有七個咚咚，分別是：

```bash
root:x:0:0:root:/root:/bin/bash
kevin:x:1000:1000:,,,:/home/kevin:/bin/bash
```

**帳號名稱**：
就是帳號啦！用來提供給對數字不太敏感的人類使用來登入系統的！需要用來對應 UID 喔。例如 root 的 UID 對應就是 0 (第三欄位)；

**密碼**：
早期 Unix 系統的密碼就是放在這欄位上！但是因為這個檔案的特性是所有的程序都能夠讀取，這樣一來很容易造成密碼資料被竊取， 因此後來就將這個欄位的密碼資料給他改放到 /etc/shadow 中了。所以這裡你會看到一個『 x 』，呵呵！

**UID**：
這個就是使用者識別碼囉！通常 Linux 對於 UID 有幾個限制需要說給您瞭解一下：

|id 範圍|該 ID 使用者特性|
|---|---|
|0(系統管理員)|當 UID 是 0 時，代表這個帳號是『系統管理員』！ 所以當你要讓其他的帳號名稱也具有 root 的權限時，將該帳號的 UID 改為 0 即可。 這也就是說，一部系統上面的系統管理員不見得只有 root 喔！ 不過，很不建議有多個帳號的 UID 是 0 啦～容易讓系統管理員混亂！|
|1~999(系統帳號)|保留給系統使用的 ID，其實除了 0 之外，其他的 UID 權限與特性並沒有不一樣。預設 1000 以下的數字讓給系統作為保留帳號只是一個習慣。由於系統上面啟動的網路服務或背景服務希望使用較小的權限去運作，因此不希望使用 root 的身份去執行這些服務， 所以我們就得要提供這些運作中程式的擁有者帳號才行。這些系統帳號通常是不可登入的， 所以才會有我們在第十章提到的 /sbin/nologin 這個特殊的 shell 存在。根據系統帳號的由來，通常這類帳號又約略被區分為兩種： 1~200：由 distributions 自行建立的系統帳號；201~999：若使用者有系統帳號需求時，可以使用的帳號 UID。
|1000~60000(可登入帳號)|給一般使用者用的。事實上，目前的 linux 核心 (3.10.x 版)已經可以支援到 4294967295 (2^32-1) 這麼大的 UID 號碼喔！|

上面這樣說明可以瞭解了嗎？是的， UID 為 0 的時候，就是 root 呦！所以請特別留意一下你的 /etc/passwd 檔案！

**GID**：
這個與 /etc/group 有關！其實 /etc/group 的觀念與 /etc/passwd 差不多，只是他是用來規範群組名稱與 GID 的對應而已！

**使用者資訊說明欄**：
這個欄位基本上並沒有什麼重要用途，只是用來解釋這個帳號的意義而已！不過，如果您提供使用 finger 的功能時， 這個欄位可以提供很多的訊息呢！本章後面的 chfn 指令會來解釋這裡的說明。

**家目錄**：
這是使用者的家目錄，以上面為例， root 的家目錄在 /root ，所以當 root 登入之後，就會立刻跑到 /root 目錄裡頭啦！呵呵！ 如果你有個帳號的使用空間特別的大，你想要將該帳號的家目錄移動到其他的硬碟去該怎麼作？ 沒有錯！可以在這個欄位進行修改呦！預設的使用者家目錄在 /home/yourIDname

**Shell**：
我們在第十章 BASH 提到很多次，當使用者登入系統後就會取得一個 Shell 來與系統的核心溝通以進行使用者的操作任務。那為何預設 shell 會使用 bash 呢？就是在這個欄位指定的囉！ 這裡比較需要注意的是，有一個 shell 可以用來替代成讓帳號無法取得 shell 環境的登入動作！那就是 /sbin/nologin 這個東西！這也可以用來製作純 pop 郵件帳號者的資料呢！

#### /etc/shadow 檔案結構

我們知道很多程式的運作都與權限有關，而權限與 UID/GID 有關！因此各程式當然需要讀取 /etc/passwd 來瞭解不同帳號的權限。 因此 /etc/passwd 的權限需設定為 -rw-r--r-- 這樣的情況， 雖然早期的密碼也有加密過，但卻放置到 /etc/passwd 的第二個欄位上！這樣一來很容易被有心人士所竊取的， 加密過的密碼也能夠透過暴力破解法去 trial and error (試誤) 找出來！

因為這樣的關係，所以後來發展出將密碼移動到 /etc/shadow 這個檔案分隔開來的技術， 而且還加入很多的密碼限制參數在 /etc/shadow 裡頭呢！在這裡，我們先來瞭解一下這個檔案的構造吧！ 鳥哥的 /etc/shadow 檔案有點像這樣：

```bash
kevin@Kevin-Laptop:~/os$ sudo head -n 4 /etc/shadow
[sudo] password for kevin: 
root:*:19290:0:99999:7:::
daemon:*:19290:0:99999:7:::
bin:*:19290:0:99999:7:::
sys:*:19290:0:99999:7:::
```

基本上， shadow 同樣以『:』作為分隔符號，如果數一數，會發現共有九個欄位啊，這九個欄位的用途是這樣的：

**帳號名稱**：
由於密碼也需要與帳號對應啊～因此，這個檔案的第一欄就是帳號，必須要與 /etc/passwd 相同才行！

**密碼**   ：
這個欄位內的資料才是真正的密碼，而且是經過編碼的密碼 (加密) 啦！ 你只會看到有一些特殊符號的字母就是了！需要特別留意的是，雖然這些加密過的密碼很難被解出來， 但是『很難』不等於『不會』，所以，這個檔案的預設權限是『-rw-------』或者是『----------』，亦即只有 root 才可以讀寫就是了！你得隨時注意，不要不小心更動了這個檔案的權限呢！

另外，由於各種密碼編碼的技術不一樣，因此不同的編碼系統會造成這個欄位的長度不相同。 舉例來說，舊式的 DES, MD5 編碼系統產生的密碼長度就與目前慣用的 SHA 不同(註2)！SHA 的密碼長度明顯的比較長些。由於固定的編碼系統產生的密碼長度必須一致，因此『當你讓這個欄位的長度改變後，該密碼就會失效(算不出來)』。 很多軟體透過這個功能，在此欄位前加上 ! 或 * 改變密碼欄位長度，就會讓密碼『暫時失效』了。

**最近更動密碼的日期**：
這個欄位記錄了『更動密碼那一天』的日期，不過，很奇怪呀！在我的例子中怎麼會是 16559 呢？呵呵，這個是因為計算 Linux 日期的時間是以 1970 年 1 月 1 日作為 1 而累加的日期，1971 年 1 月 1 日則為 366 啦！ 得注意一下這個資料呦！上述的 16559 指的就是 2015-05-04 那一天啦！瞭解乎？ 而想要瞭解該日期可以使用本章後面 chage 指令的幫忙！至於想要知道某個日期的累積日數， 可使用如下的程式計算：

```bash
[root@study ~]# echo $(($(date --date="2015/05/04" +%s)/86400+1))
16559
```

上述指令中，2015/05/04 為你想要計算的日期，86400 為每一天的秒數， %s 為 1970/01/01 以來的累積總秒數。 由於 bash 僅支援整數，因此最終需要加上 1 補齊 1970/01/01 當天。

**密碼不可被更動的天數：(與第 3 欄位相比)**
第四個欄位記錄了：這個帳號的密碼在最近一次被更改後需要經過幾天才可以再被變更！如果是 0 的話， 表示密碼隨時可以更動的意思。這的限制是為了怕密碼被某些人一改再改而設計的！如果設定為 20 天的話，那麼當你設定了密碼之後， 20 天之內都無法改變這個密碼呦！

**密碼需要重新變更的天數：(與第 3 欄位相比)**
經常變更密碼是個好習慣！為了強制要求使用者變更密碼，這個欄位可以指定在最近一次更改密碼後， 在多少天數內需要再次的變更密碼才行。你必須要在這個天數內重新設定你的密碼，否則這個帳號的密碼將會『變為過期特性』。 而如果像上面的 99999 (計算為 273 年) 的話，那就表示，呵呵，密碼的變更沒有強制性之意。

**密碼需要變更期限前的警告天數：(與第 5 欄位相比)**
當帳號的密碼有效期限快要到的時候 (第 5 欄位)，系統會依據這個欄位的設定，發出『警告』言論給這個帳號，提醒他『再過 n 天你的密碼就要過期了，請盡快重新設定你的密碼呦！』，如上面的例子，則是密碼到期之前的 7 天之內，系統會警告該用戶。

**密碼過期後的帳號寬限時間(密碼失效日)：(與第 5 欄位相比)**
密碼有效日期為『更新日期(第3欄位)』+『重新變更日期(第5欄位)』，過了該期限後使用者依舊沒有更新密碼，那該密碼就算過期了。 雖然密碼過期但是該帳號還是可以用來進行其他工作的，包括登入系統取得 bash 。不過如果密碼過期了， 那當你登入系統時，系統會強制要求你必須要重新設定密碼才能登入繼續使用喔，這就是密碼過期特性。

那這個欄位的功能是什麼呢？是在密碼過期幾天後，如果使用者還是沒有登入更改密碼，那麼這個帳號的密碼將會『失效』， 亦即該帳號再也無法使用該密碼登入了。要注意密碼過期與密碼失效並不相同。

**帳號失效日期**：
這個日期跟第三個欄位一樣，都是使用 1970 年以來的總日數設定。這個欄位表示： 這個帳號在此欄位規定的日期之後，將無法再使用。 就是所謂的『帳號失效』，此時不論你的密碼是否有過期，這個『帳號』都不能再被使用！ 這個欄位會被使用通常應該是在『收費服務』的系統中，你可以規定一個日期讓該帳號不能再使用啦！

**保留**：
最後一個欄位是保留的，看以後有沒有新功能加入。
舉個例子來說好了，假如我的 dmtsai 這個使用者的密碼欄如下所示：

```bash
dmtsai:$6$M4IphgNP2TmlXaSS$B418YFroYxxmm....:16559:5:60:7:5:16679:
```

這表示什麼呢？先要注意的是 16559 是 2015/05/04 。所以 dmtsai 這個使用者的密碼相關意義是：

由於密碼幾乎僅能單向運算(由明碼計算成為密碼，無法由密碼反推回明碼)，因此由上表的資料我們無法得知 dmstai 的實際密碼明文 (第二個欄位)；

此帳號最近一次更動密碼的日期是 2015/05/04 (16559)；

能夠再次修改密碼的時間是 5 天以後，也就是 2015/05/09 以前 dmtsai 不能修改自己的密碼；如果使用者還是嘗試要更動自己的密碼，系統就會出現這樣的訊息：

```bash
You must wait longer to change your password
passwd: Authentication token manipulation error
```

畫面中告訴我們：你必須要等待更久的時間才能夠變更密碼之意啦！

由於密碼過期日期定義為 60 天後，亦即累積日數為： 16559+60=16619，經過計算得到此日數代表日期為 2015/07/03。 這表示：『使用者必須要在 2015/05/09 (前 5 天不能改) 到 2015/07/03 之間的 60 天限制內去修改自己的密碼，若 2015/07/03 之後還是沒有變更密碼時，該密碼就宣告為過期』了！

警告日期設為 7 天，亦即是密碼過期日前的 7 天，在本例中則代表 2015/06/26 ~ 2015/07/03 這七天。 如果使用者一直沒有更改密碼，那麼在這 7 天中，只要 dmtsai 登入系統就會發現如下的訊息：

```bash
Warning: your password will expire in 5 days
```

透過這樣的說明，您應該會比較容易理解了吧？由於 shadow 有這樣的重要性，因此可不能隨意修改喔！ 但在某些情況底下你得要使用各種方法來處理這個檔案的！舉例來說，常常聽到人家說：『我的密碼忘記了』， 或者是『我的密碼不曉得被誰改過，跟原先的不一樣了』，這個時候怎麼辦？

一般用戶的密碼忘記了：這個最容易解決，請系統管理員幫忙， 他會重新設定好你的密碼而不需要知道你的舊密碼！利用 root 的身份使用 passwd 指令來處理即可。

root 密碼忘記了：這就麻煩了！因為你無法使用 root 的身份登入了嘛！ 但我們知道 root 的密碼在 /etc/shadow 當中，因此你可以使用各種可行的方法開機進入 Linux 再去修改。 例如重新開機進入單人維護模式(第十九章)後，系統會主動的給予 root 權限的 bash 介面， 此時再以 passwd 修改密碼即可；或以 Live CD 開機後掛載根目錄去修改 /etc/shadow，將裡面的 root 的密碼欄位清空， 再重新開機後 root 將不用密碼即可登入！登入後再趕快以 passwd 指令去設定 root 密碼即可。

### 13.1.3 關於群組： 有效與初始群組、groups, newgrp

認識了帳號相關的兩個檔案 /etc/passwd 與 /etc/shadow 之後，你或許還是會覺得奇怪， 那麼群組的設定檔在哪裡？還有，在 /etc/passwd 的第四欄不是所謂的 GID 嗎？那又是啥？ 呵呵～此時就需要瞭解 /etc/group 與 /etc/gshadow 囉～

#### /etc/group 檔案結構

這個檔案就是在記錄 GID 與群組名稱的對應了～鳥哥測試機的 /etc/group 內容有點像這樣：

```bash
kevin@Kevin-Laptop:~/os$ head -n 4 /etc/group
root:x:0:
daemon:x:1:
bin:x:2:
sys:x:3:
```

這個檔案每一行代表一個群組，也是以冒號『:』作為欄位的分隔符號，共分為四欄，每一欄位的意義是：

**群組名稱**：
就是群組名稱啦！同樣用來給人類使用的，基本上需要與第三欄位的 GID 對應。

**群組密碼**：
通常不需要設定，這個設定通常是給『群組管理員』使用的，目前很少有這個機會設定群組管理員啦！ 同樣的，密碼已經移動到 /etc/gshadow 去，因此這個欄位只會存在一個『x』而已；

**GID**：
就是群組的 ID 啊。我們 /etc/passwd 第四個欄位使用的 GID 對應的群組名，就是由這裡對應出來的！

**此群組支援的帳號名稱**：
我們知道一個帳號可以加入多個群組，那某個帳號想要加入此群組時，將該帳號填入這個欄位即可。 舉例來說，如果我想要讓 dmtsai 與 alex 也加入 root 這個群組，那麼在第一行的最後面加上『dmtsai,alex』，注意不要有空格， 使成為『 root:x:0:dmtsai,alex 』就可以囉～
談完了 /etc/passwd, /etc/shadow, /etc/group 之後，我們可以使用一個簡單的圖示來瞭解一下 UID / GID 與密碼之間的關係， 圖示如下。其實重點是 /etc/passwd 啦，其他相關的資料都是根據這個檔案的欄位去找尋出來的。 下圖中， root 的 UID 是 0 ，而 GID 也是 0 ，去找 /etc/group 可以知道 GID 為 0 時的群組名稱就是 root 哩。 至於密碼的尋找中，會找到 /etc/shadow 與 /etc/passwd 內同帳號名稱的那一行，就是密碼相關資料囉。

<div align=center><img src="/os_note/account/images/centos7_id_link.jpg"></div>
<div align=center>圖13.1.1、帳號相關檔案之間的 UID/GID 與密碼相關性示意圖</div>

至於在 /etc/group 比較重要的特色在於第四欄啦，因為每個使用者都可以擁有多個支援的群組，這就好比在學校唸書的時候， 我們可以加入多個社團一樣！ ^_^。不過這裡你或許會覺得奇怪的，那就是：『假如我同時加入多個群組，那麼我在作業的時候，到底是以那個群組為準？』 底下我們就來談一談這個『有效群組』的概念。

>請注意，新版的 Linux 中，初始群組的用戶群已經不會加入在第四個欄位！例如我們知道 root 這個帳號的主要群組為 root，但是在上面的範例中， 你已經不會看到 root 這個『用戶』的名稱在 /etc/group 的 root 那一行的第四個欄位內囉！這點還請留意一下即可！

#### 有效群組(effective group)與初始群組(initial group)

還記得每個使用者在他的 /etc/passwd 裡面的第四欄有所謂的 GID 吧？那個 GID 就是所謂的『初始群組 (initial group) 』！也就是說，當使用者一登入系統，立刻就擁有這個群組的相關權限的意思。 舉例來說，我們上面提到 dmtsai 這個使用者的 /etc/passwd 與 /etc/group 還有 /etc/gshadow 相關的內容如下：

```bash
[root@study ~]# usermod -a -G users dmtsai  <==先設定好次要群組
[root@study ~]# grep dmtsai /etc/passwd /etc/group /etc/gshadow
/etc/passwd:dmtsai:x:1000:1000:dmtsai:/home/dmtsai:/bin/bash
/etc/group:wheel:x:10:dmtsai    <==次要群組的設定、安裝時指定的
/etc/group:users:x:100:dmtsai   <==次要群組的設定
/etc/group:dmtsai:x:1000:       <==因為是初始群組，所以第四欄位不需要填入帳號
/etc/gshadow:wheel:::dmtsai     <==次要群組的設定
/etc/gshadow:users:::dmtsai     <==次要群組的設定
/etc/gshadow:dmtsai:!!::

home-desktop@Desktop:~/os$ sudo grep home-desktop /etc/passwd /etc/group /etc/gshadow 
/etc/passwd:home-desktop:x:1000:1000:,,,:/home/home-desktop:/bin/bash
/etc/group:adm:x:4:syslog,home-desktop
/etc/group:dialout:x:20:home-desktop
/etc/group:cdrom:x:24:home-desktop
/etc/group:floppy:x:25:home-desktop
/etc/group:sudo:x:27:home-desktop
/etc/group:audio:x:29:home-desktop
/etc/group:dip:x:30:home-desktop
/etc/group:video:x:44:home-desktop
/etc/group:plugdev:x:46:home-desktop
/etc/group:users:x:100:home-desktop
/etc/group:netdev:x:116:home-desktop
/etc/group:home-desktop:x:1000:
/etc/gshadow:adm:*::syslog,home-desktop
/etc/gshadow:dialout:*::home-desktop
/etc/gshadow:cdrom:*::home-desktop
/etc/gshadow:floppy:*::home-desktop
/etc/gshadow:sudo:*::home-desktop
/etc/gshadow:audio:*::home-desktop
/etc/gshadow:dip:*::home-desktop
/etc/gshadow:video:*::home-desktop
/etc/gshadow:plugdev:*::home-desktop
/etc/gshadow:users:*::home-desktop
/etc/gshadow:netdev:!::home-desktop
/etc/gshadow:home-desktop:!::
```

仔細看到上面這個表格，在 /etc/passwd 裡面，dmtsai 這個使用者所屬的群組為 GID=1000 ，搜尋一下 /etc/group 得到 1000 是那個名為 dmtsai 的群組啦！這就是 initial group。因為是初始群組， 使用者一登入就會主動取得，不需要在 /etc/group 的第四個欄位寫入該帳號的！

但是非 initial group 的其他群組可就不同了。舉上面這個例子來說，我將 dmtsai 加入 users 這個群組當中，由於 users 這個群組並非是 dmtsai 的初始群組，因此， 我必須要在 /etc/group 這個檔案中，找到 users 那一行，並且將 dmtsai 這個帳號加入第四欄， 這樣 dmtsai 才能夠加入 users 這個群組啊。

那麼在這個例子當中，因為我的 dmtsai 帳號同時支援 dmtsai, wheel 與 users 這三個群組， 因此，在讀取/寫入/執行檔案時，針對群組部分，只要是 users, wheel 與 dmtsai 這三個群組擁有的功能， 我 dmtsai 這個使用者都能夠擁有喔！這樣瞭呼？不過，這是針對已經存在的檔案而言， 如果今天我要建立一個新的檔案或者是新的目錄，請問一下，新檔案的群組是 dmtsai, wheel 還是 users ？呵呵！這就得要檢查一下當時的有效群組了 (effective group)。

#### groups: 有效與支援群組的觀察

如果我以 dmtsai 這個使用者的身份登入後，該如何知道我所有支援的群組呢？ 很簡單啊，直接輸入 groups 就可以了！注意喔，是 groups 有加 s 呢！結果像這樣：

```bash
[dmtsai@study ~]$ groups
dmtsai wheel users
home-desktop@Desktop:~/os$ groups
home-desktop adm dialout cdrom floppy sudo audio dip video plugdev users netdev
```

在這個輸出的訊息中，可知道 dmtsai 這個用戶同時屬於 dmtsai, wheel 及 users 這三個群組，**而且， 第一個輸出的群組即為有效群組 (effective group) 了**。 也就是說，我的有效群組為 dmtsai 啦～此時，如果我以 touch 去建立一個新檔，例如： 『 touch test 』，那麼這個檔案的擁有者為 dmtsai ，而且群組也是 dmtsai 的啦。

在這個輸出的訊息中，可知道 dmtsai 這個用戶同時屬於 dmtsai, wheel 及 users 這三個群組，而且， 第一個輸出的群組即為有效群組 (effective group) 了。 也就是說，我的有效群組為 dmtsai 啦～此時，如果我以 touch 去建立一個新檔，例如： 『 touch test 』，那麼這個檔案的擁有者為 dmtsai ，而且群組也是 dmtsai 的啦。

```bash
[dmtsai@study ~]$ touch test
[dmtsai@study ~]$ ll test
-rw-rw-r--. 1 dmtsai dmtsai 0 Jul 20 19:54 test

home-desktop@Desktop:~/os/os_note/account$ touch test
home-desktop@Desktop:~/os/os_note/account$ ls
chapter13.md  images  test
home-desktop@Desktop:~/os/os_note/account$ file test
test: empty
home-desktop@Desktop:~/os/os_note/account$ ll test 
-rw-rw-r-- 1 home-desktop home-desktop 0 Dec  1 20:56 test
```

這樣是否可以瞭解什麼是有效群組了？通常有效群組的作用是在新建檔案啦！那麼有效群組是否能夠變換？

#### newgrp: 有效群組的切換

那麼如何變更有效群組呢？就使用 newgrp 啊！不過使用 newgrp 是有限制的，那就是你想要切換的群組必須是你已經有支援的群組。舉例來說， dmtsai 可以在 dmtsai/wheel/users 這三個群組間切換有效群組，但是 dmtsai 無法切換有效群組成為 sshd 啦！使用的方式如下：

```bash
[dmtsai@study ~]$ newgrp users
[dmtsai@study ~]$ groups
users wheel dmtsai
[dmtsai@study ~]$ touch test2
[dmtsai@study ~]$ ll test*
-rw-rw-r--. 1 dmtsai dmtsai 0 Jul 20 19:54 test
-rw-r--r--. 1 dmtsai users  0 Jul 20 19:56 test2
[dmtsai@study ~]$ exit   # 注意！記得離開 newgrp 的環境喔！
```

此時，dmtsai 的有效群組就成為 users 了。我們額外的來討論一下 newgrp 這個指令，這個指令可以變更目前使用者的有效群組， 而且是另外以一個 shell 來提供這個功能的喔，所以，以上面的例子來說， dmtsai 這個使用者目前是以另一個 shell 登入的，而且新的 shell 給予 dmtsai 有效 GID 為 users 就是了。如果以圖示來看就是如下所示：

<div align=center><img src="/os_note/account/images/newgrp.gif"></div>
<div align=center>圖13.1.2、newgrp 的運作示意圖</div>

雖然使用者的環境設定(例如環境變數等等其他資料)不會有影響，但是使用者的『群組權限』將會重新被計算。 但是需要注意，由於是新取得一個 shell ，因此如果你想要回到原本的環境中，請輸入 exit 回到原本的 shell 喔！

既然如此，也就是說，只要我的用戶有支援的群組就是能夠切換成為有效群組！好了， 那麼如何讓一個帳號加入不同的群組就是問題的所在囉。你要加入一個群組有兩個方式，一個是透過系統管理員 (root) 利用 usermod 幫你加入，如果 root 太忙了而且你的系統有設定群組管理員，那麼你可以透過群組管理員以 gpasswd 幫你加入他所管理的群組中！詳細的作法留待下一小節再來介紹囉！

#### /etc/gshadow

剛剛講了很多關於『有效群組』的概念，另外，也提到 newgrp 這個指令的用法，但是，如果 /etc/gshadow 這個設定沒有搞懂得話，那麼 newgrp 是無法動作的呢！ 鳥哥測試機的 /etc/gshadow 的內容有點像這樣：

```bash
[root@study ~]# head -n 4 /etc/gshadow
root:::
bin:::
daemon:::
sys:::
```

這個檔案內同樣還是使用冒號『:』來作為欄位的分隔字元，而且你會發現，這個檔案幾乎與 /etc/group 一模一樣啊！是這樣沒錯～不過，要注意的大概就是第二個欄位吧～第二個欄位是密碼欄， 如果密碼欄上面是『!』或空的時，表示該群組不具有群組管理員！至於第四個欄位也就是支援的帳號名稱囉～ 這四個欄位的意義為：

群組名稱
密碼欄，同樣的，開頭為 ! 表示無合法密碼，所以無群組管理員
群組管理員的帳號 (相關資訊在 gpasswd 中介紹)
有加入該群組支援的所屬帳號 (與 /etc/group 內容相同！)
以系統管理員的角度來說，這個 gshadow 最大的功能就是建立群組管理員啦！ 那麼什麼是群組管理員呢？由於系統上面的帳號可能會很多，但是我們 root 可能平時太忙碌，所以當有使用者想要加入某些群組時， root 或許會沒有空管理。此時如果能夠建立群組管理員的話，那麼該群組管理員就能夠將那個帳號加入自己管理的群組中！ 可以免去 root 的忙碌啦！不過，由於目前有類似 sudo 之類的工具， 所以這個群組管理員的功能已經很少使用了。我們會在後續的 gpasswd 中介紹這個實作。

## 13.2 帳號管理

好啦！既然要管理帳號，當然是由新增與移除使用者開始的囉～底下我們就分別來談一談如何新增、 移除與更改使用者的相關資訊吧～

### 13.2.1 新增與移除使用者： useradd, 相關設定檔, passwd, usermod, userdel

要如何在 Linux 的系統新增一個使用者啊？呵呵～真是太簡單了～我們登入系統時會輸入 (1)帳號與 (2)密碼， 所以建立一個可用的帳號同樣的也需要這兩個資料。那帳號可以使用 useradd 來新建使用者，密碼的給予則使用 passwd 這個指令！這兩個指令下達方法如下：

#### useradd

```bash
[root@study ~]# useradd [-u UID] [-g 初始群組] [-G 次要群組] [-mM]\
>  [-c 說明欄] [-d 家目錄絕對路徑] [-s shell] 使用者帳號名
選項與參數：
-u  ：後面接的是 UID ，是一組數字。直接指定一個特定的 UID 給這個帳號；
-g  ：後面接的那個群組名稱就是我們上面提到的 initial group 啦～
      該群組的 GID 會被放置到 /etc/passwd 的第四個欄位內。
-G  ：後面接的群組名稱則是這個帳號還可以加入的群組。
      這個選項與參數會修改 /etc/group 內的相關資料喔！
-M  ：強制！不要建立使用者家目錄！(系統帳號預設值)
-m  ：強制！要建立使用者家目錄！(一般帳號預設值)
-c  ：這個就是 /etc/passwd 的第五欄的說明內容啦～可以隨便我們設定的啦～
-d  ：指定某個目錄成為家目錄，而不要使用預設值。務必使用絕對路徑！
-r  ：建立一個系統的帳號，這個帳號的 UID 會有限制 (參考 /etc/login.defs)
-s  ：後面接一個 shell ，若沒有指定則預設是 /bin/bash 的啦～
-e  ：後面接一個日期，格式為『YYYY-MM-DD』此項目可寫入 shadow 第八欄位，
      亦即帳號失效日的設定項目囉；
-f  ：後面接 shadow 的第七欄位項目，指定密碼是否會失效。0為立刻失效，
      -1 為永遠不失效(密碼只會過期而強制於登入時重新設定而已。)

範例一：完全參考預設值建立一個使用者，名稱為 vbird1
[root@study ~]# useradd vbird1
[root@study ~]# ll -d /home/vbird1
drwx------. 3 vbird1 vbird1 74 Jul 20 21:50 /home/vbird1
# 預設會建立使用者家目錄，且權限為 700 ！這是重點！

[root@study ~]# grep vbird1 /etc/passwd /etc/shadow /etc/group
/etc/passwd:vbird1:x:1003:1004::/home/vbird1:/bin/bash
/etc/shadow:vbird1:!!:16636:0:99999:7:::
/etc/group:vbird1:x:1004:     <==預設會建立一個與帳號一模一樣的群組名

home-desktop@Desktop:~$ sudo useradd kevin
[sudo] password for home-desktop: 
home-desktop@Desktop:~$ grep kevin /etc/passwd
kevin:x:1001:1001::/home/kevin:/bin/sh
```

其實系統已經幫我們規定好非常多的預設值了，所以我們可以簡單的使用『 useradd 帳號 』來建立使用者即可。 CentOS 這些預設值主要會幫我們處理幾個項目：

在 /etc/passwd 裡面建立一行與帳號相關的資料，包括建立 UID/GID/家目錄等；
在 /etc/shadow 裡面將此帳號的密碼相關參數填入，但是尚未有密碼；
在 /etc/group 裡面加入一個與帳號名稱一模一樣的群組名稱；
在 /home 底下建立一個與帳號同名的目錄作為使用者家目錄，且權限為 700
由於在 /etc/shadow 內僅會有密碼參數而不會有加密過的密碼資料，因此我們在建立使用者帳號時， 還需要使用『 passwd 帳號 』來給予密碼才算是完成了使用者建立的流程。如果由於特殊需求而需要改變使用者相關參數時， 就得要透過上述表格中的選項來進行建立了，參考底下的案例：

```bash
範例二：假設我已知道我的系統當中有個群組名稱為 users ，且 UID 1500 並不存在，
        請用 users 為初始群組，以及 uid 為 1500 來建立一個名為 vbird2 的帳號
[root@study ~]# useradd -u 1500 -g users vbird2
[root@study ~]# ll -d /home/vbird2
drwx------. 3 vbird2 users 74 Jul 20 21:52 /home/vbird2

[root@study ~]# grep vbird2 /etc/passwd /etc/shadow /etc/group
/etc/passwd:vbird2:x:1500:100::/home/vbird2:/bin/bash
/etc/shadow:vbird2:!!:16636:0:99999:7:::
# 看一下，UID 與 initial group 確實改變成我們需要的了！
```

在這個範例中，我們建立的是指定一個已經存在的群組作為使用者的初始群組，因為群組已經存在， 所以在 /etc/group 裡面就不會主動的建立與帳號同名的群組了！ 此外，我們也指定了特殊的 UID 來作為使用者的專屬 UID 喔！瞭解了一般帳號後，我們來瞧瞧那啥是系統帳號 (system account) 吧！

```bash
範例三：建立一個系統帳號，名稱為 vbird3
[root@study ~]# useradd -r vbird3
[root@study ~]# ll -d /home/vbird3
ls: cannot access /home/vbird3: No such file or directorya   <==不會主動建立家目錄

[root@study ~]# grep vbird3 /etc/passwd /etc/shadow /etc/group
/etc/passwd:vbird3:x:699:699::/home/vbird3:/bin/bash
/etc/shadow:vbird3:!!:16636::::::
/etc/group:vbird3:x:699:
```

我們在談到 UID 的時候曾經說過一般帳號應該是 1000 號以後，那使用者自己建立的系統帳號則一般是小於 1000 號以下的。 所以在這裡我們加上 -r 這個選項以後，系統就會主動將帳號與帳號同名群組的 UID/GID 都指定小於 1000 以下， 在本案例中則是使用 699(UID) 與 699(GID) 囉！此外，**由於系統帳號主要是用來進行運作系統所需服務的權限設定， 所以系統帳號預設都不會主動建立家目錄的**！

由這幾個範例我們也會知道，使用 useradd 建立使用者帳號時，其實會更改不少地方，至少我們就知道底下幾個檔案：

使用者帳號與密碼參數方面的檔案：/etc/passwd, /etc/shadow
使用者群組相關方面的檔案：/etc/group, /etc/gshadow
使用者的家目錄：/home/帳號名稱
那請教一下，你有沒有想過，為何『 useradd vbird1 』會主動在 /home/vbird1 建立起使用者的家目錄？家目錄內有什麼資料且來自哪裡？為何預設使用的是 /bin/bash 這個 shell ？為何密碼欄位已經都規範好了 (0:99999:7 那一串)？呵呵！這就得要說明一下 useradd 所使用的參考檔案囉！

#### useradd 參考檔

其實 useradd 的預設值可以使用底下的方法呼叫出來：

```bash
[root@study ~]# useradd -D
GROUP=100		<==預設的群組
HOME=/home		<==預設的家目錄所在目錄
INACTIVE=-1		<==密碼失效日，在 shadow 內的第 7 欄
EXPIRE=			<==帳號失效日，在 shadow 內的第 8 欄
SHELL=/bin/bash		<==預設的 shell
SKEL=/etc/skel		<==使用者家目錄的內容資料參考目錄
CREATE_MAIL_SPOOL=yes   <==是否主動幫使用者建立郵件信箱(mailbox)
```

這個資料其實是由 /etc/default/useradd 呼叫出來的！你可以自行用 vim 去觀察該檔案的內容。搭配上頭剛剛談過的範例一的運作結果，上面這些設定項目所造成的行為分別是：

**GROUP=100：新建帳號的初始群組使用 GID 為 100 者**
系統上面 GID 為 100 者即是 users 這個群組，此設定項目指的就是讓新設使用者帳號的初始群組為 users 這一個的意思。 但是我們知道 CentOS 上面並不是這樣的，在 CentOS 上面預設的群組為與帳號名相同的群組。 舉例來說， vbird1 的初始群組為 vbird1 。怎麼會這樣啊？這是因為針對群組的角度有兩種不同的機制所致， 這兩種機制分別是：

私有群組機制：
系統會建立一個與帳號一樣的群組給使用者作為初始群組。 這種群組的設定機制會比較有保密性，這是因為使用者都有自己的群組，而且家目錄權限將會設定為 700 (僅有自己可進入自己的家目錄) 之故。使用這種機制將不會參考 GROUP=100 這個設定值。代表性的 distributions 有 RHEL, Fedora, CentOS 等；

公共群組機制：
就是以 GROUP=100 這個設定值作為新建帳號的初始群組，因此每個帳號都屬於 users 這個群組， 且預設家目錄通常的權限會是『 drwxr-xr-x ... username users ... 』，由於每個帳號都屬於 users 群組，因此大家都可以互相分享家目錄內的資料之故。代表 distributions 如 SuSE等。

由於我們的 CentOS 使用私有群組機制，因此這個設定項目是不會生效的！不要太緊張啊！

**HOME=/home：使用者家目錄的基準目錄(basedir)**
使用者的家目錄通常是與帳號同名的目錄，這個目錄將會擺放在此設定值的目錄後。所以 vbird1 的家目錄就會在 /home/vbird1/ 了！很容易理解吧！

**INACTIVE=-1：密碼過期後是否會失效的設定值**
我們在 shadow 檔案結構當中談過，第七個欄位的設定值將會影響到密碼過期後， 在多久時間內還可使用舊密碼登入。這個項目就是在指定該日數啦！**如果是 0 代表密碼過期立刻失效， 如果是 -1 則是代表密碼永遠不會失效，如果是數字，如 30 ，則代表過期 30 天後才失效**。

EXPIRE=：帳號失效的日期
就是 shadow 內的第八欄位，你可以直接設定帳號在哪個日期後就直接失效，而不理會密碼的問題。 通常不會設定此項目，但如果是付費的會員制系統，或許這個欄位可以設定喔！

SHELL=/bin/bash：預設使用的 shell 程式檔名
系統預設的 shell 就寫在這裡。假如你的系統為 mail server ，你希望每個帳號都只能使用 email 的收發信件功能， 而不許使用者登入系統取得 shell ，那麼可以將這裡設定為 /sbin/nologin ，如此一來，新建的使用者預設就無法登入！ 也免去後續使用 usermod 進行修改的手續！

SKEL=/etc/skel：使用者家目錄參考基準目錄
這個咚咚就是指定使用者家目錄的參考基準目錄囉～舉我們的範例一為例， vbird1 家目錄 /home/vbird1 內的各項資料，都是由 /etc/skel 所複製過去的～所以呢，未來如果我想要讓新增使用者時，該使用者的環境變數 ~/.bashrc 就設定妥當的話，您可以到 /etc/skel/.bashrc 去編輯一下，也可以建立 /etc/skel/www 這個目錄，那麼未來新增使用者後，在他的家目錄下就會有 www 那個目錄了！這樣瞭呼？

CREATE_MAIL_SPOOL=yes：建立使用者的 mailbox
你可以使用『 ll /var/spool/mail/vbird1 』看一下，會發現有這個檔案的存在喔！這就是使用者的郵件信箱！

除了這些基本的帳號設定值之外， UID/GID 還有密碼參數又是在哪裡參考的呢？那就得要看一下 /etc/login.defs 啦！ 這個檔案的內容有點像底下這樣：

```bash
MAIL_DIR        /var/spool/mail  <==使用者預設郵件信箱放置目錄

PASS_MAX_DAYS   99999    <==/etc/shadow 內的第 5 欄，多久需變更密碼日數
PASS_MIN_DAYS   0        <==/etc/shadow 內的第 4 欄，多久不可重新設定密碼日數
PASS_MIN_LEN    5        <==密碼最短的字元長度，已被 pam 模組取代，失去效用！
PASS_WARN_AGE   7        <==/etc/shadow 內的第 6 欄，過期前會警告的日數

UID_MIN          1000    <==使用者最小的 UID，意即小於 1000 的 UID 為系統保留
UID_MAX         60000    <==使用者能夠用的最大 UID
SYS_UID_MIN       201    <==保留給使用者自行設定的系統帳號最小值 UID
SYS_UID_MAX       999    <==保留給使用者自行設定的系統帳號最大值 UID
GID_MIN          1000    <==使用者自訂群組的最小 GID，小於 1000 為系統保留
GID_MAX         60000    <==使用者自訂群組的最大 GID
SYS_GID_MIN       201    <==保留給使用者自行設定的系統帳號最小值 GID
SYS_GID_MAX       999    <==保留給使用者自行設定的系統帳號最大值 GID

CREATE_HOME     yes      <==在不加 -M 及 -m 時，是否主動建立使用者家目錄？
UMASK           077      <==使用者家目錄建立的 umask ，因此權限會是 700
USERGROUPS_ENAB yes      <==使用 userdel 刪除時，是否會刪除初始群組
ENCRYPT_METHOD SHA512    <==密碼加密的機制使用的是 sha512 這一個機制！
```

這個檔案規範的資料則是如下所示：

mailbox 所在目錄：
使用者的預設 mailbox 檔案放置的目錄在 /var/spool/mail，所以 vbird1 的 mailbox 就是在 /var/spool/mail/vbird1 囉！

shadow 密碼第 4, 5, 6 欄位內容：
透過 PASS_MAX_DAYS 等等設定值來指定的！所以你知道為何預設的 /etc/shadow 內每一行都會有『 0:99999:7 』的存在了嗎？^_^！不過要注意的是，由於目前我們登入時改用 PAM 模組來進行密碼檢驗，所以那個 PASS_MIN_LEN 是失效的！

UID/GID 指定數值：
雖然 Linux 核心支援的帳號可高達 232 這麼多個，不過一部主機要作出這麼多帳號在管理上也是很麻煩的！ 所以在這裡就針對 UID/GID 的範圍進行規範就是了。上表中的 UID_MIN 指的就是可登入系統的一般帳號的最小 UID ，至於 UID_MAX 則是最大 UID 之意。

要注意的是，系統給予一個帳號 UID 時，他是 (1)先參考 UID_MIN 設定值取得最小數值； (2)由 /etc/passwd 搜尋最大的 UID 數值， 將 (1) 與 (2) 相比，找出最大的那個再加一就是新帳號的 UID 了。我們上面已經作出 UID 為 1500 的 vbird2 ， 如果再使用『 useradd vbird4 』時，你猜 vbird4 的 UID 會是多少？答案是： 1501 。 所以中間的 1004~1499 的號碼就空下來啦！

而如果我是想要建立系統用的帳號，所以使用 useradd -r sysaccount 這個 -r 的選項時，就會找『比 201 大但比 1000 小的最大的 UID 』就是了。 ^_^

使用者家目錄設定值：
為何我們系統預設會幫使用者建立家目錄？就是這個『CREATE_HOME = yes』的設定值啦！這個設定值會讓你在使用 useradd 時， 主動加入『 -m 』這個產生家目錄的選項啊！如果不想要建立使用者家目錄，就只能強制加上『 -M 』的選項在 useradd 指令執行時啦！至於建立家目錄的權限設定呢？就透過 umask 這個設定值啊！因為是 077 的預設設定，因此使用者家目錄預設權限才會是『 drwx------ 』哩！

使用者刪除與密碼設定值：
使用『USERGROUPS_ENAB yes』這個設定值的功能是： 如果使用 userdel 去刪除一個帳號時，且該帳號所屬的初始群組已經沒有人隸屬於該群組了， 那麼就刪除掉該群組，舉例來說，我們剛剛有建立 vbird4 這個帳號，他會主動建立 vbird4 這個群組。 若 vbird4 這個群組並沒有其他帳號將他加入支援的情況下，若使用 userdel vbird4 時，該群組也會被刪除的意思。 至於『ENCRYPT_METHOD SHA512』則表示使用 SHA512 來加密密碼明文，而不使用舊式的 MD5(註2) 。
現在你知道啦，使用 useradd 這支程式在建立 Linux 上的帳號時，至少會參考：

/etc/default/useradd
/etc/login.defs
/etc/skel/*
這些檔案，不過，最重要的其實是建立 /etc/passwd, /etc/shadow, /etc/group, /etc/gshadow 還有使用者家目錄就是了～所以，如果你瞭解整個系統運作的狀態，也是可以手動直接修改這幾個檔案就是了。 OK！帳號建立了，接下來處理一下使用者的密碼吧！

#### passwd

剛剛我們講到了，使用 useradd 建立了帳號之後，在預設的情況下，該帳號是暫時被封鎖的， 也就是說，該帳號是無法登入的，你可以去瞧一瞧 /etc/shadow 內的第二個欄位就曉得囉～ 那該如何是好？怕什麼？直接給他設定新密碼就好了嘛！對吧～設定密碼就使用 passwd 囉！

```bash
[root@study ~]# passwd [--stdin] [帳號名稱]  <==所有人均可使用來改自己的密碼
[root@study ~]# passwd [-l] [-u] [--stdin] [-S] \
>  [-n 日數] [-x 日數] [-w 日數] [-i 日數] 帳號 <==root 功能
選項與參數：
--stdin ：可以透過來自前一個管線的資料，作為密碼輸入，對 shell script 有幫助！
-l  ：是 Lock 的意思，會將 /etc/shadow 第二欄最前面加上 ! 使密碼失效；
-u  ：與 -l 相對，是 Unlock 的意思！
-S  ：列出密碼相關參數，亦即 shadow 檔案內的大部分資訊。
-n  ：後面接天數，shadow 的第 4 欄位，多久不可修改密碼天數
-x  ：後面接天數，shadow 的第 5 欄位，多久內必須要更動密碼
-w  ：後面接天數，shadow 的第 6 欄位，密碼過期前的警告天數
-i  ：後面接天數，shadow 的第 7 欄位，密碼失效天數

範例一：請 root 給予 vbird2 密碼
[root@study ~]# passwd vbird2
Changing password for user vbird2.
New UNIX password: <==這裡直接輸入新的密碼，螢幕不會有任何反應
BAD PASSWORD: The password is shorter than 8 characters <==密碼太簡單或過短的錯誤！
Retype new UNIX password:  <==再輸入一次同樣的密碼
passwd: all authentication tokens updated successfully.  <==竟然還是成功修改了！

home-desktop@Desktop:~$ sudo passwd kevin
New password: 
Retype new password: 
passwd: password updated successfully
```

root 果然是最偉大的人物！當我們要給予使用者密碼時，透過 root 來設定即可。 root 可以設定各式各樣的密碼，系統幾乎一定會接受！所以您瞧瞧，如同上面的範例一，明明鳥哥輸入的密碼太短了， 但是系統依舊可接受 vbird2 這樣的密碼設定。這個是 root 幫忙設定的結果，那如果是使用者自己要改密碼呢？ 包括 root 也是這樣修改的喔！

```bash
範例二：用 vbird2 登入後，修改 vbird2 自己的密碼
[vbird2@study ~]$ passwd   <==後面沒有加帳號，就是改自己的密碼！
Changing password for user vbird2.
Changing password for vbird2
(current) UNIX password: <==這裡輸入『原有的舊密碼』
New UNIX password: <==這裡輸入新密碼
BAD PASSWORD: The password is shorter than 8 characters <==密碼太短！不可以設定！重新想
New password:  <==這裡輸入新想的密碼
BAD PASSWORD: The password fails the dictionary check - it is based on a dictionary word
# 同樣的，密碼設定在字典裡面找的到該字串，所以也是不建議！無法通過，再想新的！
New UNIX password: <==這裡再想個新的密碼來輸入吧
Retype new UNIX password: <==通過密碼驗證！所以重複這個密碼的輸入
passwd: all authentication tokens updated successfully. <==有無成功看關鍵字
```

passwd 的使用真的要很注意，尤其是 root 先生啊！鳥哥在課堂上每次講到這裡，說是要幫自己的一般帳號建立密碼時， 有一小部分的學生就是會忘記加上帳號，結果就變成改變 root 自己的密碼，最後.... root 密碼就這樣不見去！唉～ 要幫一般帳號建立密碼需要使用『 passwd 帳號 』的格式，使用『 passwd 』表示修改自己的密碼！拜託！千萬不要改錯！

與 root 不同的是，一般帳號在更改密碼時需要先輸入自己的舊密碼 (亦即 current 那一行)，然後再輸入新密碼 (New 那一行)。 要注意的是，密碼的規範是非常嚴格的，尤其新的 distributions 大多使用 PAM 模組來進行密碼的檢驗，包括太短、 密碼與帳號相同、密碼為字典常見字串等，都會被 PAM 模組檢查出來而拒絕修改密碼，此時會再重複出現『 New 』這個關鍵字！ 那時請再想個新密碼！若出現『 Retype 』才是你的密碼被接受了！重複輸入新密碼並且看到『 successfully 』這個關鍵字時才是修改密碼成功喔！

為何使用者要設訂自己的密碼會這麼麻煩啊？這是因為密碼的安全性啦！如果密碼設定太簡單， 一些有心人士就能夠很簡單的猜到你的密碼，如此一來人家就可能使用你的一般帳號登入你的主機或使用其他主機資源， 對主機的維護會造成困擾的！所以新的 distributions 是使用較嚴格的 PAM 模組來管理密碼，這個管理的機制寫在 /etc/pam.d/passwd 當中。而該檔案與密碼有關的測試模組就是使用：pam_cracklib.so，這個模組會檢驗密碼相關的資訊， 並且取代 /etc/login.defs 內的 PASS_MIN_LEN 的設定啦！關於 PAM 我們在本章後面繼續介紹，這裡先談一下， 理論上，你的密碼最好符合如下要求：

密碼不能與帳號相同；
密碼盡量不要選用字典裡面會出現的字串；
密碼需要超過 8 個字元；
密碼不要使用個人資訊，如身份證、手機號碼、其他電話號碼等；
密碼不要使用簡單的關係式，如 1+1=2， Iamvbird 等；
密碼盡量使用大小寫字元、數字、特殊字元($,_,-等)的組合。
為了方便系統管理，新版的 passwd 還加入了很多創意選項喔！鳥哥個人認為最好用的大概就是這個『 --stdin 』了！ 舉例來說，你想要幫 vbird2 變更密碼成為 abc543CC ，可以這樣下達指令呢！

```bash
範例三：使用 standard input 建立用戶的密碼
[root@study ~]# echo "abc543CC" | passwd --stdin vbird2
Changing password for user vbird2.
passwd: all authentication tokens updated successfully.
```

#### chage

除了使用 passwd -S 之外，有沒有更詳細的密碼參數顯示功能呢？有的！那就是 chage 了！他的用法如下：

```bash
[root@study ~]# chage [-ldEImMW] 帳號名
選項與參數：
-l ：列出該帳號的詳細密碼參數；
-d ：後面接日期，修改 shadow 第三欄位(最近一次更改密碼的日期)，格式 YYYY-MM-DD
-E ：後面接日期，修改 shadow 第八欄位(帳號失效日)，格式 YYYY-MM-DD
-I ：後面接天數，修改 shadow 第七欄位(密碼失效日期)
-m ：後面接天數，修改 shadow 第四欄位(密碼最短保留天數)
-M ：後面接天數，修改 shadow 第五欄位(密碼多久需要進行變更)
-W ：後面接天數，修改 shadow 第六欄位(密碼過期前警告日期)

範例一：列出 vbird2 的詳細密碼參數
[root@study ~]# chage -l vbird2
Last password change                                    : Jul 20, 2015
Password expires                                        : Sep 18, 2015
Password inactive                                       : Sep 28, 2015
Account expires                                         : never
Minimum number of days between password change          : 0
Maximum number of days between password change          : 60
Number of days of warning before password expires       : 7

home-desktop@Desktop:~$ chage -l home-desktop
Last password change                                    : Nov 18, 2022
Password expires                                        : never
Password inactive                                       : never
Account expires                                         : never
Minimum number of days between password change          : 0
Maximum number of days between password change          : 99999
Number of days of warning before password expires       : 7
```

我們在 passwd 的介紹中談到了處理 vbird2 這個帳號的密碼屬性流程，使用 passwd -S 卻無法看到很清楚的說明。如果使用 chage 那可就明白多了！如上表所示，我們可以清楚的知道 vbird2 的詳細參數呢！ 如果想要修改其他的設定值，就自己參考上面的選項，或者自行 man chage 一下吧！^_^

chage 有一個功能很不錯喔！如果你想要讓『使用者在第一次登入時， 強制她們一定要更改密碼後才能夠使用系統資源』，可以利用如下的方法來處理的！

#### usermod

所謂這『人有失手，馬有亂蹄』，您說是吧？所以囉，當然有的時候會『不小心手滑了一下』在 useradd 的時候加入了錯誤的設定資料。或者是，在使用 useradd 後，發現某些地方還可以進行細部修改。 此時，當然我們可以直接到 /etc/passwd

```bash
[root@study ~]# usermod [-cdegGlsuLU] username
選項與參數：
-c  ：後面接帳號的說明，即 /etc/passwd 第五欄的說明欄，可以加入一些帳號的說明。
-d  ：後面接帳號的家目錄，即修改 /etc/passwd 的第六欄；
-e  ：後面接日期，格式是 YYYY-MM-DD 也就是在 /etc/shadow 內的第八個欄位資料啦！
-f  ：後面接天數，為 shadow 的第七欄位。
-g  ：後面接初始群組，修改 /etc/passwd 的第四個欄位，亦即是 GID 的欄位！
-G  ：後面接次要群組，修改這個使用者能夠支援的群組，修改的是 /etc/group 囉～
-a  ：與 -G 合用，可『增加次要群組的支援』而非『設定』喔！
-l  ：後面接帳號名稱。亦即是修改帳號名稱， /etc/passwd 的第一欄！
-s  ：後面接 Shell 的實際檔案，例如 /bin/bash 或 /bin/csh 等等。
-u  ：後面接 UID 數字啦！即 /etc/passwd 第三欄的資料；
-L  ：暫時將使用者的密碼凍結，讓他無法登入。其實僅改 /etc/shadow 的密碼欄。
-U  ：將 /etc/shadow 密碼欄的 ! 拿掉，解凍啦！
```

#### userdel

這個功能就太簡單了，目的在刪除使用者的相關資料，而使用者的資料有：

使用者帳號/密碼相關參數：/etc/passwd, /etc/shadow
使用者群組相關參數：/etc/group, /etc/gshadow
使用者個人檔案資料： /home/username, /var/spool/mail/username..
整個指令的語法非常簡單：

```bash
[root@study ~]# userdel [-r] username
選項與參數：
-r  ：連同使用者的家目錄也一起刪除

範例一：刪除 vbird2 ，連同家目錄一起刪除
[root@study ~]# userdel -r vbird2
```

這個指令下達的時候要小心了！通常我們要移除一個帳號的時候，你可以手動的將 /etc/passwd 與 /etc/shadow 裡頭的該帳號取消即可！一般而言，如果該帳號只是『暫時不啟用』的話，那麼將 /etc/shadow 裡頭帳號失效日期 (第八欄位) 設定為 0 就可以讓該帳號無法使用，但是所有跟該帳號相關的資料都會留下來！ 使用 userdel 的時機通常是『你真的確定不要讓該用戶在主機上面使用任何資料了！』

另外，其實使用者如果在系統上面操作過一陣子了，那麼該使用者其實在系統內可能會含有其他檔案的。 舉例來說，他的郵件信箱 (mailbox) 或者是例行性工作排程 (crontab, 十五章) 之類的檔案。 所以，如果想要完整的將某個帳號完整的移除，最好可以在下達 userdel -r username 之前， 先以『 find / -user username 』查出整個系統內屬於 username 的檔案，然後再加以刪除吧！

### 13.2.2 使用者功能

不論是 useradd/usermod/userdel ，那都是系統管理員所能夠使用的指令， 如果我是一般身份使用者，那麼我是否除了密碼之外，就無法更改其他的資料呢？ 當然不是啦！這裡我們介紹幾個一般身份使用者常用的帳號資料變更與查詢指令囉！

#### id

id 這個指令則可以查詢某人或自己的相關 UID/GID 等等的資訊，他的參數也不少，不過，都不需要記～反正使用 id 就全部都列出囉！ 另外，也回想一下，我們在前一章談到的迴圈時，就有用過這個指令喔！ ^_^

```bash
[root@study ~]# id [username]

範例一：查閱 root 自己的相關 ID 資訊！
[root@study ~]# id
uid=0(root) gid=0(root) groups=0(root) context=unconfined_u:unconfined_r:unconfined_t:
s0-s0:c0.c1023
# 上面資訊其實是同一行的資料！包括會顯示 UID/GID 以及支援的所有群組！
# 至於後面那個 context=... 則是 SELinux 的內容，先不要理會他！
home-desktop@Desktop:~/os$ id home-desktop
uid=1000(home-desktop) gid=1000(home-desktop) groups=1000(home-desktop),4(adm),20(dialout),24(cdrom),25(floppy),27(sudo),29(audio),30(dip),44(video),46(plugdev),100(users),116(netdev)
```

#### finger

finger 的中文字面意義是：『手指』或者是『指紋』的意思。這個 finger 可以查閱很多使用者相關的資訊喔！ 大部分都是在 /etc/passwd 這個檔案裡面的資訊啦！不過，這個指令有點危險，所以新的版本中已經預設不安裝這個軟體！ 好啦！現在繼續來安裝軟體先～記得第九章 dos2unix 的安裝方式！ 假設你已經將光碟機或光碟映像檔掛載在 /mnt 底下了，所以：

```bash
home-desktop@Desktop:~/os$ finger home-desktop
Login: home-desktop                     Name: 
Directory: /home/home-desktop           Shell: /bin/bash
Never logged in.
No mail.
No Plan.
```

由於 finger 類似指紋的功能，他會將使用者的相關屬性列出來！如上表所示，其實他列出來的幾乎都是 /etc/passwd 檔案裡面的東西。列出的資訊說明如下：

Login：為使用者帳號，亦即 /etc/passwd 內的第一欄位；
Name：為全名，亦即 /etc/passwd 內的第五欄位(或稱為註解)；
Directory：就是家目錄了；
Shell：就是使用的 Shell 檔案所在；
Never logged in.：figner 還會調查使用者登入主機的情況喔！
No mail.：調查 /var/spool/mail 當中的信箱資料；
No Plan.：調查 ~vbird1/.plan 檔案，並將該檔案取出來說明！
不過是否能夠查閱到 Mail 與 Plan 則與權限有關了！因為 Mail / Plan 都是與使用者自己的權限設定有關， root 當然可以查閱到使用者的這些資訊，但是 vbird1 就不見得能夠查到 vbird3 的資訊， 因為 /var/spool/mail/vbird3 與 /home/vbird3/ 的權限分別是 660, 700 ，那 vbird1 當然就無法查閱的到！ 這樣解釋可以理解吧？此外，我們可以建立自己想要執行的預定計畫，當然，最多是給自己看的！可以這樣做：

```bash
範例二：利用 vbird1 建立自己的計畫檔
[vbird1@study ~]$ echo "I will study Linux during this year." > ~/.plan
[vbird1@study ~]$ finger vbird1
Login: vbird1                           Name:
Directory: /home/vbird1                 Shell: /bin/bash
Last login Mon Jul 20 23:06 (CST) on pts/0
No mail.
Plan:
I will study Linux during this year.

範例三：找出目前在系統上面登入的使用者與登入時間
[vbird1@study ~]$ finger
Login     Name       Tty      Idle  Login Time   Office     Office Phone   Host
dmtsai    dmtsai     tty2      11d  Jul  7 23:07
dmtsai    dmtsai     pts/0          Jul 20 17:59  
```

在範例三當中，我們發現輸出的資訊還會有 Office, Office Phone 等資訊，那這些資訊要如何記錄呢？ 底下我們會介紹 chfn 這個指令！來看看如何修改使用者的 finger 資料吧！

#### chfn

chfn 有點像是： change finger 的意思！這玩意的使用方法如下：

```bash
[root@study ~]# chfn [-foph] [帳號名]
選項與參數：
-f  ：後面接完整的大名；
-o  ：您辦公室的房間號碼；
-p  ：辦公室的電話號碼；
-h  ：家裡的電話號碼！

範例一：vbird1 自己更改一下自己的相關資訊！
[vbird1@study ~]$ chfn
Changing finger information for vbird1.
Name []: VBird Tsai test         <==輸入你想要呈現的全名
Office []: DIC in KSU            <==辦公室號碼
Office Phone []: 06-2727175#356  <==辦公室電話
Home Phone []: 06-1234567        <==家裡電話號碼

Password:  <==確認身份，所以輸入自己的密碼
Finger information changed.

[vbird1@study ~]$ grep vbird1 /etc/passwd
vbird1:x:1003:1004:VBird Tsai test,DIC in KSU,06-2727175#356,06-1234567:/home/vbird1:/bin/bash
# 其實就是改到第五個欄位，該欄位裡面用多個『 , 』分隔就是了！

[vbird1@study ~]$ finger vbird1
Login: vbird1                           Name: VBird Tsai test
Directory: /home/vbird1                 Shell: /bin/bash
Office: DIC in KSU, 06-2727175#356      Home Phone: 06-1234567
Last login Mon Jul 20 23:12 (CST) on pts/0
No mail.
Plan:
I will study Linux during this year.
# 就是上面特殊字體呈現的那些地方是由 chfn 所修改出來的！
```

#### chsh

這就是 change shell 的簡寫！使用方法就更簡單了！

```bash
[vbird1@study ~]$ chsh [-ls]
選項與參數：
-l  ：列出目前系統上面可用的 shell ，其實就是 /etc/shells 的內容！
-s  ：設定修改自己的 Shell 囉

範例一：用 vbird1 的身份列出系統上所有合法的 shell，並且指定 csh 為自己的 shell
[vbird1@study ~]$ chsh -l
/bin/sh
/bin/bash
/sbin/nologin   <==所謂：合法不可登入的 Shell 就是這玩意！
/usr/bin/sh
/usr/bin/bash
/usr/sbin/nologin
/bin/tcsh
/bin/csh        <==這就是 C shell 啦！
# 其實上面的資訊就是我們在 bash 中談到的 /etc/shells 啦！

[vbird1@study ~]$ chsh -s /bin/csh; grep vbird1 /etc/passwd
Changing shell for vbird1.
Password:  <==確認身份，請輸入 vbird1 的密碼
Shell changed.
vbird1:x:1003:1004:VBird Tsai test,DIC in KSU,06-2727175#356,06-1234567:/home/vbird1:/bin/csh

[vbird1@study ~]$ chsh -s /bin/bash
# 測試完畢後，立刻改回來！

[vbird1@study ~]$ ll $(which chsh)
-rws--x--x. 1 root root 23856 Mar  6 13:59 /bin/chsh
```

### 13.2.3 新增與移除群組

OK！瞭解了帳號的新增、刪除、更動與查詢後，再來我們可以聊一聊群組的相關內容了。 基本上，群組的內容都與這兩個檔案有關：/etc/group, /etc/gshadow。 群組的內容其實很簡單，都是上面兩個檔案的新增、修改與移除而已， 不過，如果再加上有效群組的概念，那麼 newgrp 與 gpasswd 則不可不知呢！

#### groupadd

```bash
[root@study ~]# groupadd [-g gid] [-r] 群組名稱
選項與參數：
-g  ：後面接某個特定的 GID ，用來直接給予某個 GID ～
-r  ：建立系統群組啦！與 /etc/login.defs 內的 GID_MIN 有關。

範例一：新建一個群組，名稱為 group1
[root@study ~]# groupadd group1
[root@study ~]# grep group1 /etc/group /etc/gshadow
/etc/group:group1:x:1503:
/etc/gshadow:group1:!::
# 群組的 GID 也是會由 1000 以上最大 GID+1 來決定！
```

#### groupmod

跟 usermod 類似的，這個指令僅是在進行 group 相關參數的修改而已。

```bash
[root@study ~]# groupmod [-g gid] [-n group_name] 群組名
選項與參數：
-g  ：修改既有的 GID 數字；
-n  ：修改既有的群組名稱

範例一：將剛剛上個指令建立的 group1 名稱改為 mygroup ， GID 為 201
[root@study ~]# groupmod -g 201 -n mygroup group1
[root@study ~]# grep mygroup /etc/group /etc/gshadow
/etc/group:mygroup:x:201:
/etc/gshadow:mygroup:!::
```

#### groupdel

呼呼！ groupdel 自然就是在刪除群組的囉～用法很簡單：

```bash
[root@study ~]# groupdel [groupname]

範例一：將剛剛的 mygroup 刪除！
[root@study ~]# groupdel mygroup

範例二：若要刪除 vbird1 這個群組的話？
[root@study ~]# groupdel vbird1
groupdel: cannot remove the primary group of user 'vbird1'
```

為什麼 mygroup 可以刪除，但是 vbird1 就不能刪除呢？原因很簡單，『有某個帳號 (/etc/passwd) 的 initial group 使用該群組！』 如果查閱一下，你會發現在 /etc/passwd 內的 vbird1 第四欄的 GID 就是 /etc/group 內的 vbird1 那個群組的 GID ，所以囉，當然無法刪除～否則 vbird1 這個使用者登入系統後， 就會找不到 GID ，那可是會造成很大的困擾的！那麼如果硬要刪除 vbird1 這個群組呢？ 你『必須要確認 /etc/passwd 內的帳號沒有任何人使用該群組作為 initial group 』才行喔！所以，你可以：

修改 vbird1 的 GID ，或者是：
刪除 vbird1 這個使用者。

#### gpasswd：群組管理員功能

如果系統管理員太忙碌了，導致某些帳號想要加入某個專案時找不到人幫忙！這個時候可以建立『群組管理員』喔！ 什麼是群組管理員呢？就是讓某個群組具有一個管理員，這個群組管理員可以管理哪些帳號可以加入/移出該群組！ 那要如何『建立一個群組管理員』呢？就得要透過 gpasswd 囉！

```bash
# 關於系統管理員(root)做的動作：
[root@study ~]# gpasswd groupname
[root@study ~]# gpasswd [-A user1,...] [-M user3,...] groupname
[root@study ~]# gpasswd [-rR] groupname
選項與參數：
    ：若沒有任何參數時，表示給予 groupname 一個密碼(/etc/gshadow)
-A  ：將 groupname 的主控權交由後面的使用者管理(該群組的管理員)
-M  ：將某些帳號加入這個群組當中！
-r  ：將 groupname 的密碼移除
-R  ：讓 groupname 的密碼欄失效

# 關於群組管理員(Group administrator)做的動作：
[someone@study ~]$ gpasswd [-ad] user groupname
選項與參數：
-a  ：將某位使用者加入到 groupname 這個群組當中！
-d  ：將某位使用者移除出 groupname 這個群組當中。

範例一：建立一個新群組，名稱為 testgroup 且群組交由 vbird1 管理：
[root@study ~]# groupadd testgroup  <==先建立群組
[root@study ~]# gpasswd testgroup   <==給這個群組一個密碼吧！
Changing the password for group testgroup
New Password:
Re-enter new password:
# 輸入兩次密碼就對了！
[root@study ~]# gpasswd -A vbird1 testgroup  <==加入群組管理員為 vbird1
[root@study ~]# grep testgroup /etc/group /etc/gshadow
/etc/group:testgroup:x:1503:
/etc/gshadow:testgroup:$6$MnmChP3D$mrUn.Vo.buDjObMm8F2emTkvGSeuWikhRzaKHxpJ...:vbird1:
# 很有趣吧！此時 vbird1 則擁有 testgroup 的主控權喔！身份有點像板主啦！

範例二：以 vbird1 登入系統，並且讓他加入 vbird1, vbird3 成為 testgroup 成員
[vbird1@study ~]$ id
uid=1003(vbird1) gid=1004(vbird1) groups=1004(vbird1) ...
# 看得出來，vbird1 尚未加入 testgroup 群組喔！

[vbird1@study ~]$ gpasswd -a vbird1 testgroup
[vbird1@study ~]$ gpasswd -a vbird3 testgroup
[vbird1@study ~]$ grep testgroup /etc/group
testgroup:x:1503:vbird1,vbird3
```

## 13.3 主機的細部權限規劃：ACL 的使用

從第五章開始，我們就一直強調 Linux 的權限概念是非常重要的！ 但是傳統的權限僅有三種身份 (owner, group, others) 搭配三種權限 (r,w,x) 而已，並沒有辦法單純的針對某一個使用者或某一個群組來設定特定的權限需求，例如前一小節最後的那個任務！ 此時就得要使用 ACL 這個機制啦！這玩意挺有趣的，底下我們就來談一談：

### 13.3.1 什麼是 ACL 與如何支援啟動 ACL

ACL 是 Access Control List 的縮寫，主要的目的是在提供傳統的 owner,group,others 的 read,write,execute 權限之外的細部權限設定。ACL 可以針對單一使用者，單一檔案或目錄來進行 r,w,x 的權限規範，對於需要特殊權限的使用狀況非常有幫助。

那 ACL 主要可以針對哪些方面來控制權限呢？他主要可以針對幾個項目：

使用者 (user)：可以針對使用者來設定權限；
群組 (group)：針對群組為對象來設定其權限；
預設屬性 (mask)：還可以針對在該目錄下在建立新檔案/目錄時，規範新資料的預設權限；
也就是說，如果你有一個目錄，需要給一堆人使用，每個人或每個群組所需要的權限並不相同時，在過去，傳統的 Linux 三種身份的三種權限是無法達到的， 因為基本上，傳統的 Linux 權限只能針對一個用戶、一個群組及非此群組的其他人設定權限而已，無法針對單一用戶或個人來設計權限。 而 ACL 就是為了要改變這個問題啊！好了，稍微了解之後，再來看看如何讓你的檔案系統可以支援 ACL 吧！

## 13.4 使用者身份切換

什麼？在 Linux 系統當中還要作身份的變換？這是為啥？可能有底下幾個原因啦！

使用一般帳號：系統平日操作的好習慣
事實上，為了安全的緣故，一些老人家都會建議你，盡量以一般身份使用者來操作 Linux 的日常作業！等到需要設定系統環境時， 才變換身份成為 root 來進行系統管理，相對比較安全啦！避免作錯一些嚴重的指令，例如恐怖的『 rm -rf / 』(千萬作不得！)

用較低權限啟動系統服務
相對於系統安全，有的時候，我們必須要以某些系統帳號來進行程序的執行。 舉例來說， Linux 主機上面的一套軟體，名稱為 apache ，我們可以額外建立一個名為 apache 的使用者來啟動 apache 軟體啊，如此一來，如果這個程序被攻破，至少系統還不至於就損毀了～

軟體本身的限制
在遠古時代的 telnet 程式中，該程式預設是不許使用 root 的身份登入的，telnet 會判斷登入者的 UID， 若 UID 為 0 的話，那就直接拒絕登入了。所以，你只能使用一般使用者來登入 Linux 伺服器。 此外， ssh (註3) 也可以設定拒絕 root 登入喔！那如果你有系統設定需求該如何是好啊？就變換身份啊！

由於上述考量，所以我們都是使用一般帳號登入系統的，等有需要進行系統維護或軟體更新時才轉為 root 的身份來動作。 那如何讓一般使用者轉變身份成為 root 呢？主要有兩種方式喔：

**以『 su - 』直接將身份變成 root 即可，但是這個指令卻需要 root 的密碼**，也就是說，如果你要以 su 變成 root 的話，你的一般使用者就必須要有 root 的密碼才行；

以『 sudo 指令 』執行 root 的指令串，由於 sudo 需要事先設定妥當，且 sudo 需要輸入使用者自己的密碼， 因此多人共管同一部主機時， sudo 要比 su 來的好喔！至少 root 密碼不會流出去！
底下我們就來說一說 su 跟 sudo 的用法啦！

### 13.4.1 su

su 是最簡單的身份切換指令了，他可以進行任何身份的切換唷！方法如下：

```bash
[root@study ~]# su [-lm] [-c 指令] [username]
選項與參數：
-   ：單純使用 - 如『 su - 』代表使用 login-shell 的變數檔案讀取方式來登入系統；
      若使用者名稱沒有加上去，則代表切換為 root 的身份。
-l  ：與 - 類似，但後面需要加欲切換的使用者帳號！也是 login-shell 的方式。
-m  ：-m 與 -p 是一樣的，表示『使用目前的環境設定，而不讀取新使用者的設定檔』
-c  ：僅進行一次指令，所以 -c 後面可以加上指令喔！
```

上表的解釋當中有出現之前第十章談過的 login-shell 設定檔讀取方式，如果你忘記那是啥東西， 請先回去第十章瞧瞧再回來吧！這個 su 的用法當中，有沒有加上那個減號『 - 』差很多喔！ 因為涉及 login-shell 與 non-login shell 的變數讀取方法。這裡讓我們以一個小例子來說明吧！

```bash
範例一：假設你原本是 dmtsai 的身份，想要使用 non-login shell 的方式變成 root
[dmtsai@study ~]$ su       <==注意提示字元，是 dmtsai 的身份喔！
Password:                  <==這裡輸入 root 的密碼喔！
[root@study dmtsai]# id    <==提示字元的目錄是 dmtsai 喔！
uid=0(root) gid=0(root) groups=0(root) context=unconf....  <==確實是 root 的身份！
[root@study dmtsai]# env | grep 'dmtsai'
USER=dmtsai                                         <==竟然還是 dmtsai 這傢伙！
PATH=...:/home/dmtsai/.local/bin:/home/dmtsai/bin   <==這個影響最大！ 
MAIL=/var/spool/mail/dmtsai                         <==收到的 mailbox 是 vbird1
PWD=/home/dmtsai                                    <==並非 root 的家目錄
LOGNAME=dmtsai
# 雖然你的 UID 已經是具有 root 的身份，但是看到上面的輸出訊息嗎？
# 還是有一堆變數為原本 dmtsai 的身份，所以很多資料還是無法直接利用。
[root@study dmtsai]# exit   <==這樣可以離開 su 的環境！

home-desktop@Desktop:~/os$ su
Password: 
root@Desktop:/home/home-desktop/os# 
exit
home-desktop@Desktop:~/os$ id
uid=1000(home-desktop) gid=1000(home-desktop) groups=1000(home-desktop),4(adm),20(dialout),24(cdrom),25(floppy),27(sudo),29(audio),30(dip),44(video),46(plugdev),100(users),116(netdev)
home-desktop@Desktop:~/os$ su
Password: 
root@Desktop:/home/home-desktop/os# id
uid=0(root) gid=0(root) groups=0(root)
```

單純使用『 su 』切換成為 root 的身份，讀取的變數設定方式為 non-login shell 的方式，這種方式很多原本的變數不會被改變， 尤其是我們之前談過很多次的 PATH 這個變數，由於沒有改變成為 root 的環境， 因此很多 root 慣用的指令就只能使用絕對路徑來執行咯。其他的還有 MAIL 這個變數，你輸入 mail 時， 收到的郵件竟然還是 dmtsai 的，而不是 root 本身的郵件！是否覺得很奇怪啊！所以切換身份時，請務必使用如下的範例二：

```bash
範例二：使用 login shell 的方式切換為 root 的身份並觀察變數
[dmtsai@study ~]$ su -
Password:   <==這裡輸入 root 的密碼喔！
[root@study ~]# env | grep root
USER=root
MAIL=/var/spool/mail/root
PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin
PWD=/root
HOME=/root
LOGNAME=root
# 瞭解差異了吧？下次變換成為 root 時，記得最好使用 su - 喔！
[root@study ~]# exit   <==這樣可以離開 su 的環境！
```

上述的作法是讓使用者的身份變成 root 並開始操作系統，如果想要離開 root 的身份則得要利用 exit 離開才行。 那我如果只是想要執行『一個只有 root 才能進行的指令，且執行完畢就恢復原本的身份』呢？那就可以加上 -c 這個選項囉！ 請參考底下範例三！

su 就這樣簡單的介紹完畢，總結一下他的用法是這樣的：

**若要完整的切換到新使用者的環境，必須要使用『 su - username 』或『 su -l username 』， 才會連同 PATH/USER/MAIL 等變數都轉成新使用者的環境；**

**如果僅想要執行一次 root 的指令，可以利用『 su - -c "指令串" 』的方式來處理；**

使用 root 切換成為任何使用者時，並不需要輸入新使用者的密碼；
雖然使用 su 很方便啦，不過缺點是，當我的主機是多人共管的環境時，如果大家都要使用 su 來切換成為 root 的身份，那麼不就每個人都得要知道 root 的密碼，這樣密碼太多人知道可能會流出去， 很不妥當呢！怎辦？透過 sudo 來處理即可！

### 13.4.2 sudo

相對於 su 需要瞭解新切換的使用者密碼 (常常是需要 root 的密碼)， sudo 的執行則僅需要自己的密碼即可！ 甚至可以設定不需要密碼即可執行 sudo 呢！由於 sudo 可以讓你以其他用戶的身份執行指令 (通常是使用 root 的身份來執行指令)，因此並非所有人都能夠執行 sudo ， 而是僅有規範到 /etc/sudoers 內的用戶才能夠執行 sudo 這個指令喔！說的這麼神奇，底下就來瞧瞧那 sudo 如何使用？

#### sudo 的指令用法

由於一開始系統預設僅有 root 可以執行 sudo ，因此底下的範例我們先以 root 的身份來執行，等到談到 visudo 時，再以一般使用者來討論其他 sudo 的用法吧！ sudo 的語法如下：

```bash
[root@study ~]# sudo [-b] [-u 新使用者帳號]
選項與參數：
-b  ：將後續的指令放到背景中讓系統自行執行，而不與目前的 shell 產生影響
-u  ：後面可以接欲切換的使用者，若無此項則代表切換身份為 root 。

範例一：你想要以 sshd 的身份在 /tmp 底下建立一個名為 mysshd 的檔案
[root@study ~]# sudo -u sshd touch /tmp/mysshd
[root@study ~]# ll /tmp/mysshd
-rw-r--r--. 1 sshd sshd 0 Jul 21 23:37 /tmp/mysshd
# 特別留意，這個檔案的權限是由 sshd 所建立的情況喔！

範例二：你想要以 vbird1 的身份建立 ~vbird1/www 並於其中建立 index.html 檔案
[root@study ~]# sudo -u vbird1 sh -c "mkdir ~vbird1/www; cd ~vbird1/www; \
>  echo 'This is index.html file' > index.html"
[root@study ~]# ll -a ~vbird1/www
drwxr-xr-x. 2 vbird1 vbird1   23 Jul 21 23:38 .
drwx------. 6 vbird1 vbird1 4096 Jul 21 23:38 ..
-rw-r--r--. 1 vbird1 vbird1   24 Jul 21 23:38 index.html
# 要注意，建立者的身份是 vbird1 ，且我們使用 sh -c "一串指令" 來執行的！
```

sudo 可以讓你切換身份來進行某項任務，例如上面的兩個範例。範例一中，我們的 root 使用 sshd 的權限去進行某項任務！ 要注意，因為我們無法使用『 su - sshd 』去切換系統帳號 (因為系統帳號的 shell 是 /sbin/nologin)， 這個時候 sudo 真是他 X 的好用了！立刻以 sshd 的權限在 /tmp 底下建立檔案！查閱一下檔案權限你就瞭解意義啦！ 至於範例二則更使用多重指令串 (透過分號 ; 來延續指令進行)，使用 sh -c 的方法來執行一連串的指令， 如此真是好方便！

但是 sudo 預設僅有 root 能使用啊！為什麼呢？因為 sudo 的執行是這樣的流程：

當使用者執行 sudo 時，系統於 /etc/sudoers 檔案中搜尋該使用者是否有執行 sudo 的權限；
若使用者具有可執行 sudo 的權限後，便讓使用者『輸入使用者自己的密碼』來確認；
若密碼輸入成功，便開始進行 sudo 後續接的指令(但 root 執行 sudo 時，不需要輸入密碼)；
若欲切換的身份與執行者身份相同，那也不需要輸入密碼。
所以說，sudo 執行的重點是：『能否使用 sudo 必須要看 /etc/sudoers 的設定值， 而可使用 sudo 者是透過輸入使用者自己的密碼來執行後續的指令串』喔！由於能否使用與 /etc/sudoers 有關， 所以我們當然要去編輯 sudoers 檔案啦！不過，因為該檔案的內容是有一定的規範的，因此直接使用 vi 去編輯是不好的。 此時，我們得要透過 visudo 去修改這個檔案喔！

#### visudo 與 /etc/sudoers

從上面的說明我們可以知道，除了 root 之外的其他帳號，若想要使用 sudo 執行屬於 root 的權限指令，則 root 需要先使用 visudo 去修改 /etc/sudoers ，讓該帳號能夠使用全部或部分的 root 指令功能。為什麼要使用 visudo 呢？這是因為 /etc/sudoers 是有設定語法的，如果設定錯誤那會造成無法使用 sudo 指令的不良後果。因此才會使用 visudo 去修改， 並在結束離開修改畫面時，系統會去檢驗 /etc/sudoers 的語法就是了。

一般來說，visudo 的設定方式有幾種簡單的方法喔，底下我們以幾個簡單的例子來分別說明：

I. 單一使用者可進行 root 所有指令，與 sudoers 檔案語法：
假如我們要讓 vbird1 這個帳號可以使用 root 的任何指令，基本上有兩種作法，第一種是直接透過修改 /etc/sudoers ，方法如下

```bash
[root@study ~]# visudo
....(前面省略)....
root    ALL=(ALL)       ALL  <==找到這一行，大約在 98 行左右
vbird1  ALL=(ALL)       ALL  <==這一行是你要新增的！
....(底下省略)....
```

## 13.6 Linux 主機上的使用者訊息傳遞

談了這麼多的帳號問題，總是該要談一談，那麼如何針對系統上面的使用者進行查詢吧？ 想幾個狀態，如果你在 Linux 上面操作時，剛好有其他的使用者也登入主機，你想要跟他對談，該如何是好？ 你想要知道某個帳號的相關資訊，該如何查閱？呼呼！底下我們就來聊一聊～

### 13.6.1 查詢使用者： w, who, last, lastlog

如何查詢一個使用者的相關資料呢？這還不簡單，我們之前就提過了 id, finger 等指令了，都可以讓您瞭解到一個使用者的相關資訊啦！那麼想要知道使用者到底啥時候登入呢？ 最簡單可以使用 last 檢查啊！這個玩意兒我們也在 第十章 bash 提過了， 您可以自行前往參考啊！簡單的很。

那如果你想要知道目前已登入在系統上面的使用者呢？可以透過 w 或 who 來查詢喔！如下範例所示：

```bash
[root@study ~]# w
 01:49:18 up 25 days,  3:34,  3 users,  load average: 0.00, 0.01, 0.05
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
dmtsai   tty2                      07Jul15 12days  0.03s  0.03s -bash
dmtsai   pts/0    172.16.200.254   00:18    6.00s  0.31s  0.11s sshd: dmtsai [priv]
# 第一行顯示目前的時間、開機 (up) 多久，幾個使用者在系統上平均負載等；
# 第二行只是各個項目的說明，
# 第三行以後，每行代表一個使用者。如上所示，dmtsai 登入並取得終端機名 tty2 之意。

[root@study ~]# who
dmtsai   tty2         2015-07-07 23:07
dmtsai   pts/0        2015-07-22 00:18 (192.168.1.100)

home-desktop@Desktop:~/os$ w
 16:31:26 up  4:27,  0 users,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
home-desktop@Desktop:~/os$ who
```

另外，如果您想要知道每個帳號的最近登入的時間，則可以使用 lastlog 這個指令喔！ lastlog 會去讀取 /var/log/lastlog 檔案，結果將資料輸出如下表：

```bash
home-desktop@Desktop:~/os$ lastlog
Username         Port     From             Latest
root                                       **Never logged in**
daemon                                     **Never logged in**
bin                                        **Never logged in**
sys                                        **Never logged in**
sync                                       **Never logged in**
games                                      **Never logged in**
man                                        **Never logged in**
lp                                         **Never logged in**
mail                                       **Never logged in**
news                                       **Never logged in**
uucp                                       **Never logged in**
proxy                                      **Never logged in**
www-data                                   **Never logged in**
backup                                     **Never logged in**
list                                       **Never logged in**
irc                                        **Never logged in**
gnats                                      **Never logged in**
nobody                                     **Never logged in**
systemd-network                            **Never logged in**
systemd-resolve                            **Never logged in**
messagebus                                 **Never logged in**
systemd-timesync                           **Never logged in**
syslog                                     **Never logged in**
_apt                                       **Never logged in**
uuidd                                      **Never logged in**
tcpdump                                    **Never logged in**
home-desktop                               **Never logged in**
rtkit                                      **Never logged in**
usbmux                                     **Never logged in**
kevin                                      **Never logged in**
```

## 13.8 重點回顧

Linux 作業系統上面，關於帳號與群組，其實記錄的是 UID/GID 的數字而已；
使用者的帳號/群組與 UID/GID 的對應，參考 /etc/passwd 及 /etc/group 兩個檔案
/etc/passwd 檔案結構以冒號隔開，共分為七個欄位，分別是『帳號名稱、密碼、UID、GID、全名、家目錄、shell』
UID 只有 0 與非為 0 兩種，非為 0 則為一般帳號。一般帳號又分為系統帳號 (1~999) 及可登入者帳號 (大於 1000)
帳號的密碼已經移動到 /etc/shadow 檔案中，該檔案權限為僅有 root 可以更動。該檔案分為九個欄位，內容為『 帳號名稱、加密密碼、密碼更動日期、密碼最小可變動日期、密碼最大需變動日期、密碼過期前警告日數、密碼失效天數、 帳號失效日、保留未使用』
使用者可以支援多個群組，其中在新建檔案時會影響新檔案群組者，為有效群組。而寫入 /etc/passwd 的第四個欄位者， 稱為初始群組。
與使用者建立、更改參數、刪除有關的指令為：useradd, usermod, userdel等，密碼建立則為 passwd；
與群組建立、修改、刪除有關的指令為：groupadd, groupmod, groupdel 等；
群組的觀察與有效群組的切換分別為：groups 及 newgrp 指令；
useradd 指令作用參考的檔案有： /etc/default/useradd, /etc/login.defs, /etc/skel/ 等等
觀察使用者詳細的密碼參數，可以使用『 chage -l 帳號 』來處理；
使用者自行修改參數的指令有： chsh, chfn 等，觀察指令則有： id, finger 等
ACL 的功能需要檔案系統有支援，CentOS 7 預設的 XFS 確實有支援 ACL 功能！
ACL 可進行單一個人或群組的權限管理，但 ACL 的啟動需要有檔案系統的支援；
ACL 的設定可使用 setfacl ，查閱則使用 getfacl ；
身份切換可使用 su ，亦可使用 sudo ，但使用 sudo 者，必須先以 visudo 設定可使用的指令；
PAM 模組可進行某些程式的驗證程序！與 PAM 模組有關的設定檔位於 /etc/pam.d/*及/etc/security/*
系統上面帳號登入情況的查詢，可使用 w, who, last, lastlog 等；
線上與使用者交談可使用 write, wall，離線狀態下可使用 mail 傳送郵件！
