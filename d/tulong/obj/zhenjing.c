inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>; 
void setup()
{}
void init()
{
        add_action("do_du", "yanjiu");
        add_action("do_du", "research");
}
void create()
{
        set_name(HIY "��" NOR+HIW "�����澭" NOR+HIY "��" NOR, ({ "jiuyin zhenjing", "zhenjing"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW
        "����һ���ñ�ֽд�ɵ��顣������д�š������澭������Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n"
        "�澭������˴����ơ������׹�צ���׽�͹Ǻ������귭������������о��о���\n\n" NOR, );
        }
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        string skill, book;
        int lv;

        if(! arg)
        {
                write("�о������澭��ָ���ʽ��\n"
                      "research|yanjiu <����> from <�����澭>\n");
                return 1;
        }
        if(arg == "yijin-duangu" || arg == "shexing-lifan"  
        || arg == "cuixin-zhang" || arg == "jiuyin-baiguzhao" 
        || arg == "jiuyin zhenjing" || arg == "zhenjing"
        || arg == "yinlong-bian" )
        {
                write("�о������澭��ָ���ʽ��\n"
                      "research|yanjiu <����> from <�����澭>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        return 0;
        if( me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }
        if( me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }
        if( ! me->query_skill("literate", 1) )
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }
        if (! id(book))
        {
                write("����û���Ȿ�顣\n");
                return 1;
        }
        if ( skill != "yijin-duangu" && skill != "shexing-lifan"  
          && skill != "cuixin-zhang" && skill != "jiuyin-baiguzhao"
          && skill != "yinlong-bian" )
        {
                write(HIW "����ԴӾ����澭���о����׽�͹ǣ�yijin-duangu���������귭��shexing-lifan����\n"
                          "�����ƣ�cuixin-zhang���������޷� (yinlong-bian) �Լ������׹�צ��jiuyin-baiguzhao����\n\n" NOR,);
                return 1;
        }
        if( me->query_skill("sanscrit", 1) < 199)
        {
                write("�������ˮƽ̫�ͣ��޷������澭�������ص����ݡ�\n");        
                return 1;
        }
        if( query("combat_exp", me)<500000 )
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }
        if( query("jing", me)<101 || query("qi", me)<101 )
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        if ( skill == "yijin-duangu" )
        {
                lv = me->query_skill("yijin-duangu", 1);
                if( query("con", me)<30 )
                {
                        write("���ж���һ��������Ƿ����Լ�������ǲ��㣬һʱ����������\n");
                        return 1;
                }

                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
                }
                if( lv > 199) {
                        write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                        return 1;
                }
                message("vision", me->name() + "��ר�ĵ��ж������澭��\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("yijin-duangu",query("int", me)/4+1);
                write("����ϸ�ж������澭�����澭�������ص��׽�͹������ĵá�\n");
                return 1;
        }
        if ( skill == "shexing-lifan" )
        {
                lv = me->query_skill("shexing-lifan", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
                }
                if( lv > 199) {
                        write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                        return 1;
                }
                message("vision", me->name() + "��ר�ĵ��ж������澭��\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("shexing-lifan",query("int", me)/4+1);
                write("����ϸ�ж������澭�����澭�������ص������귭�Ṧ�����ĵá�\n");
                return 1;
        }
        if ( skill == "cuixin-zhang" )
        {
                lv = me->query_skill("cuixin-zhang", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
                }
                if( lv > 199) {
                        write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                        return 1;
                }
                message("vision", me->name() + "��ר�ĵ��ж������澭��\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("cuixin-zhang",query("int", me)/4+1);
                write("����ϸ�ж������澭�����澭�������صĴ����������ĵá�\n");
                return 1;
        }
        if ( skill == "jiuyin-baiguzhao" )
        {
                lv = me->query_skill("jiuyin-baiguzhao", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
                }
                if( lv > 199) {
                        write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                        return 1;
                }
                message("vision", me->name() + "��ר�ĵ��ж������澭��\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("jiuyin-baiguzhao",query("int", me)/4+1);
                write("����ϸ�ж������澭�����澭�������صľ����׹�צ�����ĵá�\n");
                return 1;
        }
        if ( skill == "yinlong-bian" )
        {
                lv = me->query_skill("yinlong-bian", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
                }
                if( lv > 199) {
                        write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                        return 1;
                }
                message("vision", me->name() + "��ר�ĵ��ж������澭��\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("yinlong-bian",query("int", me)/4+1);
                write("����ϸ�ж������澭�����澭�������ص������޷������ĵá�\n");
                return 1;
        }
}
