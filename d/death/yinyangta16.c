#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "������" NOR);
        set("long", HIB @LONG
���ǵ�������ߵ�һ��������Լ������ߣ�����ʮ�˼����ഫ����
ס��������ȸ���������Ҳ��֪�����Ǽ١�
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta17",
              "down" : __DIR__"yinyangta15",
        ]));
        
        set("objects",([
        ]));
        
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}