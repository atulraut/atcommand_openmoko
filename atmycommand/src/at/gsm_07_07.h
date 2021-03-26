/*
 * neo1973.h 
 *
 * Linked list implementation to store AT+OUTPUT results
 * 
 * Authored by Atul Ramesh Raut <rauji.raut@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#include <glib.h>

/* list of AT command strings */
typedef struct _item
{
  gchar string[15];
} item_t;

item_t list [] =  {
  {"AT"},	   /* 1 */	
    {"AT+CGMI"},   /* AT_2, 5.1 */
    {"AT+CGMM"},   /* AT_3, 5.2 */
    {"AT+CGMR"},   /* AT_4, 5.3 */

    /* {"AT+CGSN"}, just display OK, 5.4 */
 
    {"AT+CSCS=?"}, /* AT_5, 5.5 */
    /* {"AT+CIMI"}, just display OK,  5.6 */

    /* AT+CMUX? doesn't return anything, 5.7 */
    {"AT+CMUX=?"}, /* AT_6, 5.7 */
    {"AT+GMI"},    /* AT_7, 5.8 */
    {"AT+GMM"},    /* AT_8, 5.8 */
    {"AT+GMR"},    /* AT_9, 5.8 */
    {"AT+GSN"},    /* AT_10, 5.8 */
    /* Phone not supported   	
    {"AT+GOI"},             5.8  */	

    /* {"AT+GSN"}, just display OK, 5.8 */
    {"AT+GCAP"},   /* AT_11, 5.8 */

    /* optional, gives error {"AT+GCI"}, 5.8 */
    {"AT+WS46=?"}, /* AT_12, 5.9 */
    {"AT+CSTA?"},  /* AT_13, 6.0 */
    
    {"AT+CSTA=?"}, /* AT_14, 6.0 */
    {"AT+CMOD=?"}, /* AT_15, 6.1 */
    {"AT+CHUP"},   /* AT_16, 6.2 */
    {"AT+CBST?"},  /* AT_17, 6.3 */  

    {"AT+CBST=?"}, /* AT_18, 6.3 */
    {"AT+CRLP?"},  /* AT_19,6.4 */
    {"AT+CRLP=?"}, /* AT_20, 6.4 */  

    {"AT+CR=?"},   /* AT_21, 6.5 */
    {"AT+CEER"},   /* AT_22, 6.6 */
    {"AT+CRC?"},   /* AT_23, 6.7 */
    {"AT+CRC=?"},  /* AT_24, 6.7 */  /* count: 25 */

    /* 
     * No support yet for
     * AT+CHSD, 6.12
     * AT+CHST, 6.13
     * AT+CHSN, 6.14
     * AT+CHSC, 6.15 	
     * AT+CHSR, 6.16
     * AT+CHSU, 6.17
     */

    {"AT+CSNS=?"},  /*s AT_25, 6.18 * No support yet */

    /* 
     * No support yet for
     * AT+CVHU,  6.19
     * AT+CV120, 6.20
     */

    /* 6.21 ITU-T V.25ter [14] call control commands 
     * D[<dial_
     * string>][;]
    */
	
    /* 6.22 ITU-T V.25ter [14] data compression commands
     * +DS=[<dir>[,<neg> 6.6.1[,<P1>[,<P2>]]]] 
    */
    /* 7] Network service related commands       
   */	
    {"AT+CNUM=?"}, /* AT_26, 7.1 */
    {"AT+CREG?"},  /* AT_27, 7.2 */
    {"AT+CREG=?"}, /* AT_28, 7.2 */      
    {"AT+COPS?"},  /* AT_29, 7.3 */
    /* Phone not supported   	
    {"AT+CLCK"},             7.4 */
    {"AT+CLCK=?"}, /* AT_30 , 7.4 */    
    {"AT++CPWD?"},/* AT_31,  7.5 */
/* Below one Commands Returns Error */
    {"AT++CPWD=?"},/* AT_32, 7.5 */
    {"AT+CLIP?"},/* AT_33,  7.6 */
    {"AT+CLIP=?"},/* AT_34, 7.6 */
    {"AT+CLIR?"},/* AT_35,  7.7 */
    {"AT+CLIR=?"},/* AT_36, 7.7 */
    {"AT+COLP?"},/* AT_37,  7.8 */
    {"AT+COLP=?"},/* AT_38, 7.8 */
    {"AT+CCUG?"},/* AT_39,  7.9 */
    {"AT+CCUG=?"},/* AT_40, 7.9 */
    {"AT+CCFC=?"},/* AT_41, 7.10 */  	
    {"AT+CCWA?"},/* AT_42,  7.11 */
    {"AT+CCWA=?"},/* AT_43, 7.11 */    
    {"AT+CHLD=?"},/* AT_44, 7.12 */
    {"AT+CTFR=?"},/* AT_45, 7.13 */
    {"AT+CUSD?"},/* AT_46,  7.14 */
    {"AT+CUSD=?"},/* AT_47, 7.14 */
    {"AT+CAOC?"},/* AT_48,  7.15 */
    {"AT+CAOC=?"},/* AT_49, 7.15 */
    {"AT+CSSN?"},/* AT_50,  7.16 */
    {"AT+CSSN=?"},/* AT_51, 7.16 */
    {"AT+CLCC?"},/* AT_52,  7.17 */
    {"AT+CLCC=?"},/* AT_53, 7.17 */
    {"AT+CPOL=?"},/* AT_54, 7.18 */
    {"AT+COPN=?"},/* AT_55, 7.19 */
    {"ATE1"},      /* AT_56  Use to manually test SMS in neo1973 */
    {"AT+CPAS?"},/* AT_57,  8.1 */
    {"AT+CPAS=?"},/* AT_58, 8.1 */
    {"AT+CFUN?"},  /* AT_59, 8.2 */
    {"AT+CFUN=?"}, /* AT_60  8.2 */
    {"AT+CPIN?"},  /* AT_61, 8.3 */
    {"AT+CBC"},	   /* AT_62, 8.4 */
    {"AT+CBC=?"},  /* AT_63, 8.4 */    
    {"AT+CSQ=?"},  /* AT_64, 8.5 */ 
    /* Phone not supported   	   
    {"AT+CMEC=1,0,0"},       8.6 */
    {"AT+CKPD=C,20"},/* AT_65, 8.7 */
    /* Phone not supported   	    	       
    {"AT+CDIS?"},            8.8 */
    {"AT+CIND?"},  /* AT_66, 8.9 */
    {"AT+CIND=?"}, /* AT_67, 8.9 */
    {"AT+CMER?"},  /* AT_68, 8.10 */
    {"AT+CMER=?"}, /* AT_69, 8.10 */
    {"AT+CPBS?"},  /* AT_70, 8.11 */
    {"AT+CPBS=?"}, /* AT_71, 8.11 */

    /* Result unkonw of below 2 commnad */		    
    {"AT+CPBR=?"}, /* AT_72, 8.12 */    
    {"AT+CPBF=?"}, /* AT_73, 8.13 */
  
    {"AT+CPBW?"},  /* AT_74, 8.14 */
    {"AT+CCLK?"},  /* AT_75, 8.15 */
    {"AT+CCLK=?"}, /* AT_76, 8.15 */
    /* Phone not supported 
    {"AT+CALA?"},            8.16 */    
    {"AT+CSIM=?"}, /* AT_77, 8.17 */
    {"AT+CRSM=?"}, /* AT_78, 8.18 */
    /* Phone not supported 
    {"AT+CSCC?=?"},          8.19 
    {"AT+CALM=?"},           8.20 */
    {"AT+CRSL?"},  /* AT_79, 8.21 */
    {"AT+CRSL=?"}, /* AT_80, 8.21 */
/* Phone not supported 
    {"AT+CVIB?"},            8.22 */    
    {"AT+CLVL?"},  /* AT_81, 8.23 */
    {"AT+CLVL=?"}, /* AT_82, 8.23 */
    {"AT+CMUT?"},  /* AT_83, 8.24 */
    {"AT+CMUT=?"}, /* AT_84, 8.24 */
    {"AT+CACM?"},  /* AT_85, 8.25 */
    {"AT+CACM=?"}, /* AT_86, 8.25 */
    {"AT+CAMM?"},  /* AT_87, 8.26 */
    {"AT+CAMM=?"}, /* AT_88, 8.26 */
    {"AT+CPUC?"},  /* AT_89, 8.27 */
    {"AT+CPUC=?"}, /* AT_90, 8.27 */
    {"AT+CCWE?"},  /* AT_91, 8.28 */
    {"AT+CCWE=?"}, /* AT_92, 8.28 */
/* Phone not supported 
    {"AT+CPWC?"},            8.29 
    {"AT+CLAN?"},            8.30 */
    {"AT+CLAE?"},  /* AT_93, 8.31 */
    {"AT+CLAE=?"}, /* AT_94, 8.31 */
/* Phone not supported 
    {"AT+CSGT?"},            8.32 */
    {"AT+CSVM?"},  /* AT_95, 8.33 */
    {"AT+CSVM=?"}, /* AT_96, 8.33 */
/* Phone not supported 
    {"AT+CRMP=?"},           8.34 
    {"AT+CMAR=?"},           8.35 */
    {"AT+CLAC=?"}, /* AT_97, 8.36 */ 
    {"AT+CMEE?"},  /* AT_98, 9.1 */ 
    {"AT+CMEE=?"}, /* AT_99, 9.1 */ 
    {"AT+CGDCONT?"},/* AT_100, 10.1.1 */
    {"AT+CGDCONT=?"},/* AT_101 ,10.1.1 */
    {"AT+CGQREQ?"},/* AT_102, 10.1.2 */
    {"AT+CGQREQ=?"},/* AT_103,10.1.2 */
    {"AT+CGQMIN?"},/* AT_104, 10.1.3 */
    {"AT+CGQMIN=?"},/* AT_105,10.1.3 */
    {"AT+CGATT?"}, /* AT_106, 10.1.4 */
    {"AT+CGATT=?"},/* AT_107, 10.1.4 */
    {"AT+CGACT=?"},/* AT_108, 10.1.5 */
    {"AT+CGDATA?"},/* AT_109, 10.1.6 */
    {"AT+CGDATA=?"},/* AT_110,10.1.6 */
/* Phone not supported
    {"AT+CGCLOSP=?"},        10.1.7 
    {"AT+CGPADDR?"},         10.1.8 
    {"AT+CGPADDR?"},         10.1.8 */
    {"AT+CGAUTO?"},/* AT_111, 10.1.9 */
    {"AT+CGAUTO=?"},/*AT_112, 10.1.9 */    
    {"AT+CGANS=?"},/* AT_113, 10.1.10 */
    {"AT+CGCLASS?"},/*AT_114, 10.1.11 */
    {"AT+CGCLASS=?"},/*AT_115,10.1.11 */
/* Phone not supported 
    {"AT+CGCLPAD=?"},        10.1.12 */
    {"AT+CGEREP?"},/* AT_116, 10.1.13 */
    {"AT+CGEREP=?"},/*AT_117, 10.1.13 */    
    {"AT+CGREG?"}, /* AT_118,  10.1.14 */
    {"AT+CGREG=?"},/* AT_119, 10.1.14 */     
    {"AT+CGSMS?"},/* AT_120,  10.1.15 */
    {"AT+CGSMS=?"},/* AT_121, 10.1.15 */ 


};

item_t return_custom[] = {
  {"AT+CGSN"},
  {"AT+GSN"},
  {"AT+CIMI"},
};
