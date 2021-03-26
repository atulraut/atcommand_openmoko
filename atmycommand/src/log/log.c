/*
 * log.c 
 *
 * Functions to store results to file.
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <at/atcmd.h>

#define LOG_DIRECTORY_MODE 0755

FILE *g_fp_logfile = NULL;

static gchar const *GS_LOG_DIRECTORY		= "/var/log/atmycommand/";
static gchar const *GS_TIME_FORMAT 	     	= "%Y-%m-%dT%H.%M.%S";
static gchar const *GS_LOG_EXTENSION 	     	= ".log";
static gchar const *GS_VERSION_COMMAND     	= "cat /etc/version";
static gchar const *GS_ISSUE_COMMAND 	     	= "cat /etc/issue | tail -2 | grep \"OpenMoko\"";
static gchar const *GS_KERNEL_COMMAND      	= "/bin/uname -a";
static gchar const *GS_DATE_COMMAND 	     	= "/bin/date";
static gchar const *GS_CLEAR_LOGS_COMMAND  	= "rm -f /var/log/atmycommand/*";

/* Test if log directory exists, else create it */
void
log_test_dir (void)
{
  GFileTest *directory_exists = NULL;
	
  /* Check if directory exists */
  if (!g_file_test (GS_LOG_DIRECTORY, G_FILE_TEST_EXISTS))
    {
      g_mkdir (GS_LOG_DIRECTORY, LOG_DIRECTORY_MODE);
    }
	
}

/* Create the log file */
gint
log_create_file (void)
{
  struct timeval tv;
  struct tm* ptm;
  gchar time_string[40];
  gchar log_file[100];

  g_stpcpy (log_file, GS_LOG_DIRECTORY);

  /* Get time */
  gettimeofday (&tv, NULL);
  ptm = localtime (&tv.tv_sec);
  
  /* Format string */
  strftime (time_string, sizeof (time_string), GS_TIME_FORMAT, ptm);

  g_strlcat (log_file, time_string, sizeof (log_file));
  g_strlcat (log_file, GS_LOG_EXTENSION, sizeof (log_file));

  g_fp_logfile = fopen (log_file, "a");

  if (g_fp_logfile == NULL)
    {
      g_printf ("oops! cannot create file!\n");
      return -1;
    }
  else
    {
      g_printf ("Opened!\n");
      return 0;	
    }
}

/* Write data to file */
void
log_write_to_file (FILE *fp, gchar *buf)
{
  gint ret = 0;

  g_assert (fp);
  g_assert (buf);

  ret = g_fprintf (fp, "%s\n", buf);
}

/* Execute shell script, or command, and return output */
gchar *
log_return_shell_result (gchar *return_string, gchar const *command)
{
  FILE *fp = NULL;

  g_assert (command);

  /* Clear buffer before assigning value */
  memset (return_string, ' ', strlen (return_string));

  fp = popen (command, "r");

  if (fp == NULL)
    return NULL;

  while (fgets (return_string, STDIN_BUF_SIZE, fp) != '\0')
    g_printf ("%s\n", return_string);

  pclose (fp);

  return ((gchar *) return_string);
}

/* Write log header content */
void
log_write_header_to_file (FILE *fp)
{
  gchar return_string [STDIN_BUF_SIZE];

  g_assert (fp);

  g_fprintf (fp, "--- Header ---\n");
  g_fprintf (fp, "Version: %s", log_return_shell_result (return_string, GS_VERSION_COMMAND));
  g_fprintf (fp, "Issue: %s", 	log_return_shell_result (return_string, GS_ISSUE_COMMAND));
  g_fprintf (fp, "Kernel: %s", 	log_return_shell_result (return_string, GS_KERNEL_COMMAND));
  g_fprintf (fp, "Date: %s", 	log_return_shell_result (return_string, GS_DATE_COMMAND));
  g_fprintf (fp, "\n--- Results ---\n");
}

/* Clear all log files */
void
log_clear_logs (void)
{
  system (GS_CLEAR_LOGS_COMMAND);
}

/* Close file */
void
log_close_file (FILE *fp)
{
  g_assert (fp);

  if (fp)
    fclose (fp);
}
