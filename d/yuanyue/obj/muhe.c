// This program is a part of NITAN MudLIB

inherit ITEM;

void create()
{
        set_name("ľ����", ({ "woodbox", "ľ����" }) );
        set_weight(500);        
        set_max_encumbrance(2000);      
        set("prep","on");        
        if( clonep() )                
                set_default_object(__FILE__);        
        else 
        {
                set("unit", "��");
                set("long", "��Сľ�������ǻҳ���ճ����úм��ݣ����ƺ����԰����򿪣�������\n");
                set("value", 100);
                set("closed", 1);
        }
        setup();
} 
int is_container() 
{ 
        return 1; 
} 
void init()
{
        if(this_player()==environment())
                 add_action("do_open","open");
}
int do_open(string arg)
{
        object  me, ob;
        if( !arg || arg != "woodbox" )
                return notify_fail("��Ҫ��ʲô��\n");
        me = this_player();
        ob = this_object();
        if( !query("closed", ob) )
                return notify_fail("ľ�����Ѿ����ˣ�\n");
        message_vision("$NС��������$n��\n", me, ob);
        set("closed", 0, ob);
        return 1;
} 
int is_closed()
{
        return (query("closed", this_object()));
}    