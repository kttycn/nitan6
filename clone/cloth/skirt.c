// skirt.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIG "��ɴ��ȹ" NOR, ({ "qingsha changqun", "skirt", "cloth"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ���������ʵ�ɴȹ������������һ�ɵ��㡣\n");
                set("unit", "��");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}

//int query_autoload() { return 1; }