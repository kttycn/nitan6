#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ���·�ɶ���ɽ���쳣���С�����
���£�Ȼ����ɽ������ɽ�ѣ�Ҳ�����ú��ߣ���֮����������·�Ϸ�
Ҫ����С�ģ��þ�ȫ���������С�����һ�������;��ý�ƣ�����ˡ�
LONG );
        set("exits", ([
                  "westup" :  __DIR__"shudao18",
                  "eastdown" : __DIR__"shudao16",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15140);
	set("coor/y", -1830);
	set("coor/z", -10);
	setup();
}

int init()
{
        object me;
        int i;
        me = this_player();
    i=query("max_qi", me)/50;
        me->receive_damage("qi", i);
        tell_object(me, HIR "���������������ϣ��۵�����������\n" NOR);
}