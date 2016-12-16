// This program is a part of NT MudLIB
// itemd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>

void do_enchase_attack(object item, object me, object victim, int damage);
void create() { seteuid(getuid()); }

int gift_point() { return 1; }
// ����������͸����Ʒ�б�����������Ʒ��base_name
string *imbue_list = ({
        "/d/shenlong/obj/hua4",
        "/clone/gift/puti-zi",
        "/clone/gift/xiandan",
        "/clone/gift/xisuidan",
        "/clone/gift/jiuzhuan",
        "/clone/gift/tianxiang",
        "/clone/gift/xuanhuang",
});

// ����Ĵ�����������ޣ����ÿ��IMBUE�Ժ�ȡ0-IMBUE���������
// �����������ֵ����IMBUE���ճɹ���
#define RANDOM_IMBUE_OK         100

// ÿ�ν�����Ҫʥ���Ĵ���
#define SAN_PER_IMBUE           5

// ɱ�����Ժ�Ľ���
void killer_reward(object me, object victim, object item)
{
        int exp;
        mapping o;
        string my_id;

        if (!me || !victim)
                return;

        if( !query("can_speak", victim) )
                // only human does effect
                return;

        // record for this weapon
        if (victim->is_not_bad())  addn("combat/WPK_NOTBAD", 1, item);
        if (victim->is_not_good()) addn("combat/WPK_NOTGOOD", 1, item);
        if (victim->is_good())     addn("combat/WPK_GOOD", 1, item);
        if (victim->is_bad())      addn("combat/WPK_BAD", 1, item);

        if (userp(victim))
                addn("combat/PKS", 1, item);
        else
                addn("combat/MKS", 1, item);

        exp=query("combat_exp", victim);
        if( exp<10000 || query("combat_exp", me)<exp*4/5 )
                return;

        exp /= 10000;
        if (exp > 250) exp = 100 + (exp - 250) / 16; else
        if (exp > 50) exp = 50 + (exp - 50) / 4;
        my_id=query("id", me);
        o=query("owner", item);
        if (!o) o = ([ ]);
        if (!undefinedp(o[my_id]) || sizeof(o) < 12)
                o[my_id] += exp;
        else
        {
                // Too much owner, I must remove one owner
                int i;
                int lowest;
                string *ks;

                lowest = 0;
                ks = keys(o);
                for (i = 1; i < sizeof(ks); i++)
                        if (o[ks[lowest]] > o[ks[i]])
                                lowest = i;
                map_delete(o, ks[lowest]);
                o += ([ my_id : exp ]);
        }
        set("owner", o, item);

        if (my_id == item->item_owner() && !random(10))
                addn("magic/blood", 1, item);
}

// �ٻ���Ʒ
int receive_summon(object me, object item)
{
        object env;
        object temp;
        int type;

        if ((env = environment(item)) && env == me)
        {
                tell_object(me, item->name() + "������������"
                            "����ٻ���ʲô����\n");
                return 1;
        }

        if( query("jingli", me)<200 )
        {
                tell_object(me, "����ͼ����" + item->name() +
                            "���������Խ��뾳�磬�����Ǿ������á�\n");
                return 0;
        }
        addn("jingli", -200, me);

        if( query("id", me) == "lonely" )
        {
              message_sort(HIM "\nֻ�����ܽ��ɢ�������ƶ�䣬Զ���з�����ƣ�������Ϸ������"
                           "��������������$N"HIM"һ����Х��"+query("name", item)+HIM
                           "�ƿն��� ������\n\n" NOR, me);
        }
        else

              message_vision(HIW "$N" HIW "ͻȻ���һ��������������"
                             "һץ����Ȼ�����ܲ�������������\n\n" NOR, me);

        if (env == environment(me))
        {
                message_vision(HIW "ֻ�����ϵ�" + item->name() +
                               HIW "Ӧ�����𣬷�Ծ��$N" HIW
                               "�����У�\n\n" NOR, me);
        } else
        {
                type = random(3);
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        switch (type)
                        {
                        case 0:
                                message("vision", HIW "����д�������������"
                                        "����Ȼ����������" + item->name() +
                                        HIW "�ڿն���"
                                        "��ʧ������\n\n" NOR, env);
                                break;
                        case 1:
                                message("vision", HIC "һ�����������"
                                        "���ֶ���" + item->name() + HIC "��ֻ��" +
                                        item->name() + HIC "���������ƿն�"
                                        "�ߡ�\n\n" NOR, env);
                                break;
                        default:
                                message("vision", HIY "��Ȼ�������أ���������" +
                                        item->name() + HIY "�����ʵĶ������£�����һ"
                                        "�����ת˲������\n\n" NOR, env);
                                break;
                        }

                        if (interactive(env = environment(item)))
                        {
                                tell_object(env, HIM + item->name() +
                                                 HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                        }
                }

                switch (type)
                {
                case 0:
                        message_vision(HIW "һ��" HIR "����" HIW "��"
                                       "���绮�Ƴ��գ�" + item->name() + HIW
                                       "�������������$N" HIW "�����У�\n\n" NOR, me);
                        break;
                case 1:
                        if( query("id", item) == "lonely")break;

                        message_vision(HIW "һ��" HIY "����" HIW "ɨ��"
                                       "��գ�ֻ��" + item->name() + HIW
                                        "������$N" HIW "�����У�\n\n" NOR, me);
                        break;
                default:
                        message_vision(HIW "ֻ��" + item->name() + HIW "�������죬��"
                                       "����ʣ�Ю�ƴ�����ͻ����$N"
                                       HIW "�����У�\n\n" NOR, me);
                        break;
                }
        }

        // ȡ��no_get����
        delete_temp("stab_by", item);
        delete("no_get", item);

        item->move(me, 1);
        if (environment(item) != me)
                return 1;

        if( query("armor_type", item) )
        {
                // is armor
                temp = query_temp("armor/" + query("armor_type", item), me);
                if (temp) temp->unequip();
                WEAR_CMD->do_wear(me, item);
        } else
        if( query("skill_type", item) )
        {
                if( query("skill_type", item) == "throwing" )
                {
                        HAND_CMD->main(me,query("id", item));
                        return 1;
                }
                if( temp=query_temp("weapon", me) )
                        temp->unequip();
                if( temp=query_temp("secondary_weapon", me) )
                        temp->unequip();
                WIELD_CMD->do_wield(me, item);
        }

        return 1;
}

// ������Ʒ
int hide_anywhere(object me, object item)
{
        if( item->item_owner() != query("id", me) &&
            query("item_owner", item) != query("id", me) && query("owner", item) != query("id", me)) // ���������Ʒӵ��hide����
                return 0;

        if( query("jingli", me)<100 )
        {
                tell_object(me, "����ͼ��" + item->name() +
                            "��ȥ�����Ǿ������ã����Է�������������\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "����һ��" + item->name() +
                       HIM "����Ȼ�����ټ���\n", me);
        destruct(item);
        return 1;
}

// ׷Ѱ��Ʒ
int receive_miss(object me, object item)
{
        object env;

        env = environment(item);

        if (env == environment(me))
        {
                write("�����" + item->name() + "����ɶ��\n");
                return 0;
        }

        if (env == me)
        {
                write("������" + item->name() + "�����˰���Ĵ���\n");
                return 0;
        }

        if (!objectp(env) || userp(env) || environment(env))
        {
                write("����ͼ��Ӧ" + item->name() + "�����Ǹо��ǳ�����ã��\n");
                return 0;
        }

        if( !wizardp(me) && (!query("outdoors", env) || query("no_magic", env) ||
            query("maze", env)) )
        {
                write("ڤڤ�����Ӧ��" + item->name() + "�������ƺ����Ե������\n");
                return 0;
        }

        message("vision", me->name() + "������˼������֪��Ҫ��Щʲô��\n",
                environment(me), ({ me }));
        if( query("jingli", me)<400 )
        {
                write("�����" + item->name() + "�ĸо��൱"
                      "Ʈ���������������ã����Ը�Ӧ��\n");
                return 0;
        }

        // ���ľ���
        addn("jingli", -300-random(100), me);
        message_vision(HIM "$N" HIM "���������дʣ�ת˲���һ�����绮"
                       "����$N" HIM "�ݲʺ���ߡ�\n" NOR, me);
        tell_object(me, "��׷Ѱ" + item->name() + "��ȥ��\n");
        me->move(environment(item));
        message("vision", HIM "һ���ʺ绮����ʣ�" + me->name() +
                HIM "ƮȻ���£��������ɡ�\n" NOR, environment(me), ({ me }));
        tell_object(me, HIM "��׷Ѱ����" + item->name() +
                    HIM "�����¶ݹ⡣\n" NOR);
        return 1;
}

// ���ڵ���
int do_stab(object me, object item)
{
        if( query("no_magic", environment(me)) )
                return notify_fail("��������Ūʲô��\n");

        if (!item->is_weapon() && !item->is_unarmed_weapon())
                return notify_fail(item->name() + "Ҳ�ܲ��ڵ��ϣ�\n");

        if( !query("outdoors", environment(me)) &&
            !wizardp(me))
                return notify_fail("��������Ūʲô��\n");

        set("no_get", bind((:call_other,__FILE__,"do_get_item",item:),item), item);
        set_temp("stab_by",query("id",  me), item);

        message_vision(WHT "\n$N" WHT "���ֽ�" + item->name() + NOR +
                       WHT "������һ�壬��������㶡�һ�����졣\n\n" NOR, me);
        item->move(environment(me));
        return 1;
}

// ��ȡ��Ʒʱ���
mixed do_get_item(object item)
{
        object me;

        if (!objectp(me = this_player()))
                return 1;

        if( query("id", me) != query_temp("stab_by", item) &&
            query("id", me) != item->item_owner() )
                return "����ͼ��" + item->name() + "����ȴ"
                       "�������·�������������һ�㣬�޷�������\n";

        message_vision(HIW "\n$N" HIW "���ַ���" + item->name() +
                       HIW "��������ʱֻ�����͡���һ��������һ��"
                       "������\n\n" NOR, me);
        delete_temp("stab_by", item);
        delete("no_get", item);
        return 0;
}

// �������⹦��
mixed do_touch(object me, object item)
{
        string msg;
        object ob;
        object *obs;
        mapping my;

        if( query("id", me) != item->item_owner() ||
            (me->query_condition("killer") &&
            (query("no_fight", environment(me)) ||
            query("room_owner_id", environment(me)))) )
        {
                message_vision(HIR "\n$N���ᴥ��" + item->name() +
                               HIR "��ͻȻ��ȫ��һ��������������"
                               "���ܵ����\n" NOR, me);
                me->receive_damage("qi", 50 + random(50));
                return 1;
        }

        if( query("jingli", me)<100 )
        {
                set("jingli", 0, me);
                return notify_fail(CYN "\n������" + item->name() +
                                   CYN "���ã�����һ����̾��\n" NOR);
        }

        addn("jingli", -80-random(20), me);
        switch (random(3))
        {
        case 0:
                msg = CYN "\n$N" CYN "����һ��$n" CYN "������"
                      "��������������������\n" NOR;
                break;
        case 1:
                msg = CYN "\n$N" CYN "���ḧ��$n" CYN "������"
                      "��һ�ף�$n" CYN "�������죬���Ժ�֮��\n" NOR;
                break;
        default:
                msg = CYN "\n$N" CYN "��Ȼһ����̾���ḧ$n"
                      CYN "����˼���ã������п���ǧ��\n" NOR;
                break;
        }

        switch (random(3))
        {
        case 0:
                msg += HIM "��Ȼֻ��$n" HIM "����һ���⻪��"
                       "��Ծ����ɢ��ǧ�����롣\n" NOR;
                break;
        case 1:
                msg += HIM "����$n" HIM "һ�����������Ʋ���"
                       "��ֱ���뵽����ķ���ȥ��\n" NOR;
                break;
        default:
                msg += HIM "��ʱ��$n" HIM "��â���䣬������"
                       "����ʣ��Ƶ�������Ŀ�ӡ�\n" NOR;
                break;
        }

        msg = replace_string(msg, "$n", item->name());
        msg = replace_string(msg, "$N", "��");
        // message_vision(msg, me);
        tell_object(me, msg);

        if (random(1000) == 1 || wizardp(me))
        {
                obs = filter_array(all_inventory(environment(me)), (: userp :));
                foreach (ob in obs)
                {
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"] = my["max_jing"];
                        my["qi"]     = my["eff_qi"]   = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                        my["jingli"] = my["max_jingli"];
                        set_temp("nopoison", 1, ob);
                }
                tell_object(obs, HIC "��е�һ���º͵�����Ϯ��������"
                                "�������һ�㡣\n" NOR);
        } else
        if( query("neili", me)<query("max_neili", me) )
        {
                set("neili",query("max_neili",  me), me);
                tell_object(me, HIC "��ֻ��һ������������ȽȽ����"
                                "˵�����������\n" NOR);
        }
        if (me->is_fighting() && !me->is_busy())
                me->start_busy(10);
        return 1;
}

// ʥ����Ʒ
int do_san(object me, object item)
{
        string my_id;
        int count;
        int san;

        /*
        if( !query("skill_type", item) && query("armor_type", item) != "hands" )
        {
                // ��װ���ࣿ
                return notify_fail("װ�����ڻ��޷�ʥ��...\n");
        }
        */

        // �������ʥ��
        if( query("magic/power", item)>0 )
                return notify_fail("����" + item->name() + "������"
                                   "�Ѿ��õ��˳�ֵķ����ˡ�\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("����" + item->name() + "��Ǳ��"
                                   "�Ѿ�����ھ��ˣ�����ֻ����Ҫ��"
                                   "��һ���ںϡ�\n");

        my_id=query("id", me);

        count=sizeof(query("magic/do_san", item));
        if( query("magic/imbue_ob", item) )
                return notify_fail("����" + item->name() + "�Ѿ�����ֵ�ʥ"
                                   "���ˣ���Ҫ���������Խ�һ��ĥ����\n");

        if( query("magic/do_san/"+my_id, item) )
                return notify_fail("���Ѿ�Ϊ" + item->name() + "ʥ�����ˣ�"
                                   "�Ƿ����������޷�������ȫ���ա�\n��"
                                   "�б�ҪѰ�����˰����Լ���ʥ����\n");

        if (item->item_owner() == my_id)
        {
                if (!count)
                        return notify_fail("��Ӧ����Ѱ����λ����Э��������ʥ��" +
                                           item->name() + "��\n");

                if (count < SAN_PER_IMBUE - 1)
                        return notify_fail("��Ӧ����Ѱ��" +
                                           chinese_number(SAN_PER_IMBUE - 1 - count) +
                                           "λ��������ʥ��" + item->name() + "��\n");
        } else
        {
                if (count >= SAN_PER_IMBUE - 1)
                        return notify_fail("�����Ҫ��������Ϊ��ʥ��������������ˡ�\n");
        }

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("�����������������棬����óȻ���ã�\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("�����ھ������ã�����óȻ���ã�\n");

        if (me->query_skillo("force", 1) < 300)
                return notify_fail("����ڹ�����������ʵ������óȻʥ����\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("�㳢������һ���������޷�˳"
                                   "������һ�����죬����ʩչ���������\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");

        message_sort(HIM "$N" HIM "���ḧ��$n" HIM "����ָ�������ϣ�ͬ"
                     "ʱ��ת���������������澭\n����ԴԴ������������ע"
                     "��$n" HIM "��\n����ֻ����������$n" HIM
                     "����Ȼ�������������ܡ�\n" NOR, me, item);

        if( query("max_neili", me)<me->query_neili_limit()-400 )
        {
                if (random(2) == 1)
                {
                        // ����δ������
                        message_vision(HIR "$N" HIR "��ɫ��Ȼ���˱䡣\n" NOR,
                                       me);
                        tell_object(me, HIC "���Ȼ���õ�����Ϣ��Щ���ҡ�\n" NOR);
                } else
                {
                        message_vision(HIR "$N" HIR "��Ȼ�ƺ�һ������"
                                       "��ɲʱ�����죡\n" NOR, me);
                        tell_object(me, HIC "��е����������������δ����"
                                    "���������������������ڹ�������\n" NOR);
                        tell_object(me, HIC "��Ļ����ڹ��½��ˡ�\n");
                        me->set_skill("force", me->query_skillo("force", 1) - 10 - random(5));
                        return 1;
                }
        }

        // ͳ��IMBUE���Ĵ��������������㱾��MAX_NEILI/JINGLI������
        san=query("magic/imbue", item);

        addn("max_neili", -(san+5), me);
        addn("neili", -(san*10+100), me);
        addn("max_jingli", -(san*5+50), me);
        addn("jingli", -(san*5+50), me);
        set("magic/do_san/"+my_id, me->name(1), item);
        me->start_busy(1);

        if (item->item_owner() == my_id ||
            sizeof(query("magic/do_san", item)) == SAN_PER_IMBUE )
        {
                tell_object(me, HIW "������Ƭ�̣�����" + item->name() +
                            HIW "�ƺ��������ԣ���Ծ���ݣ�����΢΢һЦ��\n" NOR);
                message("vision", HIW + me->name() + HIW "��Ȼ"
                        "΢΢һЦ��\n" HIW, environment(me), ({ me }));

                if( !item->is_weapon() && !item->is_unarmed_weapon() && !query("magic/imbue", item) )
                {
                        set("magic/imbue_element", 1, item);
                        return 1;
                }

                // ѡ��һ����Ҫimbue����Ʒ
                set("magic/imbue_ob", imbue_list[random(sizeof(imbue_list))], item);
        }
        return 1;
}

// ��͸��Ʒ
int do_imbue(object me, object item, object imbue)
{
        if( query("magic/power", item)>0 )
                return notify_fail("����" + item->name() + "������"
                                   "�Ѿ��õ��˳�ֵķ����ˡ�\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("����" + item->name() + "��Ǳ��"
                                   "�Ѿ�����ھ��ˣ�����ֻ����Ҫ��"
                                   "��һ���ںϡ�\n");

        if( sizeof(query("magic/do_san", item))<SAN_PER_IMBUE )
                return notify_fail("������ȶ�" + item->name() +
                                   "���г�ֵ�ʥ�����С�\n");

        if( query("magic/imbue_element", item) )
        {
                if( !query("magic/element", imbue) )
                        return notify_fail(item->name() + "�������Ƚ�������������Ե���Ʒ��\n");
        }
        else
        {
                if( base_name(imbue) != query("magic/imbue_ob", item) )
                        return notify_fail(item->name() + "���ڲ���Ҫ��" +
                                           imbue->name() + "�����롣\n");
        }

        message_sort(HIM "$N" HIM "����һ����������������һ���˪��ֻ����ס$n" +
                     imbue->name() +
                     HIM "����Ȼ���ڻ������ģ���Ө��͸��$N"
                     HIM "����һ�ӣ���һ����Һ����$n" HIM
                     "�ϣ���ʱ������������������ʣ������˸��\n" NOR,
                     me, item);

        tell_object(me, "�㽫" + imbue->name() + "��Ч��������" +
                    item->name() + "��\n");
        delete("magic/do_san", item);
        delete("magic/imbue_ob", item);
        if( query("magic/imbue_element", item) )
                delete("magic/imbue_element", item);
        if( query("magic/element", imbue) )
                set("magic/type",query("magic/element",  imbue), item);
        if (imbue->query_amount())
                imbue->add_amount(-1);
        else
                destruct(imbue);
        me->start_busy(1);

        addn("magic/imbue", 1, item);
        if ((item->is_weapon() || item->is_unarmed_weapon())
         && (random(query("magic/imbue", item)) >= RANDOM_IMBUE_OK
         || query("magic/imbue", item) >= 150) )
        {
                        // ��͸���
                tell_object(me, HIG "���Ȼ�������е�" + item->name() +
                                HIG "��һ��ԾԾ���Եĸо����ƺ��ڴ���ʲô��\n" NOR);
                set("magic/imbue_ok", 1, item);
        } else
        if (!item->is_weapon() && !item->is_unarmed_weapon()
         && (random(query("magic/imbue", item)) >= RANDOM_IMBUE_OK/5
         || query("magic/imbue", item) >= 30) )
        {
                tell_object(me, HIG "���Ȼ�������е�" + item->name() +
                                HIG "��һ��ԾԾ���Եĸо����ƺ��ڴ���ʲô��\n" NOR);
                set("magic/imbue_ok", 1, item);
        }

        return 1;
}

// ��Ƕ��Ʒ
int do_enchase(object me, object item, object tessera)
{
        mapping ins;
        mapping data, enchase_prop, temp;
        string  *apply;
        string  str;
        object  obj;
        int     i, n, level, wash, addsn;

        if( query("equipped", item) )
                return notify_fail("���Ƚ��" + item->name() + "��װ����˵��\n");

        if( !query("enchase/flute", item) )
                return notify_fail(item->name() + "�ϲ�û�а��ۿ�������Ƕ��\n");

        if( query("enchase/used", item) >= query("enchase/flute", item) )
                return notify_fail(item->name() + "�ϵİ����Ѿ������ˡ�\n");

        /*
        if( query("magic/type", item) && query("can_be_enchased", tessera) )
                return notify_fail(item->name() + "���Ѿ�ӵ��������Ʒ�ˡ�\n");

        if( !item->is_weapon() && !item->is_unarmed_weapon() && query("can_be_enchased", tessera) )
                return notify_fail(tessera->name() + "ֻ����Ƕ�ڱ�����װ���ϡ�\n");
        */

        if( !tessera->is_tessera() || !mapp(query("enchase", tessera)) )
                return notify_fail(tessera->name() + "���ܷ���ħ����û�б�Ҫ��Ƕ��" + item->name() + "���档\n");

        if( query("magic/type", item) && query("magic/type", tessera) && query("magic/type", tessera) != query("magic/type", item) )
                return notify_fail(item->name() + "���Ѿ�ӵ�������������Ժ���Ƕ��������������Բ�һ�£��޷���Ƕ�ںϡ�\n");

        if( (level = me->query_skill("certosina", 1)) < 200 )
                return notify_fail("����������Ƕ���ջ�������죬����óȻ���֡�\n");

        if( tessera->is_rune() && query("enchase/rune" + query("enchase/SN", tessera), item) )
                return notify_fail(item->name() + "�ϵİ������Ѿ���Ƕ�˷���,����Ƕ�����ħ�Գ�ͻ��\n");

        if( !query("magic/type", item) && (item->is_weapon() || item->is_unarmed_weapon()))
        {
                if( !query("can_be_enchased", tessera) )
                if( query("enchase/used", item)+1 >= query("enchase/flute", item) )
                        return notify_fail(item->name() + "�ϵ�ʣ�µ�Ψһ�İ�����������Ƕ������������Ʒ��\n");
        }

        temp = query("enchase", tessera);
        if( undefinedp(temp["type"]) )
                return notify_fail(tessera->name() + "��ħ�����Բ��ʺ���Ƕ��" + item->name() + "�ϡ�\n");
        else
        {
                if (temp["type"] != "all" &&
                    temp["type"] != query("skill_type", item) &&
                    temp["type"] != query("armor_type", item) )
                        return notify_fail(tessera->name() + "��ħ�����Բ��ʺ���Ƕ��" + item->name() + "�ϡ�\n");
        }

        if( !tessera->is_rune() && !query("can_be_enchased", tessera) && temp["level"] != query("require/level", item) )
                return notify_fail(tessera->name() + "�ĵȼ����ʺ���Ƕ��" + item->name() + "�ϡ�\n");
        
        if( tessera->is_rune() && (query("armor_type", item) == "rings" || 
            query("armor_type", item) == "neck" || query("armor_type", item) == "charm") )
                return notify_fail("���Ĳ��ʺ���Ƕ��" + item->name() + "�ϡ�\n");
                
        if( level < 400 && random(level) < 180 && !(obj = present("enchase symbol", me)) )
        {
                message_vision(HIM "���á�������һ����ֻ��" + tessera->name() + HIM "ײ��$n" +
                               HIM "�ϣ�ƬƬ�ѿ���\n" NOR, me, item);
                tell_object(me, HIC "����Ƕ" + tessera->name() + CYN "ʧ���ˡ�\n" NOR);
                destruct(tessera);
                me->start_busy(1);
                return 1;
        }
        if( objectp(obj) ) destruct(obj);

        message_vision( HIM "���á�������һ����$N" HIM "��" + tessera->name() + NOR HIM"��Ƕ����$n" HIM "���棬\nֻ��$n"
                        HIM "���������Թ���һ������Ĺ�â���漴���ƽ����˵������ƽ����\n\n" NOR, me, item);
        tell_object(me, HIC "�����" + item->name() + HIC "�����˲��������ı仯��\n" NOR);

        if( query("can_be_enchased", tessera) )
        {
                //CHANNEL_D->do_channel(this_object(), "rumor", "��˵��Ʒ" + item->name() + HIM + "�������˼䡣");
                //set("magic/power",query("magic/power",  tessera), item);
                addn("magic/power",query("magic/power",  tessera), item);
                set("magic/type",query("magic/type",  tessera), item);
                set("magic/tessera", tessera->name(), item);
        }

        if( intp(query("enchase/wash", item)) )
                wash=query("enchase/wash", item);
        else
                wash = 0;

        addsn = 0;
        if (item->is_weapon() || item->is_unarmed_weapon())
        {
                if (wash >= 220) addsn = 4;
                else if (wash >= 180) addsn = 3;
                else if (wash >= 150) addsn = 2;
                else if (wash >= 50) addsn = 1;

                enchase_prop=query("enchase/weapon_prop", tessera);
        } else
        if( query("armor_type", item) == "rings" || query("armor_type", item) == "neck" || query("armor_type", item) == "charm" )
        {
                if (wash >= 100) addsn = 3;
                else if (wash >= 80) addsn = 2;
                else if (wash >= 30) addsn = 1;
                else if (wash < 15) addsn = -1;
                
                enchase_prop=query("enchase/rings_prop", tessera);
        } else
        {
                if (wash >= 100) addsn = 3;
                else if (wash >= 80) addsn = 2;
                else if (wash >= 30) addsn = 1;
                else if (wash < 15) addsn = -1;
                
                enchase_prop=query("enchase/armor_prop", tessera);
        }

        if (!mapp(enchase_prop)) enchase_prop = ([]);
        apply = keys(enchase_prop);
        /*
        if (tessera->is_rune())
                data=query("enchase/rune_prop", item);//���ĵ�ħ�������������
        else
        */
                data=query("enchase/apply_prop", item);

        if (!mapp(data) ) data = ([]);

        for (i = 0; i<sizeof(apply); i++)
        {
                if ( undefinedp(data[apply[i]]) )
                        data[apply[i]] = enchase_prop[apply[i]];
                else
                        data[apply[i]] += enchase_prop[apply[i]];
        }

        set("enchase/apply_prop", data, item);

        n = sizeof(query("insert", item));
        ins = ([ "name" : query("name", tessera),
                 "id"   : query("id", tessera),
                 "SN"   : query("enchase/SN", tessera),
                 "apply_prop" : enchase_prop ]);

        set("insert/"+(n+1), ins, item);
        
        addn("enchase/used", 1, item);
        if( tessera->is_rune() ) {
                if( !query("enchase/rune", item) ){
                        addn("enchase/SN", query("enchase/SN", tessera), item);
                        set("enchase/rune", 1, item);
                }
                set("enchase/rune"+query("enchase/SN", tessera), 1, item);
        } else {
                /*
                if( query("can_be_enchased", tessera) )
                        //addn("enchase/SN", 5+random(5), item);
                        addn("enchase/SN",query("enchase/SN", tessera), item);
                else
                */
                {
                        addsn += random(query("enchase/SN", tessera))+1;
                        if (addsn > 9 ) addsn = 9;
                        if (addsn < 1 ) addsn = 1;

                        addn("enchase/SN", addsn, item);
                }
        }

        item->add_weight(tessera->query_weight());
        /* ȡ��ϴװ��
        if( IDENTIFY_D->identify_ultimate_ob(item) )
                tell_object(me, BLINK HBMAG + tessera->name() + BLINK HBMAG "��" + item->name() +
                                BLINK HBMAG "��ħ������ں�����ʹ" + item->name() +
                                BLINK HBMAG "�����˲���˼���ͻ�䡣\n\n" NOR);
        */
        item->save();
        destruct(tessera);
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// ����������Ƕ��Ʒ�ܻ��� melt
int do_wash(object me, object item)
{
        mapping enchase, insert, applied_prop;
        mapping mod_prop;
        string *apply, *ks;
        int i, j, f, n;

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("�����������������棬����óȻ���ã�\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("�����ھ������ã�����óȻ���ã�\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����������ʵ������óȻ�˹���\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("�㳢������һ���������޷�˳"
                                   "������һ�����죬����ʩչ���������\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");

        message_vision(HIM "$N" HIM "��$n" HIM "�������У�ĬĬ��ת������ע��$n" HIM "���ۡ�\nֻ��$n" HIM
                       "�������ڣ����������ܡ�\n" NOR, me, item);


        message_vision(HIC"����ȴ��$n"HIC"����"HIY+chinese_number(query("enchase/flute", item))+
                       HIC "����������Ʒ�͵Ļ���һ�����̣�\n$n"HIC "�������ѿ���һ������³���\n" NOR,
                       me, item);

        if( query("enchase/rune30", item) || query("enchase/rune31", item) ||
            query("enchase/rune32", item) || query("enchase/rune33", item) )
        {
                if (item->is_weapon() || item->is_unarmed_weapon())
                {
                        if( query("enchase/used", item) >= 7 )
                                addn("enchase/wash", 1, item);
                }
                else
                {
                        if( query("enchase/used", item) >= 5 )
                                addn("enchase/wash", 1, item);
                }
        }

        f = query("enchase/flute", item);
        n = query("enchase/wash", item);
        applied_prop = copy(query("enchase/apply_prop", item));
        mod_prop = copy(query("enchase/mod_prop", item));
        /*
        insert = copy(query("insert", item));
        ks = keys(insert);
        for( i=0; i<sizeof(ks);i++ )
        {
                enchase = copy(insert[ks[i]]["apply_prop"]);
                apply = keys(enchase);
                for( j=0;j<sizeof(apply);j++ )
                {
                        applied_prop[apply[j]] -= enchase[apply[j]];
                        if( applied_prop[apply[j]] <= 0 )
                                map_delete(applied_prop, apply[j]);
                }
        }
        */
        delete("enchase", item);
        delete("insert", item);
        delete("magic/power", item);
        delete("magic/type", item);
        delete("magic/tessera", item);
        delete("ultimate/69", item);
        delete("ultimate/87", item);
        delete("ultimate/105", item);
        delete("ultimate/121", item);
        delete("ultimate/ob", item);
        delete("qianghua", item);
        set("enchase/flute", f, item);
        set("enchase/wash", n, item);
        //set("enchase/apply_prop", applied_prop, item);
        if( mapp(mod_prop) ) set("enchase/mod_prop", mod_prop, item);

        switch(query("material", item) )
        {
        case "tian jing":
                set("enchase/SN", 8, item);
                break;
        case "no name":
                set("enchase/SN", 16, item);
                break;
        default         :
                break;
        }

        item->save();
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// ����װ������
int do_forging(object me, object item, object ob)
{
        mapping temp;
        int n, rate, level;

        if( (int)me->query_skill("forging", 1) < 200 )
                return notify_fail("��Զ��켼�����ղ�����\n");

        if( query("level", me)/10*10 <= query("require/level", item) )
                return notify_fail("��Ŀǰ�������޷��ټ����������װ����\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("����ڹ���Ϊ���㡣\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˡ�\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˡ�\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("������������в��㡣\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˡ�\n");

        if( (query("potential", me)-query("learned_points", me)) < 20 )
                return notify_fail("���Ǳ�ܲ������޷�����������\n");

        message_sort(HIM "$N" HIM "����" +ob->name()+ HIM "��һ������˿˿�Ĵ��˽�ȥ��" +ob->name()+
                     HIM "��Ȼ���ڻ������ģ���Ө��͸��$N"
                     HIM "����һ�ӣ���һ����Һ����$n"
                     HIM "�ϣ�" HIM "$n" HIM "�����һ�������һ�㣬ɢ����ѤĿ�Ĺ�ʣ�\n" NOR,
                     me, item);

        addn("max_neili", -10, me);
        set("neili", query("max_neili", me), me);
        addn("qi", -50, me);
        addn("eff_qi", -30, me);
        addn("eff_jing", -30, me);
        addn("potential", -20, me);

        temp = query("require", item);
        level = temp["level"];
        temp["ilvl"] += 1;
        n = temp["ilvl"];

        if( n >= level+10 )
        {
                temp["level"] += 10;
                level = temp["level"];
                rate = random(100);
                if( rate < 40 ) temp["str"] = level*2 + random(level);
                else if( rate < 60 ) temp["con"] = level*2 + random(level);
                else if( rate < 80 ) temp["dex"] = level*2 + random(level);
                else temp["int"] = level*2 + random(level);
                temp["ilvl"] = 0;

                message_vision(HIY +item->name()+ HIY "����һ����һ���������$N" HIY "��" +item->name()+ HIY "�������ˣ�\n" NOR +
                               HIG "$N" HIG "��" +item->name()+ HIG "�ĵȼ�����ˣ�\n" NOR, me);

                //set("enchase/steady", 0, item);   // ǿ�������ָ�0
                //set("enchase/increase", 0, item); // ��������ָ�0
        }

        set("require", temp, item);
        item->save();
        destruct(ob);
        message_vision(RED "$N" RED "��" +item->name()+ RED "���ʵظ�����!\n" NOR, me);
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// ��װ������Ҫ��
int do_require(object me, object ob)
{
        mapping temp;
        int level;
        int rate;

        if( (int)me->query_skill("smelting", 1) < 200 )
                return notify_fail("���ұ���������ղ�����\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("����ڹ���Ϊ���㡣\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˡ�\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˡ�\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("������������в��㡣\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˡ�\n");

        temp = query("require", ob);
        level = temp["level"];

        rate = random(100);
        if( rate < 40 ) temp["str"] = level*2 + random(level);
        else if( rate < 60 ) temp["con"] = level*2 + random(level);
        else if( rate < 80 ) temp["dex"] = level*2 + random(level);
        else temp["int"] = level*2 + random(level);
        set("require", temp, ob);
        message_vision(HIY +ob->name()+ HIY "�������Թ���һ������Ĺ�â���漴���ƽ����\n" NOR, me);
        ob->save();
}

// 10��������������
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        mapping magic;
        int jingjia;
        int power, resistance;
        int damage;
        int add, reduce;
        string msg;

        // ����ħ��Ч��
        magic=query("magic", weapon);
        if( !mapp(magic) ) return;
        power = magic["power"];
        damage = 0;
        resistance = 0;
        //jingjia = me->query("jiajing");
        jingjia=query("jiali", me)/3;

        switch (magic["type"])
        {
        case "lighting":
                // ���繥�����˺�����++����+
                resistance=query_temp("apply/resistance/lighting", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_lighting", me);
                reduce=query_temp("apply/reduce_lighting", victim);
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                switch (random(6))
                {
                case 0:
                        msg = HIY + weapon->name() + HIY "�ŷ����������������⣬�������죬��$n"
                              HIY "����Ϊ֮���顣\n" NOR;
                        break;
                case 1:
                        msg = HIY "һ�����������" + weapon->name() + HIY
                              "���ҫ�۶�Ŀ����$n" HIY "�޷����ӣ������ϡ�\n" NOR;
                        break;
                case 2:
                        msg=HIY+query("name", weapon)+HIY"���һ�ų�׵Ĺ���ֱ��$n"
                              HIY "��ȥ��$n" HIY "�����˸����ţ����˲��ᡣ\n" NOR;
                        break;
                case 3:
                        msg = HIY "һȦ��׵Ĺ⻷Χ��" + weapon->name() + HIY
                             "������ɢ����������֮��������磬$n" HIY "���̻����ɢ��\n" NOR;
                        break;
                case 4:
                        msg=HIY+query("name", weapon)+HIY"��������������׵�����ֱ��������$n"
                              HIY "������Ϥ��ֱ�������������ʱ����������\n" NOR;
                        break;
                default:
                        msg = HIY "����������������ף�������һ������ֱ�£�" +
                              weapon->name() + HIY "��������������ͷף����$n"
                              HIY "����������\n" NOR;
                        break;
                }

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                break;

        case "water":
                // �䶳�������˺���++����+
                resistance=query_temp("apply/resistance/water", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_water", me);
                reduce=query_temp("apply/reduce_water", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(6))
                {
                case 0:
                        msg = HIB + weapon->name() + HIB "����һ����ɬ�����⣬��$n"
                              HIB "����������\n" NOR;
                        break;
                case 1:
                        msg = HIB "��Ȼ��" + weapon->name() + HIB
                              "���͸��ͨ����һ��������ĺ���ŷ�������$n"
                              HIB "����ֻ��һ�䡣\n" NOR;
                        break;
                case 2:
                        msg = HIB "һȦ��Ө�ı��⻷Χ��" + weapon->name() + HIB
                              "������ɢ����������֮�����������$n" HIB
                              "ֻ���Լ���Ѫ���͡�\n" NOR;
                        break;
                case 3:
                        msg=HIB+query("name", weapon)+HIB"���������׶ֱ�������$n"
                              HIB "ת�ۼ���Ȼ���˷��ѡ�\n" NOR;
                        break;
                case 4:
                        msg = HIB "��Ȼ��" + weapon->name() + HIB
                              "���͸��ͨ������Χ������Ȼ�������ᣬһ�浭���ı�ǽ��$n"
                              HIB "�����������档\n" NOR;
                        break;
                default:
                        msg = HIB "һ����Ȧ��" + weapon->name() + HIB "�����"
                              "ɭȻ������$n" HIB "���ܣ���Ȼ��Ϣ��\n" NOR;
                        break;
                }
                break;

        case "fire":
                // ���湥�����˺���+����++
                resistance=query_temp("apply/resistance/fire", victim);
                damage = (power + jingjia) * 300 / (100 + resistance);
                add=query_temp("apply/add_fire", me);
                reduce=query_temp("apply/reduce_fire", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                switch (random(6))
                {
                case 0:
                        msg = HIR + weapon->name() + HIR "�������һ�����棬��$n"
                              HIR "�����������������ҽ�������\n" NOR;
                        break;
                case 1:
                        msg = HIR "һ������" + weapon->name() + HIR
                              "�ϱų���Ѹ�����׵Ļ���$n" HIR "�����˱��޿ɱܣ�\n" NOR;
                        break;
                case 2:
                        msg = HIR "һȦͨ��Ļ���" + weapon->name() + HIR
                              "�ϱų���ɢ����������֮������Իң���$n"
                              HIR "�����ճ���һ�����ڵĿ�����\n" NOR;
                        break;
                case 3:
                        msg=HIR+query("name", weapon)+HIB"��������ͨ��Ļ���ֱ��������$n"
                              HIR "������һƬ�𺣣��ҽ�������\n" NOR;
                        break;
                case 4:
                        msg = HIR "��Ȼ��" + weapon->name() + HIR
                              "���͸��ͨ�죬��Χ������Ȼ�쳣���$n"
                              HIR "գ�۹���������Ȼ�������һ�����Χס�����յ����������\n" NOR;
                        break;
                default:
                        msg = HIR "һ���������" + weapon->name() + HIR "�Ϸɽ������"
                              "����ɢ������������$n" HIR "��\n" NOR;
                        break;
                }
                break;
                
        case "metal":
                // �䶳�������˺���++����+
                resistance=query_temp("apply/resistance/metal", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_metal", me);
                reduce=query_temp("apply/reduce_metal", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg = HIY + weapon->name()+HIY"��ʱ������䣬�ݺύ���������������ռ䣬$n"HIY"��������Ŀ��\n"NOR;
                        break;
                case 1:
                        msg = HIY + weapon->name()+HIY"һ�ɳ��죬Ƭ��ʱ�仯��������"HIY + weapon->name()+HIY"��Ǯ���ذ������$n��\n"NOR;
                        break;
                default:
                        msg = HIY + weapon->name()+HIY"ͨ���Ľ��ҫĿ����������ص�˺����ֱ��$n"HIY"Ҫ��֮����\n"NOR;
                        break;
                }
                break;

        case "wood":
                // �䶳�������˺���++����+
                resistance=query_temp("apply/resistance/wood", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_wood", me);
                reduce=query_temp("apply/reduce_wood", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg =  HIG"��ʱ��"HIG + weapon->name()+HIG"֮Ӱ���� ���ƺ���ó�����֦�ɣ���$N����ץס��\n" NOR;
                        break;
                case 1:
                        msg =  HIG + weapon->name()+HIG"��$n"HIG"������������$n"HIG"��������ξ�����$n��ʧ���ѡ�\n" NOR;
                        break;
                default:
                        msg =  HIG  + weapon->name()+HIG"������������Ӱ�����ľ�ش���������$n"HIG"ȫ����\n" NOR;
                        break;
                }
                break;
                
        case "earth":
                // �䶳�������˺���++����+
                resistance=query_temp("apply/resistance/earth", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_earth", me);
                reduce=query_temp("apply/reduce_earth", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0: 
                        msg = YEL + weapon->name()+ YEL"ͻȻ�����������ͳ����أ���ɽҡ�ض�֮ʽ��$n"YEL"�Բ������ѣ�\n" NOR;
                        break;
                case 1:
                        msg = YEL + weapon->name()+ YEL"���ٵĻ�����ʯ֮Ե������ɽʯ֮�꣬�����������ĵ����ѵ�����ŭ�����$n�� \n"NOR;
                        break;
                default:
                        msg = YEL + weapon->name()+ YEL"��ȡ�������֮�������𹥻���ɲ�Ǽ���زԲԣ���ɳ��ʯ��\n" NOR;  
                        break;
                }
                break;     
                
        case "poison":
                // ��ϵħ��������������æ��
                resistance=query_temp("apply/resistance/poison", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_poison", me);
                reduce=query_temp("apply/reduce_poison", victim);
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                if (!victim->is_busy())
                        victim->start_busy(2 + random(3));

                switch (random(6))
                {
                case 0:
                        msg = HIG + weapon->name() + HIG "���ð��˿˿������ɢ������$n"
                              HIG "��ʱ������������������\n" NOR;
                        break;
                case 1:
                        msg=HIG+query("name", weapon)+HIG"����ɹɻ��̿���Χ�ƹ�����$n"
                              HIG "��ʱ�о�ͷ�ؽ��ᣬ��Ȼ��Щ�ò���������\n" NOR;
                        break;
                case 2:
                        msg=HIG+query("name", weapon)+HIG"�����������������������$n"
                              HIG "�������������Χ�����У����޷�֮����\n" NOR;
                        break;
                case 3:
                        msg = HIG + weapon->name() + HIG "���ð����˿�Դ�����İ���ƮȻ������$n"
                              HIG "��ʱȫ��������\n" NOR;
                        break;
                case 4:
                        msg = HIG + weapon->name() + HIG "���һȦ�Դ�����Ļ�ɫ����������ɢ����������֮������Կݣ�$n"
                              HIG "ֻ���Լ�ƮƮ���ɣ�ȫ��ʹ������������\n" NOR;
                        break;
                default:
                        msg=HIG+query("name", weapon)+HIG"�������Ũ������������$n"
                              HIG "ֻ������������ȫ��ʹ������������\n" NOR;
                        break;
                }
                break;

        case "wind":
                // ��ϵħ�����������߼�����
                resistance=query_temp("apply/resistance/wind", victim);
                damage = (power + jingjia) * 300 / (100 + resistance);
                add=query_temp("apply/add_wind", me);
                reduce=query_temp("apply/reduce_wind", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                switch (random(6))
                {
                case 0:
                        msg = HIW + weapon->name() + HIW "����һ��ǿ�磬ֱ����$n"
                              HIW "����������վ��ס����Щ���ѡ�\n" NOR;
                        break;
                case 1:
                        msg = HIW + weapon->name() + HIW "�γ�һ�����磬���ӻ�ɳ����������ѷ絶��$n"
                              HIW "Ϯ��������$n" HIW "������ת����Ȼ��Щ�ò���������\n" NOR;
                        break;
                case 2:
                        msg = HIW + weapon->name() + HIW "��Χ������Ȼ������ת��$n"
                              HIW "��������գ�۹���������Ȼ��ǿ�ҵ�������Χ�����У������ڵ����޷�֮����\n" NOR;
                        break;
                case 3:
                        msg = HIW + weapon->name() + HIW "�γ�ǿ���ƣ�һ�����������$n"
                              HIW "�ƺ�ʧȥ��Щ������������\n" NOR;
                        break;
                case 4:
                        msg = HIW + weapon->name() + HIW "�γ�һ������Ѹ����ת��������ɢ����������֮���������$n"
                              HIW "ֻ���Լ�������ת�����˲��ᡣ\n" NOR;
                        break;
                default:
                        msg = HIW + weapon->name() + HIW "�γ�ǿ�����������ӻ�ɳ���дӸ�����$n"+HIG+"Ѹ��Ϯ����$n"
                              HIW "��������߷�������������ת��ȫ�����������\n" NOR;
                        break;
                }
                break;

        case "magic":
                // ħ����������ȡ��+
                resistance=query_temp("apply/resistance/magic", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_magic", me);
                reduce=query_temp("apply/reduce_magic", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                switch (random(3))
                {
                case 0:
                        msg = HIM + weapon->name() + HIM "����һ�������������������������$n"
                              HIM "���񲻶��������㱡�\n" NOR;
                        break;
                case 1:
                        msg = HIM "��࣡���һ����" + weapon->name() + HIM
                              "����ܸȴ��$n" HIM "�ƺ�һ����ҡ�β�����\n" NOR;
                        break;
                default:
                        msg = HIM + weapon->name() + HIM "������һ��������ͷ׵�"
                              "��Ȧ��������$n" HIM "�����·��衣\n" NOR;
                        break;
                }
                break;

        default:
                msg = "";
                break;
        }

        // ʹ��perform
        if( random(2) && random(query("magic/blood", weapon)) < 2100 ) return msg;
        damage = power + jingjia;

        switch (random(6))
        {
        case 0:
                victim->receive_wound("jing", damage / 6 + random(damage / 6), me);
                return msg + HIM "$N" HIM "��Ȼ��Ц������" + weapon->name() +
                       HIM "�������⻪һ���������$n" HIM "���ڵ��У��޷��԰Ρ�\n" NOR;

        case 1:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return msg + HIC "$N" HIC "���е�" + weapon->name() + HIC "������ֹ�â��"
                       "ѣĿ���ˣ�һ�������ӳ�����ؾ���ʧɫ����$n"
                       HIC "Ŀ�ɿڴ���\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 4 + random(damage / 4), me);
                return msg + HIY "$N" HIY "����" + weapon->name() +
                       HIY "��ֻ�����һ������������$n" HIY "���¼�����Ѫ��\n" NOR;

        case 3:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return msg + HIG "$N" HIG "���ֻ���" + weapon->name() + HIG "��һȦȦ��â"
                       "Χ��$n" HIG "�����$n��Ѫ������\n" NOR;

        case 4:
                victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
                return msg + HIW "$N" HIW "һ����̾��" + weapon->name() + HIW "����ݳ���"
                       "��ʱ�����㾲��$n" HIW "ֻ���������˶������˵�����ȥ��\n" NOR;

        default:

                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 10 + random(4) :), me), 0);
        }
}

// 9��������������
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        int ap;
        int dp;
        int damage;
        string msg;

        if (random(2)) return;

        msg = "";

        // ����damage�������ǿ�������������ͨ������ͳһ����
        if (weapon->is_weapon())
                damage=query_temp("apply/damage", me);
        else
                damage=query_temp("apply/unarmed_damage", me);

        if (damage < 1) return;
        switch (random(8))
        {
        case 0:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                msg += HIY "$N" HIY "�������е�" + weapon->name() + HIY
                       "���û���ҹ�����ǣ�����" HIM "��â" HIY "������"
                       "��Ϯ��$n" HIY "��\n" NOR;
                break;
        case 1:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                msg += HIR "$N" HIR "���һ��������" + weapon->name() +
                       HIR "ңָ$n" HIR "��һ��ɱ����ʱ��$n" HIR "����"
                       "������\n" NOR;
                break;
        case 2:
                victim->receive_wound("qi", damage / 6 + random(damage / 6), me);
                victim->receive_wound("jing", damage / 10 + random(damage / 10), me);
                msg += HIG "$N" HIG "��ػ�ת" + weapon->name() + HIG
                       "��������̲�������" NOR + HIB "�Ǻ�" HIG "��"
                       "������$n" HIG "Ȧ�����С�\n" NOR;
                break;
        case 3:
        case 4:
        case 5:
        case 6:
                break;

        default:
                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);
        }
        return msg;
}

// ���У�12��������
void continue_attack(object me, object victim, object weapon, int times)
{
        int i;
        string msg;
        int ap, dp;

        if (!me || !victim || !weapon || !me->is_fighting(victim) ||
            environment(me) != environment(victim))
                return;

        if (!living(me) || !living(victim) )
                return;
        
        /*
        msg  = HIC "\n$N" HIC "һ����Ц������" + weapon->name() +
               HIC "�϶�Ϊһ����Ҳ�Ƶ�����$n" HIC "��\n" NOR;
        */
        msg  = HIW "��ʱֻ��$N" HIW "������Х������" + weapon->name() +
               HIW "��Ϊһ�壬��ʱ�亮â��ɢ����$n" HIW "��ȥ��\n" NOR;

        ap = me->query_skill("martial-cognize");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) > dp / 2)
                /*
                msg += HIR "$n" HIR "��֮�»�æ���ˣ�ȴ�����ܵÿ���һʱ��������������\n"
                       HIY "$N" HIY "ץס$n" HIY "¶�����������������е�" +
                       weapon->name() + HIY "������" + chinese_number(times) +
                       "��ȫ��ָ��$n" HIY "��Ҫ����\n" NOR;
                */
                msg += HIR "$n" HIR "��֮����æ���ˣ�����Ȼ�������ܣ�����"
                       "�в�������������\n" HIW "$N" HIW "��ס$n" HIW "����"
                       "������������ת����" + weapon->name() + HIW "������"
                       "ʯ���ѳ�$n" HIW "����" + chinese_number(times) + HIW
                       "�У�\n" NOR;
        else
        {
                /*
                msg += HIC "$n" HIC "ڤ��ֵ�����$N" HIC "���ɱһ�������б仯ȫȻ��ס��\n" NOR;
                */
                msg += CYN "����$n" CYN "ڤ��ֵ�����$N"
                       CYN "���е����б仯ȫȻ��ס��\n" NOR;
                message_combatd(msg, me, victim);
                return;
        }
        message_combatd(msg, me, victim);

        set_temp("weapon_performing", 1, me);
        i = times;
        while (i--)
        {
                if (!me->is_fighting(victim))
                        break;

                if (!victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),0);
        }
        delete_temp("weapon_performing", me);
}

// ������Ч��
int qianghua_effect(object item, string type)
{
        int level;
        
        level = query("qianghua/level", item);
        level *= 2;

        if( type == "weapon" )
                return level;
        
        return level;
}

// �����;ö�
void reduce_consistence(object item, object me, object victim, int damage)
{
        int st;
        int con;

        // ������Ƕ��Ʒ������Ч 
        if( !objectp(item) ) return;
        
        do_enchase_attack(item, me, victim, damage);
                        
        st=query("stable", item);

        if (st < 2)
                return;

        con=query("consistence", item);

        // ����쾧���Ƶ���������ĥ��
        if( query("material", item) == "tian jing" )
                return;

        if( query("material", item) == "no name" )
                return;

        if (random(st) > (100 - con) / 12)
                return;

        if( addn("consistence",-1, item)>0 )
                return;

        set("consistence", 0, item);

        if (environment(item))
                tell_object(environment(item), HIG "���" +
                            item->name() + HIG "�Ѿ��������ˡ�\n");

        item->unequip();
}

// ������Ʒȱʡ���;ö���Ϣ
void equip_setup(object item)
{
        int stable;
        mapping dbase;
        int max_consistence;

        dbase = item->query_entire_dbase();
        if (!undefinedp(dbase["max_consistence"]))
                max_consistence = dbase["max_consistence"];
        else
                max_consistence = 100;
        if (undefinedp(dbase["consistence"]))
               dbase["consistence"] = max_consistence;

        if( undefinedp(query("stable", item)) )
        {
                switch(query("material", item) )
                {
                case "cloth":
                        // ��Զ������
                        stable = 0;
                        break;

                case "paper":
                        stable = 3;
                        set("no_repair", "�ⶫ���ҿ�û��������\n", item);
                        break;

                case "bone":
                        stable = 8;
                        set("no_repear", "����������ɱ�����Ѱ���ġ�\n", item);
                        break;

                case "bamboo":
                case "wood":
                        stable = 10;
                        set("no_repair", "�ⶫ����զ������\n", item);
                        break;

                case "stone":
                        stable = 20;
//                        item->set("no_repair", "������˾ͻ��ˣ����޲��ˡ�\n");
                        break;

                case "copper":
                        stable = 40;
                        break;

                case "silver":
                        stable = 40;
                        break;

                case "iron":
                        stable = 45;
                        break;

                case "gold":
                        stable = 50;
                        break;

                case "steel":
                        stable = 75;
                        break;

                default:
                        stable = 100;
                        break;
                }

                if (!item->is_item_make())
                        stable /= 2;

                set("stable", stable, item);
        }
}

// ������Ƕ�ı�ʯ����
void do_enchase_attack(object item, object me, object victim, int damage)
{
        mapping enchase;
        string *apply;
        string msg;
        object *inv;
        object shenlong;
        int a1, a2, a3, a4;
        int extra, avoid, i, j, n;
        int dam;

        if( !me || !victim ) return;
                
        // �������������⹥������

        //if( !item->is_item_make() ) return;

        if( !query("skill_type", item) && query("armor_type", item) != "hands" &&
             query("armor_type", item) != "finger" ) return;

        // û����Ƕ�򷵻�
        enchase = query("enchase/apply_prop", item);

        if( !mapp(enchase) || sizeof(enchase) < 1 ) 
                return;
        
        message_combatd(HIG + "$N" HIG "�ġ�" + item->name() + HIG "������һ������Ĺ�â��\n" NOR, me);
        
        apply = keys(enchase);
        n = sizeof(apply);   
        for( i=0;i<n;i++ )
        {
                // ������Ч
                switch( apply[i] )
                {
                case "suck_qi":
                        extra = enchase[apply[i]]; // ͵ȡ����%
                        if( random(100) > extra ) break;
                        extra = damage*10/100;
                        if( query("qi", victim) < extra ) break;
                        victim->receive_damage("qi", extra, me);
                        me->receive_heal("qi", extra);
                        msg = HIR +victim->name()+ HIR "�е��Լ�����Ѫ��" + item->name() + HIR "�������Ƶġ�\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "��" + item->name() + HIY "����ȡ��" + victim->name() + HIY + "����Ѫ��" + sprintf("%d", extra) + "��\n" NOR;
                        tell_object(me, msg);
                        break;
                        
                case "suck_neili":
                        extra = enchase[apply[i]]; // ͵ȡ����%
                        if( random(100) > extra ) break;
                        extra = damage*10/100;
                        if( query("neili", victim) < extra ) break;
                        addn("neili", -extra, victim);
                        addn("neili", extra, me);
                        if( query("neili", me) > query("max_neili", me))
                                set("neili", query("max_neili", me), me);                        
                        msg = HIG +victim->name()+ HIG "�е��Լ���������" + item->name() + HIG "�������Ƶġ�\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "��" + item->name() + HIY "����ȡ��" + victim->name() + HIY + "��������" + sprintf("%d", extra) + "��\n" NOR;
                        tell_object(me, msg);
                        break;
                
                case "add_blind":
                        extra = enchase[apply[i]]; // ��ä
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_blind", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "ֻ��˫Ŀһ���ʹ����ǰһ�ڣ���ʲôҲ�������ˣ���ʱ����ʹ��������\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("block_msg/all", 1, victim);
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "��ä" :), 5);
                        break;
                
                case "add_freeze":
                        extra = enchase[apply[i]]; // ����
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_freeze", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIB "$n" HIB "ֻ����֫��Ӳ�����忪ʼ�������ж��ٻ����������ѣ���һ�������Ƶġ�\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("freeze", 1, victim); // combatd��perform�е���
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "����" :), 5);
                        break;
                
                case "add_burning":
                        extra = enchase[apply[i]]; // ����
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_burning", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "ֻ���Լ������ڻ�ɽ֮�У����忪ʼ��ȼ����Ѫ��������ʼ��ͣ���½���\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->apply_condition("add_burning", 50);
                        break;

                case "add_dizziness":
                        if( query("env/no_dizziness", me) ) break;
                        if( query("fight_room", environment(me)) ) break;
                        extra = enchase[apply[i]]; // ѣ��
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_dizziness", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIY "$n" HIY "ֻ��ͷ�Ի���������Ȼ��˯�����������Ժ���������ѣ��״̬�С�\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->remove_all_killer();
                        all_inventory(environment(victim))->remove_killer(victim);
                        set_temp("dizziness", 1, victim);
                        set_temp("override/receive_damage", (: call_other, __FILE__, "receive_damage" :), victim); // damage���ûָ�
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "ѣ��" :), 5);
                        break;
 
                 case "add_forget":
                        extra = enchase[apply[i]]; // ����
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_forget", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "ͻȻ����һ�ң�����һƬ�հף���ʱ�����˾������ʹ�á�\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("forget", 1, victim); 
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "����" :), 5);
                        break;
                /*
                case "add_weak":
                        extra = enchase[apply[i]]; // ����
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_weak", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "��ʱֻ��������ǳ���������ÿ���������ǳ����ѣ�һ������Ҳʹ�������ˡ�����\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->set_weak(5);
                        break;

                case "add_busy":
                        extra = enchase[apply[i]]; // æ��
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_busy", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�" + victim->name() + HIY + "��æ��Ч����" + sprintf("%d", 5) + "��\n" NOR;
                        tell_object(me, msg);
                        if( !victim->is_busy() ) victim->start_busy(5);
                        break;
                                                             
                case "add_damage":
                        extra = enchase[apply[i]];
                        extra = damage * extra/100;
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�" + victim->name() + HIY + "���˺���" + sprintf("%d", extra) + "��\n" NOR;
                        tell_object(me, msg);
                        victim->receive_damage("qi", extra, me);
                        break;

                case "no_exert":
                        extra = enchase[apply[i]];                       
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�" + victim->name() + HIY + "����Ϣ���ң�" + sprintf("%d", extra) + "��\n" NOR;
                        tell_object(me, msg);
                        if( !query_temp("no_exert", victim) ) 
                                set_temp("no_exert", 1, victim);
                        tell_object(victim, HIM "�㱻" + me->name() + HIM "��" + HIY + item->name() + HIM "���У��پ���Ϣ���ң�\n" NOR);

                        // ����Ч��
                        call_out("remove_effect", extra, victim, "��Ϣ����");
                        break;

                case "no_perform":
                        extra = enchase[apply[i]]; 
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�" + victim->name() + HIY + "��������ɢ��" + sprintf("%d", extra) + "��\n" NOR;
                        tell_object(me, msg);
                        if( !query_temp("no_perform", victim) ) 
                                set_temp("no_perform", 1, victim);
                        tell_object(victim, HIM "�㱻" + me->name() + HIM "��" + HIY + item->name() + HIM "���У��پ�������ɢ��\n" NOR);

                        // ����Ч��
                        call_out("remove_effect", extra, "������ɢ");
                        break;
                */
                case "clear_force":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query("neili", victim) < 100 ) break;
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�" + victim->name() + HIY + "���Ƴ�����ҪѨ��\n" NOR;
                        tell_object(me, msg);
                        set("neili", 0, victim);
                        tell_object(victim, HIM "�㱻" + me->name() + HIM "��" + HIY + item->name() + HIM "��������ҪѨ���پ�������ɢ��\n" NOR);
                        break;

                // ����ս��
                case "reduce_combat":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query_temp("reduce_combat", victim) ) break;

                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�$n" + HIR "������ս�����������������رܡ����и�30%��\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("reduce_combat", 1, victim);
                        a1 = query_temp("apply/damage", victim) / 10 * 3;
                        a2 = query_temp("apply/unarmed_damage", victim) / 10 * 3;
                        a3 = query_temp("apply/defense", victim) / 10 * 3;
                        a4 = query_temp("apply/attack", victim) / 10 * 3;
                        addn_temp("apply/damage", -a1, victim);
                        addn_temp("apply/unarmed_damage", -a2, victim);
                        addn_temp("apply/defense", -a3, victim);
                        addn_temp("apply/attack", -a4, victim);
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "����ս��", a1, a2, a3, a4 :), 15);
                        break;

                // ����һ��
                case "fatal_blow":
                        extra = enchase[apply[i]]; 
                        if( random(100) > 20 ) break;
                        extra = query("qi", victim) * extra/100;
                        
                        msg = HIR "��" + item->name() + HIR "��׷�ӡ�$n" + HIY + "������һ�����˺���" + sprintf("%d", extra) + "��\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->receive_damage("qi", extra, me);
                        victim->receive_wound("qi", extra/2, me);
                        break;

                // ��ħ����
                case "absorb_blood":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query_temp("absorb_blood", me) ) break;
                        msg = HIG "��" + item->name() + HIG "����â���ɣ���ħ�����Ź�â���������$N" + HIG "���и��塣\n" NOR;
                        message_combatd(msg, me);
                        set_temp("absorb_blood", 1, me);
                        a1 = query_temp("apply/damage", me) / 10 * 3;
                        a2 = query_temp("apply/unarmed_damage", me) / 10 * 3;
                        a3 = query_temp("apply/defense", me) / 10 * 3;
                        a4 = query_temp("apply/attack", me) / 10 * 3;
                        addn_temp("apply/damage", a1, me);
                        addn_temp("apply/unarmed_damage", a2, me);
                        addn_temp("apply/defense", a3, me);
                        addn_temp("apply/attack", a4, me);
                        me->start_call_out((: call_other, __FILE__, "remove_effect", me, "��ħ����", a1, a2, a3, a4 :), 15);
                        break;
                
                // ɱ¾
                case "slaughter":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        dam = query("magic/power", item) + query("jiali", me);
                        msg = HIR "��" + item->name() + HIR "��ɱ�����죬һ����ɱ��������������������\n" NOR;
                        message_combatd(msg, me);
                        inv = all_inventory(environment(me));
                        for( j=sizeof(inv)-1; j>=0; j--)
                        {
                                if( inv[j] == me ) continue;
                                if( !inv[j]->is_killing(query("id", me)) ) continue;
                                inv[j]->receive_damage("qi", dam, me);
                                inv[j]->receive_wound("qi", dam/2, me);
                        }
                        break;
                        
                // �ٻ�����
                case "summon_shenlong":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( time() - query_temp("last_summon_shenlong", me) < 180 ) break;

                        msg = HIG "��" + item->name() + HIG "����â���ɣ�һ�����������Ź�â���������\n" NOR;
                        message_combatd(msg, me);
                        
                        shenlong = new("/kungfu/class/misc/shenlong");
                        
                        if( !objectp(shenlong) ) break;
                                                
                        set_temp("last_summon_shenlong", time(), me);

                        shenlong->move(environment(me));
                        set("long", HIC + me->name() + HIC "�ı�����Ů���̺��������������ٻ��������������ޱȡ�\n" NOR, shenlong);
                        shenlong->kill_ob(victim);
                        shenlong->force_me("guard " + query("id", me) );
                        break;
                default :
                        break;
                }
        }       
        return;
}

// ������Ч
varargs void remove_effect(object victim, string eff, int a1, int a2, int a3, int a4)
{
        if( !objectp(victim) ) return;

        switch( eff )
        {
                case "��ä":
                        if( !query_temp("block_msg/all", victim) ) return;
                        delete_temp("block_msg/all", victim);
                        tell_object(victim, HIR "������Ĩ������ǰ����Ѫ���ܿ����ˡ�\n" NOR);
                        return;
                case "����":
                        if( !query_temp("freeze", victim) ) return;
                        delete_temp("freeze", victim); 
                        tell_object(victim, HIR "������ȫ����ʼ�ⶳ���ָ���������\n" NOR);
                        return;
                case "ѣ��":
                        if( !query_temp("dizziness", victim) ) return;
                        delete_temp("dizziness", victim);
                        tell_object(victim, HIR "��ѣ��״̬������ָ���������\n" NOR);
                        return;
                case "����":
                        if( !query_temp("forget", victim) ) return;
                        delete_temp("forget", victim); 
                        tell_object(victim, HIR "���������������еļ��䣬�ָ���������\n" NOR);
                        return;
                case "��Ϣ����":
                        if( !query_temp("no_exert", victim) ) return;
                        delete_temp("no_exert", victim);
                        tell_object(victim, HIR "����Ϣ����״���������ָ���������\n" NOR);
                        return;
                case "������ɢ":
                        if( !query_temp("no_perform", victim) ) return;
                        delete_temp("no_perform", victim);
                        tell_object(victim, HIR "��������ɢ״���������ָ���������\n" NOR);
                        return;
                case "��ħ����":
                        if( !query_temp("absorb_blood", victim) ) return;
                        delete_temp("absorb_blood", victim);
                        addn_temp("apply/damage", -a1, victim);
                        addn_temp("apply/unarmed_damage", -a2, victim);
                        addn_temp("apply/defense", -a3, victim);
                        addn_temp("apply/attack", -a4, victim);
                        return;
                case "����ս��":
                        if( !query_temp("reduce_combat", victim) ) return;
                        delete_temp("reduce_combat", victim);
                        addn_temp("apply/damage", a1, victim);
                        addn_temp("apply/unarmed_damage", a2, victim);
                        addn_temp("apply/defense", a3, victim);
                        addn_temp("apply/attack", a4, victim);
                        return;
        }
        return;
}

varargs int receive_damage(object me, string type, int damage, object who)
{
        delete_temp("override/receive_damage", me);
        if( !query_temp("dizziness", me) ) return 0;
        delete_temp("dizziness", me);
        tell_object(me, HIR "�����ܵ���������ѣ��״̬������ָ���������\n" NOR);
        return 0;
}