// jian-ke.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "jian ke","ke" }) );
        set("gender", "����");
        set("age", 45);
        set("long","����λ�������ˣ��米�����������Ľ������Ʈ������ƺ��������ա�\n");
        set("combat_exp", 20000);
        set("shen_type", -1);
        set("attitude", "heroism");

        set("apply/attack",  30);
        set("apply/defense", 30);

        set_skill("sword", 60);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);

        setup();

        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 20);
}

void init()
{
        object room, ob;
        string mengzhu;
        
        if(!( room = find_object("/d/taishan/fengchan")) )
        room = load_object("/d/taishan/fengchan");

        if( objectp(ob = present("mengzhu", room)) ) 
        mengzhu=query("winner", ob);

        if( query("id", this_player()) == mengzhu){
                message_vision(HIY "������$N����Ϊ��˵�������������˼Һã�\n" NOR, 
                this_player());
        }        
}