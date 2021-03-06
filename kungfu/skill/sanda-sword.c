// This is player's own skill (Write by Lonely@nt2)
//Createby虚宁(Ningbufan)atSun May  8 00:28:05 2011
// 三达剑(sanda-sword.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N目无表情，手握$w,似瞒不经心却又准确无误的往$n的$l斜斜刺出一剑",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "刺伤",
	"skill_name" : "智剑平八方"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        object weapon; 
        
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练" + "三达剑" + "。\n");
                
        return 1;
}

int valid_enable(string usage) { 
        return usage == "sword" || 
               usage == "parry"; 
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
        level = (int)me->query_skill("sanda-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("sanda-sword", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        object weapon; 
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");        
        
        if( query("qi", me)<25 )
                return notify_fail("你的体力不够了，休息一下再练吧。\n");
                
        if( query("neili", me)<3 )
                return notify_fail("你的内力不够了，休息一下再练吧。\n");
                
        me->receive_damage("qi", 25);
        addn("neili", -3, me);
        return 1;
} 

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str()) 
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "你听到「喀嚓」一声轻响，已被$N的兵器所发杀气挫伤，$n顿时血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "sanda-sword" + "/" + action; 
}
string query_description()
{
	return
 "华山武学最高乃是三达剑，宁不凡18岁便学成三达剑之一的“智剑平八方”，
以稚龄崛起于江湖，武功天分之高，悟性之高，乃是千载难逢的人才。之
后的宁不凡以晚辈身份向当时就已名噪江湖的九州剑王方子敬切磋。结果
却战胜方子敬，逼得方子敬弃剑从刀。从此之后，武功更是成为天下第一" ; 
}
