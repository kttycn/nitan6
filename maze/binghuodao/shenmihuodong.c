inherit __DIR__"binghuodao";

void create()
{
        set("short", "���ػ�");
        set("long",
"���Ǳ��������ص�һ���𶴣������������ڣ�������Ϣ��\n"
);
        set("exits", ([ 
                "north"   : __DIR__"shenghuotai", 
                "east"   : __DIR__"shenmihuodong2",
                "south"   : __DIR__"shenmihuodong3",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huoqilin");            
        setup();
}
