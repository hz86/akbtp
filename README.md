# akbtp
秋叶原之旅加强版-DATA解包

```
fix为插件
eboot注入插件目的是实现自定义编码转换为ucs2编码



修改 0017D588 启动线程到自己的接口
新启动入口 0x00006838 = 0x0880A838


$a1 = 启动线程的回调
修改a1的数值为 0x00006838 = 0x08804000 + 0x6838

loc_0017D580:		; Refs: 0x0017D56C 
	0x0017D580: 0x3C110000 '...<' - lui        $s1, 0x0
	0x0017D584: 0x26256838 '8h%&' - addiu      $a1, $s1, 26680
	0x0017D588: 0x0C07E6F9 '....' - jal        sceKernelCreateThread

清理掉原有函数代码 6828开始 大小260字节
修改为默认直接返回

sub_00006828:		; Refs: 0x00006680 
	0x00006828: 0x03E00008 '....' - jr         $ra
	0x0000682C: 0x00000000 '....' - nop        
	0x00006830: 0x00000000 '....' - nop        
	0x00006834: 0x00000000 '....' - nop    

这是新的主线程入口
先加载插件，然后调用旧的线程入口
6828原来存在2个重定位。正好给下面2个sub使用了
重定位表内，将原地址改为 6848,6858

sub_00006838:		; Refs: 0x0017D584 
	0x00006838: 0x27BDFFF0 '...'' - addiu      $sp, $sp, -16
	0x0000683C: 0xAFBF0004 '....' - sw         $ra, 4($sp)
	0x00006840: 0xAFA40008 '....' - sw         $a0, 8($sp)
	0x00006844: 0xAFA5000C '....' - sw         $a1, 12($sp)
	0x00006848: 0x0C001A1C '....' - jal        sub_00006870
	0x0000684C: 0x00000000 '....' - nop        
	0x00006850: 0x8FA5000C '....' - lw         $a1, 12($sp)
	0x00006854: 0x8FA40008 '....' - lw         $a0, 8($sp)
	0x00006858: 0x0C05F576 'v...' - jal        sub_0017D5D8
	0x0000685C: 0x00000000 '....' - nop        
	0x00006860: 0x8FBF0004 '....' - lw         $ra, 4($sp)
	0x00006864: 0x03E00008 '....' - jr         $ra
	0x00006868: 0x27BD0010 '...'' - addiu      $sp, $sp, 16
	0x0000686C: 0x00000000 '....' - nop       


这里为载入插件的代码
$a0 = 插件路径
$s1 = sceKernelLoadModule
$s2 = sceKernelStartModule
$s0 = 0x00006850

sub_00006870:		; Refs: 0x00006848 
	0x00006870: 0x03E08021 '!...' - move       $s0, $ra
	0x00006874: 0x3C02001F '...<' - lui        $v0, 0x1F
	0x00006878: 0x344234AC '.4B4' - ori        $v0, $v0, 0x34AC
	0x0000687C: 0x02028821 '!...' - addu       $s1, $s0, $v0
	0x00006880: 0x3C02001F '...<' - lui        $v0, 0x1F
	0x00006884: 0x3442349C '.4B4' - ori        $v0, $v0, 0x349C
	0x00006888: 0x02029021 '!...' - addu       $s2, $s0, $v0
	0x0000688C: 0x27BDFFF8 '...'' - addiu      $sp, $sp, -8
	0x00006890: 0xAFBF0004 '....' - sw         $ra, 4($sp)
	0x00006894: 0x26040078 'x..&' - addiu      $a0, $s0, 120
	0x00006898: 0x00002821 '!(..' - move       $a1, $zr
	0x0000689C: 0x0220F809 '.. .' - jalr       $s1
	0x000068A0: 0x00003021 '!0..' - move       $a2, $zr
	0x000068A4: 0x00402021 '! @.' - move       $a0, $v0
	0x000068A8: 0x8FBF0004 '....' - lw         $ra, 4($sp)
	0x000068AC: 0x00002821 '!(..' - move       $a1, $zr
	0x000068B0: 0x00003021 '!0..' - move       $a2, $zr
	0x000068B4: 0x00003821 '!8..' - move       $a3, $zr
	0x000068B8: 0x00004021 '!@..' - move       $t0, $zr
	0x000068BC: 0x02400008 '..@.' - jr         $s2
	0x000068C0: 0x27BD0008 '...'' - addiu      $sp, $sp, 8
	0x000068C4: 0x00000000 '....' - nop        
	0x000068C8: 0x63736964 'disc' - Unknown    
	0x000068CC: 0x502F3A30 '0:/P' - beql       $at, $t7, loc_00015190
	0x000068D0: 0x475F5053 'SP_G' - Unknown    
	0x000068D4: 0x2F454D41 'AME/' - sltiu      $a1, $k0, 19777
	0x000068D8: 0x44535953 'SYSD' - Unknown    
	0x000068DC: 0x462F5249 'IR/F' - Unknown    
	0x000068E0: 0x502E5849 'IX.P' - beql       $at, $t6, loc_0001CA08
	0x000068E4: 0x00005852 'RX..' - Unknown    
	0x000068E8: 0x00000000 '....' - nop        
	0x000068EC: 0x00000000 '....' - nop        
	0x000068F0: 0x00000000 '....' - nop        
	0x000068F4: 0x00000000 '....' - nop        
	0x000068F8: 0x00000000 '....' - nop        
	0x000068FC: 0x00000000 '....' - nop        
	0x00006900: 0x00000000 '....' - nop        
	0x00006904: 0x00000000 '....' - nop        
	0x00006908: 0x00000000 '....' - nop        
	0x0000690C: 0x00000000 '....' - nop        
	0x00006910: 0x00000000 '....' - nop        
	0x00006914: 0x00000000 '....' - nop        
	0x00006918: 0x00000000 '....' - nop        
	0x0000691C: 0x00000000 '....' - nop        
	0x00006920: 0x00000000 '....' - nop        
	0x00006924: 0x00000000 '....' - nop        
	0x00006928: 0x00000000 '....' - nop         


```