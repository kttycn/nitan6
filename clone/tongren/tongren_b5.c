#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "��Ѩͭ�ˡ���������Ğ��Ѩ" NOR, ({ "tongren b5", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + YEL "����һ����Ѩͭ�ˣ����������һЩ����Ѩλͼ�����Լ���Ѩʹ�÷�����\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "������");
        set("xuewei_name", "Ğ��Ѩ");
        set("chongxue_xiaoguo", "QI:500:MAR:50");
        set("neili_cost", "800");
        setup();
}
