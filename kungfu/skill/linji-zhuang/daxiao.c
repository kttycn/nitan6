
// daxiao.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int amount;

        if (level < 150) return notify_fail("你的临济十二庄修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你现在气血受伤，只怕无法调节精气平衡！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你现在精神受伤，只怕无法调节精气平衡！\n");

        if( query_temp("linji/daxiao", me) )
                return notify_fail("你已经运功调节精气大小了。\n");

        set_temp("linji/daxiao", 1, me);
        write( HIY "你屏息静气，交错运行大小二庄，只觉一股暖流出天门，穿地户，沿着全身经脉运行一周，汇入丹田气海。\n" NOR);
        message_combatd(
                HIY + "只见" + me->name() + "屏息静气，头顶飘起一缕缕白气，神态略现疲乏。\n" NOR,
                me);

        amount=query("max_jing", me)-query("max_qi", me);
        amount /= 2;

        addn("max_qi", amount, me);
        addn("max_jing", -amount, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);

        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, amount :), 1800);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level, me);
        addn("max_jing", level, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);
        delete_temp("linji/daxiao", me);

        tell_object(me, HIG"你行大小二庄已久，又恢复了原有精气。\n"NOR);
}