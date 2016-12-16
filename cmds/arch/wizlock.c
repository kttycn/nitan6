// wizlock.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int lvl;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg || arg == "")
                return notify_fail("ָ���ʽ��wizlock <��ʦ�ȼ�>\n");

        if (sscanf(arg, "%d", lvl) != 1) lvl = wiz_level(arg);
        seteuid(getuid());

        if (LOGIN_D->set_wizlock(lvl))
        {
                write("Ok.\n");
                return 1;
        } else
                return notify_fail("����Ȩ���趨ʧ�ܡ�\n");
}

int help (object me)
{
        write(@HELP
ָ���ʽ: wizlock <��ʦ�ȼ�>
 
����ĳ���ȼ����µ�ʹ���߽�����Ϸ��
������ʦ�ȼ��ֱ�Ϊ (immortal) (wizard) (arch) (admin), ��Ҫȡ
������, ������ (player).
 
HELP );
        return 1;
}