// /guanwai/xuedi1.c

inherit ROOM;

#include "gwxuedi.h"

void create()
{
        set("short", "ѩ��");
        set("long", @LONG
������һƬ��ãã��ѩ�أ�һ���������߼ʡ�����һ����ӰҲû�У���
��Ļ�ѩ������������֨�����������������һ���¶��Ľ�ӡ������ı���
��Х��������������ʹ��������̫����������ߣ��Ե���ô�԰ס�
LONG );
        set("exits", ([
                "west"       : __DIR__"dongcheng",
                "northeast"  : __DIR__"xuedi2",
                "southeast"  : "/d/yubifeng/songlin1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 4010);
	set("coor/y", 9240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}