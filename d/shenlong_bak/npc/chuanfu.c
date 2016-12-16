// chuanfu.c �ϴ���

#include <ansi.h>

inherit NPC;

int  chu_hai();
void goto_dao(object ob);

void create()
{
        set_name("�ϴ���", ({ "lao chuanfu","chuanfu","lao" }));
        set("gender", "����");
        set("age", 56);
        set("long","����һ���ϴ��򡣱�����˪������͸��һ˿�ƻ�����������������ǰ����\nȥ����������������ӵ��һ�Ҵ󴬿��Գ�����\n");
        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("eff_qi",2000);
        set("qi",2000);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 100);

        set_skill("force", 200);
        set_skill("unarmed", 400);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set("inquiry", ([
                "������" : "����������һ�����ˣ�ǧ����ȥ��\n",
                "����" :   (: chu_hai :),
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
 }

int chu_hai()
{
        object myenv, ob = this_player ( ) ;
        if( query("party/party_name", ob) == HIY"������"NOR )
        {
                message_vision("�ϴ���һ���֣������������ᴬ��\n",ob);
                message_vision("���ᴬ���$N���˴���һ������ê�����Ϳ����ˣ����ϴ���ȴû�ϴ�......\n", ob);
                myenv = environment (ob) ;
                ob->move ("/d/shenlong/dahai");
                tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�.......\n" NOR ) ;
                call_out("goto_shenlong",10,ob) ;
                       return 1;
        }
        else
                message_vision("�ϴ����������´�����$Nһ�£�ʲô���������㲻Ҫ���ˣ���\n�ϴ���������һ�£�����...�������һ�����ӣ��������Կ��ǡ�\n", ob);
        set_temp("����", 1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( !query_temp("����", who) )
        {
                message_vision("�ϴ���Ц�Ŷ�$N˵���޹�����»���������Լ����Űɣ�\n", who);
                return 0 ;
        }
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("�ϴ����$N˵���ã���Ȼ��λ" + RANK_D->query_respect(who) + "��˿������ң�\n����Ҳƴ�������ƴ�����������ӱ��ˣ�\n" , who);
                delete_temp("����", this_player());
                message_vision("�ϴ���һ���֣������������ᴬ��\n", who);
                message_vision("���ᴬ���$N���˴���һ������ê�����Ϳ����ˣ����ϴ���ȴû�ϴ�......\n", who);
                myenv = environment (who) ;
                who->move ("/d/shenlong/dahai");
                tell_room(myenv, "�ϴ��򿴴����ˣ���������Ľ���Ц�ˣ�ȥ�������������������ҿɲ��ɡ�\nֻ��ϧ���Ǽ��������Ĵ���Ҫ���ǰ��˸��Ե��ˡ��ٺ٣�������\n") ;
                tell_object(who, BLU "���ں��Ϻ����˺ܾúܾ�.......\n" NOR ) ;
                call_out("goto_shenlong",10,who) ;
                       return 1;
        }
        else  message_vision("�ϴ�����ü��$N˵��������Ҳ̫���˰ɣ�\n", who);
        return 0;
}

void goto_shenlong (object ob)
{
        tell_object(ob , "������ͣ����һ��С���ߡ������´�����\n" ) ;
        ob->move ("/d/shenlong/beach") ;
}