/*
 * main.c 
 *
 * Used to for testing AT Commands. 
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
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <glib.h>
#include <libgsmd/libgsmd.h>
#include <libgsmd/pin.h>
#include <ui/callbacks.h>
#include <ui/interface.h>
#include <ui/support.h>
#include <at/pin.h>
#include <at/atcmd.h>

amc_item_t *g_run = NULL;

static char const *GS_GSMD_RESTART = "/etc/init.d/gsmd restart";

/* The main() function */
int 
main (gint argc, gchar *argv[])
{   
  GtkWidget *window = NULL; 

  g_run = g_new (amc_item_t, 1);

  /* gsmd and modem power on */
  system (GS_GSMD_RESTART);

  /* delayed call due to gsmd init delay */
  g_usleep (GSMD_DELAY);
  g_run->lgsmh = (struct lgsm_handle *) pin_gsm_init (g_run->lgsmh, g_run->pin);

  gtk_init (&argc, &argv);    

  window = (GtkWidget *) ui_support_create_window ();
  ui_support_combine_widget (window);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}
