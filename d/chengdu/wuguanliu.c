// Room: wuguanliu.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "��ţ����Ĳ�");
        set("long", @LONG
�����ǡ���ţ��ݡ������Ĳ���ʦ���������������¼��ܣ�����
�Ṧ�������ڹ��������мܣ������Ʒ�������������
LONG );
        set("objects", ([
                __DIR__"npc/liuhongying" : 1,
        ]));
        set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"wuguan",
        ]));
        set("coor/x", -15200);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}