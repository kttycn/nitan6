// powerup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me ) return notify_fail("你只能提升自己的战斗力。\n");
        if( query("neili", me)<100)return notify_fail("你的内力不够。\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        message_combatd(HIR"$N舌尖一咬，喷出一口鲜血，运起君临天下神功已将全身潜力尽数提起！\n" NOR, me);

        addn_temp("apply/attack", skill, me);
//        me->addn_temp("apply/dodge", skill);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
//                me->addn_temp("apply/dodge", - amount);
                delete_temp("powerup", me);
                tell_object(me, "你的君临天下神功运行完毕，将内力收回丹田。\n");
        }
}