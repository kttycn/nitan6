//bing2.c ���ٱ�
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIY "���ٱ�" NOR, ({"bing2", "erjubing"}));
        set("unit", "��");
        set("long", "����һ������Ķ��ٱ���\n");
        set("no_get", 1);
        set("no_drop", 1);
        set("no_put", 1);
        set("no_beg", 1);
        set("no_steal", 1);
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
        if( query("owner") != query("id", me) )
        {
                write(HIR"��ֻ�ܳ��Ը�Ӯ���ı���\n"NOR);
                return 1;
        }
        if(arg=="bing2"||arg=="erjubing")
        {
                addn("combat_exp", 168, me);
                addn("potential", 68, me);
                message_vision(HIY "$N�������ڳ���һ��$n��\n" NOR, this_player(), this_object());
                destruct(this_object());
        }
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}