// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "��÷԰"); 
        set("long", @LONG
������ǰ�÷԰�ˣ�ƽ����ʨ����ϲ�����������ߣ�˵��������
��÷�����ܾ�������Щ���飬ÿ���ʱ����������ƲƲ���죬��м����
һ���˵����ϴ��������Ǵ���ı��·���������װ������������Ե�
�����棬��Ψһ�����������͵Ķ������ǿ�������������ȥ��������
�ӵģ���������ʲô÷������Ȼ÷�����ǻ��������ǵ����Կ��ǿ��ǡ�
�����÷����ûʲô��������ֵ���������Ʈɢ��һ�����㡣
LONG );
        set("type","forest");
        set("outdoors", "wansong");
        set("exits",([
                "east":__DIR__"woshi1",
                "west":__DIR__"woshi",
                "north":__DIR__"chaifang",
        ]) );
        set("item_desc", ([
                "÷��": "÷����û�л��������϶���һ��С���ӣ���������ܾ�Զ�ˡ�\n",
                "tree": "÷����û�л��������϶���һ��С���ӣ���������ܾ�Զ�ˡ�\n",
                "����": "������д��-[..����....����]�����������Զ���м����ֿ������ˡ�\n",
                "paizi": "������д��-[..����....����]�����������Զ���м����ֿ������ˡ�\n"
        ]) );
        set("objects",([
                CLASS_D("mojiao/jinshi") : 1,
        ]) );
        
        set("coor/x",-590);
        set("coor/y",250);
        set("coor/z",80);
        setup();
} 

int dig_notify(object obj, int i)
{
        object me,jt;
        int qi;
        int max_qi;
        me = this_player();
        
        qi=query("qi", me);
        max_qi=query("max_qi", me);
        if (qi < max_qi/4) {
                message_vision("$N�����е�"+obj->name()+"����������ͻȻһ��ѣ��......\n" , me);
           me->unconcious();
        }
        else {
                message_vision("$N���е�"+obj->name()+"������Ӳ�ĵ��棬������������һ����\n" , me);
                me->receive_damage("qi",query("max_qi", me)/4);
                if (query("digged")) 
                {
                        message_vision("$N����������˰���ʲôҲû�ڵ���\n", me);
                        return 1;
                }
                else
                {
                        switch ( random(3) )
                        {
                          case 0: 
                                message_vision("$N���ֵ����ƺ��и���̳�ӡ�\n",this_player());
                                jt = new(__DIR__"obj/bottle");
                                jt->move(this_player());
                                set("digged",1);
                                message_vision("$N�������ӵ�"+obj->name()+"����æ����"+jt->name()+"�� \n",this_player());
                                destruct(obj);
                                break;
                          case 1:
                                message_vision("���ϵ�����$N����һ��,ûʲô���֡�\n",obj);
                                break;
                          case 2:
                                message_vision("�ϣ�����һ����$N���е�"+obj->name()+"���ˡ�\n",this_player());
                                destruct(obj);
                                break;
                        }
                 }
                 me->start_busy(3);
         }
         return 1; 
}    