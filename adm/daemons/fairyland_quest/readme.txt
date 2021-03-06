*******************************************************
***** 『幻境·遥远传说之起缘·幽灵显现』 移植必读 *****
*******************************************************

奈何 10:46 05-8-29 更新如下：

    改名叫做 幻境2003(SP1) ，主要是为了和之前的第一版
幻境(hj2002)、第二版幻境(hj2003)、以及现正开发了50%的
第三版幻境(hj2005) 区分。

    所谓的 SP1 ，其实基本和 hj2003 没有什么大的改变，
主要是修正一个关于“no_refresh”标记的问题、以及把 
ctime_new() 方式更改为 ctime_format()方式。此外的代码
并没有任何优化和改变——一切更完善的设置，尽在2005版了。

    移植时，本目录应放置一个能保证 save_object() 权限
的目录下，例如 /adm/daemons/ 之类。

    有几个问题需要注意一下的：

    1、房间 no_clean_up, 物件 no_refresh 的问题。
       幻境系列都有特殊的要求，不允许被MUD底层隔段时间
    更新。所以，你必须保证这些物件能够长时间地驻留。

    2、log, data 目录问题。
       需要在 /log/ 及 /data/ 下建立 huanjing/ 目录，
    用以写入游戏日志及数据记录等。未有目录时，可能会发
    生权限错误。

    3、updated 丢失物件问题。
       一般来说，ES2 底层有个/adm/daemons/updated.c 的
    东东，当你身上携带物品过多时，它会随机给你丢一些。
    必须保证游戏主支持物件“七星灯”不会被丢弃！请自行
    更改。

    4、各类著作权问题。
       LPC 有什么版权可言，我自己的CODE就不谈这个了 -_-"
    而需要说明的是，游戏里使用了一幅漂亮的图片，就是在
    第 1号房间里的那张——这张图片摘自网络，来自：
             哈尔滨工业大学 TELNET BBS 字符版
    特此声明一下。
       而其它所有CODE，由奈何本人用记事本(汗)逐字写成。

    5、相关文件的问题。
       temp/ 里是一些旧的(没用了的)文件、或者游戏里使用
    的一些外部相关文件，如果你的MUD里没有一些 .h 之类的
    东东，可以来这里找到。
       而至于 hj_room_created.c 这个东西，应该不需要用
    到罢……

    6、游戏奖励问题。
       游戏奖励的函数写得很不好……但是这个版本已定，请
    各站自行更改罢。

    - naihe 奈何   2005.08.29 广东茂名
    - lovesb@21cn.com , lonely@163.com , QQ: 107507
    - hj2005 一再跳票，玩家怒火朝天，于是拉 2003 版出来顶着……

    - naihe 16:40 05-9-1
      注：在此基础上又进行了两次细节更新，修正细节十余处，
          版本号改为 hj2003 v1.2 而不再使用“SP1”的叫法。

*******************************************************


    以下是旧的说明：

可随意放置于任何目录内开放，不必作任何参数修改；
但务必保证所有文件无缺漏。

如果不是在神州里开放，也许会发生未知的
“贡献度”有关的错误，也许不会。


temp/  里的三个文件需要复制到对应目录。
  (1) get.c  主要是为了一些信息，无大碍
  (2) hj_room_created.c 是为了更改地图
      尺寸时快速生成地图文件的。
  (3) huanjing_pro_b.c  根据你的MUD目录，
      放置到例如： /clone/board/ 下，并
      且保证它里边的设置与你的幻境目录配合。


需要在 /log/ 下建立 huanjing/ 目录，
否则也许会出现本游戏不够权限新建目录的错误。

需要在 /data/ 下建立 huanjing/ 目录，
否则也许会出现本游戏不够权限新建目录的错误。

游戏内仅 入口 及 出口 两个地方使用了 save_object()
和 restore_object() 存储一些统计数据。如果和
所在MUD

查看MUD里的定时更新文件，例如 /adm/daemons/updated.c ,
加入判断句，以防止出现当玩家身上物品过多，而导致
丢失了七星灯的情况。其他obj允许被系统刷新。


“幽灵显现”里使用了一些字符图片，其中仅 "hj_room1.c"
的“月夜幽亭”图（名字由奈何暂定）是摘自网络。如有版权
纠纷等情况，奈何将于接到原作之抗议时，将其删除。
其他大小图片由奈何所绘。


其它的一些信息，请参阅 zreadme.txt。


本系列所有文件，皆由奈何以记事本逐字写成。

naihe 4:14 03-10-19 广东茂名
lovesb@21cn.com || lonely@163.com
*******************************************************
