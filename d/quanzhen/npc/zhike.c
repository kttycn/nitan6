// zhike.c ֪�͵���

inherit NPC;
//inherit F_MASTER;

string ask_me();
//string ask_for_join();
//int do_kneel();

void create()
{
        set_name("֪�͵���", ({"zhike daozhang","zhike"}));
        set("gender", "����");
        set("age", 42);
        set("class", "quanzhen");
        set("long",
                "����ȫ��̵��Ĵ��������������һλ����ǰ����С������\n"
                "���ϴ���������ʶ�㣬�����ݵ�ȫ�����¡��ƽ̼��������Ͼ�\n"
                "���ˣ��������������ϳ˹�����ϲ�������Ƶ�����ʶ��ڣ�\n"
                "�Ͱ�����ɽ�Ŵ�ר�½Ӵ��ÿ͡�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 18);
        set("int", 18);
        set("con", 20);
        set("dex", 21);

        set("qi", 500);
        set("max_qi", 500);
        set("jing", 350);
        set("max_jing", 350);
        set("neili", 900);
        set("max_neili", 900);
        set("jiali", 0);

        set("combat_exp", 20000);
        set("score", 15000);

        set_skill("array", 20);
        set_skill("force", 40);
        set_skill("xiantian-gong", 40);    //��������
        set_skill("sword", 40);
        set_skill("quanzhen-jian", 40);  //ȫ�潣
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 40);   //���㹦
        set_skill("parry", 50);
        set_skill("strike", 50);
        set_skill("haotian-zhang", 50);    //�����
        set_skill("cuff", 50);
        set_skill("chunyang-quan", 50);    //����ȭ
        set_skill("literate", 60);
        set_skill("taoism", 50);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("strike", "haotian-zhang");
        map_skill("cuff", "chunyang-quan");
        prepare_skill("cuff", "chunyang-quan");
        prepare_skill("strike", "haotian-zhang");

        create_family("ȫ���", 4, "����");

        set("book_count",1);
        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
                //"����"   :  (: ask_for_join() :),
                "����"   :  (: ask_me :),
                "ŷ����" :  (: ask_me :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/yellowrobe")->wear();
}

string ask_me()
{
        object me=this_player();
        set_temp("tmark/ָ", 1, me);
        return("ȥ����ʦ����������������������澭�������������ʦ��һ��ָ������������ĸ�󡹦��\n");
}

/*
void init()
{
        add_action("do_kneel", "kneel");
}

#include "qing.h"
*/