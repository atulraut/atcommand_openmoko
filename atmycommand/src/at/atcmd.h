/*
 * atcmd.h 
 *
 * Header file for atcmd.c
 * 
 * Authored by Atul Raut <rauji.raut@gmail.com>
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#define STDIN_BUF_SIZE	1024

#define GSMD_DELAY	1000000	

#define HWINDOW_SIZE	480
#define VWINDOW_SIZE	640

#define ATCMD_NUMBER 38
#define ATCMD_RETURNCHECK_NUMBER 3
#define ATCMD_TOTAL (ATCMD_NUMBER + ATCMD_RETURNCHECK_NUMBER)

/* for command-output entry */
typedef struct _amc_entry {
  gchar *command;
  gchar *output;
} amc_entry_t;

/* back-end data structures */
typedef struct _amc
{
  /* PIN handlers */
  struct lgsm_handle *lgsmh;
  gchar *pin;

  /* data structures */
  GSList *amc_list;
} amc_item_t;
