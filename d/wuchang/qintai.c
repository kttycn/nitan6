//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "����̨");
        set ("long", @LONG
������������̨���ഫ����ս��ʱ�ڣ�������ʦ�Ხ��·��������
ҹ����������������������壬���������㻳���Է�������·��������
һ������ɽ��ˮ�����鲻�Խ��޵������������̩ɽ�������������ӡ���
��������֪������Ϊ���ˡ�������Լ���������һ�ۡ��ڶ��꣬���ڲ�
�Ҳ��ţ�������ʹ��������������Ĺǰ���ص�����ɽ��ˮ������������
��ˤ�飬����ʹ�ޡ�����Ϊ�˼��������ˤ��л֪�����Ĺ��£�������
����̨����̨����ʯ���Ͽ��в��������񡣱�����һ�����ܸ��ʵ�ͤ�ӡ�
LONG);
        set("outdoors", "wuchang");
        set("exits", ([ 
                "north" : __DIR__"qinguan",
                "west"  : __DIR__"hzjie3",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5080);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}