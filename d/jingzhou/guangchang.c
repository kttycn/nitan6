inherit ROOM;

void create()
{
        set("short", "��������" );
        set("long", @LONG
�����Ǿ��ݵ�����Ҫʮ��·�ڣ������������������֣��ϱ�ס��
һЩ���ǵĸ��ˣ������ǹٸ�������һ���õط�����������Ĵ�����
�˶��ڴ���ţ���Ϣ�Ժ��ٸ�·��
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
                "south" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}