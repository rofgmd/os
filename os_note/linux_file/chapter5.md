# Linux 的檔案權限與目錄配置Linux 的檔案權限與目錄配置
---
## 5.1 使用者與群組

1. 這個『使用者與群組』的功能可是相當健全而好用的一個安全防護呢！怎麼說呢？ 由於Linux是個多人多工的系統，因此可能常常會有多人同時使用這部主機來進行工作的情況發生， 為了考慮每個人的隱私權以及每個人喜好的工作環境，因此，這個『檔案擁有者』的角色就顯的相當的重要了！
2. 其實，群組最有用的功能之一，就是當你在團隊開發資源的時候啦！ 舉例來說，假設有兩組專題生在我的主機裡面，第一個專題組別為projecta，裡面的成員有 class1, class2, class3三個；第二個專題組別為projectb，裡面的成員有class4, class5, class6。 這兩個專題之間是有競爭性質的，但卻要繳交同一份報告。每組的組員之間必須要能夠互相修改對方的資料， 但是其他組的組員則不能看到本組自己的檔案內容，此時該如何是好？
3. 因此，我們就可以知道啦，在Linux裡面，任何一個檔案都具有『User, Group及Others』三種身份的個別權限， 我們可以將上面的說明以底下的圖示來解釋：
<div align=center><img src="/os_note/linux_file/picture/0210filepermission_1.jpg"></div>

我們以王三毛為例，王三毛這個『檔案』的擁有者為王三毛，他屬於王大毛這個群組， 而張小豬相對於王三毛，則只是一個『其他人(others)』而已。

**Linux 使用者身份與群組記錄的檔案**
在我們Linux系統當中，預設的情況下，所有的系統上的帳號與一般身份使用者，還有那個root的相關資訊， 都是記錄在/etc/passwd這個檔案內的。至於個人的密碼則是記錄在/etc/shadow這個檔案下。 此外，Linux所有的群組名稱都紀錄在/etc/group內！這三個檔案可以說是Linux系統裡面帳號、密碼、群組資訊的集中地囉！ 不要隨便刪除這三個檔案啊！ ^_^

##Linux 檔案權限概念
###Linux檔案屬性

**ls**

kevin@ubuntu:~/os$ ls
os_experiment  os_note  路线图.jpg

kevin@ubuntu:~/os$ ls -a
.  ..  .git  .gitmodules  os_experiment  os_note  .vscode  路线图.jpg

kevin@ubuntu:~/os$ ls -al
total 528
drwxrwxr-x  6 kevin kevin   4096 Oct 19 17:33 .
drwxr-xr-x 40 kevin kevin   4096 Oct 20 09:46 ..
drwxrwxr-x  9 kevin kevin   4096 Oct 19 17:51 .git
-rw-rw-r--  1 kevin kevin    141 Oct 13 17:55 .gitmodules
drwxrwxr-x  5 kevin kevin   4096 Oct 18 15:42 os_experiment
drwxrwxr-x  7 kevin kevin   4096 Oct 19 15:09 os_note
drwxrwxr-x  2 kevin kevin   4096 Oct 19 17:33 .vscode
-rwxrw-rw-  1 kevin kevin 508889 Oct  9 15:33 路线图.jpg
[    1    ][  2 ][   3  ][  4 ][    5   ][    6     ] [       7          ]
[  權限   ][連結][擁有者][群組][檔案容量][ 修改日期 ] [      檔名        ]

ls是『list』的意思，重點在顯示檔案的檔名與相關屬性。而選項『-al』則表示列出所有的檔案詳細的權限與屬性 (包含隱藏檔，就是檔名第一個字元為『 . 』的檔案)。如上所示，在你第一次以root身份登入Linux時， 如果你輸入上述指令後，應該有上列的幾個東西，先解釋一下上面七個欄位個別的意思：
<div align=center><img src="/os_note/linux_file/picture/centos7_0210filepermission_2.gif"></div>

<center>圖5.2.1、檔案屬性的示意圖</center>

- 第一欄代表這個檔案的類型與權限(permission)
- 這個地方最需要注意了！仔細看的話，你應該可以發現這一欄其實共有十個字元：(圖5.2.1及圖5.2.2內的權限並無關係)

<div align=center><img src="/os_note/linux_file/picture/0210filepermission_3.gif"></div>
<center>圖5.2.2、檔案的類型與權限之內容</center>

##### 第一個字元代表這個檔案是『目錄、檔案或連結檔等等』：
當為[ d ]則是目錄，例如上表檔名為『.config』的那一行；
當為[ - ]則是檔案，例如上表檔名為『initial-setup-ks.cfg』那一行；
若是[ l ]則表示為連結檔(link file)；
若是[ b ]則表示為裝置檔裡面的可供儲存的周邊設備(可隨機存取裝置)；
若是[ c ]則表示為裝置檔裡面的序列埠設備，例如鍵盤、滑鼠(一次性讀取裝置)。

- 接下來的字元中，以三個為一組，且均為『rwx』 的三個參數的組合。其中，[ r ]代表可讀(read)、[ w ]代表可寫(write)、[ x ]代表可執行(execute)。 要注意的是，這三個權限的位置不會改變，如果沒有權限，就會出現減號[ - ]而已。
第一組為『檔案擁有者可具備的權限』，以『initial-setup-ks.cfg』那個檔案為例， 該檔案的擁有者可以讀寫，但不可執行；
第二組為『加入此群組之帳號的權限』；
第三組為『非本人且沒有加入本群組之其他帳號的權限』。

>請你特別注意喔！不論是那一組權限，基本上，都是『針對某些帳號來設計的權限』喔！以群組來說，他規範的是『加入這個群組的帳號具有什麼樣的權限』之意， 以學校社團為例，假設學校有個童軍社的社團辦公室，『加入童軍社的同學就可以進出社辦』，主角是『學生(帳號)』而不是童軍社本身喔！這樣可以理解嗎？ 

>例題：
若有一個檔案的類型與權限資料為『-rwxr-xr--』，請說明其意義為何？
答：
先將整個類型與權限資料分開查閱，並將十個字元整理成為如下所示：
[-][rwx][r-x][r--]
 1  234  567  890
 1 為：**代表這個檔名為目錄或檔案**，本例中為檔案(-)；
234為：**擁有者的權限**，本例中為可讀、可寫、可執行(rwx)；
567為：**同群組使用者權限**，本例中為可讀可執行(rx)；
890為：**其他使用者權限**，本例中為可讀(r)，就是唯讀之意
同時注意到，rwx所在的位置是不會改變的，有該權限就會顯示字元，沒有該權限就變成減號(-)就是了。

##### 第二欄表示有多少檔名連結到此節點(i-node)：
每個檔案都會將他的權限與屬性記錄到檔案系統的i-node中，不過，我們使用的目錄樹卻是使用檔名來記錄， 因此每個檔名就會連結到一個i-node囉！這個屬性記錄的，就是有多少不同的檔名連結到相同的一個i-node號碼去就是了。 關於i-node的相關資料我們會在第七章談到檔案系統時再加強介紹的。

##### 第三欄表示這個檔案(或目錄)的『擁有者帳號』
##### 第四欄表示這個檔案的所屬群組

在Linux系統下，你的帳號會加入於一個或多個的群組中。舉剛剛我們提到的例子，class1, class2, class3均屬於projecta這個群組，假設某個檔案所屬的群組為projecta，且該檔案的權限如圖5.2.2所示(-rwxrwx---)， 則class1, class2, class3三人對於該檔案都具有可讀、可寫、可執行的權限(看群組權限)。 但如果是不屬於projecta的其他帳號，對於此檔案就不具有任何權限了。

##### 第五欄為這個檔案的容量大小，預設單位為bytes；
##### 第六欄為這個檔案的建檔日期或者是最近的修改日期：
這一欄的內容分別為日期(月/日)及時間。如果這個檔案被修改的時間距離現在太久了，那麼時間部分會僅顯示年份而已。
ll命令==ls -l

##### 第七欄為這個檔案的檔名
這個欄位就是檔名了。比較特殊的是：如果檔名之前多一個『 . 』，則代表這個檔案為『隱藏檔』，例如上表中的.config那一行，該檔案就是隱藏檔。 你可以使用『ls』及『ls -a』這兩個指令去感受一下什麼是隱藏檔囉！

#### Linux檔案權限的重要性：
- 系統保護的功能：
- 團隊開發軟體或資料共用的功能：
- 未將權限設定妥當的危害：

### 5.2.2 如何改變檔案屬性與權限

- chgrp ：改變檔案所屬群組
- chown ：改變檔案擁有者
- chmod ：改變檔案的權限, SUID, SGID, SBIT等等的特性

#### 改變所屬群組, chgrp
[root@study ~]# chgrp [-R] dirname/filename ...

#### 改變檔案擁有者, chown
[root@study ~]# chown [-R] 帳號名稱 檔案或目錄
[root@study ~]# chown [-R] 帳號名稱:群組名稱 檔案或目錄
選項與參數：
-R : 進行遞迴(recursive)的持續變更，亦即連同次目錄下的所有檔案都變更

>[root@study ~]# cp 來源檔案 目的檔案
kevin@ubuntu:~/os$ cp text.txt ~/os/os_note/

#### 改變權限, chmod
檔案權限的改變使用的是chmod這個指令，但是，權限的設定方法有兩種， 分別可以使用數字或者是符號來進行權限的變更。我們就來談一談：
- **數字類型改變檔案權限**

    Linux檔案的基本權限就有九個，分別是owner/group/others三種身份各有自己的read/write/execute權限， 先複習一下剛剛上面提到的資料：檔案的權限字元為：『-rwxrwxrwx』， 這九個權限是三個三個一組的！其中，我們可以使用數字來代表各個權限，各權限的分數對照表如下：
    **r:4**
    **w:2**
    **x:1** 
    **(owner/group/others)** 
    每種身份 **(owner/group/others)** 各自的三個權限(r/w/x)分數是需要累加的，例如當權限為： [-rwxrwx---] 分數則是：
    owner = rwx = 4+2+1 = 7
    group = rwx = 4+2+1 = 7
    others= --- = 0+0+0 = 0
    所以等一下我們設定權限的變更時，該檔案的權限數字就是770啦！變更權限的指令chmod的語法是這樣的：
    >[root@study ~]# chmod [-R] xyz 檔案或目錄
    >選項與參數：
    >xyz : 就是剛剛提到的數字類型的權限屬性，為 rwx 屬性數值的相加。
    >-R : 進行遞迴(recursive)的持續變更，亦即連同次目錄下的所有檔案都會變更

    那如果要將權限變成『 -rwxr-xr-- 』呢？那麼權限的分數就成為 [4+2+1][4+0+1][4+0+0]=754 囉！所以你需要下達『 chmod 754 filename』。 另外，在實際的系統運作中最常發生的一個問題就是，常常我們以vim編輯一個shell的文字批次檔後，他的權限通常是 -rw-rw-r-- 也就是664， 如果要將該檔案變成可執行檔，並且不要讓其他人修改此一檔案的話， 那麼就需要-rwxr-xr-x這樣的權限，此時就得要下達：『 chmod 755 test.sh 』的指令囉！

    另外，如果有些檔案你不希望被其他人看到，那麼應該將檔案的權限設定為例如：『-rwxr-----』，那就下達『 chmod 740 filename 』吧！
    
    >例題：
    >將剛剛你的.bashrc這個檔案的權限修改回-rw-r--r--的情況吧！
    >chmod 644 .bashrc

- **符號類型改變檔案權限**
    還有一個改變權限的方法呦！從之前的介紹中我們可以發現，基本上就九個權限分別是(1)user (2)group (3)others三種身份啦！那麼我們就可以藉由u, g, o來代表三種身份的權限！此外， a 則代表 all 亦即全部的身份！那麼讀寫的權限就可以寫成r, w, x囉！也就是可以使用底下的方式來看：
    <div align=center><img src="/os_note/linux_file/picture/屏幕截图%202022-10-20%20155540.png"></div>
    來實作一下吧！假如我們要『設定』一個檔案的權限成為『-rwxr-xr-x』時，基本上就是

    - user (u)：具有可讀、可寫、可執行的權限；
    - group 與 others (g/o)：具有可讀與執行的權限。

    >[root@study ~]# chmod  u=rwx,go=rx  .bashrc
    >#注意喔！那個 u=rwx,go=rx 是連在一起的，中間並沒有任何空白字元！
    >[root@study ~]# ls -al .bashrc
    >-rwxr-xr-x. 1 root root 176 Dec 29  2013 .bashrc

    **增加**
    那麼假如是『 -rwxr-xr-- 』這樣的權限呢？可以使用『 chmod u=rwx,g=rx,o=r filename 』來設定。此外，如果我不知道原先的檔案屬性，而我只想要增加.bashrc這個檔案的每個人均可寫入的權限， 那麼我就可以使用：

    >[root@study ~]# ls -al .bashrc
    >-rwxr-xr-x. 1 root root 176 Dec 29  2013 .bashrc
    >[root@study ~]# chmod  a+w  .bashrc
    >[root@study ~]# ls -al .bashrc
    >-rwxrwxrwx. 1 root root 176 Dec 29  2013 .bashrc

    **减少**
    而如果是要將權限去掉而不更動其他已存在的權限呢？例如要拿掉全部人的可執行權限，則：
    >[root@study ~]# chmod  a-x  .bashrc
    >[root@study ~]# ls -al .bashrc
    >-rw-rw-rw-. 1 root root 176 Dec 29  2013 .bashrc
    >[root@study ~]# chmod 644 .bashrc  # 測試完畢得要改回來喔！

    知道 +, -, = 的不同點了嗎？對啦！ **+ 與 – 的狀態下，只要是沒有指定到的項目，則該權限『不會被變動』**， 例如上面的例子中，由於僅以 – 拿掉 x 則其他兩個保持當時的值不變！多多實作一下，你就會知道如何改變權限囉！ 這在某些情況底下很好用的～舉例來說，你想要教一個朋友如何讓一個程式可以擁有執行的權限， 但你又不知道該檔案原本的權限為何，此時，利用『chmod a+x filename』 ，就可以讓該程式擁有執行的權限了。是否很方便？

### 5.2.3 目錄與檔案之權限意義：
**權限對檔案的重要性**
檔案是實際含有資料的地方，包括一般文字檔、資料庫內容檔、二進位可執行檔(binary program)等等。 因此，權限對於檔案來說，他的意義是這樣的：

- r (read)：可讀取此一檔案的實際內容，如讀取文字檔的文字內容等；
- w (write)：可以編輯、新增或者是修改該檔案的內容(但不含刪除該檔案)；
- x (eXecute)：該檔案具有可以被系統執行的權限。

 因為在Windows底下一個檔案是否具有執行的能力是藉由『 副檔名 』來判斷的， 例如：.exe, .bat, .com 等等，**但是在Linux底下，我們的檔案是否能被執行，則是藉由是否具有『x』這個權限來決定的！跟檔名是沒有絕對的關係的！**

**權限對目錄的重要性**
檔案是存放實際資料的所在，那麼目錄主要是儲存啥玩意啊？目錄主要的內容在記錄檔名清單，檔名與目錄有強烈的關連啦！ 所以如果是針對目錄時，那個 r, w, x 對目錄是什麼意義呢？
- r (read contents in directory)：

    表示具有讀取目錄結構清單的權限，所以當你具有讀取(r)一個目錄的權限時，表示你可以查詢該目錄下的檔名資料。 **所以你就可以利用 ls 這個指令將該目錄的內容列表顯示出來！**
- w (modify contents of directory)：

    對目錄來說，是很了不起的！ 因為他表示你具有異動該目錄結構清單的權限，也就是底下這些權限：
    - 建立新的檔案與目錄；
    - 刪除已經存在的檔案與目錄(不論該檔案的權限為何！)
    - 將已存在的檔案或目錄進行更名；
    - 搬移該目錄內的檔案、目錄位置。

    **總之，目錄的w權限就與該目錄底下的檔名異動有關就對了啦！**
- x (access directory)：

    咦！目錄的執行權限有啥用途啊？目錄只是記錄檔名而已，總不能拿來執行吧？沒錯！目錄不可以被執行，**目錄的x代表的是使用者能否進入該目錄成為工作目錄的用途**！ 所謂的工作目錄(work directory)就是你目前所在的目錄啦！舉例來說，**當你登入Linux時， 你所在的家目錄就是你當下的工作目錄。而變換目錄的指令是『cd』(change directory)囉！**

上面的東西這麼說，也太條列式～太教條了～有沒有清晰一點的說明啊？好～讓我們來思考一下人類社會使用的東西好了！ 現在假設『檔案是一堆文件資料夾』，所以你可能可以在上面寫/改一些資料。而『目錄是一堆抽屜』，因此你可以將資料夾分類放置到不同的抽屜去。 因此抽屜最大的目的是拿出/放入資料夾喔！現在讓我們彙整一下資料：
<div align=center><img src="/os_note/linux_file/picture/屏幕截图%202022-10-20%20170043.png"></div>
根據上述的分析，你可以看到，對一般檔案來說，rwx 主要是針對『檔案的內容』來設計權限，對目錄來說，rwx則是針對『目錄內的檔名列表』來設計權限。 其中最有趣的大概就屬目錄的 x 權限了！『檔名怎麼執行』？沒道理嘛！其實，這個 x 權限設計，就相當於『該目錄，也就是該抽屜的 "鑰匙" 』啦！ 沒有鑰匙你怎麼能夠打開抽屜呢？對吧！

上面這個例題中因為vbird具有r的權限，因為是r乍看之下好像就具有可以進入此目錄的權限，其實那是錯的。 **能不能進入某一個目錄，只與該目錄的x權限有關啦！**此外， 工作目錄對於指令的執行是非常重要的，如果你在某目錄下不具有x的權限， 那麼你就無法切換到該目錄下，也就無法執行該目錄下的任何指令，即使你具有該目錄的r或w的權限。 

```
kevin@ubuntu:~/os/os_note$ su root
Password: 
root@ubuntu:/home/kevin/os/os_note# mkdir test
root@ubuntu:/home/kevin/os/os_note# chmod 744 test/
root@ubuntu:/home/kevin/os/os_note# ls -al 
total 32
drwxrwxr-x 8 kevin kevin 4096 Oct 20 17:09 .
drwxrwxr-x 6 kevin kevin 4096 Oct 20 15:33 ..
drwxrwxr-x 3 kevin kevin 4096 Oct  9 16:31 elementary_knowledge
drwxrwxr-x 2 kevin kevin 4096 Oct 11 14:59 install_centos
drwxrwxr-x 2 kevin kevin 4096 Oct 18 16:11 linux_command
drwxrwxr-x 3 kevin kevin 4096 Oct  9 17:51 linux_environment
drwxrwxr-x 3 kevin kevin 4096 Oct 20 10:02 linux_file
drwxr--r-- 2 root  root  4096 Oct 20 17:09 test
root@ubuntu:/home/kevin/os/os_note# touch test/test
root@ubuntu:/home/kevin/os/os_note# chmod test/test 
chmod: missing operand after ‘test/test’
Try 'chmod --help' for more information.
root@ubuntu:/home/kevin/os/os_note# chmod 600 test/test 
root@ubuntu:/home/kevin/os/os_note# ls -al test/ test/test 
-rw------- 1 root root    0 Oct 20 17:09 test/test
test/:
total 8
drwxr--r-- 2 root  root  4096 Oct 20 17:09 .

drwxrwxr-x 8 kevin kevin 4096 Oct 20 17:09 ..
-rw------- 1 root  root     0 Oct 20 17:09 test
root@ubuntu:/home/kevin/os/os_note# su kevin
kevin@ubuntu:~/os/os_note$ ls
elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test
kevin@ubuntu:~/os/os_note$ cd test/
bash: cd: test/: Permission denied
kevin@ubuntu:~/os/os_note$ ls -l test/
ls: cannot access 'test/test': Permission denied
total 0
-????????? ? ? ? ?            ? test
```

权限r：可以[ls]
权限x：可以[cd]
权限w: 可以修改

<div align=center><img src="/os_note/linux_file/picture/屏幕截图%202022-10-20%20171917.png"></div>

### 5.2.4 Linux檔案種類與副檔名
我們在基礎篇一直強調一個概念，那就是：任何裝置在Linux底下都是檔案， 不僅如此，連資料溝通的介面也有專屬的檔案在負責～所以，你會瞭解到，Linux的檔案種類真的很多～ 除了前面提到的**一般檔案(-)與目錄檔案(d)**之外，還有哪些種類的檔案呢？

#### Linux檔案種類
我們在剛剛提到使用『ls -l』觀察到第一欄那十個字元中，第一個字元為檔案的類型。 除了常見的一般檔案(-)與目錄檔案(d)之外，還有哪些種類的檔案類型呢？

##### 正規檔案(regular file )：
就是一般我們在進行存取的類型的檔案，在由 ls -al 所顯示出來的屬性方面，第一個字元為 [ - ]，例如 [-rwxrwxrwx ]。另外，依照檔案的內容，又大略可以分為：

- 純文字檔(ASCII)：這是Linux系統中最多的一種檔案類型囉， 稱為純文字檔是因為內容為我們人類可以直接讀到的資料，例如數字、字母等等。 幾乎只要我們可以用來做為設定的檔案都屬於這一種檔案類型。 舉例來說，**你可以下達『 cat ~/.bashrc 』就可以看到該檔案的內容。 (cat 是將一個檔案內容讀出來的指令**)

**cat命令**
```
kevin@ubuntu:~/os/os_note$ touch hello.txt
kevin@ubuntu:~/os/os_note$ ls
elementary_knowledge  hello.txt  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ chmod u+rwx hello.txt 
kevin@ubuntu:~/os/os_note$ ls
elementary_knowledge  hello.txt  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ nano hello.txt 
kevin@ubuntu:~/os/os_note$ echo "add word:hello in hello.txt"
add word:hello in hello.txt
kevin@ubuntu:~/os/os_note$ cat hello.txt 
hello world
```

- 二進位檔(binary)：還記得我們在『 第零章、計算機概論 』裡面的軟體程式的運作中提過， 我們的系統其實僅認識且可以執行二進位檔案(binary file)吧？沒錯～ 你的Linux當中的可執行檔(scripts, 文字型批次檔不算)就是這種格式的啦～ 舉例來說，剛剛下達的指令cat就是一個binary file。

- 資料格式檔(data)： 有些程式在運作的過程當中會讀取某些特定格式的檔案，那些特定格式的檔案可以被稱為資料檔 (data file)。舉例來說，我們的Linux在使用者登入時，都會將登錄的資料記錄在 /var/log/wtmp那個檔案內，該檔案是一個data file，他能夠透過last這個指令讀出來！ 但是使用cat時，會讀出亂碼～因為他是屬於一種特殊格式的檔案。瞭乎？

##### 目錄(directory)：
就是目錄囉～第一個屬性為 [ d ]，例如 [drwxrwxrwx]。

##### 連結檔(link)：
就是類似Windows系統底下的捷徑啦！ 第一個屬性為 [ l ](英文L的小寫)，例如 [lrwxrwxrwx] ；

##### 與系統周邊及儲存等相關的一些檔案

**通常都集中在/dev這個目錄之下！通常又分為兩種：**
- 區塊(block)設備檔 ：就是一些儲存資料， 以提供系統隨機存取的周邊設備，舉例來說，**硬碟與軟碟等**就是啦！ 你可以隨機的在硬碟的不同區塊讀寫，這種裝置就是區塊裝置囉！你可以自行查一下/dev/sda看看， 會發現第一個屬性為[ b ]喔！
- 字元(character)設備檔：**亦即是一些序列埠的周邊設備， 例如鍵盤、滑鼠等等！**這些設備的特色就是『一次性讀取』的，不能夠截斷輸出。 舉例來說，你不可能讓滑鼠『跳到』另一個畫面，而是『連續性滑動』到另一個地方啊！第一個屬性為 [ c ]。

##### 資料接口檔(sockets)：
既然被稱為資料接口檔， 想當然爾，這種類型的檔案通常被用在網路上的資料承接了。我們可以啟動一個程式來監聽用戶端的要求， 而用戶端就可以透過這個socket來進行資料的溝通了。第一個屬性為 [ s ]， 最常在/run或/tmp這些個目錄中看到這種檔案類型了。

##### 資料輸送檔(FIFO, pipe)：
FIFO也是一種特殊的檔案類型，他主要的目的在解決多個程序同時存取一個檔案所造成的錯誤問題。 FIFO是first-in-first-out的縮寫。第一個屬性為[p] 。

除了設備檔是我們系統中很重要的檔案，最好不要隨意修改之外(通常他也不會讓你修改的啦！)， 另一個比較有趣的檔案就是連結檔。如果你常常將應用程式捉到桌面來的話，你就應該知道在 Windows底下有所謂的『捷徑』。同樣的，你可以將 linux下的連結檔簡單的視為一個檔案或目錄的捷徑。 至於socket與FIFO檔案比較難理解，因為這兩個咚咚與程序(process)比較有關係， 這個等到未來你瞭解process之後，再回來查閱吧！此外， 你也可以透過man fifo及man socket來查閱系統上的說明！

#### Linux檔案副檔名(后缀)：
基本上，Linux的檔案是沒有所謂的『副檔名』的，我們剛剛就談過，一個Linux檔案能不能被執行，與他的第一欄的十個屬性有關， 與檔名根本一點關係也沒有。這個觀念跟Windows的情況不相同喔！在Windows底下， 能被執行的檔案副檔名通常是 .com .exe .bat等等，而在Linux底下，只要你的權限當中具有x的話，例如[ -rwxr-xr-x ] 即代表這個檔案具有可以被執行的能力喔！

**常用的后缀名**
- *.sh ： 腳本或批次檔 (scripts)，因為批次檔為使用shell寫成的，所以副檔名就編成 .sh 囉；
- Z, *.tar, *.tar.gz, *.zip, *.tgz： 經過打包的壓縮檔。這是因為壓縮軟體分別為 gunzip, tar 等等的，由於不同的壓縮軟體，而取其相關的副檔名囉！
- *.html, *.php：網頁相關檔案，分別代表 HTML 語法與 PHP 語法的網頁檔案囉！ .html 的檔案可使用網頁瀏覽器來直接開啟，至於 .php 的檔案， 則可以透過 client 端的瀏覽器來 server 端瀏覽，以得到運算後的網頁結果呢！

基本上，Linux系統上的檔名真的只是讓你瞭解該檔案可能的用途而已， 真正的執行與否仍然需要權限的規範才行！例如雖然有一個檔案為可執行檔， 如常見的/bin/ls這個顯示檔案屬性的指令，不過，如果這個檔案的權限被修改成無法執行時， 那麼ls就變成不能執行囉！

上述的這種問題最常發生在檔案傳送的過程中。例如你在網路上下載一個可執行檔，但是偏偏在你的 Linux系統中就是無法執行！呵呵！那麼就是可能檔案的屬性被改變了！不要懷疑，從網路上傳送到你的 Linux系統中，檔案的屬性與權限確實是會被改變的喔！

##### Linux檔名長度限制(註1)：
在Linux底下，使用傳統的Ext2/Ext3/Ext4檔案系統以及近來被 CentOS 7 當作預設檔案系統的 xfs 而言，針對檔案的檔名長度限制為：
- 單一檔案或目錄的最大容許檔名為 255bytes，以一個 ASCII 英文佔用一個 bytes 來說，則大約可達 255 個字元長度。若是以每個中文字佔用 2bytes 來說， 最大檔名就是大約在 128 個中文字之譜！

是相當長的檔名喔！我們希望Linux的檔案名稱可以一看就知道該檔案在幹嘛的， 所以檔名通常是很長很長！而用慣了Windows的人可能會受不了，因為檔案名稱通常真的都很長， 對於用慣Windows而導致打字速度不快的朋友來說，嗯！真的是很困擾.....不過，只得勸你好好的加強打字的訓練囉！

##### Linux檔案名稱的限制：
由於Linux在文字介面下的一些指令操作關係，一般來說，你在設定Linux底下的檔案名稱時， 最好可以避免一些特殊字元比較好！例如底下這些：

* ? > < ; & ! [ ] | \ ' " ` ( ) { }
因為這些符號在文字介面下，是有特殊意義的！另外，檔案名稱的開頭為小數點『.』時， 代表這個檔案為『隱藏檔』喔！同時，由於指令下達當中，常常會使用到 -option 之類的選項， 所以你最好也避免將檔案檔名的開頭以 - 或 + 來命名啊！

## 5.3 Linux目錄配置