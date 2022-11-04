# 第八章、檔案與檔案系統的壓縮,打包與備份
---
## 8.1 壓縮檔案的用途與技術
文件檔案太大，那個好用的『檔案壓縮』技術可就派的上用場了！

因為這些比較大型的檔案透過所謂的檔案壓縮技術之後，可以將他的磁碟使用量降低，可以達到減低檔案容量的效果。此外，有的壓縮程式還可以進行容量限制， 使一個大型檔案可以分割成為數個小型檔案，以方便軟碟片攜帶呢！

由於我們記錄數字是 1 ，考慮電腦所謂的二進位喔，如此一來， 1 會在最右邊佔據 1 個 bit ，而其他的 7 個 bits 將會自動的被填上 0 囉！你看看，其實在這樣的例子中，那 7 個 bits 應該是『空的』才對！不過，為了要滿足目前我們的作業系統資料的存取，所以就會將該資料轉為 byte 的型態來記錄了！而一些聰明的電腦工程師就利用一些複雜的計算方式， 將這些沒有使用到的空間『丟』出來，以讓檔案佔用的空間變小！這就是壓縮的技術啦！

另外一種壓縮技術也很有趣，他是將重複的資料進行統計記錄的。舉例來說，如果你的資料為『111....』共有100個1時， 那麼壓縮技術會記錄為『100個1』而不是真的有100個1的位元存在！這樣也能夠精簡檔案記錄的容量呢！ 非常有趣吧！

簡單的說，你可以將他想成，其實檔案裡面有相當多的『空間』存在，並不是完全填滿的， 而『壓縮』的技術就是將這些『空間』填滿，以讓整個檔案佔用的容量下降！ 不過，這些『壓縮過的檔案』並無法直接被我們的作業系統所使用的，因此， 若要使用這些被壓縮過的檔案資料，則必須將他『還原』回來未壓縮前的模樣， 那就是所謂的『解壓縮』囉！而至於壓縮後與壓縮的檔案所佔用的磁碟空間大小， 就可以被稱為是『壓縮比』囉！

## 8.2 Linux 系統常見的壓縮指令
在Linux的環境中，壓縮檔案的副檔名大多是：『*.tar, *.tar.gz, *.tgz, *.gz, *.Z, *.bz2, *.xz』，為什麼會有這樣的副檔名呢？不是說 Linux 的副檔名沒有什麼作用嗎？

這是因為 Linux 支援的壓縮指令非常多，且不同的指令所用的壓縮技術並不相同，當然彼此之間可能就無法互通壓縮/解壓縮檔案囉。 所以，當你下載到某個壓縮檔時，自然就需要知道該檔案是由哪種壓縮指令所製作出來的，好用來對照著解壓縮啊！ 也就是說，雖然 Linux 檔案的屬性基本上是與檔名沒有絕對關係的， 但是為了幫助我們人類小小的腦袋瓜子，所以適當的副檔名還是必要的！ 底下我們就列出幾個常見的壓縮檔案副檔名吧：

>*.Z         compress 程式壓縮的檔案；
*.zip       zip 程式壓縮的檔案；
*.gz        gzip 程式壓縮的檔案；
*.bz2       bzip2 程式壓縮的檔案；
*.xz        xz 程式壓縮的檔案；
*.tar       tar 程式打包的資料，並沒有壓縮過；
*.tar.gz    tar 程式打包的檔案，其中並且經過 gzip 的壓縮
*.tar.bz2   tar 程式打包的檔案，其中並且經過 bzip2 的壓縮
*.tar.xz    tar 程式打包的檔案，其中並且經過 xz 的壓縮

Linux上常見的壓縮指令就是 gzip, bzip2 以及最新的 xz ，至於 compress 已經退流行了。為了支援 windows 常見的 zip，其實 Linux 也早就有 zip 指令了！ gzip 是由 GNU 計畫所開發出來的壓縮指令，該指令已經取代了 compress 。 後來 GNU 又開發出 bzip2 及 xz 這幾個壓縮比更好的壓縮指令！**不過，這些指令通常僅能針對一個檔案來壓縮與解壓縮，如此一來， 每次壓縮與解壓縮都要一大堆檔案，豈不煩人？此時，那個所謂的『打包軟體, tar』就顯的很重要啦**！

這個 tar 可以將很多檔案『打包』成為一個檔案！甚至是目錄也可以這麼玩。不過，單純的 tar 功能僅是『打包』而已，亦即是將很多檔案集結成為一個檔案， 事實上，他並沒有提供壓縮的功能，後來，GNU 計畫中，將整個 tar 與壓縮的功能結合在一起，如此一來提供使用者更方便並且更強大的壓縮與打包功能！ 底下我們就來談一談這些在 Linux 底下基本的壓縮指令吧！

### 8.2.1 gzip, zcat/zmore/zless/zgrep
gzip 可以說是應用度最廣的壓縮指令了！**目前 gzip 可以解開 compress, zip 與 gzip 等軟體所壓縮的檔案。 至於 gzip 所建立的壓縮檔為 *.gz 的檔名喔**！讓我們來看看這個指令的語法吧：
```
[dmtsai@study ~]$ gzip [-cdtv#] 檔名
[dmtsai@study ~]$ zcat 檔名.gz
選項與參數：
-c  ：將壓縮的資料輸出到螢幕上，可透過資料流重導向來處理；
-d  ：解壓縮的參數；
-t  ：可以用來檢驗一個壓縮檔的一致性～看看檔案有無錯誤；
-v  ：可以顯示出原檔案/壓縮檔案的壓縮比等資訊；
-#  ：# 為數字的意思，代表壓縮等級，-1 最快，但是壓縮比最差、-9 最慢，但是壓縮比最好！預設是 -6

kevin@ubuntu:~/os$ mkdir os_note/test
kevin@ubuntu:~/os$ ls os_note/
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test
kevin@ubuntu:~/os$ touch os_note/test/test.txt
kevin@ubuntu:~/os$ chmod u+x os_note/test/test.txt 
kevin@ubuntu:~/os$ cp os_note/test/ os_note/test1
cp: -r not specified; omitting directory 'os_note/test/'
kevin@ubuntu:~/os$ cp -r os_note/test/ os_note/test1
kevin@ubuntu:~/os$ ls
os_experiment  os_note  路线图.jpg
kevin@ubuntu:~/os$ ls os_note/
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test  test1
kevin@ubuntu:~/os$ gzip -v os_note/test1
gzip: os_note/test1 is a directory -- ignored
kevin@ubuntu:~/os$ ls os_note/test1
test.txt
kevin@ubuntu:~/os$ gzip -v os_note/test1/test.txt 
os_note/test1/test.txt:   0.0% -- replaced with os_note/test1/test.txt.gz
```
**當你使用 gzip 進行壓縮時，在預設的狀態下原本的檔案會被壓縮成為 .gz 的檔名，原始檔案就不再存在了**。 這點與一般習慣使用 windows 做壓縮的朋友所熟悉的情況不同喔！要注意！要注意！ 此外，使用 gzip 壓縮的檔案在 Windows 系統中，竟然可以被 WinRAR/7zip 這個軟體解壓縮呢！很好用吧！至於其他的用法如下：
```
範例二：由於 services 是文字檔，請將範例一的壓縮檔的內容讀出來！
[dmtsai@study tmp]$ zcat services.gz
# 由於 services 這個原本的檔案是是文字檔，因此我們可以嘗試使用 zcat/zmore/zless 去讀取！
# 此時螢幕上會顯示 servcies.gz 解壓縮之後的原始檔案內容！

範例三：將範例一的檔案解壓縮
[dmtsai@study tmp]$ gzip -d services.gz
# 鳥哥不要使用 gunzip 這個指令，不好背！使用 gzip -d 來進行解壓縮！
# 與 gzip 相反， gzip -d 會將原本的 .gz 刪除，回復到原本的 services 檔案。

範例四：將範例三解開的 services 用最佳的壓縮比壓縮，並保留原本的檔案
[dmtsai@study tmp]$ gzip -9 -c services > services.gz

範例五：由範例四再次建立的 services.gz 中，找出 http 這個關鍵字在哪幾行？
[dmtsai@study tmp]$ zgrep -n 'http' services.gz
14:#       http://www.iana.org/assignments/port-numbers
89:http            80/tcp          www www-http    # WorldWideWeb HTTP
90:http            80/udp          www www-http    # HyperText Transfer Protocol
.....(底下省略).....
```
**使用用法**
```
压缩 gzip -v
解压缩 gzip -d 
```
範例四的重點在那個 -c 與 > 的使用囉！-c 可以將原本要轉成壓縮檔的資料內容，將它變成文字類型從螢幕輸出， 然後我們可以透過大於 (>) 這個符號，將原本應該由螢幕輸出的資料，轉成輸出到檔案而不是螢幕，所以就能夠建立出壓縮擋了。只是檔名也要自己寫， 當然最好還是遵循 gzip 的壓縮檔名要求較佳喔！！更多的 > 這個符號的應用，我們會在 bash 章節再次提及！

cat/more/less 可以使用不同的方式來讀取純文字檔，那個 zcat/zmore/zless 則可以對應於 cat/more/less 的方式來讀取純文字檔被壓縮後的壓縮檔！ 由於 gzip 這個壓縮指令主要想要用來取代 compress 的，所以不但 compress 的壓縮檔案可以使用 gzip 來解開，同時 zcat 這個指令可以同時讀取 compress 與 gzip 的壓縮檔呦！

另外，如果你還想要從文字壓縮檔當中找資料的話，可以透過 zgrep 來搜尋關鍵字喔！而不需要將壓縮檔解開才以 grep 進行！ 這對查詢備份中的文字檔資料相當有用！

### 8.2.2 bzip2, bzcat/bzmore/bzless/bzgrep
若說 gzip 是為了取代 compress 並提供更好的壓縮比而成立的，那麼 bzip2 則是為了取代 gzip 並提供更佳的壓縮比而來的。 bzip2 真是很不錯用的東西～這玩意的壓縮比竟然比 gzip 還要好～至於 bzip2 的用法幾乎與 gzip 相同！看看底下的用法吧！
```
[dmtsai@study ~]$ bzip2 [-cdkzv#] 檔名
[dmtsai@study ~]$ bzcat 檔名.bz2
選項與參數：
-c  ：將壓縮的過程產生的資料輸出到螢幕上！
-d  ：解壓縮的參數
-k  ：保留原始檔案，而不會刪除原始的檔案喔！
-z  ：壓縮的參數 (預設值，可以不加)
-v  ：可以顯示出原檔案/壓縮檔案的壓縮比等資訊；
-#  ：與 gzip 同樣的，都是在計算壓縮比的參數， -9 最佳， -1 最快！

kevin@ubuntu:~/os$ bzip2 -v os_note/test1/test.txt 
  os_note/test1/test.txt:  0.424:1, 18.857 bits/byte, -135.71% saved, 28 in, 66 out.
kevin@ubuntu:~/os$ bzcat os_note/test1/test.txt.bz2 
hello world
Taiwan
Mainland
kevin@ubuntu:~/os$ bzip2 -d os_note/test1/test.txt.bz2 
kevin@ubuntu:~/os$ ls os_note/test1/
test.txt
```
看上面的範例，你會發現到 bzip2 連選項與參數都跟 gzip 一模一樣！只是副檔名由 .gz 變成 .bz2 而已！其他的用法都大同小異，所以鳥哥就不一一介紹了！ 你也可以發現到 bzip2 的壓縮率確實比 gzip 要好些！不過，對於大容量檔案來說，bzip2 壓縮時間會花比較久喔！至少比 gzip 要久的多！ 這沒辦法～要有更多可用容量，就得要花費相對應的時間！還 OK 啊！

### 8.2.3 xz, xzcat/xzmore/xzless/xzgrep
雖然 bzip2 已經具有很棒的壓縮比，不過顯然某些自由軟體開發者還不滿足，因此後來還推出了 xz 這個壓縮比更高的軟體！這個軟體的用法也跟 gzip/bzip2 幾乎一模一樣！ 那我們就來瞧一瞧！
```
[dmtsai@study ~]$ xz [-dtlkc#] 檔名
[dmtsai@study ~]$ xcat 檔名.xz
選項與參數：
-d  ：就是解壓縮啊！
-t  ：測試壓縮檔的完整性，看有沒有錯誤
-l  ：列出壓縮檔的相關資訊
-k  ：保留原本的檔案不刪除～
-c  ：同樣的，就是將資料由螢幕上輸出的意思！
-#  ：同樣的，也有較佳的壓縮比的意思

kevin@ubuntu:~/os$ xz -v os_note/test1/test.txt 
os_note/test1/test.txt (1/1)
  100 %                 84 B / 28 B = 3.000                                    
kevin@ubuntu:~/os$ xzcat os_note/test1/test.txt.xz 
hello world
Taiwan
Mainland
kevin@ubuntu:~/os$ xz -l os_note/test1/test.txt.xz 
Strms  Blocks   Compressed Uncompressed  Ratio  Check   Filename
    1       1         84 B         28 B  3.000  CRC64   os_note/test1/test.txt.xz
kevin@ubuntu:~/os$ xz -d os_note/test1/test.txt.xz 
kevin@ubuntu:~/os$ ls os_note/test1
test.txt
kevin@ubuntu:~/os$ xz -k os_note/test1/test.txt 
kevin@ubuntu:~/os$ ls os_note/test1/
test.txt  test.txt.xz
```

雖然 xz 這個壓縮比真的好太多太多了！以鳥哥選擇的這個 services 檔案為範例，他可以將 gzip 壓縮比 (壓縮後/壓縮前) 的 21% 更進一步優化到 15% 耶！ 差非常非常多！不過， xz 最大的問題是...時間花太久了！如果你曾經使用過 xz 的話，應該會有發現，他的運算時間真的比 gzip 久很多喔！

鳥哥以自己的系統，透過『 time [gzip|bzip2|xz] -c services > services.[gz|bz2|xz] 』去執行運算結果，結果發現這三個指令的執行時間依序是： 0.019s, 0.042s, 0.261s， 看最後一個數字！差了 10 倍的時間耶！所以，如果你並不覺得時間是你的成本考量，那麼使用 xz 會比較好！如果時間是你的重要成本，那麼 gzip 恐怕是比較適合的壓縮軟體喔！

## 8.3 打包指令： tar
前一小節談到的指令大多僅能針對單一檔案來進行壓縮，雖然 gzip, bzip2, xz 也能夠針對目錄來進行壓縮，不過， **這兩個指令對目錄的壓縮指的是『將目錄內的所有檔案 "分別" 進行壓縮』的動作**！而不像在 Windows 的系統，可以使用類似 WinRAR 這一類的壓縮軟體來將好多資料『包成一個檔案』的樣式。

這種將多個檔案或目錄包成一個大檔案的指令功能，我們可以稱呼他是一種『打包指令』啦！ 那 Linux 有沒有這種打包指令呢？是有的！那就是鼎鼎大名的 tar 這個玩意兒了！ tar 可以將多個目錄或檔案打包成一個大檔案，同時還可以透過 gzip/bzip2/xz 的支援，將該檔案同時進行壓縮！ 更有趣的是，由於 tar 的使用太廣泛了，目前 Windows 的 WinRAR 也支援 .tar.gz 檔名的解壓縮呢！ 很不錯吧！所以底下我們就來玩一玩這個咚咚！

### 8.3.1 tar
tar 的選項與參數非常的多！我們只講幾個常用的選項，更多選項您可以自行 man tar 查詢囉！
```
[dmtsai@study ~]$ tar [-z|-j|-J] [cv] [-f 待建立的新檔名] filename... <==打包與壓縮
[dmtsai@study ~]$ tar [-z|-j|-J] [tv] [-f 既有的 tar檔名]             <==察看檔名
[dmtsai@study ~]$ tar [-z|-j|-J] [xv] [-f 既有的 tar檔名] [-C 目錄]   <==解壓縮
選項與參數：
-c  ：建立打包檔案，可搭配 -v 來察看過程中被打包的檔名(filename)
-t  ：察看打包檔案的內容含有哪些檔名，重點在察看『檔名』就是了；
-x  ：解打包或解壓縮的功能，可以搭配 -C (大寫) 在特定目錄解開
      特別留意的是， -c, -t, -x 不可同時出現在一串指令列中。
-z  ：透過 gzip  的支援進行壓縮/解壓縮：此時檔名最好為 *.tar.gz
-j  ：透過 bzip2 的支援進行壓縮/解壓縮：此時檔名最好為 *.tar.bz2
-J  ：透過 xz    的支援進行壓縮/解壓縮：此時檔名最好為 *.tar.xz
      特別留意， -z, -j, -J 不可以同時出現在一串指令列中
-v  ：在壓縮/解壓縮的過程中，將正在處理的檔名顯示出來！
-f filename：-f 後面要立刻接要被處理的檔名！建議 -f 單獨寫一個選項囉！(比較不會忘記)
-C 目錄    ：這個選項用在解壓縮，若要在特定目錄解壓縮，可以使用這個選項。

其他後續練習會使用到的選項介紹：
-p(小寫) ：保留備份資料的原本權限與屬性，常用於備份(-c)重要的設定檔
-P(大寫) ：保留絕對路徑，亦即允許備份資料中含有根目錄存在之意；
--exclude=FILE：在壓縮的過程中，不要將 FILE 打包！

kevin@ubuntu:~/os/os_note$ tar -zcvf test1.tar.gz test1
test1/
test1/test.cpp
test1/test.txt
test1/test.txt.xz
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test1  test1.tar.gz
kevin@ubuntu:~/os/os_note$ tar -ztvf test1.tar.gz 
drwxrwxr-x kevin/kevin       0 2022-11-04 17:01 test1/
-rw-rw-r-- kevin/kevin       0 2022-11-04 17:01 test1/test.cpp
-rwxrw-r-- kevin/kevin      28 2022-11-04 15:47 test1/test.txt
-rwxrw-r-- kevin/kevin      84 2022-11-04 15:47 test1/test.txt.xz
kevin@ubuntu:~/os/os_note$ tar -zxvf test1.tar.gz 
test1/
test1/test.cpp
test1/test.txt
test1/test.txt.xz
kevin@ubuntu:~/os/os_note$ ls
compress  elementary_knowledge  install_centos  linux_command  linux_environment  linux_file  test1  test1.tar.gz
```

壓縮比越好當然要花費的運算時間越多！我們從上面可以看到，雖然使用 gzip 的速度相當快，總時間花費不到 1 秒鐘，但是壓縮率最糟糕！ 如果使用 xz 的話，雖然壓縮比最佳！不過竟然花了 9 秒鐘的時間耶！這還僅是備份 28MBytes 的 /etc 而已，如果備份的資料是很大容量的， 那你真的要考量時間成本才行！

至於加上『 -p 』這個選項的原因是為了保存原本檔案的權限與屬性！我們曾在第六章的 cp 指令介紹時談到權限與檔案類型(例如連結檔)對複製的不同影響。 同樣的，在備份重要的系統資料時，這些原本檔案的權限需要做完整的備份比較好。此時 -p 這個選項就派的上用場了。 接下來讓我們看看打包檔案內有什麼資料存在？

#### 僅解開單一檔案的方法
剛剛上頭我們解壓縮都是將整個打包檔案的內容全部解開！想像一個情況，如果我只想要解開打包檔案內的其中一個檔案而已， 那該如何做呢？很簡單的，你只要使用 -jtv 找到你要的檔名，然後將該檔名解開即可。 我們用底下的例子來說明一下：
```
# 1. 先找到我們要的檔名，假設解開 shadow 檔案好了：
[root@study ~]# tar -jtv -f /root/etc.tar.bz2 | grep 'shadow'
---------- root/root       721 2015-06-17 00:20 etc/gshadow
---------- root/root      1183 2015-06-17 00:20 etc/shadow-
---------- root/root      1210 2015-06-17 00:20 etc/shadow  <==這是我們要的！
---------- root/root       707 2015-06-17 00:20 etc/gshadow-
# 先搜尋重要的檔名！其中那個 grep 是『擷取』關鍵字的功能！我們會在第三篇說明！
# 這裡您先有個概念即可！那個管線 | 配合 grep 可以擷取關鍵字的意思！

# 2. 將該檔案解開！語法與實際作法如下：
[root@study ~]# tar -jxv -f 打包檔.tar.bz2 待解開檔名
[root@study ~]# tar -jxv -f /root/etc.tar.bz2 etc/shadow
etc/shadow
[root@study ~]# ll etc
total 4
----------. 1 root root 1210 Jun 17 00:20 shadow
# 很有趣！此時只會解開一個檔案而已！不過，重點是那個檔名！你要找到正確的檔名。
# 在本例中，你不能寫成 /etc/shadow ！因為記錄在 etc.tar.bz2 內的並沒有 / 之故！
```

## 8.6 其他常見的壓縮與備份工具
還有一些很好用的工具得要跟大家介紹介紹，尤其是 dd 這個玩意兒呢！

### 8.6.1 dd
我們在第七章當中的特殊 loop 裝置掛載時使用過 dd 這個指令對吧？ 不過，這個指令可不只是製作一個檔案而已喔～這個 dd 指令最大的功效，鳥哥認為，應該是在於『備份』啊！ 因為 dd 可以讀取磁碟裝置的內容(幾乎是直接讀取磁區"sector")，然後將整個裝置備份成一個檔案呢！真的是相當的好用啊～ dd 的用途有很多啦～但是我們僅講一些比較重要的選項，如下：
```
[root@study ~]# dd if="input_file" of="output_file" bs="block_size" count="number"
選項與參數：
if   ：就是 input file 囉～也可以是裝置喔！
of   ：就是 output file 喔～也可以是裝置；
bs   ：規劃的一個 block 的大小，若未指定則預設是 512 bytes(一個 sector 的大小)
count：多少個 bs 的意思。
```
其實使用 dd 來備份是莫可奈何的情況，很笨耶！因為預設 dd 是一個一個磁區去讀/寫的，而且即使沒有用到的磁區也會被寫入備份檔中！ 因此這個檔案會變得跟原本的磁碟一模一樣大！不像使用 xfsdump 只備份檔案系統中有使用到的部份。不過， dd 就是因為不理會檔案系統， 單純有啥紀錄啥，因此不論該磁碟內的檔案系統你是否認識，它都可以備份、還原的！所以，鳥哥認為，上述的第三個案例是比較重要的學習喔！
