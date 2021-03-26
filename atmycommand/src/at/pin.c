/* libgsmd tool
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libgsmd/libgsmd.h>
#include <libgsmd/event.h>
#include <libgsmd/pin.h>
#include <glib.h>
#include <glib/gstdio.h>

#define PIN_SIZE 8

static gchar *pin;
static gchar pinbuf  [PIN_SIZE+1];
static gchar pinbuf2 [PIN_SIZE+1];

/* Pin handler */
static 
gint pin_handler (struct lgsm_handle *lh, gint evt, struct gsmd_evt_auxdata *aux)
{
  gint rc;
  gint type = aux->u.pin.type;
  gchar *newpin = NULL;

  g_debug ("EVENT: PIN request\n");
  g_printf ("EVENT: PIN request (type='%s') ", lgsm_pin_name (aux->u.pin.type));

  /* FIXME: read pin from STDIN and send it back via lgsm_pin */
  if (type == 1 && pin) 
    {
      g_debug ("type == 1 && pin\n");
      g_printf ("Auto-responding with pin `%s'\n", pin);
      lgsm_pin (lh, type, pin, NULL);
    }
  else 
    {
      do 
	{
	  g_debug ("do %s \n", rc);
	  g_printf ("Please enter %s: ", lgsm_pin_name (type));
	  rc = fscanf (stdin, "%8s", &pinbuf);
	}
      while (rc < 1);

      switch (type) 
	{
	case GSMD_PIN_SIM_PUK:
	case GSMD_PIN_SIM_PUK2:
	  do 
	    {
	      g_printf ("Please enter new PIN: ");
	      rc = fscanf (stdin, "%8s", &pinbuf2);
	      newpin = pinbuf2;
	      g_debug ("puk2\n");
	    }
	  while (rc < 1);
	  break;
	default:
	  g_debug ("default\n");
	  break;
	}

      return lgsm_pin (lh, type, pinbuf, newpin);
    }
  return 0;
}

/* Pin initialization */
gint 
pin_init (struct lgsm_handle *lh, const gchar *pin_preset)
{
  pin = (char *) pin_preset;
  return lgsm_evt_handler_register (lh, GSMD_EVT_PIN, &pin_handler);
}

/* Initialize gsm */
struct lgsmh_handle *
pin_gsm_init (struct lgsmh_handle *lgsmh, gchar *pin)
{
  lgsmh = (struct lgsmh_handle *) lgsm_init (LGSMD_DEVICE_GSMD);
	
  pin_init ((struct lgsm_handle *) lgsmh, (gchar *) pin);

  return lgsmh;
}
