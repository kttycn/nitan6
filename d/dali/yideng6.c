//Cracked by Kafei
// yideng6.c
// AceP

inherit ROOM;

int do_exert(string);
int do_pian(string);

void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
�������ʹ��ȫ�������ʯ������һ�����������Լ���ũ������
��վ��һ�������Թۣ�һ����������˼Ҳû�С�
LONG );
        set("invalid_startroom", 1);
        set("no_fight", "1");
    setup();
}

void init()
{
        object me;
        int i,j,k;
        i=5; k=0;
        me=this_player();
        while(i<85 && k <= query("jingli", me)){
                j=10+random(40);
                k=k+j;
                call_out("dropjingli", i, me, j);
                i=i+5;
        }
        remove_call_out("moveout");
        call_out("moveout", 90, me);
        add_action("do_exert", "exert");
        add_action("do_exert", "yun");
        add_action("do_pian", "pian");
}

void dropjingli(object me, int losejl)
{
      if (!me || environment(me) != environment()) 
              return; 
        if (environment(me)==find_object("/d/dali/yideng6.c")) {
                message_vision("$N�еþ��ˣ�ֻ�������۷��飬��ǰһ�������ð��\n",me);
                      losejl = 10+random(40);
                set_temp("die_reason", "����͸֧���ȶ�����", me);
                addn("jing", -losejl, me);
                return;
        }
}

void moveout(object me)
{
      if (!me || environment(me) != environment())  
              return;  
        if (environment(me)==find_object("/d/dali/yideng6.c")) {
                message_vision("$N��ǰһ�󷢺ڣ����ڼ�ֲ�ס�ˣ���һ�ɣ�����¡���� ... ...\n",me);
                me->unconcious();
                me->move("/d/dali/xiaodao2.c");
                return;
        }
}

int do_exert(string arg)
{
        tell_object(this_player(), "�������Ŵ�ʯͷ�أ���ô��������\n");
        return 1;
}

int do_pian(string arg)
{
        object me;
        me=this_player();
        if (arg=="nong" || arg=="wu santong" || arg=="farmer" || arg=="wu") {
                message_vision("$N�鼱���ǣ��󺰵��������壬�һ�����һ�����ү�Ӹ��λ�ү���ţ���\n",me);
                message_vision("����������һ�£�����ȡ�����㡣��\n",me);
                message_vision("�ȵ�ũ�������ʯ��$N����һ�ݣ����������ӹ��������ɽ��\n\n",me);
                me->move("/d/dali/yideng7.c");
                return 1;
        }
        return 1;
}