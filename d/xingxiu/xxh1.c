// Room: /d/xingxiu/xxh1.c
// Last Modified by winder on Apr. 25 2001

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "���޺�");
        set("long", @LONG
���������޺�����Բ�����ﶼ��һ���޼ʵĺ��������󣬵���
�����˳�֮Ϊ��������Ҳ��������ʪ�����深ֳ���������޵��ӳ�����
��׽���棬�Ա�����֮�á�����ͨ�����޺������
LONG
        );
        set("objects", ([
                __DIR__"npc/xxdizi"  : 1,
        ]) );
        set("exits", ([
                "south" : __DIR__"xxh",
                "north" : __DIR__"xxh2",
        ]));
        set("outdoors", "xingxiu");
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20200);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);

}
//#include "/d/xingxiu/xxh.h";