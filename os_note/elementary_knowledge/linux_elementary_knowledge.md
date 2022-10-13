# Linux 基础知识笔记
---
## 发展历史

<font size="4">**Unix**</font> 
1973诞生，1977 BSD诞生

<font size="4">**GNU**</font> 
- gcc 
- bash shell
- GNU的通用公共许可证：General Public License, GPL

<font size="4">**Linux**</font>
版本号： 
>3.10.0-123.el7.x86_64
>主版本.次版本.释出版本-修改版本

奇数、偶数版本分类:
>主、次版本为奇数：发展中版本（development） 如2.5.xx，这种核心版本主要用在测试与发展新功能，所以通常这种版本仅有核心开发工程师会使用。 如果有新增的核心程序码，会加到这种版本当中，等到众多工程师测试没问题后，才加入下一版的稳定核心

>主、次版本为偶数：稳定版本（stable） 如2.6.xx，等到核心功能发展成熟后会加到这类的版本中，主要用在一般家用计算机以及企业版本中。 重点在于提供使用者一个相对稳定的Linux作业环境平台。

>主线版本、长期维护版本:而旧的版本在新的主线版本出现之后，会有两种机制来处理，一种机制为结束开发 （End of Live, EOL），亦即该程序码已经结束，不会有继续维护的状态。 另外一种机制为保持该版本的持续维护，亦即为长期维护版本 （Longterm）！例如 3.10 即为一个长期维护版本，这个版本的程序码会被持续维护，若程序码有 bug 或其他问题， 核心维护者会持续进行程序码的更新维护喔！

>**從 Linux kernel 3.0 開始，已經捨棄奇數、偶數的核心版本規劃，新的規劃使用主線版本 (MainLine) 為依據， 並提供長期支援版本 (longterm) 來加強某些功能的持續維護。** 

**所以啰，如果你想要使用 Linux 核心来开发你的系统，那么当然要选择长期支持的版本才
行！要判断你的 Linux 核心是否为长期支持的版本， 可以使用“ uname -r ”来查阅核心版本，
然后对照下列链接来了解其对应值喔！**
- https://www.kernel.org/releases.html

Linux 核心版本与 Linux 发布商版本:
Linux核心版本与distribution （下个小节会谈到） 的版本并不相同，很多朋友常常上网问到：“我的Linux是7.x版，请问....”之类的留言， 这是不对的提问方式，因为所谓的Linux版本指的应该是核心版本， 而目前最新的核心版本应该是4.0.0（2015/04） 才对，并不会有7.x的版本出现的。
你常用的Linux系统则应该说明为distribution才对！因此，如果以CentOS这个distribution来说， 你应该说：“我用的Linux是CentOS这个 distribution，版本为7.x 版，请问....”才对喔！

<font size="4">**Linux distributions**</font>
好了，经过上面的说明，我们知道了Linux其实就是一个操作系统最底层的核心及其提供的核心工具。 他是GNU GPL授权模式，所以，任何人均可取得源代码与可执行这个核心程序，并且可以修改。 此外，因为Linux参考POSIX设计规范，于是相容于Unix操作系统，故亦可称之为Unix Like的一种。

为了让使用者能够接触到Linux，于是很多的商业公司或非营利团体， 就将Linux Kernel（含tools）与可运行的软件整合起来，加上自己具有创意的工具程序， 这个工具程序可以让使用者以光盘/DVD或者通过网络直接安装/管理Linux系统。 这个“Kernel + Softwares + Tools + 可完整安装程序”的咚咚，我们称之为Linux distribution， 一般中文翻译成可完整安装套件，或者Linux发布商套件等。

由于GNU的GPL授权并非不能从事商业行为，于是很多商业公司便成立来贩售Linuxdistribution。 而由于Linux的GPL版权宣告，因此，商业公司所贩售的Linux distributions通常也都可以从Internet上面来下载的！ 此外，如果你想要其他商业公司的服务，那么直接向该公司购买光盘来安装，也是一个很不错的方式的！

此外，為了讓所有的Linux distributions開發不致於差異太大，且讓這些開發商在開發的時候有所依據，還有**Linux Standard Base (LSB)** 等標準來規範開發者，以及目錄架構的**File system Hierarchy Standard (FHS)** 標準規範！ 唯一差別的，可能就是該開發者自家所開發出來的管理工具，以及套件管理的模式吧！ 所以說，基本上，每個Linux distributions除了架構的嚴謹度與選擇的套件內容外， 其實差異並不太大啦！ ^_^ 。大家可以選擇自己喜好的distribution來安裝即可！

事實上鳥哥認為distributions主要分為兩大系統，**一種是使用RPM方式安裝軟體的系統** ，包括Red Hat, Fedora, SuSE等都是這類； **一種則是使用Debian的dpkg方式安裝軟體的系統** ，包括Debian, Ubuntu, B2D等等。若是加上商業公司或社群單位的分類，那麼我們可以簡單的用下表來做個解釋喔！
![Linux distribution](/os_note/elementary_knowledge/picture/Linux%20distribution%20classify.png)



---
## 何为开源
常见开源协议：
- Apache License 2.0
- BSD 3-Clause "New" or "Revised" license
- BSD 2-Clause "Simplified" or "FreeBSD" license
- GNU General Public License （GPL）
- GNU Library or "Lesser" General Public License （LGPL）
- MIT license
- Mozilla Public License 2.0
- Common Development and Distribution Licens
####GNU GPL
free:"Free software" is a matter of liberty, not price. To understand the concept, you should think of "free speech", not "free beer". "Free software" refers to the users' freedom to run, copy, distribute, study, change, and improve the software

- 取得软件与源代码：你可以根据自己的需求来执行这个自由软件；
- 复制：你可以自由的复制该软件；
- 修改：你可以将取得的源代码进行程序修改工作，使之适合你的工作；
- 再发行：你可以将你修改过的程序，再度的自由发行，而不会与原先的撰写者冲突；
- 回馈：你应该将你修改过的程序码回馈于社群！


但请特别留意，你所修改的任何一个自由软件都不应该也不能这样：

- 修改授权：你不能将一个GPL授权的自由软件，在你修改后而将他取消GPL授权～
- 单纯贩卖：你不能单纯的贩卖自由软件。

---
## 应用场景
### 企業環境的利用
- 網路伺服器：
- 關鍵任務的應用(金融資料庫、大型企業網管環境)
- 學術機構的高效能運算任務
### 個人環境的利用
- Desktop
- 手持系統(PDA、手機)
- 嵌入式系統
### 雲端運用
- 雲程序
- 端設備

---
## Linux 特点与优势

网上查的，懒得写了 https://haicoder.net/linux/linux-feature.html#:~:text=Linux%E7%89%B9%E7%82%B9%EF%BC%9A%E5%BC%80%E6%94%BE%E6%80%A7%E3%80%81%E5%A4%9A%E7%94%A8%E6%88%B7%E3%80%81%E5%A4%9A%E4%BB%BB%E5%8A%A1%E3%80%81%E8%89%AF%E5%A5%BD%E7%9A%84%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2%E3%80%81%E8%AE%BE%E5%A4%87%E7%8B%AC%E7%AB%8B%E6%80%A7%E3%80%81%E4%B8%B0%E5%AF%8C%E7%9A%84%E7%BD%91%E7%BB%9C%E5%8A%9F%E8%83%BD%E3%80%81%E5%8F%AF%E9%9D%A0%E7%9A%84%E5%AE%89%E5%85%A8%E7%B3%BB%E7%BB%9F,%E5%92%8C%20%E8%89%AF%E5%A5%BD%E7%9A%84%E5%8F%AF%E7%A7%BB%E6%A4%8D%E6%80%A7%E3%80%82

---
##习题
####实作题
1. 最新稳定版（20221009）	5.19.14；发展中版本6.0
2. Linux企鹅名字：**Tux** 
3. 請上網找出 Andriod 與 Linux 核心版本間的關係：
https://zh.wikipedia.org/wiki/Android#Linux%E6%A0%B8%E5%BF%83

Android Version    |API Level  |Linux Kernel in AOSP
-------------------|-----------|--------------------
1.5   Cupcake      |3          |2.6.27
1.6   Donut        |4          |2.6.29
2.0/1 Eclair       |5-7        |2.6.29
2.2.x Froyo        |8          |2.6.32
2.3.x Gingerbread  |9, 10      |2.6.35
3.x.x Honeycomb    |11-13      |2.6.36
4.0.x Ice Cream San|14, 15     |3.0.1
4.1.x Jelly Bean   |16         |3.0.31
4.2.x Jelly Bean   |17         |3.4.0
4.3   Jelly Bean   |18         |3.4.39
4.4   Kit Kat      |19, 20     |3.10
5.x   Lollipop     |21, 22     |3.16.1
6.0   Marshmallow  |23         |3.18.10
7.0   Nougat       |24         |4.4.1
7.1   Nougat       |25         |4.4.1 (To be updated)

####簡答題部分：
1. 你在你的主機上面安裝了一張網路卡，但是開機之後，系統卻無法使用，你確定網路卡是好的，那麼可能的問題出在哪裡？該如何解決？ <font color=RED>因為所有的硬體都沒有問題，所以，可能出問題的地方在於系統的核心(kernel) 不支援這張網路卡。解決的方法，(1)到網路卡的開發商網站，(2)下載支援你主機作業系統的驅動程式， (3)安裝網路卡驅動程式後，就可以使用了。</font>
2. 一個作業系統至少要能夠完整的控制整個硬體，請問，作業系統應該要控制硬體的哪些單元？ <font color=BLUE>应该控制CPU、内存、外存、IO设备、显卡</font>  <font color=RED>根據硬體的運作，以及資料在主機上面的運算情況與寫入/讀取情況，我們知道至少要能夠控制： (1)input/output control, (2)device control, (3)process management, (4)file management. 等等！</font>
3. Linux本身僅是一個核心與相關的核心工具而已，不過，他已經可以驅動所有的硬體， 所以，可以算是一個很陽春的作業系統了。經過其他應用程式的開發之後，被整合成為Linux distribitions。請問眾多的distributions之間，有何異同？<font color=BLUE>不同：該開發者自家所開發出來的管理工具，以及套件管理的模式；相同：LSB和FHS，Linux核心，gcc等开源软件</font>
4. Unix 是誰寫出來的？ GNU 計畫是誰發起的？<font color=BLUE>Ken Thompson；Richard Mathew Stallman</font>
5. GNU 的全名為何？他主要由那個基金會支持？GNU's Not Unix；FSF
6. 何謂多人 ( Multi-user ) 多工 ( Multitask )？ Multiuser 指的是 Linux 允許多人同時連上主機之外，每個使用者皆有其各人的使用環境，並且可以同時使用系統的資源！Multitask 指的是多工環境，在 Linux 系統下， CPU 與其他例如網路資源可以同時進行多項工作， Linux 最大的特色之一即在於其多工時，資源分配較為平均！
7. 簡單說明 GNU General Public License ( GPL ) 與 Open Source 的精神：1. GPL 的授權之軟體，乃為自由軟體（Free software），任何人皆可擁有他； 2. 開發 GPL 的團體(或商業企業)可以經由該軟體的服務來取得服務的費用； 3. 經過 GPL 授權的軟體，其屬於 Open source 的情況，所以應該公布其原始碼； 4. 任何人皆可修改經由 GPL 授權過的軟體，使符合自己的需求； 5. 經過修改過後 Open source 應該回饋給 Linux 社群。
8. 什麼是 POSIX ?為何說 Linux 使用 POSIX 對於發展有很好的影響？ **POSIX 是一種標準規範，主要針對在 Unix 作業系統上面跑的程式來進行規範。**  若你的作業系統符合 POSIX ，則符合 POSIX 的程式就可以在你的作業系統上面運作。 Linux 由於支援 POSIX ，因此很多 Unix 上的程式可以直接在 Linux 上運作， 因此程式的移植相當簡易！也讓大家容易轉換平台，提升 Linux 的使用率。
9. 簡單說明 Linux 成功的因素？ 
    - 藉由 Minix 作業系統開發的 Unix like ，沒有版權的糾紛；
    - 藉助於 GNU 計畫所提供的各項工具軟體， gcc/bash 等；
    - 藉由 Internet 廣為流傳；
    - 藉由支持 POSIX 標準，讓核心能夠適合所有軟體的開發；
    - 托瓦茲強調務實，虛擬團隊的自然形成！