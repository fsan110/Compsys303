/*
 * pacemakerFSM.c
 *
 *  Created on: 16/09/2019
 *      Author: utri092
 */


char ASense;
char AEITO;
char APace;
char VRP_stop;
char LRI_stop;
char URI_stop;
char AVI_stop;
char PVARP_stop;
char AEI_stop;
char VSense;
char VRPTO;
char LRITO;
char URITO;
char AVITO;
char PVARPTO;
char VPace;
char VRP_start;
char LRI_start;
char URI_start;
char AVI_start;
char PVARP_start;
char AEI_start;
char _DDDPacemaker_local_AEI_ex;
char _DDDPacemaker_local_VRP_ex;
char _DDDPacemaker_local_LRI_ex;
char _DDDPacemaker_local_URI_ex;
char _DDDPacemaker_local_AVI_ex;
char _DDDPacemaker_local_PVARP_ex;
char _DDDPacemaker_local__pre_URI_ex3;
char _DDDPacemaker_local__reg_URI_ex3;
char g0;
char g1;
char g2;
char g3;
char PRE_g3;
char g4;
char g4b;
char g5;
char PRE_g5;
char g6;
char g7;
char g8;
char g9;
char g10;
char PRE_g10;
char g11;
char g11b;
char g12;
char g13;
char PRE_g13;
char g14;
char g14b;
char g15;
char g16;
char g17;
char g18;
char g19;
char g20;
char g21;
char g22;
char PRE_g22;
char g23;
char g23b;
char g24;
char g25;
char g26;
char PRE_g26;
char g27;
char g28;
char g29;
char g30;
char PRE_g30;
char g31;
char g31b;
char g32;
char g33;
char PRE_g33;
char g34;
char g34b;
char g35;
char PRE_g35;
char g36;
char g36b;
char g37;
char PRE_g37;
char g38;
char g38b;
char g39;
char g40;
char g41;
char g42;
char g43;
char g44;
char g45;
char g46;
char g47;
char PRE_g47;
char g48;
char g48b;
char g49;
char g50;
char PRE_g50;
char g51;
char g51b;
char g52;
char PRE_g52;
char g53;
char g54;
char g55;
char g56;
char g57;
char g58;
char g59;
char g60;
char PRE_g60;
char g61;
char g61b;
char g62;
char PRE_g62;
char g63;
char g64;
char g65;
char g66;
char g67;
char PRE_g67;
char g68;
char g68b;
char g69;
char PRE_g69;
char g70;
char g71;
char g72;
char g73;
char g74;
char PRE_g74;
char g75;
char g75b;
char g76;
char g77;
char PRE_g77;
char g78;
char g78b;
char g79;
char PRE_g79;
char g80;
char g80b;
char g81;
char g82;
char g83;
char g84;
char g85;
char g86;
char g87;
char PRE_g87;
char g88;
char g88b;
char g89;
char PRE_g89;
char g90;
char g90b;
char g91;
char g92;
char g93;
char g94;
char g95;
char PRE_g95;
char g96;
char g97;
char g98;
char PRE_g98;
char g99;
char g99b;
char g100;
char PRE_g100;
char g101;
char g101b;
char g102;
char PRE_g102;
char g103;
char g104;
char g105;
char g106;
char g107;
char g108;
char g109;
char g110;
char g111;
char PRE_g111;
char g112;
char g112b;
char g113;
char PRE_g113;
char g114;
char g114b;
char g115;
char g116;
char g117;
char g118;
char g119;
char PRE_g119;
char g120;
char g121;
char g122;
char PRE_g122;
char g123;
char g123b;
char g124;
char g125;
char PRE_g125;
char g126;
char g126b;
char g127;
char PRE_g127;
char g128;
char g128b;
char g129;
char g130;
char PRE_g130;
char g131;
char g131b;
char g132;
char PRE_g132;
char g133;
char g133b;
char g134;
char g134b;
char g135;
char g136;
char g137;
char g138;
char PRE_g138;
char g139;
char g139b;
char g140;
char g141;
char PRE_g141;
char g142;
char g142b;
char g143;
char g144;
char g145;
char g146;
char PRE_g146;
char g147;
char g148;
char g149;
char g150;
char PRE_g150;
char g151;
char g152;
char g153;
char g154;
char g155;
char PRE_g155;
char g156;
char g157;
char g158;
char _GO;
char _cg4;
char _cg6;
char _cg17;
char _cg11;
char _cg16;
char _cg14;
char _cg23;
char _cg21;
char _cg24;
char _cg43;
char _cg31;
char _cg34;
char _cg36;
char _cg41;
char _cg38;
char _cg56;
char _cg48;
char _cg51;
char _cg53;
char _cg54;
char _cg61;
char _cg63;
char _cg68;
char _cg70;
char _cg83;
char _cg75;
char _cg78;
char _cg82;
char _cg80;
char _cg90;
char _cg88;
char _cg91;
char _cg107;
char _cg96;
char _cg99;
char _cg101;
char _cg105;
char _cg103;
char _cg114;
char _cg112;
char _cg115;
char _cg143;
char _cg120;
char _cg131;
char _cg137;
char _cg123;
char _cg126;
char _cg142;
char _cg135;
char _cg128;
char _cg133;
char _cg140;
char g8_e1;
char g19_e2;
char g28_e3;
char g45_e4;
char g58_e5;
char g65_e6;
char g72_e7;
char g85_e8;
char g93_e9;
char g109_e10;
char g117_e11;
char g144_e12;
char g148_e13;
char g152_e14;
char g153_fix0;
char g153_fix1;
char g153_fix2;
char g153_fix3;
char g153_fix4;
char g153_e1_fix_fix_fix;
char g153_e1_fix_fix;
char g153_e1_fix;
char g153_e1;
char g157_e2;
int _PRE_GO;
void reset(){
   _GO = 1;
   _PRE_GO = 0;
   PRE_g3 = 0;
   PRE_g5 = 0;
   PRE_g10 = 0;
   PRE_g13 = 0;
   PRE_g22 = 0;
   PRE_g26 = 0;
   PRE_g30 = 0;
   PRE_g33 = 0;
   PRE_g35 = 0;
   PRE_g37 = 0;
   PRE_g47 = 0;
   PRE_g50 = 0;
   PRE_g52 = 0;
   PRE_g60 = 0;
   PRE_g62 = 0;
   PRE_g67 = 0;
   PRE_g69 = 0;
   PRE_g74 = 0;
   PRE_g77 = 0;
   PRE_g79 = 0;
   PRE_g87 = 0;
   PRE_g89 = 0;
   PRE_g95 = 0;
   PRE_g98 = 0;
   PRE_g100 = 0;
   PRE_g102 = 0;
   PRE_g111 = 0;
   PRE_g113 = 0;
   PRE_g119 = 0;
   PRE_g122 = 0;
   PRE_g125 = 0;
   PRE_g127 = 0;
   PRE_g130 = 0;
   PRE_g132 = 0;
   PRE_g138 = 0;
   PRE_g141 = 0;
   PRE_g146 = 0;
   PRE_g150 = 0;
   PRE_g155 = 0;
   return;
}
void tick(){
   if(_PRE_GO == 1){
      _GO = 0;
   }
   {
      g0 = _GO;
      g1 = g0;
      g2 = g1;
      g147 =(PRE_g146);
      g145 = g1;
      g146 =(g147||g145);
      if(g146){
         _DDDPacemaker_local_VRP_ex = 0;
         _DDDPacemaker_local_LRI_ex = 0;
         _DDDPacemaker_local_URI_ex = 0;
         _DDDPacemaker_local_AVI_ex = 0;
         _DDDPacemaker_local_PVARP_ex = 0;
         _DDDPacemaker_local_AEI_ex = 0;
      }
      g6 =(PRE_g5);
      _cg6 = VRPTO;
      g7 =(g6&&_cg6);
      if(g7){
         _DDDPacemaker_local_VRP_ex =(_DDDPacemaker_local_VRP_ex||1);
      }
      g156 =(PRE_g155);
      g154 = g0;
      g155 =(g156||g154);
      if(g155){
         VPace = 0;
         APace = 0;
         VRP_start = 0;
         VRP_stop = 0;
         LRI_start = 0;
         LRI_stop = 0;
         URI_start = 0;
         URI_stop = 0;
         AVI_start = 0;
         AVI_stop = 0;
         PVARP_start = 0;
         PVARP_stop = 0;
         AEI_start = 0;
         AEI_stop = 0;
      }
      g139 =(PRE_g138);
      g139b = g139;
      if(g139b){
         VPace =(VPace||1);
      }
      g151 =(PRE_g150);
      if(g151){
         _DDDPacemaker_local__pre_URI_ex3 = _DDDPacemaker_local__reg_URI_ex3;
      }
      g133 =(PRE_g132);
      g133b = g133;
      _cg133 = _DDDPacemaker_local__pre_URI_ex3;
      g134 =(g133b&&_cg133);
      if(g134){
         AVI_stop =(AVI_stop||1);
      }
      g134b = g134;
      if(g134b){
         VPace =(VPace||1);
      }
      g38 =(PRE_g37);
      g38b = g38;
      _cg38 =(VSense||VPace);
      g39 =(g38b&&_cg38);
      if(g39){
         LRI_stop =(LRI_stop||1);
      }
      g23 =(PRE_g22);
      g23b = g23;
      _cg23 = LRI_stop;
      g24 =(g23b&&(!(_cg23)));
      _cg24 = LRITO;
      g25 =(g24&&_cg24);
      if(g25){
         _DDDPacemaker_local_LRI_ex =(_DDDPacemaker_local_LRI_ex||1);
      }
      g41 =(g38b&&(!(_cg38)));
      _cg41 = _DDDPacemaker_local_LRI_ex;
      g42 =(g41&&_cg41);
      if(g42){
         VPace =(VPace||1);
      }
      g40 =(g42||g39);
      if(g40){
         LRI_start =(LRI_start||1);
      }
      g31 =(PRE_g30);
      g31b = g31;
      _cg31 = VPace;
      g32 =(g31b&&_cg31);
      if(g32){
         LRI_start =(LRI_start||1);
      }
      g43 =(g31b&&(!(_cg31)));
      _cg43 = VSense;
      g44 =(g43&&_cg43);
      if(g44){
         LRI_start =(LRI_start||1);
      }
      g48 =(PRE_g47);
      g48b = g48;
      _cg48 = VPace;
      g49 =(g48b&&_cg48);
      if(g49){
         URI_start =(URI_start||1);
      }
      g56 =(g48b&&(!(_cg48)));
      _cg56 = VSense;
      g57 =(g56&&_cg56);
      if(g57){
         URI_start =(URI_start||1);
      }
      g11 =(PRE_g10);
      g11b = g11;
      _cg11 =(VPace&&(URI_start&&LRI_start));
      g12 =(g11b&&_cg11);
      if(g12){
         VRP_start =(VRP_start||1);
      }
      g17 =(g11b&&(!(_cg11)));
      _cg17 =(VSense&&(URI_start&&LRI_start));
      g18 =(g17&&_cg17);
      if(g18){
         VRP_start =(VRP_start||1);
      }
      g4 =(PRE_g3);
      g4b = g4;
      _cg4 = VRP_start;
      g3 =(g2||g7||(g4b&&(!(_cg4))));
      g5 =((g4b&&_cg4)||(g6&&(!(_cg6))));
      g9 = g1;
      g14 =(PRE_g13);
      g14b = g14;
      _cg14 = _DDDPacemaker_local_VRP_ex;
      g15 =(g14b&&_cg14);
      if(g15){
         VRP_stop =(VRP_stop||1);
      }
      g10 =(g15||(g17&&(!(_cg17)))||g9);
      g16 =(g14b&&(!(_cg14)));
      _cg16 = VSense;
      g13 =((g16&&_cg16)||g12||g18||(g16&&_cg16));
      g20 = g1;
      g27 =(PRE_g26);
      g21 =(g20||g27||g25||(g23b&&_cg23));
      _cg21 = LRI_start;
      g22 =((g21&&_cg21)||(g24&&(!(_cg24))));
      g26 =(g21&&(!(_cg21)));
      g29 = g1;
      g30 =(g29||(g43&&(!(_cg43))));
      g34 =(PRE_g33);
      g34b = g34;
      _cg34 = _DDDPacemaker_local_VRP_ex;
      g33 =((g34b&&(!(_cg34)))||g32||g44||g40);
      g63 =(PRE_g62);
      _cg63 = URITO;
      g64 =(g63&&_cg63);
      if(g64){
         _DDDPacemaker_local_URI_ex =(_DDDPacemaker_local_URI_ex||1);
      }
      g36 =(PRE_g35);
      g36b = g36;
      _cg36 = _DDDPacemaker_local_URI_ex;
      g35 =((g36b&&(!(_cg36)))||(g34b&&_cg34));
      g37 =((g41&&(!(_cg41)))||(g36b&&_cg36));
      g46 = g1;
      g53 =(PRE_g52);
      _cg53 = VSense;
      g54 =(g53&&(!(_cg53)));
      _cg54 = _DDDPacemaker_local_URI_ex;
      g55 =(g54&&_cg54);
      if(g55){
         URI_stop =(URI_stop||1);
      }
      g47 =((g56&&(!(_cg56)))||g46||g55);
      g51 =(PRE_g50);
      g51b = g51;
      _cg51 = _DDDPacemaker_local_VRP_ex;
      g50 =(g57||(g51b&&(!(_cg51)))||g49);
      g52 =((g53&&_cg53)||(g51b&&_cg51)||(g54&&(!(_cg54))));
      g59 = g1;
      g61 =(PRE_g60);
      g61b = g61;
      _cg61 = URI_start;
      g60 =(g59||(g61b&&(!(_cg61)))||g64);
      g62 =((g63&&(!(_cg63)))||(g61b&&_cg61));
      g66 = g1;
      g70 =(PRE_g69);
      _cg70 = PVARPTO;
      g71 =(g70&&_cg70);
      if(g71){
         _DDDPacemaker_local_PVARP_ex =(_DDDPacemaker_local_PVARP_ex||1);
      }
      g75 =(PRE_g74);
      g75b = g75;
      _cg75 =(VSense&&(URI_start&&LRI_start));
      g76 =(g75b&&_cg75);
      if(g76){
         PVARP_start =(PVARP_start||1);
      }
      g83 =(g75b&&(!(_cg75)));
      _cg83 =(VPace&&(URI_start&&LRI_start));
      g84 =(g83&&_cg83);
      if(g84){
         PVARP_start =(PVARP_start||1);
      }
      g68 =(PRE_g67);
      g68b = g68;
      _cg68 = PVARP_start;
      g67 =(g71||(g68b&&(!(_cg68)))||g66);
      g69 =((g68b&&_cg68)||(g70&&(!(_cg70))));
      g73 = g1;
      g80 =(PRE_g79);
      g80b = g80;
      _cg80 = _DDDPacemaker_local_PVARP_ex;
      g81 =(g80b&&_cg80);
      if(g81){
         PVARP_stop =(PVARP_stop||1);
      }
      g74 =((g83&&(!(_cg83)))||g73||g81);
      g78 =(PRE_g77);
      g78b = g78;
      _cg78 = _DDDPacemaker_local_VRP_ex;
      g77 =(g76||(g78b&&(!(_cg78)))||g84);
      g82 =(g80b&&(!(_cg80)));
      _cg82 = ASense;
      g79 =((g82&&_cg82)||(g78b&&_cg78)||(g82&&_cg82));
      g86 = g1;
      g96 =(PRE_g95);
      _cg96 = VSense;
      g97 =(g96&&_cg96);
      if(g97){
         AEI_start =(AEI_start||1);
      }
      g107 =(g96&&(!(_cg96)));
      _cg107 = VPace;
      g108 =(g107&&_cg107);
      if(g108){
         AEI_start =(AEI_start||1);
      }
      g88 =(PRE_g87);
      g88b = g88;
      _cg88 = AEI_start;
      g103 =(PRE_g102);
      _cg103 = ASense;
      g104 =(g103&&_cg103);
      if(g104){
         AEI_stop =(AEI_stop||1);
      }
      g90 =(PRE_g89);
      g90b = g90;
      _cg90 = AEI_stop;
      g91 =(g90b&&(!(_cg90)));
      _cg91 = AEITO;
      g92 =(g91&&_cg91);
      if(g92){
         _DDDPacemaker_local_AEI_ex =(_DDDPacemaker_local_AEI_ex||1);
      }
      g87 =((g88b&&(!(_cg88)))||g86||g92||(g90b&&_cg90));
      g89 =((g88b&&_cg88)||(g91&&(!(_cg91))));
      g94 = g1;
      g105 =(g103&&(!(_cg103)));
      _cg105 = _DDDPacemaker_local_AEI_ex;
      g106 =(g105&&_cg105);
      if(g106){
         APace =(APace||1);
      }
      g95 =(g106||(g107&&(!(_cg107)))||g104||g94);
      g99 =(PRE_g98);
      g99b = g99;
      _cg99 = _DDDPacemaker_local_VRP_ex;
      g98 =(g108||(g99b&&(!(_cg99)))||g97);
      g101 =(PRE_g100);
      g101b = g101;
      _cg101 = _DDDPacemaker_local_PVARP_ex;
      g100 =((g99b&&_cg99)||(g101b&&(!(_cg101))));
      g102 =((g105&&(!(_cg105)))||(g101b&&_cg101));
      g110 = g1;
      g120 =(PRE_g119);
      _cg120 = ASense;
      g121 =(g120&&_cg120);
      if(g121){
         AVI_start =(AVI_start||1);
      }
      g128 =(PRE_g127);
      g128b = g128;
      _cg128 = APace;
      g129 =(g128b&&_cg128);
      if(g129){
         AVI_start =(AVI_start||1);
      }
      g135 =(g128b&&(!(_cg128)));
      _cg135 = ASense;
      g136 =(g135&&_cg135);
      if(g136){
         AVI_start =(AVI_start||1);
      }
      g112 =(PRE_g111);
      g112b = g112;
      _cg112 = AVI_start;
      g123 =(PRE_g122);
      g123b = g123;
      _cg123 =(VPace||VSense);
      g124 =(g123b&&_cg123);
      if(g124){
         AVI_stop =(AVI_stop||1);
      }
      g114 =(PRE_g113);
      g114b = g114;
      _cg114 = AVI_stop;
      g115 =(g114b&&(!(_cg114)));
      _cg115 = AVITO;
      g116 =(g115&&_cg115);
      if(g116){
         _DDDPacemaker_local_AVI_ex =(_DDDPacemaker_local_AVI_ex||1);
      }
      g111 =((g112b&&(!(_cg112)))||g110||(g114b&&_cg114)||g116);
      g113 =((g115&&(!(_cg115)))||(g112b&&_cg112));
      g118 = g1;
      g140 =(g120&&(!(_cg120)));
      _cg140 = VPace;
      g143 =(g140&&(!(_cg140)));
      _cg143 = VSense;
      g119 =(g118||(g143&&(!(_cg143))));
      g131 =(PRE_g130);
      g131b = g131;
      _cg131 = _DDDPacemaker_local_URI_ex;
      g137 =(g123b&&(!(_cg123)));
      _cg137 = _DDDPacemaker_local_AVI_ex;
      g122 =(g121||(g131b&&_cg131)||(g137&&(!(_cg137))));
      g126 =(PRE_g125);
      g126b = g126;
      _cg126 = _DDDPacemaker_local_PVARP_ex;
      g142 =(PRE_g141);
      g142b = g142;
      _cg142 = _DDDPacemaker_local_VRP_ex;
      g125 =((g126b&&(!(_cg126)))||g124||(g142b&&_cg142)||g139b||g134b);
      g127 =((g126b&&_cg126)||(g135&&(!(_cg135))));
      g130 =(g129||g136);
      g132 =((g131b&&(!(_cg131)))||(g133b&&(!(_cg133))));
      g138 =(g137&&_cg137);
      g141 =((g143&&_cg143)||(g142b&&(!(_cg142)))||(g140&&_cg140));
      g149 = g1;
      g150 =(g149||g151);
      if(g150){
         _DDDPacemaker_local__reg_URI_ex3 = _DDDPacemaker_local_URI_ex;
      }
      g8_e1 =(!((g4||g6)));
      g19_e2 =(!((g11||g14)));
      g28_e3 =(!((g23||g27)));
      g45_e4 =(!((g31||g34||g36||g38)));
      g58_e5 =(!((g48||g51||g53)));
      g65_e6 =(!((g61||g63)));
      g72_e7 =(!((g68||g70)));
      g85_e8 =(!((g75||g78||g80)));
      g93_e9 =(!((g88||g90)));
      g109_e10 =(!((g96||g99||g101||g103)));
      g117_e11 =(!((g112||g114)));
      g144_e12 =(!((g120||g123||g142||g126||g139||g128||g131||g133)));
      g148_e13 =(!(g147));
      g152_e14 =(!(g151));
      g153_fix0 =((g8_e1||g8)&&(g19_e2||g19)&&(g28_e3||g28)&&(g45_e4||g45));
      g153_fix1 =(g153_fix0&&(g58_e5||g58)&&(g65_e6||g65)&&(g72_e7||g72));
      g153_fix2 =(g153_fix1&&(g85_e8||g85)&&(g93_e9||g93)&&(g109_e10||g109));
      g153_fix3 =(g8||g19||g28||g45);
      g153_fix4 =(g153_fix3||g58||g65||g72);
      g153_e1_fix_fix_fix =(g123||g142||g36||g53||g80||g101||g126||g139||g147||g38||g103);
      g153_e1_fix_fix =(g70||g90||g114||g14||g34||g51||g78||g99||g128||g153_e1_fix_fix_fix);
      g153_e1_fix =(g96||g112||g120||g23||g27||g151||g6||g63||g131||g153_e1_fix_fix);
      g153_e1 =(!((g4||g11||g31||g48||g61||g68||g75||g88||g133||g153_e1_fix)));
      g157_e2 =(!(g156));
   }
   PRE_g3 = g3;
   PRE_g5 = g5;
   PRE_g10 = g10;
   PRE_g13 = g13;
   PRE_g22 = g22;
   PRE_g26 = g26;
   PRE_g30 = g30;
   PRE_g33 = g33;
   PRE_g35 = g35;
   PRE_g37 = g37;
   PRE_g47 = g47;
   PRE_g50 = g50;
   PRE_g52 = g52;
   PRE_g60 = g60;
   PRE_g62 = g62;
   PRE_g67 = g67;
   PRE_g69 = g69;
   PRE_g74 = g74;
   PRE_g77 = g77;
   PRE_g79 = g79;
   PRE_g87 = g87;
   PRE_g89 = g89;
   PRE_g95 = g95;
   PRE_g98 = g98;
   PRE_g100 = g100;
   PRE_g102 = g102;
   PRE_g111 = g111;
   PRE_g113 = g113;
   PRE_g119 = g119;
   PRE_g122 = g122;
   PRE_g125 = g125;
   PRE_g127 = g127;
   PRE_g130 = g130;
   PRE_g132 = g132;
   PRE_g138 = g138;
   PRE_g141 = g141;
   PRE_g146 = g146;
   PRE_g150 = g150;
   PRE_g155 = g155;
   _PRE_GO = _GO;
   return;
}
