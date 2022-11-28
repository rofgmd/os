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

|id 範圍	|該 ID 使用者特性|
|---|---|
|0(系統管理員)|	當 UID 是 0 時，代表這個帳號是『系統管理員』！ 所以當你要讓其他的帳號名稱也具有 root 的權限時，將該帳號的 UID 改為 0 即可。 這也就是說，一部系統上面的系統管理員不見得只有 root 喔！ 不過，很不建議有多個帳號的 UID 是 0 啦～容易讓系統管理員混亂！|
|1~999(系統帳號)|	保留給系統使用的 ID，其實除了 0 之外，其他的 UID 權限與特性並沒有不一樣。預設 1000 以下的數字讓給系統作為保留帳號只是一個習慣。由於系統上面啟動的網路服務或背景服務希望使用較小的權限去運作，因此不希望使用 root 的身份去執行這些服務， 所以我們就得要提供這些運作中程式的擁有者帳號才行。這些系統帳號通常是不可登入的， 所以才會有我們在第十章提到的 /sbin/nologin 這個特殊的 shell 存在。根據系統帳號的由來，通常這類帳號又約略被區分為兩種： 1~200：由 distributions 自行建立的系統帳號；201~999：若使用者有系統帳號需求時，可以使用的帳號 UID。
|1000~60000(可登入帳號)|	給一般使用者用的。事實上，目前的 linux 核心 (3.10.x 版)已經可以支援到 4294967295 (2^32-1) 這麼大的 UID 號碼喔！|

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

最近更動密碼的日期：
這個欄位記錄了『更動密碼那一天』的日期，不過，很奇怪呀！在我的例子中怎麼會是 16559 呢？呵呵，這個是因為計算 Linux 日期的時間是以 1970 年 1 月 1 日作為 1 而累加的日期，1971 年 1 月 1 日則為 366 啦！ 得注意一下這個資料呦！上述的 16559 指的就是 2015-05-04 那一天啦！瞭解乎？ 而想要瞭解該日期可以使用本章後面 chage 指令的幫忙！至於想要知道某個日期的累積日數， 可使用如下的程式計算：