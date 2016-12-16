// This program is a part of NT MudLIB

#include <ansi.h>
#include "xueshan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("�����", ({ "da erba", "da", "erba" }));
        set("long", @LONG
���ǽ��ַ������µĴ���ӡ���÷������洫��
����һ����ɫ���ģ�ͷ��ɮñ��
LONG);
        set("nickname", HIY "��շ�" NOR);
        set("gender", "����");
        set("class", "bonze");
        set("age", 38);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 35);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 3500);
        set("max_jing", 2500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("mizong-neigong", 180);
        set_skill("unarmed", 180);
        set_skill("longxiang-gong", 180);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("hammer", 180);
        set_skill("dali-chu", 160);
        set_skill("xiangmo-chu", 180);
        set_skill("hand", 160);
        set_skill("dashou-yin", 160);
        set_skill("cuff", 160);
        set_skill("yujiamu-quan", 160);
        set_skill("parry", 160);
        set_skill("lamaism", 180);
        set_skill("literate", 100);
        set_skill("sanscrit", 200);
        set_skill("martial-cognize", 160);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "xiangmo-chu");
        map_skill("hammer", "xiangmo-chu");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.zhen" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }));

        create_family("ѩɽ��", 3, "���");

        set("inquiry", ([
                "�������" : (: ask_skill1 :),
                "�����"   : (: ask_skill2 :),
        ]));

        set("master_ob", 3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "����" )
        {
                command("say ��ϰ�����ڹ���Ҫ����֮�壬�㻹���߰ɡ�");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say ����ѩɽ��ֻ�ճ��ҵ��ӣ��㻹����ذɡ�");
                return;
        }

        if( query("shen", ob)>-3000 )
        {
                command("say �Ҵ�������������ʿ�򽻵����㻹���߰ɡ�");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 50)
        {
                command("say ���ڹ���ô���ô���и�����似��");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 30)
        {
                command("say �ţ����пջ��Ƕ����������ķ��ɡ�");
                return;
        }

        command("say ����������Ժ�͸���������ɣ�");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/dali-chu/hong", me) )
                return "��������ʲô���Լ���ȥ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ���ʶ�㣬���������ʲô��";

        if (me->query_skill("dali-chu", 1) < 1)
                return "�������ϴ����ƶ�ûѧ�����������У�";

        if( query("family/gongji", me)<100 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-3000 )
                return "��Ϊ��̫��������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 120)
                return "����ڹ���Ϊ���㣬��ѧ������һ�С�";

        if( query("max_neili", me)<800 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("dali-chu", 1) < 80)
                return "��������ϴ������������������ҡ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ���ȵ���������"
                     "ϸ�ˡ����������䣬ֻ��$n" HIY "�߾����еĸ��ƣ���"
                     "���л�����̣����ƾ��ˣ����ڴ�ʱ���Ǳ�������Я��"
                     "������ײ��֮����Ȼ���䡣ֱ��$N" HIY "����Ŀ�ɿڴ�"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say �������˾��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������������\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("dali-chu"))
                me->improve_skill("dali-chu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dali-chu/hong", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/xiangmo-chu/zhen", me) )
                return "�Ҳ��������Լ���ȥ������ô�����ˣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ���ʶ�㣬���������ʲô��";

        if (me->query_skill("xiangmo-chu", 1) < 1)
                return "������ս�ħ�ƶ�ûѧ�����������У�";

        if( query("family/gongji", me)<200 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-6000 )
                return "��Ϊ��̫��������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 150)
                return "����ڹ���Ϊ���㣬��ѧ������һ�С�";

        if( query("max_neili", me)<1500 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("xiangmo-chu", 1) < 100)
                return "����ѽ�ս�ħ���������������ҡ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ���ȵ���������"
                     "���ˡ����������䣬ֻ��$n" HIY "�߾����еĸ��ƣ���"
                     "���л�����̣�����ׯ�ϣ�������ǧ����ʱ��ó�����"
                     "��Ӱ��������˷����¡���ʽ���棬����̾Ϊ��ֹ��\n"
                     "\n" NOR, me, this_object());

        command("nod");
        command("say ���п��Ƹ��ӣ���ʵ�����ѣ�����ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����衹��\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("xiangmo-chu"))
                me->improve_skill("xiangmo-chu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiangmo-chu/zhen", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}