// Room: /d/huanggong/gong5.c

inherit ROOM;

void create()
{
        set("short", "̫����");
        set("long", @LONG
�����������Ժ. ������һЩ��������, ����Ǻ�����Ů��ס��
�ط�. �����������������ܵ���ν��һ�빬�����ƺ���.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "east"  : __DIR__"tinglang3",
                "north" : __DIR__"gong3",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}