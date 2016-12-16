#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me); 
string *deep_file_list(string dir, string opt);

int main(object me, string arg)
{
        string file, opt;
        string sname;
        mixed *dir;
        int i, total;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0; 

        seteuid(geteuid(this_player(1)));

        if (! arg || (arg != "all" && arg != "pfm" && arg != "skl")) 
                return help(me); 
        
        opt = arg;  
        total = 0;     
        
        dir = deep_file_list("/kungfu/skill/", opt);
        for(i = 0; i < sizeof(dir); i++)
        {
                reset_eval_cost();
                if (file_size(dir[i]) > 0)
                {
                        file = read_file(dir[i]);
                        if (opt == "pfm" || opt == "all")
                        {                               
                                if (file[0..52] == "// This is player's own perform (Write by Lonely@nt2)")
                                {
                                        rm(dir[i]);
                                        total++;
                                        write(dir[i] +" ��ɾ����\n");
                                        continue;
                                }
                        }
                        
                        if (opt == "skl" || opt == "all")
                        {
                                if (file[0..50] == "// This is player's own skill (Write by Lonely@nt2)")
                                {
                                        /*
                                        if (sscanf(dir[i], "/kungfu/skill/%s.c", sname))
                                                SKILLS_D->remove_skill_from_skills(me, sname); 
                                        */
                                        rm(dir[i]);
                                        total++;
                                        write(dir[i] +" ��ɾ����\n");
                                        continue;
                                }
                        }
                        
                }
        }
        
        write("\n����Ŀ¼�������Դ��ļ��� " + total + " ����ɾ����\n");
        return 1;               
}

string *deep_file_list(string dir, string opt)
{
        int i;
        string *flist, *result = ({ });
        string file;
        
        flist = get_dir(dir);

        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];
                
                if (opt == "skl")
                {
                        if (file_size(file) > 0)
                                result += ({ file });
                } else
                if (opt == "pfm")
                {                       
                        if (file_size(file + "/") == -2)
                                result += deep_file_list(file + "/", opt);
                        else 
                        if (dir != "/kungfu/skill/")
                                result += ({ file });
                } else
                if (opt == "all")
                {
                        if (file_size(file + "/") == -2)
                                result += deep_file_list(file + "/", opt);
                        else
                                result += ({ file });
                }                         
        }
        return result;
}

int help(object me) 
{ 
write(@HELP

ָ���ʽ: clearinvent [pfm] | [skl] | [all]
��ָ���������Դ��书���Դ������ļ�ȫ��ɾ����
ע�⣺������Ƚ�Σ�գ���С��ʹ�á�

HELP);
return 1;
}