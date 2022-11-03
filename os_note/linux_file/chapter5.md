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

## 6.2 檔案與目錄管理
談了談目錄與路徑之後，再來討論一下關於檔案的一些基本管理吧！檔案與目錄的管理上，不外乎『顯示屬性』、 『拷貝』、『刪除檔案』及『移動檔案或目錄』等等，由於檔案與目錄的管理在 Linux 當中是很重要的， 尤其是每個人自己家目錄的資料也都需要注意管理！所以我們來談一談有關檔案與目錄的一些基礎管理部分吧！
### 6.2.1 檔案與目錄的檢視： ls
```
[root@study ~]# ls [-aAdfFhilnrRSt] 檔名或目錄名稱..
[root@study ~]# ls [--color={never,auto,always}] 檔名或目錄名稱..
[root@study ~]# ls [--full-time] 檔名或目錄名稱..
選項與參數：
-a  ：全部的檔案，連同隱藏檔( 開頭為 . 的檔案) 一起列出來(常用)
-A  ：全部的檔案，連同隱藏檔，但不包括 . 與 .. 這兩個目錄
-d  ：僅列出目錄本身，而不是列出目錄內的檔案資料(常用)
-f  ：直接列出結果，而不進行排序 (ls 預設會以檔名排序！)
-F  ：根據檔案、目錄等資訊，給予附加資料結構，例如：
      *:代表可執行檔； /:代表目錄； =:代表 socket 檔案； |:代表 FIFO 檔案；
-h  ：將檔案容量以人類較易讀的方式(例如 GB, KB 等等)列出來；
-i  ：列出 inode 號碼，inode 的意義下一章將會介紹；
-l  ：長資料串列出，包含檔案的屬性與權限等等資料；(常用)
-n  ：列出 UID 與 GID 而非使用者與群組的名稱 (UID與GID會在帳號管理提到！)
-r  ：將排序結果反向輸出，例如：原本檔名由小到大，反向則為由大到小；
-R  ：連同子目錄內容一起列出來，等於該目錄下的所有檔案都會顯示出來；
-S  ：以檔案容量大小排序，而不是用檔名排序；
-t  ：依時間排序，而不是用檔名。
--color=never  ：不要依據檔案特性給予顏色顯示；
--color=always ：顯示顏色
--color=auto   ：讓系統自行依據設定來判斷是否給予顏色
--full-time    ：以完整時間模式 (包含年、月、日、時、分) 輸出
--time={atime,ctime} ：輸出 access 時間或改變權限屬性時間 (ctime) 
                       而非內容變更時間 (modification time)
```

所以，**當你只有下達 ls 時，預設顯示的只有：非隱藏檔的檔名、 以檔名進行排序及檔名代表的顏色顯示如此而已。**舉例來說， 你下達『 ls /etc 』之後，只有經過排序的檔名以及以藍色顯示目錄及白色顯示一般檔案，如此而已。

```
範例一：將家目錄下的所有檔案列出來(含屬性與隱藏檔)
[root@study ~]# ls -al ~
total 56
dr-xr-x---.  5 root root 4096 Jun  4 19:49 .
dr-xr-xr-x. 17 root root 4096 May  4 17:56 ..
-rw-------.  1 root root 1816 May  4 17:57 anaconda-ks.cfg
-rw-------.  1 root root 6798 Jun  4 19:53 .bash_history
-rw-r--r--.  1 root root   18 Dec 29  2013 .bash_logout
-rw-r--r--.  1 root root  176 Dec 29  2013 .bash_profile
-rw-rw-rw-.  1 root root  176 Dec 29  2013 .bashrc
-rw-r--r--.  1 root root  176 Jun  3 00:04 .bashrc_test
drwx------.  4 root root   29 May  6 00:14 .cache
drwxr-xr-x.  3 root root   17 May  6 00:14 .config
# 這個時候你會看到以 . 為開頭的幾個檔案，以及目錄檔 (.) (..) .config 等等，
# 不過，目錄檔檔名都是以深藍色顯示，有點不容易看清楚就是了。
```

```
範例二：承上題，不顯示顏色，但在檔名末顯示出該檔名代表的類型(type)
[root@study ~]# ls -alF --color=never  ~
total 56
dr-xr-x---.  5 root root 4096 Jun  4 19:49 ./
dr-xr-xr-x. 17 root root 4096 May  4 17:56 ../
-rw-------.  1 root root 1816 May  4 17:57 anaconda-ks.cfg
-rw-------.  1 root root 6798 Jun  4 19:53 .bash_history
-rw-r--r--.  1 root root   18 Dec 29  2013 .bash_logout
-rw-r--r--.  1 root root  176 Dec 29  2013 .bash_profile
-rw-rw-rw-.  1 root root  176 Dec 29  2013 .bashrc
-rw-r--r--.  1 root root  176 Jun  3 00:04 .bashrc_test
drwx------.  4 root root   29 May  6 00:14 .cache/
drwxr-xr-x.  3 root root   17 May  6 00:14 .config/
# 注意看到顯示結果的第一行，嘿嘿～知道為何我們會下達類似 ./command 
# 之類的指令了吧？因為 ./ 代表的是『目前目錄下』的意思啊！至於什麼是 FIFO/Socket ？
# 請參考前一章節的介紹啊！另外，那個.bashrc 時間僅寫2013，能否知道詳細時間？
```

```
kevin@ubuntu:~/os$ ls -al --full-time
total 528
drwxrwxr-x  6 kevin kevin   4096 2022-10-21 22:00:02.064017917 +0800 .
drwxr-xr-x 40 kevin kevin   4096 2022-10-22 10:42:41.948637341 +0800 ..
drwxrwxr-x  9 kevin kevin   4096 2022-10-21 22:01:43.407121353 +0800 .git
-rw-rw-r--  1 kevin kevin    141 2022-10-13 17:55:47.039085278 +0800 .gitmodules
drwxrwxr-x  5 kevin kevin   4096 2022-10-18 15:42:59.322451909 +0800 os_experiment
drwxrwxr-x  8 kevin kevin   4096 2022-10-21 21:38:44.634544445 +0800 os_note
drwxrwxr-x  2 kevin kevin   4096 2022-10-19 17:33:32.701266390 +0800 .vscode
-rwxrw-rw-  1 kevin kevin 508889 2022-10-09 15:33:14.941494000 +0800 路线图.jpg
```

無論如何， ls 最常被使用到的功能還是那個 -l 的選項，為此，很多 distribution 在預設的情況中， 已經將 ll (L 的小寫) 設定成為 ls -l 的意思了！其實，那個功能是 Bash shell 的 alias 功能呢～也就是說，我們直接輸入 ll 就等於是輸入 ls -l 是一樣的～關於這部分，我們會在後續 bash shell 時再次的強調滴～
```
kevin@ubuntu:~/os$ ls -al
total 528
drwxrwxr-x  6 kevin kevin   4096 Oct 21 22:00 .
drwxr-xr-x 40 kevin kevin   4096 Oct 22 10:42 ..
drwxrwxr-x  9 kevin kevin   4096 Oct 21 22:01 .git
-rw-rw-r--  1 kevin kevin    141 Oct 13 17:55 .gitmodules
drwxrwxr-x  5 kevin kevin   4096 Oct 18 15:42 os_experiment
drwxrwxr-x  8 kevin kevin   4096 Oct 21 21:38 os_note
drwxrwxr-x  2 kevin kevin   4096 Oct 19 17:33 .vscode
-rwxrw-rw-  1 kevin kevin 508889 Oct  9 15:33 路线图.jpg
kevin@ubuntu:~/os$ ls -l
total 508
drwxrwxr-x 5 kevin kevin   4096 Oct 18 15:42 os_experiment
drwxrwxr-x 8 kevin kevin   4096 Oct 21 21:38 os_note
-rwxrw-rw- 1 kevin kevin 508889 Oct  9 15:33 路线图.jpg
```

### 6.2.2 複製、刪除與移動： cp, rm, mv
要複製檔案，請使用 cp (copy) 這個指令即可～不過， cp 這個指令的用途可多了～ 除了單純的複製之外，還可以建立連結檔 (就是捷徑囉)，比對兩檔案的新舊而予以更新， 以及複製整個目錄等等的功能呢！至於移動目錄與檔案，則使用 mv (move)， 這個指令也可以直接拿來作更名 (rename) 的動作喔！至於移除嗎？那就是 rm (remove) 這個指令囉～底下我們就來瞧一瞧先～

**cp (複製檔案或目錄)**
```
[root@study ~]# cp [-adfilprsu] 來源檔(source) 目標檔(destination)
[root@study ~]# cp [options] source1 source2 source3 .... directory
選項與參數：
-a  ：相當於 -dr --preserve=all 的意思，至於 dr 請參考下列說明；(常用)
-d  ：若來源檔為連結檔的屬性(link file)，則複製連結檔屬性而非檔案本身；
-f  ：為強制(force)的意思，若目標檔案已經存在且無法開啟，則移除後再嘗試一次；
-i  ：若目標檔(destination)已經存在時，在覆蓋時會先詢問動作的進行(常用)
-l  ：進行硬式連結(hard link)的連結檔建立，而非複製檔案本身；
-p  ：連同檔案的屬性(權限、用戶、時間)一起複製過去，而非使用預設屬性(備份常用)；
-r  ：遞迴持續複製，用於目錄的複製行為；(常用)
-s  ：複製成為符號連結檔 (symbolic link)，亦即『捷徑』檔案；
-u  ：destination 比 source 舊才更新 destination，或 destination 不存在的情況下才複製。
--preserve=all ：除了 -p 的權限相關參數外，還加入 SELinux 的屬性, links, xattr 等也複製了。
最後需要注意的，如果來源檔有兩個以上，則最後一個目的檔一定要是『目錄』才行！
```
這個 cp 的功能很多，由於我們常常會進行一些資料的複製，所以也會常常用到這個指令的。 一般來說，我們如果去複製別人的資料 (當然，該檔案你必須要有 read 的權限才行啊！ ^_^) 時， 總是希望複製到的資料最後是我們自己的，所以，在預設的條件中， **cp 的來源檔與目的檔的權限是不同的，目的檔的擁有者通常會是指令操作者本身**。舉例來說， **上面的範例二中，由於我是 root 的身份，因此複製過來的檔案擁有者與群組就改變成為 root 所有了！**這樣說，可以明白嗎？^_^

由於具有這個特性，**因此當我們在進行備份的時候，某些需要特別注意的特殊權限檔案， 例如密碼檔 (/etc/shadow) 以及一些設定檔，就不能直接以 cp 來複製，而必須要加上 -a 或者是 -p 等等可以完整複製檔案權限的選項才行！**另外，如果你想要複製檔案給其他的使用者， 也必須要注意到檔案的權限(包含讀、寫、執行以及檔案擁有者等等)， 否則，其他人還是無法針對你給予的檔案進行修訂的動作喔！注意注意！

```
範例三：複製 /etc/ 這個目錄下的所有內容到 /tmp 底下
[root@study tmp]# cp /etc/ /tmp
cp: omitting directory `/etc'   <== 如果是目錄則不能直接複製，要加上 -r 的選項
[root@study tmp]# cp -r /etc/ /tmp
# 還是要再次的強調喔！ -r 是可以複製目錄，但是，檔案與目錄的權限可能會被改變
# 所以，也可以利用『 cp -a /etc /tmp 』來下達指令喔！尤其是在備份的情況下！
```

範例四可有趣了！**使用 -l 及 -s 都會建立所謂的連結檔(link file)，但是這兩種連結檔卻有不一樣的情況。**這是怎麼一回事啊？ **那個 -l 就是所謂的實體連結(hard link)**，**至於 -s 則是符號連結(symbolic link)**， 簡單來說，**bashrc_slink 是一個『捷徑』，這個捷徑會連結到bashrc去！所以你會看到檔名右側會有個指向(->)的符號！**
```
範例四：將範例一複製的 bashrc 建立一個連結檔 (symbolic link)
[root@study tmp]# ls -l bashrc
-rw-r--r--. 1 root root 176 Jun 11 19:01 bashrc  <==先觀察一下檔案情況
[root@study tmp]# cp -s bashrc bashrc_slink
[root@study tmp]# cp -l bashrc bashrc_hlink
[root@study tmp]# ls -l bashrc*
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc         <==與原始檔案不太一樣了！
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc_hlink
lrwxrwxrwx. 1 root root   6 Jun 11 19:06 bashrc_slink -> bashrc
```
>下面是自我实践
测试出，cp -s 是符号链接，cp -l创建了实体文件
```
kevin@ubuntu:~/os$ file ltext.txt 
ltext.txt: ASCII text
kevin@ubuntu:~/os$ file stest 
stest: symbolic link to test.txt
```

```
kevin@ubuntu:~/os$ cp -s test.txt stest
kevin@ubuntu:~/os$ ls
ltext.txt  os_experiment  os_note  stest  test.txt  路线图.jpg
kevin@ubuntu:~/os$ ls -l
total 508
-rwxrw-r-- 2 kevin kevin      0 Oct 22 19:56 ltext.txt
drwxrwxr-x 5 kevin kevin   4096 Oct 18 15:42 os_experiment
drwxrwxr-x 8 kevin kevin   4096 Oct 22 19:57 os_note
lrwxrwxrwx 1 kevin kevin      8 Oct 22 20:00 stest -> test.txt
-rwxrw-r-- 2 kevin kevin      0 Oct 22 19:56 test.txt
-rwxrw-rw- 1 kevin kevin 508889 Oct  9 15:33 路线图.jpg
kevin@ubuntu:~/os$ ls -a
.  ..  .git  .gitmodules  ltext.txt  os_experiment  os_note  stest  test.txt  .vscode  路线图.jpg
kevin@ubuntu:~/os$ file stest 
stest: symbolic link to test.txt
kevin@ubuntu:~/os$ vim test.txt 
kevin@ubuntu:~/os$ ls
ltext.txt  os_experiment  os_note  stest  test.txt  路线图.jpg
kevin@ubuntu:~/os$ cat ltext.txt 
hello world
kevin@ubuntu:~/os$ cat stest 
hello world
```

cp -u 备份
```
範例五：若 ~/.bashrc 比 /tmp/bashrc 新才複製過來
[root@study tmp]# cp -u ~/.bashrc /tmp/bashrc
# 這個 -u 的特性，是在目標檔案與來源檔案有差異時，才會複製的。
# 所以，比較常被用於『備份』的工作當中喔！ ^_^
```

```
範例六：將範例四造成的 bashrc_slink 複製成為 bashrc_slink_1 與bashrc_slink_2
[root@study tmp]# cp bashrc_slink bashrc_slink_1
[root@study tmp]# cp -d bashrc_slink bashrc_slink_2
[root@study tmp]# ls -l bashrc bashrc_slink*
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc
lrwxrwxrwx. 1 root root   6 Jun 11 19:06 bashrc_slink -> bashrc
-rw-r--r--. 1 root root 176 Jun 11 19:09 bashrc_slink_1            <==與原始檔案相同
lrwxrwxrwx. 1 root root   6 Jun 11 19:10 bashrc_slink_2 -> bashrc  <==是連結檔！
# 這個例子也是很有趣喔！原本複製的是連結檔，但是卻將連結檔的實際檔案複製過來了
# 也就是說，如果沒有加上任何選項時，cp複製的是原始檔案，而非連結檔的屬性！
# 若要複製連結檔的屬性，就得要使用 -d 的選項了！如 bashrc_slink_2 所示。

範例七：將家目錄的 .bashrc 及 .bash_history 複製到 /tmp 底下
[root@study tmp]# cp ~/.bashrc ~/.bash_history /tmp
# 可以將多個資料一次複製到同一個目錄去！最後面一定是目錄！
```

##### rm (移除檔案或目錄)
```
[root@study ~]# rm [-fir] 檔案或目錄
選項與參數：
-f  ：就是 force 的意思，忽略不存在的檔案，不會出現警告訊息；
-i  ：互動模式，在刪除前會詢問使用者是否動作
-r  ：遞迴刪除啊！最常用在目錄的刪除了！這是非常危險的選項！！！
```

這是移除的指令(remove)，要注意的是，通常在Linux系統下，為了怕檔案被 root 誤殺，所以很多 distributions 都已經預設加入 -i 這個選項了！而如果要連目錄下的東西都一起殺掉的話， 例如子目錄裡面還有子目錄時，那就要使用 -r 這個選項了！不過，使用『 rm -r 』這個指令之前，請千萬注意了，因為該目錄或檔案『肯定』會被 root 殺掉！因為系統不會再次詢問你是否要砍掉呦！所以那是個超級嚴重的指令下達呦！ 得特別注意！不過，如果你確定該目錄不要了，那麼使用 rm -r 來循環殺掉是不錯的方式！

```
rm -r [filename]/ #删除该文件，包括该文件下的所有文件
rm -r [filename]/* #删除该文件下的所有文件，但这个文件保留

kevin@ubuntu:~/os$ mkdir test
kevin@ubuntu:~/os$ mkdir test/test1 test/test2
kevin@ubuntu:~/os$ ls test/
test1  test2
kevin@ubuntu:~/os$ rm -r test/*
kevin@ubuntu:~/os$ ls
os_experiment  os_note  test  路线图.jpg
kevin@ubuntu:~/os$ mkdir test/test1 test/test2
kevin@ubuntu:~/os$ ls test/
test1  test2
kevin@ubuntu:~/os$ rm -r test/
kevin@ubuntu:~/os$ ls
os_experiment  os_note  路线图.jpg
```

**example**
另外，範例四也是很有趣的例子，我們在之前就談過，檔名最好不要使用 "-" 號開頭， 因為 "-" 後面接的是選項，因此，單純的使用『 rm -aaa- 』系統的指令就會誤判啦！ 那如果使用後面會談到的正規表示法時，還是會出問題的！所以，只能用避過首位字元是 "-" 的方法啦！ **就是加上本目錄『 ./ 』即可！**如果 man rm 的話，其實還有一種方法，那就是『 rm -- -aaa- 』也可以啊！
```
範例四：刪除一個帶有 - 開頭的檔案
[root@study tmp]# touch ./-aaa-  <==touch這個指令可以建立空檔案！
[root@study tmp]# ls -l 
-rw-r--r--. 1 root   root       0 Jun 11 19:22 -aaa-  <==檔案大小為0，所以是空檔案
[root@study tmp]# rm -aaa-
rm: invalid option -- 'a'                    <== 因為 "-" 是選項嘛！所以系統誤判了！
Try 'rm ./-aaa-' to remove the file `-aaa-'. <== 新的 bash 有給建議的
Try 'rm --help' for more information.
[root@study tmp]# rm ./-aaa-
```

##### mv (移動檔案與目錄，或更名)
```
[root@study ~]# mv [-fiu] source destination
[root@study ~]# mv [options] source1 source2 source3 .... directory
選項與參數：
-f  ：force 強制的意思，如果目標檔案已經存在，不會詢問而直接覆蓋；
-i  ：若目標檔案 (destination) 已經存在時，就會詢問是否覆蓋！
-u  ：若目標檔案已經存在，且 source 比較新，才會更新 (update)
```


### 6.2.3 取得路徑的檔案名稱與目錄名稱
每個檔案的完整檔名包含了前面的目錄與最終的檔名，而每個檔名的長度都可以到達 255 個字元耶！ 那麼你怎麼知道那個是檔名？那個是目錄名？嘿嘿！就是利用斜線 (/) 來分辨啊！ 其實，取得檔名或者是目錄名稱，一般的用途應該是在寫程式的時候用來判斷之用的啦～ 所以，這部分的指令可以用在第三篇內的 shell scripts 裡頭喔！ 底下我們簡單的以幾個範例來談一談 basename 與 dirname 的用途！
```
[root@study ~]# basename /etc/sysconfig/network
network         <== 很簡單！就取得最後的檔名～
[root@study ~]# dirname /etc/sysconfig/network
/etc/sysconfig  <== 取得的變成目錄名了！
```

## 6.3 檔案內容查閱
如果我們要查閱一個檔案的內容時，該如何是好呢？這裡有相當多有趣的指令可以來分享一下： 最常使用的顯示檔案內容的指令可以說是 cat 與 more 及 less 了！此外，如果我們要查看一個很大型的檔案 (好幾百MB時)，但是我們只需要後端的幾行字而已，那麼該如何是好？呵呵！用 tail 呀，此外， tac 這個指令也可以達到這個目的喔！好了，說說各個指令的用途吧！
- cat  由第一行開始顯示檔案內容
- tac  從最後一行開始顯示，可以看出 tac 是 cat 的倒著寫！
- nl   顯示的時候，順道輸出行號！
- more 一頁一頁的顯示檔案內容
- less 與 more 類似，但是比 more 更好的是，他可以往前翻頁！
- head 只看頭幾行
- tail 只看尾巴幾行
- od   以二進位的方式讀取檔案內容！

##### cat(concatenate)
```
[root@study ~]# cat [-AbEnTv]
選項與參數：
-A  ：相當於 -vET 的整合選項，可列出一些特殊字符而不是空白而已；
-b  ：列出行號，僅針對非空白行做行號顯示，空白行不標行號！
-E  ：將結尾的斷行字元 $ 顯示出來；
-n  ：列印出行號，連同空白行也會有行號，與 -b 的選項不同；
-T  ：將 [tab] 按鍵以 ^I 顯示出來；
-v  ：列出一些看不出來的特殊字符
```

```
kevin@ubuntu:~/os$ cat test.txt 
test 1
test 2

test 3
test 4

test 5
test 6
kevin@ubuntu:~/os$ cat -n test.txt 
     1  test 1
     2  test 2
     3
     4  test 3
     5  test 4
     6
     7  test 5
     8  test 6
kevin@ubuntu:~/os$ cat -A test.txt 
test 1$
test 2$
$
test 3$
test 4$
$
test 5$
test 6$
```

##### tac(反向列示)

tac 這個好玩了！怎麼說呢？詳細的看一下， cat 與 tac ，有沒有發現呀！對啦！ tac 剛好是將 cat 反寫過來，所以他的功能就跟 cat 相反啦， cat 是由『第一行到最後一行連續顯示在螢幕上』，而 tac 則是『 由最後一行到第一行反向在螢幕上顯示出來 』，很好玩吧！

```
kevin@ubuntu:~/os$ tac test.txt 
test 6
test 5

test 4
test 3

test 2
test 1
```

##### nl (添加行號列印)
```
[root@study ~]# nl [-bnw] 檔案
選項與參數：
-b  ：指定行號指定的方式，主要有兩種：
      -b a ：表示不論是否為空行，也同樣列出行號(類似 cat -n)；
      -b t ：如果有空行，空的那一行不要列出行號(預設值)；
-n  ：列出行號表示的方法，主要有三種：
      -n ln ：行號在螢幕的最左方顯示；
      -n rn ：行號在自己欄位的最右方顯示，且不加 0 ；
      -n rz ：行號在自己欄位的最右方顯示，且加 0 ；
-w  ：行號欄位的佔用的字元數。
```
使用案例
```
kevin@ubuntu:~/os$ nl test.txt 
     1  test 1
     2  test 2
       
     3  test 3
     4  test 4
       
     5  test 5
     6  test 6
```
空行显示行号
```
kevin@ubuntu:~/os$ nl -b a test.txt 
     1  test 1
     2  test 2
     3
     4  test 3
     5  test 4
     6
     7  test 5
     8  test 6
```
行号最左
```
kevin@ubuntu:~/os$ nl -b a -n ln test.txt 
1       test 1
2       test 2
3     
4       test 3
5       test 4
6     
7       test 5
8       test 6
```

### 6.3.2 可翻頁檢視
**前面提到的 nl 與 cat, tac 等等，都是一次性的將資料一口氣顯示到螢幕上面**，那有沒有可以進行一頁一頁翻動的指令啊？ 讓我們可以一頁一頁的觀察，才不會前面的資料看不到啊～呵呵！有的！那就是 more 與 less 囉～

```
kevin@ubuntu:~/os$ more os_note/linux_environment/chapter2_Linux_environment.md 
#Linux 环境
---
## Linux 硬件搭配
**因為，各個元件或裝置在Linux底下都是『一個檔案！』**  
CPU
RAM:主記憶體是越大越好！事實上在Linux伺服器中，主記憶體的重要性比CPU還要高的多！因為如果主記憶體不夠大， 就會使用到硬碟的記憶體置換空間(swap)。 而由計算機概論的內容我們知道硬碟比記憶體的速度要慢的多， 所以主
記憶體太小可能會影響到整體系統的效能的！
#### 各硬體裝置在Linux中的檔名
『在Linux系統中，每個裝置都被當成一個檔案來對待』 舉例來說，SATA介面的硬碟的檔案名稱即為/dev/sd[a-d]，其中， 括號內的字母為a-d當中的任意一個，亦即有/dev/sda, /dev/sdb, /dev/sdc, 及 /dev/sdd這四個檔案的意思。
>在Linux這個系統當中，幾乎所有的硬體裝置檔案都在/dev這個目錄內， 所以你會看到/dev/sda, /dev/sr0等等的檔名喔。

**各种设备在Linux中的名字**
![设备名称](/os_note/linux_environment/picture/各类设备名称.png)
usb,sata /dev/sd[a-p]
floppy disk /dev/fd[0-1]
```

- Enter 下一行
- Space 下一页
- /字串         ：代表在這個顯示的內容當中，向下搜尋『字串』這個關鍵字；
- :f            ：立刻顯示出檔名以及目前顯示的行數；
- q             ：代表立刻離開 more ，不再顯示該檔案內容。
- b 或 [ctrl]-b ：代表往回翻頁，不過這動作只對檔案有用，對管線無用。

##### less (一頁一頁翻動)
```
kevin@ubuntu:~/os$ less os_note/linux_environment/chapter2_Linux_environment.md
```

- 空白鍵    ：向下翻動一頁；
- [pagedown]：向下翻動一頁；
- [pageup]  ：向上翻動一頁；
- /字串     ：向下搜尋『字串』的功能；
- ?字串     ：向上搜尋『字串』的功能；
- n         ：重複前一個搜尋 (與 / 或 ? 有關！)
- N         ：反向的重複前一個搜尋 (與 / 或 ? 有關！)
- g         ：前進到這個資料的第一行去；
- G         ：前進到這個資料的最後一行去 (注意大小寫)；
- q         ：離開 less 這個程式；

### 6.3.3 資料擷取

##### head(取出前几行，默认10行)
我們可以將輸出的資料作一個最簡單的擷取，那就是取出檔案前面幾行 (head) 或取出後面幾行 (tail) 文字的功能。 不過，要注意的是， head 與 tail 都是以『行』為單位來進行資料擷取的喔！

```
[root@study ~]# head [-n number] 檔案 
選項與參數：
-n  ：後面接數字，代表顯示幾行的意思

[root@study ~]# head /etc/man_db.conf
# 預設的情況中，顯示前面十行！若要顯示前 20 行，就得要這樣：
[root@study ~]# head -n 20 /etc/man_db.conf

kevin@ubuntu:~/os$ head os_note/elementary_knowledge/linux_elementary_knowledge.md 
# Linux 基础知识笔记
---
## 发展历史

<font size="4">**Unix**</font> 
1973诞生，1977 BSD诞生

<font size="4">**GNU**</font> 
- gcc 
- bash shell
```

##### tail (取出後面幾行)
```
[root@study ~]# tail [-n number] 檔案 
選項與參數：
-n  ：後面接數字，代表顯示幾行的意思
-f  ：表示持續偵測後面所接的檔名，要等到按下[ctrl]-c才會結束tail的偵測
```
>
>例題：
    假如我想要顯示 /etc/man_db.conf 的第 11 到第 20 行呢？
答：
    這個應該不算難，想一想，在第 11 到第 20 行，那麼我取前 20 行，再取後十行，所以結果就是：『 head -n 20 /etc/man_db.conf | tail -n 10 』，這樣就可以得到第 11 到第 20 行之間的內容了！
    這兩個指令中間有個管線 (|) 的符號存在，這個管線的意思是：『前面的指令所輸出的訊息，請透過管線交由後續的指令繼續使用』的意思。 所以， head -n 20 /etc/man_db.conf 會將檔案內的 20 行取出來，但不輸出到螢幕上，而是轉交給後續的 tail 指令繼續處理。 因此 tail 『不需要接檔名』，因為 tail 所需要的資料是來自於 head 處理後的結果！這樣說，有沒有理解？
    更多的管線命令，我們會在第三篇繼續解釋的！

### 6.3.4 非純文字檔： od
我們上面提到的，都是在查閱純文字檔的內容。那麼萬一我們想要查閱非文字檔，舉例來說，例如 /usr/bin/passwd 這個執行檔的內容時， 又該如何去讀出資訊呢？事實上，由於執行檔通常是 binary file ，使用上頭提到的指令來讀取他的內容時， 確實會產生類似亂碼的資料啊！那怎麼辦？沒關係，我們可以利用 od 這個指令來讀取喔！

```
[root@study ~]# od [-t TYPE] 檔案
選項或參數：
-t  ：後面可以接各種『類型 (TYPE)』的輸出，例如：
      a       ：利用預設的字元來輸出；
      c       ：使用 ASCII 字元來輸出
      d[size] ：利用十進位(decimal)來輸出資料，每個整數佔用 size bytes ；
      f[size] ：利用浮點數值(floating)來輸出資料，每個數佔用 size bytes ；
      o[size] ：利用八進位(octal)來輸出資料，每個整數佔用 size bytes ；
      x[size] ：利用十六進位(hexadecimal)來輸出資料，每個整數佔用 size bytes ；

```

其中，size是一个表示相应数据类型字节数量的十进制整数，或采用C语言的数据类型字符表示字节数量。例如，对于d、o、u和x类型标志，可用C表示一个字符，S表示一个短整数，I表示一个整数，L表示一个长整数，对于f类型标志，可用F表示一个浮点数，D表示一个双精度的浮点数，L表示长的双精度浮点数等。
```
範例一：請將/usr/bin/passwd的內容使用ASCII方式來展現！
[root@study ~]# od -t c /usr/bin/passwd
0000000 177   E   L   F 002 001 001  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000020 003  \0   >  \0 001  \0  \0  \0 364   3  \0  \0  \0  \0  \0  \0
0000040   @  \0  \0  \0  \0  \0  \0  \0   x   e  \0  \0  \0  \0  \0  \0
0000060  \0  \0  \0  \0   @  \0   8  \0  \t  \0   @  \0 035  \0 034  \0
0000100 006  \0  \0  \0 005  \0  \0  \0   @  \0  \0  \0  \0  \0  \0  \0
.....(後面省略)....
# 最左邊第一欄是以 8 進位來表示bytes數。以上面範例來說，第二欄0000020代表開頭是
# 第 16 個 byes (2x8) 的內容之意。
```

```
### 将password 以八进制ascii码输出
kevin@ubuntu:~/os$ echo password | od -t oCc
0000000 160 141 163 163 167 157 162 144 012
          p   a   s   s   w   o   r   d  \n
0000011
```

### 6.3.5 修改檔案時間或建置新檔： touch

我們在 ls 這個指令的介紹時，有稍微提到每個檔案在linux底下都會記錄許多的時間參數， 其實是有三個主要的變動時間，那麼三個時間的意義是什麼呢？

- modification time (mtime)：
當該檔案的『內容資料』變更時，就會更新這個時間！內容資料指的是檔案的內容，而不是檔案的屬性或權限喔！

- status time (ctime)：
當該檔案的『狀態 (status)』改變時，就會更新這個時間，舉例來說，像是權限與屬性被更改了，都會更新這個時間啊。

- access time (atime)：
當『該檔案的內容被取用』時，就會更新這個讀取時間 (access)。舉例來說，我們使用 cat 去讀取 /etc/man_db.conf ， 就會更新該檔案的 atime 了。

看到了嗎？在預設的情況下，ls 顯示出來的是該檔案的 mtime ，也就是這個檔案的內容上次被更動的時間。 至於鳥哥的系統是在 5 月 4 號的時候安裝的，因此，這個檔案被產生導致狀態被更動的時間就回溯到那個時間點了(ctime)！ 而還記得剛剛我們使用的範例當中，有使用到man_db.conf這個檔案啊，所以啊，他的 atime 就會變成剛剛使用的時間了！

檔案的時間是很重要的，因為，如果檔案的時間誤判的話，可能會造成某些程式無法順利的運作。 OK！那麼萬一我發現了一個檔案來自未來，該如何讓該檔案的時間變成『現在』的時刻呢？ 很簡單啊！就用『touch』這個指令即可！

在上面這個案例當中我們使用了『ll』這個指令(兩個英文L的小寫)，這個指令其實就是『ls -l』的意思， ll本身不存在，是被『做出來』的一個命令別名。相關的命令別名我們會在bash章節當中詳談的，**這裡先知道ll="ls -l"即可。** **至於分號『 ; 』則代表連續指令的下達啦！你可以在一行指令當中寫入多重指令， 這些指令可以『依序』執行。**由上面的指令我們會知道ll那一行有三個指令被下達在同一行中。

無論如何， touch 這個指令最常被使用的情況是：

- 建立一個空的檔案；
- 將某個檔案日期修訂為目前 (mtime 與 atime)

## 6.4 檔案與目錄的預設權限與隱藏權限
由第五章、Linux檔案權限的內容我們可以知道一個檔案有若干個屬性， 包括讀寫執行(r, w, x)等基本權限，及是否為目錄 (d) 與檔案 (-) 或者是連結檔 (l) 等等的屬性！ 要修改屬性的方法在前面也約略提過了(chgrp, chown, chmod) ，本小節會再加強補充一下！

除了基本r, w, x權限外，在Linux傳統的Ext2/Ext3/Ext4檔案系統下，我們還可以設定其他的系統隱藏屬性， 這部份可使用 chattr 來設定，而以 lsattr 來查看，最重要的屬性就是可以設定其不可修改的特性！讓連檔案的擁有者都不能進行修改！ 這個屬性可是相當重要的，尤其是在安全機制上面 (security)！比較可惜的是，在 CentOS 7.x 當中利用 xfs 作為預設檔案系統， 但是 xfs 就沒有支援所有的 chattr 的參數了！僅有部份參數還有支援而已！

首先，先來複習一下上一章談到的權限概念，將底下的例題看一看先：

### 6.4.1 檔案預設權限：umask
OK！那麼現在我們知道如何建立或者是改變一個目錄或檔案的屬性了，不過， 你知道當你建立一個新的檔案或目錄時，他的預設權限會是什麼嗎？呵呵！那就與 umask 這個玩意兒有關了！那麼 umask 是在搞什麼呢？基本上， **umask 就是指定 『目前使用者在建立檔案或目錄時候的權限預設值』**， 那麼如何得知或設定 umask 呢？他的指定條件以底下的方式來指定：

```
kevin@ubuntu:~/os$ umask
0002
kevin@ubuntu:~/os$ man umask
kevin@ubuntu:~/os$ umask -S
u=rwx,g=rwx,o=rx
```

查閱的方式有兩種，一種可以直接輸入 umask ，就可以看到數字型態的權限設定分數， 一種則是加入 -S (Symbolic) 這個選項，就會以符號類型的方式來顯示出權限了！ 奇怪的是，怎麼 umask 會有四組數字啊？不是只有三組嗎？是沒錯啦。 第一組是特殊權限用的，我們先不要理他，所以先看後面三組即可。

在預設權限的屬性上，目錄與檔案是不一樣的。**從第五章我們知道 x 權限對於目錄是非常重要的！ 但是一般檔案的建立則不應該有執行的權限，因為一般檔案通常是用在於資料的記錄嘛！當然不需要執行的權限了。** 因此，預設的情況如下：
- 若使用者建立為『檔案』則預設『沒有可執行( x )權限』，亦即只有 rw 這兩個項目，也就是最大為 666 分，預設權限如下：
-rw-rw-rw-
- 若使用者建立為『目錄』，則由於 x 與是否可以進入此目錄有關，因此預設為所有權限均開放，亦即為 777 分，預設權限如下：
drwxrwxrwx

要注意的是，**umask 的分數指的是『該預設值需要減掉的權限！』**因為 r、w、x 分別是 4、2、1 分，所以囉！也就是說，當要拿掉能寫的權限，就是輸入 2 分，而如果要拿掉能讀的權限，也就是 4 分，那麼要拿掉讀與寫的權限，也就是 6 分，而要拿掉執行與寫入的權限，也就是 3 分，這樣瞭解嗎？請問你， 5 分是什麼？呵呵！ 就是讀與執行的權限啦！

>建立檔案時：(-rw-rw-rw-) - (-----w--w-) ==> -rw-r--r--
>建立目錄時：(drwxrwxrwx) - (d----w--w-) ==> drwxr-xr-x

#### umask的利用與重要性：專題製作
這個問題很常發生啊！舉上面的案例來看就好了，你看一下 test1 的權限是幾分？ 644 呢！意思是『如果 umask 訂定為 022 ，那新建的資料只有使用者自己具有 w 的權限， 同群組的人只有 r 這個可讀的權限而已，並無法修改喔！』這樣要怎麼共同製作專題啊！您說是吧！

所以，當我們需要新建檔案給同群組的使用者共同編輯時，那麼 umask 的群組就不能拿掉 2 這個 w 的權限！ 所以囉， umask 就得要是 002 之類的才可以！這樣新建的檔案才能夠是 -rw-rw-r-- 的權限模樣喔！ 那麼如何設定 umask 呢？簡單的很，直接在 umask 後面輸入 002 就好了！

```
[root@study ~]# umask 002
[root@study ~]# touch test3
[root@study ~]# mkdir test4
[root@study ~]# ll -d test[34]   # 中括號 [ ] 代表中間有個指定的字元，而不是任意字元的意思
-rw-rw-r--. 1 root root 0  6月 16 01:12 test3
drwxrwxr-x. 2 root root 6  6月 16 01:12 test4
```
所以說，這個 umask 對於新建檔案與目錄的預設權限是很有關係的！這個概念可以用在任何伺服器上面， 尤其是未來在你架設檔案伺服器 (file server) ，舉例來說， SAMBA Server 或者是 FTP server 時， 都是很重要的觀念！這牽涉到你的使用者是否能夠將檔案進一步利用的問題喔！不要等閒視之！

> 例題：
     假設你的 umask 為 003 ，請問該 umask 情況下，建立的檔案與目錄權限為？
> 答：
     umask 為 003 ，所以拿掉的權限為 --------wx，因此：
     檔案： (-rw-rw-rw-) - (--------wx) = -rw-rw-r--
     目錄： (drwxrwxrwx) - (d-------wx) = drwxrwxr--


### 6.4.2 檔案隱藏屬性
什麼？檔案還有隱藏屬性？光是那九個權限就快要瘋掉了，竟然還有隱藏屬性，真是要命～ 但是沒辦法，就是有檔案的隱藏屬性存在啊！不過，這些隱藏的屬性確實對於系統有很大的幫助的～ 尤其是在系統安全 (Security) 上面，重要的緊呢！不過要先強調的是，底下的chattr指令只能在Ext2/Ext3/Ext4的 Linux 傳統檔案系統上面完整生效， 其他的檔案系統可能就無法完整的支援這個指令了，例如 xfs 僅支援部份參數而已。底下我們就來談一談如何設定與檢查這些隱藏的屬性吧！

#### chattr
```
[root@study ~]# chattr [+-=][ASacdistu] 檔案或目錄名稱
選項與參數：
+   ：增加某一個特殊參數，其他原本存在參數則不動。
-   ：移除某一個特殊參數，其他原本存在參數則不動。
=   ：設定一定，且僅有後面接的參數

A  ：當設定了 A 這個屬性時，若你有存取此檔案(或目錄)時，他的存取時間 atime 將不會被修改，
     可避免 I/O 較慢的機器過度的存取磁碟。(目前建議使用檔案系統掛載參數處理這個項目)
S  ：一般檔案是非同步寫入磁碟的(原理請參考前一章sync的說明)，如果加上 S 這個屬性時，
     當你進行任何檔案的修改，該更動會『同步』寫入磁碟中。
a  ：當設定 a 之後，這個檔案將只能增加資料，而不能刪除也不能修改資料，只有root 才能設定這屬性
c  ：這個屬性設定之後，將會自動的將此檔案『壓縮』，在讀取的時候將會自動解壓縮，
     但是在儲存的時候，將會先進行壓縮後再儲存(看來對於大檔案似乎蠻有用的！)
d  ：當 dump 程序被執行的時候，設定 d 屬性將可使該檔案(或目錄)不會被 dump 備份
i  ：這個 i 可就很厲害了！他可以讓一個檔案『不能被刪除、改名、設定連結也無法寫入或新增資料！』
     對於系統安全性有相當大的助益！只有 root 能設定此屬性
s  ：當檔案設定了 s 屬性時，如果這個檔案被刪除，他將會被完全的移除出這個硬碟空間，
     所以如果誤刪了，完全無法救回來了喔！
u  ：與 s 相反的，當使用 u 來設定檔案時，如果該檔案被刪除了，則資料內容其實還存在磁碟中，
     可以使用來救援該檔案喔！
注意1：屬性設定常見的是 a 與 i 的設定值，而且很多設定值必須要身為 root 才能設定
注意2：xfs 檔案系統僅支援 AadiS 而已

範例：請嘗試到/tmp底下建立檔案，並加入 i 的參數，嘗試刪除看看。
[root@study ~]# cd /tmp
[root@study tmp]# touch attrtest     <==建立一個空檔案
[root@study tmp]# chattr +i attrtest <==給予 i 的屬性
[root@study tmp]# rm attrtest        <==嘗試刪除看看
rm: remove regular empty file `attrtest'? y
rm: cannot remove `attrtest': Operation not permitted
# 看到了嗎？呼呼！連 root 也沒有辦法將這個檔案刪除呢！趕緊解除設定！

範例：請將該檔案的 i 屬性取消！
[root@study tmp]# chattr -i attrtest
```
Myself test
```
root@ubuntu:/home/kevin/os# ls
os_experiment  os_note  路线图.jpg
root@ubuntu:/home/kevin/os# touch attest
root@ubuntu:/home/kevin/os# chattr +i attest 
root@ubuntu:/home/kevin/os# rm attest 
rm: cannot remove 'attest': Operation not permitted
root@ubuntu:/home/kevin/os# chattr -i attest 
root@ubuntu:/home/kevin/os# rm attest 
root@ubuntu:/home/kevin/os# ls
os_experiment  os_note  路线图.jpg
```
#### lsattr
```
[root@study ~]# lsattr [-adR] 檔案或目錄
選項與參數：
-a ：將隱藏檔的屬性也秀出來；
-d ：如果接的是目錄，僅列出目錄本身的屬性而非目錄內的檔名；
-R ：連同子目錄的資料也一併列出來！ 

[root@study tmp]# chattr +aiS attrtest
[root@study tmp]# lsattr attrtest
--S-ia---------- attrtest
```
使用 chattr 設定後，可以利用 lsattr 來查閱隱藏的屬性。不過， 這兩個指令在使用上必須要特別小心，否則會造成很大的困擾。例如：某天你心情好，突然將 /etc/shadow 這個重要的密碼記錄檔案給他設定成為具有 i 的屬性，那麼過了若干天之後， 你突然要新增使用者，卻一直無法新增！別懷疑，趕快去將 i 的屬性拿掉吧！

### 6.4.3 檔案特殊權限： SUID, SGID, SBIT
一定注意到了一件事，那就是，怎麼我們的 /tmp 權限怪怪的？ 還有，那個 /usr/bin/passwd 也怪怪的？怎麼回事啊？看看先：


```
root@ubuntu:/home/kevin/os# ls -ld /tmp
drwxrwxrwt 22 root root 4096 Oct 24 16:49 /tmp
kevin@ubuntu:~/os$ sudo ls -ld /usr/bin/passwd
[sudo] password for kevin: 
-rwsr-xr-x 1 root root 59640 Mar 14  2022 /usr/bin/passwd
```

不是應該只有 rwx 嗎？還有其他的特殊權限( s 跟 t )啊？啊.....頭又開始昏了～ @_@ 因為 s 與 t 這兩個權限的意義與系統的帳號 (第十三章)及系統的程序(process, 第十六章)較為相關， 所以等到後面的章節談完後你才會比較有概念！底下的說明先看看就好，如果看不懂也沒有關係， 先知道s放在哪裡稱為SUID/SGID以及如何設定即可，等系統程序章節讀完後，再回來看看喔！

#### Set UID
當 s 這個標誌出現在檔案擁有者的 x 權限上時，例如剛剛提到的 /usr/bin/passwd 這個檔案的權限狀態：『-rwsr-xr-x』，此時就被稱為 Set UID，簡稱為 SUID 的特殊權限。 那麼SUID的權限對於一個檔案的特殊功能是什麼呢？基本上SUID有這樣的限制與功能：
- SUID 權限僅對二進位程式(binary program)有效；
- 執行者對於該程式需要具有 x 的可執行權限；
- 本權限僅在執行該程式的過程中有效 (run-time)；
- 執行者將具有該程式擁有者 (owner) 的權限。

唔！有沒有衝突啊！明明 /etc/shadow 就不能讓 dmtsai 這個一般帳戶去存取的，為什麼 dmtsai 還能夠修改這個檔案內的密碼呢？ 這就是 SUID 的功能啦！藉由上述的功能說明，我們可以知道

1. dmtsai 對於 /usr/bin/passwd 這個程式來說是具有 x 權限的，表示 dmtsai 能執行 passwd；
2. passwd 的擁有者是 root 這個帳號；
3. dmtsai 執行 passwd 的過程中，會『暫時』獲得 root 的權限；
4. /etc/shadow 就可以被 dmtsai 所執行的 passwd 所修改。
但如果 dmtsai 使用 cat 去讀取 /etc/shadow 時，他能夠讀取嗎？因為 cat 不具有 SUID 的權限，所以 dmtsai 執行 『cat /etc/shadow』 時，是不能讀取 /etc/shadow 的。我們用一張示意圖來說明如下：

另外，**SUID 僅可用在binary program 上， 不能夠用在 shell script 上面**這是因為 shell script 只是將很多的 binary 執行檔叫進來執行而已！所以 SUID 的權限部分，還是得要看 shell script 呼叫進來的程式的設定， 而不是 shell script 本身。當然，SUID 對於目錄也是無效的～這點要特別留意。

#### Set GID
**當 s 標誌在檔案擁有者的 x 項目為 SUID，那 s 在群組的 x 時則稱為 Set GID, SGID 囉！** 是這樣沒錯！^_^。 舉例來說，你可以用底下的指令來觀察到具有 SGID 權限的檔案喔：
```
kevin@ubuntu:~/os$ ls -l /usr/bin/locate
lrwxrwxrwx 1 root root 24 Mar 23  2022 /usr/bin/locate -> /etc/alternatives/locate
```
與 SUID 不同的是，SGID 可以針對檔案或目錄來設定！如果是對檔案來說， SGID 有如下的功能：

- SGID 對二進位程式有用；
- 程式執行者對於該程式來說，需具備 x 的權限；
- 執行者在執行的過程中將會獲得該程式群組的支援！

#### Sticky Bit
這個 Sticky Bit, SBIT 目前只針對目錄有效，對於檔案已經沒有效果了。SBIT 對於目錄的作用是：
- 當使用者對於此目錄具有 w, x 權限，亦即具有寫入的權限時；
- 當使用者在該目錄下建立檔案或目錄時，僅有自己與 root 才有權力刪除該檔案

#### SUID/SGID/SBIT 權限設定
前面介紹過 SUID 與 SGID 的功能，那麼如何設定檔案使成為具有 SUID 與 SGID 的權限呢？ 這就需要第五章的數字更改權限的方法了！ 現在你應該已經知道數字型態更改權限的方式為『三個數字』的組合， 那麼如果在這三個數字之前再加上一個數字的話，最前面的那個數字就代表這幾個權限了！

- 4 為 SUID
- 2 為 SGID
- 1 為 SBIT
假設要將一個檔案權限改為『-rwsr-xr-x』時，由於 s 在使用者權限中，所以是 SUID ，因此， 在原先的 755 之前還要加上 4 ，也就是：『 chmod 4755 filename 』來設定！此外，還有大 S 與大 T 的產生喔！參考底下的範例啦！



換句話說：當甲這個使用者於 A 目錄是具有群組或其他人的身份，並且擁有該目錄 w 的權限， 這表示『甲使用者對該目錄內任何人建立的目錄或檔案均可進行 "刪除/更名/搬移" 等動作。』 不過，如果將 A 目錄加上了 SBIT 的權限項目時， 則甲只能夠針對自己建立的檔案或目錄進行刪除/更名/移動等動作，而無法刪除他人的檔案。

### 6.4.4 觀察檔案類型：file
如果你想要知道某個檔案的基本資料，例如是屬於 ASCII 或者是 data 檔案，或者是 binary ， 且其中有沒有使用到動態函式庫 (share library) 等等的資訊，就可以利用 file 這個指令來檢閱喔！舉例來說：
```
[root@study ~]# file ~/.bashrc
/root/.bashrc: ASCII text  <==告訴我們是 ASCII 的純文字檔啊！
[root@study ~]# file /usr/bin/passwd
/usr/bin/passwd: setuid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically 
linked (uses shared libs), for GNU/Linux 2.6.32, 
BuildID[sha1]=0xbf35571e607e317bf107b9bcf65199988d0ed5ab, stripped
# 執行檔的資料可就多的不得了！包括這個檔案的 suid 權限、相容於 Intel x86-64 等級的硬體平台
# 使用的是 Linux 核心 2.6.32 的動態函式庫連結等等。
[root@study ~]# file /var/lib/mlocate/mlocate.db
/var/lib/mlocate/mlocate.db: data  <== 這是 data 檔案！
```
透過這個指令，我們可以簡單的先判斷這個檔案的格式為何喔！包括未來你也可以用來判斷使用 tar 包裹時，該 tarball 檔案是使用哪一種壓縮功能哩！

## 6.5 指令與檔案的搜尋
### 6.5.1 指令檔名的搜尋
我們知道在終端機模式當中，連續輸入兩次[tab]按鍵就能夠知道使用者有多少指令可以下達。 那你知不知道這些指令的完整檔名放在哪裡？舉例來說，ls 這個常用的指令放在哪裡呢？ 就透過 which 或 type 來找尋吧！

which (尋找『執行檔』)
```
[root@study ~]# which [-a] command
選項或參數：
-a ：將所有由 PATH 目錄中可以找到的指令均列出，而不止第一個被找到的指令名稱

範例一：搜尋 ifconfig 這個指令的完整檔名
[root@study ~]# which ifconfig
/sbin/ifconfig 

範例二：用 which 去找出 which 的檔名為何？
[root@study ~]# which which
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
        /bin/alias
        /usr/bin/which
# 竟然會有兩個 which ，其中一個是 alias 這玩意兒呢！那是啥？
# 那就是所謂的『命令別名』，意思是輸入 which 會等於後面接的那串指令啦！
# 更多的資料我們會在 bash 章節中再來談的！

範例三：請找出 history 這個指令的完整檔名
[root@study ~]# which history
/usr/bin/which: no history in (/usr/local/sbin:/usr/local/bin:/sbin:/bin:
/usr/sbin:/usr/bin:/root/bin)

[root@study ~]# history --help
-bash: history: --: invalid option
history: usage: history [-c] [-d offset] [n] or history -anrw [filename] or history -ps arg 
# 瞎密？怎麼可能沒有 history ，我明明就能夠用 root 執行 history 的啊！
```

是找出『執行檔』而已！且 which 後面接的是『完整檔名』喔！若加上 -a 選項，則可以列出所有的可以找到的同名執行檔，而非僅顯示第一個而已！

最後一個範例最有趣，怎麼 history 這個常用的指令竟然找不到啊！為什麼呢？這是因為 **history 是『bash 內建的指令』啦！**  但是 which 預設是找 PATH 內所規範的目錄，所以當然一定找不到的啊(有 bash 就有 history！)！那怎辦？沒關係！我們可以透過 type 這個指令喔！ 關於 type 的用法我們將在 第十章的 bash 再來談！

### 6.5.2 檔案檔名的搜尋
再來談一談怎麼搜尋檔案吧！在 Linux 底下也有相當優異的搜尋指令呦！通常 find 不很常用的！因為速度慢之外， 也很操硬碟！一般我們都是先使用 whereis 或者是 locate 來檢查，如果真的找不到了，才以 find 來搜尋呦！ 為什麼呢？**因為 whereis 只找系統中某些特定目錄底下的檔案而已，locate 則是利用資料庫來搜尋檔名，**當然兩者就相當的快速， 並且沒有實際的搜尋硬碟內的檔案系統狀態，比較省時間啦！

#### whereis (由一些特定的目錄中尋找檔案檔名)
```

[root@study ~]# whereis [-bmsu] 檔案或目錄名
選項與參數：
-l    :可以列出 whereis 會去查詢的幾個主要目錄而已
-b    :只找 binary 格式的檔案
-m    :只找在說明檔 manual 路徑下的檔案
-s    :只找 source 來源檔案
-u    :搜尋不在上述三個項目當中的其他特殊檔案

範例一：請找出 ifconfig 這個檔名
[root@study ~]# whereis ifconfig 
ifconfig: /sbin/ifconfig /usr/share/man/man8/ifconfig.8.gz

範例二：只找出跟 passwd 有關的『說明文件』檔名(man page)
[root@study ~]# whereis passwd     # 全部的檔名通通列出來！
passwd: /usr/bin/passwd /etc/passwd /usr/share/man/man1/passwd.1.gz /usr/share/man/man5/passwd.5.gz
[root@study ~]# whereis -m passwd  # 只有在 man 裡面的檔名才抓出來！
passwd: /usr/share/man/man1/passwd.1.gz /usr/share/man/man5/passwd.5.gz
```

等一下我們會提到 find 這個搜尋指令， find 是很強大的搜尋指令，但時間花用的很大！(**因為 find 是直接搜尋硬碟**，為如果你的硬碟比較老舊的話，嘿嘿！有的等！) 這個時候 whereis 就相當的好用了！另外， whereis 可以加入選項來找尋相關的資料，例如，如果你是要找可執行檔 (binary) 那麼加上 -b 就可以啦！ 如果不加任何選項的話，那麼就將所有的資料列出來囉！

那麼 whereis 到底是使用什麼咚咚呢？為何搜尋的速度會比 find 快這麼多？ 其實那也沒有什麼，**只是因為 whereis 只找幾個特定的目錄而已～並沒有全系統去查詢之故**。所以說，**whereis 主要是針對 /bin /sbin 底下的執行檔， 以及 /usr/share/man 底下的 man page 檔案，跟幾個比較特定的目錄來處理而已。所以速度當然快的多！**不過，就有某些檔案是你找不到的啦！ 想要知道 whereis 到底查了多少目錄？可以使用 whereis -l 來確認一下即可！

#### locate / updatedb
```
[root@study ~]# locate [-ir] keyword
選項與參數：
-i  ：忽略大小寫的差異；
-c  ：不輸出檔名，僅計算找到的檔案數量
-l  ：僅輸出幾行的意思，例如輸出五行則是 -l 5
-S  ：輸出 locate 所使用的資料庫檔案的相關資訊，包括該資料庫紀錄的檔案/目錄數量等
-r  ：後面可接正規表示法的顯示方式

範例一：找出系統中所有與 passwd 相關的檔名，且只列出 5 個
[root@study ~]# locate -l 5 passwd
/etc/passwd
/etc/passwd-
/etc/pam.d/passwd
/etc/security/opasswd
/usr/bin/gpasswd

範例二：列出 locate 查詢所使用的資料庫檔案之檔名與各資料數量
[root@study ~]# locate -S
Database /var/lib/mlocate/mlocate.db:
        8,086 directories     # 總紀錄目錄數
        109,605 files         # 總紀錄檔案數
        5,190,295 bytes in file names
        2,349,150 bytes used to store database
```

但是，這個東西還是有使用上的限制呦！為什麼呢？**你會發現使用 locate 來尋找資料的時候特別的快， 這是因為 locate 尋找的資料是由『已建立的資料庫 /var/lib/mlocate/』 裡面的資料所搜尋到的，所以不用直接在去硬碟當中存取資料**，呵呵！當然是很快速囉！

那麼有什麼限制呢？就是因為他是經由資料庫來搜尋的，而資料庫的建立預設是在每天執行一次 (每個 distribution 都不同，CentOS 7.x 是每天更新資料庫一次！)，所以當你新建立起來的檔案， 卻還在資料庫更新之前搜尋該檔案，那麼 locate 會告訴你『找不到！』呵呵！因為必須要更新資料庫呀！

那能否手動更新資料庫哪？當然可以啊！更新 locate 資料庫的方法非常簡單，**直接輸入『 updatedb 』就可以了！ updatedb 指令會去讀取 /etc/updatedb.conf 這個設定檔的設定，然後再去硬碟裡面進行搜尋檔名的動作， 最後就更新整個資料庫檔案囉！因為 updatedb 會去搜尋硬碟，所以當你執行 updatedb 時，可能會等待數分鐘的時間喔！**

#### find
```
[root@study ~]# find [PATH] [option] [action]
選項與參數：
1. 與時間有關的選項：共有 -atime, -ctime 與 -mtime ，以 -mtime 說明
   -mtime  n ：n 為數字，意義為在 n 天之前的『一天之內』被更動過內容的檔案；
   -mtime +n ：列出在 n 天之前(不含 n 天本身)被更動過內容的檔案檔名；
   -mtime -n ：列出在 n 天之內(含 n 天本身)被更動過內容的檔案檔名。
   -newer file ：file 為一個存在的檔案，列出比 file 還要新的檔案檔名

範例一：將過去系統上面 24 小時內有更動過內容 (mtime) 的檔案列出
[root@study ~]# find / -mtime 0
# 那個 0 是重點！0 代表目前的時間，所以，從現在開始到 24 小時前，
# 有變動過內容的檔案都會被列出來！那如果是三天前的 24 小時內？
# find / -mtime 3 有變動過的檔案都被列出的意思！

範例二：尋找 /etc 底下的檔案，如果檔案日期比 /etc/passwd 新就列出
[root@study ~]# find /etc -newer /etc/passwd
# -newer 用在分辨兩個檔案之間的新舊關係是很有用的！
```

時間參數真是挺有意思的！我們現在知道 atime, ctime 與 mtime 的意義，如果你想要找出一天內被更動過的檔案名稱， 可以使用上述範例一的作法。但如果我想要找出『4天內被更動過的檔案檔名』呢？那可以使用『 find /var -mtime -4 』。那如果是『4天前的那一天』就用『 find /var -mtime 4 』。有沒有加上『+, -』差別很大喔！我們可以用簡單的圖示來說明一下：

<div align=center><img src="/os_note/linux_file/picture/find_time.gif"></div>
<div align=center>圖6.5.1、find 相關的時間參數意義</div>

圖中最右邊為目前的時間，越往左邊則代表越早之前的時間軸啦。由圖 6.5.1 我們可以清楚的知道：

- +4代表大於等於5天前的檔名：ex> find /var -mtime +4
- -4代表小於等於4天內的檔案檔名：ex> find /var -mtime -4
- 4則是代表4-5那一天的檔案檔名：ex> find /var -mtime 4

```
選項與參數：
2. 與使用者或群組名稱有關的參數：
   -uid n ：n 為數字，這個數字是使用者的帳號 ID，亦即 UID ，這個 UID 是記錄在
            /etc/passwd 裡面與帳號名稱對應的數字。這方面我們會在第四篇介紹。
   -gid n ：n 為數字，這個數字是群組名稱的 ID，亦即 GID，這個 GID 記錄在
            /etc/group，相關的介紹我們會第四篇說明～
   -user name ：name 為使用者帳號名稱喔！例如 dmtsai 
   -group name：name 為群組名稱喔，例如 users ；
   -nouser    ：尋找檔案的擁有者不存在 /etc/passwd 的人！
   -nogroup   ：尋找檔案的擁有群組不存在於 /etc/group 的檔案！
                當你自行安裝軟體時，很可能該軟體的屬性當中並沒有檔案擁有者，
                這是可能的！在這個時候，就可以使用 -nouser 與 -nogroup 搜尋。

範例三：搜尋 /home 底下屬於 dmtsai 的檔案
[root@study ~]# find /home -user dmtsai
# 這個東西也很有用的～當我們要找出任何一個使用者在系統當中的所有檔案時，
# 就可以利用這個指令將屬於某個使用者的所有檔案都找出來喔！

範例四：搜尋系統中不屬於任何人的檔案
[root@study ~]# find / -nouser
# 透過這個指令，可以輕易的就找出那些不太正常的檔案。如果有找到不屬於系統任何人的檔案時，
# 不要太緊張，那有時候是正常的～尤其是你曾經以原始碼自行編譯軟體時。
```

```
選項與參數：
3. 與檔案權限及名稱有關的參數：
   -name filename：搜尋檔案名稱為 filename 的檔案；
   -size [+-]SIZE：搜尋比 SIZE 還要大(+)或小(-)的檔案。這個 SIZE 的規格有：
                   c: 代表 byte， k: 代表 1024bytes。所以，要找比 50KB
                   還要大的檔案，就是『 -size +50k 』
   -type TYPE    ：搜尋檔案的類型為 TYPE 的，類型主要有：一般正規檔案 (f), 裝置檔案 (b, c),
                   目錄 (d), 連結檔 (l), socket (s), 及 FIFO (p) 等屬性。
   -perm mode  ：搜尋檔案權限『剛好等於』 mode 的檔案，這個 mode 為類似 chmod
                 的屬性值，舉例來說， -rwsr-xr-x 的屬性為 4755 ！
   -perm -mode ：搜尋檔案權限『必須要全部囊括 mode 的權限』的檔案，舉例來說，
                 我們要搜尋 -rwxr--r-- ，亦即 0744 的檔案，使用 -perm -0744，
                 當一個檔案的權限為 -rwsr-xr-x ，亦即 4755 時，也會被列出來，
                 因為 -rwsr-xr-x 的屬性已經囊括了 -rwxr--r-- 的屬性了。
   -perm /mode ：搜尋檔案權限『包含任一 mode 的權限』的檔案，舉例來說，我們搜尋
                 -rwxr-xr-x ，亦即 -perm /755 時，但一個檔案屬性為 -rw-------
                 也會被列出來，因為他有 -rw.... 的屬性存在！

範例五：找出檔名為 passwd 這個檔案
[root@study ~]# find / -name passwd

範例五-1：找出檔名包含了 passwd 這個關鍵字的檔案
[root@study ~]# find / -name "*passwd*"
# 利用這個 -name 可以搜尋檔名啊！預設是完整檔名，如果想要找關鍵字，
# 可以使用類似 * 的任意字元來處理

範例六：找出 /run 目錄下，檔案類型為 Socket 的檔名有哪些？
[root@study ~]# find /run -type s
# 這個 -type 的屬性也很有幫助喔！尤其是要找出那些怪異的檔案，
# 例如 socket 與 FIFO 檔案，可以用 find /run -type p 或 -type s 來找！

範例七：搜尋檔案當中含有 SGID 或 SUID 或 SBIT 的屬性
[root@study ~]# find / -perm /7000 
# 所謂的 7000 就是 ---s--s--t ，那麼只要含有 s 或 t 的就列出，所以當然要使用 /7000，
# 使用 -7000 表示要同時含有 ---s--s--t 的所有三個權限。而只需要任意一個，就是 /7000 ～瞭乎？
```

因為 SUID 是 4 分，SGID 2 分，總共為 6 分，因此可用 /6000 來處理這個權限！ 至於 find 後面可以接多個目錄來進行搜尋！另外， find 本來就會搜尋次目錄，這個特色也要特別注意喔！ 最後，我們再來看一下 find 還有什麼特殊功能吧！
```
選項與參數：
4. 額外可進行的動作：
   -exec command ：command 為其他指令，-exec 後面可再接額外的指令來處理搜尋到的結果。
   -print        ：將結果列印到螢幕上，這個動作是預設動作！

範例八：將上個範例找到的檔案使用 ls -l 列出來～
[root@study ~]# find /usr/bin /usr/sbin -perm /7000 -exec ls -l {} \;
# 注意到，那個 -exec 後面的 ls -l 就是額外的指令，指令不支援命令別名，
# 所以僅能使用 ls -l 不可以使用 ll 喔！注意注意！

範例九：找出系統中，大於 1MB 的檔案
[root@study ~]# find / -size +1M
```

## 6.6 極重要的複習！權限與指令間的關係
一、讓使用者能進入某目錄成為『可工作目錄』的基本權限為何：

     可使用的指令：例如 cd 等變換工作目錄的指令；
     目錄所需權限：使用者對這個目錄至少需要具有 x 的權限
     額外需求：如果使用者想要在這個目錄內利用 ls 查閱檔名，則使用者對此目錄還需要 r 的權限。
二、使用者在某個目錄內讀取一個檔案的基本權限為何？

     可使用的指令：例如本章談到的 cat, more, less等等
     目錄所需權限：使用者對這個目錄至少需要具有 x 權限；
     檔案所需權限：使用者對檔案至少需要具有 r 的權限才行！
三、讓使用者可以修改一個檔案的基本權限為何？

     可使用的指令：例如 nano 或未來要介紹的 vi 編輯器等；
     目錄所需權限：使用者在該檔案所在的目錄至少要有 x 權限；
     檔案所需權限：使用者對該檔案至少要有 r, w 權限
四、讓一個使用者可以建立一個檔案的基本權限為何？

     目錄所需權限：使用者在該目錄要具有 w,x 的權限，重點在 w 啦！
五、讓使用者進入某目錄並執行該目錄下的某個指令之基本權限為何？

     目錄所需權限：使用者在該目錄至少要有 x 的權限；
     檔案所需權限：使用者在該檔案至少需要有 x 的權限

## 6.7 重點回顧
- 絕對路徑：『一定由根目錄 / 寫起』；相對路徑：『不由 / 寫起，而是由相對當前目錄寫起』
- 特殊目錄有：., .., -, ~, ~account需要注意；
- 與目錄相關的指令有：cd, mkdir, rmdir, pwd 等重要指令；
- rmdir 僅能刪除空目錄，要刪除非空目錄需使用『 rm -r 』指令；
- 使用者能使用的指令是依據 PATH 變數所規定的目錄去搜尋的；
- ls 可以檢視檔案的屬性，尤其 -d, -a, -l 等選項特別重要！
- 檔案的複製、刪除、移動可以分別使用：cp, rm , mv等指令來操作；
- 檢查檔案的內容(讀檔)可使用的指令包括有：cat, tac, nl, more, less, head, tail, od 等
- cat -n 與 nl 均可顯示行號，但預設的情況下，空白行會不會編號並不相同；
- touch 的目的在修改檔案的時間參數，但亦可用來建立空檔案；
- 一個檔案記錄的時間參數有三種，分別是 access time(atime), status time (ctime), modification time(mtime)，ls 預設顯示的是 mtime。
- 除了傳統的rwx權限之外，在Ext2/Ext3/Ext4/xfs檔案系統中，還可以使用chattr與lsattr設定及觀察隱藏屬性。 常見的包括只能新增資料的 +a 與完全不能更動檔案的 +i 屬性。
- 新建檔案/目錄時，新檔案的預設權限使用 umask 來規範。預設目錄完全權限為drwxrwxrwx， 檔案則為-rw-rw-rw-。
- 檔案具有SUID的特殊權限時，代表當使用者執行此一binary程式時，在執行過程中使用者會暫時具有程式擁有者的權限
- 目錄具有SGID的特殊權限時，代表使用者在這個目錄底下新建的檔案之群組都會與該目錄的群組名稱相同。
- 目錄具有SBIT的特殊權限時，代表在該目錄下使用者建立的檔案只有自己與root能夠刪除！
- 觀察檔案的類型可以使用 file 指令來觀察；
- 搜尋指令的完整檔名可用 which 或 type ，這兩個指令都是透過 PATH 變數來搜尋檔名；
- 搜尋檔案的完整檔名可以使用 whereis 找特定目錄或 locate 到資料庫去搜尋，而不實際搜尋檔案系統；
- 利用 find 可以加入許多選項來直接查詢檔案系統，以獲得自己想要知道的檔名。

---
# 第七章、Linux 磁碟與檔案系統管理

## 7.1 認識 Linux 檔案系統
**Linux 最傳統的磁碟檔案系統 (filesystem) 使用的是 EXT2 這個啦！**所以要瞭解 Linux 的檔案系統就得要由認識 EXT2 開始！ 而檔案系統是建立在磁碟上面的，因此我們得瞭解磁碟的物理組成才行。磁碟物理組成的部分我們在第零章談過了，至於磁碟分割則在第二章談過了，所以底下只會很快的複習這兩部份。 重點在於 inode, block 還有 superblock 等檔案系統的基本部分喔！

### 7.1.1 磁碟組成與分割的複習
由於各項磁碟的物理組成我們在第零章裡面就介紹過， 同時第二章也談過分割的概念了，所以這個小節我們就拿之前的重點出來介紹就好了！ 詳細的資訊請您回去那兩章自行複習喔！^_^。好了，首先說明一下磁碟的物理組成，整顆磁碟的組成主要有：

- 圓形的磁碟盤(主要記錄資料的部分)；
- 機械手臂，與在機械手臂上的磁碟讀取頭(可讀寫磁碟盤上的資料)；
- 主軸馬達，可以轉動磁碟盤，讓機械手臂的讀取頭在磁碟盤上讀寫資料。

從上面我們知道資料儲存與讀取的重點在於磁碟盤，而磁碟盤上的物理組成則為(假設此磁碟為單碟片， 磁碟盤圖示請參考第二章圖2.2.1的示意)：
- 磁區(Sector)為最小的物理儲存單位，且依據磁碟設計的不同，目前主要有 512bytes 與 4K 兩種格式；
- 將磁區組成一個圓，那就是磁柱(Cylinder)；
- 早期的分割主要以磁柱為最小分割單位，現在的分割通常使用磁區為最小分割單位(每個磁區都有其號碼喔，就好像座位一樣)；
- 磁碟分割表主要有兩種格式，一種是限制較多的 MBR 分割表，一種是較新且限制較少的 GPT 分割表。
- MBR 分割表中，第一個磁區最重要，裡面有：(1)主要開機區(Master boot record, MBR)及分割表(partition table)， 其中 MBR 佔有 446 bytes，而 partition table 則佔有 64 bytes。
- GPT 分割表除了分割數量擴充較多之外，支援的磁碟容量也可以超過 2TB。

至於磁碟的檔名部份，基本上，所有實體磁碟的檔名都已經被模擬成 /dev/sd[a-p] 的格式，第一顆磁碟檔名為 /dev/sda。 **而分割槽的檔名若以第一顆磁碟為例，則為 /dev/sda[1-128]**。除了實體磁碟之外，**虛擬機的磁碟通常為 /dev/vd[a-p] 的格式。** 若有使用到軟體磁碟陣列的話，那還有 /dev/md[0-128] 的磁碟檔名。使用的是 LVM 時，檔名則為 /dev/VGNAME/LVNAME 等格式。 關於軟體磁碟陣列與 LVM 我們會在後面繼續介紹，這裡主要介紹的以實體磁碟及虛擬磁碟為主喔！

- /dev/sd[a-p][1-128]：為實體磁碟的磁碟檔名；
- /dev/vd[a-d][1-128]：為虛擬磁碟的磁碟檔名

### 7.1.2 檔案系統特性
我們都知道磁碟分割完畢後還需要進行格式化(format)，之後作業系統才能夠使用這個檔案系統。 為什麼需要進行『格式化』呢？這是因為每種作業系統所設定的檔案屬性/權限並不相同， 為了存放這些檔案所需的資料，**因此就需要將分割槽進行格式化，以成為作業系統能夠利用的『檔案系統格式(filesystem)』**。

由此我們也能夠知道，每種作業系統能夠使用的檔案系統並不相同。 舉例來說，**windows 98 以前的微軟作業系統主要利用的檔案系統是 FAT (或 FAT16)**，**windows 2000 以後的版本有所謂的 NTFS 檔案系統**，至於 **Linux 的正統檔案系統則為 Ext2 (Linux second extended file system, ext2fs)這一個**。此外，在預設的情況下，windows 作業系統是不會認識 Linux 的 Ext2 的。

傳統的磁碟與檔案系統之應用中，一個分割槽就是只能夠被格式化成為一個檔案系統，所以我們可以說一個 filesystem 就是一個 partition。但是由於新技術的利用，例如我們常聽到的LVM與軟體磁碟陣列(software raid)， 這些技術可以將一個分割槽格式化為多個檔案系統(例如LVM)，也能夠將多個分割槽合成一個檔案系統(LVM, RAID)！ 所以說，目前我們在格式化時已經不再說成針對 partition 來格式化了， 通常我們可以稱呼一個可被掛載的資料為一個檔案系統而不是一個分割槽喔！

那麼檔案系統是如何運作的呢？這與作業系統的檔案資料有關。**較新的作業系統的檔案資料除了檔案實際內容外， 通常含有非常多的屬性**，例如 **Linux 作業系統的檔案權限(rwx)與檔案屬性(擁有者、群組、時間參數等)。 檔案系統通常會將這兩部份的資料分別存放在不同的區塊**，**權限與屬性放置到 inode 中，至於實際資料則放置到 data block 區塊中。 另外，還有一個超級區塊 (superblock) 會記錄整個檔案系統的整體資訊，包括 inode 與 block 的總量、使用量、剩餘量等。**

每個 inode 與 block 都有編號，至於這三個資料的意義可以簡略說明如下：
- superblock：記錄此 filesystem 的整體資訊，包括inode/block的總量、使用量、剩餘量， 以及檔案系統的格式與相關資訊等；
- inode：記錄檔案的屬性，一個檔案佔用一個inode，同時記錄此檔案的資料所在的 block 號碼；
- block：實際記錄檔案的內容，若檔案太大時，會佔用多個 block 。

由於每個 inode 與 block 都有編號，而每個檔案都會佔用一個 inode ，inode 內則有檔案資料放置的 block 號碼。 因此，我們可以知道的是，**如果能夠找到檔案的 inode 的話，那麼自然就會知道這個檔案所放置資料的 block 號碼， 當然也就能夠讀出該檔案的實際資料了。**這是個比較有效率的作法，因為如此一來我們的磁碟就能夠在短時間內讀取出全部的資料， 讀寫的效能比較好囉。

我們將 inode 與 block 區塊用圖解來說明一下，如下圖所示，檔案系統先格式化出 inode 與 block 的區塊，假設某一個檔案的屬性與權限資料是放置到 inode 4 號(下圖較小方格內)，而這個 inode 記錄了檔案資料的實際放置點為 2, 7, 13, 15 這四個 block 號碼，此時我們的作業系統就能夠據此來排列磁碟的讀取順序，可以一口氣將四個 block 內容讀出來！ 那麼資料的讀取就如同下圖中的箭頭所指定的模樣了。

<div align=center><img src="/os_note/linux_file/picture/filesystem-1.jpg"></div>
<div align=center>圖7.1.1、inode/block 資料存取示意圖</div>

**這種資料存取的方法我們稱為索引式檔案系統(indexed allocation)。** 那有沒有其他的慣用檔案系統可以比較一下啊？ 有的，那就是我們慣用的隨身碟(快閃記憶體)，隨身碟使用的檔案系統一般為 FAT 格式。FAT 這種格式的檔案系統並沒有 inode 存在，所以 FAT 沒有辦法將這個檔案的所有 block 在一開始就讀取出來。每個 block 號碼都記錄在前一個 block 當中， 他的讀取方式有點像底下這樣：

<div align=center><img src="/os_note/linux_file/picture/filesystem-2.jpg"></div>
<div align=center>圖7.1.2、FAT檔案系統資料存取示意圖（链表式存储）</div>

常常會聽到所謂的『磁碟重組』吧？ 需要磁碟重組的原因就是檔案寫入的 block 太過於離散了，此時檔案讀取的效能將會變的很差所致。 這個時候可以透過磁碟重組將同一個檔案所屬的 blocks 彙整在一起，這樣資料的讀取會比較容易啊！ 想當然爾，FAT 的檔案系統需要三不五時的磁碟重組一下，那麼 Ext2 是否需要磁碟重整呢？

由於 Ext2 是索引式檔案系統，基本上不太需要常常進行磁碟重組的。但是如果檔案系統使用太久， 常常刪除/編輯/新增檔案時，那麼還是可能會造成檔案資料太過於離散的問題，此時或許會需要進行重整一下的。 不過，老實說，鳥哥倒是沒有在 Linux 作業系統上面進行過 Ext2/Ext3 檔案系統的磁碟重組說！似乎不太需要啦！^_^

### 7.1.3 Linux 的 EXT2 檔案系統(inode)
在第五章當中我們介紹過 Linux 的檔案除了原有的資料內容外，還含有非常多的權限與屬性，這些權限與屬性是為了保護每個使用者所擁有資料的隱密性。 而前一小節我們知道 filesystem 裡面可能含有的 inode/block/superblock 等。為什麼要談這個呢？因為標準的 Linux 檔案系統 Ext2 就是使用這種 inode 為基礎的檔案系統啦！

而如同前一小節所說的，inode 的內容在記錄檔案的權限與相關屬性，至於 block 區塊則是在記錄檔案的實際內容。 而且檔案系統一開始就將 inode 與 block 規劃好了，除非重新格式化(或者利用 resize2fs 等指令變更檔案系統大小)，**否則 inode 與 block 固定後就不再變動**。但是如果仔細考慮一下，如果我的檔案系統高達數百GB時， 那麼將所有的 inode 與 block 通通放置在一起將是很不智的決定，因為 inode 與 block 的數量太龐大，不容易管理。

為此之故，**因此 Ext2 檔案系統在格式化的時候基本上是區分為多個區塊群組 (block group) 的**，**每個區塊群組都有獨立的 inode/block/superblock 系統**。感覺上就好像我們在當兵時，一個營裡面有分成數個連，每個連有自己的聯絡系統， 但最終都向營部回報連上最正確的資訊一般！這樣分成一群群的比較好管理啦！整個來說，Ext2 格式化後有點像底下這樣：

<div align=center><img src="/os_note/linux_file/picture/ext2_filesystem.jpg"></div>
<div align=center>圖7.1.3、ext2檔案系統示意圖 (註1)</div>

在整體的規劃當中，檔案系統最前面有一個開機磁區(boot sector)，這個開機磁區可以安裝開機管理程式， 這是個非常重要的設計，因為如此一來我們就能夠將不同的開機管理程式安裝到個別的檔案系統最前端，而不用覆蓋整顆磁碟唯一的 MBR， 這樣也才能夠製作出多重開機的環境啊！至於每一個區塊群組(block group)的六個主要內容說明如後：

#### data block (資料區塊)
data block 是用來放置檔案內容資料地方，在 Ext2 檔案系統中所支援的 block 大小有 1K, 2K 及 4K 三種而已。在格式化時 block 的大小就固定了，且每個 block 都有編號，以方便 inode 的記錄啦。 不過要注意的是，由於 block 大小的差異，會導致該檔案系統能夠支援的最大磁碟容量與最大單一檔案容量並不相同。 因為 block 大小而產生的 Ext2 檔案系統限制如下：(註2)


| Block 大小      | 1KB | 2KB | 4KB |
| --------------- | ----------- |---- | --- | --- |
| 最大單一檔案限制      | 16GB   | 256GB | 2TB |
| 最大檔案系統總容量   | 2TB  | 8TB | 16TB |

你需要注意的是，雖然 Ext2 已經能夠支援大於 2GB 以上的單一檔案容量，不過某些應用程式依然使用舊的限制， 也就是說，某些程式只能夠捉到小於 2GB 以下的檔案而已，這就跟檔案系統無關了！ 舉例來說，鳥哥在環工方面的應用中有一套秀圖軟體稱為PAVE(註3)， 這套軟體就無法捉到鳥哥在數值模式模擬後產生的大於 2GB 以上的檔案！所以後來只能找更新的軟體來取代它了！
除此之外 Ext2 檔案系統的 block 還有什麼限制呢？有的！基本限制如下：
- 原則上，block 的大小與數量在格式化完就不能夠再改變了(除非重新格式化)；
- 每個 block 內最多只能夠放置一個檔案的資料；
- 承上，如果檔案大於 block 的大小，則一個檔案會佔用多個 block 數量；
- 承上，若檔案小於 block ，則該 block 的剩餘容量就不能夠再被使用了(磁碟空間會浪費)。

如上第四點所說，由於每個 block 僅能容納一個檔案的資料而已，因此如果你的檔案都非常小，但是你的 block 在格式化時卻選用最大的 4K 時，可能會產生一些容量的浪費喔！我們以底下的一個簡單例題來算一下空間的浪費吧！

>
>例題：
>假設你的Ext2檔案系統使用 4K block ，而該檔案系統中有 10000 個小檔案，每個檔案大小均為 50bytes， 請問此時你的磁碟浪費多少容量？

>答：
由於 Ext2 檔案系統中一個 block 僅能容納一個檔案，因此每個 block 會浪費『 4096 - 50 = 4046 (byte)』， 系統中總共有一萬個小檔案，所有檔案容量為：50 (bytes) x 10000 = 488.3Kbytes，但此時浪費的容量為：『 4046 (bytes) x 10000 = 38.6MBytes 』。想一想，不到 1MB 的總檔案容量卻浪費將近 40MB 的容量，且檔案越多將造成越多的磁碟容量浪費。

什麼情況會產生上述的狀況呢？例如 BBS 網站的資料啦！如果 BBS 上面的資料使用的是純文字檔案來記載每篇留言， 而留言內容如果都寫上『如題』時，想一想，是否就會產生很多小檔案了呢？

好，既然大的 block 可能會產生較嚴重的磁碟容量浪費，那麼我們是否就將 block 大小訂為 1K 即可？ 這也不妥，**因為如果 block 較小的話，那麼大型檔案將會佔用數量更多的 block ，而 inode 也要記錄更多的 block 號碼，此時將可能導致檔案系統不良的讀寫效能。**

所以我們可以說，在您進行檔案系統的格式化之前，請先想好該檔案系統預計使用的情況。 以鳥哥來說，我的數值模式模擬平台隨便一個檔案都好幾百 MB，那麼 block 容量當然選擇較大的！至少檔案系統就不必記錄太多的 block 號碼，讀寫起來也比較方便啊！

#### inode table (inode 表格)
再來討論一下 inode 這個玩意兒吧！如前所述 **inode 的內容在記錄檔案的屬性以及該檔案實際資料是放置在哪幾號 block 內！** 基本上，inode 記錄的檔案資料至少有底下這些：(註4)

- 該檔案的存取模式(read/write/excute)；
- 該檔案的擁有者與群組(owner/group)；
- 該檔案的容量；
- 該檔案建立或狀態改變的時間(ctime)；
- 最近一次的讀取時間(atime)；
- 最近修改的時間(mtime)；
- 定義檔案特性的旗標(flag)，如 SetUID...；
- 該檔案真正內容的指向 (pointer)；

inode 的數量與大小也是在格式化時就已經固定了，除此之外 inode 還有些什麼特色呢？

- **每個 inode 大小均固定為 128 bytes (新的 ext4 與 xfs 可設定到 256 bytes)**；
- **每個檔案都僅會佔用一個 inode 而已**；
- 承上，因此檔案系統能夠建立的檔案數量與 inode 的數量有關；
- 系統讀取檔案時需要先找到 inode，並分析 inode 所記錄的權限與使用者是否符合，若符合才能夠開始實際讀取 block 的內容。

我們約略來分析一下 EXT2 的 inode / block 與檔案大小的關係好了。inode 要記錄的資料非常多，但偏偏又只有 128bytes 而已， 而 inode 記錄一個 block 號碼要花掉 4byte ，假設我一個檔案有 400MB 且每個 block 為 4K 時， 那麼至少也要十萬筆 block 號碼的記錄呢！inode 哪有這麼多可記錄的資訊？為此我們的系統很聰明的將 inode 記錄 block 號碼的區域定義為12個直接，一個間接, 一個雙間接與一個三間接記錄區。這是啥？我們將 inode 的結構畫一下好了。
<div align=center><img src="/os_note/linux_file/picture/inode.jpg"></div>
<div align=center>
圖7.1.4、inode 結構示意圖</div>
上圖最左邊為 inode 本身 (128 bytes)，裡面有 12 個直接指向 block 號碼的對照，這 12 筆記錄就能夠直接取得 block 號碼啦！ 至於所謂的間接就是再拿一個 block 來當作記錄 block 號碼的記錄區，如果檔案太大時， 就會使用間接的 block 來記錄號碼。如上圖 7.1.4 當中間接只是拿一個 block 來記錄額外的號碼而已。 同理，如果檔案持續長大，那麼就會利用所謂的雙間接，第一個 block 僅再指出下一個記錄號碼的 block 在哪裡， 實際記錄的在第二個 block 當中。依此類推，三間接就是利用第三層 block 來記錄號碼啦！

這樣子 inode 能夠指定多少個 block 呢？我們以較小的 1K block 來說明好了，可以指定的情況如下：
- 12 個直接指向： 12*1K=12K
由於是直接指向，所以總共可記錄 12 筆記錄，因此總額大小為如上所示；

- 間接： 256*1K=256K
每筆 block 號碼的記錄會花去 4bytes，因此 1K 的大小能夠記錄 256 筆記錄，因此一個間接可以記錄的檔案大小如上；

- 雙間接： 256*256*1K=2562K
第一層 block 會指定 256 個第二層，每個第二層可以指定 256 個號碼，因此總額大小如上；

- 三間接： 256*256*256*1K=2563K
第一層 block 會指定 256 個第二層，每個第二層可以指定 256 個第三層，每個第三層可以指定 256 個號碼，因此總額大小如上；

- 總額：將直接、間接、雙間接、三間接加總，得到 12 + 256 + 256*256 + 256*256*256 (K) = 16GB

此時我們知道當檔案系統將 block 格式化為 1K 大小時，能夠容納的最大檔案為 16GB，比較一下檔案系統限制表的結果可發現是一致的！但這個方法不能用在 2K 及 4K block 大小的計算中， 因為大於 2K 的 block 將會受到 Ext2 檔案系統本身的限制，所以計算的結果會不太符合之故。

>如果你的 Linux 依舊使用 Ext2/Ext3/Ext4 檔案系統的話，例如鳥哥之前的 CentOS 6.x 系統，那麼預設還是使用 Ext4 的檔案系統喔！ Ext4 檔案系統的 inode 容量已經可以擴大到 256bytes 了，更大的 inode 容量，可以紀錄更多的檔案系統資訊，包括新的 ACL 以及 SELinux 類型等， 當然，可以紀錄的單一檔案容量達 16TB 且單一檔案系統總容量可達 1EB 哩！

#### Superblock (超級區塊)
Superblock 是記錄整個 filesystem 相關資訊的地方， 沒有 Superblock ，就沒有這個 filesystem 了。他記錄的資訊主要有：
- block 與 inode 的總量；
- 未使用與已使用的 inode / block 數量；
- block 與 inode 的大小 (block 為 1, 2, 4K，inode 為 128bytes 或 256bytes)；
- filesystem 的掛載時間、最近一次寫入資料的時間、最近一次檢驗磁碟 (fsck) 的時間等檔案系統的相關資訊；
- 一個 valid bit 數值，若此檔案系統已被掛載，則 valid bit 為 0 ，若未被掛載，則 valid bit 為 1 。

Superblock 是非常重要的，因為我們這個檔案系統的基本資訊都寫在這裡，因此，如果 superblock 死掉了， 你的檔案系統可能就需要花費很多時間去挽救啦！一般來說， superblock 的大小為 1024bytes。相關的 superblock 訊息我們等一下會以 dumpe2fs 指令來呼叫出來觀察喔！

此外，每個 block group 都可能含有 superblock 喔！但是我們也說一個檔案系統應該僅有一個 superblock 而已，那是怎麼回事啊？ 事實上除了第一個 block group 內會含有 superblock 之外，後續的 block group 不一定含有 superblock ， 而若含有 superblock 則該 superblock 主要是做為第一個 block group 內 superblock 的備份咯，這樣可以進行 superblock 的救援呢！

#### Filesystem Description (檔案系統描述說明)
這個區段可以描述每個 block group 的開始與結束的 block 號碼，以及說明每個區段 (superblock, bitmap, inodemap, data block) 分別介於哪一個 block 號碼之間。這部份也能夠用 dumpe2fs 來觀察的。

#### block bitmap (區塊對照表)
如果你想要新增檔案時總會用到 block 吧！那你要使用哪個 block 來記錄呢？當然是選擇『空的 block 』來記錄新檔案的資料囉。 那你怎麼知道哪個 block 是空的？這就得要透過 block bitmap 的輔助了。從 block bitmap 當中可以知道哪些 block 是空的，因此我們的系統就能夠很快速的找到可使用的空間來處置檔案囉。

同樣的，如果你刪除某些檔案時，那麼那些檔案原本佔用的 block 號碼就得要釋放出來， 此時在 block bitmap 當中相對應到該 block 號碼的標誌就得要修改成為『未使用中』囉！這就是 bitmap 的功能。

#### inode bitmap (inode 對照表)
這個其實與 block bitmap 是類似的功能，只是 block bitmap 記錄的是使用與未使用的 block 號碼， 至於 inode bitmap 則是記錄使用與未使用的 inode 號碼囉！

---
#### dumpe2fs： 查詢 Ext 家族 superblock 資訊的指令
瞭解了檔案系統的概念之後，再來當然是觀察這個檔案系統囉！剛剛談到的各部分資料都與 block 號碼有關！ 每個區段與 superblock 的資訊都可以使用 dumpe2fs 這個指令來查詢的！不過很可惜的是，我們的 CentOS 7 現在是以 xfs 為預設檔案系統， 所以目前你的系統應該無法使用 dumpe2fs 去查詢任何檔案系統的。沒關係，鳥哥先找自己的一部機器來跟大家介紹， 你可以在後續的格式化內容講完之後，自己切出一個 ext4 的檔案系統去查詢看看即可。鳥哥這塊檔案系統是 1GB 的容量，使用預設方式來進行格式化的， 觀察的內容如下：

```
[root@study ~]# dumpe2fs [-bh] 裝置檔名
選項與參數：
-b ：列出保留為壞軌的部分(一般用不到吧！？)
-h ：僅列出 superblock 的資料，不會列出其他的區段內容！

範例：鳥哥的一塊 1GB ext4 檔案系統內容
[root@study ~]# blkid   <==這個指令可以叫出目前系統有被格式化的裝置
/dev/vda1: LABEL="myboot" UUID="ce4dbf1b-2b3d-4973-8234-73768e8fd659" TYPE="xfs"
/dev/vda2: LABEL="myroot" UUID="21ad8b9a-aaad-443c-b732-4e2522e95e23" TYPE="xfs"
/dev/vda3: UUID="12y99K-bv2A-y7RY-jhEW-rIWf-PcH5-SaiApN" TYPE="LVM2_member"
/dev/vda5: UUID="e20d65d9-20d4-472f-9f91-cdcfb30219d6" TYPE="ext4"  <==看到 ext4 了！

[root@study ~]# dumpe2fs /dev/vda5
dumpe2fs 1.42.9 (28-Dec-2013)
Filesystem volume name:   <none>           # 檔案系統的名稱(不一定會有)
Last mounted on:          <not available>  # 上一次掛載的目錄位置
Filesystem UUID:          e20d65d9-20d4-472f-9f91-cdcfb30219d6
Filesystem magic number:  0xEF53           # 上方的 UUID 為 Linux 對裝置的定義碼
Filesystem revision #:    1 (dynamic)      # 下方的 features 為檔案系統的特徵資料
Filesystem features:      has_journal ext_attr resize_inode dir_index filetype extent 64bit 
 flex_bg sparse_super large_file huge_file uninit_bg dir_nlink extra_isize
Filesystem flags:         signed_directory_hash
Default mount options:    user_xattr acl   # 預設在掛載時會主動加上的掛載參數
Filesystem state:         clean            # 這塊檔案系統的狀態為何，clean 是沒問題
Errors behavior:          Continue
Filesystem OS type:       Linux
Inode count:              65536            # inode 的總數
Block count:              262144           # block 的總數
Reserved block count:     13107            # 保留的 block 總數
Free blocks:              249189           # 還有多少的 block 可用數量
Free inodes:              65525            # 還有多少的 inode 可用數量
First block:              0
Block size:               4096             # 單個 block 的容量大小
Fragment size:            4096
Group descriptor size:    64
....(中間省略)....
Inode size:               256              # inode 的容量大小！已經是 256 了喔！
....(中間省略)....
Journal inode:            8
Default directory hash:   half_md4
Directory Hash Seed:      3c2568b4-1a7e-44cf-95a2-c8867fb19fbc
Journal backup:           inode blocks
Journal features:         (none)
Journal size:             32M              # Journal 日誌式資料的可供紀錄總容量
Journal length:           8192
Journal sequence:         0x00000001
Journal start:            0

Group 0: (Blocks 0-32767)                  # 第一塊 block group 位置
  Checksum 0x13be, unused inodes 8181
  Primary superblock at 0, Group descriptors at 1-1   # 主要 superblock 的所在喔！
  Reserved GDT blocks at 2-128
  Block bitmap at 129 (+129), Inode bitmap at 145 (+145)
  Inode table at 161-672 (+161)                       # inode table 的所在喔！
  28521 free blocks, 8181 free inodes, 2 directories, 8181 unused inodes
  Free blocks: 142-144, 153-160, 4258-32767           # 底下兩行說明剩餘的容量有多少
  Free inodes: 12-8192
Group 1: (Blocks 32768-65535) [INODE_UNINIT]          # 後續為更多其他的 block group 喔！
....(底下省略)....
# 由於資料量非常的龐大，因此鳥哥將一些資訊省略輸出了！上表與你的螢幕會有點差異。
# 前半部在秀出 supberblock 的內容，包括標頭名稱(Label)以及inode/block的相關資訊
# 後面則是每個 block group 的個別資訊了！您可以看到各區段資料所在的號碼！
# 也就是說，基本上所有的資料還是與 block 的號碼有關就是了！很重要！
```
如上所示，利用 dumpe2fs 可以查詢到非常多的資訊，不過依內容主要可以區分為上半部是 superblock 內容， 下半部則是每個 block group 的資訊了。從上面的表格中我們可以觀察到鳥哥這個 /dev/vda5 規劃的 block 為 4K， 第一個 block 號碼為 0 號，且 block group 內的所有資訊都以 block 的號碼來表示的。 然後在 superblock 中還有談到目前這個檔案系統的可用 block 與 inode 數量喔！

至於 block group 的內容我們單純看 Group0 資訊好了。從上表中我們可以發現：
- Group0 所佔用的 block 號碼由 0 到 32767 號，**superblock 則在第 0 號的 block 區塊內！**
- **檔案系統描述說明在第 1 號 block 中；**
- block bitmap 與 inode bitmap 則在 129 及 145 的 block 號碼上。
- 至於 inode table 分佈於 161-672 的 block 號碼中！
- 由於 (1)一個 inode 佔用 256 bytes ，(2)總共有 672 - 161 + 1(161本身) = 512 個 - block 花在 inode table 上， (3)每個 block 的大小為 4096 bytes(4K)。由這些數據可以算出 inode 的數量共有 512 * 4096 / 256 = 8192 個 inode 啦！
- 這個 Group0 目前可用的 block 有 28521 個，可用的 inode 有 8181 個；
- 剩餘的 inode 號碼為 12 號到 8192 號。

### 7.1.4 與目錄樹的關係
由前一小節的介紹我們知道在 Linux 系統下，每個檔案(不管是一般檔案還是目錄檔案)都會佔用一個 inode ， 且可依據檔案內容的大小來分配多個 block 給該檔案使用。而由第五章的權限說明中我們知道目錄的內容在記錄檔名， 一般檔案才是實際記錄資料內容的地方。那麼目錄與檔案在檔案系統當中是如何記錄資料的呢？基本上可以這樣說：

#### 目錄
當我們在 Linux 下的檔案系統建立一個目錄時，**檔案系統會分配一個 inode 與至少一塊 block 給該目錄。** 其中，inode 記錄該目錄的相關權限與屬性，並可記錄分配到的那塊 block 號碼； 而 block 則是記錄在這個目錄下的檔名與該檔名佔用的 inode 號碼資料。也就是說目錄所佔用的 block 內容在記錄如下的資訊：
<div align =center><img src="/os_note/linux_file/picture/centos7_dir_block.jpg"></div>
<div align =center>圖7.1.5、記載於目錄所屬的 block 內的檔名與 inode 號碼對應示意圖</div>
如果想要實際觀察 root 家目錄內的檔案所佔用的 inode 號碼時，可以使用 ls -i 這個選項來處理：
```
kevin@ubuntu:~/os$ ls -li
total 508
1769589 drwxrwxr-x 5 kevin kevin   4096 Oct 18 15:42 os_experiment
1769590 drwxrwxr-x 8 kevin kevin   4096 Oct 22 19:57 os_note
1745543 -rwxrw-rw- 1 kevin kevin 508889 Oct  9 15:33 路线图.jpg
```
由於每個人所使用的電腦並不相同，系統安裝時選擇的項目與 partition 都不一樣，因此你的環境不可能與我的 inode 號碼一模一樣！上表的左邊所列出的 inode 僅是鳥哥的系統所顯示的結果而已！而由這個目錄的 block 結果我們現在就能夠知道， 當你使用『 ll / 』時，出現的目錄幾乎都是 1024 的倍數，為什麼呢？因為每個 block 的數量都是 1K, 2K, 4K 嘛！ 看一下鳥哥的環境：

由於鳥哥的根目錄使用的 block 大小為 4K ，因此每個目錄幾乎都是 4K 的倍數。 其中由於 /usr/sbin 的內容比較複雜因此佔用了 4 個 block ！至於奇怪的 /proc 我們在第五章就講過該目錄不佔磁碟容量， 所以當然耗用的 block 就是 0 囉！
>由上面的結果我們知道目錄並不只會佔用一個 block 而已，也就是說： 在目錄底下的檔案數如果太多而導致一個 block 無法容納的下所有的檔名與 inode 對照表時，Linux 會給予該目錄多一個 block 來繼續記錄相關的資料；

#### 檔案：
當我們在 Linux 下的 ext2 建立一個一般檔案時， ext2 會分配一個 inode 與相對於該檔案大小的 block 數量給該檔案。例如：假設我的一個 block 為 4 Kbytes ，而我要建立一個 100 KBytes 的檔案，那麼 linux 將分配一個 inode 與 25 個 block 來儲存該檔案！ 但同時請注意，由於 inode 僅有 12 個直接指向，因此還要多一個 block 來作為區塊號碼的記錄喔！
#### 目錄樹讀取：
好了，經過上面的說明你也應該要很清楚的知道 inode 本身並不記錄檔名，**檔名的記錄是在目錄的 block 當中**。 因此在第五章檔案與目錄的權限說明中， 我們才會提到『新增/刪除/更名檔名與目錄的 w 權限有關』的特色！**那麼因為檔名是記錄在目錄的 block 當中， 因此當我們要讀取某個檔案時，就務必會經過目錄的 inode 與 block ，然後才能夠找到那個待讀取檔案的 inode 號碼， 最終才會讀到正確的檔案的 block 內的資料**。

由於目錄樹是由根目錄開始讀起，**因此系統透過掛載的資訊可以找到掛載點的 inode 號碼，此時就能夠得到根目錄的 inode 內容，並依據該 inode 讀取根目錄的 block 內的檔名資料，再一層一層的往下讀到正確的檔名**。舉例來說，如果我想要讀取 /etc/passwd 這個檔案時，系統是如何讀取的呢？
```
[root@study ~]# ll -di / /etc /etc/passwd
     128 dr-xr-xr-x.  17 root root 4096 May  4 17:56 /
33595521 drwxr-xr-x. 131 root root 8192 Jun 17 00:20 /etc
36628004 -rw-r--r--.   1 root root 2092 Jun 17 00:20 /etc/passwd
```
在鳥哥的系統上面與 /etc/passwd 有關的目錄與檔案資料如上表所示，該檔案的讀取流程為(假設讀取者身份為 dmtsai 這個一般身份使用者)：

1. / 的 inode：
透過掛載點的資訊找到 inode 號碼為 128 的根目錄 inode，且 inode 規範的權限讓我們可以讀取該 block 的內容(有 r 與 x) ；

2. / 的 block：
經過上個步驟取得 block 的號碼，並找到該內容有 etc/ 目錄的 inode 號碼 (33595521)；

3. etc/ 的 inode：
讀取 33595521 號 inode 得知 dmtsai 具有 r 與 x 的權限，因此可以讀取 etc/ 的 block 內容；

4. etc/ 的 block：
經過上個步驟取得 block 號碼，並找到該內容有 passwd 檔案的 inode 號碼 (36628004)；

5. passwd 的 inode：
讀取 36628004 號 inode 得知 dmtsai 具有 r 的權限，因此可以讀取 passwd 的 block 內容；

6. passwd 的 block：
最後將該 block 內容的資料讀出來。

#### filesystem 大小與磁碟讀取效能：
另外，關於檔案系統的使用效率上，當你的一個檔案系統規劃的很大時，例如 100GB 這麼大時， 由於磁碟上面的資料總是來來去去的，所以，整個檔案系統上面的檔案通常無法連續寫在一起(block 號碼不會連續的意思)， 而是填入式的將資料填入沒有被使用的 block 當中。如果檔案寫入的 block 真的分的很散， 此時就會有所謂的檔案資料離散的問題發生了。

如前所述，雖然我們的 ext2 在 inode 處已經將該檔案所記錄的 block 號碼都記上了， 所以資料可以一次性讀取，但是如果檔案真的太過離散，確實還是會發生讀取效率低落的問題。 因為磁碟讀取頭還是得要在整個檔案系統中來來去去的頻繁讀取！ 果真如此，那麼可以將整個 filesystem 內的資料全部複製出來，將該 filesystem 重新格式化， 再將資料給他複製回去即可解決這個問題。

此外，如果 filesystem 真的太大了，那麼當一個檔案分別記錄在這個檔案系統的最前面與最後面的 block 號碼中， 此時會造成磁碟的機械手臂移動幅度過大，也會造成資料讀取效能的低落。而且讀取頭在搜尋整個 filesystem 時， 也會花費比較多的時間去搜尋！因此， partition 的規劃並不是越大越好， 而是真的要針對您的主機用途來進行規劃才行！^_^

### 7.1.5 EXT2/EXT3/EXT4 檔案的存取與日誌式檔案系統的功能
上一小節談到的僅是讀取而已，那麼如果是新建一個檔案或目錄時，我們的檔案系統是如何處理的呢？ 這個時候就得要 **block bitmap 及 inode bitmap** 的幫忙了！假設我們想要新增一個檔案，此時檔案系統的行為是：

1. 先確定使用者對於欲新增檔案的目錄是否具有 w 與 x 的權限，若有的話才能新增；
2. 根據 inode bitmap 找到沒有使用的 inode 號碼，並將新檔案的權限/屬性寫入；
3. 根據 block bitmap 找到沒有使用中的 block 號碼，並將實際的資料寫入 block 中，且更新 inode 的 block 指向資料；
4. 將剛剛寫入的 inode 與 block 資料同步更新 inode bitmap 與 block bitmap，並更新 superblock 的內容。

一般來說，我們將 inode table 與 data block 稱為資料存放區域，至於其他例如 superblock、 block bitmap 與 inode bitmap 等區段就被稱為 metadata (中介資料) 囉，因為 superblock, inode bitmap 及 block bitmap 的資料是經常變動的，每次新增、移除、編輯時都可能會影響到這三個部分的資料，因此才被稱為中介資料的啦。
#### 資料的不一致 (Inconsistent) 狀態
发生意外，所以寫入的資料僅有 inode table 及 data block 而已， 最後一個同步更新中介資料的步驟並沒有做完，此時就會發生 metadata 的內容與實際資料存放區產生不一致 (Inconsistent) 的情況了。

在早期的 Ext2 檔案系統中，如果發生這個問題， 那麼系統在重新開機的時候，就會藉由 Superblock 當中記錄的 valid bit (是否有掛載) 與 filesystem state (clean 與否) 等狀態來判斷是否強制進行資料一致性的檢查！若有需要檢查時則以 e2fsck 這支程式來進行的。

不過，這樣的檢查真的是很費時～因為要針對 metadata 區域與實際資料存放區來進行比對， 呵呵～得要搜尋整個 filesystem 呢～如果你的檔案系統有 100GB 以上，而且裡面的檔案數量又多時， 哇！系統真忙碌～而且在對 Internet 提供服務的伺服器主機上面， 這樣的檢查真的會造成主機復原時間的拉長～真是麻煩～這也就造成後來所謂日誌式檔案系統的興起了。

#### 日誌式檔案系統 (Journaling filesystem)
為了避免上述提到的檔案系統不一致的情況發生，因此我們的前輩們想到一個方式， 如果在我們的 filesystem 當中規劃出一個區塊，該區塊專門在記錄寫入或修訂檔案時的步驟， 那不就可以簡化一致性檢查的步驟了？也就是說：

1. 預備：當系統要寫入一個檔案時，會先在日誌記錄區塊中紀錄某個檔案準備要寫入的資訊；
2. 實際寫入：開始寫入檔案的權限與資料；開始更新 metadata 的資料；
3. 結束：完成資料與 metadata 的更新後，在日誌記錄區塊當中完成該檔案的紀錄。

在這樣的程序當中，萬一資料的紀錄過程當中發生了問題，那麼我們的系統只要去檢查日誌記錄區塊， 就可以知道哪個檔案發生了問題，針對該問題來做一致性的檢查即可，而不必針對整塊 filesystem 去檢查， 這樣就可以達到快速修復 filesystem 的能力了！這就是日誌式檔案最基礎的功能囉～

### 7.1.6 Linux 檔案系統的運作
為了解決這個效率的問題，因此我們的 Linux 使用的方式是透過一個稱為非同步處理 (asynchronously) 的方式。所謂的非同步處理是這樣的：

當系統載入一個檔案到記憶體後，如果該檔案沒有被更動過，則在記憶體區段的檔案資料會被設定為乾淨(clean)的。**但如果記憶體中的檔案資料被更改過了(例如你用 nano 去編輯過這個檔案)，此時該記憶體中的資料會被設定為髒的 (Dirty)。此時所有的動作都還在記憶體中執行，並沒有寫入到磁碟中** !系統會不定時的將記憶體中設定為『Dirty』的資料寫回磁碟，以保持磁碟與記憶體資料的一致性。 你也可以利用第四章談到的 sync指令來手動強迫寫入磁碟。

我們知道記憶體的速度要比磁碟快的多，因此如果能夠將常用的檔案放置到記憶體當中，這不就會增加系統性能嗎？ 沒錯！是有這樣的想法！因此我們 Linux 系統上面檔案系統與記憶體有非常大的關係喔：

- 系統會將常用的檔案資料放置到主記憶體的緩衝區，以加速檔案系統的讀/寫；
- 承上，因此 Linux 的實體記憶體最後都會被用光！這是正常的情況！可加速系統效能；
- 你可以手動使用 sync 來強迫記憶體中設定為 Dirty 的檔案回寫到磁碟中；
- 若正常關機時，關機指令會主動呼叫 sync 來將記憶體的資料回寫入磁碟內；
- 但若不正常關機(如跳電、當機或其他不明原因)，由於資料尚未回寫到磁碟內， 因此重新開機後可能會花很多時間在進行磁碟檢驗，甚至可能導致檔案系統的損毀(非磁碟損毀)。

### 7.1.7 掛載點的意義 (mount point)
每個 filesystem 都有獨立的 inode / block / superblock 等資訊，這個檔案系統要能夠連結到目錄樹才能被我們使用。 將檔案系統與目錄樹結合的動作我們稱為『掛載』。 關於掛載的一些特性我們在第二章稍微提過， 重點是：**掛載點一定是目錄，該目錄為進入該檔案系統的入口。**  因此並不是你有任何檔案系統都能使用，必須要『掛載』到目錄樹的某個目錄後，才能夠使用該檔案系統的。
```
kevin@ubuntu:~$ ls -ild /  /.  /..
2 drwxr-xr-x 24 root root 4096 Oct 20 09:54 /
2 drwxr-xr-x 24 root root 4096 Oct 20 09:54 /.
2 drwxr-xr-x 24 root root 4096 Oct 20 09:54 /..
```
上面的資訊中由於掛載點均為 / ，因此三個檔案 (/, /., /..) 均在同一個 filesystem 內，而這三個檔案的 inode 號碼均為 2 號，**因此這三個檔名都指向同一個 inode 號碼，當然這三個檔案的內容也就完全一模一樣了！ 也就是說，根目錄的上層 (/..) 就是他自己！** 這麼說，看的懂了嗎？ ^_^

### 7.1.8 其他 Linux 支援的檔案系統與 VFS

常見的支援檔案系統有：

- 傳統檔案系統：ext2 / minix / MS-DOS / FAT (用 vfat 模組) / iso9660 (光碟)等等；
- 日誌式檔案系統： ext3 /ext4 / ReiserFS / Windows' NTFS / IBM's JFS / SGI's XFS / ZFS
- 網路檔案系統： NFS / SMBFS

##### Linux VFS (Virtual Filesystem Switch)
瞭解了我們使用的檔案系統之後，再來則是要提到，那麼 Linux 的核心又是如何管理這些認識的檔案系統呢？ 其實，整個 Linux 的系統都是透過一個名為 Virtual Filesystem Switch 的核心功能去讀取 filesystem 的。 也就是說，整個 Linux 認識的 filesystem 其實都是 VFS 在進行管理，我們使用者並不需要知道每個 partition 上頭的 filesystem 是什麼～ VFS 會主動的幫我們做好讀取的動作呢～

假設你的 / 使用的是 /dev/hda1 ，用 ext3 ，而 /home 使用 /dev/hda2 ，用 reiserfs ， 那麼你取用 /home/dmtsai/.bashrc 時，有特別指定要用的什麼檔案系統的模組來讀取嗎？ 應該是沒有吧！這個就是 VFS 的功能啦！透過這個 VFS 的功能來管理所有的 filesystem， 省去我們需要自行設定讀取檔案系統的定義啊～方便很多！整個 VFS 可以約略用下圖來說明：
<div align=center><img src="/os_note/linux_file/picture/centos7_vfs.gif"></div>
<div align=center>圖7.1.6、VFS 檔案系統的示意圖</div>

### 7.1.9 XFS 檔案系統簡介
#### EXT 家族當前較傷腦筋的地方：支援度最廣，但格式化超慢！
Ext 檔案系統家族對於檔案格式化的處理方面，採用的是預先規劃出所有的 inode/block/meta data 等資料，未來系統可以直接取用， 不需要再進行動態配置的作法。這個作法在早期磁碟容量還不大的時候還算 OK 沒啥問題，但時至今日，磁碟容量越來越大，連傳統的 MBR 都已經被 GPT 所取代，連我們這些老人家以前聽到的超大 TB 容量也已經不夠看了！現在都已經說到 PB 或 EB 以上容量了呢！那妳可以想像得到，當你的 TB 以上等級的傳統 ext 家族檔案系統在格式化的時候，光是系統要預先分配 inode 與 block 就消耗你好多好多的人類時間了

xfs 檔案系統在資料的分佈上，主要規劃為三個部份，一個資料區 (data section)、一個檔案系統活動登錄區 (log section)以及一個即時運作區 (realtime section)。 這三個區域的資料內容如下：

- 資料區 (data section)

基本上，資料區就跟我們之前談到的 ext 家族一樣，包括 inode/data block/superblock 等資料，都放置在這個區塊。 這個資料區與 ext 家族的 block group 類似，也是分為多個儲存區群組 (allocation groups) 來分別放置檔案系統所需要的資料。 每個儲存區群組都包含了 (1)整個檔案系統的 superblock、 (2)剩餘空間的管理機制、 (3)inode的分配與追蹤。此外，inode與 block 都是系統需要用到時， 這才動態配置產生，所以格式化動作超級快！

- 檔案系統活動登錄區 (log section)

在登錄區這個區域主要被用來紀錄檔案系統的變化，其實有點像是日誌區啦！檔案的變化會在這裡紀錄下來，直到該變化完整的寫入到資料區後， 該筆紀錄才會被終結。如果檔案系統因為某些緣故 (例如最常見的停電) 而損毀時，系統會拿這個登錄區塊來進行檢驗，看看系統掛掉之前， 檔案系統正在運作些啥動作，藉以快速的修復檔案系統。
- 即時運作區 (realtime section)

當有檔案要被建立時，xfs 會在這個區段裡面找一個到數個的 extent 區塊，將檔案放置在這個區塊內，等到分配完畢後，再寫入到 data section 的 inode 與 block 去！ 這個 extent 區塊的大小得要在格式化的時候就先指定，最小值是 4K 最大可到 1G。一般非磁碟陣列的磁碟預設為 64K 容量，而具有類似磁碟陣列的 stripe 情況下，則建議 extent 設定為與 stripe 一樣大較佳。這個 extent 最好不要亂動，因為可能會影響到實體磁碟的效能喔。

## 7.2 檔案系統的簡單操作
### 7.2.1 磁碟與目錄的容量

現在我們知道磁碟的整體資料是在 superblock 區塊中，但是每個各別檔案的容量則在 inode 當中記載的。 那在文字介面底下該如何叫出這幾個資料呢？底下就讓我們來談一談這兩個指令：

- df：列出檔案系統的整體磁碟使用量；
- du：評估檔案系統的磁碟使用量(常用在推估目錄所佔容量)

#### df
**使用方式**
```
[root@study ~]# df [-ahikHTm] [目錄或檔名]
選項與參數：
-a  ：列出所有的檔案系統，包括系統特有的 /proc 等檔案系統；
-k  ：以 KBytes 的容量顯示各檔案系統；
-m  ：以 MBytes 的容量顯示各檔案系統；
-h  ：以人們較易閱讀的 GBytes, MBytes, KBytes 等格式自行顯示；
-H  ：以 M=1000K 取代 M=1024K 的進位方式；
-T  ：連同該 partition 的 filesystem 名稱 (例如 xfs) 也列出；
-i  ：不用磁碟容量，而以 inode 的數量來顯示
```
**example**
```
kevin@ubuntu:~$ df
Filesystem     1K-blocks     Used Available Use% Mounted on
udev             2743268        0   2743268   0% /dev
tmpfs             553688     2208    551480   1% /run
/dev/sda1       51420796 30888204  18104648  64% /
tmpfs            2768432        0   2768432   0% /dev/shm
tmpfs               5120        4      5116   1% /run/lock
tmpfs            2768432        0   2768432   0% /sys/fs/cgroup
/dev/loop0        354688   354688         0 100% /snap/gnome-3-38-2004/115
/dev/loop1          2688     2688         0 100% /snap/gnome-calculator/920
/dev/loop2         56960    56960         0 100% /snap/core18/2566
/dev/loop3         66816    66816         0 100% /snap/gtk-common-themes/1519
/dev/loop4         93952    93952         0 100% /snap/gtk-common-themes/1535
/dev/loop5        224256   224256         0 100% /snap/gnome-3-34-1804/77
/dev/loop6         64768    64768         0 100% /snap/core20/1623
/dev/loop7        117760   117760         0 100% /snap/core/13886
/dev/loop8        354688   354688         0 100% /snap/gnome-3-38-2004/119
/dev/loop9        168832   168832         0 100% /snap/gnome-3-28-1804/161
/dev/loop10       261120   261120         0 100% /snap/clash/1476
/dev/loop11         1536     1536         0 100% /snap/gnome-system-monitor/181
/dev/loop12       116736   116736         0 100% /snap/core/13425
/dev/loop14        72192    72192         0 100% /snap/core22/275
/dev/loop13       164096   164096         0 100% /snap/gnome-3-28-1804/116
/dev/loop15         2688     2688         0 100% /snap/gnome-system-monitor/178
/dev/loop16          768      768         0 100% /snap/gnome-logs/115
/dev/loop18         4352     4352         0 100% /snap/tree/18
/dev/loop17        74624    74624         0 100% /snap/core22/310
/dev/loop19          640      640         0 100% /snap/gnome-logs/112
/dev/loop20          768      768         0 100% /snap/gnome-characters/741
/dev/loop21         4352     4352         0 100% /snap/gnome-calculator/544
/dev/loop22        56960    56960         0 100% /snap/core18/2409
/dev/loop23          128      128         0 100% /snap/bare/5
/dev/loop24        63488    63488         0 100% /snap/core20/1518
/dev/loop25          512      512         0 100% /snap/gnome-characters/781
/dev/loop26       424320   424320         0 100% /snap/gnome-42-2204/29
tmpfs             553684       16    553668   1% /run/user/121
tmpfs             553684       32    553652   1% /run/user/1000
```

先來說明一下範例一所輸出的結果訊息為：

- Filesystem：代表該檔案系統是在哪個 partition ，所以列出裝置名稱；
- 1k-blocks：說明底下的數字單位是 1KB 呦！可利用 -h 或 -m 來改變容量；
- Used：顧名思義，就是使用掉的磁碟空間啦！
- Available：也就是剩下的磁碟空間大小；
- Use%：就是磁碟的使用率啦！如果使用率高達 90% 以上時， 最好需要注意一下了，免得容量不足造成系統問題喔！(例如最容易被灌爆的 /var/spool/mail 這個放置郵件的磁碟)
- Mounted on：就是磁碟掛載的目錄所在啦！(掛載點啦！)

**example 2**
```
kevin@ubuntu:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            2.7G     0  2.7G   0% /dev
tmpfs           541M  2.2M  539M   1% /run
/dev/sda1        50G   30G   18G  64% /
tmpfs           2.7G     0  2.7G   0% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           2.7G     0  2.7G   0% /sys/fs/cgroup
/dev/loop0      347M  347M     0 100% /snap/gnome-3-38-2004/115
/dev/loop1      2.7M  2.7M     0 100% /snap/gnome-calculator/920
/dev/loop2       56M   56M     0 100% /snap/core18/2566
/dev/loop3       66M   66M     0 100% /snap/gtk-common-themes/1519
/dev/loop4       92M   92M     0 100% /snap/gtk-common-themes/1535
/dev/loop5      219M  219M     0 100% /snap/gnome-3-34-1804/77
/dev/loop6       64M   64M     0 100% /snap/core20/1623
/dev/loop7      115M  115M     0 100% /snap/core/13886
/dev/loop8      347M  347M     0 100% /snap/gnome-3-38-2004/119
/dev/loop9      165M  165M     0 100% /snap/gnome-3-28-1804/161
/dev/loop10     255M  255M     0 100% /snap/clash/1476
/dev/loop11     1.5M  1.5M     0 100% /snap/gnome-system-monitor/181
/dev/loop12     114M  114M     0 100% /snap/core/13425
/dev/loop14      71M   71M     0 100% /snap/core22/275
/dev/loop13     161M  161M     0 100% /snap/gnome-3-28-1804/116
/dev/loop15     2.7M  2.7M     0 100% /snap/gnome-system-monitor/178
/dev/loop16     768K  768K     0 100% /snap/gnome-logs/115
/dev/loop18     4.3M  4.3M     0 100% /snap/tree/18
/dev/loop17      73M   73M     0 100% /snap/core22/310
/dev/loop19     640K  640K     0 100% /snap/gnome-logs/112
/dev/loop20     768K  768K     0 100% /snap/gnome-characters/741
/dev/loop21     4.3M  4.3M     0 100% /snap/gnome-calculator/544
/dev/loop22      56M   56M     0 100% /snap/core18/2409
/dev/loop23     128K  128K     0 100% /snap/bare/5
/dev/loop24      62M   62M     0 100% /snap/core20/1518
/dev/loop25     512K  512K     0 100% /snap/gnome-characters/781
/dev/loop26     415M  415M     0 100% /snap/gnome-42-2204/29
tmpfs           541M   16K  541M   1% /run/user/121
tmpfs           541M   32K  541M   1% /run/user/1000
```
**example 3**
```
### 展示/下面挂载的磁盘容量
kevin@ubuntu:~$ df -h /
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda1        50G   30G   18G  64% /
```

**example 4**
```
### 展示-i参数 inode数量
kevin@ubuntu:~$ df -ih /
Filesystem     Inodes IUsed IFree IUse% Mounted on
/dev/sda1        3.2M  678K  2.5M   22% /
```

df读取superblock中间的内容
**由於 df 主要讀取的資料幾乎都是針對一整個檔案系統，因此讀取的範圍主要是在 Superblock 內的資訊**， 所以這個指令顯示結果的速度非常的快速！在顯示的結果中你需要特別留意的是那個根目錄的剩餘容量！ 因為我們所有的資料都是由根目錄衍生出來的，因此當根目錄的剩餘容量剩下 0 時，那你的 Linux 可能就問題很大了。

/proc
另外需要注意的是，**如果使用 -a 這個參數時，系統會出現 /proc 這個掛載點，但是裡面的東西都是 0 ，不要緊張！ /proc 的東西都是 Linux 系統所需要載入的系統資料，而且是掛載在『記憶體當中』的， 所以當然沒有佔任何的磁碟空間囉！**

至於那個 /dev/shm/ 目錄，其實是利用記憶體虛擬出來的磁碟空間，通常是總實體記憶體的一半！ 由於是透過記憶體模擬出來的磁碟，因此你在這個目錄底下建立任何資料檔案時，存取速度是非常快速的！(在記憶體內工作) 不過，也由於他是記憶體模擬出來的，因此這個檔案系統的大小在每部主機上都不一樣，而且建立的東西在下次開機時就消失了！ 因為是在記憶體中嘛！

#### du
**usage**
```
[root@study ~]# du [-ahskm] 檔案或目錄名稱
選項與參數：
-a  ：列出所有的檔案與目錄容量，因為預設僅統計目錄底下的檔案量而已。
-h  ：以人們較易讀的容量格式 (G/M) 顯示；
-s  ：列出總量而已，而不列出每個各別的目錄佔用容量；
-S  ：不包括子目錄下的總計，與 -s 有點差別。
-k  ：以 KBytes 列出容量顯示；
-m  ：以 MBytes 列出容量顯示；

# 直接輸入 du 沒有加任何選項時，則 du 會分析『目前所在目錄』
# 的檔案與目錄所佔用的磁碟空間。但是，實際顯示時，僅會顯示目錄容量(不含檔案)，
# 因此 . 目錄有很多檔案沒有被列出來，所以全部的目錄相加不會等於 . 的容量喔！
# 此外，輸出的數值資料為 1K 大小的容量單位。
```
**example **
```
example 1
kevin@ubuntu:~/os/os_note$ du
4       ./install_centos
20      ./linux_command
584     ./linux_file/picture
744     ./linux_file
4       ./compress/picture
8       ./compress
616     ./linux_environment/picture
648     ./linux_environment
44      ./elementary_knowledge/picture
60      ./elementary_knowledge
1488    .
# 直接輸入 du 沒有加任何選項時，則 du 會分析『目前所在目錄』
# 的檔案與目錄所佔用的磁碟空間。但是，實際顯示時，僅會顯示目錄容量(不含檔案)，
# 因此 . 目錄有很多檔案沒有被列出來，所以全部的目錄相加不會等於 . 的容量喔！
# 此外，輸出的數值資料為 1K 大小的容量單位。

範例二：同範例一，但是將檔案的容量也列出來
kevin@ubuntu:~/os/os_note$ du -a
4       ./install_centos
16      ./linux_command/chapter4.md
20      ./linux_command
156     ./linux_file/chapter5.md
24      ./linux_file/picture/0210filepermission_1.jpg
88      ./linux_file/picture/屏幕截图 2022-10-21 103511.png
20      ./linux_file/picture/filesystem-1.jpg
8       ./linux_file/picture/centos7_dir_block.jpg
12      ./linux_file/picture/filesystem-2.jpg
16      ./linux_file/picture/ext2_filesystem.jpg
272     ./linux_file/picture/屏幕截图 2022-10-20 171917.png
8       ./linux_file/picture/0210filepermission_3.gif
16      ./linux_file/picture/centos7_vfs.gif
48      ./linux_file/picture/inode.jpg
40      ./linux_file/picture/屏幕截图 2022-10-20 170043.png
12      ./linux_file/picture/centos7_0210filepermission_2.gif
4       ./linux_file/picture/find_time.gif
12      ./linux_file/picture/屏幕截图 2022-10-20 155540.png
584     ./linux_file/picture
744     ./linux_file
4       ./compress/picture
8       ./compress
28      ./linux_environment/chapter2_Linux_environment.md
8       ./linux_environment/picture/dirtree.gif
320     ./linux_environment/picture/磁盘示意.png
84      ./linux_environment/picture/bios or uefi.png
120     ./linux_environment/picture/各类设备名称.png
20      ./linux_environment/picture/partition-2.png
36      ./linux_environment/picture/gpt_partition_1.jpg
12      ./linux_environment/picture/loader.gif
12      ./linux_environment/picture/mbr disk partition-1.png
616     ./linux_environment/picture
648     ./linux_environment
12      ./elementary_knowledge/linux_elementary_knowledge.md
40      ./elementary_knowledge/picture/Linux distribution classify.png
44      ./elementary_knowledge/picture
60      ./elementary_knowledge
1488    .

```

與 df 不一樣的是，du 這個指令其實會直接到檔案系統內去搜尋所有的檔案資料， 所以上述第三個範例指令的運作會執行一小段時間！此外，在預設的情況下，容量的輸出是以 KB 來設計的， 如果你想要知道目錄佔了多少 MB ，那麼就使用 -m 這個參數即可囉！而， 如果你只想要知道該目錄佔了多少容量的話，使用 -s 就可以啦！

至於 -S 這個選項部分，由於 du 預設會將所有檔案的大小均列出，因此假設你在 /etc 底下使用 du 時， 所有的檔案大小，包括 /etc 底下的次目錄容量也會被計算一次。然後最終的容量 (/etc) 也會加總一次， 因此很多朋友都會誤會 du 分析的結果不太對勁。所以囉，如果想要列出某目錄下的全部資料， 或許也可以加上 -S 的選項，減少次目錄的加總喔！

### 7.2.2 實體連結與符號連結： ln
關於連結(link)資料我們第五章的Linux檔案屬性及Linux檔案種類與副檔名當中提過一些資訊， 不過當時由於尚未講到檔案系統，因此無法較完整的介紹連結檔啦。不過在上一小節談完了檔案系統後， 我們可以來瞭解一下連結檔這玩意兒了。

在 Linux 底下的連結檔有兩種，一種是類似 Windows 的捷徑功能的檔案，可以讓你快速的連結到目標檔案(或目錄)； 另一種則是透過檔案系統的 inode 連結來產生新檔名，而不是產生新檔案！這種稱為實體連結 (hard link)。 這兩種玩意兒是完全不一樣的東西呢！現在就分別來談談。

#### Hard Link (實體連結, 硬式連結或實際連結)
在前一小節當中，我們知道幾件重要的資訊，包括：

- 每個檔案都會佔用一個 inode ，檔案內容由 inode 的記錄來指向；
- 想要讀取該檔案，必須要經過目錄記錄的檔名來指向到正確的 inode 號碼才能讀取。


也就是說，其實檔名只與目錄有關，但是檔案內容則與 inode 有關。那麼想一想， 有沒有可能有多個檔名對應到同一個 inode 號碼呢？有的！那就是 hard link 的由來。 所以簡單的說：hard link 只是在某個目錄下新增一筆檔名連結到某 inode 號碼的關連記錄而已。

舉個例子來說，假設我系統有個 /root/crontab 他是 /etc/crontab 的實體連結，也就是說這兩個檔名連結到同一個 inode ， 自然這兩個檔名的所有相關資訊都會一模一樣(除了檔名之外)。實際的情況可以如下所示：
```
kevin@ubuntu:~$ ll -i git_learn/
total 1020
1778411 drwxrwxr-x  6 kevin kevin    4096 Oct 19 10:53 ./
1714999 drwxr-xr-x 40 kevin kevin    4096 Oct 31 17:11 ../
1778619 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:58 bin/
1778412 drwxrwxr-x  8 kevin kevin    4096 Oct 12 15:13 .git/
1748149 -rwxrw-rw-  1 kevin kevin 1000924 Oct 12 15:07 git_learn_route_chart*
1778613 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:55 lib/
1748147 -rwxrw-r--  1 kevin kevin     163 Oct 12 15:10 readme.md*
1748139 -rwxrwxr-x  1 kevin kevin     143 Oct 12 14:57 sample.cpp*
1708703 -rwxrwxr-x  1 kevin kevin       0 Oct 11 16:19 sample.py*
1748128 -rwxrwxr-x  1 kevin kevin      90 Oct 12 14:35 sample.txt*
1778612 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:43 src/
1748325 -rw-rw-r--  1 kevin kevin      46 Oct 19 10:53 text.txt
kevin@ubuntu:~$ ln ./git_learn/sample.cpp ./test/test.cpp
kevin@ubuntu:~$ ls -li ./git_learn/
total 1008
1778619 drwxrwxr-x 2 kevin kevin    4096 Oct 12 14:58 bin
1748149 -rwxrw-rw- 1 kevin kevin 1000924 Oct 12 15:07 git_learn_route_chart
1778613 drwxrwxr-x 2 kevin kevin    4096 Oct 12 14:55 lib
1748147 -rwxrw-r-- 1 kevin kevin     163 Oct 12 15:10 readme.md
1748139 -rwxrwxr-x 2 kevin kevin     143 Oct 12 14:57 sample.cpp
1708703 -rwxrwxr-x 1 kevin kevin       0 Oct 11 16:19 sample.py
1748128 -rwxrwxr-x 1 kevin kevin      90 Oct 12 14:35 sample.txt
1778612 drwxrwxr-x 2 kevin kevin    4096 Oct 12 14:43 src
1748325 -rw-rw-r-- 1 kevin kevin      46 Oct 19 10:53 text.txt
kevin@ubuntu:~$ ls -li ./test/
total 4
1748139 -rwxrwxr-x 2 kevin kevin 143 Oct 12 14:57 test.cpp
```
你可以發現兩個檔名都連結到 1748139 這個 inode 號碼，所以您瞧瞧，是否檔案的權限/屬性完全一樣呢？ 因為這兩個『檔名』其實是一模一樣的『檔案』啦！而且你也會發現第二個欄位由原本的 1 變成 2 了！ 那個欄位稱為『連結』，這個欄位的意義為：『有多少個檔名連結到這個 inode 號碼』的意思。 如果將讀取到正確資料的方式畫成示意圖，就類似如下畫面：
<div align=center><img src="/os_note/linux_file/picture/hard_link1.gif"></div>
<div align=center>圖7.2.1、實體連結的檔案讀取示意圖</div>

上圖的意思是，你可以透過 1 或 2 的目錄之 inode 指定的 block 找到兩個不同的檔名，而不管使用哪個檔名均可以指到 real 那個 inode 去讀取到最終資料！那這樣有什麼好處呢？最大的好處就是『安全』！如同上圖中， 如果你將任何一個『檔名』刪除，其實 inode 與 block 都還是存在的！ 此時你可以透過另一個『檔名』來讀取到正確的檔案資料喔！此外，不論你使用哪個『檔名』來編輯， 最終的結果都會寫入到相同的 inode 與 block 中，因此均能進行資料的修改哩！

一般來說，使用 hard link 設定連結檔時，磁碟的空間與 inode 的數目都不會改變！ 我們還是由圖 7.2.1 來看，由圖中可以知道， hard link 只是在某個目錄下的 block 多寫入一個關連資料而已，既不會增加 inode 也不會耗用 block 數量哩！

由圖 7.2.1 其實我們也能夠知道，事實上 hard link 應該僅能在單一檔案系統中進行的，應該是不能夠跨檔案系統才對！ 因為圖 7.2.1 就是在同一個 filesystem 上嘛！所以 hard link 是有限制的：

- 不能跨 Filesystem；
- 不能 link 目錄。

不能跨 Filesystem 還好理解，那不能 hard link 到目錄又是怎麼回事呢？這是因為如果使用 hard link 連結到目錄時， 連結的新目錄得要多出一個 . 以及 .. ，那個 .. 就會導致父目錄也多出一個新的連結計算，如果多重處理時， 很可能會導致目錄搜尋時的錯誤循環問題，導致一個名為死結 (打了死結，一直在裡面轉不出來) 的困境！同時， 如果是在不同的目錄底下建立目錄的 hard link 時，將可能會導致『同一個目錄會有好幾個父目錄』的存在！ 因此， hard link 一個目錄不是做不到，而是建議不要做！避免產生檔案系統錯亂的困擾啊！舉例來說，底下為兩個互為 hard link 的目錄：

你在 aadir 看到的資料應該是要跟 bbdir 看到的一樣，但是 aadir 的 .. 會是 aapdir ，不過 bbdir 的 .. 卻變成 bbpdir， 明明是互為連結的 hard link 目錄，裡面的 .. 卻指向不同的地方～這就傷腦筋了！為了避免許多這方面的困擾，所以才建議不要使用 hard link 在目錄上的！

>Linux 文件系统中的目录均隐藏了两个个特殊的目录当前目录（.）和父目录（..），如果允许对目录进行硬链接，大家来看一下下面两种情况：
>情况A：存在一个/usr/local/myapp的目录， 我们将他hard link 链接到/root/目录ln /usr/local/myapp /root/myapp 那么请问，myapp目录里的(..)访问父目录，是指的/usr/local呢，还是/root/呢？
>情况B: 如果存在目录/root/test/a 和 目录/root/app/b 如果a是app目录的hard link, b是test 的hard link, 这时就形成了循环引用，假设可以这样设定，那么/root/test/a 既然是/root/app/目录，里面肯定有b, 这时可以访问 /root/test/a/b ，此时你发现b又是/root/test/的hard link 那么b里肯定有a，这时你课可以访问/root/test/a/b/a，以此循环/root/test/a/b/a/b/a/b/a/b/.... 难道你不觉得这样有问题吗？
>作者：时光猫投资
链接：https://www.zhihu.com/question/50223526/answer/864874726
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#### Symbolic Link (符號連結，亦即是捷徑)
相對於 hard link ， Symbolic link 可就好理解多了，基本上， Symbolic link 就是在建立一個獨立的檔案，而這個檔案會讓資料的讀取指向他 link 的那個檔案的檔名！由於只是利用檔案來做為指向的動作， 所以，當來源檔被刪除之後，symbolic link 的檔案會『開不了』， 會一直說『無法開啟某檔案！』。實際上就是找不到原始『檔名』而已啦！
```
kevin@ubuntu:~$ ln -s ./git_learn/sample.txt ./test/test.txt
kevin@ubuntu:~$ ll -i git_learn/ test/
git_learn/:
total 1020
1778411 drwxrwxr-x  6 kevin kevin    4096 Oct 19 10:53 ./
1714999 drwxr-xr-x 41 kevin kevin    4096 Oct 31 17:25 ../
1778619 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:58 bin/
1778412 drwxrwxr-x  8 kevin kevin    4096 Oct 12 15:13 .git/
1748149 -rwxrw-rw-  1 kevin kevin 1000924 Oct 12 15:07 git_learn_route_chart*
1778613 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:55 lib/
1748147 -rwxrw-r--  1 kevin kevin     163 Oct 12 15:10 readme.md*
1748139 -rwxrwxr-x  2 kevin kevin     143 Oct 12 14:57 sample.cpp*
1708703 -rwxrwxr-x  1 kevin kevin       0 Oct 11 16:19 sample.py*
1748128 -rwxrwxr-x  1 kevin kevin      90 Oct 12 14:35 sample.txt*
1778612 drwxrwxr-x  2 kevin kevin    4096 Oct 12 14:43 src/
1748325 -rw-rw-r--  1 kevin kevin      46 Oct 19 10:53 text.txt

test/:
total 12
2494365 drwxrwxr-x  2 kevin kevin 4096 Oct 31 19:38 ./
1714999 drwxr-xr-x 41 kevin kevin 4096 Oct 31 17:25 ../
1748139 -rwxrwxr-x  2 kevin kevin  143 Oct 12 14:57 test.cpp*
2492506 lrwxrwxrwx  1 kevin kevin   22 Oct 31 19:38 test.txt -> ./git_learn/sample.txt
```

由上表的結果我們可以知道兩個檔案指向不同的 inode 號碼，當然就是兩個獨立的檔案存在！ 而且連結檔的重要內容就是他會寫上目標檔案的『檔名』， 你可以發現為什麼上表中連結檔的大小為 12 bytes 呢？ 因為箭頭(-->)右邊的檔名『/etc/crontab』總共有 12 個英文，每個英文佔用 1 個 bytes ，所以檔案大小就是 12bytes了！

關於上述的說明，我們以如下圖示來解釋：

<div align=center><img src="/os_note/linux_file/picture/symbolic_link1.gif"></div>
<div align=center>圖7.2.2、符號連結的檔案讀取示意圖</div>

由 1 號 inode 讀取到連結檔的內容僅有檔名，根據檔名連結到正確的目錄去取得目標檔案的 inode ， 最終就能夠讀取到正確的資料了。你可以發現的是，如果目標檔案(/etc/crontab)被刪除了，那麼整個環節就會無法繼續進行下去， 所以就會發生無法透過連結檔讀取的問題了！

這裡還是得特別留意，這個 Symbolic Link 與 Windows 的捷徑可以給他劃上等號，由 Symbolic link 所建立的檔案為一個獨立的新的檔案，所以會佔用掉 inode 與 block 喔！

由上面的說明來看，似乎 hard link 比較安全，因為即使某一個目錄下的關連資料被殺掉了， 也沒有關係，只要有任何一個目錄下存在著關連資料，那麼該檔案就不會不見！舉上面的例子來說，我的 /etc/crontab 與 /root/crontab 指向同一個檔案，如果我刪除了 /etc/crontab 這個檔案，該刪除的動作其實只是將 /etc 目錄下關於 crontab 的關連資料拿掉而已， crontab 所在的 inode 與 block 其實都沒有被變動喔！

不過由於 Hard Link 的限制太多了，包括無法做『目錄』的 link ， 所以在用途上面是比較受限的！反而是 Symbolic Link 的使用方面較廣喔！好了， 說的天花亂墜，看你也差不多快要昏倒了！沒關係，實作一下就知道怎麼回事了！要製作連結檔就必須要使用 ln 這個指令呢！

```
[root@study ~]# ln [-sf] 來源檔 目標檔
選項與參數：
-s  ：如果不加任何參數就進行連結，那就是hard link，至於 -s 就是symbolic link
-f  ：如果 目標檔 存在時，就主動的將目標檔直接移除後再建立！
```

要注意囉！使用 ln 如果不加任何參數的話，那麼就是 Hard Link 囉！如同範例二的情況，增加了 hard link 之後，可以發現使用 ls -l 時，顯示的 link 那一欄屬性增加了！而如果這個時候砍掉 passwd 會發生什麼事情呢？passwd-hd 的內容還是會跟原來 passwd 相同，但是 passwd-so 就會找不到該檔案啦！

而如果 ln 使用 -s 的參數時，就做成差不多是 Windows 底下的『捷徑』的意思。當你修改 Linux 下的 symbolic link 檔案時，則更動的其實是『原始檔』， 所以不論你的這個原始檔被連結到哪裡去，只要你修改了連結檔，原始檔就跟著變囉！ 以上面為例，由於你使用 -s 的參數建立一個名為 passwd-so 的檔案，則你修改 passwd-so 時，其內容與 passwd 完全相同，並且，當你按下儲存之後，被改變的將是 passwd 這個檔案！

那麼如果你進入 /root/bin 這個目錄下，『請注意呦！**該目錄其實是 /bin 這個目錄，因為你做了連結檔了**！』所以，如果你進入 /root/bin 這個剛剛建立的連結目錄， 並且將其中的資料殺掉時，嗯！ /bin 裡面的資料就通通不見了！這點請千萬注意！所以趕緊利用『rm /root/bin 』 將這個連結檔刪除吧！

#### 關於目錄的 link 數量：
或許您已經發現了，那就是，當我們以 hard link 進行『檔案的連結』時，可以發現，在 ls -l 所顯示的第二欄位會增加一才對，那麼請教，如果建立目錄時，**他預設的 link 數量會是多少？** 讓我們來想一想，一個『空目錄』裡面至少會存在些什麼？呵呵！就是存在 . 與 .. 這兩個目錄啊！ 那麼，當我們建立一個新目錄名稱為 /tmp/testing 時，基本上會有三個東西，那就是：

- /tmp/testing
- /tmp/testing/.
- /tmp/testing/..

而其中 /tmp/testing 與 /tmp/testing/. 其實是一樣的！都代表該目錄啊～而 /tmp/testing/.. 則代表 /tmp 這個目錄，所以說，當我們建立一個新的目錄時， 『新的目錄的 link 數為 2 ，而上層目錄的 link 數則會增加 1 』 

## 7.3 磁碟的分割、格式化、檢驗與掛載
對於一個系統管理者( root )而言，磁碟的的管理是相當重要的一環，尤其近來磁碟已經漸漸的被當成是消耗品了 ..... 如果我們想要在系統裡面新增一顆磁碟時，應該有哪些動作需要做的呢：

- 對磁碟進行分割，以建立可用的 partition ；
- 對該 partition 進行格式化 (format)，以建立系統可用的 filesystem；
- 若想要仔細一點，則可對剛剛建立好的 filesystem 進行檢驗；
- 在 Linux 系統上，需要建立掛載點 (亦即是目錄)，並將他掛載上來；

### 7.3.1 觀察磁碟分割狀態
由於目前磁碟分割主要有 MBR 以及 GPT 兩種格式，這兩種格式所使用的分割工具不太一樣！你當然可以使用本章預計最後才介紹的 parted 這個通通有支援的工具來處理，不過，我們還是比較習慣使用 fdisk 或者是 gdisk 來處理分割啊！因此，我們自然就得要去找一下目前系統有的磁碟有哪些？ 這些磁碟是 MBR 還是 GPT 等等的！這樣才能處理啦！

#### lsblk 列出系統上的所有磁碟列表
lsblk 可以看成『 list block device 』的縮寫，就是列出所有儲存裝置的意思！這個工具軟體真的很好用喔！來瞧一瞧！
```
[root@study ~]# lsblk [-dfimpt] [device]
選項與參數：
-d  ：僅列出磁碟本身，並不會列出該磁碟的分割資料
-f  ：同時列出該磁碟內的檔案系統名稱
-i  ：使用 ASCII 的線段輸出，不要使用複雜的編碼 (再某些環境下很有用)
-m  ：同時輸出該裝置在 /dev 底下的權限資料 (rwx 的資料)
-p  ：列出該裝置的完整檔名！而不是僅列出最後的名字而已。
-t  ：列出該磁碟裝置的詳細資料，包括磁碟佇列機制、預讀寫的資料量大小等

範例一：列出本系統下的所有磁碟與磁碟內的分割資訊
kevin@ubuntu:~/os$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
loop0    7:0    0 414.4M  1 loop /snap/gnome-42-2204/29
loop1    7:1    0   4.2M  1 loop /snap/gnome-calculator/544
loop2    7:2    0   1.5M  1 loop /snap/gnome-system-monitor/181
loop3    7:3    0  65.2M  1 loop /snap/gtk-common-themes/1519
loop4    7:4    0   219M  1 loop /snap/gnome-3-34-1804/77
loop5    7:5    0 254.9M  1 loop /snap/clash/1476
loop6    7:6    0   114M  1 loop /snap/core/13425
loop7    7:7    0   556K  1 loop /snap/gnome-logs/112
loop8    7:8    0   115M  1 loop /snap/core/13886
loop9    7:9    0 346.3M  1 loop /snap/gnome-3-38-2004/119
loop10   7:10   0   476K  1 loop /snap/gnome-characters/781
loop11   7:11   0  63.2M  1 loop /snap/core20/1623
loop12   7:12   0   696K  1 loop /snap/gnome-logs/115
loop13   7:13   0  91.7M  1 loop /snap/gtk-common-themes/1535
loop14   7:14   0  61.9M  1 loop /snap/core20/1518
loop15   7:15   0 346.3M  1 loop /snap/gnome-3-38-2004/115
loop16   7:16   0   4.2M  1 loop /snap/tree/18
loop17   7:17   0     4K  1 loop /snap/bare/5
loop18   7:18   0  55.6M  1 loop /snap/core18/2566
loop19   7:19   0  72.8M  1 loop /snap/core22/310
loop20   7:20   0   2.6M  1 loop /snap/gnome-system-monitor/178
loop21   7:21   0 160.2M  1 loop /snap/gnome-3-28-1804/116
loop22   7:22   0   2.6M  1 loop /snap/gnome-calculator/920
loop23   7:23   0  70.4M  1 loop /snap/core22/275
loop24   7:24   0 164.8M  1 loop /snap/gnome-3-28-1804/161
loop25   7:25   0   704K  1 loop /snap/gnome-characters/741
loop26   7:26   0  55.5M  1 loop /snap/core18/2409
sda      8:0    0    50G  0 disk 
└─sda1   8:1    0    50G  0 part /
sr0     11:0    1  1024M  0 rom
```
從範例一我們來談談預設輸出的資訊有哪些。
- NAME：就是裝置的檔名囉！會省略 /dev 等前導目錄！
- MAJ:MIN：其實核心認識的裝置都是透過這兩個代碼來熟悉的！分別是主要：次要裝置代碼！
- RM：是否為可卸載裝置 (removable device)，如光碟、USB 磁碟等等
- SIZE：當然就是容量囉！
- RO：是否為唯讀裝置的意思
- TYPE：是磁碟 (disk)、分割槽 (partition) 還是唯讀記憶體 (rom) 等輸出
- MOUTPOINT：就是前一章談到的掛載點！

```
範例二：僅列出 /dev/sda 裝置內的所有資料的完整檔名
kevin@ubuntu:~/os$ lsblk -ip /dev/sda
NAME        MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
/dev/sda      8:0    0  50G  0 disk 
`-/dev/sda1   8:1    0  50G  0 part /
```

#### blkid 列出裝置的 UUID 等參數
雖然 lsblk 已經可以使用 -f 來列出檔案系統與裝置的 UUID 資料，不過，鳥哥還是比較習慣直接使用 blkid 來找出裝置的 UUID 喔！ 什麼是 UUID 呢？UUID 是全域單一識別碼 (universally unique identifier)，Linux 會將系統內所有的裝置都給予一個獨一無二的識別碼， 這個識別碼就可以拿來作為掛載或者是使用這個裝置/檔案系統之用了。
```
root@ubuntu:/home/kevin/os# blkid
/dev/loop0: TYPE="squashfs"
/dev/loop1: TYPE="squashfs"
/dev/loop2: TYPE="squashfs"
/dev/loop3: TYPE="squashfs"
/dev/loop4: TYPE="squashfs"
/dev/loop5: TYPE="squashfs"
/dev/loop6: TYPE="squashfs"
/dev/loop7: TYPE="squashfs"
/dev/sda1: UUID="b16bcca1-6f61-4f98-883d-08da92739870" TYPE="ext4" PARTUUID="7c65c297-01"
/dev/loop8: TYPE="squashfs"
/dev/loop9: TYPE="squashfs"
/dev/loop10: TYPE="squashfs"
/dev/loop11: TYPE="squashfs"
/dev/loop12: TYPE="squashfs"
/dev/loop13: TYPE="squashfs"
/dev/loop14: TYPE="squashfs"
/dev/loop15: TYPE="squashfs"
/dev/loop16: TYPE="squashfs"
/dev/loop17: TYPE="squashfs"
/dev/loop18: TYPE="squashfs"
/dev/loop19: TYPE="squashfs"
/dev/loop20: TYPE="squashfs"
/dev/loop21: TYPE="squashfs"
/dev/loop22: TYPE="squashfs"
/dev/loop23: TYPE="squashfs"
/dev/loop24: TYPE="squashfs"
/dev/loop25: TYPE="squashfs"
/dev/loop26: TYPE="squashfs"
```
如上所示，每一行代表一個檔案系統，主要列出裝置名稱、UUID 名稱以及檔案系統的類型 (TYPE)！這對於管理員來說，相當有幫助！ 對於系統上面的檔案系統觀察來說，真是一目了然！

#### parted 列出磁碟的分割表類型與分割資訊
雖然我們已經知道了系統上面的所有裝置，並且透過 blkid 也知道了所有的檔案系統！不過，還是不清楚磁碟的分割類型。 這時我們可以透過簡單的 parted 來輸出喔！我們這裡僅簡單的利用他的輸出而已～本章最後才會詳細介紹這個指令的用法的！
```
[root@study ~]# parted device_name print

範例一：列出 /dev/sda 磁碟的相關資料
kevin@ubuntu:~/os$ sudo parted /dev/sda print 
[sudo] password for kevin: 
Model: VMware, VMware Virtual S (scsi)
Disk /dev/sda: 53.7GB
Sector size (logical/physical): 512B/512B
Partition Table: msdos
Disk Flags: 

Number  Start   End     Size    Type     File system  Flags
 1      1049kB  53.7GB  53.7GB  primary  ext4         boot
```
分割模式：msdos-MBR

### 7.3.2 磁碟分割： gdisk/fdisk
接下來我們想要進行磁碟分割囉！要注意的是：**『MBR 分割表請使用 fdisk 分割， GPT 分割表請使用 gdisk 分割！』** 這個不要搞錯～否則會分割失敗的！另外，這兩個工具軟體的操作很類似，執行了該軟體後，可以透過該軟體內部的說明資料來操作， 因此不需要硬背！只要知道方法即可。剛剛從上面 parted 的輸出結果，我們也知道鳥哥這個測試機使用的是 GPT 分割， 因此底下通通得要使用 gdisk 來分割才行！

### 7.3.3 磁碟格式化(建置檔案系統)

#### EXT4 檔案系統 mkfs.ext4
如果想要格式化為 ext4 的傳統 Linux 檔案系統的話，可以使用 mkfs.ext4 這個指令即可！這個指令的參數快速的介紹一下！
```
[root@study ~]# mkfs.ext4 [-b size] [-L label] 裝置名稱
選項與參數：
-b  ：設定 block 的大小，有 1K, 2K, 4K 的容量，
-L  ：後面接這個裝置的標頭名稱。
```

### 7.3.4 檔案系統檢驗
由於系統在運作時誰也說不準啥時硬體或者是電源會有問題，所以『當機』可能是難免的情況(不管是硬體還是軟體)。 現在我們知道檔案系統運作時會有磁碟與記憶體資料非同步的狀況發生，因此莫名其妙的當機非常可能導致檔案系統的錯亂。 問題來啦，如果檔案系統真的發生錯亂的話，那該如何是好？就...挽救啊！不同的檔案系統救援的指令不太一樣，我們主要針對 xfs 及 ext4 這兩個主流來說明而已喔！
#### fsck.ext4 處理 EXT4 檔案系統
fsck 是個綜合指令，如果是針對 ext4 的話，建議直接使用 fsck.ext4 來檢測比較妥當！那 fsck.ext4 的選項有底下幾個常見的項目：
```
[root@study ~]# fsck.ext4 [-pf] [-b superblock] 裝置名稱
選項與參數：
-p  ：當檔案系統在修復時，若有需要回覆 y 的動作時，自動回覆 y 來繼續進行修復動作。
-f  ：強制檢查！一般來說，如果 fsck 沒有發現任何 unclean 的旗標，不會主動進入
      細部檢查的，如果您想要強制 fsck 進入細部檢查，就得加上 -f 旗標囉！
-D  ：針對檔案系統下的目錄進行最佳化配置。
-b  ：後面接 superblock 的位置！一般來說這個選項用不到。但是如果你的 superblock 因故損毀時，
      透過這個參數即可利用檔案系統內備份的 superblock 來嘗試救援。一般來說，superblock 備份在：
      1K block 放在 8193, 2K block 放在 16384, 4K block 放在 32768

範例：找出剛剛建置的 /dev/vda5 的另一塊 superblock，並據以檢測系統
[root@study ~]# dumpe2fs -h /dev/vda5 | grep 'Blocks per group'
Blocks per group:         32768
# 看起來每個 block 群組會有 32768 個 block，因此第二個 superblock 應該就在 32768 上！
# 因為 block 號碼為 0 號開始編的！

[root@study ~]# fsck.ext4 -b 32768 /dev/vda5
e2fsck 1.42.9 (28-Dec-2013)
/dev/vda5 was not cleanly unmounted, check forced.
Pass 1: Checking inodes, blocks, and sizes
Deleted inode 1577 has zero dtime.  Fix<y>? yes
Pass 2: Checking directory structure
Pass 3: Checking directory connectivity
Pass 4: Checking reference counts
Pass 5: Checking group summary information

/dev/vda5: ***** FILE SYSTEM WAS MODIFIED *****  # 檔案系統被改過，所以這裡會有警告！
/dev/vda5: 11/65536 files (0.0% non-contiguous), 12955/262144 blocks
# 好巧合！鳥哥使用這個方式來檢驗系統，恰好遇到檔案系統出問題！於是可以有比較多的解釋方向！
# 當檔案系統出問題，它就會要你選擇是否修復～如果修復如上所示，按下 y 即可！
# 最終系統會告訴你，檔案系統已經被更改過，要注意該項目的意思！

範例：已預設設定強制檢查一次 /dev/vda5
[root@study ~]# fsck.ext4 /dev/vda5
e2fsck 1.42.9 (28-Dec-2013)
/dev/vda5: clean, 11/65536 files, 12955/262144 blocks
# 檔案系統狀態正常，它並不會進入強制檢查！會告訴你檔案系統沒問題 (clean)

[root@study ~]# fsck.ext4 -f /dev/vda5
e2fsck 1.42.9 (28-Dec-2013)
Pass 1: Checking inodes, blocks, and sizes
....(底下省略)....
```
無論是 xfs_repair 或 fsck.ext4，這都是用來檢查與修正檔案系統錯誤的指令。注意：通常只有身為 root 且你的檔案系統有問題的時候才使用這個指令，否則在正常狀況下使用此一指令， 可能會造成對系統的危害！通常使用這個指令的場合都是在系統出現極大的問題，導致你在 Linux 開機的時候得進入單人單機模式下進行維護的行為時，才必須使用此一指令！

所以『執行 xfs_repair/fsck.ext4 時， 被檢查的 partition 務必不可掛載到系統上！亦即是需要在卸載的狀態喔！』

### 7.3.5 檔案系統掛載與卸載

我們在本章一開始時的掛載點的意義當中提過掛載點是目錄， 而這個目錄是進入磁碟分割槽(其實是檔案系統啦！)的入口就是了。不過要進行掛載前，你最好先確定幾件事：
- 單一檔案系統不應該被重複掛載在不同的掛載點(目錄)中；
- 單一目錄不應該重複掛載多個檔案系統；
- 要作為掛載點的目錄，理論上應該都是空目錄才是。

尤其是上述的後兩點！**如果你要用來掛載的目錄裡面並不是空的，那麼掛載了檔案系統之後，原目錄下的東西就會暫時的消失**。 舉個例子來說，假設你的 /home 原本與根目錄 (/) 在同一個檔案系統中，底下原本就有 /home/test 與 /home/vbird 兩個目錄。然後你想要加入新的磁碟，並且直接掛載 /home 底下，那麼當你掛載上新的分割槽時，則 /home 目錄顯示的是新分割槽內的資料，至於原先的 test 與 vbird 這兩個目錄就會暫時的被隱藏掉了！**注意喔！並不是被覆蓋掉， 而是暫時的隱藏了起來，等到新分割槽被卸載之後，則 /home 原本的內容就會再次的跑出來啦**！而要將檔案系統掛載到我們的 Linux 系統上，就要使用 mount 這個指令啦！ 不過，這個指令真的是博大精深～粉難啦！我們學簡單一點啊～ ^_^

```
[root@study ~]# mount -a
[root@study ~]# mount [-l]
[root@study ~]# mount [-t 檔案系統] LABEL=''  掛載點
[root@study ~]# mount [-t 檔案系統] UUID=''   掛載點  # 鳥哥近期建議用這種方式喔！
[root@study ~]# mount [-t 檔案系統] 裝置檔名  掛載點
選項與參數：
-a  ：依照設定檔 /etc/fstab 的資料將所有未掛載的磁碟都掛載上來
-l  ：單純的輸入 mount 會顯示目前掛載的資訊。加上 -l 可增列 Label 名稱！
-t  ：可以加上檔案系統種類來指定欲掛載的類型。常見的 Linux 支援類型有：xfs, ext3, ext4,
      reiserfs, vfat, iso9660(光碟格式), nfs, cifs, smbfs (後三種為網路檔案系統類型)
-n  ：在預設的情況下，系統會將實際掛載的情況即時寫入 /etc/mtab 中，以利其他程式的運作。
      但在某些情況下(例如單人維護模式)為了避免問題會刻意不寫入。此時就得要使用 -n 選項。
-o  ：後面可以接一些掛載時額外加上的參數！比方說帳號、密碼、讀寫權限等：
      async, sync:   此檔案系統是否使用同步寫入 (sync) 或非同步 (async) 的
                     記憶體機制，請參考檔案系統運作方式。預設為 async。
      atime,noatime: 是否修訂檔案的讀取時間(atime)。為了效能，某些時刻可使用 noatime
      ro, rw:        掛載檔案系統成為唯讀(ro) 或可讀寫(rw)
      auto, noauto:  允許此 filesystem 被以 mount -a 自動掛載(auto)
      dev, nodev:    是否允許此 filesystem 上，可建立裝置檔案？ dev 為可允許
      suid, nosuid:  是否允許此 filesystem 含有 suid/sgid 的檔案格式？
      exec, noexec:  是否允許此 filesystem 上擁有可執行 binary 檔案？
      user, nouser:  是否允許此 filesystem 讓任何使用者執行 mount ？一般來說，
                     mount 僅有 root 可以進行，但下達 user 參數，則可讓
                     一般 user 也能夠對此 partition 進行 mount 。
      defaults:      預設值為：rw, suid, dev, exec, auto, nouser, and async
      remount:       重新掛載，這在系統出錯，或重新更新參數時，很有用！
```
由於檔案系統幾乎都有 superblock ，我們的 Linux 可以透過分析 superblock 搭配 Linux 自己的驅動程式去測試掛載， 如果成功的套和了，就立刻自動的使用該類型的檔案系統掛載起來啊！那麼系統有沒有指定哪些類型的 filesystem 才需要進行上述的掛載測試呢？ 主要是參考底下這兩個檔案：
- /etc/filesystems：系統指定的測試掛載檔案系統類型的優先順序；
- /proc/filesystems：Linux系統已經載入的檔案系統類型。

那我怎麼知道我的 Linux 有沒有相關檔案系統類型的驅動程式呢？我們 Linux 支援的檔案系統之驅動程式都寫在如下的目錄中：
- /lib/modules/$(uname -r)/kernel/fs/

另外，過去我們都習慣使用裝置檔名然後直接用該檔名掛載， 不過近期以來鳥哥比較建議使用 UUID 來識別檔案系統，會比裝置名稱與標頭名稱還要更可靠！因為是獨一無二的啊！

#### 挂载usb设备（fat32）
```
kevin@ubuntu:~$ mkdir -p /media/kevin/test
mkdir: cannot create directory ‘/media/kevin/test’: Permission denied
kevin@ubuntu:~$ sudo mkdir -p /media/kevin/test
kevin@ubuntu:~$ ls /media/kevin/
test
kevin@ubuntu:~$ mount /dev/sdb1 /media/kevin/test
mount: only root can do that
kevin@ubuntu:~$ sudo mount /dev/sdb1 /media/kevin/test
kevin@ubuntu:~$ cd /media/kevin/test/
kevin@ubuntu:/media/kevin/test$ ls
'System Volume Information'
kevin@ubuntu:/media/kevin/test$ mkdir -p /test/test1
mkdir: cannot create directory ‘/test’: Permission denied
kevin@ubuntu:/media/kevin/test$ ls
'System Volume Information'
kevin@ubuntu:/media/kevin/test$ df /media/kevin/
Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda1       51420796 31077356  17915496  64% /
kevin@ubuntu:/media/kevin/test$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
loop0    7:0    0 414.4M  1 loop /snap/gnome-42-2204/29
loop1    7:1    0   4.2M  1 loop /snap/gnome-calculator/544
loop2    7:2    0   1.5M  1 loop /snap/gnome-system-monitor/181
loop3    7:3    0  65.2M  1 loop /snap/gtk-common-themes/1519
loop4    7:4    0   219M  1 loop /snap/gnome-3-34-1804/77
loop5    7:5    0 254.9M  1 loop /snap/clash/1476
loop6    7:6    0   114M  1 loop /snap/core/13425
loop7    7:7    0   556K  1 loop /snap/gnome-logs/112
loop8    7:8    0   115M  1 loop /snap/core/13886
loop9    7:9    0 346.3M  1 loop /snap/gnome-3-38-2004/119
loop10   7:10   0   476K  1 loop /snap/gnome-characters/781
loop11   7:11   0  63.2M  1 loop /snap/core20/1623
loop12   7:12   0   696K  1 loop /snap/gnome-logs/115
loop13   7:13   0  91.7M  1 loop /snap/gtk-common-themes/1535
loop14   7:14   0  61.9M  1 loop /snap/core20/1518
loop15   7:15   0 346.3M  1 loop /snap/gnome-3-38-2004/115
loop16   7:16   0   4.2M  1 loop /snap/tree/18
loop17   7:17   0     4K  1 loop /snap/bare/5
loop18   7:18   0  55.6M  1 loop /snap/core18/2566
loop19   7:19   0  72.8M  1 loop /snap/core22/310
loop20   7:20   0   2.6M  1 loop /snap/gnome-system-monitor/178
loop21   7:21   0 160.2M  1 loop /snap/gnome-3-28-1804/116
loop22   7:22   0   2.6M  1 loop /snap/gnome-calculator/920
loop23   7:23   0  70.4M  1 loop /snap/core22/275
loop24   7:24   0 164.8M  1 loop /snap/gnome-3-28-1804/161
loop25   7:25   0   704K  1 loop /snap/gnome-characters/741
loop26   7:26   0  55.5M  1 loop /snap/core18/2409
sda      8:0    0    50G  0 disk 
└─sda1   8:1    0    50G  0 part /
sdb      8:16   1  28.9G  0 disk 
└─sdb1   8:17   1  28.9G  0 part /media/kevin/test
sr0     11:0    1  1024M  0 rom  
kevin@ubuntu:/media/kevin/test$ df /media/kevin/test/
Filesystem     1K-blocks  Used Available Use% Mounted on
/dev/sdb1       30253024    64  30252960   1% /media/kevin/test
kevin@ubuntu:/media/kevin/test$ ls
'System Volume Information'
kevin@ubuntu:/media/kevin/test$ sudo nano test.txt
kevin@ubuntu:/media/kevin/test$ cat test.txt 
hello world
kevin@ubuntu:/media/kevin/test$ umount /dev/sdb1
umount: /media/kevin/test: umount failed: Operation not permitted.
kevin@ubuntu:/media/kevin/test$ sudo umount /dev/sdb1
umount: /media/kevin/test: target is busy.
kevin@ubuntu:/media/kevin/test$ cd ~
kevin@ubuntu:~$ sudo umount /dev/sdb1
```

#### umount (將裝置檔案卸載)
```
[root@study ~]# umount [-fn] 裝置檔名或掛載點
選項與參數：
-f  ：強制卸載！可用在類似網路檔案系統 (NFS) 無法讀取到的情況下；
-l  ：立刻卸載檔案系統，比 -f 還強！
-n  ：不更新 /etc/mtab 情況下卸載。

範例：
kevin@ubuntu:/$ mount 
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,relatime)
proc on /proc type proc (rw,nosuid,nodev,noexec,relatime)
udev on /dev type devtmpfs (rw,nosuid,relatime,size=2743272k,nr_inodes=685818,mode=755)
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000)
tmpfs on /run type tmpfs (rw,nosuid,noexec,relatime,size=553688k,mode=755)
/dev/sda1 on / type ext4 (rw,relatime,errors=remount-ro)
securityfs on /sys/kernel/security type securityfs (rw,nosuid,nodev,noexec,relatime)
tmpfs on /dev/shm type tmpfs (rw,nosuid,nodev)
tmpfs on /run/lock type tmpfs (rw,nosuid,nodev,noexec,relatime,size=5120k)
tmpfs on /sys/fs/cgroup type tmpfs (ro,nosuid,nodev,noexec,mode=755)
cgroup on /sys/fs/cgroup/unified type cgroup2 (rw,nosuid,nodev,noexec,relatime,nsdelegate)
cgroup on /sys/fs/cgroup/systemd type cgroup (rw,nosuid,nodev,noexec,relatime,xattr,name=systemd)
pstore on /sys/fs/pstore type pstore (rw,nosuid,nodev,noexec,relatime)
cgroup on /sys/fs/cgroup/freezer type cgroup (rw,nosuid,nodev,noexec,relatime,freezer)
cgroup on /sys/fs/cgroup/devices type cgroup (rw,nosuid,nodev,noexec,relatime,devices)
cgroup on /sys/fs/cgroup/perf_event type cgroup (rw,nosuid,nodev,noexec,relatime,perf_event)
cgroup on /sys/fs/cgroup/cpuset type cgroup (rw,nosuid,nodev,noexec,relatime,cpuset)
cgroup on /sys/fs/cgroup/rdma type cgroup (rw,nosuid,nodev,noexec,relatime,rdma)
cgroup on /sys/fs/cgroup/cpu,cpuacct type cgroup (rw,nosuid,nodev,noexec,relatime,cpu,cpuacct)
cgroup on /sys/fs/cgroup/memory type cgroup (rw,nosuid,nodev,noexec,relatime,memory)
cgroup on /sys/fs/cgroup/pids type cgroup (rw,nosuid,nodev,noexec,relatime,pids)
cgroup on /sys/fs/cgroup/hugetlb type cgroup (rw,nosuid,nodev,noexec,relatime,hugetlb)
cgroup on /sys/fs/cgroup/net_cls,net_prio type cgroup (rw,nosuid,nodev,noexec,relatime,net_cls,net_prio)
cgroup on /sys/fs/cgroup/blkio type cgroup (rw,nosuid,nodev,noexec,relatime,blkio)
systemd-1 on /proc/sys/fs/binfmt_misc type autofs (rw,relatime,fd=24,pgrp=1,timeout=0,minproto=5,maxproto=5,direct,pipe_ino=25151)
hugetlbfs on /dev/hugepages type hugetlbfs (rw,relatime,pagesize=2M)
debugfs on /sys/kernel/debug type debugfs (rw,relatime)
mqueue on /dev/mqueue type mqueue (rw,relatime)
/var/lib/snapd/snaps/gnome-42-2204_29.snap on /snap/gnome-42-2204/29 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-calculator_544.snap on /snap/gnome-calculator/544 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-system-monitor_181.snap on /snap/gnome-system-monitor/181 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gtk-common-themes_1519.snap on /snap/gtk-common-themes/1519 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-3-34-1804_77.snap on /snap/gnome-3-34-1804/77 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/clash_1476.snap on /snap/clash/1476 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core_13425.snap on /snap/core/13425 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-logs_112.snap on /snap/gnome-logs/112 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core_13886.snap on /snap/core/13886 type squashfs (ro,nodev,relatime,x-gdu.hide)
fusectl on /sys/fs/fuse/connections type fusectl (rw,relatime)
binfmt_misc on /proc/sys/fs/binfmt_misc type binfmt_misc (rw,relatime)
configfs on /sys/kernel/config type configfs (rw,relatime)
vmware-vmblock on /run/vmblock-fuse type fuse.vmware-vmblock (rw,relatime,user_id=0,group_id=0,default_permissions,allow_other)
/var/lib/snapd/snaps/gnome-3-38-2004_119.snap on /snap/gnome-3-38-2004/119 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core20_1623.snap on /snap/core20/1623 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-logs_115.snap on /snap/gnome-logs/115 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-characters_781.snap on /snap/gnome-characters/781 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gtk-common-themes_1535.snap on /snap/gtk-common-themes/1535 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core20_1518.snap on /snap/core20/1518 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-3-38-2004_115.snap on /snap/gnome-3-38-2004/115 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/tree_18.snap on /snap/tree/18 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/bare_5.snap on /snap/bare/5 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core18_2566.snap on /snap/core18/2566 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core22_310.snap on /snap/core22/310 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-system-monitor_178.snap on /snap/gnome-system-monitor/178 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-3-28-1804_116.snap on /snap/gnome-3-28-1804/116 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-calculator_920.snap on /snap/gnome-calculator/920 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core22_275.snap on /snap/core22/275 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-characters_741.snap on /snap/gnome-characters/741 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/gnome-3-28-1804_161.snap on /snap/gnome-3-28-1804/161 type squashfs (ro,nodev,relatime,x-gdu.hide)
/var/lib/snapd/snaps/core18_2409.snap on /snap/core18/2409 type squashfs (ro,nodev,relatime,x-gdu.hide)
tmpfs on /run/user/121 type tmpfs (rw,nosuid,nodev,relatime,size=553684k,mode=700,uid=121,gid=125)
tmpfs on /run/user/1000 type tmpfs (rw,nosuid,nodev,relatime,size=553684k,mode=700,uid=1000,gid=1000)
gvfsd-fuse on /run/user/1000/gvfs type fuse.gvfsd-fuse (rw,nosuid,nodev,relatime,user_id=1000,group_id=1000)
/dev/fuse on /run/user/1000/doc type fuse (rw,nosuid,nodev,relatime,user_id=1000,group_id=1000)
tmpfs on /run/snapd/ns type tmpfs (rw,nosuid,noexec,relatime,size=553688k,mode=755)
nsfs on /run/snapd/ns/tree.mnt type nsfs (rw)
/dev/sdb1 on /media/kevin/KINGSTON type vfat (rw,nosuid,nodev,relatime,uid=1000,gid=1000,fmask=0022,dmask=0022,codepage=437,iocharset=iso8859-1,shortname=mixed,showexec,utf8,flush,errors=remount-ro,uhelper=udisks2)
kevin@ubuntu:/$ umount /dev/sdb1
# success umount KINGSTON usb device 
```
由於通通卸載了，此時你才可以退出光碟片、軟碟片、USB隨身碟等設備喔！如果你遇到這樣的情況：
```
[root@study ~]# mount /dev/sr0 /data/cdrom
[root@study ~]# cd /data/cdrom
[root@study cdrom]# umount /data/cdrom
umount: /data/cdrom: target is busy.
        (In some cases useful info about processes that use
         the device is found by lsof(8) or fuser(1))

[root@study cdrom]# cd /
[root@study /]# umount /data/cdrom
```
由於你目前正在 /data/cdrom/ 的目錄內，也就是說其實『你正在使用該檔案系統』的意思！所以自然無法卸載這個裝置！那該如何是好？就『離開該檔案系統的掛載點』即可。以上述的案例來說， 你可以使用『 cd / 』回到根目錄，就能夠卸載 /data/cdrom 囉！簡單吧！

#### 重新掛載根目錄與掛載不特定目錄
整個目錄樹最重要的地方就是根目錄了，所以根目錄根本就不能夠被卸載的！問題是，如果你的掛載參數要改變， 或者是根目錄出現『唯讀』狀態時，如何重新掛載呢？最可能的處理方式就是重新開機 (reboot)！ 不過你也可以這樣做：
```
範例：將 / 重新掛載，並加入參數為 rw 與 auto
[root@study ~]# mount -o remount,rw,auto /
```
重點是那個『 -o remount,xx 』的選項與參數！請注意，要重新掛載 (remount) 時， 這是個非常重要的機制！尤其是當你進入單人維護模式時，你的根目錄常會被系統掛載為唯讀，這個時候這個指令就太重要了！

另外，我們也可以利用 mount 來將某個目錄掛載到另外一個目錄去喔！這並不是掛載檔案系統，而是額外掛載某個目錄的方法！ 雖然底下的方法也可以使用 symbolic link 來連結，不過在某些不支援符號連結的程式運作中，還是得要透過這樣的方法才行。
```
範例：將 /var 這個目錄暫時掛載到 /data/var 底下：
[root@study ~]# mkdir /data/var
[root@study ~]# mount --bind /var /data/var
[root@study ~]# ls -lid /var /data/var
16777346 drwxr-xr-x. 22 root root 4096 Jun 15 23:43 /data/var
16777346 drwxr-xr-x. 22 root root 4096 Jun 15 23:43 /var
# 內容完全一模一樣啊！因為掛載目錄的緣故！

[root@study ~]# mount | grep var
/dev/mapper/centos-root on /data/var type xfs (rw,relatime,seclabel,attr2,inode64,noquota)
```
看起來，其實兩者連結到同一個 inode 嘛！ ^_^ 沒錯啦！**透過這個 mount --bind 的功能， 您可以將某個目錄掛載到其他目錄去喔！而並不是整塊 filesystem 的啦！所以從此進入 /data/var 就是進入 /var 的意思喔**！
### 7.3.6 磁碟/檔案系統參數修訂
某些時刻，你可能會希望修改一下目前檔案系統的一些相關資訊，舉例來說，你可能要修改 Label name ， 或者是 journal 的參數，或者是其他磁碟/檔案系統運作時的相關參數 (例如 DMA 啟動與否～)。 這個時候，就得需要底下這些相關的指令功能囉～

#### mknod
還記得我們說過，在 Linux 底下所有的裝置都以檔案來代表吧！**但是那個檔案如何代表該裝置呢？ 很簡單！就是透過檔案的 major 與 minor 數值來替代的**～所以，那個 major 與 minor 數值是有特殊意義的，不是隨意設定的喔！我們在 lsblk 指令的用法裡面也談過這兩個數值呢！舉例來說，在鳥哥的這個測試機當中， 那個用到的磁碟 /dev/sda 的相關裝置代碼如下：
```
kevin@ubuntu:~/os$ ll /dev/sda
brw-rw---- 1 root disk 8, 0 Nov  1 12:07 /dev/sda
```
上表當中 8 為主要裝置代碼 (Major) 而 0 則為次要裝置代碼 (Minor)。 我們的 Linux 核心認識的裝置資料就是透過這兩個數值來決定的！舉例來說，常見的磁碟檔名 /dev/sda 與 /dev/loop0 裝置代碼如下所示：
<div align=center><img src="/os_note/linux_file/picture/屏幕截图%202022-11-01%20192201.png"></div>
Linux 核心 2.6 版以後，硬體檔名已經都可以被系統自動的即時產生了，我們根本不需要手動建立裝置檔案。 不過某些情況底下我們可能還是得要手動處理裝置檔案的，例如在某些服務被關到特定目錄下時(chroot)， 就需要這樣做了。此時這個 mknod 就得要知道如何操作才行！
```
[root@study ~]# mknod 裝置檔名 [bcp] [Major] [Minor]
選項與參數：
裝置種類：
   b  ：設定裝置名稱成為一個周邊儲存設備檔案，例如磁碟等；
   c  ：設定裝置名稱成為一個周邊輸入設備檔案，例如滑鼠/鍵盤等；
   p  ：設定裝置名稱成為一個 FIFO 檔案；
Major ：主要裝置代碼；
Minor ：次要裝置代碼；

範例：由上述的介紹我們知道 /dev/vda10 裝置代碼 252, 10，請建立並查閱此裝置
[root@study ~]# mknod /dev/vda10 b 252 10
[root@study ~]# ll /dev/vda10
brw-r--r--. 1 root root 252, 10 Jun 24 23:40 /dev/vda10
# 上面那個 252 與 10 是有意義的，不要隨意設定啊！

範例：建立一個 FIFO 檔案，檔名為 /tmp/testpipe
[root@study ~]# mknod /tmp/testpipe p
[root@study ~]# ll /tmp/testpipe
prw-r--r--. 1 root root 0 Jun 24 23:44 /tmp/testpipe
# 注意啊！這個檔案可不是一般檔案，不可以隨便就放在這裡！
# 測試完畢之後請刪除這個檔案吧！看一下這個檔案的類型！是 p 喔！^_^

[root@study ~]# rm /dev/vda10 /tmp/testpipe
rm: remove block special file '/dev/vda10' ? y
rm: remove fifo '/tmp/testpipe' ? y
```
**test for myself**
```
kevin@ubuntu:~/os$ sudo mknod /tmp/testpipe p
[sudo] password for kevin: 
kevin@ubuntu:~/os$ ll /tmp/testpipe 
prw-r--r-- 1 root root 0 Nov  1 19:29 /tmp/testpipe|
```
#### tune2fs 修改 ext4 的 label name 與 UUID
```
[root@study ~]# tune2fs [-l] [-L Label] [-U uuid] 裝置檔名
選項與參數：
-l  ：類似 dumpe2fs -h 的功能～將 superblock 內的資料讀出來～
-L  ：修改 LABEL name
-U  ：修改 UUID 囉！

範例：列出 /dev/vda5 的 label name 之後，將它改成 vbird_ext4
[root@study ~]# dumpe2fs -h /dev/vda5 | grep name
dumpe2fs 1.42.9 (28-Dec-2013)
Filesystem volume name:   <none>   # 果然是沒有設定的！

[root@study ~]# tune2fs -L vbird_ext4 /dev/vda5
[root@study ~]# dumpe2fs -h /dev/vda5 | grep name
Filesystem volume name:   vbird_ext4
[root@study ~]# mount LABEL=vbird_ext4 /data/ext4
```

## 7.4 設定開機掛載

### 7.4.1 開機掛載 /etc/fstab 及 /etc/mtab
剛剛上面說了許多，那麼可不可以在開機的時候就將我要的檔案系統都掛好呢？這樣我就不需要每次進入 Linux 系統都還要在掛載一次呀！當然可以囉！那就直接到 **/etc/fstab** 裡面去修修就行囉！不過，在開始說明前，這裡要先跟大家說一說系統掛載的一些限制：

- 根目錄 / 是必須掛載的﹐而且一定要先於其它 mount point 被掛載進來。
- 其它 mount point 必須為已建立的目錄﹐可任意指定﹐但一定要遵守必須的系統目錄架構原則 (FHS)
- 所有 mount point 在同一時間之內﹐只能掛載一次。
- 所有 partition 在同一時間之內﹐只能掛載一
- 如若進行卸載﹐您必須先將工作目錄移到 mount point(及其子目錄) 之外。

```
kevin@ubuntu:~/os$ cat /etc/fstab
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/sda1 during installation
UUID=b16bcca1-6f61-4f98-883d-08da92739870 /               ext4    errors=remount-ro 0       1
/swapfile                                 none            swap    sw              0       0
/dev/fd0        /media/floppy0  auto    rw,user,noauto,exec,utf8 0       0
```
各個欄位的總結資料與詳細資料如下：
```
[裝置/UUID等]  [掛載點]  [檔案系統]  [檔案系統參數]  [dump]  [fsck]
```
第一欄：磁碟裝置檔名/UUID/LABEL name：這個欄位可以填寫的資料主要有三個項目：

- 檔案系統或磁碟的裝置檔名，如 /dev/vda2 等
- 檔案系統的 UUID 名稱，如 UUID=xxx
- 檔案系統的 LABEL 名稱，例如 LABEL=xxx

因為每個檔案系統都可以有上面三個項目，所以你喜歡哪個項目就填哪個項目！無所謂的！只是從鳥哥測試機的 /etc/fstab 裡面看到的，在掛載點 /boot 使用的已經是 UUID 了喔！那你會說不是還有多個寫 /dev/mapper/xxx 的嗎？怎麼回事啊？ 因為那個是 LVM 啊！LVM 的檔名在你的系統中也算是獨一無二的，這部份我們在後續章節再來談。 不過，如果為了一致性，你還是可以將他改成 UUID 也沒問題喔！(鳥哥還是比較建議使用 UUID 喔！) 要記得使用 blkid 或 xfs_admin 來查詢 UUID 喔！

第二欄：掛載點 (mount point)：：
就是掛載點啊！掛載點是什麼？一定是目錄啊～要知道啊！忘記的話，請回本章稍早之前的資料瞧瞧喔！

第三欄：磁碟分割槽的檔案系統：
在手動掛載時可以讓系統自動測試掛載，但在這個檔案當中我們必須要手動寫入檔案系統才行！ 包括 xfs, ext4, vfat, reiserfs, nfs 等等。

第四欄：檔案系統參數：
記不記得我們在 mount 這個指令中談到很多特殊的檔案系統參數？ 還有我們使用過的『-o codepage=950』？這些特殊的參數就是寫入在這個欄位啦！ 雖然之前在 mount 已經提過一次，這裡我們利用表格的方式再彙整一下：

|參數|	內容意義|
|  ----  | ----  |
|async/sync   非同步/同步	|設定磁碟是否以非同步方式運作！預設為 async(效能較佳)
|auto/noauto自動/非自動	|當下達 mount -a 時，此檔案系統是否會被主動測試掛載。預設為 auto。|
|rw/ro可讀寫/唯讀	|讓該分割槽以可讀寫或者是唯讀的型態掛載上來，如果你想要分享的資料是不給使用者隨意變更的， 這裡也能夠設定為唯讀。則不論在此檔案系統的檔案是否設定 w 權限，都無法寫入喔！
|exec/noexec可執行/不可執行	|限制在此檔案系統內是否可以進行『執行』的工作？如果是純粹用來儲存資料的目錄， 那麼可以設定為 noexec 會比較安全。不過，這個參數也不能隨便使用，因為你不知道該目錄下是否預設會有執行檔。舉例來說，如果你將 noexec 設定在 /var ，當某些軟體將一些執行檔放置於 /var 下時，那就會產生很大的問題喔！ 因此，建議這個 noexec 最多僅設定於你自訂或分享的一般資料目錄。
|user/nouser允許/不允許使用者掛載	|是否允許使用者使用 mount 指令來掛載呢？一般而言，我們當然不希望一般身份的 user 能使用 mount 囉，因為太不安全了，因此這裡應該要設定為 nouser 囉！|
|suid/nosuid具有/不具有 suid 權限	|該檔案系統是否允許 SUID 的存在？如果不是執行檔放置目錄，也可以設定為 nosuid 來取消這個功能！
|defaults	|同時具有 rw, suid, dev, exec, auto, nouser, async 等參數。 基本上，預設情況使用 defaults 設定即可！

第五欄：能否被 dump 備份指令作用：
dump 是一個用來做為備份的指令，不過現在有太多的備份方案了，所以這個項目可以不要理會啦！直接輸入 0 就好了！

第六欄：是否以 fsck 檢驗磁區：
早期開機的流程中，會有一段時間去檢驗本機的檔案系統，看看檔案系統是否完整 (clean)。 不過這個方式使用的主要是透過 fsck 去做的，我們現在用的 xfs 檔案系統就沒有辦法適用，因為 xfs 會自己進行檢驗，不需要額外進行這個動作！所以直接填 0 就好了。

### 7.4.2 特殊裝置 loop 掛載 (映象檔不燒錄就掛載使用)
如果有光碟映像檔，或者是使用檔案作為磁碟的方式時，那就得要使用特別的方法來將他掛載起來，不需要燒錄啦！
#### 掛載光碟/DVD映象檔
下載了 Linux 或者是其他所需光碟/DVD的映象檔後， 難道一定需要燒錄成為光碟才能夠使用該檔案裡面的資料嗎？當然不是啦！我們可以透過 loop 裝置來掛載的！

那要如何掛載呢？鳥哥將整個 CentOS 7.x 的 DVD 映象檔捉到測試機上面，然後利用這個檔案來掛載給大家參考看看囉！
```
[root@study ~]# ll -h /tmp/CentOS-7.0-1406-x86_64-DVD.iso
-rw-r--r--. 1 root root 3.9G Jul  7  2014 /tmp/CentOS-7.0-1406-x86_64-DVD.iso
# 看到上面的結果吧！這個檔案就是映象檔，檔案非常的大吧！

[root@study ~]# mkdir /data/centos_dvd
[root@study ~]# mount -o loop /tmp/CentOS-7.0-1406-x86_64-DVD.iso /data/centos_dvd
[root@study ~]# df /data/centos_dvd
Filesystem     1K-blocks    Used Available Use% Mounted on
/dev/loop0       4050860 4050860         0 100% /data/centos_dvd
# 就是這個項目！ .iso 映象檔內的所有資料可以在 /data/centos_dvd 看到！

[root@study ~]# ll /data/centos_dvd
total 607
-rw-r--r--. 1  500  502     14 Jul  5  2014 CentOS_BuildTag <==瞧！就是DVD的內容啊！
drwxr-xr-x. 3  500  502   2048 Jul  4  2014 EFI
-rw-r--r--. 1  500  502    611 Jul  5  2014 EULA
-rw-r--r--. 1  500  502  18009 Jul  5  2014 GPL
drwxr-xr-x. 3  500  502   2048 Jul  4  2014 images
.....(底下省略).....

[root@study ~]# umount /data/centos_dvd/
# 測試完成！記得將資料給他卸載！同時這個映像檔也被鳥哥刪除了...測試機容量不夠大！
```
非常方便吧！如此一來我們不需要將這個檔案燒錄成為光碟或者是 DVD 就能夠讀取內部的資料了！ 換句話說，你也可以在這個檔案內『動手腳』去修改檔案的！這也是為什麼很多映象檔提供後，還得要提供驗證碼 (MD5) 給使用者確認該映象檔沒有問題！

#### 建立大檔案以製作 loop 裝置檔案！
想一想，既然能夠掛載 DVD 的映象檔，那麼我能不能製作出一個大檔案，然後將這個檔案格式化後掛載呢？ 好問題！這是個有趣的動作！而且還能夠幫助我們解決很多系統的分割不良的情況呢！舉例來說，如果當初在分割時， 你只有分割出一個根目錄，假設你已經沒有多餘的容量可以進行額外的分割的！偏偏根目錄的容量還很大！ 此時你就能夠製作出一個大檔案，然後將這個檔案掛載！如此一來感覺上你就多了一個分割槽囉！用途非常的廣泛啦！
底下我們在 /srv 下建立一個 512MB 左右的大檔案，然後將這個大檔案格式化並且實際掛載來玩一玩！ 這樣你會比較清楚鳥哥在講啥！

- 建立大型檔案

首先，我們得先有一個大的檔案吧！怎麼建立這個大檔案呢？在 Linux 底下我們有一支很好用的程式 dd ！他可以用來建立空的檔案喔！詳細的說明請先翻到下一章 壓縮指令的運用 來查閱，這裡鳥哥僅作一個簡單的範例而已。 假設我要建立一個空的檔案在 /srv/loopdev ，那可以這樣做：
```
kevin@ubuntu:~/os$ sudo dd if=/dev/zero of=/srv/loopdev bs=1M count=512
[sudo] password for kevin: 
512+0 records in
512+0 records out
536870912 bytes (537 MB, 512 MiB) copied, 1.67879 s, 320 MB/s
# 這個指令的簡單意義如下：
# if    是 input file ，輸入檔案。那個 /dev/zero 是會一直輸出 0 的裝置！
# of    是 output file ，將一堆零寫入到後面接的檔案中。
# bs    是每個 block 大小，就像檔案系統那樣的 block 意義；
# count 則是總共幾個 bs 的意思。所以 bs*count 就是這個檔案的容量了！
kevin@ubuntu:~/os$ ll -h /srv/loopdev 
-rw-r--r-- 1 root root 512M Nov  3 15:08 /srv/loopdev
```
dd 就好像在疊磚塊一樣，將 512 塊，每塊 1MB 的磚塊堆疊成為一個大檔案 (/srv/loopdev) ！ 最終就會出現一個 512MB 的檔案！粉簡單吧！
- 大型檔案的格式化

預設 xfs 不能夠格式化檔案的，所以要格式化檔案得要加入特別的參數才行喔！讓我們來瞧瞧！

```
kevin@ubuntu:~/os$ sudo mkfs.xfs -f /srv/loopdev
[sudo] password for kevin: 
meta-data=/srv/loopdev           isize=512    agcount=4, agsize=32768 blks
         =                       sectsz=512   attr=2, projid32bit=1
         =                       crc=1        finobt=1, sparse=0, rmapbt=0, reflink=0
data     =                       bsize=4096   blocks=131072, imaxpct=25
         =                       sunit=0      swidth=0 blks
naming   =version 2              bsize=4096   ascii-ci=0 ftype=1
log      =internal log           bsize=4096   blocks=855, version=2
         =                       sectsz=512   sunit=0 blks, lazy-count=1
realtime =none                   extsz=4096   blocks=0, rtextents=0
kevin@ubuntu:~/os$ blkid /srv/loopdev
/srv/loopdev: UUID="7b46df6c-aebc-473b-a4ea-0d029d0a1179" TYPE="xfs"
```
其實很簡單啦！所以鳥哥就不輸出格式化的結果了！要注意 UUID 的數值，未來會用到！

- 掛載

那要如何掛載啊？利用 mount 的特殊參數，那個 -o loop 的參數來處理！
```
root@ubuntu:/home/kevin/os# blkid /srv/loopdev
/srv/loopdev: UUID="7b46df6c-aebc-473b-a4ea-0d029d0a1179" TYPE="xfs"
root@ubuntu:/home/kevin/os# mount -o loop UUID="7b46df6c-aebc-473b-a4ea-0d029d0a1179" /mnt
root@ubuntu:/home/kevin/os# df /mnt
Filesystem     1K-blocks  Used Available Use% Mounted on
/dev/loop27       520868 26976    493892   6% /mnt
```
透過這個簡單的方法，感覺上你就可以在原本的分割槽在不更動原有的環境下製作出你想要的分割槽就是了！ 這東西很好用的！尤其是想要玩 Linux 上面的『虛擬機器』的話， 也就是以一部 Linux 主機再切割成為數個獨立的主機系統時，類似 VMware 這類的軟體， 在 Linux 上使用 xen 這個軟體，他就可以配合這種 loop device 的檔案類型來進行根目錄的掛載，真的非常有用的喔！ ^_^

比較特別的是，CentOS 7.x 越來越聰明了，現在你不需要下達 -o loop 這個選項與參數，它同樣可以被系統掛上來！ 連直接輸入 blkid 都會列出這個檔案內部的檔案系統耶！相當有趣！不過，為了考量向下相容性，鳥哥還是建議你加上 loop 比較妥當喔！ 現在，請將這個檔案系統永遠的自動掛載起來吧！

```
root@ubuntu:/home/kevin/os# df /mnt
Filesystem     1K-blocks  Used Available Use% Mounted on
/dev/loop27       520868 26976    493892   6% /mnt
root@ubuntu:/home/kevin/os# nano /etc/fstab 
root@ubuntu:/home/kevin/os# umount /mnt
root@ubuntu:/home/kevin/os# mkdir -p /data/file
root@ubuntu:/home/kevin/os# mount -a
root@ubuntu:/home/kevin/os# df /data/file
Filesystem     1K-blocks  Used Available Use% Mounted on
/dev/loop27       520868 26976    493892   6% /data/file
```

## 7.5 記憶體置換空間(swap)之建置
以前的年代因為記憶體不足，因此那個可以暫時將記憶體的程序拿到硬碟中暫放的記憶體置換空間 (swap) 就顯的非常的重要！ 否則，如果突然間某支程式用掉你大部分的記憶體，那你的系統恐怕有損毀的情況發生喔！所以，早期在安裝 Linux 之前，大家常常會告訴你： 安裝時一定需要的兩個 partition ，一個是根目錄，另外一個就是 swap(記憶體置換空間)。關於記憶體置換空間的解釋在第三章安裝 Linux 內的磁碟分割時有約略提過，請你自行回頭瞧瞧吧！

一般來說，如果硬體的配備資源足夠的話，那麼 swap 應該不會被我們的系統所使用到， swap 會被利用到的時刻通常就是實體記憶體不足的情況了。從第零章的計算機概論當中，我們知道 CPU 所讀取的資料都來自於記憶體， 那當記憶體不足的時候，為了讓後續的程式可以順利的運作，因此在記憶體中暫不使用的程式與資料就會被挪到 swap 中了。 此時記憶體就會空出來給需要執行的程式載入。由於 swap 是用磁碟來暫時放置記憶體中的資訊，所以用到 swap 時，你的主機磁碟燈就會開始閃個不停啊！

雖然目前(2015)主機的記憶體都很大，至少都有 4GB 以上囉！因此在個人使用上，你不要設定 swap 在你的 Linux 應該也沒有什麼太大的問題。 不過伺服器可就不這麼想了～由於你不會知道何時會有大量來自網路的要求，因此最好還是能夠預留一些 swap 來緩衝一下系統的記憶體用量！ 至少達到『備而不用』的地步啊！

現在想像一個情況，你已經將系統建立起來了，此時卻才發現你沒有建置 swap ～那該如何是好呢？ 透過本章上面談到的方法，你可以使用如下的方式來建立你的 swap 囉！

- 設定一個 swap partition
- 建立一個虛擬記憶體的檔案


不囉唆，就立刻來處理處理吧！

### 7.5.1 使用實體分割槽建置swap
建立 swap 分割槽的方式也是非常的簡單的！透過底下幾個步驟就搞定囉：

1. 分割：先使用 gdisk 在你的磁碟中分割出一個分割槽給系統作為 swap 。由於 Linux 的 gdisk 預設會將分割槽的 ID 設定為 Linux 的檔案系統，所以你可能還得要設定一下 system ID 就是了。
2. 格式化：利用建立 swap 格式的『mkswap 裝置檔名』就能夠格式化該分割槽成為 swap 格式囉
3. 使用：最後將該 swap 裝置啟動，方法為：『swapon 裝置檔名』。
4. 觀察：最終透過 free 與 swapon -s 這個指令來觀察一下記憶體的用量吧！

不囉唆，立刻來實作看看！既然我們還有多餘的磁碟容量可以分割，那麼讓我們繼續分割出 512MB 的磁碟分割槽吧！ 然後將這個磁碟分割槽做成 swap 吧！

- 3. 開始觀察與載入看看吧！
```
kevin@ubuntu:~/os$ free
              total        used        free      shared  buff/cache   available
Mem:        5536876     2029884      778368       27748     2728624     3219516
Swap:       1459804           0     1459804
kevin@ubuntu:~/os$ swapon -s 
Filename                                Type            Size    Used    Priority
/swapfile                               file            1459804 0       -2
```

### 7.5.2 使用檔案建置swap
如果是在實體分割槽無法支援的環境下，此時前一小節提到的 loop 裝置建置方法就派的上用場啦！ 與實體分割槽不一樣的，這個方法只是利用 dd 去建置一個大檔案而已。多說無益，我們就再透過檔案建置的方法建立一個 128 MB 的記憶體置換空間吧！

說實話，swap 在目前的桌上型電腦來講，存在的意義已經不大了！這是因為目前的 x86 主機所含的記憶體實在都太大了 (一般入門級至少也都有 4GB 了)，所以，我們的 Linux 系統大概都用不到 swap 這個玩意兒的。不過， 如果是針對伺服器或者是工作站這些常年上線的系統來說的話，那麼，無論如何，swap 還是需要建立的。

**因為 swap 主要的功能是當實體記憶體不夠時，則某些在記憶體當中所佔的程式會暫時被移動到 swap 當中，讓實體記憶體可以被需要的程式來使用**。另外，**如果你的主機支援電源管理模式， 也就是說，你的 Linux 主機系統可以進入『休眠』模式的話，那麼， 運作當中的程式狀態則會被紀錄到 swap 去，以作為『喚醒』主機的狀態依據**！ 另外，有某些程式在運作時，本來就會利用 swap 的特性來存放一些資料段， 所以， swap 來是需要建立的！只是不需要太大！

## 7.6 檔案系統的特殊觀察與操作
### 7.6.1 磁碟空間之浪費問題
我們在前面的 EXT2 data block 介紹中談到了一個 block 只能放置一個檔案， 因此太多小檔案將會浪費非常多的磁碟容量。但你有沒有注意到，整個檔案系統中包括 superblock, inode table 與其他中介資料等其實都會浪費磁碟容量喔！所以當我們在 /dev/vda4, /dev/vda5 建立起 xfs/ext4 檔案系統時， 一掛載就立刻有很多容量被用掉了！

另外，不知道你有沒有發現到，當你使用 ls -l 去查詢某個目錄下的資料時，第一行都會出現一個『total』的字樣！ 那是啥東西？其實那就是該目錄下的所有資料所耗用的實際 block 數量 * block 大小的值。 我們可以透過 ll -s 來觀察看看上述的意義：
```
kevin@ubuntu:~/os$ ll -sh
total 540K
4.0K drwxrwxr-x  6 kevin kevin 4.0K Oct 28 09:47 ./
4.0K drwxr-xr-x 41 kevin kevin 4.0K Nov  3 14:50 ../
4.0K drwxrwxr-x  9 kevin kevin 4.0K Nov  2 17:05 .git/
4.0K -rw-rw-r--  1 kevin kevin 2.5K Oct 28 09:47 .gitattributes
8.0K -rw-rw-r--  1 kevin kevin 5.7K Oct 28 09:47 .gitignore
4.0K -rw-rw-r--  1 kevin kevin  141 Oct 13 17:55 .gitmodules
4.0K drwxrwxr-x  5 kevin kevin 4.0K Oct 18 15:42 os_experiment/
4.0K drwxrwxr-x  8 kevin kevin 4.0K Oct 22 19:57 os_note/
4.0K drwxrwxr-x  2 kevin kevin 4.0K Oct 19 17:33 .vscode/
500K -rwxrw-rw-  1 kevin kevin 497K Oct  9 15:33 路线图.jpg*
```
從上面的特殊字體部分，那就是每個檔案所使用掉 block 的容量！舉例來說，那個 crontab 雖然僅有 451bytes ， 不過他卻佔用了整個 block (每個 block 為 4K)，所以將所有的檔案的所有的 block 加總就得到 12Kbytes 那個數值了。 如果計算每個檔案實際容量的加總結果，其實只有不到 5K 而已～所以囉，這樣就耗費掉好多容量了！未來大家在討論小磁碟、 大磁碟，檔案容量的損耗時，要回想到這個區塊喔！ ^_^

### 7.6.2 利用 GNU 的 parted 進行分割行為(Optional)
parted 可以直接在一行指令列就完成分割，是一個非常好用的指令！它常用的語法如下：
```
[root@study ~]# parted [裝置] [指令 [參數]]
選項與參數：
指令功能：
          新增分割：mkpart [primary|logical|extended] [ext4|vfat|xfs] 開始 結束
          顯示分割：print
          刪除分割：rm [partition]

範例一：以 parted 列出目前本機的分割表資料
kevin@ubuntu:~/os$ sudo parted /dev/sda print
[sudo] password for kevin: 
Model: VMware, VMware Virtual S (scsi)
Disk /dev/sda: 53.7GB
Sector size (logical/physical): 512B/512B
Partition Table: msdos
Disk Flags: 

Number  Start   End     Size    Type     File system  Flags
 1      1049kB  53.7GB  53.7GB  primary  ext4         boot
```

## 7.7 重點回顧
- 一個可以被掛載的資料通常稱為『檔案系統, filesystem』而不是分割槽 (partition) 喔！
- 基本上 Linux 的傳統檔案系統為 Ext2 ，該檔案系統內的資訊主要有：
     - superblock：記錄此 filesystem 的整體資訊，包括inode/block的總量、使用量、剩餘量， 以及檔案系統的格式與相關資訊等；
     - inode：記錄檔案的屬性，一個檔案佔用一個inode，同時記錄此檔案的資料所在的 block 號碼；
     - block：實際記錄檔案的內容，若檔案太大時，會佔用多個 block 。
- Ext2 檔案系統的資料存取為索引式檔案系統(indexed allocation)
- 需要磁碟重組的原因就是檔案寫入的 block 太過於離散了，此時檔案讀取的效能將會變的很差所致。 這個時候可以透過磁碟重組將同一個檔案所屬的 blocks 彙整在一起。
- Ext2檔案系統主要有：boot sector, superblock, inode bitmap, block bitmap, inode table, data block 等六大部分。
- data block 是用來放置檔案內容資料地方，在 Ext2 檔案系統中所支援的 block 大小有 1K, 2K 及 4K 三種而已
- inode 記錄檔案的屬性/權限等資料，其他重要項目為： 每個 inode 大小均為固定，有 128/256bytes 兩種基本容量。每個檔案都僅會佔用一個 inode 而已； 因此檔案系統能夠建立的檔案數量與 inode 的數量有關；
- 檔案的 block 在記錄檔案的實際資料，目錄的 block 則在記錄該目錄底下檔名與其 inode 號碼的對照表；
- 日誌式檔案系統 (journal) 會多出一塊記錄區，隨時記載檔案系統的主要活動，可加快系統復原時間；
- Linux 檔案系統為增加效能，會讓主記憶體作為大量的磁碟快取；
- 實體連結只是多了一個檔名對該 inode 號碼的連結而已；
- 符號連結就類似Windows的捷徑功能。
- 磁碟的使用必需要經過：分割、格式化與掛載，分別慣用的指令為：gdisk, mkfs, mount三個指令
- 分割時，應使用 parted 檢查分割表格式，再判斷使用 fdisk/gdisk 來分割，或直接使用 parted 分割
- 為了考慮效能，XFS 檔案系統格式化時，可以考慮加上 agcount/su/sw/extsize 等參數較佳
- 如果磁碟已無未分割的容量，可以考慮使用大型檔案取代磁碟裝置的處理方式，透過 dd 與格式化功能。
- 開機自動掛載可參考/etc/fstab之設定，設定完畢務必使用 mount -a 測試語法正確否；