//1997-3-10 by qyz
#include <room.h>
#include <ansi.h>

inherit ROOM;


void create()
{
	set("short","疑无路");
	set("long",@LONG
在光滑的崖壁上，垂下来一条三丈馀长的铁索梯，黑黝黝，山风吹起不时地
摆动，撞在石壁上发出铮铮锵锵的响声，令人不寒而栗。崖顶又是一条长长的天
桥栈道，一面临崖，一面悬空，用钢钎钉入崖壁，其上架些木板，十分险峻，下
脚稍重，木板另一头就翘起，把人吓得丧魂失魄。所以除了修为很深的真人，谁
也不敢爬上崖壁去。
LONG);
	set("not_startroom",1);
	set("exits",
	([
             "down" : __DIR__"xianren_qiao",
//             "up" : __DIR__"xuanhe_dong",
          	]));
        set("outdoors","kongdong");
	set("objects",([
		__DIR__"npc/zhou" : 1,
		]) );
        setup();
        //place_program(ROOM);
}
void init()
{
	add_action("do_climb","climb");
	add_action("do_update","update");	
	}
int do_update()
{return 1;}
int do_climb(string arg)
{
        object *all;
                int i;
	object me =this_player();
	
	if(!arg||arg!="栈道")
	return notify_fail("你要往哪里去？可不是闹着玩的！\n");
	if(me->query_temp("climbing"))
	return notify_fail("你正在战战兢兢地过栈道呢！\n");

       all=all_inventory(me);
            for(i=0;i<sizeof(all);i++)
                if(userp(all[i])){
                    message_vision("$N把$n往地下一摔，勇敢的跳了下去。\n",me,all[i]);
                    all[i]->move("/d/menpai/kongdong/yiwu_lu");
                }        
    me->start_busy(30,"性命攸关哪\n");
	call_out("pashan", 5, me, 0);
	me->set_temp("climbing",1);
        message_vision( HIG"$N深深吸了几口气，沿着颤颤悠悠的栈道走了过去......\n"NOR ,me);
	return 1;

}
	
void pashan( object me, int number )
{
	object *inv;
int i,j;
object dong =load_object(__DIR__"xuanhe_dong");  
i=number + 1;
switch( i ) {
case 1:
case 2:
case 3:
case 4:
message_vision( HIR"$N慢慢地一步一步地往前挪......\n"NOR ,me);
break;
case 5:
message_vision( HIG"眼看$N已经到了栈道中央了......\n"NOR,me );
break;
case 6:
case 7:
case 8:
case 9:
message_vision( HIR"$N慢慢地一步一步地往前挪......\n"NOR ,me);
break;
default:
if( !random(7)&&me->query("id")=="zhou zhenren" && !present("zhou zhenren",dong))
{
message_vision( HIG"终于，$N到达了对面的石壁....好险呀！\n",me);
me->move("/d/menpai/kongdong/xuanhe_dong");
inv = all_inventory(this_object());
for (j = 0; j < sizeof(inv); j++)
  if (userp(inv[j]))
  inv[j]->set("marks/kongdong/zhou",1);
return;	
	}
message_vision( HIY"突然一个踉跄，$N歪向一边，晃了两晃就掉了下去.....\n"NOR, me);
if( me->query_xiuwei("dodge")>3200&&present("zhou zhenren",dong)&&random(me->query_kar())>28)
{message_vision( HIG"石壁对面的周真人抛出一道铁索，正好缠在$N的腰间，把$N救了上去....好险呀！\n"NOR,me );
me->move("/d/menpai/kongdong/xuanhe_dong");
}
else
{message_vision( HIY"只听$N一身惨叫，已坠下万丈深渊......\n"NOR,me);
me->set("eff_sen",me->query("eff_sen")/2);
me->move(__DIR__"xiangtou_ya");
me->delete_temp("climbing");
if(!userp(me))
destruct(me);
else if(me->query("eff_sen")<me->query("max_sen")/6)
me->die();
else
me->unconcious();
}
return;
}
call_out( "pashan", 5, me, i );
return;
}
/*
int valid_leave(object me,string dir)
{
    if(dir=="up")
      return notify_fail("只有爬过栈道才能走过去的，可以尝试(climb 栈道)。\n");
    return ::valid_leave(me,dir);
}
*/