#include <ansi.h>
#include <combat.h>

string name() { return HIM "С¥һҹ������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, md, ly;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("moon-blade", 1) < 200)
                return notify_fail("���Բ���䵶�������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("��û�м���Բ���䵶������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HBRED "С¥һҹ�����꣺Բ���䣬�������ݺ���ʮ������⺮��ѩ���δ������ꣿ\n" NOR
              HIY "ֻ��৵�һ����" + weapon->name() + HIY "�����ˣ�һ��ֻ����һ������ȥ���ݣ������������ѿ�����ĸ����£�\n"
              "$N" HIY "��һ������ʱ������Ҳ��ֱֱ�ģ��������ֱ��������һ��������Ȼ������һ������ĵ��⡣\n"
              "����ĵ�������ĵ��⣬��ʼʱ����һ�����£���Ȼ��ͱ����һ���ɺ硣��һ������ĵ�������ʱ��\n"
              + weapon->name() + HIY "�ϵ�����֮����ʹ��Ϊ֮��ѣ�Ի�\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        md = me->query_skill("moon-blade", 1);
        ly = target->query_skill("lonely-sword", 1);

        if (ap * 2 / 3 + random(ap) > dp )
        {
                damage = 0;
                if (me->query_skill("blade") > target->query_skill("force") &&
                    query("reborn/times", me) >= query("reborn/times", target) && random(md)>ly )
                {
                        me->start_busy(2);
                        addn("neili", -100, me);
                        msg += HIR "��$n" HIR "�е�$N" HIR "����ʱ��" + weapon->name() + HIR "���ѻӳ�����������ʱ���¹⣬�������ɵ��������$n��\n"
                               "$n" HIR "ֻ�е��������е��������������Ʊ�$N" HIR "�⾪�춯�ص�һ������һ˿��ʣ��һ������������\n"
                               "��������ɱ�ĺ���ζ����ֻ���������һ���죬�ǵ�����ĵ���ȴ���ڣ��������һת��Ȼ�������¹�ĵ�����ʧ�ˣ�\n"
                               "���е����������ţ����еĶ�����ͣ�١�$N" HIR "������һ˲ǰ��ô��������վ������������û�ж���������$N"
                               HIR "�����" + weapon->name() + HIR "�Ѿ��ڵ���Ѫ��\n" NOR;
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        addn("neili", -600, me);
                        damage = damage_power(me, "blade");
                        damage+= query("jiali", me);
                        damage*= 3;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                                   HIR "���$p" HIR "���ܲ�����ֻ����"
                                                   "һ�ɱ����ĵ����ӹ�ȫ����$nȫ����ʱ��Ѫ���죡\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -300, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
