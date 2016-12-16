 // by Tie@fy3
 
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

#define MAX_DIS 7
#define MAX_ALT  2
#define MAX_DIR  8  

mapping *quests;
string locate_obj(object me, string strr);
object find_env(object ob);

int main(object me, string str)
{
        string output = "";
        object room;
        int    x0, y0, z0;
        
        room = environment(me);
        x0=query("coor/x", room);
        y0=query("coor/y", room);
        z0=query("coor/z", room);
   
        if (! x0 && ! y0 && ! z0 && base_name(room) != "/d/city/guangchang") 
                return notify_fail(WHT "����ط�����ʹ��locateָ�ֻ������task�����ĵ����ſ���ʹ�ã�\n" NOR);
                
        if (! str) 
                return notify_fail("ָ���ʽ: locate <��Ʒ>\n");

/*
        if( query("reborn/times", me) )
                return notify_fail("ת����Ҳ�������ʹ������\n");
*/

        if( query("qi", me)<30 )
                return notify_fail("����������Բ�Ѱλ�á�\n");
                
        me->receive_damage("qi", 20);
        output = TASK_D->locate_ob(me, str);
        // if(output=="")
        // output = QUESTNPC_D->locate_obj(me, str);
        
        if (output == "")
                return notify_fail("ȷ������" + str + "�Ĵ��λ�á�\n");
        
        write(output);
        return 1;
}  

object find_env(object ob)
{
        while(ob)
        {
                if( query("coor", ob) )
                        return ob;
                else 
                        ob = environment(ob);        
        }
        return ob;
}        

int help(object me)
{
        write(@HELP
ָ���ʽ: locate <��Ʒ> 
���ָ����������֪ʹ����Ʒ�Ĵ��λ�á�
��͢��Ա�������ô�ָ���Ѱ����Ĵ��λ�á� 
HELP
        );
        return 1;
} 