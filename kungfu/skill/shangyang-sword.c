// six-fingers.c ������ - ������
#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([ "name":   "������",
           "action": "$Nʳָ����������԰ת������������һ����һ���Ĵ̳�������"
                     "Ѹ�٣����ɻ��ã������ݺᣬ�����ܹ����彣������·",
           "force":  340,
           "dodge":  100,
           "damage": 70,
           "damage_type":  "����"
        ]),
});

string main_skill() { return "six-finger"; }

int valid_enable(string usage) { return usage=="finger" ||  usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��������������֡�\n");

        if( query("max_neili", me)<2250 )
                return notify_fail("�������̫�����޷�ѧ��������\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("shangyang-sword", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��޷������������������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage;

        if ((int)me->query_skill("six-finger", 1))
                return notify_fail("���Ѿ�ѧ���������ˡ�\n");

        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<200 )
                return notify_fail("���������������������\n");

        me->receive_damage("qi", 40);
        addn("neili", -80, me);
        return 1;
}
                                          
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/4) > victim->query_str() )
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                return HIR "��������������һ�����죬���Ͼ�����һЩѪ�Σ�\n" NOR;
        }
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}