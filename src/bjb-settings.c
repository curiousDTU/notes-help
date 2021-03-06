/* bjb-settings.c
 * Copyright (C) Pierre-Yves LUYTEN 2011 <py@luyten.fr>
 * 
 * bijiben is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bijiben is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "config.h"

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "bjb-bijiben.h"
#include "bjb-settings.h"
#include "bjb-settings-dialog.h"


struct _BjbSettingsPrivate
{
  /* Note edition settings */
  gchar *font;
  gchar *color;

  /* Default Provider */
  gchar *primary;
};


enum
{
  PROP_0,
  PROP_FONT,
  PROP_COLOR,
  PROP_PRIMARY,
  N_PROPERTIES
};

#define BJB_SETTINGS_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), BJB_TYPE_SETTINGS, BjbSettingsPrivate))

G_DEFINE_TYPE (BjbSettings, bjb_settings, G_TYPE_SETTINGS);

static void
bjb_settings_init (BjbSettings *object)
{    
  object->priv = 
  G_TYPE_INSTANCE_GET_PRIVATE(object,BJB_TYPE_SETTINGS,BjbSettingsPrivate);
}

static void
bjb_settings_finalize (GObject *object)
{
  G_OBJECT_CLASS (bjb_settings_parent_class)->finalize (object);
}

static void
bjb_settings_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  BjbSettings *settings = BJB_SETTINGS (object);

  switch (prop_id)
  {            
    case PROP_FONT:
      g_value_set_string (value, settings->priv->font);
      break;

    case PROP_COLOR:
      g_value_set_string (value, settings->priv->color);
      break;

    case PROP_PRIMARY:
      g_value_set_string (value, settings->priv->primary);
      break;
                                
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
bjb_settings_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  BjbSettings *settings = BJB_SETTINGS (object);

  switch (prop_id)
  {
    case PROP_FONT:
      settings->priv->font = g_value_dup_string(value) ; 
      break;

    case PROP_COLOR:
      settings->priv->color = g_value_dup_string(value);
      break;

    case PROP_PRIMARY:
      settings->priv->primary = g_value_dup_string (value);
      break;
            
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}


static void
bjb_settings_constructed (GObject *object)
{
  BjbSettings *self;
  GSettings   *settings;

  G_OBJECT_CLASS (bjb_settings_parent_class)->constructed (object);

  self = BJB_SETTINGS (object);
  settings = G_SETTINGS (object);


  g_settings_bind  (settings, "font",
                    self,     "font",
                    G_SETTINGS_BIND_DEFAULT);

  g_settings_bind  (settings, "color",
                    self,     "color",
                    G_SETTINGS_BIND_DEFAULT);

  g_settings_bind  (settings,  "default-location",
                    self,      "default-location",
                    G_SETTINGS_BIND_DEFAULT);
}


static void
bjb_settings_class_init (BjbSettingsClass *klass)
{
  GObjectClass* object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (BjbSettingsPrivate));

  object_class->constructed = bjb_settings_constructed;
  object_class->finalize = bjb_settings_finalize;
  object_class->get_property = bjb_settings_get_property;
  object_class->set_property = bjb_settings_set_property;
    
  g_object_class_install_property (object_class,PROP_FONT,
                                   g_param_spec_string("font",
                                                       "Notes Font",
                                                       "Font for Notes",
                                                       NULL,
                                                       G_PARAM_READWRITE | 
                                                       G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (object_class,PROP_COLOR,
                                   g_param_spec_string("color",
                                                       "New Notes Color",
                                                       "Default Color for New Notes",
                                                       NULL,
                                                       G_PARAM_READWRITE | 
                                                       G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (object_class,PROP_PRIMARY,
                                   g_param_spec_string("default-location",
                                                       "Primary Location",
                                                       "Default Provider for New Notes",
                                                       NULL,
                                                       G_PARAM_READWRITE | 
                                                       G_PARAM_STATIC_STRINGS));
}




BjbSettings *
bjb_settings_new (void)
{
  return g_object_new (BJB_TYPE_SETTINGS, "schema-id", "org.gnome.bijiben", NULL);
}



gchar *
bjb_settings_get_default_font           (BjbSettings *settings)
{
  return settings->priv->font;
}


gchar *
bjb_settings_get_default_color          (BjbSettings *settings)
{
  return settings->priv->color;
}


gchar *
bjb_settings_get_default_location       (BjbSettings *settings)
{
  return settings->priv->primary;
}


void
show_bijiben_settings_window (GtkWidget *parent_window)
{
  GtkDialog *dialog;

  dialog = bjb_settings_dialog_new (parent_window);
  /* result = */ gtk_dialog_run (dialog);
  gtk_widget_destroy (GTK_WIDGET (dialog));
}
