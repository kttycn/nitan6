// Code of JHSH
// wuzhuan.c ������ת

#include <ansi.h>

//inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int i, extra;

        if( query_temp("wuzhuan", me) )
                return notify_fail("���������á�������ת���ķ���\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("�����õ��ڹ��롸������ת���ķ���㣣�\n");

        if( me->query_skill("bibo-shengong", 1) < 100 )
                return notify_fail("����ڹ���Ϊ���δ������δ����������ת����\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������������ʩչ��������ת����\n");
        
        if( me->query_skill("qimen-wuxing", 1) < 120 )
                return notify_fail("�������������Ϊ��������δ����������ת����\n");

        msg = HIG "$N����������ʢ�����»������žŹ����Է�λ��ͷ��ð�����ڰ�����";
        msg += "��������������ӿ֮�����̲����ѷ��ӵ����£�\n"NOR;

        addn("neili", -200, me);
        
        extra = (int)me->query_skill("qimen-wuxing",1);
        addn_temp("apply/attack", extra/2, me);
        addn_temp("apply/defense", extra/2, me);
        addn_temp("apply/dodge", extra/30, me);

        set_temp("wuzhuan", 1, me);
        set_temp("wuzhuan_hit", extra/60+random(2), me);

        
        call_out("remove_effect", extra/2, me, extra);

        message_vision(msg, me);

        return 1;
}

void remove_effect(object me, int extra)
{
        if (!me) return;

        addn_temp("apply/attack", -extra/2, me);
        addn_temp("apply/defense", -extra/2, me);
        addn_temp("apply/dodge", -extra/30, me);

        delete_temp("wuzhuan_hit", me);
        delete_temp("wuzhuan", me);
        message_vision(CYN"$Nֻ��������ת���������ò�������������Ϣ���ɡ�\n"NOR,me);
}