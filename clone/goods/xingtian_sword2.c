

// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
 
void create()
{
        set_name(HBGRN "刑天魔剑" NOR, ({ "xingtian sword", "sword" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "这便是刑天曾经使用的魔剑，剑体血光冲天。\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }     

        set("mod_mark", "A2034");
        set("mod_level", "M2030");
        set("mod_name", HBRED "刑天套装" NOR);
        init_sword(50000);
        set("quality_level", 3);
        
        setup();
}

