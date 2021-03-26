/*
 * linked-list.c 
 *
 * Linked list implementation to store AT+OUTPUT results
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <glib.h>
#include <glib/gstdio.h>
#include <string.h>
#include <at/atcmd.h>

extern amc_item_t *g_run;

/* Add a result to the linked list */
void
ll_add_to_list (char *buf, char *rbuf)
{
  amc_entry_t *x = NULL;

  g_assert (buf);
  g_assert (rbuf);

  x = g_new (amc_entry_t, 1);

  /* this needs to be changed to log level, no done yet? */
  g_printf ("%d\n", strlen (buf));
  g_printf ("%d\n", strlen (rbuf));

  x->command = g_strdup (buf);
  x->output  = g_strdup (rbuf);

  /* Add to list */
  g_run->amc_list = g_slist_append (g_run->amc_list, (gpointer) x);
}

/* Free each structure entry data */
void 
ll_free_gslist_memory (gpointer data, gpointer user_data)
{
  amc_entry_t *local;

  g_assert (data);
  local = (amc_entry_t *) data;

  if (local->command)
    g_free (local->command);

  if (local->output)
    g_free (local->output);
}

/* Free all memory */
void
ll_cleanup_all_memory (void)
{
  if (g_run)
    {
      if (g_run->amc_list)
	{
	  g_slist_foreach (g_run->amc_list, ll_free_gslist_memory, NULL);
	  g_slist_free (g_run->amc_list);
	}

      g_free (g_run);
    }
}
