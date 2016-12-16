#include <ansi.h>
inherit SKILL;

mapping *action = ({
([        "action" : "$Nһ�С���ɫ���������������ɻ��Σ�����$n��$l",
        "force" : 60,
        "attack": 2,
        "parry" : 1,
        "damage": 2,
        "lvl"   : 0,
        "skill_name" : "��ɫ����",
        "damage_type" : "����"
]),
([        "action" : "$Nһ�С��߲����𡹣�����߸�Ծ������$n��$l��"
                   "��һ������",
        "force" : 80,
        "attack": 8,
        "parry" : 3,
        "damage": 4,
        "lvl"   : 20,
        "skill_name" : "�߲�����",
        "damage_type" : "����"
]),
([        "action" : "$Nһ�С����ӭ��ϼ������Ȼ����˫��զ�֣��ֱ��"
                   "�����������빥��$n",
        "force" : 100,
        "attack": 12,
        "dodge" : 43,
        "damage": 6,
        "lvl"   : 30,
        "skill_name" : "���ӭ��ϼ",
        "damage_type" : "����"
]),

([        "action" : "$Nһ�С�Ⱥɽ�����ա�,ͷ�������£��ƺ��Ե�û����"
                   "�ɣ�һ�����������������$n",
        "force" : 130,
        "attack": 15,
        "dodge" : 55,
        "damage": 8,
        "lvl"   : 40,
        "skill_name" : "Ⱥɽ������",
        "damage_type" : "����"
]),
([        "action" : "$Nһ�С����Ĺ����𡹣�ͻȻ�������࣬����һֻ�ڿ�"
                   "�������ķ�����һ������$n",
        "force" : 150,
        "attack": 22,
        "dodge" : 52,
        "damage": 14,
        "lvl"   : 60,
        "skill_name" : "���Ĺ�����",
        "damage_type" : "����"
]),

([        "action" : "$N˫��ƽ�ӣ�һ�С�ڤڤ���оۡ��������ݼ�ת����Ȼ"
                   "��������һ������$n��$l",
        "force" : 180,
        "attack": 23,
        "dodge" : 65,
        "damage": 25,
        "lvl"   : 80,
        "skill_name" : "ڤڤ���о�",
        "damage_type" : "����"
]),
([        "action" : "$Nһ�С�����������������һֻչ�᰿��Ĵ���������"
                   "����Ϯ��$n",
        "force" : 210,
        "attack": 20,
        "dodge" : 63,
        "damage": 40,
        "lvl"   : 100,
        "skill_name" : "��������",
        "damage_type" : "����"
]),

([        "action" : "$N������Σ�����һ�ǡ������˼䡹�͵ز���$n��$l",
        "force" : 240,
        "attack": 18,
        "dodge" : 77,
        "damage": 50,
        "lvl"   : 120,
        "skill_name" : "�����˼�",
        "damage_type" : "����"
]),
([        "action" : "$Nʩ������ʯΪ������˫�Ʋ��Ϸ�ת�����ز�£����ֱ"
                   "����$n��$lϮȥ",
        "force" : 260,
        "attack": 21,
        "dodge" : 80,
        "damage": 60,
        "lvl"   : 140,
        "skill_name" : "��ʯΪ��",
        "damage_type" : "����"
]),
([        "action" : "$Nʩ�������ڹ��ġ���˫�Ʒ��ڲ�Ϣ��������ľ���$n",
        "force" : 280,
        "attack": 25,
        "dodge" : 81,
        "damage": 80,
        "lvl"   : 160,
        "skill_name" : "���ڹ���",
        "damage_type" : "����"
])
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("�������̫�����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chilian-shenzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĳ������ơ�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("chilian-shenzhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<60 )
                return notify_fail("��������������������ơ�\n");

        me->receive_damage("qi", 61);
        addn("neili", -53, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chilian-shenzhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chilian-shenzhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "name"  : "�������ƶ�",
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "��Ȼ����һ����Ϯ��������һ�Σ�ͷ��΢΢��Щ���衣\n" NOR;
        }
}