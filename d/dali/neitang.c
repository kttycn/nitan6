//Room: /d/dali/neitang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����");
        set("long", @LONG
�������������������á�ʮ�ֿ�������������ǽ�Ϲ���һ��ˮī
�������߸���һ�����ӣ�͸���������Կ����������ɽ��ˮ��
LONG );
        set("objects", ([
            CLASS_D("duan")+"/duanzc": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/yongdao2",
        ]));
	set("coor/x", -19091);
	set("coor/y", -6811);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}