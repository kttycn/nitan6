//Room: majiu1.c ����
//Date: Oct. 2 1997 by That

#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","����");
        set("long",@LONG
����������͵������ǣ����깩Ӧ���ʲ��ϡ������Թźų����ã�
���ݵĿ͵�㼯�ĺ����͡������ǻ����ǣ�����Ǻ����տ���������ι��
���㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿�����·�����������µ���ľ����
����һ����ľ��(paizi)��
    �����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
        set("outdoors", "xihu"); 
        set("no_fight", "1");
        set("no_beg", "1");
        set("objects", ([
                "/d/city/npc/zaohongma": 1,
                "/d/city/npc/huangbiaoma": 1,
                "/d/city/npc/ziliuma": 1,
                "/clone/misc/mafu": 1,
        ]));
        set("item_desc", ([
                "paizi": @TEXT
������ֻҪ������һ�����������Ϳ��Թ͵�һƥ���ˡ�

ǰ��        ���ݳ�:  rideyz


TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian",
                "north" : __DIR__"business",
                "up"   : SHOP_DIR"hangzhou_shop",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 850);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}