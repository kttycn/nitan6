// trunk.c
// Modified by haiyan

inherit ITEM;

void create()
{
        set_name("����֦", ({ "trunk" }));
        set_weight(1200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���������Ͽ���������֦�����԰���������ľ����\n");
                set("value", 0);
                set("material", "bamboo");
        }
}

void init()
{
        if (this_player() == environment())
        {
            add_action("do_make", "zao");
            add_action("do_make", "zuo");
            add_action("do_make", "xiao");
        }
}

int do_make(string arg)
{
        object me, weapon;
        object where, sword;
        me = this_player();
        weapon=query_temp("weapon", me);
        if (! arg || ! id(arg))
             return notify_fail("��Ҫ��ʲô������\n");

        if (! objectp(weapon))
             return notify_fail("�㲻�ù��߾���������\n");

        if( query("skill_type", weapon) != "dagger" )
             return notify_fail(weapon->name()+"����������̫˳�֡�\n");

        where = environment(me);
        message_vision("$N�������е�" + weapon->name() +
                       "�����¾Ͱ�����֦������һ�ѽ�����������һЩ�����ķ��š�\n", me);
        sword = new("/d/wudang/quest/obj/ghost_sword");
        sword->move(me);
        destruct(this_object()); 
        return 1;
}