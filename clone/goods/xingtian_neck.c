// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit NECK;
 
void create()
{
        set_name(HBGRN "��������" NOR, ({ "xingtian neck", "neck" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "��������������������ͨ��Ѫ�����졣\n" NOR);
                set("value", 3000); 
                set("no_sell", "����������������\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("armor_prop/armor", 10);
        }
        
        set("mod_mark", "A2030");
        set("mod_level", "M2030");
        set("mod_name", HBRED "������װ" NOR);
        set("quality_level", 3);

        setup();
}
