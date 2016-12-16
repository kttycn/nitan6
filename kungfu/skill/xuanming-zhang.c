// create by rcwiz 2003 for yanhuang online 

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$Nʹ��һ�С�ѩ��ãã����˫�ƶ�Ȼ����������˿˿�������$n��$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "ѩ��ãã",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��һ�С���ڤ��ɽ�������ƻ��أ��������Ĵ��ż���֮������$n��$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 20,
        "lvl"   : 30,
        "skill_name" : "��ڤ��ɽ",
        "damage_type" : "����"
]),
([      "action" : "$N�ֽ�һ����һ�С�����ŭ�š���˫������ǵذ�����$n��$l",
        "force" : 160,
        "attack": 45,
        "dodge" : 20,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 60,
        "skill_name" : "����ŭ��",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�ա�������硹��˫���ĳ��������磬��Ȼ����������Ϣ������$n��$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 80,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$N����һԾ��һ�С�������ԭ�������ƿ�����������$n��$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "lvl"   : 100,
        "skill_name" : "������ԭ",
        "damage_type" : "����"
]),
([      "action" : "$N��Цһ����һ�С���ɽ��������˫��һ�������ƺ�Ȼ�������߻���$n��$l",
        "force" : 280,
        "attack": 95,
        "dodge" : 25,
        "parry" : 25,
        "damage": 55,
        "lvl"   : 120,
        "skill_name" : "��ɽ����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�ѩԭ���¡������μ��Σ�һԾ����$n��ǰ�����ƴ��ų��캮������$n��$l",
        "force" : 320,
        "attack": 110,
        "dodge" : 30,
        "parry" : 30,
        "damage": 70,
        "lvl"   : 140,
        "skill_name" : "ѩԭ����",
        "damage_type" : "����"
]),
([      "action" : "$N���쳤Х��һ�С�������ڤ����˫���Ʒ���ǧ�Ų����ĺ���������$n��$l",
        "force" : 360,
        "attack": 135,
        "dodge" : 30,
        "parry" : 35,
        "damage": 95,
        "lvl"   : 150,
        "skill_name" : "������ڤ",
        "damage_type" : "����"
]),
([      "action" : "$N������Ȼһ�䣬ʹ��һʽ������ڤڤ������Ӱǧ����ã���$n�޷�����",
        "force" : 420,
        "attack": 150,
        "dodge" : 30,
        "parry" : 75,
        "damage": 110,
        "lvl"   : 160,
        "skill_name" : "����ڤڤ",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����Х��һʽ�������������˫��Я������ű���ֱֱ����$n",
        "force" : 450,
        "attack": 185,
        "dodge" : 40,
        "parry" : 80,
        "damage": 160,
        "lvl"   : 180,
        "skill_name" : "�������",
        "damage_type" : "����"
])
});

int valid_enable(string usage)
{
        return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
        if( query("character", me) == "��������" )
                return notify_fail("�����а��룺��Ϊ�˹������䣬����ѧϰ���������书��\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����ڤ���Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹����޷���ϰ��ڤ���ơ�\n");

       if( query("con", me)<30 )
                return notify_fail("��������ǲ��㣬�޷�������ڤ���ơ�\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("�������̫�����޷���ϰ��ڤ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("��Ļ����Ʒ���򲻹����޷�����ڤ���ơ�\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < (int)me->query_skill("xuanming-zhang", 1))
                return notify_fail("�����ڤ��ˮƽ���ޣ��޷������������ڤ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xuanming-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ڤ���ơ�\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("xuanming-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("con", me)<30 )
                return notify_fail("��������ǲ��㣬�޷�������ڤ���ơ�\n");

        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<100 )
                return notify_fail("���������������ڤ���ơ�\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("xuanming-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 240 || ! damage_bonus ||
            me->query_skill_mapped("force") != "xuanming-shengong" ||
            query("neili", me)<300 )
                return;

        if (flvl * 5 / 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xuanming_poison",
                              ([ "level" : flvl * 3,
                                 "id":query("id", me),
                                 "duration" : lvl / 40 + random(lvl / 20) ])))
        {
                addn("neili", -100, me);
                return HIW "$n" HIW "��Ȼ�е�һ��Ī���Ķ��ģ��������������ģ�ȫ��̱������Ƥ���ϡ�\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"xuanming-zhang/" + action;
}