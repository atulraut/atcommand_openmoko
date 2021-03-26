/* 
 * atcmd.c
 *
 * Handles AT run tests
 *
 * (C) 2006-2007 by OpenMoko, Inc.
 * Written by Harald Welte <laforge@openmoko.org>
 * All Rights Reserved
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */ 

#include <glib.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include <libgsmd/libgsmd.h>
#include <string.h>
#include <at/atcmd.h>
#include <ui/support.h>
#include <at/gsm_07_07.h>

extern FILE *g_fp_logfile;
static gchar const *GS_VALID	= "VALID";
static gchar const *GS_INVALID	= "INVALID";

/* This is the handler for receiving passthrough responses */
static gint 
pt_msghandler (struct lgsm_handle *lh, struct gsmd_msg_hdr *gmh)
{
  gchar *payload = (char *) gmh + sizeof (*gmh);
  g_printf ("RFOOOOOOOOOSTR=`%s'\n", payload);
}

/* Interaction with lgsm_passthrough */
gint 
atcmd_command_main (struct lgsm_handle *lgsmh, gchar *buf)
{
  gchar rbuf[STDIN_BUF_SIZE+1];
  gint rlen = strlen (rbuf);

  g_assert (buf);

  g_printf ("STR=`%s'\n", buf);
  lgsm_passthrough (lgsmh, buf, rbuf, &rlen);
  g_printf ("RSTR=`%s'\n", rbuf);

  /* Add to linked list */	
  ll_add_to_list (buf, rbuf);

  /* Log to file */
  if (g_fp_logfile)
    {
      log_write_to_file (g_fp_logfile, buf);
      log_write_to_file (g_fp_logfile, rbuf);
    }

  return 0;
}

/* Just say "VALID" for output numbers that shouldn't be displayed :) */
gint 
atcmd_return_checked_command_main (struct lgsm_handle *lgsmh, gchar *buf)
{
  gint i = 0;
  gchar rbuf [STDIN_BUF_SIZE+1];
  gint rlen = strlen (rbuf);
  gboolean alphabet = FALSE;

  g_assert (buf);

  g_printf ("STR=`%s'\n", buf);
  lgsm_passthrough (lgsmh, buf, rbuf, &rlen);
  g_printf ("RSTR=`%s'\n", rbuf);

  /* If there is a semi-colon, rip everything before it */
  if (strchr (rbuf, ' '))
    strcpy (rbuf, strchr (rbuf, ' '));

  /* Remove leading and trailing white-space */
  g_strstrip (rbuf);

  /* Check if it is only numeric */
  for (i=0; i<strlen (rbuf); i++)
    {
      if (!g_ascii_isdigit (rbuf[i]))
	{
	  alphabet = TRUE;
	  break;
	}
    }

  /* Clear buffer before assigning value */
  memset (rbuf, ' ', strlen (rbuf));

  if (alphabet == TRUE)
    g_stpcpy (rbuf, GS_INVALID);
  else
    g_stpcpy (rbuf, GS_VALID);

  /* Add to linked list */	
  ll_add_to_list (buf, rbuf);

  /* Log to file */
  if (g_fp_logfile)
    {
      log_write_to_file (g_fp_logfile, buf);
      log_write_to_file (g_fp_logfile, rbuf);
    }

  return 0;
}


/* Run the tests */
gint 
atcmd_run_test (struct lgsm_handle *lgsmh)
{
  gint i, j;
  gint ret;

  i = j = ret = 0;

  g_printf ("Starting tests ...\n");

  /* File log operations */
  log_test_dir ();
  ret = log_create_file ();

  if (!ret)
    {
      log_write_header_to_file (g_fp_logfile);

      /* List of commands whose values can be displayed */
      for (i = 0; i < ATCMD_NUMBER; i++)
	{
	  atcmd_command_main (lgsmh, list[i].string);
	}
    }
  else
    {
      g_printf ("Cannot open file :(\n");
      return 1;
    }

  /* List of numeric outputs whose values should not be displaed */
  for (j = 0; j < ATCMD_RETURNCHECK_NUMBER; j++, i++)
    {
      atcmd_return_checked_command_main (lgsmh, return_custom[j].string);
    }

  /* Close file */
  log_close_file (g_fp_logfile);
}

