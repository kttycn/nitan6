#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���ҷ�");
        set("long", @LONG
�������䵱��ʮ����֮��������죬ľʯ���棬�ͱ�������
����֮������һ���������Ԩ�����̺ƴ󡣹�ǰ��һʯ�������ͱ�
�Ϻ����
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/mo": 1,
        ]));

        set("exits", ([
                "eastdown" : __DIR__"langmeiyuan",
                "southdown": __DIR__"shizhu",
                "west"     : __DIR__"sheshenya",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -360);
        set("coor/y", -320);
        set("coor/z", 110);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "�䵱��")
           && dir == "southdown"
           && objectp(present("mo shenggu", environment(me))))
                return notify_fail(CYN "Ī������ס��˵���˴��˱��ɽ�"
                                   "�أ���ֹ����\n" NOR);

        return ::valid_leave(me, dir);
}