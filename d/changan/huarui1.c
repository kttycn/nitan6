//Room: huarui1.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ
����ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ����ͷ�д�������Ʈ��
������ζ����Զ�������Ҽһ������׵����������д��˼�ե����
�Ĵ���ζ��·�������С���������ֳ�����ˣ�š�����
LONG );
        set("exits", ([
                "north" : __DIR__"majiu",
                "south" : __DIR__"minju1",
                "west" : __DIR__"yongtai-nankou",
                "east" : __DIR__"huarui2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}