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

