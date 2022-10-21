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

### 5.3.1 Linux目錄配置的依據--FHS
因為利用Linux來開發產品或distributions的社群/公司與個人實在太多了，後來就有所謂的Filesystem Hierarchy Standard (FHS)標準的出爐了！
根據FHS(註2)的標準文件指出，他們的主要目的是希望讓使用者可以瞭解到已安裝軟體通常放置於那個目錄下， 所以他們希望獨立的軟體開發商、作業系統製作者、以及想要維護系統的使用者，都能夠遵循FHS的標準。 **也就是說，FHS的重點在於規範每個特定的目錄下應該要放置什麼樣子的資料而已**。 這樣做好處非常多，因為Linux作業系統就能夠在既有的面貌下(目錄架構不變)發展出開發者想要的獨特風格。
<div align=center><img src="/os_note/linux_file/picture/屏幕截图%202022-10-21%20103511.png"></div>

- 可分享的：可以分享給其他系統掛載使用的目錄，所以包括執行檔與使用者的郵件等資料， 是能夠分享給網路上其他主機掛載用的目錄；
- 不可分享的：自己機器上面運作的裝置檔案或者是與程序有關的socket檔案等， 由於僅與自身機器有關，所以當然就不適合分享給其他主機了。
- 不變的：有些資料是不會經常變動的，跟隨著distribution而不變動。 例如函式庫、文件說明檔、系統管理員所管理的主機服務設定檔等等；
- 可變動的：經常改變的資料，例如登錄檔、一般用戶可自行收受的新聞群組等。

事實上，FHS針對目錄樹架構僅定義出三層目錄底下應該放置什麼資料而已，分別是底下這三個目錄的定義：
- / (root, 根目錄)：與開機系統有關；
- /usr (unix software resource)：與軟體安裝/執行有關；
- /var (variable)：與系統運作過程有關。

#### 根目錄 (/) 的意義與內容：
根目錄是整個系統最重要的一個目錄，因為不但所有的目錄都是由根目錄衍生出來的，**同時根目錄也與開機/還原/系統修復等動作有關。** 由於系統開機時需要特定的開機軟體、核心檔案、開機所需程式、函式庫等等檔案資料，若系統出現錯誤時，根目錄也必須要包含有能夠修復檔案系統的程式才行。 因為根目錄是這麼的重要，所以在FHS的要求方面，他希望根目錄不要放在非常大的分割槽內， 因為越大的分割槽妳會放入越多的資料，如此一來根目錄所在分割槽就可能會有較多發生錯誤的機會。

因此FHS標準建議：**根目錄(/)所在分割槽應該越小越好， 且應用程式所安裝的軟體最好不要與根目錄放在同一個分割槽內，保持根目錄越小越好。** 如此不但效能較佳，根目錄所在的檔案系統也較不容易發生問題。

有鑑於上述的說明，因此FHS定義出根目錄(/)底下應該要有底下這些次目錄的存在才好，即使沒有實體目錄，FHS也希望至少有連結檔存在才好：

##### 第一部份：FHS 要求必須要存在的目錄
- /bin:系統有很多放置執行檔的目錄，但/bin比較特殊。**因為/bin放置的是在單人維護模式下還能夠被操作的指令。 在/bin底下的指令可以被root與一般帳號所使用**，主要有：cat, chmod, chown, date, mv, mkdir, cp, bash等等常用的指令。
- /boot:**這個目錄主要在放置開機會使用到的檔案**，包括Linux核心檔案以及開機選單與開機所需設定檔等等。 Linux kernel常用的檔名為：vmlinuz，如果使用的是grub2這個開機管理程式， 則還會存在/boot/grub2/這個目錄喔！

```
kevin@ubuntu:/$ cd boot/
kevin@ubuntu:/boot$ ls
config-5.4.0-128-generic  grub                          initrd.img-5.4.0-131-generic  memtest86+.elf            System.map-5.4.0-128-generic  vmlinuz-5.4.0-128-generic
config-5.4.0-131-generic  initrd.img-5.4.0-128-generic  memtest86+.bin                memtest86+_multiboot.bin  System.map-5.4.0-131-generic  vmlinuz-5.4.0-131-generic
```

- /dev:在Linux系統上，任何裝置與周邊設備都是以檔案的型態存在於這個目錄當中的。 你只要透過存取這個目錄底下的某個檔案，就等於存取某個裝置囉～ 比要重要的檔案有/dev/null, /dev/zero, /dev/tty, /dev/loop*, /dev/sd*等等
- /etc:系統主要的設定檔幾乎都放置在這個目錄內，例如人員的帳號密碼檔、 各種服務的啟始檔等等。一般來說，這個目錄下的各檔案屬性是可以讓一般使用者查閱的， 但是只有root有權力修改。FHS建議不要放置可執行檔(binary)在這個目錄中喔。比較重要的檔案有： /etc/modprobe.d/, /etc/passwd, /etc/fstab, /etc/issue 等等。另外 FHS 還規範幾個重要的目錄最好要存在 /etc/ 目錄下喔：
    - /etc/opt(必要)：這個目錄在放置第三方協力軟體 /opt 的相關設定檔
    - /etc/X11/(建議)：與 X Window 有關的各種設定檔都在這裡，尤其是 xorg.conf 這個 X Server 的設定檔。
    - /etc/sgml/(建議)：與 SGML 格式有關的各項設定檔
    - /etc/xml/(建議)：與 XML 格式有關的各項設定檔
- /lib:系統的函式庫非常的多，而/lib放置的則是在開機時會用到的函式庫， 以及在/bin或/sbin底下的指令會呼叫的函式庫而已。 什麼是函式庫呢？妳可以將他想成是『外掛』，某些指令必須要有這些『外掛』才能夠順利完成程式的執行之意。 另外 FHS 還要求底下的目錄必須要存在：/lib/modules/：這個目錄主要放置可抽換式的核心相關模組(驅動程式)喔！
- /media:	media是『媒體』的英文，顧名思義，這個/media底下放置的就是可移除的裝置啦！ 包括軟碟、光碟、DVD等等裝置都暫時掛載於此。常見的檔名有：/media/floppy, /media/cdrom等等。
- /mnt:	如果妳想要暫時掛載某些額外的裝置，一般建議妳可以放置到這個目錄中。 在古早時候，這個目錄的用途與/media相同啦！只是有了/media之後，這個目錄就用來暫時掛載用了。
- /opt: 	這個是給第三方協力軟體放置的目錄。什麼是第三方協力軟體啊？ 舉例來說，KDE這個桌面管理系統是一個獨立的計畫，不過他可以安裝到Linux系統中，因此KDE的軟體就建議放置到此目錄下了。 另外，如果妳想要自行安裝額外的軟體(非原本的distribution提供的)，那麼也能夠將你的軟體安裝到這裡來。 不過，以前的Linux系統中，我們還是習慣放置在/usr/local目錄下呢！
- /run: 早期的 FHS 規定系統開機後所產生的各項資訊應該要放置到 /var/run 目錄下，新版的 FHS 則規範到 /run 底下。 由於 /run 可以使用記憶體來模擬，因此效能上會好很多！
- /sbin: Linux有非常多指令是用來設定系統環境的，這些指令只有root才能夠利用來『設定』系統，其他使用者最多只能用來『查詢』而已。 **放在/sbin底下的為開機過程中所需要的，裡面包括了開機、修復、還原系統所需要的指令。** 至於某些伺服器軟體程式，一般則放置到/usr/sbin/當中。至於本機自行安裝的軟體所產生的系統執行檔(system binary)， 則放置到/usr/local/sbin/當中了。常見的指令包括：fdisk, fsck, ifconfig, mkfs等等。
- /srv: srv可以視為『service』的縮寫，是一些網路服務啟動之後，這些服務所需要取用的資料目錄。 常見的服務例如WWW, FTP等等。舉例來說，WWW伺服器需要的網頁資料就可以放置在/srv/www/裡面。 不過，系統的服務資料如果尚未要提供給網際網路任何人瀏覽的話，預設還是建議放置到 /var/lib 底下即可。
- /tmp: 這是讓一般使用者或者是正在執行的程序暫時放置檔案的地方。 這個目錄是任何人都能夠存取的，所以你需要定期的清理一下。當然，重要資料不可放置在此目錄啊！ 因為FHS甚至建議在開機時，應該要將/tmp下的資料都刪除唷！
- /usr 第二层FHS    
- /var 第二层FHS

##### 應放置檔案內容
- /lost+found: 這個目錄是使用標準的ext2/ext3/ext4檔案系統格式才會產生的一個目錄，目的在於當檔案系統發生錯誤時， 將一些遺失的片段放置到這個目錄下。不過如果使用的是 xfs 檔案系統的話，就不會存在這個目錄了！
- proc:這個目錄本身是一個『虛擬檔案系統(virtual filesystem)』喔！他放置的資料都是在記憶體當中， 例如系統核心、行程資訊(process)、周邊裝置的狀態及網路狀態等等。因為這個目錄下的資料都是在記憶體當中， 所以本身不佔任何硬碟空間啊！比較重要的檔案例如：/proc/cpuinfo, /proc/dma, /proc/interrupts, /proc/ioports, /proc/net/* 等等。
- /sys: 這個目錄其實跟/proc非常類似，也是一個虛擬的檔案系統，主要也是記錄核心與系統硬體資訊較相關的資訊。 包括目前已載入的核心模組與核心偵測到的硬體裝置資訊等等。這個目錄同樣不佔硬碟容量喔！

早期 Linux 在設計的時候，若發生問題時，救援模式通常僅掛載根目錄而已，因此有五個重要的目錄被要求一定要與根目錄放置在一起， 那就是 /etc, /bin, /dev, /lib, /sbin 這五個重要目錄。現在許多的 Linux distributions 由於已經將許多非必要的檔案移出 /usr 之外了， 所以 /usr 也是越來越精簡，同時因為 /usr 被建議為『即使掛載成為唯讀，系統還是可以正常運作』的模樣，所以救援模式也能同時掛載 /usr 喔！ 

#### /usr 的意義與內容：
依據FHS的基本定義，/usr裡面放置的資料屬於可分享的與不可變動的(shareable, static)， 如果你知道如何透過網路進行分割槽的掛載(例如在伺服器篇會談到的NFS伺服器)，那麼/usr確實可以分享給區域網路內的其他主機來使用喔！

**很多讀者都會誤會/usr為user的縮寫，其實usr是Unix Software Resource的縮寫， 也就是『Unix作業系統軟體資源』所放置的目錄，而不是使用者的資料啦**！這點要注意。 FHS建議所有軟體開發者，應該將他們的資料合理的分別放置到這個目錄下的次目錄，而不要自行建立該軟體自己獨立的目錄。

- /usr/bin/ 	所有一般用戶能夠使用的指令都放在這裡！目前新的 CentOS 7 已經將全部的使用者指令放置於此，而使用連結檔的方式將 /bin 連結至此！ 也就是說， /usr/bin 與 /bin 是一模一樣了！另外，FHS 要求在此目錄下不應該有子目錄！
- /usr/lib/     基本上，與 /lib 功能相同，所以 /lib 就是連結到此目錄中的！
- /usr/local/   **系統管理員在本機自行安裝自己下載的軟體(非distribution預設提供者)，建議安裝到此目錄**， 這樣會比較便於管理。舉例來說，你的distribution提供的軟體較舊，你想安裝較新的軟體但又不想移除舊版， 此時你可以將新版軟體安裝於/usr/local/目錄下，可與原先的舊版軟體有分別啦！ 你可以自行到/usr/local去看看，該目錄下也是具有bin, etc, include, lib...的次目錄喔！
- /usr/sbin/    非系統正常運作所需要的系統指令。最常見的就是某些網路伺服器軟體的服務指令(daemon)囉！不過基本功能與 /sbin 也差不多， 因此目前 /sbin 就是連結到此目錄中的。
- /usr/share/   主要放置唯讀架構的資料檔案，當然也包括共享文件。在這個目錄下放置的資料幾乎是不分硬體架構均可讀取的資料， 因為幾乎都是文字檔案嘛！在此目錄下常見的還有這些次目錄：
    - /usr/share/man：線上說明文件
    - /usr/share/doc：軟體雜項的文件說明
    - /usr/share/zoneinfo：與時區有關的時區檔案

- /usr/games/   	與遊戲比較相關的資料放置處
- /usr/include/     c/c++等程式語言的檔頭(header)與包含檔(include)放置處，當我們以tarball方式 (*.tar.gz 的方式安裝軟體)安裝某些資料時，會使用到裡頭的許多包含檔喔！
- /usr/libexec/     	某些不被一般使用者慣用的執行檔或腳本(script)等等，都會放置在此目錄中。例如大部分的 X 視窗底下的操作指令， 很多都是放在此目錄下的。
- /usr/lib<qual>/		與 /lib<qual>/功能相同，因此目前 /lib<qual> 就是連結到此目錄中
- /usr/src/         	一般原始碼建議放置到這裡，src有source的意思。至於核心原始碼則建議放置到/usr/src/linux/目錄下。


#### /var 的意義與內容：
如果/usr是安裝時會佔用較大硬碟容量的目錄，**那麼/var就是在系統運作後才會漸漸佔用硬碟容量的目錄。 因為/var目錄主要針對常態性變動的檔案，包括快取(cache)、登錄檔(log file)以及某些軟體運作所產生的檔案， 包括程序檔案(lock file, run file)，或者例如MySQL資料庫的檔案等等。** 常見的次目錄有：
##### 第一部份：FHS 要求必須要存在的目錄
- /var/cache/	應用程式本身運作過程中會產生的一些暫存檔；
- /var/lib/	程式本身執行的過程中，需要使用到的資料檔案放置的目錄。在此目錄下各自的軟體應該要有各自的目錄。 舉例來說，MySQL的資料庫放置到/var/lib/mysql/而rpm的資料庫則放到/var/lib/rpm去！
- /var/lock/    锁机制实现
- /var/log/     登錄檔放置的目錄！裡面比較重要的檔案如/var/log/messages, /var/log/wtmp(記錄登入者的資訊)等。
- /var/mail/    放置個人電子郵件信箱的目錄
- /var/run/     某些程式或者是服務啟動後，會將他們的PID放置在這個目錄下喔！至於PID的意義我們會在後續章節提到的。 與 /run 相同，這個目錄連結到 /run 去了！
- /var/spool/	這個目錄通常放置一些佇列資料，所謂的『佇列』就是排隊等待其他程式使用的資料啦！ 這些資料被使用後通常都會被刪除。舉例來說，系統收到新信會放置到/var/spool/mail/中， 但使用者收下該信件後該封信原則上就會被刪除。信件如果暫時寄不出去會被放到/var/spool/mqueue/中， 等到被送出後就被刪除。如果是工作排程資料(crontab)，就會被放置到/var/spool/cron/目錄中！

### 5.3.2 目錄樹(directory tree)
```
kevin@ubuntu:/$ ls -l
total 1459916
drwxr-xr-x   2 root root       4096 Oct 13 17:25 bin
drwxr-xr-x   3 root root       4096 Oct 21 10:10 boot
drwxrwxr-x   2 root root       4096 Mar 23  2022 cdrom
drwxr-xr-x  17 root root       4420 Oct 21 15:39 dev
drwxr-xr-x 144 root root      12288 Oct 20 09:53 etc
drwxr-xr-x   3 root root       4096 Mar 23  2022 home
lrwxrwxrwx   1 root root         33 Oct 20 09:54 initrd.img -> boot/initrd.img-5.4.0-131-generic
lrwxrwxrwx   1 root root         33 Oct 20 09:54 initrd.img.old -> boot/initrd.img-5.4.0-128-generic
drwxr-xr-x  21 root root       4096 Oct 13 17:25 lib
drwxr-xr-x   2 root root       4096 Oct 13 17:25 lib64
drwx------   2 root root      16384 Mar 24  2022 lost+found
drwxr-xr-x   4 root root       4096 Apr 21  2022 media
drwxr-xr-x   2 root root       4096 Feb  4  2020 mnt
drwxr-xr-x   5 root root       4096 Oct 11 16:41 opt
dr-xr-xr-x 429 root root          0 Oct 21 15:39 proc
drwx------   5 root root       4096 Apr 13  2022 root
drwxr-xr-x  29 root root        940 Oct 21 15:40 run
drwxr-xr-x   2 root root      12288 Oct 13 17:25 sbin
drwxr-xr-x  19 root root       4096 Oct 18 09:27 snap
drwxr-xr-x   2 root root       4096 Feb  4  2020 srv
-rw-------   1 root root 1494845440 Mar 23  2022 swapfile
dr-xr-xr-x  13 root root          0 Oct 21 15:39 sys
drwxrwxrwt  21 root root       4096 Oct 21 17:40 tmp
drwxr-xr-x  12 root root       4096 Oct 13 15:50 usr
drwxr-xr-x  14 root root       4096 Feb  4  2020 var
lrwxrwxrwx   1 root root         30 Oct 20 09:54 vmlinuz -> boot/vmlinuz-5.4.0-131-generic
lrwxrwxrwx   1 root root         30 Oct 20 09:54 vmlinuz.old -> boot/vmlinuz-5.4.0-128-generic
```
根據FHS的定義，妳最好能夠將/var獨立出來， 這樣對於系統的資料還有一些安全性的保護呢！因為至少/var死掉時，你的根目錄還會活著嘛！ 還能夠進入救援模式啊！

### 5.3.3 絕對路徑與相對路徑

除了需要特別注意的FHS目錄配置外，在檔名部分我們也要特別注意喔！因為根據檔名寫法的不同，也可將所謂的路徑(path)定義為絕對路徑(absolute)與相對路徑(relative)。 這兩種檔名/路徑的寫法依據是這樣的：
* **絕對路徑：由根目錄(/)開始寫起的檔名或目錄名稱， 例如 /home/dmtsai/.bashrc；**
* **相對路徑：相對於目前路徑的檔名寫法。 例如 ./home/dmtsai 或 ../../home/dmtsai/ 等等。反正開頭不是 / 就屬於相對路徑的寫法**

### 5.3.4 CentOS 的觀察
1. 透過 uname 檢查 Linux 核心與作業系統的位元版本
```
kevin@ubuntu:/$ uname -a
Linux ubuntu 5.4.0-131-generic #147~18.04.1-Ubuntu SMP Sat Oct 15 13:10:18 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
kevin@ubuntu:/$ man uname
kevin@ubuntu:/$ uname -v
#147~18.04.1-Ubuntu SMP Sat Oct 15 13:10:18 UTC 2022
kevin@ubuntu:/$ uname -r
5.4.0-131-generic
```

## 5.4 重點回顧
- Linux的每個檔案中，可分別給予擁有者、群組與其他人三種身份個別的 rwx 權限；
- 群組最有用的功能之一，就是當你在團隊開發資源的時候，且每個帳號都可以有多個群組的支援；
- 利用ls -l顯示的檔案屬性中，第一個欄位是檔案的權限，共有十個位元，第一個位元是檔案類型， 接下來三個為一組共三組，為擁有者、群組、其他人的權限，權限有r,w,x三種；
- 如果檔名之前多一個『 . 』，則代表這個檔案為『隱藏檔』；
- 若需要root的權限時，可以使用 su - 這個指令來切換身份。處理完畢則使用 exit 離開 su 的指令環境。
- 更改檔案的群組支援可用chgrp，修改檔案的擁有者可用chown，修改檔案的權限可用chmod
- chmod修改權限的方法有兩種，分別是符號法與數字法，數字法中r,w,x分數為4,2,1；
  - 對檔案來講，權限的效能為：
    - r：可讀取此一檔案的實際內容，如讀取文字檔的文字內容等；
    - w：可以編輯、新增或者是修改該檔案的內容(但不含刪除該檔案)；
    - x：該檔案具有可以被系統執行的權限。
  - 對目錄來說，權限的效能為：
    - r (read contents in directory)
    - w (modify contents of directory)
    - x (access directory)
- 要開放目錄給任何人瀏覽時，應該至少也要給予r及x的權限，但w權限不可隨便給；
- 能否讀取到某個檔案內容，跟該檔案所在的目錄權限也有關係 (目錄至少需要有 x 的權限)。
- Linux檔名的限制為：單一檔案或目錄的最大容許檔名為 255 個英文字元或 128 個中文字元；
- 根據FHS的官方文件指出， 他們的主要目的是希望讓使用者可以瞭解到已安裝軟體通常放置於那個目錄下
- FHS訂定出來的四種目錄特色為：shareable, unshareable, static, variable等四類；
- FHS所定義的三層主目錄為：/, /var, /usr三層而已；
- 絕對路徑檔名為從根目錄 / 開始寫起，否則都是相對路徑的檔名。

---
# 第六章、Linux 檔案與目錄管理
## 6.1 目錄與路徑
### 6.1.1 相對路徑與絕對路徑

##### 相對路徑的用途
如果需要用到絕對路徑的話，那麼是否很麻煩呢？是的！ 如此一來每個目錄下的東西就很難對應的起來！這個時候相對路徑的寫法就顯的特別的重要了！

**相对路径比较方便** 

##### 絕對路徑的用途

但是對於檔名的正確性來說，『絕對路徑的正確度要比較好～』。 一般來說，鳥哥會建議你，**如果是在寫程式 (shell scripts) 來管理系統的條件下，務必使用絕對路徑的寫法。** 怎麼說呢？因為絕對路徑的寫法雖然比較麻煩，但是可以肯定這個寫法絕對不會有問題。 如果使用相對路徑在程式當中，則可能由於你執行的工作環境不同，導致一些問題的發生。 這個問題在工作排程(at, cron, 第十五章)當中尤其重要！這個現象我們在十二章、shell script時，會再次的提醒你喔！ ^_^

### 6.1.2 目錄的相關操作
我們之前稍微提到變換目錄的指令是cd，還有哪些可以進行目錄操作的指令呢？ 例如建立目錄啊、刪除目錄之類的～還有，得要先知道的，就是有哪些比較特殊的目錄呢？ 舉例來說，底下這些就是比較特殊的目錄，得要用力的記下來才行：
>.         代表此層目錄
>..        代表上一層目錄
>\-         代表前一個工作目錄
>~         **代表『目前使用者身份』所在的家目錄**
>~account  **代表 account 這個使用者的家目錄(account是個帳號名稱)**

>例題：
>   請問在Linux底下，根目錄下有沒有上層目錄(..)存在？
>答：
>   若使用『 ls -al / 』去查詢，可以看到根目錄下確實存在 . 與 .. 兩個目錄，再仔細的查閱， 可發現這兩個目錄的屬性與權限完全一致，這代表根目錄的上一層(..)與根目錄自己(.)是同一個目錄。

```
kevin@ubuntu:/$ cd ..
kevin@ubuntu:/$ 
```
底下我們就來談一談幾個常見的處理目錄的指令吧：

- cd：變換目錄
- pwd：顯示目前的目錄
- mkdir：建立一個新的目錄
- rmdir：刪除一個空的目錄

**cd**
```
kevin@ubuntu:/$ cd ~
kevin@ubuntu:~$ pwd
/home/kevin
```

用-实例
```
kevin@ubuntu:~$ cd os
kevin@ubuntu:~/os$ cd -
/home/kevin
kevin@ubuntu:~$ cd os/os_note/
kevin@ubuntu:~/os/os_note$ ls
elementary_knowledge  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ cd install_centos/
kevin@ubuntu:~/os/os_note/install_centos$ cd -
/home/kevin/os/os_note
kevin@ubuntu:~/os/os_note$ 
```

**pwd**

使用man pwd
NAME
       pwd - print name of current/working directory

SYNOPSIS
       pwd [OPTION]...

DESCRIPTION
       Print the full filename of the current working directory.

       -L, --logical
              use PWD from environment, even if it contains symlinks

       -P, --physical
              avoid all symlinks

一般就用pwd吧

**mkdir (建立新目錄)**

>[root@study ~]# mkdir [-mp] 目錄名稱
>選項與參數：
>-m ：設定檔案的權限喔！直接設定，不需要看預設權限 (umask) 的臉色～
>-p ：幫助你直接將所需要的目錄(包含上層目錄)遞迴建立起來！

mkdir -m 设置权限
```
kevin@ubuntu:~/os/os_note$ mkdir -m 755 test
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test
```

mkdir -p 设置多级文件
```
kevin@ubuntu:~/os/os_note$ mkdir -p compress/picture
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ cd compress/
kevin@ubuntu:~/os/os_note/compress$ ls
picture
```

**rmdir (刪除『空』的目錄)**
```
[root@study ~]# rmdir [-p] 目錄名稱
選項與參數：
-p ：連同『上層』『空的』目錄也一起刪除
```

### 6.1.3 關於執行檔路徑的變數： $PATH
經過前一章FHS的說明後，我們知道查閱檔案屬性的指令ls完整檔名為：/bin/ls(這是絕對路徑)， 那你會不會覺得很奇怪：『為什麼我可以在任何地方執行/bin/ls這個指令呢？ 』 **為什麼我在任何目錄下輸入 ls 就一定可以顯示出一些訊息而不會說找不到該 /bin/ls 指令呢？ 這是因為環境變數 PATH 的幫助所致呀！**
```
kevin@ubuntu:~/os/os_note$ /bin/ls 
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file
```

echo $path
```
kevin@ubuntu:~/os/os_note$ echo $PATH
/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a075/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

**PATH(一定是大寫)這個變數的內容是由一堆目錄所組成的，每個目錄中間用冒號(:)來隔開， 每個目錄是有『順序』之分的。**仔細看一下上面的輸出，妳可以發現到無論是root還是dmtsai都有 /bin 或 /usr/bin 這個目錄在PATH變數內，所以當然就能夠在任何地方執行ls來找到/bin/ls執行檔囉！因為 /bin 在 CentOS 7 當中，就是連結到 /usr/bin 去的！ 所以這兩個目錄內容會一模一樣！

如果想要讓root在任何目錄均可執行/root底下的ls，那麼就將/root加入PATH當中即可。 加入的方法很簡單，就像底下這樣：
```
[root@study ~]# PATH="${PATH}:/root"
```
上面這個作法就能夠將/root加入到執行檔搜尋路徑PATH中了！不相信的話請您自行使用『echo $PATH』去查看吧！ 另外，除了 $PATH 之外，如果想要更明確的定義出變數的名稱，可以使用大括號 ${PATH} 來處理變數的呼叫喔！

```
kevin@ubuntu:~/os/os_note$ touch test.sh
kevin@ubuntu:~/os/os_note$ vim test.sh 
kevin@ubuntu:~/os/os_note$ chmod u+rwx test.sh 
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test.sh
kevin@ubuntu:~/os/os_note$ ./test.sh 
hello world
kevin@ubuntu:~/os/os_note$ mv test.sh ../
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ ls ..
os_experiment  os_note  test.sh  路线图.jpg
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file
kevin@ubuntu:~/os/os_note$ ./test.sh
bash: ./test.sh: No such file or directory
kevin@ubuntu:~/os/os_note$ pwd
/home/kevin/os/os_note
kevin@ubuntu:~/os/os_note$ PATH="${PATH}:/home/kevin/os" #临时添加
kevin@ubuntu:~/os/os_note$ echo $PATH
/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/opt/ros/melodic/bin:/home/kevin/.vscode-server/bin/d045a5eda657f4d7b676dedbfa7aab8207f8a075/bin/remote-cli:/usr/local/riscv64-linux-musl-cross/bin:/usr/local/riscv64-unknown-elf-gcc/bin:/home/kevin/qemu-5.0.0/riscv64-linux-user:/home/kevin/qemu-5.0.0/riscv64-softmmu:/home/kevin/qemu-5.0.0:/usr/lib/ccache:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/kevin/os
kevin@ubuntu:~/os/os_note$ test.sh
hello world
```
// 命令行输入ls,test.sh 这些可执行文件之后，若当前目录没有可执行文件，在$PATH中文件寻找
可执行文件。

PATH=""

- 不同身份使用者預設的PATH不同，預設能夠隨意執行的指令也不同(如root與dmtsai)；
- PATH是可以修改的；
- 使用絕對路徑或相對路徑直接指定某個指令的檔名來執行，會比搜尋PATH來的正確；
- 指令應該要放置到正確的目錄下，執行才會比較方便；
- 本目錄(.)最好不要放到PATH當中。
