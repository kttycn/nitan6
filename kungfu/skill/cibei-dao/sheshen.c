// This program is a part of NITAN MudLIB
// sheshen.c 「舍身喂鹰」

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return "舍身喂鹰"; }
void remove_effect(object me, int a_amount, int d_amount);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("cibei-dao", 1) < 60)
                return notify_fail("你的慈悲刀法不够娴熟，不会使用「舍身喂鹰」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法使用「舍身喂鹰」。\n");

        if( query_temp("cbd_sheshen", me) )
                return notify_fail("你已经在运功中了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        skill = me->query_skill("cibei-dao", 1);
        msg = HIR "$N" HIR "使出慈悲刀法「舍身喂鹰」，将浑身的功力都运到" +
              weapon->name() + HIR "上！\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", -skill/5, me);
        set_temp("cbd_sheshen", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill / 3, skill / 5 :), skill / 4);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        if( query_temp("cbd_sheshen", me) )
        {
                addn_temp("apply/attack", -a_amount, me);
                addn_temp("apply/defense", d_amount, me);
                delete_temp("cbd_sheshen", me);
                tell_object(me, "你的「舍身喂鹰」运行完毕，将内力收回丹田。\n");
        }
}