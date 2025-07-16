                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module tst1
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _timer_isr
                                     13 	.globl _CY
                                     14 	.globl _AC
                                     15 	.globl _F0
                                     16 	.globl _RS1
                                     17 	.globl _RS0
                                     18 	.globl _OV
                                     19 	.globl _F1
                                     20 	.globl _P
                                     21 	.globl _PS
                                     22 	.globl _PT1
                                     23 	.globl _PX1
                                     24 	.globl _PT0
                                     25 	.globl _PX0
                                     26 	.globl _RD
                                     27 	.globl _WR
                                     28 	.globl _T1
                                     29 	.globl _T0
                                     30 	.globl _INT1
                                     31 	.globl _INT0
                                     32 	.globl _TXD
                                     33 	.globl _RXD
                                     34 	.globl _P3_7
                                     35 	.globl _P3_6
                                     36 	.globl _P3_5
                                     37 	.globl _P3_4
                                     38 	.globl _P3_3
                                     39 	.globl _P3_2
                                     40 	.globl _P3_1
                                     41 	.globl _P3_0
                                     42 	.globl _EA
                                     43 	.globl _ES
                                     44 	.globl _ET1
                                     45 	.globl _EX1
                                     46 	.globl _ET0
                                     47 	.globl _EX0
                                     48 	.globl _P2_7
                                     49 	.globl _P2_6
                                     50 	.globl _P2_5
                                     51 	.globl _P2_4
                                     52 	.globl _P2_3
                                     53 	.globl _P2_2
                                     54 	.globl _P2_1
                                     55 	.globl _P2_0
                                     56 	.globl _SM0
                                     57 	.globl _SM1
                                     58 	.globl _SM2
                                     59 	.globl _REN
                                     60 	.globl _TB8
                                     61 	.globl _RB8
                                     62 	.globl _TI
                                     63 	.globl _RI
                                     64 	.globl _P1_7
                                     65 	.globl _P1_6
                                     66 	.globl _P1_5
                                     67 	.globl _P1_4
                                     68 	.globl _P1_3
                                     69 	.globl _P1_2
                                     70 	.globl _P1_1
                                     71 	.globl _P1_0
                                     72 	.globl _TF1
                                     73 	.globl _TR1
                                     74 	.globl _TF0
                                     75 	.globl _TR0
                                     76 	.globl _IE1
                                     77 	.globl _IT1
                                     78 	.globl _IE0
                                     79 	.globl _IT0
                                     80 	.globl _P0_7
                                     81 	.globl _P0_6
                                     82 	.globl _P0_5
                                     83 	.globl _P0_4
                                     84 	.globl _P0_3
                                     85 	.globl _P0_2
                                     86 	.globl _P0_1
                                     87 	.globl _P0_0
                                     88 	.globl _CKCON0
                                     89 	.globl _XBR2
                                     90 	.globl _P1SKIP
                                     91 	.globl _P1MDOUT
                                     92 	.globl _CLKSEL
                                     93 	.globl _B
                                     94 	.globl _ACC
                                     95 	.globl _PSW
                                     96 	.globl _IP
                                     97 	.globl _P3
                                     98 	.globl _IE
                                     99 	.globl _P2
                                    100 	.globl _SBUF
                                    101 	.globl _SCON
                                    102 	.globl _P1
                                    103 	.globl _TH1
                                    104 	.globl _TH0
                                    105 	.globl _TL1
                                    106 	.globl _TL0
                                    107 	.globl _TMOD
                                    108 	.globl _TCON
                                    109 	.globl _PCON
                                    110 	.globl _DPH
                                    111 	.globl _DPL
                                    112 	.globl _SP
                                    113 	.globl _P0
                                    114 	.globl _last_ms
                                    115 	.globl _ms
                                    116 ;--------------------------------------------------------
                                    117 ; special function registers
                                    118 ;--------------------------------------------------------
                                    119 	.area RSEG    (ABS,DATA)
      000000                        120 	.org 0x0000
                           000080   121 _P0	=	0x0080
                           000081   122 _SP	=	0x0081
                           000082   123 _DPL	=	0x0082
                           000083   124 _DPH	=	0x0083
                           000087   125 _PCON	=	0x0087
                           000088   126 _TCON	=	0x0088
                           000089   127 _TMOD	=	0x0089
                           00008A   128 _TL0	=	0x008a
                           00008B   129 _TL1	=	0x008b
                           00008C   130 _TH0	=	0x008c
                           00008D   131 _TH1	=	0x008d
                           000090   132 _P1	=	0x0090
                           000098   133 _SCON	=	0x0098
                           000099   134 _SBUF	=	0x0099
                           0000A0   135 _P2	=	0x00a0
                           0000A8   136 _IE	=	0x00a8
                           0000B0   137 _P3	=	0x00b0
                           0000B8   138 _IP	=	0x00b8
                           0000D0   139 _PSW	=	0x00d0
                           0000E0   140 _ACC	=	0x00e0
                           0000F0   141 _B	=	0x00f0
                           0000A9   142 _CLKSEL	=	0x00a9
                           0000A5   143 _P1MDOUT	=	0x00a5
                           0000D5   144 _P1SKIP	=	0x00d5
                           0000E3   145 _XBR2	=	0x00e3
                           00008E   146 _CKCON0	=	0x008e
                                    147 ;--------------------------------------------------------
                                    148 ; special function bits
                                    149 ;--------------------------------------------------------
                                    150 	.area RSEG    (ABS,DATA)
      000000                        151 	.org 0x0000
                           000080   152 _P0_0	=	0x0080
                           000081   153 _P0_1	=	0x0081
                           000082   154 _P0_2	=	0x0082
                           000083   155 _P0_3	=	0x0083
                           000084   156 _P0_4	=	0x0084
                           000085   157 _P0_5	=	0x0085
                           000086   158 _P0_6	=	0x0086
                           000087   159 _P0_7	=	0x0087
                           000088   160 _IT0	=	0x0088
                           000089   161 _IE0	=	0x0089
                           00008A   162 _IT1	=	0x008a
                           00008B   163 _IE1	=	0x008b
                           00008C   164 _TR0	=	0x008c
                           00008D   165 _TF0	=	0x008d
                           00008E   166 _TR1	=	0x008e
                           00008F   167 _TF1	=	0x008f
                           000090   168 _P1_0	=	0x0090
                           000091   169 _P1_1	=	0x0091
                           000092   170 _P1_2	=	0x0092
                           000093   171 _P1_3	=	0x0093
                           000094   172 _P1_4	=	0x0094
                           000095   173 _P1_5	=	0x0095
                           000096   174 _P1_6	=	0x0096
                           000097   175 _P1_7	=	0x0097
                           000098   176 _RI	=	0x0098
                           000099   177 _TI	=	0x0099
                           00009A   178 _RB8	=	0x009a
                           00009B   179 _TB8	=	0x009b
                           00009C   180 _REN	=	0x009c
                           00009D   181 _SM2	=	0x009d
                           00009E   182 _SM1	=	0x009e
                           00009F   183 _SM0	=	0x009f
                           0000A0   184 _P2_0	=	0x00a0
                           0000A1   185 _P2_1	=	0x00a1
                           0000A2   186 _P2_2	=	0x00a2
                           0000A3   187 _P2_3	=	0x00a3
                           0000A4   188 _P2_4	=	0x00a4
                           0000A5   189 _P2_5	=	0x00a5
                           0000A6   190 _P2_6	=	0x00a6
                           0000A7   191 _P2_7	=	0x00a7
                           0000A8   192 _EX0	=	0x00a8
                           0000A9   193 _ET0	=	0x00a9
                           0000AA   194 _EX1	=	0x00aa
                           0000AB   195 _ET1	=	0x00ab
                           0000AC   196 _ES	=	0x00ac
                           0000AF   197 _EA	=	0x00af
                           0000B0   198 _P3_0	=	0x00b0
                           0000B1   199 _P3_1	=	0x00b1
                           0000B2   200 _P3_2	=	0x00b2
                           0000B3   201 _P3_3	=	0x00b3
                           0000B4   202 _P3_4	=	0x00b4
                           0000B5   203 _P3_5	=	0x00b5
                           0000B6   204 _P3_6	=	0x00b6
                           0000B7   205 _P3_7	=	0x00b7
                           0000B0   206 _RXD	=	0x00b0
                           0000B1   207 _TXD	=	0x00b1
                           0000B2   208 _INT0	=	0x00b2
                           0000B3   209 _INT1	=	0x00b3
                           0000B4   210 _T0	=	0x00b4
                           0000B5   211 _T1	=	0x00b5
                           0000B6   212 _WR	=	0x00b6
                           0000B7   213 _RD	=	0x00b7
                           0000B8   214 _PX0	=	0x00b8
                           0000B9   215 _PT0	=	0x00b9
                           0000BA   216 _PX1	=	0x00ba
                           0000BB   217 _PT1	=	0x00bb
                           0000BC   218 _PS	=	0x00bc
                           0000D0   219 _P	=	0x00d0
                           0000D1   220 _F1	=	0x00d1
                           0000D2   221 _OV	=	0x00d2
                           0000D3   222 _RS0	=	0x00d3
                           0000D4   223 _RS1	=	0x00d4
                           0000D5   224 _F0	=	0x00d5
                           0000D6   225 _AC	=	0x00d6
                           0000D7   226 _CY	=	0x00d7
                                    227 ;--------------------------------------------------------
                                    228 ; overlayable register banks
                                    229 ;--------------------------------------------------------
                                    230 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        231 	.ds 8
                                    232 ;--------------------------------------------------------
                                    233 ; internal ram data
                                    234 ;--------------------------------------------------------
                                    235 	.area DSEG    (DATA)
                                    236 ;--------------------------------------------------------
                                    237 ; overlayable items in internal ram 
                                    238 ;--------------------------------------------------------
                                    239 ;--------------------------------------------------------
                                    240 ; Stack segment in internal ram 
                                    241 ;--------------------------------------------------------
                                    242 	.area	SSEG
      000008                        243 __start__stack:
      000008                        244 	.ds	1
                                    245 
                                    246 ;--------------------------------------------------------
                                    247 ; indirectly addressable internal ram data
                                    248 ;--------------------------------------------------------
                                    249 	.area ISEG    (DATA)
                                    250 ;--------------------------------------------------------
                                    251 ; absolute internal ram data
                                    252 ;--------------------------------------------------------
                                    253 	.area IABS    (ABS,DATA)
                                    254 	.area IABS    (ABS,DATA)
                                    255 ;--------------------------------------------------------
                                    256 ; bit data
                                    257 ;--------------------------------------------------------
                                    258 	.area BSEG    (BIT)
                                    259 ;--------------------------------------------------------
                                    260 ; paged external ram data
                                    261 ;--------------------------------------------------------
                                    262 	.area PSEG    (PAG,XDATA)
                                    263 ;--------------------------------------------------------
                                    264 ; external ram data
                                    265 ;--------------------------------------------------------
                                    266 	.area XSEG    (XDATA)
                                    267 ;--------------------------------------------------------
                                    268 ; absolute external ram data
                                    269 ;--------------------------------------------------------
                                    270 	.area XABS    (ABS,XDATA)
                                    271 ;--------------------------------------------------------
                                    272 ; external initialized ram data
                                    273 ;--------------------------------------------------------
                                    274 	.area XISEG   (XDATA)
      000001                        275 _ms::
      000001                        276 	.ds 2
      000003                        277 _last_ms::
      000003                        278 	.ds 2
                                    279 	.area HOME    (CODE)
                                    280 	.area GSINIT0 (CODE)
                                    281 	.area GSINIT1 (CODE)
                                    282 	.area GSINIT2 (CODE)
                                    283 	.area GSINIT3 (CODE)
                                    284 	.area GSINIT4 (CODE)
                                    285 	.area GSINIT5 (CODE)
                                    286 	.area GSINIT  (CODE)
                                    287 	.area GSFINAL (CODE)
                                    288 	.area CSEG    (CODE)
                                    289 ;--------------------------------------------------------
                                    290 ; interrupt vector 
                                    291 ;--------------------------------------------------------
                                    292 	.area HOME    (CODE)
      000000                        293 __interrupt_vect:
      000000 02 00 11         [24]  294 	ljmp	__sdcc_gsinit_startup
      000003 32               [24]  295 	reti
      000004                        296 	.ds	7
      00000B 02 00 6D         [24]  297 	ljmp	_timer_isr
                                    298 ;--------------------------------------------------------
                                    299 ; global & static initialisations
                                    300 ;--------------------------------------------------------
                                    301 	.area HOME    (CODE)
                                    302 	.area GSINIT  (CODE)
                                    303 	.area GSFINAL (CODE)
                                    304 	.area GSINIT  (CODE)
                                    305 	.globl __sdcc_gsinit_startup
                                    306 	.globl __sdcc_program_startup
                                    307 	.globl __start__stack
                                    308 	.globl __mcs51_genXINIT
                                    309 	.globl __mcs51_genXRAMCLEAR
                                    310 	.globl __mcs51_genRAMCLEAR
                                    311 	.area GSFINAL (CODE)
      00006A 02 00 0E         [24]  312 	ljmp	__sdcc_program_startup
                                    313 ;--------------------------------------------------------
                                    314 ; Home
                                    315 ;--------------------------------------------------------
                                    316 	.area HOME    (CODE)
                                    317 	.area HOME    (CODE)
      00000E                        318 __sdcc_program_startup:
      00000E 02 00 CE         [24]  319 	ljmp	_main
                                    320 ;	return from main will return to caller
                                    321 ;--------------------------------------------------------
                                    322 ; code
                                    323 ;--------------------------------------------------------
                                    324 	.area CSEG    (CODE)
                                    325 ;------------------------------------------------------------
                                    326 ;Allocation info for local variables in function 'timer_isr'
                                    327 ;------------------------------------------------------------
                                    328 ;	tst1.c:26: void timer_isr(void) __interrupt(1) {
                                    329 ;	-----------------------------------------
                                    330 ;	 function timer_isr
                                    331 ;	-----------------------------------------
      00006D                        332 _timer_isr:
                           000007   333 	ar7 = 0x07
                           000006   334 	ar6 = 0x06
                           000005   335 	ar5 = 0x05
                           000004   336 	ar4 = 0x04
                           000003   337 	ar3 = 0x03
                           000002   338 	ar2 = 0x02
                           000001   339 	ar1 = 0x01
                           000000   340 	ar0 = 0x00
      00006D C0 E0            [24]  341 	push	acc
      00006F C0 82            [24]  342 	push	dpl
      000071 C0 83            [24]  343 	push	dph
      000073 C0 07            [24]  344 	push	ar7
      000075 C0 06            [24]  345 	push	ar6
      000077 C0 05            [24]  346 	push	ar5
      000079 C0 04            [24]  347 	push	ar4
      00007B C0 D0            [24]  348 	push	psw
      00007D 75 D0 00         [24]  349 	mov	psw,#0x00
                                    350 ;	tst1.c:27: TH0 = TICK >> 8;
      000080 75 8C F8         [24]  351 	mov	_TH0,#0xf8
                                    352 ;	tst1.c:28: TL0 = TICK & 0xFF;
      000083 75 8A 07         [24]  353 	mov	_TL0,#0x07
                                    354 ;	tst1.c:29: ++ms;
      000086 90 00 01         [24]  355 	mov	dptr,#_ms
      000089 E0               [24]  356 	movx	a,@dptr
      00008A 24 01            [12]  357 	add	a,#0x01
      00008C F0               [24]  358 	movx	@dptr,a
      00008D A3               [24]  359 	inc	dptr
      00008E E0               [24]  360 	movx	a,@dptr
      00008F 34 00            [12]  361 	addc	a,#0x00
      000091 F0               [24]  362 	movx	@dptr,a
                                    363 ;	tst1.c:30: if (ms - last_ms >= FLASH_MS) {
      000092 90 00 03         [24]  364 	mov	dptr,#_last_ms
      000095 E0               [24]  365 	movx	a,@dptr
      000096 FE               [12]  366 	mov	r6,a
      000097 A3               [24]  367 	inc	dptr
      000098 E0               [24]  368 	movx	a,@dptr
      000099 FF               [12]  369 	mov	r7,a
      00009A 90 00 01         [24]  370 	mov	dptr,#_ms
      00009D E0               [24]  371 	movx	a,@dptr
      00009E FC               [12]  372 	mov	r4,a
      00009F A3               [24]  373 	inc	dptr
      0000A0 E0               [24]  374 	movx	a,@dptr
      0000A1 FD               [12]  375 	mov	r5,a
      0000A2 EC               [12]  376 	mov	a,r4
      0000A3 C3               [12]  377 	clr	c
      0000A4 9E               [12]  378 	subb	a,r6
      0000A5 FE               [12]  379 	mov	r6,a
      0000A6 ED               [12]  380 	mov	a,r5
      0000A7 9F               [12]  381 	subb	a,r7
      0000A8 FF               [12]  382 	mov	r7,a
      0000A9 C3               [12]  383 	clr	c
      0000AA EE               [12]  384 	mov	a,r6
      0000AB 94 F4            [12]  385 	subb	a,#0xf4
      0000AD EF               [12]  386 	mov	a,r7
      0000AE 94 01            [12]  387 	subb	a,#0x01
      0000B0 40 0B            [24]  388 	jc	00103$
                                    389 ;	tst1.c:31: P1 ^= 1 << 4;
      0000B2 63 90 10         [24]  390 	xrl	_P1,#0x10
                                    391 ;	tst1.c:32: last_ms = ms;
      0000B5 90 00 03         [24]  392 	mov	dptr,#_last_ms
      0000B8 EC               [12]  393 	mov	a,r4
      0000B9 F0               [24]  394 	movx	@dptr,a
      0000BA ED               [12]  395 	mov	a,r5
      0000BB A3               [24]  396 	inc	dptr
      0000BC F0               [24]  397 	movx	@dptr,a
      0000BD                        398 00103$:
                                    399 ;	tst1.c:34: }
      0000BD D0 D0            [24]  400 	pop	psw
      0000BF D0 04            [24]  401 	pop	ar4
      0000C1 D0 05            [24]  402 	pop	ar5
      0000C3 D0 06            [24]  403 	pop	ar6
      0000C5 D0 07            [24]  404 	pop	ar7
      0000C7 D0 83            [24]  405 	pop	dph
      0000C9 D0 82            [24]  406 	pop	dpl
      0000CB D0 E0            [24]  407 	pop	acc
      0000CD 32               [24]  408 	reti
                                    409 ;	eliminated unneeded push/pop b
                                    410 ;------------------------------------------------------------
                                    411 ;Allocation info for local variables in function 'main'
                                    412 ;------------------------------------------------------------
                                    413 ;	tst1.c:36: int main(void) {
                                    414 ;	-----------------------------------------
                                    415 ;	 function main
                                    416 ;	-----------------------------------------
      0000CE                        417 _main:
                                    418 ;	tst1.c:37: P1MDOUT = 1 << 4 | 1 << 5 | 1 << 6;
      0000CE 75 A5 70         [24]  419 	mov	_P1MDOUT,#0x70
                                    420 ;	tst1.c:38: P1SKIP = 1 << 4 | 1 << 5 | 1 << 6;
      0000D1 75 D5 70         [24]  421 	mov	_P1SKIP,#0x70
                                    422 ;	tst1.c:39: XBR2 = 1 << 6;
      0000D4 75 E3 40         [24]  423 	mov	_XBR2,#0x40
                                    424 ;	tst1.c:53: CLKSEL = 0;
      0000D7 75 A9 00         [24]  425 	mov	_CLKSEL,#0x00
                                    426 ;	tst1.c:54: while (!(CLKSEL & 0x80)) { }
      0000DA                        427 00101$:
      0000DA E5 A9            [12]  428 	mov	a,_CLKSEL
      0000DC 30 E7 FB         [24]  429 	jnb	acc.7,00101$
                                    430 ;	tst1.c:66: CKCON0 = 0;
      0000DF 75 8E 00         [24]  431 	mov	_CKCON0,#0x00
                                    432 ;	tst1.c:69: TMOD = 1;
      0000E2 75 89 01         [24]  433 	mov	_TMOD,#0x01
                                    434 ;	tst1.c:72: TH0 = 0xFF;
      0000E5 75 8C FF         [24]  435 	mov	_TH0,#0xff
                                    436 ;	tst1.c:73: TL0 = 0xFF;
      0000E8 75 8A FF         [24]  437 	mov	_TL0,#0xff
                                    438 ;	tst1.c:75: TR0 = 1;
                                    439 ;	assignBit
      0000EB D2 8C            [12]  440 	setb	_TR0
                                    441 ;	tst1.c:76: ET0 = 1;
                                    442 ;	assignBit
      0000ED D2 A9            [12]  443 	setb	_ET0
                                    444 ;	tst1.c:77: EA = 1;
                                    445 ;	assignBit
      0000EF D2 AF            [12]  446 	setb	_EA
                                    447 ;	tst1.c:79: while (1) { }
      0000F1                        448 00105$:
                                    449 ;	tst1.c:81: return 0;
                                    450 ;	tst1.c:82: }
      0000F1 80 FE            [24]  451 	sjmp	00105$
                                    452 	.area CSEG    (CODE)
                                    453 	.area CONST   (CODE)
                                    454 	.area XINIT   (CODE)
      0000F7                        455 __xinit__ms:
      0000F7 00 00                  456 	.byte #0x00, #0x00	; 0
      0000F9                        457 __xinit__last_ms:
      0000F9 00 00                  458 	.byte #0x00, #0x00	; 0
                                    459 	.area CABS    (ABS,CODE)
